#include "DRAWPHAS.H"

#include "3D_GEN.H"
#include "BUBBLES.H"
#include "CALCLARA.H"
#include "CONTROL.H"
#include "CONTROL_S.H"
#include "DELTAPAK.H"
#include "DELTAPAK_S.H"
#include "DELSTUFF.H"
#include "DOOR.H"
#include "DRAW.H"
#include "DRAWOBJ.H"
#include "DRAWSKY.H"
#include "EFFECTS.H"
#include "FOOTPRNT_S.H"
#include "FXDRAW.H"
#include "FXTRIG.H"
#include "GAMEFLOW.H"
#include "GPU.H"
#include "HEALTH.H"
#include "LARA.H"
#include "OBJECTS.H"
#include "PRINTOBJ.H"
#include "PROFILE.H"
#include "MATHS.H"
#include "MISC.H"
#include "ROOMLOAD.H"
#include "ROOMLETB.H"
#include "SETUP.H"
#include "SPECIFIC.H"
#include "SPOTCAM.H"
#include "TOMB4FX.H"

#include INLINE_H
#include <LIBGPU.H>
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
	int temp;

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
		scalarx = ((((SIN(XSoff1) + SIN(XSoff2)) >> 2) * (lara.poisoned - 256)) << 3) >> 16;
		scalary = ((((SIN(YSoff1) + SIN(YSoff2)) >> 2) * (lara.poisoned - 256)) << 3) >> 16;
		scalarz = ((((SIN(ZSoff1) + SIN(ZSoff2)) >> 2) * (lara.poisoned - 256)) << 3) >> 16;
	}

	//loc_64090
	if (camera.underwater != 0)
	{
		scalarx = ((scalarx + (((rcossin_tbl[(GlobalCounter & 0x3F) << 7]) << 16) >> 24)) << 16) >> 16;
		scalary = ((scalary + (((rcossin_tbl[((GlobalCounter - 16) & 0x3F) << 7]) << 16) >> 23)) << 16) >> 16;
		scalarz = ((scalarz + (((rcossin_tbl[((64 - GlobalCounter) & 0x3F) << 7]) << 16) >> 25)) << 16) >> 16;
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
			DrawPsxTile(0, 0xF00200, 0x62202000, 2);//@a1 = 8bit window height 16bit window width
			DrawPsxTile(0, 0xF00200, 0x62000020, 1);//@a1 = 8bit window height 16bit window width
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
			insert_psx_clip_window(SCREEN_WIDTH / 2, 100, 23, 312, SCREEN_HEIGHT - 44);

			if (SniperOverlay != 0)
			{
				MGDrawSprite(0x100, 0x78, 0xE, 0, 4, 4, 0x80);
			}//loc_643C4
		}
		else
		{
			//loc_64380
			insert_psx_clip_window(SCREEN_WIDTH / 2, 33, 23, 448, SCREEN_HEIGHT - 46);
		}
	}
	else
	{
		//loc_64398
		if (FadeScreenHeight != 0)
		{
			insert_psx_clip_window(0, FadeScreenHeight, SCREEN_WIDTH, SCREEN_HEIGHT, FadeScreenHeight * 2);
		}//loc_643C4
	}

	//loc_643C4
	GPU_EndScene();
	camera.number_frames = S_DumpScreen();

#if BETA_VERSION//GC change?
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

#if DEBUG_VERSION
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
					//DrawFlatSky_ASM(((LightningRGB[2] << 16) | (LightningRGB[1] << 8) | LightningRGB[0]) | 0x2C00), SkyPos, 0xFFFFFA00);
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
#if DEBUG_VERSION
			ProfileRGB(0, 255, 0);
#endif

			//unsigned long* ptr = (unsigned long*)RelocPtr[1];
			//jalr ptr[0];

#if DEBUG_VERSION
			ProfileRGB(255, 255, 0);
#endif
			mPushMatrix();

			if (lara.right_arm.flash_gun != 0)
			{
				mCopyMatrix(&lara_matrices[11]);
				SetGunFlash(lara.gun_type);
			}//loc_64954

			if (lara.left_arm.flash_gun != 0)
			{
				mCopyMatrix(&lara_matrices[14]);
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

#if DEBUG_VERSION
	ProfileRGB(255, 255, 255);
#endif

	if (BinocularRange != 0)
	{
		DrawRoomletListAsmBinocular(camera_underwater, &room[camera.pos.room_number]);
	}
	else
	{
		DrawRoomletListAsmBinocular(camera_underwater, &room[camera.pos.room_number]);
		//loc_64BA0
		//unsigned long* v1 = (unsigned long*)RelocPtr[2];
		//jalr v1[0];
	}

	//loc_64BBC
#if DEBUG_VERSION
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

	//DrawAllFx();

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
		SetUpLensFlare(gfLensFlare.x, gfLensFlare.y - SECTOR(4), gfLensFlare.z, NULL);
	}

	//loc_64DE0
	InItemControlLoop = 1;
#if DEBUG_VERSION
	ProfileRGB(255, 255, 255);
#endif

	print_all_object_NOW();

#if DEBUG_VERSION
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

void SortOutWreckingBallDraw()//64E78(<), 65528(<) (F)
{
	int i;

	if (number_draw_rooms > 0)
	{
		//loc_64EA0
		for(i = 0; i < number_draw_rooms; i++)
		{
			if(draw_rooms[i] == WB_room)
			{
				return;
			}
		}

		//loc_64EBC
		//a0 = &WB_item[0];
		//v1 = (unsigned long*)RelocPtr[31];
		//jalr v1[1](&WB_item[0]);
		WB_room = -1;

	}//loc_64EBC
}

void MGDrawSprite(int x, int y, int def, int z, int xs, int ys, long rgb)//64EF8(<) ? (F)
{
	POLY_FT4* polyft4;
	struct PSXSPRITESTRUCT* pSpriteInfo;

	polyft4 = (POLY_FT4*)&db.polyptr[0];

	polyft4->y0 = y - (ys / 2);
	polyft4->y1 = y - (ys / 2);
	polyft4->x0 = x - (xs / 2);
	polyft4->x1 = x + (xs / 2);
	polyft4->x2 = x - (xs / 2);
	polyft4->y2 = y + (ys / 2);
	polyft4->x3 = x + (xs / 2);
	polyft4->y3 = y + (ys / 2);

	((char*)polyft4)[3] = 9;
	pSpriteInfo = &psxspriteinfo[objects[DEFAULT_SPRITES].mesh_index + def];
	((long*)polyft4)[1] = rgb | 0x2E000000;

	polyft4->tpage = pSpriteInfo->tpage;

	polyft4->u0 = pSpriteInfo->u1;
	polyft4->v0 = pSpriteInfo->v1;

	polyft4->u1 = pSpriteInfo->u2;
	polyft4->v1 = pSpriteInfo->v1;

	polyft4->u2 = pSpriteInfo->u1;
	polyft4->v2 = pSpriteInfo->v2;

	polyft4->u3 = pSpriteInfo->u2;
	polyft4->v3 = pSpriteInfo->v2;

	polyft4->clut = pSpriteInfo->clut;

	polyft4->tag = (polyft4->tag & 0xFF000000) | (db.ot[z] & 0xFFFFFF);

	db.ot[z] = (db.ot[z] & 0xFF000000) | ((unsigned long)polyft4 & 0xFFFFFF);

	db.polyptr += sizeof(POLY_FT4);
}