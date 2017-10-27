#ifndef MATHS_H
#define MATHS_H

#include "TYPES.H"

extern long phd_sqrt_asm(long value);
extern void ScaleCurrentMatrix(long a0, long sx, long sy, long sz);
extern void mPushUnitMatrix();
extern void mPopMatrix();
extern void iPopMatrix(struct MATRIX3D* m, struct MATRIX3D* m2);
extern void mPushMatrix();
extern void iPushMatrix(struct MATRIX3D* m);
extern void mSetTrans(long x, long y, long z);
extern void mLoadMatrix(struct MATRIX3D* m);
extern void setrot(struct MATRIX3D* m, long m00, long m02, long m11, long m20, long m22);
extern void mTranslateXYZ(long x, long y, long z);
extern void mTranslateAbsXYZ(long x, long y, long z);
extern void mRotY(long ry);
extern void mCopyMatrix(struct MATRIX3D* m);

#endif