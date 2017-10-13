#ifndef GPU_H
#define GPU_H
#include "PCINPUT.H"
#include <d3d.h>
#include <dsound.h>
#include "SPECIFIC.H"
#pragma pack(push, 1)
dispmode
{
	DWORD width; // pos 0 s 4
	DWORD height; // pos 4 s 4
	DWORD depth; // pos 8 s 4
	DWORD mipMapCount; // pos 12 s 4
	DWORD isIndexed8; // pos 16 s 4
	DDSURFACEDESC2 surfaceDesc; // pos 20 s 124
	BYTE bitsR; // pos 144 s 1
	BYTE bitsG; // pos 145 s 1
	BYTE bitsB; // pos 146 s 1
	BYTE offsetR; // pos 147 s 1
	BYTE offsetG; // pos 148 s 1
	BYTE offsetB; // pos 149 s 1
};

acceltexformatinfo
{
	DDPIXELFORMAT format; // pos 0 s 32
	DWORD depth; // pos 32 s 4
	DWORD field1; // pos 36 s 4
	DWORD field2; // pos 40 s 4
	BYTE bitsR; // pos 44 s 1
	BYTE bitsG; // pos 45 s 1
	BYTE bitsB; // pos 46 s 1
	BYTE bitsA; // pos 47 s 1
	BYTE offsetR; // pos 48 s 1
	BYTE offsetG; // pos 49 s 1
	BYTE offsetB; // pos 50 s 1
	BYTE offsetA; // pos 51 s 1
};

zBufFormat
{
	DDPIXELFORMAT pixFormat; // pos 0 s 32
	DWORD depth; // pos 32 s 4
};

acceladapt
{
	char name[30]; // pos 0 s 30
	char description[80]; // pos 30 s 80
	GUID* field1; // pos 110 s 4
	GUID guid; // pos 114 s 16
	D3DDEVICEDESC deviceDesc; // pos 130 s 252
	DWORD field2; // pos 382 s 4
	DWORD numDispModes; // pos 386 s 4
	dispmode* displayModes; // pos 390 s 4
	DWORD numTexFormats; // pos 394 s 4
	acceltexformatinfo* texFormats; // pos 398 s 4
	DWORD numZbufFormats; // pos 402 s 4
	zBufFormat* zBufFormats; // pos 406 s 4
};

gfxadapt
{
	char driverName[30]; // pos 0 s 30
	char driverDesc[80]; // pos 30 s 80
	GUID* field3; // pos 110 s 4
	GUID guid; // pos 114 s 16
	DDCAPS capabilities; // pos 130 s 380
	char driverDllName[512]; // pos 510 s 512
	char deviceName[512]; // pos 1022 s 4
	WORD versionRevision; // pos 1534 s 2
	WORD versionBuild; // pos 1536 s 2
	WORD versionMinor; // pos 1538 s 2
	WORD versionMajor; // pos 1540 s 2
	char pad4[32]; // pos 1542 s 32
	DWORD numDispModes; // pos 1574 s 4
	dispmode* displayModes; // pos 1578 s 4
	DWORD numAccelAdapters; // pos 1582 s 4
	acceladapt* accelAdapters; // pos 1586 s 4
};

soundcard
{
	char name[30]; // pos 0 s 30
	char description[80]; // pos 30 s 80
	GUID* field1; // pos 110 s 4
	GUID guid; // pos 114 s 16
};
#pragma pop

dxcontext_s
{
	DWORD numGraphicsAdapters; // pos 0 s 4  D9AB68
	DWORD numSoundCards; // pos 4 s 4
	gfxadapt* graphicsAdapters; // pos 8 s 4
	soundcard* soundCards; // pos 12 s 4
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
	HWND dxWndHwnd; // pos 100 s 4
	DWORD isInScene; // pos 104 s 4
	DWORD dword_D9ABFD; // pos 108 s 4

	DWORD dword_D9AC01;
	HANDLE hObject; // D9AC05

	DWORD dword_D9AC09;
	DWORD dword_D9AC0D;
	DWORD dword_D9AC11;

	HACCEL hAccTable;
	uint8 byte_D9AC19;
	BYTE opt_BumpMap;
	DWORD dword_D9AC1B;
	DWORD dword_D9AC1F;
	uint8 byte_D9AC23;
	BYTE opt_Filter;
	BYTE opt_Volumetric;
	BYTE opt_DisableSound;
	DWORD dword_D9AC27;
	BYTE byte_D9AC2B;
	DWORD dword_D9AC2C;
	DWORD opt_AutoTarget;
	DWORD dword_D9AC34;
	DWORD dword_D9AC38;
} dxctx;
dxcontext_s* ptr_ctx;
LPDIRECT3DVERTEXBUFFER vertexBuffer;
DWORD opt_GraphicsAdapter;
DWORD opt_AccelAdapter;
LPDIRECT3D3 iface_D3D3;
LPDIRECTDRAW4 iface_DirectDraw;
extern signed int __cdecl DXInitialise(void *lpContext, HWND hwnd);
extern int sub_401424();
extern int DXChangeVideoMode();
extern int DXMove(int xLeft, int yTop);
extern signed int __cdecl DXCreate(int a1, int a2, int a3, int flags, dxcontext_s *a5, HWND a6, DWORD dwStyle);
extern signed int __cdecl DXCreateSurface(LPDIRECTDRAW4 a1, LPDDSURFACEDESC2 a2, LPDIRECTDRAWSURFACE4* a3);
#endif