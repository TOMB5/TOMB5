#ifndef EMULATOR_H
#define EMULATOR_H

#define GL_GLEXT_PROTOTYPES 1
#define GLEW_STATIC 1
#include <gl\glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_opengl_glext.h>

extern void Emulator_Init(int screen_width, int screen_height);
extern void Emulator_BeginScene();
extern void Emulator_EndScene();
extern void Emulator_SaveVRAM(int width, int height);
extern void Emulator_SaveVRAM2(int width, int height);
extern void Emulator_ShutDown();

extern GLuint vramTexture;
extern SDL_Renderer* g_renderer;
extern int lastTime;

#endif

