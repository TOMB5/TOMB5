#include "DRAWPHAS.H"
#include "SPECIFIC.H"
#include <stdio.h>

void PrintString(long x, long y, char* string)
{
	char* buf = (char*)malloc(strlen(string) + 64);
	sprintf(buf, "PrintString - X:%d Y:%d - %s\n", x, y, string);
	S_Warn(buf);
}
