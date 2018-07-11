#define _X86_
#include "STANDARD.H"
#include "GLOBAL.H"
#include "TEMPLATE.H"
#include "DIRECTX.H"
#include "WINMAIN.H"
//#include "console.h"
#include "crtdbg.h"
//#include "texture.h"
#include "DRAWPRIMITIVE.H"
#include "HWRENDER.H"
#include "UTILS.H"
#include "DI.H"
#include "DS.H"
#include "time.h"
//#include "spanbuffer.h"
#include "HWINSERT.H"
#include "PICTURE.H"
#include "resource.h"
#include "FILE.H"
#include "GAMEFLOW.H"
#include "GAME.H"

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

	SetWindowPos(App.WindowHandle, 0, App.GnWindowRect.left, App.GnWindowRect.top, 0, 0, SWP_NOSIZE | SWP_NOMOVE);

	HWND dWnd = GetDesktopWindow();
	HDC context = GetDC(dWnd);
	App.dword_D9AC2C = GetDeviceCaps(context, BITSPIXEL);
	ReleaseDC(dWnd, context);

	App.bNoFocus = false;
	App.isInScene = false;
	App.byte_D9AC2B = false;

	if (!DXCreate(
		CUR_DM.w,
		CUR_DM.h,
		CUR_DM.bpp,
		App.dword_D9AC27,
		&App,
		App.WindowHandle,
		WS_CAPTION))
	{
		MessageBoxA(nullptr, &gfStringWad[gfStringOffset[STR_FAILED_TO_SETUP_DIRECTX]], "Tomb Raider", 0);
		return 0;
	}

	ShowBumpInfo();

	UpdateWindow(App.WindowHandle);
	ShowWindow(App.WindowHandle, nCmdShow);

	if (App.Flags & WA_FULLSCREEN)
	{
		SetCursor(nullptr);
		ShowCursor(false);
	}

	DICreate(App.WindowHandle, hInstance);

	App.hAccTable = LoadAcceleratorsA(hInstance, (LPCSTR)0x65);

	// sound

	uint32_t thread_id;
	HANDLE hThread = (HANDLE)_beginthreadex(nullptr, 0, GameMain, nullptr, 0, &thread_id);

	//WinProcMsg();
	
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






void ShowBumpInfo()
{
	if (CUR_D3D.DeviceDesc.dwTextureOpCaps & (D3DTEXOPCAPS_BUMPENVMAP | D3DTEXOPCAPS_BUMPENVMAPLUMINANCE))
	{
		if (CUR_D3D.DeviceDesc.wMaxTextureBlendStages >= 3)
		{
			//App.lpD3DDevice->EnumTextureFormats(nullptr, nullptr);

			if (false)
			{
				/*Log(LT_Info, "Bump bit count 0x%X", BumpBitCount);
				Log(LT_Info, "Bump DU %X", BumpDU);
				Log(LT_Info, "Bump DV %X", BumpDV);*/
			}
		}
	}
}

bool DICreate(HWND hWnd, HINSTANCE hInstance)
{
	return false;
}