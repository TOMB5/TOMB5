#ifndef GPU_H
#define GPU_H
#include "PCINPUT.H"
#include <d3d.h>
#include <dsound.h>
#include "SPECIFIC.H"
#include <stdbool.h>
#pragma pack(push, 1)
struct DISPLAYMODE
{
	int				w;				// Width
	int				h;				// Height
	unsigned long	bpp;			// Bits Per Pixel
	DWORD mipMapCount; // pos 12 s 4
	bool			bPalette;		// Is It Palettised
	DDSURFACEDESC2	ddsd;			// Surface Description
	unsigned char	rbpp;			// Red Bits Per Pixel
	unsigned char	gbpp;			// Green Bits Per Pixel
	unsigned char	bbpp;			// Blue Bits Per Pixel
	unsigned char	rshift;			// Shifts For Red 
	unsigned char	gshift;			// Shifts For Green
	unsigned char	bshift;			// Shifts For Blue
};

struct D3DTEXTUREINFO
{
	DDPIXELFORMAT	ddpf;			// Texture Pixel Format
	unsigned long	bpp;			// Bits Per Pixel (if Palettised)
	bool			bPalette;		// Is it Palettised
	bool			bAlpha;			// Does It Support Alpha
	unsigned char	rbpp;			// Red Bits Per Pixel 
	unsigned char	gbpp;			// Green Bits Per Pixel
	unsigned char	bbpp;			// Blue Bits Per Pixel
	unsigned char	abpp;			// Alpha Bits Per Pixel
	unsigned char	rshift;			// Shifts For Red
	unsigned char	gshift;			// Shifts For Green
	unsigned char	bshift;			// Shifts For Blue
	unsigned char	ashift;			// Shifts For Alpha
};

struct zBufFormat
{
	DDPIXELFORMAT pixFormat; // pos 0 s 32
	DWORD depth; // pos 32 s 4
};

struct DIRECT3DINFO
{
	char			Name[30];		// Name String
	char			About[80];		// Description String
	LPGUID			lpGuid;			// GUID
	GUID			Guid;
	D3DDEVICEDESC	DeviceDesc;		// Device Description
	bool			bHardware;		// Is It Hardware
	int				nDisplayMode;	// Number Of Display Modes
	struct DISPLAYMODE*	DisplayMode;	// Ptr To Compatible Display Modes
	int				nTexture;		// Number Of Texture Formats
	struct D3DTEXTUREINFO*	Texture;		// Texture Info
	DWORD nZbuffer; // pos 402 s 4
	struct zBufFormat* zBufFormats; // pos 406 s 4
};

struct DIRECTDRAWINFO
{
	char			Name[30];		// Name String   
	char			About[80];		// Description String
	LPGUID			lpGuid;			// GUID
	GUID			Guid;
	DDCAPS			DDCaps;			// Device Capabilites
	char driverDllName[512]; // pos 510 s 512
	char deviceName[512]; // pos 1022 s 4
	WORD versionRevision; // pos 1534 s 2
	WORD versionBuild; // pos 1536 s 2
	WORD versionMinor; // pos 1538 s 2
	WORD versionMajor; // pos 1540 s 2
	char pad4[32]; // pos 1542 s 32
	int				nDisplayMode;	// Number Of Display Modes	
	struct DISPLAYMODE*	DisplayMode;	// Ptr To Display Mode Structure
	int				nD3DInfo;		// Number Of D3D Drivers
	struct DIRECT3DINFO*	D3DInfo;		// Ptr To D3D Info Structure
};

struct soundcard
{
	char name[30]; // pos 0 s 30
	char description[80]; // pos 30 s 80
	GUID* field1; // pos 110 s 4
	GUID guid; // pos 114 s 16
};
#pragma pop

struct WINAPP
{
	DWORD numGraphicsAdapters; // pos 0 s 4  D9AB68
	DWORD numSoundCards; // pos 4 s 4
	struct DIRECTDRAWINFO* graphicsAdapters; // pos 8 s 4
	struct soundcard* soundCards; // pos 12 s 4
	DWORD curGfxAdapt; // pos 16 s 4
	DWORD curAccelAdapt; // pos 20 s 4
	DWORD curDispMode; // pos 24 s 4
	DWORD curTexFormat; // pos 28 s 4
	DWORD field2; // pos 32 s 4
	DWORD curSoundCard; // pos 36 s 4

	BYTE fieldspacer;

	LPDIRECTDRAW4 ddraw; // pos 0 s 4  D9AB91
	LPDIRECT3D3 d3d; // pos 4 s 4
	LPDIRECT3DDEVICE3 d3d_dev; // pos 8 s 4
	LPDIRECT3DDEVICE3 d3d_dev_bis; // pos 12 s 4

	LPDIRECTDRAWSURFACE4 buf_primary; // pos 16 s 4
	LPDIRECTDRAWSURFACE4 buf_back; // pos 20 s 4
	LPDIRECTDRAWSURFACE4 buf_z; // pos 24 s 4
	LPDIRECT3DVIEWPORT3 viewport; // pos 28 s 4

	LPDIRECTSOUND dsound; // pos 32 s 4
	DWORD width; // pos 36 s 4
	DWORD height; // pos 40 s 4

	RECT stru_D9ABBD; // pos 44 s 16

	RECT windowPos; // pos 60 s 16

	DWORD flags; // pos 76 s 4

	DWORD dxWndStyle; // pos 80 s 4
	DWORD dword_D9ABE5; // pos 84 s 4
	LPDIRECTINPUT7A dinput; // pos 88 s 4
	LPDIRECTINPUTDEVICE2A dinput_keyboard; // pos 92 s 4

	LPDIRECTINPUTDEVICE2A dinput_other; // pos 96 s 4
	HWND GhWnd; // pos 100 s 4
	DWORD isInScene; // pos 104 s 4
	DWORD dword_D9ABFD; // pos 108 s 4

	DWORD sceneDone;
	HANDLE hObject; // D9AC05

	DWORD dword_D9AC09;
	DWORD dword_D9AC0D;
	DWORD dword_D9AC11;

	HACCEL hAccTable;
	uint8 byte_D9AC19;
	BYTE tEnableBumpMap;
	DWORD textRes;
	DWORD bumpRes;
	uint8 byte_D9AC23;
	BYTE opt_Filter;
	BYTE opt_Volumetric;
	BYTE opt_DisableSound;
	DWORD orig_flags;
	BYTE byte_D9AC2B;
	DWORD OriginalBPP;
	DWORD opt_AutoTarget;
	DWORD dword_D9AC34;
	DWORD dword_D9AC38;
} dxctx;
struct WINAPP* ptr_ctx;
LPDIRECT3DVERTEXBUFFER vertexBuffer;
DWORD opt_GraphicsAdapter;
DWORD opt_AccelAdapter;
LPDIRECT3D3 iface_D3D3;
LPDIRECTDRAW4 iface_DirectDraw;
extern signed int __cdecl DXInitialise(void *lpContext, HWND hwnd);
extern int sub_401424();
extern int DXChangeVideoMode();
extern int DXMove(int xLeft, int yTop);
extern signed int __cdecl DXCreate(int a1, int a2, int a3, int flags, struct WINAPP *a5, HWND a6, DWORD dwStyle);
extern bool	DXCreateSurface(LPDIRECTDRAW2 lpDD2, DDSURFACEDESC* ddsd, LPDIRECTDRAWSURFACE3* lpSurface);
extern int __cdecl sub_4B8780(LPDIRECTDRAWSURFACE4 a3, HGDIOBJ h, int xSrc, int ySrc, int wSrc, int hSrc);
extern signed int __cdecl LoadBitmapEx(struct IDirectDrawSurface4 *surface, const CHAR *name);
extern int __cdecl DDCopyBitmap(LPDIRECTDRAWSURFACE4 surface, char *filename);

#endif