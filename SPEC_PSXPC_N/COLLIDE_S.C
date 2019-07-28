#include "COLLIDE_S.H"

#include "DRAW.H"
#include "GAMEFLOW.H"

void UpdateSky()//7CE88(<), 7EECC(<) (F)
{
	int v1;

	v1 = SkyPos + gfLayer1Vel;

	if ((gfLevelFlags & GF_LVOP_LAYER1_USED))
	{
		if (v1 < 0)
		{
			v1 += 3280;
		}
		else if(v1 > 3280)
		{
			//loc_7CEB0
			v1 -= 3280;
		}

		SkyPos = v1;
	}//loc_7CEC0

	if ((gfLevelFlags & GF_LVOP_LAYER2_USED))
	{
		v1 = SkyPos2 + gfLayer2Vel;

		if (v1 < 0)
		{
			v1 += 3280;
			//j loc_7CEF8
		}
		else if (v1 > 3280)
		{
			v1 -= 3280;
		}

		SkyPos2 = v1;

	}//locret_7CEFC
}