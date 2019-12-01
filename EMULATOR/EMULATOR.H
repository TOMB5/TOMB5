#ifndef EMULATOR_H
#define EMULATOR_H

/*
 * Platform specific emulator setup
 */
#if (defined(_WINDOWS) || defined(__APPLE__) || defined(__linux__) || defined(__MINGW32__)) && !defined(__ANDROID__)
#define OGL
//#define D3D9
#define SDL2
#if defined(OGL)
#define GLEW
#endif
//#define OGLES
//#define ES3_SHADERS
#elif defined(__EMSCRIPTEN__) || defined(__ANDROID__)
#define OGLES
#define ES3_SHADERS
#endif

#if defined(GLEW)
#define GL_GLEXT_PROTOTYPES 1
#include <GL/glew.h>
#endif

/*
 * Emulator render options.
 */
#define RO_DOUBLE_BUFFERED

#if defined(__APPLE__) || defined(__EMSCRIPTEN__)
#include <stddef.h>
#endif

/*
 * SDL.H inclusion.
 */

#if defined(__APPLE__)
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#elif defined(__EMSCRIPTEN__)
#include <emscripten.h>
#include <SDL.h>
#elif (defined(_WINDOWS) || defined(__MINGW32__) || defined(__linux__)) && !defined(__ANDROID__)
#include <SDL.h>
#elif defined (__ANDROID__)
#include <SDL.h>
#endif

#if defined (OGL)
#include <SDL_opengl.h>///@FIXME see mac!
#elif defined (OGLES)
#include <SDL_syswm.h>
#include <GLES3/gl3.h>
#include <EGL/egl.h>
#endif

#include <LIBGPU.H>

#define RESOLUTION_SCALE (1)

#define MAX_NUM_CACHED_TEXTURES (512)

#define VRAM_WIDTH (1024 * RESOLUTION_SCALE)
#define VRAM_HEIGHT (512 * RESOLUTION_SCALE)

#define TPAGE_WIDTH (256)
#define TPAGE_HEIGHT (256)

#define CLUT_WIDTH (16)
#define CLUT_HEIGHT (1)

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

#pragma pack(push,1)
struct Vertex
{
	GLfloat x, y;
	GLfloat u0, v0;
	GLfloat col[4];
};
#pragma pack(pop)

extern GLuint g_lastBoundTexture;

extern void Emulator_InitialiseGL();
extern void Emulator_SaveVRAM(const char* outputFileName, int x, int y, int width, int height, int bReadFromFrameBuffer);
extern void Emulator_ShutDown();
extern void Emulator_SwapWindow();
extern GLuint Emulator_GenerateTpage(unsigned short tpage, unsigned short clut);
extern void Emulator_DestroyFrameBuffer(GLuint& fbo);
extern void Emulator_GenerateFrameBuffer(GLuint& fbo);
extern void Emulator_GenerateAndBindNullWhite();
extern void Emulator_CheckTextureIntersection(RECT16* rect);
extern void Emulator_SetBlendMode(int mode);
extern void Emulator_CounterLoop();
extern void Emulator_GenerateVertexArrayQuad(Vertex* vertex, short* p0, short* p1, short* p2, short* p3, short w, short h);
extern void Emulator_GenerateTexcoordArrayQuad(Vertex* vertex, unsigned char* uv0, unsigned char* uv1, unsigned char* uv2, unsigned char* uv3, short w, short h);
extern void Emulator_GenerateColourArrayQuad(Vertex* vertex, unsigned char* col0, unsigned char* col1, unsigned char* col2, unsigned char* col3, bool bMultiplyColour);
extern void Emulator_AllocateVirtualMemory(unsigned int baseAddress, unsigned int size);
extern int Emulator_InitialiseGameVariables();
extern void Emulator_Ortho2D(float left, float right, float bottom, float top, float znear, float zfar);
extern void Emulator_BindTexture(GLuint textureId);

#endif

