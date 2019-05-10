#ifndef SHADOWS_H
#define SHADOWS_H

#include <stdint.h>
#include "STYPES.H"

extern void S_DrawGouraudBar(int x, int y, int width, int value, struct GouraudBarColourSet* colour);
extern long OptimiseOTagR(unsigned long* ot, int nOTSize);
extern void DelBox(short x, short y, short w, short h, int color);
extern void DelLine(short x0, short y0, short x1, short y1, int color1, int color2);

#endif
