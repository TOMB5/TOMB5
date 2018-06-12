#ifndef MATHS_H
#define MATHS_H

#include "TYPES.H"

extern long mGetAngle(long x, long z, long tx, long tz);
extern void mQuickW2VMatrix();
extern long phd_sqrt_asm(long value);
extern void ScaleCurrentMatrix(long a0, long sx, long sy, long sz);
extern void mPushMatrix();
extern void mPopMatrix();
extern void mPushUnitMatrix();
extern void mTranslate();
extern void mTranslateAbsXYZ(long x, long y, long z);
extern void mTranslateXYZ(long x, long y, long z);
extern void mRotX();
extern void mRotY(long ry);
extern void mRotYXZ();
extern void mRotZ();
extern void mRotSuperPackedYXZ();
extern void mRotPackedYXZ();
extern void SetRotation();
extern void setrot(struct MATRIX3D* m, long m00, long m02, long m11, long m20, long m22);
extern void mLoadMatrix(struct MATRIX3D* m);
extern void mCopyMatrix(struct MATRIX3D* m);
extern void ASM_GetBounds();
extern void GetBounds();
extern void mSetTrans(long x, long y, long z);
extern void mClipBoundingBox();
extern void InitInterpolation(long frac, long rate, struct MATRIX3D* m);
extern void iPushMatrix0();
extern void iPushMatrix(struct MATRIX3D* m);
extern void iPopMatrix0();
extern void iPopMatrix(struct MATRIX3D* m, struct MATRIX3D* m2);
extern void mPushMatrix0();
extern void mmPushMatrix(struct MATRIX3D* m);
extern void GetRoomBoundsAsm(short room_number);
extern void phd_GetVectorAngles(long dx, long dy, long dz, short* angles);
extern void phd_LookAt(long x, long y, long z, long tx, long ty, long tz, long croll);
extern long phd_atan_asm(long x, long y);

#endif