#ifndef EMULATOR_GLOBALS_H
#define EMULATOR_GLOBALS_H


#ifndef TRUE
#define TRUE		1
#endif
#ifndef FALSE
#define FALSE		0
#endif
#ifndef NULL
#define NULL		0
#endif

#ifdef __APPLE__
#include <stddef.h>
#endif

#include <stdint.h>
#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>

#ifdef _MSC_VER
#define FUNCNAME __FUNCTION__
#else
#define FUNCNAME __func__
#endif

extern int(*printf_)(const char * format, ...);

#define eprintf(fmt, ...) printf_("[EMU] " fmt, ##__VA_ARGS__)
#define eprinterr(fmt, ...) eprintf("[%s] - " fmt, FUNCNAME, ##__VA_ARGS__);

#define UNIMPLEMENTED() eprinterr("Unimplemented!\n");

extern GLuint vramTexture;
extern GLuint nullWhiteTexture;
extern SDL_Renderer* g_renderer;
extern int lastTime;
extern int screenWidth;
extern int screenHeight;
extern int windowWidth;
extern int windowHeight;
extern uint32_t DMAControlRegister;

#endif