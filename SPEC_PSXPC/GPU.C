#include "GPU.H"

#include "CAMERA.H"
#include "LOAD_LEV.H"
#include "PROFILE.H"
#include "SHADOWS.H"
#include "SPECIFIC.H"
#include "SPECTYPES.H"

#include <stdlib.h>

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

SDL_Window* g_window = NULL;

void GPU_UseOrderingTables(unsigned long* pBuffers, int nOTSize)//5DF68(<), 5F1C8(<)
{
	db.order_table[0] = &pBuffers[0];
	db.order_table[1] = &pBuffers[nOTSize];
	db.nOTSize = nOTSize;
	db.pickup_order_table[0] = (unsigned long*) &db.disp[1];
	db.pickup_order_table[1] = &GadwOrderingTables_V2[256];
#if 0
	//Should be safe to use 32-bit ptrs tho
	db.order_table[0] = (unsigned long*) ((unsigned long) pBuffers & 0xFFFFFF);
	db.order_table[1] = (unsigned long*) ((unsigned long) &pBuffers[nOTSize] & 0xFFFFFF);
	db.nOTSize = nOTSize;
	db.pickup_order_table[0] = (unsigned long*) ((unsigned long) &db.disp[1] & 0xFFFFFF);
	db.pickup_order_table[1] = (unsigned long*) ((unsigned long) &GadwOrderingTables_V2[256] & 0xFFFFFF);
#endif
}

void GPU_UsePolygonBuffers(unsigned long* pBuffers, int nPBSize)//5DFB0(<), 
{
#if 1
	db.nPBSize = nPBSize;
	db.poly_buffer[0] = &pBuffers[0];
	db.poly_buffer[1] = &pBuffers[nPBSize];
#else
	db.nPBSize = nPBSize;
	db.poly_buffer[0] = (unsigned long*) ((unsigned long) pBuffers & 0xFFFFFF);
	db.poly_buffer[1] = (unsigned long*) ((unsigned long) &pBuffers[nPBSize] & 0xFFFFFF);
#endif
	return;
}

void GPU_EndScene()//5DFDC(<), 5F23C(<) (F)
{
#if DEBUG_VERSION
	int nPolys = 0;
	static int nWorstPolys;

#if 0
	nPolys = ((int) &db.polyptr[0] - (int) &db.curpolybuf[0]) * 0x4EC4EC4F / 16 - (((long) &db.polyptr[0] - (long) &db.curpolybuf[0]) >> 31);
#endif

	if (psxtextinfo->u2v2pad < nPolys)
	{
		psxtextinfo->u2v2pad = nPolys;
	}

	//loc_5E020
#endif

	OptimiseOTagR(&db.ot[0], db.nOTSize);

#if DEBUG_VERSION
	ProfileRGB(255, 255, 255);
	do_gfx_debug_mode(&db.ot[db.nOTSize - 1]);
	ProfileRGB(0, 255, 255);
#endif

	SDL_GL_SwapWindow(g_window);

	return;
}

int GPU_FlipNoIdle()//5E078(<), 5F264(<)
{
#if DEBUG_VERSION
	if (ProfileDraw)
	{
		ProfileRGB(255, 255, 255);
		ProfileAddOT(&db.ot[0]);
	}//loc_5E0B0
#endif

#if DEBUG_VERSION
	if (ProfileDraw)
	{
		ProfileAddDrawOT(&db.ot[0]);
	}//loc_5E0D8
#endif

	LnFlipFrame = GnLastFrameCount;

	if (GnLastFrameCount < 2)
	{
		//loc_5E0F4
		do
		{
			LnFlipFrame++;
		} while (LnFlipFrame < 2);
	}
	else
	{
		//loc_5E120
		LnFlipFrame++;
	}

	//loc_5E138
	//v0 = db.current_buffer;
	GnLastFrameCount = 0;

#if DEBUG_VERSION
	ProfileStartCount();
#endif

	db.current_buffer ^= 1;

	return LnFlipFrame;
}

void do_gfx_debug_mode(unsigned long* otstart)
{
	S_Warn("[do_gfx_debug_mode] - Unimplemented!\n");
}

void GPU_FlipStory(unsigned long* gfx)//5E448(<), * (F)
{
#if 0
	RECT r;
	RECT* fuckmyanalpassage;

	fuckmyanalpassage = (RECT*) &db.disp[db.current_buffer ^ 1].disp;
	r.x = fuckmyanalpassage->x;
	r.y = fuckmyanalpassage->y;
	r.w = fuckmyanalpassage->w;
	r.h = fuckmyanalpassage->h;
	LoadImage(&r, gfx);

	DrawOTagEnv(&db.ot[db.nOTSize - 1], &db.draw[db.current_buffer]);
	db.current_buffer ^= 1;
#endif
}