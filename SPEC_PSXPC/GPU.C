#include "GPU.H"

#include "PROFILE.H"
#include "SPECIFIC.H"

#include <SDL.h>
#include <SDL_opengl.h>

unsigned long GnFrameCounter = 19;
unsigned long GnLastFrameCount = 19;
struct PSXTEXTSTRUCT* psxtextinfo;
struct PSXSPRITESTRUCT* psxspriteinfo;
int rgbscaleme = 256;
int gfx_debugging_mode;
struct MMTEXTURE* RoomTextInfo;
unsigned long GadwOrderingTables_V2[512];
static int LnFlipFrame;
unsigned long GadwOrderingTables[5128];
unsigned long GadwPolygonBuffers[52260];

SDL_Window* g_window = NULL;

void GPU_UseOrderingTables(unsigned long* pBuffers, int nOTSize)//5DF68(<), 5F1C8(<)
{
	S_Warn("[GPU_UseOrderingTables] - Unimplemented!\n");
}

void GPU_UsePolygonBuffers(unsigned long* pBuffers, int nPBSize)
{
	S_Warn("[GPU_UsePolygonBuffers] - Unimplemented!\n");
}

void GPU_SyncBothScreens()
{
	int test = 0;
	test++;
}

void GPU_BeginScene()//5F0F0(<), 5FDD0(<) 
{
	glClear((GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			SDL_Quit();
			exit(0);
		}
	}
}

int GPU_FlipNoIdle()//5E078, 5F264
{

	//ret LnFlipFrame
	return 0;
}

void GPU_GetScreenPosition(short *x, short *y)
{
	int test = 0;
	test++;
#if 0
	if (ProfileDraw)
	{
		ProfileRGB(255, 255, 255);
		ProfileAddOT(&db.ot);
	}

	//loc_5E0B0
	DrawSync(0);

	if (ProfileDraw)
	{
		ProfileAddDrawOT(&db.ot);
	}

	//loc_5E0D8
	//TODO
#endif
}

void GPU_ClearVRAM()//5F2D0(<), 5FFB0(<)
{
	int test = 0;
	test++;
#if 0
	//RECT r;
	DrawSync(0);
	VSync(0);
	clear_a_rect(0);
	clear_a_rect(0x100);
	clear_a_rect(0x200);
	clear_a_rect(0);
	DrawSync(0);
	VSync(0);
#endif
}

void GPU_FlipToBuffer(int buffer_index)
{
	S_Warn("[GPU_FlipToBuffer] - Unimplemented!\n");
}

void GPU_EndScene()
{
	SDL_GL_SwapWindow(g_window);
}

void GPU_SetScreenPosition(short x, short y)
{
	S_Warn("[GPU_SetScreenPosition] - Unimplemented!\\n");
}
