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
#include "SETUP.H"
#include "DEBUG.H"
#include "INPUT.H"

WINAPP	 App;
bool thread_started;
HANDLE hThread;

void WinProcMsg()
{
	Log(LT_Enter, "WinProcMsg");

	MSG Msg;
	
	do
	{
		GetMessageA(&Msg, nullptr, 0, 0);

		if (!TranslateAcceleratorA(App.WindowHandle, App.hAccTable, &Msg))
		{
			TranslateMessage(&Msg);
			DispatchMessageA(&Msg);
		}
	} while (!thread_started && Msg.message != WM_QUIT);
}

void WinClose()
{
	Log(LT_Enter, "WinClose");

	SaveSettings();
	CloseHandle(App.hObject);
	//
	DestroyAcceleratorTable(App.hAccTable);
	CloseDirectX();

	DX_TRY(App.lpDIKeyboard->Unacquire());
	DXRelease(App.lpDIKeyboard, "Keyboard");

	DX_TRY(App.lpDIJoystick->Unacquire());
	DXRelease(App.lpDIJoystick, "Joystick");

	DXRelease(App.lpDI, "DirectInput");
}

bool WinRunCheck(LPCSTR lpName, LPCSTR lpClassName, HANDLE* mutex)
{
	Log(LT_Enter, "WinRunCheck");

	*mutex = CreateMutexA(0, true, lpName);

	if (GetLastError() != 183)
		return false;

	HWND wnd = FindWindowA(lpClassName, lpName);

	if (wnd)
		SendMessageA(wnd, WM_ACTIVATE, 0, 0);

	return true;
}

void WinProcessCommandLine(LPSTR lpCmdLine)
{
	Log(LT_Enter, "WinProcessCommandLine");

	Unimpl();
}

int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	int RetVal;
	int n;

	appsettings.OpenSetup = false;

	// Clear Application Structure
	memset(&App, 0, sizeof(WINAPP));

	DB_InitLog(1);

	HWND dblog = FindWindowA("DBLogWindowClass", "DBLog Server");
	if (dblog)
		PostMessageA(dblog, dbm_command, 2, 0);

	dblog = FindWindowA("DBLogWindowClass", "DBLog Server");
	if (dblog)
		PostMessageA(dblog, dbm_clearlog, 0, 0);

	DB_DefType("Error", 0xFF, 1);
	DB_DefType("Function", 0x8000, 0);
	DB_DefType("DirectX Information", 0x802040, 1);
	DB_DefType("Object Release", 0x80, 0);
	DB_DefType("General Information", 0x800000, 1);
	DB_DefType("Windows Message", 0x800080, 0);
	DB_DefType("Level Info", 0x8000FF, 0);
	DB_DefType("Sound", 0x8080, 0);

	Log(LT_Info, "Launching - %s", WINDOWNAME);
	Log(LT_Enter, "WinMain");

	if (WinRunCheck(WINDOWNAME, WINDOWCLASS, &App.hObject))
		return false;

	FindCdDrive();
	LoadGameflow();
	WinProcessCommandLine(lpCmdLine);

	App.hInstance = hInstance;
	App.WindowClass.hIcon = nullptr;
	App.WindowClass.lpszMenuName = nullptr;
	App.WindowClass.lpszClassName = WINDOWCLASS;
	App.WindowClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	App.WindowClass.hInstance = hInstance;
	App.WindowClass.style = CS_VREDRAW | CS_HREDRAW;
	App.WindowClass.lpfnWndProc = WinAppProc;
	App.WindowClass.cbClsExtra = 0;
	App.WindowClass.cbWndExtra = 0;
	App.WindowClass.hCursor = LoadCursor(App.hInstance, IDC_ARROW);

	if (!RegisterClass(&App.WindowClass))
	{
		Log(LT_Error, "Unable To Register Window Class");
		return false;
	}

	RECT Rect;

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

	if (appsettings.OpenSetup || !LoadSettings())
	{
		if (!InitSetupDialog())
		{
			free(gfScriptFile);
			free(gfStringOffset);
			WinClose();
			return 0;
		}

		LoadSettings();
	}

	SetWindowPos(App.WindowHandle, 0, App.GnWindowRect.left, App.GnWindowRect.top, 0, 0, SWP_NOSIZE | SWP_NOMOVE);

	HWND dWnd = GetDesktopWindow();
	HDC context = GetDC(dWnd);
	App.OriginalBPP = GetDeviceCaps(context, BITSPIXEL);
	ReleaseDC(dWnd, context);

	App.bNoFocus = false;
	App.isInScene = false;
	App.byte_D9AC2B = false;

	if (!DXCreate(
		CUR_DM.w,
		CUR_DM.h,
		CUR_DM.bpp,
		App.orig_flags,
		&App,
		App.WindowHandle,
		WS_CAPTION))
	{
		MessageBoxA(nullptr, &gfStringWad[gfStringOffset[STR_FAILED_TO_SETUP_DIRECTX]], "Tomb Raider", 0);
		return false;
	}

	ShowBumpInfo();

	UpdateWindow(App.WindowHandle);
	ShowWindow(App.WindowHandle, nCmdShow);

	if (App.Flags & WA_FULLSCREEN)
	{
		SetCursor(nullptr);
		ShowCursor(false);
	}

	DXCreateDirectInput(App.WindowHandle, hInstance);

	App.hAccTable = LoadAcceleratorsA(hInstance, (LPCSTR)0x65);

	// sound

	game_running = true;
	thread_started = false;

	uint32_t thread_id;
	hThread = (HANDLE)_beginthreadex(nullptr, 0, GameMain, nullptr, 0, &thread_id);

	WinProcMsg();

	thread_started = true;

	while (game_running);

	WinClose();

	HWND desktop = GetDesktopWindow();
	ReleaseDC(desktop, GetDC(desktop));

	DEVMODEA dm;
	dm.dmSize = sizeof(dm);
	dm.dmBitsPerPel = App.OriginalBPP;
	dm.dmFields = DM_BITSPERPEL;
	ChangeDisplaySettingsA(&dm, 0);

	dblog = FindWindowA("DBLogWindowClass", "DBLog Server");
	if (dblog)
		PostMessageA(dblog, dbm_command, 4, 0);

	
	return 0;
}

void HandleCommand(WORD param)
{
	Unimpl();
}

void HandleApp(LPARAM lParam, WPARAM wParam)
{
	Unimpl();
}

HMODULE GetKernel32()
{
	return GetModuleHandleA("kernel32.dll");
}

void* FindSleepAddress(HMODULE kernel)
{
	return GetProcAddress(kernel, "Sleep");
}

void* GetSleepFunc()
{
	return FindSleepAddress(GetKernel32());
}

void Sleep1ms()
{
	((void (__stdcall*)(DWORD))GetSleepFunc())(1);
}

void WaitUntilFalse(DWORD* ptr)
{
	do
	{
		Sleep1ms();
	} while (*ptr);
}

void WaitUntilTrue(DWORD* ptr)
{
	do
	{
		Sleep1ms();
	} while (!*ptr);
}

/*
Function : AppWinProc
Useage   : Application Window Procedure
*/

long FAR PASCAL WinAppProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:
		Log(LT_WindowMessage, "WM_CLOSE");
		// TODO TODO TODO TODO TODO
		PostQuitMessage(EXIT_SUCCESS);
		break;

	case WM_CREATE:
		// todo todo todo
		Log(LT_WindowMessage, "WM_CREATE");
		break;

	case WM_MOVE:
		Log(LT_WindowMessage, "WM_MOVE");
		DXMove(SLOWORD(lParam), SHIWORD(lParam));
		break;

	case WM_COMMAND:
		Log(LT_WindowMessage, "WM_COMMAND");
		HandleCommand((WORD)wParam);
		break;

	case WM_MOUSEMOVE:
		//Log(LT_WindowMessage, "WM_MOUSEMOVE");
		mouse_x = GET_X_LPARAM(lParam);
		mouse_y = GET_Y_LPARAM(lParam);
		mouse_vkeys = (int)wParam;
		break;

	case WM_APP:
		HandleApp(lParam, wParam);
		return 0;

	/*case WM_CHAR:
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
		break;*/


	case WM_ACTIVATE:
		Log(LT_WindowMessage, "WM_ACTIVATE");

		if (!false) // todo
		{
			if (!App.byte_D9AC2B)
			{
				switch (LOWORD(wParam))
				{
				case WA_ACTIVE:
				case WA_CLICKACTIVE:
					Log(LT_WindowMessage, "WM_ACTIVE");

					if (App.byte_D9AC19)
					{
						AcquireInput(true);
						ResumeThread(hThread);

						App.bNoFocus = false;

						Log(LT_Info, "Game Thread Resumed");
					}
					break;

				case WA_INACTIVE:
					Log(LT_WindowMessage, "WM_INACTIVE");

					if (App.byte_D9AC19)
					{
						AcquireInput(false);

						Log(LT_Info, "HangGameThread");

						if (App.isInScene)
							WaitUntilFalse(&App.isInScene);

						App.bNoFocus = true;

						if (!App.isInScene)
							WaitUntilTrue(&App.isInScene);

						SuspendThread(hThread);

						Log(LT_Info, "Game Thread Suspended");
					}
					break;
				}
			}

			return 0;
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