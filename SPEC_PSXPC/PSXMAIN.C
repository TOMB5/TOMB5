#include <assert.h>

#include "CD.H"
#include "GAMEFLOW.H"
//#include "GPU.H"
#include "LOAD_LEV.H"
#include "MALLOC.H"
#include "PROFILE.H"
#include "SOUND.H"
//#include "SPUSOUND.H"
#include "TEXT.H"

#include <SDL.h>

unsigned long dword_9A884 = 0;

void VSyncFunc()
{
#if 0
	cbvsync();

	if (LoadingBarEnabled == 0)
	{
		//LOAD_VSyncHandler();

		GnFrameCounter++;
		GnLastFrameCount++;
	}
	else
	{
		//LOAD_VSyncHandler();
	}
#endif
}

void SetSp()
{

}

int main(int argc, char* args[])//10064, 10064
{
	SDL_Init(0);
#ifdef PSX
	ResetCallback();
	//SPU_Init();
	//ResetGraph();
	//SetGraphDebug();
	//InitGeom();
	int height = 240;// li	$s1, 0xF0
	int width = 512;//li	$a3, 0x200
	SetDefDrawEnv();
	height = 240;//li	$a2, 0xF0
	width = 512;//li	$a3, 0x200
	SetDefDrawEnv();
	SetDefDispEnv();
	SetDefDispEnv();// jal	sub_68408
	GPU_ClearVRAM();
	GPU_FlipToBuffer();
	SetDispMask();
	VSyncCallback();
	VSync();
	DrawSync();
	PutDispEnv();
	MemCardInit();
	PadInitDirect();
	PadSetAct();
	PadStartCom();
	CdInit();
	CdSetDebug();
#endif

#ifndef INTERNAL
	InitNewCDSystem();
#endif

#ifdef PSX
	CDDA_SetMasterVolume();
	GPU_UseOrderingTables();
	GPU_UsePolygonBuffers();
	GPU_GetScreenPosition();
	ProfileInit();
#endif

	init_game_malloc();
	InitFont();
	SOUND_Init();
	DoGameflow();
	return 0;
}
