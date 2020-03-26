#ifndef EMULATOR_GLOBALS_H
#define EMULATOR_GLOBALS_H

#include <SDL_gamecontroller.h>
#include <EMULATOR.H>

#if defined(D3D9)
extern LPDIRECT3DVERTEXBUFFER9 g_vertexBufferObject;
#endif

#if defined(VK)

struct FrameBufferAttachment 
{
	VkImage image;
	VkDeviceMemory mem;
	VkImageView view;
};

struct FrameBuffer
{
	int32_t width, height;
	VkFramebuffer frameBuffer;
	FrameBufferAttachment color, depth;
	VkRenderPass renderPass;
	VkSampler sampler;
	VkDescriptorImageInfo descriptor;
};

extern struct FrameBuffer vramFrameBuffer;
extern unsigned int nullWhiteTexture;
#else
extern TextureID        nullWhiteTexture;
extern TextureID        vramTexture;
extern RenderTargetID   vramFrameBuffer;
#endif

extern int screenWidth;
extern int screenHeight;
extern int windowWidth;
extern int windowHeight;
extern uint32_t DMAControlRegister;
extern int assetsLoaded;
extern ShaderID g_gte_shader;
extern ShaderID g_blit_shader;

extern RenderTargetID g_defaultFBO;

struct CachedTexture
{
	TextureID texture;
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