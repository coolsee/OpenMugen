#include "global.h"
//only include this when compiling for windows
#include "windows.h"

//Main object of the game
CGame mugen;

//only for VC compiler 
#ifdef WIN32
#pragma comment(lib, "SDL.lib")
#pragma comment(lib, "SDLmain.lib")
#endif

int main(int argc, char **argv)
{
    try
    {
     mugen.InitGame();
     mugen.RunGame();
     mugen.Quit();
    }
    catch(CError &e)
    {
      mugen.Quit();          
      //windows only , change this for other OS 
      MessageBox(0,e.GetError(),"Error",0 );       
    }
 
   return 0;
}
