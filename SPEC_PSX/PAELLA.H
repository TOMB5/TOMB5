#ifndef PAELLA_H
#define PAELLA_H

#ifdef PAELLA

#include "SPECTYPES.H"

void gte_ldlzc(long data);
void gte_SetRotMatrix(struct MATRIX3D* m);
void gte_SetTransMatrix(struct MATRIX3D* m);
void gte_ReadLightMatrix(struct MATRIX3D* m);
void gte_ReadRotMatrix(struct MATRIX3D* m);
void gte_SetLightMatrix(struct MATRIX3D* m);
void gte_ldtr(long x, long y, long z);
void gte_SetGeomOffset(long ofx, long ofy);
void gte_SetGeomScreen(long h);

#endif

#endif