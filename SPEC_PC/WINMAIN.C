#include "WINMAIN.H"
#include "SPECIFIC.H"
#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <crtdbg.h>
#include "GAMEFLOW.H"
#include <process.h>
#include <mm3dnow.h>
#include <ddraw.h>
#include <dsound.h>
#include "GAME.H"

int dword_876C48 = 0;
HWND hWnd;
HACCEL hAccTable;
const char* Name = "Tomb Raider Chronicles";
const char* ClassName = "DBLogWindowClass";
const char* WindowName = "DBLog Server";
UINT Msg;
HANDLE hObject;
WNDCLASSA WndClass;
HINSTANCE hinst;
HANDLE hThread;
const char* Caption = "Tomb Raider";
LPARAM dword_E4ACB8;
HANDLE dword_E4ACA4;
UINT dword_E4ACA8;
UINT dword_E4ACAC;
UINT dword_E4ACB0;
uint8 byte_57A098;
uint8 byte_D9AC23;
uint8 byte_D9AC19;
const char* String = "UM_DBLOGOUT";
const char* SubKey = "Software\\Core\\DBlog";
const char* ValueName = "CmdLine";
char GameDrive;
BYTE byte_D9ADEC;
DWORD dword_D9AD9C;
DWORD dword_D9AB24;
DWORD dword_D9AB20;
DWORD dword_D9AB28;
DWORD dword_86BD94;
BYTE byte_D9AC2B;
DWORD dword_D9ABFD;
uint32 dword_D9ABF9;
DWORD dword_86B9A4;
DWORD dword_86B9A8;


unsigned thread_id;
DWORD dword_D9ABDD;
void* dword_E916E0;
DWORD dword_876C40;
DWORD dword_D9AC2C;

DWORD dword_86BA30;

DWORD dword_86B9AC;
DWORD dword_D9AB68;

HKEY hKey;
LPSTR Class;
LPDWORD dwDisposition;

HKEY hKey;
DWORD opt_DD;
DWORD opt_D3D;
DWORD opt_VMode;
DWORD opt_TFormat;
DWORD opt_DS;
BYTE opt_BumpMap;
BYTE opt_Filter;
BYTE opt_DisableSound;
BYTE opt_Volumetric;
BYTE opt_NoFMV;
BYTE opt_Setup;

DWORD dword_D9AC1B;
DWORD dword_D9AC1F;
DWORD dword_D9AC27;

WORD opt_Key0;
WORD opt_Key1;
WORD opt_Key2;
WORD opt_Key3;
WORD opt_Key4;
WORD opt_Key5;
WORD opt_Key6;
WORD opt_Key7;
WORD opt_Key8;
WORD opt_Key9;
WORD opt_Key10;
WORD opt_Key11;
WORD opt_Key12;
WORD opt_Key13;
WORD opt_Key14;
WORD opt_Key15;
WORD opt_Key16;

DWORD opt_JDck;
DWORD opt_JDsh;
DWORD opt_JWlk;
DWORD opt_JJmp;
DWORD opt_JAct;
DWORD opt_JDrw;
DWORD opt_JFlr;
DWORD opt_JLok;
DWORD opt_JRol;
DWORD opt_JInv;

DWORD opt_MusicVolume;
DWORD opt_SFXVolume;
DWORD opt_ControlMethod;
DWORD opt_SoundQuality;
DWORD opt_AutoTarget;
DWORD opt_WindowX;
DWORD opt_WindowY;

HGDIOBJ gdiobject;

DWORD dword_D9AB70;
DWORD dword_57A094;
DWORD dword_57A084;

HWND SendMsg(HWND hWnd, LPARAM lParam)
{
	HWND result; // eax@1

	do
	{
		result = (HWND)PostMessageA(hWnd, dword_E4ACA8, 0, lParam);
		if (result)
			break;
		result = FindWindowA(ClassName, WindowName);
	} while (result);
	return result;
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

char *WinProcessCommandLine(char *a1)
{
	S_Warn("[WinProcessCommandLine] - Unimplemented!\n");
#if 0
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
#endif
	return 0;
}

char WinRunCheck(const CHAR *lpName, const CHAR *lpClassName, HANDLE *mutex)
{
	HWND v3; // eax@2
	char result; // al@4

	sub_4DEB10(2, "WinRunCheck");
	*mutex = CreateMutexA(0, 1, lpName);
	if (GetLastError() == 183)
	{
		v3 = FindWindowA(lpClassName, lpName);
		if (v3)
			SendMessageA(v3, 6u, 0, 0);
		result = 1;
	}
	else
	{
		result = 0;
	}
	return result;
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

	freopen("CONOUT$", "w", stdout);
	freopen("CONIN$", "r", stdin);
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
	/*signed int result; // eax@1
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
	return result;*/
	return 0; // TODO IF IT DOESNT WORK PUT 1 HERE
}

char sub_4DEC40(char a1)
{
	LSTATUS v1; // eax@1
	HKEY phkResult; // [sp+4h] [bp-464h]@2
	DWORD Type; // [sp+8h] [bp-460h]@4
	DWORD cbData; // [sp+Ch] [bp-45Ch]@4
	DWORD dwDisposition; // [sp+10h] [bp-458h]@2
	struct _PROCESS_INFORMATION ProcessInformation; // [sp+14h] [bp-454h]@4
	struct _STARTUPINFOA StartupInfo; // [sp+24h] [bp-444h]@4
	BYTE Data[0x400]; // [sp+68h] [bp-400h]@4

	dword_E4ACA8 = RegisterWindowMessageA(String);
	dword_E4ACAC = RegisterWindowMessageA("UM_DBCLEARLOG");
	dword_E4ACB0 = RegisterWindowMessageA("UM_DBDEFTYPE");
	Msg = RegisterWindowMessageA("UM_DBCOMMAND");
	LOBYTE(v1) = a1;
	if (a1 & 1)
	{
		v1 = RegCreateKeyExA(HKEY_LOCAL_MACHINE, SubKey, 0, 0, 0, 0xF003Fu, 0, &phkResult, &dwDisposition);
		if (!v1 && dwDisposition == 2)
		{
			memset(&Data, 0, 0x400u);
			Type = 1;
			cbData = 1024;
			RegQueryValueExA(phkResult, ValueName, 0, &Type, Data, &cbData);
			memset(&StartupInfo, 0, sizeof(StartupInfo));
			StartupInfo.cb = 68;
			if (!CreateProcessA(0, (LPSTR)Data, 0, 0, 0, 0, 0, 0, &StartupInfo, &ProcessInformation))
				GetLastError();
			WaitForInputIdle(ProcessInformation.hProcess, 0xFFFFFFFF);
			LOBYTE(v1) = RegCloseKey(phkResult);
		}
	}
	return v1;
}

char FindGameDrive()
{
	unsigned int v0; // ebx@1
	HANDLE v1; // eax@4
	char result; // al@6
	CHAR String1[8]; // [sp+Ch] [bp-18h]@1
	CHAR FileName[14]; // [sp+14h] [bp-10h]@1

	strcpy(FileName, "c:\\script.dat");
	v0 = GetLogicalDrives();
	GameDrive = 'A';
	lstrcpyA(String1, "A:\\");
	if (v0)
	{
		while (1)
		{
			if (v0 & 1)
			{
				String1[0] = GameDrive;
				if (GetDriveTypeA(String1) == 3 || GetDriveTypeA(String1) == 5)
				{
					FileName[0] = GameDrive;
					v1 = CreateFileA(FileName, 0x80000000, 0, 0, 3u, 0x80u, 0);
					if (v1 != (HANDLE)-1)
						break;
				}
			}
			v0 >>= 1;
			++GameDrive;
			if (!v0)
				goto LABEL_6;
		}
		CloseHandle(v1);
		result = 1;
	}
	else
	{
	LABEL_6:
		result = 0;
	}
	return result;
}

void sub_4018AC(signed int a1)
{
	/*signed int v1; // esi@1
	int v2; // edi@10
	int v3; // ebx@11
	int v4; // eax@11
	int v5; // ecx@11
	int v6; // edi@13
	int v7; // ecx@13
	int v8; // ecx@16
	int v9; // ecx@17
	int v10; // ebx@27
	int v11; // ebx@29
	HCURSOR v12; // eax@41
	int v13; // [sp+Ch] [bp+4h]@10

	v1 = a1;
	if (a1 == 8)
	{
		if (!byte_D9AC2B
			&& *(_DWORD *)(*(_DWORD *)(dword_86B9AC + 8) + 1590 * *(_DWORD *)(dword_86B9AC + 16) + 138) & 0x80000
			&& !dword_874968)
		{
			sub_4DEB10(6, aKa_altenter);
			sub_4DEB10(5, aHanggamethread);
			while (dword_D9ABF9)
				;
			dword_D9ABFD = 1;
			while (!dword_D9ABF9)
				;
			SuspendThread(hThread);
			sub_4DEB10(5, aGameThreadSusp);
			j_nullsub_22();
			sub_401DD9();
			j_HWInitialise();
			j_nullsub_24();
			sub_401D84();
			sub_402BAD();
			ResumeThread(hThread);
			dword_D9ABFD = 0;
			sub_4DEB10(5, aGameThreadResu);
			if (dword_D9ABDD & 1)
			{
				SetCursor(0);
				ShowCursor(0);
			}
			else
			{
				v12 = LoadCursorA(hinst, (LPCSTR)0x68);
				SetCursor(v12);
				ShowCursor(1);
			}
		}
	}
	else if (a1 > 40000 && a1 <= 40002 && !dword_874968 && !byte_D9AC2B)
	{
		sub_4DEB10(5, aChangeVideoMod);
		sub_4DEB10(5, aHanggamethread);
		if (dword_D9ABF9)
			sub_4D3211();
		dword_D9ABFD = 1;
		if (!dword_D9ABF9)
			sub_4D31D1();
		SuspendThread(hThread);
		sub_4DEB10(5, aGameThreadSusp);
		v2 = *(_DWORD *)&dword_D9AB80;
		v13 = *(_DWORD *)&dword_D9AB80;
		if (v1 == 40001)
		{
			v3 = dword_86B9AC;
			v4 = *(_DWORD *)&dword_D9AB80 + 1;
			*(_DWORD *)&dword_D9AB80 = v4;
			v5 = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(dword_86B9AC + 8) + 1590 * *(_DWORD *)(dword_86B9AC + 16) + 1586)
				+ 410 * *(_DWORD *)(dword_86B9AC + 20)
				+ 386);
			if (v4 >= v5)
			{
				v4 = v5 - 1;
				*(_DWORD *)&dword_D9AB80 = v5 - 1;
			}
			v6 = 150 * v2;
			v7 = *(_DWORD *)(*(_DWORD *)(1590 * dword_D9AB78 + *(_DWORD *)(dword_86B9AC + 8) + 1586) + 410 * dword_D9AB7C + 390);
			if (*(_DWORD *)(v7 + 150 * v4 + 8) != *(_DWORD *)(v6 + v7 + 8))
			{
				while (1)
				{
					*(_DWORD *)&dword_D9AB80 = ++v4;
					v8 = *(_DWORD *)(dword_86B9AC + 8);
					if (v4 >= *(_DWORD *)(*(_DWORD *)(v8 + 1590 * *(_DWORD *)(v3 + 16) + 1586) + 410 * *(_DWORD *)(v3 + 20) + 386))
						break;
					v9 = *(_DWORD *)(*(_DWORD *)(1590 * dword_D9AB78 + v8 + 1586) + 410 * dword_D9AB7C + 390);
					if (*(_DWORD *)(v9 + 150 * v4 + 8) == *(_DWORD *)(v6 + v9 + 8))
						goto LABEL_18;
					v3 = dword_86B9AC;
				}
				*(_DWORD *)&dword_D9AB80 = v13;
				goto LABEL_23;
			}
		LABEL_18:
			v2 = v13;
		}
		else
		{
			v4 = *(_DWORD *)&dword_D9AB80 - 1;
			*(_DWORD *)&dword_D9AB80 = v4;
			if (v4 < 0)
			{
				v4 = 0;
				*(_DWORD *)&dword_D9AB80 = 0;
			}
			v10 = *(_DWORD *)(*(_DWORD *)(1590 * dword_D9AB78 + *(_DWORD *)(dword_86B9AC + 8) + 1586)
				+ 410 * dword_D9AB7C
				+ 390);
			if (*(_DWORD *)(v10 + 150 * v4 + 8) != *(_DWORD *)(150 * v2 + v10 + 8))
			{
				while (1)
				{
					*(_DWORD *)&dword_D9AB80 = --v4;
					if (v4 < 0)
						break;
					v11 = *(_DWORD *)(*(_DWORD *)(1590 * dword_D9AB78 + *(_DWORD *)(dword_86B9AC + 8) + 1586)
						+ 410 * dword_D9AB7C
						+ 390);
					if (*(_DWORD *)(v11 + 150 * v4 + 8) == *(_DWORD *)(150 * v2 + v11 + 8))
						goto LABEL_19;
				}
				*(_DWORD *)&dword_D9AB80 = v2;
				goto LABEL_23;
			}
		}
	LABEL_19:
		if (v2 != v4)
		{
			j_nullsub_22();
			if (!sub_401857())
			{
				*(_DWORD *)&dword_D9AB80 = v2;
				sub_401857();
			}
			j_HWInitialise();
			j_nullsub_24();
			sub_4017E9(0, 0, *(_DWORD *)dword_D9ABB5, dword_D9ABB9, 20, 20480, 80);
			sub_402DD3();
			sub_401D84();
			sub_402BAD();
		}
	LABEL_23:
		ResumeThread(hThread);
		dword_D9ABFD = 0;
		sub_4DEB10(5, aGameThreadResu);
		dword_D9AD9C = 120;
		return;
	}*/
}

int DXMove(int xLeft, int yTop)
{
	int result; // eax@1

	sub_4DEB10(2, "DXMove : x %d y %d", xLeft, yTop);
	result = dword_86BD94;
	if (dword_86BD94)
	{
		if (!(*(_BYTE *)(dword_86BD94 + 76) & 1))
			result = SetRect(
			(LPRECT)(dword_86BD94 + 60),
				xLeft,
				yTop,
				xLeft + *(_DWORD *)(dword_86BD94 + 36),
				yTop + *(_DWORD *)(dword_86BD94 + 40));
	}
	return result;
}

FARPROC sub_4DB931(HMODULE a1)
{
	return GetProcAddress(a1, "Sleep");
}

HMODULE sub_4DB911()
{
	return GetModuleHandleA("kernel32.dll");
}

FARPROC sub_4DA6F1()
{
	HMODULE v0; // eax@1

	v0 = sub_4DB911();
	return sub_4DB931(v0);
}

void sub_4DA6D1()
{
	FARPROC v0; // eax@1

	v0 = sub_4DA6F1();
	((void(__stdcall *)(_DWORD))v0)(1);
}

int sub_4DA111(_DWORD *a1)
{
	_DWORD *v1; // ST00_4@1
	int result; // eax@1

	do
	{
		v1 = a1;
		sub_4DA6D1();
		a1 = v1;
		result = *v1;
	} while (*v1);
	return result;
}

int sub_4D3191()
{
	return sub_4DA111(&dword_D9ABF9);
}

int __fastcall sub_4D8F51(_DWORD *a1)
{
	_DWORD *v1; // ST00_4@1
	int result; // eax@1

	do
	{
		v1 = a1;
		sub_4DA6D1();
		a1 = v1;
		result = *v1;
	} while (!*v1);
	return result;
}

int sub_4CF191()
{
	return sub_4D8F51(&dword_D9ABF9);
}

LRESULT __stdcall sub_401E8D(HWND hWnd, unsigned int Msg, int wParam, void *lParam)
{
	if (Msg > 0x10)
	{
		if (Msg == 273)
		{
			sub_4DEB10(6, "WM_COMMAND");
			sub_4018AC((unsigned __int16)wParam);
		}
		else
		{
			if (Msg == 512)
			{
				dword_D9AB24 = (signed __int16)lParam;
				dword_D9AB20 = SHIWORD(lParam);
				dword_D9AB28 = wParam;
				return DefWindowProcA(hWnd, 0x200u, wParam, (LPARAM)lParam);
			}
			if (Msg == 0x8000)
			{
				//sub_4027DE(lParam, wParam); TODO
				return 0;
			}
		}
		return DefWindowProcA(hWnd, Msg, wParam, (LPARAM)lParam);
	}
	if (Msg == 16)
	{
		sub_4DEB10(6, "WM_CLOSE");
		byte_D9ADEC = 1;
		PostQuitMessage(0);
		return DefWindowProcA(hWnd, 0x10u, wParam, (LPARAM)lParam);
	}
	if (Msg == 1)
	{
		dword_D9AD9C = 0;
		sub_4DEB10(6, "WM_CREATE");
		return DefWindowProcA(hWnd, 1u, wParam, (LPARAM)lParam);
	}
	if (Msg == 3)
	{
		sub_4DEB10(6, "WM_MOVE");
		DXMove((signed __int16)lParam, SHIWORD(lParam));
		return DefWindowProcA(hWnd, 3u, wParam, (LPARAM)lParam);
	}
	if (Msg != 6)
		return DefWindowProcA(hWnd, Msg, wParam, (LPARAM)lParam);
	sub_4DEB10(6, "WM_ACTIVATE");
	if (byte_D9ADEC)
		return DefWindowProcA(hWnd, Msg, wParam, (LPARAM)lParam);
	if (byte_D9AC2B)
		return 0;
	if ((_WORD)wParam)
	{
		if ((signed int)(unsigned __int16)wParam > 0 && (signed int)(unsigned __int16)wParam <= 2)
		{
			sub_4DEB10(6, "WM_ACTIVE");
			if (byte_D9AC19)
			{
				//sub_40286A(1);
				ResumeThread(hThread);
				dword_D9ABFD = 0;
				sub_4DEB10(5, "Game Thread Resumed");
				return 0;
			}
		}
	}
	else
	{
		sub_4DEB10(6, "WM_INACTIVE");
		if (byte_D9AC19)
		{
			//sub_40286A(0);
			sub_4DEB10(5, "HangGameThread");
			if (dword_D9ABF9)
				sub_4D3191();
			dword_D9ABFD = 1;
			if (!dword_D9ABF9)
				sub_4CF191();
			SuspendThread(hThread);
			sub_4DEB10(5, "Game Thread Suspended");
		}
	}
	return 0;
}

char *__cdecl sub_401A7D(void *a1, int a2, size_t a3)
{
	unsigned int v3; // esi@2
	char *result; // eax@2

	if (a2)
	{
		v3 = a3;
		result = (char *)realloc(a1, a3 * (a2 + 1));
	}
	else
	{
		v3 = a3;
		result = (char *)malloc(a3);
	}
	memset(&result[v3 * a2], 0, v3);
	return result;
}

char *__cdecl sub_401C94(signed int a1)
{
	char *result; // eax@16

	if (a1 > -2005532081)
	{
		if (a1 > -2005531929)
		{
			if (a1 > -2005530624)
			{
				if (a1 > -2005530590)
				{
					if (a1 <= -2005401500)
					{
						if (a1 == -2005401500)
							return "The specified wave format is not supported. ";
						if (a1 > -2005401590)
						{
							if (a1 == -2005401570)
								return "The buffer control (volume, pan, and so on) requested by the caller is not available. ";
							if (a1 == -2005401550)
								return "This function is not valid for the current state of this object. ";
							if (a1 == -2005401530)
								return "The caller does not have the priority level required for the function to succeed. ";
						}
						else
						{
							if (a1 == -2005401590)
								return "The request failed because resources, such as a priority level, were already in use by another caller. ";
							if (a1 == -2005530589)
								return "Too many primitives";
							if (a1 == -2005530588)
								return "Invalid matrix";
							if (a1 == -2005530586)
								return "Conflicting texture palette";
						}
						return "Undefined Error";
					}
					if (a1 <= -2005401440)
					{
						if (a1 == -2005401440)
							return "Another application has a higher priority level, preventing this call from succeeding ";
						if (a1 == -2005401480)
							return "No sound driver is available for use. ";
						if (a1 == -2005401470)
							return "The object is already initialized. ";
						if (a1 == -2005401450)
							return "The buffer memory has been lost and must be restored. ";
						return "Undefined Error";
					}
					if (a1 == -2005401430)
					{
						result = "The IDirectSound::Initialize method has not been called or has not been called successfully before other methods were called. ";
					}
					else
					{
						if (a1)
							return "Undefined Error";
						result = "The request completed successfully.";
					}
				}
				else if (a1 == -2005530590)
				{
					result = "Unsupported texture filter";
				}
				else
				{
					switch (a1)
					{
					case -2005530622:
						result = "Colorkey attached";
						break;
					case -2005530594:
						result = "Conflicting texture filter";
						break;
					case -2005530591:
						result = "Conflicting render state";
						break;
					case -2005530601:
						result = "Stencil buffer not present";
						break;
					case -2005530595:
						result = "Too many operations";
						break;
					case -2005530596:
						result = "Unsupported alpha argument";
						break;
					case -2005530597:
						result = "Unsupported alpha operation";
						break;
					case -2005530598:
						result = "Unsupported color argument";
						break;
					case -2005530599:
						result = "Unsupported color opertation";
						break;
					case -2005530593:
						result = "Unsupported factor value";
						break;
					case -2005530611:
						result = "Vertex buffer create failed";
						break;
					case -2005530610:
						result = "Vertex buffer locked";
						break;
					case -2005530612:
						result = "Vertex buffer optimised";
						break;
					case -2005530600:
						result = "Wrong texture format";
						break;
					case -2005530602:
						result = "ZBuffer not present";
						break;
					default:
						return "Undefined Error";
					}
				}
			}
			else if (a1 == -2005530624)
			{
				result = "Invalid vertex format";
			}
			else
			{
				switch (a1)
				{
				case -2005531902:
					result = "Already in begin scene";
					break;
				case -2005531928:
					result = "Invalid palette";
					break;
				case -2005531922:
					result = "Light set failed";
					break;
				case -2005531921:
					result = "Light has viewport";
					break;
				case -2005531920:
					result = "Light not in this viewport";
					break;
				case -2005531897:
					result = "No current viewport";
					break;
				case -2005531901:
					result = "Not in begin scene";
					break;
				case -2005531900:
					result = "No viewports";
					break;
				case -2005531910:
					result = "Begin scene failed";
					break;
				case -2005531909:
					result = "End scene failed";
					break;
				case -2005531912:
					result = "Scene in scene";
					break;
				case -2005531911:
					result = "Scene not in scene";
					break;
				case -2005531925:
					result = "Surface not in video memory";
					break;
				case -2005531899:
					result = "Viewport data not set";
					break;
				case -2005531898:
					result = "Viewport has no device";
					break;
				case -2005531927:
					result = "ZBuffer needs system memory";
					break;
				case -2005531926:
					result = "ZBuffer needs video memory";
					break;
				default:
					return "Undefined Error";
				}
			}
		}
		else if (a1 == -2005531929)
		{
			result = "Material get data failed";
		}
		else
		{
			switch (a1)
			{
			case -2005532032:
				result = "An attempt to page lock a surface failed. Page lock will not work on a display-memory surface or an emulated primary surface. ";
				break;
			case -2005532012:
				result = "An attempt to page unlock a surface failed. Page unlock will not work on a display-memory surface or an emulated primary surface. ";
				break;
			case -2005532052:
				result = "A device context (DC) has already been returned for this surface. Only one DC can be retrieved for each surface. ";
				break;
			case -2005531973:
				result = "Surfaces created by one DirectDraw device cannot be used directly by another DirectDraw device. ";
				break;
			case -2005531981:
				result = "The data has expired and is therefore no longer valid. ";
				break;
			case -2005532080:
				result = "The requested operation could not be performed because the surface was of the wrong type. ";
				break;
			case -2005531982:
				result = "There is more data available than the specified buffer size can hold. ";
				break;
			case -2005532070:
				result = "An attempt was made to create or set a device window without first setting the focus window. ";
				break;
			case -2005532042:
				result = "An attempt was made to allocate non-local video memory from a device that does not support non-local video memory. ";
				break;
			case -2005532072:
				result = "The device does not support optimized surfaces. ";
				break;
			case -2005532071:
				result = "The surface is an optimized surface, but it has not yet been allocated any memory. ";
				break;
			case -2005531992:
				result = "An attempt is made to page unlock a surface with no outstanding page locks. ";
				break;
			case -2005531977:
				result = "The video port is not active. ";
				break;
			case -2005531972:
				result = "Bad major version";
				break;
			case -2005531971:
				result = "Bad minor version";
				break;
			case -2005531965:
				result = "Device aggregated";
				break;
			case -2005531955:
				result = "Execute clipped failed";
				break;
			case -2005531962:
				result = "Execute create failed";
				break;
			case -2005531961:
				result = "Execute destroy failed";
				break;
			case -2005531956:
				result = "Execute failed";
				break;
			case -2005531960:
				result = "Execute lock failed";
				break;
			case -2005531958:
				result = "Execute locked";
				break;
			case -2005531957:
				result = "Execute not locked";
				break;
			case -2005531959:
				result = "Execute unlock failed";
				break;
			case -2005531966:
				result = "Init failed";
				break;
			case -2005531967:
				result = "Invalid device";
				break;
			case -2005531937:
				result = "Invalid current viewport";
				break;
			case -2005531936:
				result = "Invalid primitive type";
				break;
			case -2005531933:
				result = "Invalid ramp texture";
				break;
			case -2005531935:
				result = "Invalid vertex type";
				break;
			case -2005531932:
				result = "Material create failed";
				break;
			case -2005531931:
				result = "Material destroy failed";
				break;
			case -2005531930:
				result = "Material set data failed";
				break;
			case -2005531942:
				result = "Matrix create failed";
				break;
			case -2005531941:
				result = "Matrix destroy failed";
				break;
			case -2005531939:
				result = "Matrix get data failed";
				break;
			case -2005531940:
				result = "Matrix set data failed";
				break;
			case -2005531938:
				result = "Set viewport data failed";
				break;
			case -2005531934:
				result = "Bad texture size";
				break;
			case -2005531951:
				result = "Texture create failed";
				break;
			case -2005531950:
				result = "Texture destroy failed";
				break;
			case -2005531943:
				result = "Texture get surface failed";
				break;
			case -2005531947:
				result = "Texture load failed";
				break;
			case -2005531949:
			case -2005531945:
				result = "Texture lock failed";
				break;
			case -2005531952:
				result = "Texture no support";
				break;
			case -2005531944:
				result = "Texture not locked";
				break;
			case -2005531946:
				result = "Texture swap failed";
				break;
			case -2005531948:
				result = "Texture unlock failed";
				break;
			default:
				return "Undefined Error";
			}
		}
	}
	else
	{
		if (a1 == -2005532081)
			return "The operation cannot be carried out because no mipmap capable texture mapping hardware is present or available. ";
		if (a1 > -2005532288)
		{
			switch (a1)
			{
			case -2005532098:
				result = "A DirectDrawClipper object is attached to a source surface that has passed into a call to the IDirectDrawSurface4::BltFast method.";
				break;
			case -2005532087:
				result = "Windows can not create any more device contexts (DCs), or a DC was requested for a palette-indexed surface when the surface had no palette and the display mode was not palette-indexed (in this case DirectDraw cannot select a proper palette into the DC).";
				break;
			case -2005532089:
				result = "Primary and 3-D surfaces, or surfaces that are implicitly created, cannot be duplicated. ";
				break;
			case -2005532237:
				result = "Access to this surface is refused because an attempt was made to lock the primary surface without DCI support. ";
				break;
			case -2005532105:
				result = "An attempt was made to set a clip list for a DirectDrawClipper object that is already monitoring a window handle. ";
				break;
			case -2005532272:
				result = "No source color key is specified for this operation. ";
				break;
			case -2005532110:
				result = "A DirectDraw object representing this driver has already been created for this process. ";
				break;
			case -2005532091:
				result = "An attempt was made to set the cooperative level when it was already set to exclusive. ";
				break;
			case -2005532101:
				result = "The DirectDraw cooperative level window handle has already been set. It cannot be reset while the process has surfaces or palettes created. ";
				break;
			case -2005532102:
				result = "DirectDraw is prevented from restoring state because the DirectDraw cooperative level window handle has been subclassed. ";
				break;
			case -2005532084:
				result = "The surface cannot be restored because it is an implicitly created surface. ";
				break;
			case -2005532111:
				result = "The globally unique identifier (GUID) passed to the DirectDrawCreate function is not a valid DirectDraw driver identifier. ";
				break;
			case -2005532093:
				result = "The position of the overlay on the destination is no longer legal. ";
				break;
			case -2005532151:
				result = "The specified stream contains invalid data. ";
				break;
			case -2005532097:
				result = "No blitter hardware is present. ";
				break;
			case -2005532104:
				result = "No DirectDrawClipper object is attached to the surface object. ";
				break;
			case -2005532086:
				result = "No DC has ever been created for this surface. ";
				break;
			case -2005532096:
				result = "No DirectDraw raster operation (ROP) hardware is available. ";
				break;
			case -2005532109:
				result = "Hardware-only DirectDraw object creation is not possible; the driver does not support any hardware. ";
				break;
			case -2005532107:
				result = "Software emulation is not available. ";
				break;
			case -2005532103:
				result = "Clipper notification requires a window handle, or no window handle has been previously set as the cooperative level window handle. ";
				break;
			case -2005532094:
				result = "The IDirectDrawSurface4::GetOverlayPosition method is called on an overlay that the IDirectDrawSurface4::UpdateOverlay method has not been called on to establish a destination. ";
				break;
			case -2005532100:
				result = "No palette object is attached to this surface. ";
				break;
			case -2005532099:
				result = "There is no hardware support for 16- or 256-color palettes. ";
				break;
			case -2005532092:
				result = "An overlay component is called for a non-overlay surface. ";
				break;
			case -2005532090:
				result = "An attempt has been made to flip a surface that cannot be flipped. ";
				break;
			case -2005532088:
				result = "An attempt is made to unlock a surface that was not locked. ";
				break;
			case -2005532083:
				result = "The surface being used is not a palette-based surface. ";
				break;
			case -2005532095:
				result = "The IDirectDrawSurface4::GetOverlayPosition method is called on a hidden overlay. ";
				break;
			case -2005532285:
				result = "Access to this palette is refused because the palette is locked by another thread. ";
				break;
			case -2005532108:
				result = "This process has already created a primary surface. ";
				break;
			case -2005532106:
				result = "The region passed to the IDirectDrawClipper::GetClipList method is too small. ";
				break;
			case -2005532262:
				result = "An attempt was made to attach a surface to another surface to which it is already attached. ";
				break;
			case -2005532252:
				result = "An attempt was made to make a surface a dependency of another surface to which it is already dependent. ";
				break;
			case -2005532242:
				result = "Access to the surface is refused because the surface is locked by another thread. ";
				break;
			case -2005532232:
				result = "Access to the surface is refused because the surface is obscured. ";
				break;
			case -2005532222:
				result = "Access to the surface is refused because the surface memory is gone. Call the IDirectDrawSurface4::Restore method on this surface to restore the memory associated with it. ";
				break;
			case -2005532212:
				result = "The requested surface is not attached. ";
				break;
			case -2005532202:
				result = "The height requested by DirectDraw is too large. ";
				break;
			case -2005532192:
				result = "The size requested by DirectDraw is too large. However, the individual height and width are valid sizes. ";
				break;
			case -2005532182:
				result = "The width requested by DirectDraw is too large. ";
				break;
			case -2005532162:
				result = "The FourCC format requested is not supported by DirectDraw. ";
				break;
			case -2005532152:
				result = "The bitmask in the pixel format requested is not supported by DirectDraw. ";
				break;
			case -2005532082:
				result = "The display is currently in an unsupported mode. ";
				break;
			case -2005532135:
				result = "A vertical blank is in progress. ";
				break;
			case -2005532132:
				result = "The previous blit operation that is transferring information to or from this surface is incomplete. ";
				break;
			case -2005532085:
				result = "This surface cannot be restored because it was created in a different mode. ";
				break;
			case -2005532112:
				result = "The provided rectangle was not horizontally aligned on a required boundary. ";
				break;
			default:
				return "Undefined Error";
			}
		}
		else
		{
			if (a1 == -2005532288)
				return "An attempt was made to have more than one color key active on an overlay. ";
			if (a1 > -2005532462)
			{
				switch (a1)
				{
				case -2005532457:
					result = "The surface does not currently have a color key. ";
					break;
				case -2005532452:
					result = "The operation cannot be carried out because there is no hardware support for the destination color key. ";
					break;
				case -2005532460:
					result = "A create function is called without the IDirectDraw4::SetCooperativeLevel method being called. ";
					break;
				case -2005532450:
					result = "DirectDraw support is not possible with the current display driver. ";
					break;
				case -2005532447:
					result = "The operation requires the application to have exclusive mode, but the application does not have exclusive mode. ";
					break;
				case -2005532442:
					result = "Flipping visible surfaces is not supported. ";
					break;
				case -2005532432:
					result = "No GDI is present. ";
					break;
				case -2005532422:
					result = "The operation cannot be carried out because no mirroring hardware is present or available. ";
					break;
				case -2005532412:
					result = "The operation cannot be carried out because no overlay hardware is present or available. ";
					break;
				case -2005532392:
					result = "The operation cannot be carried out because no appropriate raster operation hardware is present or available. ";
					break;
				case -2005532382:
					result = "The operation cannot be carried out because no rotation hardware is present or available. ";
					break;
				case -2005532362:
					result = "The operation cannot be carried out because there is no hardware support for stretching. ";
					break;
				case -2005532356:
					result = "The DirectDrawSurface object is not using a 4-bit color palette and the requested operation requires a 4-bit color palette. ";
					break;
				case -2005532355:
					result = "The DirectDrawSurface object is not using a 4-bit color index palette and the requested operation requires a 4-bit color index palette. ";
					break;
				case -2005532352:
					result = "The DirectDrawSurface object is not using an 8-bit color palette and the requested operation requires an 8-bit color palette. ";
					break;
				case -2005532342:
					result = "The operation cannot be carried out because no texture-mapping hardware is present or available. ";
					break;
				case -2005532417:
					result = "The requested item was not found. ";
					break;
				case -2005532337:
					result = "The operation cannot be carried out because there is no hardware support for vertical blank synchronized operations. ";
					break;
				case -2005532332:
					result = "The operation to create a z-buffer in display memory or to perform a blit using a z-buffer cannot be carried out because there is no hardware support for z-buffers. ";
					break;
				case -2005532322:
					result = "The overlay surfaces cannot be z-layered based on the z-order because the hardware does not support z-ordering of overlays. ";
					break;
				case -2005532312:
					result = "The hardware needed for the requested operation has already been allocated. ";
					break;
				case -2005532292:
					result = "DirectDraw does not have enough display memory to perform the operation. ";
					break;
				case -2005532402:
					result = "Operation could not be carried out because the source and destination rectangles are on the same surface and overlap each other. ";
					break;
				case -2005532290:
					result = "The hardware does not support clipped overlays. ";
					break;
				default:
					return "Undefined Error";
				}
			}
			else
			{
				if (a1 == -2005532462)
					return "The operation cannot be carried out because no color-conversion hardware is present or available. ";
				if (a1 > (signed int)0x8876005A)
				{
					switch (a1)
					{
					case -2005532577:
						result = "The primary surface creation request does not match with the existing primary surface. ";
						break;
					case -2005532572:
						result = "One or more of the capability bits passed to the callback function are incorrect. ";
						break;
					case -2005532562:
						result = "DirectDraw does not support the provided clip list. ";
						break;
					case -2005532552:
						result = "DirectDraw does not support the requested mode. ";
						break;
					case -2005532542:
						result = "DirectDraw received a pointer that was an invalid DirectDraw object. ";
						break;
					case -2005532527:
						result = "The pixel format was invalid as specified. ";
						break;
					case -2005532522:
						result = "The provided rectangle was invalid. ";
						break;
					case -2005532512:
						result = "One or more surfaces are locked, causing the failure of the requested operation. ";
						break;
					case -2005532502:
						result = "No 3-D hardware or emulation is present. ";
						break;
					case -2005532492:
						result = "No alpha acceleration hardware is present or available, causing the failure of the requested operation. ";
						break;
					case -2005532467:
						result = "No clip list is available. ";
						break;
					default:
						return "Undefined Error";
					}
				}
				else
				{
					if (a1 == 0x8876005A)
						return "The height of the provided rectangle is not a multiple of the required alignment. ";
					if (a1 <= (signed int)0x80070057)
					{
						if (a1 == 0x80070057)
							return "One or more of the parameters passed to the method are incorrect. ";
						if (a1 > (signed int)0x80040110)
						{
							if (a1 == 0x800401F0)
								return "An attempt was made to call an interface method of a DirectDraw object created by CoCreateInstance before the object was initialized. ";
							if (a1 == 0x8007000E)
								return "DirectDraw does not have enough memory to perform the operation. ";
						}
						else
						{
							if (a1 == 0x80040110)
								return "The object does not support aggregation. ";
							if (a1 == 0x80004001)
								return "The operation is not supported. ";
							if (a1 == 0x80004002)
								return "The requested COM interface is not available. ";
							if (a1 == 0x80004005)
								return "There is an undefined error condition. ";
						}
						return "Undefined Error";
					}
					switch (a1)
					{
					case 0x88760005:
						result = "The object has already been initialized.";
						break;
					case 0x8876000A:
						result = "A surface cannot be attached to another requested surface.";
						break;
					case 0x88760014:
						result = "A surface cannot be detached from another requested surface.";
						break;
					case 0x88760028:
						result = "No support is currently available. ";
						break;
					case 0x88760037:
						result = "An exception was encountered while performing the requested operation. ";
						break;
					default:
						return "Undefined Error";
					}
				}
			}
		}
	}
	return result;
}

signed int __cdecl sub_40179E(int a1)
{
	signed int result; // eax@2
	char* v2; // eax@3

	if (a1 < 0)
	{
		v2 = sub_401C94(a1);
		sub_4DEB10(1, "ERROR : %s", v2);
		result = 1;
	}
	else
	{
		result = 0;
	}
	return result;
}

int __cdecl DXDDCreate(GUID *lpGUID, LPVOID* a2)
{
	int v2; // ecx@0
	HRESULT v3; // eax@1
	int v4; // eax@2
	int v5; // eax@3
	int result; // eax@5
	LPDIRECTDRAW lpDD; // [sp+10h] [bp-4h]@1

	lpDD = (LPDIRECTDRAW)v2;
	sub_4DEB10(2, "DXDDCreate");
	v3 = DirectDrawCreate(lpGUID, &lpDD, 0);
	if (sub_40179E(v3))
	{
		sub_4DEB10(1, "DXDDCreate Failed");
		result = 0;
	}
	else
	{
		v4 = lpDD->lpVtbl->QueryInterface(lpDD, &IID_IDirectDraw4, a2);

		//v4 = (*(int(__stdcall **)(LPDIRECTDRAW, void *, int))lpDD->lpVtbl)(lpDD, IID_IDirectDraw4, a2);
		sub_40179E(v4);
		if (lpDD)
		{
			//v5 = (*((int(__stdcall **)(LPDIRECTDRAW))lpDD->lpVtbl + 2))(lpDD);
			v5 = lpDD->lpVtbl->Release(lpDD);
			sub_4DEB10(4, "Released %s @ %x - RefCnt = %d", "DirectDraw", lpDD, v5);
			lpDD = 0;
		}
		else
		{
			sub_4DEB10(1, "%s Attempt To Release NULL Ptr", "DirectDraw");
		}
		sub_4DEB10(5, "DXDDCreate Successful");
		result = 1;
	}
	return result;
}

BOOL __cdecl sub_402FA9(int a1, int a2, int a3)
{
	S_Warn("[sub_402FA9] - Unimplemented!\n");
}

unsigned int __cdecl sub_49F9C0(unsigned int a1, _BYTE *a2, _BYTE *a3)
{
	unsigned int result; // eax@1
	char i; // cl@1
	char v5; // cl@3

	result = a1;
	for (i = 0; !(result & 1); ++i)
		result >>= 1;
	*a2 = i;
	v5 = 0;
	if (result & 1)
	{
		do
		{
			result >>= 1;
			++v5;
		} while (result & 1);
		result = (unsigned int)a3;
		*a3 = v5;
	}
	else
	{
		*a3 = 0;
	}
	return result;
}

unsigned int __cdecl sub_4016B3(int a1, int a2, int a3)
{
	return sub_49F9C0(a1, (_BYTE *)a2, (_BYTE *)a3);
}

signed int __stdcall sub_401CBC(int a1, int a2)
{
	int v2; // esi@1
	char *v3; // eax@1
	int v4; // ebx@1
	int v5; // edx@1

	v2 = *(_DWORD *)(a2 + 1574);
	v3 = sub_401A7D(*(void **)(a2 + 1578), *(_DWORD *)(a2 + 1574), 0x96u);
	*(_DWORD *)(a2 + 1578) = (DWORD)v3;
	v4 = (int)&v3[150 * v2];
	*(_DWORD *)v4 = *(_DWORD *)(a1 + 12);
	*(_DWORD *)(v4 + 4) = *(_DWORD *)(a1 + 8);
	*(_DWORD *)(v4 + 8) = *(_DWORD *)(a1 + 84);
	v5 = (*(_DWORD *)(a1 + 76) >> 5) & 1;
	*(_DWORD *)(v4 + 16) = v5;
	*(_DWORD *)(v4 + 12) = *(_DWORD *)(a1 + 24);
	qmemcpy((void *)(v4 + 20), (const void *)a1, 0x7Cu);
	if (v5)
	{
		sub_4DEB10(3, "%d x %d - %d Bit - Palette", *(_DWORD *)v4, *(_DWORD *)(v4 + 4), *(_DWORD *)(v4 + 8));
	}
	else
	{
		sub_4016B3(*(_DWORD *)(a1 + 88), v4 + 147, v4 + 144);
		sub_4016B3(*(_DWORD *)(a1 + 92), v4 + 148, v4 + 145);
		sub_4016B3(*(_DWORD *)(a1 + 96), v4 + 149, v4 + 146);
		sub_4DEB10(
			3,
			"%d x %d - %d Bit - %d%d%d",
			*(_DWORD *)v4,
			*(_DWORD *)(v4 + 4),
			*(_DWORD *)(v4 + 8),
			*(_BYTE *)(v4 + 144),
			*(_BYTE *)(v4 + 145),
			*(_BYTE *)(v4 + 146));
	}
	++*(_DWORD *)(a2 + 1574);
	return 1;
}

signed int __cdecl sub_4028B5(int(__stdcall ***a1)(_DWORD, _DWORD, _DWORD), int a2)
{
	/*int v2; // eax@1
	signed int result; // eax@2

	sub_4DEB10(2, "DXD3DCreate");
	v2 = (**a1)(a1, &unk_502A10, a2);
	if (sub_40179E(v2))
	{
		sub_4DEB10(1, "DXD3DCreate Failed");
		result = 0;
	}
	else
	{
		sub_4DEB10(5, "DXD3DCreate Successful");
		result = 1;
	}
	return result;*/

	S_Warn("[DXD3DCreate] - Unimplemented!\n");
	return 0;
}

signed int __cdecl sub_40206D(int a1)
{
	signed int result; // eax@2

	switch (a1)
	{
	case 1:
		result = 0x4000;
		break;
	case 2:
		result = 0x2000;
		break;
	case 4:
		result = 4096;
		break;
	case 8:
		result = 2048;
		break;
	case 16:
		result = 1024;
		break;
	case 24:
		result = 512;
		break;
	case 32:
		result = 256;
		break;
	default:
		result = 0;
		break;
	}
	return result;
}

BOOL __cdecl DXSetCooperativeLevel(int a1, int a2, int a3)
{
	S_Warn("[DXSetCooperativeLevel] - Unimplemented!\\n");
	return FALSE;
}

signed int __cdecl DXCreateSurface(int a1, int a2, int a3)
{
	int v3; // eax@1
	signed int result; // eax@2

	sub_4DEB10(2, "DXCreateSurface");
	v3 = (*(int(__stdcall **)(int, int, int, _DWORD))(*(_DWORD *)a1 + 24))(a1, a2, a3, 0);
	if (sub_40179E(v3))
	{
		sub_4DEB10(1, "DXCreateSurface Failed");
		result = 0;
	}
	else
	{
		result = 1;
	}
	return result;
}

signed int __cdecl DXCreateD3DDevice(int a1, char a2, int a3, int a4, int a5, int a6, int a7)
{
	int v7; // eax@1
	signed int result; // eax@2

	sub_4DEB10(2, "DXCreateD3DDevice");
	v7 = (*(int(__stdcall **)(int, char *, int, int, _DWORD))(*(_DWORD *)a1 + 32))(a1, &a2, a6, a7, 0);
	if (sub_40179E(v7))
	{
		sub_4DEB10(1, "DXCreateD3DDevice Failed");
		result = 0;
	}
	else
	{
		sub_4DEB10(2, "DXCreateD3DDevice Successful");
		result = 1;
	}
	return result;
}

BOOL __cdecl DXSetVideoMode(int a1, int a2, int a3, int a4)
{
	int v4; // eax@1

	sub_4DEB10(2, "DXSetVideoMode");
	sub_4DEB10(5, "SetDisplayMode - %dx%dx%d", a2, a3, a4);
	v4 = (*(int(__stdcall **)(int, int, int, int, _DWORD, _DWORD))(*(_DWORD *)a1 + 84))(a1, a2, a3, a4, 0, 0);
	return sub_40179E(v4) == 0;
}

signed int __stdcall sub_401019(int a1, int a2)
{
	int v2; // eax@1
	int v3; // esi@3
	char *v4; // eax@3
	int v5; // ebp@3
	int v6; // eax@3
	int v7; // eax@7
	_BYTE *v8; // esi@8
	int v9; // ST18_4@9
	int v10; // ST14_4@9
	int v11; // ST10_4@9
	int v12; // ST0C_4@9
	int v13; // ST08_4@9
	signed int result; // eax@11
	int v15; // [sp-10h] [bp-14h]@8

	v2 = *(_DWORD *)(a1 + 4);
	if (v2 & 1 && v2 & 0x40)
	{
		v3 = *(_DWORD *)(a2 + 394);
		v4 = sub_401A7D(*(void **)(a2 + 398), *(_DWORD *)(a2 + 394), 0x34u);
		*(_DWORD *)(a2 + 398) = v4;
		v5 = (int)&v4[52 * v3];
		qmemcpy(&v4[52 * v3], (const void *)a1, 0x20u);
		v6 = *(_DWORD *)(a1 + 4);
		if (v6 & 0x20)
		{
			*(_DWORD *)(v5 + 36) = 1;
			*(_DWORD *)(v5 + 32) = 8;
			sub_4DEB10(3, "8 Bit");
		}
		else if (v6 & 8)
		{
			*(_DWORD *)(v5 + 36) = 1;
			*(_DWORD *)(v5 + 32) = 4;
			sub_4DEB10(3, "4 Bit");
		}
		else
		{
			*(_DWORD *)(v5 + 36) = 0;
			*(_DWORD *)(v5 + 32) = *(_DWORD *)(a1 + 12);
			v7 = *(_DWORD *)(a1 + 4);
			if (v7 & 0x40)
			{
				v8 = (_BYTE *)(v5 + 44);
				v15 = v5 + 44;
				if (v7 & 1)
				{
					sub_4016B3(*(_DWORD *)(a1 + 16), v5 + 48, v15);
					sub_4016B3(*(_DWORD *)(a1 + 20), v5 + 49, v5 + 45);
					sub_4016B3(*(_DWORD *)(a1 + 24), v5 + 50, v5 + 46);
					sub_4016B3(*(_DWORD *)(a1 + 28), v5 + 51, v5 + 47);
					v9 = *(_BYTE *)(v5 + 47);
					v10 = *(_BYTE *)(v5 + 46);
					v11 = *(_BYTE *)(v5 + 45);
					v12 = *v8;
					v13 = *(_DWORD *)(v5 + 32);
					*(_DWORD *)(v5 + 40) = 1;
					sub_4DEB10(3, "%d Bit %d%d%d%d RGBA", v13, v12, v11, v10, v9);
				}
				else
				{
					sub_4016B3(*(_DWORD *)(a1 + 16), v5 + 48, v15);
					sub_4016B3(*(_DWORD *)(a1 + 20), v5 + 49, v5 + 45);
					sub_4016B3(*(_DWORD *)(a1 + 24), v5 + 50, v5 + 46);
					sub_4DEB10(3, "%d Bit %d%d%d RGB", *(_DWORD *)(v5 + 32), *v8, *(_BYTE *)(v5 + 45), *(_BYTE *)(v5 + 46));
				}
			}
		}
		++*(_DWORD *)(a2 + 394);
		result = 1;
	}
	else
	{
		result = 1;
	}
	return result;
}

signed int __stdcall sub_402FDB(int a1, int a2)
{
	int v2; // esi@1
	char *v3; // eax@1
	int v4; // eax@1
	int v5; // ST08_4@1

	v2 = *(_DWORD *)(a2 + 402);
	v3 = sub_401A7D(*(void **)(a2 + 406), *(_DWORD *)(a2 + 402), 0x24u);
	*(_DWORD *)(a2 + 406) = v3;
	v4 = (int)&v3[36 * v2];
	qmemcpy((void *)v4, (const void *)a1, 0x20u);
	v5 = *(_DWORD *)(a1 + 12);
	*(_DWORD *)(v4 + 32) = v5;
	sub_4DEB10(3, "%d Bit", v5);
	++*(_DWORD *)(a2 + 402);
	return 1;
}

signed int __stdcall sub_402ECD(int a1, const CHAR *lpString2, const CHAR *a3, int a4, const void *a5, int a6)
{
	int v6; // esi@1
	char *v7; // eax@1
	int v8; // ebp@1
	int v9; // ecx@3
	char *v10; // ebx@4
	unsigned int v11; // ecx@7
	char v12; // dl@7
	char *v13; // edi@7
	char *v14; // esi@7
	char v15; // cl@7
	unsigned int v16; // ecx@8
	char v17; // al@8
	int v18; // ebx@10
	int v19; // eax@10
	int v20; // edi@11
	char *v21; // eax@12
	int v22; // ecx@12
	char *v23; // eax@12
	int v24; // ecx@16
	int v25; // eax@20
	int v26; // eax@22
	int v27; // eax@25
	int v28; // eax@26
	int v29; // eax@30
	int v30; // eax@32
	int v32; // [sp+10h] [bp-88h]@17
	int v33; // [sp+14h] [bp-84h]@18
	int v34; // [sp+18h] [bp-80h]@10
	int v35; // [sp+1Ch] [bp-7Ch]@17
	int v36; // [sp+20h] [bp-78h]@17
	int v37; // [sp+84h] [bp-14h]@17

	v6 = *(_DWORD *)(a6 + 1582);
	v7 = sub_401A7D(*(void **)(a6 + 1586), *(_DWORD *)(a6 + 1582), 0x19Au);
	*(_DWORD *)(a6 + 1586) = v7;
	v8 = (int)&v7[410 * v6];
	if (a1)
	{
		v9 = v8 + 114;
		*(_DWORD *)(v8 + 110) = v8 + 114;
		*(_DWORD *)v9 = *(_DWORD *)a1;
		*(_DWORD *)(v9 + 4) = *(_DWORD *)(a1 + 4);
		*(_DWORD *)(v9 + 8) = *(_DWORD *)(a1 + 8);
		*(_DWORD *)(v9 + 12) = *(_DWORD *)(a1 + 12);
	}
	else
	{
		*(_DWORD *)(v8 + 110) = 0;
	}
	v10 = (char *)(v8 + 30);
	lstrcpyA((LPSTR)(v8 + 30), lpString2);
	lstrcpyA((LPSTR)v8, a3);
	sub_4DEB10(5, "Found - %s", lpString2);
	if (*(_DWORD *)(a4 + 4))
	{
		*(_DWORD *)(v8 + 382) = 1;
		qmemcpy((void *)(v8 + 130), (const void *)a4, 0xFCu);
	}
	else
	{
		*(_DWORD *)(v8 + 382) = 0;
		qmemcpy((void *)(v8 + 130), a5, 0xFCu);
		if (byte_D9AC23)
		{
			char* aCoreDesignMmxH = "Core Design MMX Hardware Card Emulation";
			v11 = strlen(aCoreDesignMmxH) + 1;
			v12 = v11;
			v11 >>= 2;
			qmemcpy(v10, aCoreDesignMmxH, 4 * v11);
			v14 = &aCoreDesignMmxH[4 * v11];
			v13 = &v10[4 * v11];
			v15 = v12;
		}
		else
		{
			char* aCoreDesignHard = "Core Design Hardware Card Emulation";
			v16 = strlen(aCoreDesignHard) + 1;
			v17 = v16;
			v16 >>= 2;
			qmemcpy(v10, aCoreDesignHard, 4 * v16);
			v14 = &aCoreDesignHard[4 * v16];
			v13 = &v10[4 * v16];
			v15 = v17;
		}
		qmemcpy(v13, v14, v15 & 3);
	}
	sub_4DEB10(5, "Finding Compatible Display Modes");
	v18 = 0;
	*(_DWORD *)(v8 + 386) = 0;
	v19 = *(_DWORD *)(a6 + 1574);
	v34 = 0;
	if (v19 > 0)
	{
		do
		{
			v20 = a6;
			if (sub_40206D(*(_DWORD *)(v18 + *(_DWORD *)(a6 + 1578) + 8)) & *(_DWORD *)(v8 + 286))
			{
				v21 = sub_401A7D(*(void **)(v8 + 390), *(_DWORD *)(v8 + 386), 0x96u);
				v22 = *(_DWORD *)(v8 + 386);
				*(_DWORD *)(v8 + 390) = v21;
				v23 = &v21[150 * v22];
				qmemcpy(v23, (const void *)(*(_DWORD *)(a6 + 1578) + v18), 0x96u);
				if (*((_DWORD *)v23 + 4))
					sub_4DEB10(3, "%d x %d - %d Bit - Palette", *(_DWORD *)v23, *((_DWORD *)v23 + 1), *((_DWORD *)v23 + 2));
				else
					sub_4DEB10(
						3,
						"%d x %d - %d Bit - %d%d%d",
						*(_DWORD *)v23,
						*((_DWORD *)v23 + 1),
						*((_DWORD *)v23 + 2),
						(unsigned __int8)v23[144],
						(unsigned __int8)v23[145],
						(unsigned __int8)v23[146]);
				v20 = a6;
				++*(_DWORD *)(v8 + 386);
			}
			v24 = *(_DWORD *)(v20 + 1574);
			v18 += 150;
			++v34;
		} while (v34 < v24);
	}
	sub_4DEB10(5, "Enumerate Texture Formats");
	memset(&v35, 0, 0x7Cu);
	v35 = 124;
	v36 = 1;
	v37 = 8704;
	DXSetCooperativeLevel(*(int *)dword_86B9A8, dword_86B9A4, 21);
	DXCreateSurface(*(int *)dword_86B9A8, (int)&v35, (int)&v32);
	if (v32)
	{
		DXCreateD3DDevice(
			dword_86BA30,
			*(_DWORD *)(v8 + 114),
			*(_DWORD *)(v8 + 118),
			*(_DWORD *)(v8 + 122),
			*(_DWORD *)(v8 + 126),
			v32,
			(int)&v33);
		if (v33)
			goto LABEL_35;
		sub_4DEB10(1, "Create D3DDevice Failed");
		if (v32)
		{
			v25 = (*(int(__stdcall **)(int))(*(_DWORD *)v32 + 8))(v32);
			sub_4DEB10(4, "Released %s @ %x - RefCnt = %d", "DirectDrawSurface", v32, v25);
			v32 = 0;
		}
		else
		{
			sub_4DEB10(1, "%s Attempt To Release NULL Ptr", "DirectDrawSurface");
		}
		DXSetVideoMode(
			*(int *)dword_86B9A8,
			**(_DWORD **)(v8 + 390),
			*(_DWORD *)(*(_DWORD *)(v8 + 390) + 4),
			*(_DWORD *)(*(_DWORD *)(v8 + 390) + 8));
		DXCreateSurface(*(int *)dword_86B9A8, (int)&v35, (int)&v32);
		v26 = v32;
		if (v32)
		{
			DXCreateD3DDevice(
				dword_86BA30,
				*(_DWORD *)(v8 + 114),
				*(_DWORD *)(v8 + 118),
				*(_DWORD *)(v8 + 122),
				*(_DWORD *)(v8 + 126),
				v32,
				(int)&v33);
			v26 = v32;
		}
		if (v33)
		{
		LABEL_35:
			*(_DWORD *)(v8 + 394) = 0;
			sub_4DEB10(2, "DXEnumTextureFormats");
			v27 = (*(int(__stdcall **)(int, void *, int))(*(_DWORD *)v33 + 32))(v33, &sub_401019, v8);
			sub_40179E(v27);
			if (v33)
			{
				v28 = (*(int(__stdcall **)(int))(*(_DWORD *)v33 + 8))(v33);
				sub_4DEB10(4, "Released %s @ %x - RefCnt = %d", "D3DDevice", v33, v28);
				v33 = 0;
			}
			else
			{
				sub_4DEB10(1, "%s Attempt To Release NULL Ptr", "D3DDevice");
			}
			v26 = v32;
		}
		if (v26)
		{
			v29 = (*(int(__stdcall **)(int))(*(_DWORD *)v26 + 8))(v26);
			sub_4DEB10(4, "Released %s @ %x - RefCnt = %d", "DirectDrawSurface", v32, v29);
			v32 = 0;
		}
		else
		{
			sub_4DEB10(1, "%s Attempt To Release NULL Ptr", "DirectDrawSurface");
		}
	}
	DXSetCooperativeLevel(*(int *)dword_86B9A8, dword_86B9A4, 8);
	sub_4DEB10(5, "Enumerating ZBuffer Formats");
	sub_4DEB10(2, "DXEnumZBufferFormats");
	v30 = (*(int(__stdcall **)(int, int, int(__stdcall *)(int, int), int))(*(_DWORD *)dword_86BA30 + 40))(
		dword_86BA30,
		v8 + 114,
		sub_402FDB,
		v8);
	sub_40179E(v30);
	++*(_DWORD *)(a6 + 1582);
	return 1;
}

signed int __stdcall Callback(GUID *lpGUID, LPSTR lpString2, LPSTR a3, LPVOID a4)
{
	int v4; // esi@1
	char* v5; // eax@1
	char* v6; // esi@1
	char* v7; // eax@3
	int v8; // eax@5
	int v9; // eax@5
	int v10; // eax@5
	int v11; // eax@6
	int v12; // eax@7
	int v13; // eax@10

	sub_4DEB10(2, "DXEnumDirectDraw");
	v4 = *(_DWORD *)a4;
	v5 = sub_401A7D(*(void **)((char*)a4 + 8), *(_DWORD *)a4, 0x636u);
	*(_DWORD *)((char*)a4 + 8) = (_DWORD)v5;
	v6 = v5 + 1590 * v4;
	if (lpGUID)
	{
		v7 = v6 + 114;
		*(_DWORD *)(v6 + 110) = (DWORD)v6 + 114;
		*(_DWORD *)v7 = lpGUID->Data1;
		*(_DWORD *)(v7 + 4) = *(_DWORD *)&lpGUID->Data2;
		*(_DWORD *)(v7 + 8) = *(_DWORD *)&lpGUID->Data4[0];
		*(_DWORD *)(v7 + 12) = *(_DWORD *)&lpGUID->Data4[4];
	}
	else
	{
		*(_DWORD *)(v6 + 110) = 0;
	}
	lstrcpyA((LPSTR)(v6 + 30), lpString2);
	lstrcpyA((LPSTR)v6, a3);
	sub_4DEB10(5, "Obtaining Information For %s", lpString2);
	if (DXDDCreate(lpGUID, (LPVOID*)dword_86B9A8))
	{
		v8 = (*(int(__stdcall **)(_DWORD, int, _DWORD))(**(_DWORD **)dword_86B9A8 + 108))(
			*(_DWORD *)dword_86B9A8,
			(int)v6 + 510,
			0);
		sub_40179E(v8);
		sub_4DEB10(
			5,
			"Found - %s\r\nDriver %s Version %d.%d.%d.%d",
			v6 + 1022,
			v6 + 510,
			*(_DWORD *)(v6 + 1538) >> 16,
			*(_WORD *)(v6 + 1538),
			*(_DWORD *)(v6 + 1534) >> 16,
			*(_WORD *)(v6 + 1534));
		memset((void *)(v6 + 130), 0, 0x17Cu);
		*(_DWORD *)(v6 + 130) = 380;
		sub_4DEB10(5, "Getting Device Capabilities");
		v9 = (*(int(__stdcall **)(_DWORD, int, _DWORD))(**(_DWORD **)dword_86B9A8 + 44))(
			*(_DWORD *)dword_86B9A8,
			(int)v6 + 130,
			0);
		sub_40179E(v9);
		sub_4DEB10(5, "Enumerating Display Modes");
		sub_402FA9(*(_DWORD *)dword_86B9A8, 0, 77);
		sub_4DEB10(2, "DXEnumDisplayModes");
		v10 = (*(int(__stdcall **)(_DWORD, _DWORD, _DWORD, int, void *))(**(_DWORD **)dword_86B9A8 + 32))(
			*(_DWORD *)dword_86B9A8,
			0,
			0,
			v6,
			&sub_401CBC);
		sub_40179E(v10);
		if (sub_4028B5(*(_DWORD *)dword_86B9A8, &dword_86BA30))
		{
			sub_4DEB10(2, "DXEnumDirect3D");
			v11 = (*(int(__stdcall **)(int, void *, int))(*(_DWORD *)dword_86BA30 + 12))(dword_86BA30, &sub_402ECD, v6);
			sub_40179E(v11);
			if (dword_86BA30)
			{
				v12 = (*(int(__stdcall **)(int))(*(_DWORD *)dword_86BA30 + 8))(dword_86BA30);
				sub_4DEB10(4, "Released %s @ %x - RefCnt = %d", "Direct3D", dword_86BA30, v12);
				dword_86BA30 = 0;
			}
			else
			{
				sub_4DEB10(1, "%s Attempt To Release NULL Ptr", "Direct3D");
			}
		}
		sub_402FA9(*(_DWORD *)dword_86B9A8, 0, 8);
		if (*(_DWORD *)dword_86B9A8)
		{
			v13 = (*(int(__stdcall **)(_DWORD))(**(_DWORD **)dword_86B9A8 + 8))(*(_DWORD *)dword_86B9A8);
			sub_4DEB10(4, "Released %s @ %x - RefCnt = %d", "DirectDraw", *(_DWORD *)dword_86B9A8, v13);
			*(_DWORD *)dword_86B9A8 = 0;
			++*(_DWORD *)a4;
			return 1;
		}
		sub_4DEB10(1, "%s Attempt To Release NULL Ptr", "DirectDraw");
	}
	++*(_DWORD *)a4;
	return 1;
}

signed int __stdcall DXEnumDirectSound(int a1, const CHAR *lpString2, const CHAR *a3, int a4)
{
	int v4; // edi@1
	char *v5; // eax@1
	int v6; // edi@1
	int v7; // eax@3

	sub_4DEB10(2, "DXEnumDirectSound");
	v4 = *(_DWORD *)(a4 + 4);
	v5 = sub_401A7D(*(void **)(a4 + 12), *(_DWORD *)(a4 + 4), 0x82u);
	*(_DWORD *)(a4 + 12) = v5;
	v6 = (int)&v5[130 * v4];
	if (a1)
	{
		v7 = v6 + 114;
		*(_DWORD *)(v6 + 110) = v6 + 114;
		*(_DWORD *)v7 = *(_DWORD *)a1;
		*(_DWORD *)(v7 + 4) = *(_DWORD *)(a1 + 4);
		*(_DWORD *)(v7 + 8) = *(_DWORD *)(a1 + 8);
		*(_DWORD *)(v7 + 12) = *(_DWORD *)(a1 + 12);
	}
	else
	{
		*(_DWORD *)(v6 + 110) = 0;
	}
	lstrcpyA((LPSTR)(v6 + 30), lpString2);
	lstrcpyA((LPSTR)v6, a3);
	sub_4DEB10(5, "Found - %s %s", lpString2, a3);
	++*(_DWORD *)(a4 + 4);
	return 1;
}

signed int __cdecl DXInitialise(void *lpContext, int a2)
{
	HRESULT v2; // eax@1
	HRESULT v3; // eax@1

	sub_4DEB10(2, "DXInitialise");
	dword_86B9A4 = a2;
	sub_4DEB10(5, "Enumerating DirectDraw Devices");
	v2 = DirectDrawEnumerateA(Callback, lpContext);
	sub_40179E(v2);
	v3 = DirectSoundEnumerateA(DXEnumDirectSound, lpContext);
	sub_40179E(v3);
	dword_86B9AC = (int)lpContext;
	return 1;
}

int sub_402CD4(HWND hWnd, HINSTANCE hInstance)
{
	S_Warn("[sub_402CD4] - Unimplemented!\n");
	return 1;
}

void DXDSCreate()
{
	S_Warn("[DXDSCreate] - Unimplemented!\n");
}

void InitACM()
{
	S_Warn("[InitACM] - Unimplemented!\n");
}

LSTATUS __cdecl sub_4029B9(LPCSTR lpValueName, BYTE Data)
{
	return RegSetValueExA(hKey, lpValueName, 0, 4u, &Data, 4u);
}

char __cdecl sub_402806(LPCSTR lpValueName, DWORD Type, BYTE Data)
{
	_DWORD *v3; // edi@1
	char result; // al@4
	int v5; // esi@5
	DWORD cbData; // [sp+Ch] [bp-4h]@1

	v3 = (_DWORD *)Type;
	cbData = 4;
	if (RegQueryValueExA(hKey, lpValueName, 0, &Type, (LPBYTE)Type, &cbData) || Type != 4 || cbData != 4)
	{
		v5 = Data;
		sub_4029B9(lpValueName, Data);
		*v3 = v5;
		result = 0;
	}
	else
	{
		result = 1;
	}
	return result;
}

BOOL __cdecl sub_4020A9(LPCSTR lpSubKey)
{
	return RegCreateKeyExA(HKEY_CURRENT_USER, lpSubKey, 0, Class, 0, 0xF003Fu, 0, &hKey, &dwDisposition) == 0;
}

int __cdecl sub_402964(char* a1)
{
	int result; // eax@2
	CHAR SubKey; // [sp+0h] [bp-100h]@2

	if (a1)
	{
		sprintf(&SubKey, "%s\\%s", "Software\\Core Design\\Tomb Raider Chronicles", a1);
		result = sub_4020A9(&SubKey);
	}
	else
	{
		result = sub_4020A9("Software\\Core Design\\Tomb Raider Chronicles");
	}
	return result;
}

LSTATUS __cdecl sub_402B94(LPCSTR lpValueName, BYTE Data)
{
	*(_DWORD *)&Data = (unsigned __int8)Data;
	return RegSetValueExA(hKey, lpValueName, 0, 4u, &Data, 4u);
}

char __cdecl sub_401FAA(LPCSTR lpValueName, int a2, BYTE a3)
{
	const CHAR *v3; // esi@1
	char result; // al@4
	BYTE v5; // bl@5
	DWORD cbData; // [sp+4h] [bp-8h]@1
	BYTE Data[4]; // [sp+8h] [bp-4h]@1

	v3 = lpValueName;
	cbData = 4;
	if (RegQueryValueExA(hKey, lpValueName, 0, (LPDWORD)&lpValueName, Data, &cbData)
		|| lpValueName != (LPCSTR)4
		|| cbData != 4)
	{
		v5 = a3;
		sub_402B94(v3, a3);
		*(_BYTE *)a2 = v5;
		result = 0;
	}
	else
	{
		*(_BYTE *)a2 = *(_DWORD *)Data != 0;
		result = 1;
	}
	return result;
}
char __cdecl sub_4017B7(HWND hDlg, HWND hWnd, char a3)
{
	S_Warn("[sub_4017B7] - Unimplemented!\n");
	return 0;
}

int __cdecl sub_40199C(HWND hDlg, HWND hWnd)
{
	int v2; // esi@1
	int v3; // eax@1
	int v4; // edi@2
	HWND v5; // eax@4

	SendMessageA(hWnd, 0x14Bu, 0, 0);
	v2 = 0;
	v3 = dword_D9AB70 + 1590 * dword_57A094;
	if (*(_DWORD *)(v3 + 1582) > 0)
	{
		v4 = 0;
		do
		{
			SendMessageA(hWnd, 0x143u, 0, *(_DWORD *)(v3 + 1586) + v4 + 30);
			++v2;
			v4 += 410;
			v3 = dword_D9AB70 + 1590 * dword_57A094;
		} while (v2 < *(_DWORD *)(v3 + 1582));
	}
	SendMessageA(hWnd, 0x14Eu, 1u, 0);
	dword_57A084 = 1;
	v5 = GetDlgItem(hDlg, 1004);
	return sub_4017B7(hDlg, v5, 1);
}

int __cdecl sub_4026FD(HWND hDlg, HWND hWnd)
{
	int v2; // eax@1
	int v3; // edi@1
	int v4; // esi@2
	HWND v5; // eax@4
	CHAR v7; // [sp+10h] [bp-100h]@3

	SendMessageA(hWnd, 0x14Bu, 0, 0);
	v2 = dword_D9AB68;
	v3 = 0;
	if (dword_D9AB68 > 0)
	{
		v4 = 0;
		do
		{
			wsprintfA(
				&v7,
				"%s - %s (%d.%d.%02d.%04d)",
				v4 + dword_D9AB70 + 1022,
				v4 + dword_D9AB70 + 510,
				*(_DWORD *)(v4 + dword_D9AB70 + 1538) >> 16,
				*(_WORD *)(v4 + dword_D9AB70 + 1538),
				*(_DWORD *)(v4 + dword_D9AB70 + 1534) >> 16,
				*(_WORD *)(v4 + dword_D9AB70 + 1534));
			SendMessageA(hWnd, 0x143u, 0, (LPARAM)&v7);
			v2 = dword_D9AB68;
			++v3;
			v4 += 1590;
		} while (v3 < dword_D9AB68);
	}
	SendMessageA(hWnd, 0x14Eu, v2 - 1, 0);
	dword_57A094 = dword_D9AB68 - 1;
	v5 = GetDlgItem(hDlg, 1003);
	return sub_40199C(hDlg, v5);
}

char sub_402F77()
{
	int v0; // eax@8
	int v1; // eax@9
	int v2; // edx@13
	int v3; // ecx@13
	char result; // al@13
	DWORD Type; // [sp+3h] [bp-5h]@3

	if ((unsigned __int8)sub_402964("System"))
	{
		sub_401FAA("Setup", (int)&opt_Setup, 0);
		if (opt_Setup)
		{
			dword_D9AC1B = 256;
			dword_D9AC1F = 256;
			dword_D9AC27 = 32;
			sub_402806("DD", (DWORD)&opt_DD, 0);
			sub_402806("D3D", (DWORD)&opt_D3D, 0);
			sub_402806("VMode", (DWORD)&opt_VMode, 0);
			sub_402806("TFormat", (DWORD)&opt_TFormat, 0);
			sub_402806("DS", (DWORD)&opt_DS, 0);
			sub_401FAA("BumpMap", (int)&opt_BumpMap, 1);
			sub_401FAA("Filter", (int)&opt_Filter, 1);
			sub_401FAA("DisableSound", (int)&opt_DisableSound, 0);
			sub_401FAA("Volumetric", (int)&opt_Volumetric, 1);
			sub_401FAA("NoFMV", (int)&opt_NoFMV, 0);
			sub_401FAA("TextLow", (int)&Type, 0);
			if ((_BYTE)Type)
				dword_D9AC1B = 128;
			sub_401FAA("BumpLow", (int)&Type, 0);
			if ((_BYTE)Type)
				dword_D9AC1F = 128;
			sub_401FAA("HardWare", (int)&Type, 1);
			if ((_BYTE)Type)
			{
				v0 = dword_D9AC27;
				LOBYTE(v0) = dword_D9AC27 | 0x90;
				dword_D9AC27 = v0;
			}
			sub_401FAA("Window", (int)&Type, 0);
			v1 = dword_D9AC27;
			if ((_BYTE)Type)
				LOBYTE(v1) = dword_D9AC27 | 2;
			else
				LOBYTE(v1) = dword_D9AC27 | 1;
			dword_D9AC27 = v1;
		}
		sub_402964("Game");
		sub_402806("Key0", (DWORD)&Type + 1, opt_Key0);
		word_516C60[0] = *(_WORD *)((char *)&Type + 1);
		sub_402806("Key1", (DWORD)&Type + 1, opt_Key1);
		word_516C62 = *(_WORD *)((char *)&Type + 1);
		sub_402806("Key2", (DWORD)&Type + 1, opt_Key2);
		word_516C64 = *(_WORD *)((char *)&Type + 1);
		sub_402806("Key3", (DWORD)&Type + 1, opt_Key3);
		word_516C66 = *(_WORD *)((char *)&Type + 1);
		sub_402806("Key4", (DWORD)&Type + 1, opt_Key4);
		word_516C68 = *(_WORD *)((char *)&Type + 1);
		sub_402806("Key5", (DWORD)&Type + 1, opt_Key5);
		word_516C6A = *(_WORD *)((char *)&Type + 1);
		sub_402806("Key6", (DWORD)&Type + 1, opt_Key6);
		word_516C6C = *(_WORD *)((char *)&Type + 1);
		sub_402806("Key7", (DWORD)&Type + 1, opt_Key7);
		word_516C6E = *(_WORD *)((char *)&Type + 1);
		sub_402806("Key8", (DWORD)&Type + 1, opt_Key8);
		word_516C70 = *(_WORD *)((char *)&Type + 1);
		sub_402806("Key9", (DWORD)&Type + 1, opt_Key9);
		word_516C72 = *(_WORD *)((char *)&Type + 1);
		sub_402806("Key10", (DWORD)&Type + 1, opt_Key10);
		word_516C74 = *(_WORD *)((char *)&Type + 1);
		sub_402806("Key11", (DWORD)&Type + 1, opt_Key11);
		word_516C76 = *(_WORD *)((char *)&Type + 1);
		sub_402806("Key12", (DWORD)&Type + 1, opt_Key12);
		word_516C78 = *(_WORD *)((char *)&Type + 1);
		sub_402806("Key13", (DWORD)&Type + 1, opt_Key13);
		word_516C7A = *(_WORD *)((char *)&Type + 1);
		sub_402806("Key14", (DWORD)&Type + 1, opt_Key14);
		word_516C7C = *(_WORD *)((char *)&Type + 1);
		sub_402806("Key15", (DWORD)&Type + 1, opt_Key15);
		word_516C7E = *(_WORD *)((char *)&Type + 1);
		sub_402806("Key16", (DWORD)&Type + 1, opt_Key16);
		word_516C80 = *(_WORD *)((char *)&Type + 1);
		sub_402806("Key17", (DWORD)&Type + 1, opt_Key17);
		word_516C82 = *(_WORD *)((char *)&Type + 1);
		sub_402806("JDck", (DWORD)&opt_JDck, 5);
		sub_402806("JDsh", (DWORD)&opt_JDsh, 3);
		sub_402806("JWlk", (DWORD)&opt_JWlk, 4);
		sub_402806("JJmp", (DWORD)&opt_JJmp, 0);
		sub_402806("JAct", (DWORD)&opt_JAct, 1);
		sub_402806("JDrw", (DWORD)&opt_JDrw, 2);
		sub_402806("JFlr", (DWORD)&opt_JFlr, 9);
		sub_402806("JLok", (DWORD)&opt_JLok, 6);
		sub_402806("JRol", (DWORD)&opt_JRol, 7);
		sub_402806("JInv", (DWORD)&opt_JInv, 8);
		sub_402806("MusicVolume", (DWORD)&opt_MusicVolume, 80);
		sub_402806("SFXVolume", (DWORD)&opt_SFXVolume, 90);
		sub_402806("ControlMethod", (DWORD)&opt_ControlMethod, 0);
		sub_402806("SoundQuality", (DWORD)&opt_SoundQuality, 1);
		sub_402806("AutoTarget", (DWORD)&opt_AutoTarget, 1);
		sub_402806("WindowX", (DWORD)&opt_WindowX, 0);
		sub_402806("WindowY", (DWORD)&opt_WindowY, 0);
		sub_402D10(v3, v2);
		result = opt_Setup;
	}
	else
	{
		result = 0;
	}
	return result;
}

char *__cdecl sub_401C9E(const char *a1, char *a2)
{
	const char *v2; // ebp@1
	char *v3; // esi@1
	unsigned int v4; // kr04_4@1
	char v5; // bl@3
	int v6; // ecx@4
	_BYTE *v7; // eax@4
	char *result; // eax@9
	int v9; // [sp+10h] [bp+4h]@2

	v2 = a1;
	v3 = a2;
	v4 = strlen(a1) + 1;
	if ((signed int)(v4 - 1) <= 0)
	{
		result = a2;
		*a2 = 0;
	}
	else
	{
		v9 = v4 - 1;
		do
		{
			v5 = *v2++;
			if (v5 >= 128)
			{
				v6 = 0;
				v7 = &unk_511894;
				while (v5 != *v7)
				{
					v7 += 2;
					++v6;
					if ((signed int)v7 >= (signed int)&unk_5118A2)
					{
						sub_4DEB10(1, "Reqd : %x", v5);
						goto LABEL_8;
					}
				}
				v5 = byte_511895[2 * v6];
			}
		LABEL_8:
			*v3++ = v5;
			--v9;
		} while (v9);
		result = a2;
		*v3 = 0;
	}
	return result;
}

signed int __stdcall DialogFunc(HWND hDlg, int msg, unsigned int wParam, int lParam)
{
	signed int result; // eax@11
	HWND v5; // eax@16
	HWND v6; // eax@16
	HWND v7; // esi@22
	HWND(__stdcall *v8)(HWND, int); // edi@22
	HWND v9; // eax@22
	HWND v10; // eax@25
	HWND v11; // ebx@28
	HWND v12; // esi@28
	HWND v13; // eax@32
	HWND v14; // eax@34
	HWND v15; // eax@36
	HWND v16; // eax@38
	HWND v17; // eax@40
	HGDIOBJ v18; // ST10_4@43
	HWND v19; // eax@43
	HGDIOBJ v20; // ST10_4@43
	HWND v21; // eax@43
	HGDIOBJ v22; // ST10_4@43
	HWND v23; // eax@43
	HGDIOBJ v24; // ST10_4@43
	HWND v25; // eax@43
	HGDIOBJ v26; // ST10_4@43
	HWND v27; // eax@43
	char *v28; // ST10_4@44
	HWND v29; // eax@44
	char *v30; // ST10_4@44
	HWND v31; // eax@44
	char *v32; // ST10_4@44
	HWND v33; // eax@44
	char *v34; // ST10_4@44
	HWND v35; // eax@44
	char *v36; // ST10_4@44
	HWND v37; // eax@44
	char *v38; // ST10_4@44
	HWND v39; // eax@44
	char *v40; // ST10_4@44
	HWND v41; // eax@44
	char *v42; // ST10_4@44
	HWND v43; // eax@44
	char *v44; // ST10_4@44
	HWND v45; // eax@44
	char *v46; // ST10_4@44
	HWND v47; // eax@44
	char *v48; // ST10_4@44
	HWND v49; // eax@44
	char *v50; // ST10_4@44
	HWND v51; // eax@44
	char *v52; // ST10_4@44
	HWND v53; // eax@44
	char *v54; // ST10_4@44
	HWND v55; // eax@44
	char *v56; // ST10_4@44
	HWND v57; // eax@44
	char *v58; // ST10_4@44
	HWND v59; // eax@44
	char *v60; // ST10_4@44
	HWND v61; // eax@44
	char *v62; // ST10_4@44
	HWND v63; // eax@44
	HWND v64; // eax@44
	HWND v65; // eax@44
	WPARAM v66; // [sp-8h] [bp-114h]@20
	char v67; // [sp-4h] [bp-110h]@22
	char v68; // [sp+Ch] [bp-100h]@44

	if (msg == 272)
	{
		sub_4DEB10(6, "WM_INITDIALOG");
		if ((*(_BYTE *)Gameflow & 0x70) == 96)
		{
			v18 = GetStockObject(13);
			gdiobject = v18;
			v19 = GetDlgItem(hDlg, 1000);
			SendMessageA(v19, 0x30u, 0, (LPARAM)v18);
			v20 = gdiobject;
			v21 = GetDlgItem(hDlg, 1003);
			SendMessageA(v21, 0x30u, 0, (LPARAM)v20);
			v22 = gdiobject;
			v23 = GetDlgItem(hDlg, 1004);
			SendMessageA(v23, 0x30u, 0, (LPARAM)v22);
			v24 = gdiobject;
			v25 = GetDlgItem(hDlg, 1006);
			SendMessageA(v25, 0x30u, 0, (LPARAM)v24);
			v26 = gdiobject;
			v27 = GetDlgItem(hDlg, 1005);
			SendMessageA(v27, 0x30u, 0, (LPARAM)v26);
		}
		v28 = sub_401C9E(&gfStringWad[gfStringOffset[266]], &v68);
		v29 = GetDlgItem(hDlg, 1001);
		SendMessageA(v29, 0xCu, 0, (LPARAM)v28);
		v30 = sub_401C9E(&gfStringWad[gfStringOffset[267]], &v68);
		v31 = GetDlgItem(hDlg, 1002);
		SendMessageA(v31, 0xCu, 0, (LPARAM)v30);
		v32 = sub_401C9E(&gfStringWad[gfStringOffset[270]], &v68);
		v33 = GetDlgItem(hDlg, 1);
		SendMessageA(v33, 0xCu, 0, (LPARAM)v32);
		v34 = sub_401C9E(&gfStringWad[gfStringOffset[271]], &v68);
		v35 = GetDlgItem(hDlg, 2);
		SendMessageA(v35, 0xCu, 0, (LPARAM)v34);
		v36 = sub_401C9E(&gfStringWad[gfStringOffset[268]], &v68);
		v37 = GetDlgItem(hDlg, 1009);
		SendMessageA(v37, 0xCu, 0, (LPARAM)v36);
		v38 = sub_401C9E(&gfStringWad[gfStringOffset[275]], &v68);
		v39 = GetDlgItem(hDlg, 1012);
		SendMessageA(v39, 0xCu, 0, (LPARAM)v38);
		v40 = sub_401C9E(&gfStringWad[gfStringOffset[276]], &v68);
		v41 = GetDlgItem(hDlg, 1016);
		SendMessageA(v41, 0xCu, 0, (LPARAM)v40);
		v42 = sub_401C9E(&gfStringWad[gfStringOffset[272]], &v68);
		v43 = GetDlgItem(hDlg, 1010);
		SendMessageA(v43, 0xCu, 0, (LPARAM)v42);
		v44 = sub_401C9E(&gfStringWad[gfStringOffset[273]], &v68);
		v45 = GetDlgItem(hDlg, 1011);
		SendMessageA(v45, 0xCu, 0, (LPARAM)v44);
		v46 = sub_401C9E(&gfStringWad[gfStringOffset[279]], &v68);
		v47 = GetDlgItem(hDlg, 1017);
		SendMessageA(v47, 0xCu, 0, (LPARAM)v46);
		v48 = sub_401C9E(&gfStringWad[gfStringOffset[280]], &v68);
		v49 = GetDlgItem(hDlg, 1018);
		SendMessageA(v49, 0xCu, 0, (LPARAM)v48);
		v50 = sub_401C9E(&gfStringWad[gfStringOffset[277]], &v68);
		v51 = GetDlgItem(hDlg, 1014);
		SendMessageA(v51, 0xCu, 0, (LPARAM)v50);
		v52 = sub_401C9E(&gfStringWad[gfStringOffset[278]], &v68);
		v53 = GetDlgItem(hDlg, 1015);
		SendMessageA(v53, 0xCu, 0, (LPARAM)v52);
		v54 = sub_401C9E(&gfStringWad[gfStringOffset[269]], &v68);
		v55 = GetDlgItem(hDlg, 1013);
		SendMessageA(v55, 0xCu, 0, (LPARAM)v54);
		v56 = sub_401C9E(&gfStringWad[gfStringOffset[283]], &v68);
		v57 = GetDlgItem(hDlg, 1025);
		SendMessageA(v57, 0xCu, 0, (LPARAM)v56);
		v58 = sub_401C9E(&gfStringWad[gfStringOffset[284]], &v68);
		v59 = GetDlgItem(hDlg, 1023);
		SendMessageA(v59, 0xCu, 0, (LPARAM)v58);
		v60 = sub_401C9E(&gfStringWad[gfStringOffset[274]], &v68);
		v61 = GetDlgItem(hDlg, 1029);
		SendMessageA(v61, 0xCu, 0, (LPARAM)v60);
		v62 = sub_401C9E(&gfStringWad[gfStringOffset[307]], &v68);
		v63 = GetDlgItem(hDlg, 1030);
		SendMessageA(v63, 0xCu, 0, (LPARAM)v62);
		v64 = GetDlgItem(hDlg, 1000);
		sub_4026FD(hDlg, v64);
		v65 = GetDlgItem(hDlg, 1005);
		sub_4018F2(hDlg, v65);
		return 1;
	}
	if (msg != 273)
		return 0;
	if ((signed int)(unsigned __int16)wParam > 1011)
	{
		switch ((unsigned __int16)wParam)
		{
		case 0x3FAu:
			if (wParam >> 16)
				return 0;
			v11 = GetDlgItem(hDlg, (unsigned __int16)wParam);
			v12 = GetDlgItem(hDlg, 1005);
			if (SendMessageA(v11, 0xF0u, 0, 0))
			{
				EnableWindow(v12, 0);
				result = 0;
			}
			else
			{
				EnableWindow(v12, 1);
				result = 0;
			}
			return result;
		case 0x3F6u:
			if (wParam >> 16)
				return 0;
			v7 = hDlg;
			v8 = GetDlgItem;
			v13 = GetDlgItem(hDlg, 1014);
			byte_57A09A = SendMessageA(v13, 0xF0u, 0, 0) != 0;
			break;
		case 0x3F8u:
			if (wParam >> 16)
				return 0;
			v7 = hDlg;
			v8 = GetDlgItem;
			v14 = GetDlgItem(hDlg, 1016);
			byte_57A09B = SendMessageA(v14, 0xF0u, 0, 0) != 0;
			break;
		case 0x405u:
			if (wParam >> 16)
				return 0;
			v7 = hDlg;
			v8 = GetDlgItem;
			v15 = GetDlgItem(hDlg, 1029);
			LOBYTE(dword_57A09C) = SendMessageA(v15, 0xF0u, 0, 0) != 0;
			break;
		case 0x3F4u:
			if (wParam >> 16)
				return 0;
			v7 = hDlg;
			v8 = GetDlgItem;
			v16 = GetDlgItem(hDlg, 1012);
			byte_511892 = SendMessageA(v16, 0xF0u, 0, 0) != 0;
			break;
		default:
			return 0;
		}
		v67 = 0;
		goto LABEL_40;
	}
	if ((unsigned __int16)wParam == 1011)
	{
		if (wParam >> 16)
			return 0;
		dword_57A084 = 0;
		v66 = 0;
		goto LABEL_25;
	}
	if ((signed int)(unsigned __int16)wParam > 1000)
	{
		if ((unsigned __int16)wParam == 1003)
		{
			if (wParam >> 16 != 1)
				return 0;
			v7 = hDlg;
			v8 = GetDlgItem;
			v9 = GetDlgItem(hDlg, 1003);
			dword_57A084 = SendMessageA(v9, 0x147u, 0, 0);
			v67 = 1;
		LABEL_40:
			v17 = v8(v7, 1004);
			sub_4017B7(v7, v17, v67);
			return 0;
		}
		if ((unsigned __int16)wParam != 1010 || wParam >> 16)
			return 0;
		dword_57A084 = 1;
		v66 = 1;
	LABEL_25:
		v7 = hDlg;
		v8 = GetDlgItem;
		v10 = GetDlgItem(hDlg, 1003);
		SendMessageA(v10, 0x14Eu, v66, 0);
		v67 = 1;
		goto LABEL_40;
	}
	if ((unsigned __int16)wParam == 1000)
	{
		if (wParam >> 16 == 1)
		{
			v5 = GetDlgItem(hDlg, 1000);
			dword_57A094 = SendMessageA(v5, 0x147u, 0, 0);
			v6 = GetDlgItem(hDlg, 1003);
			sub_40199C(hDlg, v6);
			return 0;
		}
		return 0;
	}
	if ((unsigned __int16)wParam != 1)
	{
		if ((unsigned __int16)wParam == 2)
		{
			if (gdiobject)
				DeleteObject(gdiobject);
			EndDialog(hDlg, 0);
			return 1;
		}
		return 0;
	}
	if (gdiobject)
		DeleteObject(gdiobject);
	sub_402DF1(hDlg);
	EndDialog(hDlg, 1);
	return 1;
}

BOOL  sub_402C34()
{
	INT_PTR v0; // esi@1
	BOOL result; // al@2

	ShowCursor(1);
	v0 = DialogBoxParamA(hinst, (LPCSTR)0x6D, 0, DialogFunc, 0);
	ShowCursor(0);
	if (v0 == -1)
	{
		MessageBoxA(0, "Unable To Initialise Dialog", Class, 0);
		result = 0;
	}
	else
	{
		result = v0 != 0;
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
	HWND desktopHwnd; // eax@25
	HWND v13; // esi@25
	HDC desktopDC; // eax@25
	HWND v15; // eax@25
	struct tagRECT Rect; // [sp+Ch] [bp-A4h]@8
	char v17[36]; // [sp+1Ch] [bp-94h]@25
	__int16 v18; // [sp+40h] [bp-70h]@25
	int v19; // [sp+44h] [bp-6Ch]@25
	int v20; // [sp+84h] [bp-2Ch]@25

	byte_57A098 = 0;
	byte_D9AC23 = sub_4D22D0() != 0;
	byte_D9AC19 = 0;
	opt_AutoTarget = 0;
	sub_4DEC40(1);
	v4 = FindWindowA(ClassName, WindowName);
	if (v4)
		PostMessageA(v4, Msg, 2u, 0);
	v5 = FindWindowA(ClassName, WindowName);
	if (v5)
		PostMessageA(v5, dword_E4ACAC, 0, 0);
	sub_4DEA50("Error", 255, 1);
	sub_4DEA50("Function", 0x8000, 0);
	sub_4DEA50("DirectX Information", 0x802040, 1);
	sub_4DEA50("Object Release", 128, 0);
	sub_4DEA50("General Information", 0x800000, 1);
	sub_4DEA50("Windows Message", 0x800080, 0);
	sub_4DEA50("Level Info", 0x8000FF, 0);
	sub_4DEA50("Sound", 32896, 0);
	sub_4DEB10(5, "Launching - %s", Name);
	sub_4DEB10(2, "WinMain");
	_CrtSetReportMode(0, 2);
	v6 = _CrtSetDbgFlag(-1);
	LOBYTE(v6) = v6 | 0x24;
	_CrtSetDbgFlag(v6);
	if (!(unsigned __int8)WinRunCheck(Name, "MainGameWindow", &hObject))
	{
		FindGameDrive();
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
		AdjustWindowRect(&Rect, WS_CAPTION, 0);
		v8 = CreateWindowExA(
			0x40000u,
			"MainGameWindow",
			Name,
			WS_CAPTION,
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
		DXInitialise(&dword_D9AB68, (int)v8);
		if (byte_57A098 || !(unsigned __int8)sub_402F77())
		{
			if (!(unsigned __int8)sub_402C34())
			{
				free(gfScriptFile);
				free(gfStringOffset);
				WinClose();
				return 0;
			}
			sub_402F77();
		}
		SetWindowPos(hWnd, 0, *(int *)&opt_WindowX, *(int *)&opt_WindowY, 0, 0, 5u);
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
		sub_402CD4(hWnd, hinst);
		hAccTable = LoadAcceleratorsA(hInstance, (LPCSTR)0x65);
		if (!opt_DisableSound)
		{
			DXDSCreate();
			InitACM();
		}
		dword_E916E0 = NULL;
		dword_876C40 = 1;
		dword_876C48 = 0;
		hThread = (HANDLE)_beginthreadex(0, 0, GameMain, 0, 0, &thread_id);
		WinProcMsg();
		dword_876C48 = 1;
		while (dword_876C40)
			;
		if (dword_E916E0)
			free(dword_E916E0);
		WinClose();
		desktopHwnd = GetDesktopWindow();
		v13 = desktopHwnd;
		desktopDC = GetDC(desktopHwnd);
		v18 = 148;
		v20 = dword_D9AC2C;
		ReleaseDC(v13, desktopDC);
		v19 = 0x40000;
		ChangeDisplaySettingsA((DEVMODEA *)&v17[0], 0);
		v15 = FindWindowA(ClassName, WindowName);
		if (v15)
			PostMessageA(v15, Msg, 4u, 0);
	}
	return 0;
}
