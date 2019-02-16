#ifndef EMULATOR_H
#define EMULATOR_H

#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <LIBGPU.H>

extern void Emulator_Init(char* windowName, int screen_width, int screen_height);
extern void Emulator_BeginScene();
extern void Emulator_EndScene();
extern void Emulator_SaveVRAM(int width, int height);
extern void Emulator_SaveVRAM2(int width, int height);
extern void Emulator_ShutDown();
extern void Emulator_SwapWindow();
extern void Emulator_GenerateAndBindTpage(unsigned int type, unsigned int tpageX, unsigned int tpageY, unsigned int clutX, unsigned int clutY);
extern void Emulator_DestroyLastVRAMTexture();
extern void Emulator_DestroyFrameBuffer(GLuint& fbo);
extern void Emulator_GenerateFrameBuffer(GLuint& fbo);
extern void Emulator_GenerateFrameBufferTexture();
extern void Emulator_DeleteFrameBufferTexture();
extern void Emulator_GenerateAndBindNullWhite();
extern void Emulator_CheckTextureIntersection(RECT16* rect);

#endif

