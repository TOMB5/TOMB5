#include "CD.H"
#include "GAMEFLOW.H"
#include "GPU.H"
#include "LOAD_LEV.H"
#include "MALLOC.H"
#include "MISC.H"
#include "PROFILE.H"
#include "PSXINPUT.H"
#include "SAVEGAME.H"
#include "SOUND.H"
#include "SPECIFIC.H"
#include "SPUSOUND.H"
#include "TEXT.H"

#include <sys/types.h>
#include <LIBCD.H>
#include <LIBPAD.H>
#include <LIBMCRD.H>
#include <LIBETC.H>

int gp_start_address = 'T' | ('W' << 8) | ('A' << 16) | ('T' << 24);

void VSyncFunc()//10000(<), 10000(<) (F) (*)
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

#ifdef PAELLA
int main(int argc, char* args[])
#else
int main(int argc, char* args[])//10064(<), 10064(!) (F) (*)
#endif
{
	SetSp(0x801FFFE0);
	ResetCallback();

	SPU_Init();
	
	ResetGraph(0);
	SetGraphDebug(0);
	InitGeom();
	
	SetDefDrawEnv(&db.draw[0], 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	SetDefDrawEnv(&db.draw[1], 0, SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT);

	SetDefDispEnv(&db.disp[0], 0, SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT);
	SetDefDispEnv(&db.disp[1], 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	
	db.draw[1].dtd = 1;
	db.draw[0].dtd = 1;
	db.draw[1].isbg = 1;
	db.draw[0].isbg = 1;

	GPU_ClearVRAM();
	GPU_FlipToBuffer(0);

	SetDispMask(1);
	VSyncCallback(&VSyncFunc);
	
	VSync(0);
	DrawSync(0);

	PutDispEnv(&db.disp[db.current_buffer]);

#ifndef PAELLA
	MemCardInit(1);

	PadInitDirect((unsigned char*)&GPad1.transStatus, (unsigned char*)&GPad2.transStatus);
	PadSetAct(0, &Motors[0], sizeof(Motors));
	PadStartCom();
#endif
	CdInit();
	CdSetDebug(0);

	InitNewCDSystem();

#if BETA_VERSION
	CDDA_SetMasterVolume(192);
#else
	CDDA_SetMasterVolume(178);
#endif

	GPU_UseOrderingTables(&GadwOrderingTables[0], sizeof(GadwOrderingTables) / 8);
	GPU_UsePolygonBuffers(&GadwPolygonBuffers[0], sizeof(GadwPolygonBuffers) / 8);
	GPU_GetScreenPosition(&savegame.ScreenX, &savegame.ScreenY);

#if DEBUG_VERSION
	ProfileInit(1);
	ProfileDraw = 1;
#endif

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

	init_game_malloc();
	InitFont();
	SOUND_Init();
	DoGameflow();

	return 0;
}