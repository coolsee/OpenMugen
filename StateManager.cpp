//    Open Mugen is a redevelopment of Elecbyte's M.U.G.E.N wich will be 100% compatible to it
//    Copyright (C) 2004  Sahin Vardar
//
//    If you know bugs or have a wish on Open Muegn or (money/girls/a car) for me ;-)
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

#include "global.h"


//OP_CODE table
char *strOpCode[] =
{
    "OP_PUSH",
    "OP_POP",
    "OP_ADD",
    "OP_SUB",
    "OP_MUL",
    "OP_DIV",
    "OP_EQUAL",
    "OP_NOTEQUAL",
    "OP_LESS",
    "OP_GREATER",
    "OP_LESSEQUAL",
    "OP_GRAETEREQUAL",
    "OP_INTERVALOP1",
    "OP_INTERVALOP2",
    "OP_INTERVALOP3",
    "OP_INTERVALOP4",
    "OP_INTERVALOP5",
    "OP_INTERVALOP6",
    "OP_INTERVALOP7",
    "OP_INTERVALOP8",
    "OP_LOGNOT",
    "OP_LOGAND",
    "OP_LOGOR",
    "OP_LOGXOR",
    "OP_NOT",
    "OP_AND",
    "OP_OR",
    "OP_XOR",
    "OP_SQUARE",
    "OP_NEG",
    "OP_Abs",
    "OP_Acos",
    "OP_Alive",
    "OP_Anim",
    "OP_AnimElem",
    "OP_AnimElemNo",
    "OP_AnimElemTime",
    "OP_AnimExist",
    "OP_AnimTime",
    "OP_Asin",
    "OP_Atan",
    "OP_AuthorName",
    "OP_BackEdgeBodyDist",
  "OP_BackEdgeDist",
  "OP_CanRecover",
  "OP_Ceil",
  "OP_Command",
  "OP_Const",
  "OP_Cos",
  "OP_Ctrl",
  "OP_DrawGame",
  "OP_EOP",
  "OP_Exp",
  "OP_Facing",
  "OP_Floor",
  "OP_FrontEdgeBodyDist",
  "OP_FrontEdgeDist",
  "OP_FVar",
  "OP_GameTime",
  "OP_GetHitVar",
  "OP_HitCount",
  "OP_HitDefAttr",
  "OP_HitFall",
  "OP_HitOver",
  "OP_HitPauseTime",
  "OP_HitShakeOver",
  "OP_HitVel",
  "OP_ID",
  "OP_IfElse",
  "OP_InGuardDist",
  "OP_IsHelper",
  "OP_IsHomeTeam",
  "OP_Life",
  "OP_LifeMax",
  "OP_Log",
  "OP_Ln",
  "OP_Lose",
  "OP_MatchNo",
  "OP_MatchOver",
  "OP_MoveContact",
  "OP_MoveGuarded",
  "OP_MoveHit",
  "OP_MoveType",
  "OP_MoveReversed",
  "OP_Name",
  "OP_NumEnemy",
  "OP_NumExplod",
  "OP_NumHelper",
  "OP_NumPartner",
  "OP_NumProj",
  "OP_NumProjID",
  "OP_NumTarget",
  "OP_P1Name",
  "OP_P2BodyDist",
  "OP_P2Dist",
  "OP_P2Life",
  "OP_P2MoveType",
  "OP_P2Name",
  "OP_P2StateNo",
  "OP_P2StateType",
  "OP_P3Name",
  "OP_P4Name",
  "OP_PalNo",
  "OP_ParentDist",
  "OP_Pi",
  "OP_Pos",
  "OP_Power",
  "OP_PowerMax",
  "OP_PlayerIDExist",
  "OP_PrevStateNo",
  "OP_ProjCancelTime",
  "OP_ProjContact",
  "OP_ProjContactTime",
  "OP_ProjGuarded",
  "OP_ProjGuardedTime",
  "OP_ProjHit",
  "OP_ProjHitTime",
  "OP_Random",
  "OP_RootDist",
  "OP_RoundNo",
  "OP_RoundsExisted",
  "OP_RoundState",
  "OP_ScreenPos",
  "OP_SelfAnimExist",
  "OP_Sin",
  "OP_StateNo",
  "OP_StateType",
  "OP_SysFVar",
  "OP_SysVar",
  "OP_Tan",
  "OP_TeamMode",
  "OP_TeamSide",
  "OP_TicksPerSecond",
  "OP_Time",
  "OP_TimeMod",
  "OP_UniqHitCount",
  "OP_Var",
  "OP_Vel",
  "OP_Win",
  "OP_MOD",
  "OP_NOP",
   

};
//Constructor
CStateManager::CStateManager()
{
	

}
//Destructor
CStateManager::~CStateManager()
{
    
}

//restet after clean up
void CStateManager::Reset()
{
     nTotalStateDef=0;
     nTotalStateDefSize=100;
     nCurrInst=0;
     lpStateDefList=(PLSTATEDEF*)m_pAlloc->Alloc(sizeof(PLSTATEDEF)*nTotalStateDefSize);
     nCurrTrigger=0;
}

void CStateManager::ReallocStatedef(u16 index)
{
     lpStateDefList[index].lpState=(PLSTATE*)m_pAlloc->Realloc(lpStateDefList[index].lpState,sizeof(PLSTATE)*lpStateDefList[index].nHowManyState);
     
     for(int i=0;i<lpStateDefList[index].nHowManyState;i++)
     {
         lpStateDefList[index].lpState[i].triggers=(PLTRIGGER*)m_pAlloc->Realloc(lpStateDefList[index].lpState[i].triggers,
                                                         sizeof(PLTRIGGER)*lpStateDefList[index].lpState[i].nHowManyTriggers);
     }
}

//frees unused memory
void CStateManager::ReallocManager()
{
     
     ReallocStatedef(nTotalStateDef-1);
     
     lpStateDefList=(PLSTATEDEF*)m_pAlloc->Realloc(lpStateDefList,sizeof(PLSTATEDEF)*nTotalStateDef);
     
}

bool CStateManager::IsStateDefAviable(s32 nStateDefNum)
{
     for(s32 i=0;i < nTotalStateDef;i++)
     {
      if(lpStateDefList[i].StateNumber==nStateDefNum)
      {
         //make this state invalide to overwrite it 
         lpStateDefList[i].StateNumber=-11;                                           
         return true;
      }   
     }
     return false;
}

//Add a new statedef in the list
void CStateManager::AddStateDef(s32 nStateDefNum)
{
//    PrintMessage("AddStateDef %i",nStateDefNum);
    
     if( IsStateDefAviable(nStateDefNum) )
        PrintMessage("Overwriting StateDef %i",nStateDefNum);                             
         
     if(nTotalStateDef!=0)
        ReallocStatedef(nTotalStateDef-1);                  
     
     if( nTotalStateDef > nTotalStateDefSize -1)
     {
         nTotalStateDefSize+=100;
         lpStateDefList=(PLSTATEDEF*)m_pAlloc->Realloc(lpStateDefList,sizeof(PLSTATEDEF)*nTotalStateDefSize);
     }
     
     lpStateDefList[nTotalStateDef].StateNumber=nStateDefNum;
     
     nTotalState=0;
     
     nTotalStateSize=100;
     lpStateDefList[nTotalStateDef].lpState=(PLSTATE*)m_pAlloc->Alloc(sizeof(PLSTATE)*nTotalStateSize);

     nTotalStateDef++;
     
     //Set default values
     SetDefaultStatedef();
     

}

void CStateManager::SetStateDefType(u8 nType)
{
     lpStateDefList[nTotalStateDef-1].type=nType;
     
}
void CStateManager::SetStateMoveType(u8 nType)
{
    lpStateDefList[nTotalStateDef-1].movetype=nType;
}

void CStateManager::SetStatePhysicType(u8 nType)
{
     lpStateDefList[nTotalStateDef-1].physics=nType;
}
//Sets default values to the Statedef
void CStateManager::SetDefaultStatedef()
{
     lpStateDefList[nTotalStateDef-1].type            =stand;
     lpStateDefList[nTotalStateDef-1].movetype        =idle;
     lpStateDefList[nTotalStateDef-1].physics         =none;
     lpStateDefList[nTotalStateDef-1].nAnim           =-1;
     lpStateDefList[nTotalStateDef-1].Velset.x        =-3333;
     lpStateDefList[nTotalStateDef-1].Velset.y        =-3333;
     lpStateDefList[nTotalStateDef-1].bCtrl           =-1;
     lpStateDefList[nTotalStateDef-1].nPoweradd       =-3333;
     lpStateDefList[nTotalStateDef-1].bFacep2         =false;
     lpStateDefList[nTotalStateDef-1].nJuggle         =-3333;
     lpStateDefList[nTotalStateDef-1].bHitdefpersist  =false;
     lpStateDefList[nTotalStateDef-1].bHitcountpersist=false;
     lpStateDefList[nTotalStateDef-1].nSprpriority    =255;       
     
}

void CStateManager::SetStateAnim(s32 nAnim)
{
     lpStateDefList[nTotalStateDef-1].nAnim=nAnim;
}
void CStateManager::SetStateCtrl(s8 nCtrl)
{
     lpStateDefList[nTotalStateDef-1].bCtrl=nCtrl;
}
void CStateManager::SetStatePowerAdd(s16 nPowerAdd)
{
   lpStateDefList[nTotalStateDef-1].nPoweradd=nPowerAdd;
}
void CStateManager::SetStateJuggle(s16 nJuggle)
{
     lpStateDefList[nTotalStateDef-1].nJuggle=nJuggle;
}

void CStateManager::SetStateHitDefPresit(bool bHitDef)
{
    lpStateDefList[nTotalStateDef-1].bHitdefpersist=bHitDef;
}
void CStateManager::SetMoveHitPresit(bool bMoveHit)
{
    lpStateDefList[nTotalStateDef-1].bMovehitpersist=bMoveHit;
}

void CStateManager::SetStateHitCounterPresit(bool bHitCounter)
{
  lpStateDefList[nTotalStateDef-1].bHitcountpersist=bHitCounter;
}
void CStateManager::SetSprPriority(u8 nSprpriority)
{
  lpStateDefList[nTotalStateDef-1].nSprpriority=nSprpriority;
}

void CStateManager::SetStateFaceP2(bool bFaceP2)
{
  lpStateDefList[nTotalStateDef-1].bFacep2=bFaceP2;       
}

void CStateManager::SetVelSet(float x,float y)
{
  lpStateDefList[nTotalStateDef-1].Velset.x=x;
  lpStateDefList[nTotalStateDef-1].Velset.y=y;
  
}

//Add a State tothe current Statedef
void CStateManager::AddState(s32 nStateNum,char* strSomeNumber)
{
  //  PrintMessage("Add state %i",nStateNum);
     if(nTotalState > nTotalStateSize-1)
     {
                    
          nTotalStateSize+=100;
          lpStateDefList[nTotalStateDef-1].lpState=(PLSTATE*)m_pAlloc->Realloc(lpStateDefList[nTotalStateDef].lpState,
                                                                             sizeof(PLSTATE)*nTotalStateSize);
     }
    
     lpStateDefList[nTotalStateDef-1].lpState[nTotalState].nStateNumber=nStateNum;
     
     nCurrTrigger=0;
     nTriggerListSize=100;

     lpStateDefList[nTotalStateDef-1].lpState[nTotalState].triggers=(PLTRIGGER*)m_pAlloc->Alloc(sizeof(PLTRIGGER)*nTriggerListSize);
     
     nTotalState++;
     lpStateDefList[nTotalStateDef-1].nHowManyState=nTotalState;
     
     nCurrInst=0;
  
}
//Now save the controller type wich would be executeted
void CStateManager::AddTypeToState(u16 nType)
{

    lpStateDefList[nTotalStateDef-1].lpState[nTotalState-1].nType=nType;

}

PLSTATEDEF* CStateManager::GetCurrStateDef()
{
   
    return &lpStateDefList[nTotalStateDef-1];        
}

void* CStateManager::GetController()
{
	return NULL;
	//	return lpCurrent->lpController;
}

//Cleans up ;-)
void CStateManager::CleanUp()
{
     
}
//Add Instruction to currrent trigger
void CStateManager::AddInstruction(Uint16 nOpCode,float value,const char *strValue)
{
          PrintMessage("AddInstruction = %s %f %s(%i)",strOpCode[nOpCode],value,strValue,nOpCode);

          pInst[nCurrInst].n_OpCode=nOpCode;
          pInst[nCurrInst].Value=value;
          pInst[nCurrInst].strValue=NULL;
          
          //only add a string if we need one
          if(strValue[0]!='#')
          {
                pInst[nCurrInst].strValue=new char[strlen(strValue)+1];   
                 strcpy(pInst[nCurrInst].strValue,strValue);
          }
             
         nCurrInst++;
    


}
//Increase the index of the current trigger ref
void CStateManager::AddTriggerToState(u8 nType)
{   
            
    if(nCurrTrigger > nTriggerListSize)
        PrintMessage("CStateManager::What the hell are you doing with 100 triggers!!!!(Error)" );
        
    //First lets copy the instruction to the trigger
    //Create a new instance to store the instruction
    
    lpStateDefList[nTotalStateDef-1].lpState[nTotalState-1].triggers[nCurrTrigger].nTriggerType=nType;
    lpStateDefList[nTotalStateDef-1].lpState[nTotalState-1].triggers[nCurrTrigger].pInts=(INSTRUCTION*)m_pAlloc->Alloc(sizeof(INSTRUCTION)* nCurrInst);
    
    memcpy(lpStateDefList[nTotalStateDef-1].lpState[nTotalState-1].triggers[nCurrTrigger].pInts,
           pInst,sizeof(INSTRUCTION)*nCurrInst);
           
    nCurrTrigger++;
           
    lpStateDefList[nTotalStateDef-1].lpState[nTotalState-1].nHowManyTriggers=nCurrTrigger;
           
    nCurrInst=0;
    
        
}


//set the param value
void CStateManager::SetParam(int nParam)
{
   // PrintMessage("%i param",nParam);

}
//search for the given state and return it
PLSTATEDEF* CStateManager::GetStateDef(int nStateNumber)
{
    for(u16 i=0;i<nTotalStateDef;i++)
    {
       if(lpStateDefList[i].StateNumber==nStateNumber)
        return &lpStateDefList[i];
    }
    PrintMessage("CStateManager::Statedef %i not found",nStateNumber);
    return 0;    
}

void CStateManager::ExchangeIns()
{
    INSTRUCTION temp;
    
    memcpy(&temp,&pInst[nCurrInst-1],sizeof(temp));
 
    memcpy(&pInst[nCurrInst-1],&pInst[nCurrInst-2],sizeof(temp));
    memcpy(&pInst[nCurrInst-2],&temp,sizeof(temp));

}
