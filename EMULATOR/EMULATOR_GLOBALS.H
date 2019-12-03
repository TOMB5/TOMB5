#ifndef EMULATOR_GLOBALS_H
#define EMULATOR_GLOBALS_H

#include "EMULAOR_PLATFORM_SETUP.H"

#ifndef TRUE
#define TRUE		1
#endif
#ifndef FALSE
#define FALSE		0
#endif
#ifndef NULL
#define NULL		0
#endif

#ifdef _MSC_VER
#define FUNCNAME __FUNCTION__
#else
#define FUNCNAME __func__
#endif

extern int(*printf_)(const char * format, ...);

#define eprintf(fmt, ...) printf_("[EMU] " fmt, ##__VA_ARGS__)
#define eprinterr(fmt, ...) eprintf("[%s] - " fmt, FUNCNAME, ##__VA_ARGS__);

#if defined(__EMSCRIPTEN__)
#define UNIMPLEMENTED() eprinterr("Unimplemented!\n");
#else
#define UNIMPLEMENTED() eprinterr("Unimplemented!\n");
#endif

extern GLuint nullWhiteTexture;
extern GLuint vramFrameBuffer;
extern int screenWidth;
extern int screenHeight;
extern int windowWidth;
extern int windowHeight;
extern uint32_t DMAControlRegister;
extern int assetsLoaded;
#if defined(OGLES) || defined(OGL)
extern GLuint g_defaultShaderProgram;
#endif
extern GLint g_defaultFBO;


struct CachedTexture
{
	GLuint textureID;
	unsigned short tpage;
	unsigned short clut;
	unsigned int lastAccess;
};

#define MAX_NUM_CACHED_TEXTURES (512)

extern struct CachedTexture cachedTextures[MAX_NUM_CACHED_TEXTURES];

#endif