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

CStack::CStack()
{   
    nPos=0;
    memset(m_Stack,0,sizeof(m_Stack));

}


CStack::~CStack()
{

}

void CStack::ResetStack()
{
    nPos=0;
    memset(m_Stack,0,sizeof(m_Stack));

}

void CStack::Push(float nValue,char* strValue)
{
    if(nPos>STACKSIZE)
        PrintMessage("CStack::Push Stack overflow");
      
      if(strValue!=NULL)
        strcpy(m_Stack[nPos].string,strValue);
      
      m_Stack[nPos].Value=nValue;
       
#ifdef DEBUG
    PrintMessage("Push %f",nValue);
#endif       
    nPos++;      
  
}

Stacktype CStack::Pop()
{
    if(nPos<0)
        PrintMessage("CStack::Pop Stack underflow");
    
    return m_Stack[--nPos];


}
