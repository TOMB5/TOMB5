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

	// Create And Display Window
	App.WindowHandle = WinCreateWindow(hInstance, nCmdShow);
	if (!App.WindowHandle)
	{
		MessageBox(NULL, "Unable To Create Window", "", MB_OK);
		return FALSE;
	}

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
		WinAppExit();
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
			App.bFocus = TRUE;
			break;

		case WA_INACTIVE:
			App.bFocus = FALSE;
			break;
		}

	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}