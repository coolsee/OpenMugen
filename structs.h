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


struct KEYELEMENT
{
	KEYELEMENT()  { isPressed = false; sdlKeycode = 0; }
	Uint16 isPressed, sdlKeycode;
};


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
	// 扩展字段，用于方向键是否按下，尚待支持
	//char stringEx[50];

};


struct XYVALUE
{
	float x;
	float y;          
};

// 操作堆栈的元素
struct INSTRUCTION
{   
	Uint16 n_OpCode;
	float Value;
	char *strValue;

};
// 触发器，一个触发器就是一个表达式
struct PLTRIGGER
{
	u8 nTriggerType;
	INSTRUCTION* pInts;

};

// 触发器执行需要的值，用表达式保存，
struct CONTROLLERPARAMS
{
	ConParmName nParam;
	//TODO:动态生成内存
	INSTRUCTION pInts[INSPerConParam];
};

// HitDef 保存的值
struct CONTROLHITDEF
{
	CONTROLHITDEFParmName nParam;
	//TODO:动态生成内存
	INSTRUCTION pInts[INSPerConParam];
};

// TODO control中的执行语句只有这三个是表达式，其他的都是数值，为保险还是用CONTROLLERPARAMS统一保存
//struct CHANGESTATE
//{
//	INSTRUCTION *value;
//	INSTRUCTION *ctrl;
//	INSTRUCTION *anim;
//
//};

struct PLSTATE
{
	// control所属的state num
	s32 nStateNumber;
	u16 nType;
	PLTRIGGER *triggers;
	u16 nHowManyTriggers;

	bool bPresist;
	bool bIgnorPause;
	// 暂时无用，存储的control都直接由nType，映射成函数了
	//void *controller;

	// http://elecbyte.com/wiki/index.php/Category:State_Controllers
	// 里面有说明persistent和ignorehitpause是必须的字段，其他非必须，用map映射存储
	//TODO: 定义40参数的列表，可以改为动态产生
	CONTROLLERPARAMS pConParm[ConParmPerState];
	u16 nParamCount;

	// HitDef参数比较多，单独解析
	CONTROLHITDEF pConHDParm[ConHDParmPerState];
	u16 nParamHDCount;
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
	char szPlayerName[10];

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
