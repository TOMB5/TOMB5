#include "SPECIFIC.H"

#include "GPU.H"
#include "SOUND.H"

#include <stdio.h>
#include <stdlib.h>

#include <assert.h>

static struct REQUESTER PauseReq = { 0xA4, 0x08, 0x03, 0x00, 0x05, 0x08, 0x03, 0x0A, 0x00, { 0xDE, 0xDF, 0xE0, 0x00, 0x00 } };
static struct REQUESTER AdjustReq = { 0xE6, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,{ 0x00, 0x00, 0x00, 0x00, 0x00 } };
static struct REQUESTER QuitReq = { 0xE2, 0x08, 0x02, 0x01, 0x02, 0x00, 0x00, 0x00, 0x00,{ 0xA0, 0xA1, 0x00, 0x00, 0x00 } };
static struct REQUESTER StatisticsReq = { 0xB2, 0x08, 0x01, 0x01, 0x05, 0x00, 0x00, 0x00, 0x01,{ 0xEE, 0x00, 0x00, 0x00, 0x00 } };
static unsigned short PadStrings[5][8] =
{
	{ 0x00BC, 0xBE00, 0x00BE, 0xBD00, 0x00BD, 0xBF00, 0x00BF, 0xC100 },
	{ 0x00BC, 0xBE00, 0x00BE, 0xBD00, 0x00BD, 0xBF00, 0x00BF, 0xC100 },
	{ 0x00BC, 0xBE00, 0x00BE, 0xBD00, 0x00BD, 0xBF00, 0x00BF, 0xC100 },
	{ 0x00BC, 0xBE00, 0x00BE, 0xBD00, 0x00BD, 0xBF00, 0x00BF, 0xC100 },
	{ 0x00BC, 0xBE00, 0x00BE, 0xBD00, 0x00BD, 0xBF00, 0x00BF, 0xC100 }
};
static unsigned char PauseMenuNum;

unsigned short AnimComp;
short AnimatingTexturesVOffset;
struct REQUESTER SettingsReq = { 0xE0, 0x08, 0x05, 0x00, 0x05, 0x00, 0x03, 0x03, 0x00,{ 0xE4, 0xE5, 0xE7, 0xE3, 0xEB } };
struct REQUESTER ConfigReq = { 0xE7, 0x08, 0x03, 0x01, 0x05, 0x00, 0x00, 0x02, 0x01,{ 0xED, 0xE8, 0xE9, 0x00, 0x00 } };
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

#ifdef PSX_VERSION
	SpuSetKey(0, 0xFFFFFF);

	do
	{
		ret = SPU_UpdateStatus();
	} while (ret != MAX_SOUND_SLOTS);
#endif

	return ret;
}

long S_DumpScreen()//607A8, 61320
{
	return GPU_FlipNoIdle();
}

void S_control_screen_position()//6068C, 61204
{
	S_Warn("[S_control_screen_position] - Unimplemented!\n");
}
