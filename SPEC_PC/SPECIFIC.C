#include "SPECIFIC.H"
#define _X86_
#include <SDKDDKVer.h>
#include <windows.h>
#include <winbase.h>
#include <stdio.h>
#include "WINMAIN.H"
#include <time.h>

void S_Warn(char* warning_message)
{
	char buf[512];
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	sprintf(buf, "[%d:%d:%d] %s", tm.tm_hour, tm.tm_min, tm.tm_sec, warning_message);
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
			vsprintf(v13, format, va);
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

int S_SoundStopAllSamples()
{
	S_Warn("[S_SoundStopAllSamples] - Unimplemented!\\n");
	return 0;
}
