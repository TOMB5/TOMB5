#ifndef PHD_MATH_H
#define PHD_MATH_H

extern long phd_sqrt_asm(long val);
extern void ScaleCurrentMatrix(long a0, long sx, long sy, long sz);
extern void mPushUnitMatrix();
extern void mPopMatrix();

#endif