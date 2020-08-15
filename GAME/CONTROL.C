#include "CONTROL.H"
#include "CALCHAIR.H"

#if PSX_VERSION || PSXPC_VERSION
#include "COLLIDE_S.H"
#include "DRAWPHAS.H"
#include "3D_GEN.H"
#include "CD.H"
#elif SAT_VERSION
#include "SCOLLIDE.H"
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
#include "DISPLAY.H"
	#include "GAME.H"
	#include "FILE.H"
#include "GLOBAL.H"
#include "SPECIFIC.H"
#include "INPUT.H"
#include "INCLUDE.H"
#endif
#include "GAMEFLOW.H"
#if PSX_VERSION || PSXPC_VERSION || SAT_VERSION
#include "GPU.H"

#include "LOAD_LEV.H"
#include "MATHS.H"
#include "ROOMLOAD.H"
#include "PSOUTPUT.H"
#include "SETUP.H"
#include "CODEWAD.H"

#include "GETSTUFF.H"
#include "TEXT_S.H"
#include "FXTRIG.H"
#include "TYPEDEFS.H"
#include "MISC.H"
#endif
#include "LARA1GUN.H"
#include "HAIR.H"
#include "HEALTH.H"
#include "ITEMS.H"
#include "SPHERES.H"
#if PSX_VERSION
#include <LIBETC.H>
#include <LIBGTE.H>
#include "TEXT_S.H"
#endif
#include "LOT.H"

#include "NEWINV2.H"
#include "PICKUP.H"
#include INPUT_H
#include "SAVEGAME.H"
#include "SOUND.H"
#include "SPECIFIC.H"
#include "SPHERE.H"
#include "SPOTCAM.H"
#include "TOMB4FX.H"
#include "TYPES.H"

#if !SAT_VERSION
#include <assert.h>
#include <string.h>
#endif

#include "LARAMISC.H"
#include "LARA.H"
#include "TRAPS.H"
#include "SWITCH.H"
#include "TWOGUN.H"

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

#if PC_VERSION
#define CDEF(u, v, w, h, yo, ts, bs) { (u) / 255.0f, (v) / 255.0f, w, h, yo, ts, bs }
#else
#define CDEF(u, v, w, h, yo, ts, bs) { u, v, w, h, yo, ts, bs }
#endif

struct CHARDEF CharDef[106] =
{
	CDEF(174, 52, 4, 13, -11, 0, 11),
	CDEF(98, 58, 7, 5, -10, 1, 5),
	CDEF(82, 26, 14, 12, -10, 1, 11),
	CDEF(78, 38, 10, 14, -10, 1, 13),
	CDEF(214, 13, 15, 12, -9, 2, 12),
	CDEF(40, 26, 14, 12, -10, 1, 11),
	CDEF(158, 57, 5, 5, -11, 0, 4),
	CDEF(204, 39, 6, 16, -12, 0, 13),
	CDEF(34, 40, 6, 16, -11, 0, 14),
	CDEF(184, 59, 5, 5, -11, 0, 4),
	CDEF(22, 40, 11, 11, -9, 2, 11),
	CDEF(178, 59, 5, 5, -2, 8, 12),
	CDEF(106, 60, 8, 3, -4, 6, 9),
	CDEF(114, 60, 5, 4, -2, 8, 11),
	CDEF(212, 38, 9, 15, -12, 0, 12),
	CDEF(88, 49, 10, 10, -8, 3, 11),
	CDEF(200, 55, 6, 10, -8, 3, 11),
	CDEF(46, 52, 9, 10, -8, 3, 11),
	CDEF(88, 38, 8, 11, -8, 3, 12),
	CDEF(62, 40, 11, 11, -8, 3, 12),
	CDEF(142, 48, 9, 12, -9, 2, 12),
	CDEF(232, 50, 9, 11, -9, 2, 11),
	CDEF(120, 47, 9, 12, -9, 2, 12),
	CDEF(22, 51, 9, 11, -9, 2, 11),
	CDEF(110, 49, 9, 11, -8, 3, 12),
	CDEF(152, 57, 5, 9, -7, 4, 11),
	CDEF(136, 57, 5, 10, -7, 4, 12),
	CDEF(178, 40, 12, 10, -8, 3, 11),
	CDEF(210, 53, 11, 7, -7, 4, 9),
	CDEF(240, 40, 12, 10, -8, 3, 11),
	CDEF(12, 39, 10, 13, -11, 0, 11),
	CDEF(66, 13, 16, 14, -10, 1, 13),
	CDEF(130, 13, 14, 13, -11, 0, 11),
	CDEF(214, 25, 13, 13, -11, 0, 11),
	CDEF(132, 35, 11, 13, -11, 0, 11),
	CDEF(0, 26, 13, 13, -11, 0, 11),
	CDEF(14, 26, 13, 13, -11, 0, 11),
	CDEF(66, 27, 12, 13, -11, 0, 11),
	CDEF(182, 27, 12, 13, -11, 0, 11),
	CDEF(200, 13, 14, 13, -11, 0, 11),
	CDEF(222, 54, 5, 13, -11, 0, 11),
	CDEF(56, 52, 5, 16, -11, 0, 14),
	CDEF(230, 15, 13, 13, -11, 0, 11),
	CDEF(144, 35, 11, 13, -11, 0, 11),
	CDEF(48, 13, 18, 13, -11, 0, 11),
	CDEF(144, 13, 14, 13, -11, 0, 11),
	CDEF(54, 26, 12, 13, -11, 0, 11),
	CDEF(200, 26, 12, 13, -11, 0, 11),
	CDEF(240, 0, 14, 15, -11, 0, 13),
	CDEF(158, 13, 14, 13, -11, 0, 11),
	CDEF(156, 35, 11, 13, -11, 0, 11),
	CDEF(172, 13, 14, 13, -11, 0, 11),
	CDEF(98, 13, 15, 13, -11, 0, 11),
	CDEF(82, 13, 15, 13, -11, 0, 11),
	CDEF(24, 13, 23, 13, -11, 0, 11),
	CDEF(186, 13, 13, 14, -11, 0, 12),
	CDEF(114, 13, 15, 13, -11, 0, 11),
	CDEF(228, 28, 12, 13, -11, 0, 11),
	CDEF(62, 60, 6, 4, -4, 6, 9),
	CDEF(248, 59, 6, 4, -4, 6, 9),
	CDEF(88, 59, 8, 4, -4, 6, 9),
	CDEF(142, 60, 7, 3, -3, 7, 9),
	CDEF(120, 59, 8, 4, -4, 6, 9),
	CDEF(242, 59, 5, 5, -11, 0, 4),
	CDEF(98, 49, 11, 9, -7, 4, 11),
	CDEF(96, 35, 11, 14, -12, 0, 11),
	CDEF(72, 52, 9, 9, -7, 4, 11),
	CDEF(0, 39, 11, 12, -10, 1, 11),
	CDEF(164, 52, 9, 9, -7, 4, 11),
	CDEF(168, 38, 10, 14, -12, 0, 11),
	CDEF(120, 35, 12, 12, -7, 4, 14),
	CDEF(108, 35, 11, 14, -12, 0, 11),
	CDEF(194, 27, 6, 12, -10, 1, 11),
	CDEF(40, 51, 6, 16, -10, 1, 14),
	CDEF(28, 26, 12, 14, -12, 0, 11),
	CDEF(82, 52, 6, 13, -11, 0, 11),
	CDEF(96, 26, 18, 9, -7, 4, 11),
	CDEF(152, 48, 12, 9, -7, 4, 11),
	CDEF(62, 51, 10, 9, -7, 4, 11),
	CDEF(244, 15, 11, 13, -7, 4, 14),
	CDEF(52, 39, 10, 13, -7, 4, 14),
	CDEF(10, 52, 10, 9, -7, 4, 11),
	CDEF(190, 52, 9, 9, -7, 4, 11),
	CDEF(0, 51, 9, 11, -9, 2, 11),
	CDEF(178, 50, 11, 9, -7, 4, 11),
	CDEF(130, 48, 12, 9, -7, 4, 11),
	CDEF(132, 26, 18, 9, -7, 4, 11),
	CDEF(242, 50, 11, 9, -7, 4, 11),
	CDEF(40, 38, 11, 13, -7, 4, 14),
	CDEF(232, 41, 8, 9, -7, 4, 11),
	CDEF(222, 41, 9, 13, -7, 4, 14),
	CDEF(130, 57, 6, 9, -7, 4, 11),
	CDEF(194, 39, 10, 13, -10, 1, 12),
	CDEF(32, 56, 5, 12, -10, 1, 11),
	CDEF(0, 13, 24, 13, -10, 6, 11),
	CDEF(192, 0, 24, 13, -10, 6, 11),
	CDEF(168, 0, 24, 13, -10, 6, 11),
	CDEF(216, 0, 24, 13, -10, 6, 11),
	CDEF(150, 26, 18, 9, -8, 6, 11),
	CDEF(168, 26, 13, 12, -9, 6, 11),
	CDEF(114, 26, 18, 9, -8, 6, 11),
	CDEF(240, 28, 13, 12, -9, 6, 11),
	CDEF(0, 0, 41, 13, -10, 6, 11),
	CDEF(84, 0, 41, 13, -10, 6, 11),
	CDEF(42, 0, 41, 13, -10, 6, 11),
	CDEF(126, 0, 41, 13, -10, 6, 11)
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

void UpdatePulseColour()
{
	unsigned int localPulseCnt = PulseCnt = (++PulseCnt & 0x1F);
	if (localPulseCnt > 15)
	{
		localPulseCnt = -localPulseCnt;
	}

	for (int i = 0; i < 16; i++)
	{
		uint8_t r, g, b;
		r = g = b = localPulseCnt << 3;
		uint32_t c1, c2;
		CalcColorSplit(RGB_MAKE(r, g, b), &c1, &c2);

		c1 |= 0xFF000000;
		c2 |= 0xFF000000;

		FontShades[1][i].color.rgbcd = c1;
		FontShades[1][i].specular.rgbcd = c2;
	}
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

long ControlPhase(long nframes, int demo_mode)//1D538(<), 1D6CC(!) //DO NOT TOUCH (PSX/PSXPC)
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
				HairControl(0, false, nullptr);

				if (gfLevelFlags & GF_LVOP_YOUNG_LARA)
					HairControl(0, true, nullptr);
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
	struct FLOOR_INFO* floor; // $s0
	int val;

	if (SlowMotion)
	{
		SlowMotion--;

		if (SlowMoFrameCount < 40)
		{
			SlowMoFrameCount++;
		}

		//loc_1D5CC
		if (nframes < (SlowMoFrameCount >> 3))
		{
			do
			{
				VSync(0);
				nframes++;
			} while (nframes < (SlowMoFrameCount >> 3));
		}
	}
	else
	{
		//loc_1D5B4
		if (SlowMoFrameCount > 16)
		{
			SlowMoFrameCount--;

			if (nframes < (SlowMoFrameCount >> 3))
			{
				//loc_1D5E8
				do
				{
					VSync(0);
					nframes++;
				} while (nframes < (SlowMoFrameCount >> 3));
			}//loc_1D60C
		}//loc_1D618		
	}
	//loc_1D60C
	nframes = 2;
	GnLastFrameCount = 0;

	//loc_1D618
	RegeneratePickups();

	if (nframes > 10)
	{
		nframes = 10;
	}

	if (bTrackCamInit)
	{
		bUseSpotCam = 0;
	}
	//1D64C
	SetDebounce = 1;
	framecount += nframes;

	if (nframes <= 0)
	{
		return 0;
	}

	if (GLOBAL_enterinventory != -1)
	{
		return 0;
	}

	//loc_1D684
	do
	{
		GlobalCounter++;
		UpdateSky();
		S_UpdateInput();

		if (bDisableLaraControl)
		{
			if (gfCurrentLevel != LVL5_TITLE)
			{
				dbinput = 0;
			}//loc_1D6D4

			input &= IN_LOOK;

		}//loc_1D6EC

		if (cutseq_trig)
		{
			input = IN_NONE;
		}//loc_1D708

		SetDebounce = 0;

		if (gfLevelComplete)
		{
			return 3;
		}

		//v0 = reset_flag
		if (reset_flag)
		{
			reset_flag = 0;
			return 1;
		}

		if (lara.death_count > 90)
		{
			//loc_1D5A0
			reset_flag = 0;
			return S_Death();
		}

		if (!demo_mode)
		{
			//loc_1D7D4
			if (gfGameMode != 1 && Gameflow->DemoDisc)
			{
				if (input == IN_NONE)
				{
					if (Gameflow->InputTimeout < NoInput++)
					{
						return 1;
					}
				}
				else
				{
					//loc_1D844
					NoInput = 0;
				}
			}
		}
		else
		{
			if (!PadConnected && ScreenFading)
			{
				PrintString(SCREEN_WIDTH / 2, 230, 2, &gfStringWad[gfStringOffset[STR_DEMO_MODE]], (FF_CENTER | FF_BLINK));
			}

			//loc_1D7A0
			if (input == -1)
			{
				input = 0;
				Motors[1] = 0;
				Motors[0] = 0;
			}
		}

#if !BETA_VERSION
		//loc_1D9DC

		if (!(input & IN_PAUSE))
		{
			//v0 = PadConnected
			//a0 = InGameCnt
			
		}
		else
		{
			//loc_1DA3C
			Motors[0] = 0;
			Motors[1] = 0;
			return sub_62190();
		}
#endif

		//loc_1D848
		if (InGameCnt < 4)
		{
			InGameCnt++;
		}//loc_1D860

		if ((input & IN_LOOK) && !SniperCamActive && !bUseSpotCam && !bTrackCamInit)
		{
			if (lara_item->current_anim_state != 2 || lara_item->anim_number == 0x67)
			{
				//loc_1D8E0
				if (lara.IsDucked && (input & IN_DUCK) && lara_item->anim_number == 0xDE && lara_item->goal_anim_state == 0x47)
				{
					//loc_1D920
					if (BinocularRange == 0)
					{
						if (lara.gun_type == 5)
						{
							//loc_1D990
							if (lara.gun_status == 2)
							{
								BinocularRange = 128;
								LaserSight = 1;
								BinocularOldCamera = camera.old_type;
								lara.Busy = 1;
							}
						}
						else if (lara.gun_type == 6)
						{
							//loc_1D97C
							if ((lara.sixshooter_type_carried & 4))
							{
								//loc_1D990
								if (lara.gun_status == 4)
								{
									BinocularRange = 128;
									LaserSight = 1;
									BinocularOldCamera = camera.old_type;
									lara.Busy = 1;
								}
							}
						}
						else if (lara.gun_type == 2)
						{
							//loc_1D970
							if ((lara.crossbow_type_carried & 4))
							{
								//loc_1D990
								if (lara.gun_status == 4)
								{
									BinocularRange = 128;
									LaserSight = 1;
									BinocularOldCamera = camera.old_type;
									lara.Busy = 1;
								}
							}
						}
					}
				}
			}
		}
		else
		{
			//loc_1D9D0
			if (BinocularRange != 0)
			{
				if (LaserSight != 0)
				{
					BinocularRange = 0;
					LaserSight = 0;
					AlterFOV(0x3FFC);
					lara_item->mesh_bits = -1;
					camera.type = BinocularOldCamera;
					lara.head_y_rot = 0;
					lara.head_x_rot = 0;
					lara.torso_y_rot = 0;
					lara.torso_x_rot = 0;
					BinocularOn = -8;
					camera.bounce = 0;
					input &= IN_LOOK;
					lara.Busy = 0;
				}//loc_1DAC0
			}
			else
			{
				//loc_1DA80
				if (SniperCamActive != 0 || bUseSpotCam != 0 || !bTrackCamInit)
				{
					input &= 0xFFFFFDFF;
				}
			}
		}
		//loc_1DAC8
		if (BinocularRange != 0)
		{
			//loc_1DB28
			if (LaserSight != 0)
			{
				//loc_1DB28
				if ((gfLevelFlags & GF_LVOP_TRAIN))
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
				if ((gfLevelFlags & GF_LVOP_TRAIN) && (inputBusy & 0x40))
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
			//loc_1DB44
			InfraRed = 0;
		}

		ClearDynamics();
		ClearFires();

		item_num = next_item_active;
		GotLaraSpheres = 0;
		InItemControlLoop = 1;

		while (item_num != -1)
		{
			if (items[next_item_active].after_death < 128)
			{
				//loc_1DBB4
				if (objects[items[next_item_active].object_number].control != NULL)
				{
					objects[items[next_item_active].object_number].control(item_num);
				}
				//loc_1DBDC
			}
			else
			{
				KillItem(item_num);
			}
			//1DBE0
			item_num = items[next_item_active].next_active;
		}

		InItemControlLoop = 0;
		KillMoveItems();
		nex = next_fx_active;
		InItemControlLoop = 1;

		//loc_1DC10
		while (nex != -1)
		{
			if (objects[effects[nex].object_number].control != NULL)
			{
				objects[effects[nex].object_number].control(nex);
			}//loc_1DC54

			nex = effects[next_fx_active].next_active;
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

		if (SmokeCountR != 0)
		{
			SmokeCountR--;
		}

		//loc_1DCC0
		if (SplashCount != 0)
		{
			SplashCount--;
		}

		if (WeaponDelay != 0)
		{
			WeaponDelay--;
		}
		//loc_1DCF0
		if (lara.has_fired && !(wibble & 0x7F))
		{
			AlertNearbyGuards(lara_item);
			lara.has_fired = 0;
		}//loc_1DD40

		XSoff1 += 150;
		ZSoff1 += 660;
		YSoff1 += 230;

		XSoff2 += 270;
		YSoff2 += 440;
		ZSoff2 += 160;

		//loc_1DE84

		if (lara.poisoned && GLOBAL_playing_cutseq == 0)
		{
			if (lara.poisoned > 4096)
			{
				lara.poisoned = 4096;
			}
			else
			{
				if (lara.dpoisoned)
				{
					lara.dpoisoned--;
				}
			}

			//loc_1DDD4
			if ((gfLevelFlags & GF_LVOP_TRAIN) && !lara.Gassed)
			{
				if (lara.dpoisoned)
				{
					lara.dpoisoned -= 8;

					if (lara.dpoisoned < 0)
					{
						lara.dpoisoned = 0;
					}
				}//loc_1DE24
			}//loc_1DE24

			if (lara.poisoned > 255 && wibble == 0)
			{
				lara_item->hit_points -= lara.poisoned >> (8 - lara.Gassed);
				PoisonFlag = 16;
			}

		}
		//loc_1DE84
		//loc_1DE90
		lara.skelebob = 0;
		InItemControlLoop = 1;

		if (GLOBAL_playing_cutseq == 0 && gfGameMode == 0)
		{
			lara.Fired = 0;
			LaraControl(LARA);

			if (LaraDrawType == 5)
			{
#if !PSXPC_TEST
				((VOIDFUNCVOID*)RelocPtr[MOD_SUBSUIT][0])();
#endif
			}
			//loc_1DEF4
		}
		//loc_1DEF4
		InItemControlLoop = 0;

		KillMoveItems();

		if ((gfLevelFlags & GF_LVOP_TRAIN) && !bUseSpotCam)
		{
			if (room[lara_item->room_number].FlipNumber > 10)
			{
				InitialiseSpotCam(room[lara_item->room_number].FlipNumber);
				bUseSpotCam = 1;
			}
		}
		//loc_1DF7C
		if (GLOBAL_inventoryitemchosen != -1)
		{
			SayNo();
			GLOBAL_inventoryitemchosen = -1;
		}
		//loc_1DFA0
		if (GLOBAL_playing_cutseq == 0)
		{
			if (LaraDrawType != 5)
			{
				HairControl(0, 0, NULL);

				if ((gfLevelFlags & GF_LVOP_YOUNG_LARA))
				{
					HairControl(0, 1, NULL);
				}
			}//loc_1DFF4

			if (GLOBAL_playing_cutseq == 0)
			{
				if (bUseSpotCam)
				{
					CalculateSpotCams();
				}
				else
				{
					bTrackCamInit = 0;
					CalculateCamera();
				}
			}
			else
			{
				//loc_1E044
				camera.type = CINEMATIC_CAMERA;
			}
		}
		else
		{
			//loc_1E044
			camera.type = CINEMATIC_CAMERA;
			CalculateCamera();
		}

		//loc_1E054
		CamRot.vy = (mGetAngle(camera.pos.z, camera.pos.x, camera.target.z, camera.target.x) >> 4) & 0xFFF;
		wibble = (wibble + 4) & 0xFC;
		TriggerLaraDrips();

		if (SmashedMeshCount != 0)
		{
			//loc_1E0C0
			while (--SmashedMeshCount)
			{
				floor = GetFloor(SmashedMesh[SmashedMeshCount]->x, SmashedMesh[SmashedMeshCount]->y, SmashedMesh[SmashedMeshCount]->z, &SmashedMeshRoom[SmashedMeshCount]);
				GetHeight(floor, SmashedMesh[SmashedMeshCount]->x, SmashedMesh[SmashedMeshCount]->y, SmashedMesh[SmashedMeshCount]->z);
				TestTriggers(trigger_index, 1, 0);
				floor->stopper = 0;
				SmashedMesh[SmashedMeshCount] = NULL;
			}
		}//loc_1E15C

		///UpdateSparks();
		///UpdateFireSparks();
		///UpdateSmokeSparks();
		///UpdateBubbles();
		///UpdateSplashes();
		///UpdateDebris();
		///UpdateBlood();
		///UpdateDrips();
		///UpdateGunShells();

		if (RelocPtr[MOD_RAT] != NULL)
		{
			///((VOIDFUNCVOID*)RelocPtr[MOD_RAT][5])();
		}
		//loc_1E1C4
		if (RelocPtr[MOD_BAT] != NULL)
		{
			///((VOIDFUNCVOID*)RelocPtr[MOD_BAT][1])();
		}
		//loc_1E1E4
		if (RelocPtr[MOD_SPIDER] != NULL)
		{
			///((VOIDFUNCVOID*)RelocPtr[MOD_SPIDER][5])();
		}
		//loc_1E204
		///UpdateShockwaves();

		//loc_1E1E4
		if (RelocPtr[MOD_LIGHTNG] != NULL)
		{
			///((VOIDFUNCVOID*)RelocPtr[MOD_LIGHTNG][1])();
		}

		//loc_1E22C
		if (RelocPtr[MOD_TWOGUN] != NULL)
		{
			///((VOIDFUNCVOID*)RelocPtr[MOD_TWOGUN][2])();
		}
		//loc_1E24C
		AnimateWaterfalls();
		UpdatePulseColour();

		if (gfCurrentLevel == LVL5_SINKING_SUBMARINE)
		{
			///((VOIDFUNCVOID*)RelocPtr[MOD_JOBY5][0])();
		}
		//loc_1E288
		SoundEffects();
		health_bar_timer--;

		if (gfGameMode == 0)
		{
			//a1 = &savegame
			GameTimer++;
			if (savegame.Level.Timer != 0 && GLOBAL_playing_cutseq == 0)
			{
				savegame.Level.Timer++;
			}//loc_1E2F0
		}
		//loc_1E2F0
		VibratePad();

		if (Motors[0] == 0 && camera.bounce << 9 != 0)
		{
			val = camera.bounce << 9;
			if (camera.bounce < 0)
			{
				val = -val;
			}

			//loc_1E32C

			val += GetRandomControl() / val;
			if (0xFF00 < val)
			{
				val = 0xFF00;
			}

			//loc_1E360
			SetupPadVibration(1, 0x7F00, val, 8, val, 8);

		}//loc_1E384

		UpdateFadeClip();
		framecount -= 2;

		if (framecount <= 0)
		{
			return 0;
		}
	} while (GLOBAL_enterinventory == -1);

	//loc_1E3B8
	return 0;
#endif
}


void KillMoveItems()//1D420(<), 1D5B4(<) (F)
{
	short nex; // $v0
	int i = 0;

	if (ItemNewRoomNo > 0)
	{
		//loc_1D444
		do
		{
			if ((ItemNewRooms[i][0] & 0x8000))
			{
				KillItem((ItemNewRooms[i][0] & 0x7FFF));
				i++;
			}
			else
			{
				//loc_1D468
				ItemNewRoom(ItemNewRooms[i][0], ItemNewRooms[i][1]);
				i++;
			}
		} while (i < ItemNewRoomNo);
	}//loc_1D494

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

void TestTriggers(short* data, int heavy, int HeavyFlags)//1E9B4, 1EBC8(F)
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
long rand_2 = 0xD371F947;

#if PC_VERSION ///@FIXME remove, this needs to go in specific
long GetRandomControl()//5E9F0, 926F8 (F)
{
	rand_1 = (rand_1 * 0x41C64E6D) + 0x3039;
	return (rand_1 >> 16) & 0x7FFF;
}

void SeedRandomControl(long seed)//(F)
{
	rand_1 = seed;
}

long GetRandomDraw()//5EA18, 5F6F8 (F)
{
	rand_2 = (rand_2 * 0x41C64E6D) + 0x3039;
	return (rand_2 >> 16) * 0x7FFF;
}

void SeedRandomDraw(long seed)//(F)
{
	rand_2 = seed;
}
#endif

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

void NeatAndTidyTriggerCutscene(int value/*s0*/, int timer/*s1*/)
{
	//v0 = 0x41

	if (value == 0x41)
	{
		//v1 = lara_item
		if (lara_item->pos.y_pos < 0x3601)
		{
			if (have_i_got_object(0xDC))
			{
				gfLevelComplete = gfCurrentLevel + 1;
			}
		}//loc_215B8
	}
	else if((unsigned)(value - 0x1C) < 4)
	{
		//loc_20EE0
		//v1 = lara
		if (cutseq_trig == 0)
		{
			//v1 = Chris_Menu
			cutrot = timer & 3;

			//v0 = 0x1C
			if (Chris_Menu == 0)
			{
				//v0 = 0x1C
				if (dels_cutseq_selector_flag == 0)
				{
					cutseq_num = value;
					return;
				}
			}
			//loc_20F34
			//v0 = 0x1D
			if (value == 0x1C)
			{
				trigger_title_spotcam(2);
			}
			else if (value == 0x1D)
			{
				//loc_20F4C
				trigger_title_spotcam(3);
			}
			else if (value == 0x1E)
			{
				trigger_title_spotcam(4);
			}
			else if (value == 0x1F)
			{
				trigger_title_spotcam(1);
			}

			//loc_20F8C
			title_controls_locked_out = 0;
			return;
		}//loc_20FA0
	}
	//loc_20FA0
	//v1 = lara
	//s2 = a0
	if (!(lara.look))
	{
		if (value == 0x17)
		{
			if (cutseq_trig != 0)
			{
				return;
			}

			if (CheckCutPlayed(0x17))
			{
				richcutfrigflag = 1;
			}//loc_20FE8
		}
		//loc_20FE8

		if (cutseq_trig != 0)
		{
			return;
		}

		if (CheckCutPlayed(value))
		{
			return;
		}

		cutrot = timer & 3;

		//v0 = 0x2B
		if ((unsigned)(value - 5) < 0x3B)
		{
			//v0 = 0x27
			if (value == 0x2B)
			{
				if (cutrot != 1)
				{
					cutseq_num = value;
					return;
				}

				//v0 = lara_item
				if(!is_object_in_room(lara_item->room_number, 0x4F) || have_i_got_object(0xAD))
				{
					return;
				}

				cutseq_num = value;
				return;
			}
			else if (value == 0x27)
			{
				//loc_21070
				//v0 = input
				//v0 = lara
				//v0 = 0xD
				if ((input & IN_ACTION) && BinocularRange == 0 && lara.gun_status == 0 && lara_item->current_anim_state == 0xD && lara_item->anim_number == 0x6C && GLOBAL_inventoryitemchosen == -1 && have_i_got_object(0xAD) != 0)
				{
					//a0 = lara_item
					//v0 = 0x6C
					//v0 = -1
					GLOBAL_enterinventory = 0xAD;
					return;
				}
				//loc_21104

				//v0 = 0xAD
				//v1 = GLOBAL_inventoryitemchosen
				if (GLOBAL_inventoryitemchosen != 0xAD)
				{
					return;
				}
				else
				{
					GLOBAL_inventoryitemchosen = -1;
					return;
				}

			}//loc_21120
			else if (value == 0x26)
			{
				//v0 = 2
				//a0 = lara_item
				if ((input & IN_ACTION) && BinocularRange == 0 && lara.gun_status == 0 && lara_item->current_anim_state == 2 && lara_item->anim_number == 0x67)
				{
					//v0 = 0xAC
					if (GLOBAL_inventoryitemchosen == -1)
					{
						if (have_i_got_object(0xAC))
						{
							GLOBAL_enterinventory = 0xAC;
							return;
						}
					}//loc_211D0
				}
				else
				{
					//loc_211C4
					//v1 = GLOBAL_inventoryitemchosen
					if (GLOBAL_inventoryitemchosen == 0xAC)
					{
						GLOBAL_inventoryitemchosen = -1;
						cutseq_num = value;
						return;
					}
				}
			}
			//loc_211E0
			else if (value == 10)
			{
				if (have_i_got_object(0xAE))
				{
					SetCutPlayed(10);
					value = 9;
				}
			}

			if (value == 0x18)
			{
				//v1 = lara_item
				//a0 = lara_item->room_number
				if (room[lara_item->room_number].item_number != -1)
				{
					//t2 = 0x45
					//t1 = objects
					//t0 = -1
					//a3 = items
					//a2 = anims
					//a0 = room[lara_item->room_number].item_number

					//loc_21264
					//a0 = items[room[lara_item->room_number].item_number];
				}
				//loc_215B8
			}
			//loc_212D8
			//v0 = 0x14

		}//loc_214B0

	}
	//loc_215B8

#if 0
addu    $v0, $a0
sll     $v0, 4
addu    $a0, $a3, $v0
lh      $v1, 0xC($a0)
lh      $a1, 0x1A($a0)
bne     $v1, $t2, loc_212C4
nop
lh      $v0, 0x22($a0)
nop
blez    $v0, loc_212C4
nop
lh      $v0, 0x966($t1)
lh      $v1, 0x14($a0)
addiu   $v0, 0x3E
bne     $v1, $v0, loc_212C4
sll     $v0, $v1, 2
addu    $v0, $v1
sll     $v0, 3
addu    $v0, $a2
lh      $a0, 0x16($a0)
lh      $v1, 0x1A($v0)
nop
beq     $a0, $v1, loc_215B0
nop

loc_212C4:
move    $a0, $a1
bne     $a0, $t0, loc_21264
sll     $v0, $a0, 3
j       loc_215B8
nop

loc_212D8:
bne     $s0, $v0, loc_21398
li      $v0, 0xE
lw      $v0, dword_800A457C
nop
andi    $v0, 0x40
beqz    $v0, loc_2137C
nop
lw      $v0, dword_A0758
nop
bnez    $v0, loc_2137C
addiu   $v0, $s2, 0x57DC
lh      $v1, 2($v0)
nop
bnez    $v1, loc_2137C
li      $v0, 2
lw      $a0, dword_800A2048
nop
lh      $v1, 0xE($a0)
nop
bne     $v1, $v0, loc_2137C
li      $v0, 0x67
lh      $v1, 0x14($a0)
nop
bne     $v1, $v0, loc_2137C
li      $v0, 0xFFFFFFFF
lw      $v1, dword_A0B34
nop
bne     $v1, $v0, loc_21388
li      $v0, 0xCA
jal     sub_4086C
li      $a0, 0xCA
beqz    $v0, loc_2137C
li      $v0, 0xCA
sw      $v0, dword_A0B30
j       loc_215B8
nop

loc_2137C:
lw      $v1, dword_A0B34
li      $v0, 0xCA

loc_21388:
bne     $v1, $v0, loc_215B8
li      $v0, 0xFFFFFFFF
j       loc_215A8
nop

loc_21398:
bne     $s0, $v0, loc_21470
li      $v0, 0x17
lw      $v0, dword_800A457C
nop
andi    $v0, 0x40
beqz    $v0, loc_2143C
nop
lw      $v0, dword_A0758
nop
bnez    $v0, loc_2143C
addiu   $v0, $s2, 0x57DC
lh      $v1, 2($v0)
nop
bnez    $v1, loc_2143C
li      $v0, 2
lw      $a0, dword_800A2048
nop
lh      $v1, 0xE($a0)
nop
bne     $v1, $v0, loc_2143C
li      $v0, 0x67
lh      $v1, 0x14($a0)
nop
bne     $v1, $v0, loc_2143C
li      $v0, 0xFFFFFFFF
lw      $v1, dword_A0B34
nop
bne     $v1, $v0, loc_21448
li      $v0, 0xAD
jal     sub_4086C
li      $a0, 0xAD
beqz    $v0, loc_2143C
li      $v0, 0xAD

loc_2142C:
sw      $v0, dword_A0B30
j       loc_215B8
nop

loc_2143C:
lw      $v1, dword_A0B34
li      $v0, 0xAD

loc_21448:
bne     $v1, $v0, loc_215B8
li      $v0, 0xFFFFFFFF
sw      $v0, dword_A0B34
sw      $s0, dword_A09A8
jal     sub_4097C
li      $a0, 0xAD
j       loc_215B8
nop

loc_21470:
bne     $s0, $v0, loc_215B0
addiu   $v0, $s2, 0x57DC
lbu     $v1, 0x121($v0)
nop
beqz    $v1, loc_215B8
nop
jal     sub_21634
nop
bnez    $v0, loc_215B8
nop
lbu     $v0, 0xB0($gp)
nop
bnez    $v0, loc_215B8
nop
j       loc_215B0
nop

loc_214B0:
li      $a0, 2
bne     $s0, $a0, loc_214C0
li      $s1, 0xED
li      $s1, 0xF0

loc_214C0:
lw      $v0, dword_800A457C
nop
andi    $v0, 0x40
beqz    $v0, loc_2156C
nop
lw      $v0, dword_A0758
nop
bnez    $v0, loc_2156C
addiu   $v0, $s2, 0x57DC
lh      $v1, 2($v0)
nop
bnez    $v1, loc_2156C
nop
lw      $v1, dword_800A2048
nop
lh      $v0, 0xE($v1)
nop
bne     $v0, $a0, loc_2156C
li      $v0, 0x67
lh      $v1, 0x14($v1)
nop
bne     $v1, $v0, loc_2156C
li      $v0, 0xFFFFFFFF
lw      $v1, dword_A0B34
nop
bne     $v1, $v0, loc_2156C
nop
jal     sub_4086C
move    $a0, $s1
beqz    $v0, loc_2156C
nop
jal     sub_209AC
nop
beqz    $v0, loc_215B8
nop
sw      $s1, dword_A0B30
j       loc_215B8
nop

loc_2156C:
lw      $v0, dword_A0B34
nop
bne     $v0, $s1, loc_215B8
nop
jal     sub_209AC
nop
beqz    $v0, loc_215B8
li      $v0, 0xED
bne     $s1, $v0, loc_215A8
li      $v0, 0xFFFFFFFF
addiu   $v1, $s2, 0x57DC
li      $v0, 1
sb      $v0, 0x12A($v1)
li      $v0, 0xFFFFFFFF

loc_215A8:
sw      $v0, dword_A0B34

loc_215B0:
sw      $s0, dword_A09A8

loc_215B8:
lw      $ra, 0x20+var_4($sp)
lw      $s2, 0x20+var_8($sp)
lw      $s1, 0x20+var_C($sp)
lw      $s0, 0x20+var_10($sp)
jr      $ra
addiu   $sp, 0x20
#endif
	

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
				if (ABS(item->pos.x_pos - lara_item->pos.x_pos) < SECTOR(1) &&
					ABS(item->pos.z_pos - lara_item->pos.z_pos) < SECTOR(1) &&
					ABS(item->pos.y_pos - lara_item->pos.y_pos) < (int)SECTOR(0.25))
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
			SoundEffect(SFX_SMASH_METAL, &item->pos, SFX_DEFAULT);
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

void _TestTriggers(short* data, int heavy, int HeavyFlags)//1E9FC(<), 1EC10(<) (F)
{
#if PSXPC_TEST || PC_VERSION
	int key = 0;
#else
	int key;
#endif
	struct ITEM_INFO* item;
	struct ITEM_INFO* camera_item;
	short camera_timer;
	short type;
	short trigger;
	short value;
	short flags;
	char timer;
	char SwitchOnOnly;
	int switch_off;
	int flip;
	
#if PSXPC_TEST
	int flip_available = 0;
#else
	int flip_available;
#endif
	int neweffect = -1;
	int quad;
	short CamSeq;
	short lp;

	flip = -1;
	HeavyTriggered = 0;

	if (!heavy)
	{
		lara.climb_status = 0;
		lara.CanMonkeySwing = 0;
	}

	//loc_1EA6C
	if (data == NULL)
	{
		return;
	}

	if ((*data & 0x1F) == 5)
	{
		if (!heavy)
		{
			if (lara_item->pos.y_pos == lara_item->floor || lara.water_status != LW_ABOVE_WATER)
			{
				//loc_1EAC0
				LavaBurn(lara_item);
			}
		}

		//loc_1EAC8
		if ((*data++ & 0x8000))
		{
			return;
		}
	}
	//loc_1EADC
	if ((*data & 0x1F) == 6)
	{
		if (!heavy)
		{
			quad = ((lara_item->pos.y_rot + 0x2000) & 0xFFFF) >> 14;
			if ((*data >> (quad + 8)) & 1)
			{
				lara.climb_status = 1;
			}
		}
		//loc_1EB38
		if ((*data++ & 0x8000))
		{
			return;
		}
	}
	//loc_1EB4C
	if ((*data & 0x1F) == 19)
	{
		if (!heavy)
		{
			lara.CanMonkeySwing = 1;
		}

		//loc_1EB7C
		if ((*data++ & 0x8000))
		{
			return;
		}
	}
	//loc_1EB90
	if ((*data & 0x1F) == 20 && !(*data & 0x20))
	{
		if ((*data++ & 0x8000))
		{
			return;
		}
	}

	//loc_1EBB4
	type = ((*data++) >> 8) & 0x3F;
	flags = *data++;
	timer = flags;//FIXME says << 24 >> 24 but this gets optimised out

	if (camera.type != HEAVY_CAMERA)
	{
		RefreshCamera(type, data);
	}
	//loc_1EBF4
	SwitchOnOnly = 0;

	if (heavy)//fp
	{
		if (type != 10)//s2 != v0
		{
			if (type > 10)
			{
				return;
			}

			if(type != 5)
			{
				//loc_1EC20
				return;
			}
		}
		else
		{
			//loc_1EC34
			if (HeavyFlags != 0)
			{
				if (HeavyFlags < 0)
				{
					flags = (flags | 0x3E00) + HeavyFlags;
				}
				else
				{
					//loc_1EC64
					//v1 = HeavyFlags
					if ((flags & 0x3E00) != HeavyFlags)
					{
						return;
					}
				}
			}
			else
			{
				//loc_1F7A4
				return;
			}
		}
	}
	else
	{
		//loc_1EC7C
		switch (type)
		{
		case PAD:
		case ANTIPAD:
		{
			//loc_1EE94
			if (lara_item->pos.y_pos != lara_item->floor)
			{
				return;
			}

			break;
		}
		case SWITCH:
			//loc_1ECA8
			value = (*data++) & 0x3FF;
			if ((flags & 0x100))
			{
				items[value].item_flags[0] = 1;
			}

			//loc_1ECD8
			if (!SwitchTrigger(value, timer))
			{
				return;
			}

			if (items[value].object_number >= SWITCH_TYPE1 && items[value].object_number <= SWITCH_TYPE6 && items[value].trigger_flags == 5)
			{
				SwitchOnOnly = 1;
			}

			//loc_1ED2C
			switch_off = items[value].current_anim_state = items[value].current_anim_state == 1;
			switch_off = 1;
			break;
		case KEY:
			//loc_1EEBC
			key = KeyTrigger((*data++) & 0x3FF);
			if (key == -1)
			{
				return;
			}
			break;
		case PICKUP:
			//loc_1EEE8
			if (!PickupTrigger((*data++) & 0x3FF))
			{
				return;
			}
			break;
		case COMBAT:
		{
			//loc_1EF08
			if (lara.gun_status != LG_READY)
			{
				return;
			}
			//j loc_1EF34
			break;
		}
		case ANTITRIGGER:
			//def_1ECA0
			break;
		case HEAVY:
		case DUMMY:
		case HEAVYSWITCH:
		case HEAVYANTITRIGGER:
			//loc_1F7A4
			return;
			break;
		case MONKEY:
		{
			//loc_1ED50
			if ((lara_item->current_anim_state >= ANIMATION_LARA_JUMP_BACK &&
			     lara_item->current_anim_state <= ANIMATION_LARA_JUMP_LEFT) ||
			    lara_item->current_anim_state == ANIMATION_LARA_LANDING_MIDDLE ||
			    lara_item->current_anim_state == ANIMATION_LARA_FORWARD_TO_FREE_FALL
				)
				break;
			return;
		}
		case SKELETON_T:
		{
			//loc_1EF24
			lara.skelebob = 2;
			break;
		}
		case TIGHTROPE_T:
		{
			//loc_1ED90
			if (lara_item->current_anim_state >= ANIMATION_LARA_FREE_FALL_TO_UNDERWATER_ALTERNATE &&
			    lara_item->current_anim_state <= ANIMATION_LARA_AH_LEFT &&
			    lara_item->current_anim_state != ANIMATION_LARA_AH_BACKWARD)
				break;
			return;
		}
		case CRAWLDUCK_T:
		{
			//loc_1EDCC
			if (lara_item->current_anim_state == ANIMATION_LARA_JUMP_RIGHT_BEGIN ||
			    lara_item->current_anim_state == ANIMATION_LARA_JUMP_RIGHT ||
			    lara_item->current_anim_state == ANIMATION_LARA_LEFT_TO_FREE_FALL ||
			    lara_item->current_anim_state == ANIMATION_LARA_RIGHT_TO_FREE_FALL ||
			    lara_item->current_anim_state == ANIMATION_LARA_UNDERWATER_SWIM_FORWARD ||
			    lara_item->current_anim_state == ANIMATION_LARA_SLIDE_FORWARD_END ||
			    lara_item->current_anim_state == ANIMATION_LARA_SLIDE_FORWARD_STOP ||
			    lara_item->current_anim_state == ANIMATION_LARA_SLIDE_BACKWARD ||
			    lara_item->current_anim_state == ANIMATION_LARA_SLIDE_BACKWARD_END)
				break;

			return;
		}
		case CLIMB_T:
			//loc_1EE38

			if (lara_item->current_anim_state == ANIMATION_LARA_RUN_TO_STAY_RIGHT ||
			    lara_item->current_anim_state == ANIMATION_LARA_RUN_UP_STEP_LEFT ||
			    lara_item->current_anim_state == ANIMATION_LARA_WALK_UP_STEP_RIGHT ||
			    lara_item->current_anim_state == ANIMATION_LARA_WALK_UP_STEP_LEFT ||
			    lara_item->current_anim_state == ANIMATION_LARA_WALK_DOWN_LEFT ||
			    lara_item->current_anim_state == ANIMATION_LARA_WALK_DOWN_RIGHT ||
			    lara_item->current_anim_state == ANIMATION_LARA_WALK_DOWN_BACK_LEFT ||
			    lara_item->current_anim_state == ANIMATION_LARA_JUMP_BACK)
				break;
			return;

		}
	}
	//def_1ECA0
	camera_item = NULL;

	//loc_1EF34
	do
	{
		trigger = *data++;
		value = trigger & 0x3FF;

		switch ((trigger & 0x3FFF) >> 10)
		{
		case TO_OBJECT:
		{
			//loc_1EF70
			item = &items[value];
			if (key < 2)
			{
				if (type == ANTIPAD || type == ANTITRIGGER || type == HEAVYANTITRIGGER && (item->flags & IFLAG_CLEAR_BODY))
				{
					break;
				}

				//loc_1EFC8
				if (type == SWITCH && (item->flags & IFLAG_UNK40))
				{
					break;
				}

				//loc_1EFDC
				if (type != ANTIPAD && type != ANTITRIGGER && type != HEAVYANTITRIGGER && (item->flags & 0x100))
				{
					break;
				}

				//loc_1F010
				if (type != ANTIPAD && type != ANTITRIGGER && type != HEAVYANTITRIGGER && item->object_number == DART_EMITTER && item->active)
				{
					break;
				}

				//loc_1F04C
				///@FIXME sh s6, 26(s0) (s0 = item?)
				if (timer != 1)
				{
					item->timer *= 30;
				}//loc_1F068


				if (type == SWITCH || type == HEAVYSWITCH)
				{
					//loc_1F07C
					if (HeavyFlags < 0)
					{
						if (((item->flags ^ (flags & 0x3E00)) & 0x3E00) == 0x3E00 && (flags & 0x100))
						{
							item->flags |= IFLAG_UNK40;
						}//loc_1F1BC
					}
					else
					{
						//loc_1F0B8
						if (SwitchOnOnly)
						{
							item->flags |= (flags & 0x3E00);
						}
						else
						{
							//loc_1F0D4
							item->flags ^= (flags & 0x3E00);
						}
						//loc_1F0E0
						if ((flags & 0x100))
						{
							item->flags |= IFLAG_UNK40;
						}
					}
				}
				else
				{
					//loc_1F0FC
					if (type == 6 || type == 9 || type == 11)
					{
						//loc_1F114
						if (item->object_number == EARTHQUAKE)
						{
							item->item_flags[0] = 0;
							item->item_flags[1] = 100;
						}
						//loc_1F12C
						item->flags &= 0x81FF;

						if ((flags & 0x100))
						{
							item->flags |= 0x80;
						}//loc_1F14C

						if (item->active)
						{
							if (objects[item->object_number].intelligent)
							{
								item->hit_points = 0x3FFF;
								DisableBaddieAI(value);
								KillItem(value);
							}//loc_1F1BC
						}//loc_1F1BC
					}
					else
					{
						//loc_1F1A4
						if ((flags & 0x3E00))
						{
							item->flags |= (flags & 0x3E00);
						}
						//loc_1F1BC
					}
				}
				//loc_1F1B8
				if ((item->flags & 0x3E00) == 0x3E00)
				{
					item->flags |= 0x20;
					if ((flags & 0x100))
					{
						item->flags = (item->flags & 0x3E00) | 0x100;
					}//loc_1F1E8

					if (!item->active)
					{
						if (objects[item->object_number].intelligent)
						{
							if (!(item->status))
							{
								item->gravity_status = 0;
								item->status = 1;
								item->touch_bits = 0;
								AddActiveItem(value);
								EnableBaddieAI(value, 1);
							}//loc_1F264
							else if (item->status == 3)
							{
								item->touch_bits = 0;
								if (EnableBaddieAI(value, 0))
								{
									item->status = 1;
								}
								else
								{
									//loc_1F298
									item->status = 2;
								}
								//loc_1F2A4
								AddActiveItem(value);
							}//loc_1F720
						}
						else
						{
							//loc_1F2B8
							item->touch_bits = 0;
							AddActiveItem(value);
							item->status = 1;
							HeavyTriggered = heavy;
						}
					}//loc_1F720
				}//loc_1F720
			}//def_1EF68
			break;
		}
		case TO_CAMERA:
		{
			//loc_1F2E4
			trigger = *data++;
			camera_timer = trigger & 0xFF;
			if (key != trigger)
			{
				if (!(camera.fixed[value].flags & 0x100))
				{
					camera.number = value;

					if (camera.type == FIXED_CAMERA || camera.type == CHASE_CAMERA && (camera.fixed[value].flags & 3))
					{
						break;
					}//loc_1F35C

					if (type != COMBAT && type != SWITCH || timer == 0 || switch_off == 0)
					{
						if (camera.number != camera.last || type == SWITCH)
						{
							camera.timer = 30 * camera_timer;
							if ((trigger & 0x100))
							{
								camera.fixed[CamSeq].flags |= 0x100;
							}//loc_1F3F0

							camera.speed = ((trigger & 0x3E00) >> 6) + 1;
							camera.type = heavy ? HEAVY_CAMERA : FIXED_CAMERA;
						}
					}

				}//loc_1F720
			}//def_1EF68
			break;
		}
		case TO_SINK:
		{
			//loc_1F564
			lara.current_active = value + 1;
			break;
		}
		case TO_FLIPMAP:
		{
			//loc_1F574
			flip_available = 1;

			if (!(flipmap[value] & 0x100))
			{
				if (type == 2)
				{
					flipmap[value] ^= (flags & 0x3E00);
				}
				else if ((flags & 0x3E00))
				{

					flipmap[value] |= (flags & 0x3E00);
				}
				//loc_1F5B8
				if ((flipmap[value] & 0x3E00) == 0x3E00)
				{
					if ((flags & 0x100))
					{
						flipmap[value] |= 0x100;
					}
					//loc_1F5E8
					if (!(flip_stats[value]))
					{
						flip = value;
					}
				}
				else
				{
					//loc_1F60C
					if (flip_stats[value] != 0)
					{
						flip = value;
					}
				}
			}//def_1EF68
			break;
		}
		case TO_FLIPON:
		{
			//loc_1F62C
			flip_available = 1;
			if (flip_stats[value] == 0)
			{
				flipmap[value] |= 0x3E00;
			}
			flip = value;
			break;
		}
		case TO_FLIPOFF:
		{
			//loc_1F66C
			flip_available = 1;
			if (flip_stats[value] != 0)
			{
				flipmap[value] &= 0xC1FF;
				flip = value;
			}
			break;
		}
		case TO_TARGET:
		{
			//loc_1F548
			camera_item = &items[value];
			break;
		}
		case TO_FINISH:
		{
			//loc_1F6CC
			gfRequiredStartPos = 0;
			gfLevelComplete = gfCurrentLevel + 1;
			break;
		}
		case TO_CD:
		{
			//loc_1F6F0
			TriggerCDTrack(value, flags, type);
			break;
		}
		case TO_FLIPEFFECT:
		{
			//loc_1F6B0
			TriggerTimer = timer;
			neweffect = value;
			break;
		}
		case TO_SECRET:
		{
			//def_1EF68
			break;
		}
		case TO_BODYBAG:
		{
			//loc_1F6BC
			ResetGuards();
			break;
		}
		case TO_FLYBY:
		{
			//loc_1F430
			trigger = *data++;

			if (trigger != key)
			{
				lp = 0;
				if (type == ANTIPAD || type == ANTITRIGGER || type == HEAVYANTITRIGGER)
				{
					//loc_1F460
					bUseSpotCam = 0;
				}
				else
				{
					CamSeq = 0;

					if (SpotRemap[value] != 0)
					{
						for (lp = 0; lp < SpotRemap[value]; lp++)
						{
							CamSeq += CameraCnt[lp];
						}
					}
					//loc_1F4CC
					if (!(SpotCam[CamSeq].flags & SCF_CAMERA_ONE_SHOT))
					{
						if ((trigger & 0x100))
						{
							SpotCam[CamSeq].flags |= SCF_CAMERA_ONE_SHOT;
						}
						//loc_1F500
						if (bUseSpotCam == 0)
						{
							bUseSpotCam = 1;

							if (LastSequence != value)
							{
								bTrackCamInit = 0;
							}//loc_1F538
							InitialiseSpotCam(value);
						}//loc_1F720
					}//loc_1F720
				}//loc_1F720
			}//def_1EF68
			break;
		}
		case TO_CUTSCENE:
		{
			//loc_1F708
			globoncuttrig = 1;
			NeatAndTidyTriggerCutscene(value, timer);
			break;
		}
		}
	} while (!(trigger & 0x8000));
	//def_1EF68
	//loc_1F720

	if (camera_item != NULL && (camera.type == FIXED_CAMERA || camera.type == HEAVY_CAMERA))
	{
		camera.item = camera_item;
	}
	//loc_1F760
	if (flip != -1)
	{
		FlipMap(flip);
	}
	//loc_1F774
	if (neweffect != -1 && (flip == 0 || flip_available == 0))
	{
		fliptimer = 0;
		flipeffect = neweffect;
	}//loc_1F7A4
}

void RefreshCamera(short type, short* data)//1E7FC, ? (F)
{
	short trigger;
	short value;
	short target_ok;

	target_ok = 2;

	//loc_1E814
	do
	{
		trigger = *data++;
		value = trigger & 0x3FF;

		if ((trigger & 0x3FFF) >> 10 == 1)
		{
			//loc_1E840
			data++;
			if (value == camera.last)
			{
				camera.number = value;

				if (camera.timer < 0)
				{
					//loc_1E894
					camera.timer = -1;
				}
				else if (camera.type == LOOK_CAMERA || camera.fixed[value].flags & 3)
				{
					//loc_1E8A4
					camera.type = FIXED_CAMERA;
					target_ok = 1;
				}
				else
				{
					camera.timer = -1;
				}
			}
			else
			{
				//loc_1E89C
				target_ok = 0;
			}
		}
		else if ((trigger & 0x3FFF) >> 10 == 6)
		{
			//loc_1E8B4
			if (camera.type == LOOK_CAMERA || camera.number == -1 || camera.fixed[camera.number].flags & 3)
			{
				camera.item = &items[value];
			}
		}
	} while (!(trigger & 0x8000));

	//loc_1E91C
	if (camera.item != NULL)
	{
		if (!target_ok || target_ok == 2 || camera.item->looked_at || camera.item != camera.last_item)
		{
			camera.item = NULL;
		}
	}//loc_1E97C

	if (camera.number == -1 && camera.timer > 0)
	{
		camera.timer = camera.number;
	}
}

long GetWaterHeight(long x, long y, long z, short room_number)
{
	long x_floor;
	long y_floor;
	struct room_info* r;
	struct FLOOR_INFO* floor;
	/*short*/ unsigned char data;


	//loc_1E570
	r = &room[room_number];

	do
	{	
		x_floor = (z - r->z) >> 10;
		y_floor = (x - r->x) >> 10;

		if (x_floor <= 0)
		{
			x_floor = 0;

			if (y_floor <= 0)
			{
				y_floor = 1;
			}
			else
			{
				//loc_1E5A4
				if ((r->y_size - 2) < y_floor)
				{
					y_floor = r->y_size - 2;
				}
			}
		}
		//loc_1E5C4
		if (x_floor >= (r->x_size - 1))
		{
			x_floor = r->x_size - 1;
			if (y_floor <= 0)
			{
				y_floor = 1;
			}
			else if ((r->y_size - 2) < y_floor)
			{
				y_floor = r->y_size - 2;
			}
		}
		else
		{
			//loc_1E60C
			if (y_floor <= 0)
			{
				y_floor = 0;
			}//loc_1E61C
			else if ((y_floor >= r->y_size))
			{
				y_floor = r->y_size - 1;
			}
		}
		//loc_1E634
		floor = &r->floor[x_floor + (y_floor * r->x_size)];
		data = GetDoor(floor);

		if (data == 255)
			break;

		r = &room[data];

	} while (TRUE);

	//loc_1E680

	if ((r->flags & RF_FILL_WATER))
	{
		//loc_1E704
		do
		{
			if (floor->sky_room != 0xFF)
			{
				if (CheckNoColCeilingTriangle(floor, x, z) == 1)
				{
					break;
				}

				//loc_1E69C
				r = &room[floor->sky_room];

				if ((r->flags & RF_FILL_WATER))
				{
					floor = &r->floor[(((x - r->x) >> 10) * r->x_size) + ((z - r->z) >> 10)];
				}
				else
				{
					//loc_1E734
					return r->minfloor;
				}
			}
			else
			{
				break;
			}

		} while (TRUE);

		//loc_1E740
		return r->y;
	}
	else
	{
		//loc_1E7B4
		while (floor->pit_room != 0xFF)
		{
			if (CheckNoColFloorTriangle(floor, x, z) == 1)
				break;

			//loc_1E74C
			r = &room[floor->pit_room];

			if ((r->flags & 1))
			{
				return r->y;
			}

			floor = &r->floor[((z - r->z) >> 10) + ((x - r->x) >> 10) * r->x_size];
		}
	}

	return BAD_HEIGHT;
}

void AlterFloorHeight(struct ITEM_INFO* item, int height)//1E3E4(<), 1E5F8(<) (F)
{
	struct FLOOR_INFO* floor;
	struct FLOOR_INFO* ceiling;
	short room_num;
	short joby;

	joby = 0;

	if (ABS(height) & 0xFF)
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

#if PC_VERSION
void GH_adjust_height(int a1, int s4, short* t7, int a2, int s3)
{
	int v0;

	v0 = s4 & 0x3FF;
	if (a1 < 0)
	{
		v0 = (v0 * a1) >> 2;
		*t7 -= v0;
	}
	else
	{
		//loc_79008
		v0 = 0x3FF;
		v0 -= s4;
		v0 &= 0x3FF;
		v0 *= a1;
		v0 >>= 2;
		*t7 += v0;
	}

	//loc_79024
	v0 = s3 & 0x3FF;
	if (a2 < 0)
	{
		v0 = (v0 * a2) >> 2;
		*t7 -= v0;
		return;
	}//loc_79040

	v0 = 0x3FF;
	v0 -= s3;
	v0 &= 0x3FF;
	v0 = (v0 * a2) >> 2;
	*t7 += v0;
}

short GetHeight(struct FLOOR_INFO* floor, int x, int y, int z)//78C74(<), 7ACB8(<) (F)
{
	struct room_info* r;//$a0
	struct FLOOR_INFO* f;//$s0
	unsigned short* fd;//$s1
	unsigned short value;//$s2
	short ret;//$t7 @ret
	unsigned short trigger_value;//$s0
	struct ITEM_INFO* item;//$a0
	struct object_info* object;//$v0
	int height;
	unsigned short v1;//$v1

	//s0 = floor
	//s3 = x
	OnObject = 0;
	height_type = 0;
	tiltyoff = 0;
	tiltxoff = 0;
	//s4 = z
	f = floor;

	//loc_78CB4
	while (f->pit_room != 0xFF)
	{
		if (CheckNoColFloorTriangle(f, x, z) == 1)
			break;//loc_78D28

		r = &room[f->pit_room];
		f = &r->floor[((z - r->z) >> 10) + (((x - r->x) >> 10) * r->x_size)];
	}

	//loc_78D28
	ret = f->floor << 8;
	//v0 = -32512

	if ((f->floor << 8) == -32512)
	{
		return ret;
	}

	//v1 = f->index
	//v1 <<= 1;
	trigger_index = NULL;

	if (f->index == 0)
	{
		return ret;
	}

	fd = (unsigned short*)&floor_data[f->index];

	//loc_78D60
	do
	{
		value = *fd++;

		//v0 = value & 0x1F
		//v1 = v0 - 1
		//v0 = v1 < 0x15 ? 1 : 0
		//v0 = v1 << 2

		switch ((value & 0x1F))
		{
		case DOOR_TYPE:
		case ROOF_TYPE:
		case SPLIT3:
		case SPLIT4:
		case NOCOLC1T:
		case NOCOLC1B:
		case NOCOLC2T:
		case NOCOLC2B://COMPLETE
		{
			//loc_78EEC
			fd++;
			break;
		}
		case TILT_TYPE://COMPLETE
		{
			//loc_78EA0
			char a1 = ((char*)fd)[1];
			char a2 = ((char*)fd)[0];

			//loc_78EB4
			tiltxoff = a1;
			tiltyoff = a2;

			if (ABS(a1) < 3)
			{
				if (ABS(a2) < 3)
				{
					height_type = 1;
					GH_adjust_height(a1, z, &ret, a2, x);
				}
				else
				{
					height_type = 2;
					GH_adjust_height(a1, z, &ret, a2, x);
				}
			}
			else
			{
				//loc_78EE4
				height_type = 2;
				GH_adjust_height(a1, z, &ret, a2, x);
			}
			fd++;
			break;
		}
		case TRIGGER_TYPE://COMPLETE
		{
			//loc_78F0C
			fd++;

			if (trigger_index == 0)
			{
				trigger_index = (short*)&fd[-2];
			}
			//loc_78F20
			do
			{
				trigger_value = *fd++;

				if (((trigger_value & 0x3FFF) >> 10) == 0xC || ((trigger_value & 0x3FFF) >> 10) == 0x1)
				{
					trigger_value = *fd++;
					continue;
				}
				//loc_78F54
				item = &items[trigger_value & 0x3FF];

				if (!(item->flags & 0x8000))
				{
					object = &objects[item->object_number];

					if (object->floor != NULL)
					{
						object->floor(item, x, y, z, &height);
					}//loc_78FB8
				}//loc_78FB8
			} while (!(trigger_value & 0x8000));
			break;
		}
		case LAVA_TYPE://COMPLETE
		{
			//loc_78F00
			trigger_index = (short*)--fd;
			break;
		}
		case CLIMB_TYPE:
		case MONKEY_TYPE:
		case TRIGTRIGGER_TYPE:
		case MINER_TYPE://COMPLETE
		{
			//loc_78EF4
			if (trigger_index == NULL)
			{
				trigger_index = (short*)&fd[-1];
			}
			break;
		}
		case SPLIT1:
		case SPLIT2:
		case NOCOLF1T:
		case NOCOLF1B:
		case NOCOLF2T:
		case NOCOLF2B:
		{
			//loc_78D94
			//v0 = 4
			v1 = *fd;
			//a0 = value & 0x1F;
			height_type = 4;
			int t0 = v1 & 0xF;
			int a3 = (v1 >> 4) & 0xF;
			int a2 = (v1 >> 8) & 0xF;
			int t1 = z & 0x3FF;
			int t2 = x & 0x3FF;
			//v0 = 7
			int a1;
			int v0;

			v1 >>= 12;
			if ((value & 0x1F) == 7 || (unsigned)((value & 0x1F) - 11) < 2)
			{
				//loc_78DD8
				v0 = value >> 10;
				if (0x400 - t1 < t2)
				{
					//loc_78DF8
					v0 = value >> 5;
					a1 = v1 - t0;
					a2 = v1 - a2;
					//j loc_78E2C
				}
				else
				{
					//loc_78DF8
					a1 = a2 - a3;
					a2 = t0 - a3;
					//j loc_78E2C
				}
			}
			else
			{
				//loc_78E08
				v0 = value >> 10;
				if (t1 < t2)
				{
					v0 = value >> 5;
					a1 = v1 - t0;
					a2 = t0 - a3;
				}
				else
				{
					//loc_78E20
					a1 = a2 - a3;
					a2 = v1 - a2;
					//j       loc_78E2C
				}
			}

			//loc_78E2C
			tiltxoff = a1;
			tiltyoff = a2;

			v0 &= 0x1F;

			int at = -16;
			if ((v0 & 0x10))
			{
				v0 |= at;
			}
			//loc_78E48
			v0 <<= 8;
			ret += v0;

			if (ABS(a1) >= 3)
			{
				//loc_78E90
				height_type = 3;
			}
			else if(ABS(a2) >= 3)
			{
				//loc_78E90
				height_type = 3;
			}
			else if (height_type != 4)
			{
				height_type = 1;
			}

			//loc_78E94
			fd++;
			GH_adjust_height(a1, z, &ret, a2, x);
			break;
		}
		default:
			Error("GetHeight(): Unknown type");
			break;
		}

		//loc_78FC0
	} while (!(value & 0x8000));

	return ret;
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
		if (y < floor->ceiling << 8 && floor->sky_room != 0xFF)
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
			floor = &r->floor[tmp];
			if (y < r->floor[tmp].floor << 8)
				break;
			if (floor->pit_room == 0xFF)
				return &r->floor[tmp];
		}
	}

	return floor;
}


void GC_adjust_height(unsigned short a0, char a1, char a2, int t4, int t5, int* t7/*ret*/)
{
	int v0;

	v0 = t5 & 0x3FF;
	if (a1 < 0)
	{
		v0 = (v0 * a1) >> 2;
		*t7 += v0;
	}
	else
	{
		//loc_79408
		v0 = 0x3FF;
		v0 -= t5;
		v0 &= 0x3FF;
		v0 = (v0 * a1) >> 2;
		*t7 -= v0;
	}

	//loc_79424
	v0 = 0x3FF;
	if (a2 < 0)
	{
		v0 -= t4;
		v0 &= 0x3FF;
		v0 = (v0 * a2) >> 2;
		*t7 += v0;
		return;
	}
	//loc_79448
	v0 = t4 & 0x3FF;
	v0 = (v0 * a2) >> 2;
	*t7 -= v0;
	return;
}

short GetCeiling(struct FLOOR_INFO* floor, int x, int y, int z)
{
	struct room_info* r;//$a0
	struct FLOOR_INFO* f;//$s0
	unsigned short* fd;//$s0
	unsigned short a0;
	unsigned short v1;
	int a1;
	int a2;
	int t7;
	//s1 = floor
	//t4 = x
	//t5 = z
	f = floor;

	//loc_790F0
	while (f->sky_room != 0xFF)
	{
		//loc_7908C
		if (CheckNoColCeilingTriangle(f, x, z) == 1)
		{
			break;
		}

		r = &room[f->sky_room];
		f = &r->floor[((z - r->z) >> 10) + (((x - r->x) >> 10) * r->x_size)];
	}
	//loc_79100
	t7 = f->ceiling << 8;
	//v1 = f->index << 1
	//v0 = -32512

	if ((f->ceiling << 8) != -32512)
	{
		if(f->index != 0)
		{
			//s0 = floor_data
			//v0 = 2
			fd = (unsigned short*)&floor_data[f->index];
			a0 = *fd++;
			if ((unsigned)(a0 & 0x1F) == 2 || (unsigned)((a0 & 0x1F) - 7) < 2 || (unsigned)((a0 & 0x1F) - 11) < 4)
			{
				//loc_79154
				if (((a0 & 0x8000) << 10) != 0)
				{
					a0 = fd[1];
					fd += 2;
					//s2 = a0 & 0x1F
					///goto loc_792BC;
				}
				else
				{
					a0 = fd[1];
					fd += 2;
					//s2 = a0 & 0x1F
				}
			}
			//loc_7916C
			if ((a0 & 0x1F) == 3)
			{
				//loc_7924C
				//Below todo pass as args
				///lb      $a1, 1($s0)
				///j       loc_79244
				///lb      $a2, 0($s0)
				GC_adjust_height(a0, ((char*)fd)[1], ((char*)fd)[0], x, z, &t7);
				//j loc_792BC
			}
			else if ((unsigned)((a0 & 0x1F) - 9) < 2 || (unsigned)((a0 & 0x1F) - 15) < 4)
			{
				//loc_7918C
				//a2 = x & 0x3FF
				v1 = fd[0];
				//a1 = z & 0x3FF
				//t1 = -(fd[0] & 0xF)
				//t0 = -((fd[0] >> 4) & 0xF);
				//a3 = -((fd[0] >> 8) & 0xF);
				//v1 = -(fd[0] >> 12);
				//v0 = 9

				if ((a0 & 0x1F) == 9 || (a0 & 0x1F) - 15  < 2)
				{
					//loc_791D4
					//v0 = (1024 - (z & 1023));
					if ((1024 - (z & 1023)) < (x & 1023))
					{
						//loc_791F8
						a0 >>= 5;
						a1 = -(fd[0] >> 12) - -(fd[0] & 0xF);
						a2 = -(fd[0] & 0xF) - -((fd[0] >> 4) & 0xF);
						//j       loc_79228
					}
					else
					{
						//loc_791F8
						a0 >>= 10;
						a1 = -((fd[0] >> 8) & 0xF) - -((fd[0] >> 4) & 0xF);
						a2 = -(fd[0] >> 12) - -((fd[0] >> 8) & 0xF);
						//j       loc_79228
					}
				}//loc_79204
				else if ((z & 0x3FF) < (x & 0x3FF))
				{
					//loc_79220
					a0 >>= 5;
					a1 = -(fd[0] >> 12) - -(fd[0] & 0xF);
					a2 = -(fd[0] >> 12) - -((fd[0] >> 8) & 0xF);
				}
				else
				{
					a0 >>= 10;
					a1 = -((fd[0] >> 8) & 0xF) - -((fd[0] >> 4) & 0xF);
					a2 = -(fd[0] & 0xF) - -((fd[0] >> 4) & 0xF);
				}
				//loc_79228
				a0 &= 0x1F;

				if ((a0 & 0x10))
				{
					a0 |= -0x10;
				}
				//loc_7923C
				a0 <<= 8;
				t7 += a0;

				GC_adjust_height(a0, a1, a2, x, z, &t7);
				//j loc_792BC
			}
		}
		//loc_792BC
		//v1 = floor->pit_room
		f = floor;
		while (f->pit_room != 0xFF)
		{
			//loc_79258
			if (CheckNoColFloorTriangle(f, x, z) == 1)
			{
				break;
			}

			r = &room[f->pit_room];
			f = &r->floor[((z - r->z) >> 10) + ((x - r->x) >> 10) * r->x_size];
		}
		//loc_792CC
		//v0 = floor->index
		//v1 = floor_data
		if (floor->index == 0)
		{
			return t7;
		}

		fd = (unsigned short*)&floor_data[floor->index];

	loc_792E0:
		unsigned short s2 = *fd++;
		unsigned short v0 = (s2) & 0x1F;
		unsigned short s1;

		switch (v0)
		{
		case 1:
		case 2:
		case 3:
		case 7:
		case 8:
		case 9:
		case 10:
		case 11:
		case 12:
		case 13:
		case 14:
		case 15:
		case 16:
		case 17:
		case 18:
			//loc_79314
			fd++;
			goto loc_793C8;
			break;
		case 4:
			//loc_79318
			fd++;
		loc_7931C:
			s1 = *fd++;
			v0 = s1 & 0x3FFF;

			//v0 = 0xC
			if ((v0 >> 10) != 0)
			{
				if ((v0 >> 10) == 0xC || (v0 >> 10) == 0x1)
				{
					//loc_79344
					s1 = *fd++;
				}
			}
			else
			{
				//loc_79350
				//a0 = items
				v1 = s1 & 0x3FF;
				struct ITEM_INFO* item = &items[s1 & 0x3FF];//$a0
				//v0 = item->flags & 0x8000
				//v1 = item->object_number

				if (!(item->flags & 0x8000))
				{
					struct object_info* object = &objects[item->object_number];

					if (object->ceiling != NULL)
					{
						///@CHECKME args?!?!?
						object->ceiling(item, x, y, z, NULL);
					}
				}//loc_793C0
			}
			//loc_793C0

			if (!(s1 & 0x8000))
				goto loc_7931C;

		case 5:
		case 6:
		case 19:
		case 20:
		case 21:
		loc_793C8:
			if (!(s2 & 0x8000))
				goto loc_792E0;
			break;
		}

		//loc_793D0
		return t7;

	}//loc_793D4

	return -32512;
}

#endif

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

#if PC_VERSION || PSXPC_VERSION
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
	if (height == BAD_HEIGHT || y > height)
		return -2;

	ceiling = GetCeiling(floor, x, y, z);

	if (y >= ceiling)
		return (r->flags & RF_WIND_BLOWS_PONYTAIL || r->flags & RF_FILL_WATER) ? 1 : -3;

	return -2;
}
#endif

#if PC_VERSION
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
#endif

int LOS(struct GAME_VECTOR* start, struct GAME_VECTOR* target)//79460(<), 7B4A4(<) (F)
{
	struct FLOOR_INFO* floor;
	int los1, los2;

	if ((ABS(target->z - start->z)) > (ABS(target->x - start->x)))
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

#if PC_VERSION 
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
#endif

#if PC_VERSION
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
#endif

int ClipTarget(struct GAME_VECTOR* start, struct GAME_VECTOR* target, struct FLOOR_INFO* floor)
{
	UNIMPLEMENTED();
	return 0;
}

#if !(PSX_VERSION || SAT_VERSION)
void GetJointAbsPosition(struct ITEM_INFO* item, struct PHD_VECTOR* pos, int joint)
{
	UNIMPLEMENTED();
}

int ObjectOnLOS2(struct GAME_VECTOR* start, struct GAME_VECTOR* target, struct PHD_VECTOR* a3, struct MESH_INFO** a4)
{
	UNIMPLEMENTED();
	return 0;
}
#endif

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