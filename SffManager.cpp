#include "global.h"


CSffManager::CSffManager()
{
  m_pVideoSystem=0;
  m_pAlloc=0;  
  xScaleValue=1.0;
  yScaleValue=1.0;                     
                          
}

CSffManager::~CSffManager()
{
                           
}

//Set the pointers to the class
void CSffManager::SetPointers(CVideoSystem* p,CAllocater* a,CGameTimer *t,CAirManager *air)
{
     m_pVideoSystem=p;
     m_pAlloc=a;
     m_pTimer=t;
     m_pAirManger=air;
}

//reste the class variables
void CSffManager::ResetManager()
{
     bPalletLoaded=false;
     lpSffFile=0;
     nTotalImages=0;
     nCurrImage=0;
     nImageListSize=100;
     lpSpriteList=(SFFSPRITE*)m_pAlloc->Alloc(sizeof(SFFSPRITE)*nImageListSize);
     //NORMAL BLIT
     nFlags=BLT_NORMAL;
     
}

//load and deccode the SFF sprite and store it in a array
bool CSffManager::LoadSffFile(const char *strSffFile)
{
  SFFHEADER header;   

  PrintMessage("CSffManager::Loading %s",strSffFile);
  
  lpSffFile=fopen(strSffFile,"rb");
  
  if(lpSffFile==0)
  {
     PrintMessage("CSffManager::Can't find %s",strSffFile);             
     return false;
  }
  
  //read the header of the file
  fread(&header,sizeof(header),1,lpSffFile);
  
  //check file signatur
  if(strcmp((char*)header.signature,"ElecbyteSpr")!=0)
  {
    PrintMessage("CSffManager::%s is not an SFF file",strSffFile);
    return false;                                           
                                               
  }
  PrintMessage("CSffManager::Sff file include %i images",header.NumberOfImage);
  
  //move the file to the first subheader
  fseek(lpSffFile,header.SubHeaderFileOffset,SEEK_SET);
  
  DecodeSffFile();
  
  fclose(lpSffFile);
  
  //save memory
  lpSpriteList=(SFFSPRITE*)m_pAlloc->Realloc(lpSpriteList,sizeof(SFFSPRITE)*nTotalImages);
  
     
  return true;
}
//Load an Colorpallet from file
bool CSffManager::LoadActToSff(const char *strActFile)
{
  bPalletLoaded=true;    
  
  FILE *Act=fopen(strActFile,"rb");

	if(Act==NULL)
	   	PrintMessage("CSffSpriteManager %s File not found",strActFile);
		

	for(int j=255;j>=0;j--)
	{
        int r,g,b;    
        r=fgetc(Act);
        g=fgetc(Act);
        b=fgetc(Act); 
            
		ColorPallet[j]=m_pVideoSystem->MapRGB(r,
                                              g,
                                              b)   ;
	}



	fclose(Act);
  return true;    
}

//blt function
void CSffManager::BlitSprite(s16 nGroupNumber,s16 nImageNumber,s16 x, s16 y)
{
     //search the Sprite int the list
     int i=FindSprite(nGroupNumber,nImageNumber);
 
     if(i==-1)
        return;
        
    //normal blit with with masked bits
    if(nFlags==BLT_NORMAL)
       m_pVideoSystem->NormalBlt(&lpSpriteList[i],x,y,false);
    
    if(nFlags== BLT_NORMALMASKED)
       m_pVideoSystem->NormalBlt(&lpSpriteList[i],x,y,true);
       
    if(nFlags== BLT_FLIPH)
       m_pVideoSystem->NormalFlipH(&lpSpriteList[i],x,y,false);
       
    if(nFlags== BLT_FLIPHMASKED)
       m_pVideoSystem->NormalFlipH(&lpSpriteList[i],x,y,true);
                         
    
     
    
}

//prepares the animation
void CSffManager::PrepareAnim(s32 nAnim)
{
    Anim=m_pAirManger->GetAction(nAnim);
    
    Anim->nDuringTime=m_pTimer->GetGameTime()+Anim->AnimationElement[0].nDuringTime;
    Anim->nCurrentImage=0;
    Anim->bLooped=false;
    Anim->nCurrentImageTime=0;
    Anim->nCurrTime=0;
}


//Blit the given animation
void CSffManager::BlitAnim(s16 x, s16 y)
{
    
            
    BlitSprite(Anim->AnimationElement[Anim->nCurrentImage].nGroupNumber,
                Anim->AnimationElement[Anim->nCurrentImage].nImageNumber,
                x,y);
                
    
        
     //is the current image in time? && do not check if during time of the current image is -1
     if(Anim->nDuringTime <= m_pTimer->GetGameTime() && Anim->AnimationElement[Anim->nCurrentImage].nDuringTime!=-1)
     {
       Anim->nCurrentImage++;
       
      
       if(Anim->nCurrentImage >= Anim->nNumberOfElements)
       {
          Anim->nCurrentImage=0;
          Anim->nCurrTime=0;
         //if we have a loop start go to it
         if(Anim->loopStart!=-1) 
         Anim->nCurrentImage=Anim->loopStart;
          
       }
       

       //calculate the new during time
       Anim->nDuringTime=m_pTimer->GetGameTime()+Anim->AnimationElement[Anim->nCurrentImage].nDuringTime;
           
     }
     Anim->nCurrTime++;
     
     
}

//decodes one PCX file
u8* CSffManager::DecodePcx(u8* PcxByte,PCXHEADER header)
{
  u8* byImageBuffer=0;
  u8 BPP,byData;  
  u16 size;
  s16 x,y,widht;
  u32 Pos=0;
  
  u32 nCountByte,nTotalyByte,
      nHowManyBytes,nHowManyBlank;
      
  nTotalyByte=header.bytesPerLine*header.NPlanes;
	
	nHowManyBytes=0;
	nHowManyBlank=0;
	nCountByte=0;
	
  BPP=header.NPlanes*8; 
  
  //allocate memory
  byImageBuffer=(u8*)m_pAlloc->Alloc(sizeof(u8)*(header.widht*header.NPlanes*header.height+1));
  
  widht=header.widht;

  if(widht<header.bytesPerLine * header.NPlanes)
		widht=header.bytesPerLine*header.NPlanes;
		
   //we do not support 24bit pcx images
   if(BPP>8)
   {
            
     PrintMessage("24Bit pcx file is not supproted");       
     return byImageBuffer;
   }

	size=0;
	y=0;
	x=0;
	for(y=0;y<header.height;y++)
	{
		x=0;
		while(x < widht)
		{
	     
			  byData=PcxByte[Pos++];

			  if( (byData & 0xC0) == 0xC0 )
			  {
				  size = byData & 0x3F;
				  byData=PcxByte[Pos++];

			  }
			  else
			  {
				size=1;
			  }

			       while(size-- > 0)
				  {
					  if(x <= header.widht)
					  {
						byImageBuffer[x + (y * header.widht)]=byData;
						
					  }
					//this it to Skip blank data on PCX image wich are on the right side
					//TODO:OK? Skip two bytes
      				  if(x == widht && widht != header.widht)
      				  {
      				         nHowManyBlank=widht-header.widht;
      				         for(u32 i=0;i<nHowManyBlank;i++)
					              Pos+=2;
					  }
				      x++;
	  					 
				  }
				 
         } 
		
    }
    
  return byImageBuffer;    
}

void CSffManager::DecodeSffFile()
{
    SFFSUBHEADER subheader;
    u8 *tempByte;
    //read the first subheader
    fread(&subheader,sizeof(subheader),1,lpSffFile);
    
     
    while(!feof(lpSffFile))
    {
      //when we need more a bigger array to store the information that get an bigger array                    
      if(nTotalImages > nImageListSize-1)
      {
        nImageListSize+=100;
        lpSpriteList=(SFFSPRITE*)m_pAlloc->Realloc(lpSpriteList,sizeof(SFFSPRITE)*nImageListSize);
         
       
      }
	        
      //copy the information contained in the subheader
      lpSpriteList[nTotalImages].GroupNumber=subheader.GroubNumber;
      lpSpriteList[nTotalImages].ImageNumber=subheader.ImageNumber;
      lpSpriteList[nTotalImages].x=subheader.x;
      lpSpriteList[nTotalImages].y=subheader.y;
                 
      //is it a linked sprite??
      if(subheader.LenghtOfSubheader!=0)
      {
        //read the pcx header
        fread(&lpSpriteList[nTotalImages].PcxHeader,sizeof(PCXHEADER),1,lpSffFile);
        
        //Correct the Image dimension 
		lpSpriteList[nTotalImages].PcxHeader.widht=lpSpriteList[nTotalImages].PcxHeader.widht - lpSpriteList[nTotalImages].PcxHeader.x + 1;
		lpSpriteList[nTotalImages].PcxHeader.height=lpSpriteList[nTotalImages].PcxHeader.height - lpSpriteList[nTotalImages].PcxHeader.y +1;
		
		//now read the pcx data 
		//TODO:check subheader.LenghtOfSubheader
		tempByte=(u8*)m_pAlloc->Alloc(sizeof(u8)*(subheader.LenghtOfSubheader-127));
		fread(tempByte,sizeof(u8)*(subheader.LenghtOfSubheader-127),1,lpSffFile);
		
		lpSpriteList[nTotalImages].byPcxFile=DecodePcx(tempByte,
                                                       lpSpriteList[nTotalImages].PcxHeader);
  
        //free memormy                                               
        m_pAlloc->Free(tempByte);
        
        //move the file pointer to Color pallet of the PCX file
		fseek(lpSffFile,-768L,SEEK_CUR);
		
        //eat empty 8bit
		fgetc(lpSffFile);
		
		if(fgetc(lpSffFile)==12 && !subheader.PalletSame &&
           !bPalletLoaded       && lpSpriteList[nTotalImages].PcxHeader.NPlanes<=1)
        {
           for(int j=0;j<256;j++)
    	   {
                   int r,g,b;
                   r=fgetc(lpSffFile);
                   g=fgetc(lpSffFile);
                   b=fgetc(lpSffFile);
		           ColorPallet[j]=m_pVideoSystem->MapRGB(r,
                                                         g,
                                                         b );
                   

           }
                                
        }
        
        //copy the color pallet to the Sffsprite Struct
		memcpy(&lpSpriteList[nTotalImages].ColorPallet,
               &ColorPallet,
               sizeof(u16)*256);   

                                        
      }
      else
      {
		  //subheader.IndexOfPrevious-1 if the first ellement is 1 and not 0
          // we have a linked image here
          memcpy(&lpSpriteList[nTotalImages],
                 &lpSpriteList[subheader.IndexOfPrevious-1],
                 sizeof(SFFSPRITE));
                 
          lpSpriteList[nTotalImages].GroupNumber=subheader.GroubNumber;
          lpSpriteList[nTotalImages].ImageNumber=subheader.ImageNumber;
          
                    
          
      }
      nTotalImages++;
      
      fseek(lpSffFile,subheader.NextSubheaderFileOffset,SEEK_SET);
      //read the next subheader
      fread(&subheader,sizeof(subheader),1,lpSffFile);
                 
    }
    PrintMessage("CSffManager:: %i image are decoded",nTotalImages);
}

int CSffManager::FindSprite(s16 nGroupNumber,s16 nImageNumber)
{
    
    for(int i=0;i<nImageListSize;i++)
    {
       if(lpSpriteList[i].GroupNumber == nGroupNumber &&
          lpSpriteList[i].ImageNumber == nImageNumber)
       {   
              
       return i;                                   
       }
    }
    
    //no image found
    return -1;
}

void CSffManager::FreeManager()
{
     m_pAlloc->Free(lpSpriteList);
     lpSpriteList=0;
}

