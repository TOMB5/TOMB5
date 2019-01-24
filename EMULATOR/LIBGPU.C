#include "LIBGPU.H"

#include "EMULATOR.H"

#define GL_GLEXT_PROTOTYPES 1
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_opengl_glext.h>

#include <stdio.h>
#include <cstring>
#include <cassert>
#include <LIBETC.H>

unsigned short vram[1024 * 512];
DISPENV word_33BC;
int dword_3410 = 0;
char byte_3352 = 0;

void* off_3348[]=
{
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL
};

int ClearImage(RECT16* rect, u_char r, u_char g, u_char b)
{
	for (int y = rect->y; y < 512; y++)
	{
		for (int x = rect->x; x < 1024; x++)
		{
			unsigned short* pixel = vram + (y * 1024 + x);

			if (x >= rect->x && x < rect->x + rect->w && 
				y >= rect->y && y < rect->y + rect->h)
			{
				pixel[0] = 1 << 15 | ((r >> 3) << 10) | ((g >> 3) << 5) | ((b >> 3));
			}
		}
	}

	return 0;
}

int DrawSync(int mode)
{
	return 0;
}

int LoadImagePSX(RECT16* rect, u_long* p)
{
	unsigned short* dst = (unsigned short*)p;

	for (int y = rect->y; y < 512; y++)
	{
		for (int x = rect->x; x < 1024; x++)
		{
			unsigned short* src = vram + (y * 1024 + x);

			if (x >= rect->x && x < rect->x + rect->w &&
				y >= rect->y && y < rect->y + rect->h)
			{
				src[0] = *dst++;

				//pixel[0] = 1 << 15 | ((r >> 3) << 10) | ((g >> 3) << 5) | ((b >> 3));
			}
		}
	}

#if _DEBUG
	FILE* f = fopen("VRAM.BIN", "wb");
	fwrite(&vram[0], 1, 1024 * 512 * 2, f);
	fclose(f);
#endif

	return 0;
}

int ResetGraph(int mode)
{
	return 0;
}

int SetGraphDebug(int level)
{
	return 0;
}

int StoreImage(RECT16 * RECT16, u_long * p)
{
	return 0;
}

u_long * ClearOTag(u_long * ot, int n)
{
	assert(0);
	return 0;
}

u_long* ClearOTagR(u_long* ot, int n)
{
	//v0 = byte_3352;
	//s0 = ot
	//s1 = n

	//v0 = v0 < 2 ? 1 : 0
	if (byte_3352 > 1)
	{
		///GPU_printf("ClearOTagR(%08x,%d)...\n", ot, n);
	}

	//loc_CB0
//	((void*)off_3348[11])();

	return 0;
}

void SetDispMask(int mask)
{
}

DISPENV* GetDispEnv(DISPENV* env)//(F)
{
	memcpy(env, &word_33BC, sizeof(DISPENV));
	return env;
}

DISPENV* PutDispEnv(DISPENV* env)//To Finish
{
	memcpy((char*)&word_33BC, env, sizeof(DISPENV));
	return 0;
}

DISPENV* SetDefDispEnv(DISPENV* env, int x, int y, int w, int h)//(F)
{
	env->disp.x = x;
	env->disp.y = y;
	env->disp.w = w;
	env->screen.x = 0;
	env->screen.y = 0;
	env->screen.w = 0;
	env->screen.h = 0;
	env->isrgb24 = 0;
	env->isinter = 0;
	env->pad1 = 0;
	env->pad0 = 0;
	env->disp.h = h;
	return 0;
}

DRAWENV* PutDrawEnv(DRAWENV* env)
{
	return NULL;
}

DRAWENV* SetDefDrawEnv(DRAWENV* env, int x, int y, int w, int h)//(F)
{
	env->clip.x = x;
	env->clip.y = y;
	env->clip.w = w;
	env->tw.x = 0;
	env->tw.y = 0;
	env->tw.w = 0;
	env->tw.h = 0;
	env->r0 = 0;
	env->g0 = 0;
	env->b0 = 0;
	env->dtd = 1;
	env->clip.h = h;

	if (GetVideoMode() == 0)
	{
		env->dfe = h < 0x121 ? 1 : 0;
	}
	else
	{
		env->dfe = h < 0x101 ? 1 : 0;
	}

	env->ofs[0] = x;
	env->ofs[1] = y;

	env->tpage = 10;
	env->isbg = 0;

	return env;
}

u_long DrawSyncCallback(void(*func)(void))
{

	return u_long();
}

void DrawOTagEnv(u_long* p, DRAWENV* env)
{
	printf("Debug");
}
