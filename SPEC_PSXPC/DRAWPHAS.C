#include "DRAWPHAS.H"

#include "3D_GEN.H"
#include "DRAWSPKS.H"
#include "LARA.H"
#include "LOAD_LEV.H"
#include "SPECIFIC.H"

long DrawPhaseGame()//63F04, 
{
	short scalarx; // $a3
	short scalary; // $t0
	short scalarz; // $t1

	mQuickW2VMatrix();

	struct lara_info* a1 = &lara;
	
	if (lara.poisoned != lara.dpoisoned)
	{
		if (lara.dpoisoned > 4096)
		{
			lara.dpoisoned = 4096;
		}
		
		//loc_63F44
		lara.poisoned = ((lara.poisoned - lara.dpoisoned) >> 4) + lara.poisoned;

		int temp = ((lara.poisoned - lara.dpoisoned) >> 4);

		if (temp < 0)
		{
			temp = -temp;
		}//loc_63F74

		if (temp < 16)
		{
			lara.poisoned = lara.dpoisoned;
		}

	}//loc_63F88

	//a2 = 0x000A000
	/*
	


	*/
	S_Warn("[DrawPhaseGame] - Unimplemented!\n");
	return 2;//hack
}

void UpdateSky()
{
	S_Warn("[UpdateSky] - Unimplemented!\n");
}


void mQuickW2VMatrix()
{
	MatrixSP = 0;
	Matrix = &MatrixStack[0];

	Matrix->m00 = phd_mxptr[1];
	Matrix->m01 = phd_mxptr[0];
	Matrix->m02 = phd_mxptr[4];
	Matrix->m10 = phd_mxptr[2];
	Matrix->m11 = phd_mxptr[6];
	Matrix->m12 = phd_mxptr[5];
	Matrix->m20 = phd_mxptr[9];
	Matrix->m21 = phd_mxptr[8];

#if 0
	ctc2	$at, $0
	ctc2	$a1, $1
	ctc2	$a3, $2
	ctc2	$t1, $3
#endif

	Matrix->m22 = phd_mxptr[10];
	Matrix->tx = phd_mxptr[3];
	Matrix->ty = phd_mxptr[7];
	Matrix->tz = phd_mxptr[11];

#if 0 
	ctc2	$at, $4
	ctc2	$v0, $5
	ctc2	$a1, $6
	ctc2	$a2, $7
#endif

	CamGTE.m00 = w2v_matrix[0];
	CamGTE.m01 = w2v_matrix[1];
	CamGTE.m02 = w2v_matrix[2];

	CamGTE.m10 = w2v_matrix[4];
	CamGTE.m11 = w2v_matrix[5];
	CamGTE.m12 = w2v_matrix[6];

	CamGTE.m20 = w2v_matrix[8];
	CamGTE.m21 = w2v_matrix[9];
	CamGTE.m22 = w2v_matrix[10];
}