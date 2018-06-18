#include "standard.h"
#include "global.h"
#include "template.h"
#include "directx.h"
#include "winmain.h"
//#include "console.h"
#include "crtdbg.h"
//#include "texture.h"
#include "drawprimitive.h"
#include "hwrender.h"
#include "utils.h"
#include "di.h"
#include "ds.h"
#include "time.h"
//#include "spanbuffer.h"
#include "hwinsert.h"
#include "picture.h"
#include "resource.h"
#include "FILE.H"
#include "GAMEFLOW.H"

WINAPP	 App;

int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	int RetVal;
	int n;

	// Clear Application Structure
	memset(&App, 0, sizeof(WINAPP));

	FindCdDrive();
	LoadGameflow();

	App.hInstance = hInstance;
	App.WindowClass.hIcon = NULL;
	App.WindowClass.lpszMenuName = NULL;
	App.WindowClass.lpszClassName = WINDOWCLASS;
	App.WindowClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	App.WindowClass.hInstance = hInstance;
	App.WindowClass.style = CS_VREDRAW | CS_HREDRAW;
	App.WindowClass.lpfnWndProc = (WNDPROC)WinAppProc;
	App.WindowClass.cbClsExtra = 0;
	App.WindowClass.cbWndExtra = 0;
	App.WindowClass.hCursor = LoadCursor(App.hInstance, IDC_ARROW);

	if (!RegisterClass(&App.WindowClass))
	{
		Log(LT_Error, "Unable To Register Window Class");
		return FALSE;
	}

	tagRECT Rect;

	Rect.left = 0;
	Rect.top = 0;
	Rect.right = 640;
	Rect.bottom = 480;

	AdjustWindowRect(&Rect, WS_CAPTION, false);

	App.WindowHandle = CreateWindowEx(
		WS_THICKFRAME,
		WINDOWCLASS,
		WINDOWNAME,
		WS_BORDER,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		Rect.right - Rect.left,
		Rect.bottom - Rect.top,
		nullptr,
		nullptr,
		App.hInstance,
		nullptr
	);

	if (!App.WindowHandle)
	{
		Log(LT_Error, "Unable To Create Window");
		return FALSE;
	}

	DXInitialise(&App.DeviceInfo, App.WindowHandle);

	SetWindowPos(App.WindowHandle, 0, App.GnWindowPosX, App.GnWindowPosY, 0, 0, SWP_NOSIZE | SWP_NOMOVE);

	HWND dWnd = GetDesktopWindow();
	HDC context = GetDC(dWnd);
	App.dword_D9AC2C = GetDeviceCaps(context, BITSPIXEL);
	ReleaseDC(dWnd, context);

	App.bNoFocus = 0;
	App.isInScene = 0;
	App.byte_D9AC2B = 0;

	auto dd = App.DeviceInfo.DDInfo[App.DeviceInfo.nDDInfo];
	auto d3d = dd.D3DInfo[dd.nD3DInfo];
	auto dm = d3d.DisplayMode;
	
	return 0;
}

/*
Function : AppWinProc
Useage   : Application Window Procedure
*/

long FAR PASCAL WinAppProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CREATE:
		ShowCursor(FALSE);
		break;

	case WM_DESTROY:
		//WinAppExit();
		PostQuitMessage(0);
		break;


	case WM_CHAR:
		//		KeyToConsole(wParam);
		break;


	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_F1:
			//			ToggleConsole();
			break;
		}
		break;

	case WM_KEYUP:
		break;


	case WM_ACTIVATE:
		switch (LOWORD(wParam))
		{
		case WA_ACTIVE:
		case WA_CLICKACTIVE:
			App.bNoFocus = FALSE;
			break;

		case WA_INACTIVE:
			App.bNoFocus = TRUE;
			break;
		}

	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}