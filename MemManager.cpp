#include "global.h"

CAllocater::CAllocater(char *strName)
{
   //copy the name
   strcpy(strAllocName,strName);
   nAllocSize=0;
                           
}

CAllocater::~CAllocater()
{
                         
}

void CAllocater::SetMemListFree(MEMLIST* lpList)
{
  memset(lpList,0,sizeof(MEMLIST)*100);   
}


void CAllocater::ResetAllocater()
{
    nAllocSize=0;
    nAllocNumber=0;
    nMemListSize=100;
    bFree=true;
    lpMemList=(MEMLIST*)malloc(sizeof(MEMLIST)*nMemListSize);
    SetMemListFree(lpMemList);     
}


void CAllocater::ShowMemUsage()
{
    PrintMessage("---Memory usage of %s allocater",strAllocName); 
    PrintMessage("---Allocated memory %i in bytes",nAllocSize);
    PrintMessage("---Allocated number of Memory %i",nAllocNumber);
   // PrintMessage("////////////////////////////////////");
    PrintMessage("");
     
}
//Allocate memory and save its address in a list
void* CAllocater::Alloc(size_t nSize,int nMemInit)
{
      if(bFree)
         bFree=false;
      
      //if we have more alloaction as we can hold in ouer list then grow ouer list
      if(nAllocNumber > nMemListSize-1)
      {
        //grow the list by 100
        nMemListSize+=100;
        lpMemList=(MEMLIST*)realloc(lpMemList,sizeof(MEMLIST)*nMemListSize);
        //set memlist empty
        SetMemListFree(&lpMemList[nMemListSize-100]);
                                
      }

	 
      u32 i;
      //search the list for a free place to hold the address
      for (i=0;i<nMemListSize;i++)
       if(lpMemList[i].nType==FREE) break;
       
      if(i > nMemListSize)
          PrintMessage("CAllocater::no free block found"); 
       
      lpMemList[i].nType=ALLOC;
      lpMemList[i].adrress=malloc(nSize);
      
      if(lpMemList[i].adrress==0)
         PrintMessage("CAllocater::malloc failed");                        
      
      memset(lpMemList[i].adrress,0,nSize);
      lpMemList[i].nSize=nSize;
 
      nAllocNumber++;
      nAllocSize+=nSize;
 
      return lpMemList[i].adrress;
 
       
}
//reallocate the given memory block and save the new address in the list
void* CAllocater::Realloc(void *CurMem,size_t nSize)
{
  u32 i;
  bool bFound=false;
      
  for(i=0;i<nMemListSize;i++)
  {
      if(CurMem==lpMemList[i].adrress && lpMemList[i].nType == ALLOC )
      {
       bFound=true;
       break;
      }
  }
  
  if(!bFound)
     PrintMessage("Realloc failed %x was never allocated",CurMem);        
  
  nAllocSize-=lpMemList[i].nSize;
  
  lpMemList[i].adrress=realloc(lpMemList[i].adrress,nSize);
  lpMemList[i].nSize=nSize;
  nAllocSize+=nSize;
  
  
  return lpMemList[i].adrress;
 
}

//seacrh the list for the allocated block and free it from memory
void CAllocater::Free(void *CurMem)
{
     
  u32 i;
  bool bFound=false;
      
  for(i=0;i<nMemListSize;i++)
  {
      if(CurMem==lpMemList[i].adrress && lpMemList[i].nType == ALLOC )
      {
       bFound=true;
       break;
      }
  }
  
  if(!bFound)
     PrintMessage("free failed %x was never allocated",CurMem);
     
   free(lpMemList[i].adrress);
   lpMemList[i].adrress=0;
   lpMemList[i].nType=FREE;
   nAllocSize-=lpMemList[i].nSize;
   
   nAllocNumber--;
  
}


//Free all allocated memory
void CAllocater::FreeAllocater()
{
     if(!bFree)
     {
       for(u32 i=0;i<nMemListSize;i++)
       {
         if(lpMemList[i].nType==ALLOC) Free(lpMemList[i].adrress);      
       
       }
               
     } 
    // PrintMessage("CAllocater::%s unfreed %i bytes",strAllocName,nAllocSize);
     //clear ouer memlist         
     free(lpMemList);
     
}

//the MemManager with the included allocaters
CMemManager::CMemManager()
{
                          
}

CMemManager::~CMemManager()
{
                           
}

void CMemManager::InitManager()
{
      
     lpAlloc[MAINMENU]         =new CAllocater("Main Menu");
     lpAlloc[STAGE]            =new CAllocater("Stage");
     lpAlloc[ENGINE]           =new CAllocater("Engine");
     lpAlloc[P1]               =new CAllocater("Player 1");
     lpAlloc[P2]               =new CAllocater("Player 2");
     lpAlloc[P3]               =new CAllocater("Player 3");
     lpAlloc[P4]               =new CAllocater("Player 4");
     
     PrintMessage("Init Memory Manager");
}

CAllocater* CMemManager::GetAllocater(int nAllocater)
{
  return lpAlloc[nAllocater];          
}

//free all the allocaters from mem
void CMemManager::FreeManager()
{
     for(int i=0;i<7;i++)
     {
             lpAlloc[i]->FreeAllocater();
             delete lpAlloc[i];
     }
     
}
//show and return the memusage
size_t CMemManager::GetMemUsage()
{
   size_t nMem=0;
   
   PrintMessage("======================Memory Manager============================");
   PrintMessage("|Name:               |Allocated bytes                          |"); 
   PrintMessage("----------------------------------------------------------------");

   for(int i=0;i<7;i++)
   {
   PrintMessage("|%20s                  |%20i  | ",lpAlloc[i]->GetName(),lpAlloc[i]->GetMemUsage());
   }
   PrintMessage("================================================================");  
   return nMem;
    
}
