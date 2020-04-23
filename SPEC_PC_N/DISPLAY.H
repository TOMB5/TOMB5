#ifndef DISPLAY_H
#define DISPLAY_H

#include "GLOBAL.H"
#include "TEXT.H"

void InitWindow(int x, int y, int width, int height, int nearz, int farz, int view_angle);

void PrintString(unsigned short x, unsigned short y, unsigned char colourFlag, const char* string, unsigned short flag);

void DrawChar(uint16_t x, uint16_t y, uint16_t a2, const CHARDEF* def);

void setXY4(D3DTLVERTEX p[4], int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3, int z, WORD* a10);

extern bool in_loading_screen;

#endif