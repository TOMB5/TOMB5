#ifndef EMULATOR_GLOBALS_H
#define EMULATOR_GLOBALS_H

#include <SDL.h>
#include <SDL_opengl.h>

extern GLuint vramTexture;
extern SDL_Renderer* g_renderer;
extern int lastTime;
extern int screenWidth;
extern int screenHeight;
extern int windowWidth;
extern int windowHeight;
extern uint32_t DMAControlRegister;

#endif