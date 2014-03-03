//    Open Mugen is a redevelopment of Elecbyte's M.U.G.E.N wich will be 100% compatible to it
//    Copyright (C) 2004  Sahin Vardar
//
//    If you know bugs or have a wish on Open Muegn o
//    Feel free and email me: sahin_v@hotmail.com  ICQ:317502935
//    Web: http://openmugen.sourceforge.net/
//    --------------------------------------------------------------------------
//
//    This program is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.

//    You should have received a copy of the GNU General Public License
//    along with this program; if not, write to the Free Software
//    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
#ifndef __PLAYER__H
#define __PLAYER__H


class CPlayer
{
CAllocater         *m_pAlloc;
CVideoSystem       *m_pVideoSystem;
CSffManager         m_SffManager;
CAirManager         m_AirManager;
CStateManager       m_StateManager;  
CGameTimer         *m_pTimer;
CVirtualMachine    *m_pVMachine;
CControllerExecuter m_ControllerExec;
CCmdManager         m_CmdManager;
//Player information
float              x,y;
float              xVel,yVel;
float              nGround;
s32                nAnimNumber;
u32                nStateTime;
u8                 nStateType;
u8                 nPhysic;
u8                 nMoveType;
u8                 nSprPrio;
s16                nLife;
s16                nPower;
bool               bHitDefPresit;
bool               bHitCounterPresit;
bool               bMoveHitPresit;        
bool               bCtrl;
bool               bRightFaced;
bool               bDebugInfo;
bool               bHitDef;
bool               bAlive;
char               strCommand[50];
PLSTATEDEF         *lpCurrStatedef;
public:
PLAYERCONST         myPlayerConst;

       CPlayer();
       ~CPlayer();
       void SetPointers(CVideoSystem *p,CAllocater *a,CGameTimer *t);
       bool LoadPlayer(const char* strPlayer);
       void UpDatePlayer();
       void DrawPlayer();
//Set functions
      void SetVM(CVirtualMachine *p){m_pVMachine=p;}
      void SetPos(s16 xAxis,s16 yAxis){x=xAxis;y=yAxis;}
      void VelSetX(float xvel){xVel=xvel;}
      void VelSetY(float yvel){yVel=yvel;}
      void SetDebug(bool bDebug){bDebugInfo=bDebug;}
      void FaceLeft(){bRightFaced=false;}
      void FaceRight(){bRightFaced=true;}
//Set the the ground value of the stage
      void SetGroundValue(float yLimit){nGround=yLimit;} 
      
//Player Controllers
      void ChangeState(s32 nSateNumber);
      
//trigger functions
      char *GetCommand(){return strCommand;}
      bool IsPlayerAlive(){return bAlive;}
      s32  GetAnim(){return nAnimNumber;}
      ActionElement *GetCurrAnim(){return m_SffManager.GetCurrAnimation();}
      bool IsAnimAviable(s32 nAnim);
      bool IsCtrl(){return bCtrl;}

private:
      bool CheckState(PLSTATE* tempState);
      void ExecuteController(PLSTATE* tempState);
      void HandleFSM();  
      void HandlePhysic();
      void UpDateFacing();
      void Debug();

};

#endif
