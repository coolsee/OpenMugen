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

#ifndef _AIRMANAGER_H_
#define _AIRMANAGER_H_


class CAirManager
{
ActionElement *lpActionList;
CAllocater    *m_pAlloc;      
u16           nTotalActionBlock;
u16           nActionListSize;
u16           nAnimTime;
u16           nTotalElement;
u16           nElementListSize;
u16           nTotalCns;
u16           nCnsListSize;
bool          bDefaultClsn;
bool          bIsClsn1;
Clsn          pClsn[200];
public:
	CAirManager();
	~CAirManager();

public:
   void SetAlloc(CAllocater* a){m_pAlloc=a;}
   void AddAction(s32 nActionNumber);
   void AddElement(s16 nGroupNumber,s16 nImageNumber,s16 x,s16 y,s16 nDuringTime,u16 nFlip,u32 nColorFlag);
   void SetLoop();
   void AddClsnBox(s16 x,s16 y,s16 w,s16 h,int nNumberOfClsn);
   void CreateClsnBox(u16 nNumberOfClsn,bool bClsn1,bool bDefault);
   void OpenAir(char *strFileName);
   ActionElement* GetAction(s32 nActionNumber);
   void CleanUp();
   void RealocateActionBlock();
   void ResetManager();



	



};
#endif
