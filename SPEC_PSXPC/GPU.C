#include "GPU.H"

#include <SDL.h>
#include <SDL_opengl.h>

unsigned long GnFrameCounter = 0;
unsigned long GnLastFrameCount = 0;
struct PSXTEXTSTRUCT* psxtextinfo;
struct PSXSPRITESTRUCT* psxspriteinfo;
int rgbscaleme;
int gfx_debugging_mode;
struct DB_STRUCT db;
struct MMTEXTURE* RoomTextInfo;
unsigned long GadwOrderingTables_V2[512];
static int LnFlipFrame;
unsigned long GadwOrderingTables[5128];
unsigned long GadwPolygonBuffers[52260];

SDL_Window* g_window = NULL;


void GPU_UseOrderingTables(unsigned long* pBuffers, int nOTSize)//5DF68, 5F1C8
{
}

void GPU_UsePolygonBuffers(unsigned long* pBuffers, int nPBSize)
{
}

void GPU_BeginScene()
{
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
}

int GPU_FlipNoIdle()//5E078, 5F264
{

	//ret LnFlipFrame
	return 0;
}

void GPU_GetScreenPosition(short x, short y)
{
}

void GPU_ClearVRAM()
{
}

void GPU_FlipToBuffer(int unknown)
{
	//unknown is probably db.current_buffer flip index
}

void GPU_EndScene()
{
	//int nPolys;
	//static int nWorstPolys;
	SDL_GL_SwapWindow(g_window);
}
