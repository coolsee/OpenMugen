#include "global.h"


CCmdManager::CCmdManager( int keyBufferSize )
{
    m_Commands = NULL;
    m_CommandCount = 0;
    m_CurrCommandName = NULL;
    
    m_KeyBuffer = new PLCOMMANDFRAMEINPUT[ keyBufferSize ];
    m_KeyBufferSize = keyBufferSize;
    m_KeyIndex = 0;
    memset( m_KeyBuffer, 0, keyBufferSize );
}

CCmdManager::~CCmdManager()
{
    delete []m_Commands;
    delete m_KeyBuffer;
}

bool CCmdManager::LoadCMDFile( const char* file )
{
    int defaultCommandTime = 15;
    int defaultBufferTime = 1;
    
    m_CommandCount = 0;

    CTokenizer tok;
    //changed this to throw a exception
    if( !tok.OpenFile( file ) )
    {
        throw(CError("CCmdManager::LoadCMDFile : Can't open %s",file));
        return false;
    }
        
    // get count first to set up memory        
    while( !tok.AtEndOfFile() )
    {
        bool foundSomething = false;
        if( tok.CheckToken( "command.time" ) )
        {
            foundSomething = true;
            if( !tok.CheckToken( "=" ) )
            {
            }
            if( tok.CheckTokenIsNumber() )
            {
                defaultCommandTime = tok.GetInt();
            }            
        }
        
        if( tok.CheckToken( "command.buffer.time" ) )
        {
            foundSomething = true;
            if( !tok.CheckToken( "=" ) )
            {
            }
            if( tok.CheckTokenIsNumber() )
            {
                defaultBufferTime = tok.GetInt();
            }
        }
        
        if( tok.CheckToken( "[" ) )
        {
            foundSomething = true;
            if( tok.CheckToken( "Command" ) )
            {
                if( tok.CheckToken( "]" ) )
                {
                    m_CommandCount++;
                }       
            }
        }        
        if( !foundSomething )
        {
            tok.GetToken(); // skip it
        }
    }
        
    tok.CloseFile();
 
    if( !tok.OpenFile( file ) )
        return false;
 
    m_Commands = new PLCOMMAND[ m_CommandCount ];
    PLCOMMAND* command = m_Commands;
    
    while( !tok.AtEndOfFile() )
    {
        bool foundCommand = false;
        if( tok.CheckToken( "[" ) )
        {
            if( tok.CheckToken( "Command" ) )
            {
                if( !tok.CheckToken( "]" ) )
                {
                }
                
                foundCommand = true;
                command->nCommandTime = defaultCommandTime;
                command->nBufferTime = defaultBufferTime;
                command->strCommand[0] = 0;
                command->nHowManyCommand = 0;
                
                while( command->nHowManyCommand < MAXCOMMAND && !tok.CheckToken( "[", false ) && !tok.AtEndOfFile() )
                {
                    if( tok.CheckToken( "name" ) )
                    {
                        if( !tok.CheckToken( "=" ) )
                        {
                        }
                        
                        strcpy( command->strCommand, tok.GetToken() );                    
                    }
                    else if( tok.CheckToken( "command" ) )
                    {
                        if( !tok.CheckToken( "=" ) )
                        {
                        } 
                        
                        while( !tok.AtEndOfLine() )
                        {
                            const char* token = tok.GetToken();
                           
                            if( !strcmp( token, "~" ) )
                            {
                                command->nCommand[ command->nHowManyCommand ].keyModifier += PLC_KEYMOD_ON_RELEASE;
                                if( tok.CheckTokenIsNumber() )
                                {
                                    command->nCommand[ command->nHowManyCommand ].gameTicksForHold = tok.GetInt();
                                }
                                else
                                {
                                    command->nCommand[ command->nHowManyCommand ].gameTicksForHold = 1;
                                }
                            }
                            else if( !strcmp( token, "+" ) )
                            {
                            }
                            else if( !strcmp( token, "/" ) )
                            {
                                command->nCommand[ command->nHowManyCommand ].keyModifier += PLC_KEYMOD_MUST_BE_HELD;
                            }
                            else if( !strcmp( token, "$" ) )
                            {
                                command->nCommand[ command->nHowManyCommand ].keyModifier += PLC_KEYMOD_DETECT_AS_4WAY;
                            }
                            else if( !strcmp( token, ">" ) )
                            {
                                command->nCommand[ command->nHowManyCommand ].keyModifier += PLC_KEYMOD_BAN_OTHER_INPUT;
                            }
                            else if( !strcmp( token, "," ) )
                            {
                                command->nHowManyCommand++;
                            }                            
                            else if( !strcmp( token, "D" ) )
                            {
                                command->nCommand[ command->nHowManyCommand ].keyCode += PLC_KEYCODE( KEY_DOWN );
                            }
                            else if( !strcmp( token, "U" ) )
                            {
                                command->nCommand[ command->nHowManyCommand ].keyCode += PLC_KEYCODE( KEY_UP );
                            }
                            else if( !strcmp( token, "B" ) )
                            {
                                command->nCommand[ command->nHowManyCommand ].keyCode += PLC_KEYCODE( KEY_LEFT );
                            }
                            else if( !strcmp( token, "F" ) )
                            {
                                command->nCommand[ command->nHowManyCommand ].keyCode += PLC_KEYCODE( KEY_RIGHT );
                            }
                            else if( !strcmp( token, "DB" ) )
                            {
                                command->nCommand[ command->nHowManyCommand ].keyCode += PLC_KEYCODE( KEY_DOWN ) + PLC_KEYCODE( KEY_LEFT );
                            }
                            else if( !strcmp( token, "DF" ) )
                            {
                                command->nCommand[ command->nHowManyCommand ].keyCode += PLC_KEYCODE( KEY_DOWN ) + PLC_KEYCODE( KEY_RIGHT );
                            }
                            else if( !strcmp( token, "UF" ) )
                            {
                                command->nCommand[ command->nHowManyCommand ].keyCode += PLC_KEYCODE( KEY_UP ) + PLC_KEYCODE( KEY_LEFT );
                            }
                            else if( !strcmp( token, "UB" ) )
                            {
                                command->nCommand[ command->nHowManyCommand ].keyCode += PLC_KEYCODE( KEY_UP ) + PLC_KEYCODE( KEY_LEFT );
                            }
                            else if( !strcmp( token, "a" ) )
                            {
                                command->nCommand[ command->nHowManyCommand ].keyCode += PLC_KEYCODE( KEY_BUTTON_A );
                            }
                            else if( !strcmp( token, "b" ) )
                            {
                                command->nCommand[ command->nHowManyCommand ].keyCode += PLC_KEYCODE( KEY_BUTTON_B );
                            }
                            else if( !strcmp( token, "c" ) )
                            {
                                command->nCommand[ command->nHowManyCommand ].keyCode += PLC_KEYCODE( KEY_BUTTON_C );
                            }
                            else if( !strcmp( token, "x" ) )
                            {
                                command->nCommand[ command->nHowManyCommand ].keyCode += PLC_KEYCODE( KEY_BUTTON_X );
                            }
                            else if( !strcmp( token, "y" ) )
                            {
                                command->nCommand[ command->nHowManyCommand ].keyCode += PLC_KEYCODE( KEY_BUTTON_Y );
                            }
                            else if( !strcmp( token, "z" ) )
                            {
                                command->nCommand[ command->nHowManyCommand ].keyCode += PLC_KEYCODE( KEY_BUTTON_Z );
                            }
                            else if( !strcmp( token, "s" ) )
                            {
                                command->nCommand[ command->nHowManyCommand ].keyCode += PLC_KEYCODE( KEY_BUTTON_START );
                            }
                        }
                        command->nHowManyCommand++;
                    }
                    else if( tok.CheckToken( "time" ) )
                    {
                        if( !tok.CheckToken( "=" ) )
                        {
                        } 
                        
                        if( !tok.CheckTokenIsNumber() )
                        {
                        }
                        
                        command->nCommandTime = tok.GetInt();
                    }
                    else if( tok.CheckToken( "buffer.time" ) )
                    {
                        if( !tok.CheckToken( "=" ) )
                        {
                        } 
                        
                        if( !tok.CheckTokenIsNumber() )
                        {
                        }
                        
                        command->nBufferTime = tok.GetInt();
                    }
                }
                                
                command++;                
            }
        } 
        if( !foundCommand )
            tok.GetToken(); // skip it
    }
 
    tok.CloseFile();
    return true;
}

void CCmdManager::Update( KEYBOARDDATA* keys, bool facingRight )
{
    m_CurrCommandName = NULL;
    m_KeyBuffer[ m_KeyIndex ].keyBitfield = 0;
  
    m_KeyBuffer[ m_KeyIndex ].gameTicks = m_pTimer->GetGameTime();

    // add current keystrokes to input buffer
    for( int k = 0; k < KEY_COUNT; k++ )
    {
        if( keys->keyInfo[ k ].isPressed )
        {
            if( ( k == KEY_LEFT ) && !facingRight )
            {
                m_KeyBuffer[ m_KeyIndex ].keyBitfield += PLC_KEYCODE( KEY_RIGHT );
            }
            else if( ( k == KEY_RIGHT ) && !facingRight )
            {
                m_KeyBuffer[ m_KeyIndex ].keyBitfield += PLC_KEYCODE( KEY_LEFT );
            }
            else
            {
                m_KeyBuffer[ m_KeyIndex ].keyBitfield += PLC_KEYCODE( k );
            }
        }    
    }

    PLCOMMAND* currCommand = m_Commands;
    
    for( int a = 0; a < m_CommandCount; a++ )
    {           
        int nTime = -1, nLastTime = -1;
        int currKeyIndex = 0;

        for( int b = currCommand->nHowManyCommand - 1; b >= 0; b-- )
        {
            bool bCommand = false;
            bool onRelease = (( currCommand->nCommand[ b ].keyModifier & PLC_KEYMOD_ON_RELEASE ) != 0 );
            bool onHold = (( currCommand->nCommand[ b ].keyModifier & PLC_KEYMOD_MUST_BE_HELD ) != 0 );
            bool use4Way = (( currCommand->nCommand[ b ].keyModifier & PLC_KEYMOD_DETECT_AS_4WAY ) != 0 );
            bool banOtherInput = (( currCommand->nCommand[ b ].keyModifier & PLC_KEYMOD_BAN_OTHER_INPUT ) != 0 );
            int gameTicksToHold = currCommand->nCommand[ b ].gameTicksForHold;
            int keyCode = currCommand->nCommand[ b ].keyCode;
            
            for( ; currKeyIndex < m_KeyBufferSize; currKeyIndex++ )
            {
                PLCOMMANDFRAMEINPUT* frameInput = &m_KeyBuffer[ AdjustKeyIndex( m_KeyIndex, -currKeyIndex ) ];
                bool keyDown = (( frameInput->keyBitfield & keyCode ) == keyCode );
                if( keyDown && !use4Way )
                {
                    int keyCodeDirs = ( keyCode & PLC_ALL_DIRECTIONS_BITFIELD );
                    int frameInputDirs = ( frameInput->keyBitfield & PLC_ALL_DIRECTIONS_BITFIELD );
                    keyDown = !keyCodeDirs || ( keyCodeDirs == frameInputDirs );
                }
                
                bool buttonConditionsMet = false;
                
                // see how long it's been held                
                if( onRelease != keyDown )
                {
                    int gameTicksHeld = 0;
                    for( int k = currKeyIndex + 1; k < m_KeyBufferSize; k++ )
                    {
                        PLCOMMANDFRAMEINPUT* frameInput2 = &m_KeyBuffer[ AdjustKeyIndex( m_KeyIndex, -k ) ];
                        bool keyDown2 = (( frameInput2->keyBitfield & keyCode ) == keyCode );
                        if( keyDown2 && !use4Way )
                        {
                            int keyCodeDirs = ( keyCode & PLC_ALL_DIRECTIONS_BITFIELD );
                            int frameInputDirs = ( frameInput2->keyBitfield & PLC_ALL_DIRECTIONS_BITFIELD );
                            keyDown2 = !keyCodeDirs || ( keyCodeDirs == frameInputDirs );
                        }  
                        if( keyDown2 )
                        {
                            gameTicksHeld++;
                            if( onHold )
                            {
                                buttonConditionsMet = keyDown;
                                break;
                            }
                            else if( onRelease )
                            {
                                if( gameTicksHeld >= gameTicksToHold )
                                {
                                    buttonConditionsMet = true;
                                    break;
                                }
                            }
                            else
                            {
                                buttonConditionsMet = ( b < currCommand->nHowManyCommand - 1 );
                                break;
                            }
                        }
                        else
                        {
                            buttonConditionsMet = !( onHold || onRelease );    
                            break;
                        }                        
                    }
                }
                
                if( buttonConditionsMet )
                {
                    //if its the first element store the time of it
                    if( b == 0 )
                    {
                        nTime = frameInput->gameTicks;
                    }
                    
                    if( b == ( currCommand->nHowManyCommand - 1 ))
                    {
                        nLastTime = frameInput->gameTicks;   
                    }
                    
                    bCommand = true;
                    currKeyIndex++;
                    break;                    
                }
           }
            if( !bCommand )
                break;            
        }
        
        if( ( nTime >= 0 ) && ( nLastTime > 0 ) )
        {
            // the last button of the sequenz must be pressed int the Current game tick to
            // be valid and then it must be check for how long it has taken to do the input
           // int gameTicks = GetGameTicks();
           if( ( nLastTime >= ( m_pTimer->GetGameTime()- currCommand->nBufferTime )) && ( nLastTime - nTime ) <= currCommand->nCommandTime )
            {
                m_CurrCommandName = currCommand->strCommand;
                PrintMessage("%s",m_CurrCommandName);
                break;
            }
        }
        currCommand++;
    }

    if( ++m_KeyIndex >= m_KeyBufferSize )
        m_KeyIndex = 0;
}

const char* CCmdManager::GetCurrentCommandName()  
{ 
    return m_CurrCommandName; 
}

