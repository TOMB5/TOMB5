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
#if USE_FRAME_BUFFERS
	char* pixelData = new char[rect->w*rect->h * 3];
	memset(pixelData, 0, rect->w*rect->h * 3);

	for (int y = 0; y < rect->w*rect->h * 3; y += 3)
	{
		pixelData[y + 0] = r;
		pixelData[y + 1] = g;
		pixelData[y + 2] = b;
	}

	GLuint blitFramebufferName = 0;
	glGenFramebuffers(1, &blitFramebufferName);
	glBindFramebuffer(GL_FRAMEBUFFER, blitFramebufferName);

	GLuint blitTexture = 0;
	glGenTextures(1, &blitTexture);

	glBindTexture(GL_TEXTURE_2D, blitTexture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, rect->w, rect->h, 0, GL_RGB, GL_UNSIGNED_BYTE, pixelData);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, blitTexture, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, blitFramebufferName);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, blitTexture, 0);
	glReadBuffer(GL_COLOR_ATTACHMENT0);

	glBindFramebuffer(GL_FRAMEBUFFER, vramFramebufferName);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, vramTexture, 0);
	glDrawBuffer(GL_COLOR_ATTACHMENT1);

	//tr glBlitNamedFramebuffer(blitFramebufferName, vramFramebufferName, 0, 0, rect->w, rect->h, 512,   0, 512+(rect->y*2), 256, GL_COLOR_BUFFER_BIT, GL_NEAREST);
	//tl glBlitNamedFramebuffer(blitFramebufferName, vramFramebufferName, 0, 0, rect->w, rect->h, 0  ,   0, 512+(rect->y*2), 256, GL_COLOR_BUFFER_BIT, GL_NEAREST);
	//bl glBlitNamedFramebuffer(blitFramebufferName, vramFramebufferName, 0, 0, rect->w, rect->h, 0,   256, 512,             512 + (rect->y * 2), GL_COLOR_BUFFER_BIT, GL_NEAREST);

	glBlitNamedFramebuffer(blitFramebufferName, vramFramebufferName, 0, 0, rect->w, rect->h, rect->x, rect->y, 512 + (rect->x * 2), 256 + rect->y, GL_COLOR_BUFFER_BIT, GL_NEAREST);
	printf("X: %d Y: %d W: %d H: %d\n", 0, rect->y, 512 + (rect->x * 2), rect->h);

#else
	for (int y = 0; y < 512; y++)
	{
		for (int x = 0; x < 1024; x++)
		{
			unsigned short* pixel = vram + (y * 1024 + x);

			if (x >= rect->x && x < rect->x + rect->w && 
				y >= rect->y && y < rect->y + rect->h)
			{
				pixel[0] = ((r >> 3) << 11) | ((g >> 3) << 6) | ((b >> 3) << 1) | 1;
			}
		}
	}
#endif
	return 0;
}

int DrawSync(int mode)
{
	return 0;
}

int LoadImagePSX(RECT16* rect, u_long* p)
{
#if USE_FRAME_BUFFERS
	GLuint blitFramebufferName = 0;
	glGenFramebuffers(1, &blitFramebufferName);
	glBindFramebuffer(GL_FRAMEBUFFER, blitFramebufferName);

	GLuint blitTexture = 0;
	glGenTextures(1, &blitTexture);

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, blitTexture);

	// Give an empty image to OpenGL ( the last "0" )
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, rect->w, rect->h, 0, GL_RGB, GL_UNSIGNED_SHORT_4_4_4_4_REV, (unsigned short*)p);

	///glCopyBufferSubData(blitTexture, vramTexture, 0, 0, rect->w * rect->h * 4)

	// Poor filtering. Needed !
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, blitTexture, 0);

	glBindFramebuffer(GL_FRAMEBUFFER, blitFramebufferName);
	// Bind input FBO + texture to a color attachment

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, blitTexture, 0);
	glReadBuffer(GL_COLOR_ATTACHMENT0);

	// Bind destination FBO + texture to another color attachment
	glBindFramebuffer(GL_FRAMEBUFFER, vramFramebufferName);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, vramTexture, 0);
	glDrawBuffer(GL_COLOR_ATTACHMENT1);

	//	glBlitFramebuffer(0, 0, rect->w, rect->h, 0, 0, rect->w, rect->h, GL_COLOR_BUFFER_BIT, GL_NEAREST);

	glBlitNamedFramebuffer(blitFramebufferName, vramFramebufferName, 0, 0, rect->w, rect->h, rect->x, rect->y, 512 + (rect->x * 2), 256 + rect->y, GL_COLOR_BUFFER_BIT, GL_NEAREST);

#else
	unsigned short* dst = (unsigned short*)p;

	for (int y = 0; y < 512; y++)
	{
		for (int x = 0; x < 1024; x++)
		{
			unsigned short* src = vram + (y * 1024 + x);

			if (x >= rect->x && x < rect->x + rect->w &&
				y >= rect->y && y < rect->y + rect->h)
			{
				src[0] = *dst++;
			}
		}
	}
#endif

#if 1
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
