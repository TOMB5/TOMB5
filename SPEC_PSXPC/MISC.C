#include "MISC.H"
#include "CONTROL.H"
#include "CAMERA.H"
#include "GPU.H"
#include "LOAD_LEV.H"
#include "SPECIFIC.H"

#include <SDL.h>
#include <SDL_opengl.h>

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

void DrawF4(unsigned short x, unsigned short y, unsigned short w, unsigned short h)//5EDF8
{
	S_Warn("[DrawF4] - Unimplemented!\n");
}

void DrawTPage(unsigned char a0, unsigned char a1)//5EE78(<), 5FB58(<)
{
	S_Warn("[DrawTPage] - Unimplemented!\n");
}

void DrawLineH(long a0, long a1, long a2, long a3)//5EECC(<)
{
	S_Warn("[DrawLineH] - Unimplemented!\n");
}

void DrawLineV(long a0, long a1, long a2, long a3)//5EF84(<),
{
	S_Warn("[DrawLineV] - Unimplemented!\n");
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
	
	//sizeof(POLY_G3);
	db.polyptr += 0x28;
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
#if 0
	RECT r;

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
#endif
	return;
}

#if 0
void clear_a_rect(RECT* r)//5F334(<), 60014(<) (F)
{

	return;
}
#endif

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
	db.current_buffer ^= 1;
	if (db.current_buffer != 0)
	{
		//MoveImage(&db.disp[1].disp, db.disp[0].disp.x, db.disp[0].disp.y);
		//TODO: Verify ra += 0x10;! prolly else skip loc_5F3A8 (implemented but should be checked).
	}
	else
	{
		//loc_5F3A8
		//MoveImage(&db.disp[0].disp, db.disp[1].disp.x, db.disp[1].disp.y);
	}

	return;
}

//@Gh0stblade - Not sure why this is so unoptimal, we can basically &disp[db.current_buffer]... double check code.
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

void S_AnimateTextures(long nFrames)
{
	S_Warn("[S_AnimateTextures] - Unimplemented!\n");
}

long GetRandomControl()//5E9F0, 926F8 (F)
{
	rand_1 = (rand_1 * 0x41C64E6D) + 0x3039;
	return (rand_1 >> 16) & 0x7FFF;
}

void SeedRandomControl(long seed)//(F)
{
	rand_1 = seed;
}

long GetRandomDraw()//5EA18, 5F6F8 (F)
{
	rand_2 = (rand_2 * 0x41C64E6D) + 0x3039;
	return (rand_2 >> 16) * 0x7FFF;
}

void SeedRandomDraw(long seed)//(F)
{
	rand_2 = seed;
}
