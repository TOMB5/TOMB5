#ifndef MATHS_H
#define MATHS_H

#include "TYPES.H"
#include "LIBGTE.H"

extern long mGetAngle(long x, long z, long tx, long tz);
extern void mQuickW2VMatrix();
extern long phd_sqrt_asm(long value);
extern void ScaleCurrentMatrix(long bStoreInMatrix, long sx, long sy, long sz);
extern void mPushMatrix();
extern void mPopMatrix();
extern void mPushUnitMatrix();
extern void mTranslate();
extern void mTranslateAbsXYZ(long x, long y, long z);
extern void mTranslateXYZ(long x, long y, long z);
extern void mRotX(long rx);
extern void mRotY(long ry);
extern void mRotYXZ(short y, short x, short z);
extern void mRotZ(long rz);
extern void gte_sttr(struct PHD_VECTOR* vec);
extern void mRotSuperPackedYXZ(short** a0, long a1);
extern void mRotPackedYXZ(long yxz);
extern void SetRotation(int t0, int t1, int t2, int t3, int t4);
extern void setrot(struct MATRIX3D* m, long t0, long t1, long t2, long t3, long t4);
extern void mLoadMatrix(struct MATRIX3D* m);
extern void mCopyMatrix(struct MATRIX3D* m);
extern void ASM_GetBounds();
extern void GetBounds();
extern void mSetTrans(long x, long y, long z);
extern void mClipBoundingBox(short* bounds);
extern void InitInterpolation(long frac, long rate, struct MATRIX3D* m);
extern void iPushMatrix0();
extern void iPushMatrix();
extern void iPopMatrix0();
extern void iPopMatrix();
extern void mPushMatrix0();
extern void mmPushMatrix(int* fp);
extern void GetRoomBoundsAsm(short room_number);
extern void phd_GetVectorAngles(long dx, long dy, long dz, short* angles);
extern void phd_LookAt(long x, long y, long z, long tx, long ty, long tz, long croll);
extern long phd_atan_asm(long x, long y);
extern long mSqrt(long x);
extern void mRotBoundingBoxNoPersp(short* bounds, short* tbounds);
extern void phd_GenerateW2V(struct PHD_3DPOS* view);
extern void iTranslateXYZ2(short x, short y, short z, short x2, short y2, short z2);
extern void iTranslateXYZ(long x, long y, long z);
extern long GetFrames(struct ITEM_INFO* item/*$a0*/, short* frames[]/*a1*/, int* rate/*$a2*/);
extern void iRotSuperPackedYXZ(short** a0, long a1);
extern void iRotY(int a0);
extern void iRotX(int a0);
extern void iRotZ(int a0);

#endif