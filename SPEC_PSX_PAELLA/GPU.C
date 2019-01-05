#include "GPU.H"

#include "iepaella.h"

unsigned long GnFrameCounter = 19;
unsigned long GnLastFrameCount = 19;
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
	//Should be safe to use 32-bit ptrs tho
	db.order_table[0] = (unsigned long*)((unsigned long) pBuffers & 0xFFFFFF);
	db.order_table[1] = (unsigned long*)((unsigned long) &pBuffers[nOTSize] & 0xFFFFFF);
	db.nOTSize = nOTSize;
	db.pickup_order_table[0] = (unsigned long*)((unsigned long)&db.disp[1] & 0xFFFFFF);
	db.pickup_order_table[1] = (unsigned long*)((unsigned long)&GadwOrderingTables_V2[256] & 0xFFFFFF);
	return;
}

void GPU_UsePolygonBuffers(unsigned long* pBuffers, int nPBSize)//5DFB0(<), 
{
	db.nPBSize = nPBSize;
	db.poly_buffer[0] = (unsigned long*)((unsigned long)pBuffers & 0xFFFFFF);
	db.poly_buffer[1] = (unsigned long*)((unsigned long)&pBuffers[nPBSize] & 0xFFFFFF);
	return;
}

void GPU_EndScene()//5DFDC(<), 5F23C(<) (F)
{
#if DEBUG_VERSION
	int nPolys;
	static int nWorstPolys;

	nPolys = ((int) &db.polyptr[0] - (int) &db.curpolybuf[0]) * 0x4EC4EC4F / 16 - (((long) &db.polyptr[0] - (long) &db.curpolybuf[0]) >> 31);


	//loc_5E020
#endif

	//OptimiseOTagR(&db.ot[0], db.nOTSize);

#if 0
	ProfileRGB(255, 255, 255);
	do_gfx_debug_mode(&db.ot[db.nOTSize - 1]);
	ProfileRGB(0, 255, 255);
#endif

	return;
}

int GPU_FlipNoIdle()//5E078(<), 5F264(<) (F)
{
#if 0
	if (ProfileDraw)
	{
		ProfileRGB(255, 255, 255);
		ProfileAddOT(&db.ot[0]);
	}
#endif

	//loc_5E0B0
	DrawSync(0);

#if 0
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

#if 0
	ProfileStartCount();
#endif

	db.current_buffer ^= 1;

	return LnFlipFrame;
}

void do_gfx_debug_mode(unsigned long* otstart)//5E1B4(<) ? (F)
{
}

void GPU_FlipToBuffer(int buffer_index)//5F3C8(<), 600A8(<) (F)
{
	buffer_index &= 1;

	if (buffer_index)
	{
		db.current_buffer = buffer_index ^ 1;
	}
	else
	{
		db.current_buffer = buffer_index ^ 1;
	}

	return;
}

void GPU_FlipStory(unsigned long* gfx)//5E448(<), * (F)
{
	RECTPSX r;
	RECTPSX* fuckmyanalpassage;

	DrawSync(0);
	VSync(0);

	PutDispEnv(&db.disp[db.current_buffer]);
	fuckmyanalpassage = (RECTPSX*) &db.disp[db.current_buffer ^ 1].disp;
	r.x = fuckmyanalpassage->x;
	r.y = fuckmyanalpassage->y;
	r.w = fuckmyanalpassage->w;
	r.h = fuckmyanalpassage->h;
	LoadImage(&r, gfx);
	DrawOTagEnv(&db.ot[db.nOTSize - 1], &db.draw[db.current_buffer]);
	db.current_buffer ^= 1;
}