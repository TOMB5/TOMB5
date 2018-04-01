#include "GPU.H"

#include "CAMERA.H"
#include "LOAD_LEV.H"
#include "PROFILE.H"
#include "SHADOWS.H"
#include "SPECIFIC.H"

#include <assert.h>
#include <LIBGPU.H>
#include <LIBETC.H>

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


void GPU_UseOrderingTables(unsigned long* pBuffers, int nOTSize)//5DF68(<), 5F1C8(<)
{
#if 0
	db.order_table[0] = &pBuffers[0];
	db.order_table[1] = &pBuffers[nOTSize];
	db.nOTSize = nOTSize;
	db.pickup_order_table[0] = (unsigned long*)&db.disp[1];
	db.pickup_order_table[1] = &GadwOrderingTables_V2[256];
#else
	//Should be safe to use 32-bit ptrs tho
	db.order_table[0] = (unsigned long*)((unsigned long) pBuffers & 0xFFFFFF);
	db.order_table[1] = (unsigned long*)((unsigned long) &pBuffers[nOTSize] & 0xFFFFFF);
	db.nOTSize = nOTSize;
	db.pickup_order_table[0] = (unsigned long*)((unsigned long)&db.disp[1] & 0xFFFFFF);
	db.pickup_order_table[1] = (unsigned long*)((unsigned long)&GadwOrderingTables_V2[256] & 0xFFFFFF);
#endif
	return;
}

void GPU_UsePolygonBuffers(unsigned long* pBuffers, int nPBSize)//5DFB0(<), 
{
#if 0
	db.nPBSize = nPBSize;
	db.poly_buffer[0] = &pBuffers[0];
	db.poly_buffer[1] = &pBuffers[nPBSize];
#else
	db.nPBSize = nPBSize;
	db.poly_buffer[0] = (unsigned long*)((unsigned long)pBuffers & 0xFFFFFF);
	db.poly_buffer[1] = (unsigned long*)((unsigned long)&pBuffers[nPBSize] & 0xFFFFFF);
#endif
	return;
}

void GPU_EndScene()//5DFDC(<), 5F23C(<) (F)
{
#if DEBUG_VERSION
	int nPolys;
	static int nWorstPolys;

	nPolys = ((int) &db.polyptr[0] - (int) &db.curpolybuf[0]) * 0x4EC4EC4F / 16 - (((long) &db.polyptr[0] - (long) &db.curpolybuf[0]) >> 31);

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

	return;
}

int GPU_FlipNoIdle()//5E078(<), 5F264(<) (F)
{
#if DEBUG_VERSION
	if (ProfileDraw)
	{
		ProfileRGB(255, 255, 255);
		ProfileAddOT(&db.ot[0]);
	}
#endif

	//loc_5E0B0
	DrawSync(0);

#if DEBUG_VERSION
	if (ProfileDraw)
	{
		ProfileAddDrawOT(&db.ot[0]);
	}
#endif

	LnFlipFrame = GnLastFrameCount;

	//loc_5E0D8
	if (LnFlipFrame < 2)
	{
		do
		{
			VSync(0);
			LnFlipFrame++;
		} while (LnFlipFrame < 2);
	}
	else
	{
		//loc_5E120
		VSync(0);
		LnFlipFrame++;
	}

	GnLastFrameCount = 0;
	PutDispEnv(&db.disp[db.current_buffer]);
	DrawOTagEnv(&db.ot[db.nOTSize-1], &db.draw[db.current_buffer]);

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
	RECT r;
	RECT* fuckmyanalpassage;

	DrawSync(0);
	VSync(0);

	PutDispEnv(&db.disp[db.current_buffer]);
	fuckmyanalpassage = (RECT*) &db.disp[db.current_buffer ^ 1].disp;
	r.x = fuckmyanalpassage->x;
	r.y = fuckmyanalpassage->y;
	r.w = fuckmyanalpassage->w;
	r.h = fuckmyanalpassage->h;
	LoadImage(&r, gfx);
	DrawOTagEnv(&db.ot[db.nOTSize - 1], &db.draw[db.current_buffer]);
	db.current_buffer ^= 1;
}