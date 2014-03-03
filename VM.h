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


#ifndef VM_H
#define VM_H

#define NUMFUNCT 140

class CVirtualMachine
{
CPlayer *m_pPlayer1,*m_pPlayer2;
public:
CVirtualMachine();
~CVirtualMachine();

float Execute(INSTRUCTION *pInst);
void PushValue();
void PopValue();
void AddOP();
void SubOP();
void DivOP();
void MulOP();
void EqualOP();
void NotEqual();
void Less();
void Greater();
void LessEqual();
void GreaterEqual();
void InterValOP1();
void InterValOP2();
void InterValOP3();
void InterValOP4();
void InterValOP5();
void InterValOP6();
void InterValOP7();
void InterValOP8();
void LogNot();
void LogAnd();
void LogOr();
void LogXor();
void Not();
void And();
void Or();
void Xor();
void Square();
void Abs();
void Neg();
void Acos();
void Alive();
void Anim();
void AnimElem();
void AnimeElemNo();
void AnimeElemTime();
void AnimExist();
void AnimTime();
void Asin();
void Atan();
void AuthorName();
void BackEdgeBodyDist();
void BackEdgeDist();
void CanRecover();
void Ceil();
void Command();
void Const();
void Cos();
void Ctrl();
void DrawGame();
void Exp();
void Facing();
void Floor();
void FrontEdgeBodyDist();
void FrontEdgeDist();
void FVar();
void GameTime();
void GetHitVar();
void HitCount();
//void HitDefAttr()
void HitFall();
void HitOver();
void HitPauseTime();
void HitShakeOver();
void HitVel();
void PlayerIdent();
void IfElse();
void InGuardDist();
void IsHelper();
void IsHomeTeam();
void Life();
void LifeMax();
void LogN();
void Log();
void Lose();
void MatchNo();
void MatchOver();
void MoveContact();
void MoveGuarded();
void MoveHit();
void MoveType();
void MoveReversed();
void Name();
void NumEnemy();
void NumExplod();
void NumHelper();
void NumPartner();
void NumProj();
void NumProjID();
void NumTarget();
void P2BodyDist();
void P2Dist();
void P2Life();
void P2MoveType();
void P2Name();
void P2StateNo();
void P2StateType();
void P3Name();
void P4Name();
void PalNo();
void ParentDist();
void Pi();
void PlayerIDExist();
void PrevStateNo();
void Pos();
void Power();
void PowerMax();
void ProjCancelTime();
void Random();
void RootDist();
void RoundNo();
void RoundsExisted();
void RoundState();
void ScreenPos();
void SelfAnimExist();
void Sin();
void StateNo();
void StateType();
void SysFVar();
void SysVar();
void Tan();
void TeamMode();
void TeamSide();
void TicksPerSecond();
void Time();
void UniqHitCount();
void Var();
void Vel();
void Win();
void ProjContact();
void ProjContactTime();
void ProjGuarded();
void ProjGuardedTime();
void NOP(){};
void MODOP();


//helper functions
void Save();
void Restore();

void InitFunctTable();
void SetPlayers(CPlayer *p1,CPlayer *p2);

//variables
CStack m_Stack;

int nCurrentIns;
INSTRUCTION *pCurrentIns;
Stacktype m_pop;
float temp1,temp2,temp3;
float nSave;
//pointer to player
void *m_p1;
void *m_p2;




typedef void (CVirtualMachine::*pt2Member)();

pt2Member pFuncTable[NUMFUNCT];



};


#endif
