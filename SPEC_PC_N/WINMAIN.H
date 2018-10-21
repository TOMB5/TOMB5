#ifndef _WINMAIN_H
#define _WINMAIN_H
#define _X86_
#include "DIRECTX.H"
//#include "crtdbg.h"

#define	WINDOWCLASS	"MainGameWindow"
#define WINDOWNAME	"Tomb Raider Chronicles"

int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
BOOL WinRegisterWindow(HINSTANCE hInstance);
HWND WinCreateWindow(HINSTANCE hInstance, int nCmdShow);
long FAR PASCAL WinAppProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);



struct	HWCONFIG
{
	bool	Perspective;
	bool	Dither;
	int		Filter;
	int		nShadeMode;
	int		nFillMode;
};


extern struct HWCONFIG HWConfig;








void ShowBumpInfo();
float WinFrameRate();
void WinDisplayString(int x, int y, char *String, ...);


#endif