#include "GAMEFLOW.H"

#if !PC_VERSION
#include "3D_GEN.H"
#include "TITSEQ.H"
#include "TYPEDEFS.H"
#endif
#include "CDTRACKS.H"
#include "CODEWAD.H"
#include "CONTROL.H"
#include "DELTAPAK.H"
#include "DRAW.H"

#include "FILE.H"
#if PSX_VERSION || PSXPC_VERSION || PSXPC_TEST
#include "CD.H"
#include "MOVIE.H"
#include "MEMCARD.H"
#include "SPUSOUND.H"
#include "MISC.H"
#include "SFX.H"
#include "GPU.H"
#include "DRAWPHAS.H"
#include "ROOMLOAD.H"
#include <LIBAPI.H>
#include <LIBGTE.H>
#elif SAT_VERSION
#include "CD.H"
#include "MOVIE.H"
#include "MEMCARD.H"
#include "SPUSOUND.H"
#include "MISC.H"
#include "SFX.H"
#include "GPU.H"
#include "DRAWPHAS.H"
#include "ROOMLOAD.H"
#endif

#if PC_VERSION
#include "SPECIFIC.H"
#include "DRAWPRIMITIVE.H"
#include "DISPLAY.H"
#include "GAME.H"
#include "INIT.H"
#endif

#include "HEALTH.H"
#include "ITEMS.H"
#include "LARA.H"
#include "MALLOC.H"
#include "NEWINV2.H"
#include INPUT_H

#include "SAVEGAME.H"
#include "SOUND.H"

#include "SPECIFIC.H"
#include "SPOTCAM.H"
#include "TOMB4FX.H"

#include <assert.h>
#if PSXPC_VERSION || PSXPC_TEST
	#include <stdint.h>
#if DEBUG_VERSION
#include "PROFILE.H"
#endif
#endif

#if (PSX_VERSION || SAT_VERSION) && !PSXPC_TEST
typedef unsigned int uintptr_t;
#endif

#if PSX_VERSION || SAT_VERSION
#include "FXTRIG.H"
#include "TEXT_S.H"
#endif

#if PSXPC_TEST
#include <LIBETC.H>
#endif

#if !SAT_VERSION
#include <string.h>
#endif
#include "LOT.H"
#include "TEXT.H"

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
CVECTOR gfLayer1Col;
CVECTOR gfLayer2Col;
unsigned long GameTimer;
struct PHD_VECTOR gfLensFlare;
CVECTOR gfLensFlareColour;
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
int special_features_num = -1;
#if PC_VERSION
char* gfScriptFile;

const char* screens[5] =
{
	"SCREENS\\STORY1.STR", "SCREENS\\NXG.STR", "SCREENS\\STORY2.STR", "SCREENS\\GALLERY.STR", "SCREENS\\SCREENS.STR"
};
#endif

void DoGameflow()//10F5C(<), 10FD8(<)
{
	unsigned char* gf; // $a3
	unsigned char n; // $a1

#if PC_VERSION
	do_boot_screen(Gameflow->Language);
#else
	LoadGameflow();
#endif

#if DISC_VERSION && PSX_VERSION && PLAY_FMVS
	S_PlayFMV(FMV_COPYRIGHT_INTRO, 0);
	S_PlayFMV(FMV_GAME_INTRO, 0);
#endif

	//v1 = Gameflow
	num_fmvs = 0;
	fmv_to_play[1] = 0;
	fmv_to_play[0] = 0;

	gfCurrentLevel = Gameflow->TitleEnabled == 0;
	//v1 = gfCurrentLevel
	//v1 = &gfScriptOffset[gfCurrentLevel]
	//a0 = gfScriptOffset[gfCurrentLevel]
	//v0 = &gfScriptWad[0]

	gf = &gfScriptWad[gfScriptOffset[gfCurrentLevel]];

	while (1)
	{
		switch (n = *gf++)
		{
		case GF_FMV:
#if PLAY_FMVS
			fmv_to_play[num_fmvs++] = *gf++;
#else
			gf++;
#endif
			break;
		case GF_LEVEL:

			gfLevelFlags = gf[1] | (gf[2] << 8);

			if ((gfLevelFlags & 0x8000))
			{
				gfStatus = 999;
				gfCurrentLevel++;
			}
			else
			{
				//loc_112E4
				DoLevel(gf[3], gf[4]);
			}
			//loc_112F8

			gfLegendTime = 0;
			LaserSight = 0;
			BinocularRange = 0;
			gfResidentCut[0] = 0;///@CHECK in asm it's *(int*)&gfResidentCut[0] = 0, check if optimised to this
			gfResidentCut[1] = 0;
			gfResidentCut[2] = 0;
			gfResidentCut[3] = 0;
			gfUVRotate = 0;
			gfNumMips = 0;
			gfNumPickups = 0;
			gfMirrorRoom = 255;

			if (gfStatus != 2)
			{
				if (gfStatus < 3)
				{
					if (gfStatus == 1)
					{
						//loc_11364
						gfInitialiseGame = 1;
						gfCurrentLevel = Gameflow->TitleEnabled == 0;
					}
				}
				else
				{
					//loc_11348
					if (gfStatus == 3)
					{
						//loc_1138C
						if (!Gameflow->DemoDisc && Gameflow->nLevels != 2 && gfLevelComplete <= Gameflow->nLevels)
						{
							//loc_11460
							gfCurrentLevel = gfLevelComplete;
						}
						//loc_113CC
						gfCurrentLevel = 0;
					}
					else if (gfStatus == 4)
					{
						//loc_115DC
						return;
					}
				}
			}
			else
			{
				//loc_1146C
				gfGameMode = 4;
				gfCurrentLevel = savegame.CurrentLevel;
			}
			//loc_11480
			gf = &gfScriptWad[gfScriptOffset[gfCurrentLevel]];
			break;
		case GF_TITLE_LEVEL:

			gfLevelFlags = gf[0] | (gf[1] << 8);
			DoTitle(gf[2], gf[3]);
			gfMirrorRoom = 255;
			gfResidentCut[0] = 0;///@CHECK in asm it's *(int*)&gfResidentCut[0] = 0, check if optimised to this
			gfResidentCut[1] = 0;
			gfResidentCut[2] = 0;
			gfResidentCut[3] = 0;
			gfUVRotate = 0;
			gfNumMips = 0;
			gfNumPickups = 0;

			if (gfStatus == 3)
			{
				//loc_11450
				gfGameMode = 0;
				gfInitialiseGame = 1;
				gfCurrentLevel = gfLevelComplete;
			}
			else if (gfStatus < 4)
			{
				if (gfStatus == 2)
				{
					//loc_11470
					gfGameMode = 4;
					gfCurrentLevel = savegame.CurrentLevel;
				}
			}
			else if (gfStatus == 4)
			{
				//loc_115DC
				return;
			}
			//loc_11480
			gf = &gfScriptWad[gfScriptOffset[gfCurrentLevel]];
			break;
		case GF_LEVEL_DATA_END:
			continue;
			break;
		case GF_CUT:
			gfCutNumber = *gf++;
			break;
		case GF_RESIDENTCUT1:
			gfResidentCut[0] = *gf++;
			break;
		case GF_RESIDENTCUT2:
			gfResidentCut[1] = *gf++;
			break;
		case GF_RESIDENTCUT3:
			gfResidentCut[2] = *gf++;
			break;
		case GF_RESIDENTCUT4:
			gfResidentCut[3] = *gf++;
			break;
		case GF_LAYER1:
			LightningRGB[0] = *gf;
			LightningRGBs[0] = *gf;
			gfLayer1Col.r = *gf++;

			LightningRGB[1] = *gf;
			LightningRGBs[1] = *gf;
			gfLayer1Col.g = *gf++;

			gfLayer1Col.cd = 44;
			LightningRGB[2] = *gf;
			LightningRGBs[2] = *gf;
			gfLayer1Col.b = *gf++;

			gfLayer1Vel = *gf++;
			break;
		case GF_LAYER2:
			LightningRGB[0] = *gf;
			LightningRGBs[0] = *gf;
			gfLayer2Col.r = *gf++;

			LightningRGB[1] = *gf;
			LightningRGBs[1] = *gf;
			gfLayer2Col.g = *gf++;

			gfLayer2Col.cd = 46;
			LightningRGB[2] = *gf;
			LightningRGBs[2] = *gf;
			gfLayer2Col.b = *gf++;

			gfLayer2Vel = *gf++;
			break;
		case GF_UV_ROTATE:
			gfUVRotate = *gf++;
			break;
		case GF_LEGEND:
			gfLegend = *gf++;
			if (gfGameMode != 4)
			{
				gfLegendTime = 150;
			}
			break;
		case GF_LENS_FLARE:

			gfLensFlare.x = ((gf[1] << 8) | gf[0]) << 8;
			gfLensFlare.y = ((gf[2] | (gf[3] << 8)) << 16) >> 8;
			gfLensFlare.z = ((gf[5] << 8) | gf[4]) << 8;

			gfLensFlareColour.r = gf[6];
			gfLensFlareColour.g = gf[7];
			gfLensFlareColour.b = gf[8];

			gf += 9;
			break;
		case GF_MIRROR:
			gfMirrorRoom = *gf;
			gfMirrorZPlane = (gf[4] << 24) | (gf[3] << 16) | (gf[2] << 8) | gf[1];
			gf += 5;
			break;
		case GF_FOG:
			gf += 3;
			break;
		case GF_ANIMATING_MIP:
			//loc_111DC:
			gfMips[gfNumMips++] = *gf++;
			break;
		case GF_RESET_HUB:
			//loc_11290:
			gfResetHubDest = *gf++;
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
		default:
			//def_10FE0
			if (((n + 0x6E) & 0xFF) < 8)
			{
				inventry_objects_list[(n + 0xA3) & 0xFF].objname = gf[0] | (gf[1] << 8);
				inventry_objects_list[(n + 0xA3) & 0xFF].yoff = gf[2] | (gf[3] << 8);
				inventry_objects_list[(n + 0xA3) & 0xFF].scale1 = gf[4] | (gf[5] << 8);
				inventry_objects_list[(n + 0xA3) & 0xFF].yrot = gf[6] | (gf[7] << 8);
				inventry_objects_list[(n + 0xA3) & 0xFF].xrot = gf[8] | (gf[9] << 8);
				inventry_objects_list[(n + 0xA3) & 0xFF].zrot = gf[10] | (gf[11] << 8);
				inventry_objects_list[(n + 0xA3) & 0xFF].flags = gf[12] | (gf[13] << 8);
			}
			else if (((n + 0x62) & 0xFF) < 8)
			{
				inventry_objects_list[(n + 0x7F) & 0xFF].objname = gf[0] | (gf[1] << 8);
				inventry_objects_list[(n + 0x7F) & 0xFF].yoff = gf[2] | (gf[3] << 8);
				inventry_objects_list[(n + 0x7F) & 0xFF].scale1 = gf[4] | (gf[5] << 8);
				inventry_objects_list[(n + 0x7F) & 0xFF].yrot = gf[6] | (gf[7] << 8);
				inventry_objects_list[(n + 0x7F) & 0xFF].xrot = gf[8] | (gf[9] << 8);
				inventry_objects_list[(n + 0x7F) & 0xFF].zrot = gf[10] | (gf[11] << 8);
				inventry_objects_list[(n + 0x7F) & 0xFF].flags = gf[12] | (gf[13] << 8);
			}
			else if (((n + 0x56) & 0xFF) < 4)
			{
				inventry_objects_list[(n + 0xA3) & 0xFF].objname = gf[0] | (gf[1] << 8);
				inventry_objects_list[(n + 0xA3) & 0xFF].yoff = gf[2] | (gf[3] << 8);
				inventry_objects_list[(n + 0xA3) & 0xFF].scale1 = gf[4] | (gf[5] << 8);
				inventry_objects_list[(n + 0xA3) & 0xFF].yrot = gf[6] | (gf[7] << 8);
				inventry_objects_list[(n + 0xA3) & 0xFF].xrot = gf[8] | (gf[9] << 8);
				inventry_objects_list[(n + 0xA3) & 0xFF].zrot = gf[10] | (gf[11] << 8);
				inventry_objects_list[(n + 0xA3) & 0xFF].flags = gf[12] | (gf[13] << 8);
			}
			else if (((n + 0x52) & 0xFF) < 3)
			{
				inventry_objects_list[(n + 0xAD) & 0xFF].objname = gf[0] | (gf[1] << 8);
				inventry_objects_list[(n + 0xAD) & 0xFF].yoff = gf[2] | (gf[3] << 8);
				inventry_objects_list[(n + 0xAD) & 0xFF].scale1 = gf[4] | (gf[5] << 8);
				inventry_objects_list[(n + 0xAD) & 0xFF].yrot = gf[6] | (gf[7] << 8);
				inventry_objects_list[(n + 0xAD) & 0xFF].xrot = gf[8] | (gf[9] << 8);
				inventry_objects_list[(n + 0xAD) & 0xFF].zrot = gf[10] | (gf[11] << 8);
				inventry_objects_list[(n + 0xAD) & 0xFF].flags = gf[12] | (gf[13] << 8);
			}
			else if (((n + 0x4F) & 0xFF) < 16)
			{
				inventry_objects_list[(n + 0x8C) & 0xFF].objname = gf[0] | (gf[1] << 8);
				inventry_objects_list[(n + 0x8C) & 0xFF].yoff = gf[2] | (gf[3] << 8);
				inventry_objects_list[(n + 0x8C) & 0xFF].scale1 = gf[4] | (gf[5] << 8);
				inventry_objects_list[(n + 0x8C) & 0xFF].yrot = gf[6] | (gf[7] << 8);
				inventry_objects_list[(n + 0x8C) & 0xFF].xrot = gf[8] | (gf[9] << 8);
				inventry_objects_list[(n + 0x8C) & 0xFF].zrot = gf[10] | (gf[11] << 8);
				inventry_objects_list[(n + 0x8C) & 0xFF].flags = gf[12] | (gf[13] << 8);
			}
			else if (((n + 0x3F) & 0xFF) < 16)
			{
				inventry_objects_list[(n + 0x64) & 0xFF].objname = gf[0] | (gf[1] << 8);
				inventry_objects_list[(n + 0x64) & 0xFF].yoff = gf[2] | (gf[3] << 8);
				inventry_objects_list[(n + 0x64) & 0xFF].scale1 = gf[4] | (gf[5] << 8);
				inventry_objects_list[(n + 0x64) & 0xFF].yrot = gf[6] | (gf[7] << 8);
				inventry_objects_list[(n + 0x64) & 0xFF].xrot = gf[8] | (gf[9] << 8);
				inventry_objects_list[(n + 0x64) & 0xFF].zrot = gf[10] | (gf[11] << 8);
				inventry_objects_list[(n + 0x64) & 0xFF].flags = gf[12] | (gf[13] << 8);
			}
			else if (((n + 0x2F) & 0xFF) < 8)
			{
				inventry_objects_list[(n + 0x80) & 0xFF].objname = gf[0] | (gf[1] << 8);
				inventry_objects_list[(n + 0x80) & 0xFF].yoff = gf[2] | (gf[3] << 8);
				inventry_objects_list[(n + 0x80) & 0xFF].scale1 = gf[4] | (gf[5] << 8);
				inventry_objects_list[(n + 0x80) & 0xFF].yrot = gf[6] | (gf[7] << 8);
				inventry_objects_list[(n + 0x80) & 0xFF].xrot = gf[8] | (gf[9] << 8);
				inventry_objects_list[(n + 0x80) & 0xFF].zrot = gf[10] | (gf[11] << 8);
				inventry_objects_list[(n + 0x80) & 0xFF].flags = gf[12] | (gf[13] << 8);
			}
			gf += 14;
			break;
		case GF_GIVE_ITEM_AT_STARTUP:
			//loc_11198
			gfPickups[gfNumPickups++] = *gf;
			gf += 2;
			break;
		case GF_LOSE_ITEM_AT_STARTUP:
			//loc_111BC
			gfTakeaways[gfNumTakeaways++] = *gf;
			gf += 2;
			break;
		}

		//loc_10FB4
	}
}

void LoadGameflow()//102E0(<), 102B0(<) (F)
{
	int i;
	int len;
	unsigned char* s = NULL;
	struct STRINGHEADER sh;
	int j;
	int flag;

#if PSX_VERSION || PSXPC_VERSION
	len = FILE_Length(GF_SCRIPT_FILENAME);
	s = (unsigned char*)game_malloc(len);
	FILE_Load(GF_SCRIPT_FILENAME, s);
#endif

#if PC_VERSION
	LoadFile(GF_SCRIPT_FILENAME, (void**)&s);
	gfScriptFile = (char*)s;
#endif

	Gameflow = (struct GAMEFLOW*)s;
	s += sizeof(struct GAMEFLOW);

	gfExtensions = (char*)s;
	s += 40;

	gfFilenameOffset = (unsigned short*)s;
	s += Gameflow->nFileNames * sizeof(unsigned short);

	gfFilenameWad = (char*)s;
	s += Gameflow->FileNameLen;

	gfScriptOffset = (unsigned short*)s;

#if !PC_VERSION
	gfScriptLen = (len + 3) & -4;
#endif
	s += Gameflow->nLevels * sizeof(unsigned short);

	gfScriptWad = s;
	s += Gameflow->ScriptLen;

	

	//loc_103A8
#if PC_VERSION
	for(gfStringOffset = NULL, i = 0; !LoadFile((char*)s, (void**)&gfStringOffset); i++, gfScriptOffset = NULL)
#else
	gfStringOffset = (unsigned short*)(((uintptr_t)s + 3) & -4);

	for(i = 0; FILE_Length((char*)s) == -1; i++)
#endif
	{
		s += strlen((char*)s) + 1;
	}

	Gameflow->Language = i;

#if !PC_VERSION
	FILE_Load((char*)s, gfStringOffset);
#endif

	memcpy(&sh, &gfStringOffset[0], sizeof(struct STRINGHEADER));

#if PSX_VERSION || PSXPC_VERSION

	memcpy(&gfStringOffset[0], &gfStringOffset[sizeof(struct STRINGHEADER) / sizeof(unsigned short)], (sh.nStrings + sh.nPSXStrings) * sizeof(unsigned short));

	gfStringWad = (char*)&gfStringOffset[sh.nStrings + sh.nPSXStrings];

#if BETA_VERSION
	memcpy(&gfStringOffset[sh.nStrings + sh.nPSXStrings], &gfStringOffset[317], sh.StringWadLen + sh.PSXStringWadLen);
#else
	memcpy(&gfStringOffset[sh.nStrings + sh.nPSXStrings], &gfStringOffset[315], sh.StringWadLen + sh.PSXStringWadLen);
#endif

	gfScriptLen += (((sh.nStrings + sh.nPSXStrings * sizeof(unsigned short)) + sh.StringWadLen + sh.PSXStringWadLen + 3) & -4);

#else
	memcpy(&gfStringOffset[0], &gfStringOffset[sizeof(struct STRINGHEADER) / sizeof(unsigned short)], (sh.nStrings + sh.nPSXStrings + sh.nPCStrings) * sizeof(unsigned short));

	gfStringWad = (char*)&gfStringOffset[sh.nStrings + sh.nPSXStrings + sh.nPCStrings];

	memcpy(&gfStringOffset[sh.nStrings + sh.nPSXStrings + sh.nPCStrings], &gfStringOffset[315], sh.StringWadLen + sh.PSXStringWadLen + sh.PCStringWadLen);///@TODO check 315 const for PC

#endif

	//loc_10490
#if PSX_VERSION || PSXPC_VERSION
	for (i = 0; i < sh.nStrings + sh.nPSXStrings; i++)
#else
	for (i = 0; i < sh.nStrings + sh.nPSXStrings + sh.nPCStrings - 1; i++)
#endif
	{
		for (j = 0; j < gfStringOffset[i + 1] - gfStringOffset[i] - 1; j++)
		{
			gfStringWad[gfStringOffset[i] + j] ^= 0xA5;
		}
		//loc_104DC
	}//loc_104F8

	if (Gameflow->nLevels != 0)
	{
		//loc_10510
		for (i = 0; i + 1 < Gameflow->nLevels; i++)
		{
			flag = 0;
			s = &gfScriptWad[gfScriptOffset[i]];

			//loc_10530
			do
			{
				switch (*s++)
				{
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
					//loc_10568
					s += 1;
					break;
				case GF_LEVEL:
					//loc_10588
					gfLevelNames[i] = *s;
					gfWadNames[i] = s[3];
					s += 5;
					break;
				case GF_TITLE_LEVEL:
				case GF_LAYER1:
				case GF_LAYER2:
					//loc_10578
					s += 4;
					break;
				case GF_LEVEL_DATA_END:
					//loc_105BC
					flag = 1;
					break;
				case GF_LENS_FLARE:
					//loc_105B4
					s += 9;
					break;
				case GF_MIRROR:
					//loc_10580
					s += 5;
					break;
				case GF_FOG:
					//loc_10570
					s += 3;
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
				case GF_GIVE_ITEM_AT_STARTUP:///@CHECKME
				case GF_LOSE_ITEM_AT_STARTUP:///@CHECKME
				default:
					//def_10560
					s += 2;
					break;
				}

			} while (flag == 0);
		}
	}
	//loc_105EC
}

void QuickControlPhase()//10274(<), 10264(<) (F) (*) (D) (ND)
{
#if PSX_VERSION
#if DEBUG_VERSION
	ProfileRGB(255, 255, 255);
#endif
	OldSP = SetSp(0x1F8003E0);
#endif

#if PSX_VERSION || PSXPC_VERSION
	gfStatus = ControlPhase(nframes, gfGameMode == 2);
#else
	gfStatus = ControlPhase(nframes, 0);
#endif

#if PSX_VERSION
	SetSp(OldSP);
#if DEBUG_VERSION
	ProfileRGB(0, 0, 0);
#endif
#endif
}

void DoTitle(unsigned char Name, unsigned char Audio)//10604(<), 105C4(<) (F) (*) (D) (ND)
{
/*#if PC_VERSION
	S_Warn("DoTitle PC");
	gfCurrentLevel = LVL5_STREETS_OF_ROME;
	DoLevel(LVL5_STREETS_OF_ROME, Audio);
	return;
#endif*/

	int i;

	CreditsDone = 0;
	CanLoad = 0;

#if PC_VERSION
	SetFade(255, 0);
#else
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

	S_MemSet((char*)&savegame.Level, 0, sizeof(struct STATS));
	S_MemSet((char*)&savegame.Game, 0, sizeof(struct STATS));

	S_LoadLevelFile(Name);
	
	GLOBAL_lastinvitem = -1;
	dels_cutseq_player = 0;

	InitSpotCamSequences();
	
	title_controls_locked_out = 0;

#if PC_VERSION
	InitialiseFXArray(1);
	InitialiseLOTarray(1);

	// TODO fog

	ClearFXFogBulbs();
#endif

	InitialisePickUpDisplay();

#if PSX_VERSION || PSXPC_VERSION
	phd_InitWindow(90);
#endif

#if PC_VERSION
	S_InitialiseScreen();
#endif
	
#if !PSXPC_TEST//Im sure this causes an infinite loop for PSXPC_N, disable for now.
	SOUND_Stop();
#endif
	IsAtmospherePlaying = 0;
	
	S_SetReverbType(1);

	InitialiseCamera();

	if (!bDoCredits)
	{
		trigger_title_spotcam(1);
		ScreenFadedOut = 0;
		ScreenFade = 0;
		dScreenFade = 0;
		ScreenFadeBack = 0;
		ScreenFadeSpeed = 8;
		ScreenFading = 0;
	}
	else
	{
		//loc_10730
		cutseq_num = 28;
		SetFadeClip(32, 1);
		ScreenFadedOut = 1;
		ScreenFade = 255;
		dScreenFade = 255;
#if !BETA_VERSION
		S_CDPlay(CDA_XA14_ECREDITS, 1);
#endif
	}

	//loc_10764
	bUseSpotCam = 1;
	lara_item->mesh_bits = 0;
	gfGameMode = 1;

#if DEBUG_VERSION
	show_game_malloc_totals();
#endif

	gfLevelComplete = 0;
	nframes = 2;
	gfStatus = ControlPhase(2, 0);
	JustLoaded = 0;

#if PC_VERSION
	while (gfStatus == 0)
	{
		GPU_BeginScene();
		SkyDrawPhase();
		gfStatus = TitleOptions();
		if (gfStatus != 0)
			break;
		handle_cutseq_triggering(Name);
		nframes = DrawPhaseGame();
		gfStatus = ControlPhase(nframes, 0);
		DoSpecialFeaturesServer();
	}
#else
	if (gfStatus == 0)
	{
		//loc_107BC
		while (gfStatus == 0)
		{
			GPU_BeginScene();

			if (bDoCredits)
			{
#if !PSXPC_VERSION && RELOC
				if (!((INTFUNCVOID*)RelocPtr[MOD_TITSEQ][1])())
				{
					bDoCredits = 0;
					SetFadeClip(0, 2);
				}
#endif
				//loc_10800
				if (bDoCredits)
					goto loc_10890;
					
			}
			//loc_10810
			if (GLOBAL_playing_cutseq == 0)
			{
				if (ScreenFading == 0 && cutseq_num == 0)
				{
#if DEBUG_VERSION
					if ((RawPad & (IN_R2 | 1)) == (IN_R2 | 1))
					{
						dels_cutseq_selector_flag = 1;
					}
#endif
					//loc_10868
					CreditsDone = 1;
#if RELOC
					gfStatus = ((INTFUNCINT*)RelocPtr[MOD_TITSEQ][0])(Name);
#else
					gfStatus = TitleOptions(Name);
#endif
					//Early out
					if (gfStatus != 0)
						break;

				}//loc_10890

			loc_10890:
				if (GLOBAL_playing_cutseq == 0)
					goto loc_108EC;
			}
			//loc_108A4
			if (bDoCredits == 0 && CreditsDone)
			{
				PrintString(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 20, 1, &gfStringWad[gfStringOffset[STR_DEMO_MODE]], FF_CENTER);
			}
			//loc_108EC
		loc_108EC:
			nframes = DrawPhaseGame();

			if (!PadConnected)
			{
				
				PrintString(SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 2) + 8, 3, &gfStringWad[gfStringOffset[STR_CONTROLLER_REMOVED]], (FF_BLINK | FF_CENTER));
			}
			//loc_1092C
			handle_cutseq_triggering(Name);

			if (gfGameMode == 2)
			{
				if ((dbinput & 0x100))
					goto loc_10970;

				if (GLOBAL_enterinventory == -1)
					goto loc_109A8;

				//loc_10970
			loc_10970:
				if (cutseq_trig == 0 && lara_item->hit_points > 0)
				{
					S_CallInventory2();
				}//loc_109A8
			}//loc_109A8
		loc_109A8:
			QuickControlPhase();

			if (gfGameMode == 2 && ScreenFadedOut != 0)
			{
				InitialiseItemArray(256);

				for (i = 0; i < number_rooms; i++)
				{
					room[i].item_number = -1;
				}
				//loc_10A10
				gfGameMode = 1;

			}//loc_10A14
		}
	}
	//loc_10A24
	Motors[1] = 0;
	Motors[0] = 0;

	if (Gameflow->LoadSaveEnabled)
	{
		mcClose();
	}


	//loc_10A58
	do
	{
#if PSXPC_TEST
		//Because emulator doesn't call this every Vblank
		VSync(0);
#endif
		XAReqVolume = 0;
		
	} while (XAVolume != 0);

#endif

	NoInput = 0;
	S_SoundStopAllSamples(); //Bug, infinite loop on PSX?
	S_CDStop();
	bUseSpotCam = 0;
	bDisableLaraControl = 0;

#if PSX_VERSION || PSXPC_VERSION
	input = 0;
#else
	if (gfStatus != 4)
		input = 0;
#endif

}

void DoLevel(unsigned char Name, unsigned char Audio)//10ABC(<) 10A84(<) (F)
{
	char *d;

#if !BETA_VERSION
	int fmvStatus;
#endif
#if PSXENGINE
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

#if PC_VERSION
	SetFade(255, 0);
#endif

	if (gfGameMode == 4)
	{
		memset(&savegame.Level, 0, sizeof(struct STATS));
	}

	//loc_10B58
	S_LoadLevelFile(Name);

#if PC_VERSION
	//SetFogColor(...); todo

	InitialiseFXArray(TRUE);
	InitialiseLOTarray(TRUE);

	ClearFXFogBulbs();

	// todo
#endif

	InitSpotCamSequences();
	InitialisePickUpDisplay();

#if PC_VERSION
	S_InitialiseScreen();
#endif

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

#if PC_VERSION
		if (IsVolumetric())
		{
			//SetFogColor(...); todo
		}
#endif
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
		CurrentAtmosphere = Audio;
		savegame.Level.Timer = 0;

		if (gfCurrentLevel == LVL5_STREETS_OF_ROME)
		{
			savegame.TLCount = 0;
		}
	}

	//loc_10BF8
	S_CDPlay(CurrentAtmosphere, 1);

	IsAtmospherePlaying = TRUE;
	ScreenFadedOut = FALSE;
	ScreenFading = FALSE;
	ScreenFadeBack = FALSE;
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
		ScreenFadedOut = TRUE;
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

	dbinput = 0;
	JustLoaded = 0;

	//loc_10D30
	while (gfStatus == 0)
	{

		GPU_BeginScene();

		if (gfLegendTime != 0 && DestFadeScreenHeight == 0 && FadeScreenHeight == 0 && cutseq_num == 0)
		{
			PrintString(
#if PSX_VERSION || PSXPC_TEST || PSXPC_VERSION || SAT_VERSION
				0x100, 0xE8, 
#else
				phd_winwidth / 2, phd_winymax - font_height,
#endif
				2, &gfStringWad[gfStringOffset[gfLegend]], FF_CENTER);
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
#if PSX_VERSION
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
#endif

			//loc_10E7C
			QuickControlPhase();
		}
		else
		{
#if PSXENGINE
				//loc_10CAC
				gfStatus = 3;
#endif
			break;
		}
	}

#if PSXENGINE
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
#endif

	S_SoundStopAllSamples();
	S_CDStop();

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

void SpecialFeaturesDisplayScreens(int num)
{
	UNIMPLEMENTED();
}

void DoSpecialFeaturesServer()// (F)
{
	switch(special_features_num)
	{
	case 0:
		SpecialFeaturesDisplayScreens(0);
		break;
	case 1:
		SpecialFeaturesDisplayScreens(1);
		break;
	case 2:
		SpecialFeaturesDisplayScreens(2);
		break;
	case 3:
		SpecialFeaturesDisplayScreens(3);
		break;
	}

	special_features_num = -1;
}