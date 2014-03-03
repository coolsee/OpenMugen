#include "global.h"
static const int skTokDefaultOperatorCount = 23;
static char sTokDefaultCommentChars[] = ";";
static char* sTokDefaultOperators[skTokDefaultOperatorCount] = 
{
    "~",
    "!",
    "+",
    "-",
    "=",
    "!=",
    "[",
    "]",
    "(",
    ")",
    "/",
    "$",
    ",",
    "<",
    ">",
    "<=",
    ">=",
    "&",
    "|",
    "^",
    "&&",
    "||",
    "*",
};

CTokenizer::CTokenizer( int bufferSize, char* commentChars, char** operators, int operatorCount )
{
//    Assert(( bufferSize > 0 ) && ( bufferSize < ( 1 << 30 ) );
    m_BufferSize = bufferSize;        
    m_Buffer = new char[ bufferSize ];
    m_CommentChars = commentChars ? commentChars : sTokDefaultCommentChars;
    
    if( operators )
    {
        m_Operators = operators;
 //       Assert( operatorCount >= 0 );
        m_OperatorCount = operatorCount;
    }
    else
    {
        m_Operators = sTokDefaultOperators;
        m_OperatorCount = skTokDefaultOperatorCount;
    }
    
    m_NumOperatorCharsRead = 0;
    
    m_Filename[0] = 0;
    m_FileBuffer = NULL;
    m_FileSize = 0;
    m_CurrFilePos = 0;
    m_CurrFileLine = 0;
    m_LastLinePos = 0;

    m_BufferIsNextToken = false;
    m_AtEndOfLine = false;
    m_AtEndOfFile = false;
    
    m_ReturnNegativeSeperatelyFromNumber = false;
    m_IsCaseSensitive = true;
    
    m_LastTokenWasQuotedString = false;
}

CTokenizer::~CTokenizer()
{
    if( m_FileBuffer )
        delete m_FileBuffer;
    delete m_Buffer;
}

bool CTokenizer::OpenFile( const char* filename )
{
    if( m_FileBuffer )
        return false;
        
    strcpy( m_Filename, filename );
    
    FILE* file = fopen( filename, "rb" );
    if( !file )
    {
        throw(CError("CTokenizer::OpenFile: File %s not found",filename));
        return false;
    }
        
    fseek( file, 0, SEEK_END );
    m_FileSize = ftell( file );
    if( !m_FileSize )
        return false;
        
    m_FileBuffer = new char[ m_FileSize ];
    
    fseek( file, 0, SEEK_SET );
    fread( m_FileBuffer, m_FileSize, 1, file );
    
    fclose( file );
    
    m_CurrFilePos = 0;
    m_CurrFileLine = 0;
    m_LastLinePos = 0;

    m_BufferIsNextToken = false;
    m_AtEndOfLine = false;
    m_AtEndOfFile = false;

    return true;
}

bool CTokenizer::CloseFile()
{
    if( !m_FileBuffer )
        return false;
        
    delete m_FileBuffer;
    m_FileSize = 0;
    m_Filename[0] = 0;
    m_FileBuffer = NULL;
    m_FileSize = 0;
    m_CurrFilePos = 0;
    m_CurrFileLine = 0;
    m_LastLinePos = 0;

    m_BufferIsNextToken = false;
    m_AtEndOfLine = false;
    m_AtEndOfFile = false;

    return true;
}

bool CTokenizer::AtEndOfLine()
{
    return m_AtEndOfLine;
}

bool CTokenizer::AtEndOfFile()
{
    return m_AtEndOfFile;
}

const char* CTokenizer::GetToken()
{
    if( !m_BufferIsNextToken )
    {
        if( m_AtEndOfFile || !m_FileBuffer )
            return NULL;
            
        m_LastTokenWasQuotedString = false;

        m_AtEndOfLine = false;
        bool haveHitSecondWhitespace = false;
        
        char* buf = m_Buffer;
        while( !m_AtEndOfFile && ( buf - m_Buffer < m_BufferSize ))
        {
            char c = m_FileBuffer[ m_CurrFilePos++ ];
            
            if( m_CurrFilePos >= m_FileSize )
            {
                m_AtEndOfFile = true;
                break;
            }
            
           // read quoted strings in literally with no processing
            if( c == '\"' )
            {
                // if there is something already in buffer, backup and return what is already there
                if( buf > m_Buffer )                 
                {
                    // rewind file pointer by one
                    m_CurrFilePos--;
                }
                else
                {
                    while(1)
                    {
                        c = m_FileBuffer[ m_CurrFilePos++ ];                        

                        if( m_CurrFilePos >= m_FileSize )
                        {
                            m_AtEndOfFile = true;
                            break;
                        }

                        if( c == '\"' )
                        {
                            // check for end of line/end of file
                            while( 1 )
                            {
                                c = m_FileBuffer[ m_CurrFilePos++ ];

                                if( m_CurrFilePos >= m_FileSize )
                                {
                                    m_AtEndOfFile = true;
                                    break;
                                }

                                if( c == '\n' )
                                {
                                    m_AtEndOfLine = true;
                                    m_CurrFileLine++;
                                    m_LastLinePos = m_CurrFilePos;
                                }
                                
                                if( !isspace( c ) )
                                {
                                    // rewind file pointer by one
                                    m_CurrFilePos--;
                                    break;
                                }
                            }
                            m_LastTokenWasQuotedString = true;
                            break;
                        }
                        (*buf) = c;
                        buf++;
                    }
                }
                break;
            }
            
            // skip chars after comment chars till end of line
            bool hitCommentChar = false;
            int commentCharCount = m_CommentChars ? strlen( m_CommentChars ) : 0;
            for( int a = 0; a < commentCharCount; a++ )
            {
                if( c == m_CommentChars[ a ] )
                {
                    hitCommentChar = true;
                    while( 1 )
                    {
                        c = m_FileBuffer[ m_CurrFilePos++ ];
                        if( m_CurrFilePos >= m_FileSize )
                        {
                            m_AtEndOfFile = true;                        
                            break;
                        }                  
                        if( c == '\n' )
                        {
                            m_CurrFileLine++;
                            m_LastLinePos = m_CurrFilePos;
                            break;
                        } 
                    }
                }
            }       
            
            if( hitCommentChar )
            {
                if( buf > m_Buffer )
                    break;
            }
            else if( !isspace( c ) )
            {                
                // check for operators and return them as seperate strings from other things, even if no whitespace between
                bool hitOperator = false, breakToReturnToken = false, negativeNumber = false;

                if( ( c == '-' ) && !m_ReturnNegativeSeperatelyFromNumber )
                {
                    char nextC = m_FileBuffer[ m_CurrFilePos ];
                    if( isdigit( nextC ) || ( nextC == '.' ) )
                    {
                        negativeNumber = true;
                    }
                }
                
                if( !negativeNumber )
                {
                    for( int a = 0; a < m_OperatorCount; a++ )
                    {
                        bool prevCharsMatched = ( strlen( m_Operators[ a ] ) > m_NumOperatorCharsRead );
                        for( int b = 0; prevCharsMatched && ( b < m_NumOperatorCharsRead ); b++ )
                        {
                            if( m_Buffer[ b ] != ( m_Operators[ a ] )[ b ] )
                                prevCharsMatched = false;
                        }
                                            
                        if( prevCharsMatched && ( c == ( m_Operators[ a ] )[ m_NumOperatorCharsRead ] ))
                        {
                            hitOperator = true;
                             // if there is something already in buffer, backup and return what is already there
                            if( !m_NumOperatorCharsRead && ( buf > m_Buffer ))
                            {
                                // rewind file pointer by one
                                m_CurrFilePos--;
                                breakToReturnToken = true;
                            }
                            else
                            {
                                (*buf) = c;
                                buf++;  
                                m_NumOperatorCharsRead++;                                  
                            }
                            break;
                        }
                    }
                }
                                
                if( breakToReturnToken )
                    break;
                
                if( !hitOperator )
                {
                    // we want to check whitespace after token to see if end of line/file bits should be set
                    if( !m_NumOperatorCharsRead && !haveHitSecondWhitespace )
                    {
                        (*buf) = c;
                        buf++;
                    }
                    else
                    {
                        // rewind file pointer by one
                        m_CurrFilePos--;
                        break;
                    }
                }
            }
            else
            {
                if( c == '\n' )
                {
                    m_AtEndOfLine = true;
                    m_CurrFileLine++;
                    m_LastLinePos = m_CurrFilePos;
                }
                haveHitSecondWhitespace = ( buf > m_Buffer );
            }
        }
        *buf = 0;
        m_NumOperatorCharsRead = 0;
    }
    
    m_BufferIsNextToken = false;
    return m_Buffer;
}

bool CTokenizer::GetToken( char* destString, int maxLength )
{
    if( !GetToken() )
        return false;

    strncpy( destString, m_Buffer, maxLength > m_BufferSize ? m_BufferSize : maxLength );

    return true;
}

bool CTokenizer::CheckToken( const char* stringToLookFor, bool consumeIfMatch )
{
    if( !m_BufferIsNextToken )
    {
        if( !GetToken() )
            return false;
    }
        
    bool result = m_IsCaseSensitive ? ( strcmp( stringToLookFor, m_Buffer ) == 0 ) : ( strcmpi( stringToLookFor, m_Buffer ) == 0 ); 
    m_BufferIsNextToken = consumeIfMatch ? !result : true;
    return result;    
}

float CTokenizer::GetFloat()
{
    if( !m_BufferIsNextToken )
    {
        if( !GetToken() )
            return 0.0f;
    }
    
    m_BufferIsNextToken = false;
    return (float)atof( m_Buffer ); 
}

int CTokenizer::GetInt()
{
    if( !m_BufferIsNextToken )
    {
        if( !GetToken() )
            return 0;
    }
    
    m_BufferIsNextToken = false;
    return atoi( m_Buffer ); 
}

bool CTokenizer::CheckTokenIsNumber()
{
    if( !m_BufferIsNextToken )
    {
        if( !GetToken() )
            return false;
    }
    
    m_BufferIsNextToken = true;
    
    if( m_LastTokenWasQuotedString )
        return false;
    
    int len = strlen( m_Buffer );
    char* c = m_Buffer;
    
    for( int a = 0; a < len; a++ )
    {
        if( (( *c < '0' ) || ( *c > '9' )) && ( *c != '.' ) && !( !m_ReturnNegativeSeperatelyFromNumber && ( a == 0 ) && ( *c == '-' ) && ( len > 1 ) ) )
            return false;
        c++;
    }
    
    return ( len > 0 );
}

bool CTokenizer::CheckTokenIsQuotedString()
{
    if( !m_BufferIsNextToken )
    {
        if( !GetToken() )
            return false;
    }
    
    m_BufferIsNextToken = true;
    return m_LastTokenWasQuotedString;    
}
