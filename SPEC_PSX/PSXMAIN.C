#include "3D_GEN.H"
#include "CD.H"
#include "GAMEFLOW.H"
#include "GPU.H"
#include "LOAD_LEV.H"
#include "MALLOC.H"
#include "PROFILE.H"
#include "PSXINPUT.H"
#include "SAVEGAME.H"
#include "SOUND.H"
#include "SPECIFIC.H"
#include "SPUSOUND.H"
#include "TEXT.H"

#include <sys/types.h>
#include <LIBAPI.H>
#include <LIBCD.H>
#include <LIBGTE.H>
#include <LIBGPU.H>
#include <LIBPAD.H>
#include <stdio.h>
#include <LIBMCRD.H>

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

int main(int argc, char* args[])//10064(<), 10064(!) (F)
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

	db.draw[0].dtd = 1;
	db.draw[0].isbg = 1;
	db.draw[1].dtd = 1;
	db.draw[1].isbg = 1;

	GPU_ClearVRAM();
	GPU_FlipToBuffer(0);

	SetDispMask(1);
	VSyncCallback(&VSyncFunc);
	
	VSync(0);
	DrawSync(0);

	PutDispEnv(&db.disp[db.current_buffer]);

	MemCardInit(1);

	PadInitDirect(&GPad1.transStatus, &GPad2.transStatus);
	PadSetAct(0, &Motors[0], sizeof(Motors));
	PadStartCom();

	CdInit();
	CdSetDebug(0);

	InitNewCDSystem();
	CDDA_SetMasterVolume(192);

	GPU_UseOrderingTables(&GadwOrderingTables[0], 2564);
	GPU_UsePolygonBuffers(&GadwPolygonBuffers[0], 26130);
	GPU_GetScreenPosition(&savegame.ScreenX, &savegame.ScreenY);

#if DEBUG_VERSION
	ProfileInit(1);
	ProfileDraw = 1;
#endif

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