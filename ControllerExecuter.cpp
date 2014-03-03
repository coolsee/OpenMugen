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

//Constructor
CControllerExecuter::CControllerExecuter()
{
    //init ouer function table
    InitFuncTable();

}
//Destructor
CControllerExecuter::~CControllerExecuter()
{

}

//Inits the Function Table
void CControllerExecuter::InitFuncTable()
{
    pFuncTable[0]=&CControllerExecuter::NullController;
    pFuncTable[1]=NULL;
    pFuncTable[2]=NULL;
    pFuncTable[3]=NULL;
    pFuncTable[4]=NULL;
    pFuncTable[5]=NULL;
    pFuncTable[6]=NULL;
    pFuncTable[7]=NULL;
    pFuncTable[8]=NULL;
    pFuncTable[9]=NULL;
    pFuncTable[10]=NULL;
    pFuncTable[11]=NULL;
    pFuncTable[12]=NULL;
    pFuncTable[13]=NULL;
    pFuncTable[14]=NULL;
    pFuncTable[15]=&CControllerExecuter::ChangeState;
    pFuncTable[16]=NULL;
    pFuncTable[17]=NULL;
    pFuncTable[18]=NULL;
    pFuncTable[19]=NULL;
    pFuncTable[20]=NULL;
    pFuncTable[21]=NULL;
    pFuncTable[22]=NULL;
    pFuncTable[23]=NULL;
    pFuncTable[24]=NULL;
    pFuncTable[25]=NULL;
    pFuncTable[26]=NULL;
    pFuncTable[27]=NULL;
    pFuncTable[28]=NULL;
    pFuncTable[29]=NULL;
    pFuncTable[30]=NULL;
    pFuncTable[31]=NULL;
    pFuncTable[32]=NULL;
    pFuncTable[33]=NULL;
    pFuncTable[34]=NULL;
    pFuncTable[35]=NULL;
    pFuncTable[36]=NULL;
    pFuncTable[37]=NULL;
    pFuncTable[38]=NULL;
    pFuncTable[39]=NULL;
    pFuncTable[40]=NULL;
    pFuncTable[41]=NULL;
    pFuncTable[42]=NULL;
    pFuncTable[43]=NULL;
    pFuncTable[44]=NULL;
    pFuncTable[45]=NULL;
    pFuncTable[46]=NULL;
    pFuncTable[47]=NULL;
    pFuncTable[48]=NULL;
    pFuncTable[49]=NULL;
    pFuncTable[50]=NULL;
    pFuncTable[51]=NULL;
    pFuncTable[52]=NULL;
    pFuncTable[53]=NULL;
    pFuncTable[54]=NULL;
    pFuncTable[55]=NULL;
    pFuncTable[56]=NULL;
    pFuncTable[57]=NULL;
    pFuncTable[58]=NULL;
    pFuncTable[59]=NULL;
    pFuncTable[60]=NULL;
    pFuncTable[61]=NULL;
    pFuncTable[62]=NULL;
    pFuncTable[63]=NULL;
    pFuncTable[64]=NULL;
    pFuncTable[65]=NULL;
    pFuncTable[66]=NULL;
    pFuncTable[67]=NULL;
    pFuncTable[68]=NULL;
    pFuncTable[69]=NULL;
    pFuncTable[70]=NULL;
    pFuncTable[71]=NULL;
    pFuncTable[72]=NULL;
    pFuncTable[73]=NULL;
    pFuncTable[74]=NULL;
    pFuncTable[75]=NULL;
    pFuncTable[76]=NULL;
    pFuncTable[77]=NULL;
    pFuncTable[78]=NULL;
    pFuncTable[79]=NULL;
    pFuncTable[80]=&CControllerExecuter::VarSet;
    pFuncTable[81]=NULL;
    pFuncTable[82]=NULL;
    pFuncTable[83]=&CControllerExecuter::VelSet;
    pFuncTable[84]=NULL;
    pFuncTable[85]=NULL;
    pFuncTable[86]=NULL;
    pFuncTable[87]=NULL;

}

//NUll Controller does nothing ;-)
void CControllerExecuter::NullController()
{

}


//executes the controller
void CControllerExecuter::ExecuteController(int nController)
{
#ifdef DEBUG
    PrintMessage("Execute controller %i",nController-TNULL);
#endif
 //   (this->*pFuncTable[nController-TNULL])();

}
//ChangeState Controller
void CControllerExecuter::ChangeState()
{
   /* int nStateToChange;
    //Get the Statenumber to wich it will be changed
    nStateToChange=(int)((CPlayer*)lpPlayer)->GetParamValue(PA_VALUE);
    ((CPlayer*)lpPlayer)->ChangeState(nStateToChange);*/
       
}

//Change Anim controller
void CControllerExecuter::ChangeAnim()
{
}

//VelSet controller
void CControllerExecuter::VelSet()
{
/*    float x=((CPlayer*)lpPlayer)->GetParamValue(PA_XVALUE);
    float y=((CPlayer*)lpPlayer)->GetParamValue(PA_YVALUE);
#ifdef DEBUG
    PrintMessage("Velset X=%f,Y=%f",x,y);
#endif

    if(x!=NOPARAM)
       ((CPlayer*)lpPlayer)->PlRtInfo.xvel=x;
       
    if(y!=NOPARAM)
        ((CPlayer*)lpPlayer)->PlRtInfo.yvel=y;
*/
}

//VarSet Controller
void CControllerExecuter::VarSet()
{
    /*float fVarValue=0;
    int index=0;
    
    //check which var to set
    
    //VAR
    fVarValue=((CPlayer*)lpPlayer)->GetParamValue(PA_VAR);
    if(fVarValue!=NOPARAM)
    {
        index=(int)((CPlayer*)lpPlayer)->m_VM.m_Stack.Pop().Value;
       ((CPlayer*)lpPlayer)->SetIVar(index,fVarValue);
    
    }

    //FVAR
    fVarValue=((CPlayer*)lpPlayer)->GetParamValue(PA_FVAR);
    if(fVarValue!=NOPARAM)
    {
        index=(int)((CPlayer*)lpPlayer)->m_VM.m_Stack.Pop().Value;
       ((CPlayer*)lpPlayer)->SetFVar(index,fVarValue);
    
    }
    
    //SYSVAR
    fVarValue=((CPlayer*)lpPlayer)->GetParamValue(PA_SYSVAR);
    if(fVarValue!=NOPARAM)
    {
        index=(int)((CPlayer*)lpPlayer)->m_VM.m_Stack.Pop().Value;
       ((CPlayer*)lpPlayer)->SetSysVar(index,fVarValue);
    
    }
    
   //SYSFVAR
    fVarValue=((CPlayer*)lpPlayer)->GetParamValue(PA_SYSFVAR);
    if(fVarValue!=NOPARAM)
    {
        index=(int)((CPlayer*)lpPlayer)->m_VM.m_Stack.Pop().Value;
       ((CPlayer*)lpPlayer)->SetSysFVar(index,fVarValue);
    
    }

    
        */

}
