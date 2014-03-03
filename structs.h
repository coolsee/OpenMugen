#ifndef __STRUCTS__H
#define __STRUCTS__H

//typedefs
typedef unsigned char   u8;
typedef signed   char   s8;
typedef unsigned short  u16;
typedef signed   short  s16;
typedef unsigned long   u32;
typedef signed   long   s32;



typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned long DWORD;

//#define MAX_PATH 255

//Define  Controller buttoms
enum KEY_NAMES
{
    KEY_UP,
    KEY_DOWN,
    KEY_LEFT,
    KEY_RIGHT,
    KEY_BUTTON_A,
    KEY_BUTTON_B,
    KEY_BUTTON_C,
    KEY_BUTTON_X,
    KEY_BUTTON_Y,
    KEY_BUTTON_Z,
    KEY_BUTTON_START,
    KEY_BUTTON_PAUSE,
    KEY_COUNT
};

struct KEYELEMENT
{
    KEYELEMENT()  { isPressed = false; sdlKeycode = 0; }
    Uint16 isPressed, sdlKeycode;
};

#define MAXCOMMAND 30

//now lets define a command

#define PLC_KEYMOD_MUST_BE_HELD    ( 1 << 0 )
#define PLC_KEYMOD_DETECT_AS_4WAY  ( 1 << 1 )
#define PLC_KEYMOD_BAN_OTHER_INPUT ( 1 << 2 )
#define PLC_KEYMOD_ON_RELEASE      ( 1 << 3 )
#define PLC_KEYCODE(x)             ( 1 << x )
#define IsKeyInPLCKeyCode( k, c )  ((( PLC_KEYCODE( k ) & c ) > 0 )

#define PLC_ALL_DIRECTIONS_BITFIELD ( PLC_KEYCODE( KEY_UP ) + PLC_KEYCODE( KEY_DOWN ) + PLC_KEYCODE( KEY_LEFT ) + PLC_KEYCODE( KEY_RIGHT ) )

struct PLCOMMANDELEMENT
{
    PLCOMMANDELEMENT() { keyCode = 0; keyModifier = 0; gameTicksForHold = 0; }
    int keyCode;
    Uint16 keyModifier;
    Uint16 gameTicksForHold;
};

struct PLCOMMANDFRAMEINPUT
{
    PLCOMMANDFRAMEINPUT()  { keyBitfield = gameTicks = 0; }
    Uint16 keyBitfield;
    Uint32 gameTicks;
};

struct PLCOMMAND
{
    PLCOMMANDELEMENT nCommand[MAXCOMMAND];
    Uint8 nHowManyCommand;
    Uint8 nCommandTime, nBufferTime;
    char strCommand[255];

};


//Movedata Struct for Saving the current Button States
struct KEYBOARDDATA
{
    KEYELEMENT keyInfo[ KEY_COUNT ];
    bool bKeyBoard;
};


//memlist for Allocater class
struct MEMLIST
{
   u8    nType;
   size_t   nSize;
   void *adrress;    
       
};

//font struct
struct MUGENFONT
{
    u8 c;
    s16 x;
    u8 nWidth;

};

struct PCXHEADER
{
	u8 Manufacturer;
	u8 Version;
	u8 Encoding;
	u8 BPP;
	u16 x,y;
	u16 widht,height;
	u16 HRES,VRES;
	u8 ColorMap[48];
	u8 reserved;
	u8 NPlanes;
	u8 bytesPerLine;
	u8 palletInfo;
	u8 Filler[58];

};
struct SFFHEADER
{
	u8 signature[11];
	u8 verhi;
	u8 verlo;
	u8 verhi2;
	u8 verlo2;
	u32		  NumberOfGroups;
	u32		  NumberOfImage;
	u32		  SubHeaderFileOffset;
	u32		  SizeOfSubheader;
	u8 PaletteType;
	u8 BLANK[476];

};

//Sff Subheader
struct SFFSUBHEADER
{
	u32 NextSubheaderFileOffset;
	u32 LenghtOfSubheader;
	s16 x;
	s16 y;
	s16 GroubNumber;
	s16 ImageNumber;
	s16 IndexOfPrevious;
	bool  PalletSame;
	u8 BALNK[13];

};

//Sound  header
struct SNDHEADER
{
	u8 strSignatur[12];
	s16 verhi;
	s16 verlo;
	u32 nNumberOfSounds;
	u32 SubHeaderFileOffset;
	u8 strBlank[488];

};

//Sound SubHeader
struct SNDSUBHEADER
{
	u32  NextSubHeaderFileOffset;
	u32  SubFileLenght;
	s32  nGroupNumber;
	s32  SampleNumber;

};

struct RGBColor
{
   u8 R;
   u8 G;
   u8 B;
       
};

struct PalFX
{
  u8 dummy;
       
};

struct SFFSPRITE
{
	s16 x;
	s16 y;
	PCXHEADER PcxHeader;
	s16 GroupNumber;
	s16 ImageNumber;
	u16 ColorPallet[256];
	      
	u8 *byPcxFile;

};

struct Stacktype
{
    float Value;
    char string[50]; 

};

enum OPCODES
{
    OP_PUSH=0,
    OP_POP,
    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_DIV,
    OP_EQUAL,
    OP_NOTEQUAL,
    OP_LESS,
    OP_GREATER,
    OP_LESSEQUAL,
    OP_GRAETEREQUAL,
    OP_INTERVALOP1,
    OP_INTERVALOP2,
    OP_INTERVALOP3,
    OP_INTERVALOP4,
    OP_INTERVALOP5,
    OP_INTERVALOP6,
    OP_INTERVALOP7,
    OP_INTERVALOP8,
    OP_LOGNOT,
    OP_LOGAND,
    OP_LOGOR,
    OP_LOGXOR,
    OP_NOT,
    OP_AND,
    OP_OR,
    OP_XOR,
    OP_SQUARE,
    OP_NEG,
    OP_Abs,
    OP_Acos,
  OP_Alive,
  OP_Anim,
  OP_AnimElem,
  OP_AnimElemNo,
  OP_AnimElemTime,
  OP_AnimExist,
  OP_AnimTime,
  OP_Asin,
  OP_Atan,
  OP_AuthorName,
  OP_BackEdgeBodyDist,
  OP_BackEdgeDist,
  OP_CanRecover,
  OP_Ceil,
  OP_Command,
  OP_Const,
  OP_Cos,
  OP_Ctrl,
  OP_DrawGame,
  OP_E,
  OP_Exp,
  OP_Facing,
  OP_Floor,
  OP_FrontEdgeBodyDist,
  OP_FrontEdgeDist,
  OP_FVar,
  OP_GameTime,
  OP_GetHitVar,
  OP_HitCount,
  OP_HitDefAttr,
  OP_HitFall,
  OP_HitOver,
  OP_HitPauseTime,
  OP_HitShakeOver,
  OP_HitVel,
  OP_ID,
  OP_IfElse,
  OP_InGuardDist,
  OP_IsHelper,
  OP_IsHomeTeam,
  OP_Life,
  OP_LifeMax,
  OP_Log,
  OP_Ln,
  OP_Lose,
  OP_MatchNo,
  OP_MatchOver,
  OP_MoveContact,
  OP_MoveGuarded,
  OP_MoveHit,
  OP_MoveType,
  OP_MoveReversed,
  OP_Name,
  OP_NumEnemy,
  OP_NumExplod,
  OP_NumHelper,
  OP_NumPartner,
  OP_NumProj,
  OP_NumProjID,
  OP_NumTarget,
  OP_P1Name,
  OP_P2BodyDist,
  OP_P2Dist,
  OP_P2Life,
  OP_P2MoveType,
  OP_P2Name,
  OP_P2StateNo,
  OP_P2StateType,
  OP_P3Name,
  OP_P4Name,
  OP_PalNo,
  OP_ParentDist,
  OP_Pi,
  OP_Pos,
  OP_Power,
  OP_PowerMax,
  OP_PlayerIDExist,
  OP_PrevStateNo,
  OP_ProjCancelTime,
  OP_ProjContact,
  OP_ProjContactTime,
  OP_ProjGuarded,
  OP_ProjGuardedTime,
  OP_ProjHit,
  OP_ProjHitTime,
  OP_Random,
  OP_RootDist,
  OP_RoundNo,
  OP_RoundsExisted,
  OP_RoundState,
  OP_ScreenPos,
  OP_SelfAnimExist,
  OP_Sin,
  OP_StateNo,
  OP_StateType,
  OP_SysFVar,
  OP_SysVar,
  OP_Tan,
  OP_TeamMode,
  OP_TeamSide,
  OP_TicksPerSecond,
  OP_Time,
  OP_TimeMod,
  OP_UniqHitCount,
  OP_Var,
  OP_Vel,
  OP_Win,
  OP_MOD,
  OP_NOP,
  OP_STOP,
   
};

struct XYVALUE
{
   float x;
   float y;          
};

enum PARAMVALUES
{
    PA_VALUE=128,
    PA_XVALUE,
    PA_YVALUE,
    PA_VAR,
    PA_FVAR,
    PA_SYSVAR,
    PA_SYSFVAR,


};

const int INSPERTRIGGER = 40;
const int NUMTRIGGER = 20;
const int PARAMS = 10;
const int T_TRIGGERALL = 192;
const int NOPARAM = -333;

struct INSTRUCTION
{   
    Uint16 n_OpCode;
    float Value;
    char *strValue;

};

struct PLTRIGGER
{
    u8 nTriggerType;
    INSTRUCTION* pInts;

};

struct CONTROLLERPARAMS
{
    int nParam;
    INSTRUCTION pInts[INSPERTRIGGER];
};



struct PLSTATE
{
	s32 nStateNumber;
	u16 nType;
	PLTRIGGER *triggers;
	u16 nHowManyTriggers;
	bool bPresist;
	bool bIgnorPause;
	void *controller;

};

//StateTypes
enum Types
{
     stand=0,
     crouch,
     air,
     liedown,
     attack,
     idle,
     hit,
     none,
     untouch
};




struct PLSTATEDEF
{
	//recommend parameters
	s32 StateNumber;
	u8 type;
	u8 movetype;
	u8 physics;
	s32 nAnim;
	//optional param
	XYVALUE Velset;
	s8 bCtrl;
	s16 nPoweradd;
	s16 nJuggle;
	bool bFacep2;
	///Some  flags
    bool bHitdefpersist;
	bool bMovehitpersist;
	bool bHitcountpersist;
	//////////////////////
	u8 nSprpriority;
	u16 nHowManyState;
	
	PLSTATE* lpState;
	
	

};

//FlipFlags for air manager
enum
{
    HFLIPFLAG=1,
    VFLIPFLAG=2,
    HVFLIPFLAG=3
    
};

struct ClsnRECT
{
    s16 x,y;
    s16 h,w;

};
//Clsn Struct to hold one Clns Rectangle with type
struct Clsn
{
	bool bClsn1;
	ClsnRECT ClsnRect;

};
//Element Strcut to save one Elment of an Action Block
struct Element
{
	s16 nGroupNumber;
	s16 nImageNumber;
	s16 x;
	s16 y;
	u32 nDuringTime;
	u16 FlipFlags;
	u32 ColorFlags;
	Clsn *pClnsData;
	u16 nNumberOfClsn;
};

//Action Element to hold one Action Block with its Elements
struct ActionElement
{
	s32 nActionNumber;
	Element* AnimationElement;
	s16 loopStart;
	u16 nNumberOfElements;
	u16 nCurrentImage;
	
    u32 nDuringTime;
	s16 nCompletAnimTime;
	u32 nCurrTime;
	u16 nCurrentImageTime;
	bool bLooped;


};

//Player Data
struct PLDATA
{
	s16 nLife;
	s16 nAttack;
	s16 nDefence;
	s16 nFallDefenceUp;
	s16 nLieDownTime;
	s16 nAirjuggle;
	s16 nSparkno;
	s16 nGuardSparkno;
	bool bKoEcho;
	s16 nVolumen;
	u8 nIntPersistIndex;
	u8 nFloatPersistIndex;

};
//Player Size
struct PLAYERSIZE
{
	float nXscale;
	float nYscale;
	s16 nGroundBack;
	s16 nGroundFront;
	s16 nAirBack;
	s16 nAirFront;
	s16 nHeight;
	XYVALUE nAttackWidth;
	s16 nAttackDistance;
	s16 nProjAttackDist;
	bool bProjDoScale;
	XYVALUE nHeadPos;
	XYVALUE nMidPos;
	s16 nShadowOffset;
	XYVALUE nDrawOffset;

};
//Playervelocity struct
struct PLAYERVELOCITY
{
	float nWalkFwd;
	float nWalkBack;
	XYVALUE RunFwd;
	XYVALUE RunBack;
	XYVALUE JumpNeu;
	XYVALUE JumpBack;
	XYVALUE JumpFwd;
	XYVALUE RunjumpBack;
	XYVALUE RunjumpFwd;
	XYVALUE AirjumpNeu;
	XYVALUE AirjumpBack;
	XYVALUE AirjumpFwd;

};
//Playermovement Struct
struct PLAYERMOVEMENT
{
	s16 AirJumpNum;
	s16 nAirJumpHight;
	float yaccel;
	float StandFriction;
	float CrouchFriction;

};
//Playerconstant struct
struct PLAYERCONST
{
	PLDATA			PlayerData;
	PLAYERSIZE		PlayerSize;
	PLAYERVELOCITY	PlayerVelocity;
	PLAYERMOVEMENT	PlayerMovement;


};

struct CHANGESTATE
{
  INSTRUCTION *value;
  INSTRUCTION *ctrl;
  INSTRUCTION *anim;
       
};



class CError
{
char strMessage[100];      
public:
  CError(const char* strError,...)
  {

  char string[100];                  // Temporary string

  va_list ap;                // Pointer To List Of Arguments
  va_start(ap, strError);         // Parses The String For Variables
  vsprintf(string, strError, ap); // Converts Symbols To Actual Numbers
  va_end(ap);      

  strcpy(strMessage,string);

              }
  const char *GetError(){return strMessage;}     
};



#endif
