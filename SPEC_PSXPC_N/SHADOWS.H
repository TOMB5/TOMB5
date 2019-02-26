#ifndef SHADOWS_H
#define SHADOWS_H

#include <stdint.h>
#include "STYPES.H"

extern void S_DrawGouraudBar(int x, int y, int width, int value, GouraudBarColourSet* colour);
extern long OptimiseOTagR(unsigned long* ot, int nOTSize);

#endif
