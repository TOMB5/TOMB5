#include "LIBGPU.H"

#define GL_GLEXT_PROTOTYPES 1
#include "GL\glew.h"
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_opengl_glext.h>
#include <stdio.h>
#include <cstring>
#include <cassert>
#include <LIBETC.H>

#include "EMULATOR.H"
#include "EMULATOR_GLOBALS.H"

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
	memset(ot, 0, n * sizeof(int));
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

int test = 0;

void DrawOTagEnv(u_long* p, DRAWENV* env)
{
	P_TAG* pTag = (P_TAG*)*p;
	if (pTag != NULL)
	{
		GLuint fbo = 0;
		glGenFramebuffers(1, &fbo);
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);

		glEnable(GL_TEXTURE_2D);
		glGenTextures(1, &vramTexture);
		glBindTexture(GL_TEXTURE_2D, vramTexture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1024, 512, 0, GL_RGBA, GL_UNSIGNED_SHORT_1_5_5_5_REV, &vram[0]);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, vramTexture, 0);
		GLenum DrawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
		glDrawBuffers(1, DrawBuffers);

		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		glOrtho(0, 1024, 0, 512, -1, 1);
		glViewport(0, 0, 1024, 512);

		while (1)
		{
			switch (pTag->code)
			{
			case 0x2C:
			{
				POLY_FT4* poly = (POLY_FT4*)pTag;

				///@FIXME im unsure if this is stable.
				int tpage = (poly->tpage & 0x1F) / 4 + 1;
				int x = (tpage * 256) % 1024 - 256;
				int y = (tpage / 4) * 256;


				glBegin(GL_QUADS);
				glTranslatef(1.0f, 0.0f, 0.0f);
				//glColor3ub(poly->r0, poly->g0, poly->b0);
				glTexCoord2f(1.0f / (1024.0f / (float)(poly->u0 + x)), 1.0f / (512.0f / (float)(poly->v0 + y)));
				glVertex2f(poly->x0, poly->y0);
				
				//glColor3ub(poly->r0, poly->g0, poly->b0);
				glTexCoord2f(1.0f / (1024.0f / (float)(poly->u1 + x)), 1.0f / (512.0f / (float)(poly->v1 + y)));
				glVertex2f(poly->x1, poly->y1);
				
				//glColor3ub(poly->r0, poly->g0, poly->b0);
				glTexCoord2f(1.0f / (1024.0f / (float)(poly->u3 + x)), 1.0f / (512.0f / (float)(poly->v3 + y)));
				glVertex2f(poly->x3, poly->y3);
				
				//glColor3ub(poly->r0, poly->g0, poly->b0);
				glTexCoord2f(1.0f / (1024.0f / (float)(poly->u2 + x)), 1.0f / (512.0f / (float)(poly->v2 + y)));
				glVertex2f(poly->x2, poly->y2);
				
				glEnd();
				break;
			}
			default:
				//Unhandled poly
				assert(0);
				break;
			}

			if (pTag->addr == 0)
			{
				break;
			}

			pTag = (P_TAG*)((int)pTag - ((pTag->len * 4) + 4));
		}

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			printf("Frame buffer error!\n");
		}

		unsigned short* pixels = new unsigned short[1024 * 512];
		memset(&pixels[0], 0, 1024 * 512 * 2);
		glReadPixels(0, 0, 1024, 512, GL_RGBA, GL_UNSIGNED_SHORT_1_5_5_5_REV, &pixels[0]);
		memcpy(&vram[0], pixels, 1024 * 512 * 2);

#if _DEBUG
		FILE* f = fopen("VRAM2.TGA", "wb");
		unsigned char TGAheader[12] = { 0,0,2,0,0,0,0,0,0,0,0,0 };
		unsigned char header[6] = { 1024 % 256, 1024 / 256, 512 % 256, 512 / 256,16,0 };
		fwrite(TGAheader, sizeof(unsigned char), 12, f);
		fwrite(header, sizeof(unsigned char), 6, f);
		fwrite(pixels, sizeof(char), 1024 * 512 * 2, f);
		fclose(f);
#endif
		delete[] pixels;
		glDeleteFramebuffers(1, &fbo);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, screenWidth, screenHeight);
		glPopMatrix();
		glDeleteTextures(1, &vramTexture);
	}
}
