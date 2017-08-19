#include "SPECIFIC.H"

#include "GPU.H"

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

void S_ExitSystem(char* exit_message)
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

void S_SoundStopAllSamples()//91D34
{
	if (GtSFXEnabled != 0)
	{
#if 0
		int a1 = -1;
		int a0 = 0;
		//SpuSetKey();

		while (GtSFXEnabled != 24)
		{
			//SPU_UpdateStatus();
		}
#endif
	}
}

long S_DumpScreen()
{
	return GPU_FlipNoIdle();
}