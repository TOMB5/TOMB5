#include "EMULATOR.H"

#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <LIBPAD.H>
#include <stdio.h>
#include <LIBGPU.H>
#include <LIBETC.H>
#include <string.h>
#include "EMULATOR_GLOBALS.H"

#define MAX_NUM_CACHED_TEXTURES (256)
#define BLEND_MODE (0)

#define V_SCALE 2

SDL_Window* g_window = NULL;
SDL_Renderer* g_renderer;

GLuint vramTexture = 0;
GLuint nullWhiteTexture = 0;
int screenWidth = 0;
int screenHeight = 0;
int windowWidth = 0;
int windowHeight = 0;
int lastTextureCacheIndex = 0;

struct CachedTexture
{
	GLuint textureID;
	unsigned int tpageX;
	unsigned int tpageY;
	unsigned int clutX;
	unsigned int clutY;
	unsigned int lastAccess;
};

struct CachedTexture cachedTextures[MAX_NUM_CACHED_TEXTURES];

void Emulator_Init(char* windowName, int screen_width, int screen_height)
{
	screenWidth = screen_width;
	screenHeight = screen_height;
	windowWidth = screen_width * V_SCALE;
	windowHeight = screen_height * V_SCALE;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == 0)
	{
		g_window = SDL_CreateWindow(windowName, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_OPENGL);
		g_renderer = SDL_CreateRenderer(g_window, 0, SDL_RENDERER_ACCELERATED);
		SDL_RenderSetLogicalSize(g_renderer, screenWidth, screenHeight);
		if (g_renderer == NULL)
		{
			eprinterr("Error initialising renderer\n");
		}
	}
	else
	{
		eprinterr("Error: Failed to initialise SDL\n");
	}

	SDL_GL_CreateContext(g_window);

	if (glewInit() != GLEW_OK)
	{
		eprinterr("Error initialising GLEW!\n");
	}

	SDL_memset(&vram, 0, sizeof(1024 * 512 * 2));
	SDL_GL_SetSwapInterval(1);

	Emulator_InitialiseGL();
}

void Emulator_InitialiseGL()
{
	Emulator_GenerateAndBindNullWhite();

//	glPolygonMode(GL_FRONT_AND_BACK, self.command_polygon_mode);
//	glEnable(GL_SCISSOR_TEST);
//	glEnable(GL_DEPTH_TEST);
//	glDepthFunc(GL_LEQUAL);

	glBlendColor(0.25, 0.25, 0.25, 0.5);
}

void Emulator_GenerateAndBindNullWhite()
{
	unsigned int pixelData;
	pixelData = -1;

	glGenTextures(1, &nullWhiteTexture);
	glBindTexture(GL_TEXTURE_2D, nullWhiteTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, &pixelData);
}

void Emulator_CheckTextureIntersection(RECT16* rect)
{
	for (int i = 0; i < MAX_NUM_CACHED_TEXTURES; i++)
	{
		if (!(cachedTextures[i].tpageX > rect->x + rect->w || cachedTextures[i].tpageX + 256 < rect->x || cachedTextures[i].tpageY > rect->y + rect->h || cachedTextures[i].tpageY + 256 < rect->y))
		{
			cachedTextures[i].lastAccess = -1;
			cachedTextures[i].tpageX = -1;
			cachedTextures[i].tpageY = -1;
			glDeleteTextures(1, &cachedTextures[i].textureID);
		}
	}
}

void Emulator_SaveVRAM(int width, int height)
{
	FILE* f = fopen("VRAM.TGA", "wb");

	unsigned char TGAheader[12] = { 0,0,2,0,0,0,0,0,0,0,0,0 };
	unsigned char header[6] = { width % 256, width / 256, height % 256, height / 256,24,0 };
	char* pixels = new char[width * height * 3];
	glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, pixels);

	fwrite(TGAheader, sizeof(unsigned char), 12, f);
	fwrite(header, sizeof(unsigned char), 6, f);
	fwrite(pixels, sizeof(char), width*height*3, f);
	fclose(f);
	delete[] pixels;
}

void Emulator_SaveVRAM2(int width, int height)
{
	FILE* f = fopen("VRAM.TGA", "wb");
	if (f == NULL)
	{
		return;
	}
	unsigned char TGAheader[12] = { 0,0,2,0,0,0,0,0,0,0,0,0 };
	unsigned char header[6] = { width % 256, width / 256, height % 256, height / 256,16,0 };
	char* pixels = new char[width * height * 2];
	glGetTexImage(GL_TEXTURE_2D, 0, GL_BGRA, GL_UNSIGNED_SHORT_1_5_5_5_REV, pixels);

	fwrite(TGAheader, sizeof(unsigned char), 12, f);
	fwrite(header, sizeof(unsigned char), 6, f);
	fwrite(pixels, sizeof(char), width*height * 2, f);
	fclose(f);
	delete[] pixels;
}

int lastTime = 0;

void Emulator_BeginScene()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
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

	lastTime = SDL_GetTicks();

	//Update pad
	if (SDL_NumJoysticks() > 0)
	{
		for (int i = 0; i < MAX_CONTROLLERS; i++)
		{
			if (padHandle[i] != NULL)
			{
				padData[i][0] = 0;
				padData[i][1] = 0x41;//?
				((unsigned short*)padData[i])[1] = UpdateGameControllerInput(padHandle[i]);
			}
		}
	}

	//Update keyboard
	if (padData[0] != NULL)
	{
		((unsigned short*)padData[0])[1] = UpdateKeyboardInput();
	}
}

void Emulator_SwapWindow()
{
	SDL_GL_SwapWindow(g_window);
}

void Emulator_EndScene()
{
	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &vramTexture);
	glBindTexture(GL_TEXTURE_2D, vramTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1024, 512, 0, GL_RGBA, GL_UNSIGNED_SHORT_1_5_5_5_REV, &vram[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	float x = 1.0f / (1024.0f / (float)(word_33BC.disp.x));
	float y = 1.0f / (512.0f / (float)(word_33BC.disp.y));
	float h = 1.0f / (512.0f / (float)(word_33BC.disp.h));
	float w = 1.0f / (1024.0f / (float)(word_33BC.disp.w));

#define USE_VBO 1

#if USE_VBO

	float vertexBuffer[] =
	{
		0.0f, (float)word_33BC.disp.h, 0.0f, x, y,
		0.0f, 0.0f, 0.0f, x, y + h,
		(float)word_33BC.disp.w, 0.0f, 0.0f, x + w, y + h,
		(float)word_33BC.disp.w, (float)word_33BC.disp.h, 0.0f, x + w, y,
		(float)word_33BC.disp.w, 0.0f, 0.0f, x + w, y + h,
		0.0f, (float)word_33BC.disp.h, 0.0f, x, y,
	};

	GLushort indexBuffer[] =
	{
		3,2,0,
		0,1,2,
	};

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBuffer), vertexBuffer, GL_STATIC_DRAW);

	GLuint ibo;
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexBuffer), indexBuffer, GL_STATIC_DRAW);

	glVertexPointer(3, GL_FLOAT, 5 * sizeof(float), (void*)0);
	glTexCoordPointer(2, GL_FLOAT, 5 * sizeof(float), (void*)(sizeof(float) * 3));

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
#endif

	glDisable(GL_LIGHTING);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, word_33BC.disp.w, 0, word_33BC.disp.h, -1, 1);

#if USE_VBO
	glDrawElements(GL_TRIANGLES, sizeof(indexBuffer), GL_UNSIGNED_SHORT, 0);
#else
	glBegin(GL_TRIANGLES);
	glTexCoord2f(0, y + h); glVertex3f(0, 0, 0);
	glTexCoord2f(0.5, y + h); glVertex3f(512, 0, 0);
	glTexCoord2f(0, y); glVertex3f(0, 240, 0);

	glTexCoord2f(0.5, y); glVertex3f(512, 240, 0);
	glTexCoord2f(0.5, y + h); glVertex3f(512, 0, 0);
	glTexCoord2f(0.0, y); glVertex3f(0, 240, 0);
	glEnd();
#endif
	/*glBegin(GL_TRIANGLES);
	glVertex2f(0, 0);
	glVertex2f(512, 0);
	glVertex2f(0, 240);
	glEnd();*/
#if USE_VBO
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);
#endif

	glPopMatrix();

#if _DEBUG
	Emulator_SaveVRAM2(1024, 512);
#endif
	Emulator_SwapWindow();

	glDisable(GL_TEXTURE_2D);
	glDeleteTextures(1, &vramTexture);
}

void Emulator_ShutDown()
{
	glDeleteTextures(1, &vramTexture);
	glDeleteTextures(1, &nullWhiteTexture);
	SDL_QuitSubSystem(SDL_INIT_GAMECONTROLLER);

	for (int i = 0; i < lastTextureCacheIndex; i++)
	{
		glDeleteTextures(1, &cachedTextures[i].textureID);
	}
}

void Emulator_GenerateFrameBuffer(GLuint& fbo)
{
	fbo = 0;
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
}

void Emulator_GenerateFrameBufferTexture()
{
	unsigned short* pixelData = new unsigned short[word_unknown00.clip.w * word_unknown00.clip.h];
	unsigned short* dst = &pixelData[0];

	for (int y = word_unknown00.clip.y; y < 512; y++)
	{
		for (int x = word_unknown00.clip.x; x < 1024; x++)
		{
			unsigned short* src = vram + (y * 1024 + x);

			if (x >= word_unknown00.clip.x && x < word_unknown00.clip.x + word_unknown00.clip.w &&
				y >= word_unknown00.clip.y && y < word_unknown00.clip.y + word_unknown00.clip.h)
			{
				*dst++ = src[0];
			}
		}
	}

	glGenTextures(1, &vramTexture);
	glBindTexture(GL_TEXTURE_2D, vramTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, word_unknown00.clip.w, word_unknown00.clip.h, 0, GL_RGBA, GL_UNSIGNED_SHORT_1_5_5_5_REV, &pixelData[0]);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, vramTexture, 0);


	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		eprinterr("Frame buffer error");
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

#if _DEBUG
	unsigned short* pixelData2 = new unsigned short[word_unknown00.clip.w * word_unknown00.clip.h];
	glReadPixels(0, 0, word_unknown00.clip.w, word_unknown00.clip.h, GL_RGBA, GL_UNSIGNED_SHORT_1_5_5_5_REV, pixelData2);

	FILE* f = fopen("VRAM4.TGA", "wb");
	if (f == NULL)
	{
		return;
	}
	unsigned char TGAheader[12] = { 0,0,2,0,0,0,0,0,0,0,0,0 };
	unsigned char header[6] = { word_unknown00.clip.w % 256, word_unknown00.clip.w / 256, word_unknown00.clip.h % 256, word_unknown00.clip.h / 256,16,0 };
	fwrite(TGAheader, sizeof(unsigned char), 12, f);
	fwrite(header, sizeof(unsigned char), 6, f);
	fwrite(pixelData2, sizeof(char), word_unknown00.clip.w * word_unknown00.clip.h * 2, f);
	fclose(f);
	
#endif

	delete[] pixelData;
#if _DEBUG
	delete[] pixelData2;
#endif
}

void Emulator_DeleteFrameBufferTexture()
{
	glDeleteTextures(1, &vramTexture);
}

///@TODO check rectangular intersection plus clut x, y
///@TODO check if LoadImage and ClearImage, FrameBuffer rect intersection updates a texture, if so, we delete the original and generate a new one
GLuint Emulator_FindTextureInCache(unsigned int tpageX, unsigned int tpageY, unsigned int clutX, unsigned int clutY)
{
	for (int i = lastTextureCacheIndex-1; i > -1; i--)
	{
		if (cachedTextures[i].tpageX == tpageX && cachedTextures[i].tpageY == tpageY &&
		    cachedTextures[i].clutX == clutX && cachedTextures[i].clutY == clutY)
		{
			cachedTextures[i].lastAccess = SDL_GetTicks();
			return cachedTextures[i].textureID;
		}
	}

	return -1;
}

void Emulator_GenerateAndBindTpage(unsigned short tpage, unsigned short clut)
{
	unsigned int textureType = (tpage >> 7) & 0x3;
	unsigned int tpageX = (tpage << 6) & 0x7C0 % 1024;
	unsigned int tpageY = ((tpage << 4) & 0x100) + ((tpage >> 2) & 0x200);
	unsigned int clutX = (clut & 0x3F) << 4;
	unsigned int clutY = (clut >> 6);
	unsigned int tpageAbr = (tpage >> 5) & 3;

	//Emulator_SetBlendMode(tpageAbr);

#if DEBUG_MSG
	printf("tpage: (%d,%d,%d,%d)\n", ((tpage) >> 7) & 0x003, ((tpage) >> 5) & 0x003, ((tpage) << 6) & 0x7c0, (((tpage) << 4) & 0x100) + (((tpage) >> 2) & 0x200));
	printf("clut: (%d,%d)\n", (clut & 0x3F) << 4, (clut >> 6));
#endif

	GLuint tpageTexture = Emulator_FindTextureInCache(tpageX, tpageY, clutX, clutY);
	bool bMustAddTexture = tpageTexture == -1 ? 1 : 0;

	if (bMustAddTexture)
	{
		cachedTextures[lastTextureCacheIndex].tpageX = tpageX;
		cachedTextures[lastTextureCacheIndex].tpageY = tpageY;
		cachedTextures[lastTextureCacheIndex].clutX = clutX;
		cachedTextures[lastTextureCacheIndex].clutY = clutY;
		glGenTextures(1, &cachedTextures[lastTextureCacheIndex].textureID);
		tpageTexture = cachedTextures[lastTextureCacheIndex++].textureID;
	}

	glBindTexture(GL_TEXTURE_2D, tpageTexture);

	if (bMustAddTexture)
	{
		switch (textureType)
		{
		case 2:
		{
			//ARGB1555
			unsigned short texturePage[256 * 256];
			unsigned short* dst = &texturePage[0];

			for (int y = tpageY; y < tpageY + 256; y++)
			{
				for (int x = tpageX; x < tpageX + 256; x++)
				{
					unsigned short* src = vram + (y * 1024 + x);

					if (x >= tpageX && x < tpageX + 256 &&
						y >= tpageY && y < tpageY + 256)
					{
						*dst++ = *src;
					}
				}


#if 1
				FILE* f = fopen("TPAGE.TGA", "wb");
				unsigned char TGAheader[12] = { 0,0,2,0,0,0,0,0,0,0,0,0 };
				unsigned char header[6] = { 256 % 256, 256 / 256, 256 % 256, 256 / 256,16,0 };
				fwrite(TGAheader, sizeof(unsigned char), 12, f);
				fwrite(header, sizeof(unsigned char), 6, f);
				fwrite(&texturePage[0], sizeof(char), 256 * 256 * 2, f);
				fclose(f);
#endif
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 256, 256, 0, GL_RGBA, GL_UNSIGNED_SHORT_1_5_5_5_REV, &texturePage[0]);
			}

			break;
		}
		case 1:
		{
			//RGBA8888
			unsigned int texturePage[256 * 256];
			unsigned int* dst = &texturePage[0];

			for (int y = tpageY; y < tpageY + 256; y++)
			{
				for (int x = tpageX; x < tpageX + 256; x++)
				{
					unsigned short* src = vram + (y * 1024 + x);

					if (x >= tpageX && x < tpageX + 256 &&
						y >= tpageY && y < tpageY + 256)
					{
						*dst++ = 255 << 24 | ((((*src & 0x1F)) << 3) << 16) | ((((*src & 0x3E0) >> 5) << 3) << 8) | ((((*src & 0x7C00) >> 10) << 3));
					}
				}
			}

#if 0
			FILE* f = fopen("TPAGE.TGA", "wb");
			unsigned char TGAheader[12] = { 0,0,2,0,0,0,0,0,0,0,0,0 };
			unsigned char header[6] = { 256 % 256, 256 / 256, 256 % 256, 256 / 256,32,0 };
			fwrite(TGAheader, sizeof(unsigned char), 12, f);
			fwrite(header, sizeof(unsigned char), 6, f);
			fwrite(&texturePage[0], sizeof(char), 256 * 256 * 4, f);
			fclose(f);
#endif
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 256, 256, 0, GL_RGBA, GL_UNSIGNED_BYTE, &texturePage[0]);
			break;
		}
		case 0:
		{
			//RGBA4444
			unsigned int texturePage[256 * 256];
			unsigned int* dst = &texturePage[0];
			unsigned int clut[16];
			unsigned int* clutDst = &clut[0];

			//Get CLUT
			for (int y = clutY; y < clutY + 1; y++)
			{
				for (int x = clutX; x < clutX + 16; x++)
				{
					unsigned short* src = vram + (y * 1024 + x);
					*clutDst++ = 255 << 24 | ((((*src & 0x1F)) << 3) << 16) | ((((*src & 0x3E0) >> 5) << 3) << 8) | ((((*src & 0x7C00) >> 10) << 3));
				}
			}

			//Get Texture
			for (int y = tpageY; y < tpageY + 256; y++)
			{
				for (int x = tpageX; x < tpageX + 256; x++)
				{
					unsigned short* src = vram + (y * 1024 + x);

					if (x >= tpageX / 4 && x < (tpageX + 256 / 4) &&
						y >= tpageY && y < tpageY + 256)
					{
						*dst++ = (255 << 24) | (((clut[(*src & 0xF)] & 0xFF0000) >> 16) << 16) | (((clut[(*src & 0xF)] & 0xFF00) >> 8) << 8) | (clut[(*src & 0xF)] & 0xFF);
						if (((dst[-1] & 0xFF) | ((dst[-1] & 0xFF00) >> 8) | ((dst[-1] & 0xFF0000) >> 16)) == 0)
						{
							dst[-1] &= ~(255 << 24);
						}

						*dst++ = (255 << 24) | (((clut[(*src & 0xF0) >> 4] & 0xFF0000) >> 16) << 16) | (((clut[(*src & 0xF0) >> 4] & 0xFF00) >> 8) << 8) | (clut[(*src & 0xF0) >> 4] & 0xFF);
						if (((dst[-1] & 0xFF) | ((dst[-1] & 0xFF00) >> 8) | ((dst[-1] & 0xFF0000) >> 16)) == 0)
						{
							dst[-1] &= ~(255 << 24);
						}

						*dst++ = (255 << 24) | (((clut[(*src & 0xF00) >> 8] & 0xFF0000) >> 16) << 16) | (((clut[(*src & 0xF00) >> 8] & 0xFF00) >> 8) << 8) | (clut[(*src & 0xF00) >> 8] & 0xFF);
						if (((dst[-1] & 0xFF) | ((dst[-1] & 0xFF00) >> 8) | ((dst[-1] & 0xFF0000) >> 16)) == 0)
						{
							dst[-1] &= ~(255 << 24);
						}

						*dst++ = (255 << 24) | (((clut[(*src & 0xF000) >> 12] & 0xFF0000) >> 16) << 16) | (((clut[(*src & 0xF000) >> 12] & 0xFF00) >> 8) << 8) | (clut[(*src & 0xF000) >> 12] & 0xFF);
						if (((dst[-1] & 0xFF) | ((dst[-1] & 0xFF00) >> 8) | ((dst[-1] & 0xFF0000) >> 16)) == 0)
						{
							dst[-1] &= ~(255 << 24);
						}
					}
				}
			}


#if _DEBUG
			FILE* f = fopen("TPAGE.TGA", "wb");
			unsigned char TGAheader[12] = { 0,0,2,0,0,0,0,0,0,0,0,0 };
			unsigned char header[6] = { 256 % 256, 256 / 256, 256 % 256, 256 / 256,32,0 };
			fwrite(TGAheader, sizeof(unsigned char), 12, f);
			fwrite(header, sizeof(unsigned char), 6, f);
			fwrite(&texturePage[0], sizeof(char), 256 * 256 * 4, f);
			fclose(f);
#endif
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 256, 256, 0, GL_BGRA, GL_UNSIGNED_BYTE, &texturePage[0]);
			break;
		}
		}
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

void Emulator_DestroyFrameBuffer(GLuint& fbo)
{
	glDeleteFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Emulator_DestroyLastVRAMTexture()
{
	/*Read from frame buffer and send to VRAM*/
	unsigned short* pixelData = new unsigned short[word_unknown00.clip.w * word_unknown00.clip.h];
	unsigned short* dst = &pixelData[0];
	glReadPixels(0, 0, word_unknown00.clip.w, word_unknown00.clip.h, GL_RGBA, GL_UNSIGNED_SHORT_1_5_5_5_REV, pixelData);

	for (int y = word_unknown00.clip.y; y < 512; y++)
	{
		for (int x = word_unknown00.clip.x; x < 1024; x++)
		{
			unsigned short* src = vram + (y * 1024 + x);

			if (x >= word_unknown00.clip.x && x < word_unknown00.clip.x + word_unknown00.clip.w &&
				y >= word_unknown00.clip.y && y < word_unknown00.clip.y + word_unknown00.clip.h)
			{
				src[0] = *dst++;
			}
		}
	}

#if _DEBUG
	FILE* f = fopen("VRAM2.TGA", "wb");
	if (f == NULL)
	{
		return;
	}
	unsigned char TGAheader[12] = { 0,0,2,0,0,0,0,0,0,0,0,0 };
	unsigned char header[6] = { word_unknown00.clip.w % 256, word_unknown00.clip.w / 256, word_unknown00.clip.h % 256, word_unknown00.clip.h / 256,16,0 };
	fwrite(TGAheader, sizeof(unsigned char), 12, f);
	fwrite(header, sizeof(unsigned char), 6, f);
	fwrite(pixelData, sizeof(char), word_unknown00.clip.w * word_unknown00.clip.h * 2, f);
	fclose(f);
#endif

	delete[] pixelData;
}

void Emulator_SetBlendMode(int mode)
{
	glEnable(GL_BLEND);
#if 1
	switch (mode)
	{
	case 0://Average
		glBlendFunc(GL_SRC_ALPHA, GL_SRC_ALPHA);
		break;
	case 1://Add
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		break;
	case 2://Subtract
		glBlendFunc(GL_ZERO, GL_ONE_MINUS_SRC_COLOR);
		break;
	case 3://Addquatersource
		glBlendFunc(GL_ONE_MINUS_SRC_ALPHA, GL_ONE);
		break;
	default:
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//glDisable(GL_BLEND);
		break;
	}
#else
	switch (mode)
	{
	case 0://Average
		glBlendFuncSeparate(GL_CONSTANT_ALPHA, GL_CONSTANT_ALPHA, GL_ONE, GL_ZERO);
		glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
		break;
	case 1://Add
		//glBlendFuncSeparate(GL_ONE, GL_ONE, GL_ONE, GL_ZERO);
		//glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
		glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);
		glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
		break;
	case 2://Subtract
		glBlendFuncSeparate(GL_ONE, GL_ONE, GL_ONE, GL_ZERO);
		glBlendEquationSeparate(GL_FUNC_REVERSE_SUBTRACT, GL_FUNC_ADD);

		break;
	case 3://Addquatersource
		glBlendFuncSeparate(GL_CONSTANT_COLOR, GL_ONE, GL_ONE, GL_ZERO);
		glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
		break;
	default:
		glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);
		glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
		break;
	}
#endif
}