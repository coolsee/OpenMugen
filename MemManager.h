#ifndef __MEMMANAGER__H
#define __MEMMANAGER__H

   enum {
       MAINMENU=0,
       STAGE=1,
       ENGINE=2,
       P1=3,
       P2=4,
       P3=5,
       P4=6
     };

class CAllocater
{

   char strAllocName[255];
   size_t  nAllocSize;
   size_t  nAllocNumber;
   size_t  nMemListSize;
   MEMLIST *lpMemList;
   bool bFree;
   
enum { FREE=0x00,
       ALLOC=0xff

      };
      void SetMemListFree(MEMLIST* lpList); 
public:
      //Constructor & Desctructor 
      CAllocater(char *strName);
      ~CAllocater();
      
      void ShowMemUsage();
      void* Alloc(size_t nSize,int nMemInit = 0);
      void* Realloc(void *CurMem,size_t nSize);
      void  Free(void *CurMem);
      void  FreeAllocater();
      void ResetAllocater();
      size_t   GetMemUsage(){return nAllocSize;}
      char *GetName(){return strAllocName;}        
      
};

class CMemManager
{
     CAllocater *lpAlloc[7];                 
public:
      //Constructor & Desctructor  
      CMemManager();
      ~CMemManager();
      
      void InitManager();
      CAllocater *GetAllocater(int nAllocater);
      void FreeManager();
      size_t GetMemUsage();
      
};

  
#endif
