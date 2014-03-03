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

//Destructor
CSDLManager::~CSDLManager()
{

}
//Constructor
CSDLManager::CSDLManager()
{


}

//Init the SDL SUB systems
bool CSDLManager::Init()
{
    PrintMessage("CSDLManager:: Init()");

    //Init SDL and the sub-systems of it(VIDEO, TIMER AND AUDIO SYSTEM)
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO) < 0 )
    {
        PrintMessage("CSDLManager::SDL_Init Failed");
        PrintMessage("SDL error=%s",SDL_GetError());
        return false;
    }
    PrintMessage("CSDLManager:: SDL_Init OK");
    //Set the icon for the application
    SDL_WM_SetIcon(SDL_LoadBMP("icon.bmp"), NULL);
    
    //Now init ouer Video System
    if(!m_VideoSystem.InitSystem())
    {
        PrintMessage("CSDLManager:: VideoSystem Init Failed");
        return false;
    }
    PrintMessage("CSDLManager::VideoSystem Init OK");

	return true;
}

void CSDLManager::CleanSDL()
{
    PrintMessage("CSDLManager:: Cleaning SDL");
    m_VideoSystem.CleanUp();
    //SDL_Quit();
}
