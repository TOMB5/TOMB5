#include "CALCHAIR.H"

#include "CALCLARA.H"
#include "CAMERA.H"
#include "DRAW.H"
#include "LARA.H"
#include "TYPES.H"
#include "MISC.H"
#include "GTEREG.H"
#include "SETUP.H"
#include "LARA.H"
#include "GAMEFLOW.H"
#include "HAIR.H"
#include "EFFECT2.H"

int* snaff_sphere_special(int* at, short* s7)
{
	at[0] = TRX;
	at[1] = TRY;
	at[2] = TRZ;
	at[3] = (((s7[3] << 1) + s7[3]) + (((s7[3] << 1) + s7[3]) >> 31)) >> 1;
	return at + 45;
}

void load_matrix(int* at)
{
	R11 = at[0] & 0xFFFF;
	R12 = (at[0] >> 16) & 0xFFFF;
	R13 = at[1] & 0xFFFF;
	R21 = (at[1] >> 16) & 0xFFFF;
	R22 = at[2] & 0xFFFF;
	R23 = (at[2] >> 16) & 0xFFFF;
	R31 = at[3] & 0xFFFF;
	R32 = (at[3] >> 16) & 0xFFFF;
	R33 = at[4] & 0xFFFF;
	TRX = at[5];
	TRY = at[6];
	TRZ = at[7];

	at[5] = TRX;
	at[6] = TRY;
	at[7] = TRZ;
}

void snaff_sphere_normal(short* s7, int* at)
{
	at[0] = TRX;
	at[1] = TRY;
	at[2] = TRZ;
	at[3] = s7[3];
}

void mTranslateXYZ_CH(int x, int y, int z)
{
	int t4 = y >> 15;

	if (y < 0)
	{
		y = -y;
		t4 = y >> 15;
		y &= 0x7FFF;
		t4 = -t4;
		y = -y;
	}
	else
	{
		//loc_1378
		y &= 0x7FFF;
	}

	int t5 = z >> 15;
	if (z < 0)
	{
		z = -z;
		t5 = z >> 15;
		z &= 0x7FFF;
		t5 = -t5;
		z = -z;
	}
	else
	{
		z &= 0x7FFF;
	}

	//loc_13A0
	int t3 = x >> 15;
	if (x < 0)
	{
		x = -x;
		t3 = x >> 15;
		x &= 0x7FFF;
		t3 = -t3;
		x = -x;
	}
	else
	{
		x &= 0x7FFF;
	}

	//loc_13C4
	IR1 = t3;
	IR2 = t4;
	IR3 = t5;

	docop2(0x41E012);

	t3 = MAC1;
	t4 = MAC2;
	t5 = MAC3;

	IR1 = x;
	IR2 = y;
	IR3 = z;

	docop2(0x498012);

	int t0 = t3 << 3;
	if (t3 < 0)
	{
		t3 = -t3;
		t3 <<= 3;
		t0 = -t3;
	}

	//loc_1408
	int t1 = t4 << 3;
	if (t4 < 0)
	{
		t4 = -t4;
		t4 <<= 3;
		t1 = -t4;
	}

	//loc_1430
	int t2 = t5 << 3;
	if (t5 < 0)
	{
		t5 = -t5;
		t5 <<= 3;
		t2 = -t5;
	}

	//loc_1430
	t3 = MAC1;
	t4 = MAC2;
	t5 = MAC3;

	t0 += t3;
	t1 += t4;
	t2 += t5;

	TRX = t0;
	TRY = t1;
	TRZ = t2;
}

void mRotY_CH(int y_rot)
{
	y_rot >>= 2;
	y_rot &= 0x3FFC;

	if (y_rot != 0)
	{
		int t5 = ((int*)&rcossin_tbl[y_rot >> 1])[0];
		int t7 = 0xFFFF0000;
		int t6 = t5 >> 16;
		t5 &= 0xFFFF;
		int t2 = -t5;

		VX0 = t6 & 0xFFFF;
		VY0 = (t6 >> 16) & 0xFFFF;
		VZ0 = t2;

		int t0 = (R11 & 0xFFFF) | ((R12 & 0xFFFF) << 16);
		t2 = (R22 & 0xFFFF) | ((R23 & 0xFFFF) << 16);
		int t3 = (R31 & 0xFFFF) | ((R32 & 0xFFFF) << 16);

		docop2(0x486012);
		VX1 = t5 & 0xFFFF;
		VY1 = (t5 >> 16) & 0xFFFF;
		VZ1 = t6;

		t0 &= t7;
		t2 &= 0xFFFF;
		t3 &= t7;
		int t4 = MAC1;
		int t1 = MAC2;
		t5 = MAC3;
		docop2(0x48E012);
		t4 &= 0xFFFF;
		t0 |= t4;
		t1 <<= 16;
		t5 &= 0xFFFF;
		t3 |= t5;
		t5 = MAC1;
		t6 = MAC2;
		t4 = MAC3;
		t5 &= 0xFFFF;
		t1 |= t5;
		t6 <<= 16;
		t2 |= t6;

		R11 = t0 & 0xFFFF;
		R12 = (t0 >> 16) & 0xFFFF;
		R13 = t1 & 0xFFFF;
		R21 = (t1 >> 16) & 0xFFFF;
		R22 = t2 & 0xFFFF;
		R23 = (t2 >> 16) & 0xFFFF;
		R31 = t3 & 0xFFFF;
		R32 = (t3 >> 16) & 0xFFFF;
		R33 = t4;
	}
}

void mRotX_CH(int a0)
{
	a0 >>= 2;
	a0 &= 0x3FFC;

	if (a0 != 0)
	{
		int t5 = ((int*)&rcossin_tbl[a0 >> 1])[0];
		int t7 = 0xFFFF0000;
		int t6 = t7 & t5;

		VX0 = t6 & 0xFFFF;
		VY0 = (t6 >> 16) & 0xFFFF;
		VZ0 = t5;

		int t0 = (R11 & 0xFFFF) | ((R12 & 0xFFFF) << 16);
		int t1 = (R13 & 0xFFFF) | ((R21 & 0xFFFF) << 16);
		int t3 = (R31 & 0xFFFF) | ((R32 & 0xFFFF) << 16);

		docop2(0x486012);

		t6 = t5 >> 16;
		t5 <<= 16;
		t5 = -t5;

		VX1 = t5 & 0xFFFF;
		VY1 = (t5 >> 16) & 0xFFFF;
		VZ1 = t6 & 0xFFFF;

		t0 &= 0xFFFF;
		t1 &= t7;
		t3 &= 0xFFFF;

		int t4 = MAC1;
		int t2 = MAC2;
		t5 = MAC3;

		docop2(0x48E012);
		t4 <<= 16;
		t0 |= t4;
		t2 &= 0xFFFF;
		t5 <<= 16;
		t3 |= t5;

		t5 = MAC1;
		t6 = MAC2;
		t4 = MAC3;

		t5 &= 0xFFFF;
		t1 |= t5;
		t6 <<= 16;
		t2 |= t6;

		R11 = t0 & 0xFFFF;
		R12 = (t0 >> 16) & 0xFFFF;
		R13 = t1 & 0xFFFF;
		R21 = (t1 >> 16) & 0xFFFF;
		R22 = t2 & 0xFFFF;
		R23 = (t2 >> 16) & 0xFFFF;
		R31 = t3 & 0xFFFF;
		R32 = (t3 >> 16) & 0xFFFF;
		R33 = t4;
	}
}

void mRotZ_CH(int a0)
{
	a0 >>= 2;
	a0 &= 0x3FFC;

	if (a0 != 0)
	{
		int t0 = ((int*)&rcossin_tbl[a0 >> 1])[0];
		int t7 = 0xFFFF0000;
		int t1 = (t0 >> 16) & 0xFFFF;
		int t2 = t0 << 16;
		t1 |= t2;

		VX0 = t1 & 0xFFFF;
		VY0 = (t1 >> 16) & 0xFFFF;
		VZ0 = 0;

		t1 = (R13 & 0xFFFF) | ((R21 & 0xFFFF) << 16);
		t2 = (R22 & 0xFFFF) | ((R23 & 0xFFFF) << 16);
		int t4 = R33;

		docop2(0x486012);

		int t3 = t0 & t7;
		t0 &= 0xFFFF;
		t0 = -t0;
		t0 &= 0xFFFF;
		t0 |= t3;

		VX1 = t0 & 0xFFFF;
		VY1 = (t0 >> 16) & 0xFFFF;
		VZ1 = 0;

		t1 &= 0xFFFF;

		t0 = MAC1;
		int t5 = MAC2;
		t3 = MAC3;

		docop2(0x48E012);

		t2 &= t7;
		t0 &= 0xFFFF;
		t5 <<= 16;
		t1 |= t5;
		t3 &= 0xFFFF;

		t5 = MAC1;
		int t6 = MAC2;
		int a0 = MAC3;

		t5 <<= 16;
		t0 |= t5;
		t6 &= 0xFFFF;
		t2 |= t6;
		a0 <<= 16;
		t3 |= a0;

		R11 = t0 & 0xFFFF;
		R12 = (t0 >> 16) & 0xFFFF;
		R13 = t1 & 0xFFFF;
		R21 = (t1 >> 16) & 0xFFFF;
		R22 = t2 & 0xFFFF;
		R23 = (t2 >> 16) & 0xFFFF;
		R31 = t3 & 0xFFFF;
		R32 = (t3 >> 16) & 0xFFFF;
		R33 = t4;
	}
}

void mRotSuperPackedYXZ_CH(int* fp, int a1)
{
	unsigned short* a2 = (unsigned short*)fp[10];
	int v0 = *a2;

	if (a1 != 0)
	{
		//loc_83A88
		do
		{
			v0 = *a2;
			a1--;
			if (!(v0 & 0xC000))
			{
				a2++;
			}
			a2++;

			//loc_83AA0
		} while (a1 != 0);

		v0 = *a2;
	}
	//loc_83AAC
	a2++;

	int at = v0 >> 14;
	if (at-- != 0)
	{
		fp[10] = (int)a2;

		if (at-- != 0)
		{
			if (at != 0)
			{
				mRotZ_CH((v0 & 0xFFF) << 4);
				return;
			}
			//loc_83AD8
			mRotY_CH((v0 & 0xFFF) << 4);
			return;
		}
		//loc_83AE0
		mRotX_CH((v0 & 0xFFF) << 4);
		return;
	}
	//loc_83AEC
	at = *a2++;
	fp[10] = (int)a2;
	v0 <<= 16;
	v0 |= at;

	mRotY_CH((v0 >> 4) & 0xFFC0);
	mRotX_CH((v0 >> 14) & 0xFFC0);
	mRotZ_CH((v0 & 0x3FF) << 6);
}

void mRotYXZ_CH(int y_rot, int x_rot, int z_rot)
{
	mRotY_CH(y_rot);
	mRotX_CH(x_rot);
	mRotZ_CH(z_rot);
}

void save_matrix(int* at)
{
	at[0] = (R11 & 0xFFFF) | ((R12 & 0xFFFF) << 16);
	at[1] = (R13 & 0xFFFF) | ((R21 & 0xFFFF) << 16);
	at[2] = (R22 & 0xFFFF) | ((R23 & 0xFFFF) << 16);
	at[3] = (R31 & 0xFFFF) | ((R32 & 0xFFFF) << 16);
	at[4] = (R33 & 0xFFFF);
	at[5] = TRX;
	at[6] = TRY;
	at[7] = TRZ;
}

void HairControl(int unk01, int bIsYoungLara, short* frame)
{
	struct ANIM_STRUCT* anim = NULL;//$v1
	int scratchPad[256];
	short* hit_frame = NULL;//$s3
	struct object_info* object = NULL;//$at
	long* bone = NULL;//$s6
	int* at = NULL;
	struct HAIR_STRUCT* s7 = NULL;
	int* a1 = NULL;
	int s5 = 0;

	S_MemSet((char*)&scratchPad, 0, 1024);

	//s0 = gfLevelFlags & 1
	int* fp = &scratchPad[0];
	//s5 = lara_item
	//v1 = lara.hit_direction
	//s4 = bIsYoungLara
	fp[11] = unk01;
	hit_frame = frame;
	int a0 = 0;

	if (frame == NULL)
	{
		if (lara.hit_direction >= 0)
		{
			//a1 = anims
			if (lara.hit_direction == 0)
			{
				//loc_82DAC
				if (lara.BurnSmoke == 0)
				{
					a0 = 0x7D;
				}
				else
				{
					a0 = 0x126;
				}
			}
			else if (lara.hit_direction == 2)
			{
				//loc_82DBC
				if (lara.BurnSmoke == 0)
				{
					a0 = 0x7E;
				}
				else
				{
					a0 = 0x125;
				}
			}
			else if (lara.hit_direction == 1)
			{
				//loc_82DCC
				if (lara.BurnSmoke == 0)
				{
					a0 = 0x7F;
				}
				else
				{
					a0 = 0x127;
				}
			}
			else
			{
				if (lara.BurnSmoke == 0)
				{
					a0 = 0x80;
				}
				else
				{
					a0 = 0x128;
				}
			}

			//loc_82DD8
			anim = &anims[a0];//$v1
			//v0 = anim->interpolation >> 8
			//a0 = lara.hit_frame
			//t1 = (lara.hit_frame * (anim->interpolation >> 8))
			//s3 = anim->frame_ptr
			hit_frame = &anim->frame_ptr[(lara.hit_frame * (anim->interpolation >> 8))];
		}
		else
		{
			//loc_82E00
			hit_frame = GetBestFrame(lara_item);
		}
	}//loc_82E0C

	save_matrix(&fp[37]);

	R11 = 4096;
	R12 = 0;
	R13 = 0;
	R21 = 0;
	R22 = 4096;
	R23 = 0;
	R31 = 0;
	R32 = 0;
	R33 = 4096;

	fp[10] = (int)&hit_frame[9];

	TRX = lara_item->pos.x_pos;
	TRY = lara_item->pos.y_pos;
	TRZ = lara_item->pos.z_pos;
	
	mRotYXZ_CH(lara_item->pos.y_rot, lara_item->pos.x_rot, lara_item->pos.z_rot);
	object = &objects[LARA];
	//v0 = objects.bone_index
	bone = &bones[object->bone_index];
	mTranslateXYZ_CH(hit_frame[6], hit_frame[7], hit_frame[8]);
	mRotSuperPackedYXZ_CH(fp, 0);

	//s7 = lara.mesh_ptrs[0];
	save_matrix(&fp[45]);
	mTranslateXYZ_CH(lara.mesh_ptrs[0][0], lara.mesh_ptrs[0][1], lara.mesh_ptrs[0][2]);
	snaff_sphere_normal(lara.mesh_ptrs[0], &fp[17]);
	mTranslateXYZ_CH(bone[25], bone[26], bone[27]);
	mRotSuperPackedYXZ_CH(fp, 6);
	mRotYXZ_CH(lara.torso_y_rot, lara.torso_x_rot, lara.torso_z_rot);
	save_matrix(&fp[45]);
	mTranslateXYZ_CH(lara.mesh_ptrs[0][0], lara.mesh_ptrs[0][1], lara.mesh_ptrs[0][2]);

	//at = &fp[21];
	//v0 = lara.mesh_ptrs[0][3];
	fp[21] = TRX;
	fp[22] = TRY;
	fp[23] = TRZ;

	//a0 = v0 >> 2
	if ((gfLevelFlags & 1))
	{
		fp[24] = lara.mesh_ptrs[0][3] - ((lara.mesh_ptrs[0][3] >> 2) + lara.mesh_ptrs[0][3] >> 3);
	}
	else
	{
		fp[24] = lara.mesh_ptrs[0][3];
	}

	//loc_82F1C
	load_matrix(&fp[45]);
	//s7 = lara.mesh_ptrs[8];
	mTranslateXYZ_CH(bone[29], bone[30], bone[31]);
	mRotSuperPackedYXZ_CH(fp, 0);
	mTranslateXYZ_CH(lara.mesh_ptrs[8][0], lara.mesh_ptrs[8][1], lara.mesh_ptrs[8][2]);

	at = snaff_sphere_special(&fp[29], lara.mesh_ptrs[8]);
	//s7 = lara.mesh_ptrs[11];
	mTranslateXYZ_CH(bone[41], bone[42], bone[43]);
	mRotSuperPackedYXZ_CH(fp, 2);
	mTranslateXYZ_CH(lara.mesh_ptrs[11][0], lara.mesh_ptrs[11][1], lara.mesh_ptrs[11][2]);
	at = snaff_sphere_special(&fp[33], lara.mesh_ptrs[11]);
	mTranslateXYZ_CH(bone[53], bone[54], bone[55]);
	mRotSuperPackedYXZ_CH(fp, 2);
	mRotYXZ_CH(lara.head_y_rot, lara.head_x_rot, lara.head_z_rot);
	//s7 = lara.mesh_ptrs[14]
	save_matrix(&fp[45]);
	mTranslateXYZ_CH(lara.mesh_ptrs[14][0], lara.mesh_ptrs[14][1], lara.mesh_ptrs[14][2]);
	snaff_sphere_normal(lara.mesh_ptrs[14], &fp[25]);

	fp[21] = (fp[21] + fp[25]) >> 1;
	fp[22] = (fp[22] + fp[26]) >> 1;
	fp[23] = (fp[23] + fp[27]) >> 1;

	//loc_83020
	if (bIsYoungLara == 0)
	{
		if ((gfLevelFlags & 1))
		{
			mTranslateXYZ_CH(-52, -48, -50);
		}
		else
		{
			//loc_83040
			mTranslateXYZ_CH(-4, -4, -48);
		}
	}
	else
	{
		//loc_83054
		mTranslateXYZ_CH(44, -48, -50);
	}

	fp[12] = TRX;
	fp[13] = TRY;
	fp[14] = TRZ;

	load_matrix(&fp[37]);
	s7 = &hairs[bIsYoungLara][0];
	a1 = &first_hair[bIsYoungLara];
	//a0 = objects[HAIR].bone_index
	bone = &bones[objects[HAIR].bone_index];

	if (lara.hit_direction != 0)
	{
		a1[0] = 0;
		s7->pos.x_pos = fp[12];
		s7->pos.y_pos = fp[13];
		s7->pos.z_pos = fp[14];

		s5 = 6;
		//loc_830DC
		do
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

			TRX = s7->pos.x_pos;
			TRY = s7->pos.y_pos;
			TRZ = s7->pos.z_pos;
			s5--;
			mRotYXZ_CH(s7->pos.y_rot, s7->pos.x_rot, 0);
			mTranslateXYZ_CH(bone[1], bone[2], bone[3]);

			s7[1].pos.x_pos = TRX;
			s7[1].pos.y_pos = TRY;
			s7[1].pos.z_pos = TRZ;
			bone += 4;
			s7++;

		} while (s5 != 0);

		SmokeWindZ = 0;
		SmokeWindX = 0;
		hair_wind = 0;
		hair_dwind_angle = 2048;
		hair_wind_angle = 2048;
		load_matrix(&fp[37]);
		return;
	}
	else
	{
		//loc_8316C

	}
#if 0

		loc_8316C:
		lw      $v0, arg_30($fp)
		lw      $v1, arg_34($fp)
		lw      $a0, arg_38($fp)
		sw      $v0, 0($s7)
		sw      $v1, 4($s7)
		sw      $a0, 8($s7)
		lw      $t1, arg_2C($fp)
		lh      $a3, 0x18($s5)
		beqz    $t1, loc_831A0
		sh      $a3, arg_3C($fp)
		li      $t1, 0xFFFF8100
		j       loc_831F0
		sw      $t1, arg_40($fp)

		loc_831A0:
	lh      $a0, 0($s3)
		lh      $v0, 2($s3)
		lw      $v1, 0x40($s5)
		lh      $a1, 4($s3)
		lh      $a2, 8($s3)
		addu    $a0, $v0
		sra     $a0, 1
		addu    $a0, $v1, $a0
		lh      $v0, 6($s3)
		lw      $v1, 0x44($s5)
		addu    $a1, $v0
		sra     $a1, 1
		lh      $v0, 0xA($s3)
		addu    $a1, $v1, $a1
		addu    $a2, $v0
		lw      $v0, 0x48($s5)
		sra     $a2, 1
		jal     sub_1E534
		addu    $a2, $v0, $a2
		sw      $v0, arg_40($fp)

		loc_831F0:
	jal     sub_5E9F0
		nop
		lw      $v1, 0x534($gp)
		andi    $v0, 7
		addiu   $v1, -3
		addu    $v1, $v0
		slti    $v0, $v1, -1
		bnez    $v0, loc_83220
		li      $v0, 1
		slti    $v0, $v1, 9
		bnez    $v0, loc_83224
		li      $v0, 0xFFFFFFFF

		loc_83220:
	addu    $v1, $v0

		loc_83224 :
	sw      $v1, 0x534($gp)
		jal     sub_5E9F0
		nop
		andi    $v0, 0x3F
		addiu   $v0, -0x20
		lw      $v1, 0x53C($gp)
		sll     $v0, 1
		addu    $v1, $v0
		andi    $v1, 0x1FFE
		slti    $v0, $v1, 0x400
		beqz    $v0, loc_83264
		li      $v0, 0x400
		subu    $v0, $v1
		sll     $v0, 1
		j       loc_8327C
		addu    $v1, $v0

		loc_83264 :
	slti    $v0, $v1, 0xC01
		bnez    $v0, loc_8327C
		li      $v0, 0xC00
		subu    $v0, $v1, $v0
		sll     $v0, 1
		subu    $v1, $v0

		loc_8327C :
	sw      $v1, 0x53C($gp)
		lw      $v0, 0x53C($gp)
		lw      $v1, 0x538($gp)
		lw      $a0, 0x534($gp)
		subu    $v0, $v1
		sra     $v0, 3
		addu    $v1, $v0
		andi    $v1, 0x1FFE
		sw      $v1, 0x538($gp)
		sll     $v1, 1
		lw      $v0, dword_9A8C8($v1)
		addiu   $s7, 0x20
		sra     $at, $v0, 16
		mult    $at, $a0
		mflo    $a1
		sll     $at, $v0, 16
		sra     $at, 16
		mult    $at, $a0
		sra     $a1, 12
		sw      $a1, 0x2BFC($gp)
		mflo    $a2
		sra     $a2, 12
		sw      $a1, 0x2BF8($gp)
		li      $s3, 1

		loc_832E4:
	lw      $a0, 0($s7)
		lw      $a1, 4($s7)
		lw      $a2, 8($s7)
		lw      $t1, arg_2C($fp)
		sw      $a0, arg_30($fp)
		sw      $a1, arg_34($fp)
		bnez    $t1, loc_83328
		sw      $a2, arg_38($fp)
		jal     sub_78954
		addiu   $a3, $fp, arg_3C
		lw      $a1, arg_30($fp)
		lw      $a2, arg_34($fp)
		lw      $a3, arg_38($fp)
		jal     sub_78C74
		move    $a0, $v0
		j       loc_8332C
		move    $a2, $v0

		loc_83328 :
	li      $a2, 0x7FFF

		loc_8332C :
		lw      $v1, 0x14($s7)
		lw      $v0, 0($s7)
		sll     $at, $v1, 1
		addu    $v1, $at, $v1
		sra     $v1, 2
		addu    $v0, $v1
		sw      $v0, 0($s7)
		lw      $v1, 0x18($s7)
		lw      $v0, 4($s7)
		sll     $at, $v1, 1
		addu    $v1, $at, $v1
		sra     $v1, 2
		addu    $v0, $v1
		sw      $v0, 4($s7)
		lw      $v1, 0x1C($s7)
		lw      $v0, 8($s7)
		sll     $at, $v1, 1
		addu    $v1, $at, $v1
		sra     $v1, 2
		addu    $v0, $v1
		sw      $v0, 8($s7)
		lh      $a3, 0x5234($gp)
		lh      $v1, arg_3C($fp)
		bnez    $a3, loc_833D4
		sll     $v0, $v1, 2
		addu    $v0, $v1
		lw      $v1, 0x1F28($gp)
		sll     $v0, 4
		addu    $v0, $v1
		lhu     $v0, 0x4E($v0)
		nop
		andi    $v0, 0x20
		beqz    $v0, loc_833D4
		nop
		lw      $v0, 0($s7)
		lw      $a0, 8($s7)
		lw      $v1, 0x2BF8($gp)
		lw      $a1, 0x2BFC($gp)
		addu    $v0, $v1
		addu    $a0, $a1
		sw      $v0, 0($s7)
		sw      $a0, 8($s7)

		loc_833D4:
	lw      $v1, 4($s7)
		lw      $t1, arg_40($fp)
		beqz    $a3, loc_8341C
		li      $at, 1
		beq     $a3, $at, loc_833F8
		li      $at, 2
		beq     $a3, $at, loc_833F8
		li      $at, 4
		bne     $a3, $at, loc_8344C

		loc_833F8 :
	slt     $v0, $v1, $t1
		beqz    $v0, loc_8340C
		slt     $v0, $a2, $v1

		loc_83404 :
	j       loc_8344C
		sw      $t1, 4($s7)

		loc_8340C :
		beqz    $v0, loc_8344C
		nop
		j       loc_8344C
		sw      $a2, 4($s7)

		loc_8341C :
		li      $v0, 0xFFFF8100
		addiu   $v1, 0xA
		sw      $v1, 4($s7)
		beq     $t1, $v0, loc_83434
		slt     $v0, $t1, $v1
		bnez    $v0, loc_83404

		loc_83434 :
	slt     $v0, $a2, $v1
		beqz    $v0, loc_8344C
		lw      $v0, arg_30($fp)
		lw      $v1, arg_38($fp)
		sw      $v0, 0($s7)
		sw      $v1, 8($s7)

		loc_8344C:
	li      $t3, 5
		addiu   $t4, $fp, arg_44

		loc_83454 :
	lw      $a0, 0($s7)
		lw      $a1, 4($s7)
		lw      $a2, 8($s7)
		lw      $at, 0($t4)
		lw      $v0, 4($t4)
		lw      $v1, 8($t4)
		subu    $t0, $a0, $at
		subu    $t1, $a1, $v0
		subu    $t2, $a2, $v1
		lw      $v0, 0xC($t4)
		mtc2    $t0, $9
		mtc2    $t1, $10
		mtc2    $t2, $11
		mult    $v0, $v0
		cop2    0xA00428
		mflo    $v0
		mfc2    $a0, $25
		mfc2    $v1, $26
		mfc2    $at, $27
		addu    $a0, $v1
		addu    $a0, $at
		slt     $at, $a0, $v0
		beqz    $at, loc_8351C
		addiu   $t3, -1
		jal     sub_83B30
		nop
		bnez    $v0, loc_834C8
		lw      $v1, 0xC($t4)
		li      $v0, 1

		loc_834C8:
	lw      $at, 0($t4)
		sll     $v1, 16
		div     $v1, $v0
		mflo    $a0
		lw      $v0, 4($t4)
		lw      $v1, 8($t4)
		mult    $a0, $t0
		mflo    $t0
		sra     $t0, 16
		addu    $t0, $at
		mult    $a0, $t1
		sw      $t0, 0($s7)
		mflo    $t1
		sra     $t1, 16
		addu    $t1, $v0
		mult    $a0, $t2
		sw      $t1, 4($s7)
		mflo    $t2
		sra     $t2, 16
		addu    $t2, $v1
		sw      $t2, 8($s7)

		loc_8351C:
	bnez    $t3, loc_83454
		addiu   $t4, 0x10
		li      $at, 0x1000
		ctc2    $at, $0
		ctc2    $zero, $1
		ctc2    $at, $2
		ctc2    $zero, $3
		ctc2    $at, $4
		lw      $v0, 8($s7)
		lw      $v1, -0x18($s7)
		lw      $a0, 0($s7)
		lw      $a1, -0x20($s7)
		subu    $t0, $v0, $v1
		subu    $t1, $a0, $a1
		mtc2    $t0, $9
		mtc2    $t1, $10
		nop
		cop2    0xA00428
		mfc2    $a0, $25
		mfc2    $a1, $26
		jal     sub_83B30
		addu    $a0, $a1
		move    $t2, $v0
		move    $a0, $t0
		jal     sub_77A40
		move    $a1, $t1
		sh      $v0, -0x12($s7)
		lw      $v1, 4($s7)
		lw      $a1, -0x1C($s7)
		move    $a0, $t2
		jal     sub_77A40
		subu    $a1, $v1, $a1
		negu    $v0, $v0
		sh      $v0, -0x14($s7)
		lw      $a0, -0x20($s7)
		lw      $a1, -0x1C($s7)
		lw      $a2, -0x18($s7)
		ctc2    $a0, $5
		ctc2    $a1, $6
		ctc2    $a2, $7
		lh      $a0, -0x12($s7)
		lh      $a1, -0x14($s7)
		jal     sub_83994
		move    $a2, $zero
		li      $v0, 6
		bne     $s3, $v0, loc_835E8
		nop
		lw      $a0, -0xC($s6)
		lw      $a1, -8($s6)
		j       loc_835F4
		lw      $a2, -4($s6)

		loc_835E8:
	lw      $a0, 4($s6)
		lw      $a1, 8($s6)
		lw      $a2, 0xC($s6)

		loc_835F4 :
		jal     sub_83744
		addiu   $s6, 0x10
		sw      $t0, 0($s7)
		sw      $t1, 4($s7)
		sw      $t2, 8($s7)
		lw      $v0, arg_30($fp)
		lw      $v1, arg_34($fp)
		lw      $a0, arg_38($fp)
		subu    $t0, $v0
		subu    $t1, $v1
		subu    $t2, $a0
		sw      $t0, 0x14($s7)
		sw      $t1, 0x18($s7)
		sw      $t2, 0x1C($s7)
		jal     sub_836B8
		addiu   $at, $fp, arg_94
		addiu   $s3, 1
		slti    $v0, $s3, 7
		bnez    $v0, loc_832E4
		addiu   $s7, 0x20
		lw      $ra, 0x1F800024
		lw      $s0, 0x1F800000
		lw      $s3, 0x1F80000C
		lw      $s4, 0x1F800010
		lw      $s5, 0x1F800014
		lw      $s6, 0x1F800018
		lw      $s7, 0x1F80001C
		lw      $fp, 0x1F800020
		jr      $ra
		nop
#endif
}
