#include "MISC.H"
#include "CONTROL.H"
#include "CAMERA.H"
#include "GPU.H"
#include "LOAD_LEV.H"
#include "SPECIFIC.H"
#include "TEXT_S.H"

#include <EMULATOR.H>
#include <LIBETC.H>

#if PSXPC_VERSION || PSXPC_TEST
	#include <stdint.h>
#endif

#if PSX_VERSION && !PSXPC_TEST
typedef unsigned int uintptr_t;
#endif

void S_MemSet(char* p, int value, int length)
{
	int size;

	if (length != 0)
	{
		if (length > 3)
		{
			value |= value << 8;
			value |= value << 16;

			if (((uintptr_t)p) & 3)
			{
				size = 4 - (((uintptr_t)p) & 3);
				length -= 4 - (((uintptr_t)p) & 3);

				//loc_5E918
				while (size--)
					*p++ = value;

			}
			//loc_5E928
			size = length >> 2;
			if ((length >> 2))
			{
				length &= 3;

				//loc_5E934
				while (size--)
				{
					((int*)p)[0] = value;
					p += 4;
				}
			}
		}
		//loc_5E94C
		while (length-- != 0)
			*p++ = value;
	}
}

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

void DrawF4(unsigned short x, unsigned short y, unsigned short w, unsigned short h, int unk, int unk2)//5EDF8
{
	x &= 0xFFFF;
	y &= 0xFFFF;
	w &= 0xFFFF;
	h &= 0xFFFF;

	if ((unsigned long)db.polyptr < (unsigned long)db.polybuf_limit)
	{
		((int*)db.polyptr)[1] = unk2;
		((short*)db.polyptr)[4] = x;
		((short*)db.polyptr)[5] = y;
		((short*)db.polyptr)[6] = x + w;
		((short*)db.polyptr)[7] = y;
		((short*)db.polyptr)[8] = x;
		((short*)db.polyptr)[9] = y + h;
		((short*)db.polyptr)[10] = x + w;
		((short*)db.polyptr)[11] = y + h;

		((int*)db.polyptr)[0] = db.ot[unk] | 0x5000000;
		db.ot[unk] = (unsigned long)db.polyptr;
		db.polyptr += 0x18;
	}
	//locret_5EE70
}

void DrawTPage(unsigned char a0, unsigned char a1)//5EE78(<), 5FB58(<)
{
	a0 &= 0xFF;
	a1 &= 0xFF;

	if ((unsigned long)db.polyptr < (unsigned long)db.polybuf_limit)
	{
		((int*)db.polyptr)[0] = db.ot[a0] | 0x1000000;
		db.ot[a0] = (unsigned long)db.polyptr;
		((int*)db.polyptr)[1] = (a1 << 5) | 0xE1000000;
		db.polyptr += sizeof(DR_TPAGE);
	}
}

void DrawLineH(unsigned short a0, unsigned short a1, unsigned short a2, unsigned char a3, unsigned long a4, unsigned long a5)//5EECC(<)
{
	if ((unsigned long)db.polyptr < (unsigned long)db.polybuf_limit)
	{
		((int*)db.polyptr)[1] = (a4 & 0xFFFFFF) | 0x52000000;
		((short*)db.polyptr)[4] = a0;
		((short*)db.polyptr)[5] = a1;
		((int*)db.polyptr)[3] = (a5 & 0xFFFFFF) | 0x52000000;
		((short*)db.polyptr)[8] = a0 + (a2 >> 1);
		((short*)db.polyptr)[9] = a1;
		((int*)db.polyptr)[6] = (a5 & 0xFFFFFF) | 0x52000000;
		((short*)db.polyptr)[14] = a0 + (a2 >> 1) + 1;
		((short*)db.polyptr)[15] = a1;
		((int*)db.polyptr)[8] = (a4 & 0xFFFFFF) | 0x52000000;
		((short*)db.polyptr)[18] = (a0 + a2) - 1;
		((short*)db.polyptr)[19] = a1;
		((int*)db.polyptr)[5] = 0;
		((int*)db.polyptr)[0] = db.ot[a3] | 0x9000000;
		db.ot[a3] = (unsigned long)db.polyptr;
		db.polyptr += sizeof(LINE_G4);
	}//locret_5EF7C
}

void DrawLineV(unsigned short a0, unsigned short a1, unsigned short a2, unsigned char a3, unsigned long a4, unsigned long a5)//5EF84(<),
{
	if ((unsigned long)db.polyptr < (unsigned long)db.polybuf_limit)
	{
		((int*)db.polyptr)[1] = (a4 & 0xFFFFFF) | 0x52000000;
		((short*)db.polyptr)[4] = a0;
		((short*)db.polyptr)[5] = a1 + 1;
		((int*)db.polyptr)[3] = (a5 & 0xFFFFFF) | 0x52000000;
		((short*)db.polyptr)[8] = a0;
		((short*)db.polyptr)[9] = a1 + (a2 >> 1);
		((int*)db.polyptr)[6] = (a5 & 0xFFFFFF) | 0x52000000;
		((short*)db.polyptr)[14] = a0;
		((short*)db.polyptr)[15] = a1 + (a2 >> 1) + 2;
		((int*)db.polyptr)[8] = (a4 & 0xFFFFFF) | 0x52000000;
		((short*)db.polyptr)[18] = a0;
		((short*)db.polyptr)[19] = a1 + a2 - 2;
		((int*)db.polyptr)[5] = 0;
		((int*)db.polyptr)[0] = db.ot[a3] | 0x9000000;
		db.ot[a3] = (unsigned long)db.polyptr;
		db.polyptr += sizeof(LINE_G4);
	}//locret_5F038
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
	db.polybuf_limit = (char*)(db.poly_buffer[db.current_buffer] + 26000);
	db.pickup_ot = db.pickup_order_table[db.current_buffer];
	ClearOTagR(db.order_table[db.current_buffer], db.nOTSize);

	Emulator_BeginScene();
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
void GPU_ClearVRAM()//5F2D0(<), 5FFB0(<) (F) (D) (ND)
{
	RECT16 r;

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

	return;
}

void clear_a_rect(RECT16* r)//5F334(<), 60014(<) (F) (D) (ND)
{
	ClearImage(r, 0, 48, 0);
	return;
}

void GPU_GetScreenPosition(short* x, short* y)//5F34C, ? (*) (F) (D) (ND)
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
	}
	else
	{
		//loc_5F3A8
		MoveImage(&db.disp[0].disp, db.disp[1].disp.x, db.disp[1].disp.y);
	}

	DrawSync(0);

	return;
}

///@Gh0stblade - Not sure why this is so unoptimal, we can basically &disp[db.current_buffer]... double check code.
void GPU_FlipToBuffer(int buffer_index)//5F3C8(<), 600A8(<) (F) (D) (ND)
{
	DrawSync(0);
	VSync(0);

	if (buffer_index & 1)
	{
		PutDispEnv(&db.disp[1]);
	}
	else
	{
		PutDispEnv(&db.disp[0]);
	}

	if (buffer_index & 1)
	{
		PutDrawEnv(&db.draw[1]);
	}
	else
	{
		PutDrawEnv(&db.draw[0]);
	}

	db.current_buffer = buffer_index & 1 ^ 1;

	return;
}

void S_AnimateTextures(long nFrames)
{
	UNIMPLEMENTED();
}

void PrintGauge(int x, int y, int length)
{
	UNIMPLEMENTED();
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

void S_MemCpy(char* pSrc, char* pDest, int size)
{
	if (size > 0)
	{
		while (size-- > 0)
			*pSrc++ = *pDest++;
	}
}
