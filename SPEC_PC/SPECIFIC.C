#include "SPECIFIC.H"
#define _X86_
#include <SDKDDKVer.h>
#include <windows.h>
#include <winbase.h>
#include <stdio.h>
#include "WINMAIN.H"
#include <time.h>
#include <dsound.h>
#include "PCSOUND.H"
#include "ERROR.H"

HANDLE Handles;
HANDLE dword_579FA4;
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

signed int __cdecl sub_4D30E0(_WORD *a1)
{
	signed int result; // eax@1
	__int16 v2; // [sp+0h] [bp-8h]@0

	result = 0;
	if (HIBYTE(v2) & 3 || (v2 & 0x3F) != 63 || HIBYTE(v2) & 0xC)
		result = 1;
	*a1 = v2;
	return result;
}

void S_Warn(char* warning_message)
{
	char buf[512];
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	sprintf(buf, "[%d:%d:%d] %s", tm.tm_hour, tm.tm_min, tm.tm_sec, warning_message);
	/*char buf1[512];
	strcpy(buf1, buf);
	int len = strlen(buf1);
	if (buf1[len - 1] == '\n')
	{
		buf1[len - 1] = '\r';
		buf1[len] = '\n';
		buf1[len + 1] = 0;
	}*/

	int len = strlen(buf);
	if (buf[len - 1] != '\n')
	{
		buf[len] = '\n';
		buf[len + 1] = 0;
	}

	OutputDebugString(buf);
	printf(buf);
}

HWND sub_4DEB10(char a1, char* format, ...)
{
	HWND result; // eax@1
	void *v3; // eax@2
	HWND v4; // esi@2
	char *v5; // esi@3
	char *v6; // esi@3
	char *v7; // ebx@3
	signed int v8; // ecx@3
	signed int v9; // ebp@3
	signed int v10; // edi@4
	char v11; // al@5
	HWND hWnd; // [sp+4h] [bp-404h]@1
	char v13[0x40C]; // [sp+8h] [bp-400h]@3
	va_list va; // [sp+414h] [bp+Ch]@1

	va_start(va, format);
	vsnprintf(v13, sizeof(v13), format, va);
	char buf[0x40C];
	sprintf(buf, "[DBLOG] %s", v13);
	S_Warn(buf);
	result = FindWindowA(ClassName, WindowName);
	hWnd = result;
	if (result)
	{
		v3 = (void *)sub_4DEA40("DBLOGMAPMEM");
		dword_E4ACA4 = v3;
		result = (HWND)sub_4DEA20(v3);
		v4 = result;
		if (result)
		{			
			v5 = (char *)v4 + dword_E4ACB8;
			*v5 = a1;
			v6 = v5 + 1;
			v7 = v13;
			v8 = strlen(v13) + 1;
			v9 = 1;
			if (v8 > 0)
			{
				v10 = v8;
				do
				{
					v11 = *v7;
					if (*v7 != 10 && v11)
					{
						*v6++ = v11;
					}
					else
					{
						if (v9 > 1)
						{
							*v6 = 0;
							SendMsg(hWnd, dword_E4ACB8);
							v6 += 2;
							dword_E4ACB8 += v9 + 1;
							*(v6 - 1) = a1;
						}
						v9 = 0;
					}
					++v9;
					++v7;
					--v10;
				} while (v10);
			}
			if (dword_E4ACB8 > 1047552)
			{
				dword_E4ACB8 = 0;
				SendMessageA(hWnd, dword_E4ACAC, 0, 0);
			}
			result = (HWND)CloseHandle(dword_E4ACA4);
		}
	}
	return result;
}

int __cdecl StopSample(int snum)
{
	int result; // eax@1
	int v2; // esi@2
	LPDIRECTSOUNDBUFFER buf; // edi@2
	int v4; // eax@3
	int v5; // eax@3

	result = snum;
	if (snum >= 0)
	{
		v2 = snum;
		buf = samples[snum].buf;
		if (buf)
		{
			v4 = buf->lpVtbl->Stop(buf);
			sub_40179E(v4);
			v5 = buf->lpVtbl->Release(buf);
			result = sub_40179E(v5);
			samples[v2].field2 = 0;
			samples[v2].buf = 0;
		}
	}
	return result;
}

int S_SoundStopAllSamples()
{
	int result;

	for (int i = 0; i < 32; i++)
		result = StopSample(i);

	return result;
}
