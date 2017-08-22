#include "SPECIFIC.H"
#define _X86_
#include <SDKDDKVer.h>
#include <windows.h>
#include <winbase.h>
#include <cstdio>

void S_Warn(char* warning_message)
{
	OutputDebugString(warning_message);
}

void PrintString(long x, long y, char* string)
{
	char* buf = (char*)malloc(strlen(string) + 64);
	sprintf(buf, "PrintString - X:%d Y:%d - %s\n", x, y, string);
	OutputDebugString(buf);
}