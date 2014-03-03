#ifndef __GAMETIMER__H
#define __GAMETIMER__H

class CGameTimer
{
u32   nGameTime;
bool  bPause;
      
public:
    void ResetTimer(){nGameTime=0;bPause=false;}
    void UpdateTimer(){if(!bPause)nGameTime++;}
    u32  GetGameTime(){return nGameTime;}
    void Pause(){bPause=true;}
    void Resume(){bPause=false;}
};



#endif
