#ifndef DISPLAY_H
#define DISPLAY_H

#include "GLOBAL.H"

void InitWindow(int x, int y, int width, int height, int nearz, int farz, int view_angle);
void PrintString(long x, long y, int unk1, char* string, int unk2);
void DrawChar(uint16_t x, uint16_t y, uint16_t a2, CHARDEF* def);

enum PRINT_OPTIONS
{
	PRINT_CENTER = 1 << 15,
};

#endif