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

CAirManager::CAirManager()
{
   

}

CAirManager::~CAirManager()
{
}

void CAirManager::ResetManager()
{
   nTotalActionBlock=0;
   nActionListSize=100;
   nElementListSize=100;
   nTotalCns=0;
   bDefaultClsn=false;
   
   lpActionList=(ActionElement*)m_pAlloc->Alloc(sizeof(ActionElement)*nActionListSize);

}
//add one action block int the list
void CAirManager::AddAction(s32 nActionNumber)
{
     RealocateActionBlock();
         
      //restet Complete animtime of the action block
     nAnimTime=0;
     nTotalElement=0;
     nElementListSize=100;
     bDefaultClsn=false;
         
     if(nTotalActionBlock > nActionListSize-1)
     {
        nActionListSize+=100;
        lpActionList=(ActionElement*)m_pAlloc->Realloc(lpActionList,sizeof(ActionElement)*nActionListSize);
                                  
     }
     //Set loop start -1
     lpActionList[nTotalActionBlock].loopStart=-1;
     lpActionList[nTotalActionBlock].nActionNumber     =nActionNumber;
     lpActionList[nTotalActionBlock].AnimationElement  =(Element*)m_pAlloc->Alloc(sizeof(Element)*nElementListSize);

     nTotalActionBlock++;
}
//Reallocates unessery memory
void CAirManager::RealocateActionBlock()
{
   if(nTotalActionBlock > 0)
   {
      lpActionList[nTotalActionBlock-1].AnimationElement=(Element*)m_pAlloc->Realloc(lpActionList[nTotalActionBlock-1].AnimationElement,
                                                                           sizeof(Element)*lpActionList[nTotalActionBlock-1].nNumberOfElements); 
   }
}

void CAirManager::AddElement(s16 nGroupNumber,s16 nImageNumber,s16 x,s16 y,
                             s16 nDuringTime,u16 nFlip,u32 nColorFlag)
{
   //TODO:Handel ColorFlags
   //32bit
   //8Bit ADDOP 8bit ADDOPVALUE 8bit SUBOP 8Bit SUBOPVALUE
   // PrintMessage("%i %i %i %i",nGroupNumber,nImageNumber,x,y);
   
   if(nTotalElement > nElementListSize-1)
   {
       nElementListSize+=100;
       lpActionList[nTotalActionBlock-1].AnimationElement  =(Element*)m_pAlloc->Realloc(lpActionList[nTotalActionBlock-1].AnimationElement,sizeof(Element)*nElementListSize);
   }
   
   lpActionList[nTotalActionBlock-1].AnimationElement[nTotalElement].nGroupNumber=nGroupNumber;
   lpActionList[nTotalActionBlock-1].AnimationElement[nTotalElement].nImageNumber=nImageNumber;
   lpActionList[nTotalActionBlock-1].AnimationElement[nTotalElement].x=x;
   lpActionList[nTotalActionBlock-1].AnimationElement[nTotalElement].y=y;
   lpActionList[nTotalActionBlock-1].AnimationElement[nTotalElement].nDuringTime=nDuringTime;
   lpActionList[nTotalActionBlock-1].AnimationElement[nTotalElement].FlipFlags=nFlip;
   lpActionList[nTotalActionBlock-1].AnimationElement[nTotalElement].ColorFlags=nColorFlag;
   
   lpActionList[nTotalActionBlock-1].nCompletAnimTime+=nDuringTime;
   
   lpActionList[nTotalActionBlock-1].AnimationElement[nTotalElement].nNumberOfClsn=nTotalCns;
   
       
   
   if(!bDefaultClsn)
   {
       lpActionList[nTotalActionBlock-1].AnimationElement[nTotalElement].pClnsData=(Clsn*)m_pAlloc->Alloc(sizeof(Clsn)*nTotalCns);             
      
       memcpy(lpActionList[nTotalActionBlock-1].AnimationElement[nTotalElement].pClnsData,
              pClsn,sizeof(Clsn)* nTotalCns); 
                                                                                        
       nTotalCns=0;
   }
   else
   {
       lpActionList[nTotalActionBlock-1].AnimationElement[nTotalElement].pClnsData=(Clsn*)m_pAlloc->Alloc(sizeof(Clsn)*nTotalCns);             
       memcpy(lpActionList[nTotalActionBlock-1].AnimationElement[nTotalElement].pClnsData,
       pClsn,sizeof(Clsn)* nTotalCns); 
   }
     
  
   nTotalElement++;
   lpActionList[nTotalActionBlock-1].nNumberOfElements=nTotalElement;

}

void CAirManager::SetLoop()
{
 lpActionList[nTotalActionBlock-1].loopStart=nTotalElement;

}
//to add a Clsn box 
void CAirManager::AddClsnBox(s16 x,s16 y,s16 w,s16 h,int nNumberOfClsn)
{
 /*   if(nTotalCns > 200)
       PrintMessage("To many Clsn boxes defined (more then 200!!!) line %i",nLineNr);*/
       
  /*  if(nNumberOfClsn!=nTotalCns)
       PrintMessage("Wrong cns index at line %i(%i != %i)",nLineNr,nNumberOfClsn,nTotalCns);*/

    pClsn[nTotalCns].ClsnRect.x=x;
    pClsn[nTotalCns].ClsnRect.y=y;
    pClsn[nTotalCns].ClsnRect.w=w;
    pClsn[nTotalCns].ClsnRect.h=h;
    pClsn[nTotalCns].bClsn1=bIsClsn1;
    
    
    nTotalCns++;
}

void CAirManager::CreateClsnBox(u16 nNumberOfClsn,bool bClsn1,bool bDefault)
{
  bDefaultClsn=bDefault;
  bIsClsn1=bClsn1;
 // nTotalCns=0;
  
}

ActionElement* CAirManager::GetAction(s32 nActionNumber)
{
    
    for(u16 i=0;i<nTotalActionBlock;i++)
    {
        if(lpActionList[i].nActionNumber==nActionNumber)
           return &lpActionList[i];
    
    }
    PrintMessage("No anim block with %i",nActionNumber);           
	
    return NULL;


}

void CAirManager::OpenAir(char *strFileName)
{
    CTokenizer tok;
    if( !tok.OpenFile( strFileName ) )
    {
        throw(CError("CAirManager::OpenAir : Can't open %s",strFileName));
        return;
    }
    
    tok.SetIsCaseSensitive(false);

    while( !tok.AtEndOfFile() )
    {
        int actionNum = -1;
        if( tok.CheckToken( "[" ) )
        {
            if( !tok.CheckToken( "Begin" ) )
            {
            }
            
            if( !tok.CheckToken( "Action" ) )
            {
            }                    
            
            if( !tok.CheckTokenIsNumber() )
            {
            }
            
            actionNum = tok.GetInt();
            
            if( !tok.CheckToken( "]" ) )
            {
            }
            
            AddAction( actionNum );                       
        }
        else if( tok.CheckToken( "Clsn1Default:", false ) || tok.CheckToken( "Clsn2Default:", false ) || tok.CheckToken( "Clsn1:", false ) || tok.CheckToken( "Clsn2:", false ) )
        {
            const char* token = tok.GetToken();
            bool isClsn1 = ( token[ 4 ] == '1' );
            bool isDefault = ( strlen( token ) > 7 );
                        
            if( !tok.CheckTokenIsNumber() )
            {
            }
            
            int clsnBoxCount = tok.GetInt();
            CreateClsnBox( clsnBoxCount, isClsn1, isDefault );
            
            for( int c = 0; c < clsnBoxCount; c++ )
            {
                if( !( tok.CheckToken( "Clsn1" ) || tok.CheckToken( "Clsn2" ) )) // for some reason kfm uses clsn2 sometimes in clsn1 items
                {
                }
                
                if( !tok.CheckToken( "[" ) )
                {
                }
                
                if( tok.GetInt() != c )
                {
                }

                if( !tok.CheckToken( "]" ) )
                {
                }

                if( !tok.CheckToken( "=" ) )
                {
                }
                
                int coor[4];
                for( int i = 0; i < 4; i++ )
                {
                    if( !tok.CheckTokenIsNumber() )
                    {
                    }
                    
                    coor[i] = tok.GetInt();
                    
                    if( i < 3 )
                    {
                        if( !tok.CheckToken( "," ) )
                        {
                        }
                    }
                }
                
                AddClsnBox( coor[0], coor[1], coor[2], coor[3], c ); 
            }
        }
        else if( tok.CheckToken( "Loopstart" ) )
        {
            SetLoop();
        }
        else if( tok.CheckTokenIsNumber() )
        {
            int values[5];
            for( int v = 0; v < 5; v++ )
            {
                if( !tok.CheckTokenIsNumber() )
                {
                }
                
                values[ v ] = tok.GetInt();
                
                if( v < 4 )
                {
                    if( !tok.CheckToken( "," ) )
                    {
                    }
                }
            }
            
            int flipFlag = 0;
            
            if( tok.CheckToken( "," ) )
            {
                if( tok.CheckToken( "H" ) )
                {
                    flipFlag = HFLIPFLAG;
                }
                else if( tok.CheckToken( "V" ) )
                {
                    flipFlag = VFLIPFLAG;
                }
                else if( tok.CheckToken( "VH" ) || tok.CheckToken( "HV" ) )
                {
                    flipFlag = HVFLIPFLAG;
                }
                else if( !tok.CheckToken( ",", false ) )
                {
                }
            }
            
            if( tok.CheckToken( "," ) )
            {
                tok.GetToken(); // alpha param
            }
            
            AddElement( values[0], values[1], values[2], values[3], values[4], flipFlag, 0 );
        }
        else
        {
        }
    }    
    tok.CloseFile();
}

void CAirManager::CleanUp()
{
   

}
