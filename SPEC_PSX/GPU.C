#include "GPU.H"

#include "CAMERA.H"
#include "LOAD_LEV.H"
#include "PROFILE.H"

#include <assert.h>
#include <LIBGPU.H>

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
	db.order_table[0] = &pBuffers[0];
	db.order_table[1] = &pBuffers[nOTSize];
	db.nOTSize = nOTSize;
	db.pickup_order_table[0] = (unsigned long*)&db.disp[1];
	db.pickup_order_table[1] = &GadwOrderingTables_V2[256];
#if 0
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
#if 1
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

void GPU_SyncBothScreens()//5F374(<), 60054(<)
{
	DrawSync(0);

	db.current_buffer ^= 1;
	if (db.current_buffer != 0)
	{
		MoveImage(&db.disp[1].disp, db.disp[0].disp.x, db.disp[0].disp.y);
		//TODO: Verify ra += 0x10;! prolly else skip loc_5F3A8 (implemented but should be checked).
	}
	else
	{
		//loc_5F3A8
		MoveImage(&db.disp[0].disp, db.disp[1].disp.x, db.disp[1].disp.y);
	}

	DrawSync(0);

	return;
}

void GPU_BeginScene()//5F0F0(<), 5FDD0(<)
{
	db.ot = db.order_table[db.current_buffer];
	db.polyptr = (char*)db.poly_buffer[db.current_buffer];
	db.curpolybuf = (char*)db.poly_buffer[db.current_buffer];
	db.polybuf_limit = (char*)(db.poly_buffer[db.current_buffer]) + 26000;
	db.pickup_ot = db.pickup_order_table[db.current_buffer];
	ClearOTagR(db.order_table[db.current_buffer], db.nOTSize);

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

	DrawSync(0);//TODO confirm retail is sub_6B144 draw sync

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

	//loc_5E138
	//v0 = db.current_buffer;
	GnLastFrameCount = 0;
	PutDispEnv(&db.disp[db.current_buffer]);
	DrawOTagEnv(&db.ot[db.nOTSize - 1], &db.draw[db.current_buffer]);

#if DEBUG_VERSION
	ProfileStartCount();
#endif

	db.current_buffer ^= 1;

	return LnFlipFrame;
}

void GPU_FlipStory(unsigned long* gfx)//5E448(<), * (F)
{
	RECT r;
	RECT* fuckmyanalpassage;

	DrawSync(0);
	VSync(0);

	PutDispEnv(&db.disp[db.current_buffer]);
	fuckmyanalpassage = (RECT*)&db.disp[db.current_buffer ^ 1].disp;
	r.x = fuckmyanalpassage->x;
	r.y = fuckmyanalpassage->y;
	r.w = fuckmyanalpassage->w;
	r.h = fuckmyanalpassage->h;
	LoadImage(&r, gfx);

	DrawOTagEnv(&db.ot[db.nOTSize - 1], &db.draw[db.current_buffer]);
	db.current_buffer ^= 1;
}

void GPU_GetScreenPosition(short* x, short* y)//5F34C, ?
{
	*x = db.disp[0].screen.x;
	*y = db.disp[0].screen.y;
	return;
}

/*   PSX VRAM   (H)
 *  ----------- 1024px
 *  | TL | TR |  |
 *  -----------  v
 *  | BL | BR |  
 *  -----------
 *(W)1024px-->
 * 
 */
void GPU_ClearVRAM()//5F2D0(<), 5FFB0(<) (F)
{
	RECT r;

	DrawSync(0);
	VSync(0);

	//Clear TL
	r.x = 0;
	r.y = 0;
	r.w = 512;
	r.h = 256;
	clear_a_rect(&r);

	//Clear BL
	r.y = 256;
	clear_a_rect(&r);

	//Clear BR
	r.x = 512;
	clear_a_rect(&r);

	//Clear TR
	r.y = 0;
	clear_a_rect(&r);

	DrawSync(0);
	VSync(0);

	return;
}

void clear_a_rect(RECT* r)//5F334(<), 60014(<) (F)
{
	ClearImage(r, 0, 48, 0);

	return;
}

//@Gh0stblade - Not sure why this is so unoptimal, we can basically &disp[db.current_buffer]... double check code.
void GPU_FlipToBuffer(int buffer_index)//5F3C8(<), 600A8(<) (F)
{
	DrawSync(0);
	VSync(0);

	buffer_index &= 1;

	if (buffer_index)
	{
		PutDispEnv(&db.disp[1]);
		db.current_buffer = buffer_index ^ 1;
		PutDrawEnv(&db.draw[1]);
	}
	else
	{
		PutDispEnv(&db.disp[0]);
		db.current_buffer = buffer_index ^ 1;
		PutDrawEnv(&db.draw[0]);
	}

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

long OptimiseOTagR(unsigned long* ot, int nOTSize)//86CC4(<), 88D08(<)
{
	unsigned long* a1;
	unsigned long* a3;
	unsigned long v0;
	unsigned long* v1;
	long at = 0;

	if (nOTSize < 8)
	{
		return 0;
	}

	a1 = &ot[nOTSize - 1];
	v1 = &ot[1];
	v0 = a1[0];

	//loc_86CE4
	do
	{
		a1--;

		if ((unsigned long*)v0 == a1)
		{
			a3 = a1 - 1;
			if (a1 == ot)
			{
				return at;
			}

			//loc_86CF4
			do
			{
				v0 = a1[0];
				a1--;
				if (a1 == v1)
				{
					break;
				}

				at++;
			} while ((unsigned long*) v0 == a1);

			//loc_86D08
			a3[0] = v0;
		}
		v0 = a1[0];
	} while (a1 != ot);

	//loc_86D0C
	return at;
}

void draw_rotate_sprite(long a0, long a1, long a2)//5F134, 5FE14 (F)
{
	long t0;
	short* r_cossinptr;
	long t6;
	long t5;
	long t1;
	long t4;

	DelRotAng = (DelRotAng - 52) & 0xFFF;
	r_cossinptr = &rcossin_tbl[DelRotAng * 2];

	t6 = ((-a2 / 2) * r_cossinptr[0]) / 4096;
	t5 = ((-a2 / 2) * r_cossinptr[1]) / 4096;

	*(long*) &db.polyptr[4] = 0x2C808080;
	*(long*) &db.polyptr[12] = 0;
	*(long*) &db.polyptr[20] = 0x1303F00;

	t0 = t6 - t5;
	a2 = -t6;
	t4 = a2 - t5;
	a2 += t5;
	t1 = t6 + t5;

	*(short*) &db.polyptr[8] = t0 + (t0 / 2) + a0;
	*(short*) &db.polyptr[10] = t5 + t6 + a1;

	*(short*) &db.polyptr[16] = t4 + (t4 / 2) + a0;
	*(short*) &db.polyptr[18] = -t5 + t6 + a1;


	*(short*) &db.polyptr[24] = t1 + (t1 / 2) + a0;
	*(short*) &db.polyptr[26] = (t5 - t6) + a1;

	*(short*) &db.polyptr[28] = 0x3F;//width/height of loading cd?
	*(short*) &db.polyptr[36] = 0x3F3F;

	*(short*) &db.polyptr[32] = a2 + (a2 / 2) + a0;
	*(short*) &db.polyptr[34] = a1 + (-t5 - t6);

	*(long*) &db.polyptr[0] = db.ot[0] | 0x09000000;
	db.ot[0] = (unsigned long)&db.polyptr[0];
	
	db.polyptr += 0x28;//sizeof(POLY_F3); * 2?

	*(long*) &db.polyptr[4] = 0x2C808080;
	*(long*) &db.polyptr[8] = 0x780100;
	*(long*) &db.polyptr[12] = 0x6800;
	*(long*) &db.polyptr[16] = 0x7801FF;


	*(long*) &db.polyptr[20] = 0x13468FF;
	*(long*) &db.polyptr[24] = 0xEF0100;
	*(short*) &db.polyptr[28] = 0xDF00;
	*(long*) &db.polyptr[32] = 0xEF01FF;

	*(short*) &db.polyptr[36] = 0xDFFF;

	*(long*) &db.polyptr[0] = db.ot[0] | 0x9000000;
	db.ot[0] = (unsigned long)db.polyptr;
	
	sizeof(POLY_G3);
	db.polyptr += 0x28;
	return;
}

void GPU_SetScreenPosition(short x, short y)//5F360(<), 60040(<)
{
	db.disp[0].screen.x = x;
	db.disp[0].screen.y = y;
	db.disp[1].screen.x = x;
	db.disp[1].screen.y = y;

	return;
}
