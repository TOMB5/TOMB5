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
#include "MATHS.H"
#include "ROOMLOAD.H"
#include "SETUP.H"
#include "SPECIFIC.H"
#include "SPOTCAM.H"
#include "TEXT.H"
#include "TOMB4FX.H"

#include <INLINE_C.H>
#include <LIBGPU.H>
#include <stdio.h>

#define gte_SetRotMatrixH( r0 ) __asm__ volatile (		\
	"lhu	$12, 0( %0 );"					\
	"lhu	$13, 4( %0 );"					\
	"ctc2	$12, $0;"					\
	"ctc2	$13, $1;"					\
	"lhu	$12, 8( %0 );"					\
	"lhu	$13, 12( %0 );"					\
	"lhu	$14, 16( %0 );"					\
	"ctc2	$12, $2;"					\
	"ctc2	$13, $3;"					\
	"ctc2	$14, $4"					\
	:							\
	: "r"( r0 )						\
	: "$12", "$13", "$14" )

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
			//DrawPsxTile(0, 0xF00200, 0x62202000, 2);//@a1 = 8bit window height 16bit window width
			//DrawPsxTile(0, 0xF00200, 0x62000020, 1);//@a1 = 8bit window height 16bit window width
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
			insert_psx_clip_window(SCREEN_WIDTH / 2, 100, 23, 312, SCREEN_HEIGHT - 44);

			if (SniperOverlay != 0)
			{
				//MGDrawSprite(0x100, 0x78, 0xE, 0, 4, 4, 0x80);
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
		SetUpLensFlare(gfLensFlare.x, gfLensFlare.y - SECTOR(4), gfLensFlare.z, NULL);
	}

	//loc_64DE0
	InItemControlLoop = 1;
#if INTERNAL
	ProfileRGB(255, 255, 255);
#endif

	print_all_object_NOW();

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


void mQuickW2VMatrix()
{
	//v1  = &phd_mxptr;
	//a0 = &MatrixStack[0];
	MatrixSP = 0;
	Matrix = &MatrixStack[0];


	//lhu	$at, 0($v1)
	//lhu	$v0, 4($v1)
	//lhu	$a1, 8($v1)
	//lhu	$a2, 0x10($v1)
	//sll	$v0, 16
	//or $at, $v0
	//sll	$a2, 16
	//or $a1, $a2
	//lhu	$a3, 0x14($v1)
	//lhu	$t0, 0x18($v1)
	//lhu	$t1, 0x20($v1)
	//lhu	$t2, 0x24($v1)
	//sll	$t0, 16
	//or $a3, $t0
	//sll	$t2, 16
	//or $t1, $t2
	
	//sw	$at, 0($a0)
	//sw	$a1, 4($a0)
	//sw	$a3, 8($a0)
	//sw	$t1, 0xC($a0)
	
	//gte_SetRotMatrixH(phd_mxptr);
	//ctc2	$at, $0
	//ctc2	$a1, $1
	//ctc2	$a3, $2
	//ctc2	$t1, $3
		
	//lhu	$at, 0x28($v1)
	//lw	$v0, 0xC($v1)
	//lw	$a1, 0x1C($v1)
	//lw	$a2, 0x2C($v1)
	//sh	$at, 0x10($a0)
	//sw	$v0, 0x14($a0)
	//sw	$a1, 0x18($a0)
	//sw	$a2, 0x1C($a0)
	
	//ctc2	$at, $4

	//gte_SetTransMatrix?
	//ctc2	$v0, $5
	//ctc2	$a1, $6
	//ctc2	$a2, $7
	//lhu	$v0, 0x34D4($gp)
	//lhu	$v1, 0x34D8($gp)
	//lhu	$a0, 0x34DC($gp)
	//lhu	$a1, 0x34E4($gp)
	//lhu	$a2, 0x34E8($gp)
	//lhu	$a3, 0x34EC($gp)
	//lhu	$t0, 0x34F4($gp)
	//lhu	$t1, 0x34F8($gp)
	//lhu	$t2, 0x34FC($gp)
	//sh	$v0, 0x4048($gp)
	//sh	$v1, 0x404A($gp)
	//sh	$a0, 0x404C($gp)
	//sh	$a1, 0x404E($gp)
	//sh	$a2, 0x4050($gp)
	//sh	$a3, 0x4052($gp)
	//sh	$t0, 0x4054($gp)
	//sh	$t1, 0x4056($gp)
	//jr	$ra
	//sh	$t2, 0x4058($gp)
}

//ushort, ushort, uchar, char*, ushort
void PrintString(unsigned short x, unsigned short y, unsigned char colourFlag, char* string, unsigned short flag)//8DB4C, 8FB90
{
#if 0
	long s0, s4, s3, at, s6, s2, v0;
	char* s5;
	unsigned short buf[64];//TODO check size
	///@TODO unk is type (3 is red) also as byte
	s0 = x;
	s4 = y;
	s3 = colourFlag & 0xFF;
	s5 = string;
	s6 = 0xA000;//?????$50($sp)
	at = GnFrameCounter;

	at &= 0x10;
	if (s6 & 0x2000 && GnFrameCounter & 0x10)
	{
		return;
	}

	//loc_8DBA0
	ScaleFlag = (s6 >> 12) & 1;

	v0 = GetStringLength(string, 0, &buf[0]);///@FIXME - ret is 65 on first call (Retail)

	//Unpick @sub_8DD90
	if (s6 & 0x8000)
	{
		s2 = s0 - (v0 >> 1);
	}
	else if (s6 & 0x4000)
	{
		s2 = s0 - v0;
	}
	else
	{
		s2 = s0;
	}
	//@ret jr ra +0x190(base 0x8FC000)
	//0x0008FD9C (RETAIL)

	a0 = *s5++;
	//v0 = 0xA;

	if (a0 == 0)
	{
		//sb, 0 1284(gp)
		return;
	}

	//0x8FC08
	//v0 = 0x20
	if (a0 == 0xA)
	{
		//v0 = *s5;
		//a1 = sp+0x12
		//a0 = s5;
		//if(v0 == a0)
		//{
			//$sp+0x10 = 0;

		//}
	}

	if (a0 == 0x20)
	{
	}

	if (a0 == 0x9)
	{

	}

	if (a0 < 0x14)
	{

	}

	if (a0 - 0x80 < 0x2E)
	{

	}
	//loc_8DCDC
#if 0
	move	$a0, $s5
	move	$a1, $zero
	jal	sub_8DEDC
	addiu	$a2, $sp, 0x40 + var_30
	jal	sub_8DD90
	addiu	$ra, 0x190

	loc_8DBC4:
	bne	$a0, $v0, loc_8DC14
	 li	$v0, 0x20
	 lbu	$v0, 0($s5)
	 addiu	$a1, $sp, 0x40 + var_2E
	 bne	$v0, $a0, loc_8DBE8
	 move	$a0, $s5
	 sh	$zero, 0x40 + var_30($sp)
	 j	loc_8DD54
	 addiu	$s4, 0x10

	 loc_8DBE8:
	 jal	sub_8DEDC
	 addiu	$a2, $sp, 0x40 + var_2C
	 jal	sub_8DD90
	 lhu	$v1, 0x40 + var_30($sp)
	 lhu	$v0, 0x40 + var_2E($sp)
	 lhu	$a0, 0x40 + var_2C($sp)
	 subu	$v1, $v0
	 addiu	$v1, 2
	 addu	$s4, $v1
	 j	loc_8DD54
	 sh	$a0, 0x40 + var_30($sp)

	 loc_8DC14:
	bne	$a0, $v0, loc_8DC30
	 li	$v0, 9
	 andi	$v0, $s6, 0x1000
	 bnez	$v0, loc_8DD54
	 addiu	$s2, 6
	 j	loc_8DD54
	 addiu	$s2, 2

	loc_8DC30:
	bne	$a0, $v0, loc_8DC40
	 sltiu	$v0, $a0, 0x14
	 j	loc_8DD54
	 addiu	$s2, 0x28

	loc_8DC40 :
	beqz	$v0, loc_8DC50
	addiu	$v0, $a0, -1
	j	loc_8DD54
	andi	$s3, $v0, 0xFF

	loc_8DC50 :
	addiu	$v0, $a0, -0x80
	 sltiu	$v1, $v0, 0x2E
	beqz	$v1, loc_8DCDC
	sll	$v0, 1
	 la	$t1, aUEAAAAEEEAAEOO  #	" u^e\\a]a^a[a\\{ e]e^e[|^|]|[A^A]E\\   "...
				 addu	$t1, $v0
				 lbu	$v1, -1($t1)
				 la	$s1, (loc_92020 + 1)
				 sll	$v0, $v1, 3
				 subu	$v0, $v1
				 addu	$s1, $v0
				 move	$a0, $s2
				 move	$a1, $s4
				 move	$a2, $s3
				 jal	sub_8DDBC
				 move	$a3, $s1
				 lbu	$v1, 0($t1)
				 li	$at, 0x20
				 beq	$v1, $at, loc_8DD3C
				 sll	$v0, $v1, 3
				 subu	$v0, $v1
				 la	$a3, (loc_92020 + 1)
				 addu	$a3, $v0, $a3
				 lb	$a0, 2($s1)
				 lb	$a1, 4($s1)
				 sra	$a0, 1
				 addu	$a0, $s2
				 addiu	$a0, -3
				 addu	$a1, $s4, $a1
				 move	$a2, $s3
				 jal	sub_8DDBC
				 addiu	$ra, 0x60

				 loc_8DCDC:
			 sll	$v0, $a0, 3
				 subu	$v0, $a0
				 sltiu	$at, $a0, 0x20
				 beqz	$at, loc_8DD20
				 move	$a2, $s3
				 la	$v1, word_9230E
				 addiu	$a0, -0x18
				 sltiu	$a0, 4
				 bnez	$a0, loc_8DD0C
				 addu	$s1, $v0, $v1
				 move	$a2, $zero

				 loc_8DD0C :
			 move	$a0, $s2
				 move	$a1, $s4
				 move	$a3, $s1
				 jal	sub_8DDBC
				 addiu	$ra, 0x1C

				 loc_8DD20 :
				 la	$a0, (loc_92020 + 1)
				 addu	$s1, $v0, $a0
				 move	$a0, $s2
				 move	$a1, $s4
				 jal	sub_8DDBC
				 move	$a3, $s1

				 loc_8DD3C :
			 lbu	$v1, 2($s1)
				 andi	$v0, $s6, 0x1000
				 beqz	$v0, loc_8DD50
				 srl	$v0, $v1, 2
				 subu	$v1, $v0

				 loc_8DD50 :
			 addu	$s2, $v1

				 loc_8DD54 :
			 lbu	$a0, 0($s5)
				 addiu	$s5, 1
				 bnez	$a0, loc_8DBC4
				 li	$v0, 0xA
				 sb	$zero, 0x1A8C($gp)

				 loc_8DD68 :
				 lw	$ra, 0x40 + var_4($sp)
				 lw	$s6, 0x40 + var_8($sp)
				 lw	$s5, 0x40 + var_C($sp)
				 lw	$s4, 0x40 + var_10($sp)
				 lw	$s3, 0x40 + var_14($sp)
				 lw	$s2, 0x40 + var_18($sp)
				 lw	$s1, 0x40 + var_1C($sp)
				 lw	$s0, 0x40 + var_20($sp)
				 jr	$ra
				 addiu	$sp, 0x40
#endif

#else
	printf("PrintString - X:%d Y:%d C:%d - %s\n", x, y, colourFlag, string);
#endif
}

//char*, unsigned short*, unsigned short*
#if 1
long GetStringLength(char* string, unsigned short* a1, unsigned short* a2)//8DEDC(<), 8FF20(<)
{
	char c;
	long t0, t1, t2, t3, t5, v0;
	t5 = 0;
	t0 = 0;
	t2 = 0xFFFFFC00;

	c = *string++;//c = a3
	t1 = 0x400;

	if (c != 0 || c != 10)
	{
		t3 = ScaleFlag;
		//t6 = &AccentTable[0][0];
		//t4 = &CharDef[0];

		//loc_8DF18
		while (string[0] != 10 || string[0] != 0)
		{
			if (c == 32)
			{
				t0 += 8;
				if (t3 != 0)
				{
					t0 -= 2;
				}
			}
			else if (c == 9)
			{
				//loc_8DF30
				t0 += 40;

				if (!(t1 < -11))
				{
					t1 = -12;
				}

				if (t2 < 2)
				{
					t2 = 2;
				}
			}
			else if (c > 19)
			{
				//loc_8DF5C
				if (c < 0x20)
				{
					//v0 = (c << 3) - c;
					//v0 += 0x206;
					//a3 = v0 + t4
					sizeof(struct CHARDEF);
				}
				else
				{
					//loc_8DF7C
					//v1 = c - 0x80;
					//v0 = v1 < 0x2E ? 1 : 0;
					//v0 = v1 << 1;
					if (c - 0x80 < 0x2E)
					{
						//v0 += t6;
						//a3 = v0[0];
						t5 = 1;
					}//loc_8DF98

					//v0 = a3 << 3;
					//v0 -= a3;
					//v0 -= 0xE7;
					//a3 = v0 + t4;
				}

				//loc_8DFA8

			}
		}
	}

	//loc_8DFFC
	if (a1 != 0 && t5 == 0)
	{
		//loc_8E010
		*a1 = t1;
	}
	else if (a1 != 0 && t1 != 0)
	{
		t1 -= 4;
	}

	//loc_8E014
	if (a2 != 0)
	{
		*a2 = t2;
	}
	
	*a1 = t1;

	return t0;
}
#endif

void DrawChar(unsigned short a0, unsigned short a1, unsigned short a2, struct CHARDEF* a3)//8DDBC(<), 8FE00(<) (F)
{
	struct CVECTOR* TopShade;//$v0
	struct CVECTOR* BottomShade;//$at
	long v1;

	a2 &= 0xFFFF;

	if ((unsigned long)&db.polyptr[0] < (unsigned long)&db.polybuf_limit[0])
	{
		TopShade = &FontShades[a2][a3->TopShade];
		BottomShade = &FontShades[a2][a3->BottomShade];

		*(long*) &db.polyptr[4] = *(long*) &TopShade->r;
		*(long*) &db.polyptr[28] = *(long*) &BottomShade->r;
		*(long*) &db.polyptr[16] = *(long*) &TopShade->r;
		*(long*) &db.polyptr[40] = *(long*) &BottomShade->r;

		((char*)db.polyptr)[7] = 0x3C;//#define TAG_PGT4                    0x3C

		*(short*) &db.polyptr[14] = 4197;
		*(short*) &db.polyptr[26] = 41;
		sizeof(POLY_GT4);

		v1 = a3->w;
		a1 += a3->YOffset;

		if (ScaleFlag != 0)
		{
			v1 = (a3->w >> 2) - a3->w + 1;
		}
		
		//loc_8DE5C
		*(short*) &db.polyptr[8] = a0;
		*(short*) &db.polyptr[10] = a1;
		*(short*) &db.polyptr[20] = a0 + v1;
		*(short*) &db.polyptr[22] = a1;

		*(short*) &db.polyptr[32] = a0;
		*(short*) &db.polyptr[34] = a1 + a3->h;
		*(short*) &db.polyptr[44] = a0 + v1;
		*(short*) &db.polyptr[46] = a1 + a3->h;

		*(char*) &db.polyptr[12] = a3->w;
		*(char*) &db.polyptr[13] = a3->v;
		*(char*) &db.polyptr[24] = a3->u + a3->v;
		*(char*) &db.polyptr[25] = a3->v;

		*(char*) &db.polyptr[36] = a3->u;
		*(char*) &db.polyptr[37] = a3->v + a3->h;
		*(char*) &db.polyptr[48] = a3->u + a3->w;
		*(char*) &db.polyptr[49] = a3->v + a3->h;

		*(long*) &db.polyptr[0] = db.ot[0] | 0x0C000000;
		db.ot[0] = db.polyptr;

		db.polyptr += sizeof(POLY_GT4);

	}//locret_8DED4
}

void DrawBinoculars()
{
	S_Warn("[DrawBinoculars] - Unimplemented!\n");
}

void DrawFlash()
{
	S_Warn("[DrawFlash] - Unimplemented!\n");
}

void SortOutWreckingBallDraw()
{
	S_Warn("[SortOutWreckingBallDraw] - Unimplemented!\n");
}

void CalcClipWindow_ONGTE(short room_number, long unknown)
{
	S_Warn("[CalcClipWindow_ONGTE] - Unimplemented!\n");
}

void DrawAllFx()
{
	S_Warn("[DrawAllFx] - Unimplemented!\n");
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

void InitObjGTE()
{
	__asm__ volatile ("li $0, 0xAA;");
	__asm__ volatile ("ctc2	$0, $29;");
	__asm__ volatile ("li $0, 0x80A;");
	__asm__ volatile ("ctc2	$0, $30;");
	gte_ldfcdir(0, 0, 0);
}

void insert_psx_clip_window(long x, long y, long w, long a3, long h)
{
	static DRAWENV env;

	if (db.current_buffer != 0)
	{
		env.dr_env.tag = 0xF000;
		y += 0xF0;
	}
	else
	{
		env.dr_env.tag = 0;
	}
	//loc_8FDCC:
	SetDefDrawEnv(&env, x, y, w, h);
	*(long*) &env.ofs[0] = env.dr_env.tag;
	env.dtd = 1;
	env.isbg = 0;
	SetDrawEnv((DR_ENV*)&db.polyptr[0], &env);
	*(long*)&db.polyptr[0] = db.ot[2563] |= 0x60000000;
	*(long*) &db.ot[2563] = (long)db.polyptr;
	db.polyptr += 0x1C;
}

void print_all_object_NOW()//8F474(<), 914B8(<) (F)
{
	int i;

	//CalcAllAnimatingItems_ASM();

	for (i = 0; i < number_draw_rooms; i++)
	{
		//s3 = draw_rooms[i];//Why?
		//PrintAllOtherObjects_ASM();
	}
}

void DrawTpage(unsigned char a0, unsigned char a1)//5EE78(<), 5FB58(<) (F)
{
	if ((unsigned long) db.polyptr < (unsigned long)db.polybuf_limit)
	{
		*(long*) &db.ot[a0] = db.polyptr;
		*(long*) &db.polyptr[0] = db.ot[a0] | 0x01000000;
		*(long*) &db.polyptr[4] = a1 << 5 | 0xE1000000;
	}
}