#ifndef DRAWSKY_H
#define DRAWSKY_H

#include <LIBGTE.H>

extern void DrawFlatSky_ASM(CVECTOR layer, short pos, int flags);
extern void DrawSkyMesh(short* mesh);
extern int HorClipXY(int t1, int t2, int t3, int t4);
extern void DrawSubdivChunk(int* a3, int t6, int t7, unsigned long* t4, int* t9);
extern int SkyClipXY(int v0, int v1, int a0, int a1);

#endif