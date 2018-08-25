#include "CALCLARA.H"
#include "SPECIFIC.H"
#include "DRAW.H"

short* GetBoundsAccurate(struct ITEM_INFO* item)//858F8, 8793C (F)
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
