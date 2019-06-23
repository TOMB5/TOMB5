#include "EMULATOR.H"

#if __APPLE__
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#else
#include <SDL.h>
#include <SDL_opengl.h>
#endif
#include <LIBPAD.H>
#include <stdio.h>
#include <LIBGPU.H>
#include <LIBETC.H>
#include <string.h>
#include <thread>
#include "EMULATOR_GLOBALS.H"
#include "CRASHHANDLER.H"
#include <assert.h>

#if __linux__ || __APPLE__
        #include <sys/mman.h>
        #include <unistd.h>
#endif

#ifdef _WINDOWS
#include <Windows.h>
#include <ddraw.h>
#endif

#define MAX_NUM_CACHED_TEXTURES (256)
#define BLEND_MODE (1)
#define V_SCALE (1)
#define VERTEX_COLOUR_MULT (2)
#define DOUBLE_BUFFERED (1)

#if NTSC_VERSION
#define COUNTER_UPDATE_INTERVAL (263)
#else
#define COUNTER_UPDATE_INTERVAL (313)
#endif

#if DX9
#include <d3dx9.h>
#include <d3d9.h>

#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "d3d9.lib")
#endif

#define MAX_NUM_VERTICES (4)
Vertex vertices[MAX_NUM_VERTICES];
int vertexCount = 0;

SDL_Window* g_window = NULL;
GLuint vramTexture = 0;
GLuint vramFrameBuffer = -1;
GLuint nullWhiteTexture = 0;
int screenWidth = 0;
int screenHeight = 0;
int windowWidth = 0;
int windowHeight = 0;
int lastTextureCacheIndex = 0;
char* pVirtualMemory = NULL;
SysCounter counters[3] = {0};
std::thread counter_thread;
int assetsLoaded = 0;

#if _WINDOWS && USE_DDRAW
LPDIRECTDRAW pDD;
#pragma comment(lib, "ddraw.lib")
#else
#undef USE_DDRAW//Codeblocks?
#endif

#if D3D9
SDL_Renderer* g_Renderer;
IDirect3DDevice9* g_Device;
#endif

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

int callGameMain(void *ptr)
{
	extern int psx_main();
	psx_main();
	return 1;
}

#undef main

int main(int argc, char* argv[])
{

	SDL_Thread* gameThread = SDL_CreateThread(callGameMain, "GameThread", (void *)NULL);
	if (gameThread ==  NULL)
	{
		printf("Failed to create thread %s\n", SDL_GetError());
	}
	
	while (true)
	{
		Emulator_UpdateInput();
	}

	return 0;
}


void Emulator_Init(char* windowName, int screen_width, int screen_height)
{

#if _WINDOWS && USE_DDRAW
	HRESULT hResult = DirectDrawCreate(NULL, &pDD, NULL);
	if (FAILED(hResult)) exit(0);
#endif

#if _DEBUG && _WINDOWS
	SetUnhandledExceptionFilter(unhandled_handler);
#endif
	screenWidth = screen_width;
	screenHeight = screen_height;
	windowWidth = screen_width * V_SCALE;
	windowHeight = screen_height * V_SCALE;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == 0)
	{
#if !DOUBLE_BUFFERED
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 0);
#endif

#if CORE_PROF_3_1
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
#elif CORE_PROF_3_2
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
#endif
		g_window = SDL_CreateWindow(windowName, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_OPENGL);

#if D3D9
		g_Renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		g_Device = SDL_RenderGetD3D9Device(g_Renderer);
#endif

	}
	else
	{
		eprinterr("Error: Failed to initialise SDL\n");
	}

#if CORE_PROF_3_1 || CORE_PROF_3_2
	SDL_GL_CreateContext(g_window);
#endif
	
	if (g_window == NULL)
	{
		eprinterr("Failed to initialise GL context!\n");
	}

#if CORE_PROF_3_1 || CORE_PROF_3_2
	glewExperimental = GL_TRUE;

	GLenum err = glewInit();

	if (err != GLEW_OK)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}
#endif
	
#if !USE_DDRAW
	SDL_GL_SetSwapInterval(1);
#endif

#if CORE_PROF_3_1 || CORE_PROF_3_2
	Emulator_InitialiseGL();
#endif

#if __linux__ || __APPLE__
	if (!Emulator_InitialiseGameVariables())
	{
		exit(0);
	}
#endif
	counter_thread = std::thread(Emulator_CounterLoop);
}

void Emulator_AllocateVirtualMemory(unsigned int baseAddress, unsigned int size)
{
	do
	{
#if __linux__ || __APPLE__
		pVirtualMemory = (char*)mmap((void*)baseAddress, size, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_ANON | MAP_SHARED, 0, 0);
#endif

#ifdef _WINDOWS
		size = size + (4096 - 1) & ~(4096 - 1);
		baseAddress = baseAddress + (4096 - 1) & ~(4096 - 1);
		MEMORY_BASIC_INFORMATION memInfo;
		VirtualQuery((void*)baseAddress, &memInfo, size);
#if _DEBUG
		printf("VQ: %d\n", GetLastError());
#endif
		if (!(memInfo.State & MEM_FREE))
		{
			if (memInfo.Type & MEM_MAPPED)
			{
#if _DEBUG
				printf("Mapped\n");
#endif
			}
			else
			{
#if _DEBUG
				printf("Not Mapped\n");
#endif
				VirtualUnlock((void*)baseAddress, memInfo.RegionSize);
				VirtualFree((void*)baseAddress, NULL, MEM_RELEASE);
			}
		}
		else
		{
			
			pVirtualMemory = (char*)VirtualAlloc((void*)memInfo.BaseAddress, size, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

#if _DEBUG
			printf("VA: %d\n", GetLastError());
#endif
		}
#endif

		if (pVirtualMemory)
		{
			printf("%x\n", (unsigned int)baseAddress);
			//VirtualLock((void*)baseAddress, size);
			break;
		}

	} while (baseAddress += size);

	if (pVirtualMemory == NULL)
	{
		printf("Failed to map virtual memory!\n");
	}

	return;
}

int Emulator_InitialiseGameVariables()
{
#if __linux__ || __APPLE__
	extern unsigned long* GadwOrderingTables;
	extern unsigned long* GadwPolygonBuffers;
	extern unsigned long* GadwOrderingTables_V2;
	extern unsigned long* terminator;

#if _WINDOWS
	SYSTEM_INFO info;
	GetSystemInfo(&info);
	Emulator_AllocateVirtualMemory((unsigned int)info.lpMinimumApplicationAddress, (5128 * 4) + (52260 * 4) + (512 * 4) + 4);
#else
	Emulator_AllocateVirtualMemory(0x400000, (5128 * 4) + (52260 * 4) + (512 * 4) + 4);
#endif
	
	if (pVirtualMemory == NULL)
	{
		return 0;
	}
	if ((uintptr_t)pVirtualMemory & 0xFF000000)
	{
		printf("*********************************************************************** And an error occured!\n");
		return 0;
	}

	GadwOrderingTables = (unsigned long*)&pVirtualMemory[0];
	GadwPolygonBuffers = (unsigned long*)&pVirtualMemory[(5128 * 4)];
	GadwOrderingTables_V2 = (unsigned long*)&pVirtualMemory[(5128 * 4) + (52260 * 4)];
	terminator = (unsigned long*)&pVirtualMemory[(5128 * 4) + (52260 * 4) + (512 * 4)];
	*terminator = -1;
#endif
	return 1;
}

void Emulator_CounterLoop()
{
	static int numUpdates = 0;
	int last_time = 0;
	
	while (TRUE)
	{
		int now = SDL_GetTicks();

		if (now > last_time + 1000)
		{
			numUpdates = 0;
			last_time = now;
		}

		if(numUpdates++ <= 60)
		{
			for (int i = 0; i < 3; i++)
			{
				//if (!counters[i].IsStopped)
				{
					counters[i].cycle += COUNTER_UPDATE_INTERVAL;
					if (counters[i].target > 0)
					{
						counters[i].cycle %= counters[i].target;
					}
				}
			}
		}
	}
}

char* Emulator_GenerateVertexArrayQuad(short* p0, short* p1, short* p2, short* p3)
{
	//Copy over position
	if (p0 != NULL)
	{
		vertices[0].x = (float)p0[0];
		vertices[0].y = (float)p0[1];
	}

	if (p1 != NULL)
	{
		vertices[1].x = (float)p1[0];
		vertices[1].y = (float)p1[1];
	}
	
	if (p2 != NULL)
	{
		vertices[2].x = (float)p2[0];
		vertices[2].y = (float)p2[1];
	}

	if (p3 != NULL)
	{
		vertices[3].x = (float)p3[0];
		vertices[3].y = (float)p3[1];
	}

	return (char*)&vertices[0].x;
}

char* Emulator_GenerateTexcoordArrayQuad(unsigned char* uv0, unsigned char* uv1, unsigned char* uv2, unsigned char* uv3)
{
	//Copy over uvs
	if (uv0 != NULL)
	{
		vertices[0].u0 = ((float)uv0[0]) / TPAGE_WIDTH;
		vertices[0].v0 = ((float)uv0[1]) / TPAGE_WIDTH;
	}
	
	if (uv1 != NULL)
	{
		vertices[1].u0 = ((float)uv1[0]) / TPAGE_WIDTH;
		vertices[1].v0 = ((float)uv1[1]) / TPAGE_WIDTH;
	}
	
	if (uv2 != NULL)
	{
		vertices[2].u0 = ((float)uv2[0]) / TPAGE_WIDTH;
		vertices[2].v0 = ((float)uv2[1]) / TPAGE_WIDTH;
	}

	if (uv3 != NULL)
	{
		vertices[3].u0 = ((float)uv3[0]) / TPAGE_WIDTH;
		vertices[3].v0 = ((float)uv3[1]) / TPAGE_WIDTH;
	}

	return (char*)&vertices[0].u0;
}

char* Emulator_GenerateColourArrayQuad(unsigned char* col0, unsigned char* col1, unsigned char* col2, unsigned char* col3, bool bMultiplyColour)
{
	//Copy over rgb vertex colours
	if (col0 != NULL)
	{
		if (bMultiplyColour)
		{
			vertices[0].col[0] = ((float)col0[0] * VERTEX_COLOUR_MULT) / 255.0f;
			vertices[0].col[1] = ((float)col0[1] * VERTEX_COLOUR_MULT) / 255.0f;
			vertices[0].col[2] = ((float)col0[2] * VERTEX_COLOUR_MULT) / 255.0f;
			vertices[0].col[3] = ((float)0xFF) / 255.0f;
		}
		else
		{
			vertices[0].col[0] = ((float)col0[0]) / 255.0f;
			vertices[0].col[1] = ((float)col0[1]) / 255.0f;
			vertices[0].col[2] = ((float)col0[2]) / 255.0f;
			vertices[0].col[3] = ((float)0xFF) / 255.0f;
		}
	}
	else
	{
		if (bMultiplyColour)
		{
			vertices[1].col[0] = ((float)col0[0] * VERTEX_COLOUR_MULT) / 255.0f;
			vertices[1].col[1] = ((float)col0[1] * VERTEX_COLOUR_MULT) / 255.0f;
			vertices[1].col[2] = ((float)col0[2] * VERTEX_COLOUR_MULT) / 255.0f;
			vertices[1].col[3] = ((float)0xFF) / 255.0f;
		}
		else
		{
			vertices[1].col[0] = ((float)col0[0]) / 255.0f;
			vertices[1].col[1] = ((float)col0[1]) / 255.0f;
			vertices[1].col[2] = ((float)col0[2]) / 255.0f;
			vertices[1].col[3] = ((float)0xFF) / 255.0f;
		}
	}

	if (col1 != NULL)
	{
		if (bMultiplyColour)
		{
			vertices[1].col[0] = ((float)col1[0] * VERTEX_COLOUR_MULT) / 255.0f;
			vertices[1].col[1] = ((float)col1[1] * VERTEX_COLOUR_MULT) / 255.0f;
			vertices[1].col[2] = ((float)col1[2] * VERTEX_COLOUR_MULT) / 255.0f;
			vertices[1].col[3] = ((float)0xFF) / 255.0f;
		}
		else
		{
			vertices[1].col[0] = ((float)col1[0]) / 255.0f;
			vertices[1].col[1] = ((float)col1[1]) / 255.0f;
			vertices[1].col[2] = ((float)col1[2]) / 255.0f;
			vertices[1].col[3] = ((float)0xFF) / 255.0f;
		}
	}
	else
	{
		if (bMultiplyColour)
		{
			vertices[1].col[0] = ((float)col0[0] * VERTEX_COLOUR_MULT) / 255.0f;
			vertices[1].col[1] = ((float)col0[1] * VERTEX_COLOUR_MULT) / 255.0f;
			vertices[1].col[2] = ((float)col0[2] * VERTEX_COLOUR_MULT) / 255.0f;
			vertices[1].col[3] = ((float)0xFF) / 255.0f;
		}
		else
		{
			vertices[1].col[0] = ((float)col0[0]) / 255.0f;
			vertices[1].col[1] = ((float)col0[1]) / 255.0f;
			vertices[1].col[2] = ((float)col0[2]) / 255.0f;
			vertices[1].col[3] = ((float)0xFF) / 255.0f;
		}
	}

	if (col2 != NULL)
	{
		if (bMultiplyColour)
		{
			vertices[2].col[0] = ((float)col2[0] * VERTEX_COLOUR_MULT) / 255.0f;
			vertices[2].col[1] = ((float)col2[1] * VERTEX_COLOUR_MULT) / 255.0f;
			vertices[2].col[2] = ((float)col2[2] * VERTEX_COLOUR_MULT) / 255.0f;
			vertices[2].col[3] = ((float)0xFF) / 255.0f;
		}
		else
		{
			vertices[2].col[0] = ((float)col2[0]) / 255.0f;
			vertices[2].col[1] = ((float)col2[1]) / 255.0f;
			vertices[2].col[2] = ((float)col2[2]) / 255.0f;
			vertices[2].col[3] = ((float)0xFF) / 255.0f;
		}
	}
	else
	{
		if (bMultiplyColour)
		{
			vertices[2].col[0] = ((float)col0[0] * VERTEX_COLOUR_MULT) / 255.0f;
			vertices[2].col[1] = ((float)col0[1] * VERTEX_COLOUR_MULT) / 255.0f;
			vertices[2].col[2] = ((float)col0[2] * VERTEX_COLOUR_MULT) / 255.0f;
			vertices[2].col[3] = ((float)0xFF) / 255.0f;
		}
		else
		{
			vertices[2].col[0] = ((float)col0[0]) / 255.0f;
			vertices[2].col[1] = ((float)col0[1]) / 255.0f;
			vertices[2].col[2] = ((float)col0[2]) / 255.0f;
			vertices[2].col[3] = ((float)0xFF) / 255.0f;
		}
	}

	if (col3 != NULL)
	{
		if (bMultiplyColour)
		{
			vertices[3].col[0] = ((float)col3[0] * VERTEX_COLOUR_MULT) / 255.0f;
			vertices[3].col[1] = ((float)col3[1] * VERTEX_COLOUR_MULT) / 255.0f;
			vertices[3].col[2] = ((float)col3[2] * VERTEX_COLOUR_MULT) / 255.0f;
			vertices[3].col[3] = ((float)0xFF) / 255.0f;
		}
		else
		{
			vertices[3].col[0] = ((float)col3[0]) / 255.0f;
			vertices[3].col[1] = ((float)col3[1]) / 255.0f;
			vertices[3].col[2] = ((float)col3[2]) / 255.0f;
			vertices[3].col[3] = ((float)0xFF) / 255.0f;
		}
	}
	else
	{
		if (bMultiplyColour)
		{
			vertices[3].col[0] = ((float)col0[0] * VERTEX_COLOUR_MULT) / 255.0f;
			vertices[3].col[1] = ((float)col0[1] * VERTEX_COLOUR_MULT) / 255.0f;
			vertices[3].col[2] = ((float)col0[2] * VERTEX_COLOUR_MULT) / 255.0f;
			vertices[3].col[3] = ((float)0xFF) / 255.0f;
		}
		else
		{
			vertices[3].col[0] = ((float)col0[0]) / 255.0f;
			vertices[3].col[1] = ((float)col0[1]) / 255.0f;
			vertices[3].col[2] = ((float)col0[2]) / 255.0f;
			vertices[3].col[3] = ((float)0xFF) / 255.0f;
		}
	}

	return (char*)&vertices[0].col[0];
}

void Emulator_InitialiseGL()
{
	unsigned short* vram = new unsigned short[VRAM_WIDTH * VRAM_HEIGHT];

	/* Generate NULL white texture */
	Emulator_GenerateAndBindNullWhite();

	/* Initialise VRAM */
	SDL_memset(vram, 0, VRAM_WIDTH * VRAM_HEIGHT * sizeof(unsigned short));

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_SCISSOR_TEST);

	/* Generate VRAM texture */
	glGenTextures(1, &vramTexture);
	glBindTexture(GL_TEXTURE_2D, vramTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, VRAM_WIDTH, VRAM_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_SHORT_1_5_5_5_REV, &vram[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	/* Generate VRAM Frame Buffer */
	glGenFramebuffers(1, &vramFrameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, vramFrameBuffer);

	/* Bind VRAM texture to vram framebuffer */
#if CORE_PROF_3_1
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, vramTexture, 0);
#elif CORE_PROF_3_2
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, vramTexture, 0);
#endif

#if CORE_PROF_3_1 || CORE_PROF_3_2
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		eprinterr("Frame buffer error");
	}
#endif

	glLineWidth(INTERNAL_RESOLUTION_SCALE);
	
	SDL_memset(&vertices[0].x, 0, sizeof(Vertex) * MAX_NUM_VERTICES);

#if BLEND_MODE
	glBlendColor(0.25, 0.25, 0.25, 0.5);
#endif
	glShadeModel(GL_SMOOTH);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();

	delete[] vram;
}

void Emulator_GenerateAndBindNullWhite()
{
	unsigned int pixelData;
	pixelData = -1;

	glGenTextures(1, &nullWhiteTexture);
	glBindTexture(GL_TEXTURE_2D, nullWhiteTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, &pixelData);
}

void Emulator_CheckTextureIntersection(RECT16* rect)///@TODO internal upres
{
	for (int i = lastTextureCacheIndex - 1; i > -1; i--)
	{
		if (!(cachedTextures[i].tpageX > rect->x + rect->w || cachedTextures[i].tpageX + TPAGE_WIDTH < rect->x || cachedTextures[i].tpageY > rect->y + rect->h || cachedTextures[i].tpageY + TPAGE_HEIGHT < rect->y))
		{
			cachedTextures[i].lastAccess = -1;
			cachedTextures[i].tpageX = -1;
			cachedTextures[i].tpageY = -1;
			glDeleteTextures(1, &cachedTextures[i].textureID);
		}
	}
}

void Emulator_SaveVRAM(const char* outputFileName, int x, int y, int width, int height, int bReadFromFrameBuffer)
{
#if NOFILE
	return;
#endif

	FILE* f = fopen(outputFileName, "wb");
	if (f == NULL)
	{
		return;
	}
	unsigned char TGAheader[12] = { 0,0,2,0,0,0,0,0,0,0,0,0 };
	unsigned char header[6] = { width % 256, width / 256, height % 256, height / 256,16,0 };
	unsigned short* pixels = new unsigned short[width * height];

	if (bReadFromFrameBuffer)
	{
		glReadPixels(x, y, width, height, GL_BGRA, GL_UNSIGNED_SHORT_1_5_5_5_REV, pixels);
	}
	else
	{
		glGetTexImage(GL_TEXTURE_2D, 0, GL_BGRA, GL_UNSIGNED_SHORT_1_5_5_5_REV, pixels);
	}

	fwrite(TGAheader, sizeof(unsigned char), 12, f);
	fwrite(header, sizeof(unsigned char), 6, f);

	//512 const is hdd sector size
	int numSectorsToWrite = (width * height * sizeof(unsigned short)) / 512;
	int numRemainingSectorsToWrite = (width * height * sizeof(unsigned short)) % 512;

	for (int i = 0; i < numSectorsToWrite; i++)
	{
		fwrite(&pixels[i * 512 / sizeof(unsigned short)], 512, 1, f);
	}

	for (int i = 0; i < numRemainingSectorsToWrite; i++)
	{
		fwrite(&pixels[numSectorsToWrite * 512 / sizeof(unsigned short)], numRemainingSectorsToWrite, 1, f);
	}

	fclose(f);
	delete[] pixels;
}

void Emulator_BeginScene()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_JOYDEVICEADDED:
			if (SDL_IsGameController(event.jbutton.which))
			{
				padHandle[event.jbutton.which] = SDL_GameControllerOpen(event.jbutton.which);
			}
			break;
		case SDL_JOYDEVICEREMOVED:
			SDL_GameControllerClose(padHandle[event.jbutton.which]);
			break;
		case SDL_QUIT:
			Emulator_ShutDown();
			break;
		case SDL_WINDOWEVENT:
			switch (event.window.event)
			{
			case SDL_WINDOWEVENT_CLOSE:
				Emulator_ShutDown();
				break;
			}
			break;
		}
	}
}

void Emulator_UpdateInput()
{
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
#if DOUBLE_BUFFERED
	SDL_GL_SwapWindow(g_window);
#else
	glFinish();
#endif
}

void Emulator_EndScene()
{
	glBindFramebuffer(GL_READ_FRAMEBUFFER, vramFrameBuffer);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	glBlitFramebuffer(word_33BC.disp.x * INTERNAL_RESOLUTION_SCALE, word_33BC.disp.y * INTERNAL_RESOLUTION_SCALE, (word_33BC.disp.x + word_33BC.disp.w) * INTERNAL_RESOLUTION_SCALE, (word_33BC.disp.y + word_33BC.disp.h) * INTERNAL_RESOLUTION_SCALE, 0, word_33BC.disp.h * INTERNAL_RESOLUTION_SCALE, word_33BC.disp.w * INTERNAL_RESOLUTION_SCALE, 0, GL_COLOR_BUFFER_BIT, GL_NEAREST);
	
#if _DEBUG
	Emulator_SaveVRAM("VRAM.TGA", 0, 0, VRAM_WIDTH, VRAM_HEIGHT, TRUE);
#endif

	Emulator_SwapWindow();
}

void Emulator_ShutDown()
{
	Emulator_DestroyFrameBuffer(vramFrameBuffer);
	glDeleteTextures(1, &vramTexture);
	glDeleteTextures(1, &nullWhiteTexture);
	SDL_QuitSubSystem(SDL_INIT_GAMECONTROLLER);

	for (int i = 0; i < lastTextureCacheIndex; i++)
	{
		glDeleteTextures(1, &cachedTextures[i].textureID);
	}
#ifdef _WINDOWS
	//VirtualFree(pVirtualMemory, 0, MEM_RELEASE);
#endif

#if D3D9
	SDL_DestroyRenderer(g_Renderer);
#endif

	SDL_DestroyWindow(g_window);
	SDL_Quit();
	exit(0);
}

void Emulator_GenerateFrameBuffer(GLuint& fbo)
{
#if CORE_PROF_3_1 || CORE_PROF_3_2
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
#endif
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

void Emulator_GenerateAndBindTpage(unsigned short tpage, unsigned short clut, int semiTransparent)
{
	unsigned int textureType = (tpage >> 7) & 0x3;
	unsigned int tpageX = ((tpage << 6) & 0x7C0 % 1024);
	unsigned int tpageY = (((tpage << 4) & 0x100) + ((tpage >> 2) & 0x200));
	unsigned int clutX = ((clut & 0x3F) << 4);
	unsigned int clutY = (clut >> 6);
	unsigned int tpageAbr = (tpage >> 5) & 3;

	tpageX += ((VRAM_WIDTH - (VRAM_WIDTH / INTERNAL_RESOLUTION_SCALE)) / 2);
	if (tpageY >= 256)
	{
		tpageY += ((VRAM_HEIGHT - (VRAM_HEIGHT / INTERNAL_RESOLUTION_SCALE)) / 2) * 2;
	}

	clutX += ((VRAM_WIDTH - (VRAM_WIDTH / INTERNAL_RESOLUTION_SCALE)) / 2);
	if (clutY >= 256)
	{
		clutY += ((VRAM_HEIGHT - (VRAM_HEIGHT / INTERNAL_RESOLUTION_SCALE)) / 2);
	}

	Emulator_SetBlendMode(tpageAbr);

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

	if (!bMustAddTexture)
	{
		return;
	}

	if (bMustAddTexture)
	{
		switch (textureType)
		{
		case 2:
		{
			//ARGB1555
			unsigned short* texturePage = new unsigned short[TPAGE_WIDTH * TPAGE_HEIGHT];
			glReadPixels(tpageX * INTERNAL_RESOLUTION_SCALE, tpageY * INTERNAL_RESOLUTION_SCALE, TPAGE_WIDTH, TPAGE_HEIGHT, GL_BGRA, GL_UNSIGNED_SHORT_1_5_5_5_REV, &texturePage[0]);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 256, 256, 0, GL_BGRA, GL_UNSIGNED_SHORT_1_5_5_5_REV, &texturePage[0]);
			delete[] texturePage;
			break;
		}
		case 1:
		{
			//RGBA8888
			assert(0);
			//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 256, 256, 0, GL_RGBA, GL_UNSIGNED_BYTE, &texturePage[0]);
			break;
		}
		case 0:
		{
			//RGBA4444
			unsigned short* texturePage = new unsigned short[TPAGE_WIDTH / 4 * TPAGE_HEIGHT];
			unsigned short* clut = new unsigned short[16];
			unsigned short* convertedTpage = new unsigned short[TPAGE_WIDTH * TPAGE_HEIGHT];
			//Read CLUT
			glReadPixels(clutX, clutY, CLUT_WIDTH, CLUT_HEIGHT, GL_BGRA, GL_UNSIGNED_SHORT_1_5_5_5_REV, &clut[0]);

			//Read texture data
			glReadPixels(tpageX, tpageY, TPAGE_WIDTH / 4, TPAGE_HEIGHT, GL_RGBA, GL_UNSIGNED_SHORT_1_5_5_5_REV, &texturePage[0]);

			unsigned short* convertPixel = &convertedTpage[0];

			for (int xy = 0; xy < TPAGE_WIDTH / 4 * TPAGE_HEIGHT; xy++)
			{
				*convertPixel++ = clut[(texturePage[xy] & (0xF << 0 * 4)) >> (0 * 4)];
				*convertPixel++ = clut[(texturePage[xy] & (0xF << 1 * 4)) >> (1 * 4)];
				*convertPixel++ = clut[(texturePage[xy] & (0xF << 2 * 4)) >> (2 * 4)];
				*convertPixel++ = clut[(texturePage[xy] & (0xF << 3 * 4)) >> (3 * 4)];
			}

#if _DEBUG
			FILE* f = fopen("TPAGE.TGA", "wb");
			unsigned char TGAheader[12] = { 0,0,2,0,0,0,0,0,0,0,0,0 };
			unsigned char header[6] = { 256 % 256, 256 / 256, 256 % 256, 256 / 256,16,0 };
			fwrite(TGAheader, sizeof(unsigned char), 12, f);
			fwrite(header, sizeof(unsigned char), 6, f);
			fwrite(&convertedTpage[0], sizeof(char), 256 * 256 * 2, f);
			fclose(f);
			
			FILE* f2 = fopen("TPAGE2.TGA", "wb");
			unsigned char TGAheader2[12] = { 0,0,2,0,0,0,0,0,0,0,0,0 };
			unsigned char header2[6] = { 256/4 % 256, 256/4 / 256, 256 % 256, 256 / 256,16,0 };
			fwrite(TGAheader2, sizeof(unsigned char), 12, f2);
			fwrite(header2, sizeof(unsigned char), 6, f2);
			fwrite(&texturePage[0], sizeof(char), 256/4 * 256 * 2, f2);
			fclose(f2);
#endif
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TPAGE_WIDTH, TPAGE_HEIGHT, 0, GL_BGRA, GL_UNSIGNED_SHORT_1_5_5_5_REV, &convertedTpage[0]);
			delete[] texturePage;
			delete[] convertedTpage;
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

void Emulator_SetBlendMode(int mode)
{
	glEnable(GL_BLEND);
#if !BLEND_MODE
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
		glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE);
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
	}
#endif
}
