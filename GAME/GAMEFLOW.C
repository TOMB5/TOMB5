#include "GAMEFLOW.H"

#if !PC_VERSION
#include "3D_GEN.H"
#endif
#include "CODEWAD.H"
#include "CONTROL.H"
#include "DELTAPAK.H"
#include "DRAW.H"

#include "FILE.H"
#if !PC_VERSION
#include "CD.H"
#include "MOVIE.H"
#include "MEMCARD.H"
#include "SPUSOUND.H"
#include "MISC.H"
#include "SFX.H"
#include "GPU.H"
#include "DRAWPHAS.H"
#include "ROOMLOAD.H"
#else
#include "GAME.H"
#include "INIT.H"
#endif

#include "HEALTH.H"
#include "ITEMS.H"
#include "MALLOC.H"
#include "NEWINV2.H"
#include INPUT_H

#include "SAVEGAME.H"
#include "SOUND.H"

#include "SPECIFIC.H"
#include "SPOTCAM.H"
#include "TOMB4FX.H"

#include <assert.h>
#if PSXPC_VERSION
	#include <stdint.h>
#endif

#if PSX_VERSION
typedef unsigned int uintptr_t;
#endif

#include <string.h>
#include "LOT.H"

#define GF_SCRIPT_FILENAME "SCRIPT.DAT"

unsigned char gfGameMode = 1;
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
unsigned char gfInitialiseGame = 1;
long nframes = 1;
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
struct PHD_VECTOR gfLensFlare;
struct CVECTOR gfLensFlareColour;
unsigned char gfMirrorRoom;
unsigned char gfMips[8];
char title_controls_locked_out;
long gfScriptLen = 0;
unsigned char gfLegend;
unsigned char gfWadNames[40];
static unsigned short* gfScriptOffset;
static unsigned char* gfScriptWad;
static char* gfExtensions;
static int gfStatus;
static unsigned long OldSP;
unsigned char gfPickups[16];
unsigned char gfTakeaways[16];
#if PC_VERSION
char* gfScriptFile;
#endif

void DoGameflow()//10F5C(<), 10FD8(<)
{
	//unsigned char* gf;
	//unsigned char n;
	int op;
	unsigned short* scriptOffsetPtr;
	unsigned char* sequenceCommand;

#if PSXENGINE
	LoadGameflow();
#endif

#if DISC_VERSION && PSX_VERSION
	S_PlayFMV(FMV_COPYRIGHT_INTRO, 0);
	S_PlayFMV(FMV_GAME_INTRO, 0);
#endif

#if PC_VERSION
	//do_boot_screen(Gameflow->Language);
	// todo
#endif

	num_fmvs = 0;
	fmv_to_play[0] = 0;
	fmv_to_play[1] = 0;

	//The game's title is disabled in Gameflow script. Automatically override the level id to 1 (skip it).
	gfCurrentLevel = Gameflow->TitleEnabled ? LVL5_TITLE : LVL5_STREETS_OF_ROME;

	//Current level's script offset
	scriptOffsetPtr = gfScriptOffset + (gfCurrentLevel & 0xFF);
	sequenceCommand = gfScriptWad + *scriptOffsetPtr;

	while (1)//?
	{
		op = *sequenceCommand;
		sequenceCommand++;
		switch (op)
		{
		case GF_TITLE_LEVEL://IB = 113D8, 11488
			gfLevelFlags = (sequenceCommand[0] | (sequenceCommand[1] << 8));
			DoTitle(sequenceCommand[2], sequenceCommand[3]);//a3[2]unconfirmed
			break;
		case GF_LEVEL_DATA_END://11048
			break;
		case GF_RESIDENTCUT1://112B8
			gfResidentCut[0] = *sequenceCommand++;
			break;
		case GF_RESIDENTCUT2://112CC
			gfResidentCut[1] = *sequenceCommand++;
			break;
		case GF_RESIDENTCUT3:
			gfResidentCut[2] = *sequenceCommand++;
			break;
		case GF_RESIDENTCUT4://112F4
			gfResidentCut[3] = *sequenceCommand++;
			break;
		case GF_LAYER1://1107C
		{
			int a2 = 10;//?
			int a1 = 10;//?

			LightningRGB[0] = *sequenceCommand;
			LightningRGBs[0] = *sequenceCommand;
			gfLayer2Col.r = *sequenceCommand++;

#if BETA_VERSION
			GameTimer = 46;
#else
			GameTimer = 44;
#endif
			LightningRGB[1] = *sequenceCommand;
			LightningRGBs[1] = *sequenceCommand;
			gfLayer2Col.g = *sequenceCommand++;

			GlobalRoomNumber = *sequenceCommand;
			//GLOBAL_gunflash_meshptr = *sequenceCommand;
			gfLayer1Col.cd = *sequenceCommand++;
			gfLayer1Vel = *sequenceCommand++;
			break;
		}
		case GF_FOG:
			gfUVRotate = *sequenceCommand++;
			break;
		case GF_LEGEND:
			gfLegend = *sequenceCommand++;
			if (gfGameMode != 4)
				gfLegendTime = 150;
			break;
		case GF_ANIMATING_MIP:
			gfMips[gfNumMips++] = *sequenceCommand++;
			break;
		case GF_GIVE_ITEM_AT_STARTUP:
			gfPickups[gfNumPickups++] = sequenceCommand[0] | (sequenceCommand[1] << 8);
			sequenceCommand += 2;
			break;
		case GF_LOSE_ITEM_AT_STARTUP:
			gfTakeaways[gfNumTakeaways++] = sequenceCommand[0] | (sequenceCommand[1] << 8);
			sequenceCommand += 2;
			break;
		case GF_MIRROR:
			gfMirrorRoom = *sequenceCommand++;
			gfMirrorZPlane = *(int*)sequenceCommand;
			sequenceCommand += 4;
			break;
		case GF_CUT:
			gfCutNumber = *sequenceCommand++;
			break;
		case GF_RESET_HUB:
			gfResetHubDest = *sequenceCommand++;
			break;
		case GF_FMV:
			fmv_to_play[num_fmvs++] = *sequenceCommand++;
			break;
		default://11550
			assert(1);
			break;
		}
	}
}

void LoadGameflow()//102E0, 102B0
{
	char* s = NULL;
	int len = 0;
	int j = 0;
	int i = 0;
	struct STRINGHEADER sh;

	int num_strings, wad_len;

	unsigned char* sequenceCommand;
	int endOfSequence;
	unsigned char op;

#if PSX_VERSION || PSXPC_VERSION
	len = FILE_Length(GF_SCRIPT_FILENAME);
	s = game_malloc(len);
	FILE_Load(GF_SCRIPT_FILENAME, s);
#endif

#if PC_VERSION
	LoadFile(GF_SCRIPT_FILENAME, (void**)&s);
	gfScriptFile = s;
#endif

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

#if !PC_VERSION
	gfScriptLen = len;
#endif
	gfScriptWad = (unsigned char*)s;
	s += Gameflow->ScriptLen;

	//Align
	gfStringOffset = (unsigned short*)(char*)((uintptr_t)(s + 3) & (uintptr_t)-4);

#if CORE_UNSAFE
	//This is original code, unsafe (if no lang loc files exist on disk)
	while (FILE_Length(s) == -1)
	{
		//Null terminated
		s += strlen(s) + 1;
		i++;
	}
#else
	//Safer code (no inf loop).
	for (i = 0; i < NUM_GF_LANGUAGES; i++)
	{
#if PC_VERSION
		gfStringOffset = NULL;
		if (LoadFile((char*)s, (void**)&gfStringOffset))
#else
		if (FILE_Length((char*)s) != -1)
#endif
		{
			break;
		}

		//Null terminated
		s += strlen((char*)s) + 1;
	}
#endif

	Gameflow->Language = i;

#if !PC_VERSION
	FILE_Load((char*)s, gfStringOffset);
#endif

	memcpy(&sh, gfStringOffset, sizeof(struct STRINGHEADER));

#if PC_VERSION
	num_strings = sh.nStrings + sh.nPSXStrings + sh.nPCStrings;
	wad_len = sh.StringWadLen + sh.PSXStringWadLen + sh.PCStringWadLen;
#else
	num_strings = sh.nStrings + sh.nPSXStrings;
	wad_len = sh.StringWadLen + sh.PSXStringWadLen;
#endif

	memcpy(gfStringOffset, gfStringOffset + (sizeof(struct STRINGHEADER) / sizeof(unsigned short)), num_strings * sizeof(unsigned short));

	gfStringWad = (char*)(gfStringOffset + num_strings);

	memcpy(gfStringWad, gfStringOffset + NUM_STRING_ENTRIES + (sizeof(struct STRINGHEADER) / sizeof(unsigned short)), wad_len);

	gfScriptLen += (((num_strings * sizeof(unsigned short) + wad_len) + 3) & -4);

	if (num_strings != 0)
	{
		unsigned char* stringPtr = (unsigned char*)gfStringWad;//s?

		for (i = 0; i < num_strings; i++)
		{
			int next = i + 1 == num_strings ? wad_len : gfStringOffset[i + 1];
			int stringLength = (next - gfStringOffset[i]) - 1;
			if (stringLength > 0)
			{
				for (j = 0; j < stringLength; j++)
				{
					stringPtr[j] ^= 0xA5;
				}
			}

			stringPtr += stringLength + 1;
		}
	}

	if (Gameflow->nLevels != 0)
	{
		sequenceCommand = gfScriptWad;
		for (i = 0; i < Gameflow->nLevels; i++)
		{
			endOfSequence = 0;

			while (!endOfSequence)
			{
				op = *sequenceCommand;
				sequenceCommand++;

				switch (op)
				{
				case GF_LEVEL:
					gfLevelNames[i] = *sequenceCommand;
					sequenceCommand += 5;
					break;

				case GF_TITLE_LEVEL:

				case GF_LAYER1:
				case GF_LAYER2:
					sequenceCommand += 4;
					break;

				case GF_LEVEL_DATA_END:
					endOfSequence = 1;
					break;

				case GF_FMV:
				case GF_CUT:

				case GF_RESIDENTCUT1:
				case GF_RESIDENTCUT2:
				case GF_RESIDENTCUT3:
				case GF_RESIDENTCUT4:

				case GF_UV_ROTATE:
				case GF_LEGEND:
				case GF_ANIMATING_MIP:
				case GF_RESET_HUB:
					sequenceCommand += 1;
					break;
				case GF_LENS_FLARE:
					sequenceCommand += 9;
					break;
				case GF_MIRROR:
					sequenceCommand += 5;
					break;
				case GF_FOG:
					sequenceCommand += 3;
					break;

				case GF_KEY_ITEM1:
				case GF_KEY_ITEM2:
				case GF_KEY_ITEM3:
				case GF_KEY_ITEM4:
				case GF_KEY_ITEM5:
				case GF_KEY_ITEM6:
				case GF_KEY_ITEM7:
				case GF_KEY_ITEM8:
				case GF_KEY_ITEM9:
				case GF_KEY_ITEM10:
				case GF_KEY_ITEM11:
				case GF_KEY_ITEM12:

				case GF_PUZZLE_ITEM1:
				case GF_PUZZLE_ITEM2:
				case GF_PUZZLE_ITEM3:
				case GF_PUZZLE_ITEM4:
				case GF_PUZZLE_ITEM5:
				case GF_PUZZLE_ITEM6:
				case GF_PUZZLE_ITEM7:
				case GF_PUZZLE_ITEM8:
				case GF_PUZZLE_ITEM9:
				case GF_PUZZLE_ITEM10:
				case GF_PUZZLE_ITEM11:
				case GF_PUZZLE_ITEM12:

				case GF_PICKUP_ITEM1:
				case GF_PICKUP_ITEM2:
				case GF_PICKUP_ITEM3:
				case GF_PICKUP_ITEM4:
				case GF_EXAMINE1:
				case GF_EXAMINE2:
				case GF_EXAMINE3:

				case GF_KEY_ITEM1_COMBO1:
				case GF_KEY_ITEM1_COMBO2:
				case GF_KEY_ITEM2_COMBO1:
				case GF_KEY_ITEM2_COMBO2:
				case GF_KEY_ITEM3_COMBO1:
				case GF_KEY_ITEM3_COMBO2:
				case GF_KEY_ITEM4_COMBO1:
				case GF_KEY_ITEM4_COMBO2:
				case GF_KEY_ITEM5_COMBO1:
				case GF_KEY_ITEM5_COMBO2:
				case GF_KEY_ITEM6_COMBO1:
				case GF_KEY_ITEM6_COMBO2:
				case GF_KEY_ITEM7_COMBO1:
				case GF_KEY_ITEM7_COMBO2:
				case GF_KEY_ITEM8_COMBO1:
				case GF_KEY_ITEM8_COMBO2:

				case GF_PUZZLE_ITEM1_COMBO1:
				case GF_PUZZLE_ITEM1_COMBO2:
				case GF_PUZZLE_ITEM2_COMBO1:
				case GF_PUZZLE_ITEM2_COMBO2:
				case GF_PUZZLE_ITEM3_COMBO1:
				case GF_PUZZLE_ITEM3_COMBO2:
				case GF_PUZZLE_ITEM4_COMBO1:
				case GF_PUZZLE_ITEM4_COMBO2:
				case GF_PUZZLE_ITEM5_COMBO1:
				case GF_PUZZLE_ITEM5_COMBO2:
				case GF_PUZZLE_ITEM6_COMBO1:
				case GF_PUZZLE_ITEM6_COMBO2:
				case GF_PUZZLE_ITEM7_COMBO1:
				case GF_PUZZLE_ITEM7_COMBO2:
				case GF_PUZZLE_ITEM8_COMBO1:
				case GF_PUZZLE_ITEM8_COMBO2:

				case GF_PICKUP_ITEM1_COMBO1:
				case GF_PICKUP_ITEM1_COMBO2:
				case GF_PICKUP_ITEM2_COMBO1:
				case GF_PICKUP_ITEM2_COMBO2:
				case GF_PICKUP_ITEM3_COMBO1:
				case GF_PICKUP_ITEM3_COMBO2:
				case GF_PICKUP_ITEM4_COMBO1:
				case GF_PICKUP_ITEM4_COMBO2:

				case GF_GIVE_ITEM_AT_STARTUP:
				case GF_LOSE_ITEM_AT_STARTUP:
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

void QuickControlPhase()//10274(<), 10264(<) (F)
{
#if PSX_VERSION
#if DEBUG_VERSION
	ProfileRGB(255, 255, 255);
#endif
	OldSP = SetSp(0x1F8003E0);
#endif

	gfStatus = ControlPhase(nframes, (gfGameMode ^ 2) < 1 ? 1 : 0);

#if PSX_VERSION
	SetSp(OldSP);
#if DEBUG_VERSION
	ProfileRGB(0, 0, 0);
#endif
#endif
}

void DoTitle(unsigned char Name, unsigned char Audio)//10604(<), 105C4(<)
{
	int i;

	CreditsDone = 0;
	CanLoad = 0;

#if !PC_VERSION
	if (Gameflow->LoadSaveEnabled)
	{
		mcOpen(1);
	}
#endif

	//loc_10648
	num_fmvs = 0;
	fmv_to_play[1] = 0;
	fmv_to_play[0] = 0;

#if PSX_VERSION || PSXPC_VERSION
	XAMasterVolume = savegame.VolumeCD;
#endif

	memset(&savegame.Level, 0, sizeof(struct STATS));
	memset(&savegame.Game, 0, sizeof(struct STATS));

	S_LoadLevelFile(Name);

	GLOBAL_lastinvitem = -1;
	dels_cutseq_player = 0;

	InitSpotCamSequences();

	title_controls_locked_out = 0;

#if PC_VERSION
	InitialiseFXArray(1);
	InitialiseLOTarray(1);
#endif

	InitialisePickUpDisplay();

#if PSX_VERSION || PSXPC_VERSION
	phd_InitWindow(90);
#endif

	SOUND_Stop();

	IsAtmospherePlaying = 0;

	S_SetReverbType(1);

	InitialiseCamera();

	if (bDoCredits)
	{
		cutseq_num = 28;
		SetFadeClip(32, 1);
		ScreenFadedOut = 1;
		ScreenFade = 255;
		dScreenFade = 255;
	}
	else
	{
		trigger_title_spotcam(1);

		ScreenFadedOut = 0;
		ScreenFade = 0;
		dScreenFade = 0;
		ScreenFadeBack = 0;
		ScreenFadeSpeed = 8;
		ScreenFading = 0;

#if BETA_VERSION
		S_CDPlay(CDA_XA14_ECREDITS, 1);
#endif
	}

	//loc_10764, loc_10730
	bUseSpotCam = 1;
	lara_item->mesh_bits = 0;
	gfGameMode = 1;

#if 1//INTERNAL
	show_game_malloc_totals();
#endif

	gfLevelComplete = 0;
	nframes = 2;
	gfStatus = ControlPhase(2, 0);

	JustLoaded = 0;
	
#if !PC_VERSION
	if (gfStatus == 0)
	{
		//loc_107BC, 10778
		while (gfStatus == 0)
		{
			GPU_BeginScene();

			if (bDoCredits)
			{
				if (sub_1BE988() == 0)
				{
					bDoCredits = 0;
					SetFadeClip(0, 2);

					if (bDoCredits != 0)
					{
						goto lbl_10890;
					}
				}
			}

			//FIXME branching is seriously mangled here
			//loc_10810
			if (GLOBAL_playing_cutseq != 0)//todo merge case with below then else the rest to sim jump
			{
				goto lbl_108A4;
			}

			if (ScreenFading != 0 || cutseq_num != 0)
			{
				goto lbl_10890;
			}

#if DEBUG_VERSION
			if (RawPad & 0x201)
			{
				dels_cutseq_selector_flag = 1;
			}
#endif
			//loc_10868
			CreditsDone = 1;
			gfStatus = sub_1BDF88(Name);//TitleOptions(void);

		lbl_10890:
			if (GLOBAL_playing_cutseq != 0)
			{
			lbl_108A4:
				if (!bDoCredits || CreditsDone != 0)
				{
#if BETA_VERSION
					PrintString(256, 220, 1, &gfStringWad[gfStringOffset[176]], 0);
#else
					PrintString(256, 220, 1, &gfStringWad[gfStringOffset[174]], 0);
#endif
				}

			}

			//loc_108EC
			nframes = DrawPhaseGame();

#if PSX_VERSION || PSXPC_VERSION
			if (PadConnected == 0)
			{
#if BETA_VERSION
				PrintString(256, 128, 3, &gfStringWad[gfStringOffset[221]], 0);
#else
				PrintString(256, 128, 3, &gfStringWad[gfStringOffset[219]], 0);
#endif
			}
#endif

			//loc_1092C
			handle_cutseq_triggering(Name);

			if (gfGameMode == 2)
			{
#if PSX_VERSION || PSXPC_VERSION
				if (!(dbinput & 0x100) || GLOBAL_enterinventory != -1)
				{
					if (cutseq_trig == 0 && lara_item->hit_points > 0)
					{
						S_CallInventory2();
					}
				}
#endif
			}
			
			//loc_109A8
			QuickControlPhase();

			if (gfGameMode == 2 && ScreenFadedOut != 0)
			{
				InitialiseItemArray(256);

				if (number_rooms > 0)
				{
					for (i = 0; i < number_rooms; i++)
					{
						room[i].flags = -1;
					}
				}

				gfGameMode = 1;

			}//loc_10A14
		}
	}
	
	//loc_10A24
#if PSX_VERSION || PSXPC_VERSION

	Motors[0] = 0;
	Motors[1] = 0;

	if (Gameflow->LoadSaveEnabled)
	{
		mcClose();
	}
	
	//loc_10A58
	while (XAVolume != 0)
	{
		XAReqVolume = 0;
	}
#endif

	NoInput = 0;
	S_SoundStopAllSamples();
	S_CDStop();
	bUseSpotCam = 0;
	bDisableLaraControl = 0;
	input = 0;
#endif
}

void DoLevel(unsigned char Name, unsigned char Audio)//10ABC(<) 10A84(<) (F)
{
	char *d;

#if !BETA_VERSION
	int fmvStatus;
#endif
#if PSX_VERSION || PSXPC_VERSION
	if (gfGameMode == 4)
	{
		if (FromTitle == 1)
		{
			d = (char*) &GadwPolygonBuffers[49188];
			memcpy((void*) d, &MGSaveGamePtr[0], 8192);
			MGSaveGamePtr = d;
		}
	}

	//loc_10B24
	FromTitle = 0;


	XAMasterVolume = savegame.VolumeCD;
#endif

	if (gfGameMode == 4)
	{
		memset(&savegame.Level, 0, sizeof(struct STATS));
	}

	//loc_10B58
	S_LoadLevelFile(Name);

	InitSpotCamSequences();
	InitialisePickUpDisplay();
#if PSX_VERSION || PSXPC_VERSION
	phd_InitWindow(90);
#endif
	SOUND_Stop();
	bDisableLaraControl = 0;

	if (gfGameMode == 4)
	{
		sgRestoreGame();
		gfRequiredStartPos = 0;
		gfInitialiseGame = 0;
	}
	else
	{
		//loc_10BAC
		gfRequiredStartPos = 0;

		if (gfInitialiseGame != 0)
		{
			GameTimer = 0;
			gfRequiredStartPos = 0;
			gfInitialiseGame = 0;
			FmvSceneTriggered = 0;
			InitCutPlayed();
		}

		//loc_10BD8
		CurrentAtmosphere = 0;
		flipeffect = 0;

		if (gfCurrentLevel == LVL5_STREETS_OF_ROME)
		{
			((char*) &LaserSight)[2] = 0;
		}
	}

	//loc_10BF8
	S_CDPlay(CurrentAtmosphere, 1);

	IsAtmospherePlaying = 1;
	ScreenFadedOut = 0;
	ScreenFading = 0;
	ScreenFadeBack = 0;
	dScreenFade = 255;
	ScreenFade = 255;

	if (dels_cutseq_player != 0)
	{
		gfCutNumber = 0;
	}//loc_10C50

	if (gfCutNumber == 0 || CheckCutPlayed(gfCutNumber) != 0 && dels_cutseq_player == 0)
	{
		//loc_10CC4
		cutseq_num = 0;
		gfCutNumber = 0;
		SetScreenFadeIn(16);
	}
	else
	{
		//loc_10C90
		gfCutNumber = 0;
		ScreenFadedOut = 1;
		cutseq_num = gfCutNumber;
	}

	//loc_10CD8
	InitialiseCamera();
	bUseSpotCam = 0;

#if DEBUG_VERSION
	show_game_malloc_totals();
#endif

	gfGameMode = 0;
	gfLevelComplete = 0;
	nframes = 2;
	framecount = 0;

	gfStatus = ControlPhase(2, 0);
#if PSX_VERSION || PSXPC_VERSION
	dbinput = 0;
	JustLoaded = 0;

	if (gfStatus == 0)
	{
		//loc_10D30
		while (gfStatus == 0)
		{

			GPU_BeginScene();

			if (gfLegendTime != 0 && DestFadeScreenHeight == 0 && FadeScreenHeight == 0 && cutseq_num == 0)
			{
				PrintString(0x100, 0xE8, 2, &gfStringWad[gfStringOffset[gfLegend]], 0x8000);
				gfLegendTime--;
			}

			//loc_10DC4
			nframes = DrawPhaseGame();
			handle_cutseq_triggering(Name);

			if (DEL_playingamefmv != 0)
			{
				DEL_playingamefmv = 0;
			}

			//loc_10DEC
			if (gfLevelComplete == 0)
			{
				if (dbinput & 0x100 && GLOBAL_enterinventory != -1)
				{
					//loc_10E28
					if (cutseq_trig == 0 && lara_item->hit_points > 0 && ScreenFading == 0)
					{
						if (S_CallInventory2() != 0)
						{
							//loc_10CB8
							gfStatus = 2;
						}
					}
				}

				//loc_10E7C
				QuickControlPhase();
			}
			else
			{
				//loc_10CAC
				gfStatus = 3;
				break;
			}
		}
	}

	//loc_10E94
	XAReqVolume = 0;
	Motors[1] = 0;
	Motors[0] = 0;


	if (XAVolume != 0)
	{
		//loc_10EBC
		do
		{
			XAReqVolume = 0;
		} while (XAVolume == 0);
	}


	//loc_10ED8
	reset_count = 0;
	S_SoundStopAllSamples();
	S_CDStop();
#endif
#if !BETA_VERSION

	if (gfStatus == 3)
	{
		fmvStatus = 0;

		if (fmv_to_play[0] & 0x80)
		{
			if (fmv_to_play[0] & 0x7F == 9 && gfLevelComplete != 10)
			{
				fmv_to_play[0] = 0;
			}
			
			//loc_10EF8
			if (fmv_to_play[0] & 0x7F == 8 && gfLevelComplete != 22)
			{
				fmv_to_play[0] = 0;
			}
		}
#if PSXENGINE	
		//loc_10F20
		if (fmv_to_play[0] != 0)
		{
			fmvStatus = S_PlayFMV(fmv_to_play[0] & 0x7F, 1);
		}//loc_10F3C

		if (fmvStatus != 2 && fmv_to_play[1] != 0)
		{
			S_PlayFMV(fmv_to_play[1] & 0x7F, 1);
		}
#endif
	}

	//loc_10F64
	num_fmvs = 0;
	fmv_to_play[1] = 0;
	fmv_to_play[0] = 0;
#endif

	lara.examine3 = 0;
	lara.examine2 = 0;
	lara.examine1 = 0;

	if (gfStatus == 3 && gfCurrentLevel == LVL5_RED_ALERT)
	{
		gfStatus = 1;
		bDoCredits = 1;
		scroll_pos = 0;
	}

	//loc_10F30
	input = 0;
	reset_flag = 0;
}

void TitleOptions()
{

}