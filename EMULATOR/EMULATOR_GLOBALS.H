#ifndef EMULATOR_GLOBALS_H
#define EMULATOR_GLOBALS_H

#include <SDL.h>
#include <SDL_opengl.h>
#include <stdint.h>

#ifdef _MSC_VER
#define FUNCNAME __FUNCTION__
#else
#define FUNCNAME __func__
#endif

extern int(*printf_)(const char * format, ...);

#define UNIMPLEMENTED() printf_("EMU - [%s] - Unimplemented!\n", FUNCNAME);

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