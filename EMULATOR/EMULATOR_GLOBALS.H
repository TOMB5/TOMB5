#ifndef EMULATOR_GLOBALS_H
#define EMULATOR_GLOBALS_H

#if defined(SDL2)
#include <SDL_gamecontroller.h>
#endif
#include "EMULATOR.H"

#if defined(D3D9)
extern LPDIRECT3DVERTEXBUFFER9 g_vertexBufferObject;
#endif


extern TextureID        whiteTexture;
extern TextureID        vramTexture;

extern int windowWidth;
extern int windowHeight;
extern unsigned int DMAControlRegister;
extern int assetsLoaded;
extern int g_emulatorPaused;
extern int g_polygonSelected;

#if defined(SDL2)
extern unsigned short UpdateGameControllerInput(SDL_GameController* pad);
extern unsigned short UpdateKeyboardInput();
extern unsigned short UpdateKeyboardInputDebug();

extern SDL_GameController* padHandle[];
#endif

extern unsigned char* padData[];

#endif