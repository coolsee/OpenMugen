#ifndef __SFFMANAGER__H
#define __SFFMANAGER__H

class CSffManager
{
private:
  bool           bPalletLoaded;
  FILE           *lpSffFile;
//need pointer to classes
  CVideoSystem   *m_pVideoSystem;
  CAllocater     *m_pAlloc;
  CGameTimer     *m_pTimer;
  CAirManager    *m_pAirManger;
  //global color pallet    
  u16            ColorPallet[256];
  u16            nTotalImages;
  u16            nCurrImage;
  u16            nImageListSize;
  u16            nFlags;
  //Sprite list 
  SFFSPRITE*      lpSpriteList;
  //decode the PCX file by run lenght 
  u8* DecodePcx(u8* PcxByte,PCXHEADER header);
  int FindSprite(s16 nGroupNumber,s16 nImageNumber);
  void DecodeSffFile();
  float xScaleValue,yScaleValue; 
  //hold the current Animation
   ActionElement *Anim;          
public:
enum BLTFLAGS
{
   BLT_NORMAL=10,
   BLT_NORMALMASKED,
   BLT_FLIPH,
   BLT_FLIPHMASKED,
   BLT_FLIPV,
   BLT_FLIPVMASKED,
   BLT_FLIPHV,
   BLT_FLIPHVMASKED,
   BLT_ADDALPHA,
   BLT_SUBALPHA   
};       
    CSffManager();
    ~CSffManager();
    
    //returns the current animation
    ActionElement *GetCurrAnimation(){return Anim;}
    
    //Set the blt flags to chose wich blt operation should used
    void SetBltFlags(u16 nFlag){nFlags=nFlag;}
    
    void SetPointers(CVideoSystem* p,CAllocater *a,CGameTimer *t,CAirManager *air);
    bool LoadSffFile(const char *strSffFile);
    bool LoadActToSff(const char *strActFile);
    //x and y value are the axis value not the left corner of the image
    void BlitSprite(s16 nGroupNumber,s16 nImageNumber,s16 x, s16 y);
    void BlitAnim(s16 x, s16 y);
    void PrepareAnim(s32 nAnim);
    void ResetManager();
    void FreeManager();
      
};

#endif
