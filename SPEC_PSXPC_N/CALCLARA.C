#include "CALCLARA.H"

#include "SPECIFIC.H"
#include "DRAW.H"
#include "LARA.H"
#include "GTEREG.H"
#include "DELSTUFF.H"
#include "LOAD_LEV.H"
#include "CAMERA.H"
#include "CONTROL.H"
#include "MATHS.H"
#include "MISC.H"
#include <assert.h>

void S_SetupClutAdder(long underwater)
{
	DQB = underwater;
}

void SetRotation_CL(int t0, int t1, int t2, int t3, int t4)
{
	R11 = t0 & 0xFFFF;
	R12 = (t0 >> 16) & 0xFFFF;
	R13 = t1 & 0xFFFF;
	R21 = (t1 >> 16) & 0xFFFF;
	R22 = t2 & 0xFFFF;
	R23 = (t2 >> 16) & 0xFFFF;
	R31 = t3 & 0xFFFF;
	R32 = (t3 >> 16) & 0xFFFF;
	R33 = t4 & 0xFFFF;
}

void setup_rotation_matrix(int* mat)
{
	SetRotation_CL(mat[0], mat[1], mat[2], mat[3], mat[4]);
}

void copy_matrix_from_scratch(int* a0, int* a1)
{
	int t0 = a0[0];
	int t1 = a0[1];
	int t2 = a0[2];
	int t3 = a0[3];
	a1[0] = t0;
	a1[1] = t1;
	a1[2] = t2;
	a1[3] = t3;
	int t4 = a0[4];
	int t5 = a0[5];
	int t6 = a0[6];
	int t7 = a0[7];
	a1[4] = t4;
	a1[5] = t5;
	a1[6] = t6;
	a1[7] = t7;
}

void mLoadMatrix_CL(int* mat)
{
	TRX = mat[5];
	TRY = mat[6];
	TRZ = mat[7];

	SetRotation_CL(mat[0], mat[1], mat[2], mat[3], mat[4]);
}

void mRotY_CL(long y)
{
	y >>= 2;
	y &= 0x3FFC;
	
	if (y != 0)
	{

		//loc_84DA4
		int t5 = ((int*)&rcossin_tbl[y >> 1])[0];
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

		SetRotation_CL(t0, t1, t2, t3, t4);
	}
}

void SetRotation_CL_I(int t0, int t1, int t2, int t3, int t4)
{
	L11 = (t0 & 0xFFFF);
	L12 = (t0 >> 16) & 0xFFFF;
	L13 = (t1 & 0xFFFF);
	L21 = (t1 >> 16) & 0xFFFF;
	L22 = (t2 & 0xFFFF);
	L23 = (t2 >> 16) & 0xFFFF;
	L31 = (t3 & 0xFFFF);
	L32 = (t3 >> 16) & 0xFFFF;
	L33 = (t4 & 0xFFFF);
}

void iRotY_CL(long y)
{
	y >>= 2;
	y &= 0x3FFC;

	if (y != 0)
	{
		int t5 = ((int*)&rcossin_tbl[y >> 1])[0];
		int t7 = 0xFFFF0000;
		int t6 = t5 >> 16;
		t5 &= 0xFFFF;
		int t2 = -t5;

		VX0 = (t6 & 0xFFFF);
		VY0 = (t6 >> 16) & 0xFFFF;
		VZ0 = (t2 & 0xFFFF);

		int t0 = (L11 & 0xFFFF) | ((L12 & 0xFFFF) << 16);
		t2 = (L22 & 0xFFFF) | ((L23 & 0xFFFF) << 16);
		int t3 = (L31 & 0xFFFF) | ((L32 & 0xFFFF) << 16);

		docop2(0x4A6012);

		VX1 = (t5 & 0xFFFF);
		VY1 = ((t5 >> 16) & 0xFFFF);
		VZ1 = (t6 & 0xFFFF);

		t0 &= t7;
		t2 &= 0xFFFF;
		t3 &= t7;

		int t4 = MAC1;
		int t1 = MAC2;
		t5 = MAC3;

		docop2(0x4AE012);

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
		
		SetRotation_CL_I(t0, t1, t2, t3, t4);
	}
}

void iRotX_CL(long x)
{
	x >>= 2;
	x &= 0x3FFC;

	if (x != 0)
	{
		int t5 = ((int*)&rcossin_tbl[x >> 1])[0];
		int t7 = 0xFFFF0000;
		int t6 = t7 & t5;

		VX0 = (t6 & 0xFFFF);
		VY0 = ((t6 >> 16) & 0xFFFF);
		VZ0 = (t5 & 0xFFFF);

		int t0 = (L11 & 0xFFFF) | ((L12 & 0xFFFF) << 16);
		int t1 = (L13 & 0xFFFF) | ((L21 & 0xFFFF) << 16);
		int t3 = (L31 & 0xFFFF) | ((L32 & 0xFFFF) << 16);

		docop2(0x4A6012);

		t6 = t5 >> 16;
		t5 <<= 16;
		t5 = -t5;

		VX1 = (t5 & 0xFFFF);
		VY1 = (t5 >> 16) & 0xFFFF;
		VZ1 = t6 & 0xFFFF;

		t0 &= 0xFFFF;
		t1 &= t7;
		t3 &= 0xFFFF;

		int t4 = MAC1;
		int t2 = MAC2;
		t5 = MAC3;

		docop2(0x4AE012);

		t4 <<= 16;
		t0 |= t4;
		t2 &= 0xFFFF;
		t5 <= 16;
		t3 |= t5;

		t5 = MAC1;
		t6 = MAC2;
		t4 = MAC3;

		t5 &= 0xFFFF;
		t1 |= t5;
		t6 <<= 16;
		t2 |= t6;

		SetRotation_CL_I(t0, t1, t2, t3, t4);
	}
}

void iRotZ_CL(long z)
{
	z >>= 2;
	z &= 0x3FFC;

	if (z != 0)
	{
		int t0 = ((int*)&rcossin_tbl[z >> 1])[0];
		int t7 = 0xFFFF0000;
		int t1 = t0 >> 16;
		int t2 = t0 << 16;
		t1 |= t2;

		VX0 = (t1 & 0xFFFF);
		VY0 = (t1 >> 16) & 0xFFFF;
		VZ0 = 0;

		t1 = (L13 & 0xFFFF) | ((L21 & 0xFFFF) << 16);
		t2 = (L22 & 0xFFFF) | ((L23 & 0xFFFF) << 16);
		int t4 = (L33 & 0xFFFF);
		docop2(0x4A6012);
		int t3 = t0 & t7;
		t0 &= 0xFFFF;
		t0 = -t0;
		t0 &= 0xFFFF;
		t0 |= t3;
		VX1 = (t0 & 0xFFFF);
		VY1 = (t0 >> 16) & 0xFFFF;
		VZ1 = 0;
		t1 &= 0xFFFF;
		t0 = MAC1;
		int t5 = MAC2;
		t3 = MAC3;///@FIXME bad value?!!??!

		docop2(0x4AE012);
		t2 &= t7;
		t0 &= 0xFFFF;
		t5 <<= 16;
		t1 |= t5;
		t3 &= 0xFFFF;
		t5 = MAC1;
		int t6 = MAC2;
		t7 = MAC3;
		t5 <<= 16;
		t0 |= t5;
		t6 &= 0xFFFF;
		t2 |= t6;
		t7 <<= 16;
		t3 |= t7;

		//loc_85204
		SetRotation_CL_I(t0, t1, t2, t3, t4);
	}
}

void mRotX_CL(long x)
{
	x >>= 2;
	x &= 0x3FFC;

	if (x != 0)
	{
		//loc_84D04
		int t5 = ((int*)&rcossin_tbl[x >> 1])[0];
		int t7 = 0xFFFF0000;
		int t6 = t7 & t5;

		VX0 = t6 & 0xFFFF;
		VY0 = (t6 >> 16) & 0xFFFF;
		VZ0 = (t5 & 0xFFFF);

		int t0 = (R11 & 0xFFFF) | ((R12 & 0xFFFF) << 16);
		int t1 = (R13 & 0xFFFF) | ((R21 & 0xFFFF) << 16);
		int t3 = (R31 & 0xFFFF) | ((R32 & 0xFFFF) << 16);

		docop2(0x486012);

		t6 = t5 >> 16;
		t5 <<= 16;
		t5 = -t5;

		VX1 = (t5 & 0xFFFF);
		VY1 = (t5 >> 16) & 0xFFFF;
		VZ1 = (t6 & 0xFFFF);

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

		SetRotation_CL(t0, t1, t2, t3, t4);
	}
}

void mRotZ_CL(long z)
{
	z >>= 2;
	z &= 0x3FFC;

	if (z != 0)
	{
		int t0 = ((int*)&rcossin_tbl[z >> 1])[0];
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

		SetRotation_CL(t0, t1, t2, t3, t4);
	}//loc_84E5C
}

void mRotYXZ_CL(long y, long x, long z)
{
	mRotY_CL(y);
	mRotX_CL(x);
	mRotZ_CL(z);
}

void iRotSuperPackedYXZ_CL(int* t8, int a1)
{
	unsigned short* a2 = (unsigned short*)t8[10];
	int v0 = a2[0];

	if (a1 != 0)
	{
		do
		{
			//loc_85228
			v0 = a2[0];
			a1--;
			if (!(v0 & 0xC000))
			{
				a2++;
			}

			a2++;
			//loc_85240
		} while (a1 != 0);

		v0 = a2[0];
	}
	//loc_8524C
	a2++;
	
	int at = v0 >> 14;
	if (at-- != 0)
	{
		t8[10] = (int)a2;

		if (at-- != 0)
		{
			int a0 = v0 & 0xFFF;
			if (at != 0)
			{
				iRotZ_CL(a0 << 4);
				return;
			}
			//loc_85278
			iRotY_CL(a0 << 4);
			return;
		}//loc_85280
		int a0 = v0 & 0xFFF;
		iRotX_CL(a0 << 4);
		return;
	}//loc_8528C

	at = *a2++;
	t8[10] = (int)a2;
	int a22 = v0 << 16;
	a22 |= at;

	iRotY_CL((a22 >> 4) & 0xFFC0);
	iRotX_CL((a22 >> 14) & 0xFFC0);
	iRotZ_CL((a22 << 6) & 0xFFC0);
}

void iRotYXZ_CL(int y, int x, int z)
{
	iRotY_CL(y);
	iRotX_CL(x);
	iRotZ_CL(z);
}

void mRotSuperPackedYXZ_CL(int* t8, int a1)
{
	unsigned short* a2 = (unsigned short*)t8[9];
	int v0 = a2[0];

	if (a1 != 0)
	{
		//loc_84C48
		do
		{
			v0 = a2[0];
			a1--;
			a2++;
			if (!(v0 & 0xC000))
			{
				a2++;
			}
			//loc_84C60
		} while (a1 != 0);

		v0 = a2[0];
	}
	//loc_84C6C
	a2++;
	int at = v0 >> 14;

	if (at-- != 0)
	{
		t8[9] = (int)a2;

		if (at-- != 0)
		{
			if (at != 0)
			{
				mRotZ_CL((v0 & 0xFFF) << 4);
				return;
			}
			//loc_84C98
			mRotY_CL((v0 & 0xFFF) << 4);
			return;
		}
		//loc_84CA0
		mRotX_CL((v0 & 0xFFF) << 4);
		return;

	}//loc_84CAC

	at = a2[0];
	a2++;
	t8[9] = (int)a2;
	v0 <<= 16;
	v0 |= at;

	mRotY_CL((v0 >> 4) & 0xFFC0);
	mRotX_CL((v0 >> 14) & 0xFFC0);
	mRotZ_CL((v0 & 0x3FF) << 6);
}

void iTranslateXYZ2_CL(long x /*a3*/, long y /*a1*/, long z /*a2*/)
{
	int t0 = x >> 15;
	if (x < 0)
	{
		x = -x;
		t0 = x >> 15;
		x &= 0x7FFF;
		t0 = -t0;
		x = -x;
	}
	else
	{
		//loc_85318
		x &= 0x7FFF;
	}

	int t1 = y >> 15;
	if (y < 0)
	{
		y = -y;
		t1 = y >> 15;
		y & -0x7FFF;
		t1 = -t1;
		y = -y;
	}
	else
	{
		//loc_8533C
		y &= 0x7FFF;
	}

	//loc_85340
	int t2 = z >> 15;
	if (t2 < 0)
	{
		z = -z;
		t2 = z >> 15;
		z &= 0x7FFF;
		t2 = -t2;
		z = -z;
	}
	else
	{
		//loc_85360
		z &= 0x7FFF;
	}

	IR1 = t0;
	IR2 = t1;
	IR3 = t2;

	docop2(0x43E012);

	int t6 = MAC1;

	IR1 = x;
	IR2 = y;
	IR3 = z;

	int t7 = MAC2;
	int v0 = MAC3;

	docop2(0x4BE012);

	int t3 = t6 << 3;
	if (t3 < 0)
	{
		t6 = -t6;
		t6 <<= 3;
		t3 = -t6;
	}

	//loc_853A8
	int t4 = t7 << 3;
	if (t7 < 0)
	{
		t7 = -t7;
		t7 <<= 3;
		t4 = -t7;
	}

	//loc_853BC
	int t5 = v0 << 3;
	if (v0 < 0)
	{
		v0 = -v0;
		v0 <<= 3;
		t5 = -v0;
	}

	//loc_853D0
	t6 = MAC1;
	t7 = MAC2;
	v0 = MAC3;

	t3 += t6;
	t4 += t7;
	t5 += v0;

	t0 = RBK;
	t1 = GBK;
	t2 = BBK;

	t0 += t3;
	t1 += t4;
	t2 += t5;

	RBK = t0;
	GBK = t1;
	BBK = t2;
}

void mTranslateXYZ_CL(long x, long y, long z)
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
		y &= 0x7FFF;
	}

	//loc_84B5C
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
		//loc_84B80
		z &= 0x7FFF;
	}

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
		//loc_84BA4
		x &= 0x7FFF;
	}

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

	//loc_84BEC
	int t1 = t4 << 3;
	if (t4 < 0)
	{
		t4 = -t4;
		t4 <<= 3;
		t1 = -t4;
	}

	//loc_84C00
	int t2 = t5 << 3;
	if (t5 < 0)
	{
		t5 = -t5;
		t5 <<= 3;
		t2 = -t5;
	}

	//loc_84C14
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

void mTranslateAbsXYZ_CL(long x, long y, long z)
{
	TRX = 0;
	TRY = 0;
	TRZ = 0;

	mTranslateXYZ_CL(x - ((int*)& MatrixStack[0])[5], y - ((int*)& MatrixStack[0])[6], z - ((int*)& MatrixStack[0])[7]);
}

void Hardcore_iTranslateXYZ_CL(long* a22, int* t8)
{
	int a0 = a22[0];
	int a1 = a22[1];
	int a2 = a22[2];
	int a3 = a0;

	t8[96] = a1;
	t8[97] = a2;

	mTranslateXYZ_CL(a0, a1, a2);

	///@TODO Not required but....
	a1 = t8[96];
	a2 = t8[97];
	iTranslateXYZ2_CL(a3, a1, a2);
}

void Hardcore_mTranslateXYZ_CL(long* a2)
{
	mTranslateXYZ_CL(a2[0], a2[1], a2[2]);
}

void DEL_CalcLaraMatrices_Normal_ASM(short* frame, long* bone, int flag)
{
	int sp[256];
	int* t8 = &sp[0];
	struct ITEM_INFO* item = lara_item;
	short* t9 = frame;
	long* s1 = bone;
	S_MemSet((char*)&sp[0], 0, 1024);
	frame += 9;
	GLaraShadowframe = t9;
	t8[9] = (int)frame;
	snaff_current_gte_matrix_V1(&t8[38]);
	struct MATRIX3D* a0 = NULL;

	if ((flag & 0x1))
	{
		TRX = 0;
		TRY = 0;
		TRZ = 0;
		t8[13] = (int)lara_joint_matrices;
	}
	else
	{
		//loc_83C40
		t8[13] = (int)lara_matrices;
		mTranslateAbsXYZ_CL(item->pos.x_pos, item->pos.y_pos, item->pos.z_pos);
		if ((flag & 0x2))
		{
			ScaleCurrentMatrix(0, -4096, -4096, -4096);
		}
	}
	//loc_83C74
	mRotYXZ_CL(item->pos.y_rot, item->pos.x_rot, item->pos.z_rot);
	snaff_current_gte_matrix_V1(&t8[14]);
	mTranslateXYZ_CL(t9[6], t9[7], t9[8]);
	mRotSuperPackedYXZ_CL(t8, 0);

	int* s0 = (int*)t8[13];
	snaff_current_gte_matrix_V1(&t8[22]);
	int a3 = 6;

	//loc_83CB4
	do
	{
		Hardcore_mTranslateXYZ_CL(&s1[1]);
		mRotSuperPackedYXZ_CL(t8, 0);
		snaff_current_gte_matrix_V1(&s0[8]);

		s1 += 4;
		if (--a3 == 3)
		{
			mLoadMatrix_CL(&t8[22]);
		}//loc_83CE4

		s0 += 8;

	} while (a3 != 0);

	mLoadMatrix_CL(&t8[22]);
	bone -= 24;
	s0 -= 48;

	Hardcore_mTranslateXYZ_CL(&s1[25]);

	if (lara.weapon_item != -1 && lara.gun_type == 5 &&
		(items[lara.weapon_item + 1].frame_number == 0 ||
			items[lara.weapon_item + 1].frame_number == 2 ||
			items[lara.weapon_item + 1].frame_number == 4))
	{
		t8[9] = (int)& lara.right_arm.frame_base[(lara.right_arm.frame_number * (anims[lara.right_arm.anim_number].interpolation >> 8)) + 9];
		mRotSuperPackedYXZ_CL(t8, 7);
	}
	else
	{
		//loc_83DA8
		mRotSuperPackedYXZ_CL(t8, 0);
	}

	mRotYXZ_CL(lara.torso_y_rot, lara.torso_x_rot, lara.torso_z_rot);
	snaff_current_gte_matrix_V1(&t8[30]);
	Hardcore_mTranslateXYZ_CL(&s1[53]);
	a3 = t8[9];
	mRotSuperPackedYXZ_CL(t8, 6);
	t8[9] = a3;
	mRotYXZ_CL(lara.head_y_rot, lara.head_x_rot, lara.head_z_rot);
	snaff_current_gte_matrix_V1(&s0[64]);
	mLoadMatrix_CL(&t8[30]);
	Hardcore_mTranslateXYZ_CL(&s1[29]);

	if (lara.gun_status == 2 || lara.gun_status == 3 ||
		lara.gun_status == 4 || lara.gun_status == 5)
	{
		switch (lara.gun_type)
		{
		case 0:
		case 7:
		case 8:
		{
		loc_83E60:
			mRotSuperPackedYXZ_CL(&t8[0], 0);
			snaff_current_gte_matrix_V1(&s0[72]);
			Hardcore_mTranslateXYZ_CL(&s1[33]);

			mRotSuperPackedYXZ_CL(&t8[0], 0);
			snaff_current_gte_matrix_V1(&s0[80]);
			Hardcore_mTranslateXYZ_CL(&s1[37]);

			mRotSuperPackedYXZ_CL(&t8[0], 0);
			snaff_current_gte_matrix_V1(&s0[88]);

			mLoadMatrix_CL(&t8[30]);
			Hardcore_mTranslateXYZ_CL(&s1[41]);

			if (lara.flare_control_left)
			{
				((unsigned int*)t8)[9] = (unsigned int)& lara.left_arm.frame_base[((lara.left_arm.frame_number - anims[lara.left_arm.anim_number].frame_base) * (anims[lara.left_arm.anim_number].interpolation >> 8)) + 9];
				mRotSuperPackedYXZ_CL(&t8[0], 11);
			}
			else
			{
				//loc_83F14
				mRotSuperPackedYXZ_CL(&t8[0], 0);
			}

			//loc_83F18
			snaff_current_gte_matrix_V1(&s0[96]);
			Hardcore_mTranslateXYZ_CL(&s1[45]);
			mRotSuperPackedYXZ_CL(&t8[0], 0);
			snaff_current_gte_matrix_V1(&s0[104]);
			Hardcore_mTranslateXYZ_CL(&s1[49]);
			mRotSuperPackedYXZ_CL(&t8[0], 0);
			snaff_current_gte_matrix_V1(&s0[112]);
			break;
		}
		case 1:
		case 3:
		{
			//loc_83F5C
			setup_rotation_matrix(&t8[14]);
			mRotYXZ_CL(lara.right_arm.y_rot, lara.right_arm.x_rot, lara.right_arm.z_rot);

			((unsigned int*)t8)[9] = (unsigned int)&lara.right_arm.frame_base[((lara.right_arm.frame_number - anims[lara.right_arm.anim_number].frame_base) * (anims[lara.right_arm.anim_number].interpolation >> 8)) + 9];
			mRotSuperPackedYXZ_CL(&t8[0], 8);
			snaff_current_gte_matrix_V1(&s0[72]);
			Hardcore_mTranslateXYZ_CL(&s1[33]);

			mRotSuperPackedYXZ_CL(&t8[0], 0);
			snaff_current_gte_matrix_V1(&s0[80]);
			Hardcore_mTranslateXYZ_CL(&s1[37]);

			mRotSuperPackedYXZ_CL(&t8[0], 0);
			snaff_current_gte_matrix_V1(&s0[88]);
			mLoadMatrix_CL(&t8[30]);
			Hardcore_mTranslateXYZ_CL(&s1[41]);
			setup_rotation_matrix(&t8[14]);
			mRotYXZ_CL(lara.left_arm.y_rot, lara.left_arm.x_rot, lara.left_arm.z_rot);

			((unsigned int*)t8)[9] = (unsigned int)& lara.left_arm.frame_base[((lara.left_arm.frame_number - anims[lara.left_arm.anim_number].frame_base) * (anims[lara.left_arm.anim_number].interpolation >> 8)) + 9];
			mRotSuperPackedYXZ_CL(&t8[0], 11);
			snaff_current_gte_matrix_V1(&s0[96]);
			Hardcore_mTranslateXYZ_CL(&s1[45]);
			mRotSuperPackedYXZ_CL(&t8[0], 0);
			snaff_current_gte_matrix_V1(&s0[104]);
			Hardcore_mTranslateXYZ_CL(&s1[49]);
			mRotSuperPackedYXZ_CL(&t8[0], 0);
			snaff_current_gte_matrix_V1(&s0[112]);
			break;
		}
		case 2:
		{
			//loc_840B0
			setup_rotation_matrix(&t8[14]);
			mRotYXZ_CL(lara.torso_y_rot, lara.torso_x_rot, lara.torso_z_rot);

			((unsigned int*)t8)[9] = (unsigned int)& lara.right_arm.frame_base[((lara.right_arm.frame_number - anims[lara.right_arm.anim_number].frame_base) * (anims[lara.right_arm.anim_number].interpolation >> 8)) + 9];
			mRotSuperPackedYXZ_CL(&t8[0], 8);
			snaff_current_gte_matrix_V1(&s0[72]);
			Hardcore_mTranslateXYZ_CL(&s1[33]);
			mRotSuperPackedYXZ_CL(&t8[0], 0);
			snaff_current_gte_matrix_V1(&s0[80]);
			Hardcore_mTranslateXYZ_CL(&s1[37]);
			mRotSuperPackedYXZ_CL(&t8[0], 0);
			snaff_current_gte_matrix_V1(&s0[88]);
			mLoadMatrix_CL(&t8[30]);
			Hardcore_mTranslateXYZ_CL(&s1[41]);

			setup_rotation_matrix(&t8[14]);
			mRotYXZ_CL(lara.torso_y_rot, lara.torso_x_rot, lara.torso_z_rot);

			((unsigned int*)t8)[9] = (unsigned int)& lara.left_arm.frame_base[((lara.left_arm.frame_number - anims[lara.left_arm.anim_number].frame_base) * (anims[lara.left_arm.anim_number].interpolation >> 8)) + 9];
			mRotSuperPackedYXZ_CL(&t8[0], 11);
			snaff_current_gte_matrix_V1(&s0[96]);
			Hardcore_mTranslateXYZ_CL(&s1[45]);
			mRotSuperPackedYXZ_CL(&t8[0], 0);
			snaff_current_gte_matrix_V1(&s0[104]);
			Hardcore_mTranslateXYZ_CL(&s1[49]);
			mRotSuperPackedYXZ_CL(&t8[0], 0);
			snaff_current_gte_matrix_V1(&s0[112]);
			break;
		}
		case 4:
		case 5:
		case 6:
		{
			//loc_84204
			((unsigned int*)t8)[9] = (unsigned int)& lara.right_arm.frame_base[(lara.right_arm.frame_number * (anims[lara.right_arm.anim_number].interpolation >> 8)) + 9];
			mRotSuperPackedYXZ_CL(&t8[0], 8);
			snaff_current_gte_matrix_V1(&s0[72]);
			Hardcore_mTranslateXYZ_CL(&s1[33]);
			mRotSuperPackedYXZ_CL(&t8[0], 0);
			snaff_current_gte_matrix_V1(&s0[80]);
			Hardcore_mTranslateXYZ_CL(&s1[37]);
			mRotSuperPackedYXZ_CL(&t8[0], 0);
			snaff_current_gte_matrix_V1(&s0[88]);
			mLoadMatrix_CL(&t8[30]);
			Hardcore_mTranslateXYZ_CL(&s1[41]);
			mRotSuperPackedYXZ_CL(&t8[0], 0);
			snaff_current_gte_matrix_V1(&s0[96]);
			Hardcore_mTranslateXYZ_CL(&s1[45]);
			mRotSuperPackedYXZ_CL(&t8[0], 0);
			snaff_current_gte_matrix_V1(&s0[104]);
			Hardcore_mTranslateXYZ_CL(&s1[49]);
			mRotSuperPackedYXZ_CL(&t8[0], 0);
			snaff_current_gte_matrix_V1(&s0[112]);
			break;
		}
		case 9:///@FIXME Says < 0xA investigate me!
		{
			break;
		}
		}
	
	} else
	{
		goto loc_83E60;
	}

	copy_matrix_from_scratch(&t8[22], s0);
	copy_matrix_from_scratch(&t8[30], &s0[56]);
	mLoadMatrix_CL(&t8[38]);
}

void DEL_restore_both_matrices(int* t8, int* a0)
{
	int t0 = t8[56];
	int t1 = t8[57];
	int t2 = t8[58];
	int t3 = t8[59];

	L11 = t0 & 0xFFFF;
	L12 = (t0 >> 16) & 0xFFFF;

	L13 = t1 & 0xFFFF;
	L21 = (t1 >> 16) & 0xFFFF;

	L22 = t2 & 0xFFFF;
	L23 = (t2 >> 16) & 0xFFFF;

	L31 = t3 & 0xFFFF;
	L32 = (t3 >> 16) & 0xFFFF;

	int t4 = t8[60];
	int t5 = t8[61];
	int t6 = t8[62];
	int t7 = t8[63];

	L33 = t4;
	RBK = t5;
	GBK = t6;
	BBK = t7;

	mLoadMatrix_CL(a0);
}

void DEL_stash_both_matrices(int* t8, int* a0)
{
	int t0 = (L11 & 0xFFFF) | ((L12 & 0xFFFF) << 16);
	int t1 = (L13 & 0xFFFF) | ((L21 & 0xFFFF) << 16);
	int t2 = (L22 & 0xFFFF) | ((L23 & 0xFFFF) << 16);
	int t3 = (L31 & 0xFFFF) | ((L32 & 0xFFFF) << 16);

	t8[56] = t0;
	t8[57] = t1;
	t8[58] = t2;
	t8[59] = t3;

	int t4 = L33;
	int t5 = RBK;
	int t6 = GBK;
	int t7 = BBK;

	t8[60] = t4;
	t8[61] = t5;
	t8[62] = t6;
	t8[63] = t7;

	snaff_current_gte_matrix_V1(a0);
}

void InterpolateMatrix(int* t8, int* a0)//85414
{
	int t0 = (R22 & 0xFFFF) | ((R23 & 0xFFFF) << 16);
	int t1 = (R31 & 0xFFFF) | ((R32 & 0xFFFF) << 16);
	int t2 = R33;
	int t3 = (L22 & 0xFFFF) | ((L23 & 0xFFFF) << 16);
	int t4 = (L31 & 0xFFFF) | ((L32 & 0xFFFF) << 16);
	int t5 = L33;

	t8[90] = t0;
	t8[91] = t1;
	t8[92] = t2;

	t8[82] = t3;
	t8[83] = t4;
	t8[84] = t5;

	int v1 = t8[47];
	int t7 = t8[46];

	int t6 = (R11 & 0xFFFF) | ((R12 & 0xFFFF) << 16);
	t3 = (R13 & 0xFFFF) | ((R21 & 0xFFFF) << 16);
	int a3 = (L11 & 0xFFFF) | ((L12 & 0xFFFF) << 16);
	t2 = (L13 & 0xFFFF) | ((L21 & 0xFFFF) << 16);

	t1 = t6 >> 16;
	t6 <<= 16;
	t6 >>= 16;
	t5 = t3 >> 16;
	t3 <<= 16;
	t3 >>= 16;
	t0 = a3 >> 16;
	a3 <<= 16;
	a3 >>= 16;
	t4 = t2 >> 16;
	t2 <<= 16;
	t2 >>= 16;

	if (v1 == 2 || (t7 == 2 && v1 == 4))
	{
		//loc_854A8
		t0 += t1;
		t0 >>= 1;
		a3 += t6;
		a3 >>= 1;
		t2 += t3;
		t2 >>= 1;
		t4 += t5;
		t4 >>= 1;

		((short*)a0)[0] = a3;
		((short*)a0)[1] = t0;
		((short*)a0)[2] = t2;
		((short*)a0)[3] = t4;

		a3 = ((short*)t8)[164];
		t6 = ((short*)t8)[180];
		t0 = ((short*)t8)[165];
		t1 = ((short*)t8)[181];
		a3 += t6;
		a3 >>= 1;
		t0 += t1;
		t0 >>= 1;
		t2 = ((short*)t8)[166];
		t3 = ((short*)t8)[182];
		t4 = ((short*)t8)[167];
		t5 = ((short*)t8)[183];
		t2 += t3;
		t2 >>= 1;
		t4 += t5;
		t4 >>= 1;

		((short*)a0)[4] = a3;
		((short*)a0)[5] = t0;
		((short*)a0)[6] = t2;
		((short*)a0)[7] = t4;

		a3 = ((short*)t8)[168];
		t6 = ((short*)t8)[184];

		t0 = RBK;
		t1 = TRX;

		a3 += t6;
		a3 >>= 1;
		t0 += t1;
		t0 >>= 1;
		t2 = GBK;
		t3 = TRY;
		t4 = BBK;
		t5 = TRZ;

		t2 += t3;
		t2 >>= 1;
		t4 += t5;
		t4 >>= 1;
	}
	else if(t7 == 1)
	{
		//loc_8556C
		int at = t0 - t1;
		t0 = at >> 2;
		t0 = t1 + t0;
		a3 -= t6;
		a3 >>= 2;
		a3 = t6 + a3;
		t2 -= t3;
		t2 >>= 2;
		t2 = t3 + t2;
		t4 -= t5;
		t4 >>= 2;
		t4 = t5 + t4;

		((short*)a0)[0] = a3;
		((short*)a0)[1] = t0;
		((short*)a0)[2] = t2;
		((short*)a0)[3] = t4;

		a3 = ((short*)t8)[164];
		t6 = ((short*)t8)[180];
		t0 = ((short*)t8)[165];
		t1 = ((short*)t8)[181];

		a3 -= t6;
		a3 >>= 2;
		a3 = t6 + a3;
		t0 -= t1;
		t0 >>= 2;
		t0 = t1 + t0;

		t2 = ((short*)t8)[166];
		t3 = ((short*)t8)[182];
		t4 = ((short*)t8)[167];
		t5 = ((short*)t8)[183];

		t2 -= t3;
		t2 >>= 2;
		t2 = t3 + t2;
		t4 -= t5;
		t4 >>= 2;
		t4 = t5 + t4;

		((short*)a0)[4] = a3;
		((short*)a0)[5] = t0;
		((short*)a0)[6] = t2;
		((short*)a0)[7] = t4;

		a3 = ((short*)t8)[168];
		t6 = ((short*)t8)[184];

		t0 = RBK;
		t1 = TRX;

		a3 -= t6;
		a3 >>= 2;
		a3 = t6 + a3;
		t0 -= t1;
		t0 >>= 2;

		t0 = t1 + t0;
		t2 = GBK;
		t3 = TRY;
		t4 = BBK;
		t5 = TRZ;
		t2 -= t3;
		t2 >>= 2;
		t2 = t3 + t2;
		t4 -= t5;
		t4 >>= 2;
		t4 = t5 + t4;
	}
	else
	{
		//loc_85664
		int at = t0 - t1;
		t1 = at >> 2;
		t0 -= t1;
		t6 = a3 - t6;
		t6 >>= 2;
		a3 -= t6;
		t3 = t2 - t3;
		t3 >>= 2;
		t2 -= t3;
		t5 = t4 - t5;
		t5 >>= 2;
		t4 -= t5;

		((short*)a0)[0] = a3;
		((short*)a0)[1] = t0;
		((short*)a0)[2] = t2;
		((short*)a0)[3] = t4;

		a3 = ((short*)t8)[164];
		t6 = ((short*)t8)[180];
		t0 = ((short*)t8)[165];
		t1 = ((short*)t8)[181];

		t6 = a3 - t6;
		t6 >>= 2;
		a3 -= t6;
		t1 = t0 - t1;
		t1 >>= 2;
		t0 -= t1;

		t2 = ((short*)t8)[166];
		t3 = ((short*)t8)[182];
		t4 = ((short*)t8)[167];
		t5 = ((short*)t8)[183];

		t3 = t2 - t3;
		t3 >>= 2;
		t2 -= t3;
		t5 = t4 - t5;
		t5 >>= 2;
		t4 -= t5;

		((short*)a0)[4] = a3;
		((short*)a0)[5] = t0;
		((short*)a0)[6] = t2;
		((short*)a0)[7] = t4;

		a3 = ((short*)t8)[168];
		t6 = ((short*)t8)[184];

		t0 = RBK;
		t1 = TRX;

		t6 = a3 - t6;
		t6 >>= 2;
		a3 -= t6;
		t1 = t0 - t1;
		t1 >>= 2;
		t0 -= t1;

		t2 = GBK;
		t3 = TRY;
		t4 = BBK;
		t5 = TRZ;

		t3 = t2 - t3;
		t3 >>= 2;
		t2 -= t3;
		t5 = t4 - t5;
		t5 >>= 2;
		t4 -= t5;
	}

	//loc_85750
	((short*)a0)[8] = a3;
	((int*)a0)[5] = t0;
	((int*)a0)[6] = t2;
	((int*)a0)[7] = t4;
}

void DEL_CalcLaraMatrices_Interpolated_ASM(short* frame1, short* frame2, int frac, int rate, long* bone, int flag)
{
	int sp[256];
	int* t8 = &sp[0];
	S_MemSet((char*)&sp[0], 0, 1024);
	struct ITEM_INFO* item = lara_item;//$t9
	t8[46] = frac;
	t8[47] = rate;
	short* s0 = frame1;
	short* s1 = frame2;
	frame1 += 9;
	frame2 += 9;
	t8[9] = (int)frame1;
	t8[10] = (int)frame2;
	snaff_current_gte_matrix_V1(&t8[72]);
	struct MATRIX3D* a0 = NULL;
	struct ANIM_STRUCT* anim = NULL;

	if ((flag & 0x1))
	{
		TRX = 0;
		TRY = 0;
		TRZ = 0;
		t8[13] = (int)lara_joint_matrices;
	}
	else
	{
		//loc_83C40
		t8[13] = (int)lara_matrices;
		mTranslateAbsXYZ_CL(item->pos.x_pos, item->pos.y_pos, item->pos.z_pos);
		if ((flag & 0x2))
		{
			ScaleCurrentMatrix(0, -4096, -4096, -4096);
		}
	}

	//loc_83C74
	mRotYXZ_CL(item->pos.y_rot, item->pos.x_rot, item->pos.z_rot);
	snaff_current_gte_matrix_V1(&t8[64]);
	L11 = R11;
	L12 = R12;
	L13 = R13;
	L21 = R21;
	L22 = R22;
	L23 = R23;
	L31 = R31;
	L32 = R32;
	L33 = R33;
	RBK = TRX;
	GBK = TRY;
	BBK = TRZ;

	mTranslateXYZ_CL(s0[6], s0[7], s0[8]);
	iTranslateXYZ2_CL(s1[6], s1[7], s1[8]);
	mRotSuperPackedYXZ_CL(t8, 0);
	iRotSuperPackedYXZ_CL(t8, 0);///@FIXME iRotZ MAC3 bad value!!

	s0 = (short*)t8[13];

	InterpolateMatrix(t8, (int*)s0);
	DEL_stash_both_matrices(t8, &t8[48]);

	s1 = (short*)&bone[0];
	int t9 = 6;

	//loc_84480
	do
	{
		Hardcore_iTranslateXYZ_CL((long*)&s1[2], t8);
		mRotSuperPackedYXZ_CL(t8, 0);
		iRotSuperPackedYXZ_CL(t8, 0);
		InterpolateMatrix(t8, (int*)&s0[16]);
		t9--;

		s1 += 8;
		if (t9 == 3)
		{
			DEL_restore_both_matrices(t8, &t8[48]);
		}
		//loc_844B8
		s0 += 16;
	} while (t9 != 0);

	DEL_restore_both_matrices(t8, &t8[48]);

	s0 -= 96;
	s1 -= 48;

	struct ANIM_STRUCT* t99 = &anims[0];
	Hardcore_iTranslateXYZ_CL((long*)&s1[50], t8);

	//a0 = lara.weapon_item
	//v0 = 5
	if (lara.weapon_item != -1 && lara.gun_type == 5 &&
		items[lara.weapon_item + 1].frame_number == 0 ||
		items[lara.weapon_item + 1].frame_number == 2 ||
		items[lara.weapon_item + 1].frame_number == 4)
	{
		//v1 = lara.right_arm.anim_number
		//v0 = (anims[lara.right_arm.anim_number].interpolation >> 8);
		//v1 = lara.right_arm.frame_number
		//t0 = lara.right_arm.frame_number * (anims[lara.right_arm.anim_number].interpolation >> 8);
		//a1 = 7
		t8[10] = (int)lara.right_arm.frame_base[lara.right_arm.frame_number * (anims[lara.right_arm.anim_number].interpolation >> 8) + 9];
		t8[9] = (int)lara.right_arm.frame_base[lara.right_arm.frame_number * (anims[lara.right_arm.anim_number].interpolation >> 8) + 9];

		mRotSuperPackedYXZ_CL(t8, 7);
		iRotSuperPackedYXZ_CL(t8, 7);
	}
	else
	{
		mRotSuperPackedYXZ_CL(t8, 0);
		iRotSuperPackedYXZ_CL(t8, 0);
	}

	//loc_84594
	mRotYXZ_CL(lara.torso_y_rot, lara.torso_x_rot, lara.torso_z_rot);
	iRotYXZ_CL(lara.torso_y_rot, lara.torso_x_rot, lara.torso_z_rot);

	InterpolateMatrix(t8, (int*)&s0[112]);
	DEL_stash_both_matrices(t8, (int*)&t8[48]);
	Hardcore_iTranslateXYZ_CL((long*)&s1[106], t8);

	t8[11] = t8[9];
	t8[12] = t8[10];

	mRotSuperPackedYXZ_CL(t8, 6);
	iRotSuperPackedYXZ_CL(t8, 6);

	t8[9] = t8[11];
	t8[10] = t8[12];

	mRotYXZ_CL(lara.head_y_rot, lara.head_x_rot, lara.head_z_rot);
	iRotYXZ_CL(lara.head_y_rot, lara.head_x_rot, lara.head_z_rot);

	InterpolateMatrix(t8, (int*)&s0[128]);
	DEL_restore_both_matrices(t8, &t8[48]);
	Hardcore_iTranslateXYZ_CL((long*)&s1[58], t8);

	//a0 = lara.gun_status
	if (lara.gun_status == 2 || lara.gun_status == 3 ||
		lara.gun_status == 4 || lara.gun_status == 5)
	{
		switch (lara.gun_type)
		{
		case 0:
		case 7:
		case 8:
		{
		loc_8469C:
			mRotSuperPackedYXZ_CL(t8, 0);
			iRotSuperPackedYXZ_CL(t8, 0);
			InterpolateMatrix(t8, (int*)&s0[144]);
			Hardcore_iTranslateXYZ_CL((long*)&s1[66], t8);
			mRotSuperPackedYXZ_CL(t8, 0);
			iRotSuperPackedYXZ_CL(t8, 0);
			InterpolateMatrix(t8, (int*)&s0[160]);
			Hardcore_iTranslateXYZ_CL((long*)&s1[74], t8);
			mRotSuperPackedYXZ_CL(t8, 0);
			iRotSuperPackedYXZ_CL(t8, 0);
			InterpolateMatrix(t8, (int*)&s0[176]);
			DEL_restore_both_matrices(t8, &t8[48]);
			Hardcore_iTranslateXYZ_CL((long*)&s1[82], t8);

			if (lara.flare_control_left)
			{
				anim = &anims[lara.left_arm.anim_number];
				t8[10] = (int)&lara.left_arm.frame_base[((lara.left_arm.frame_number - anim->frame_base) * (anim->interpolation >> 8)) + 9];
				t8[9] = (int)&lara.left_arm.frame_base[((lara.left_arm.frame_number - anim->frame_base) * (anim->interpolation >> 8)) + 9];
				mRotSuperPackedYXZ_CL(t8, 11);
				iRotSuperPackedYXZ_CL(t8, 11);
			}//loc_84778
			else
			{
				mRotSuperPackedYXZ_CL(t8, 0);
				iRotSuperPackedYXZ_CL(t8, 0);
			}

			InterpolateMatrix(t8, (int*)&s0[192]);
			Hardcore_iTranslateXYZ_CL((long*)&s1[90], t8);
			mRotSuperPackedYXZ_CL(t8, 0);
			break;
		}
		case 1:
		case 3:
		{
			//loc_847A4
			break;
		}
		case 2:
		{
			//loc_84870
			break;
		}
		case 4:
		case 5:
		case 6:
		{
			//loc_849E4

			break;
		}
		}
	}
	else
	{
		goto loc_8469C;
	}

	mRotSuperPackedYXZ_CL(t8, 0);
	iRotSuperPackedYXZ_CL(t8, 0);
	InterpolateMatrix(t8, (int*)&s0[208]);
	Hardcore_iTranslateXYZ_CL((long*)&s1[98], t8);
	mRotSuperPackedYXZ_CL(t8, 0);
	iRotSuperPackedYXZ_CL(t8, 0);
	InterpolateMatrix(t8, (int*)&s0[224]);

	//def_84694
	mLoadMatrix_CL(&t8[72]);
}

int GetFrames(struct ITEM_INFO* item, int* a1, int* a2)//8582C
{
	struct ANIM_STRUCT* anim;//$t0
	int t1;
	int t2;
	int t3;

	anim = &anims[item->anim_number];
	
	t1 = (item->frame_number - anim->frame_base) / (anim->interpolation & 0xFF);
	t2 = (item->frame_number - anim->frame_base) % (anim->interpolation & 0xFF);

	a2[0] = anim->interpolation & 0xFF;

	t3 = t1 * (anim->interpolation >> 8);

	((short**)a1)[0] = &anim->frame_ptr[t3];
	((short**)a1)[1] = &anim->frame_ptr[t3 + (anim->interpolation >> 8)];

	if (t2 == 0)
	{
		return 0;
	}

	//loc_8589C
	t3 = t1 * (anim->interpolation & 0xFF);

	if (anim->frame_end < t3 + (anim->interpolation & 0xFF))
	{
		a2[0] = anim->frame_end - (t3 + (anim->interpolation & 0xFF)) - (anim->interpolation & 0xFF);
	}

	return t2;
}

short* GetBoundsAccurate(struct ITEM_INFO* item)//858F8, 8793C
{
	int var_10[2];
	int var_8;
	int t0;
	int i;//$a1
	short v0;
	short a0;
	int v1;
	short* t4;
	short* t5;
	short* a2;

	t0 = GetFrames(item, &var_10[0], &var_8);

	if (t0 == 0)
	{
		return (short*)var_10[0];
	}

	//loc_8591C
	a2 = &interpolated_bounds[0];
	i = 6;
	
	//loc_85928
	t4 = ((short*)var_10[0]);
	t5 = ((short*)var_10[1]);
	
	do
	{
		v0 = t5[0];
		a0 = t4[0];

		i--;

		v0 -= a0;
		v1 = v0 * t0;

		t5++;
		t4++;

		v0 = v1 / var_8;
		a2++;
		a0 -= v0;
		a2[-1] = a0;
	} while (i != 0);

	return interpolated_bounds;
}

void snaff_current_gte_matrix_V1(int* mat)
{
	mat[0] = (R11 & 0xFFFF) | ((R12 & 0xFFFF) << 16);
	mat[1] = (R13 & 0xFFFF) | ((R21 & 0xFFFF) << 16);
	mat[2] = (R22 & 0xFFFF) | ((R23 & 0xFFFF) << 16);
	mat[3] = (R31 & 0xFFFF) | ((R32 & 0xFFFF) << 16);
	mat[4] = R33;
	mat[5] = TRX;
	mat[6] = TRY;
	mat[7] = TRZ;
}

void GetLaraJointPos(struct PHD_VECTOR* pos, long joint)
{
	UNIMPLEMENTED();
}

short* GetBestFrame(struct ITEM_INFO* item)
{
	UNIMPLEMENTED();
	return NULL;
}