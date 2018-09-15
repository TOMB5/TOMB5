#ifndef INCLUDE_H
#define INCLUDE_H

#include "STANDARD.H"

#include <stdbool.h>
#include <windows.h>
#include <mmsystem.h>
#include <ddraw.h>
#include <d3d.h>
#include <dinput.h>
#include <dsound.h>
#include <windowsx.h>
#include <time.h>
#include "SPECIFIC.H"
#include <stdio.h>


#if !defined(__cplusplus)
//#error Dude insists on C++ !!!
#endif

#define global extern
#define local static
#define defglobal

typedef void* Handle;

enum
{
	LOG_OUTPUT,
	LOG_RESET,
	LOG_END
};

#define LOG_DO_STRLEN 0xffffffff

//#define Log2(type, fmt, ...) Log_real("[DBLOG] [%s] %s", STRINGIFY(type), )

//#define Log(type, fmt, ...) S_Warn("[DBLOG] [" STRINGIFY(type) "] " fmt, __VA_ARGS__)
#define Log(type, fmt, ...) Log_real(type, #type, fmt, __VA_ARGS__)

#define ArraySize(a) (sizeof(a)/sizeof((a)[0]))
#define Zero(thing) memset(&(thing),0,sizeof(thing))
#define ZeroArray(a) memset((a),0,sizeof(a))
#define EndOfArray(a) ((a)+ArraySize(a))
#define InitDXStruct(s) memset(&(s),0,sizeof(s)),(s).dwSize=sizeof(s)
#define DefLocalString(x,y) local char Lsz##x[]=y
#define LocalString(x) Lsz##x
#define DefValueName(x) local char Lsz##x[]=#x
#define ValueName(x) Lsz##x
#define Align(x,b) (x)=(x)&~((b)-1)

void DebugPrint(const char* message);
void Log_backend(char type, char* fmt, ...);
inline void Log_real(char ctype, char* type, char* fmt, ...)
{
	char buf[128], pbuf[1024];
	char tbuf[15];
	memset(tbuf, ' ', 14);
	tbuf[14] = 0;
	strcpy(tbuf, type + 3);
	ZeroArray(buf);
	ZeroArray(pbuf);
	strcpy(buf, "[DBLOG] [");
	strcat(buf, tbuf);
	strcat(buf, "] ");

	va_list args;
	va_start(args, fmt);
	vsprintf(pbuf, fmt, args);
	va_end(args);

	char res[1152];
	ZeroArray(res);
	strcat(res, buf);
	strcat(res, pbuf);

	DebugPrint(res);
	Log_backend(ctype, pbuf);
}







/*** dxerror.cpp ***/
char* ERR_Describe_DX(HRESULT hr);
char* ERR_Describe_Init(int nError);

enum InitResult	// possible initialisation results
{
	INIT_OK,

	INIT_ERR_PreferredAdapterNotFound,
	INIT_ERR_CantCreateWindow,
	INIT_ERR_CantCreateDirectDraw,
	INIT_ERR_CantInitRenderer,
	INIT_ERR_CantCreateDirectInput,
	INIT_ERR_CantCreateKeyboardDevice,
	INIT_ERR_CantSetKBCooperativeLevel,
	INIT_ERR_CantSetKBDataFormat,
	INIT_ERR_CantAcquireKeyboard,
	INIT_ERR_CantSetDSCooperativeLevel,

	INIT_ERR_DD_SetExclusiveMode,
	INIT_ERR_DD_ClearExclusiveMode,
	INIT_ERR_SetDisplayMode,
	INIT_ERR_CreateScreenBuffers,
	INIT_ERR_GetBackBuffer,
	INIT_ERR_CreatePalette,
	INIT_ERR_SetPalette,
	INIT_ERR_CreatePrimarySurface,
	INIT_ERR_CreateBackBuffer,
	INIT_ERR_CreateClipper,
	INIT_ERR_SetClipperHWnd,
	INIT_ERR_SetClipper,
	INIT_ERR_CreateZBuffer,
	INIT_ERR_AttachZBuffer,
	INIT_ERR_CreateRenderBuffer,
	INIT_ERR_CreatePictureBuffer,
	INIT_ERR_D3D_Create,
	INIT_ERR_CreateDevice,
	INIT_ERR_CreateViewport,
	INIT_ERR_AddViewport,
	INIT_ERR_SetViewport2,
	INIT_ERR_SetCurrentViewport,

	INIT_ERR_ClearRenderBuffer,
	INIT_ERR_UpdateRenderInfo,
	INIT_ERR_GetThirdBuffer,

	INIT_ERR_GoFullScreen,
	INIT_ERR_GoWindowed,

	INIT_ERR_WrongBitDepth,
	INIT_ERR_GetPixelFormat,
	INIT_ERR_GetDisplayMode
};
typedef void* Position;	// iterator for linked lists etc
/*** settings.cpp ***/
struct AppSettings
{
	Position DisplayAdapter;			// G_DisplayAdapterList[DisplayAdapter] is the one we're using...
	Position SoundAdapter;				// same for sound card
	Position Joystick;					// and joystick
	Position FullScreenMode;			// hardware fullscreen mode x/y/bpp
	int nRenderMode;					// none/internal/HAL/RGB
	int nWindowWidth, nWindowHeight;		// size of desktop window
	int nAspectMode;					// 4:3 / 16:9 / any
	bool tPerspectiveCorrect;			// perspective correct textures
	bool tDither;						// dithering on/off
	bool tZBuffer;						// render using z buffer
	bool tBilinearFiltering;			// use bilinear filtering when texture mapping
	bool tTripleBuffering;				// use three buffers instead of two, for better performance but more memory usage
										//	bool tMipMap;						// use mipmapped textures
										//	bool tAntialias;					// antialias edges
	bool tFullScreen;					// switch to full screen or run in window
	bool tSoundEnabled;					// false = disable sound
	bool tLaraMic;						// position mic at lara instead of camera (for paul & toby)
	bool tJoystickEnabled;				// false = disable joystick
	bool tDisable16BitTextures;			// true = disable 16 bit textures (for 2MB Mystique etc)
	bool tDontSortPrimitives;			// true = no need to sort primitives (for PowerVR)
	bool tFlipBroken;					// true = driver doesn't wait for flip to finish before rendering.  must do it myself...
	bool tDisableFMV;					// true = don't play any FMVs
	int nTexelAdjustMode;				// never / when filtering / always
	int nNearestAdjustment;				// non-filtered texel adjustment
	int nLinearAdjustment;				// bilinear filtered texel adjustment
};
enum
{
	RENDERER_NONE,
	RENDERER_INTERNAL,
	RENDERER_HAL,
	RENDERER_HOWMANY
};

enum
{
	TEXEL_NEVER,
	TEXEL_WHENFILTERING,
	TEXEL_ALWAYS,
	TEXEL_HOWMANY
};
global struct AppSettings G_AppSettings;

#define DXCB_FRONT 1
#define DXCB_BACK 2
#define DXCB_THIRD 4
#define DXCB_ZBUFFER 8
#define DXCB_RENDER 16
#define DXCB_PICTURE 32
#define DXCB_CLIENT 64
#define DXCB_CLRWINDOW 256

bool HWR_Init();
void HWR_InitVertexList();
bool HWR_IsVertexBufferFull();
void HWR_InitState();
void HWR_BeginScene();
void HWR_EndScene();
void HWR_DrawPolyList();
void HWR_LoadTexturePages(int nPages, char* pImage, uint8* pPalette);
void HWR_FreeTexturePages();
void HWR_RestoreTexturePages();
void HWR_ResetCurrentTexture();
void HWR_ResetColorKey();
void HWR_ResetZBuffer();
void HWR_SetCurrentTexture(DWORD dwHandle);
void HWR_EnableColorKey(bool tEnable);
void HWR_EnableZBuffer(bool tWrite, bool tCompare);
void HWR_GetAllTextureHandles();
extern "C" void __cdecl HWR_DrawRoomBucket(void*);

bool TIME_Init();

/*** misc ***/
inline bool DX_TRY(HRESULT hr)
{
	if (SUCCEEDED(hr))
		return false;
	Log(LT_Error, "ERROR : %s", ERR_Describe_DX(hr));
	return true;
}

inline bool DX_FAILED(HRESULT hr)
{
	return FAILED(hr);
}

#endif