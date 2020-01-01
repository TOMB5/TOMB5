#ifndef EMULATOR_GLOBALS_H
#define EMULATOR_GLOBALS_H


#include <SDL_gamecontroller.h>

extern unsigned int nullWhiteTexture;
extern unsigned int vramFrameBuffer;
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
	unsigned int textureID;
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