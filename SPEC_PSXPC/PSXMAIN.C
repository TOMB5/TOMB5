#include <assert.h>

#include "CD.H"
#include "GAMEFLOW.H"
#include "GPU.H"
#include "LOAD_LEV.H"
#include "MALLOC.H"
#include "PROFILE.H"
#include "SAVEGAME.H"
#include "SOUND.H"
#include "SPECIFIC.H"
#include "SPUSOUND.H"
#include "TEXT.H"

#include <SDL.h>

void VSyncFunc()//10000(<), 10000(<) (F)
{
	cbvsync();

	if (LoadingBarEnabled != 0)
	{
		LOAD_VSyncHandler();
	}

	//loc_1002C
	GnFrameCounter++;
	GnLastFrameCount++;

	return;
}

void SetSp()
{

}

int main(int argc, char* args[])//10064(<), 10064(!)
{
#ifdef PSX
	SetSp(0x801FFFE0);

	ResetCallback();
#endif

	SPU_Init();

#ifdef PSX
	ResetGraph(0);
	SetGraphDebug(0);
	InitGeom();
	SetDefDrawEnv(&db.draw[0], 0, 0, 512, 240);
	SetDefDrawEnv(&db.draw[1], 0, 240, 512, 240);

	SetDefDispEnv(&db.disp[0], 0, 240, 512, 240);
	SetDefDispEnv(&db.disp[1], 0, 0, 512, 240);
#endif

	db.draw[0].dtd = 1;
	db.draw[0].isbg = 1;
	db.draw[1].dtd = 1;
	db.draw[1].isbg = 1;

	GPU_ClearVRAM();
	GPU_FlipToBuffer(0);

#ifdef PSX
	SetDispMask(1);
	VSyncCallback(&VSyncFunc);
	VSync(0);
	DrawSync(0);

	PutDispEnv(&db.disp[db.current_buffer]);

	MemCardInit(1);

	PadInitDirect(GPad1, GPad2);

	PadSetAct(0, &Motors[0], 2);

	PadStartCom();

	CdInit(0);//check arg
	CdSetDebug(0);
#endif

	InitNewCDSystem();
	CDDA_SetMasterVolume(192);

	GPU_UseOrderingTables(&GadwOrderingTables[0], 2564);
	GPU_UsePolygonBuffers(&GadwPolygonBuffers[0], 26130);

	GPU_GetScreenPosition(savegame.ScreenX, savegame.ScreenY);

#ifdef INTERNAL
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
