#include "MISC.H"
#include "CONTROL.H"
#include "CAMERA.H"
#include "GPU.H"
#include "LOAD_LEV.H"
#include "PSXINPUT.H"
#include "SPECIFIC.H"
#include "TEXT_S.H"

#include <EMULATOR.H>
#include <LIBETC.H>
#include "GAMEFLOW.H"
#include "SHADOWS.H"

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

void S_LongMemCpy(unsigned long* pDest, unsigned long* pSrc, unsigned long size) //5E964(<), ? (F)
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

void DrawF4(unsigned short x, unsigned short y, unsigned short w, unsigned short h, int otnum, int color) //5EDF8
{
	if ((unsigned long)db.polyptr < (unsigned long)db.polybuf_limit)
	{
		POLY_F4* ptr = (POLY_F4*)db.polyptr;

		setPolyF4(ptr);
		setSemiTrans(ptr, TRUE);

		setRGB0(ptr, getR(color), getG(color), getB(color));

		setXYWH(ptr, x, y, w, h);

		addPrim(db.ot + otnum, ptr);
		
		db.polyptr += sizeof(POLY_F4);
	}
	//locret_5EE70
}

void DrawTPage(unsigned char otnum, unsigned char tpage) //5EE78(<), 5FB58(<)
{
	if ((unsigned long)db.polyptr < (unsigned long)db.polybuf_limit)
	{
		setDrawTPage(db.polyptr, FALSE, FALSE, tpage * 32);

		addPrim(db.ot + otnum, db.polyptr);

		db.polyptr += sizeof(DR_TPAGE);
	}
}

void DrawLineH(unsigned short x, unsigned short y, unsigned short width, unsigned char otnum, unsigned long color1, unsigned long color2)//5EECC(<)
{
	if ((unsigned long)db.polyptr < (unsigned long)db.polybuf_limit)
	{
		LINE_G2* ptr = (LINE_G2*)db.polyptr;

		setLineG2(ptr);
		setSemiTrans(ptr, TRUE);
		setlen(ptr, 9);

		ptr->p1 = getcode(ptr);

		setRGB0(ptr, getR(color1), getG(color1), getB(color1));
		setRGB1(ptr, getR(color2), getG(color2), getB(color2));
		setXY2(ptr, x, y, x + width / 2, y);

		addPrim(db.ot + otnum, ptr);

		ptr++;
		db.polyptr += sizeof(LINE_G2);

		setcode(ptr, 0);
		setaddr(ptr, 0);

		ptr->p1 = getcode(ptr);
	
		setRGB0(ptr, getR(color2), getG(color2), getB(color2));
		setRGB1(ptr, getR(color1), getG(color1), getB(color1));
		setXY2(ptr, x + width / 2 + 1, y, x + width - 1, y);

		db.polyptr += sizeof(LINE_G2);
	}//locret_5EF7C
}

void DrawLineV(unsigned short x, unsigned short y, unsigned short height, unsigned char otnum, unsigned long color1, unsigned long color2)//5EF84(<),
{
	if ((unsigned long)db.polyptr < (unsigned long)db.polybuf_limit)
	{
		LINE_G2* ptr = (LINE_G2*)db.polyptr;

		setLineG2(ptr);
		setSemiTrans(ptr, TRUE);
		setlen(ptr, 9);

		ptr->p1 = getcode(ptr);

		setRGB0(ptr, getR(color1), getG(color1), getB(color1));
		setRGB1(ptr, getR(color2), getG(color2), getB(color2));
		setXY2(ptr, x, y + 1, x, y + height / 2);

		addPrim(db.ot + otnum, ptr);

		ptr++;
		db.polyptr += sizeof(LINE_G2);

		setcode(ptr, 0);
		setaddr(ptr, 0);

		ptr->p1 = getcode(ptr);

		setRGB0(ptr, getR(color2), getG(color2), getB(color2));
		setRGB1(ptr, getR(color1), getG(color1), getB(color1));
		setXY2(ptr, x, y + height / 2 + 2, x, y + height - 2);

		db.polyptr += sizeof(LINE_G2);
	}//locret_5F038
}

void LOAD_VSyncHandler() //5F074(<), 5FD54(<) (F)
{
	int a0, a1, a2;

	if (!LtLoadingBarEnabled)
	{
		return;
	}

	//loc_5F08C
	GPU_BeginScene();

	a0 = 440; //x?
	a1 = 200; //y?
	a2 = 64; //cd width or height?

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

void LOAD_DrawEnable(unsigned char isEnabled) //5F2C8, 5FFA8
{
	LtLoadingBarEnabled = isEnabled;
}

void GPU_BeginScene() //5F0F0(<), 5FDD0(<)
{
	db.ot = db.order_table[db.current_buffer];
	db.polyptr = (char*)db.poly_buffer[db.current_buffer];
	db.curpolybuf = (char*)db.poly_buffer[db.current_buffer];
	db.polybuf_limit = (char*)(db.poly_buffer[db.current_buffer] + 26000);
	db.pickup_ot = db.pickup_order_table[db.current_buffer];
	ClearOTagR(db.order_table[db.current_buffer], db.nOTSize);

	Emulator_BeginScene();
}

void draw_rotate_sprite(long x, long y, long a2) //5F134, 5FE14 (F)
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

	POLY_FT4* ptr = (POLY_FT4*)db.polyptr;

	t0 = t6 - t5;
	a2 = -t6;
	t4 = a2 - t5;
	a2 += t5;
	t1 = t6 + t5;

	setPolyFT4(ptr);
	setRGB0(ptr, 128, 128, 128);

	setUV4(ptr, 0, 0, 0, 63, 63, 0, 63, 63);
	setXY4(ptr,
		x + t0 + t0 / 2, y + t5 + t6,
		x + t4 + t4 / 2, y - t5 + t6,
		x + t1 + t1 / 2, y + t5 - t6,
		x + a2 + a2 / 2, y - t5 - t6);
	setClut(ptr, 0, 0);
	setTPage(ptr, 2, 1, 0, 256);

	addPrim(db.ot, ptr);

	db.polyptr += sizeof(POLY_FT4);
	ptr++;

	setPolyFT4(ptr);
	setRGB0(ptr, 128, 128, 128);

	setUV4(ptr, 0, 104, 255, 104, 0, 223, 255, 223);
	setXY4(ptr,
		256, 120,
		511, 120,
		256, 239,
		511, 239);
	setClut(ptr, 0, 0);
	setTPage(ptr, 2, 1, 256, 256);

	addPrim(db.ot, ptr);

	db.polyptr += sizeof(POLY_FT4);
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
void GPU_ClearVRAM() //5F2D0(<), 5FFB0(<) (F) (D) (ND)
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

void clear_a_rect(RECT16* r) //5F334(<), 60014(<) (F) (D) (ND)
{
	ClearImage(r, 0, 48, 0);
	return;
}

void GPU_GetScreenPosition(short* x, short* y) //5F34C, ? (*) (F) (D) (ND)
{
	*x = db.disp[0].screen.x;
	*y = db.disp[0].screen.y;
	return;
}

void GPU_SetScreenPosition(short x, short y) //5F360(<), 60040(<)
{
	db.disp[0].screen.x = x;
	db.disp[0].screen.y = y;
	db.disp[1].screen.x = x;
	db.disp[1].screen.y = y;

	return;
}

void GPU_SyncBothScreens() //5F374(<), 60054(<)
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
void GPU_FlipToBuffer(int buffer_index) //5F3C8(<), 600A8(<) (F) (D) (ND)
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

void frig_with_monitor_screen(int a0)
{
	UNIMPLEMENTED();
}

void S_AnimateTextures(long nFrames)
{
#if DEBUGSKIP || 1///@FIXME @zdimension this doesn't work.
	return;
#endif

	AnimComp += nFrames;

	while (AnimComp > 5)
	{
		uint16_t* ptr = AnimTextureRanges;

		for (uint16_t i = *(ptr++); i > 0; i--, ptr++)
		{
			MMTEXTURE tmp = RoomTextInfo[*(ptr + 1)];

			for (uint16_t j = *ptr++; j > 0; j--, ptr++)
			{
				RoomTextInfo[*ptr] = RoomTextInfo[*(ptr + 1)];
			}

			RoomTextInfo[*ptr] = tmp;
		}

		AnimComp -= 5;
	}

	if (gfUVRotate) // 19d8
	{
		uint16_t* t3 = AnimTextureRanges;
		AnimatingTexturesVOffset = (AnimatingTexturesVOffset - gfUVRotate * (nFrames / 2)) & 0x1f;
		if (nAnimUVRanges > 0)
		{
			short (*t2)[8][3] = AnimatingTexturesV;

			for (int i = 0; i < nAnimUVRanges; i++, t2++)
			{
				unsigned short num = *t3++;
				if (num > 0)
				{
					short* t1 = t2[i][num];

					for (int j = 0; j <= num; j++, t1-=3, t3++)
					{
						int t0 = 32;
						int a2 = AnimatingTexturesVOffset;
						MMTEXTURE* a0tm = &RoomTextInfo[*t3];
						for (int a3 = 0; a3 < 3; a3++, a2 >>= 1, t0 >>= 1)
						{
							uint8_t v0__ = (uint8_t)(t1[a3] >> 8);

							a0tm->t[a3].v0 = v0__ + a2;

							a0tm->t[a3].v1 = v0__ + a2;

							a0tm->t[a3].v2 = v0__ + a2 + t0;

							a0tm->t[a3].v3 = v0__ + a2 + t0;
						}
					}
				}
			}
		}
	}

	frig_with_monitor_screen(0);
}

void PrintGauge(int x, int y, int length)
{
	S_DrawGouraudBar(x & 0xFFFF, y & 0xFFFF, 100, (length * 100) / 255, &dashBarColourSet);
}

long GetRandomControl() //5E9F0, 926F8 (F)
{
	rand_1 = (rand_1 * 0x41C64E6D) + 0x3039;
	return (rand_1 >> 16) & 0x7FFF;
}

void SeedRandomControl(long seed) //(F)
{
	rand_1 = seed;
}

long GetRandomDraw() //5EA18, 5F6F8 (F)
{
	rand_2 = (rand_2 * 0x41C64E6D) + 0x3039;
	return (rand_2 >> 16) * 0x7FFF;
}

void SeedRandomDraw(long seed) //(F)
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
