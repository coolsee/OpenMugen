//    Open Mugen is a redevelopment of Elecbyte's M.U.G.E.N wich will be 100% compatible to it
//    Copyright (C) 2004  Sahin Vardar
//
//    If you know bugs or have a wish on Open Muegn o
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

#ifndef VIDEO_H
#define VIDEO_H

const int SCREENX_LIMIT = 319;
const int SCREENY_LIMIT = 239;
const int XMAX = 320;
const int YMAX = 240;

class CVideoSystem
{
void LoadFont();
public:
    CVideoSystem();
    ~CVideoSystem();
    
bool InitSystem();
void CleanUp();
SDL_Surface* CreateSurface(int x,int y);
void Draw();
void Clear();
void DrawRect(Sint16 x,Sint16 y,Sint16 w,Sint16 h,Uint8 R,Uint8 G,Uint8 B);
void DrawText(int x,int y,char *strText,...);
void FilterImage();
u16  MapRGB(Uint8  red,Uint8  green,Uint8  blue);


//Blt functions

//normal Blt
void NormalBlt(SFFSPRITE *lpSprite,s16 x,s16 y,bool bMask);
void NormalFlipH(SFFSPRITE *lpSprite,s16 x,s16 y,bool bMask);
void NormalFlipV(SFFSPRITE *lpSprite,s16 x,s16 y,bool bMask);
void NormalFlipHV(SFFSPRITE *lpSprite,s16 x,s16 y,bool bMask);


//primitiv functions



    
private:
    SDL_Surface *screen;
    SDL_Surface *work;
    SDL_Surface *font;
    
    Uint8* deltaPtr;
    Uint32 nowTime,lastTime;
    Uint32 nFpsCount;
    float nFps;
    FPSmanager m_FPSmanager;
    MUGENFONT my_Fonts[255];
   
                
};


#endif
