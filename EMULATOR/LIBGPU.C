#include "LIBGPU.H"

#include "EMULATOR.H"
#include "EMULATOR_GLOBALS.H"

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <LIBETC.H>

DISPENV word_33BC;
DRAWENV activeDrawEnv;
DRAWENV byte_9CCA4;
int dword_3410 = 0;
char byte_3352 = 0;

struct VertexBufferSplitIndex
{
	unsigned short splitIndex;
	unsigned short numVertices;
	GLuint textureId;
};

#define MAX_NUM_POLY_BUFFER_VERTICES (12040)//?FIXME
#define MAX_NUM_INDEX_BUFFERS (4096)
Vertex g_vertexBuffer[MAX_NUM_POLY_BUFFER_VERTICES];
unsigned char* g_IndexBuffer[MAX_NUM_INDEX_BUFFERS];
VertexBufferSplitIndex g_splitIndices[MAX_NUM_INDEX_BUFFERS];
int g_vertexIndex = 0;
int currentIndexBuffer = 0;
int g_numSplitIndices = 0;

//#define WIREFRAME_MODE

//Nasty hack, win32 is like original but due to memory differences
//Between Linux and Windows we must do this unfortunately.
#if defined(_WINDOWS) || defined(__EMSCRIPTEN__)
unsigned long terminator = -1;
#else
unsigned long* terminator;
#endif
void(*drawsync_callback)(void) = NULL;

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
	glBindFramebuffer(GL_FRAMEBUFFER, vramFrameBuffer);
	Emulator_CheckTextureIntersection(rect);
	glClearColor(r/255.0f, g/255.0f, b/255.0f, 1.0f);
	glScissor(rect->x * RESOLUTION_SCALE, rect->y * RESOLUTION_SCALE, rect->w * RESOLUTION_SCALE, rect->h * RESOLUTION_SCALE);
	glClear(GL_COLOR_BUFFER_BIT);
	return 0;
}

int DrawSync(int mode)
{
	if (drawsync_callback != NULL)
	{
		drawsync_callback();
	}

	return 0;
}

int LoadImagePSX(RECT16* rect, u_long* p)
{
	Emulator_CheckTextureIntersection(rect);
	glScissor(rect->x * RESOLUTION_SCALE, rect->y * RESOLUTION_SCALE, rect->w * RESOLUTION_SCALE, rect->h * RESOLUTION_SCALE);

	GLuint srcTexture;
	GLuint srcFrameBuffer;

	glGenTextures(1, &srcTexture);
	Emulator_BindTexture(srcTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

#if defined(OGL)
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, rect->w, rect->h, 0, GL_RGBA, GL_UNSIGNED_SHORT_1_5_5_5_REV, &p[0]);
#elif defined(OGLES)
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, rect->w, rect->h, 0, GL_RGBA, GL_UNSIGNED_SHORT_5_5_5_1, &p[0]);
#endif

	/* Generate src Frame Buffer */
	glGenFramebuffers(1, &srcFrameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, srcFrameBuffer);

	/* Bind src texture to src framebuffer */
#if defined(CORE_PROF_3_1) || defined(OGLES)
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, srcTexture, 0);
#elif defined(CORE_PROF_3_2) || defined(CORE_PROF_3_3)
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, srcTexture, 0);
#endif

#if defined(OGL) || defined(OGLES)
	while (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		eprinterr("Frame buffer error: %x\n", glCheckFramebufferStatus(GL_FRAMEBUFFER));
	}

#endif

	glBindFramebuffer(GL_READ_FRAMEBUFFER, srcFrameBuffer);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, vramFrameBuffer);
	glBlitFramebuffer(0, 0, rect->w * RESOLUTION_SCALE, rect->h * RESOLUTION_SCALE, rect->x * RESOLUTION_SCALE, rect->y * RESOLUTION_SCALE, (rect->x + rect->w) * RESOLUTION_SCALE, (rect->y + rect->h) * RESOLUTION_SCALE, GL_COLOR_BUFFER_BIT, GL_LINEAR);

#if _DEBUG
	Emulator_SaveVRAM("VRAM3.TGA", 0, 0, rect->w, rect->h, TRUE);
#endif

	glDeleteTextures(1, &srcTexture);
	Emulator_DestroyFrameBuffer(srcFrameBuffer);

	return 0;
}

int MoveImage(RECT16* rect, int x, int y)
{
	//Emulator_CheckTextureIntersection(rect); Not yet need to construct actual rect
	glScissor(x * RESOLUTION_SCALE, y * RESOLUTION_SCALE, x + rect->w * RESOLUTION_SCALE, y + rect->h * RESOLUTION_SCALE);
	GLuint srcTexture;
	GLuint srcFrameBuffer;

	unsigned short* pixels = new unsigned short[rect->w * rect->h];///@FIXME res scale

	/* Read in src pixels for rect */
	glBindFramebuffer(GL_FRAMEBUFFER, vramFrameBuffer);
#if defined(OGLES)
	glReadPixels(rect->x, rect->y, rect->w, rect->h, GL_RGBA, GL_UNSIGNED_SHORT_5_5_5_1, &pixels[0]);
#elif defined(OGL)
	glReadPixels(rect->x, rect->y, rect->w, rect->h, GL_RGBA, GL_UNSIGNED_SHORT_1_5_5_5_REV, &pixels[0]);
#endif

	glGenTextures(1, &srcTexture);
	Emulator_BindTexture(srcTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

#if defined(OGL)
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, rect->w, rect->h, 0, GL_RGBA, GL_UNSIGNED_SHORT_1_5_5_5_REV, &pixels[0]);
#elif defined(OGLES)
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, rect->w, rect->h, 0, GL_RGBA, GL_UNSIGNED_SHORT_5_5_5_1, &pixels[0]);
#endif

	/* Generate src Frame Buffer */
	glGenFramebuffers(1, &srcFrameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, srcFrameBuffer);

	/* Bind src texture to src framebuffer */
#if defined(CORE_PROF_3_1) || defined(OGLES)
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, srcTexture, 0);
#elif defined(CORE_PROF_3_2) || defined(CORE_PROF_3_3)
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, srcTexture, 0);
#endif

#if defined(OGL) || defined(OGLES)
	while (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		eprinterr("Frame buffer error: %x\n", glCheckFramebufferStatus(GL_FRAMEBUFFER));
	}
#endif
	glBindFramebuffer(GL_READ_FRAMEBUFFER, srcFrameBuffer);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, vramFrameBuffer);
	glBlitFramebuffer(0, 0, rect->w, rect->h, x, y, x+rect->w, y + rect->h, GL_COLOR_BUFFER_BIT, GL_LINEAR);
#if _DEBUG
	glBindFramebuffer(GL_FRAMEBUFFER, vramFrameBuffer);
	Emulator_SaveVRAM("VRAM3.TGA", 0, 0, VRAM_WIDTH, VRAM_HEIGHT, TRUE);
#endif

	glDeleteTextures(1, &srcTexture);
	Emulator_DestroyFrameBuffer(srcFrameBuffer);

	delete[] pixels;

	return 0;
}

int ResetGraph(int mode)
{
	UNIMPLEMENTED();
	return 0;
}

int SetGraphDebug(int level)
{
	UNIMPLEMENTED();
	return 0;
}

int StoreImage(RECT16* rect, u_long * p)
{
	glBindFramebuffer(GL_FRAMEBUFFER, vramFrameBuffer);
#if defined(OGL)
	glReadPixels(rect->x, rect->y, rect->w, rect->h, GL_RGBA, GL_UNSIGNED_SHORT_1_5_5_5_REV, &p[0]);
#elif defined(OGLES)
	glReadPixels(rect->x, rect->y, rect->w, rect->h, GL_RGBA, GL_UNSIGNED_SHORT_5_5_5_1, (unsigned short*)&p[0]);
#endif
	return 0;
}

u_long* ClearOTag(u_long* ot, int n)
{
	//Nothing to do here.
	if (n == 0)
		return NULL;

#if defined(_WINDOWS) || defined(__EMSCRIPTEN__)
	//last is special terminator
	ot[n-1] = (unsigned long)&terminator;
#else
	//last is special terminator
	ot[n-1] = (unsigned long)terminator;
#endif

	for (int i = n - 2; i > -1; i--)
	{
		ot[i] = (unsigned long)& ot[i + 1];
	}

	return NULL;
}

u_long* ClearOTagR(u_long* ot, int n)
{
	//Nothing to do here.
	if (n == 0)
		return NULL;

#if defined(_WINDOWS) || defined(__EMSCRIPTEN__)
	//First is special terminator
	ot[0] = (unsigned long)&terminator;
#else
	//First is special terminator
	ot[0] = (unsigned long)terminator;
#endif

	for (int i = 1; i < n; i++)
	{
		ot[i] = (unsigned long)& ot[i - 1];
	}

	return NULL;
}

void SetDispMask(int mask)
{
	UNIMPLEMENTED();
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
	memcpy((char*)&activeDrawEnv, env, sizeof(DRAWENV));
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

void SetDrawEnv(DR_ENV* dr_env, DRAWENV* env)
{

}

u_long DrawSyncCallback(void(*func)(void))
{
	drawsync_callback = func;
	return 0;
}

#if defined(OGLES) || defined(CORE_PROF_3_3) || defined(CORE_PROF_3_1)
GLuint vbo;
GLuint vao;
#endif

static unsigned short lastTpage = -1;
static unsigned short lastClut = -1;
static unsigned short numVertices = 0;

void DrawOTagEnv(u_long* p, DRAWENV* env)//
{
#if defined(WIREFRAME_MODE)
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
#endif

#if 0
	//if (byte_3352[0] > 1)
	{
		GPU_printf("DrawOTagEnv(%08x,&08x)...\n", p, env);
	}//loc_EF8

	//s0 = &env->dr_env

	//sub_17C0(&env->dr_env, env);

	env->dr_env.tag = env->dr_env.tag & 0xFF000000 | (ptrdiff_t)p & 0xFFFFFF;
	//a0 = off_3348[6];
	//v0 = off_3348[2];
	///jalr off_3348[2](off_3348[6]);
	memcpy(&byte_9CCA4, &env, sizeof(DRAWENV));

#else
	PutDrawEnv(env);

	if (env->dtd)
	{
		glEnable(GL_DITHER);
	}
	else
	{
		glDisable(GL_DITHER);
	}

	if (env->isbg)
	{
		ClearImage(&env->clip, env->r0, env->g0, env->b0);
	}

	if (p != NULL)
	{
		lastClut = 0xFFFF;
		lastTpage = 0xFFFF;
		numVertices = 0;
		g_vertexIndex = 0;
		g_numSplitIndices = 0;
		SDL_memset(&g_vertexBuffer[0], 0, MAX_NUM_POLY_BUFFER_VERTICES * sizeof(Vertex));
		SDL_memset(&g_splitIndices[0], 0, MAX_NUM_INDEX_BUFFERS * sizeof(VertexBufferSplitIndex));

#if defined(OGL) && !defined(CORE_PROF_3_3)
		glLoadIdentity();
		glOrtho(0, VRAM_WIDTH, 0, VRAM_HEIGHT, 0, 1);
#elif defined(OGLES) || defined(CORE_PROF_3_3)
		Emulator_Ortho2D(0, VRAM_WIDTH, 0, VRAM_HEIGHT, 0, 1);
#endif
		glBindFramebuffer(GL_FRAMEBUFFER, vramFrameBuffer);
		glViewport(activeDrawEnv.clip.x * RESOLUTION_SCALE, activeDrawEnv.clip.y * RESOLUTION_SCALE, VRAM_WIDTH, VRAM_HEIGHT);
		
#if !defined(OGLES)
		
#if RESOLUTION_SCALE > 1 && defined(CORE_PROF_3_1)
		glScaled(RESOLUTION_SCALE, RESOLUTION_SCALE, RESOLUTION_SCALE);
#endif
#if defined(CORE_PROF_3_1)
		glEnableClientState(GL_VERTEX_ARRAY);
#endif
#endif
		glScissor(activeDrawEnv.clip.x * RESOLUTION_SCALE, activeDrawEnv.clip.y * RESOLUTION_SCALE, activeDrawEnv.clip.w * RESOLUTION_SCALE, activeDrawEnv.clip.h * RESOLUTION_SCALE);
		P_TAG* pTag = (P_TAG*)p;

#if defined(OGLES) || defined(CORE_PROF_3_3) || defined(CORE_PROF_3_1)
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
#endif

#if defined(OGLES) || defined(CORE_PROF_3_3)
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		GLint posAttrib = glGetAttribLocation(g_defaultShaderProgram, "a_position");
		GLint colAttrib = glGetAttribLocation(g_defaultShaderProgram, "a_colour");
		GLint texAttrib = glGetAttribLocation(g_defaultShaderProgram, "a_texcoord");
		glEnableVertexAttribArray(posAttrib);
		glEnableVertexAttribArray(colAttrib);
		glEnableVertexAttribArray(texAttrib);
		glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
		glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)8);
		glVertexAttribPointer(colAttrib, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)16);
#endif
		do
		{
			if (pTag->len > 0)
			{
				ParsePrimitive((int)pTag, (int)pTag + (int)(pTag->len * 4) + 4);
			}
			pTag = (P_TAG*)pTag->addr;
#if __linux__ || __APPLE_
		}while ((unsigned long)pTag != 0xFFFFFF);
#else
		}while ((unsigned long)pTag != (unsigned long)&terminator);
#endif

#if defined(OGLES) || defined(CORE_PROF_3_3) || defined(CORE_PROF_3_1)
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * MAX_NUM_POLY_BUFFER_VERTICES, &g_vertexBuffer[0], GL_STATIC_DRAW);

		for (int i = 0; i < g_numSplitIndices; i++)
		{
			Emulator_BindTexture(g_splitIndices[i].textureId);
			glDrawArrays(GL_TRIANGLES, g_splitIndices[i].splitIndex, g_splitIndices[i].numVertices);
		}

		glDeleteBuffers(1, &vbo);
#endif
#if defined(OGLES) || defined(CORE_PROF_3_3)
		glDisableVertexAttribArray(posAttrib);
		glDisableVertexAttribArray(colAttrib);
		glDisableVertexAttribArray(texAttrib);

		glDeleteVertexArrays(1, &vao);
#endif
#if defined(OGL) && defined(CORE_PROF_3_1)
		glDisableClientState(GL_VERTEX_ARRAY);
#endif
#if 1//OLD_RENDERER
		glViewport(0, 0, windowWidth, windowHeight);
#endif
	}

	Emulator_CheckTextureIntersection(&env->clip);
#if defined(WIREFRAME_MODE)
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
#endif
#endif
}


void ParsePrimitive(unsigned int packetStart, unsigned int packetEnd)
{
	unsigned int currentAddress = packetStart;

	while (currentAddress != packetEnd)
	{
		P_TAG* pTag = (P_TAG*)currentAddress;
		
		int textured = (pTag->code & 4) != 0;
		int blend_mode = 0;
		int semi_transparent = (pTag->code & 2) != 0;

		if (textured)
		{
			if ((pTag->code & 1) != 0)
			{
				blend_mode = 2;
			}
			else
			{
				blend_mode = 1;
			}
		}
		else
		{
			blend_mode = 0;
		}

		if (semi_transparent)
		{
			Emulator_SetBlendMode(blend_mode);
		}

		switch (pTag->code & ~3)
		{
		case 0x0:
		{
			currentAddress += 4;
			break;
		}
		case 0x20: // POLY_F3
		{
#if !defined(OGLES)
			//glBindTexture(GL_TEXTURE_2D, nullWhiteTexture);
			POLY_F3* poly = (POLY_F3*)pTag;

			//char* vertexPointer = Emulator_GenerateVertexArrayQuad(&poly->x0, &poly->x1, &poly->x2, NULL, -1, -1);
			//char* texCoordPointer = Emulator_GenerateTexcoordArrayQuad(NULL, NULL, NULL, NULL, -1, -1);
			//char* colourPointer = Emulator_GenerateColourArrayQuad(&poly->r0, NULL, NULL, NULL, false);

			//glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			//glEnableClientState(GL_COLOR_ARRAY);
			//glVertexPointer(2, GL_FLOAT, sizeof(Vertex), vertexPointer);
			//glColorPointer(3, GL_FLOAT, sizeof(Vertex), colourPointer);
			//glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), texCoordPointer);
			//glDrawArrays(GL_TRIANGLES, 0, 3);
			//glDisableClientState(GL_COLOR_ARRAY);
			//glDisableClientState(GL_TEXTURE_COORD_ARRAY);
#endif

			currentAddress += sizeof(POLY_F3);
			break;
		}
		case 0x24: // POLY_FT3
		{

			POLY_FT3* poly = (POLY_FT3*)pTag;

			Emulator_GenerateTpage(poly->tpage, poly->clut);

			//char* vertexPointer = Emulator_GenerateVertexArrayQuad(&poly->x0, &poly->x1, &poly->x2, NULL, -1, -1);
			//char* texCoordPointer = Emulator_GenerateTexcoordArrayQuad(NULL, NULL, NULL, NULL, -1, -1);
			//char* colourPointer = Emulator_GenerateColourArrayQuad(&poly->r0, NULL, NULL, NULL, true);
#if defined(OGL)
			//glEnableClientState(GL_VERTEX_ARRAY);
			//glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			//glEnableClientState(GL_COLOR_ARRAY);
			//glVertexPointer(2, GL_FLOAT, sizeof(Vertex), vertexPointer);
			//glColorPointer(3, GL_FLOAT, sizeof(Vertex), colourPointer);
			//glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), texCoordPointer);
			//glDrawArrays(GL_TRIANGLES, 0, 3);
			//glDisableClientState(GL_COLOR_ARRAY);
			//glDisableClientState(GL_TEXTURE_COORD_ARRAY);
			//glDisableClientState(GL_VERTEX_ARRAY);
#endif
			currentAddress += sizeof(POLY_FT3);
			break;
		}
		case 0x28: // POLY_F4
		{
			//glBindTexture(GL_TEXTURE_2D, nullWhiteTexture);
			POLY_F4* poly = (POLY_F4*)pTag;

			//char* vertexPointer = Emulator_GenerateVertexArrayQuad(&poly->x0, &poly->x1, &poly->x3, &poly->x2, -1, -1);
			//char* texCoordPointer = Emulator_GenerateTexcoordArrayQuad(NULL, NULL, NULL, NULL, -1, -1);
			//char* colourPointer = Emulator_GenerateColourArrayQuad(&poly->r0, NULL, NULL, NULL, false);
#if defined(OGL)
			//glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			//glEnableClientState(GL_COLOR_ARRAY);
			//glVertexPointer(2, GL_FLOAT, sizeof(Vertex), vertexPointer);
			//glColorPointer(3, GL_FLOAT, sizeof(Vertex), colourPointer);
			///glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), texCoordPointer);
			//glDrawArrays(GL_QUADS, 0, 4);
			//glDisableClientState(GL_COLOR_ARRAY);
			//glDisableClientState(GL_TEXTURE_COORD_ARRAY);
#endif
			currentAddress += sizeof(POLY_F4);
			break;
		}
		case 0x2C: // POLY_FT4
		{

			POLY_FT4* poly = (POLY_FT4*)pTag;

			if (lastTpage == 0xFFFF || lastClut == 0xFFFF)
			{
				lastTpage = poly->tpage;
				lastClut = poly->clut;
				g_splitIndices[g_numSplitIndices].textureId = Emulator_GenerateTpage(lastTpage, lastClut);
				g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
			}
			else if (poly->tpage != lastTpage || poly->clut != lastClut)
			{
				lastClut = poly->clut;
				lastTpage = poly->tpage;
				g_splitIndices[g_numSplitIndices].textureId = Emulator_GenerateTpage(lastTpage, lastClut);
				g_splitIndices[g_numSplitIndices - 1].numVertices = numVertices;
				g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
				numVertices = 0;
			}

			Emulator_GenerateVertexArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->x0, &poly->x1, &poly->x3, &poly->x2, -1, -1);
			Emulator_GenerateTexcoordArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->u0, &poly->u1, &poly->u3, &poly->u2, -1, -1);
			Emulator_GenerateColourArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->r0, NULL, NULL, NULL, false);

			//Make tri
			g_vertexBuffer[g_vertexIndex + 5] = g_vertexBuffer[g_vertexIndex + 3];
			g_vertexBuffer[g_vertexIndex + 3] = g_vertexBuffer[g_vertexIndex];
			g_vertexBuffer[g_vertexIndex + 4] = g_vertexBuffer[g_vertexIndex + 2];

			currentAddress += sizeof(POLY_FT4);
			g_vertexIndex += 6;
			numVertices += 6;
			break;
		}
		case 0x30: // POLY_G3
		{
			POLY_G3* poly = (POLY_G3*)pTag;

			//glBindTexture(GL_TEXTURE_2D, nullWhiteTexture);

			//char* vertexPointer = Emulator_GenerateVertexArrayQuad(&polyGT4Buffer[polyGT4Index], &poly->x0, &poly->x1, &poly->x2, NULL, -1, -1);
			//char* texcoordPointer = Emulator_GenerateTexcoordArrayQuad(&polyGT4Buffer[polyGT4Index], NULL, NULL, NULL, NULL, -1, -1);
			//char* colourPointer = Emulator_GenerateColourArrayQuad(&polyGT4Buffer[polyGT4Index], &poly->r0, &poly->r1, &poly->r2, NULL, false);
#if defined(OGL)
			//glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			//glEnableClientState(GL_COLOR_ARRAY);
			//glVertexPointer(2, GL_FLOAT, sizeof(Vertex), vertexPointer);
			//glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), texcoordPointer);
			//glColorPointer(4, GL_FLOAT, sizeof(Vertex), colourPointer);
			//glDrawArrays(GL_TRIANGLES, 0, 3);
			//glDisableClientState(GL_COLOR_ARRAY);
			//glDisableClientState(GL_TEXTURE_COORD_ARRAY);
#endif
			currentAddress += sizeof(POLY_G3);
			break;
		}
		case 0x34: // POLY_GT3
		{
			POLY_GT3* poly = (POLY_GT3*)pTag;

			if (lastTpage == 0xFFFF || lastClut == 0xFFFF)
			{
				lastTpage = poly->tpage;
				lastClut = poly->clut;
				g_splitIndices[g_numSplitIndices].textureId = Emulator_GenerateTpage(lastTpage, lastClut);
				g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
			}
			else if (poly->tpage != lastTpage || poly->clut != lastClut)
			{
				lastTpage = poly->tpage;
				lastClut = poly->clut;
				g_splitIndices[g_numSplitIndices].textureId = Emulator_GenerateTpage(lastTpage, lastClut);
				g_splitIndices[g_numSplitIndices - 1].numVertices = numVertices;
				g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
				numVertices = 0;
			}

			Emulator_GenerateVertexArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->x0, &poly->x1, &poly->x2, NULL, -1, -1);
			Emulator_GenerateTexcoordArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->u0, &poly->u1, &poly->u2, NULL, -1, -1);
			Emulator_GenerateColourArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->r0, &poly->r1, &poly->r2, NULL, true);

			
			g_vertexIndex += 3;
			numVertices += 3;
			currentAddress += sizeof(POLY_GT3);
			break;
		}
		case 0x38: // POLY_G4
		{
			POLY_G4* poly = (POLY_G4*)pTag;

			//char* vertexPointer = Emulator_GenerateVertexArrayQuad(&poly->x0, &poly->x1, &poly->x3, &poly->x2, -1, -1);
			//char* colourPointer = Emulator_GenerateColourArrayQuad(&poly->r0, &poly->r1, &poly->r3, &poly->r2, true);
#if defined(OGL)
			//glEnableClientState(GL_COLOR_ARRAY);
			//glVertexPointer(2, GL_FLOAT, sizeof(Vertex), vertexPointer);
			//glColorPointer(4, GL_FLOAT, sizeof(Vertex), colourPointer);
			//glDrawArrays(GL_QUADS, 0, 4);
			//glDisableClientState(GL_COLOR_ARRAY);

#endif
			currentAddress += sizeof(POLY_G4);
			break;
		}
		case 0x3C: // POLY_GT4
		{
			POLY_GT4* poly = (POLY_GT4*)pTag;

			if (lastTpage == 0xFFFF || lastClut == 0xFFFF)
			{
				lastTpage = poly->tpage;
				lastClut = poly->clut;
				g_splitIndices[g_numSplitIndices].textureId = Emulator_GenerateTpage(lastTpage, lastClut);
				g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
			}
			else if (poly->tpage != lastTpage || poly->clut != lastClut)
			{
				lastClut = poly->clut;
				lastTpage = poly->tpage;
				g_splitIndices[g_numSplitIndices].textureId = Emulator_GenerateTpage(lastTpage, lastClut);
				g_splitIndices[g_numSplitIndices - 1].numVertices = numVertices;
				g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
				numVertices = 0;
			}

			Emulator_GenerateVertexArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->x0, &poly->x1, &poly->x3, &poly->x2, -1, -1);
			Emulator_GenerateTexcoordArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->u0, &poly->u1, &poly->u3, &poly->u2, -1, -1);
			Emulator_GenerateColourArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->r0, &poly->r1, &poly->r3, &poly->r2, true);

			//Make tri
			g_vertexBuffer[g_vertexIndex + 5] = g_vertexBuffer[g_vertexIndex+3];
			g_vertexBuffer[g_vertexIndex + 3] = g_vertexBuffer[g_vertexIndex];
			g_vertexBuffer[g_vertexIndex + 4] = g_vertexBuffer[g_vertexIndex+2];

			
			g_vertexIndex += 6;
			numVertices += 6;
			currentAddress += sizeof(POLY_GT4);
			break;
		}
		case 0x40: // LINE_F2
		{
			//glBindTexture(GL_TEXTURE_2D, nullWhiteTexture);

			LINE_F2* poly = (LINE_F2*)pTag;
#if !defined(OGLES)
			glBegin(GL_LINES);

			glColor3ubv(&poly->r0);
			glVertex2f(poly->x0, poly->y0);

			glVertex2f(poly->x1, poly->y1);

			glEnd();
#endif
			currentAddress += sizeof(LINE_F2);
			break;
		}
		case 0x50: // LINE_G2
		{
			//glBindTexture(GL_TEXTURE_2D, nullWhiteTexture);

			LINE_G2* poly = (LINE_G2*)pTag;
#if !defined(OGLES)
			glBegin(GL_LINES);
			glColor3ubv(&poly->r0);
			glVertex2f(poly->x0, poly->y0);
			glColor3ubv(&poly->r1);
			glVertex2f(poly->x1, poly->y1);
			glEnd();
#endif
			currentAddress += sizeof(LINE_G2);
			break;
		}
		case 0x60: // TILE
		{
			//glBindTexture(GL_TEXTURE_2D, nullWhiteTexture);

			TILE* poly = (TILE*)pTag;
#if !defined(OGLES) && 0
			glBegin(GL_QUADS);

			glColor3ubv(&poly->r0);

			glTexCoord2f(0.0f, 0.0f);
			glVertex2f(poly->x0, poly->y0);

			glTexCoord2f(1.0f, 0.0f);
			glVertex2f(poly->x0 + poly->w, poly->y0);

			glTexCoord2f(0.0f, 1.0f);
			glVertex2f(poly->x0 + poly->w, poly->y0 + poly->h);

			glTexCoord2f(1.0f, 1.0f);
			glVertex2f(poly->x0, poly->y0 + poly->h);

			glEnd();
#endif
			currentAddress += sizeof(TILE);
			break;
		}
		case 0x64: // SPRT
		{
			SPRT* poly = (SPRT*)pTag;

			if (lastClut == 0xFFFF)
			{
				lastClut = poly->clut;
				g_splitIndices[g_numSplitIndices].textureId = Emulator_GenerateTpage(-1, lastClut);
				g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
			}
			else if (poly->clut != lastClut)
			{
				lastClut = poly->clut;
				g_splitIndices[g_numSplitIndices].textureId = Emulator_GenerateTpage(-1, lastClut);
				g_splitIndices[g_numSplitIndices - 1].numVertices = numVertices;
				g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
				numVertices = 0;
			}

			Emulator_GenerateVertexArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->x0, NULL, NULL, NULL, poly->w, poly->h);
			Emulator_GenerateTexcoordArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->u0, NULL, NULL, NULL, poly->w, poly->h);
			Emulator_GenerateColourArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->r0, &poly->r0, &poly->r0, &poly->r0, false);

			//Make tri
			g_vertexBuffer[g_vertexIndex + 5] = g_vertexBuffer[g_vertexIndex + 3];
			g_vertexBuffer[g_vertexIndex + 3] = g_vertexBuffer[g_vertexIndex];
			g_vertexBuffer[g_vertexIndex + 4] = g_vertexBuffer[g_vertexIndex + 2];

			g_vertexIndex += 6;
			numVertices += 6;

			currentAddress += sizeof(SPRT);
			break;
		}
		case 0x68: // TILE_1
		{
			const int width = 1;

			//glBindTexture(GL_TEXTURE_2D, nullWhiteTexture);

			TILE_1* poly = (TILE_1*)pTag;
#if !defined(OGLES) && 0
			glBegin(GL_QUADS);

			glColor3ubv(&poly->r0);

			glTexCoord2f(0.0f, 0.0f);
			glVertex2f(poly->x0, poly->y0);

			glTexCoord2f(1.0f, 0.0f);
			glVertex2f(poly->x0 + width, poly->y0);

			glTexCoord2f(0.0f, 1.0f);
			glVertex2f(poly->x0 + width, poly->y0 + width);

			glTexCoord2f(1.0f, 1.0f);
			glVertex2f(poly->x0, poly->y0 + width);

			glEnd();
#endif
			currentAddress += sizeof(TILE_1);
			break;
		}
		case 0x70: // TILE_8
		{
			const int width = 8;

			//glBindTexture(GL_TEXTURE_2D, nullWhiteTexture);
#if !defined(OGLES) && 0
			TILE_1* poly = (TILE_1*)pTag;

			glBegin(GL_QUADS);

			glColor3ubv(&poly->r0);

			glTexCoord2f(0.0f, 0.0f);
			glVertex2f(poly->x0, poly->y0);

			glTexCoord2f(1.0f, 0.0f);
			glVertex2f(poly->x0 + width, poly->y0);

			glTexCoord2f(0.0f, 1.0f);
			glVertex2f(poly->x0 + width, poly->y0 + width);

			glTexCoord2f(1.0f, 1.0f);
			glVertex2f(poly->x0, poly->y0 + width);

			glEnd();
#endif
			currentAddress += sizeof(TILE_8);
			break;
		}
		case 0x74: // SPRT_8
		{
			SPRT_8* poly = (SPRT_8*)pTag;
#if !defined(OGLES) && 0
			glBegin(GL_QUADS);

			glColor3ubv(&poly->r0);

			glTexCoord2f(poly->u0 / 256.0f, poly->v0 / 256.0f);
			glVertex2f(poly->x0, poly->y0);

			glTexCoord2f((poly->u0 + 8) / 256.0f, poly->v0 / 256.0f);
			glVertex2f(poly->x0 + 8, poly->y0);

			glTexCoord2f(poly->u0 / 256.0f, (poly->v0 + 8) / 256.0f);
			glVertex2f(poly->x0 + 8, poly->y0 + 8);

			glTexCoord2f((poly->u0 + 8) / 256.0f, (poly->v0 + 8) / 256.0f);
			glVertex2f(poly->x0, poly->y0 + 8);

			glEnd();
#endif
			currentAddress += sizeof(SPRT_8);
			break;
		}
		case 0x78: // TILE_16
		{
			const int width = 16;

			//glBindTexture(GL_TEXTURE_2D, nullWhiteTexture);

			TILE_1* poly = (TILE_1*)pTag;
#if !defined(OGLES) && 0
			glBegin(GL_QUADS);

			glColor3ubv(&poly->r0);

			glTexCoord2f(0.0f, 0.0f);
			glVertex2f(poly->x0, poly->y0);

			glTexCoord2f(1.0f, 0.0f);
			glVertex2f(poly->x0 + width, poly->y0);

			glTexCoord2f(0.0f, 1.0f);
			glVertex2f(poly->x0 + width, poly->y0 + width);

			glTexCoord2f(1.0f, 1.0f);
			glVertex2f(poly->x0, poly->y0 + width);

			glEnd();
#endif
			currentAddress += sizeof(TILE_16);
			break;
		}
		case 0x7C: // SPRT_16
		{
			SPRT_16* poly = (SPRT_16*)pTag;
#if !defined(OGLES) && 0
			glBegin(GL_QUADS);

			glColor3ubv(&poly->r0);

			glTexCoord2f(poly->u0 / 256.0f, poly->v0 / 256.0f);
			glVertex2f(poly->x0, poly->y0);

			glTexCoord2f((poly->u0 + 16) / 256.0f, poly->v0 / 256.0f);
			glVertex2f(poly->x0 + 16, poly->y0);

			glTexCoord2f(poly->u0 / 256.0f, (poly->v0 + 16) / 256.0f);
			glVertex2f(poly->x0 + 16, poly->y0 + 16);

			glTexCoord2f((poly->u0 + 16) / 256.0f, (poly->v0 + 16) / 256.0f);
			glVertex2f(poly->x0, poly->y0 + 16);

			glEnd();
#endif
			currentAddress += sizeof(SPRT_16);
			break;
		}
		case 0xE0: // TPAGE
		{
			unsigned short tpage = ((unsigned short*)pTag)[2];
			GlobalTpageTexture = tpage;
			currentAddress += 8;
			break;
		}
		default:
			eprinterr("Unhandled primitive type: %02X type2:%02X\n", pTag->code, pTag->code & ~3);
			//Unhandled poly
			break;
		}

		//Reset for vertex colours
#if !defined(OGLES) && !defined(CORE_PROF_3_3)
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
#endif
	}

	g_splitIndices[g_numSplitIndices - 1].numVertices = numVertices;
	//g_splitIndices[g_numSplitIndices].splitIndex = g_vertexIndex;
}