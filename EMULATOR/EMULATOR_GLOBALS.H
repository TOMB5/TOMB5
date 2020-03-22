#ifndef EMULATOR_GLOBALS_H
#define EMULATOR_GLOBALS_H


#include <SDL_gamecontroller.h>


#if defined(D3D9)
extern IDirect3DTexture9* nullWhiteTexture;
extern IDirect3DTexture9* vramTexture;
extern IDirect3DSurface9* vramFrameBuffer;
#else
extern unsigned int nullWhiteTexture;
extern unsigned int vramFrameBuffer;
extern unsigned int vramTexture;
#endif
extern int screenWidth;
extern int screenHeight;
extern int windowWidth;
extern int windowHeight;
extern uint32_t DMAControlRegister;
extern int assetsLoaded;
extern unsigned int g_defaultShaderProgram;

extern int g_defaultFBO;


struct CachedTexture
{
#if defined(OGL) || defined(OGLES)
	unsigned int textureID;
#elif defined(D3D9)
	IDirect3DTexture9* texture;
#endif
	unsigned short tpage;
	unsigned short clut;
	unsigned int lastAccess;
};

#define MAX_NUM_CACHED_TEXTURES (512)

extern struct CachedTexture cachedTextures[MAX_NUM_CACHED_TEXTURES];

extern unsigned short UpdateGameControllerInput(SDL_GameController* pad);
extern unsigned short UpdateKeyboardInput();

extern SDL_GameController* padHandle[];
extern unsigned char* padData[];
extern const unsigned char* keyboardState;

#endif