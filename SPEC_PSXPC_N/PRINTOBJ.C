#include "PRINTOBJ.H"

#include "CAMERA.H"
#include "DRAW.H"
#include "SPECIFIC.H"
#include "MATHS.H"
#include "3D_GEN.H"
#include "CONTROL.H"
#include "SETUP.H"
#include "ITEMS.H"
#include "EFFECTS.H"
#include "LOAD_LEV.H"
#include "DELTAPAK.H"
#include "DRAWOBJ.H"

#include <GTEREG.H>

void init_scratchpad(int* fp)//8281C(<) (F)
{
	int t0;
	int t1;
	int t2;
	int t3;
	int t4;
	int t5;
	int t6;
	int t7;
	int* at = &fp[47];
	fp[20] = (int)at;

	t0 = R11 | (R12 << 16);
	t1 = R13 | (R21 << 16);
	t2 = R22 | (R23 << 16);
	t3 = R31 | (R32 << 16);
	t4 = R33;
	t5 = TRX;
	t6 = TRY;
	t7 = TRZ;

	at[0] = t0;
	at[1] = t1;
	at[2] = t2;
	at[3] = t3;
	at[4] = t4;
	at[5] = t5;
	at[6] = t6;
	at[7] = t7;
	//v0 = (int)&stashed_objects_list[0]
	//v1 = (int)&stashed_matrix_list[0]
	//a0 = (int)&items[0]
	//a1 = (int)&room[0]

	fp[16] = (int)stashed_objects_list;
	fp[17] = (int)stashed_matrix_list;
	fp[18] = 0;
	fp[24] = (int)items;
	fp[38] = (int)room;

	//v0 = camera.pos.room_number
	//v1 = anims
	//a0 = meshes
	//a1 = bones

	((short*)fp)[53] = camera.pos.room_number;
	fp[39] = (int)anims;
	fp[40] = (int)meshes;
	fp[41] = (int)bones;

	t0 = ((int*)MatrixStack)[5];
	t1 = ((int*)MatrixStack)[6];
	t2 = ((int*)MatrixStack)[7];

	fp[46] = BinocularRange;
	fp[27] = t0;
	fp[28] = t1;
	fp[29] = t2;

	/* Must be set in outer function */
	//s1 = number_draw_rooms 
	//s0 = &draw_rooms[0];
}

void CalcAllAnimatingItems_ASM()
{
	int scratchPad[256];
	int* fp;

	fp = &scratchPad[0];
	init_scratchpad(fp);
#if 0
		blez    $s1, loc_827DC

		loc_82658 :
		lh      $a0, 0($s0)
		lw      $v1, 0x80 + arg_18($fp)
		sll     $v0, $a0, 2
		addu    $v0, $a0
		sll     $v0, 4
		addu    $s2, $v1, $v0
		sh      $a0, 0x80 + var_18($fp)
		jal     sub_81BBC
		sw      $s2, 0x80 + var_1C($fp)
		lh      $s3, 0x32($s2)
		lw      $s4, 0x10($s2)
		blez    $s3, loc_8275C
		lw      $v0, 0x38($s2)
		lw      $v1, 0x3C($s2)
		sw      $v0, 0x80 + arg_10($fp)
		sw      $v1, 0x80 + arg_14($fp)

		loc_82698:
	lh      $v0, 0x12($s4)
		lh      $v1, 0x10($s4)
		li      $s5, 0x1F9780//static objects?
		sll     $at, $v0, 3
		subu    $at, $v0
		sll     $at, 2
		andi    $v0, $v1, 1
		beqz    $v0, loc_82750
		addu    $s5, $at
		jal     sub_81BBC
		lw      $a1, 4($s4)
		lw      $a0, 0($s4)
		jal     sub_81A8C
		lw      $a2, 8($s4)
		lh      $a0, 0xC($s4)
		jal     sub_81858
		nop
		lhu     $v1, 2($s5)
		cfc2    $at, $7
		srl     $v1, 2
		sll     $v1, 10
		beqz    $v1, loc_82704
		slt     $at, $v1, $at
		beqz    $at, loc_82704
		nop
		addiu   $s5, 0x1C

		loc_82704:
	jal     sub_811FC
		addiu   $a0, $s5, 4
		beqz    $v0, loc_8274C
		lw      $a3, 0x80 + var_38($fp)
		lw      $a2, 0x80 + var_40($fp)
		addiu   $a3, 1
		sw      $a3, 0x80 + var_38($fp)
		sh      $v0, 0($a2)
		sw      $s4, 4($a2)
		sh      $zero, 2($a2)
		addiu   $a2, 0xC
		sw      $a2, 0x80 + var_40($fp)
		lh      $v1, 0($s5)
		lw      $v0, 0x80 + arg_20($fp)
		sll     $v1, 2
		addu    $v0, $v1
		jal     sub_81750
		lw      $a0, 0($v0)

		loc_8274C:
	jal     sub_81C0C

		loc_82750 :
	addiu   $s3, -1
		bgtz    $s3, loc_82698
		addiu   $s4, 0x14

		loc_8275C :
		lh      $s2, 0x48($s2)
		li      $v1, 0xFFFFFFFF
		beq     $s2, $v1, loc_827CC
		sll     $v0, $s2, 7

		loc_8276C :
		sll     $v1, $s2, 4
		lw      $s3, 0x80 + var_20($fp)
		addu    $v0, $v1
		addu    $s3, $v0
		lh      $v1, 0xC($s3)
		li      $s6, 0x1F2480//objects?
		sll     $v1, 6
		addu    $s6, $v1
		lhu     $v0, 0x32($s6)
		lw      $a1, 0x84($s3)
		andi    $v0, 0x200
		beqz    $v0, loc_827BC
		li      $v1, 6
		andi    $a1, 6
		beq     $a1, $v1, loc_827BC
		nop
		jal     sub_81504
		move    $s2, $s3
		move    $s3, $s2

		loc_827BC :
	lh      $s2, 0x1A($s3)
		li      $v0, 0xFFFFFFFF
		bne     $s2, $v0, loc_8276C
		sll     $v0, $s2, 7

		loc_827CC :
		jal     sub_81C0C
		addiu   $s1, -1
		bnez    $s1, loc_82658
		addiu   $s0, 2

		loc_827DC :
		lw      $s4, 0x80 + var_38($fp)
		lui     $gp, 0xA
		jal     sub_82900
		la      $gp, aTwat       # "TWAT"
		lw      $ra, 0x80 + var_44($sp)
		lw      $fp, 0x80 + var_48($sp)
		lw      $s7, 0x80 + var_4C($sp)
		lw      $s6, 0x80 + var_50($sp)
		lw      $s5, 0x80 + var_54($sp)
		lw      $s4, 0x80 + var_58($sp)
		lw      $s3, 0x80 + var_5C($sp)
		lw      $s2, 0x80 + var_60($sp)
		lw      $s1, 0x80 + var_64($sp)
		lw      $s0, 0x80 + var_68($sp)
		jr      $ra
		addiu   $sp, 0x80
#endif
}

void DrawEffect(short item_num)
{
	struct FX_INFO* fx = &effects[item_num];
	struct object_info* obj = &objects[fx->object_number];

	if (obj->draw_routine != NULL && obj->loaded)
	{
		mPushMatrix();
		mTranslateAbsXYZ(fx->pos.x_pos, fx->pos.y_pos, fx->pos.z_pos);

		if (Matrix->tz < 20480)
		{
			mRotYXZ(fx->pos.y_rot, fx->pos.x_rot, fx->pos.z_rot);

			S_CalculateLight(fx->pos.x_pos, fx->pos.y_pos, fx->pos.z_pos, fx->room_number, &duff_item.il);
			duff_item.il.Light[3].pad = 0;

			phd_PutPolygons(meshes[obj->nmeshes != 0 ? obj->mesh_index : fx->frame_number], -1);
		}

		mPopMatrix();
	}
}

void PrintAllOtherObjects_ASM(short room_num /*s3*/)//(F)
{
	struct room_info* r = &room[room_num];
	struct ITEM_INFO* item = NULL;
	struct object_info* object;
	short item_num;
	struct FX_INFO* effect;
	int mesh_num;
	short* mesh;
	int effect_num;

	r->bound_active = 0;
	mPushMatrix();
	mTranslateAbsXYZ(r->x, r->y, r->z);

	phd_right = 512;
	phd_bottom = 240;
	phd_left = 0;
	phd_top = 0;

	item_num = r->item_number;

	if (item_num != -1)
	{
		do
		{
			item = &items[item_num];
			object = &objects[item->object_number];

			if (item->status != 6)
			{
				if (!object->using_drawanimating_item && object->draw_routine != NULL)
				{
					object->draw_routine(item);
				}
			}
			//loc_8F5AC
			if (object->draw_routine_extra != NULL)
			{
				object->draw_routine_extra(item);
			}

			//loc_8F5C4
			if (item->after_death - 1 < 127)
			{
				item->after_death++;

				if (item->after_death == 128)
				{
					KillItem(r->item_number);
				}
			}//loc_8F5EC

			item_num = item->next_item;
		} while (item_num != -1);

	}//loc_8F5FC

	effect_num = r->fx_number;

	if (effect_num != -1)
	{
		//loc_8F608
		do
		{
			effect = &effect[effect_num];
			object = &objects[effect->object_number];

			if (object->draw_routine != NULL && object->loaded)
			{
				mPushMatrix();
				mTranslateAbsXYZ(effect->pos.x_pos, effect->pos.y_pos, effect->pos.z_pos);

				if (((int*)MatrixStack)[2] - 21 < 20459)
				{
					mRotYXZ(effect->pos.y_rot, effect->pos.x_rot, effect->pos.z_rot);

					duff_item.il.Light[3].pad = 0;
					S_CalculateLight(effect->pos.x_pos, effect->pos.y_pos, effect->pos.z_pos, effect->room_number, &duff_item.il);

					mesh_num = effect->frame_number;

					if (object->nmeshes != 0)
					{
						mesh_num = object->mesh_index;
					}//loc_8F6C0

					phd_PutPolygons(meshes[mesh_num], -1);
				}//loc_8F6D8

				mPopMatrix();

				//loc_8F6E0
				effect_num = effect->next_fx;
			}
		} while (effect_num != -1);//loc_8F6E0
	}//loc_8F6EC

	mPopMatrix();
	((int*)&r->left)[0] = 511;
	((int*)&r->top)[0] = 239;
}

void print_all_object_NOW()//8F474(<), 914B8(<) (F)
{
	CalcAllAnimatingItems_ASM();

	for (int i = 0; i < number_draw_rooms; i++)
	{
		PrintAllOtherObjects_ASM(draw_rooms[i]);
	}
}