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

#include <stdint.h>

#if __APPLE__
#include <stddef.h>
#include <SDL2/SDL.H>
#else
#include <SDL.h>
#endif

#include <GL/glew.h>

#if __APPLE__
#include <SDL2/SDL_opengl.h>
#else
#include <SDL_opengl.h>
#endif

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

extern int lastTime;
extern int screenWidth;
extern int screenHeight;
extern int windowWidth;
extern int windowHeight;
extern uint32_t DMAControlRegister;

#endif