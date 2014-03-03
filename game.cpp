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
CGame::CGame()
{
    bError=false;
    bGame=true;
    nStartTime=nEndTime=0;
    nGameType=GFIGHTGAME;
}

//Destructor
CGame::~CGame()
{

}
//Init the hole game 
void CGame::InitGame()
{
    //First init the Log file system
    InitLogFile();
    //Now print Welcome Message
    PrintMessage("Welcome to OpenMugen Version %s",VER);
    //Now init SDL system
    PrintMessage("CGame:Init SDL system");
    
    m_MemManager.InitManager();
    
    if(!m_SdlManager.Init())
    {
        PrintMessage("CGame:SDL init failed");
        bError=true;
    
    }
    
    //init timer
    m_Timer.ResetTimer();
    //init the main engine
    m_FightEngine.InitEngine(&m_MemManager,
                             m_SdlManager.GetVideoSystem(),
                             &m_Timer);
    
       
    m_MemManager.GetMemUsage();
}
//The main game Loop
void CGame::RunGame()
{
    while(bGame)
    {
       //Checks SDL system and Get Input
       CheckSDL();
       //UpDateTimer;
       m_Timer.UpdateTimer();
       //Clear the Screen
       m_SdlManager.m_VideoSystem.Clear();
       //switch to the current Subsystem
       switch(nGameType)
       {
          //We running the Fight engine
          case GFIGHTGAME:
               m_FightEngine.RunEngine();
          break;
          //We are in the menu screen
          case GMENU:
          
          break;
       
       
       }
     //  m_SdlManager.m_VideoSystem.DrawText(10,20,"%i",m_Timer.GetGameTime());
       //Now draw the content to the screen     
       m_SdlManager.m_VideoSystem.Draw();
       //Limits the game speed to 60Hz
      
    }

}
//Checks the SDL event list
void CGame::CheckSDL()
{

   SDL_PollEvent(&event);
 
   if(event.type==SDL_QUIT)
       bGame=false;
   
   if(event.key.keysym.sym==SDLK_ESCAPE)
       bGame=false;
 
}

//Exit the game and cleans the memory and SDL
void CGame::Quit()
{
    m_MemManager.FreeManager(); 
    m_SdlManager.CleanSDL();
    SDL_Quit();
  
}

void CGame::Crash()
{
    
}
