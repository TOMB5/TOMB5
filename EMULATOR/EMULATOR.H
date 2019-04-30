#ifndef EMULATOR_H
#define EMULATOR_H

#if __APPLE__
#include <stddef.h>
#endif

#include <GL/glew.h>
#if __APPLE__
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#else
#include <SDL.h>
#include <SDL_opengl.h>
#endif
#include <LIBGPU.H>

#define VRAM_WIDTH (1024)
#define VRAM_HEIGHT (512)

#define TPAGE_WIDTH (256)
#define TPAGE_HEIGHT (256)

#define CTR_RUNNING (0)
#define CTR_STOPPED (1)

#define CTR_MODE_TO_FFFF (0)
#define CTR_MODE_TO_TARG (1)

#define CTR_CLOCK_SYS (0)
#define CTR_CLOCK_PIXEL (1)
#define CTR_HORIZ_RETRACE (1)

#define CTR_CLOCK_SYS_ONE (0)
#define CTR_CLOCK_SYS_ONE_EIGHTH (1)

struct MMTEXTURE;

typedef struct
{
	unsigned int i_cycle;

	union
	{
		unsigned short cycle;
		unsigned short unk00;
	};

	unsigned int i_value;

	union
	{
		unsigned short value;
		unsigned short unk01;
	};

	unsigned int i_target;

	union
	{
		unsigned short target;
		unsigned short unk02;
	};


	unsigned int padding00;
	unsigned int padding01;
} SysCounter;

extern SysCounter counters[3];

extern void Emulator_Init(char* windowName, int screen_width, int screen_height);
extern void Emulator_InitialiseGL();
extern void Emulator_BeginScene();
extern void Emulator_EndScene();
extern void Emulator_SaveVRAM(const char* outputFileName, int x, int y, int width, int height, int bReadFromFrameBuffer);
extern void Emulator_ShutDown();
extern void Emulator_SwapWindow();
extern void Emulator_GenerateAndBindTpage(unsigned short tpage, unsigned short clut, int semiTransparent);
extern void Emulator_DestroyLastVRAMTexture();
extern void Emulator_DestroyFrameBuffer(GLuint& fbo);
extern void Emulator_GenerateFrameBuffer(GLuint& fbo);
extern void Emulator_GenerateFrameBufferTexture();
extern void Emulator_DeleteFrameBufferTexture();
extern void Emulator_GenerateAndBindNullWhite();
extern void Emulator_CheckTextureIntersection(RECT16* rect);
extern void Emulator_SetBlendMode(int mode);
extern void Emulator_UpdateInput();
extern void Emulator_CounterLoop();
extern char* Emulator_GenerateVertexArrayQuad(short* p0, short* p1, short* p2, short* p3);
extern char* Emulator_GenerateTexcoordArrayQuad(unsigned char* uv0, unsigned char* uv1, unsigned char* uv2, unsigned char* uv3);
extern char* Emulator_GenerateColourArrayQuad(unsigned char* col0, unsigned char* col1, unsigned char* col2, unsigned char* col3, bool bMultiplyColour);

#if GLTEST
extern void Emulator_TestDrawVertices(short* vptr, MMTEXTURE* tex);
#endif

extern void Emulator_AllocateVirtualMemory(unsigned int baseAddress, unsigned int size);
extern int Emulator_InitialiseGameVariables();

#pragma pack(push,1)
struct Vertex
{
	GLfloat x, y;
	GLfloat u0, v0;
	GLfloat col[4];
	GLuint padding[3];
};
#pragma pack(pop)

#endif

