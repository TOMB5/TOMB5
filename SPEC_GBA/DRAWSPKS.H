#ifndef DRAWSPKS_H
#define DRAWSPKS_H

#include "STYPES.H"

extern long TorchWibble[8];
extern struct MATRIX3D CamGTE;
extern struct MATRIX3D LightPos;

extern void S_DrawDarts(struct ITEM_INFO* item);
extern void S_DrawSparks();

#endif