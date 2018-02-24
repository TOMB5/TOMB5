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

	LPDIRECTDRAW4			lpDD;				// DirectDraw2 Interface
	LPDIRECT3D2				lpD3D;				// Direct3D2 Interface
	LPDIRECT3DDEVICE2		lpD3DDevice;		// Direct 3D2 Device
	LPDIRECT3DDEVICE2		lpD3DDevice_BIS;	// Direct 3D2 Device

	LPDIRECTDRAWSURFACE3	lpFrontBuffer;		// Primary Surface
	LPDIRECTDRAWSURFACE3	lpBackBuffer;		// Back Buffer
	LPDIRECTDRAWSURFACE3	lpZBuffer;			// Z Buffer

	LPDIRECT3DVIEWPORT2		lpViewPort;

	LPDIRECTSOUND			lpDS;

	unsigned int width;
	unsigned int height;

	tagRECT					r1;
	int						GnWindowPosX;
	int						GnWindowPosY;
	int						GnWindowWidth;
	int						GnWindowHeight;

	unsigned int			Flags;
	unsigned int			DXWndStyle;
	unsigned int			Unk1;

	LPDIRECTINPUT7A			lpDI;
	LPDIRECTINPUTDEVICE2A	lpDIKeyboard;
	LPDIRECTINPUTDEVICE2A	lpDIJoystick;

	HWND					GhWnd; // pos 100 s 4
	DWORD isInScene; // pos 104 s 4
	DWORD					bNoFocus;				// Application Window Has Fous

	DWORD dword_D9AC01;
	HANDLE hObject; // D9AC05

	DWORD dword_D9AC09;
	DWORD dword_D9AC0D;
	DWORD dword_D9AC11;

	HACCEL hAccTable;
	uint8 byte_D9AC19;
	BYTE					tBumpMap;
	DWORD dword_D9AC1B;
	DWORD dword_D9AC1F;
	uint8 byte_D9AC23;
	BYTE					tBilinearFilter;
	BYTE					tVolumetricShadows;
	BYTE					tDisableSound;
	DWORD dword_D9AC27;
	BYTE byte_D9AC2B;
	DWORD dword_D9AC2C;
	
	BYTE					tAutoTarget;
	DWORD dword_D9AC34;
	DWORD dword_D9AC38;

	LPDIRECTDRAWPALETTE		Palette;				// Palette For SW Renderer
	PALETTEENTRY			PaletteEntries[256];	// Palette Entries

	
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