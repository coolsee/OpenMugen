#include "global.h"


//Main object of the game
CGame mugen;

//only for VC compiler 
#ifdef WIN32
//only include this when compiling for windows
#include "windows.h"
#pragma comment(lib, "SDL.lib")
#pragma comment(lib, "SDLmain.lib")
#endif

#ifdef WIN32
#pragma comment(lib, "SDL.lib")
#pragma comment(lib, "SDLmain.lib")
#endif

char globalStr[1024];
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
    }
 
   return 0;
}
