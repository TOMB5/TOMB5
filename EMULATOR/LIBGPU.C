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
	glScissor(rect->x, rect->y, rect->w, rect->h);
	Emulator_CheckTextureIntersection(rect);

	GLuint srcTexture;
	GLuint srcFrameBuffer;

	glGenTextures(1, &srcTexture);
	glBindTexture(GL_TEXTURE_2D, srcTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	printf("srcTexture: %x\n", srcTexture);
#if defined(OGL)
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, rect->w, rect->h, 0, GL_RGBA, GL_UNSIGNED_SHORT_1_5_5_5_REV, &p[0]);
#elif defined(OGLES)
	unsigned short* picture = (unsigned short*)&p[0];
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, rect->w, rect->h, 0, GL_RGBA, GL_UNSIGNED_SHORT_5_5_5_1, &picture[0]);
#endif
	printf("LoadImagePSX GLError: %x\n", glGetError());

	/* Generate src Frame Buffer */
	glGenFramebuffers(1, &srcFrameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, srcFrameBuffer);
	printf("LoadImagePSX GLError: %x\n", glGetError());
	/* Bind src texture to src framebuffer */
#if defined(CORE_PROF_3_1)
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, srcTexture, 0);
#elif defined(CORE_PROF_3_2)
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, srcTexture, 0);
#endif
	
	printf("LoadImagePSX GLError: %x\n", glGetError());
	 
#if defined(OGL) || defined(OGLES)
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		eprinterr("Frame buffer error");
	}
#endif

	glBindFramebuffer(GL_READ_FRAMEBUFFER, srcFrameBuffer);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, vramFrameBuffer);

	glBlitFramebuffer(0, 0, rect->w, rect->h, rect->x, rect->y, (rect->x + rect->w), (rect->y + rect->h), GL_COLOR_BUFFER_BIT, GL_LINEAR);

#if _DEBUG
	Emulator_SaveVRAM("VRAM3.TGA", 0, 0, rect->w, rect->h, TRUE);
#endif

	glDeleteTextures(1, &srcTexture);
	Emulator_DestroyFrameBuffer(srcFrameBuffer);

	return 0;
}

int MoveImage(RECT16* rect, int x, int y)
{
	glScissor(x, y, x + rect->w, y + rect->h);
	GLuint srcTexture;
	GLuint srcFrameBuffer;

	unsigned short* pixels = new unsigned short[rect->w * rect->h];

	/* Read in src pixels for rect */
	glBindFramebuffer(GL_FRAMEBUFFER, vramFrameBuffer);
#if defined(OGLES)
	glReadPixels(rect->x, rect->y, rect->w, rect->h, GL_RGBA, GL_UNSIGNED_SHORT_5_5_5_1, &pixels[0]);
#elif defined(OGL)
	glReadPixels(rect->x, rect->y, rect->w, rect->h, GL_RGBA, GL_UNSIGNED_SHORT_1_5_5_5_REV, &pixels[0]);
#endif

	glGenTextures(1, &srcTexture);
	glBindTexture(GL_TEXTURE_2D, srcTexture);
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
#if defined(CORE_PROF_3_1)
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, srcTexture, 0);
#elif defined(CORE_PROF_3_2)
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, srcTexture, 0);
#endif

#if defined(OGL) || defined(OGLES)
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		eprinterr("Frame buffer error");
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

#if defined(_WINDOWS) || defined(__EMSCRIPTEN__)
	//First is special terminator
	ot[0] = (unsigned long)&terminator;
#else
	//First is special terminator
	ot[0] = (unsigned long)terminator;
#endif

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

#if defined(OGLES)
GLubyte indexBuffer[] = { 0,1,2,0,2,3 };
GLuint ibo;
GLuint vbo;
GLuint vao;
#endif

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
#if !defined(OGLES)
		glLoadIdentity();
		glOrtho(0, VRAM_WIDTH, 0, VRAM_HEIGHT, 0, 1);
#elif defined(OGLES)
		Emulator_Ortho2D(0, VRAM_WIDTH, 0, VRAM_HEIGHT, 0, 1);
#endif
		glBindFramebuffer(GL_FRAMEBUFFER, vramFrameBuffer);
		glViewport(activeDrawEnv.clip.x * RESOLUTION_SCALE, activeDrawEnv.clip.y * RESOLUTION_SCALE, VRAM_WIDTH, VRAM_HEIGHT);
		
#if !defined(OGLES)
		//glScaled(RESOLUTION_SCALE, RESOLUTION_SCALE, RESOLUTION_SCALE);
		glEnableClientState(GL_VERTEX_ARRAY);
#endif
		glScissor(activeDrawEnv.clip.x * RESOLUTION_SCALE, activeDrawEnv.clip.y * RESOLUTION_SCALE, activeDrawEnv.clip.w * RESOLUTION_SCALE, activeDrawEnv.clip.h * RESOLUTION_SCALE);
		P_TAG* pTag = (P_TAG*)p;

#if defined(OGLES)
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glGenBuffers(1, &ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte) * 6, indexBuffer, GL_STATIC_DRAW);

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 4, NULL, GL_DYNAMIC_DRAW);
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
#if defined(OGLES)
		glDeleteBuffers(1, &ibo);
		glDeleteBuffers(1, &vbo);
		glDeleteVertexArrays(1, &vao);
#endif
#if !defined(OGLES)
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
			glBindTexture(GL_TEXTURE_2D, nullWhiteTexture);
			POLY_F3* poly = (POLY_F3*)pTag;

			char* vertexPointer = Emulator_GenerateVertexArrayQuad(&poly->x0, &poly->x1, &poly->x2, NULL, -1, -1);
			char* texCoordPointer = Emulator_GenerateTexcoordArrayQuad(NULL, NULL, NULL, NULL, -1, -1);
			char* colourPointer = Emulator_GenerateColourArrayQuad(&poly->r0, NULL, NULL, NULL, false);

			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glEnableClientState(GL_COLOR_ARRAY);
			glVertexPointer(2, GL_FLOAT, sizeof(Vertex), vertexPointer);
			glColorPointer(3, GL_FLOAT, sizeof(Vertex), colourPointer);
			glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), texCoordPointer);
			glDrawArrays(GL_TRIANGLES, 0, 3);
			glDisableClientState(GL_COLOR_ARRAY);
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);
#endif

			currentAddress += sizeof(POLY_F3);
			break;
		}
		case 0x24: // POLY_FT3
		{

			POLY_FT3* poly = (POLY_FT3*)pTag;

			Emulator_GenerateAndBindTpage(poly->tpage, poly->clut, semi_transparent);

			char* vertexPointer = Emulator_GenerateVertexArrayQuad(&poly->x0, &poly->x1, &poly->x2, NULL, -1, -1);
			char* texCoordPointer = Emulator_GenerateTexcoordArrayQuad(NULL, NULL, NULL, NULL, -1, -1);
			char* colourPointer = Emulator_GenerateColourArrayQuad(&poly->r0, NULL, NULL, NULL, true);
#if !defined(OGLES)
			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glEnableClientState(GL_COLOR_ARRAY);
			glVertexPointer(2, GL_FLOAT, sizeof(Vertex), vertexPointer);
			glColorPointer(3, GL_FLOAT, sizeof(Vertex), colourPointer);
			glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), texCoordPointer);
			glDrawArrays(GL_TRIANGLES, 0, 3);
			glDisableClientState(GL_COLOR_ARRAY);
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);
			glDisableClientState(GL_VERTEX_ARRAY);
#endif
			currentAddress += sizeof(POLY_FT3);
			break;
		}
		case 0x28: // POLY_F4
		{
			glBindTexture(GL_TEXTURE_2D, nullWhiteTexture);
			POLY_F4* poly = (POLY_F4*)pTag;

			char* vertexPointer = Emulator_GenerateVertexArrayQuad(&poly->x0, &poly->x1, &poly->x3, &poly->x2, -1, -1);
			char* texCoordPointer = Emulator_GenerateTexcoordArrayQuad(NULL, NULL, NULL, NULL, -1, -1);
			char* colourPointer = Emulator_GenerateColourArrayQuad(&poly->r0, NULL, NULL, NULL, false);
#if !defined(OGLES)
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glEnableClientState(GL_COLOR_ARRAY);
			glVertexPointer(2, GL_FLOAT, sizeof(Vertex), vertexPointer);
			glColorPointer(3, GL_FLOAT, sizeof(Vertex), colourPointer);
			glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), texCoordPointer);
			glDrawArrays(GL_QUADS, 0, 4);
			glDisableClientState(GL_COLOR_ARRAY);
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);
#endif
			currentAddress += sizeof(POLY_F4);
			break;
		}
		case 0x2C: // POLY_FT4
		{

			POLY_FT4* poly = (POLY_FT4*)pTag;

			Emulator_GenerateAndBindTpage(poly->tpage, poly->clut, semi_transparent);

			char* vertexPointer = Emulator_GenerateVertexArrayQuad(&poly->x0, &poly->x1, &poly->x3, &poly->x2, -1, -1);
			char* texcoordPointer = Emulator_GenerateTexcoordArrayQuad(&poly->u0, &poly->u1, &poly->u3, &poly->u2, -1, -1);
#if defined(OGL)
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glVertexPointer(2, GL_FLOAT, sizeof(Vertex), vertexPointer);
			glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), texcoordPointer);
			glDrawArrays(GL_QUADS, 0, 4);
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);
#elif defined(OGLES)
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertex) * 4, vertexPointer);

			GLint posAttrib = glGetAttribLocation(g_defaultShaderProgram, "a_position");
			GLint colAttrib = glGetAttribLocation(g_defaultShaderProgram, "a_colour");
			GLint texAttrib = glGetAttribLocation(g_defaultShaderProgram, "a_texcoord");
			glEnableVertexAttribArray(posAttrib);
			glEnableVertexAttribArray(texAttrib);
			glEnableVertexAttribArray(colAttrib);
			glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
			glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)8);
			glVertexAttribPointer(colAttrib, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)16);

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, NULL);

			glDisableVertexAttribArray(posAttrib);
			glDisableVertexAttribArray(colAttrib);
			glDisableVertexAttribArray(texAttrib);
#endif
			currentAddress += sizeof(POLY_FT4);
			break;
		}
		case 0x30: // POLY_G3
		{
			POLY_G3* poly = (POLY_G3*)pTag;

			glBindTexture(GL_TEXTURE_2D, nullWhiteTexture);

			char* vertexPointer = Emulator_GenerateVertexArrayQuad(&poly->x0, &poly->x1, &poly->x2, NULL, -1, -1);
			char* texcoordPointer = Emulator_GenerateTexcoordArrayQuad(NULL, NULL, NULL, NULL, -1, -1);
			char* colourPointer = Emulator_GenerateColourArrayQuad(&poly->r0, &poly->r1, &poly->r2, NULL, false);
#if !defined(OGLES)
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glEnableClientState(GL_COLOR_ARRAY);
			glVertexPointer(2, GL_FLOAT, sizeof(Vertex), vertexPointer);
			glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), texcoordPointer);
			glColorPointer(4, GL_FLOAT, sizeof(Vertex), colourPointer);
			glDrawArrays(GL_TRIANGLES, 0, 3);
			glDisableClientState(GL_COLOR_ARRAY);
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);
#endif
			currentAddress += sizeof(POLY_G3);
			break;
		}
		case 0x34: // POLY_GT3
		{
			POLY_GT3* poly = (POLY_GT3*)pTag;

			Emulator_GenerateAndBindTpage(poly->tpage, poly->clut, semi_transparent);

			char* vertexPointer = Emulator_GenerateVertexArrayQuad(&poly->x0, &poly->x1, &poly->x2, NULL, -1, -1);
			char* texcoordPointer = Emulator_GenerateTexcoordArrayQuad(&poly->u0, &poly->u1, &poly->u2, NULL, -1, -1);
			char* colourPointer = Emulator_GenerateColourArrayQuad(&poly->r0, &poly->r1, &poly->r2, NULL, true);
#if !defined(OGLES)
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glEnableClientState(GL_COLOR_ARRAY);
			glVertexPointer(2, GL_FLOAT, sizeof(Vertex), vertexPointer);
			glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), texcoordPointer);
			glColorPointer(4, GL_FLOAT, sizeof(Vertex), colourPointer);
			glDrawArrays(GL_TRIANGLES, 0, 3);
			glDisableClientState(GL_COLOR_ARRAY);
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);
#elif defined(OGLES)
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertex) * 4, vertexPointer);

			GLint posAttrib = glGetAttribLocation(g_defaultShaderProgram, "a_position");
			GLint colAttrib = glGetAttribLocation(g_defaultShaderProgram, "a_colour");
			GLint texAttrib = glGetAttribLocation(g_defaultShaderProgram, "a_texcoord");
			glEnableVertexAttribArray(posAttrib);
			glEnableVertexAttribArray(colAttrib);
			glEnableVertexAttribArray(texAttrib);
			glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
			glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)8);
			glVertexAttribPointer(colAttrib, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)16);
			
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, NULL);

			glDisableVertexAttribArray(posAttrib);
			glDisableVertexAttribArray(colAttrib);
			glDisableVertexAttribArray(texAttrib);
#endif
			currentAddress += sizeof(POLY_GT3);
			break;
		}
		case 0x38: // POLY_G4
		{
			POLY_G4* poly = (POLY_G4*)pTag;

			char* vertexPointer = Emulator_GenerateVertexArrayQuad(&poly->x0, &poly->x1, &poly->x3, &poly->x2, -1, -1);
			char* colourPointer = Emulator_GenerateColourArrayQuad(&poly->r0, &poly->r1, &poly->r3, &poly->r2, true);
#if !defined(OGLES)
			glEnableClientState(GL_COLOR_ARRAY);
			glVertexPointer(2, GL_FLOAT, sizeof(Vertex), vertexPointer);
			glColorPointer(4, GL_FLOAT, sizeof(Vertex), colourPointer);
			glDrawArrays(GL_QUADS, 0, 4);
			glDisableClientState(GL_COLOR_ARRAY);

#endif
			currentAddress += sizeof(POLY_G4);
			break;
		}
		case 0x3C: // POLY_GT4
		{
			POLY_GT4* poly = (POLY_GT4*)pTag;

			Emulator_GenerateAndBindTpage(poly->tpage, poly->clut, semi_transparent);

			char* vertexPointer = Emulator_GenerateVertexArrayQuad(&poly->x0, &poly->x1, &poly->x3, &poly->x2, -1, -1);
			char* texcoordPointer = Emulator_GenerateTexcoordArrayQuad(&poly->u0, &poly->u1, &poly->u3, &poly->u2, -1, -1);
			char* colourPointer = Emulator_GenerateColourArrayQuad(&poly->r0, &poly->r1, &poly->r3, &poly->r2, true);
#if !defined(OGLES)
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glEnableClientState(GL_COLOR_ARRAY);

			glVertexPointer(2, GL_FLOAT, sizeof(Vertex), vertexPointer);
			glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), texcoordPointer);
			glColorPointer(4, GL_FLOAT, sizeof(Vertex), colourPointer);
			glDrawArrays(GL_QUADS, 0, 4);
			glDisableClientState(GL_COLOR_ARRAY);
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);
#elif defined(OGLES)
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertex) * 4, vertexPointer);

			GLint posAttrib = glGetAttribLocation(g_defaultShaderProgram, "a_position");
			GLint colAttrib = glGetAttribLocation(g_defaultShaderProgram, "a_colour");
			GLint texAttrib = glGetAttribLocation(g_defaultShaderProgram, "a_texcoord");
			glEnableVertexAttribArray(posAttrib);
			glEnableVertexAttribArray(colAttrib);
			glEnableVertexAttribArray(texAttrib);
			glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
			glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)8);
			glVertexAttribPointer(colAttrib, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)16);

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, NULL);

			glDisableVertexAttribArray(posAttrib);
			glDisableVertexAttribArray(colAttrib);
			glDisableVertexAttribArray(texAttrib);
#endif
			currentAddress += sizeof(POLY_GT4);
			break;
		}
		case 0x40: // LINE_F2
		{
			glBindTexture(GL_TEXTURE_2D, nullWhiteTexture);

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
			glBindTexture(GL_TEXTURE_2D, nullWhiteTexture);

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
			glBindTexture(GL_TEXTURE_2D, nullWhiteTexture);

			TILE* poly = (TILE*)pTag;
#if !defined(OGLES)
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
			Emulator_GenerateAndBindTpage(-1, poly->clut, semi_transparent);

			char* vertexPointer = Emulator_GenerateVertexArrayQuad(&poly->x0, NULL, NULL, NULL, poly->w, poly->h);
			char* texcoordPointer = Emulator_GenerateTexcoordArrayQuad(&poly->u0, NULL, NULL, NULL, poly->w, poly->h);
			char* colourPointer = Emulator_GenerateColourArrayQuad(&poly->r0, &poly->r0, &poly->r0, &poly->r0, true);
#if defined(OGL)
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glEnableClientState(GL_COLOR_ARRAY);

			glVertexPointer(2, GL_FLOAT, sizeof(Vertex), vertexPointer);
			glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), texcoordPointer);
			glColorPointer(4, GL_FLOAT, sizeof(Vertex), colourPointer);
			glDrawArrays(GL_QUADS, 0, 4);
			glDisableClientState(GL_COLOR_ARRAY);
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);
#elif defined(OGLES)
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertex) * 4, vertexPointer);

			GLint posAttrib = glGetAttribLocation(g_defaultShaderProgram, "a_position");
			GLint colAttrib = glGetAttribLocation(g_defaultShaderProgram, "a_colour");
			GLint texAttrib = glGetAttribLocation(g_defaultShaderProgram, "a_texcoord");
			glEnableVertexAttribArray(posAttrib);
			glEnableVertexAttribArray(texAttrib);
			glEnableVertexAttribArray(colAttrib);
			glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
			glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)8);
			glVertexAttribPointer(colAttrib, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)16);

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, NULL);

			glDisableVertexAttribArray(posAttrib);
			glDisableVertexAttribArray(colAttrib);
			glDisableVertexAttribArray(texAttrib);
#endif
			currentAddress += sizeof(SPRT);
			break;
		}
		case 0x68: // TILE_1
		{
			const int width = 1;

			glBindTexture(GL_TEXTURE_2D, nullWhiteTexture);

			TILE_1* poly = (TILE_1*)pTag;
#if !defined(OGLES)
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

			glBindTexture(GL_TEXTURE_2D, nullWhiteTexture);
#if !defined(OGLES)
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
#if !defined(OGLES)
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

			glBindTexture(GL_TEXTURE_2D, nullWhiteTexture);

			TILE_1* poly = (TILE_1*)pTag;
#if !defined(OGLES)
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
#if !defined(OGLES)
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
#if !defined(OGLES)
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
#endif
		Emulator_SetBlendMode(1);
	}
}