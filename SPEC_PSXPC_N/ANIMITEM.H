#ifndef ANIMITEM_H
#define ANIMITEM_H

extern int mClipBoundingBox2(short* bounds, int* fp);
extern void stash_the_info(int meshp, int* fp);
extern void mmPopMatrix2(int* fp);
extern void mLoadMatrix2(int* a0, int* fp);
extern void CalcAllAnimatingItems_ASM();

#endif