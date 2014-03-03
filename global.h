#ifndef __GLOBAL__H
#define __GLOBAL__H

//Version
#define VER     "Alpha 2"
#define OMTITLE "OpenMugen"

#include "SDL.h"

//SDL_GFX libery


//standart include
#include <memory.h>
#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <math.h>

//using namespace std;

//used class
class CPlayer;
class CVirtualMachine;
class CGameTimer;

#include "structs.h"
#include "MemManager.h"

//Nate Pendeltons Tokenizer
#include "tokenizer.h"
#include "cmdManager.h"

#include "scale2x.h"
#include "Timer.h"
#include "SDL_framerate.h"
#include "VideoSystem.h"
#include "SDLManager.h"
#include "AirManager.h"
#include "SffManager.h"
#include "Stack.h"
#include "StateManager.h"
#include "ControllerExecuter.h"
#include "player.h"
#include "VM.h"
#include "StateParser.h"
#include "engine.h"
#include "game.h"

//functions
void PrintMessage(char *str,...);
void InitLogFile();

#endif
