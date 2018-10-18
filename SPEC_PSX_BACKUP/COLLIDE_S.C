#include "COLLIDE_S.H"

#include "DRAW.H"
#include "GAMEFLOW.H"

void UpdateSky()//7CE88(<), 7EECC(<) (F)
{
	if (gfLevelFlags & GF_LVOP_LAYER1_USED)
	{
		SkyPos += gfLayer1Vel;
		if (SkyPos >= 0 && SkyPos <= 9728)
		{
			SkyPos += 9728;
		}
		else
		{
			SkyPos -= 9728;
		}
	}

	if (gfLevelFlags & GF_LVOP_LAYER2_USED)
	{
		SkyPos2 += gfLayer2Vel;
		if (SkyPos2 >= 0 && SkyPos2 <= 9728)
		{
			SkyPos2 += 9728;
		}
		else 
		{
			SkyPos2 -= 9728;
		}
	}
}