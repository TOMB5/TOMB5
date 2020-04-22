#ifndef TEXT_H
#define TEXT_H

#include "STYPES.H"
#include "SPECIFIC.H"

#if PSX_VERSION
#include <LIBGTE.H>
#endif

extern char AccentTable[46][2];
extern unsigned char PulseCnt;
extern unsigned char ScaleFlag;
#if PC_VERSION
struct CVECTOR2
{
    CVECTOR color;
    CVECTOR specular;
};

extern CVECTOR2 FontShades[10][16];

extern int font_height;

extern CHARDEF CharDef[106];
#else
extern CVECTOR FontShades[10][16];
#endif


void InitFont();

#endif