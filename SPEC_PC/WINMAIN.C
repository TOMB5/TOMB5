#include "WINMAIN.H"
#include "SPECIFIC.H"
#include <cstdio>
#include <io.h>
#include <fcntl.h>
#include <crtdbg.h>
#include "GAMEFLOW.H"
#include <process.h>
#include <mm3dnow.h>
#include <ddraw.h>
#include <dsound.h>


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
	CHAR String1; // [sp+Ch] [bp-18h]@1
	CHAR FileName[4]; // [sp+14h] [bp-10h]@1

	strcpy(FileName, "c:\\script.dat");
	v0 = GetLogicalDrives();
	GameDrive = 'A';
	lstrcpyA(&String1, "A:\\");
	if (v0)
	{
		while (1)
		{
			if (v0 & 1)
			{
				String1 = GameDrive;
				if (GetDriveTypeA(&String1) == 3)
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
							return aTheSpecifiedWa;
						if (a1 > -2005401590)
						{
							if (a1 == -2005401570)
								return aTheBufferContr;
							if (a1 == -2005401550)
								return aThisFunctionIs;
							if (a1 == -2005401530)
								return aTheCallerDoesN;
						}
						else
						{
							if (a1 == -2005401590)
								return aTheRequestFail;
							if (a1 == -2005530589)
								return aTooManyPrimiti;
							if (a1 == -2005530588)
								return aInvalidMatrix;
							if (a1 == -2005530586)
								return aConflictingT_0;
						}
						return aUndefinedError;
					}
					if (a1 <= -2005401440)
					{
						if (a1 == -2005401440)
							return aAnotherApplica;
						if (a1 == -2005401480)
							return aNoSoundDriverI;
						if (a1 == -2005401470)
							return aTheObjectIsAlr;
						if (a1 == -2005401450)
							return aTheBufferMemor;
						return aUndefinedError;
					}
					if (a1 == -2005401430)
					{
						result = aTheIdirectsoun;
					}
					else
					{
						if (a1)
							return aUndefinedError;
						result = aTheRequestComp;
					}
				}
				else if (a1 == -2005530590)
				{
					result = aUnsupportedTex;
				}
				else
				{
					switch (a1)
					{
					case -2005530622:
						result = aColorkeyAttach;
						break;
					case -2005530594:
						result = aConflictingTex;
						break;
					case -2005530591:
						result = aConflictingRen;
						break;
					case -2005530601:
						result = aStencilBufferN;
						break;
					case -2005530595:
						result = aTooManyOperati;
						break;
					case -2005530596:
						result = aUnsupportedAlp;
						break;
					case -2005530597:
						result = aUnsupportedA_0;
						break;
					case -2005530598:
						result = aUnsupportedCol;
						break;
					case -2005530599:
						result = aUnsupportedC_0;
						break;
					case -2005530593:
						result = aUnsupportedFac;
						break;
					case -2005530611:
						result = aVertexBufferCr;
						break;
					case -2005530610:
						result = aVertexBufferLo;
						break;
					case -2005530612:
						result = aVertexBufferOp;
						break;
					case -2005530600:
						result = aWrongTextureFo;
						break;
					case -2005530602:
						result = aZbufferNotPres;
						break;
					default:
						return aUndefinedError;
					}
				}
			}
			else if (a1 == -2005530624)
			{
				result = aInvalidVertexF;
			}
			else
			{
				switch (a1)
				{
				case -2005531902:
					result = aAlreadyInBegin;
					break;
				case -2005531928:
					result = aInvalidPalette;
					break;
				case -2005531922:
					result = aLightSetFailed;
					break;
				case -2005531921:
					result = aLightHasViewpo;
					break;
				case -2005531920:
					result = aLightNotInThis;
					break;
				case -2005531897:
					result = aNoCurrentViewp;
					break;
				case -2005531901:
					result = aNotInBeginScen;
					break;
				case -2005531900:
					result = aNoViewports;
					break;
				case -2005531910:
					result = aBeginSceneFail;
					break;
				case -2005531909:
					result = aEndSceneFailed;
					break;
				case -2005531912:
					result = aSceneInScene;
					break;
				case -2005531911:
					result = aSceneNotInScen;
					break;
				case -2005531925:
					result = aSurfaceNotInVi;
					break;
				case -2005531899:
					result = aViewportDataNo;
					break;
				case -2005531898:
					result = aViewportHasNoD;
					break;
				case -2005531927:
					result = aZbufferNeedsSy;
					break;
				case -2005531926:
					result = aZbufferNeedsVi;
					break;
				default:
					return aUndefinedError;
				}
			}
		}
		else if (a1 == -2005531929)
		{
			result = aMaterialGetDat;
		}
		else
		{
			switch (a1)
			{
			case -2005532032:
				result = aAnAttemptToPag;
				break;
			case -2005532012:
				result = aAnAttemptToP_0;
				break;
			case -2005532052:
				result = aADeviceContext;
				break;
			case -2005531973:
				result = aSurfacesCreate;
				break;
			case -2005531981:
				result = aTheDataHasExpi;
				break;
			case -2005532080:
				result = aTheRequestedOp;
				break;
			case -2005531982:
				result = aThereIsMoreDat;
				break;
			case -2005532070:
				result = aAnAttemptWas_5;
				break;
			case -2005532042:
				result = aAnAttemptWas_6;
				break;
			case -2005532072:
				result = aTheDeviceDoesN;
				break;
			case -2005532071:
				result = aTheSurfaceIsAn;
				break;
			case -2005531992:
				result = aAnAttemptIsM_0;
				break;
			case -2005531977:
				result = aTheVideoPortIs;
				break;
			case -2005531972:
				result = aBadMajorVersio;
				break;
			case -2005531971:
				result = aBadMinorVersio;
				break;
			case -2005531965:
				result = aDeviceAggregat;
				break;
			case -2005531955:
				result = aExecuteClipped;
				break;
			case -2005531962:
				result = aExecuteCreateF;
				break;
			case -2005531961:
				result = aExecuteDestroy;
				break;
			case -2005531956:
				result = aExecuteFailed;
				break;
			case -2005531960:
				result = aExecuteLockFai;
				break;
			case -2005531958:
				result = aExecuteLocked;
				break;
			case -2005531957:
				result = aExecuteNotLock;
				break;
			case -2005531959:
				result = aExecuteUnlockF;
				break;
			case -2005531966:
				result = aInitFailed;
				break;
			case -2005531967:
				result = aInvalidDevice;
				break;
			case -2005531937:
				result = aInvalidCurrent;
				break;
			case -2005531936:
				result = aInvalidPrimiti;
				break;
			case -2005531933:
				result = aInvalidRampTex;
				break;
			case -2005531935:
				result = aInvalidVertexT;
				break;
			case -2005531932:
				result = aMaterialCreate;
				break;
			case -2005531931:
				result = aMaterialDestro;
				break;
			case -2005531930:
				result = aMaterialSetDat;
				break;
			case -2005531942:
				result = aMatrixCreateFa;
				break;
			case -2005531941:
				result = aMatrixDestroyF;
				break;
			case -2005531939:
				result = aMatrixGetDataF;
				break;
			case -2005531940:
				result = aMatrixSetDataF;
				break;
			case -2005531938:
				result = aSetViewportDat;
				break;
			case -2005531934:
				result = aBadTextureSize;
				break;
			case -2005531951:
				result = aTextureCreateF;
				break;
			case -2005531950:
				result = aTextureDestroy;
				break;
			case -2005531943:
				result = aTextureGetSurf;
				break;
			case -2005531947:
				result = aTextureLoadFai;
				break;
			case -2005531949:
			case -2005531945:
				result = aTextureLockFai;
				break;
			case -2005531952:
				result = aTextureNoSuppo;
				break;
			case -2005531944:
				result = aTextureNotLock;
				break;
			case -2005531946:
				result = aTextureSwapFai;
				break;
			case -2005531948:
				result = aTextureUnlockF;
				break;
			default:
				return aUndefinedError;
			}
		}
	}
	else
	{
		if (a1 == -2005532081)
			return aTheOperation_8;
		if (a1 > -2005532288)
		{
			switch (a1)
			{
			case -2005532098:
				result = aADirectdrawcli;
				break;
			case -2005532087:
				result = aWindowsCanNotC;
				break;
			case -2005532089:
				result = aPrimaryAnd3DSu;
				break;
			case -2005532237:
				result = aAccessToThisSu;
				break;
			case -2005532105:
				result = aAnAttemptWas_1;
				break;
			case -2005532272:
				result = aNoSourceColorK;
				break;
			case -2005532110:
				result = aADirectdrawObj;
				break;
			case -2005532091:
				result = aAnAttemptWas_2;
				break;
			case -2005532101:
				result = aTheDirectdrawC;
				break;
			case -2005532102:
				result = aDirectdrawIsPr;
				break;
			case -2005532084:
				result = aTheSurfaceCann;
				break;
			case -2005532111:
				result = aTheGloballyUni;
				break;
			case -2005532093:
				result = aThePositionOfT;
				break;
			case -2005532151:
				result = aTheSpecifiedSt;
				break;
			case -2005532097:
				result = aNoBlitterHardw;
				break;
			case -2005532104:
				result = aNoDirectdrawcl;
				break;
			case -2005532086:
				result = aNoDcHasEverBee;
				break;
			case -2005532096:
				result = aNoDirectdrawRa;
				break;
			case -2005532109:
				result = aHardwareOnlyDi;
				break;
			case -2005532107:
				result = aSoftwareEmulat;
				break;
			case -2005532103:
				result = aClipperNotific;
				break;
			case -2005532094:
				result = aTheIdirectdraw;
				break;
			case -2005532100:
				result = aNoPaletteObjec;
				break;
			case -2005532099:
				result = aThereIsNoHardw;
				break;
			case -2005532092:
				result = aAnOverlayCompo;
				break;
			case -2005532090:
				result = aAnAttemptHasBe;
				break;
			case -2005532088:
				result = aAnAttemptIsMad;
				break;
			case -2005532083:
				result = aTheSurfaceBein;
				break;
			case -2005532095:
				result = aTheIdirectdr_0;
				break;
			case -2005532285:
				result = aAccessToThisPa;
				break;
			case -2005532108:
				result = aThisProcessHas;
				break;
			case -2005532106:
				result = aTheRegionPasse;
				break;
			case -2005532262:
				result = aAnAttemptWas_3;
				break;
			case -2005532252:
				result = aAnAttemptWas_4;
				break;
			case -2005532242:
				result = aAccessToTheSur;
				break;
			case -2005532232:
				result = aAccessToTheS_0;
				break;
			case -2005532222:
				result = aAccessToTheS_1;
				break;
			case -2005532212:
				result = aTheRequestedSu;
				break;
			case -2005532202:
				result = aTheHeightReque;
				break;
			case -2005532192:
				result = aTheSizeRequest;
				break;
			case -2005532182:
				result = aTheWidthReques;
				break;
			case -2005532162:
				result = aTheFourccForma;
				break;
			case -2005532152:
				result = aTheBitmaskInTh;
				break;
			case -2005532082:
				result = aTheDisplayIsCu;
				break;
			case -2005532135:
				result = aAVerticalBlank;
				break;
			case -2005532132:
				result = aThePreviousBli;
				break;
			case -2005532085:
				result = aThisSurfaceCan;
				break;
			case -2005532112:
				result = aTheProvidedR_0;
				break;
			default:
				return aUndefinedError;
			}
		}
		else
		{
			if (a1 == -2005532288)
				return aAnAttemptWas_0;
			if (a1 > -2005532462)
			{
				switch (a1)
				{
				case -2005532457:
					result = aTheSurfaceDoes;
					break;
				case -2005532452:
					result = aTheOperation_0;
					break;
				case -2005532460:
					result = aACreateFunctio;
					break;
				case -2005532450:
					result = aDirectdrawSupp;
					break;
				case -2005532447:
					result = aTheOperationRe;
					break;
				case -2005532442:
					result = aFlippingVisibl;
					break;
				case -2005532432:
					result = aNoGdiIsPresent;
					break;
				case -2005532422:
					result = aTheOperation_1;
					break;
				case -2005532412:
					result = aTheOperation_2;
					break;
				case -2005532392:
					result = aTheOperation_3;
					break;
				case -2005532382:
					result = aTheOperation_4;
					break;
				case -2005532362:
					result = aTheOperation_5;
					break;
				case -2005532356:
					result = aTheDirectdraws;
					break;
				case -2005532355:
					result = aTheDirectdra_0;
					break;
				case -2005532352:
					result = aTheDirectdra_1;
					break;
				case -2005532342:
					result = aTheOperation_6;
					break;
				case -2005532417:
					result = aTheRequestedIt;
					break;
				case -2005532337:
					result = aTheOperation_7;
					break;
				case -2005532332:
					result = aTheOperationTo;
					break;
				case -2005532322:
					result = aTheOverlaySurf;
					break;
				case -2005532312:
					result = aTheHardwareNee;
					break;
				case -2005532292:
					result = aDirectdrawDo_2;
					break;
				case -2005532402:
					result = aOperationCould;
					break;
				case -2005532290:
					result = aTheHardwareDoe;
					break;
				default:
					return aUndefinedError;
				}
			}
			else
			{
				if (a1 == -2005532462)
					return aTheOperationCa;
				if (a1 > (signed int)0x8876005A)
				{
					switch (a1)
					{
					case -2005532577:
						result = aThePrimarySurf;
						break;
					case -2005532572:
						result = aOneOrMoreOfT_0;
						break;
					case -2005532562:
						result = aDirectdrawDo_0;
						break;
					case -2005532552:
						result = aDirectdrawDo_1;
						break;
					case -2005532542:
						result = aDirectdrawRece;
						break;
					case -2005532527:
						result = aThePixelFormat;
						break;
					case -2005532522:
						result = aTheProvidedRec;
						break;
					case -2005532512:
						result = aOneOrMoreSurfa;
						break;
					case -2005532502:
						result = aNo3DHardwareOr;
						break;
					case -2005532492:
						result = aNoAlphaAcceler;
						break;
					case -2005532467:
						result = aNoClipListIsAv;
						break;
					default:
						return aUndefinedError;
					}
				}
				else
				{
					if (a1 == 0x8876005A)
						return aTheHeightOfThe;
					if (a1 <= (signed int)0x80070057)
					{
						if (a1 == 0x80070057)
							return aOneOrMoreOfThe;
						if (a1 > (signed int)0x80040110)
						{
							if (a1 == 0x800401F0)
								return aAnAttemptWasMa;
							if (a1 == 0x8007000E)
								return aDirectdrawDoes;
						}
						else
						{
							if (a1 == 0x80040110)
								return aTheObjectDoesN;
							if (a1 == 0x80004001)
								return aTheOperationIs;
							if (a1 == 0x80004002)
								return aTheRequestedCo;
							if (a1 == 0x80004005)
								return aThereIsAnUndef;
						}
						return aUndefinedError;
					}
					switch (a1)
					{
					case 0x88760005:
						result = aTheObjectHasAl;
						break;
					case 0x8876000A:
						result = aASurfaceCannot;
						break;
					case 0x88760014:
						result = aASurfaceCann_0;
						break;
					case 0x88760028:
						result = aNoSupportIsCur;
						break;
					case 0x88760037:
						result = aAnExceptionWas;
						break;
					default:
						return aUndefinedError;
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
			v5 = (*((int(__stdcall **)(LPDIRECTDRAW))lpDD->lpVtbl + 2))(lpDD);
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

signed int __cdecl DXInitialise(void *lpContext, int a2)
{
	HRESULT v2; // eax@1
	HRESULT v3; // eax@1

	sub_4DEB10(2, "DXInitialise");
	dword_86B9A4 = a2;
	sub_4DEB10(5, "Enumerating DirectDraw Devices");
	v2 = DirectDrawEnumerateA(Callback, lpContext);
	sub_40179E(v2);
	v3 = DirectSoundEnumerateA(sub_4020AE, lpContext);
	sub_40179E(v3);
	dword_86B9AC = (int)lpContext;
	return 1;
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
	dword_D9AC30 = 0;
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
