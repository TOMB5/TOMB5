#include "DRAWPHAS.H"
#include "SPECIFIC.H"
#include <stdio.h>

void PrintString(long x, long y, int unk1, char* string, int unk2)
{
	char* buf = (char*)malloc(strlen(string) + 64);
	sprintf(buf, "PrintString - X:%d Y:%d Unk1:%d Flags:%4x - %s\n", x, y, unk1, unk2, string);
	S_Warn(buf);
}
