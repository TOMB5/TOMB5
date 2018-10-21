#include "CALCLARA.H"

#include "SPECIFIC.H"

#ifndef USE_ASM
void S_SetupClutAdder(long unk)
{
	S_Warn("[DEL_CalcLaraMatrices_Normal_ASM] - Unimplemented!\n");
}

void DEL_CalcLaraMatrices_Normal_ASM(short* frame, long* bone, int flag)
{
	S_Warn("[DEL_CalcLaraMatrices_Normal_ASM] - Unimplemented!\n");
}

void DEL_CalcLaraMatrices_Interpolated_ASM(short* frame1, short* frame2, int frac, int rate)
{
	S_Warn("[DEL_CalcLaraMatrices_Interpolated_ASM] - Unimplemented!\n");
}

short* GetBoundsAccurate(struct ITEM_INFO* item)//858F8, 8793C
{
	S_Warn("[GetBoundsAccurate] - Unimplemented!\n");
}
#endif