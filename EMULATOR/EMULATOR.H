#ifndef EMULATOR_H
#define EMULATOR_H

#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
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
extern void Emulator_GenerateAndBindTpage(unsigned short tpage, unsigned short clut);
extern void Emulator_DestroyLastVRAMTexture();
extern void Emulator_DestroyFrameBuffer(GLuint& fbo);
extern void Emulator_GenerateFrameBuffer(GLuint& fbo);
extern void Emulator_GenerateFrameBufferTexture();
extern void Emulator_DeleteFrameBufferTexture();
extern void Emulator_GenerateAndBindNullWhite();
extern void Emulator_CheckTextureIntersection(RECT16* rect);
extern void Emulator_SetBlendMode(int mode);
extern void Emulator_CounterLoop();

#endif

