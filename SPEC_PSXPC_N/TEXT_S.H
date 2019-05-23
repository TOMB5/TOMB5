#ifndef TEXT_S_H
#define TEXT_S_H

#include "TYPES.H"

extern void UpdatePulseColour();
extern void PrintString(unsigned short x, unsigned short y, unsigned char colourFlag, char* string, unsigned short flag);
extern int GetStringLength(char* string, unsigned short* a1, unsigned short* a2);
extern void GetStringDimensions(char* string, unsigned short* w, unsigned short* h);
extern void DrawChar(unsigned short a0, unsigned short a1, unsigned short colourFlag, struct CHARDEF* a3);
extern void draw_outlines();
extern void _draw_gbackground2(int x, int y, int w, int h);
extern void _DelDrawSprite(int x, int y, int w, int h);
extern char aUEAAAAEEEAAEOO[];
extern CHARDEF word_9230E[];
extern CHARDEF loc_92020[];

#endif