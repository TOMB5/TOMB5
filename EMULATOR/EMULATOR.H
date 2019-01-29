#ifndef EMULATOR_H
#define EMULATOR_H

#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>

extern void Emulator_Init(int screen_width, int screen_height);
extern void Emulator_BeginScene();
extern void Emulator_EndScene();
extern void Emulator_SaveVRAM(int width, int height);
extern void Emulator_SaveVRAM2(int width, int height);
extern void Emulator_ShutDown();
extern void Emulator_SwapWindow();

extern GLuint vramTexture;
extern SDL_Renderer* g_renderer;
extern int lastTime;
extern int screenWidth;
extern int screenHeight;

#endif

