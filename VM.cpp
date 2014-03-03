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

//Contructor
CVirtualMachine::CVirtualMachine()
{
    m_Stack.ResetStack();
    nCurrentIns=0;
    InitFunctTable();
  
}
//Destructor
CVirtualMachine::~CVirtualMachine()
{

}
//Sets pointers for get access to Player internal
void CVirtualMachine::SetPlayers(CPlayer *p1,CPlayer *p2)
{
   m_pPlayer1=p1;
   m_pPlayer2=p2;

}
//Sets the pointer to the Functions int this class
void CVirtualMachine::InitFunctTable()
{
   pFuncTable[0]=&CVirtualMachine::PushValue;
   pFuncTable[1]=&CVirtualMachine::PopValue;
   pFuncTable[2]=&CVirtualMachine::AddOP;
   pFuncTable[3]=&CVirtualMachine::SubOP;
   pFuncTable[4]=&CVirtualMachine::MulOP;
   pFuncTable[5]=&CVirtualMachine::DivOP;
   pFuncTable[6]=&CVirtualMachine::EqualOP;
   pFuncTable[7]=&CVirtualMachine::NotEqual;
   pFuncTable[8]=&CVirtualMachine::Less;
   pFuncTable[9]=&CVirtualMachine::Greater;
   pFuncTable[10]=&CVirtualMachine::LessEqual;
   pFuncTable[11]=&CVirtualMachine::GreaterEqual;
   pFuncTable[12]=&CVirtualMachine::InterValOP1;
   pFuncTable[13]=&CVirtualMachine::InterValOP2;
   pFuncTable[14]=&CVirtualMachine::InterValOP3;
   pFuncTable[15]=&CVirtualMachine::InterValOP4;
   pFuncTable[16]=&CVirtualMachine::InterValOP5;
   pFuncTable[17]=&CVirtualMachine::InterValOP6;
   pFuncTable[18]=&CVirtualMachine::InterValOP7;
   pFuncTable[19]=&CVirtualMachine::InterValOP8;
   pFuncTable[20]=&CVirtualMachine::LogNot;
   pFuncTable[21]=&CVirtualMachine::LogAnd;
   pFuncTable[22]=&CVirtualMachine::LogOr;
   pFuncTable[23]=&CVirtualMachine::LogXor;
   pFuncTable[24]=&CVirtualMachine::Not;
   pFuncTable[25]=&CVirtualMachine::And;
   pFuncTable[26]=&CVirtualMachine::Or;
   pFuncTable[27]=&CVirtualMachine::Xor;
   pFuncTable[28]=&CVirtualMachine::Square;
   pFuncTable[29]=&CVirtualMachine::Neg;
   pFuncTable[30]=&CVirtualMachine::Abs;
   pFuncTable[31]=&CVirtualMachine::Acos;
   pFuncTable[32]=&CVirtualMachine::Alive;
   pFuncTable[33]=&CVirtualMachine::Anim;
   pFuncTable[34]=&CVirtualMachine::AnimElem;
//   pFuncTable[35]=&CVirtualMachine::Save;
//   pFuncTable[36]=&CVirtualMachine::Restore;
   pFuncTable[35]=&CVirtualMachine::AnimeElemNo;
   pFuncTable[36]=&CVirtualMachine::AnimeElemTime;
   pFuncTable[37]=&CVirtualMachine::AnimExist;
   pFuncTable[38]=&CVirtualMachine::AnimTime;
   pFuncTable[39]=&CVirtualMachine::Asin;
   pFuncTable[40]=&CVirtualMachine::Atan;
   pFuncTable[41]=&CVirtualMachine::AuthorName;
   pFuncTable[42]=&CVirtualMachine::BackEdgeBodyDist;
   pFuncTable[43]=&CVirtualMachine::BackEdgeDist;
   pFuncTable[44]=&CVirtualMachine::CanRecover;
   pFuncTable[45]=&CVirtualMachine::Ceil;
   pFuncTable[46]=&CVirtualMachine::Command;
   pFuncTable[47]=&CVirtualMachine::Const;
   pFuncTable[48]=&CVirtualMachine::Cos;
   pFuncTable[49]=&CVirtualMachine::Ctrl;
   pFuncTable[52]=&CVirtualMachine::DrawGame;
   pFuncTable[53]=0;//&CVirtualMachine::E;
   pFuncTable[54]=&CVirtualMachine::Exp;
   pFuncTable[55]=&CVirtualMachine::Facing;
   pFuncTable[56]=&CVirtualMachine::Floor;
   pFuncTable[57]=&CVirtualMachine::FrontEdgeBodyDist;
   pFuncTable[58]=&CVirtualMachine::FrontEdgeDist;
   pFuncTable[59]=&CVirtualMachine::FVar;
   pFuncTable[60]=&CVirtualMachine::GameTime;
   pFuncTable[61]=&CVirtualMachine::GetHitVar;
   pFuncTable[62]=&CVirtualMachine::HitCount;
   pFuncTable[63]=0;//HitDefAttr
   pFuncTable[64]=&CVirtualMachine::HitFall;
   pFuncTable[65]=&CVirtualMachine::HitOver;
   pFuncTable[66]=&CVirtualMachine::HitPauseTime;
   pFuncTable[67]=&CVirtualMachine::HitShakeOver;
   pFuncTable[68]=&CVirtualMachine::HitVel;
   pFuncTable[69]=&CVirtualMachine::PlayerIdent;
   pFuncTable[70]=&CVirtualMachine::IfElse;
   pFuncTable[71]=&CVirtualMachine::InGuardDist;
   pFuncTable[72]=&CVirtualMachine::IsHelper;
   pFuncTable[73]=&CVirtualMachine::IsHomeTeam;
   pFuncTable[74]=&CVirtualMachine::Life;
   pFuncTable[75]=&CVirtualMachine::LifeMax;
   pFuncTable[76]=&CVirtualMachine::LogN;
   pFuncTable[77]=&CVirtualMachine::Log;
   pFuncTable[78]=&CVirtualMachine::Lose;
   pFuncTable[79]=&CVirtualMachine::MatchNo;
   pFuncTable[80]=&CVirtualMachine::MatchOver;
   pFuncTable[81]=&CVirtualMachine::MoveContact;
   pFuncTable[82]=&CVirtualMachine::MoveGuarded;
   pFuncTable[83]=&CVirtualMachine::MoveHit;
   pFuncTable[84]=&CVirtualMachine::MoveType;
   pFuncTable[85]=&CVirtualMachine::MoveReversed;
   pFuncTable[86]=&CVirtualMachine::Name;
   pFuncTable[87]=&CVirtualMachine::NumEnemy;
   pFuncTable[88]=&CVirtualMachine::NumExplod;
   pFuncTable[89]=&CVirtualMachine::NumHelper;
   pFuncTable[90]=&CVirtualMachine::NumPartner;
   pFuncTable[91]=&CVirtualMachine::NumProj;
   pFuncTable[92]=&CVirtualMachine::NumProjID;
   pFuncTable[93]=&CVirtualMachine::NumTarget;
   pFuncTable[94]=&CVirtualMachine::P2BodyDist;
   pFuncTable[95]=&CVirtualMachine::P2Dist;
   pFuncTable[96]=&CVirtualMachine::P2Life;
   pFuncTable[97]=&CVirtualMachine::P2MoveType;
   pFuncTable[98]=&CVirtualMachine::P2Name;
   pFuncTable[99]=&CVirtualMachine::P2StateNo;
   pFuncTable[100]=&CVirtualMachine::P2StateType;
   pFuncTable[101]=&CVirtualMachine::P3Name;
   pFuncTable[102]=&CVirtualMachine::P4Name;
   pFuncTable[103]=&CVirtualMachine::PalNo;
   pFuncTable[104]=&CVirtualMachine::ParentDist;
   pFuncTable[105]=&CVirtualMachine::Pi;
   pFuncTable[106]=&CVirtualMachine::Pos;
   pFuncTable[107]=&CVirtualMachine::Power;
   pFuncTable[108]=&CVirtualMachine::PowerMax;
   pFuncTable[109]=0;//PlayerIDExist
   pFuncTable[110]=0;//PrevStateNo
   pFuncTable[111]=&CVirtualMachine::ProjCancelTime;
   pFuncTable[112]=&CVirtualMachine::ProjContact;
   pFuncTable[113]=&CVirtualMachine::ProjContactTime;
   pFuncTable[114]=&CVirtualMachine::ProjGuarded;
   pFuncTable[115]=&CVirtualMachine::ProjGuardedTime;
   pFuncTable[116]=0;//ProjHit
   pFuncTable[117]=0;//ProjHitTime
   pFuncTable[118]=&CVirtualMachine::Random;
   pFuncTable[119]=&CVirtualMachine::RootDist;
   pFuncTable[120]=&CVirtualMachine::RoundNo;
   pFuncTable[121]=&CVirtualMachine::RoundsExisted;
   pFuncTable[122]=&CVirtualMachine::RoundState;
   pFuncTable[123]=&CVirtualMachine::ScreenPos;
   pFuncTable[124]=&CVirtualMachine::SelfAnimExist;
   pFuncTable[125]=&CVirtualMachine::Sin;
   pFuncTable[126]=&CVirtualMachine::StateNo;
   pFuncTable[127]=&CVirtualMachine::StateType;
   pFuncTable[128]=&CVirtualMachine::SysFVar;
   pFuncTable[129]=&CVirtualMachine::SysVar;
   pFuncTable[130]=&CVirtualMachine::Tan;
   pFuncTable[131]=&CVirtualMachine::TeamMode;
   pFuncTable[132]=&CVirtualMachine::TeamSide;
   pFuncTable[133]=&CVirtualMachine::TicksPerSecond;
   pFuncTable[134]=&CVirtualMachine::Time;
   pFuncTable[135]=0;//TimeMod
   pFuncTable[136]=&CVirtualMachine::UniqHitCount;
   pFuncTable[137]=&CVirtualMachine::Var;
   pFuncTable[138]=&CVirtualMachine::Vel;
   pFuncTable[139]=&CVirtualMachine::Win;

}


//Executes one instruction line
float CVirtualMachine::Execute(INSTRUCTION *pInst)
{
    nCurrentIns=0;
    
        
    //Rest the Satck for the next execution
    m_Stack.ResetStack();
  
    while(pInst[nCurrentIns].n_OpCode!=OP_STOP)
    {
        
        pCurrentIns=&pInst[nCurrentIns];
        //Execute the function
        (this->*pFuncTable[pInst[nCurrentIns].n_OpCode])();
        nCurrentIns++;
    }
    PopValue();
     
    return m_pop.Value;

}
//Pops a value from the stack
void CVirtualMachine::PopValue()
{
   m_pop=m_Stack.Pop();
}

void CVirtualMachine::PushValue()
{
      m_Stack.Push(pCurrentIns->Value,pCurrentIns->strValue);
}
//x+y
void CVirtualMachine::AddOP()
{
    PopValue();
    temp2=m_pop.Value;
    PopValue();
    temp1=m_pop.Value;
    
    m_pop.Value=temp1+temp2;
  //  PrintMessage("%f + %f = %f",temp1,temp2,m_pop.Value);
    m_Stack.Push(m_pop.Value,"#");

}
//x-y
void CVirtualMachine::SubOP()
{
    PopValue();
    temp2=m_pop.Value;
    PopValue();
    temp1=m_pop.Value;
    
    m_pop.Value=temp1-temp2;
    m_Stack.Push(m_pop.Value,"#");

}
//x*y
void CVirtualMachine::MulOP()
{
    PopValue();
    temp2=m_pop.Value;
    PopValue();
    temp1=m_pop.Value;
    
    m_pop.Value=temp1*temp2;
    m_Stack.Push(m_pop.Value,"#");

}
//x/y
void CVirtualMachine::DivOP()
{
    PopValue();
    temp2=m_pop.Value;
    PopValue();
    temp1=m_pop.Value;
    
    m_pop.Value=temp1/temp2;
    m_Stack.Push(m_pop.Value,"#");

}
//x==Y
void CVirtualMachine::EqualOP()
{
   char strTemp[50],strTemp1[50];

    PopValue();
    temp2=m_pop.Value;
    strcpy(strTemp,m_pop.string);

    PopValue();
    temp1=m_pop.Value;
    strcpy(strTemp1,m_pop.string);
    
    if(strTemp[0] != '#' && strTemp1[0] != '#')
    {
        if( strcmp(strTemp,strTemp1)==0)
        {
                m_Stack.Push(1,"#");
        }
        else
                m_Stack.Push(0,"#");
                
 //    PrintMessage("%s != %s" ,strTemp,strTemp1);                     
        
        return;    
    
    }
    
    
    
    

    if(temp1==temp2)
        m_pop.Value=1;
    else
        m_pop.Value=0;

#ifdef DEBUG    
    PrintMessage("%f == %f",temp1,temp2);
#endif
    m_Stack.Push(m_pop.Value,"#");

}
//x!=y
void CVirtualMachine::NotEqual()
{
    PopValue();
    temp2=m_pop.Value;
    PopValue();
    temp1=m_pop.Value;
    

    if(temp1!=temp2)
        m_pop.Value=1;
    else
        m_pop.Value=0;

    m_Stack.Push(m_pop.Value,"#");

}
//x<y
void CVirtualMachine::Less()
{
    PopValue();
    temp2=m_pop.Value;
    PopValue();
    temp1=m_pop.Value;
    

    if(temp1<temp2)
        m_pop.Value=1;
    else
        m_pop.Value=0;
        
    //PrintMessage("%f < %f",temp1,temp2);

    m_Stack.Push(m_pop.Value,"#");

}
//x>y
void CVirtualMachine::Greater()
{
    PopValue();
    temp2=m_pop.Value;
    PopValue();
    temp1=m_pop.Value;
    

    if(temp1>temp2)
        m_pop.Value=1;
    else
        m_pop.Value=0;
        
   // PrintMessage("%f > %f",temp1,temp2);

    m_Stack.Push(m_pop.Value,"#");

}
//x<=y
void CVirtualMachine::LessEqual()
{
    PopValue();
    temp2=m_pop.Value;
    PopValue();
    temp1=m_pop.Value;
    

    if(temp1<=temp2)
        m_pop.Value=1;
    else
        m_pop.Value=0;

    m_Stack.Push(m_pop.Value,"#");


}

void CVirtualMachine::GreaterEqual()
{
    PopValue();
    temp2=m_pop.Value;
    PopValue();
    temp1=m_pop.Value;
    

    if(temp1>=temp2)
        m_pop.Value=1;
    else
        m_pop.Value=0;

    m_Stack.Push(m_pop.Value,"#");


}
//x=[y,z]
void CVirtualMachine::InterValOP1()
{
    //Get Values from stack
    PopValue();
    temp3=m_pop.Value;
    PopValue();
    temp2=m_pop.Value;
    PopValue();
    temp1=m_pop.Value;
    
    m_pop.Value=0;
     
    if( (temp1 >= temp2) && (temp1 <= temp3) )
      m_pop.Value=1;
            
   m_Stack.Push(m_pop.Value,"#");
   
 //  PrintMessage("%2f,%2f,%2f",temp1,temp2,temp3);
      
}
//x=[y,z)
void CVirtualMachine::InterValOP2()
{
    PopValue();
    temp3=m_pop.Value;
    PopValue();
    temp2=m_pop.Value;
    PopValue();
    temp1=m_pop.Value;
    
    m_pop.Value=0;
     
    if( (temp1 >= temp2) && (temp1 < temp3) )
      m_pop.Value=1;
            
   m_Stack.Push(m_pop.Value,"#");
    
}
//x=(y,z]
void CVirtualMachine::InterValOP3()
{
    PopValue();
    temp3=m_pop.Value;
    PopValue();
    temp2=m_pop.Value;
    PopValue();
    temp1=m_pop.Value;
    
    m_pop.Value=0;
     
    if( (temp1 > temp2) && (temp1 <= temp3) )
      m_pop.Value=1;
            
   m_Stack.Push(m_pop.Value,"#");
}
//x=(y,z)
void CVirtualMachine::InterValOP4()
{
    PopValue();
    temp3=m_pop.Value;
    PopValue();
    temp2=m_pop.Value;
    PopValue();
    temp1=m_pop.Value;
    
    m_pop.Value=0;
     
    if( (temp1 > temp2) && (temp1 < temp3) )
      m_pop.Value=1;
            
   m_Stack.Push(m_pop.Value,"#");
}
//x!=[y,z]
void CVirtualMachine::InterValOP5()
{
    //Get Values from stack
    PopValue();
    temp3=m_pop.Value;
    PopValue();
    temp2=m_pop.Value;
    PopValue();
    temp1=m_pop.Value;
    
    m_pop.Value=0;
     
    //(x < y) || (x > z)
    if( (temp1 < temp2) || (temp1 > temp3) )
      m_pop.Value=1;
            
   m_Stack.Push(m_pop.Value,"#");
      
}
//x!=[y,z)
void CVirtualMachine::InterValOP6()
{
    PopValue();
    temp3=m_pop.Value;
    PopValue();
    temp2=m_pop.Value;
    PopValue();
    temp1=m_pop.Value;
    
    m_pop.Value=0;
     
    if( (temp1 < temp2) || (temp1 >= temp3) )
      m_pop.Value=1;
            
   m_Stack.Push(m_pop.Value,"#");
    
}
//x!=(y,z]
void CVirtualMachine::InterValOP7()
{
    PopValue();
    temp3=m_pop.Value;
    PopValue();
    temp2=m_pop.Value;
    PopValue();
    temp1=m_pop.Value;
    
    m_pop.Value=0;
     
     if( (temp1 <= temp2) || (temp1 > temp3) )
      m_pop.Value=1;
            
   m_Stack.Push(m_pop.Value,"#");
}
//x!=(y,z)
void CVirtualMachine::InterValOP8()
{
    PopValue();
    temp3=m_pop.Value;
    PopValue();
    temp2=m_pop.Value;
    PopValue();
    temp1=m_pop.Value;
    
    m_pop.Value=0;
     
    if( (temp1 >= temp2) && (temp1 <= temp3) )
      m_pop.Value=1;
            
   m_Stack.Push(m_pop.Value,"#");
}


void CVirtualMachine::LogNot()
{
    PopValue();
    temp1=m_pop.Value;

#ifdef DEBUG
    PrintMessage("LogNOT");
#endif
    
    if(!(temp1>0))
        m_Stack.Push(1,"#");
    else
        m_Stack.Push(0,"#");
    
       

}

void CVirtualMachine::LogAnd()
{
    PopValue();
    temp2=m_pop.Value;
    PopValue();
    temp1=m_pop.Value;
    
    if( temp1>0 && temp2>0)
        m_Stack.Push(1,"#");
    else
        m_Stack.Push(0,"#"); 
    }

void CVirtualMachine::LogOr()
{

    PopValue();
    temp2=m_pop.Value;
    PopValue();
    temp1=m_pop.Value;
    
    if( temp1>0 || temp2>0)
        m_Stack.Push(1,"#");
    else
        m_Stack.Push(0,"#"); 

}

void CVirtualMachine::LogXor()
{
    PopValue();
    temp2=m_pop.Value;
    PopValue();
    temp1=m_pop.Value;
    
    if( temp1>0  && temp2==0)
        m_Stack.Push(1,"#");
    else if ( temp1==0  && temp2>0)
        m_Stack.Push(1,"#"); 
    else
        m_Stack.Push(0,"#"); 

}

void CVirtualMachine::Not()
{
    PopValue();
    
    temp1=m_pop.Value;
        
    temp1=~(int)temp1;
    m_Stack.Push(temp1,"#");

}

void CVirtualMachine::And()
{
    PopValue();
    temp2=m_pop.Value;
    PopValue();
    temp1=m_pop.Value;
    
    temp1=(int)temp1 & (int)temp2;
    m_Stack.Push(temp1,"#");

}

void CVirtualMachine::Or()
{
    PopValue();
    temp2=m_pop.Value;
    PopValue();
    temp1=m_pop.Value;
    
    temp1=(int)temp1 | (int)temp2;
    m_Stack.Push(temp1,"#");

}

void CVirtualMachine::Xor()
{
    PopValue();
    temp2=m_pop.Value;
    PopValue();
    temp1=m_pop.Value;
    
    temp1=(int)temp1 ^ (int)temp2;
    m_Stack.Push(temp1,"#");

}

//Square x^y
void CVirtualMachine::Square()
{
    PopValue();
    temp2=m_pop.Value;
    PopValue();
    temp1=m_pop.Value;
    
    temp1=pow(temp1,temp2);
    m_Stack.Push(temp1,"#");
}
//ABS
void CVirtualMachine::Abs()
{
    PopValue();
    temp1=m_pop.Value;
    
    temp1=fabs(temp1);
    m_Stack.Push(temp1,"#");
    
}
//Negate
void CVirtualMachine::Neg()
{
    PopValue();
    temp1=m_pop.Value;
    
    temp1=-temp1;
    m_Stack.Push(temp1,"#");

}

void CVirtualMachine::Acos()
{
    PopValue();
    temp1=m_pop.Value;
    
    temp1=acos(temp1);
    m_Stack.Push(temp1,"#");

}
//Alive
void CVirtualMachine::Alive()
{
  if(m_pPlayer1->IsPlayerAlive())
     m_Stack.Push(1.0f,"#");
  else
     m_Stack.Push(0.0f,"#");
}

//Anime
void CVirtualMachine::Anim()
{
  m_Stack.Push((float)m_pPlayer1->GetAnim(),"#");

}

//Anime Elem
void CVirtualMachine::AnimElem()
{
    ActionElement* tActionElement;
    
    tActionElement=m_pPlayer1->GetCurrAnim();
    
           
    //Time since this element
    m_Stack.Push((float)tActionElement->nCurrTime,"#");
    //Element nummber(NOTE first element is not 0 it is 1)
    m_Stack.Push((float)tActionElement->nCurrentImage+1,"#");
  
       
/* TODO (#1#): Push the right values to the stack */


}
//AnimElemNo(exprs)
void CVirtualMachine::AnimeElemNo()
{   
    ActionElement* tActionElement;
    tActionElement=m_pPlayer1->GetCurrAnim();

    int nTimeOffset=0;
    int nTimeCheck=0;
    int nTimeToElement=0;

        
    PopValue();
    nTimeOffset=(int)m_pop.Value;
    
    nTimeCheck=nTimeOffset+tActionElement->nCurrTime;
    
    if(nTimeCheck > tActionElement->nCompletAnimTime)
    {
#ifdef DEBUG
    PrintMessage("AnimeElemNo should return SFalse");
#endif
    m_Stack.Push(0,"#");
    return;
    }
  
    //now check on which elemt the time offset is  
    for (int i=0;i<tActionElement->nNumberOfElements;i++)
    {
        nTimeToElement+=tActionElement->AnimationElement[i].nDuringTime;
        if(nTimeToElement >= nTimeCheck)
        {
            //Now we had found wich elemt it would be on this time
            m_Stack.Push((float)i+1,"#");
            return;
        
        }
        
    
    }
    
    m_Stack.Push(0,"#");


 
}
//AnimElemTime(exprs)
void CVirtualMachine::AnimeElemTime()
{
    ActionElement* tActionElement;
    tActionElement=m_pPlayer1->GetCurrAnim();
    
    int nElementToCheck;

    PopValue();
    nElementToCheck=(int)m_pop.Value;
    
    //(NOTE first element is not 0 it is 1)
    if(nElementToCheck == tActionElement->nCurrentImage+1 && !tActionElement->bLooped )
    {
        m_Stack.Push((float)tActionElement->nCurrentImageTime,"#");
    
    }
    else
    {
        //Should return SFalse
        m_Stack.Push(-1,"#");    
    }

}

//AnimExist(exprs)
void CVirtualMachine::AnimExist()
{
    s32 nAnim;
    PopValue();
    nAnim=(s32)m_pop.Value;
    //If != NULL psuh true else push false
    if(m_pPlayer1->IsAnimAviable(nAnim))
        m_Stack.Push(1.0,"#");
    else
        m_Stack.Push(0.0,"#");

}

//AnimeTime
void CVirtualMachine::AnimTime()
{
    u16 nAnimTime;
    ActionElement* tActionElement;
    
    tActionElement=m_pPlayer1->GetCurrAnim();

    nAnimTime=tActionElement->nCurrTime - tActionElement->nCompletAnimTime;
    
    m_Stack.Push((float)nAnimTime,"#");
}

//Asin(expr)
void CVirtualMachine::Asin()
{
    PopValue();
    temp1=m_pop.Value;
    temp1=asin(temp1);
    
    m_Stack.Push(temp1,"#");

}

//Atan (expr)
void CVirtualMachine::Atan()
{
    PopValue();
    temp1=m_pop.Value;
    temp1=atan(temp1);
    m_Stack.Push(temp1,"#");

}

//Author Name
void CVirtualMachine::AuthorName()
{
    /*PrintMessage("AuthorName %s",((CPlayer*)m_p1)->myPlayerData.strAuthor);
    m_Stack.Push(0,((CPlayer*)m_p1)->myPlayerData.strAuthor);*/
}
 
//BackEdgeBodyDist
void CVirtualMachine::BackEdgeBodyDist()
{
    m_Stack.Push(123,"#");
    
}
//BackEdgeDist
void CVirtualMachine::BackEdgeDist()
{
        m_Stack.Push(123,"#");
}
//CanRecover
void CVirtualMachine::CanRecover()
{
    //Push false for the moment
    m_Stack.Push(0,"#");    

}

//Ceil
void CVirtualMachine::Ceil()
{
    PopValue();
    temp1=m_pop.Value;
    temp1=ceil(temp1);
    m_Stack.Push(temp1,"#");

}
//Command
void CVirtualMachine::Command()
{
    m_Stack.Push(0,m_pPlayer1->GetCommand());
}

//Const
void CVirtualMachine::Const()
{
    PopValue();
    temp1=m_pop.Value;
    //TODO: Write the GetConst function for player
   switch((int)temp1)
   {
      //data.life
      case 0:
        m_Stack.Push((float)((CPlayer*)m_p1)->myPlayerConst.PlayerData.nLife,"#");
      break;
      
      //data.attack
      case 1:
        m_Stack.Push(m_pPlayer1->myPlayerConst.PlayerData.nAttack,"#");
      break;
      
      //data.defence
      case 2:
        m_Stack.Push(m_pPlayer1->myPlayerConst.PlayerData.nDefence,"#");
      break;
      
      //data.fall.defence_mul
      case 3:
         temp1=100/(m_pPlayer1->myPlayerConst.PlayerData.nFallDefenceUp+100);
        m_Stack.Push(temp1,"#");
      break;
      
      //data.liedown.time
      case 4:
        m_Stack.Push(m_pPlayer1->myPlayerConst.PlayerData.nLieDownTime,"#");
      break;
      
      //data.airjuggle
      case 5:
        m_Stack.Push(m_pPlayer1->myPlayerConst.PlayerData.nAirjuggle,"#");
      break;

      //data.sparkno
      case 6:
        m_Stack.Push(m_pPlayer1->myPlayerConst.PlayerData.nSparkno,"#");
      break;   

     //data.guard.sparkno
      case 7:
        m_Stack.Push(m_pPlayer1->myPlayerConst.PlayerData.nGuardSparkno,"#");
      break; 
      
     //data.KO.echo
      case 8:
        m_Stack.Push(m_pPlayer1->myPlayerConst.PlayerData.bKoEcho,"#");
      break; 
      
     //data.IntPersistIndex
      case 9:
        m_Stack.Push(m_pPlayer1->myPlayerConst.PlayerData.nIntPersistIndex,"#");
      break; 

     //data.IntPersistIndex
      case 10:
        m_Stack.Push(m_pPlayer1->myPlayerConst.PlayerData.nFloatPersistIndex,"#");
      break; 
      
      //size.xscale
      case 11:
        m_Stack.Push(m_pPlayer1->myPlayerConst.PlayerSize.nXscale,"#");
      break; 
     
      //size.yscale
      case 12:
        m_Stack.Push(m_pPlayer1->myPlayerConst.PlayerSize.nYscale,"#");
      break; 
      
      //size.ground.back
      case 13:
        m_Stack.Push(m_pPlayer1->myPlayerConst.PlayerSize.nGroundBack,"#");
      break; 
      
      //size.ground.front
      case 14:
        m_Stack.Push(m_pPlayer1->myPlayerConst.PlayerSize.nGroundFront,"#");
      break; 
      
      //size.air.back
      case 15:
        m_Stack.Push(m_pPlayer1->myPlayerConst.PlayerSize.nAirBack,"#");
      break; 
      
      //size.air.front
      case 16:
        m_Stack.Push(m_pPlayer1->myPlayerConst.PlayerSize.nAirFront,"#");
      break; 
      
      //size.attack.dist
      case 17:
        m_Stack.Push(m_pPlayer1->myPlayerConst.PlayerSize.nAttackDistance,"#");
      break; 
      
      //size.proj.attack.dist
      case 18:
        m_Stack.Push(m_pPlayer1->myPlayerConst.PlayerSize.nProjAttackDist,"#");
      break; 
      
      //size.proj.doscale
      case 19:
        m_Stack.Push(m_pPlayer1->myPlayerConst.PlayerSize.bProjDoScale,"#");
      break; 
      
      //size.head.pos.x
      case 20:
        m_Stack.Push(m_pPlayer1->myPlayerConst.PlayerSize.nHeadPos.x,"#");
      break;

      //size.head.pos.y
      case 21:
        m_Stack.Push(m_pPlayer1->myPlayerConst.PlayerSize.nHeadPos.y,"#");
      break;  
      
      //size.mid.pos.x
      case 22:
        m_Stack.Push(m_pPlayer1->myPlayerConst.PlayerSize.nMidPos.x,"#");
      break;
      
      //size.mid.pos.y
      case 23:
        m_Stack.Push(m_pPlayer1->myPlayerConst.PlayerSize.nMidPos.y,"#");
      break;
      
      //size.size.shadowoffset
      case 24:
        m_Stack.Push(m_pPlayer1->myPlayerConst.PlayerSize.nShadowOffset,"#");
      break;
      
      //size.draw.offset.x
      case 25:
        m_Stack.Push(m_pPlayer1->myPlayerConst.PlayerSize.nDrawOffset.x,"#");
      break;
      
      //size.draw.offset.x
      case 26:
        m_Stack.Push(m_pPlayer1->myPlayerConst.PlayerSize.nDrawOffset.x,"#");
      break;
      
      //velocity.walk.fwd.x
      case 27:
        m_Stack.Push(m_pPlayer1->myPlayerConst.PlayerVelocity.nWalkFwd,"#");
      break;
      
      //velocity.walk.back.x
      case 28:
        m_Stack.Push(m_pPlayer1->myPlayerConst.PlayerVelocity.nWalkBack,"#");
      break;
      
      //velocity.run.fwd.x
      case 29:
        m_Stack.Push(m_pPlayer1->myPlayerConst.PlayerVelocity.RunFwd.x,"#");
      break;
      
      //velocity.run.fwd.y
      case 30:
        m_Stack.Push(m_pPlayer1->myPlayerConst.PlayerVelocity.RunFwd.y,"#");
      break;
      
      //velocity.run.back.x
      case 31:
        m_Stack.Push(m_pPlayer1->myPlayerConst.PlayerVelocity.RunBack.x,"#");
      break;
      
      //velocity.back.fwd.y
      case 32:
        m_Stack.Push(m_pPlayer1->myPlayerConst.PlayerVelocity.RunBack.y,"#");
      break;
      
      //velocity.jump.neu.x
      case 33:
        m_Stack.Push(m_pPlayer1->myPlayerConst.PlayerVelocity.JumpNeu.x,"#");
      break;
      
      //velocity.jump.back.x
      case 34:
        m_Stack.Push(m_pPlayer1->myPlayerConst.PlayerVelocity.JumpBack.x,"#");
      break;
      
      //velocity.jump.fwd.x
      case 35:
        m_Stack.Push(m_pPlayer1->myPlayerConst.PlayerVelocity.JumpFwd.x,"#");
      break;
      
      //velocity.runjump.back.x
      case 36:
        m_Stack.Push(m_pPlayer1->myPlayerConst.PlayerVelocity.RunBack.x,"#");
      break;
      
      //velocity.runjump.fwd.x
      case 37:
        m_Stack.Push(m_pPlayer1->myPlayerConst.PlayerVelocity.RunFwd.x,"#");
      break;
      
      //velocity.airjump.neu.x
      case 38:
        m_Stack.Push(m_pPlayer1->myPlayerConst.PlayerVelocity.AirjumpNeu.x,"#");
      break;
      
      //velocity.airjump.back.x
      case 39:
        m_Stack.Push(m_pPlayer1->myPlayerConst.PlayerVelocity.AirjumpBack.x,"#");
      break;
      
      //velocity.airjump.fwd.x
      case 40:
        m_Stack.Push(m_pPlayer1->myPlayerConst.PlayerVelocity.AirjumpFwd.x,"#");
      break;
      
      //movement.airjump.num
      case 41:
        m_Stack.Push(m_pPlayer1->myPlayerConst.PlayerMovement.AirJumpNum,"#");
      break;
      
      //movement.airjump.height
      case 42:
        m_Stack.Push(m_pPlayer1->myPlayerConst.PlayerMovement.nAirJumpHight,"#");
      break;
      
      //movement.yaccel
      case 43:
        m_Stack.Push(m_pPlayer1->myPlayerConst.PlayerMovement.yaccel,"#");
      break;
      
      //movement.stand.friction
      case 44:
        m_Stack.Push(m_pPlayer1->myPlayerConst.PlayerMovement.StandFriction,"#");
      break;
      
      //movement.crouch.friction
      case 45:
        m_Stack.Push(m_pPlayer1->myPlayerConst.PlayerMovement.CrouchFriction,"#");
      break;
      //velocity.jump.y
      case 46:
       m_Stack.Push(0,"#");
      break;
      //velocity.airjump.y
      case 47:
       m_Stack.Push(0,"#");
      break;


      default:
        PrintMessage("CVirtualMachine::Invalide Const Param");    
      break;
   }

}

//cosinus
void CVirtualMachine::Cos()
{
    PopValue();
    temp1=m_pop.Value;
    
    temp1=cos(temp1);
    m_Stack.Push(temp1,"#");

}

//Check control of player
void CVirtualMachine::Ctrl()
{
   if(m_pPlayer1->IsCtrl())
        m_Stack.Push(1.0,"#");
    else
        m_Stack.Push(0.0,"#");

}
//DrawGame TODO:Complete this
void CVirtualMachine::DrawGame()
{
  m_Stack.Push(0.0,"#");
}

//Exp to e
void CVirtualMachine::Exp()
{
    PopValue();
    temp1=m_pop.Value;
    
    temp1=pow(2.71828182f,temp1);
    m_Stack.Push(temp1,"#");
 
}
//retunr the facing direction
void CVirtualMachine::Facing()
{
    //true = right facing = 1
    //flase = left facing = -1
  /*  if(m_pPlayer1->PlRtInfo.bFacing)
       m_Stack.Push(1.0,"#");
    else
       m_Stack.Push(-1.0,"#");*/

}

//Floor
void CVirtualMachine::Floor()
{
    PopValue();
    temp1=m_pop.Value;
    
    temp1=floor(temp1);
    m_Stack.Push(temp1,"#");

}

//FrontEdgeBodyDist
void CVirtualMachine::FrontEdgeBodyDist()
{
    //TODO:Compute the distance between the front and the player
     m_Stack.Push(124,"#");
}

//FrontEdgeDist
void CVirtualMachine::FrontEdgeDist()
{
    //TODO:Compute the distance between the x-axis of the player and  screen
     m_Stack.Push(124,"#");
}
//FVAR
void CVirtualMachine::FVar()
{
   /* PopValue();
    temp1=m_pop.Value;
    
    temp1=m_pPlayer1->GetFVar((int)temp1);
    m_Stack.Push(temp1,"#");
*/
}

//GameTime
void CVirtualMachine::GameTime()
{
    //TODO:Put the real game time on Stack
  //  m_Stack.Push((float)GetGameTicks(),"#");
    
}

//GetHitVar
void CVirtualMachine::GetHitVar()
{
    //TODO:Get the correct Hitvar and push it on the stack
    PopValue();
    temp1=m_pop.Value;
   
     m_Stack.Push(0,"#");

}

void CVirtualMachine::HitCount()
{
   //TODO:Push the correct value on stack
   m_Stack.Push(0,"#");

}


void CVirtualMachine::HitFall()
{
    m_Stack.Push(0,"#");
}

void CVirtualMachine::HitOver()
{
    m_Stack.Push(0,"#");
}

void CVirtualMachine::HitPauseTime()
{
     m_Stack.Push(0,"#");
}

void CVirtualMachine::HitShakeOver()
{
     m_Stack.Push(0,"#");
}

//HitVel [component]
void CVirtualMachine::HitVel()
{
    PopValue();
    temp1=m_pop.Value;
    
    //Pop the component value
    //1==X 2==y
     m_Stack.Push(0,"#");

}

//ID return the ID number of the player
void CVirtualMachine::PlayerIdent()
{
  //  m_Stack.Push((float)m_pPlayer1->PlRtInfo.nID,"#");

}

//IfElse(exp_cond,exp_true,exp_false)#
void CVirtualMachine::IfElse()
{
    //pops in reverse order
    //exp_false
    PopValue();
    temp3=m_pop.Value;
    //exp_true
    PopValue();
    temp2=m_pop.Value;
    //exp_cond
    PopValue();
    temp1=m_pop.Value;
    
    if(temp1==1.0f)
        m_Stack.Push(temp2,"#");
    else
        m_Stack.Push(temp3,"#");

}

/*        InGuardDist 
Returns 1 if the player is within guarding distance of an opponent's physicalor projectile attack.
The guarding distance is the value of the guard.dist parameter of the
opponent's HitDef. Returns 0 if out of guard distance, or the opponent is not attacking.
*/
void CVirtualMachine::InGuardDist()
{
    m_Stack.Push(0,"#");
}

//Is helper
void CVirtualMachine::IsHelper()
{
     m_Stack.Push(0,"#");
}

//IsHomeTeam
void CVirtualMachine::IsHomeTeam()
{
    m_Stack.Push(0,"#");
}
//return the life of the player
void CVirtualMachine::Life()
{
  //  m_Stack.Push((float)m_pPlayer1->PlRtInfo.nLife,"#");
    

}

//return the max life
void CVirtualMachine::LifeMax()
{
   //  m_Stack.Push((float)m_pPlayer1->myPlayerConst.PlayerData.nLife,"#");
}

void CVirtualMachine::LogN()
{
    m_Stack.Push(m_Stack.Pop().Value,"#");

}

void CVirtualMachine::Log()
{
    //Push  the 2 arguments
    m_Stack.Pop();
    m_Stack.Pop();
    m_Stack.Push(0,"#");
}

void CVirtualMachine::Lose()
{
    //Pop the parameter 1=Lose, 2=LoseKO ,3=LoseTime
    switch((int)m_Stack.Pop().Value)
    {
        case 1:
          m_Stack.Push(0,"#");
        break;
        
        case 2:
          m_Stack.Push(0,"#");
        break;
        
        case 3:
          m_Stack.Push(0,"#");
        break;
    
    
    }

}
//Returns the current match number.
void CVirtualMachine::MatchNo()
{
    m_Stack.Push(1,"#");
}

void CVirtualMachine::MatchOver()
{
    m_Stack.Push(0,"#");
}

void CVirtualMachine::MoveContact()
{
    m_Stack.Push(0,"#");
}

void CVirtualMachine::MoveGuarded()
{
    m_Stack.Push(0,"#");
}

void CVirtualMachine::MoveHit()
{
    m_Stack.Push(0,"#");
}

/*MoveType gives the player's move-type. Refer to the section
  on StateDef in the CNS documentation for more details on MoveType.
  Useful for "move interrupts" in the CMD file.
*/
void CVirtualMachine::MoveType()
{   
    //Pop the type to check
    //Types are A(ttack),I(dle),H(it)
    m_Stack.Pop();
    
    //for now push False on the stack
    m_Stack.Push(0,"#");

}

void CVirtualMachine::MoveReversed()
{
    //for now push False on the stack
    m_Stack.Push(0,"#");
}

void CVirtualMachine::Name()
{
    //Push the name of the player
 //   m_Stack.Push(0,m_pPlayer1->myPlayerData.strName);

}

void CVirtualMachine::NumEnemy()
{
    //for now only one enemy is supported
    m_Stack.Push(1,"#");

}

void CVirtualMachine::NumExplod()
{
     if(m_Stack.Pop().Value==1)
    {
        //Pop the parameter
         PrintMessage("NumExplod Paramerter is %i",(int)m_Stack.Pop().Value);
          m_Stack.Push(0,"#");
    }
    else
    {
        //default
        m_Stack.Push(0,"#");
    }

}

//Return the Number of helpers
void CVirtualMachine::NumHelper()
{
    if(m_Stack.Pop().Value==1)
    {
        //Pop the parameter
         PrintMessage("NumHelper Paramerter is %i",(int)m_Stack.Pop().Value);
          m_Stack.Push(0,"#");
    }
    else
    {
        //default
        m_Stack.Push(0,"#");
    }
    
    

}

void CVirtualMachine::NumPartner()
{
     m_Stack.Push(0,"#");
}

void CVirtualMachine::NumProj()
{
    m_Stack.Push(0,"#");
}

void CVirtualMachine::NumProjID()
{
    m_Stack.Pop();
    m_Stack.Push(0,"#");
}

void CVirtualMachine::NumTarget()
{
   if(m_Stack.Pop().Value==1)
    {
        //Pop the parameter
         PrintMessage("NumTarget Paramerter is %i",(int)m_Stack.Pop().Value);
          m_Stack.Push(0,"#");
    }
    else
    {
        //default
        m_Stack.Push(0,"#");
    }

}

void  CVirtualMachine::P2BodyDist()
{
    //1 = X Value
    if(m_Stack.Pop().Value==1)
    {
           m_Stack.Push(0,"#");
    }//Else y value
    else
    {
        //default
        m_Stack.Push(0,"#");
    }

}

void CVirtualMachine::P2Dist()
{
    //1 = X Value
    if(m_Stack.Pop().Value==1)
    {
           m_Stack.Push(0,"#");
    }//Else y value
    else
    {
        //default
        m_Stack.Push(0,"#");
    }

}
void CVirtualMachine::P2Life()
{
  //  m_Stack.Push((float)((CPlayer*)m_p2)->PlRtInfo.nLife,"#");

}

void CVirtualMachine::P2MoveType()
{
    //default
    m_Stack.Push(0,"#");

}

void CVirtualMachine::P2Name()
{
   // m_Stack.Push(0,((CPlayer*)m_p2)->myPlayerData.strName);

}

void CVirtualMachine::P2StateNo()
{
  //   m_Stack.Push((float)((CPlayer*)m_p2)->PlRtInfo.nState,"#");
}

void CVirtualMachine::P2StateType()
{
     m_Stack.Push(0,"#");
}

void CVirtualMachine::P3Name()
{
     m_Stack.Push(0,"P3Name");
}

void CVirtualMachine::P4Name()
{
     m_Stack.Push(0,"P4Name");
}

void CVirtualMachine::PalNo()
{
    m_Stack.Push(0,"#");
}

void CVirtualMachine::ParentDist()
{
    //1 = X Value
    if(m_Stack.Pop().Value==1)
    {
           m_Stack.Push(0,"#");
    }//Else y value
    else
    {
        //default
        m_Stack.Push(0,"#");
    }

}

void CVirtualMachine::Pi()
{
    m_Stack.Push(3.141592653589f,"#");
}

void CVirtualMachine::PlayerIDExist()
{
    //default
    m_Stack.Pop();
    m_Stack.Push(0,"#");

}

void CVirtualMachine::PrevStateNo()
{
   // m_Stack.Push((float)m_pPlayer1->PlRtInfo.nPrevState,"#");
}

void CVirtualMachine::Pos()
{
    //1 = X Value
  /*  if(m_Stack.Pop().Value==1)
    {
           m_Stack.Push(m_pPlayer1->PlRtInfo.x-XROOT,"#");
    }//Else y value
    else
    {
        //default
        m_Stack.Push(m_pPlayer1->PlRtInfo.y,"#");
    }*/

}

void CVirtualMachine::Power()
{
  //  m_Stack.Push((float)m_pPlayer1->PlRtInfo.nLevelPower,"#");
}

void CVirtualMachine::PowerMax()
{
   m_Stack.Push(3000,"#");
}

void CVirtualMachine::ProjCancelTime()
{
    m_Stack.Pop();
    m_Stack.Push(1000,"#");
}
void CVirtualMachine::Random()
{
  /*srand(1);
  m_Stack.Push((float)rand(),"#");  */

}

void CVirtualMachine::RootDist()
{
 //1 = X Value
    if(m_Stack.Pop().Value==1)
    {
           m_Stack.Push(0,"#");
    }//Else y value
    else
    {
        //default
        m_Stack.Push(0,"#");
    }

}

void CVirtualMachine::RoundNo()
{
     m_Stack.Push(0,"#");
}

void CVirtualMachine::RoundsExisted()
{
    m_Stack.Push(0,"#");
}

void CVirtualMachine::RoundState()
{
    //2= do battle
    m_Stack.Push(2,"#");

}
void CVirtualMachine::ScreenPos()
{
//1 = X Value
 /*   if(m_Stack.Pop().Value==1)
    {
       m_Stack.Push(m_pPlayer1->PlRtInfo.x,"#");
    }//Else y value
    else
    {
        //default
        m_Stack.Push(m_pPlayer1->PlRtInfo.y,"#");
    }
*/
}

void CVirtualMachine::SelfAnimExist()
{
   /* int nAnim;
    PopValue();
    nAnim=(int)m_pop.Value;
    //If != NULL push true else push false
    if(m_pPlayer1->m_AirManager.GetAction(nAnim) != NULL)
        m_Stack.Push(1,"#");
    else
        m_Stack.Push(0,"#");
    
*/
}


void CVirtualMachine::Sin()
{
    m_Stack.Push(sin(m_Stack.Pop().Value),"#");
}

void CVirtualMachine::StateNo()
{
    //m_Stack.Push((float)m_pPlayer1->PlRtInfo.nState,"#");
}

void CVirtualMachine::StateType()
{
  //  m_Stack.Push((float)m_pPlayer1->PlRtInfo.nStateTyp,"#");
}

void CVirtualMachine::SysFVar()
{
    m_Stack.Pop();
    m_Stack.Push(0,"#");

}

void CVirtualMachine::SysVar()
{
    m_Stack.Pop();
    m_Stack.Push(0,"#");

}

void CVirtualMachine::Tan()
{
    m_Stack.Push(tan(m_Stack.Pop().Value),"#");
}

void CVirtualMachine::TeamMode()
{
    m_Stack.Push(0,"#");
}

void CVirtualMachine::TeamSide()
{
     m_Stack.Push(1,"#");
}

void CVirtualMachine::TicksPerSecond()
{
     m_Stack.Push(60,"#");
}

void CVirtualMachine::Time()
{
  //  m_Stack.Push(m_pPlayer1->PlRtInfo.nStateTime,"#");
}

void CVirtualMachine::UniqHitCount()
{
     m_Stack.Push(1,"#");
}

void CVirtualMachine::Var()
{
     m_Stack.Pop();
     m_Stack.Push(1,"#");
}

void CVirtualMachine::Vel()
{
    //1 = X Value
   /* if(m_Stack.Pop().Value==1)
    {
       m_Stack.Push(m_pPlayer1->PlRtInfo.xvel,"#");
    }//Else y value
    else
    {
        //default
        m_Stack.Push(m_pPlayer1->PlRtInfo.xvel,"#");
    }*/

}

void CVirtualMachine::Win()
{
    switch((int)m_Stack.Pop().Value)
    {
        //Win
        case 1:
          m_Stack.Push(0,"#");      
        break;
        //WinKO
        case 2:
         m_Stack.Push(0,"#");
        break;
        //WinTime
        case 3:
         m_Stack.Push(0,"#");
        break;
        //WinPerfect
        case 4:
         m_Stack.Push(0,"#");
        break;
   
    }


}

void CVirtualMachine::ProjContact()
{
    m_Stack.Push(1,"#");
    m_Stack.Push(2,"#");

}

void CVirtualMachine::ProjContactTime()
{
    m_Stack.Pop();
    m_Stack.Push(0,"#");

}

void CVirtualMachine::ProjGuarded()
{
    m_Stack.Push(1,"#");
    m_Stack.Push(2,"#");

}

void CVirtualMachine::ProjGuardedTime()
{
    m_Stack.Pop();
    m_Stack.Push(0,"#");

}

void CVirtualMachine::MODOP()
{
    int nDividend,nDivisor;
    
    PopValue();
    nDivisor=(int)m_pop.Value;
    PopValue();
    nDividend=(int)m_pop.Value;
 #ifdef DEBUG
    PrintMessage("ModOp %i Mod %i=%i",nDividend,nDivisor);
#endif   
    
    nDividend=nDividend % nDivisor;

    
    if(nDividend==0)
        m_Stack.Push(1,"#");
    else
        m_Stack.Push(0,"#");
    


}

//Save one Value from stack for tempory 
void CVirtualMachine::Save()
{
    nSave=m_Stack.Pop().Value;
#ifdef DEBUG 
  PrintMessage("Save %f",nSave);
#endif    
    
}

//Restore the tempory Value to stack
void CVirtualMachine::Restore()
{
#ifdef DEBUG
    PrintMessage("restore %f",nSave);
#endif
    m_Stack.Push(nSave,"#");
    
}


