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

#if __linux__ || __APPLE__
        #include <sys/mman.h>
        #include <unistd.h>
#endif

#ifdef _WINDOWS
#include <Windows.h>
#endif

#define CORE_PROF_3_1 (1)
#define CORE_PROF_3_2 (0)
#define MAX_NUM_CACHED_TEXTURES (256)
#define BLEND_MODE (1)
#define DX9 (0)
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
GLuint nullWhiteTexture = 0;
int screenWidth = 0;
int screenHeight = 0;
int windowWidth = 0;
int windowHeight = 0;
int lastTextureCacheIndex = 0;
char* pVirtualMemory = NULL;
SysCounter counters[3] = {0};
std::thread counter_thread;

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

int main(int argc, char* argv[])
{
	SDL_Thread* gameThread = SDL_CreateThread(callGameMain, "GameThread", (void *)NULL);
	if (gameThread ==  NULL)
	{
		printf("Failed to create thread %s\n", SDL_GetError());
	}
	
	while (true)
	{
		///@FIXME Warning SDL was not initialised in this thread!
		Emulator_UpdateInput();
	}
	return 0;
}


void Emulator_Init(char* windowName, int screen_width, int screen_height)
{
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
		g_window = SDL_CreateWindow(windowName, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_OPENGL);
#elif CORE_PROF_3_2
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		g_window = SDL_CreateWindow(windowName, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_OPENGL);
#else
		Direct3D_object = Direct3DCreate9(D3D_SDK_VERSION);
		if (Direct3D_object == NULL)
		{
			MessageBox(GetActiveWindow(), "Could not create Direct3D Object", "D3D_OBJ ERR", MB_OK);
			return 0;
		}
#endif
	}
	else
	{
		eprinterr("Error: Failed to initialise SDL\n");
	}

	SDL_GL_CreateContext(g_window);
	if (g_window == NULL)
	{
		eprinterr("Failed to initialise GL context!\n");
	}

#if CORE_PROF_3_1 || CORE_PROF_3_2
	glewExperimental = GL_TRUE;
#endif

	GLenum err = glewInit();

	if (err != GLEW_OK)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}

	SDL_memset(&vram, 0, sizeof(1024 * 512 * 2));
	SDL_GL_SetSwapInterval(1);

	Emulator_InitialiseGL();
	
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
		vertices[0].u0 = ((float)uv0[0]) / 256.0f;
		vertices[0].v0 = ((float)uv0[1]) / 256.0f;
	}
	
	if (uv1 != NULL)
	{
		vertices[1].u0 = ((float)uv1[0]) / 256.0f;
		vertices[1].v0 = ((float)uv1[1]) / 256.0f;
	}
	
	if (uv2 != NULL)
	{
		vertices[2].u0 = ((float)uv2[0]) / 256.0f;
		vertices[2].v0 = ((float)uv2[1]) / 256.0f;
	}

	if (uv3 != NULL)
	{
		vertices[3].u0 = ((float)uv3[0]) / 256.0f;
		vertices[3].v0 = ((float)uv3[1]) / 256.0f;
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
	//Initialise vertex array
	glEnable(GL_TEXTURE_2D);
	memset(&vertices[0].x, 0, sizeof(Vertex) * MAX_NUM_VERTICES);
	Emulator_GenerateAndBindNullWhite();

#if BLEND_MODE
	glBlendColor(0.25, 0.25, 0.25, 0.5);
#endif
	glShadeModel(GL_SMOOTH);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
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
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glClear((GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT || (event.type == SDL_WINDOWEVENT &&
			event.window.event == SDL_WINDOWEVENT_CLOSE))
		{
			Emulator_ShutDown();
			SDL_Quit();
			exit(0);
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
	glGenTextures(1, &vramTexture);
	glBindTexture(GL_TEXTURE_2D, vramTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1024, 512, 0, GL_RGBA, GL_UNSIGNED_SHORT_1_5_5_5_REV, &vram[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	float x = 1.0f / (1024.0f / (float)(word_33BC.disp.x));
	float y = 1.0f / (512.0f / (float)(word_33BC.disp.y));
	float h = 1.0f / (512.0f / (float)(word_33BC.disp.h));
	float w = 1.0f / (1024.0f / (float)(word_33BC.disp.w));

	float vertexBuffer[] =
	{
		0.0f, (float)word_33BC.disp.h, 0.0f, x, y,
		0.0f, 0.0f, 0.0f, x, y + h,
		(float)word_33BC.disp.w, 0.0f, 0.0f, x + w, y + h,
		(float)word_33BC.disp.w, (float)word_33BC.disp.h, 0.0f, x + w, y,
		(float)word_33BC.disp.w, 0.0f, 0.0f, x + w, y + h,
		0.0f, (float)word_33BC.disp.h, 0.0f, x, y,
	};

	glVertexPointer(3, GL_FLOAT, 5 * sizeof(float), vertexBuffer);
	glTexCoordPointer(2, GL_FLOAT, 5 * sizeof(float), vertexBuffer+3);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glLoadIdentity();
	glOrtho(0, word_33BC.disp.w, 0, word_33BC.disp.h, -1, 1);
	glDrawArrays(GL_TRIANGLES, 0, 6);

#if _DEBUG
	Emulator_SaveVRAM("VRAM.TGA", 0, 0, 1024, 512, FALSE);
#endif
	Emulator_SwapWindow();

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
#ifdef _WINDOWS
	//VirtualFree(pVirtualMemory, 0, MEM_RELEASE);
#endif
}

void Emulator_GenerateFrameBuffer(GLuint& fbo)
{
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
}

void Emulator_GenerateFrameBufferTexture()
{
	unsigned short* pixelData = new unsigned short[activeDrawEnv.clip.w * activeDrawEnv.clip.h];
	unsigned short* dst = &pixelData[0];

	//Read disp env area from vram
	for (int y = activeDrawEnv.clip.y; y < 512; y++)
	{
		for (int x = activeDrawEnv.clip.x; x < 1024; x++)
		{
			unsigned short* src = vram + (y * 1024 + x);

			if (x >= activeDrawEnv.clip.x && x < activeDrawEnv.clip.x + activeDrawEnv.clip.w &&
				y >= activeDrawEnv.clip.y && y < activeDrawEnv.clip.y + activeDrawEnv.clip.h)
			{
				*dst++ = src[0];
			}
		}
	}

	glGenTextures(1, &vramTexture);
	glBindTexture(GL_TEXTURE_2D, vramTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, activeDrawEnv.clip.w, activeDrawEnv.clip.h, 0, GL_RGBA, GL_UNSIGNED_SHORT_1_5_5_5_REV, &pixelData[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

#if CORE_PROF_3_1
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, vramTexture, 0);
#else
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, vramTexture, 0);
#endif

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		eprinterr("Frame buffer error");
	}
	
#if _DEBUG
	Emulator_SaveVRAM("VRAM4.TGA", 0, 0, activeDrawEnv.clip.w, activeDrawEnv.clip.h, TRUE);
#endif

	delete[] pixelData;
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

void Emulator_GenerateAndBindTpage(unsigned short tpage, unsigned short clut, int semiTransparent)
{
	unsigned int textureType = (tpage >> 7) & 0x3;
	unsigned int tpageX = (tpage << 6) & 0x7C0 % 1024;
	unsigned int tpageY = ((tpage << 4) & 0x100) + ((tpage >> 2) & 0x200);
	unsigned int clutX = (clut & 0x3F) << 4;
	unsigned int clutY = (clut >> 6);
	unsigned int tpageAbr = (tpage >> 5) & 3;

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

#if _DEBUG && !NOFILE
				FILE* f = fopen("TPAGE.TGA", "wb");
				unsigned char TGAheader[12] = { 0,0,2,0,0,0,0,0,0,0,0,0 };
				unsigned char header[6] = { 256 % 256, 256 / 256, 256 % 256, 256 / 256,16,0 };
				fwrite(TGAheader, sizeof(unsigned char), 12, f);
				fwrite(header, sizeof(unsigned char), 6, f);
				for (int line = 255; line >= 0; line--)
					fwrite(&texturePage[line * 256], sizeof(short), 256, f);
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


#if _DEBUG && !NOFILE
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
	unsigned short* pixelData = new unsigned short[activeDrawEnv.clip.w * activeDrawEnv.clip.h];
	unsigned short* dst = &pixelData[0];
	glReadPixels(0, 0, activeDrawEnv.clip.w, activeDrawEnv.clip.h, GL_RGBA, GL_UNSIGNED_SHORT_1_5_5_5_REV, pixelData);

	for (int y = activeDrawEnv.clip.y; y < activeDrawEnv.clip.y + activeDrawEnv.clip.h; y++)
	{
		for (int x = activeDrawEnv.clip.x; x < activeDrawEnv.clip.x + activeDrawEnv.clip.w; x++)
		{
			unsigned short* src = vram + (y * 1024 + x);

			src[0] = *dst++;
		}
	}

#if _DEBUG && !NOFILE
	Emulator_SaveVRAM("VRAM2.TGA", 0, 0, activeDrawEnv.clip.w, activeDrawEnv.clip.h, TRUE);
#endif

	delete[] pixelData;
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

#if GLTEST
struct TEXTURE
{
	unsigned char u0;
	unsigned char v0;
	unsigned short clut;
	unsigned char u1;
	unsigned char v1;
	unsigned short tpage;
	unsigned char u2;
	unsigned char v2;
	unsigned char id[2];
	unsigned char u3;
	unsigned char v3;
	unsigned short wclut;
};

struct MMTEXTURE
{
	TEXTURE t[3];
};

struct tr_vertex   // 6 bytes
{
	int16_t x;
	int16_t y;
	int16_t z;
};

struct mesh_header
{
	short x;
	short y;
	short z;
	short radius;
	char vertices;
	char flags;
	short face_offset;
};

struct tr4_mesh_face4    // 12 bytes
{
	uint16_t Vertices[4];
	uint16_t Texture;
	uint16_t Effects;
};

struct tr4_mesh_face3    // 10 bytes
{
	uint16_t Vertices[3];
	uint16_t Texture;
	uint16_t Effects;    // TR4-5 ONLY: alpha blending and environment mapping strength
};


void Emulator_TestDrawVertices(short* vptr, MMTEXTURE* tex)
{
	mesh_header* h = (mesh_header*)vptr;
	uint8_t num_vert = h->vertices;

	tr_vertex* ptr = (tr_vertex*)(h + 1);

	vptr += 6;
	short num_normals = *vptr;

	if (num_normals > 0)
		vptr += num_normals * 3;
	else
		vptr += -num_normals;

	short num_rects = *vptr;
	auto rects = (tr4_mesh_face4*)++vptr;

	vptr += num_rects * 6;

	short num_tris = *vptr;
	auto tris = (tr4_mesh_face3*)++vptr;

	for(int i = 0; i < num_rects; i++, rects++)
	{
		auto poly = &tex[rects->Texture].t[0];
		Emulator_GenerateAndBindTpage(poly->tpage, poly->clut, 0);

		glBegin(GL_QUADS);

		glTexCoord2f(poly->u0 / 256.0f, poly->v0 / 256.0f);
		glVertex3s(ptr[rects->Vertices[0]].x, ptr[rects->Vertices[0]].y, ptr[rects->Vertices[0]].z);

		glTexCoord2f(poly->u1 / 256.0f, poly->v1 / 256.0f);
		glVertex3s(ptr[rects->Vertices[1]].x, ptr[rects->Vertices[1]].y, ptr[rects->Vertices[1]].z);

		glTexCoord2f(poly->u3 / 256.0f, poly->v3 / 256.0f);
		glVertex3s(ptr[rects->Vertices[3]].x, ptr[rects->Vertices[3]].y, ptr[rects->Vertices[3]].z);

		glTexCoord2f(poly->u2 / 256.0f, poly->v2 / 256.0f);
		glVertex3s(ptr[rects->Vertices[2]].x, ptr[rects->Vertices[2]].y, ptr[rects->Vertices[2]].z);

		glEnd();
	}

#endif