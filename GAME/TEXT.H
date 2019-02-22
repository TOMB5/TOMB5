#ifndef TEXT_H
#define TEXT_H

#include "STYPES.H"

#if PSX_VERSION
#include <LIBGTE.H>
#endif

extern char AccentTable[46][2];
extern unsigned char PulseCnt;
extern unsigned char ScaleFlag;
extern CVECTOR FontShades[10][16];

#ifdef PC_VERSION
extern int font_height;
#endif

void InitFont();

#endif