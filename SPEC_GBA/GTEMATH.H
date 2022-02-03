#ifndef GTEMATH_H
#define GTEMATH_H

#include "STYPES.H"

extern VECTOR MVMVA(int x, int y, int z, char shift);
extern VECTOR MVMVA(int x, int y, int z);
extern SVECTOR MVMVA(SVECTOR* v0, int tx, int ty, int tz);
extern void RTPT(int tx, int ty, int tz, SVECTOR* v);
extern void RTPS(int tx, int ty, int tz, SVECTOR* v);
extern int SXY[3];
extern short SZ[4];

#endif