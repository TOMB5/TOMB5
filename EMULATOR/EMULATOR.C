#include "EMULATOR.H"

#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <LIBPAD.H>
#include <stdio.h>
#include <LIBGPU.H>
#include <string.h>

#define MAX_NUM_CACHED_TEXTURES (256)

SDL_Window* g_window = NULL;
SDL_Renderer* g_renderer;

GLuint vramTexture = 0;
int screenWidth = 0;
int screenHeight = 0;
int lastTextureCacheIndex = 0;

struct CachedTexture
{
	GLuint textureID;
	unsigned int tpageX;
	unsigned int tpageY;
	unsigned int lastAccess;
};

struct CachedTexture cachedTextures[MAX_NUM_CACHED_TEXTURES];

void Emulator_Init(int screen_width, int screen_height)
{
	screenWidth = screen_width;
	screenHeight = screen_height;

	if (SDL_Init(SDL_INIT_VIDEO) == 0)
	{
		g_window = SDL_CreateWindow("TOMB5", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_width, screen_height, SDL_WINDOW_OPENGL);
		g_renderer = SDL_CreateRenderer(g_window, 0, SDL_RENDERER_ACCELERATED);
		if (g_renderer == NULL)
		{
			printf("Error initialising renderer\n");
		}
	}
	else
	{
		printf("Error: Failed to initialise SDL\n");
	}

	SDL_GL_CreateContext(g_window);

	if (glewInit() != GLEW_OK)
	{
		printf("Error initialising GLEW!\n");
	}

	SDL_memset(&vram, 0, sizeof(1024 * 512 * 2));
	SDL_GL_SetSwapInterval(1);
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
	glClear((GL_COLOR_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

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
}

void Emulator_SwapWindow()
{
	SDL_GL_SwapWindow(g_window);
}

void Emulator_EndScene()
{

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &vramTexture);
	glBindTexture(GL_TEXTURE_2D, vramTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1024, 512, 0, GL_RGBA, GL_UNSIGNED_SHORT_1_5_5_5_REV, &vram[0]);

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
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

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

	if (padData[0] != NULL)
	{
		((unsigned short*)padData[0])[1] = UpdateKeyboardInput();
	}
}

void Emulator_ShutDown()
{
	glDeleteTextures(1, &vramTexture);
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
	glGenTextures(1, &vramTexture);
	glBindTexture(GL_TEXTURE_2D, vramTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1024, 512, 0, GL_RGBA, GL_UNSIGNED_SHORT_1_5_5_5_REV, &vram[0]);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, vramTexture, 0);
}

void Emulator_DeleteFrameBufferTexture()
{
	glDeleteTextures(1, &vramTexture);
}

GLuint Emulator_FindTextureInCache(unsigned int tpageX, unsigned int tpageY)///@TODO check rectangular intersection plus clut x, y
{
	for (int i = lastTextureCacheIndex-1; i > -1; i--)
	{
		if (cachedTextures[i].tpageX == tpageX && cachedTextures[i].tpageY == tpageY)
		{
			cachedTextures[i].lastAccess = SDL_GetTicks();
			return cachedTextures[i].textureID;
		}
	}


	return -1;
}

void Emulator_GenerateAndBindTpage(unsigned int type, unsigned int tpageX, unsigned int tpageY, unsigned int clutX, unsigned int clutY)
{
	GLuint tpageTexture = Emulator_FindTextureInCache(tpageX, tpageY);
	bool bMustAddTexture = tpageTexture == -1 ? 1 : 0;

	if (bMustAddTexture)
	{
		cachedTextures[lastTextureCacheIndex].tpageX = tpageX;
		cachedTextures[lastTextureCacheIndex].tpageY = tpageY;
		glGenTextures(1, &cachedTextures[lastTextureCacheIndex].textureID);
		tpageTexture = cachedTextures[lastTextureCacheIndex++].textureID;
	}

	glBindTexture(GL_TEXTURE_2D, tpageTexture);

	if (bMustAddTexture)
	{
		switch (type)
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


#if 0
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
			//RGBA8888
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
						*dst++ = (255 << 24) | (((clut[(*src & 0xF0) >> 4] & 0xFF0000) >> 16) << 16) | (((clut[(*src & 0xF0) >> 4] & 0xFF00) >> 8) << 8) | (clut[(*src & 0xF0) >> 4] & 0xFF);
						*dst++ = (255 << 24) | (((clut[(*src & 0xF00) >> 8] & 0xFF0000) >> 16) << 16) | (((clut[(*src & 0xF00) >> 8] & 0xFF00) >> 8) << 8) | (clut[(*src & 0xF00) >> 8] & 0xFF);
						*dst++ = (255 << 24) | (((clut[(*src & 0xF000) >> 12] & 0xFF0000) >> 16) << 16) | (((clut[(*src & 0xF000) >> 12] & 0xFF00) >> 8) << 8) | (clut[(*src & 0xF000) >> 12] & 0xFF);
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
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 256, 256, 0, GL_RGBA, GL_UNSIGNED_BYTE, &texturePage[0]);
			break;
		}
		}
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

void Emulator_DestroyFrameBuffer(GLuint& fbo)
{
	glDeleteFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Emulator_DestroyLastVRAMTexture()
{
	unsigned short* pixelData = new unsigned short[word_unknown00.clip.w * word_unknown00.clip.h];
	unsigned short* dst = &pixelData[0];
	glReadPixels(word_unknown00.clip.x, word_unknown00.clip.y, word_unknown00.clip.w, word_unknown00.clip.h, GL_RGBA, GL_UNSIGNED_SHORT_1_5_5_5_REV, pixelData);

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
	unsigned char TGAheader[12] = { 0,0,2,0,0,0,0,0,0,0,0,0 };
	unsigned char header[6] = { word_unknown00.clip.w % 256, word_unknown00.clip.w / 256, word_unknown00.clip.h % 256, word_unknown00.clip.h / 256,16,0 };
	fwrite(TGAheader, sizeof(unsigned char), 12, f);
	fwrite(header, sizeof(unsigned char), 6, f);
	fwrite(pixelData, sizeof(char), word_unknown00.clip.w * word_unknown00.clip.h * 2, f);
	fclose(f);
#endif
}