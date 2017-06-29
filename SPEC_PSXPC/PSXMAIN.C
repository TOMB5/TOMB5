#include <assert.h>

#if 0
//#include "CD.H"
//#include "GPU.H"
#endif

#include "LOAD_LEV.H"
#include "MALLOC.H"

#if 0
//#include "PROFILE.H"
//#include "SPUSOUND.H"
#endif
#include "../GAME/GAMEFLOW.H"

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

void __main()
{
#if 0
		if (dword_9A884 != 0)//bnez	$t0, loc_67FA4
		{
			return;
		}
		
		dword_9A884 = 1;

		char* a0 = "TWAT";
		char* a1 = "TWAT";
		//__sn_cpp_structors();
#endif
}

void SetSp()
{

}

int main()//10064, 10064
{
	__main();

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
	InitNewCDSystem();
	CDDA_SetMasterVolume();
	GPU_UseOrderingTables();
	GPU_UsePolygonBuffers();
	GPU_GetScreenPosition();
	ProfileInit();
#endif
	init_game_malloc();
	//InitFont();
	//SOUND_Init();
	DoGameflow();
	return 0;
}