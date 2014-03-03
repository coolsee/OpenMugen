#ifndef __ENGINE__H
#define __ENGINE__H

class CEngine
{
CPlayer player1,player2,player3,player4;
CMemManager  *m_pMemManager;
CVideoSystem *m_pVideoSystem;
CGameTimer   *m_pTimer;
CVirtualMachine *m_pVMp1;       
CVirtualMachine *m_pVMp2;       
public:
  CEngine();
  ~CEngine();

  void ResetEngine();
  void RunEngine();
  void InitEngine(CMemManager *m,CVideoSystem *v,CGameTimer *t);           
      
};

#endif
