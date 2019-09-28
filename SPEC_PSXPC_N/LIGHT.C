#include "LIGHT.H"

#include "MATHS.H"
#include "LOAD_LEV.H"
#include "GTEREG.H"

void CalculateObjectLighting(struct ITEM_INFO* item/*a0*/, short* frmptr/*a1*/, struct STASHEDOBJ* sobject/*s0*/, short numnodestodraw/*s1*/, int t1)
{
	if (item->shade < 0)
	{
		R11 = 4096;
		R12 = 0;
		R13 = 0;
		R21 = 0;
		R22 = 4096;
		R23 = 0;
		R31 = 0;
		R32 = 0;
		R33 = 4096;
		TRX = 0;
		TRY = 0;
		TRZ = 0;
		Matrix++;
		mRotYXZ(item->pos.y_rot, item->pos.x_rot, item->pos.z_rot);
		mTranslateXYZ((frmptr[0] + frmptr[1]) >> 1, (frmptr[2] + frmptr[4]) >> 1, (frmptr[3] + frmptr[5]) >> 1);
		mPopMatrix();
		//S_CalculateLight(item->pos.x_pos + TRX, item->pos.y_pos + TRY, item->pos.z_pos + TRZ, item->room_number, &item->il);
	}
	else
	{
		//loc_8668C
		//S_CalculateStaticMeshLight(item->pos.x_pos, item->pos.y_pos, item->pos.z_pos, 0x7FFF);
	}
}