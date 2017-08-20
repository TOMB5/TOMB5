#include "SPECIFIC.H"

#include "GPU.H"
#include "SOUND.H"

#include <stdio.h>
#include <stdlib.h>

#include <assert.h>

static struct REQUESTER PauseReq;
static struct REQUESTER AdjustReq;
static struct REQUESTER QuitReq;
static struct REQUESTER StatisticsReq;
static unsigned short PadStrings[5][8];
static unsigned char PauseMenuNum;

unsigned short AnimComp;
short AnimatingTexturesVOffset;
struct REQUESTER SettingsReq;
struct REQUESTER ConfigReq;
unsigned char SoundFXVolume;
unsigned short nAnimTextureRanges;
unsigned short *AnimTextureRanges;
unsigned short nAnimUVRanges;
int GtSFXEnabled;
short AnimatingTexturesV[16][8][3];

#ifndef EXIT_FAILURE
	#define EXIT_FAILURE 1
#endif

void DisplayStatsUCunt()//61928, 625A8
{
	S_Warn("[DisplayStatsUCunt] - Unimplemented!\n");
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

#ifdef PSX
	SpuSetKey(0, 0xFFFFFF);

	do
	{
		ret = SPU_UpdateStatus();
	} while (ret != MAX_SOUND_SLOTS);
	
	return ret;
#endif
}

long S_DumpScreen()//607A8, 61320
{
	return GPU_FlipNoIdle();
}

void S_control_screen_position()//6068C, 61204
{
	S_Warn("[S_control_screen_position] - Unimplemented!\n");
}
