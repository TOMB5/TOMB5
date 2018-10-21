#include "CONTROL.H"

#if PSX_VERSION || PSXPC_VERSION
#include "COLLIDE_S.H"
#include "DRAWPHAS.H"
#include "3D_GEN.H"
#include "CD.H"
#endif
#include "BOX.H"
#include "DELTAPAK.H"
#include "DEBRIS.H"
#include "DRAW.H"

#include "EFFECTS.H"
#include "EFFECT2.H"
#if PC_VERSION
	#include "GAME.H"
	#include "FILE.H"
#include "GLOBAL.H"
#include "SPECIFIC.H"
#include "INPUT.H"
#endif
#include "GAMEFLOW.H"
#if PSX_VERSION || PSXPC_VERSION
#include "GPU.H"
#endif
#include "HAIR.H"
#include "HEALTH.H"
#include "ITEMS.H"
#include "LARA.H"
#include "LARA1GUN.H"
#if PSX_VERSION || PSXPC_VERSION
#include "LOAD_LEV.H"
#include "MATHS.H"
#include "ROOMLOAD.H"
#endif
#include "LOT.H"

#include "NEWINV2.H"
#include "PICKUP.H"
#include INPUT_H

#if PSX_VERSION || PSXPC_VERSION
#include "PSOUTPUT.H"
#include "SETUP.H"
#endif
#include "SAVEGAME.H"
#include "SOUND.H"
#include "SPECIFIC.H"
#include "SPHERE.H"
#include "SPOTCAM.H"
#include "TOMB4FX.H"
#include "TYPES.H"

#include <assert.h>
#include <string.h>
#include "LARAMISC.H"

#define MAX_FRAMES 10

int flipeffect = -1;
int fliptimer;
unsigned char ShatterSounds[18][10] =
{
	{ SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS },
	{ SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS },
	{ SFX_SMASH_WOOD,  SFX_SMASH_WOOD,  SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS },
	{ SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS },
	{ SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS },
	{ SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS },
	{ SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS },
	{ SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS },
	{ SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS },
	{ SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS },
	{ SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS },
	{ SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_METAL, SFX_SMASH_METAL, SFX_SMASH_METAL, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS },
	{ SFX_SMASH_GLASS, SFX_SMASH_METAL, SFX_SMASH_METAL, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS },
	{ SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS },
	{ SFX_SMASH_METAL, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_METAL, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS },
	{ SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS },
	{ SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS },
	{ SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS, SFX_SMASH_GLASS }
};
unsigned char WeaponDelay;
unsigned char KeyTriggerActive;
unsigned short GlobalCounter;
char TriggerTimer;
int reset_flag;
short SlowMotion;
short SlowMoFrameCount = 16;
unsigned char InItemControlLoop;
short ItemNewRoomNo;
short SmashedMeshCount;
char richcutfrigflag;
int nRope;
char GetLaraOnLOS;
int NoInput;
int number_los_rooms;
int framecount;
struct ITEM_INFO* items;
int flip_status;
#if PC_VERSION
int flipmap[255];
int flip_stats[255];
#else
int flipmap[10];
int flip_stats[10];
#endif
int height_type;
int tiltxoff;
int tiltyoff;
unsigned long _CutSceneTriggered1;
unsigned long _CutSceneTriggered2;
unsigned long FmvSceneTriggered;
unsigned char CurrentAtmosphere;
unsigned char IsAtmospherePlaying;
char* OutsideRoomTable;
short* OutsideRoomOffsets;
short IsRoomOutsideNo;
short FXType;
int OnObject;
short* trigger_index;
char cd_flags[136];
unsigned char InGameCnt;
struct RAT_STRUCT* Rats;
struct BAT_STRUCT* Bats;
struct SPIDER_STRUCT* Spiders;
struct TWOGUN_INFO twogun[4];
int SetDebounce;
short WB_room;
struct ITEM_INFO* WB_item;
unsigned char HeavyTriggered;
struct MESH_INFO* SmashedMesh[16];
short SmashedMeshRoom[16];
struct PENDULUM CurrentPendulum;
char LaraDrawType;
char WeatherType;
char RoomDrawType;
struct PHD_VECTOR ClosestCoord;
int ClosestItem;
int ClosestDist;
short XSoff1;
short YSoff1;
short ZSoff1;
short XSoff2;
short YSoff2;
short ZSoff2;
short los_rooms[20];
char globoncuttrig;
short ItemNewRooms[256][2];
struct CHARDEF CharDef[106] =
{
	{ -0x52, 0x34, 4, 0xD, -0xB, 0, 0xB },
	{ 0x62, 0x3A, 7, 5, -0xA, 1, 5 },
	{ 0x52, 0x1A, 0xE, 0xC, -0xA, 1, 0xB },
	{ 0x4E, 0x26, 0xA, 0xE, -0xA, 1, 0xD },
	{ -0x2A, 0xD, 0xF, 0xC, -9, 2, 0xC },
	{ 0x28, 0x1A, 0xE, 0xC, -0xA, 1, 0xB },
	{ -0x62, 0x39, 5, 5, -0xB, 0, 4 },
	{ -0x34, 0x27, 6, 0x10, -0xC, 0, 0xD },
	{ 0x22, 0x28, 6, 0x10, -0xB, 0, 0xE },
	{ -0x48, 0x3B, 5, 5, -0xB, 0, 4 },
	{ 0x16, 0x28, 0xB, 0xB, -9, 2, 0xB },
	{ -0x4E, 0x3B, 5, 5, -2, 8, 0xC },
	{ 0x6A, 0x3C, 8, 3, -4, 6, 9 },
	{ 0x72, 0x3C, 5, 4, -2, 8, 0xB },
	{ -0x2C, 0x26, 9, 0xF, -0xC, 0, 0xC },
	{ 0x58, 0x31, 0xA, 0xA, -8, 3, 0xB },
	{ -0x38, 0x37, 6, 0xA, -8, 3, 0xB },
	{ 0x2E, 0x34, 9, 0xA, -8, 3, 0xB },
	{ 0x58, 0x26, 8, 0xB, -8, 3, 0xC },
	{ 0x3E, 0x28, 0xB, 0xB, -8, 3, 0xC },
	{ -0x72, 0x30, 9, 0xC, -9, 2, 0xC },
	{ -0x18, 0x32, 9, 0xB, -9, 2, 0xB },
	{ 0x78, 0x2F, 9, 0xC, -9, 2, 0xC },
	{ 0x16, 0x33, 9, 0xB, -9, 2, 0xB },
	{ 0x6E, 0x31, 9, 0xB, -8, 3, 0xC },
	{ -0x68, 0x39, 5, 9, -7, 4, 0xB },
	{ -0x78, 0x39, 5, 0xA, -7, 4, 0xC },
	{ -0x4E, 0x28, 0xC, 0xA, -8, 3, 0xB },
	{ -0x2E, 0x35, 0xB, 7, -7, 4, 9 },
	{ -0x10, 0x28, 0xC, 0xA, -8, 3, 0xB },
	{ 0xC, 0x27, 0xA, 0xD, -0xB, 0, 0xB },
	{ 0x42, 0xD, 0x10, 0xE, -0xA, 1, 0xD },
	{ -0x7E, 0xD, 0xE, 0xD, -0xB, 0, 0xB },
	{ -0x2A, 0x19, 0xD, 0xD, -0xB, 0, 0xB },
	{ -0x7C, 0x23, 0xB, 0xD, -0xB, 0, 0xB },
	{ 0, 0x1A, 0xD, 0xD, -0xB, 0, 0xB },
	{ 0xE, 0x1A, 0xD, 0xD, -0xB, 0, 0xB },
	{ 0x42, 0x1B, 0xC, 0xD, -0xB, 0, 0xB },
	{ -0x4A, 0x1B, 0xC, 0xD, -0xB, 0, 0xB },
	{ -0x38, 0xD, 0xE, 0xD, -0xB, 0, 0xB },
	{ -0x22, 0x36, 5, 0xD, -0xB, 0, 0xB },
	{ 0x38, 0x34, 5, 0x10, -0xB, 0, 0xE },
	{ -0x1A, 0xF, 0xD, 0xD, -0xB, 0, 0xB },
	{ -0x70, 0x23, 0xB, 0xD, -0xB, 0, 0xB },
	{ 0x30, 0xD, 0x12, 0xD, -0xB, 0, 0xB },
	{ -0x70, 0xD, 0xE, 0xD, -0xB, 0, 0xB },
	{ 0x36, 0x1A, 0xC, 0xD, -0xB, 0, 0xB },
	{ -0x38, 0x1A, 0xC, 0xD, -0xB, 0, 0xB },
	{ -0x10, 0, 0xE, 0xF, -0xB, 0, 0xD },
	{ -0x62, 0xD, 0xE, 0xD, -0xB, 0, 0xB },
	{ -0x64, 0x23, 0xB, 0xD, -0xB, 0, 0xB },
	{ -0x54, 0xD, 0xE, 0xD, -0xB, 0, 0xB },
	{ 0x62, 0xD, 0xF, 0xD, -0xB, 0, 0xB },
	{ 0x52, 0xD, 0xF, 0xD, -0xB, 0, 0xB },
	{ 0x18, 0xD, 0x17, 0xD, -0xB, 0, 0xB },
	{ -0x46, 0xD, 0xD, 0xE, -0xB, 0, 0xC },
	{ 0x72, 0xD, 0xF, 0xD, -0xB, 0, 0xB },
	{ -0x1C, 0x1C, 0xC, 0xD, -0xB, 0, 0xB },
	{ 0x3E, 0x3C, 6, 4, -4, 6, 9 },
	{ -8, 0x3B, 6, 4, -4, 6, 9 },
	{ 0x58, 0x3B, 8, 4, -4, 6, 9 },
	{ -0x72, 0x3C, 7, 3, -3, 7, 9 },
	{ 0x78, 0x3B, 8, 4, -4, 6, 9 },
	{ -0xE, 0x3B, 5, 5, -0xB, 0, 4 },
	{ 0x62, 0x31, 0xB, 9, -7, 4, 0xB },
	{ 0x60, 0x23, 0xB, 0xE, -0xC, 0, 0xB },
	{ 0x48, 0x34, 9, 9, -7, 4, 0xB },
	{ 0, 0x27, 0xB, 0xC, -0xA, 1, 0xB },
	{ -0x5C, 0x34, 9, 9, -7, 4, 0xB },
	{ -0x58, 0x26, 0xA, 0xE, -0xC, 0, 0xB },
	{ 0x78, 0x23, 0xC, 0xC, -7, 4, 0xE },
	{ 0x6C, 0x23, 0xB, 0xE, -0xC, 0, 0xB },
	{ -0x3E, 0x1B, 6, 0xC, -0xA, 1, 0xB },
	{ 0x28, 0x33, 6, 0x10, -0xA, 1, 0xE },
	{ 0x1C, 0x1A, 0xC, 0xE, -0xC, 0, 0xB },
	{ 0x52, 0x34, 6, 0xD, -0xB, 0, 0xB },
	{ 0x60, 0x1A, 0x12, 9, -7, 4, 0xB },
	{ -0x68, 0x30, 0xC, 9, -7, 4, 0xB },
	{ 0x3E, 0x33, 0xA, 9, -7, 4, 0xB },
	{ -0xC, 0xF, 0xB, 0xD, -7, 4, 0xE },
	{ 0x34, 0x27, 0xA, 0xD, -7, 4, 0xE },
	{ 0xA, 0x34, 0xA, 9, -7, 4, 0xB },
	{ -0x42, 0x34, 9, 9, -7, 4, 0xB },
	{ 0, 0x33, 9, 0xB, -9, 2, 0xB },
	{ -0x4E, 0x32, 0xB, 9, -7, 4, 0xB },
	{ -0x7E, 0x30, 0xC, 9, -7, 4, 0xB },
	{ -0x7C, 0x1A, 0x12, 9, -7, 4, 0xB },
	{ -0xE, 0x32, 0xB, 9, -7, 4, 0xB },
	{ 0x28, 0x26, 0xB, 0xD, -7, 4, 0xE },
	{ -0x18, 0x29, 8, 9, -7, 4, 0xB },
	{ -0x22, 0x29, 9, 0xD, -7, 4, 0xE },
	{ -0x7E, 0x39, 6, 9, -7, 4, 0xB },
	{ -0x3E, 0x27, 0xA, 0xD, -0xA, 1, 0xC },
	{ 0x20, 0x38, 5, 0xC, -0xA, 1, 0xB },
	{ 0, 0xD, 0x18, 0xD, -0xA, 6, 0xB },
	{ -0x40, 0, 0x18, 0xD, -0xA, 6, 0xB },
	{ -0x58, 0, 0x18, 0xD, -0xA, 6, 0xB },
	{ -0x28, 0, 0x18, 0xD, -0xA, 6, 0xB },
	{ -0x6A, 0x1A, 0x12, 9, -8, 6, 0xB },
	{ -0x58, 0x1A, 0xD, 0xC, -9, 6, 0xB },
	{ 0x72, 0x1A, 0x12, 9, -8, 6, 0xB },
	{ -0x10, 0x1C, 0xD, 0xC, -9, 6, 0xB },
	{ 0, 0, 0x29, 0xD, -0xA, 6, 0xB },
	{ 0x54, 0, 0x29, 0xD, -0xA, 6, 0xB },
	{ 0x2A, 0, 0x29, 0xD, -0xA, 6, 0xB },
	{ 0x7E, 0, 0x29, 0xD, -0xA, 6, 0xB }
};
struct ROPE_STRUCT Ropes[12];

#if PC_VERSION
short cdtrack = -1;
BYTE byte_86BBA3 = 0;
#endif

char byte_A3660;

#if PC_VERSION
void UpdateSparks()
{
	Unimpl();
}

void UpdateFireSparks()
{
	Unimpl();
}

void UpdateSmokeSparks()
{
	Unimpl();
}

void UpdateBubbles()
{
	Unimpl();
}

void UpdateSplashes()
{
	Unimpl();
}

void UpdateDebris()
{
	Unimpl();
}

void UpdateBlood()
{
	Unimpl();
}

void UpdateDrips()
{
	Unimpl();
}

void UpdateGunShells()
{
	Unimpl();
}

void UpdateRats()
{
	Unimpl();
}

void UpdateBats()
{
	Unimpl();
}

void UpdateShockwaves()
{
	Unimpl();
}

void UpdateLightning()
{
	Unimpl();
}

void UpdateTwogunLasers()
{
	Unimpl();
}

void UpdatePulseColour()
{
	Unimpl();
}

void KlaxonTremor()
{
	Unimpl();
}

void UpdateSky()
{
	if (gfLevelFlags & GF_LVOP_LAYER1_USED)
	{
		SkyPos += gfLayer1Vel;

		if (SkyPos > 9728)
		{
			SkyPos -= 9728;
		}
		else if(SkyPos < 0)
		{
			SkyPos += 9728;
		}
	}

	if (gfLevelFlags & GF_LVOP_LAYER2_USED)
	{
		SkyPos2 += gfLayer2Vel;

		if (SkyPos2 > 9728)
		{
			SkyPos2 -= 9728;
		}
		else if (SkyPos2 < 0)
		{
			SkyPos2 += 9728;
		}
	}
}

#endif

long ControlPhase(long nframes, int demo_mode)//1D538(<), 1D6CC(<) //DO NOT TOUCH (PSX/PSXPC)
{
#if PC_VERSION
	S_Warn("PC CONTROLPHASE %d %d", nframes, demo_mode);

	RegeneratePickups();

	if (nframes > MAX_FRAMES)
		nframes = MAX_FRAMES;

	if (bTrackCamInit)
		bUseSpotCam = FALSE;

	SetDebounce = TRUE;

	for (framecount += nframes; framecount > 0; framecount -= 2)
	{
		GlobalCounter++;

		UpdateSky();

		if (cdtrack > 0)
			S_CDLoop();

		if (S_UpdateInput() == -1)
			return 0;

		if (bDisableLaraControl)
		{
			if (gfCurrentLevel != LVL5_TITLE)
				dbinput = IN_NONE;

			input &= IN_LOOK;
		}

		if (cutseq_trig)
			input = IN_NONE;

		SetDebounce = FALSE;

		if (gfCurrentLevel != LVL5_TITLE)
		{
			if ((dbinput & IN_OPTION || GLOBAL_enterinventory != -1) && !cutseq_trig && lara_item->hit_points > 0)
			{
				S_SoundStopAllSamples();

				if (S_CallInventory2())
					return 2;
			}
		}

		if (byte_86BBA3)
			dels_give_lara_items_cheat();

		if (gfLevelComplete)
			return 3;

		if (reset_flag || lara.death_count > 300 || (lara.death_count > 60 && input != IN_NONE))
		{
			reset_flag = FALSE;

			if (Gameflow->DemoDisc && reset_flag)
				return 4;
			else
				return 1;
		}

		if (demo_mode && input == IN_ALL)
		{
			input = IN_NONE;
		}

		if (lara.death_count == 0 && FadeScreenHeight == 0)
		{
			if (input & IN_SAVE)
			{
				S_LoadSave(IN_SAVE, FALSE);
			}
			else if (input & IN_LOAD)
			{
				if (S_LoadSave(IN_LOAD, FALSE) >= 0)
					return 2;
			}

			if (input & IN_PAUSE && gfGameMode == 0)
			{
				if (S_PauseMenu() == 8)
					return 1;
			}
		}

		if (thread_started)
		{
			return 4;
		}

		if (!(input & IN_LOOK)
			|| SniperCamActive
			|| bUseSpotCam
			|| bTrackCamInit
			|| 
			((lara_item->current_anim_state != STATE_LARA_STOP || lara_item->anim_number != ANIMATION_LARA_STAY_IDLE)
				&& (!lara.IsDucked
					|| input & IN_DUCK
					|| lara_item->anim_number != ANIMATION_LARA_CROUCH_IDLE
					|| lara_item->goal_anim_state != STATE_LARA_CROUCH_IDLE)))
		{
			if (BinocularRange == 0)
			{
				if (SniperCamActive
					|| bUseSpotCam
					|| bTrackCamInit)
				{
					input &= ~IN_LOOK;
				}
			}
			else
			{
				if (LaserSight)
				{
					BinocularRange = 0;
					LaserSight = 0;
					AlterFOV(ANGLE(80));
					lara_item->mesh_bits = 0xFFFFFFFF;
					lara.IsDucked = FALSE;
					camera.type = BinocularOldCamera;

					lara.head_y_rot = 0;
					lara.head_x_rot = 0;

					lara.torso_y_rot = 0;
					lara.torso_x_rot = 0;

					camera.bounce = 0;
					BinocularOn = -8;
					input &= ~IN_LOOK;
				}
				else
				{
					input |= IN_LOOK;
				}
			}

			InfraRed = FALSE;
		}
		else if (BinocularRange == 0)
		{
			if (lara.gun_status == LG_READY
				&& ((lara.gun_type == WEAPON_REVOLVER && lara.sixshooter_type_carried & WTYPE_LASERSIGHT)
					|| (lara.gun_type == WEAPON_HK)
					|| (lara.gun_type == WEAPON_CROSSBOW && lara.crossbow_type_carried & WTYPE_LASERSIGHT)))
			{
				BinocularRange = 128;
				BinocularOldCamera = camera.old_type;

				lara.Busy = TRUE;
				LaserSight = TRUE;

				if (!(gfLevelFlags & GF_LVOP_TRAIN))
					InfraRed = TRUE;
				else
					InfraRed = FALSE;
			}
			else
				InfraRed = FALSE;
		}
		else
		{
			if (LaserSight)
			{
				if (!(gfLevelFlags & GF_LVOP_TRAIN))
					InfraRed = TRUE;
				else
					InfraRed = FALSE;
			}
			else
			{
				if ((gfLevelFlags & GF_LVOP_TRAIN) && (inputBusy & IN_ACTION))
					InfraRed = TRUE;
				else
					InfraRed = FALSE;
			}
		}

		ClearDynamics();
		ClearFires();

		GotLaraSpheres = FALSE;
		InItemControlLoop = TRUE;

		short item_num = next_item_active;
		while (item_num != -1)
		{
			struct ITEM_INFO* item = &items[item_num];
			short nex = item->next_active;

			if (item->after_death < 128)
			{
				if (objects[item->object_number].control)
					objects[item->object_number].control(item_num);
			}
			else
			{
				KillItem(item_num);
			}

			item_num = nex;
		}

		InItemControlLoop = FALSE;

		KillMoveItems();

		InItemControlLoop = TRUE;

		short fx_num = next_fx_active;
		while (fx_num != -1)
		{
			struct FX_INFO* fx = &effects[fx_num];
			short nex = fx->next_active;

			if (objects[fx->object_number].control)
				objects[fx->object_number].control(fx_num);

			fx_num = nex;
		}

		InItemControlLoop = FALSE;

		KillMoveEffects();

		if (KillEverythingFlag)
			KillEverything();

		if (SmokeCountL != 0)
			SmokeCountL--;

		if (SmokeCountR != 0)
			SmokeCountR--;

		if (SplashCount != 0)
			SplashCount--;

		if (WeaponDelay != 0)
			WeaponDelay--;

		if (lara.has_fired && !(wibble & 0x7F))
		{
			AlertNearbyGuards(lara_item);
			lara.has_fired = FALSE;
		}

		XSoff1 += 150;
		YSoff1 += 230;
		ZSoff1 += 660;

		XSoff2 += 270;
		YSoff2 += 440;
		ZSoff2 += 160;

		if (lara.poisoned != 0 && !GLOBAL_playing_cutseq)
		{
			if (lara.poisoned <= 4096)
			{
				if (lara.dpoisoned)
					lara.dpoisoned++;
			}
			else
			{
				lara.poisoned = 4096;
			}

			if (gfLevelFlags & GF_LVOP_TRAIN && !lara.Gassed)
			{
				if (lara.dpoisoned != 0)
				{
					lara.dpoisoned -= 8;

					if (lara.dpoisoned < 0)
						lara.dpoisoned = 0;
				}
			}

			if (lara.poisoned >= 256 && !(wibble & 0xFF))
			{
				lara_item->hit_points -= lara.poisoned >> (8 - lara.Gassed);
				PoisonFlag = 16;
			}
		}

		lara.skelebob = 0;

		InItemControlLoop = TRUE;

		if (!GLOBAL_playing_cutseq && !gfGameMode)
		{
			lara.Fired = FALSE;

			LaraControl(0);

			if (LaraDrawType == LARA_DIVESUIT)
				DoSubsuitStuff();
		}

		InItemControlLoop = FALSE;

		KillMoveItems();

		if (gfLevelFlags & GF_LVOP_TRAIN && !bUseSpotCam)
		{
			if (room[lara_item->room_number].FlipNumber > 10)
			{
				InitialiseSpotCam(room[lara_item->room_number].FlipNumber);
				bUseSpotCam = TRUE;
			}
		}

		if (GLOBAL_inventoryitemchosen != -1)
		{
			SayNo();

			GLOBAL_inventoryitemchosen = -1;
		}

		if (GLOBAL_playing_cutseq)
		{
			camera.type = CINEMATIC_CAMERA;
			CalculateCamera();
		}
		else
		{
			if (LaraDrawType != LARA_DIVESUIT)
			{
				HairControl(0, 0, 0);

				if (gfLevelFlags & GF_LVOP_YOUNG_LARA)
					HairControl(0, 1, 0);
			}

			if (!bUseSpotCam)
			{
				bTrackCamInit = FALSE;
				CalculateCamera();
			}
			else
			{
				CalculateSpotCams();
			}
		}

		CamRot.vy = (mGetAngle(camera.pos.z, camera.pos.x, camera.target.z, camera.target.x) >> 4) & 0xFFF;
		wibble = (wibble + 4) & 0xFC;
		TriggerLaraDrips();

		while (SmashedMeshCount != 0)
		{
			SmashedMeshCount--;

			struct MESH_INFO* mesh = SmashedMesh[SmashedMeshCount];
			struct FLOOR_INFO* floor = GetFloor(mesh->x, mesh->y, mesh->z, &SmashedMeshRoom[SmashedMeshCount]);

			GetHeight(floor, mesh->x, mesh->y, mesh->z);
			TestTriggers(trigger_index, 1, 0);

			floor->stopper = FALSE;

			SmashedMesh[SmashedMeshCount] = NULL;
		}

		UpdateSparks();
		UpdateFireSparks();
		UpdateSmokeSparks();
		UpdateBubbles();
		UpdateSplashes();
		UpdateDebris();
		UpdateBlood();
		UpdateDrips();
		UpdateGunShells();
		UpdateRats();
		UpdateBats();
		UpdateSpiders();
		UpdateShockwaves();
		UpdateLightning();
		UpdateTwogunLasers();
		AnimateWaterfalls();
		UpdatePulseColour();

		if (gfCurrentLevel == LVL5_SINKING_SUBMARINE)
			KlaxonTremor();

		SoundEffects();

		health_bar_timer--;

		if (gfGameMode == 0)
		{
			GameTimer++;

			if (savegame.Level.Timer != 0)
			{
				if (!GLOBAL_playing_cutseq)
					savegame.Level.Timer++;
			}
		}

		UpdateFadeClip();
	}

	return 0;
#else
	short item_num;
	short nex;

	//s0 = a0
	//s6 = a1

	if (SlowMotion == 0)
	{
		//loc_1D5B4
		if (SlowMoFrameCount > 16)
		{
			//loc_1D5C8
			SlowMoFrameCount--;
		}
	}
	else
	{
		SlowMotion--;
		if (SlowMoFrameCount > 39)
		{
			//loc_1D5C8
			SlowMoFrameCount--;
		}
	}

	//loc_1D5CC
	while (nframes < SlowMoFrameCount / 8)
	{
#if PSX_VERSION
		VSync(0);
#endif
		nframes++;
	}

	//loc_1D60C
	nframes = 2;
	GnLastFrameCount = 0;

	//loc_1D618
	RegeneratePickups();

	if (nframes > 10)
	{
		nframes = 10;
	}//loc_1D630


	if (bTrackCamInit)
	{
		bUseSpotCam = 0;
	}

	//loc_1D64C
	SetDebounce = 1;
	framecount += nframes;

	if (framecount <= 0)
	{
		//loc_1E3B8
		return 0;
	}

	if (GLOBAL_enterinventory != -1)
	{
		return 0;
	}

	//s4 = -1
	//s3 = 1

	//loc_1D684
	while (GLOBAL_enterinventory == -1)
	{
		GlobalCounter++;
		UpdateSky();
		S_UpdateInput();

		if (bDisableLaraControl)
		{
			if (gfCurrentLevel != LVL5_TITLE)
			{
				dbinput = 0;
			}

			//loc_1D6D4
			input &= IN_LOOK;
		}

		//loc_1D6EC
		if (cutseq_trig != 0)
		{
			input = IN_NONE;
		}

		//loc_1D708
		SetDebounce = 0;
		if (gfLevelComplete != 0)
		{
			return 3;
		}

		if (reset_flag != 0)
		{
			reset_flag = 0;
			return 1;
		}

		if (lara.death_count > 90)//loc_1D708, loc_1D89C
		{
			//loc_1D5A0
			reset_flag = 0;
			return S_Death();
		}

		if (demo_mode)
		{
			if (PadConnected && !ScreenFading)
			{
				PrintString(256, 230, 2, &gfStringWad[gfStringOffset[STR_DEMO_MODE]], 0);
			}

			//loc_1D7A0
			if (input == -1)
			{
				input = IN_NONE;
				Motors[0] = 0;
				Motors[1] = 0;
			}
		}//loc_1D7D4
		else
		{
			if (gfGameMode != 1 && Gameflow->CheatEnabled)
			{
				if (input == IN_NONE)
				{
					if (Gameflow->InputTimeout < NoInput++)
					{
						return 1;
					}
				}//1D844
				else
				{
					NoInput = 0;
				}
			}
		}

		//loc_1D848, loc_1D9DC 

#if DISC_VERSION///@TODO
	//loc_1D9DC
		if (input == IN_NONE)
		{
			//lbu	$v0, byte_A335A
			//lbu	$a0, 0x14DC($gp)
			//bnez	$v0, loc_1DA5C
			//andi	$v0, $a0, 0xFF
			//lbu	$v0, byte_A2827
			//nop
			//bnez	$v0, loc_1DA5C
			//andi	$v0, $a0, 0xFF
			//sltiu	$v0, $a0, 4
			//bnez	$v0, loc_1DA68
			//addiu	$v0, $a0, 1
			//addiu	$v0, $s2, 0x71E8
			//lh	$v1, 0x1A($v0)
			//nop
			//bnez	$v1, loc_1DA5C
			//andi	$v0, $a0, 0xFF
		}
		//loc_1DA3C:
		//sb	$zero, byte_800A601D
		// sb	$zero, byte_800A601C//motors maybe
		//jal	sub_62190
		//nop
		//j	loc_1E5D0
		// move	$v0, $zero
#endif

	//1D848
		if (InGameCnt < 4)
		{
			InGameCnt++;
		}

		//loc_1D860
		//a1 = input
#if 0//TODO highly mangled branching
		if (!(input & IN_LOOK) && SniperCamActive && bUseSpotCam && bTrackCamInit)
		{
			//loc_1D9D0
		}
		//v0 = 2
		//a0 = lara_item;
		//v1 = lara_item->current_anim_state;
		//v1 = lara (lara_info);
		if (lara_item->current_anim_state == 2 && lara_item->anim_number != 0x67)
		{
			//loc_1D8E0
			if (lara_item->pos.y_pos & 0x800 && !(input & 0x2000) && lara_item->anim_number == 0xDE && lara_item->goal_anim_state == 0x47)
			{
				//loc_1D920
			}//loc_1D9D0
			else
			{
			}

		}//loc_1D920

		//^TODO!!!
	}
	else
	{
		//loc_1D9D0 //***TODO
	}

	if (BinocularRange != 0)
	{
		if (LaserSight != 0)
		{


		}//loc_1DAC0
	}//loc_1DA80
#endif

	//loc_1DAD0
	if (BinocularRange != 0)
	{
		if (LaserSight != 0)
		{
			//loc_1DB28
			if (gfLevelFlags & GF_LVOP_TRAIN)
			{
				InfraRed = 0;
			}
			else
			{
				InfraRed = 1;
			}
		}
		else
		{
			if (gfLevelFlags & GF_LVOP_TRAIN && inputBusy & 0x40)
			{
				InfraRed = 1;
			}
			else
			{
				InfraRed = 0;
			}
		}
	}
	else
	{
		InfraRed = 0;
	}

	//loc_1DB44 
	//infr skp stre
	ClearDynamics();
	ClearFires();

	item_num = next_item_active;
	GotLaraSpheres = 0;
	InItemControlLoop = 1;

	if (item_num != -1)
	{
		//loc_1DB80
		while (items[item_num].next_active != -1)
		{
			if (items[item_num].after_death > 127)
			{
				KillItem(item_num);
			}
			else
			{
				//loc_1DBB4
				if (objects[items[item_num].object_number].control != NULL)
				{
					objects[items[item_num].object_number].control(item_num);
				}
			}

			item_num++;
		}

	}//loc_1DBE8, 1DDF4

	InItemControlLoop = 0;
	KillMoveItems();
	InItemControlLoop = 1;
	nex = next_fx_active;

	while (nex != -1)
	{
		nex = effects[next_fx_active].next_active;
		if (objects[effects[nex].object_number].control != NULL)
		{
			objects[effects[nex].object_number].control(nex);
		}
	}

	//loc_1DC60
	InItemControlLoop = 0;
	KillMoveEffects();

	if (KillEverythingFlag != 0)
	{
		KillEverything();
	}

	//loc_1DC88
	if (SmokeCountL != 0)
	{
		SmokeCountL--;
	}

	//loc_1DCA4
	if (SmokeCountR != 0)
	{
		SmokeCountR--;
	}

	//loc_1DCC0
	if (SplashCount != 0)
	{
		SplashCount--;
	}

	//loc_1DCDC
	if (WeaponDelay != 0)
	{
		WeaponDelay--;
	}

	//loc_1DCF0
	if (lara.burn && !(wibble & 0x7F))
	{
		AlertNearbyGuards(lara_item);
		lara.burn = 0;

	}//loc_1DD40  // *VERIFIED TILL HERE, FIXME below looks very mangled?

	XSoff1 += 150;
	YSoff1 += 230;
	ZSoff1 += 660;

	XSoff2 += 270;
	YSoff2 += 440;
	ZSoff2 += 160;

	////a000 = lara;

	if (lara.poisoned)
	{
		if (GLOBAL_playing_cutseq == 0)
		{
			//assert(0);
		}//loc_1DE90

	}//loc_1DE84

	//a1 = lara

	//loc_1DE90
	lara.skelebob = 0;
	InItemControlLoop = 1;

	if (GLOBAL_playing_cutseq == 0 && gfGameMode == 0)
	{
		//assert(0);
#if 0
		lui	$v1, 0xFFFE
			li	$v1, 0xFFFEFFFF
			lw	$v0, 0x44($a1)
			move	$a0, $zero
			and	$v0, $v1
			jal	sub_4A838
			sw	$v0, 0x44($a1)
			lbu	$v1, 0x1C58($gp)
			li	$v0, 5
			bne	$v1, $v0, loc_1DEF4
			addiu	$v0, $s5, -0x2240
			lw	$v1, 0x18($v0)
			nop
			lw	$a0, 0($v1)
			nop
			jalr	$a0
			nop
#endif
	}
	//loc_1DEF4
	InItemControlLoop = 0;

	KillMoveItems();

	if ((gfLevelFlags & GF_LVOP_TRAIN) && bUseSpotCam == 0)
	{
		//v0 = lara_item;
		//assert(0);
	}

	//loc_1DF7C
	if (GLOBAL_inventoryitemchosen != -1)
	{
		SayNo();
		GLOBAL_inventoryitemchosen = 1;
	}

	//loc_1DFA0
	if (GLOBAL_playing_cutseq == 0)//TODO
	{
		if (LaraDrawType != 5)
		{
			HairControl(0, 0, 0);

			if ((gfLevelFlags) & GF_LVOP_YOUNG_LARA)
			{
				HairControl(0, 1, 2);
			}
		}
		//loc_1DFF4
		if (GLOBAL_playing_cutseq == 0)//redudant
		{
			if (bUseSpotCam != 0)
			{
				CalculateSpotCams();
				//j loc_1E054///@FIXME illegal jump?
			}//loc_1E02C
			CalculateCamera();
		}//loc_1E044

	}//loc_1E044

	camera.type = CINEMATIC_CAMERA;
	CalculateCamera();

	//loc_1E054
	CamRot.vy = mGetAngle(camera.pos.x, camera.pos.z, camera.target.x, camera.target.z) / 16;

	wibble = wibble + 4 & 0xFC;

	TriggerLaraDrips();

	if (SmashedMeshCount != 0)//LOOP
	{
		//TODO
		//SmashedMeshCount = v000000;
		//v0 = CamRot.vy;
	}

	//loc_1E15C
#if 0
	UpdateSparks();
	//addiu	$s0, $s5, -0x2240
	UpdateFireSparks();
	UpdateSmokeSparks();
	UpdateBubbles();
	UpdateSplashes();
	UpdateDebris();
	UpdateBlood();
	UpdateDrips();
	UpdateGunShells();

#endif

	if (RelocPtr[9] != NULL)//UpdateRats
	{
		//unsigned long* v0 = (unsigned long*)RelocPtr[9];
		//jalr v0[5];
	}

	//loc_1E1C4
	if (RelocPtr[21] != NULL)//UpdateBats
	{
		//unsigned long* v0 = (unsigned long*)RelocPtr[21];
		//jalr v0[1];
	}

	//loc_1E1E4
	if (RelocPtr[32] != NULL)//UpdateSpiders
	{
		//unsigned long* v0 = (unsigned long*)RelocPtr[32];
		//jalr v0[5];
	}

	//loc_1E204
	//UpdateShockwaves();

	if (RelocPtr[35] != NULL)//UpdateLighting
	{
		//unsigned long* v0 = (unsigned long*)RelocPtr[35];
		//jalr v0[1];
	}

	//loc_1E22C
	if (RelocPtr[7] != NULL)//UpdateTwogunLasers
	{
		//unsigned long* v0 = (unsigned long*)RelocPtr[7];
		//jalr v0[2];
	}

	//loc_1E24C
	AnimateWaterfalls();
	//UpdatePulseColour();

	if (gfCurrentLevel == LVL5_SINKING_SUBMARINE)
	{
		if (RelocPtr[48] != NULL)//KlaxonTremor
		{
			//unsigned long* v0 = (unsigned long*)RelocPtr[48];
			//jalr v0[0];
		}
	}

	//loc_1E288
	SoundEffects();
	health_bar_timer--;

	if (gfGameMode == 0)
	{
		GameTimer++;

		if (savegame.Level.Timer != 0 && GLOBAL_playing_cutseq == 0)
		{
			savegame.Level.Timer++;
		}
	}

	//loc_1E2F0
	VibratePad();

	if (Motors[1] == 0 && camera.bounce)
	{
		//TODO

	}

	//loc_1E384
	UpdateFadeClip();
	framecount -= 2;

	if (framecount <= 0)
	{
		break;
	}
	}
#endif

	//loc_1E3B8
return 0;
}


void KillMoveItems()//1D420(<), 1D5B4(<) (F)
{
	short nex;

	if (ItemNewRoomNo > 0)
	{
		for(nex = 0; nex < ItemNewRoomNo; nex++)
		{
			if (ItemNewRooms[nex][0] & 0x8000)
			{
				KillItem(ItemNewRooms[nex][0] & 0x7FFF);
			}
			else
			{
				ItemNewRoom(ItemNewRooms[nex][0], ItemNewRooms[nex][1]);
			}

		}
	}

	ItemNewRoomNo = 0;
}

void KillMoveEffects()//1D4AC(<), 1D640(<) (F) 
{
	short nex;

	if (ItemNewRoomNo > 0)
	{
		for (nex = 0; nex < ItemNewRoomNo; nex++)
		{
			if (ItemNewRooms[nex][0] & 0x8000)
			{
				KillEffect(ItemNewRooms[nex][0] & 0x7FFF);
			}
			else
			{
				EffectNewRoom(ItemNewRooms[nex][0], ItemNewRooms[nex][1]);
			}

		}
	}

	ItemNewRoomNo = 0;
}

void TestTriggers(short* data, int heavy, int HeavyFlags)//(F)
{
	globoncuttrig = 0;
	_TestTriggers(data, heavy, HeavyFlags);
	if (!globoncuttrig)
	{
		if (richcutfrigflag)
			richcutfrigflag = 0;
	}
}

long rand_1 = 0xD371F947;

long GetRandomControl()//5E9F0, 926F8 (F)
{
	rand_1 = (rand_1 * 0x41C64E6D) + 0x3039;
	return (rand_1 >> 16) & 0x7FFF;
}

void SeedRandomControl(long seed)//(F)
{
	rand_1 = seed;
}

long rand_2 = 0xD371F947;

long GetRandomDraw()//5EA18, 5F6F8 (F)
{
	rand_2 = (rand_2 * 0x41C64E6D) + 0x3039;
	return (rand_2 >> 16) * 0x7FFF;
}

void SeedRandomDraw(long seed)//(F)
{
	rand_2 = seed;
}

void ClearFires()//8B1C8(<), 8D20C(<) (F)
{
	int i;

	for (i = 0; i < 32; i++)
	{
		fires[i].on = 0;
	}
}

void AddFire(int x, int y, int z, char size, short room_num, short on)// (F)
{
	struct FIRE_LIST* fptr = &fires[0];

	while (fptr->on)
	{
		fptr++;
		if (fptr - fires >= 32)
			return;
	}

	if (on)
		fptr->on = on;
	else
		fptr->on = 1;

	fptr->x = x;
	fptr->y = y;
	fptr->z = z;
	fptr->size = size;
	fptr->room_number = room_num;
}

void ClearDynamics()//8B1EC(<), 8D230(<) (F)
{
	int i;

#if 0
	//Not sure why Core have only clearing 32 entries here.
	//Either bug or intentinal.
	for (i = 0; i < 64; i++)
#else
	for (i = 0; i < 32; i++)
#endif
	{
		dynamics[i].on = 0;
	}
}

int is_object_in_room(int roomnumber, int objnumber)// (F)
{
	short item_num = room[roomnumber].item_number;
	short nex;
	struct ITEM_INFO* item;

	for (nex = item_num; nex != -1; nex = item->next_item)
	{
		item = &items[nex];

		if (item->object_number == objnumber)
			return TRUE;
	}

	return FALSE;
}

void NeatAndTidyTriggerCutscene(int value, int timer)
{
	UNIMPLEMENTED();
}

int CheckCutPlayed(int num)//20E34(<), 21040(<) (F)
{
	if (num < 32)
		return _CutSceneTriggered1 & (1 << num);
	else
		return _CutSceneTriggered2 & (1 << (num - 32));
}

void SetCutNotPlayed(int num)//20DEC(<), 20FF8(<) (F)
{
	if (num < 32)
		_CutSceneTriggered1 &= ~(1 << num);
	else
		_CutSceneTriggered2 &= ~(1 << (num - 32));
}

void SetCutPlayed(int num)//20DA0(<), 20FAC(<) (F)
{
	if (num < 32)
		_CutSceneTriggered1 |= 1 << num;
	else
		_CutSceneTriggered2 |= 1 << (num - 32);
}

void InitCutPlayed()//20D90, 20F9C (F)
{
	_CutSceneTriggered1 = 0;
	_CutSceneTriggered2 = 0;
}

void ResetGuards()//20B48(<), ?
{
	short item_num; // $s1
	short room_num; // $t1
	struct ITEM_INFO* target_item; // $s0

	item_num = next_item_active;

	//v0 = -1;

	if (item_num == -1)
	{
		return;
	}

	//loc_20D78
	//s2 = &objects[0];
	//v1 = s1 << 3;
	//v1 += s1;
	//a0 = &items[0];
	//v1 <<= 4;
	target_item = &items[item_num];//s0
	//v0 = target_item->object_number;
	//v0 << 6 = 0x64;

	//v0 = &objects[target_item->object_number];

	//a0 = item+_num;
	if (objects[target_item->object_number].intelligent)
	{
		target_item->status = ITEM_INVISIBLE;

		RemoveActiveItem(item_num);
		DisableBaddieAI(item_num);
		//v1 = -15872
		//a3 = target_item->ai_bits;
		//t0 = target_item->TOSSPAD;
		//a1 = target_item->draw_room;
		//v0 = t0 << 1;
		//v0 = v0 & 0x3E00;
		//a3 |= v0;
		//v1 = target_item->item_flags[2];
		//v0 = room;
		//t1 = v1 & 0xFF;

	}//loc_20D68
#if 0
		sll	$v1, 16
		sra	$v1, 24
		sll	$v1, 8
		sll	$a0, $t1, 2
		addu	$a0, $t1
		sll	$a0, 4
		addu	$a0, $v0
		sll	$v0, $a1, 16
		sra	$v0, 24
		sll	$v0, 10
		lw	$a2, 0x20($a0)
		andi	$a1, 0xFF
		addu	$v1, $a2
		sw	$v1, 0x44($s0)
		lw	$v1, 0x14($a0)
		sll	$a1, 10
		addu	$v0, $v1
		addiu	$v0, 0x200
		sw	$v0, 0x40($s0)
		andi	$v0, $t0, 0xE000
		lw	$v1, 0x1C($a0)
		andi	$t0, 0xFF
		sh	$v0, 0x4E($s0)
		li	$v0, 0x57
		sw	$a3, 0x84($s0)
		sh	$t0, 0x3A($s0)
		addu	$a1, $v1
		lh	$v1, 0xC($s0)
		addiu	$a1, 0x200
		beq	$v1, $v0, loc_20C8C
		sw	$a1, 0x48($s0)
		li	$v0, 0x4D
		beq	$v1, $v0, loc_20C8C
		li	$v0, 0x47
		bne	$v1, $v0, loc_20CA8
		li	$v0, 0x27

		loc_20C8C:
	lh	$v0, 0xC($s0)
		nop
		sll	$v0, 6
		addu	$v0, $s2
		lhu	$v1, 0x26($v0)
		j	loc_20D08
		sh	$v1, 0x14($s0)

		loc_20CA8:
	bne	$v1, $v0, loc_20CBC
		lui	$v1, 1
		lhu	$v0, 0x9E6($s2)
		j	loc_20D00
		addiu	$v0, 6

		loc_20CBC :
		lw	$v0, 0x870($s2)
		nop
		and	$v0, $v1
		beqz	$v0, loc_20CDC
		nop
		lhu	$v0, 0x866($s2)
		j	loc_20D08
		sh	$v0, 0x14($s0)

		loc_20CDC:
	lw	$v0, 0x1470($s2)
		nop
		and	$v0, $v1
		beqz	$v0, loc_20CFC
		nop
		lhu	$v0, 0x1466($s2)
		j	loc_20D08
		sh	$v0, 0x14($s0)

		loc_20CFC:
	lhu	$v0, 0x966($s2)

		loc_20D00 :
		nop
		sh	$v0, 0x14($s0)

		loc_20D08 :
		lh	$v1, 0xC($s0)
		li	$v0, 0x4D
		bne	$v1, $v0, loc_20D24
		li	$v0, 1
		sh	$zero, 0xE($s0)
		j	loc_20D2C
		sh	$zero, 0x10($s0)

		loc_20D24:
	sh	$v0, 0xE($s0)
		sh	$v0, 0x10($s0)

		loc_20D2C :
		lh	$v1, 0x14($s0)
		lw	$a0, dword_800A25E0
		sll	$v0, $v1, 2
		addu	$v0, $v1
		sll	$v0, 3
		addu	$v0, $a0
		lhu	$v1, 0x18($v0)
		lh	$a0, 0x18($s0)
		nop
		beq	$a0, $t1, loc_20D68
		sh	$v1, 0x16($s0)
		move	$a0, $s1
		jal	sub_7C608
		move	$a1, $t1

		loc_20D68 :
	lh	$s1, 0x1C($s0)
		li	$v0, 0xFFFFFFFF
		bne	$s1, $v0, loc_20B78
		sll	$v1, $s1, 3

		loc_20D78 :
		lw	$ra, 0x20 + var_4($sp)
		lw	$s2, 0x20 + var_8($sp)
		lw	$s1, 0x20 + var_C($sp)
		lw	$s0, 0x20 + var_10($sp)
		jr	$ra
		addiu	$sp, 0x20
#endif

		UNIMPLEMENTED();
}

void InterpolateAngle(short dest, short* src, short* diff, short speed)//20AF0(<) ? (F)
{
	long adiff;

	adiff = (dest & 0xFFFF) - src[0];

	if (32768 < adiff)
	{
		adiff += -65536;
	}//0x20B18
	else if (adiff < -32768)
	{
		adiff += 65536;
	}

	if (diff != NULL)
	{
		diff[0] = adiff;
	}

	//0x20B34
	src[0] = (src[0] >> speed) + adiff;
}

int CheckGuardOnTrigger()//209AC(<), 20BB8(<) (F)
{
	int slot;
	short room_number;
	struct creature_info* cinfo;
	struct ITEM_INFO* item;

	room_number = lara_item->room_number;

	cinfo = &baddie_slots[0];
	GetFloor(lara_item->pos.x_pos, lara_item->pos.y_pos, lara_item->pos.z_pos, &room_number);

	//loc_209FC
	for (slot = 0; slot < 5; slot++, cinfo++)
	{
		if (cinfo->item_num != -1 && cinfo->alerted)
		{
			item = &items[cinfo->item_num];

			if (room_number == item->room_number && item->current_anim_state == 1)
			{
				//loc_20A70
				if (abs(item->pos.x_pos - lara_item->pos.x_pos) < SECTOR(1) &&
					abs(item->pos.z_pos - lara_item->pos.z_pos) < SECTOR(1) &&
					abs(item->pos.y_pos - lara_item->pos.y_pos) < SECTOR(0.25))
				{
					return 1;
				}
			}
		}
	}

	return 0;
}

int ExplodeItemNode(struct ITEM_INFO* item, int Node, int NoXZVel, long bits)//207DC(<), 209F0(<) (F)
{
	struct object_info* object;
	short* meshp;
	short num;

	if (item->mesh_bits & (1 << Node))
	{
		if (item->object_number != SWITCH_TYPE7 || gfCurrentLevel != LVL5_SINKING_SUBMARINE && gfCurrentLevel != LVL5_BASE)
		{
			num = bits;
			if (bits == 256)
				num = -64;
		}
		else
		{
			SoundEffect(SFX_SMASH_METAL, &item->pos, 0);
			num = bits;
		}
		GetSpheres(item, Slist, 3);
		object = &objects[item->object_number];
		ShatterItem.YRot = item->pos.y_rot;
		meshp = meshes[object->mesh_index + 2 * Node];
		ShatterItem.Bit = 1 << Node;
		ShatterItem.meshp = meshp;
		ShatterItem.Sphere.x = Slist[Node].x;
		ShatterItem.Sphere.y = Slist[Node].y;
		ShatterItem.Sphere.z = Slist[Node].z;
		ShatterItem.il = &item->il;
		ShatterItem.Flags = item->object_number != CROSSBOW_BOLT ? 0 : 0x400;
		ShatterObject(&ShatterItem, 0, num, item->room_number, NoXZVel);
		item->mesh_bits &= ~ShatterItem.Bit;
		return 1;
	}
	else
	{
		return 0;
	}
}

int GetTargetOnLOS(struct GAME_VECTOR* src, struct GAME_VECTOR* dest, int DrawTarget, int firing)
{
	UNIMPLEMENTED();
	return 0;
}

void FireCrossBowFromLaserSight(struct GAME_VECTOR* src, struct GAME_VECTOR* target)// (F)
{
	short angles[2];
	struct PHD_3DPOS pos;

	target->x = (target->x & ~0x3FE) | 0x200;
	target->z = (target->z & ~0x3FE) | 0x200;

#if (PSXENGINE && !defined(USE_ASM)) || PC_VERSION
	phd_GetVectorAngles(target->x - src->x, target->y - src->y, target->z - src->z, angles);
#endif
	pos.z_rot = 0;
	pos.x_pos = src->x;
	pos.y_pos = src->y;
	pos.z_pos = src->z;
	pos.x_rot = angles[1];
	pos.y_rot = angles[0];

	FireCrossbow(&pos);
}

void TriggerNormalCDTrack(short value, short flags, short type)// (F)
{
	int code;

	if (value == 117 || value == 118 || value == 121 || (value >= 123 && value <= 130))
	{
		if (CurrentAtmosphere != value)
		{
			CurrentAtmosphere = value;

			if (IsAtmospherePlaying)
				S_CDPlay(value, 1);
		}
	}
	else
	{
		code = (flags >> 8) & 0x3F;

		if ((code & cd_flags[value]) != code)
		{
			cd_flags[value] |= code;
			S_CDPlay(value, 0);
			IsAtmospherePlaying = 0;
		}
	}
}

void TriggerCDTrack(short value, short flags, short type)// (F)
{
	if (value < 136)
		TriggerNormalCDTrack(value, flags, type);
}

void RemoveRoomFlipItems(struct room_info* r)//1F938(<), 1FB4C(<) (F)
{
	short item_num;

	for (item_num = r->item_number; item_num != -1; item_num = items[item_num].next_item)
	{
		if (items[item_num].flags & IFLAG_INVISIBLE)
		{
			if (objects[items[item_num].object_number].intelligent)
			{
				if (items[item_num].hit_points <= 0 && items[item_num].hit_points != 0xC000)
				{
					KillItem(item_num);
				}
			}
		}
	}
}

void FlipMap(int FlipNumber)// (F)
{
	struct room_info* r = room;
	int i;
	for (i = 0; i < number_rooms; i++, r++)
	{
		if (r->flipped_room >= 0 && r->FlipNumber == FlipNumber)
		{
			struct room_info temp;
			struct room_info* flipped = &room[r->flipped_room];
			RemoveRoomFlipItems(r);
			memcpy(&temp, r, sizeof(struct room_info));
			memcpy(r, flipped, sizeof(struct room_info));
			memcpy(flipped, &temp, sizeof(struct room_info));
			r->flipped_room = flipped->flipped_room;
			flipped->flipped_room = -1;
			r->item_number = flipped->item_number;
			r->fx_number = flipped->fx_number;
			AddRoomFlipItems(r);
		}
	}
	flip_stats[FlipNumber] = flip_stats[FlipNumber] == 0;
	flip_status = flip_stats[FlipNumber] == 0;
	{
		struct creature_info* cinfo = baddie_slots;
		int slot;
		for (slot = 0; slot < 6; slot++, cinfo++)
		{
			cinfo->LOT.target_box = 0x7FF;
		}
	}
}

void _TestTriggers(short* data, int heavy, int HeavyFlags)
{
	UNIMPLEMENTED();
}

void RefreshCamera(short type, short* data)
{
	UNIMPLEMENTED();
}

long GetWaterHeight(long x, long y, long z, short room_number)
{
	UNIMPLEMENTED();
	return 0;
}

void AlterFloorHeight(struct ITEM_INFO* item, int height)//1E3E4(<), 1E5F8(<) (F)
{
	struct FLOOR_INFO* floor;
	struct FLOOR_INFO* ceiling;
	short room_num;
	short joby;

	joby = 0;

	if (abs(height) & 0xFF)
	{
		joby = 1;

		if (height < 0)
		{
			--height;
		}
		else
		{
			++height;
		}
	}

	//loc_1E42C
	room_num = item->room_number;
	floor = GetFloor(item->pos.x_pos, item->pos.y_pos, item->pos.z_pos, &room_num);
	ceiling = GetFloor(item->pos.x_pos, (item->pos.y_pos + height) - SECTOR(1), item->pos.z_pos, &room_num);

	if (floor->floor == -127)
	{
		if (height < 0)
		{
			floor->floor = (ceiling->ceiling + ((height + 255) >> 8));
		}
		else
		{
			floor->floor = (ceiling->ceiling + ((height) >> 8));
		}
	}
	else
	{
		//loc_1E4A0
		if (height < 0)
		{
			floor->floor = (floor->floor + ((height + 255) >> 8));
		}
		else
		{
			floor->floor = (floor->floor + (height >> 8));
		}

		//loc_1E4AC
		if (floor->floor == ceiling->ceiling && joby == 0)
		{
			floor->floor = -127;
		}
	}

	//loc_1E4D8
	if ((boxes[floor->box].overlap_index & BOX_LAST))
	{
		if (height < 0)
		{
			boxes[floor->box].overlap_index |= BOX_BLOCKED;
		}
		else
		{
			//loc_1E514
			boxes[floor->box].overlap_index &= ~BOX_BLOCKED;
		}
	}
}

short GetHeight(struct FLOOR_INFO* floor, int x, int y, int z)
{
	UNIMPLEMENTED();
	return 0;
}

struct FLOOR_INFO* GetFloor(int x, int y, int z, short* room_number)//78954(<), 7A998(<) (F)
{
	struct room_info* r;
	struct FLOOR_INFO* floor;
	int y_floor, x_floor, next_room;
	int tmp;

	for (r = &room[*room_number]; ; r = &room[next_room])
	{
		x_floor = (z - r->z) >> 10;
		y_floor = (x - r->x) >> 10;

		if (x_floor <= 0)
		{
			x_floor = 0;
			if (y_floor < 1)
			{
				y_floor = 1;
			}
			else if (y_floor > r->y_size - 2)
			{
				y_floor = r->y_size - 2;
			}
		}
		else if (x_floor >= r->x_size - 1)
		{
			x_floor = r->x_size - 1;
			if (y_floor < 1)
			{
				y_floor = 1;
			}
			else if (y_floor > r->y_size - 2)
			{
				y_floor = r->y_size - 2;
			}
		}
		else if (y_floor < 0)
		{
			y_floor = 0;
		}
		else if (y_floor >= r->y_size)
		{
			y_floor = r->y_size - 1;
		}

		floor = &r->floor[x_floor + y_floor * r->x_size];
		next_room = GetDoor(floor);
		if (next_room == 255)
			break;
		*room_number = next_room;
	}

	if (y < floor->floor << 8)
	{
		if (y < floor->ceiling << 8 && floor->sky_room != -1)
		{
			do
			{
				tmp = CheckNoColCeilingTriangle(floor, x, z);
				if (tmp == 1 || tmp == -1 && y >= r->maxceiling)
					break;
				*room_number = floor->sky_room;
				r = &room[floor->sky_room];
				floor = &r->floor[((z - r->z) >> 10) + r->x_size * ((x - r->x) >> 10)];
				if (y >= floor->ceiling << 8)
					break;
			} while (floor->sky_room != 0xFF);
		}
	}
	else if (floor->pit_room != 0xFF)
	{
		while (1)
		{
			tmp = CheckNoColFloorTriangle(floor, x, z);
			if (tmp == 1 || tmp == -1 && y < r->minfloor)
				break;
			*room_number = floor->pit_room;
			r = &room[floor->pit_room];
			tmp = ((z - r->z) >> 10) + r->x_size * ((x - r->x) >> 10);
			/*if (abs(tmp) > 1048576)
			{
				S_Warn("[GetFloor] - sector num too big -> probably room array not initialized\n");
				S_Warn("[GetFloor] - returning or the vc runtime will shit brixes\n");
				return floor;
			}*/
			floor = &r->floor[tmp];
			if (y < r->floor[tmp].floor << 8)
				break;
			if (floor->pit_room == 0xFF)
				return &r->floor[tmp];
		}
	}

	return floor;
}

short GetCeiling(struct FLOOR_INFO* floor, int x, int y, int z)
{
	UNIMPLEMENTED();
	return 0;
}

int TriggerActive(struct ITEM_INFO* item)// (F)
{
	if ((item->flags & IFLAG_ACTIVATION_MASK) == IFLAG_ACTIVATION_MASK)
	{
		if (item->timer)
		{
			if (item->timer <= 0)
			{
				if (item->timer < -1)
				{
					item->timer++;
					if (item->timer == -1)
						item->timer = 0;
				}
			}
			else
			{
				item->timer--;
				if (item->timer == 0)
					item->timer = -1;
			}

			if (item->timer < 0)
				return (~item->flags & IFLAG_REVERSE) == 0;
		}
	}
	else
	{
		return (~item->flags & IFLAG_REVERSE) == 0;
	}

	return (~item->flags & IFLAG_REVERSE) != 0;
}

void AddRoomFlipItems(struct room_info* r)//1FA0C(<), 1FC20(<) (F)
{
	short item_num;

	for (item_num = r->item_number; item_num != -1; item_num = items[item_num].next_item)
	{
		if (items[item_num].item_flags[1])
		{
			switch (items[item_num].object_number)
			{
			case RAISING_BLOCK1:
				AlterFloorHeight(&items[item_num], SECTOR(-1));
				break;

			case RAISING_BLOCK2:
				AlterFloorHeight(&items[item_num], SECTOR(-2));
				break;
			}
		}
	}
}

int IsRoomOutside(long x, long y, long z)//8EF00(<), 90F44(<) (F)
{
	short off, room_num;
	struct FLOOR_INFO* floor;
	short height, ceiling;
	struct room_info* r;

	if (x < 0 || z < 0)
		return -2;

	off = OutsideRoomOffsets[(z / 4096) + 27 * (x / 4096)];

	if (off == -1)
		return -2;

	if (off >= 0)
	{
		char* ptr = &OutsideRoomTable[off];
		

		if (*ptr == -1)
			return -2;

		while (TRUE)
		{
			r = &room[*ptr];
			if (y >= r->maxceiling && y <= r->minfloor)
			{
				if (z >= r->z + 1024 && z <= (r->x_size / 1024) + r->z - 1024)
				{
					if (x >= r->x + 1024 && x <= (r->y_size / 1024) + r->x - 1024)
						break;
				}
			}
			ptr++;

			if (*ptr == -1)
				return -2;
		}

		IsRoomOutsideNo = room_num = *ptr;
	}
	else
	{
		r = &room[off & 0x7fff];

		if (y < r->maxceiling || y > r->minfloor)
			return -2;

		if (z < r->z + 1024 || z > r->x_size / 1024 + r->z - 1024)
			return -2;

		if (x < r->x + 1024 || x > r->y_size / 1024 + r->x - 1024)
			return -2;

		IsRoomOutsideNo = room_num = off & 0x7fff;
	}

	floor = GetFloor(x, y, z, &room_num);

	height = GetHeight(floor, x, y, z);
	if (height == -32512 || y > height)
		return -2;

	ceiling = GetCeiling(floor, x, y, z);

	if (y >= ceiling)
		return (r->flags & RF_WIND_BLOWS_PONYTAIL || r->flags & RF_FILL_WATER) ? 1 : -3;

	return -2;
}

short GetDoor(struct FLOOR_INFO* floor)//787CC(<), 7A810(<) (F)
{
	int type, fixtype;
	short* data;

	if (!floor->index)
		return 255;

	type = floor_data[floor->index];
	data = &floor_data[floor->index + 1];

	fixtype = type & FD_MASK_FUNCTION;

	if (fixtype == TILT_TYPE
		|| fixtype == SPLIT1
		|| fixtype == SPLIT2
		|| fixtype == NOCOLF1B
		|| fixtype == NOCOLF1T
		|| fixtype == NOCOLF2B
		|| fixtype == NOCOLF2T)
	{
		if (type & FD_MASK_END_DATA)
			return 255;
		type = data[1];
		data += 2;
	}

	fixtype = type & FD_MASK_FUNCTION;

	if (fixtype == ROOF_TYPE
		|| fixtype == SPLIT3
		|| fixtype == SPLIT4
		|| fixtype == NOCOLC1B
		|| fixtype == NOCOLC1T
		|| fixtype == NOCOLC2B
		|| fixtype == NOCOLC2T)
	{
		if (type & FD_MASK_END_DATA)
			return 255;
		type = data[1];
		data += 2;
	}

	if ((type & FD_MASK_FUNCTION) == DOOR_TYPE)
		return *data;

	return 255;
}

int LOS(struct GAME_VECTOR* start, struct GAME_VECTOR* target)//79460(<), 7B4A4(<) (F)
{
	struct FLOOR_INFO* floor;
	int los1, los2;

	if ((abs(target->z - start->z)) > (abs(target->x - start->x)))
	{
		los1 = xLOS(start, target);
		los2 = zLOS(start, target);
	}
	else
	{
		los1 = zLOS(start, target);
		los2 = xLOS(start, target);
	}

	if (los2)
	{
		floor = GetFloor(target->x, target->y, target->z, &target->room_number);

		if (ClipTarget(start, target, floor) || los1 == 1 || los2 == 1)
			return 1;
	}

	return 0;
}

int xLOS(struct GAME_VECTOR* start, struct GAME_VECTOR* target)
{
	UNIMPLEMENTED();
	return 0;
}

int zLOS(struct GAME_VECTOR* start, struct GAME_VECTOR* target)
{
	UNIMPLEMENTED();
	return 0;
}

int CheckNoColCeilingTriangle(struct FLOOR_INFO* floor, int x, int z)// (F)
{
	short* fd = &floor_data[floor->index];
	short fixtype = *fd & FD_MASK_FUNCTION;
	int fix_x = x & 0x3FF;
	int fix_z = z & 0x3FF;

	if (floor->index == 0)
		return 0;

	if (fixtype == TILT_TYPE
		|| fixtype == SPLIT1
		|| fixtype == SPLIT2
		|| fixtype == NOCOLF1T
		|| fixtype == NOCOLF1B
		|| fixtype == NOCOLF2T
		|| fixtype == NOCOLF2B)
	{
		if (*fd & FD_MASK_END_DATA)
			return 0;

		fixtype = fd[2] & FD_MASK_FUNCTION;
	}

	switch (fixtype)
	{
	case NOCOLC1T:
		if (fix_x <= 1024 - fix_z)
			return -1;
		break;
	case NOCOLC1B:
		if (fix_x > 1024 - fix_z)
			return -1;
		break;
	case NOCOLC2T:
		if (fix_x <= fix_z)
			return -1;
		break;
	case NOCOLC2B:
		if (fix_x > fix_z)
			return -1;
		break;
	default:
		return 0;
	}

	return 1;
}

int CheckNoColFloorTriangle(struct FLOOR_INFO* floor, int x, int z)// (F)
{
	short fixtype = floor_data[floor->index] & FD_MASK_FUNCTION;
	int fix_x = x & 0x3FF;
	int fix_z = z & 0x3FF;

	if (floor->index == 0)
		return 0;

	switch (fixtype)
	{
	case NOCOLF1T:
		if (fix_x <= 1024 - fix_z)
			return -1;
		break;
	case NOCOLF1B:
		if (fix_x > 1024 - fix_z)
			return -1;
		break;
	case NOCOLF2T:
		if (fix_x <= fix_z)
			return -1;
		break;
	case NOCOLF2B:
		if (fix_x > fix_z)
			return -1;
		break;
	default:
		return 0;
	}

	return 1;
}

int ClipTarget(struct GAME_VECTOR* start, struct GAME_VECTOR* target, struct FLOOR_INFO* floor)
{
	UNIMPLEMENTED();
	return 0;
}

#ifndef PSX_VERSION || PSXPC_VERSION///@FIXME @pc
void GetJointAbsPosition(struct ITEM_INFO* item, struct PHD_VECTOR* pos, int joint)
{
	UNIMPLEMENTED();
}
#endif

int ObjectOnLOS2(struct GAME_VECTOR* start, struct GAME_VECTOR* target, struct PHD_VECTOR* a3, struct MESH_INFO** a4)
{
	UNIMPLEMENTED();
	return 0;
}

int check_xray_machine_trigger()// (F)
{
	int i;
	for (i = 0; i < level_items; i++)
	{
		if (items[i].object_number == XRAY_CONTROLLER &&
			items[i].trigger_flags == 0 &&
			items[i].item_flags[0] == 666)
		{
			return TRUE;
		}
	}

	return FALSE;
}

void AnimateItem(struct ITEM_INFO* item)
{
	UNIMPLEMENTED();
}

void UpdateSpiders()
{
	UNIMPLEMENTED();
}