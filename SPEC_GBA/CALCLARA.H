#ifndef CALCLARA_H
#define CALCLARA_H

extern void S_SetupClutAdder(long unk);
extern void DEL_CalcLaraMatrices_Normal_ASM(short* frame, long* bone, int flag);
extern void DEL_CalcLaraMatrices_Interpolated_ASM(short* frame1, short* frame2, int frac, int rate, long* bone, int flag);
extern short* GetBoundsAccurate(struct ITEM_INFO* item);
extern void snaff_current_gte_matrix_V1(int* mat);
extern void DEL_CalcLaraMatrices_Normal_ASM(short* frame, long* bone, int unk);
extern void GetLaraJointPos(struct PHD_VECTOR* pos, long joint);
extern short* GetBestFrame(struct ITEM_INFO* item);

//MATHS.C
extern void ScaleCurrentMatrix(long bStoreInMatrix, long sx, long sy, long sz);

#endif