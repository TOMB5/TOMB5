#include "LIBGPU.H"

#define GL_GLEXT_PROTOTYPES 1
#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <LIBETC.H>

#include "EMULATOR.H"
#include "EMULATOR_GLOBALS.H"

unsigned short vram[1024 * 512];
DISPENV word_33BC;
DRAWENV word_unknown00;//Guessed
int dword_3410 = 0;
char byte_3352 = 0;
unsigned long terminator = -1;

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

int MoveImage(RECT16* rect, int x, int y)
{
#if 0//TODO
	for (int sy = rect->y; sy < 512; sy++)
	{
		for (int sx = rect->x; sx < 1024; sx++)
		{
			unsigned short* src = vram + (sy * 1024 + sx);
			unsigned short* dst = vram + (y * 1024 + x);

			if (sx >= rect->x && sx < rect->x + rect->w &&
				sy >= rect->y && sy < rect->y + rect->h)
			{
				*dst++ = *src++;
			}
		}
	}
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

u_long* ClearOTag(u_long* ot, int n)
{
	//Nothing to do here.
	if (n == 0)
		return NULL;

	//Last is special terminator
	ot[n-1] = (unsigned long)&terminator;

	if (n > 1)
	{
		for (int i = n-2; i > -1; i--)
		{
			ot[i] = (unsigned long)&ot[i+1];
		}
	}
	return NULL;
}

u_long* ClearOTagR(u_long* ot, int n)
{
	//Nothing to do here.
	if (n == 0)
		return NULL;

	//First is special terminator
	ot[0] = (unsigned long)&terminator;

	if (n > 1)
	{
		for (int i = 1; i < n; i++)
		{
			ot[i] = (unsigned long)&ot[i - 1];
		}
	}
	return NULL;
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

DRAWENV* PutDrawEnv(DRAWENV* env)//Guessed
{
	memcpy((char*)&word_unknown00, env, sizeof(DRAWENV));
	return 0;
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
	PutDrawEnv(env);

	GLuint fbo = 0;

	if (p != NULL && *p != NULL)
	{


		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		glOrtho(0, 1024, 0, 512, -1, 1);
		glViewport(0, 0, 1024, 512);

		glEnable(GL_TEXTURE_2D);

#if 0
		glBlendColor(0.25, 0.25, 0.25, 0.5);
#endif

		Emulator_GenerateFrameBuffer(fbo);
		Emulator_GenerateFrameBufferTexture();
		while (1)
		{
			P_TAG* pTag = (P_TAG*)p;

			if (pTag->len != 0)
			{
				switch (pTag->code)
				{
				case 0x2A:
				{
					POLY_F4* poly = (POLY_F4*)pTag;
					glBegin(GL_QUADS);

					glColor3f(0.0f, 0.0f, 0.0f);
					//glTexCoord2f(0.0, 0.0f);//Dummy
					glVertex2f(poly->x0, poly->y0);

					//glColor3f((float)poly->r0 / 255.0f, (float)poly->g0 / 255.0f, (float)poly->b0 / 255.0f);
					//glTexCoord2f(0.01, 0.0f);//Dummy
					glVertex2f(poly->x1, poly->y1);

					//glColor3f((float)poly->r0 / 255.0f, (float)poly->g0 / 255.0f, (float)poly->b0 / 255.0f);
					//glTexCoord2f(0.0, 0.01f);//Dummy
					glVertex2f(poly->x3, poly->y3);

					//glColor3f((float)poly->r0 / 255.0f, (float)poly->g0 / 255.0f, (float)poly->b0 / 255.0f);
					//glTexCoord2f(0.01, 0.01f);//Dummy
					glVertex2f(poly->x2, poly->y2);

					glEnd();

					//Reset for vertex colours
					glColor3f(1.0f, 1.0f, 1.0f);

					break;
				}
				case 0x3C:
				{
					POLY_GT4* poly = (POLY_GT4*)pTag;

					int x = ((poly->tpage) << 6) & 0x7C0 % 1024;
					int y = (((poly->tpage) << 4) & 0x100) + (((poly->tpage) >> 2) & 0x200);

#if 0
					glBlendFuncSeparate(GL_ONE, GL_ONE, GL_ONE, GL_ZERO);
					glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
#endif

#if DEBUG_MSG
					printf("tpage: (%d,%d,%d,%d)\n", ((poly->tpage) >> 7) & 0x3, ((poly->tpage) >> 5) & 0x3, ((poly->tpage) << 6) & 0x7C0, (((poly->tpage) << 4) & 0x100) + (((poly->tpage) >> 2) & 0x200));
					printf("clut: (%d,%d)\n", (poly->clut & 0x3F) << 4, (poly->clut >> 6));
#endif

					Emulator_GenerateAndBindTpage(((poly->tpage) >> 7) & 0x3, x, y, (poly->clut & 0x3F) << 4, (poly->clut >> 6));

#if 0
					switch (((poly->tpage) >> 5) & 0x3)
					{
					case 0:
						glBlendFuncSeparate(GL_CONSTANT_ALPHA, GL_CONSTANT_ALPHA, GL_ONE, GL_ZERO);
						glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
						break;
					case 1:
						glBlendFuncSeparate(GL_ONE, GL_ONE, GL_ONE, GL_ZERO);
						glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
						break;
					case 2:
						glBlendFuncSeparate(GL_ONE, GL_ONE, GL_ONE, GL_ZERO);
						glBlendEquationSeparate(GL_FUNC_REVERSE_SUBTRACT, GL_FUNC_ADD);
						break;
					case 3:
						glBlendFuncSeparate(GL_CONSTANT_COLOR, GL_ONE, GL_ONE, GL_ZERO);
						glBlendEquationSeparate(GL_FUNC_REVERSE_SUBTRACT, GL_FUNC_ADD);
						break;
					}
#endif
					glBegin(GL_QUADS);

					glColor3f((float)poly->r0 / 255.0f, (float)poly->g0 / 255.0f, (float)poly->b0 / 255.0f);
					glTexCoord2f(1.0f / (256.0f / (float)(poly->u0)), 1.0f / (256.0f / (float)(poly->v0)));
					glVertex2f(poly->x0, poly->y0);

					glColor3f((float)poly->r1 / 255.0f, (float)poly->g1 / 255.0f, (float)poly->b1 / 255.0f);
					glTexCoord2f(1.0f / (256.0f / (float)(poly->u1)), 1.0f / (256.0f / (float)(poly->v1)));
					glVertex2f(poly->x1, poly->y1);

					glColor3f((float)poly->r3 / 255.0f, (float)poly->g3 / 255.0f, (float)poly->b3 / 255.0f);
					glTexCoord2f(1.0f / (256.0f / (float)(poly->u3)), 1.0f / (256.0f / (float)(poly->v3)));
					glVertex2f(poly->x3, poly->y3);

					glColor3f((float)poly->r2 / 255.0f, (float)poly->g2 / 255.0f, (float)poly->b2 / 255.0f);
					glTexCoord2f(1.0f / (256.0f / (float)(poly->u2)), 1.0f / (256.0f / (float)(poly->v2)));
					glVertex2f(poly->x2, poly->y2);

					glEnd();

					//Reset for vertex colours
					glColor3f(1.0f, 1.0f, 1.0f);
					break;
				}
				case 0x2C:
				{
					POLY_FT4* poly = (POLY_FT4*)pTag;

					int x = ((poly->tpage) << 6) & 0x7C0 % 1024;
					int y = (((poly->tpage) << 4) & 0x100) + (((poly->tpage) >> 2) & 0x200);

#if DEBUG_MSG
					printf("tpage: (%d,%d,%d,%d)\n", ((poly->tpage) >> 7) & 0x003, ((poly->tpage) >> 5) & 0x003, ((poly->tpage) << 6) & 0x7c0, (((poly->tpage) << 4) & 0x100) + (((poly->tpage) >> 2) & 0x200));
					printf("clut: (%d,%d)\n", (poly->clut & 0x3F) << 4, (poly->clut >> 6));
#endif

					Emulator_GenerateAndBindTpage(((poly->tpage) >> 7) & 0x3, x, y, (poly->clut & 0x3F) << 4, (poly->clut >> 6));
					
					glBegin(GL_QUADS);
					//glColor3ub(poly->r0, poly->g0, poly->b0);
					glTexCoord2f(1.0f / (256.0f / (float)(poly->u0)), 1.0f / (256.0f / (float)(poly->v0)));
					glVertex2f(poly->x0, poly->y0);

					//glColor3ub(poly->r0, poly->g0, poly->b0);
					glTexCoord2f(1.0f / (256.0f / (float)(poly->u1)), 1.0f / (256.0f / (float)(poly->v1)));
					glVertex2f(poly->x1, poly->y1);

					//glColor3ub(poly->r0, poly->g0, poly->b0);
					glTexCoord2f(1.0f / (256.0f / (float)(poly->u3)), 1.0f / (256.0f / (float)(poly->v3)));
					glVertex2f(poly->x3, poly->y3);

					//glColor3ub(poly->r0, poly->g0, poly->b0);
					glTexCoord2f(1.0f / (256.0f / (float)(poly->u2)), 1.0f / (256.0f / (float)(poly->v2)));
					glVertex2f(poly->x2, poly->y2);

					glEnd();

					//Reset for vertex colours
					glColor3f(1.0f, 1.0f, 1.0f);
					break;
				}
				default:
					//Unhandled poly
					//assert(0);
					break;
				}
			}
			
			p = (unsigned long*)((P_TAG*)p)->addr;
			//p = (unsigned long*)*p;

			if (p == &terminator)
			{
				break;
			}
		}

		Emulator_DestroyLastVRAMTexture();
		Emulator_DeleteFrameBufferTexture();

		glViewport(0, 0, windowWidth, windowHeight);
		glPopMatrix();


		Emulator_DestroyFrameBuffer(fbo);
	}
}

