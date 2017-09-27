#include "GPU.H"

#include "PROFILE.H"

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
	//Should be safe to use 32-bit ptrs tho
	db.order_table[0] = (unsigned long*)((unsigned long) pBuffers & 0xFFFFFF);
	db.order_table[1] = (unsigned long*)((unsigned long) &pBuffers[nOTSize] & 0xFFFFFF);
	db.nOTSize = nOTSize;
	db.pickup_order_table[0] = (unsigned long*)((unsigned long)GadwOrderingTables_V2 & 0xFFFFFF);
	db.pickup_order_table[0] = (unsigned long*)((unsigned long)&GadwOrderingTables_V2[256] & 0xFFFFFF);

	return;
}

void GPU_UsePolygonBuffers(unsigned long* pBuffers, int nPBSize)
{
	db.nPBSize = nPBSize;
	db.poly_buffer[0] = (unsigned long*)((unsigned long)pBuffers & 0xFFFFFF);
	db.poly_buffer[1] = (unsigned long*)((unsigned long)&pBuffers[nPBSize] & 0xFFFFFF);

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
	db.polyptr = db.poly_buffer[db.current_buffer];
	db.curpolybuf = db.poly_buffer[db.current_buffer];

	//db.polybuf_limit = db.poly_buffer[db.current_buffer] + &loc_19640;//Illegal

	ClearOTagR(&db.order_table[db.current_buffer], db.nOTSize);

	db.pickup_ot = db.pickup_order_table[db.current_buffer];

	return;
}

int GPU_FlipNoIdle()//5E078, 5F264(!)
{

	//ret LnFlipFrame
	return 0;
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

void GPU_EndScene()//5DFDC(<), ?(!)
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

	lw	$a0, 0x3640($gp)//db.ot[0];
	lw	$a1, 0x3650($gp)//db.nOTSize
	jal	sub_86CC4
	nop

	ProfileRGB(-1, -1, -1);

	a0 = db.nOTSize;
	do_gfx_debug_mode(&db.ot[db.nOTSize - 1]);

	ProfileRGB(0, -1, -1);
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