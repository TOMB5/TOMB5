#include "WINMAIN.H"
#include "SPECIFIC.H"
#include <cstdio>
#include <io.h>
#include <fcntl.h>
#include <crtdbg.h>
#include "GAMEFLOW.H"
#include <process.h>
#include <mm3dnow.h>


HWND SendMsg(HWND hWnd, LPARAM lParam)
{
	S_Warn("[SendMsg] - Unimplemented!\n");
	return NULL;
}

int WinProcMsg()
{
	int result; // eax@4
	struct tagMSG Msg; // [sp+10h] [bp-1Ch]@2

	sub_4DEB10(2, "WinProcMsg");
	do
	{
		GetMessageA(&Msg, 0, 0, 0);
		if (!TranslateAcceleratorA(hWnd, hAccTable, &Msg))
		{
			TranslateMessage(&Msg);
			DispatchMessageA(&Msg);
		}
		result = dword_876C48;
	} while (!dword_876C48 && Msg.message != 18);
	return result;
}

/*char *WinProcessCommandLine(char *a1)
{
	int(__cdecl **v1)(int); // esi@1
	unsigned int v2; // esi@3
	int(__cdecl **v3)(int); // esi@7
	char *result; // eax@8
	const char *v5; // edx@8
	unsigned int v6; // eax@10
	unsigned int v7; // kr14_4@10
	const char *v8; // edx@14
	unsigned int v9; // eax@14
	unsigned int v10; // kr1C_4@14
	size_t v11; // eax@17
	unsigned int v12; // kr24_4@17
	char v13[4]; // [sp+Ch] [bp-14h]@8
	int v14; // [sp+10h] [bp-10h]@8
	int v15; // [sp+14h] [bp-Ch]@8
	int v16; // [sp+18h] [bp-8h]@8
	int v17; // [sp+1Ch] [bp-4h]@8

	sub_4DEB10(2, "WinProcessCommandLine");
	v1 = &off_51184D;
	do
	{
		(*v1)((int)a_init);
		v1 = (int(__cdecl **)(int))((char *)v1 + 45);
	} while ((signed int)v1 < (signed int)&unk_5118A7);
	v2 = 0;
	if (strlen(a1) != 0)
	{
		do
		{
			if (toupper(a1[v2]))
				a1[v2] = toupper(a1[v2]);
			++v2;
		} while (v2 < strlen(a1));
	}
	v3 = &off_51184D;
	do
	{
		*(_DWORD *)v13 = 0;
		v14 = 0;
		v15 = 0;
		v16 = 0;
		v17 = 0;
		result = strstr(a1, (const char *)v3 - 21);
		v5 = result;
		if (result)
		{
			if (*((_BYTE *)v3 - 1))
			{
				v6 = 0;
				v7 = strlen(v5) + 1;
				if (v7 != 1)
				{
					while (*v5 != 61)
					{
						++v6;
						++v5;
						if (v6 >= v7 - 1)
						{
							result = (char *)(*v3)(v13);
							goto LABEL_23;
						}
					}
					v8 = v5 + 1;
					v9 = 0;
					v10 = strlen(v8) + 1;
					if (v10 != 1)
					{
						do
						{
							if (*v8 != 32)
								break;
							++v9;
							++v8;
						} while (v9 < v10 - 1);
					}
					v11 = 0;
					v12 = strlen(v8) + 1;
					if (v12 != 1)
					{
						do
						{
							if (v8[v11] == 32)
								break;
							++v11;
						} while (v11 < v12 - 1);
					}
					strncpy(v13, v8, v11);
				}
				result = (char *)(*v3)(v13);
			}
			else
			{
				result = (char *)(*v3)(0);
			}
		}
	LABEL_23:
		v3 = (int(__cdecl **)(int))((char *)v3 + 45);
	} while ((signed int)v3 < (signed int)&unk_5118A7);
	return result;
}*/

char WinRunCheck(const CHAR *lpName, const CHAR *lpClassName, HANDLE *mutex)
{
	S_Warn("[WinRunCheck] - Unimplemented!\n");
	return 0;
}

HWND WinClose()
{
	S_Warn("[WinClose] - Unimplemented!\n");
	return NULL;
}

void InitConsole()
{
	AllocConsole();

	HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
	int hCrt = _open_osfhandle((long)handle_out, _O_TEXT);
	FILE* hf_out = _fdopen(hCrt, "w");
	setvbuf(hf_out, NULL, _IONBF, 1);
	*stdout = *hf_out;

	HANDLE handle_in = GetStdHandle(STD_INPUT_HANDLE);
	hCrt = _open_osfhandle((long)handle_in, _O_TEXT);
	FILE* hf_in = _fdopen(hCrt, "r");
	setvbuf(hf_in, NULL, _IONBF, 128);
	*stdin = *hf_in;
}

HANDLE sub_4DEA40(LPCSTR lpName)
{
	return OpenFileMappingA(6u, 1, lpName);
}

LPVOID sub_4DEA20(HANDLE hFileMappingObject)
{
	return MapViewOfFile(hFileMappingObject, 6u, 0, 0, 0x100000u);
}

int sub_4DEA50(char* a1, LPARAM lParam, int a3)
{
	HWND v3; // ebx@1
	char *v4; // edx@2
	int result; // eax@3

	v3 = FindWindowA(ClassName, WindowName);
	if (v3 && (dword_E4ACA4 = sub_4DEA40("DBLOGMAPMEM"), (v4 = (char *)sub_4DEA20(dword_E4ACA4)) != 0))
	{
		strcpy(v4, a1);
		result = SendMessageA(v3, dword_E4ACB0, (unsigned __int8)a3, lParam);
	}
	else
	{
		result = (int)a1;
	}
	return result;
}

signed int sub_4D22D0()
{
	signed int result; // eax@1
	int v6; // [sp+Ch] [bp-20h]@1
	CPPEH_RECORD ms_exc; // [sp+14h] [bp-18h]@1

	v6 = 1;
	_EAX = 1;
	__asm { cpuid }
	ms_exc.registration.TryLevel = -1;
	result = 1;
	if ((unsigned int)&unk_800000 & _EDX)
	{
		_m_femms();
		ms_exc.registration.TryLevel = -1;
	}
	else
	{
		result = 0;
	}
	return result;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	InitConsole();

	//S_Warn("[WinMain] - Unimplemented!\n");

	HWND v4; // eax@1
	HWND v5; // eax@3
	int v6; // eax@5
	HWND v8; // eax@8
	HWND v9; // esi@15
	HDC v10; // edi@15
	int v11; // ecx@15
	HWND v12; // eax@25
	HWND v13; // esi@25
	HDC v14; // eax@25
	HWND v15; // eax@25
	struct tagRECT Rect; // [sp+Ch] [bp-A4h]@8
	char v17; // [sp+1Ch] [bp-94h]@25
	__int16 v18; // [sp+40h] [bp-70h]@25
	int v19; // [sp+44h] [bp-6Ch]@25
	int v20; // [sp+84h] [bp-2Ch]@25

	byte_57A098 = 0;
	byte_D9AC23 = sub_4D22D0() != 0;
	byte_D9AC19 = 0;
	*(DWORD *)&dword_D9AC30 = 0;
	sub_4DEC40(1);
	v4 = FindWindowA(ClassName, WindowName);
	if (v4)
		PostMessageA(v4, Msg, 2u, 0);
	v5 = FindWindowA(ClassName, WindowName);
	if (v5)
		PostMessageA(v5, dword_E4ACAC, 0, 0);
	sub_4DEA50("Error", 255, 1);
	sub_4DEA50("Function", 0x8000, 0);
	sub_4DEA50("DirectX Information", (LPARAM)&unk_802040, 1);
	sub_4DEA50("Object Release", 128, 0);
	sub_4DEA50("General Information", (LPARAM)&unk_800000, 1);
	sub_4DEA50("Windows Message", (LPARAM)&unk_800080, 0);
	sub_4DEA50("Level Info", (LPARAM)&unk_8000FF, 0);
	sub_4DEA50("Sound", 32896, 0);
	sub_4DEB10(5, "Launching - %s", Name);
	sub_4DEB10(2, "WinMain");
	_CrtSetReportMode(0, 2);
	v6 = _CrtSetDbgFlag(-1);
	LOBYTE(v6) = v6 | 0x24;
	_CrtSetDbgFlag(v6);
	if (!(unsigned __int8)WinRunCheck(Name, "MainGameWindow", &hObject))
	{
		sub_402B49();
		LoadGameflow();
		WinProcessCommandLine(lpCmdLine);
		hinst = hInstance;
		WndClass.hIcon = 0;
		WndClass.lpszMenuName = 0;
		WndClass.lpszClassName = "MainGameWindow";
		WndClass.hbrBackground = (HBRUSH)GetStockObject(4);
		WndClass.hInstance = hInstance;
		WndClass.style = 3;
		WndClass.lpfnWndProc = (WNDPROC)sub_401E8D;
		WndClass.cbClsExtra = 0;
		WndClass.cbWndExtra = 0;
		WndClass.hCursor = LoadCursorA(hinst, (LPCSTR)0x68);
		if (!RegisterClassA(&WndClass))
		{
			sub_4DEB10(1, "Unable To Register Window Class");
			return 0;
		}
		Rect.left = 0;
		Rect.top = 0;
		Rect.right = 640;
		Rect.bottom = 480;
		AdjustWindowRect(&Rect, (DWORD)&unk_C00000, 0);
		v8 = CreateWindowExA(
			0x40000u,
			"MainGameWindow",
			Name,
			(DWORD)&unk_C00000,
			2147483648,
			2147483648,
			Rect.right - Rect.left,
			Rect.bottom - Rect.top,
			0,
			0,
			hInstance,
			0);
		hWnd = v8;
		if (!v8)
		{
			sub_4DEB10(1, "Unable To Create Window");
			return 0;
		}
		sub_4027F2(&dword_D9AB68, (int)v8);
		if (byte_57A098 || !(unsigned __int8)sub_402F77())
		{
			if (!(unsigned __int8)sub_402C34())
			{
				free(dword_E5C2EC);
				free(dword_E5C2AC);
				WinClose();
				return 0;
			}
			sub_402F77();
		}
		SetWindowPos(hWnd, 0, *(int *)&X, *(int *)&Y, 0, 0, 5u);
		v9 = GetDesktopWindow();
		v10 = GetDC(v9);
		dword_D9AC2C = GetDeviceCaps(v10, 12);
		ReleaseDC(v9, v10);
		dword_D9ABFD = 0;
		dword_D9ABF9 = 0;
		byte_D9AC2B = 0;
		v11 = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(dword_86B9AC + 8) + 1590 * *(_DWORD *)(dword_86B9AC + 16) + 1586)
			+ 410 * *(_DWORD *)(dword_86B9AC + 20)
			+ 390);
		if (!sub_402B2B(
			*(_DWORD *)(v11 + 150 * *(_DWORD *)(dword_86B9AC + 24)),
			*(_DWORD *)(v11 + 150 * *(_DWORD *)(dword_86B9AC + 24) + 4),
			*(_DWORD *)(v11 + 150 * *(_DWORD *)(dword_86B9AC + 24) + 8),
			dword_D9AC27,
			(int)&dword_D9AB91,
			hWnd,
			(DWORD)&unk_C00000))
		{
			MessageBoxA(0, (LPCSTR)(dword_E5C310 + dword_E5C2B8[47].PSXStringWadLen), Caption, 0);
			return 0;
		}
		sub_401424();
		UpdateWindow(hWnd);
		ShowWindow(hWnd, nShowCmd);
		if (dword_D9ABDD & 1)
		{
			SetCursor(0);
			ShowCursor(0);
		}
		sub_402CD4((int)hWnd, hinst);
		hAccTable = LoadAcceleratorsA(hInstance, (LPCSTR)0x65);
		if (!byte_D9AC26)
		{
			sub_402EA5();
			sub_40171C();
		}
		dword_E916E0 = 0;
		dword_876C40 = 1;
		dword_876C48 = 0;
		hThread = (HANDLE)_beginthreadex(0, 0, (int)GameMain, 0, 0, &dword_876C50);
		WinProcMsg();
		dword_876C48 = 1;
		while (dword_876C40)
			;
		if (dword_E916E0)
			free(dword_E916E0);
		WinClose();
		v12 = GetDesktopWindow();
		v13 = v12;
		v14 = GetDC(v12);
		v18 = 148;
		v20 = dword_D9AC2C;
		ReleaseDC(v13, v14);
		v19 = 0x40000;
		ChangeDisplaySettingsA((DEVMODEA *)&v17, 0);
		v15 = FindWindowA(ClassName, WindowName);
		if (v15)
			PostMessageA(v15, Msg, 4u, 0);
	}
	return 0;
}
