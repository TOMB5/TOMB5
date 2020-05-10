#include "ANIMITEM.H"

#include "3D_GEN.H"
#include "CONTROL.H"
#include "LOAD_LEV.H"
#include "DRAW.H"
#include "CAMERA.H"
#include "SETUP.H"
#include "DRAWOBJ.H"
#include "MATHS.H"
#include "MISC.H"
#include "LIGHT.H"

#include "GTEREG.H"
#include <assert.h>

void SetRotation_AI(int* fp, int t0, int t1, int t2, int t3, int t4)
{
	int a0 = fp[20];

	R11 = t0 & 0xFFFF;
	R12 = (t0 >> 16) & 0xFFFF;
	R13 = t1 & 0xFFFF;
	R21 = (t1 >> 16) & 0xFFFF;
	R22 = t2 & 0xFFFF;
	R23 = (t2 >> 16) & 0xFFFF;
	R31 = t3 & 0xFFFF;
	R32 = (t3 >> 16) & 0xFFFF;
	R33 = t4 & 0xFFFF;

	((int*)a0)[0] = t0;
	((int*)a0)[1] = t1;
	((int*)a0)[2] = t2;
	((int*)a0)[3] = t3;
	((int*)a0)[4] = t4;
}


void mRotY_AI(int ry, int* fp)//0x81858
{
	ry = (ry >> 2) & 0x3FFC;
	if (ry == 0)
	{
		return;
	}

	//t0 = 0x9A8C8 rcossin_tbl
	//loc_81870
	int t5 = ((int*)&rcossin_tbl[ry >> 1])[0];
	int t7 = 0xFFFF0000;
	int t6 = (t5 >> 16) & 0xFFFF;
	t5 &= 0xFFFF;
	int t2 = -t5;
	VX0 = t6;
	VY0 = (t6 >> 16) & 0xFFFF;
	VZ0 = t2;

	int t0 = (R11 & 0xFFFF) | ((R12 & 0xFFFF) << 16);
	t2 = (R22 & 0xFFFF) | ((R23 & 0xFFFF) << 16);
	int t3 = (R31 & 0xFFFF) | ((R32 & 0xFFFF) << 16);

	docop2(0x486012);

	VX1 = t5 & 0xFFFF;
	VY1 = (t5 >> 16) & 0xFFFF;
	VZ1 = t6 & 0xFFFF;

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

	SetRotation_AI(fp, t0, t1, t2, t3, t4);
}

void mRotX_AI(int rx, int* fp)//0x817B0
{
	rx = (rx >> 2) & 0x3FFC;
	if (rx == 0)
	{
		return;
	}

	//loc_81870
	int t5 = ((int*)&rcossin_tbl[rx >> 1])[0];
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
	VZ1 = t6;

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
	t2 |= t5;

	SetRotation_AI(fp, t0, t1, t2, t3, t4);
}

void mRotZ_AI(int rz, int* fp)//0x81918
{
	rz = (rz >> 2) & 0x3FFC;
	if (rz == 0)
	{
		return;
	}

	//loc_81870
	int t0 = ((int*)&rcossin_tbl[rz >> 1])[0];
	int t7 = 0xFFFF0000;
	int t1 = t0 >> 16;
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

	SetRotation_AI(fp, t0, t1, t2, t3, t4);
}

int GetFrames_AI(struct ITEM_INFO* item /*s3*/, int* fp)//81468
{
	struct ANIM_STRUCT* anim;//$t0
	int t1;
	int t2;
	int t3;
	short* t4;
	short* t5;

	anim = &((struct ANIM_STRUCT*)fp[39])[item->anim_number];

	fp[23] = anim->interpolation & 0xFF;
	t1 = (item->frame_number - anim->frame_base) / (anim->interpolation & 0xFF);
	t2 = (item->frame_number - anim->frame_base) % (anim->interpolation & 0xFF);

	t3 = t1 * (anim->interpolation >> 8);
	t4 = &anim->frame_ptr[t3];
	fp[30] = (int)t4;
	t5 = &t4[(anim->interpolation >> 8)];
	fp[31] = (int)t5;

	if (t2 == 0)
	{
		return 0;
	}

	//loc_814D8
	t3 = t1 * (anim->interpolation & 0xFF);
	if (anim->frame_end < t3 + (anim->interpolation & 0xFF))
	{
		fp[23] = anim->frame_end - ((t3 + (anim->interpolation & 0xFF)) - (anim->interpolation & 0xFF));
	}

	return t2;
}

void mTranslateXYZ_AI(int tx, int ty, int tz, int* fp)//81AB0
{
	int t4 = ty >> 15;
	if (ty < 0)
	{
		ty = -ty;
		t4 = ty >> 15;
		ty &= 0x7FFF;
		t4 = -t4;
		ty = -ty;

	}
	else
	{
		//loc_81AD0
		ty &= 0x7FFF;
	}

	//loc_81AD4
	int t5 = tz >> 15;
	if (tz < 0)
	{
		tz = -tz;
		t5 = tz >> 15;
		tz &= 0x7FFF;
		t5 = -t5;
		tz = -tz;
	}
	else
	{
		//loc_81AF4
		tz &= 0x7FFF;
	}

	//loc_81AF8
	int t3 = tx >> 15;
	if (tx < 0)
	{
		tx = -tx;
		t3 = tx >> 15;
		tx &= 0x7FFF;
		t3 = -t3;
		tx = -tx;
	}
	else
	{
		//loc_81B18
		tx &= 0x7FFF;
	}

	//loc_81B1C
	IR1 = t3;
	IR2 = t4;
	IR3 = t5;

	int v0 = fp[20];

	docop2(0x41E012);

	t3 = MAC1;
	t4 = MAC2;
	t5 = MAC3;

	IR1 = tx;
	IR2 = ty;
	IR3 = tz;

	docop2(0x498012);

	int t0 = t3 << 3;
	if (t3 < 0)
	{
		t3 = -t3;
		t3 <<= 3;
		t0 = -t3;
	}//loc_81B60

	int t1 = t4 << 3;
	if (t4 < 0)
	{
		t4 = -t4;
		t4 <<= 3;
		t1 = -t4;
	}

	//loc_81B74
	int t2 = t5 << 3;
	if (t5 < 0)
	{
		t5 = -t5;
		t5 <<= 3;
		t2 = -t5;
	}
	//loc_81B88
	t3 = MAC1;
	t4 = MAC2;
	t5 = MAC3;

	t0 += t3;
	t1 += t4;
	t2 += t5;

	TRX = t0;
	TRY = t1;
	TRZ = t2;

	((int*)v0)[5] = t0;
	((int*)v0)[6] = t1;
	((int*)v0)[7] = t2;
}


void mTranslateAbsXYZ_AI(int tx, int ty, int tz, int* fp)
{
	TRX = 0;
	TRY = 0;
	TRZ = 0;
	tx -= fp[27];
	ty -= fp[28];
	tz -= fp[29];

	mTranslateXYZ_AI(tx, ty, tz, fp);
}

void mRotYXZ_AI(int y, int x, int z, int* fp)//818FC
{
	mRotY_AI(y, fp);
	mRotX_AI(x, fp);
	mRotZ_AI(z, fp);
}

void calc_animating_item_clip_window(struct ITEM_INFO* item /*s3*/, unsigned short* s2, int* fp)//80DD8
{
	int* s1 = (int*)fp[25];
	int t3;
	int t2;
	int t1;
	int t0;

	if (item->object_number - 0x1A0 >= 0x1F && item->object_number - 0x11C >= 0x20)
	{
		//a1 = 0x1000
		R11 = 4096;
		R12 = 0;
		R13 = 0;
		R21 = 0;
		R22 = 4096;
		R23 = 0;
		R31 = 0;
		R32 = 0;
		R33 = 4096;

		fp[20] += 0x20;
		mRotYXZ_AI(item->pos.y_rot, item->pos.x_rot, item->pos.z_rot, fp);

		TRX = 0;
		TRY = 0;
		TRZ = 0;

		//t5 = 0x1f800000
		((short*)fp)[0] = s2[0];///@0x1F800000
		((short*)fp)[1] = s2[2];
		((short*)fp)[2] = s2[4];

		((short*)fp)[4] = s2[1];
		((short*)fp)[5] = s2[2];
		((short*)fp)[6] = s2[4];

		((short*)fp)[8] = s2[1];
		((short*)fp)[9] = s2[3];
		((short*)fp)[10] = s2[4];

		((short*)fp)[12] = s2[0];
		((short*)fp)[13] = s2[3];
		((short*)fp)[14] = s2[4];

		((short*)fp)[16] = s2[0];
		((short*)fp)[17] = s2[2];
		((short*)fp)[18] = s2[5];

		((short*)fp)[20] = s2[1];
		((short*)fp)[21] = s2[2];
		((short*)fp)[22] = s2[5];

		((short*)fp)[24] = s2[1];
		((short*)fp)[25] = s2[3];
		((short*)fp)[26] = s2[5];

		((short*)fp)[28] = s2[0];
		((short*)fp)[29] = s2[3];
		((short*)fp)[30] = s2[5];

		int s5 = 32767;
		int s4 = -32767;
		int s7 = 32767;
		int t9 = -32767;
		int t8 = 32767;
		int s2 = -32767;
		int t4 = 8;

		int* t5 = &fp[0];

		//loc_80ED4
		do
		{
			VX0 = t5[0] & 0xFFFF;
			VY0 = (t5[0] >> 16) & 0xFFFF;
			VZ0 = t5[1];

			t4--;

			docop2(0x480012);
			int v1 = MAC1;
			int v0 = MAC2;
			int a2 = MAC3;

			if (v1 < s5)
			{
				s5 = v1;
			}

			if (s4 < v1)
			{
				s4 = v1;
			}

			if (v0 < s7)
			{
				s7 = v0;
			}

			if (t9 < v0)
			{
				t9 = v0;
			}

			if (a2 < t8)
			{
				t8 = a2;
			}

			if (s2 < a2)
			{
				s2 = a2;
			}

			t5 += 2;

		} while (t4 != 0);

		mmPopMatrix_AI(fp);

		int v0 = item->pos.x_pos;
		int v1 = item->pos.y_pos;
		int a0 = item->pos.z_pos;

		s5 += v0;
		s4 += v0;
		s7 += v1;
		t9 += v1;
		t8 += a0;
		s2 += a0;

		int t6 = s1[5] + 1024;
		int t55 = s1[7] + 1024;

		a0 = t6 + ((((short*)s1)[21] - 2) << 10);
		int a1 = t55 + ((((short*)s1)[20] - 2) << 10);

		int t7 = s1[9];
		v1 = s1[8];

		if (s5 < t6 || a0 < s4 || s7 < t7 || v1 < t9 || t8 < t55 || a1 < s2)
		{
			//loc_80FE4
			t3 = s1[1];
			if (((short*)fp)[53] == item->room_number)
			{
				return;
			}

			if (((short*)fp)[53] == ((short*)fp)[52])
			{
				return;
			}

			t4 = ((short*)t3)[0];
			t3 += 2;

			if (t4 > 0)
			{
				//loc_8100C
				do
				{
					int at = ((short*)t3)[0];
					v1 = ((short*)fp)[53];
					a1 = ((short*)t3)[4];

					if (at == v1)
					{
						int a2 = ((short*)t3)[5];
						int a3 = ((short*)t3)[6];
						v0 = ((short*)t3)[7];
						v1 = ((short*)t3)[8];
						a0 = ((short*)t3)[9];

						t2 = a1;
						t0 = a2;

						if (v0 < a1)
						{
							t1 = a3;
							t2 = v0;
						}
						else if (a1 < v0)
						{
							a1 = v0;
						}

						//loc_8105C
						if (v1 < t0)
						{
							t0 = v1;
						}
						else if (a2 < v1)
						{
							t0 = v1;
						}

						//loc_8107C
						if (a0 < t1)
						{
							t1 = a0;
						}
						else if (a3 < a0)
						{
							a3 = a0;
						}

						//loc_8109C
						v0 = ((short*)t3)[10];
						v1 = ((short*)t3)[11];
						a0 = ((short*)t3)[12];

						if (v0 < t2)
						{
							t2 = v0;
						}
						else if (a1 < v0)
						{
							a1 = v0;
						}

						if (v1 < t0)
						{
							t0 = v1;
						}
						else if (a2 < v1)
						{
							a2 = v1;
						}

						if (a0 < t1)
						{
							t1 = a0;
						}
						else if (a3 < a0)
						{
							a3 = a0;
						}

						//loc_81108
						v0 = ((short*)t3)[13];
						v1 = ((short*)t3)[14];
						a0 = ((short*)t3)[15];

						if (v0 < t2)
						{
							t2 = v0;
						}
						else if (a1 < v0)
						{
							a1 = v0;
						}

						if (v1 < t0)
						{
							t0 = v1;
						}
						else if (a2 < v1)
						{
							a2 = v1;
						}

						if (a0 < t1)
						{
							t1 = a0;
						}
						else if (a3 < a0)
						{
							a3 = a0;
						}

						//loc_81174
						at = t2 - 1024;
						t2 = at + t6;
						at = a1 - 1024;
						a1 = at + t6;
						t0 += t7;
						at = t1 - 1024;
						t1 = at + t55;
						at = a3 - 1024;
						a3 = at + t55;
						a2 += t7;

						if (s4 >= t2 && a1 >= t55 && t9 >= t0 && a2 >= s7 && s2 >= t1 && a3 >= t8)
						{
							//loc_811DC
							break;
						}

					}//loc_811D0
					t3 += 0x20;
				}while (--t4 > 0);
			}//loc_811DC

			if (t4 != 0)
			{
				return;
			}
		}//loc_811E4
	}//loc_811E4

	fp[36] = s1[14];
	fp[37] = s1[15];
}

int mClipBoundingBox_AI(unsigned short* a0, int* fp)//811FC
{
	int t0 = TRZ - 20480;
	int v0 = 0;

	if (t0 < 0)
	{
		t0 = a0[0];
		int t3 = a0[1];
		int t1 = a0[2] << 16;
		int t4 = a0[3] << 16;
		int t2 = a0[4];
		int t7 = a0[5];
		int at = t0 | t1;

		VX0 = at & 0xFFFF;
		VY0 = (at >> 16) & 0xFFFF;
		VZ0 = t2;

		at = t3 | t1;
		VX1 = at & 0xFFFF;
		VY1 = (at >> 16) & 0xFFFF;
		VZ1 = t2;

		at = t0 | t4;
		VX2 = at & 0xFFFF;
		VY2 = (at >> 16) & 0xFFFF;
		VZ2 = t2;

		docop2(0x280030);

		int t9 = t3 | t4;
		int t8 = t2;
		int a0 = 0x7FFFFFFF;
		int a1 = 0x8100;
		int a2 = 0x7FFFFFFF;
		int a3 = 0x8100;

		t0 = SXY0;
		t1 = SXY1;
		t2 = SXY2;
		t3 = SZ1;
		t4 = SZ2;
		int t5 = SZ3;

		VZ0 = t7;
		VZ1 = t7;
		VZ2 = t7;

		docop2(0x280030);

		t3 -= 33;
		t4 -= 33;
		t5 -= 33;

		v0 = 0;
		GetBounds_AI(&t0, &a2, &a3, &t1, &t2, &v0, &a0, &a1, &t3, &t4, &t5);

		t0 = SXY0;
		t1 = SXY1;
		t2 = SXY2;
		t3 = SZ1 - 33;
		t4 = SZ2 - 33;
		t5 = SZ3 - 33;

		VX0 = t9 & 0xFFFF;
		VY0 = (t9 >> 16) & 0xFFFF;
		VZ0 = t8;

		VX1 = t9 & 0xFFFF;
		VY1 = (t9 >> 16) & 0xFFFF;

		docop2(0x280030);

		GetBounds_AI(&t0, &a2, &a3, &t1, &t2, &v0, &a0, &a1, &t3, &t4, &t5);

		t0 = SXY0;
		t1 = SXY1;
		t3 = SZ1 - 33;
		t4 = SZ2 - 33;
		t2 = t1;
		t5 = t4;
		GetBounds_AI(&t0, &a2, &a3, &t1, &t2, &v0, &a0, &a1, &t3, &t4, &t5);

		t0 = ((short*)fp)[73];
		t1 = ((short*)fp)[75];
		t2 = ((short*)fp)[72];
		t3 = ((short*)fp)[74];

		a0 >>= 16;
		a1 >>= 16;
		a2 >>= 16;
		a3 >>= 16;

		int v1 = v0;

		if (v1 == 0 || t0 < a0 || t1 < a2 || a1 < t2 || a3 < t3)
			return 0;

		if (v1 < 9 || a0 < t2 || a2 < t3 || t0 < a1 || t1 < a3)
			return -1;

		v0 = 1;
	}
	//locret_81394
	return v0;
}

void CalcAnimatingItem_ASM(struct ITEM_INFO* item /*s3*/, struct object_info* object /*s6*/, int* fp)//81504
{
	int frames;//$s0

	//v0 = 0x1FF0000
	//v1 = 0xEF0000
	fp[36] = 0x1FF0000;
	fp[37] = 0xEF0000;

	frames = GetFrames_AI(item, fp);
	mmPushMatrix(fp);
	mTranslateAbsXYZ_AI(item->pos.x_pos, item->pos.y_pos, item->pos.z_pos, fp);
	mRotYXZ_AI(item->pos.y_rot, item->pos.x_rot, item->pos.z_rot, fp);

	//a0 = object->object_mip
	//v0 = object[1].loaded
	if (object->object_mip != 0 && object[1].loaded && object->object_mip < TRZ && fp[46] == 0)
	{
		object++;
	}

	//loc_81584
	calc_animating_item_clip_window(item, (unsigned short*)fp[30], fp);

#if 0
jal     sub_811FC
lw      $a0, arg_78($fp)
beqz    $v0, loc_81738
li      $at, 0
sw      $at, arg_4C($fp)
lw      $a2, arg_40($fp)
lw      $v1, arg_78($fp)
sh      $v0, 0($a2)
sw      $s3, 4($a2)
sw      $v1, 8($a2)
lw      $s2, 0x3C($s3)
li      $s1, 1
lh      $v0, 2($s6)
lw      $s7, arg_A0($fp)
sll     $v0, 2
addu    $s7, $v0
lw      $v0, 4($s6)
lw      $s5, arg_A4($fp)
sll     $v0, 2
bnez    $s0, loc_81C60
addu    $s5, $v0
lw      $v0, arg_78($fp)
nop
lh      $a0, 0xC($v0)
lh      $a1, 0xE($v0)
jal     sub_81AB0
lh      $a2, 0x10($v0)
lw      $v0, arg_78($fp)
lw      $gp, 0x88($s3)
lw      $s3, 8($s3)
addiu   $v0, 0x12
jal     sub_819FC
sw      $v0, arg_80($fp)
and     $v0, $s3, $s1
beqz    $v0, loc_81630
and     $v0, $gp, $s1
beqz    $v0, loc_81628
lw      $a0, 0($s7)
lw      $a0, 4($s7)

loc_81628:
jal     sub_81750
nop

loc_81630:
lh      $s4, 0($s6)
nop
addiu   $s4, -1
blez    $s4, loc_81714
addiu   $s7, 8

loc_81644:
lw      $s0, 0($s5)
nop
andi    $v0, $s0, 1
beqz    $v0, loc_81660
nop
jal     sub_81C0C
nop

loc_81660:
andi    $v0, $s0, 2
beqz    $v0, loc_81674
nop
jal     sub_81BBC
nop

loc_81674:
lw      $a0, 4($s5)
lw      $a1, 8($s5)
jal     sub_81AB0
lw      $a2, 0xC($s5)
jal     sub_819FC
nop
beqz    $s2, loc_816E0
andi    $v0, $s0, 0x1C
beqz    $v0, loc_816E0
andi    $v0, $s0, 8
beqz    $v0, loc_816B4
andi    $v0, $s0, 4
lh      $a0, 0($s2)
jal     sub_81858
addiu   $s2, 2
andi    $v0, $s0, 4

loc_816B4:
beqz    $v0, loc_816CC
andi    $v0, $s0, 0x10
lh      $a0, 0($s2)
jal     sub_817B0
addiu   $s2, 2
andi    $v0, $s0, 0x10

loc_816CC:
beqz    $v0, loc_816E0
nop
lh      $a0, 0($s2)
jal     sub_81918
addiu   $s2, 2

loc_816E0:
sll     $s1, 1
and     $v0, $s1, $s3
beqz    $v0, loc_81704
and     $v0, $gp, $s1
beqz    $v0, loc_816FC
lw      $a0, 0($s7)
lw      $a0, 4($s7)

loc_816FC:
jal     sub_81750
nop

loc_81704:
addiu   $s4, -1
addiu   $s7, 8
bnez    $s4, loc_81644
addiu   $s5, 0x10

loc_81714:
lw      $at, arg_4C($fp)
lw      $v0, arg_48($fp)
blez    $at, loc_81738
addiu   $v0, 1
lw      $v1, arg_40($fp)
sw      $v0, arg_48($fp)
sh      $at, 2($v1)
addiu   $v1, 0xC
sw      $v1, arg_40($fp)

loc_81738:
jal     sub_81C0C
lw      $s2, arg_B0($fp)
lw      $ra, arg_B4($fp)
lw      $s1, arg_AC($fp)
jr      $ra
lw      $s0, arg_A8($fp)
#endif
}

void mmPopMatrix_AI(int* fp)//81C0C(<)
{
	mLoadMatrix2((int*)(fp[20]-0x20), fp);
}

void mmPushMatrix_AI(int* fp)
{
	int* a0 = (int*)fp[20];
	a0 += 8;
	a0[0] = (R11 & 0xFFFF) | (R12 & 0xFFFF) << 16;
	a0[1] = (R13 & 0xFFFF) | (R21 & 0xFFFF) << 16;
	a0[2] = (R22 & 0xFFFF) | (R23 & 0xFFFF) << 16;
	a0[3] = (R31 & 0xFFFF) | (R32 & 0xFFFF) << 16;
	a0[4] = R33;
	a0[5] = TRX;
	a0[6] = TRY;
	a0[7] = TRZ;

	fp[20] = (int)a0;
}

void mLoadMatrix2(int* a0, int* fp)//81C18(<)
{
	R11 = (a0[0] & 0xFFFF);
	R12 = (a0[0] >> 16) & 0xFFFF;
	R13 = (a0[1] & 0xFFFF);
	R21 = (a0[1] >> 16) & 0xFFFF;
	R22 = (a0[2] & 0xFFFF);
	R23 = (a0[2] >> 16) & 0xFFFF;
	R31 = (a0[3] & 0xFFFF);
	R32 = (a0[3] >> 16) & 0xFFFF;
	R33 = (a0[4] & 0xFFFF);
	TRX = a0[5];
	TRY = a0[6];
	TRZ = a0[7];

	fp[20] = (int)a0;
}

void stash_the_info(int meshp/*a0*/, int* fp)//81750
{
	int* at;

	at = (int*)fp[17];

	((int*)at)[0] = meshp;

	at[1] = (R11 & 0xFFFF) | (R12 & 0xFFFF) << 16;
	at[2] = (R13 & 0xFFFF) | (R21 & 0xFFFF) << 16;
	at[3] = (R22 & 0xFFFF) | (R23 & 0xFFFF) << 16;
	at[4] = (R31 & 0xFFFF) | (R32 & 0xFFFF) << 16;

	at[5] = (R33 & 0xFFFF);
	at[6] = TRX;
	at[7] = TRY;
	at[8] = TRZ;

	at += 9;

	fp[19]++;
	fp[17] = (int)at;
}

void GetBounds_AI(int* t0, int* a2, int* a3, int* t1, int* t2, int* v0, int* a0, int* a1, int* t3, int* t4, int* t5)//8139C
{
	if (*t0 < *a2)
	{
		*a2 = *t0;
	}

	//loc_813AC
	if (*t0 >= *a3)
	{
		*a3 = *t0;
	}

	//loc_813B8
	if (*t1 < *a2)
	{
		*a2 = *t1;
	}

	//loc_813C4
	if (*t1 >= *a3)
	{
		*a3 = *t1;
	}

	if (*t2 < *a2)
	{
		*a3 = *t2;
	}

	//loc_813DC
	*t0 <<= 16;
	if (*t2 >= *a3)
	{
		*a3 = *t2;
	}

	//loc_813E8
	*t1 <<= 16;
	*t2 <<= 16;

	if (*t0 < *a0)
	{
		*a0 = *t0;
	}

	if (*t0 >= *a1)
	{
		*a1 = *t0;
	}

	if (*t1 < *a0)
	{
		*a0 = *t1;
	}

	if (*t1 >= *a1)
	{
		*a1 = *t1;
	}

	if (*t2 < *a0)
	{
		*a0 = *t2;
	}

	if (*t2 >= *a1)
	{
		*a1 = *t2;
	}

	if (*t3 < 0x5000)
	{
		v0[0]++;
	}

	if (*t4 < 0x5000)
	{
		v0[0]++;
	}

	if (*t5 < 0x5000)
	{
		v0[0]++;
	}
}

int mClipBoundingBox2(unsigned short* bounds, int* sp /*fp*/)//811FC
{
	int t0 = TRZ - 20480;
	int t3;
	int t1;
	int t4;
	int t2;
	int t7;
	int v0 = 0;
	int at;
	int t9;
	int t8;
	int a0;
	int a1;
	int a2;
	int t5;
	int a3;

	if (t0 < 0)
	{
		t0 = bounds[0];
		t3 = bounds[1];
		t1 = bounds[2];
		t4 = bounds[3];
		t2 = bounds[4];
		t7 = bounds[5];

		t1 <<= 16;
		t4 <<= 16;

		at = t0 | t1;
		VX0 = (at & 0xFFFF);
		VY0 = (at >> 16) & 0xFFFF;
		VZ0 = t2;

		at = t3 | t1;
		VX1 = (at & 0xFFFF);
		VY1 = (at >> 16) & 0xFFFF;
		VZ1 = t2;

		at = t0 | t4;
		VX2 = (at & 0xFFFF);
		VY2 = (at >> 16) & 0xFFFF;
		VZ2 = t2;

		docop2(0x280030);

		t9 = t3 | t4;
		t8 = t2;

		a0 = 0x7FFFFFFF;
		a1 = 0x81000000;
		a2 = a0;
		t0 = SXY0;
		t1 = SXY1;
		t2 = SXY2;
		t3 = SZ1;
		t4 = SZ2;
		t5 = SZ3;

		VZ0 = t7;
		VZ1 = t7;
		VZ2 = t7;

		a3 = a1;

		docop2(0x280030);

		t3 -= 33;
		t4 -= 33;
		t5 -= 33;

		v0 = 0;
		GetBounds_AI(&t0, &a2, &a3, &t1, &t2, &v0, &a0, &a1, &t3, &t4, &t5);

		t0 = SXY0;
		t1 = SXY1;
		t2 = SXY2;
		t3 = SZ1;
		t4 = SZ2;
		t5 = SZ3;

		VX0 = (t9 & 0xFFFF);
		VY0 = (t9 >> 16) & 0xFFFF;
		VZ0 = t8;

		VX1 = (t9 & 0xFFFF);
		VY1 = (t9 >> 16) & 0xFFFF;

		t2 -= 0x21;
		docop2(0x280030);
		t4 -= 0x21;
		t5 -= 0x21;

		GetBounds_AI(&t0, &a2, &a3, &t1, &t2, &v0, &a0, &a1, &t3, &t4, &t5);
	
		t0 = SXY0;
		t1 = SXY1;
		t3 = SZ1;
		t4 = SZ2;

		t3 -= 0x21;
		t4 -= 0x21;
		t2 = t1;
		t5 = t4;

		GetBounds_AI(&t0, &a2, &a3, &t1, &t2, &v0, &a0, &a1, &t3, &t4, &t5);
		t0 = ((short*)sp)[73];
		t1 = ((short*)sp)[75];
		t2 = ((short*)sp)[72];
		t3 = ((short*)sp)[74];

		a0 >>= 16;
		a1 >>= 16;
		a2 >>= 16;
		a3 >>= 16;

		if (v0 == 0 || t0 < a0 || t1 < a2 || a1 < t2 || a3 < t3)
		{
			return 0;
		}

		if (v0 < 9 || a0 < t2 || a2 < t3 || t0 < a1 || t1 < a3)
		{
			return -1;
		}

		return 1;
	}

	return v0;
}

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

	t0 = (R11 & 0xFFFF) | ((R12 & 0xFFFF) << 16);
	t1 = (R13 & 0xFFFF) | ((R21 & 0xFFFF) << 16);
	t2 = (R22 & 0xFFFF) | ((R23 & 0xFFFF) << 16);
	t3 = (R31 & 0xFFFF) | ((R32 & 0xFFFF) << 16);
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

	fp[16] = (int)&stashed_objects_list[0];
	fp[17] = (int)&stashed_matrix_list[0];
	fp[18] = 0;
	fp[24] = (int)&items[0];
	fp[38] = (int)&room[0];

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
	int v1;
	struct room_info* r;//$s2
	struct static_info* s5;
	int at;
	int* a2;
	int v0;
	int i;//$s1
	int j;//$s3
	struct ITEM_INFO* item;//$s3
	struct object_info* object;//$s6
	int item_number;//$s2

	S_MemSet((char*)&scratchPad[0], 0, 1024);

	fp = &scratchPad[0];
	init_scratchpad(fp);

	if (number_draw_rooms > 0)
	{
		//loc_82658
		for (i = 0; i < number_draw_rooms; i++)
		{
			r = &room[draw_rooms[i]];
			((short*)fp)[52] = draw_rooms[i];
			((int*)fp)[25] = (int)r;
			mmPushMatrix_AI(fp);

			if (r->num_meshes > 0)
			{
				fp[36] = ((int*)&r->left)[0];
				fp[37] = ((int*)&r->top)[0];

				//loc_82698
				for (j = 0; j < r->num_meshes; j++)
				{
					s5 = &static_objects[r->mesh[j].static_number];

					if ((r->mesh[j].Flags & 1))
					{
						mmPushMatrix_AI(fp);
						mTranslateAbsXYZ_AI(r->mesh[j].x, r->mesh[j].y, r->mesh[j].z, fp);
						mRotY_AI(r->mesh[j].y_rot, fp);
						v1 = ((s5->flags) >> 2) << 10;
						at = TRZ;

						if (v1 && v1 < TRZ)
						{
							s5++;
						}//loc_82704

						v0 = mClipBoundingBox2((unsigned short*)&s5->x_minp, fp);

						if (v0)
						{
							a2 = (int*)fp[16];
							fp[18]++;
							((short*)a2)[0] = v0;
							((int*)a2)[1] = (int)&r->mesh[j];
							((short*)a2)[1] = 0;
							a2 += 3;
							fp[16] = (int)a2;
							v1 = s5->mesh_number;
							v0 = fp[40];

							stash_the_info(((int*)v0)[s5->mesh_number], fp);//((int*)meshes[s5->mesh_number])[0]
						}
						//loc_8274C
						mmPopMatrix2(fp);
					}//loc_82750
				}//loc_82750
			}
			//loc_8275C
			//s2 = r->item_number

			//v0 = r->item_number << 7
			if (r->item_number != -1)
			{
				item_number = r->item_number;

				//loc_8276C
				do
				{
					item = &((struct ITEM_INFO*)fp[24])[item_number];//&items[r->item_number]
					//v1 = r->item_number << 4	
					//v1 = item->object_number
					//s6 = objects
					object = &objects[item->object_number];

					//v0 = object->using_drawanimating_item
					//a1 = item->status

					if (object->using_drawanimating_item && item->status != 3)
					{
						//s2 = item
						CalcAnimatingItem_ASM(item, object, fp);
						//item = s2 //Maybe restore backup check if modified in func above
					}
					//loc_827BC
					item_number = item->next_item;
				} while (item->next_item != -1);

			}//loc_827CC
			mmPopMatrix2(fp);
		}
	}//loc_827DC
#if !JULY_VERSION
	DrawAllAnimatingItems_ASM(fp[18]);
#endif
}


void DrawAllAnimatingItems_ASM(int s4)//82900(<)
{
	struct ITEM_INFO* item;//$a3
	STASHEDOBJ* sobject;//$s0
	STASHEDDAT* sdat;//$s2
	int i;//$s4
	int j;//$s1
	int s6;

	if (s4 > 0)
	{
		sobject = &stashed_objects_list[0];
		mPushMatrix();
		sdat = &stashed_matrix_list[0];

		//loc_8291C
		for(i = 0; i < s4; i++, sobject++)
		{
			s6 = 0x80;
			item = stashed_objects_list[i].item;

			if (sobject->numnodestodraw == 0)
			{	
				j = 1;
				S_CalculateStaticMeshLight(item->floor, item->touch_bits, item->mesh_bits, item->current_anim_state);
			}
			else
			{
				//loc_82950
				j = sobject->numnodestodraw;
				s6 =  0x80 - item->after_death;
				CalculateObjectLighting(item, sobject->frmptr0, sobject, sobject->numnodestodraw);
			}

			//loc_82964
			do
			{
				R11 = ((int*)&sdat->matrix[0])[0] & 0xFFFF;
				R12 = (((int*)&sdat->matrix[0])[0] >> 16) & 0xFFFF;
				R13 = ((int*)&sdat->matrix[0])[1] & 0xFFFF;
				R21 = (((int*)&sdat->matrix[0])[1] >> 16) & 0xFFFF;
				R22 = ((int*)&sdat->matrix[0])[2] & 0xFFFF;
				R23 = (((int*)&sdat->matrix[0])[2] >> 16) & 0xFFFF;
				R31 = ((int*)&sdat->matrix[0])[3] & 0xFFFF;
				R32 = (((int*)&sdat->matrix[0])[3] >> 16) & 0xFFFF;
				R33 = ((int*)&sdat->matrix[0])[4] & 0xFFFF;
				TRX = ((int*)&sdat->matrix[0])[5];
				TRY = ((int*)&sdat->matrix[0])[6];
				TRZ = ((int*)&sdat->matrix[0])[7];

				if (s6 != 0x80)
				{
					//loc_829C4
					if (s6 >= 5)
					{
						phd_PutPolygons_seethrough(sdat->mesh, s6);
					}
				}//loc_829C4
				else
				{
					phd_PutPolygons(sdat->mesh, sobject->clip);
				}
				sdat++;
			} while (--j > 0);
		} 
		//loc_829E8
		mPopMatrix();
	}
	//loc_829E8
	phd_left = 0;
	phd_right = 0x1FF;
	phd_top = 0;
	phd_bottom = 0xEF;
}