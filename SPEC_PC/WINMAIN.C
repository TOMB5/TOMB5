#undef __cplusplus
#define FORCE_NO_SOUND

#define DIRECTINPUT_VERSION 0x0700
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
#include <d3d.h>
#include "SOUND.H"
#include "resource.h"
#include <dinput.h>
#include "ERROR.H"
#include "MMREG.H"
#include "MSAcm.h"
#include "FILE.H"
#include "CONTROL.H"
#include "CD.H"
#pragma comment (lib, "Msacm32.lib")
#pragma comment (lib, "ddraw.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "dsound.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "dinput.lib")


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

BYTE byte_D9AC2B;
DWORD dword_D9ABFD;
uint32 dword_D9ABF9;
HWND dword_86B9A4;



unsigned thread_id;
DWORD dword_D9ABDD;
void* dword_E916E0;
DWORD dword_876C40;
DWORD dword_D9AC2C;

HKEY hKey;
LPSTR Class;
DWORD dwDisposition;

BYTE opt_BumpMap;
BYTE opt_Filter;
BYTE opt_DisableSound;
BYTE opt_Volumetric;
BYTE opt_NoFMV;
BYTE opt_Setup;

DWORD dword_D9AC1B;
DWORD dword_D9AC1F;
DWORD dword_D9AC27;

WORD opt_Keys[18] =
{
	0x00C8, 0x00D0, 0x00CB, 0x00CD, 0x0034, 0x0035, 0x0036, 0x00B8, 0x009D, 0x0039, 
	0x0033, 0x0052, 0x00CF, 0x0001, 0x00D3, 0x00D1, 0x0019, 0x001C
};

WORD opt_Keys2[18] =
{
	0x00C8, 0x00D0, 0x00CB, 0x00CD, 0x0034, 0x0035, 0x0036, 0x00B8, 0x009D, 0x0039,
	0x0033, 0x0052, 0x00CF, 0x0001, 0x00D3, 0x00D1, 0x0019, 0x001C
};

DWORD dword_878C4C[18] = { 0 };

DWORD opt_JDck = 5;
DWORD opt_JDsh = 3;
DWORD opt_JWlk = 4;
DWORD opt_JJmp = 0;
DWORD opt_JAct = 1;
DWORD opt_JDrw = 2;
DWORD opt_JFlr = 9;
DWORD opt_JLok = 6;
DWORD opt_JRol = 7;
DWORD opt_JInv = 8;

DWORD opt_MusicVolume = 40;
DWORD opt_SFXVolume = 80;
DWORD opt_ControlMethod;
DWORD opt_SoundQuality = 1;
DWORD opt_AutoTarget;

HGDIOBJ gdiobject;

DWORD opt_GraphicsAdapter;
DWORD opt_AccelAdapter;

BYTE byte_511894[] =
{
	0x82, 0xE9, 0x8A, 0xE8, 0x88, 0xEA, 0x94, 0xF6, 0x85, 0xE0, 0xA0, 0xE1, 0xA2, 0xF3
};

BYTE unk_5118A2[5] = { 0 };
DWORD dword_57A08C;
BYTE opt_LowQualityTextures;
BYTE opt_LowQualityBumpMap;
DWORD opt_VolumetricFog;
BYTE opt_BilinearFiltering;
DWORD BumpBitCount;
DWORD BumpDU;
DWORD BumpDV;

DWORD NumSamples[] = { 11025, 22050, 44100 };
DWORD dword_86CC7C;
LPDIRECTSOUNDBUFFER DSSoundBuffer;

struct _RTL_CRITICAL_SECTION CriticalSection;
BYTE ACMInited;
HACMDRIVERID hadid;
HACMDRIVER had;
BYTE* bufSource;
void* ptr;
WAVEFORMATEX pwfxDst;
WAVEFORMATEX pwfxSrc = { WAVE_FORMAT_ADPCM, 2, 44100, 44359, 2048, 4, 0x20 };
DWORD bufLockLength;
LPDIRECTSOUNDBUFFER other_buf;
LPDIRECTSOUNDNOTIFY notify_thing;
DWORD bufMaxLength;
HACMSTREAM has;
BYTE* buf_lockAudioPtr1;
DWORD buf_lockAudioBytes1;
DWORD pdwOutputBytes;
ACMSTREAMHEADER acmHeader1;
ACMSTREAMHEADER acmHeader2;
ACMSTREAMHEADER acmHeader3;
ACMSTREAMHEADER acmHeader4;



DWORD dword_D9AB74;
DWORD dword_57A088;
DWORD dword_57A090;

DWORD dword_D99D7C;
DWORD dword_D99DA4;

BYTE unk_D99D80[12];

BYTE byte_86BB8C[256];
BYTE unk_86BC8C[256];
WORD word_86B9B0[32];

DWORD dword_86BA48;

HANDLE Handles;
HANDLE dword_579FA4;
HANDLE dword_579FA8;

int XATrack = -1;
void* dword_579FD4;
BYTE byte_579FE4;
DWORD dword_579FD8;
DWORD dword_579E4C;
BYTE byte_57A01C;
FILE* stream;
DWORD dword_579E30;
DWORD dword_57A018;
DWORD dword_510B18 = 7;

//DEFINE_GUID(IID_IDirect3D3, 0xBB223240, 0xE72B, 0x11D0, 0xA9, 0xB4, 0x00, 0xAA, 0x00, 0xC0, 0x99, 0x3E);

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
			SendMessageA(v3, WM_ACTIVATE, 0, 0);
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
	setbuf(stdout, NULL);

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
	result = ptr_crctx;
	if (ptr_crctx)
	{
		if (!(ptr_crctx->flags & 1))
			result = SetRect(
			&ptr_crctx->windowPos,
				xLeft,
				yTop,
				xLeft + ptr_crctx->width,
				yTop + ptr_crctx->height);
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


BOOL __stdcall sub_401FE6(LPCDIDEVICEINSTANCEA a1, LPVOID a2)
{
	return ptr_crctx->dinput->lpVtbl->CreateDeviceEx(
		ptr_crctx->dinput,
		&a1->guidInstance,
		&IID_IDirectInputDevice2A,
		&ptr_crctx->dinput_other,
		0) < 0;
}

int __cdecl DXDDCreate(GUID *lpGUID, LPDIRECTDRAW4* a2)
{
	HRESULT v3; // eax@1
	int v4; // eax@2
	int v5; // eax@3
	int result; // eax@5
	LPDIRECTDRAW lpDD; // [sp+10h] [bp-4h]@1

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

		sub_40179E(v4);
		if (lpDD)
		{
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

signed long __stdcall sub_401CBC(LPDDSURFACEDESC2 a1, int a2__)
{
	int v2; // esi@1
	struct dispmode *v3; // eax@1
	struct dispmode* v4; // ebx@1
	int v5; // edx@1
	struct gfxadapt* a2 = (struct gfxadapt*)a2__;
	v2 = a2->numDispModes;
	v3 = (struct dispmode*)sub_401A7D(*(void **)&a2->displayModes, a2->numDispModes, 150);
	a2->displayModes = v3;
	v4 = &v3[v2];
	v4->width = a1->dwWidth;
	v4->height = a1->dwHeight;
	v4->depth = a1->ddpfPixelFormat.dwRGBBitCount;
	v5 = (a1->ddpfPixelFormat.dwFlags >> 5) & 1;
	v4->isIndexed8 = v5;
	v4->mipMapCount = a1->dwMipMapCount;
	qmemcpy(&v4->surfaceDesc, (const void *)a1, 124);
	if (v5)
	{
		sub_4DEB10(3, "%d x %d - %d Bit - Palette", v4->width, v4->height, v4->depth);
	}
	else
	{
		sub_4016B3(a1->ddpfPixelFormat.dwRBitMask, &v4->offsetR, &v4->bitsR);
		sub_4016B3(a1->ddpfPixelFormat.dwGBitMask, &v4->offsetG, &v4->bitsG);
		sub_4016B3(a1->ddpfPixelFormat.dwBBitMask, &v4->offsetB, &v4->bitsB);
		sub_4DEB10(
			3,
			"%d x %d - %d Bit - %d%d%d",
			v4->width,
			v4->height,
			v4->depth,
			v4->bitsR,
			v4->bitsG,
			v4->bitsB);
	}
	++a2->numDispModes;
	return 1;
}

signed int __cdecl DXD3DCreate(LPDIRECTDRAW4 a1, IDirect3D3** a2)
{
	int v2; // eax@1
	signed int result; // eax@2

	sub_4DEB10(2, "DXD3DCreate");
	v2 = a1->lpVtbl->QueryInterface(a1, &IID_IDirect3D3, a2);
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
	return result;
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

BOOL __cdecl DXSetCooperativeLevel(LPDIRECTDRAW4 a1, HWND a2, int a3)
{
	static const char* flags[] = 
	{
		"fullscreen",		  //    1
		"allowreboot",		  //    2
		"nowindowchanges",	  //    4
		"normal",			  //    8
		"exclusive",		  //   16
		"",					  //   32
		"allowmodex",		  //   64
		"setfocuswindow",	  //  128
		"setdevicewindow",	  //  256
		"createdevicewindow", //  512
		"multithreaded",	  // 1024
		"fpusetup",			  // 2048
	};

	char v120[1024];
	strcpy(v120, "DXSetCooperativeLevel - ");

	for (int i = 0; i < 12; i++)
	{
		if (a3 & (1 << i))
		{
			strcat(v120, flags[i]);
			strcat(v120, " ");
		}
	}

	sub_4DEB10(2, v120);
	int v7 = a1->lpVtbl->SetCooperativeLevel(a1, a2, a3);
	return sub_40179E(v7) == 0;
}

signed int __cdecl DXCreateSurface(LPDIRECTDRAW4 a1, LPDDSURFACEDESC2 a2, LPDIRECTDRAWSURFACE4* a3)
{
	int v3; // eax@1
	signed int result; // eax@2

	sub_4DEB10(2, "DXCreateSurface");
	v3 = a1->lpVtbl->CreateSurface(a1, a2, a3, 0);
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

signed int __cdecl DXCreateD3DDevice(LPDIRECT3D3 a1, const IID a2, LPDIRECTDRAWSURFACE4 a6, LPDIRECT3DDEVICE3* a7)
{
	int v7; // eax@1
	signed int result; // eax@2

	sub_4DEB10(2, "DXCreateD3DDevice");
	v7 = a1->lpVtbl->CreateDevice(a1, &a2, a6, a7, 0);
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

BOOL __cdecl DXSetVideoMode(LPDIRECTDRAW4 a1, int a2, int a3, int a4)
{
	int v4; // eax@1
#if DEBUG
	a2 = 1680;
	a3 = 1050;
	a4 = 32;
#endif
	sub_4DEB10(2, "DXSetVideoMode");
	sub_4DEB10(5, "SetDisplayMode - %dx%dx%d", a2, a3, a4);
	v4 = a1->lpVtbl->SetDisplayMode(a1, a2, a3, a4, 0, 0);
	return sub_40179E(v4) == 0;
}

signed int __stdcall sub_401019(LPDDPIXELFORMAT a1, LPVOID a2__)
{
	int v2; // eax@1
	int v3; // esi@3
	struct acceltexformatinfo *v4; // eax@3
	struct acceltexformatinfo *v5; // ebp@3
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
	struct acceladapt* a2 = (struct accelaadapt*)a2__;
	v2 = a1->dwFlags;
	if (v2 & 1 && v2 & 0x40)
	{
		v3 = a2->numTexFormats;
		v4 = (struct acceltexformatinfo*)sub_401A7D(*(void **)&a2->texFormats, a2->numTexFormats, 0x34u);
		a2->texFormats = v4;
		v5 = &v4[v3];
		qmemcpy(&v4[v3], a1, 0x20u);
		v6 = a1->dwFlags;
		if (v6 & 0x20)
		{
			v5->field1 = 1;
			v5->depth = 8;
			sub_4DEB10(3, "8 Bit");
		}
		else if (v6 & 8)
		{
			v5->field1 = 1;
			v5->depth = 4;
			sub_4DEB10(3, "4 Bit");
		}
		else
		{
			v5->field1 = 0;
			v5->depth = a1->dwRGBBitCount;
			v7 = a1->dwFlags;
			if (v7 & 0x40)
			{
				if (v7 & 1)
				{
					sub_4016B3(a1->dwRBitMask, &v5->offsetR, &v5->bitsR);
					sub_4016B3(a1->dwGBitMask, &v5->offsetG, &v5->bitsG);
					sub_4016B3(a1->dwBBitMask, &v5->offsetB, &v5->bitsB);
					sub_4016B3(a1->dwRGBAlphaBitMask, &v5->offsetA, &v5->bitsA);
					v9 = v5->bitsA;
					v10 = v5->bitsB;
					v11 = v5->bitsG;
					v12 = v5->bitsR;
					v13 = v5->depth;
					v5->field2 = 1;
					sub_4DEB10(3, "%d Bit %d%d%d%d RGBA", v13, v12, v11, v10, v9);
				}
				else
				{
					sub_4016B3(a1->dwRBitMask, &v5->offsetR, &v5->bitsR);
					sub_4016B3(a1->dwGBitMask, &v5->offsetG, &v5->bitsG);
					sub_4016B3(a1->dwBBitMask, &v5->offsetB, &v5->bitsB);
					sub_4DEB10(3, "%d Bit %d%d%d RGB", v5->depth, v5->bitsR, v5->bitsG, v5->bitsB);
				}
			}
		}
		++a2->numTexFormats;
		result = 1;
	}
	else
	{
		result = 1;
	}
	return result;
}

signed int __stdcall sub_402FDB(LPDDPIXELFORMAT a1, struct acceladapt* a2)
{
	int v2; // esi@1
	struct zBufFormat*v3; // eax@1
	struct zBufFormat* v4; // eax@1
	int v5; // ST08_4@1

	v2 = a2->numZbufFormats;
	v3 = (struct zBufFormat*)sub_401A7D(*(void **)&a2->zBufFormats, a2->numZbufFormats, 36);
	a2->zBufFormats = v3;
	v4 = &v3[v2];
	qmemcpy((void *)v4, (const void *)a1, 32);
	v5 = a1->dwRGBBitCount;
	v4->depth = v5;
	sub_4DEB10(3, "%d Bit", v5);
	++a2->numZbufFormats;
	return 1;
}

signed long __stdcall sub_402ECD(GUID* a1, CHAR *devDesc, CHAR *devName, LPD3DDEVICEDESC a4, LPD3DDEVICEDESC a5, void* a6__)
{
	int v6; // esi@1
	struct acceladapt *v7; // eax@1
	struct acceladapt * v8; // ebp@1
	GUID* v9; // ecx@3
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
	struct gfxadapt* v20; // edi@11
	struct dispmode *v21; // eax@12
	int v22; // ecx@12
	struct dispmode *v23; // eax@12
	int v24; // ecx@16
	int v25; // eax@20
	LPDIRECTDRAWSURFACE4 v26; // eax@22
	int v27; // eax@25
	int v28; // eax@26
	int v29; // eax@30
	int v30; // eax@32
	LPDIRECTDRAWSURFACE4 v32; // [sp+10h] [bp-88h]@17
	LPDIRECT3DDEVICE3 v33; // [sp+14h] [bp-84h]@18
	int v34; // [sp+18h] [bp-80h]@10
	DDSURFACEDESC2 v35; // [sp+1Ch] [bp-7Ch]@17
	struct gfxadapt* a6 = (struct gfxadapt*)a6__;
	v6 = a6->numAccelAdapters;
	v7 = (struct acceladapt*)sub_401A7D(*(void **)&a6->accelAdapters, a6->numAccelAdapters, 410);
	a6->accelAdapters = v7;
	v8 = &v7[v6];
	if (a1)
	{
		v9 = &v8->guid;
		v8->field1 = &v8->guid;
		v8->guid = *a1;
	}
	else
	{
		v8->field1 = 0;
	}
	v10 = v8->description;
	lstrcpyA(v8->description, devDesc);
	lstrcpyA(v8->name, devName);
	sub_4DEB10(5, "Found - %s", devDesc);
	if (a4->dwFlags)
	{
		v8->field2 = 1;
		qmemcpy(&v8->deviceDesc, a4, 0xFCu);
	}
	else
	{
		v8->field2 = 0;
		qmemcpy(&v8->deviceDesc, a5, 0xFCu);
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
	v8->numDispModes = 0;
	v19 = a6->numDispModes;
	v34 = 0;
	if (v19 > 0)
	{
		do
		{
			v20 = a6;
			if (sub_40206D(a6->displayModes[v18].depth) & v8->deviceDesc.dwDeviceRenderBitDepth)
			{
				v21 = (struct dispmode*)sub_401A7D(*(void **)&v8->displayModes, v8->numDispModes, 150);
				v22 = v8->numDispModes;
				v8->displayModes = v21;
				v23 = &v21[v22];
				qmemcpy(v23, &a6->displayModes[v18], 0x96u);
				if (v23->isIndexed8)
					sub_4DEB10(3, "%d x %d - %d Bit - Palette", v23->width, v23->height, v23->depth);
				else
					sub_4DEB10(
						3,
						"%d x %d - %d Bit - %d%d%d",
						v23->width,
						v23->height,
						v23->depth,
						v23->bitsR,
						v23->bitsG,
						v23->bitsB);
				v20 = a6;
				++v8->numDispModes;
			}
			v24 = v20->numDispModes;
			v18++;
			++v34;
		} while (v34 < v24);
	}
	sub_4DEB10(5, "Enumerate Texture Formats");
	memset(&v35, 0, 0x7Cu);
	v35.dwSize = 124;
	v35.dwFlags = 1;
	v35.ddsCaps.dwCaps = 8704;
	DXSetCooperativeLevel(iface_DirectDraw, dword_86B9A4, 21);
	DXCreateSurface(iface_DirectDraw, &v35, &v32);
	if (v32)
	{
		DXCreateD3DDevice(
			iface_D3D3,
			v8->guid,
			v32,
			&v33);
		if (v33)
			goto LABEL_35;
		sub_4DEB10(1, "Create D3DDevice Failed");
		if (v32)
		{
			v25 = v32->lpVtbl->Release(v32);
			sub_4DEB10(4, "Released %s @ %x - RefCnt = %d", "DirectDrawSurface", v32, v25);
			v32 = 0;
		}
		else
		{
			sub_4DEB10(1, "%s Attempt To Release NULL Ptr", "DirectDrawSurface");
		}
		DXSetVideoMode(
			iface_DirectDraw,
			v8->displayModes->width,
			v8->displayModes->height,
			v8->displayModes->depth);
		DXCreateSurface(iface_DirectDraw, &v35, &v32);
		v26 = v32;
		if (v32)
		{
			DXCreateD3DDevice(
				iface_D3D3,
				v8->guid,
				v32,
				&v33);
			v26 = v32;
		}
		if (v33)
		{
		LABEL_35:
			v8->numTexFormats = 0;
			sub_4DEB10(2, "DXEnumTextureFormats");
			v27 = v33->lpVtbl->EnumTextureFormats(v33, &sub_401019, v8);
			sub_40179E(v27);
			if (v33)
			{
				v28 = v33->lpVtbl->Release(v33);
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
			v29 = v26->lpVtbl->Release(v26);
			sub_4DEB10(4, "Released %s @ %x - RefCnt = %d", "DirectDrawSurface", v32, v29);
			v32 = 0;
		}
		else
		{
			sub_4DEB10(1, "%s Attempt To Release NULL Ptr", "DirectDrawSurface");
		}
	}
	DXSetCooperativeLevel(iface_DirectDraw, dword_86B9A4, 8);
	sub_4DEB10(5, "Enumerating ZBuffer Formats");
	sub_4DEB10(2, "DXEnumZBufferFormats");
	v30 = iface_D3D3->lpVtbl->EnumZBufferFormats(
		iface_D3D3,
		&v8->guid,
		sub_402FDB,
		v8);
	sub_40179E(v30);
	++a6->numAccelAdapters;
	return 1;
}

signed int __stdcall DXEnumDirectDraw(GUID *lpGUID, LPSTR DriverDescription, LPSTR DriverName, LPVOID Context__)
{
	int v4; // esi@1
	struct gfxadapt* v5; // eax@1
	struct gfxadapt* v6; // esi@1
	char* v7; // eax@3
	int v8; // eax@5
	int v9; // eax@5
	int v10; // eax@5
	int v11; // eax@6
	int v12; // eax@7
	int v13; // eax@10
	struct dxcontext_s* Context = (struct dxcontext_s*)Context__;
	sub_4DEB10(2, "DXEnumDirectDraw");
	v4 = Context->numGraphicsAdapters;
	v5 = (struct gfxadapt*)sub_401A7D(*(void **)&Context->graphicsAdapters, Context->numGraphicsAdapters, 1590);
	Context->graphicsAdapters = v5;
	v6 = &v5[v4];
	if (lpGUID)
	{
		v6->field3 = &v6->guid;
		v6->guid = *lpGUID;
	}
	else
	{
		v6->field3 = 0;
	}
	lstrcpyA(v6->driverDesc, DriverDescription);
	lstrcpyA(v6->driverName, DriverName);
	sub_4DEB10(5, "Obtaining Information For %s", DriverDescription);
	if (DXDDCreate(lpGUID, &iface_DirectDraw))
	{
		v8 = iface_DirectDraw->lpVtbl->GetDeviceIdentifier(
			iface_DirectDraw,
			v6->driverDllName,
			0);
		sub_40179E(v8);
		sub_4DEB10(
			5,
			"Found - %s\r\nDriver %s Version %d.%d.%d.%d",
			v6->deviceName,
			v6->driverDllName,
			v6->versionMajor,
			v6->versionMinor,
			v6->versionBuild,
			v6->versionRevision);
		memset(&v6->capabilities, 0, 380);
		v6->capabilities.dwSize = 380;
		sub_4DEB10(5, "Getting Device Capabilities");
		v9 = iface_DirectDraw->lpVtbl->GetCaps(
			iface_DirectDraw,
			&v6->capabilities,
			0);
		sub_40179E(v9);
		sub_4DEB10(5, "Enumerating Display Modes");
		DXSetCooperativeLevel(iface_DirectDraw, 0, 77);
		sub_4DEB10(2, "DXEnumDisplayModes");
		v10 = iface_DirectDraw->lpVtbl->EnumDisplayModes(
			iface_DirectDraw,
			0,
			0,
			v6,
			&sub_401CBC);
		sub_40179E(v10);
		if (DXD3DCreate(iface_DirectDraw, &iface_D3D3))
		{
			sub_4DEB10(2, "DXEnumDirect3D");
			v11 = iface_D3D3->lpVtbl->EnumDevices(iface_D3D3, &sub_402ECD, v6);
			sub_40179E(v11);
			if (iface_D3D3)
			{
				v12 = iface_D3D3->lpVtbl->Release(iface_D3D3);
				sub_4DEB10(4, "Released %s @ %x - RefCnt = %d", "Direct3D", iface_D3D3, v12);
				iface_D3D3 = 0;
			}
			else
			{
				sub_4DEB10(1, "%s Attempt To Release NULL Ptr", "Direct3D");
			}
		}
		DXSetCooperativeLevel(iface_DirectDraw, 0, 8);
		if (iface_DirectDraw)
		{
			v13 = iface_DirectDraw->lpVtbl->Release(iface_DirectDraw);
			sub_4DEB10(4, "Released %s @ %x - RefCnt = %d", "DirectDraw", iface_DirectDraw, v13);
			iface_DirectDraw = 0;
			++Context->numGraphicsAdapters;
			return 1;
		}
		sub_4DEB10(1, "%s Attempt To Release NULL Ptr", "DirectDraw");
	}
	++Context->numGraphicsAdapters;
	return 1;
}

signed int __stdcall DXEnumDirectSound(GUID* a1, CHAR *devDesc, CHAR *devName, int a4__)
{
	int v4; // edi@1
	struct soundcard *v5; // eax@1
	struct soundcard* v6; // edi@1
	int v7; // eax@3
	struct dxcontext_s* a4 = (struct dxcontext_s*)a4__;
	sub_4DEB10(2, "DXEnumDirectSound");
	v4 = a4->numSoundCards;
	v5 = (struct soundcard*)sub_401A7D(*(void **)&a4->soundCards, a4->numSoundCards, 0x82u);
	a4->soundCards = v5;
	v6 = &v5[v4];
	if (a1)
	{
		v6->field1 = &v6->guid;
		v6->guid = *a1;
	}
	else
	{
		v6->field1 = 0;
	}
	lstrcpyA(v6->description, devDesc);
	lstrcpyA(v6->name, devName);
	sub_4DEB10(5, "Found - %s %s", v6->description, v6->name);
	++a4->numSoundCards;
	return 1;
}

signed int __cdecl DXInitialise(void *lpContext, HWND hwnd)
{
	HRESULT v2; // eax@1
	HRESULT v3; // eax@1

	sub_4DEB10(2, "DXInitialise");
	dword_86B9A4 = hwnd;
	sub_4DEB10(5, "Enumerating DirectDraw Devices");
	v2 = DirectDrawEnumerateA(DXEnumDirectDraw, lpContext);
	sub_40179E(v2);
	v3 = DirectSoundEnumerateA(DXEnumDirectSound, lpContext);
	sub_40179E(v3);
	ptr_ctx = (struct dxcontext_s*)lpContext;
	return 1;
}

BOOL __stdcall sub_402E3C(LPCDIDEVICEOBJECTINSTANCEA a1, LPVOID a2)
{
	int v2; // ecx@1
	DIPROPHEADER v4; // [sp+0h] [bp-18h]@1
	int v5; // [sp+10h] [bp-8h]@1
	int v6; // [sp+14h] [bp-4h]@1

	v4.dwSize = 24;
	v4.dwHeaderSize = 16;
	v2 = a1->dwOfs;
	v4.dwHow = 1;
	v4.dwObj = v2;
	v5 = -1000;
	v6 = 1000;
	return ptr_crctx->dinput_other->lpVtbl->SetProperty(
		ptr_crctx->dinput_other,
		4,
		&v4) >= 0;
}

int sub_402CD4(HWND hWnd, HINSTANCE hInstance)
{
	int v2; // eax@1
	int v3; // eax@2
	int v4; // eax@4
	int v5; // eax@5
	int v6; // eax@7
	int v7; // eax@7
	int v8; // eax@7
	int v9; // eax@7
	LPDIRECTINPUTDEVICEA result; // eax@7
	int v11; // eax@8
	int v12; // eax@8
	int v13; // eax@8
	LPDIRECTINPUTDEVICEA v14; // [sp+64h] [bp-30h]@4
	DIDEVCAPS v15; // [sp+68h] [bp-2Ch]@8
	LPDIRECTINPUTA hinst;
	v2 = DirectInputCreateA(hInstance, 0x700u, &hinst, 0);
	sub_40179E(v2);
	hinst->lpVtbl->QueryInterface(hinst, &IID_IDirectInput2A, &ptr_crctx->dinput);
	if (hinst)
	{
		v3 = hinst->lpVtbl->Release(hinst);
		sub_4DEB10(4, "Released %s @ %x - RefCnt = %d", "DirectInput", hinst, v3);
		hinst = 0;
	}
	else
	{
		sub_4DEB10(1, "%s Attempt To Release NULL Ptr", "DirectInput");
	}
	v4 = ptr_crctx->dinput->lpVtbl->CreateDevice(
		ptr_crctx->dinput,
		&GUID_SysKeyboard,
		&v14,
		0);
	sub_40179E(v4);
	v14->lpVtbl->QueryInterface(v14, &IID_IDirectInputDevice2A, &ptr_crctx->dinput_keyboard);
	if (v14)
	{
		v5 = v14->lpVtbl->Release(v14);
		sub_4DEB10(4, "Released %s @ %x - RefCnt = %d", "Keyboard", v14, v5);
		v14 = 0;
	}
	else
	{
		sub_4DEB10(1, "%s Attempt To Release NULL Ptr", "Keyboard");
	}
	v6 = ptr_crctx->dinput_keyboard->lpVtbl->SetCooperativeLevel(
		ptr_crctx->dinput_keyboard,
		hWnd,
		10);
	sub_40211C(v6);
	v7 = ptr_crctx->dinput_keyboard->lpVtbl->SetDataFormat(
		ptr_crctx->dinput_keyboard,
		&c_dfDIKeyboard);
	sub_40211C(v7);
	v8 = ptr_crctx->dinput_keyboard->lpVtbl->Acquire(ptr_crctx->dinput_keyboard);
	sub_40211C(v8);
	memset(byte_86BB8C, 0, 0x100u);
	memset(&unk_86BC8C[0], 0, 0x100u);
	dword_86BA48 = 0;
	memset(&word_86B9B0[0], 0, 0x40u);
	v9 = ptr_crctx->dinput->lpVtbl->EnumDevices(
		ptr_crctx->dinput,
			4,
			sub_401FE6,
			0,
			1);
	sub_40211C(v9);
	result = ptr_crctx->dinput_other;
	if (result)
	{
		v11 = result->lpVtbl->SetDataFormat(result, &c_dfDIJoystick);
		sub_40211C(v11);
		v12 = ptr_crctx->dinput_other->lpVtbl->SetCooperativeLevel(
			ptr_crctx->dinput_other,
			hWnd,
			5);
		sub_40211C(v12);
		v15.dwSize = 44;
		ptr_crctx->dinput_other->lpVtbl->GetCapabilities(ptr_crctx->dinput_other, &v15);
		ptr_crctx->dinput_other->lpVtbl->EnumObjects(
			ptr_crctx->dinput_other,
			sub_402E3C,
			hWnd,
			3);
		v13 = ptr_crctx->dinput_other->lpVtbl->Acquire(ptr_crctx->dinput_other);
		result = sub_40211C(v13);
	}
	return result;

	S_Warn("[sub_402CD4] - Unimplemented!\n");
	return 1;
}

char __cdecl SetSoundOutputFormat(int a1, char a2)
{
	int v2; // eax@4
	char result; // al@5
	WAVEFORMATEX v4; // [sp+4h] [bp-14h]@3

	if ((a2 || dword_86CC7C != a1)
		&& (dword_86CC7C = a1,
			v4.wFormatTag = 1,
			v4.nChannels = 2,
			v4.nSamplesPerSec = a1,
			v4.nAvgBytesPerSec = 4 * a1,
			v4.nBlockAlign = 4,
			v4.wBitsPerSample = 16,
			v4.cbSize = 0,
			S_SoundStopAllSamples(),
			DSSoundBuffer)
		&& (v2 = DSSoundBuffer->lpVtbl->SetFormat(DSSoundBuffer, &v4), sub_40179E(v2)))
	{
		sub_4DEB10(1, "Can't set sound output format to %d", v4.nSamplesPerSec);
		result = 0;
	}
	else
	{
		result = 1;
	}
	return result;
}

char DXSetOutputFormat()
{
	int v0; // eax@1
	char result; // al@2
	DSBUFFERDESC v2; // [sp+4h] [bp-24h]@1


	sub_4DEB10(2, "DXSetOutputFormat");
	memset(&v2, 0, 0x24u);
	v2.dwSize = 36;
	v2.dwFlags = 1;
	v0 = dxctx.dsound->lpVtbl->CreateSoundBuffer(dxctx.dsound, &v2, &DSSoundBuffer, 0);
	if (sub_40179E(v0))
	{
		sub_4DEB10(1, "Can't Get Primary Sound Buffer");
		result = 0;
	}
	else
	{
		SetSoundOutputFormat(NumSamples[opt_SoundQuality], 0);
		DSSoundBuffer->lpVtbl->Play(DSSoundBuffer, 0, 0, 1);
		result = 1;
	}
	return result;
}

int DXDSCreate()
{
	int v0; // eax@1
	int v1; // eax@1
	signed int result; // eax@1

	sub_4DEB10(2, "DXDSCreate");
	v0 = DirectSoundCreate(
		ptr_ctx->soundCards[ptr_ctx->curSoundCard].field1,
		&dxctx.dsound,
		0);
	sub_40179E(v0);
	v1 = dxctx.dsound->lpVtbl->SetCooperativeLevel(dxctx.dsound, hWnd, 3);
	sub_40179E(v1);
	DXSetOutputFormat();
	result = 1;
	sound_active = 1;
	return result;
}

int __stdcall fnCallback(HACMDRIVERID arghadid, int a2, int a3)
{
	int result; // eax@2
	struct tACMDRIVERDETAILSA padd; // [sp+Ch] [bp-398h]@1

	memset(&padd, 0, sizeof(padd));
	padd.cbStruct = 920;
	acmDriverDetailsA(arghadid, &padd, 0);
	if (!strcmp(padd.szShortName, "MS-ADPCM"))
	{
		hadid = arghadid;
		result = 0;
	}
	else
	{
		result = 1;
	}
	return result;
}

char sub_402E5A()
{
	char result; // al@1

	result = ACMInited;
	if (ACMInited)
	{
		result = (char)stream;
		if (stream)
		{
			memset(ptr, 0, 0x37000u);
			other_buf->lpVtbl->Stop(other_buf);
			other_buf->lpVtbl->SetCurrentPosition(other_buf, 0);
			while (byte_57A01C)
				;
			result = fclose(stream);
			stream = 0;
			dword_57A018 = 0;
			dword_510B18 = 7;
			XATrack = -1;
		}
	}
	return result;
}

void __cdecl sub_4027DE(void *a1, int a2)
{
	byte_57A01C = 1;
	EnterCriticalSection(&CriticalSection);
	LeaveCriticalSection(&CriticalSection);
	if (!stream)
		goto LABEL_17;
	if (a2 != XATrack || a2 == -1)
	{
		sub_4DEB10(0, "Not Current Track %d", a2);
		goto LABEL_17;
	}
	memset(a1, 0, 0x5800u);
	if (!stream)
	{
	LABEL_17:
		byte_57A01C = 0;
		byte_579FE4 = 0;
		return;
	}
	fread_ex(a1, 1u, 0x5800u, stream);
	if (!stream /*|| !(stream->_flag & 0x10)*/) // TODO MAY BREAK
		goto LABEL_9;
	if (dword_579E30 == 1)
	{
		fseek(stream, 90, 0);
	LABEL_9:
		byte_57A01C = 0;
		byte_579FE4 = 1;
		return;
	}
	if (++dword_57A018 <= 8)
		goto LABEL_9;
	dword_57A018 = 0;
	if (dword_579E30 == 2)
	{
		byte_57A01C = 0;
		byte_579FE4 = 0;
		sub_402E5A();
	}
	else
	{
		if (!CurrentAtmosphere || IsAtmospherePlaying)
			goto LABEL_9;
		byte_57A01C = 0;
		byte_579FE4 = 0;
		sub_402E5A();
		S_CDPlay((unsigned __int8)CurrentAtmosphere, 1);
	}
}

int StartAddress()
{
	DWORD i; // esi@1
	int v1; // eax@10
	DWORD v3; // [sp+34h] [bp-8h]@10
	void* v4; // [sp+38h] [bp-4h]@10

	for (i = WaitForMultipleObjects(2u, &Handles, 0, 0xFFFFFFFF);
		i != -1;
		i = WaitForMultipleObjects(2u, &Handles, 0, 0xFFFFFFFF))
	{
		EnterCriticalSection(&CriticalSection);
		if (!i && other_buf)
		{
			qmemcpy(bufSource, dword_579FD4, 0x5800u);
			if (XATrack == -1)
				memset(bufSource, 0, 0x5800u);
			else
				sub_4027DE(dword_579FD4, XATrack);
			if (byte_579FE4)
			{
				dword_579FD4 = (char *)dword_579FD4 + 22528;
				if ((signed int)dword_579FD4 >= (signed int)ptr + 225280)
					dword_579FD4 = ptr;
				other_buf->lpVtbl->Lock(
					other_buf,
					dword_579FD8,
					bufMaxLength,
					&v4,
					&v3,
					0,
					0,
					0);
				acmStreamConvert(has, &acmHeader1 + dword_579E4C, 4u);
				other_buf->lpVtbl->Unlock(
					other_buf,
					v4,
					v3,
					0,
					0);
				v1 = v3 + dword_579FD8;
				dword_579FD8 += v3;
				if (dword_579FD8 >= (unsigned int)bufLockLength)
					dword_579FD8 = v1 - bufLockLength;
				dword_579E4C = ((_BYTE)dword_579E4C + 1) & 3;
			}
		}
		LeaveCriticalSection(&CriticalSection);
		if (!other_buf)
			break;
	}
	return 0;
}

int SetupNotifications()
{
	int v0; // edi@1
	char *v1; // esi@1
	signed int v2; // ebx@1
	HANDLE v3; // edx@2
	int v4; // esi@5
	int result; // eax@6
	DWORD ThreadId; // [sp+Ch] [bp-2Ch]@3
	int v7; // [sp+10h] [bp-28h]@1
	HANDLE v8; // [sp+14h] [bp-24h]@1
	char v9[16]; // [sp+18h] [bp-20h]@1
	int v10; // [sp+28h] [bp-10h]@3
	int v11; // [sp+30h] [bp-8h]@3
	HANDLE v12; // [sp+34h] [bp-4h]@3

	v0 = bufMaxLength;
	Handles = CreateEventA(0, 0, 0, 0);
	dword_579FA4 = CreateEventA(0, 0, 0, 0);
	v7 = v0;
	v8 = Handles;
	sub_4DEB10(8, "Set notifies for position %lu", v0);
	v1 = v9;
	v2 = 3;
	do
	{
		v3 = Handles;
		*(_DWORD *)v1 = v0 + *((_DWORD *)v1 - 2);
		*((_DWORD *)v1 + 1) = v3;
		sub_4DEB10(8, "Set notifies for positions %lu", *(_DWORD *)v1);
		v1 += 8;
		--v2;
	} while (v2);
	v11 = -1;
	--v10;
	v12 = dword_579FA4;
	dword_579FA8 = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)StartAddress, 0, 0, &ThreadId);
	if (!dword_579FA8)
		sub_4DEB10(1, "Create Notification Thread failed");
	v4 = (*((int(__stdcall **)(_DWORD, _DWORD, _DWORD))notify_thing->lpVtbl + 3))(notify_thing, 5, &v7);
	if (v4)
	{
		CloseHandle(Handles);
		CloseHandle(dword_579FA4);
		result = v4;
		dword_579FA4 = 0;
		Handles = 0;
	}
	else
	{
		sub_4DEB10(8, "Setup Notifications OK");
		result = 0;
	}
	return result;
}

void InitACM()
{
	unsigned int v3; // esi@1
	int v5; // eax@5
	int v6; // eax@5
	int v7; // [sp+0h] [bp-2Ch]@0
	LPDIRECTSOUNDNOTIFY *notify_shit; // [sp+4h] [bp-28h]@5
	DWORD cbwfx = 0;
	DSBUFFERDESC v9; // [sp+8h] [bp-24h]@5

	v3 = acmGetVersion();
	InitializeCriticalSection(&CriticalSection);
	ACMInited = 0;
	sub_4DEB10(8, "ACM Version %u.%.02u", v3 >> 24, (unsigned __int8)(v3 >> 16));
	acmDriverEnum(fnCallback, 0, 0);
	if (hadid)
	{
		if (acmDriverOpen(&had, hadid, 0))
		{
			sub_4DEB10(1, "*** Failed To Open Driver MS-ADPCM Driver ***");
		}
		else
		{
			bufSource = (BYTE *)malloc(22528u);
			ptr = malloc(225280u);
			pwfxDst.wFormatTag = WAVE_FORMAT_PCM;
			acmMetrics(NULL, ACM_METRIC_MAX_SIZE_FORMAT, &cbwfx);
			pwfxSrc.cbSize = 2;
			int gg = acmFormatSuggest(had, &pwfxSrc, &pwfxDst, cbwfx, ACM_FORMATSUGGESTF_WFORMATTAG);
			memset(&v9, 0, 36u);
			bufLockLength = 358336;
			bufMaxLength = 89584;
			v9.dwSize = 36;
			v9.dwFlags = DSBCAPS_LOCSOFTWARE 
			| DSBCAPS_CTRLFREQUENCY
			| DSBCAPS_CTRLPAN
			| DSBCAPS_CTRLVOLUME
			| DSBCAPS_CTRLPOSITIONNOTIFY
			| DSBCAPS_GETCURRENTPOSITION2;
			v9.dwBufferBytes = 358336;
			v9.lpwfxFormat = &pwfxDst;
			int o = ptr_crctx->dsound->lpVtbl->CreateSoundBuffer(
				ptr_crctx->dsound,
					&v9,
					&other_buf,
					0);
			notify_shit = &notify_thing;
			other_buf->lpVtbl->QueryInterface(
				other_buf,
				&IID_IDirectSoundNotify,
				&notify_thing);
			SetupNotifications();
			acmStreamOpen(&has, had, &pwfxSrc, &pwfxDst, 0, 0, 0, 0);
			acmStreamSize(has, 22528u, &pdwOutputBytes, 0);
			notify_shit = 0;
			v5 = other_buf->lpVtbl->Lock(
					other_buf,
					0,
					bufLockLength,
					&buf_lockAudioPtr1,
					&buf_lockAudioBytes1,
					0,
					0,
					0);
			sub_40179E(v5);
			memset(buf_lockAudioPtr1, 0, bufLockLength);
			memset(&acmHeader1, 0, sizeof(acmHeader1));
			memset(&acmHeader2, 0, sizeof(acmHeader2));
			memset(&acmHeader3, 0, sizeof(acmHeader3));
			memset(&acmHeader4, 0, sizeof(acmHeader4));
			acmHeader1.pbSrc = bufSource;
			acmHeader2.pbSrc = bufSource;
			acmHeader3.pbSrc = bufSource;
			acmHeader4.pbSrc = bufSource;
			acmHeader1.cbDstLength = pdwOutputBytes;
			acmHeader2.cbDstLength = pdwOutputBytes;
			acmHeader2.pbDst = &buf_lockAudioPtr1[bufMaxLength];
			acmHeader3.cbDstLength = pdwOutputBytes;
			acmHeader4.cbDstLength = pdwOutputBytes;
			acmHeader1.cbStruct = 84;
			acmHeader1.cbSrcLength = 22528;
			acmHeader1.pbDst = buf_lockAudioPtr1;
			acmHeader2.cbStruct = 84;
			acmHeader2.cbSrcLength = 22528;
			acmHeader3.cbStruct = 84;
			acmHeader3.cbSrcLength = 22528;
			acmHeader3.pbDst = &buf_lockAudioPtr1[2 * bufMaxLength];
			acmHeader4.cbStruct = 84;
			acmHeader4.cbSrcLength = 22528;
			acmHeader4.pbDst = &buf_lockAudioPtr1[3 * bufMaxLength];
			acmStreamPrepareHeader(has, &acmHeader1, 0);
			acmStreamPrepareHeader(has, &acmHeader2, 0);
			acmStreamPrepareHeader(has, &acmHeader3, 0);
			acmStreamPrepareHeader(has, &acmHeader4, 0);
			notify_shit = 0;
			v6 = other_buf->lpVtbl->Unlock(
				other_buf,
				buf_lockAudioPtr1,
				bufLockLength,
				0,
				0);
			sub_40179E(v6);
			ACMInited = 1;
		}
	}
	else
	{
		sub_4DEB10(1, "*** Unable To Locate MS-ADPCM Driver ***");
	}
}

LSTATUS __cdecl sub_4029B9(LPCSTR lpValueName, BYTE Data)
{
	return RegSetValueExA(hKey, lpValueName, 0, 4u, &Data, 4u);
}

char __cdecl ReadRegDword(LPCSTR lpValueName, DWORD* Type, BYTE Data)
{
	_DWORD *v3; // edi@1
	char result; // al@4
	int v5; // esi@5
	DWORD cbData; // [sp+Ch] [bp-4h]@1
	DWORD dwType = 0;
	v3 = Type;
	cbData = 4;
	if (RegQueryValueExA(hKey, lpValueName, 0, &dwType, (LPBYTE)Type, &cbData) || (int)Type != 4 || cbData != 4)
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
	CHAR SubKey[256]; // [sp+0h] [bp-100h]@2

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

char __cdecl ReadRegByte(LPCSTR lpValueName, BYTE* buf, BYTE defaultVal)
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
		v5 = defaultVal;
		sub_402B94(v3, defaultVal);
		*(_BYTE *)buf = v5;
		result = 0;
	}
	else
	{
		*(_BYTE *)buf = *(_DWORD *)Data != 0;
		result = 1;
	}
	return result;
}

int __cdecl LoadTextureFormats(HWND hDlg, HWND hWnd)
{
	HWND v2; // eax@1
	HWND v3; // eax@1
	struct acceladapt* result; // eax@1
	struct acceltexformatinfo* v5; // eax@3
	int depth; // esi@3
	int bitsB; // ebx@3
	int bitsR; // edi@3
	HWND v9; // eax@9
	_BYTE v10[5]; // [sp+13h] [bp-39h]@1
	int v11; // [sp+18h] [bp-34h]@2
	int bitsG; // [sp+1Ch] [bp-30h]@3
	int bitsA; // [sp+20h] [bp-2Ch]@3
	CHAR v14[40]; // [sp+24h] [bp-28h]@3

	SendMessageA(hWnd, CB_RESETCONTENT, 0, 0);
	v2 = GetDlgItem(hDlg, IDC_TEXRES);
	EnableWindow(v2, 1);
	v3 = GetDlgItem(hDlg, IDC_SOFTWARE);
	v10[4] = 0;
	*(_DWORD *)v10 = SendMessageA(v3, BM_GETCHECK, 0, 0) != 0;
	result = &dxctx.graphicsAdapters[opt_GraphicsAdapter].accelAdapters[opt_AccelAdapter];
	if (result->numTexFormats > 0)
	{
		v11 = 0;
		do
		{
			v5 = &result->texFormats[v11];
			depth = v5->depth;
			bitsB = v5->bitsB;
			bitsR = v5->bitsR;
			bitsG = v5->bitsG;
			bitsA = v5->bitsA;
			wsprintfA(v14, "%d %s RGBA %d%d%d%d", v5->depth, &gfStringWad[gfStringOffset[281]], bitsR, bitsG, bitsB, bitsA);
			SendMessageA(hWnd, CB_ADDSTRING, 0, (LPARAM)v14);
			if (v10[0])
			{
				if (depth == 32 && bitsR == 8 && bitsB == 8 && bitsG == 8 && bitsA == 8)
				{
					SendMessageA(hWnd, CB_SETCURSEL, *(WPARAM *)&v10[1], 0);
					dword_57A088 = *(_DWORD *)&v10[1];
					v9 = GetDlgItem(hDlg, IDC_TEXRES);
					EnableWindow(v9, 0);
				}
			}
			else if (depth != 16 || bitsR != 5 || bitsB != 5 || bitsG != 5 || bitsA != 1)
			{
				SendMessageA(hWnd, CB_SETCURSEL, 0, 0);
				dword_57A088 = 0;
			}
			else
			{
				SendMessageA(hWnd, CB_SETCURSEL, *(WPARAM *)&v10[1], 0);
				dword_57A088 = *(_DWORD *)&v10[1];
			}
			++*(_DWORD *)&v10[1];
			v11++;
			result = &dxctx.graphicsAdapters[opt_GraphicsAdapter].accelAdapters[opt_AccelAdapter];
		} while (*(_DWORD *)&v10[1] < result->numTexFormats);
	}
	return result;
}

char __cdecl LoadResolutions(HWND hDlg, HWND hWnd, char a3)
{
	HWND v3; // edi@2
	HWND v5; // eax@2
	HWND v7; // eax@3
	HWND v8; // eax@4
	HWND v9; // eax@4
	int v10; // ecx@5
	struct acceladapt* v11; // eax@5
	struct dispmode* v12; // eax@7
	int res_w; // edx@7
	int res_h; // ebx@7
	signed int res_bit; // eax@7
	int v16; // edx@18
	int v17; // edx@20
	struct acceladapt* v18; // eax@20
	LPARAM v19; // ebx@20
	HWND v20; // eax@24
	HWND v22; // eax@24
	HWND v23; // eax@25
	WPARAM v24; // ST10_4@26
	HWND v25; // eax@26
	HWND v26; // eax@27
	HWND v27; // eax@28
	WPARAM v28; // ST10_4@29
	HWND v29; // eax@29
	HWND v30; // eax@30
	HWND v31; // eax@31
	WPARAM v32; // ST10_4@32
	HWND v33; // eax@32
	HWND v34; // eax@33
	HWND v35; // eax@34
	WPARAM v36; // ST10_4@35
	HWND v37; // eax@35
	HWND v38; // eax@36
	HWND v39; // eax@36
	HWND v40; // eax@37
	HWND v41; // eax@37
	HWND v42; // eax@39
	HWND v43; // eax@39
	char result; // al@40
	HWND v45; // eax@41
	HWND v46; // [sp-10h] [bp-60h]@12
	WPARAM v47; // [sp-8h] [bp-58h]@2
	WPARAM v48; // [sp-8h] [bp-58h]@12
	LPARAM lParam; // [sp+10h] [bp-40h]@5
	int v50; // [sp+18h] [bp-38h]@6
	int v51; // [sp+1Ch] [bp-34h]@7
	signed int v52; // [sp+20h] [bp-30h]@7
	int wParam; // [sp+24h] [bp-2Ch]@1
	CHAR var28[44]; // [sp+28h] [bp-28h]@8
	BOOL hDlga; // [sp+54h] [bp+4h]@4

	wParam = 0;
	if (opt_AccelAdapter)
	{
		v3 = hDlg;
		v5 = GetDlgItem(hDlg, IDC_HARDACCEL);
		SendMessageA(v5, BM_SETCHECK, 1u, 0);
		v47 = 0;
	}
	else
	{
		v3 = hDlg;
		v7 = GetDlgItem(hDlg, IDC_HARDACCEL);
		SendMessageA(v7, BM_SETCHECK, 0, 0);
		v47 = 1;
	}
	v8 = GetDlgItem(v3, IDC_SOFTWARE);
	SendMessageA(v8, BM_SETCHECK, v47, 0);
	v9 = GetDlgItem(v3, IDC_SOFTWARE);
	hDlga = SendMessageA(v9, BM_GETCHECK, 0, 0) != 0;
	if (a3)
	{
		SendMessageA(hWnd, CB_RESETCONTENT, 0, 0);
		v10 = opt_GraphicsAdapter;
		lParam = 0;
		v11 = &dxctx.graphicsAdapters[opt_GraphicsAdapter].accelAdapters[opt_AccelAdapter];
		if (v11->numDispModes > 0)
		{
			v50 = 0;
			do
			{
				v12 = &v11->displayModes[v50];
				res_w = v12->width;
				res_h = v12->height;
				res_bit = v12->depth;
				v51 = res_w;
				v52 = res_bit;
				if (res_bit <= 8)
				{
					v16 = opt_AccelAdapter;
					goto LABEL_20;
				}
				wsprintfA(var28, "%dx%d %d %s", res_w, res_h, res_bit, &gfStringWad[gfStringOffset[281]]);
				SendMessageA(hWnd, CB_ADDSTRING, 0, (LPARAM)var28);
				SendMessageA(hWnd, CB_SETITEMDATA, wParam, lParam);
				if (hDlga)
				{
					if (v51 != 320 || res_h != 240 || v52 != 16)
						goto LABEL_18;
					v48 = wParam;
					v46 = hWnd;
				}
				else
				{
					if (v51 != 640 || res_h != 480 || v52 != 16)
						goto LABEL_18;
					v48 = wParam;
					v46 = hWnd;
				}
				SendMessageA(v46, CB_SETCURSEL, v48, 0);
				dword_57A090 = wParam;
			LABEL_18:
				v16 = opt_AccelAdapter;
				v10 = opt_GraphicsAdapter;
				++wParam;
			LABEL_20:
				v50++;
				++lParam;
				v18 = dxctx.graphicsAdapters[v10].accelAdapters;
				v19 = v18[v16].numDispModes;
				v11 = &v18[v16];
			} while (lParam < v19);
		}
	}
	else
	{
		v10 = opt_GraphicsAdapter;
	}
	if (dxctx.graphicsAdapters[v10].capabilities.dwCaps2 & DDCAPS2_CANRENDERWINDOWED)
	{
		v23 = GetDlgItem(v3, IDC_WINDOWED);
		EnableWindow(v23, 1);
	}
	else
	{
		v20 = GetDlgItem(v3, IDC_WINDOWED);
		EnableWindow(v20, 0);
		v22 = GetDlgItem(v3, IDC_WINDOWED);
		SendMessageA(v22, BM_SETCHECK, 0, 0);
	}
	v24 = (unsigned __int8)opt_BilinearFiltering;
	v25 = GetDlgItem(v3, IDC_BILINEAR);
	SendMessageA(v25, BM_SETCHECK, v24, 0);
	if (hDlga)
	{
		v26 = GetDlgItem(v3, IDC_VOLUMEFOG);
		EnableWindow(v26, 0);
		opt_VolumetricFog = 0;
	}
	else
	{
		v27 = GetDlgItem(v3, IDC_VOLUMEFOG);
		EnableWindow(v27, 1);
	}
	v28 = (unsigned __int8)opt_VolumetricFog;
	v29 = GetDlgItem(v3, IDC_VOLUMEFOG);
	SendMessageA(v29, BM_SETCHECK, v28, 0);
	if (hDlga)
	{
		v30 = GetDlgItem(v3, IDC_BUMPMAP);
		EnableWindow(v30, 0);
		opt_LowQualityBumpMap = 0;
	}
	else
	{
		v31 = GetDlgItem(v3, IDC_BUMPMAP);
		EnableWindow(v31, 1);
	}
	v32 = (unsigned __int8)opt_LowQualityBumpMap;
	v33 = GetDlgItem(v3, IDC_BUMPMAP);
	SendMessageA(v33, BM_SETCHECK, v32, 0);
	if (hDlga)
	{
		v34 = GetDlgItem(v3, IDC_LOWTEXT);
		EnableWindow(v34, 0);
		opt_LowQualityTextures = 0;
	}
	else
	{
		v35 = GetDlgItem(v3, IDC_LOWTEXT);
		EnableWindow(v35, 1);
	}
	v36 = (unsigned __int8)opt_LowQualityTextures;
	v37 = GetDlgItem(v3, IDC_LOWTEXT);
	SendMessageA(v37, BM_SETCHECK, v36, 0);
	if (opt_LowQualityTextures)
	{
		v38 = GetDlgItem(v3, IDC_LOWBUMP);
		SendMessageA(v38, BM_SETCHECK, 1u, 0);
		v39 = GetDlgItem(v3, IDC_LOWBUMP);
		EnableWindow(v39, 0);
	}
	else
	{
		v40 = GetDlgItem(v3, IDC_LOWBUMP);
		EnableWindow(v40, 1);
		v41 = GetDlgItem(v3, IDC_LOWBUMP);
		SendMessageA(v41, BM_SETCHECK, 0, 0);
	}
	if (!opt_LowQualityBumpMap)
	{
		v42 = GetDlgItem(v3, IDC_LOWBUMP);
		SendMessageA(v42, BM_SETCHECK, 0, 0);
		v43 = GetDlgItem(v3, IDC_LOWBUMP);
		EnableWindow(v43, 0);
	}
	result = a3;
	if (a3)
	{
		v45 = GetDlgItem(v3, IDC_TEXRES);
		result = LoadTextureFormats(v3, v45);
	}
	return result;

	S_Warn("[sub_4017B7] - Unimplemented!\n");
	return 0;
}

int __cdecl LoadAccelAdapters(HWND hDlg, HWND hWnd)
{
	int v2; // esi@1
	struct gfxadapt* v3; // eax@1
	int v4; // edi@2
	HWND v5; // eax@4

	SendMessageA(hWnd, CB_RESETCONTENT, 0, 0);
	v2 = 0;
	v3 = &dxctx.graphicsAdapters[opt_GraphicsAdapter];
	if (v3->numAccelAdapters > 0)
	{
		v4 = 0;
		do
		{
			SendMessageA(hWnd, CB_ADDSTRING, 0, v3->accelAdapters[v4].description);
			++v2;
			v4++;
			v3 = &dxctx.graphicsAdapters[opt_GraphicsAdapter];
		} while (v2 < v3->numAccelAdapters);
	}
	SendMessageA(hWnd, CB_SETCURSEL, 1u, 0);
	opt_AccelAdapter = 1;
	v5 = GetDlgItem(hDlg, IDC_RESOLUTION);
	return LoadResolutions(hDlg, v5, 1);
}

int __cdecl LoadGraphicsAdapters(HWND hDlg, HWND hWnd)
{
	int v2; // eax@1
	int v3; // edi@1
	int v4; // esi@2
	HWND v5; // eax@4
	CHAR v7[256]; // [sp+10h] [bp-100h]@3

	SendMessageA(hWnd, CB_RESETCONTENT, 0, 0);
	v2 = dxctx.numGraphicsAdapters;
	v3 = 0;
	if (dxctx.numGraphicsAdapters > 0)
	{
		v4 = 0;
		do
		{
			wsprintfA(
				v7,
				"%s - %s (%d.%d.%02d.%04d)",
				dxctx.graphicsAdapters[v4].deviceName,
				dxctx.graphicsAdapters[v4].driverDllName,
				dxctx.graphicsAdapters[v4].versionMajor,
				dxctx.graphicsAdapters[v4].versionMinor,
				dxctx.graphicsAdapters[v4].versionBuild,
				dxctx.graphicsAdapters[v4].versionRevision);
			SendMessageA(hWnd, CB_ADDSTRING, 0, (LPARAM)v7);
			v2 = dxctx.numGraphicsAdapters;
			++v3;
			v4++;
		} while (v3 < dxctx.numGraphicsAdapters);
	}
	SendMessageA(hWnd, CB_SETCURSEL, v2 - 1, 0);
	opt_GraphicsAdapter = dxctx.numGraphicsAdapters - 1;
	v5 = GetDlgItem(hDlg, IDC_OUTSETTINGS);
	return LoadAccelAdapters(hDlg, v5);
}

void sub_402D10()
{
	for(int i = 0; i < 18; i++)
	{
		dword_878C4C[i] = 0;

		for(int j = 0; j < 18; j++)
		{
			if (opt_Keys[i] == opt_Keys2[j])
			{
				dword_878C4C[i] = 1;
				break;
			}
		}
	}
}

char sub_402F77()
{
	int v0; // eax@8
	int v1; // eax@9
	int v2; // edx@13
	int v3; // ecx@13
	char result; // al@13
	DWORD Type; // [sp+3h] [bp-5h]@3
	DWORD Type2;

	if ((unsigned __int8)sub_402964("System"))
	{
		ReadRegByte("Setup", (int)&opt_Setup, 0);
		if (opt_Setup)
		{
			dword_D9AC1B = 256;
			dword_D9AC1F = 256;
			dword_D9AC27 = 32;
			ReadRegDword("DD", &ptr_ctx->curGfxAdapt, 0);
			ReadRegDword("D3D", &ptr_ctx->curAccelAdapt, 0);
			ReadRegDword("VMode", &ptr_ctx->curDispMode, 0);
			ReadRegDword("TFormat", &ptr_ctx->curTexFormat, 0);
			ReadRegDword("DS", &ptr_ctx->curSoundCard, 0);
			ReadRegByte("BumpMap", &opt_BumpMap, 1);
			ReadRegByte("Filter", &opt_Filter, 1);
			ReadRegByte("DisableSound", &opt_DisableSound, 0);
#ifdef FORCE_NO_SOUND
			opt_DisableSound = 1;
#endif
			ReadRegByte("Volumetric", &opt_Volumetric, 1);
			ReadRegByte("NoFMV", &opt_NoFMV, 0);
			ReadRegByte("TextLow", (int)&Type, 0);
			if ((_BYTE)Type)
				dword_D9AC1B = 128;
			ReadRegByte("BumpLow", (int)&Type, 0);
			if ((_BYTE)Type)
				dword_D9AC1F = 128;
			ReadRegByte("HardWare", (int)&Type, 1);
			if ((_BYTE)Type)
			{
				v0 = dword_D9AC27;
				LOBYTE(v0) = dword_D9AC27 | 0x90;
				dword_D9AC27 = v0;
			}
			/*ReadRegByte("Window", (int)&Type, 0);
			v1 = dword_D9AC27;
			if ((_BYTE)Type)
				LOBYTE(v1) = dword_D9AC27 | 2;
			else
				LOBYTE(v1) = dword_D9AC27 | 1;
			dword_D9AC27 = v1;*/
		}
		sub_402964("Game");
		ReadRegDword("Key0", &opt_Keys2[0], opt_Keys[0]);
		ReadRegDword("Key1", &opt_Keys2[1], opt_Keys[1]);
		ReadRegDword("Key2", &opt_Keys2[2], opt_Keys[2]);
		ReadRegDword("Key3", &opt_Keys2[3], opt_Keys[3]);
		ReadRegDword("Key4", &opt_Keys2[4], opt_Keys[4]);
		ReadRegDword("Key5", &opt_Keys2[5], opt_Keys[5]);
		ReadRegDword("Key6", &opt_Keys2[6], opt_Keys[6]);
		ReadRegDword("Key7", &opt_Keys2[7], opt_Keys[7]);
		ReadRegDword("Key8", &opt_Keys2[8], opt_Keys[8]);
		ReadRegDword("Key9", &opt_Keys2[9], opt_Keys[9]);
		ReadRegDword("Key10", &opt_Keys2[10], opt_Keys[10]);
		ReadRegDword("Key11", &opt_Keys2[11], opt_Keys[11]);
		ReadRegDword("Key12", &opt_Keys2[12], opt_Keys[12]);
		ReadRegDword("Key13", &opt_Keys2[13], opt_Keys[13]);
		ReadRegDword("Key14", &opt_Keys2[14], opt_Keys[14]);
		ReadRegDword("Key15", &opt_Keys2[15], opt_Keys[15]);
		ReadRegDword("Key16", &opt_Keys2[16], opt_Keys[16]);
		ReadRegDword("Key17", &opt_Keys2[17], opt_Keys[17]);
		ReadRegDword("JDck", &opt_JDck, 5);
		ReadRegDword("JDsh", &opt_JDsh, 3);
		ReadRegDword("JWlk", &opt_JWlk, 4);
		ReadRegDword("JJmp", &opt_JJmp, 0);
		ReadRegDword("JAct", &opt_JAct, 1);
		ReadRegDword("JDrw", &opt_JDrw, 2);
		ReadRegDword("JFlr", &opt_JFlr, 9);
		ReadRegDword("JLok", &opt_JLok, 6);
		ReadRegDword("JRol", &opt_JRol, 7);
		ReadRegDword("JInv", &opt_JInv, 8);
		ReadRegDword("MusicVolume", &opt_MusicVolume, 80);
		ReadRegDword("SFXVolume", &opt_SFXVolume, 90);
		ReadRegDword("ControlMethod", &opt_ControlMethod, 0);
		ReadRegDword("SoundQuality", &opt_SoundQuality, 1);
		ReadRegDword("AutoTarget", &opt_AutoTarget, 1);
		ReadRegDword("WindowX", &dxctx.windowPos.left, 0);
		ReadRegDword("WindowY", &dxctx.windowPos.top, 0);
		sub_402D10();
		result = opt_Setup;
	}
	else
	{
		result = 0;
	}
	return result;
	S_Warn("[sub_402F77] - Unimplemented!\n");
	return 0;
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
				v7 = byte_511894;
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
				v5 = byte_511894[2 * v6 + 1];
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

LRESULT __cdecl sub_4018F2(HWND hDlg, HWND hWnd)
{
	int v2; // eax@1
	int v3; // esi@1
	int v4; // ebp@2
	HWND v5; // eax@5
	HWND v6; // eax@5

	SendMessageA(hWnd, CB_RESETCONTENT, 0, 0);
	v2 = dxctx.numSoundCards;
	v3 = 0;
	if (dxctx.numSoundCards > 0)
	{
		v4 = 0;
		do
		{
			SendMessageA(hWnd, CB_ADDSTRING, 0, dword_D9AB74 + v4 + 30);
			v2 = dxctx.numSoundCards;
			++v3;
			v4 += 130;
		} while (v3 <  dxctx.numSoundCards);
	}
	dword_57A08C = 0;
	if (!v2)
	{
		SendMessageA(hWnd, CB_ADDSTRING, 0, (LPARAM)&gfStringWad[gfStringOffset[285]]);
		v5 = GetDlgItem(hDlg, IDC_NOSOUND);
		EnableWindow(v5, 0);
		v6 = GetDlgItem(hDlg, IDC_NOSOUND);
		SendMessageA(v6, BM_SETCHECK, 1u, 0);
		EnableWindow(hWnd, 0);
	}
	return SendMessageA(hWnd, CB_SETCURSEL, 0, 0);
}

char __cdecl sub_402DF1(HWND hDlg)
{
	HWND v1; // eax@1
	BYTE v2; // al@1
	HWND v3; // eax@1
	BYTE v4; // al@1
	HWND v5; // eax@1
	LRESULT v6; // ST10_4@1
	HWND v7; // eax@1
	BYTE v8; // al@1
	HWND v9; // eax@1
	BYTE v10; // al@1
	HWND v11; // eax@1
	BYTE v12; // al@1
	HWND v13; // eax@1
	LRESULT v14; // eax@1
	HWND v15; // eax@1
	LRESULT v16; // eax@1
	HWND v17; // eax@1
	LRESULT v18; // eax@1
	HWND v19; // eax@1
	LRESULT v20; // eax@1
	HWND v21; // eax@1
	LRESULT v22; // eax@1
	HWND v23; // eax@1
	LRESULT v24; // eax@1
	HWND v25; // eax@1
	LRESULT v26; // eax@1
	HWND v27; // eax@1
	LRESULT v28; // eax@1
	HWND v29; // eax@1
	LRESULT v30; // eax@1

	sub_402964("System");
	v1 = GetDlgItem(hDlg, IDC_GFXADAPTER);
	v2 = SendMessageA(v1, CB_GETCURSEL, 0, 0);
	sub_4029B9("DD", v2);
	v3 = GetDlgItem(hDlg, IDC_OUTSETTINGS);
	v4 = SendMessageA(v3, CB_GETCURSEL, 0, 0);
	sub_4029B9("D3D", v4);
	v5 = GetDlgItem(hDlg, IDC_RESOLUTION);
	v6 = SendMessageA(v5, CB_GETCURSEL, 0, 0);
	v7 = GetDlgItem(hDlg, IDC_RESOLUTION);
	v8 = SendMessageA(v7, CB_GETITEMDATA, v6, 0);
	sub_4029B9("VMode", v8);
	v9 = GetDlgItem(hDlg, IDC_SNDADAPTER);
	v10 = SendMessageA(v9, CB_GETCURSEL, 0, 0);
	sub_4029B9("DS", v10);
	v11 = GetDlgItem(hDlg, IDC_TEXRES);
	v12 = SendMessageA(v11, CB_GETCURSEL, 0, 0);
	sub_4029B9("TFormat", v12);
	v13 = GetDlgItem(hDlg, IDC_BILINEAR);
	v14 = SendMessageA(v13, BM_GETCHECK, 0, 0);
	sub_402B94("Filter", v14 != 0);
	v15 = GetDlgItem(hDlg, IDC_BUMPMAP);
	v16 = SendMessageA(v15, BM_GETCHECK, 0, 0);
	sub_402B94("BumpMap", v16 != 0);
	v17 = GetDlgItem(hDlg, IDC_HARDACCEL);
	v18 = SendMessageA(v17, BM_GETCHECK, 0, 0);
	sub_402B94("HardWare", v18 != 0);
	v19 = GetDlgItem(hDlg, IDC_NOSOUND);
	v20 = SendMessageA(v19, BM_GETCHECK, 0, 0);
	sub_402B94("DisableSound", v20 != 0);
	v21 = GetDlgItem(hDlg, IDC_LOWTEXT);
	v22 = SendMessageA(v21, BM_GETCHECK, 0, 0);
	sub_402B94("TextLow", v22 != 0);
	v23 = GetDlgItem(hDlg, IDC_LOWBUMP);
	v24 = SendMessageA(v23, BM_GETCHECK, 0, 0);
	sub_402B94("BumpLow", v24 != 0);
	v25 = GetDlgItem(hDlg, IDC_WINDOWED);
	v26 = SendMessageA(v25, BM_GETCHECK, 0, 0);
	sub_402B94("Window", v26 != 0);
	v27 = GetDlgItem(hDlg, IDC_VOLUMEFOG);
	v28 = SendMessageA(v27, BM_GETCHECK, 0, 0);
	sub_402B94("Volumetric", v28 != 0);
	v29 = GetDlgItem(hDlg, IDC_NOFMV);
	v30 = SendMessageA(v29, BM_GETCHECK, 0, 0);
	sub_402B94("NoFMV", v30 != 0);
	sub_402B94("Setup", 1);
	return 1;
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
	char v67[16]; // [sp-4h] [bp-110h]@22
	char v68[256]; // [sp+Ch] [bp-100h]@44

	if (msg == 272)
	{
		sub_4DEB10(6, "WM_INITDIALOG");
		if (Gameflow->Language == LNG_JAPAN)
		{
			v18 = GetStockObject(13);
			gdiobject = v18;
			v19 = GetDlgItem(hDlg, IDC_GFXADAPTER);
			SendMessageA(v19, WM_SETFONT, 0, (LPARAM)v18);
			v20 = gdiobject;
			v21 = GetDlgItem(hDlg, IDC_OUTSETTINGS);
			SendMessageA(v21, WM_SETFONT, 0, (LPARAM)v20);
			v22 = gdiobject;
			v23 = GetDlgItem(hDlg, IDC_RESOLUTION);
			SendMessageA(v23, WM_SETFONT, 0, (LPARAM)v22);
			v24 = gdiobject;
			v25 = GetDlgItem(hDlg, IDC_TEXRES);
			SendMessageA(v25, WM_SETFONT, 0, (LPARAM)v24);
			v26 = gdiobject;
			v27 = GetDlgItem(hDlg, IDC_SNDADAPTER);
			SendMessageA(v27, WM_SETFONT, 0, (LPARAM)v26);
		}
		v28 = sub_401C9E(&gfStringWad[gfStringOffset[266]], v68);
		v29 = GetDlgItem(hDlg, 1001);
		SendMessageA(v29, WM_SETTEXT, 0, (LPARAM)v28);
		v30 = sub_401C9E(&gfStringWad[gfStringOffset[267]], v68);
		v31 = GetDlgItem(hDlg, 1002);
		SendMessageA(v31, WM_SETTEXT, 0, (LPARAM)v30);
		v32 = sub_401C9E(&gfStringWad[gfStringOffset[270]], v68);
		v33 = GetDlgItem(hDlg, IDOK);
		SendMessageA(v33, WM_SETTEXT, 0, (LPARAM)v32);
		v34 = sub_401C9E(&gfStringWad[gfStringOffset[271]], v68);
		v35 = GetDlgItem(hDlg, IDCANCEL);
		SendMessageA(v35, WM_SETTEXT, 0, (LPARAM)v34);
		v36 = sub_401C9E(&gfStringWad[gfStringOffset[268]], v68);
		v37 = GetDlgItem(hDlg, 1009);
		SendMessageA(v37, WM_SETTEXT, 0, (LPARAM)v36);
		v38 = sub_401C9E(&gfStringWad[gfStringOffset[275]], v68);
		v39 = GetDlgItem(hDlg, IDC_BILINEAR);
		SendMessageA(v39, WM_SETTEXT, 0, (LPARAM)v38);
		v40 = sub_401C9E(&gfStringWad[gfStringOffset[276]], v68);
		v41 = GetDlgItem(hDlg, IDC_BUMPMAP);
		SendMessageA(v41, WM_SETTEXT, 0, (LPARAM)v40);
		v42 = sub_401C9E(&gfStringWad[gfStringOffset[272]], v68);
		v43 = GetDlgItem(hDlg, IDC_HARDACCEL);
		SendMessageA(v43, WM_SETTEXT, 0, (LPARAM)v42);
		v44 = sub_401C9E(&gfStringWad[gfStringOffset[273]], v68);
		v45 = GetDlgItem(hDlg, IDC_SOFTWARE);
		SendMessageA(v45, WM_SETTEXT, 0, (LPARAM)v44);
		v46 = sub_401C9E(&gfStringWad[gfStringOffset[279]], v68);
		v47 = GetDlgItem(hDlg, 1017);
		SendMessageA(v47, WM_SETTEXT, 0, (LPARAM)v46);
		v48 = sub_401C9E(&gfStringWad[gfStringOffset[280]], v68);
		v49 = GetDlgItem(hDlg, IDC_NOSOUND);
		SendMessageA(v49, WM_SETTEXT, 0, (LPARAM)v48);
		v50 = sub_401C9E(&gfStringWad[gfStringOffset[277]], v68);
		v51 = GetDlgItem(hDlg, IDC_LOWTEXT);
		SendMessageA(v51, WM_SETTEXT, 0, (LPARAM)v50);
		v52 = sub_401C9E(&gfStringWad[gfStringOffset[278]], v68);
		v53 = GetDlgItem(hDlg, IDC_LOWBUMP);
		SendMessageA(v53, WM_SETTEXT, 0, (LPARAM)v52);
		v54 = sub_401C9E(&gfStringWad[gfStringOffset[269]], v68);
		v55 = GetDlgItem(hDlg, 1013);
		SendMessageA(v55, WM_SETTEXT, 0, (LPARAM)v54);
		v56 = sub_401C9E(&gfStringWad[gfStringOffset[283]], v68);
		v57 = GetDlgItem(hDlg, IDC_WINDOWED);
		SendMessageA(v57, WM_SETTEXT, 0, (LPARAM)v56);
		v58 = sub_401C9E(&gfStringWad[gfStringOffset[284]], v68);
		v59 = GetDlgItem(hDlg, 1023);
		SendMessageA(v59, WM_SETTEXT, 0, (LPARAM)v58);
		v60 = sub_401C9E(&gfStringWad[gfStringOffset[274]], v68);
		v61 = GetDlgItem(hDlg, IDC_VOLUMEFOG);
		SendMessageA(v61, WM_SETTEXT, 0, (LPARAM)v60);
		v62 = sub_401C9E(&gfStringWad[gfStringOffset[307]], v68);
		v63 = GetDlgItem(hDlg, IDC_NOFMV);
		SendMessageA(v63, WM_SETTEXT, 0, (LPARAM)v62);
		v64 = GetDlgItem(hDlg, IDC_GFXADAPTER);
		LoadGraphicsAdapters(hDlg, v64);
		v65 = GetDlgItem(hDlg, IDC_SNDADAPTER);
		sub_4018F2(hDlg, v65);
		return 1;
	}
	if (msg != WM_COMMAND)
		return 0;
	if ((signed int)(unsigned __int16)wParam > IDC_SOFTWARE)
	{
		switch ((unsigned __int16)wParam)
		{
		case IDC_NOSOUND:
			if (wParam >> 16)
				return 0;
			v11 = GetDlgItem(hDlg, (unsigned __int16)wParam);
			v12 = GetDlgItem(hDlg, IDC_SNDADAPTER);
			if (SendMessageA(v11, BM_GETCHECK, 0, 0))
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
		case IDC_LOWTEXT:
			if (wParam >> 16)
				return 0;
			v7 = hDlg;
			v8 = GetDlgItem;
			v13 = GetDlgItem(hDlg, IDC_LOWTEXT);
			opt_LowQualityTextures = SendMessageA(v13, BM_GETCHECK, 0, 0) != 0;
			break;
		case IDC_BUMPMAP:
			if (wParam >> 16)
				return 0;
			v7 = hDlg;
			v8 = GetDlgItem;
			v14 = GetDlgItem(hDlg, IDC_BUMPMAP);
			opt_LowQualityBumpMap = SendMessageA(v14, BM_GETCHECK, 0, 0) != 0;
			break;
		case IDC_VOLUMEFOG:
			if (wParam >> 16)
				return 0;
			v7 = hDlg;
			v8 = GetDlgItem;
			v15 = GetDlgItem(hDlg, IDC_VOLUMEFOG);
			LOBYTE(opt_VolumetricFog) = SendMessageA(v15, BM_GETCHECK, 0, 0) != 0;
			break;
		case IDC_BILINEAR:
			if (wParam >> 16)
				return 0;
			v7 = hDlg;
			v8 = GetDlgItem;
			v16 = GetDlgItem(hDlg, IDC_BILINEAR);
			opt_BilinearFiltering = SendMessageA(v16, BM_GETCHECK, 0, 0) != 0;
			break;
		default:
			return 0;
		}
		v67[0] = 0;
		goto LABEL_40;
	}
	if ((unsigned __int16)wParam == IDC_SOFTWARE)
	{
		if (wParam >> 16)
			return 0;
		opt_AccelAdapter = 0;
		v66 = 0;
		goto LABEL_25;
	}
	if ((signed int)(unsigned __int16)wParam > IDC_GFXADAPTER)
	{
		if ((unsigned __int16)wParam == IDC_OUTSETTINGS)
		{
			if (wParam >> 16 != 1)
				return 0;
			v7 = hDlg;
			v8 = GetDlgItem;
			v9 = GetDlgItem(hDlg, IDC_OUTSETTINGS);
			opt_AccelAdapter = SendMessageA(v9, CB_GETCURSEL, 0, 0);
			v67[0] = 1;
		LABEL_40:
			v17 = v8(v7, IDC_RESOLUTION);
			LoadResolutions(v7, v17, v67[0]);
			return 0;
		}
		if ((unsigned __int16)wParam != IDC_HARDACCEL || wParam >> 16)
			return 0;
		opt_AccelAdapter = 1;
		v66 = 1;
	LABEL_25:
		v7 = hDlg;
		v8 = GetDlgItem;
		v10 = GetDlgItem(hDlg, IDC_OUTSETTINGS);
		SendMessageA(v10, CB_SETCURSEL, v66, 0);
		v67[0] = 1;
		goto LABEL_40;
	}
	if ((unsigned __int16)wParam == IDC_GFXADAPTER)
	{
		if (wParam >> 16 == 1)
		{
			v5 = GetDlgItem(hDlg, IDC_GFXADAPTER);
			opt_GraphicsAdapter = SendMessageA(v5, CB_GETCURSEL, 0, 0);
			v6 = GetDlgItem(hDlg, IDC_OUTSETTINGS);
			LoadAccelAdapters(hDlg, v6);
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

BOOL  InitSetupDialog()
{
	INT_PTR v0; // esi@1
	BOOL result; // al@2

	ShowCursor(1);
	v0 = DialogBoxParamA(hinst, (LPCSTR)IDD_SETUP, 0, DialogFunc, 0);
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

signed int __stdcall sub_402AB3(LPDDPIXELFORMAT a1, void *a2)
{
	signed int result; // eax@2

	if (a1->dwFlags == DDPF_BUMPDUDV)
	{
		result = 0;
		qmemcpy(a2, a1, 0x20u);
		dword_D99D7C = 1;
	}
	else
	{
		result = 1;
	}
	return result;
}

int sub_401424()
{
	struct acceladapt* result; // eax@1

	dword_D99DA4 = 0;
	result = &ptr_ctx->graphicsAdapters[ptr_ctx->curGfxAdapt].accelAdapters[ptr_ctx->curAccelAdapt];
	if ((D3DTEXOPCAPS_BUMPENVMAP | D3DTEXOPCAPS_BUMPENVMAPLUMINANCE) & result->deviceDesc.dwTextureOpCaps)
	{
		if (result->deviceDesc.wMaxTextureBlendStages >= 3u)
		{
			dword_D99D7C = 0;
			ptr_crctx->d3d_dev->lpVtbl->EnumTextureFormats(
				ptr_crctx->d3d_dev,
				sub_402AB3,
				&unk_D99D80[0]);
			result = dword_D99D7C;
			if (dword_D99D7C)
			{
				sub_4DEB10(5, "Bump bit count 0x%X", *(_DWORD *)BumpBitCount);
				sub_4DEB10(5, "Bump DU %X", *(_DWORD *)BumpDU);
				sub_4DEB10(5, "Bump DV %X", *(_DWORD *)BumpDV);
				result = *(_DWORD *)BumpBitCount;
				if (*(_DWORD *)BumpBitCount == 16)
					dword_D99DA4 = 1;
			}
		}
	}
	return result;
}

HWND CloseDirectX()
{
	HWND result; // eax@1
	LPDIRECTDRAW4 v1; // ecx@2
	LPDIRECT3DVIEWPORT3 v2; // eax@2
	int v3; // eax@3
	LPDIRECT3DDEVICE3 v4; // eax@5
	int v5; // eax@6
	LPDIRECTDRAWSURFACE4 v6; // eax@8
	int v7; // eax@9
	LPDIRECTDRAWSURFACE4 v8; // eax@11
	int v9; // eax@12
	LPDIRECTDRAWSURFACE4 v10; // eax@14
	int v11; // eax@15
	int v12; // eax@19
	LPDIRECT3D3 v13; // eax@21
	int v14; // eax@22

	sub_4DEB10(2, "CloseDirectX");
	result = (HWND)ptr_crctx;
	if (ptr_crctx)
	{
		v1 = ptr_crctx->ddraw;
		v2 = ptr_crctx->viewport;
		if (v2)
		{
			v3 = v2->lpVtbl->Release(v2);
			sub_4DEB10(4, "Released %s @ %x - RefCnt = %d", "Viewport", ptr_crctx->viewport, v3);
			ptr_crctx->viewport = 0;
		}
		else
		{
			sub_4DEB10(1, "%s Attempt To Release NULL Ptr", "Viewport");
		}
		v4 = ptr_crctx->d3d_dev;
		if (v4)
		{
			v5 = v4->lpVtbl->Release(ptr_crctx->d3d_dev);
			sub_4DEB10(4, "Released %s @ %x - RefCnt = %d", "Direct3DDevice", ptr_crctx->d3d_dev, v5);
			ptr_crctx->d3d_dev = 0;
		}
		else
		{
			sub_4DEB10(1, "%s Attempt To Release NULL Ptr", "Direct3DDevice");
		}
		v6 = ptr_crctx->buf_z;
		if (v6)
		{
			v7 = v6->lpVtbl->Release(ptr_crctx->buf_z);
			sub_4DEB10(4, "Released %s @ %x - RefCnt = %d", "Z Buffer", ptr_crctx->buf_z, v7);
			ptr_crctx->buf_z = 0;
		}
		else
		{
			sub_4DEB10(1, "%s Attempt To Release NULL Ptr", "Z Buffer");
		}
		v8 = ptr_crctx->buf_back;
		if (v8)
		{
			v9 = v8->lpVtbl->Release(ptr_crctx->buf_back);
			sub_4DEB10(4, "Released %s @ %x - RefCnt = %d", "Back Buffer", ptr_crctx->buf_back, v9);
			ptr_crctx->buf_back = 0;
		}
		else
		{
			sub_4DEB10(1, "%s Attempt To Release NULL Ptr", "Back Buffer");
		}
		v10 = ptr_crctx->buf_primary;
		if (v10)
		{
			v11 = v10->lpVtbl->Release(ptr_crctx->buf_primary);
			sub_4DEB10(4, "Released %s @ %x - RefCnt = %d", "Primary Buffer", ptr_crctx->buf_primary, v11);
			ptr_crctx->buf_primary = 0;
		}
		else
		{
			sub_4DEB10(1, "%s Attempt To Release NULL Ptr", "Primary Buffer");
		}
		result = (HWND)ptr_crctx;
		if (!(ptr_crctx->flags & 0x40))
		{
			if (ptr_crctx->ddraw)
			{
				v12 = ptr_crctx->ddraw->lpVtbl->Release(ptr_crctx->ddraw);
				sub_4DEB10(4, "Released %s @ %x - RefCnt = %d", "DirectDraw", ptr_crctx->ddraw, v12);
				ptr_crctx->ddraw = 0;
			}
			else
			{
				sub_4DEB10(1, "%s Attempt To Release NULL Ptr", "DirectDraw");
			}
			v13 = ptr_crctx->d3d;
			if (v13)
			{
				v14 = v13->lpVtbl->Release(ptr_crctx->d3d);
				result = sub_4DEB10(4, "Released %s @ %x - RefCnt = %d", "Direct3D", ptr_crctx->d3d, v14);
				ptr_crctx->d3d = 0;
			}
			else
			{
				result = sub_4DEB10(1, "%s Attempt To Release NULL Ptr", "Direct3D");
			}
		}
	}
	return result;
}

int sub_40193D()
{
	S_Warn("[sub_40193D] - Unimplemented!\\n");
	return 0;
}

signed int __cdecl DXCreateViewport(LPDIRECT3D3 a1, LPDIRECT3DDEVICE3 a2, DWORD a3, DWORD a4, LPDIRECT3DVIEWPORT3 *a5)
{
	HRESULT v5; // eax@1
	signed int result; // eax@2
	int v7; // eax@3
	LPDIRECT3DVIEWPORT3 v8; // eax@5
	HRESULT v9; // eax@5
	HRESULT v10; // eax@7
	D3DVIEWPORT2 v11; // [sp+14h] [bp-2Ch]@5

	sub_4DEB10(2, "DXCreateViewport");
	v5 = a1->lpVtbl->CreateViewport(a1, a5, 0);
	if (sub_40179E(v5))
	{
		result = 0;
	}
	else
	{
		v7 = a2->lpVtbl->AddViewport(a2, *a5);
		if (sub_40179E(v7))
		{
			result = 0;
		}
		else
		{
			memset(&v11, 0, sizeof(v11));
			v11.dvClipWidth = (D3DVALUE)a3;
			v11.dvClipHeight = (D3DVALUE)a4;
			v11.dwX = 0;
			v11.dwY = 0;
			v11.dvClipX = 0;
			v11.dvClipY = 0;
			v11.dvMinZ = 0;
			v8 = *a5;
			v11.dwHeight = a4;
			v11.dwSize = 44;
			v11.dwWidth = a3;
			v11.dvMaxZ = 1;
			v9 = v8->lpVtbl->SetViewport2(v8, &v11);
			if (sub_40179E(v9))
			{
				result = 0;
			}
			else
			{
				v10 = a2->lpVtbl->SetCurrentViewport(a2, *a5);
				sub_40179E(v10);
				result = 1;
			}
		}
	}
	return result;
}

signed int __cdecl DXCreate(int a1, int a2, int a3, int flags, struct dxcontext_s *a5, HWND a6, DWORD dwStyle)
{

	signed int v7; // edi@1
	signed int result; // eax@5
	int v9; // eax@8
	struct dispmode* v10; // ecx@13
	int v11; // eax@26
	int v12; // eax@30
	int v13; // eax@32
	int v14; // eax@32
	int v15; // eax@33
	int v16; // eax@35
	int v17; // eax@37
	struct gfxadapt* v18; // edi@38
	int v19; // eax@42
	HDC hDC; // [sp+28h] [bp-12Ch]@14
	IDirectDrawClipper* hDC_;
	struct tagRECT Rect; // [sp+2Ch] [bp-128h]@28
	int v22; // [sp+3Ch] [bp-118h]@8
	HWND hWnd; // [sp+40h] [bp-114h]@14
	DDSURFACEDESC2 a2a; // [sp+44h] [bp-110h]@15
	DEVMODEA var94; // [sp+C0h] [bp-94h]@14
	__int16 v26; // [sp+E4h] [bp-70h]@14
	int v27; // [sp+E8h] [bp-6Ch]@14
	int v28; // [sp+128h] [bp-2Ch]@14

	v7 = 0;
	sub_4DEB10(2, "DXCreate");
	ptr_crctx = a5;
	a5->flags = flags;
	dxctx.dword_D9ABF5 = a6;
	dxctx.dword_D9ABE1 = dwStyle;
	if (flags & 0x40)
		v7 = 1;
	CloseDirectX();
	if (!v7)
	{
		if (!DXDDCreate(
			ptr_ctx->graphicsAdapters[ptr_ctx->curGfxAdapt].field3,
			&ptr_crctx->ddraw))
		{
			CloseDirectX();
			return 0;
		}
		if (!DXD3DCreate(ptr_crctx->ddraw, &ptr_crctx->d3d))
		{
			CloseDirectX();
			return 0;
		}
	}
	v22 = flags & 1;
	v9 = v22 != 0 ? 19 : 8;
	if (flags & 0x20)
		v9 |= 0x800u;
	ptr_crctx->dword_D9ABE5 = v9;
	if (!DXSetCooperativeLevel(ptr_crctx->ddraw, a6, v9))
	{
		CloseDirectX();
		return 0;
	}
	if (flags & 1)
	{
		v10 = ptr_ctx->graphicsAdapters[ptr_ctx->curGfxAdapt]
			.accelAdapters[ptr_ctx->curAccelAdapt]
			.displayModes;
		DXSetVideoMode(
			ptr_crctx->ddraw,
			v10[ptr_ctx->curDispMode].width,
			v10[ptr_ctx->curDispMode].height,
			v10[ptr_ctx->curDispMode].depth);
	}
	else
	{
		hWnd = GetDesktopWindow();
		v26 = 148;
		hDC = GetDC(hWnd);
		v28 = ptr_ctx->graphicsAdapters[ptr_ctx->curGfxAdapt]
			.accelAdapters[ptr_ctx->curAccelAdapt]
			.displayModes[ptr_ctx->curDispMode]
			.depth;
		ReleaseDC(hWnd, hDC);
		v27 = 0x40000;
		ChangeDisplaySettingsA(&var94, 0);
	}
	memset(&a2a, 0, sizeof(a2a));
	a2a.dwSize = 124;
	if (v22)
	{
		a2a.dwBackBufferCount = 1;
		a2a.dwFlags = 33;
		a2a.ddsCaps.dwCaps = 25112;
		if (!(flags & 0x80))
		{
			a2a.dwBackBufferCount = 0;
			a2a.dwFlags = 1;
			a2a.ddsCaps.dwCaps = 25088;
		}
		sub_4DEB10(3, "Create Primary Surface");
		if (!DXCreateSurface(ptr_crctx->ddraw, &a2a, &ptr_crctx->buf_primary))
		{
			CloseDirectX();
			return 0;
		}
		if (flags & 0x80)
		{
			sub_4DEB10(3, "Get Attached Back Buffer");
			a2a.ddsCaps.dwCaps = 4;
			ptr_crctx->buf_primary->lpVtbl->GetAttachedSurface(
				ptr_crctx->buf_primary,
				&a2a.ddsCaps,
				&ptr_crctx->buf_back);
		}
		else
		{
			ptr_crctx->buf_back = ptr_crctx->buf_primary;
		}
		ptr_crctx->width = ptr_ctx->graphicsAdapters[ptr_ctx->curGfxAdapt]
			.accelAdapters[ptr_ctx->curAccelAdapt]
			.displayModes[ptr_ctx->curDispMode]
			.width;
		ptr_crctx->height = ptr_ctx->graphicsAdapters[ptr_ctx->curGfxAdapt]
			.accelAdapters[ptr_ctx->curAccelAdapt]
			.displayModes[ptr_ctx->curDispMode]
			.height;
		ptr_crctx->stru_D9ABBD.top = 0;
		ptr_crctx->stru_D9ABBD.left = 0;
		ptr_crctx->stru_D9ABBD.right = ptr_ctx->graphicsAdapters[ptr_ctx->curGfxAdapt]
			.accelAdapters[ptr_ctx->curAccelAdapt]
			.displayModes[ptr_ctx->curDispMode]
			.width;
		ptr_crctx->stru_D9ABBD.bottom = ptr_ctx->graphicsAdapters[ptr_ctx->curGfxAdapt]
			.accelAdapters[ptr_ctx->curAccelAdapt]
			.displayModes[ptr_ctx->curDispMode]
			.height;
	}
	else
	{
		sub_4DEB10(5, "DXCreate: Windowed Mode");
		Rect.top = 0;
		Rect.left = 0;
		Rect.right = ptr_ctx->graphicsAdapters[ptr_ctx->curGfxAdapt]
			.accelAdapters[ptr_ctx->curAccelAdapt]
			.displayModes[ptr_ctx->curDispMode]
			.width;
		Rect.bottom = ptr_ctx->graphicsAdapters[ptr_ctx->curGfxAdapt]
			.accelAdapters[ptr_ctx->curAccelAdapt]
			.displayModes[ptr_ctx->curDispMode]
			.height;
		AdjustWindowRect(&Rect, dwStyle, 0);
		SetWindowPos(a6, 0, 0, 0, Rect.right - Rect.left, Rect.bottom - Rect.top, 6u);
		GetClientRect(a6, &ptr_crctx->stru_D9ABBD);
		GetClientRect(a6, &ptr_crctx->windowPos);
		ClientToScreen(a6, (LPPOINT)&ptr_crctx->windowPos.left);
		ClientToScreen(a6, (LPPOINT)&ptr_crctx->windowPos.right);
		ptr_crctx->width = ptr_crctx->stru_D9ABBD.right;
		ptr_crctx->height = ptr_crctx->stru_D9ABBD.bottom;
		sub_4DEB10(5, "w %d h %d", ptr_crctx->width, ptr_crctx->height);
		a2a.dwFlags = 1;
		a2a.ddsCaps.dwCaps = 512;
		if (!DXCreateSurface(ptr_crctx->ddraw, &a2a, &ptr_crctx->buf_primary))
		{
			CloseDirectX();
			return 0;
		}
		v12 = ptr_crctx->ddraw->lpVtbl->CreateClipper(
			ptr_crctx->ddraw,
			0,
			&hDC_,
			0);
		if (sub_40179E(v12))
		{
			CloseDirectX();
			return 0;
		}
		v13 = hDC_->lpVtbl->SetHWnd(hDC_, 0, a6);
		sub_40179E(v13);
		v14 = ptr_crctx->buf_primary->lpVtbl->SetClipper(
			ptr_crctx->buf_primary,
			hDC_);
		sub_40179E(v14);
		if (hDC_)
		{
			v15 = hDC_->lpVtbl->Release(hDC_);
			sub_4DEB10(4, "Released %s @ %x - RefCnt = %d", "Clipper", hDC_, v15);
			hDC_ = 0;
		}
		else
		{
			sub_4DEB10(1, "%s Attempt To Release NULL Ptr", "Clipper");
		}
		a2a.dwFlags = 7;
		a2a.dwWidth = ptr_crctx->width;
		a2a.dwHeight = ptr_crctx->height;
		a2a.ddsCaps.dwCaps = 8256;
		v16 = ptr_crctx->ddraw->lpVtbl->CreateSurface(
			ptr_crctx->ddraw,
			&a2a,
			&ptr_crctx->buf_back,
			0);
		if (sub_40179E(v16))
		{
			CloseDirectX();
			return 0;
		}
	}
	if (flags & 0x10 && flags & 0x80)
	{
		sub_4DEB10(3, "ZBUFFER NOT WORKING, NOT CREATED TODO");
		/*sub_4DEB10(3, "Creating ZBuffer");
		memset(&a2a, 0, sizeof(a2a));
		a2a.dwSize = 124;
		a2a.dwFlags = DDSD_PIXELFORMAT | DDSD_WIDTH | DDSD_HEIGHT | DDSD_CAPS;
		a2a.ddsCaps.dwCaps = DDCAPS_OVERLAYSTRETCH | DDCAPS_READSCANLINE;
		a2a.dwWidth = ptr_crctx->width;
		a2a.dwHeight = ptr_crctx->height;
		qmemcpy(
			&a2a.ddpfPixelFormat,
			&ptr_ctx->graphicsAdapters[ptr_ctx->curGfxAdapt]
			.accelAdapters[ptr_ctx->curAccelAdapt]
			.zBufFormats->pixFormat,
			sizeof(a2a.ddpfPixelFormat));
		v11 = ptr_crctx->ddraw->lpVtbl->CreateSurface(
			ptr_crctx->ddraw,
			&a2a,
			&ptr_crctx->buf_z,
			0);
		if (sub_40179E(v11))
		{
			CloseDirectX();
			return 0;
		}
		v17 = ptr_crctx->buf_back->lpVtbl->AddAttachedSurface(
			ptr_crctx->buf_back,
			ptr_crctx->buf_z);
		sub_40179E(v17);
		sub_4DEB10(3, "ZBuffer Created %x", ptr_crctx->buf_z);*/
	}
	v18 = ptr_ctx->graphicsAdapters;
	if (DXCreateD3DDevice(
		ptr_crctx->d3d,
		ptr_ctx->graphicsAdapters[ptr_ctx->curGfxAdapt]
		.accelAdapters[ptr_ctx->curAccelAdapt]
		.guid,
		ptr_crctx->buf_back,
		&ptr_crctx->d3d_dev))
	{
		ptr_crctx->d3d_dev_bis = ptr_crctx->d3d_dev;
		if (DXCreateViewport(
			ptr_crctx->d3d,
			ptr_crctx->d3d_dev,
			ptr_crctx->width,
			ptr_crctx->height,
			&ptr_crctx->viewport))
		{
			v19 = ptr_crctx->d3d_dev->lpVtbl->SetRenderTarget(
				ptr_crctx->d3d_dev,
				ptr_crctx->buf_back,
				0);
			sub_40179E(v19);
			if (!(ptr_crctx->flags & 0x80))
				sub_40193D();
			result = 1;
		}
		else
		{
			CloseDirectX();
			result = 0;
		}
	}
	else
	{
		CloseDirectX();
		result = 0;
	}
	return result;
	S_Warn("[DXCreate] - Unimplemented!\n");
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	InitConsole();

	memset(&dxctx, 0, sizeof(dxctx));

	//S_Warn("[WinMain] - Unimplemented!\n");

	HWND v4; // eax@1
	HWND v5; // eax@3
	int v6; // eax@5
	HWND v8; // eax@8
	HWND v9; // esi@15
	HDC v10; // edi@15
	struct dispmode* v11; // ecx@15
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
		DXInitialise(&dxctx, v8);
		if (byte_57A098 || !(unsigned __int8)sub_402F77())
		{
			if (!(unsigned __int8)InitSetupDialog())
			{
				free(gfScriptFile);
				free(gfStringOffset);
				WinClose();
				return 0;
			}
			sub_402F77();
		}
		SetWindowPos(hWnd, 0, dxctx.windowPos.left, dxctx.windowPos.top, 0, 0, 5u);
		v9 = GetDesktopWindow();
		v10 = GetDC(v9);
		dword_D9AC2C = GetDeviceCaps(v10, 12);
		ReleaseDC(v9, v10);
		dword_D9ABFD = 0;
		dword_D9ABF9 = 0;
		byte_D9AC2B = 0;
		v11 = ptr_ctx->graphicsAdapters[ptr_ctx->curGfxAdapt].accelAdapters[ptr_ctx->curAccelAdapt].displayModes;
		if (!DXCreate(
			v11[ptr_ctx->curDispMode].width,
			v11[ptr_ctx->curDispMode].height,
			v11[ptr_ctx->curDispMode].depth,
			dword_D9AC27,
			&dxctx,
			hWnd,
			WS_CAPTION))
		{
			MessageBoxA(0, &gfStringWad[gfStringOffset[286]], Caption, 0);
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
