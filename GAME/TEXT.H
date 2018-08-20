#ifndef TEXT_H
#define TEXT_H

#include "SPECTYPES.H"

extern char AccentTable[46][2];
extern unsigned char PulseCnt;
extern unsigned char ScaleFlag;
extern struct CVECTOR FontShades[10][16];

#ifdef PC_VERSION
extern int font_height;
#endif

void InitFont();

#endif