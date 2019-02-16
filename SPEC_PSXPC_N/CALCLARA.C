#include "CALCLARA.H"

#include "SPECIFIC.H"
#include "DRAW.H"

void S_SetupClutAdder(long unk)
{
	S_Warn("[S_SetupClutAdder] - Unimplemented!\n");
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
	int rate;
	short* frmptr[2];
	int frac = GetFrames(item, frmptr, &rate);

	if (frac == 0)
		return frmptr[0];

	short* bptr = interpolated_bounds;

	for (int i = 0; i < 6; i++, bptr++, frmptr[0]++, frmptr[1]++)
	{
		*bptr = *frmptr[0] + (*frmptr[1] - *frmptr[0]) * frac / rate;
	}

	return interpolated_bounds;
}

void snaff_current_gte_matrix_V1(MATRIX3D* m)
{
}
