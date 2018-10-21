#include "MISC.H"

#include "CAMERA.H"
#include "GPU.H"
#include "LOAD_LEV.H"
#include "SPECIFIC.H"

#include <SYS/TYPES.H>
#include <LIBETC.H>
#ifndef USE_ASM
void S_LongMemCpy(unsigned long* pDest, unsigned long* pSrc, unsigned long size)//5E964(<), ? (F)
{
	int i;

	if (size > 0)
	{
		for (i = size / sizeof(unsigned long); i > 0; i--, pDest += 4, pSrc += 4)
		{
			//loc_5E974
			pDest[0] = pSrc[0];
			pDest[1] = pSrc[1];
			pDest[2] = pSrc[2];
			pDest[3] = pSrc[3];
		}

		//loc_5E9AC
		for (i = size & 3; i > 0; i--)
		{
			*pDest++ = *pSrc++;
		}
	}
}

void DrawF4(unsigned short x, unsigned short y, unsigned short w, unsigned short h, unsigned short unk, unsigned short unk2)//5EDF8
{
	S_Warn("[DrawF4] - Unimplemented!\n");
}

void DrawTPage(unsigned char a0, unsigned char a1)//5EE78(<), 5FB58(<) (F)
{
#if 0
	if ((unsigned long) db.polyptr < (unsigned long)db.polybuf_limit)
	{
		*(long*) &db.ot[a0] = (long)db.polyptr;
		*(long*) &db.polyptr[0] = db.ot[a0] | 0x01000000;
		*(long*) &db.polyptr[4] = a1 << 5 | 0xE1000000;
	}
#endif
}

void DrawLineH(long a0, long a1, long a2, long a3)//5EECC(<)
{
	return;

#if 0
	a0 &= 0xFFFF;
	a1 &= 0xFFFF;
	a2 &= 0xFFFF;
	a3 &= 0xFFFF;

	if ((unsigned long) db.polyptr < (unsigned long) db.polybuf_limit)
	{

	}//locret_5EF7C
#if 0

		lw	$t1, arg_10($sp)
		lw	$t2, arg_14($sp)
		li	$at, 0xFFFFFF
		and $t1, $at
		and	$t2, $at
		lui	$at, 0x5200
		or $t2, $at
		or $t1, $at
		srl	$v0, $a2, 1
		addu	$v0, $a0, $v0
		sw	$t1, 4($t0)
		sh	$a0, 8($t0)
		sh	$a1, 0xA($t0)
		sw	$t2, 0xC($t0)
		sh	$v0, 0x10($t0)
		sh	$a1, 0x12($t0)
		addiu	$v0, 1
		sw	$t2, 0x18($t0)
		sh	$v0, 0x1C($t0)
		sh	$a1, 0x1E($t0)
		addu	$v0, $a0, $a2
		addiu	$v0, -1
		sw	$t1, 0x20($t0)
		sh	$v0, 0x24($t0)
		sh	$a1, 0x26($t0)
		lw	$t2, 0x3640($gp)
		sll	$a3, 2
		addu	$a3, $t2
		lw	$v0, 0($a3)
		lui	$at, 0x900
		or $v0, $at
		sw	$t0, 0($a3)
		sw	$v0, 0($t0)
		sw	$zero, 0x14($t0)
		addiu	$t0, 0x28

		locret_5EF7C:
	jr	$ra
		sw	$t0, 0x3644($gp)//db.polyptr
#endif
#endif
}

void DrawLineV(long a0, long a1, long a2, long a3)//5EF84(<), //misc
{
	return;
#if 0
	a0 &= 0xFFFF;
	a1 &= 0xFFFF;
	a2 &= 0xFFFF;
	a3 &= 0xFFFF;

	if ((unsigned long) db.polyptr < (unsigned long) db.polybuf_limit)
	{

	}//locret_5F038
#if 0
		lw	$t1, arg_10($sp)
		lw	$t2, arg_14($sp)
		li	$at, 0xFFFFFF
		and $t1, $at
		and	$t2, $at
		lui	$at, 0x5200
		or $t2, $at
		or $t1, $at
		addiu	$v0, $a1, 1
		sw	$t1, 4($t0)
		sh	$a0, 8($t0)
		sh	$v0, 0xA($t0)
		sw	$t2, 0xC($t0)
		srl	$v0, $a2, 1
		addu	$v0, $a1, $v0
		sh	$a0, 0x10($t0)
		sh	$v0, 0x12($t0)
		addiu	$v0, 2
		sw	$t2, 0x18($t0)
		sh	$a0, 0x1C($t0)
		sh	$v0, 0x1E($t0)
		sw	$t1, 0x20($t0)
		addu	$v0, $a1, $a2
		addiu	$v0, -2
		sh	$a0, 0x24($t0)
		sh	$v0, 0x26($t0)
		lw	$t2, 0x3640($gp)
		sll	$a3, 2
		addu	$a3, $t2
		lw	$v0, 0($a3)
		lui	$at, 0x900
		or $v0, $at
		sw	$t0, 0($a3)
		sw	$v0, 0($t0)
		sw	$zero, 0x14($t0)
		addiu	$t0, 0x28

		locret_5F038:
	jr	$ra
		sw	$t0, 0x3644($gp)//db.polyptr
#endif
#endif
}

void LOAD_VSyncHandler()//5F074(<), 5FD54(<) (F)
{
	int a0, a1, a2;
	if (!LtLoadingBarEnabled)
	{
		return;
	}

	//loc_5F08C
	GPU_BeginScene();

	a0 = 440;//x?
	a1 = 200;//y?
	a2 = 64;//cd width or height?

	if (_first_time_ever)
	{
		a0 += 24;
		a1 += 8;
		a2 = 48;
	}

	//loc_5F0B4
	draw_rotate_sprite(a0, a1, a2);
	db.current_buffer ^= 1;
	GnLastFrameCount = 0;
	DrawOTagEnv(&db.ot[db.nOTSize - 1], &db.draw[0]);

	return;
}


void LOAD_DrawEnable(unsigned char isEnabled)//5F2C8, 5FFA8
{
	LtLoadingBarEnabled = isEnabled;
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
	
	db.polyptr += sizeof(POLY_GT3);

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
	
	db.polyptr += sizeof(POLY_GT3);

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

void GPU_GetScreenPosition(short* x, short* y)//5F34C, ?
{
	*x = db.disp[0].screen.x;
	*y = db.disp[0].screen.y;
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

void S_AnimateTextures(long nFrames)
{
	S_Warn("[S_AnimateTextures] - Unimplemented!\n");
}
#endif
