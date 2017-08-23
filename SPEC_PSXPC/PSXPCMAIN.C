#include "3D_GEN.H"
#include "CD.H"
#include "GAMEFLOW.H"
#include "GPU.H"
#include "LOAD_LEV.H"
#include "MALLOC.H"
#include "MEMCARD.H"
#include "PROFILE.H"
#include "PSXPCINPUT.H"
#include "SAVEGAME.H"
#include "SOUND.H"
#include "SPECIFIC.H"
#include "SPUSOUND.H"
#include "TEXT.H"

#include <SDL.h>

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
	CDDA_SetMasterVolume(192);

	GPU_UseOrderingTables(&GadwOrderingTables[0], 2564);
	GPU_UsePolygonBuffers(&GadwPolygonBuffers[0], 26130);
	GPU_GetScreenPosition(savegame.ScreenX, savegame.ScreenY);

	savegame.VolumeCD = 204;
	savegame.VolumeFX = 255;
	savegame.ControlOption = 0;
	savegame.AutoTarget = 1;
	savegame.VibrateOn = 0;
	SoundFXVolume = 255;

	init_game_malloc();
	InitFont();
	SOUND_Init();
	DoGameflow();
	return 0;
}