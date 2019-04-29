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

#define CTR_RUNNING (0)
#define CTR_STOPPED (1)

#define CTR_MODE_TO_FFFF (0)
#define CTR_MODE_TO_TARG (1)

#define CTR_CLOCK_SYS (0)
#define CTR_CLOCK_PIXEL (1)
#define CTR_HORIZ_RETRACE (1)

#define CTR_CLOCK_SYS_ONE (0)
#define CTR_CLOCK_SYS_ONE_EIGHTH (1)

#define INT24_MAX						0xFFFFFF
#define INT16_MAX                       0xFFFF
#define INT8_MAX						0xFF

#define INT8_4_BYTE_F000				0xFF000000
#define INT8_3_BYTE_F00					0xFF0000
#define INT8_2_BYTE_F0					0xFF00
#define HALF_2_BYTE_F000				0xF000
#define HALF_1_BYTE_F0					0xF0
#define INT16_LOW_HALF					0xF00

struct MMTEXTURE;

typedef struct
{
	uint16_t Value;
	uint16_t _pad1;

	union
	{
		struct
		{
			uint32_t _pad2 : 2;
			uint32_t IsStopped : 1;
			uint32_t _pad3 : 1;
			uint32_t TargetMode : 1;
			uint32_t IRQ1 : 1;
			uint32_t _pad4 : 1;
			uint32_t IRQ2 : 1;
			uint32_t _pad5 : 1;
			uint32_t Clock : 1;
			uint32_t Division : 1;
			uint32_t _pad6 : 21;
		};
		uint32_t I2;
	};
	union
	{
		struct
		{
			uint16_t Target;
			uint16_t _pad7;
		};
		uint32_t I3;
	};
} SysCounter;

extern SysCounter counters[3];

extern void Emulator_Init(char* windowName, int screen_width, int screen_height);
extern void Emulator_InitialiseGL();
extern void Emulator_BeginScene();
extern void Emulator_EndScene();
extern void Emulator_SaveVRAM(int width, int height);
extern void Emulator_SaveVRAM2(int width, int height);
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

