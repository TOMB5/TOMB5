#ifndef TEXT_S_H
#define TEXT_S_H

#include "TYPES.H"

extern long GetStringLength(char* string, short* a1, short* a2);
extern void DrawChar(unsigned short a0, unsigned short a1, unsigned short a2, struct CHARDEF* a3);
extern void GetStringDimensions(char* string, unsigned short* w, unsigned short* h);

#endif