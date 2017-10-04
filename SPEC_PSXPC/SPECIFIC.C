#include "SPECIFIC.H"

#include "GPU.H"
#include "PSXPCINPUT.H"
#include "REQUEST.H"
#include "SOUND.H"
#include "SAVEGAME.H"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "..\SPEC_PSX\SPECIFIC.H"



static struct REQUESTER PauseReq = { 0xA4, 0x08, 0x03, 0x00, 0x05, 0x08, 0x03, 0x0A, 0x00, { 0xDE, 0xDF, 0xE0, 0x00, 0x00 } };
static struct REQUESTER AdjustReq = { 0xE6, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,{ 0x00, 0x00, 0x00, 0x00, 0x00 } };
static struct REQUESTER QuitReq = { 0xE2, 0x08, 0x02, 0x01, 0x02, 0x00, 0x00, 0x00, 0x00,{ 0xA0, 0xA1, 0x00, 0x00, 0x00 } };
static struct REQUESTER StatisticsReq = { 0xB2, 0x08, 0x01, 0x01, 0x05, 0x00, 0x00, 0x00, 0x01,{ 0xEE, 0x00, 0x00, 0x00, 0x00 } };

static unsigned short PadStrings[5][8] =
{
	{ 0x00BC, 0x00BE, 0x00BD, 0x00BF, 0x00C1, 0x00C2, 0x00C0, 0x00C3 },
	{ 0x00BE, 0x00BD, 0x00BF, 0x00BC, 0x00C2, 0x00C1, 0x00C3, 0x00C0 },
	{ 0x00BD, 0x00BF, 0x00BE, 0x00BC, 0x00C0, 0x00C3, 0x00C1, 0x00C2 },
	{ 0x00BF, 0x00BC, 0x00C1, 0x00BE, 0x00BD, 0x00C2, 0x00C0, 0x00C3 },
	{ 0x00C0, 0x00C1, 0x00C3, 0x00C2, 0x00BE, 0x00BF, 0x00BC, 0x00BD }
};

static unsigned char PauseMenuNum;
unsigned short AnimComp;
short AnimatingTexturesVOffset;
struct REQUESTER SettingsReq = { 0xE0, 0x08, 0x05, 0x00, 0x05, 0x00, 0x03, 0x03, 0x00,{ 0xE4, 0xE5, 0xE7, 0xE3, 0xEB } };
struct REQUESTER ConfigReq = { 0xE7, 0x08, 0x03, 0x01, 0x05, 0x00, 0x00, 0x02, 0x01,{ 0xED, 0xE8, 0xE9, 0x00, 0x00 } };
unsigned char SoundFXVolume;
unsigned short nAnimTextureRanges;
unsigned short* AnimTextureRanges;
unsigned short nAnimUVRanges;
int GtSFXEnabled;
short AnimatingTexturesV[16][8][3];

void DisplayStatsUCunt()//61928(<), 625A8(<) (F)
{
	Requester(&StatisticsReq);
}

short S_Death()//61658, 622C8
{
	S_Warn("[S_Death] - Unimplemented!\n");
	return 0;
}

void gInit()//615CC, 6210C
{
	S_Warn("[gInit] - Unimplemented!\n");
}

int DoPauseMenu()//60F34, 61A68
{
	S_Warn("[DoPauseMenu] - Unimplemented!\n");
	return 0;
}

void DisplayConfig(int x, int y)//6080C, 61340
{
	S_Warn("[DisplayConfig] - Unimplemented!\n");
}

void S_ExitSystem(char* exit_message)//607C8, *
{
	printf(exit_message);
	exit(EXIT_FAILURE);
}

void S_Warn(char* warning_message)
{
	printf(warning_message);
#ifndef NDEBUG
	//assert(0);
#endif
}

int S_SoundStopAllSamples()//91D34, 93D80
{
	int ret;

	if (GtSFXEnabled == 0)
	{
		return 0;
	}

	return ret;
}

long S_DumpScreen()//607A8(<), 61320(<) (F)
{
	return GPU_FlipNoIdle();
}

void S_control_screen_position()//6068C(<), 61204(<)
{
	if (input & 1)
	{
		savegame.ScreenY--;

		if ((savegame.ScreenY << 16) < 0)
		{
			savegame.ScreenY = 0;
		}
	}
	else if (input & 2)
	{
		//loc_606D0
		savegame.ScreenY++;

		if (savegame.ScreenY > 40)
		{
			savegame.ScreenY = 40;
		}
	}

	//loc_60708
	if (input & 4)
	{
		savegame.ScreenX--;

		if (savegame.ScreenX < -10)
		{
			savegame.ScreenX = -10;
		}

	}
	else if (input & 8)
	{
		//loc_60750
		savegame.ScreenX++;

		if (savegame.ScreenX > 32)
		{
			savegame.ScreenX = 32;
		}
	}

	//loc_60784
	GPU_SetScreenPosition(savegame.ScreenX, savegame.ScreenY);
}

void S_AnimateTextures(long num_frames)
{
	S_Warn("[S_AnimateTextures] - Unimplemented!\n");
}

void S_SetupClutAdder(long unk)
{
	S_Warn("[S_SetupClutAdder] - Unimplemented!\n");
}

void S_DrawFootPrints()
{
	S_Warn("[S_DrawFootPrints] - Unimplemented!\n");
}

void S_DrawSparks()
{
	S_Warn("[S_DrawSparks] - Unimplemented!\n");
}