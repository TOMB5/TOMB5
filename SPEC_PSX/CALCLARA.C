#include "CALCLARA.H"

#include "SPECIFIC.H"

void S_SetupClutAdder(long unk)
{
#if PSX_VERSION
	__asm__ volatile("ctc2 %0, $28": "=r" (unk) : );
#endif
}

void DEL_CalcLaraMatrices_Normal_ASM(short* frame, long* bone, int flag)
{
	S_Warn("[DEL_CalcLaraMatrices_Normal_ASM] - Unimplemented!\n");
}

void DEL_CalcLaraMatrices_Interpolated_ASM(short* frame1, short* frame2, int frac, int rate)
{
	S_Warn("[DEL_CalcLaraMatrices_Interpolated_ASM] - Unimplemented!\n");
}