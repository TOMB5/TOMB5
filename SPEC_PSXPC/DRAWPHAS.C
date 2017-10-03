#include "DRAWPHAS.H"

#include "3D_GEN.H"
#include "CONTROL.H"
#include "DELTAPAK.H"
#include "DELSTUFF.H"
#include "DRAW.H"
#include "DRAWSPKS.H"
#include "DOOR.H"
#include "GAMEFLOW.H"
#include "GPU.H"
#include "HEALTH.H"
#include "LARA.H"
#include "LOAD_LEV.H"
#include "PHD_MATH.H"
#include "PROFILE.H"
#include "SPECIFIC.H"
#include "SPOTCAM.H"
#include "TOMB4FX.H"

#include <assert.h>
#include <stdio.h>

long StoreBoxes = -1;
struct GAME_VECTOR LaraPos;
struct PSXTEXTI* MonitorScreenTI;
unsigned char MonitorScreenU0;
unsigned char MonitorHold;
short MonitorOff;
short MonitorOff2;

long DrawPhaseGame()//63F04(<), 645E0(<)
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

	if (lara.poisoned != lara.dpoisoned)
	{
		if (lara.dpoisoned > 4096)
		{
			lara.dpoisoned = 4096;
		}

		temp = (lara.dpoisoned - lara.poisoned);
		if (temp < 0)
		{
			temp = -(lara.dpoisoned - lara.poisoned);//temp @ a0
		}

		//loc_63F74
		if (temp < 16)
		{
			lara.poisoned = lara.dpoisoned;
		}
	}

	//loc_63F88
	if (lara.poisoned < 256)
	{
		//loc_64088
		scalary = 0;
		scalarz = 0;
		scalarx = 0;
	}
	else
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
	if (scalarx == 0 && scalary == 0 && scalarz != 0 && GLOBAL_playing_cutseq == 0)
	{
		//loc_64148
		if (GLOBAL_playing_cutseq == 0)
		{
			ScaleCurrentMatrix(1, scalarx + 4096, scalary + 4096, scalarz + 4096);
		}
	}

	//loc_6416C
	CalcLaraMatrices(0);
	mPushUnitMatrix();
	CalcLaraMatrices(1);
	mPopMatrix();

	if (GLOBAL_playing_cutseq != 0)
	{
		frigup_lara();
	}

	//loc_641A8
	SetLaraUnderwaterNodes();
	Fade();

	if (BinocularRange == 0 && SCOverlay == 0 && SniperOverlay != 0)
	{
		//loc_641F4
		DrawBinoculars();

		if (InfraRed)
		{
#if PSX_VERSION
			DrawPsxTile(0, 0xF00200, 0x62202000, 2);//@a1 = 8bit window height 16bit window width
			DrawPsxTile(0, 0xF00200, 0x62000020, 1);//@a1 = 8bit window height 16bit window width
#endif
		}
	}

	//loc_6424C
	if (FlashFader != 0)
	{
		DrawFlash();
		FlashFader -= 2;
	}

	//loc_64280
	DrawRooms(camera.pos.room_number);

	if (WB_room != -1)
	{
		SortOutWreckingBallDraw();
	}

	//loc_642AC
	DrawGameInfo(1);

	if (BinocularRange == 0 || SniperOverlay == 0 && SCOverlay != 0)
	{
		//loc_642F0
		if (LaserSight != 0 || SCOverlay != 0 && SniperOverlay != 0)
		{
			//loc_6432C
#if PSX_VERSION
			insert_psx_clip_window(0x64, 0x17, 0x138, 0xC4);
#endif
			if (SniperOverlay != 0)
			{
				MGDrawSprite(0x100, 0x78, 0xE, 0, 4, 4, 0x80);
			}//loc_643C4
		}
		else
		{
#if PSX_VERSION
			//loc_64380
			insert_psx_clip_window(0x21, 0x17, 0x1C0, 0xC2);
#endif
		}
	}
	else
	{
		//loc_64398
		if (FadeScreenHeight != 0)
		{
#if PSX_VERSION
			insert_psx_clip_window(0, FadeScreenHeight, 0x200, 0xF0, FadeScreenHeight * 2);
#endif
		}//loc_643C4
	}

	//loc_643C4
	GPU_EndScene();
	camera.number_frames = S_DumpScreen();

#if INTERNAL//GC change?
	S_AnimateTextures(camera.number_frames);
#else
	if (gfCurrentLevel == 13)
	{
		//v0 = $gp+11A4//Unknown! A39B8
		//v0 += 1
		//v0 &= 3;
		//if(v0 == 0)
		{
			S_AnimateTextures(camera.number_frames);
		}
	}
	else
	{
		S_AnimateTextures(camera.number_frames);
	}

#endif
	
	return camera.number_frames;
}

void DrawRooms(short current_room)//643FC, 64B1C
{
	struct room_info* r; // $a0
	{ // line 146, offset 0x649b8
		short old_anim; // $t4
		short old_frame; // $t5
		short old_left_arm[2]; // stack offset -40
		short old_right_arm[2]; // stack offset -32
		short* old_arm_anim[2]; // stack offset -24
	} // line 197, offset 0x64b40
	{ // line 230, offset 0x64c24
		struct GAME_VECTOR sp; // stack offset -40
	} // line 264, offset 0x64d70

#if INTERNAL
	ProfileRGB(255, 255, 255);
#endif

	//v1 = 0x1FF;
	CurrentRoom = current_room;
	r = &room[current_room];
	//a1 = r->flags;
	//v0 = 0x1FF;
	r->test_left = 0;
	phd_left = 0;

	r->test_top = 0;
	phd_top = 0;

	r->test_right = 511;
	phd_right = 511;

	r->test_bottom = 239;
	phd_bottom = 239;

	outside = r->flags & 8;

	if (r->flags & 1)
	{
		camera_underwater = 0xFFFF0000;
	}
	else
	{
		camera_underwater = 0;
	}
	

	//loc_644A8
	//S_SetupClutAdder()
	//move	$a0, $a2
	//mPushMatrix();
	//mSetTrans(0, 0, 0);
	//mTranslateXYZ(-CamPos.x, -CamPos.y, -CamPos.z);
	//GetRoomBoundsAsm(current_room);
	ProcessClosedDoors();

	/*
	lw	$v0, dword_800A25F0
	nop
	beqz	$v0, loc_64878
	*/
	if (outside)
	{

	}//loc_64878

	S_Warn("[DrawRooms] - Unimplemented!\n");
}

void SortOutWreckingBallDraw()//64E78(<), 65528(<)
{
	long lp; // $v1

	if (number_draw_rooms > 0)
	{
		for (lp = 0; lp < number_draw_rooms; lp++)
		{
			//loc_64EA0
			if (draw_rooms[lp] == WB_room)
			{
				return;
			}
		}
	}

	//loc_64EBC
	//assert(0);
	//v1 = &RelocPtr[31];
	//a0 = WB_Item
	//a1 = v1[1];
	//jalr a1(WB_Item)

	WB_room = -1;

	//loc_64EE8
	S_Warn("[SortOutWreckingBallDraw] - Unimplemented!\n");
	return;
}

void MGDrawSprite(int x, int y, int def, int z, int xs, int ys, long rgb)//64EF8, 
{
	struct POLY_FT4* polyft4;//t0
	struct PSXSPRITESTRUCT* pSpriteInfo;//a0

	//t3 = &db;
	def *= 16;
	z *= 4;
	//t1 = xs;
	//t2 = ys;
	//t4 = rgb


}

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

void mQuickW2VMatrix()//77AEC, 79B30
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

void PrintString(long x, long y, long unk, char* string)
{
	printf("PrintString - X:%d Y:%d C:%d - %s\n", x, y, unk, string);
}

void DrawBinoculars()
{
	S_Warn("[DrawBinoculars] - Unimplemented!\n");
}

void DrawFlash()
{
	S_Warn("[DrawFlash] - Unimplemented!\n");
}