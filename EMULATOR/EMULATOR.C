#include "EMULATOR.H"

#define GL_GLEXT_PROTOTYPES 1
#define GLEW_STATIC 1
#include <gl\glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_opengl_glext.h>
#include <stdio.h>
#include <LIBGPU.H>

SDL_Window* g_window = NULL;
SDL_Renderer* g_renderer;

GLuint vramTexture = 0;
int screenWidth = 0;
int screenHeight = 0;

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
#if _DEBUG
	//glClearColor(184.0f, 213.0f, 238.0f, 1.0f);
#endif
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
	Emulator_SaveVRAM2(1024, 512);
	Emulator_SwapWindow();

	glDisable(GL_TEXTURE_2D);
	glDeleteTextures(1, &vramTexture);
}

void Emulator_ShutDown()
{
	glDeleteTextures(1, &vramTexture);
}