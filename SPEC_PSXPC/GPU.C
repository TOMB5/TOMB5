#include "GPU.H"

#include "PROFILE.H"

#ifndef PSX
	#include <SDL.h>
	#include <SDL_opengl.h>
#else
	#include <LIBGPU.H>
#endif

unsigned long GnFrameCounter = 19;
unsigned long GnLastFrameCount = 19;
struct PSXTEXTSTRUCT* psxtextinfo;
struct PSXSPRITESTRUCT* psxspriteinfo;
int rgbscaleme = 256;
int gfx_debugging_mode;
struct DB_STRUCT db;
struct MMTEXTURE* RoomTextInfo;
unsigned long GadwOrderingTables_V2[512];
static int LnFlipFrame;
unsigned long GadwOrderingTables[5128];
unsigned long GadwPolygonBuffers[52260];

#ifndef PSX
	SDL_Window* g_window = NULL;
#endif

void GPU_UseOrderingTables(unsigned long* pBuffers, int nOTSize)//5DF68(<), 5F1C8(<)
{
#ifdef PSX_VERSION
	//Should be safe to use 32-bit ptrs tho
	db.order_table[0] = (unsigned long*)((unsigned long) pBuffers & 0xFFFFFF);
	db.order_table[1] = (unsigned long*)((unsigned long) &pBuffers[nOTSize] & 0xFFFFFF);
	db.nOTSize = nOTSize;
	db.pickup_order_table[0] = (unsigned long*)((unsigned long)GadwOrderingTables_V2 & 0xFFFFFF);
	db.pickup_order_table[0] = (unsigned long*)((unsigned long)&GadwOrderingTables_V2[256] & 0xFFFFFF);
#endif
}

void GPU_UsePolygonBuffers(unsigned long* pBuffers, int nPBSize)
{
	db.nPBSize = nPBSize;
	db.poly_buffer[0] = (unsigned long*)((unsigned long)pBuffers & 0xFFFFFF);
	db.poly_buffer[1] = (unsigned long*)((unsigned long)&pBuffers[nPBSize] & 0xFFFFFF);
}

void GPU_SyncBothScreens()
{
	int test = 0;
	test++;
}

void GPU_BeginScene()//5F0F0(<), 5FDD0(<) 
{
#ifdef PSX_VERSION
	db.ot = db.order_table[db.current_buffer];
	db.polyptr = db.poly_buffer[db.current_buffer];
	db.curpolybuf = db.poly_buffer[db.current_buffer];

	//db.polybuf_limit = db.poly_buffer[db.current_buffer] + &loc_19640;//Illegal
	
	ClearOTagR(&db.order_table[db.current_buffer], db.nOTSize);

	db.pickup_ot = db.pickup_order_table[db.current_buffer];
#else

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
#endif
}

int GPU_FlipNoIdle()//5E078, 5F264
{

	//ret LnFlipFrame
	return 0;
}

void GPU_GetScreenPosition(short x, short y)
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

#ifdef PSX_VERSION
void clear_a_rect(RECT* rect)//5F334, ?
{
	ClearImage(rect, 0, 0, 0);
}
#endif

void GPU_FlipToBuffer(int buffer_index)
{
#ifdef PSX_VERSION
	DrawSync(0);
	VSync(0);

	PutDispEnv(&db.disp[buffer_index]);

	db.current_buffer = buffer_index;

	PutDrawEnv(&db.draw[buffer_index]);

#endif
}

void GPU_EndScene()
{
	//int nPolys;
	//static int nWorstPolys;
#ifdef PSXPC_VERSION
	SDL_GL_SwapWindow(g_window);
#endif
}
