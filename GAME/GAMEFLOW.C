#include "GAMEFLOW.H"

#include "3D_GEN.H"
#include "CAMERA.H"
#include "CONTROL.H"
#include "CD.H"
#include "DRAW.H"
#include "FILE.H"
#include "HEALTH.H"
#include "MALLOC.H"
#include "NEWINV2.H"
#include "ROOMLOAD.H"
#include "SAVEGAME.H"
#include "SOUND.H"
#include "SPOTCAM.H"
#include "TOMB4FX.H"

#include <stdint.h>
#include <string.h>

//Temp
#include "LOAD_LEV.H"
#include <assert.h>

#define GF_SCRIPT_FILENAME "SCRIPT.DAT"

unsigned char gfGameMode;
unsigned char gfNumMips;
int scroll_pos;
char DEL_playingamefmv;
char num_fmvs;
char fmv_to_play[2];
unsigned short dels_cutseq_selector_flag;
unsigned short dels_cutseq_player;
char Chris_Menu;
unsigned char gfLegendTime;
unsigned char bDoCredits;
static unsigned char gfCutNumber;
unsigned char gfInitialiseGame;
long nframes;
unsigned char gfNumPickups;
unsigned char gfNumTakeaways;
char CanLoad;
struct GAMEFLOW* Gameflow;
unsigned short* gfStringOffset;
char* gfStringWad;
unsigned short* gfFilenameOffset;
char* gfFilenameWad;
unsigned char gfCurrentLevel;
unsigned char gfLevelComplete;
unsigned char gfRequiredStartPos;
unsigned short gfLevelFlags;
unsigned char gfLevelNames[40];
unsigned char gfResidentCut[4];
unsigned char gfResetHubDest;
char gfUVRotate;
char gfLayer1Vel;
char gfLayer2Vel;
struct CVECTOR gfLayer1Col;
struct CVECTOR gfLayer2Col;
unsigned long GameTimer;
//
struct PHD_VECTOR gfLensFlare;
struct CVECTOR gfLensFlareColour;
unsigned char gfMirrorRoom;
unsigned char gfMips[8];
char title_controls_locked_out;
long gfScriptLen = 0;
unsigned char gfLegend;
unsigned char gfWadNames[40];
static unsigned short *gfScriptOffset;
static unsigned char *gfScriptWad;
static char* gfExtensions;
static int gfStatus;
static unsigned long OldSP;
unsigned char gfPickups[16];
unsigned char gfTakeaways[16];

void DoGameflow()//10F5C, 10FD8
{
	//unsigned char *gf;
	//unsigned char n;

	LoadGameflow();
#ifdef PSX
	//0 = Eidos Logo FMV
	//1 = TRC Intro FMV
	S_PlayFMV(0);
	S_PlayFMV(1);
#endif

#if 1
	struct GAMEFLOW* v1 = Gameflow;

	num_fmvs = 0;
	fmv_to_play[0] = 0;
	fmv_to_play[1] = 0;

	//? Since when did gf flags store the current level?
	//FIXME!
	int v0 = *(int*)v1;
	v0 >>= 2;
	v0 &= 1;
	v0 = v0 < 1 ? 1 : 0;

	gfCurrentLevel = v0;

	//Current level's script offset
	unsigned short* scriptOffsetPtr = gfScriptOffset + (gfCurrentLevel & 0xFF);
	unsigned char* sequenceCommand = gfScriptWad + *scriptOffsetPtr;

	while (1)//?
	{
		int op = *sequenceCommand - 0x80;
		sequenceCommand++;
		switch (op)
		{
		case 2://IB = 113D8, 11488
			gfLevelFlags = (sequenceCommand[0] | (sequenceCommand[1] << 8));
			DoTitle(sequenceCommand[2], sequenceCommand[3]);//a3[2]unconfirmed
			break;
		case 3://11048
			break;
		case 5://112B8
			gfResidentCut[0] = *sequenceCommand;
			sequenceCommand += 1;
			break;
		case 6://112CC
			gfResidentCut[1] = *sequenceCommand;
			sequenceCommand += 1;
			break;
		case 7:
			gfResidentCut[2] = *sequenceCommand;
			sequenceCommand += 1;
			break;
		case 8://112F4
			gfResidentCut[3] = *sequenceCommand;
			sequenceCommand += 1;
			break;
		case 9://1107C
		{
			int a2 = 10;//?
			int a1 = 10;//?

			LightningRGB[0] = *sequenceCommand;
			LightningRGBs[0] = *sequenceCommand;
			gfLayer2Col.r = *sequenceCommand;
			sequenceCommand += 1;

#ifdef _DEBUG
			//internal beta is 0x2E
			//GameTimer = 0x2E;
#endif
			LightningRGB[1] = *sequenceCommand;//*a3++;?
			LightningRGBs[1] = *sequenceCommand;//*a3++;?
			gfLayer2Col.g = *sequenceCommand;//*a3++;?
			sequenceCommand += 1;

			GameTimer = 44;
			GlobalRoomNumber = *sequenceCommand;
			//			GLOBAL_gunflash_meshptr = *sequenceCommand;
			gfLayer1Col.cd = *sequenceCommand;
			sequenceCommand += 1;

			gfLayer1Vel = *sequenceCommand;
			sequenceCommand += 1;
			break;
		}
		default://11550
			assert(1);
			break;
		}
	}

#endif

}

void LoadGameflow()//102E0, 102B0
{
	int len = FILE_Length(GF_SCRIPT_FILENAME);
	char* s = game_malloc(len);
	FILE_Load(GF_SCRIPT_FILENAME, s);

	Gameflow = (struct GAMEFLOW*)s;
	s += sizeof(struct GAMEFLOW);

	gfExtensions = s;
	s += 0x28;

	gfFilenameOffset = (unsigned short*)s;
	s += Gameflow->nFileNames * sizeof(unsigned short);

	gfFilenameWad = s;
	s += Gameflow->FileNameLen;

	gfScriptOffset = (unsigned short*)s;
	s += Gameflow->nLevels * sizeof(unsigned short);

	gfScriptLen = len;
	gfScriptWad = (unsigned char*)s;
	s += Gameflow->ScriptLen;

	//Align
	gfStringOffset = (unsigned short*)(char*)((uintptr_t)(s + 3) & (uintptr_t)-4);

	int i = 0;

#ifdef CORE_UNSAFE
	//This is original code, unsafe (if no lang loc files exist on disk)
	while (FILE_Length(s) == -1)
	{
		//Null terminated
		s += strlen(s) + 1;
		i++;
	}
#else
	//Safer code (no inf loop).
	for (i = 0; i < MAX_GF_LANGUAGES; i++)
	{
		if (FILE_Length((char*)s) != -1)
		{
			break;
		}

		//Null terminated
		s += strlen((char*)s) + 1;
	}
#endif

	Gameflow->Language = i;

	FILE_Load((char*)s, gfStringOffset);

	struct STRINGHEADER sh;
	memcpy(&sh, gfStringOffset, sizeof(struct STRINGHEADER));
	memcpy(gfStringOffset, gfStringOffset + (sizeof(struct STRINGHEADER) / sizeof(unsigned short)), (sh.nStrings + sh.nPSXStrings) * sizeof(unsigned short));

#ifdef _DEBUG
	//Internal Beta
	//memcpy(gfStringOffset + (sh.nStrings + sh.nPSXStrings), gfStringOffset + 317, sh.StringWadLen + sh.PSXStringWadLen);
	memcpy(gfStringOffset + (sh.nStrings + sh.nPSXStrings), gfStringOffset + 315, sh.StringWadLen + sh.PSXStringWadLen);
#else
	memcpy(gfStringOffset + (sh.nStrings + sh.nPSXStrings), gfStringOffset + 315, sh.StringWadLen + sh.PSXStringWadLen);
#endif

	gfScriptLen += ((((sh.nStrings + sh.nPSXStrings) * sizeof(unsigned short) + (sh.StringWadLen + sh.PSXStringWadLen)) + 3) & -4);

	if (sh.nStrings + sh.nPSXStrings != 0)
	{
		unsigned char* stringPtr = (unsigned char*)(gfStringOffset + sh.nStrings + sh.nPSXStrings);//s?

		for (i = 0; i < sh.nStrings + sh.nPSXStrings; i++)
		{
			int stringLength = (gfStringOffset[i + 1] - gfStringOffset[i]) - 1;
			if (stringLength > 0)
			{
				for (int j = 0; j < stringLength; j++)
				{
					stringPtr[j] ^= 0xA5;
				}
			}

			stringPtr += stringLength + 1;
		}
	}

	if (Gameflow->nLevels != 0)
	{
		unsigned char* sequenceCommand = gfScriptWad;
		for (i = 0; i < Gameflow->nLevels; i++)
		{
			int endOfSequence = 0;

			while (!endOfSequence)
			{
				unsigned char op = *sequenceCommand - 0x80;
				sequenceCommand++;

				switch (op)
				{
				case 0:
					sequenceCommand += 1;
					break;
				case 1:
					gfLevelNames[i] = *sequenceCommand;
					sequenceCommand += 5;
					break;
				case 2:
				case 9:
				case 10:
					sequenceCommand += 4;
					break;
				case 3:
					endOfSequence = 1;
					break;
				case 4:
				case 5:
				case 6:
				case 7:
				case 8:
				case 11:
				case 12:
				case 16:
				case 17:
					sequenceCommand += 1;
					break;
				case 13:
					sequenceCommand += 9;
					break;
				case 14:
					sequenceCommand += 5;
					break;
				case 15:
					sequenceCommand += 3;
					break;
				case 18:
				case 19:
				case 20:
				case 21:
				case 22:
				case 23:
				case 24:
				case 25:
				case 26:
				case 27:
				case 28:
				case 29:
				case 30:
				case 31:
				case 32:
				case 33:
				case 34:
				case 35:
				case 36:
				case 37:
				case 38:
				case 39:
				case 40:
				case 41:
				case 42:
				case 43:
				case 44:
				case 45:
				case 46:
				case 47:
				case 48:
				case 49:
				case 50:
				case 51:
				case 52:
				case 53:
				case 54:
				case 55:
				case 56:
				case 57:
				case 58:
				case 59:
				case 60:
				case 61:
				case 62:
				case 63:
				case 64:
				case 65:
				case 66:
				case 67:
				case 68:
				case 69:
				case 70:
				case 71:
				case 72:
				case 73:
				case 74:
				case 75:
				case 76:
				case 77:
				case 78:
				case 79:
				case 80:
				case 81:
				case 82:
				case 83:
				case 84:
				case 85:
				case 86:
				case 87:
				case 88:
				case 89:
				case 90:
					sequenceCommand += 2;
					break;
				default:
					sequenceCommand += 2;
					break;
				}
			}
		}
	}
}

void QuickControlPhase()
{
}

void DoTitle(unsigned char Name, unsigned char Audio)//10604, 105C4
{

#if 1
	//int i;
	struct GAMEFLOW* v1 = Gameflow;

	int at = 0x000A0000;//?
	CreditsDone = 0;
	CanLoad = 0;

	int v0 = ((*(int*) Gameflow) << 1) & 1;

	//beq 10648
	if (v0 == 0)
	{
		//TODO
	}

	int a0 = 0;//?param?
	int s1 = a0 & 0xFF;

	//a0 = 1;
#ifdef PSX
	mcOpen();
#endif

	struct savegame_info* s0 = &savegame;
	a0 = s0->Level.Timer;

	int a1 = 0;

	num_fmvs = 0;
	fmv_to_play[0] = 0;
	fmv_to_play[1] = 0;

	XAMasterVolume = s0->VolumeCD;

	sizeof(struct STATS);
	memset(&savegame.Level, 0, sizeof(struct STATS));

	a0 = s0->Game.Timer;
	a1 = 0;
	memset(&savegame.Game, 0, sizeof(struct STATS));

	S_LoadLevelFile(s1);//check param

	//move	$a0, $s1
	GLOBAL_lastinvitem = -1;
	dels_cutseq_player = 0;
	InitSpotCamSequences();
	title_controls_locked_out = 0;
	InitialisePickUpDisplay();

	phd_InitWindow(90);
	SOUND_Stop();
	IsAtmospherePlaying = 0;
	///S_SetReverbType();
	a0 = 1;
	InitialiseCamera();
	v0 = bDoCredits;

	//bnez	$v0, loc_10730//bdocredits
	a0 = 0x20;
	///trigger_title_spotcam();
	a0 = 1;
	ScreenFadedOut = 0;
	ScreenFade = 0;
	dScreenFade = 0;
	ScreenFadeBack = 0;
	ScreenFadeSpeed = 8;
	ScreenFading = 0;
	//j	loc_10764

	///Retail 0x001088C - jal sub_645E0 DrawPhaseGame renders screen
#else

	dump_game_malloc();
	assert(0);
#endif
}

void DoLevel(unsigned char Name, unsigned char Audio)
{
}
