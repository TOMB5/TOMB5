#include "DRAWPHAS.H"

#include "3D_GEN.H"
#include "CONTROL.H"
#include "DELTAPAK.H"
#include "DRAWSPKS.H"
#include "GPU.H"
#include "HEALTH.H"
#include "LARA.H"
#include "LOAD_LEV.H"
#include "SPECIFIC.H"
#include "SPOTCAM.H"
#include "TOMB4FX.H"

#include <stdio.h>

long StoreBoxes = -1;
struct GAME_VECTOR LaraPos;
struct PSXTEXTI* MonitorScreenTI;
unsigned char MonitorScreenU0;
unsigned char MonitorHold;
short MonitorOff;
short MonitorOff2;

long DrawPhaseGame()//63F04, 645E0
{
	short scalarx = 0; // $a3
	short scalary = 0; // $t0
	short scalarz = 0; // $t1
	struct lara_info* a1;
	struct lara_info* a2;
	int temp;
	int a3;
	int a22;
	int v1111111;

	mQuickW2VMatrix();

	a1 = &lara;

	if (lara.poisoned != lara.dpoisoned)
	{
		if (lara.dpoisoned > 4096)
		{
			lara.dpoisoned = 4096;
		}

		//loc_63F44
		lara.poisoned = ((lara.poisoned - lara.dpoisoned) >> 4) + lara.poisoned;

		temp = ((lara.poisoned - lara.dpoisoned) >> 4);

		if (temp < 0)
		{
			temp = -temp;
		}

		//loc_63F74
		if (temp < 16)
		{
			lara.poisoned = lara.dpoisoned;
		}

	}
	
	//loc_63F88
	a2 = &lara;

	if (lara.poisoned > 255)
	{
		a3 = rcossin_tbl[(((XSoff1 >> 2) & 0x3FFC) / sizeof(short))] + rcossin_tbl[(((XSoff2 >> 2) & 0x3FFC) / sizeof(short))];
/*
		short scalarx = 0; // $a3
		short scalary = 0; // $t0
		short scalarz = 0; // $t1
		*/

		a3 >>= 2;
		a3 *= -256;

		a22 = rcossin_tbl[(((YSoff1 >> 2) & 0x3FFC) / sizeof(short))] + rcossin_tbl[(((YSoff2 >> 2) & 0x3FFC) / sizeof(short))];
		a22 >>= 2;
		a22 *= -256;

		v1111111 = rcossin_tbl[(((ZSoff1 >> 2) & 0x3FFC) / sizeof(short))] + rcossin_tbl[(((ZSoff2 >> 2) & 0x3FFC) / sizeof(short))];
		v1111111 >>= 2;	
		v1111111 *= -256;

		a3 <<= 3;
		a3 >>= 16;
		a22 <<= 3;
		scalary = a22 >> 16;
		v1111111 <<= 3;
		scalarz = v1111111 >> 16;
	}
	else
	{
		//loc_64088
		scalarx = 0;
		scalary = 0;
		scalarz = 0;
	}

	//loc_64090
	//underwater v0
	if (camera.underwater > 0)
	{
#if 0
		short* a1 = &rcossin_tbl[0];
		int v00 = (GlobalCounter & 0x3F) << 8;
		int a22 = GlobalCounter;

		short* v000 = &rcossin_tbl[v00 / sizeof(short)];
		int v111 = v000[0];
		int v0000 = ((a22 - 16) & 0x3F) << 8;
#endif
	}

	//loc_64130
	if (scalarx == 0 && scalary == 0 && scalarz != 0)
	{
		//loc_64148
		if (GLOBAL_playing_cutseq == 0)
		{
			//ScaleCurrentMatrix(1, scalarx + 4096, scalary + 4096, scalarz + 4096);
		}
	}

	//loc_6416C
	//CalcLaraMatrices(0);
	//mPushUnitMatrix();
	//CalcLaraMatrices(1);
	//mPopMatrix();

	if (GLOBAL_playing_cutseq != 0)
	{
		//frigup_lara();//frig af :lennyface:
	}

	//loc_641A8
	//SetLaraUnderwaterNodes();
	//Fade();

	if (SniperOverlay != 0)
	{
		//loc_641F4:

	}

	//loc_6424C
	if (FlashFader != 0)
	{
		//DrawFlash();
		FlashFader -= 2;
	}

	//loc_64280
	DrawRooms(camera.pos.room_number);

	if (WB_room != -1)
	{
		//SortOutWreckingBallDraw();
	}

	//loc_642AC
	DrawGameInfo(1);

	//loc_643C4
	GPU_EndScene();
	//S_DumpScreen();
	//camera.number_frames = v0;
	//S_AnimateTextures(v0);
	//FIXME return numFrames;
	S_Warn("[DrawPhaseGame] - Unimplemented!\n");
	return 2;//hack, retail returns 5, sub 61320
}

void DrawRooms(short current_room)
{
	S_Warn("[DrawRooms] - Unimplemented!\n");
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

void PrintString(long x, long y, char* string)
{
	printf("PrintString - X:%d Y:%d - %s\n", x, y, string);
}
