#ifndef DRAWSKY_H
#define DRAWSKY_H

#include <LIBGTE.H>

extern void DrawFlatSky_ASM(CVECTOR layer, short pos, int flags);
extern void DrawSkyMesh(short* mesh);
extern int HorClipXY(int t1, int t2, int t3, int t4);

#endif