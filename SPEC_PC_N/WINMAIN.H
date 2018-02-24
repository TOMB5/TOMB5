#ifndef _WINMAIN_H
#define _WINMAIN_H

#include "DIRECTX.H"
//#include "crtdbg.h"

#define	WINDOWCLASS	"MainGameWindow"
#define WINDOWNAME	"Tomb Raider Chronicles"

int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
BOOL WinRegisterWindow(HINSTANCE hInstance);
HWND WinCreateWindow(HINSTANCE hInstance, int nCmdShow);
long FAR PASCAL WinAppProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

#pragma pack(push, 1)
struct WINAPP
{
	HINSTANCE				hInstance;
	HWND					WindowHandle;
	WNDCLASS				WindowClass;

	DEVICEINFO				DeviceInfo;			// Device Information
	DXCONFIG				DXConfig;

	BYTE pad;

	LPDIRECTDRAW2			lpDD;				// DirectDraw2 Interface
	LPDIRECT3D2				lpD3D;				// Direct3D2 Interface
	LPDIRECT3DDEVICE2		lpD3DDevice;		// Direct 3D2 Device
	LPDIRECT3DDEVICE2		lpD3DDevice_BIS;	// Direct 3D2 Device

	LPDIRECTDRAWSURFACE3	lpFrontBuffer;		// Primary Surface
	LPDIRECTDRAWSURFACE3	lpBackBuffer;		// Back Buffer
	LPDIRECTDRAWSURFACE3	lpZBuffer;			// Z Buffer

	LPDIRECT3DVIEWPORT2		lpViewPort;

	LPDIRECTSOUND			lpDS;

	LPDIRECTDRAWPALETTE		Palette;				// Palette For SW Renderer
	PALETTEENTRY			PaletteEntries[256];	// Palette Entries

	bool					bFocus;				// Application Window Has Fous
	bool					bRender;			// Ok To Render

	int						nRenderMode;		// Hardware/Internal Renderer
	int						nUVAdd;

	bool					tJoystickEnabled;
	int						Joystick;

	float					fps;
};

#pragma pop

struct	HWCONFIG
{
	bool	Perspective;
	bool	Dither;
	int		Filter;
	int		nShadeMode;
	int		nFillMode;
};


extern struct HWCONFIG HWConfig;
extern struct WINAPP App;

typedef struct
{
	signed char	  shimmer;
	signed char   choppy;
	unsigned char random;
	unsigned char abs;
} WATERTAB;

extern WATERTAB	WaterTable[22][64];
extern "C" short rcossin_tbl[];

#endif