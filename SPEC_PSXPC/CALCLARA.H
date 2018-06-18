#ifndef CALCLARA_H
#define CALCLARA_H

extern void S_SetupClutAdder(long unk);
extern void DEL_CalcLaraMatrices_Normal_ASM(short* frame, long* bone, int flag);
extern void DEL_CalcLaraMatrices_Interpolated_ASM(short* frame1, short* frame2, int frac, int rate);
extern short* GetBoundsAccurate(struct ITEM_INFO* item);

#endif