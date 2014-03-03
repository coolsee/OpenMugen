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

#ifndef STATEMANAGER_H 
#define STAGEMANAGER_H


#define S_type					2
#define S_movetype				4
#define S_physics				8
#define S_anime					10
#define S_ctrl					12
#define S_poweradd				14
#define S_juggle				16
#define S_hitdefpersist			18
#define S_movehitpresist		20
#define S_hitcountpresist		22
#define S_sprprio				24
#define S_facep2				26

class CStateManager
{
    CAllocater     *m_pAlloc;
public:
	//Konstructor and Destructor
	CStateManager();
	~CStateManager();
	
	void SetAlloc(CAllocater *a){m_pAlloc=a;}

	void AddStateDef(s32 nStateDefNum);
	void AddState(s32 nStateNum,char *strSomeNumber);
	void AddTriggerToState(u8 nType);
	void AddTypeToState(u16 nType);
	void AddInstruction(Uint16 nOpCode,float value,const char *strValue);
	void ExchangeIns();
	void *GetController();
	void CleanUp();
	INSTRUCTION *GetInst(){return pInst;}
	int         GetHowManyInst(){return nCurrInst;}
	//search a State
	PLSTATEDEF* GetStateDef(int nStateNumber);
	PLSTATEDEF* GetCurrStateDef();
	
	void ReallocStatedef(u16 index);
	void ReallocManager();
	
	//SetFuction
	void SetStateDefType(u8 nType);
	void SetStateMoveType(u8 nType);
	void SetStatePhysicType(u8 nType);
	void SetStateAnim(s32 nAnim);
	void SetStateCtrl(s8 nCtrl);
	void SetStatePowerAdd(s16 nPowerAdd);
	void SetStateJuggle(s16 nJuggle);
	void SetStateHitDefPresit(bool bHitDef);
	void SetMoveHitPresit(bool bMoveHit);
	void SetStateHitCounterPresit(bool bHitCounter);
	void SetSprPriority(u8 nSprpriority);
	void SetStateFaceP2(bool bFaceP2);
	
	void SetVelSet(float x,float y);
    void NewInst(){nCurrInst=0;}
	void SetParam(int nParam);
	void SetDefaultStatedef();
	void Reset();
	
	bool IsStateDefAviable(s32 nStateDefNum);

private:
	INSTRUCTION pInst[200];
	PLSTATEDEF *lpStateDefList;
	u16        nTotalStateDef;
	u16        nTotalStateDefSize;
	u16        nTotalState;
	u16        nTotalStateSize;
	u16        nCurrTrigger;
	u16        nTriggerListSize;
	u16 nCurrInst;
	u16 nCurrParamInst;
	u16 nCurrParam;
	
	bool bParam;



};

#endif
