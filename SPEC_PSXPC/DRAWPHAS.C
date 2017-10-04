#include "DRAWPHAS.H"

#include "3D_GEN.H"
#include "CONTROL.H"
#include "DELTAPAK.H"
#include "DELSTUFF.H"
#include "DOOR.H"
#include "DRAW.H"
#include "DRAWSPKS.H"
#include "EFFECTS.H"
#include "GAMEFLOW.H"
#include "GPU.H"
#include "HEALTH.H"
#include "LARA.H"
#include "LOAD_LEV.H"
#include "OBJECTS.H"
#include "PHD_MATH.H"
#include "ROOMLOAD.H"
#include "SETUP.H"
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
	if (gfCurrentLevel == LVL5_SECURITY_BREACH)
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

void DrawRooms(short current_room)//643FC(<), 64B1C(<) (F)
{
	struct room_info* r;
	short old_anim;
	short old_frame;
	short old_left_arm[2];
	short old_right_arm[2];
	short* old_arm_anim[2];
	struct GAME_VECTOR sp;

#if INTERNAL
	ProfileRGB(255, 255, 255);
#endif

	CurrentRoom = current_room;
	r = &room[current_room];

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
	S_SetupClutAdder(camera_underwater);

	//move	$a0, $a2
	mPushMatrix();
	mSetTrans(0, 0, 0);
	mTranslateXYZ(-CamPos.x, -CamPos.y, -CamPos.z);
	GetRoomBoundsAsm(current_room);
	mPopMatrix();
	ProcessClosedDoors();

	if (outside)
	{
		if (objects[HORIZON].loaded && !disable_horizon)
		{
			if (BinocularRange != 0)
			{
				AlterFOV(0x3FFC - BinocularRange);
			}

			//loc_6457C
			mPushMatrix();

			mTranslateAbsXYZ(camera.pos.x, camera.pos.y, camera.pos.z);

			if (gfLevelFlags & GF_LVOP_LIGHTNING)
			{
				if (LightningCount == 0 && LightningRand == 0)
				{
					//loc_64634
					if ((GetRandomDraw() & 0x7F) == 0)
					{
						LightningCount = (GetRandomDraw() & 0x1F) + 16;
						dLightningRand = (GetRandomDraw() & 0xFF) + 256;
						LightningSFXDelay = (GetRandomDraw() & 0x3) + 12;
					}
				}
				else
				{
					//loc_645E4
					UpdateSkyLightning();

					if (LightningSFXDelay >= 0)
					{
						LightningSFXDelay--;
					}

					//loc_6460C
					if (LightningSFXDelay == 0)
					{
						SoundEffect(182, NULL, 0);
					}
				}
			}//loc_64690

			CalcClipWindow_ONGTE(camera.pos.room_number, 1);

			if (gfLevelFlags & GF_LVOP_HORIZON)
			{
				if (gfCurrentLevel == LVL5_TITLE && jobyfrigger != 0)
				{
					DrawSkyMesh(meshes[objects[CHEF_MIP].mesh_index]);
				}
				else
				{
					DrawSkyMesh(meshes[objects[HORIZON].mesh_index]);
				}
			}//loc_64728

			if (gfLevelFlags & GF_LVOP_LAYER2_USED)
			{
				DrawFlatSky_ASM(gfLayer2Col, SkyPos2, 0xFFFFFA00);
			}//loc_64758

			if (gfLevelFlags & GF_LVOP_LAYER1_USED)
			{
				mRotY(32768);

				if (gfLevelFlags & GF_LVOP_LIGHTNING)
				{
					//Must convert a0 to CVector
					//DrawFlatSky_ASM((LightningRGB[2] << 16) | (LightningRGB[1] << 8) | LightningRGB[0]) | 0x2C00, SkyPos, 0xFFFFFA00);
				}
				else
				{
					//loc_647D4
					DrawFlatSky_ASM(gfLayer1Col, SkyPos, 0xFFFFFA00);
				}

			}//loc_647F0

			if (RelocPtr[14] != NULL)
			{
				//unsigned long* ptr = (unsigned long*)RelocPtr[14];
				//jalr ptr[1];
			}//loc_64814

			if (gfCurrentLevel == LVL5_GALLOWS_TREE)
			{
				DrawMoon();
			}//loc_64830

			mPopMatrix();

			if (BinocularRange != 0)
			{
				AlterFOV(0x3FFC - ((BinocularRange * 8) - BinocularRange));
			}
		}
		else
		{
			//loc_6486C
			outside = -1;
		}
	}//loc_64878

	if (objects[LARA].loaded && !(lara_item->flags & 0x40))
	{
		InitObjGTE();

		if (lara_item->mesh_bits != 0 && SCNoDrawLara == 0)
		{
#if INTERNAL
			ProfileRBG(0, 255, 0);
#endif

			//unsigned long* ptr = (unsigned long*)RelocPtr[1];
			//jalr ptr[0];

#if INTERNAL
			ProfileRGB(255, 255, 0);
#endif
			mPushMatrix();

			if (lara.right_arm.flash_gun != 0)
			{
				mCopyMatrix(lara_matrices[11]);
				SetGunFlash(lara.gun_type);
			}//loc_64954

			if (lara.left_arm.flash_gun != 0)
			{
				mCopyMatrix(lara_matrices[14]);
				SetGunFlash(lara.gun_type);
			}//loc_64978

			mPopMatrix();

		}//loc_64980

		old_anim = 0;
		old_frame = 0;

		if (gfLevelFlags & GF_LVOP_MIRROR_USED && lara_item->room_number == gfMirrorRoom && BinocularRange != 0)
		{
			if (LaserSight != 0)
			{
				old_arm_anim[0] = lara.left_arm.frame_base;
				old_arm_anim[1] = lara.right_arm.frame_base;

				old_left_arm[0] = lara.left_arm.frame_number;
				old_left_arm[1] = lara.left_arm.anim_number;

				old_right_arm[0] = lara.right_arm.frame_number;
				old_right_arm[1] = lara.right_arm.anim_number;

				lara.right_arm.frame_number = 0;
				lara.left_arm.frame_number = 0;

				lara.right_arm.anim_number = objects[CROSSBOW_ANIM].anim_index + 2;
				lara.left_arm.anim_number = objects[CROSSBOW_ANIM].anim_index + 2;

				lara.right_arm.frame_base = anims[objects[CROSSBOW_ANIM].anim_index + 2].frame_ptr;
				lara.left_arm.frame_base = anims[objects[CROSSBOW_ANIM].anim_index + 2].frame_ptr;
			}
			else
			{
				//loc_64A64
				old_frame = lara_item->frame_number;
				old_anim = lara_item->anim_number;
				lara_item->anim_number = ANIMATION_LARA_BINOCULARS;
				lara_item->frame_number = anims[ANIMATION_LARA_BINOCULARS].frame_base;
				lara.mesh_ptrs[10] = &meshes[objects[MESHSWAP2].mesh_index][20];
			}

			//loc_64AB0
			if (BinocularRange != 0)
			{
				if (LaserSight != 0)
				{
					lara.left_arm.frame_base = old_arm_anim[0];
					lara.right_arm.frame_base = old_arm_anim[1];

					lara.left_arm.frame_number = old_left_arm[0];
					lara.left_arm.anim_number = old_left_arm[1];

					lara.right_arm.frame_number = old_right_arm[0];
					lara.right_arm.anim_number = old_right_arm[1];
				}
				else
				{
					//loc_64B0C
					lara_item->anim_number = old_anim;
					lara_item->frame_number = old_frame;
					lara.mesh_ptrs[10] = &meshes[objects[LARA_SKIN].mesh_index][20];
				}
			}//loc_64B40
		}//loc_64B40
	}//loc_64B40

	mPushMatrix();

#if INTERNAL
	ProfileRGB(255, 255, 255);
#endif

	if (BinocularRange != 0)
	{
		DrawRoomletListAsmBinocular(camera_underwater, &room[camera.pos.room_number]);
	}
	else
	{
		//loc_64BA0
		//unsigned long* v1 = (unsigned long*)RelocPtr[3];
		//jalr v1[0];
	}

	//loc_64BBC
#if INTERNAL
	ProfileRGB(255, 0, 0);
#endif

	mPopMatrix();

	S_SetupClutAdder(camera_underwater);
	InitObjGTE();

	if (GLOBAL_playing_cutseq != 0)
	{
		DrawCutSeqActors();
	}//loc_64C04

	 //unsigned long* v0 = (unsigned long*)RelocPtr[18];
	 //jalr v0[0];

	 //loc_64C24
	sp.x = lara_item->pos.x_pos;
	LaraPos.x = lara_item->pos.x_pos;

	sp.y = lara_item->pos.y_pos;
	LaraPos.y = lara_item->pos.y_pos;

	sp.z = lara_item->pos.z_pos;
	LaraPos.z = lara_item->pos.z_pos;

	sp.room_number = lara_item->room_number;
	LaraPos.room_number = lara_item->room_number;

	lara_item->pos.x_pos = camera.pos.x;
	lara_item->pos.y_pos = camera.pos.y;
	lara_item->pos.z_pos = camera.pos.z;
	lara_item->room_number = camera.pos.room_number;

	DrawAllFx();

	if (RelocPtr[35] != NULL)
	{
		//unsigned long* v0 = (unsigned long*)RelocPtr[35];
		//jalr v0[2];
	}//loc_64CC8

	if (RelocPtr[9] != NULL)
	{
		//unsigned long* v0 = (unsigned long*)RelocPtr[9];
		//jalr v0[6];
	}//loc_64CF0

	if (RelocPtr[21] != NULL)
	{
		//unsigned long* v0 = (unsigned long*)RelocPtr[21];
		//jalr v0[2];
	}//loc_64D10

	if (RelocPtr[32] != NULL)
	{
		//unsigned long* v0 = (unsigned long*)RelocPtr[6];
		//jalr v0[2];
	}//loc_64D30

	if (RelocPtr[3] != NULL)
	{
		//unsigned long* v0 = (unsigned long*)RelocPtr[3];
		//jalr v0[0];
	}//loc_64D50

	if (RelocPtr[7] != NULL)
	{
		//unsigned long* v0 = (unsigned long*)RelocPtr[7];
		//jalr v0[3];
	}//loc_64D70

	S_DrawSparks();

	lara_item->pos.x_pos = sp.x;
	lara_item->pos.y_pos = sp.y;
	lara_item->pos.z_pos = sp.z;
	lara_item->room_number = sp.room_number;

	if (gfLevelFlags & GF_LVOP_LENSFLARE_USED)
	{
		SetUpLensFlare(gfLensFlare.x, gfLensFlare.y - 4096, gfLensFlare.z, NULL);
	}

	//loc_64DE0
	InItemControlLoop = 1;
#if INTERNAL
	ProfileRGB(255, 255, 255);
#endif

	//print_all_object_NOW();//**********************************************************

#if INTERNAL
	ProfileRGB(0, 255, 0);
#endif

	InItemControlLoop = 0;

	KillMoveItems();

	if (WeatherType != 0)
	{
		//unsigned long* v0 = (unsigned long*)RelocPtr[0];
		//jalr v0[0];
	}

	//loc_64E50
	S_DrawFootPrints();
	DrawGunflashes();
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

void CalcClipWindow_ONGTE(short room_number, long unknown)
{
	S_Warn("[CalcClipWindow_ONGTE] - Unimplemented!\n");
}

void DrawAllFx()
{
	S_Warn("[DrawAllFx] - Unimplemented!\n");
}

void InitObjGTE()
{
	S_Warn("[InitObjGTE] - Unimplemented!\n");
}

void DrawCutSeqActors()
{
	S_Warn("[DrawCutSeqActors] - Unimplemented!\n");
}

void DrawRoomletListAsmBinocular(long underwater, struct room_info* r)
{
	S_Warn("[DrawRoomletListAsmBinocular] - Unimplemented!\n");
}

void GetRoomBoundsAsm(short room_number)
{
	S_Warn("[GetRoomBoundsAsm] - Unimplemented!\n");
}

void SetGunFlash(short gun_type)
{
	S_Warn("[SetGunFlash] - Unimplemented!\n");
}
