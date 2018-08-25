#include "3D_GEN.H"
#include "CD.H"
#include "GAMEFLOW.H"
#include "GPU.H"
#include "LOAD_LEV.H"
#include "MALLOC.H"
#include "MISC.H"
#include "PROFILE.H"
#include "PSXPCINPUT.H"
#include "SAVEGAME.H"
#include "SOUND.H"
#include "SPECIFIC.H"
#include "SPUSOUND.H"
#include "TEXT.H"

#include <SDL.h>

// SDL breaks build on PSX
#undef main

int gp_start_address = 'T' | ('W' << 8) | ('A' << 16) | ('T' << 24);

void VSyncFunc()//10000(<), 10000(<) (F)
{
	cbvsync();

	if (LoadingBarEnabled)
	{
		LOAD_VSyncHandler();
	}

	//loc_1002C
	GnFrameCounter++;
	GnLastFrameCount++;

	return;
}

int main(int argc, char* args[])//10064(<), 10064(!)
{
	InitNewCDSystem();
#if BETA_VERSION
	CDDA_SetMasterVolume(192);
#else
	CDDA_SetMasterVolume(178);
#endif

	GPU_UseOrderingTables(&GadwOrderingTables[0], sizeof(GadwOrderingTables) / 8);
	GPU_UsePolygonBuffers(&GadwPolygonBuffers[0], sizeof(GadwPolygonBuffers) / 8);
	GPU_GetScreenPosition(&savegame.ScreenX, &savegame.ScreenY);

#if BETA_VERSION
	savegame.VolumeCD = 204;
	savegame.VolumeFX = 255;
#else
	savegame.VolumeCD = 178;
	savegame.VolumeFX = 204;
#endif
	savegame.ControlOption = 0;
	savegame.AutoTarget = 1;
	savegame.VibrateOn = 0;
#if BETA_VERSION
	SoundFXVolume = 255;
#else
	SoundFXVolume = 204;
#endif

	InitialisePadSubsystem();

	init_game_malloc();
	InitFont();
	SOUND_Init();
	DoGameflow();
	return 0;
}