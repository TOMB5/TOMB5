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
	db.pickup_order_table[0] = &db.disp[1];
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
	db.polyptr = (char*)&db.poly_buffer[db.current_buffer];
	db.curpolybuf = (char*)&db.poly_buffer[db.current_buffer];
	db.polybuf_limit = (char*)(&db.poly_buffer[db.current_buffer]) + 26000;
	db.pickup_ot = db.pickup_order_table[db.current_buffer];
	ClearOTagR(db.order_table[db.current_buffer], db.nOTSize);

	return;
}

int GPU_FlipNoIdle()//5E078(<), 5F264(<)
{
#if INTERNAL
	if (ProfileDraw)
	{
		ProfileRGB(255, 255, 255);
		ProfileAddOT(&db.ot[0]);
	}//loc_5E0B0
#endif

	DrawSync(0);//TODO confirm retail is sub_6B144 draw sync

#if _INTERNAL
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

#if INTERNAL
	ProfileStartCount();
#endif

	db.current_buffer ^= 1;

	return LnFlipFrame;
}

void GPU_GetScreenPosition(short* x, short* y)//5F34C, ?
{
	*x = db.disp[0].screen.x;
	*y = db.disp[0].screen.y;
	return;
}

/*   PSX VRAM   (H)
 *  ----------- 512px
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
void GPU_FlipToBuffer(int buffer_index)//5F3C8
{
	DISPENV* disp;
	DRAWENV* draw;

	DrawSync(0);
	VSync(0);

	if (buffer_index & 1)
	{
		disp = &db.disp[1];
	}
	else
	{
		disp = &db.disp[0];
	}

	//loc_5F3F4
	PutDispEnv(disp);

	if (buffer_index & 1)
	{
		draw = &db.draw[1];
	}
	else
	{
		draw = &db.draw[0];
	}

	//loc_5F408
	buffer_index &= 1 ^ 1;

	PutDrawEnv(draw);

	return;
}

void GPU_EndScene()//5DFDC(<), 5F23C(!)
{
#if 0
	//int nPolys;
	//static int nWorstPolys;

	lui	$v0, 0x4EC4
	int a0 = &db.polyptr[0];
	int v1 = &db.curpolybuf[0];
	int v0 = 0x4EC4EC4F;
	a0 -= v1;
	v0 = a0 * v0;
	a0 >>= 31;
	v1 = psxtextinfo->u2v2pad;
	v0 >>= 4;
	v0 -= a0;

	if (v1 < v0)
	{
		u2v2pad = v0;
	}//loc_5E020
	
	//loc_5E020
#endif

	OptimiseOTagR(&db.ot[0], db.nOTSize);

#if 0
	nop

	ProfileRGB(-1, -1, -1);

	a0 = db.nOTSize;
	do_gfx_debug_mode(&db.ot[db.nOTSize - 1]);

	ProfileRGB(0, -1, -1);
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

void draw_rotate_sprite(long a0, long a1, long a2)//5F134, 5FE14
{
	short* a3;

#if 1
	short t0;
	short* v0;
	short t6;
	short t5;
	long* a33;
	int t2;
	int at;
	long* t3;
	long v1;
	long t1;
	long t4;

	long v00;

	a3 = &rcossin_tbl[0];
	t0 = (DelRotAng - 52) & 0xFFF;
	a2 = -a2;
	v0 = &rcossin_tbl[t0 * 2];
	t6 = v0[0];
	a2 >>= 1;
	t6 = a2 * t6;

	t3 = &db.ot[0];//maybe current_buffer
	t5 = v0[1];
	a33 = db.polyptr;

	t2 = 0x2C808080;
	t5 = a2 * t5;

	at = 0x1303F00;
	DelRotAng = t0;
	*(int*) &db.polyptr[4] = t2;
	*(int*) &db.polyptr[12] = 0;
	*(int*) &db.polyptr[20] = at;

	t6 >>= 12;
	t5 >>= 12;

	t0 = t6 - t5;
	a2 = -t6;
	t4 = a2 - t5;
	a2 += t5;
	t1 = t6 - t5;

	v0 = t0 >> 1;
	v0 += a0;
	t0 += v0;

	v1 = t4 >> 1;
	v1 += a0;
	t0 += v0;

	v0 = a2 >> 1;
	v0 += a0;
	a2 += v0;

	v1 = t1 >> 1;
	v1 += a0;
	t1 += v1;

	v0 = t5 + t6;
	v0 = a1 + v0;
	v1 = -t5;

	*(short*) &db.polyptr[8] = t0;
	*(short*) &db.polyptr[10] = v0;

	v0 = v1 + t6;
	v0 += a1;

	*(short*) &db.polyptr[16] = t4;
	*(short*) &db.polyptr[18] = v0;

	v0 = t5 - t6;
	v0 += a1;
	v1 += t6;

	*(short*) &db.polyptr[24] = t1;
	*(short*) &db.polyptr[26] = v0;

	t4 = 0x3F;//width/height?

	*(short*) &db.polyptr[28] = t4;

	t4 = 0x3F3F;
	*(short*) &db.polyptr[36] = v0;

	a1 += v1;

	*(short*) &db.polyptr[32] = a2;
	*(short*) &db.polyptr[34] = a1;

	v00 = t3[0];
	at = 0x09000000;
	v00 |= at;

	t3[0] = a3;
	*(int*) &db.polyptr[0] = v00;

	a3 = &db.polyptr[0x28];

	v00 = 0x780100;
	v1 = 0x6800;
	a0 = 0x7801FF;

	*(int*) a3[4] = t2;
	*(int*) a3[8] = v00;
	*(int*) a3[12] = v1;
	*(int*) a3[16] = a0;

	at = 0x13468FF;
	v00 = 0xEF0100;
	v1 = 0xDF00;
	a0 = 0xEF01FF;

	*(int*) a3[20] = at;
	*(int*) a3[24] = v00;
	*(short*) a3[28] = v1;
	*(int*) a3[32] = a0;

	at = 0xDFFF;
	*(short*) a3[36] = at;

	v00 = t3[0];
	v00 |= 0x9000000;

	t3[0] = a3;
	a3[0] = v00;
	db.polyptr = &a3[0x28];



#endif
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