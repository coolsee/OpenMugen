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
    m_KeyBuffer[ m_KeyIndex ].keyBitfield = 0; // buffer是用来存储上次的键值
  
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
    
    for( int a = 0; a < m_CommandCount; a++ )// 遍历所有命令
    {           
        int nTime = -1, nLastTime = -1;
        int currKeyIndex = 0;

		// 使用例子command = ~D, DF, F, x讲解
		// 最初从x判定，按下，且与要求一致，将记录最后的时间，然后currKeyIndex++，将buffer判定向前推进
		// F，DF，一致的时候向前走，直到~D一致，记录第一时间，判定是否超出。
        for( int b = currCommand->nHowManyCommand - 1; b >= 0; b-- )// 一个命令，判断是否匹配所有按键
        {
            bool bCommand = false;
            bool onRelease = (( currCommand->nCommand[ b ].keyModifier & PLC_KEYMOD_ON_RELEASE ) != 0 );// 按键是否需要放开
            bool onHold = (( currCommand->nCommand[ b ].keyModifier & PLC_KEYMOD_MUST_BE_HELD ) != 0 );// 是否要求按住
            bool use4Way = (( currCommand->nCommand[ b ].keyModifier & PLC_KEYMOD_DETECT_AS_4WAY ) != 0 );// 是否是四个方向
            bool banOtherInput = (( currCommand->nCommand[ b ].keyModifier & PLC_KEYMOD_BAN_OTHER_INPUT ) != 0 );// 是否禁止有其他按键按下
            int gameTicksToHold = currCommand->nCommand[ b ].gameTicksForHold; // 按键按下的时间
            int keyCode = currCommand->nCommand[ b ].keyCode;// 按键转码
            
            for( ; currKeyIndex < m_KeyBufferSize; currKeyIndex++ )// 每个键对所有buff处理！！！！
            {
                PLCOMMANDFRAMEINPUT* frameInput = &m_KeyBuffer[ AdjustKeyIndex( m_KeyIndex, -currKeyIndex ) ];// 从当前的输入键值，向前遍历
                bool keyDown = (( frameInput->keyBitfield & keyCode ) == keyCode );
                if( keyDown && !use4Way )// 需要按键按下，不是四个方向
                {
                    int keyCodeDirs = ( keyCode & PLC_ALL_DIRECTIONS_BITFIELD );
                    int frameInputDirs = ( frameInput->keyBitfield & PLC_ALL_DIRECTIONS_BITFIELD );
                    keyDown = !keyCodeDirs || ( keyCodeDirs == frameInputDirs );//按下的按钮是否是方向键，是则要与需求一致，不是，则正确，继续判定
                }
                
                bool buttonConditionsMet = false;
                
                // see how long it's been held                
                if( onRelease != keyDown )// 按键松开，并保持一定时间时间(keyDown&&!onRelease）
                {
                    int gameTicksHeld = 0;
                    for( int k = currKeyIndex + 1; k < m_KeyBufferSize; k++ )
                    {
                        PLCOMMANDFRAMEINPUT* frameInput2 = &m_KeyBuffer[ AdjustKeyIndex( m_KeyIndex, -k ) ];// 从当前的输入键值，向前遍历
                        bool keyDown2 = (( frameInput2->keyBitfield & keyCode ) == keyCode );
                        if( keyDown2 && !use4Way )// 按键按下，不是四个方向
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
                // 如果单键过关了，就记录开始结束时间，继续下一个按键，
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
			// bufer时间，即时命令有效的tick时间
           if( ( nLastTime > ( m_pTimer->GetGameTime()- currCommand->nBufferTime )) && ( nLastTime - nTime ) <= currCommand->nCommandTime )
            {
                m_CurrCommandName = currCommand->strCommand;
                PrintMessage("time:%5d, %s",m_pTimer->GetGameTime(), m_CurrCommandName);
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

