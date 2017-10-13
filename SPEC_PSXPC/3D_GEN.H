#ifndef THREED_GEN_H
#define THREED_GEN_H

#include "SPECTYPES.H"

extern long phd_left;
extern long phd_right;
extern long phd_top;
extern long phd_bottom;
extern long phd_persp;
extern long w2v_matrix[12];
extern long* phd_mxptr;
extern long matrix_stack[24];
extern PHD_3DPOS viewer;
extern VECTOR3D CamPos;
extern VECTOR3D CamTgt;

extern void phd_InitWindow(int view_angle);
extern long mGetAngle(long x, long z, long tx, long tz);

#define SCREEN_WIDTH 512
#define SCREEN_HEIGHT 240

#endif