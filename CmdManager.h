#ifndef __COMMAND_MANAGER__CMDMANAGER_H__
#define __COMMAND_MANAGER__CMDMANAGER_H__

//Tokenizer by Nate Pendelton

class CCmdManager
{
// To Get the Game time
CGameTimer *m_pTimer;     
public:
    CCmdManager( int keyBufferSize = 120 );
    ~CCmdManager();
    
    bool LoadCMDFile( const char* file );  // returns false upon load failure
    
    void Update( KEYBOARDDATA* keys, bool facingRight );
    
    const char* GetCurrentCommandName();
    
    void SetGameTimer(CGameTimer *t){m_pTimer=t;}
    
protected:
    PLCOMMAND* m_Commands;
    int m_CommandCount;  
    const char* m_CurrCommandName;

    //this is the Keyboard buffer
    PLCOMMANDFRAMEINPUT* m_KeyBuffer;
    short m_KeyBufferSize;
    short m_KeyIndex;

    inline int AdjustKeyIndex( int keyIndex, int increment )  
        { return ( keyIndex + increment + m_KeyBufferSize ) % m_KeyBufferSize; }
};

#endif

