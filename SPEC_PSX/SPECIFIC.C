#include "SPECIFIC.H"

#include "3D_OBJ.H"
#include "CAMERA.H"
#include "CD.H"
#include "CONTROL.H"
#include "MOVIE.H"
#include "GPU.H"
#include "PROFILE.H"
#include "PSXINPUT.H"
#include "REQUEST.H"
#include "SAVEGAME.H"
#include "SOUND.H"
#include "SPUSOUND.H"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include <sys\types.h>
#include <LIBSPU.H>

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

void S_Warn(const char* warning_message)
{
	printf(warning_message);
#ifndef NDEBUG
	//assert(0);
#endif
}

void DisplayStatsUCunt()//61928(<), 625A8(<) (F)
{
	Requester(&StatisticsReq);
}

short S_Death()//61658, 622C8
{
	S_Warn("[S_Death] - Unimplemented!\n");
	return 0;
}

void gInit()//615CC(<), 6210C(<) (F)
{
	SOUND_Stop();
	XAFadeRate = 32;
	XAReqVolume = 0;

#if INTERNAL
	ProfileDraw = 0;
#endif
	CreateMonoScreen();

	if(XAVolume != 0)
	{
		do
		{
			XAReqVolume = 0;
		}while(XAVolume != 0);
	}
	
	S_CDPause();
	S_SetReverbType(1);
	camera.number_frames = 2;

	return;
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

int S_SoundPlaySample(int nSample, unsigned short wVol, int nPitch, short wPan, unsigned int distance)
{
	S_Warn("[S_SoundPlaySample] - Unimplemented!\n");
	return 0;
}

int S_SoundPlaySampleLooped(int nSample, unsigned short wVol, int nPitch, short wPan, unsigned int distance)
{
	S_Warn("[S_SoundPlaySampleLooped] - Unimplemented!\n");
	return 0;
}

void S_SoundSetPanAndVolume(int handle, short wPan, unsigned short wVolume, unsigned int distance)
{
	S_Warn("[S_SoundSetPanAndVolume] - Unimplemented!\n");
}

void S_SoundStopSample(int handle)//91690(<), 936D4(<)
{
	if (GtSFXEnabled == 0)
	{
		return;
	}

	if (LabSampleType[handle] != 0)
	{
		SPU_FreeChannel(handle);
	}

	//loc_916CC
	SpuSetVoiceVolume(handle, 0, 0);
	SpuSetKey(SPU_OFF, SPU_0CH);
}

void S_SoundStopAllSamples()//91D34, 93D80
{
	if (GtSFXEnabled == 0)
	{
		return;
	}

	SPU_StopAll();
}

void S_PauseAllSamples()
{
	S_Warn("[S_PauseAllSamples] - Unimplemented!\n");
}

void S_UnpauseAllSamples()
{
	S_Warn("[S_UnpauseAllSamples] - Unimplemented!\n");
}

int S_SoundSampleIsPlaying(int handle)//916F8(<), 9373C(<)
{
	char status;

	if (GtSFXEnabled == 0)
	{
		return 0;
	}

	status = (char)(SpuGetKeyStatus(1 << handle) -1);

	if (status < 2 || LabSampleType[handle] == 0)
	{
		return LabSampleType[handle];
	}

	SPU_FreeChannel(handle);

	return 0;
}

void S_SoundSetPitch(int handle, int nPitch)//91768(<), 937AC(<)
{
	if (GtSFXEnabled == 0)
	{
		return;
	}

	SpuSetVoicePitch(handle, nPitch / 64);
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
	//__asm__ volatile ("ctc2	$4, $28;");
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

void S_Pause()
{
	S_Warn("[S_Pause] - Unimplemented!\n");
}

void S_Wait(int nFrames)
{
	S_Warn("[S_Wait] - Unimplemented!\n");
}