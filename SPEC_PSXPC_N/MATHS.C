#include "MATHS.H"

#include "LOAD_LEV.H"
#include "SPECIFIC.H"

#include <INLINE_C.H>
#include "3D_GEN.H"
#include "CAMERA.H"
#include "DRAW.H"
#include "GPU.H"
#include "GTEREG.H"
#include "DRAWSPKS.H"
#include "MISC.H"

void mQuickW2VMatrix()//77AEC(<), 79B30(<)
{
	MatrixSP = 0;
	Matrix = &MatrixStack[0];

	((int*)&MatrixStack)[0] = ((unsigned short*)phd_mxptr)[0] | ((unsigned short*)phd_mxptr)[2] << 16;
	((int*)&MatrixStack)[1] = ((unsigned short*)phd_mxptr)[4] | ((unsigned short*)phd_mxptr)[8] << 16;
	((int*)&MatrixStack)[2] = ((unsigned short*)phd_mxptr)[10] | ((unsigned short*)phd_mxptr)[12] << 16;
	((int*)&MatrixStack)[3] = ((unsigned short*)phd_mxptr)[16] | ((unsigned short*)phd_mxptr)[18] << 16;

	R12 = ((unsigned short*)phd_mxptr)[2];
	R11 = ((unsigned short*)phd_mxptr)[0];

	R21 = ((unsigned short*)phd_mxptr)[8];
	R13 = ((unsigned short*)phd_mxptr)[4];

	R23 = ((unsigned short*)phd_mxptr)[12];
	R22 = ((unsigned short*)phd_mxptr)[10];

	R32 = ((unsigned short*)phd_mxptr)[18];
	R31 = ((unsigned short*)phd_mxptr)[16];

	((short*)&MatrixStack)[8] = ((unsigned short*)phd_mxptr)[20];
	((int*)&MatrixStack)[5] = ((int*)phd_mxptr)[3];
	((int*)&MatrixStack)[6] = ((int*)phd_mxptr)[7];
	((int*)&MatrixStack)[7] = ((int*)phd_mxptr)[11];

	R33 = ((unsigned short*)phd_mxptr)[20];
	TRX = ((int*)phd_mxptr)[3];
	TRY = ((int*)phd_mxptr)[7];
	TRZ = ((int*)phd_mxptr)[11];

	CamGTE.m00 = ((unsigned short*)&w2v_matrix)[0];
	CamGTE.m01 = ((unsigned short*)&w2v_matrix)[2];
	CamGTE.m02 = ((unsigned short*)&w2v_matrix)[4];
	CamGTE.m10 = ((unsigned short*)&w2v_matrix)[8];
	CamGTE.m11 = ((unsigned short*)&w2v_matrix)[10];
	CamGTE.m12 = ((unsigned short*)&w2v_matrix)[12];
	CamGTE.m20 = ((unsigned short*)&w2v_matrix)[16];
	CamGTE.m21 = ((unsigned short*)&w2v_matrix)[18];
	CamGTE.m22 = ((unsigned short*)&w2v_matrix)[20];
}

void gte_sttr(struct PHD_VECTOR* vec)//To investigate, this should not be in this file.
{
	vec->x = Matrix->tx >> 12;
	vec->y = Matrix->ty >> 12;
	vec->z = Matrix->tz >> 12;
}

long mGetAngle(long x, long z, long tx, long tz)//77678(<), 796BC(<) (F)
{
	long dx = tx - x;
	long dz = tz - z;
	short table_index = 0;
	long result_angle = 0;
	long temp = 0;

	if ((dx | dz) != 0)
	{
		if (dx < 0)
		{
			table_index |= 0x10;//FIXME: += (4);
			dx = -dx;
		}

		//0x796E0
		if (dz < 0)
		{
			table_index += 2;
			dz = -dz;
		}

		//796F0
		if (dx < dz)
		{
			table_index += 1;
			temp = dx;
			dx = dz;
			dz = temp;
		}

		//7970C
		while (dz / 65536 != 0)
		{
			dx /= 2;
			dz /= 2;
		}

		//79724
		result_angle = atanTab[dz * 2048 / dx];
		result_angle += atanOctantTab[table_index];

		if (result_angle < 0)
		{
			result_angle = -result_angle;
		}//79760

	}//79760

	return -result_angle & 0xFFFF;
}

long mSqrt(long value)//83B30(<), 85B74(<) (F)
{
	long v0 = 0x1F;

	long v1 = gte_ldlzc(value);

	if (value != 0)
	{
		v1 &= 0xFFFFFFFE;
		v0 = v0 - v1 >> 1;
		long at = v1 - 0x18;

		if (v1 - 0x18 < 0)
		{
			//loc_85BA8
			value >>= 0x18 - v1;
		}
		else
		{
			value <<= v1 - 0x18;
		}

		//loc_85BB4
		value = SqrtTable[value - 0x40] << v0;

	}//locret_85BD0

	return (value >> 12);
}

long phd_sqrt_asm(long value)//83B30(<), 85B74(<) (F)
{
	long v0 = 0x1F;

	long v1 = gte_ldlzc(value);

	if (value != 0)
	{
		v1 &= 0xFFFFFFFE;
		v0 = v0 - v1 >> 1;
		long at = v1 - 0x18;

		if (v1 - 0x18 < 0)
		{
			//loc_85BA8
			value >>= 0x18 - v1;
		}
		else
		{
			value <<= v1 - 0x18;
		}

		//loc_85BB4
		value = SqrtTable[value - 0x40] << v0;

	}//locret_85BD0

	return (value >> 12);
}

void ScaleCurrentMatrix(long bStoreInMatrix, long sx, long sy, long sz)
{
	int t2, v0, v1;
	unsigned int t0, t1, at;

	t0 = R11 | (R12 << 16);
	t1 = R13 | (R21 << 16);
	t2 = R22 | (R23 << 16);
	v0 = R31 | (R32 << 16);
	v1 = R33;

	R12 = ((((t0 << 16) >> 16) * sx) >> 12) & 0xFFFF;
	R11 = ((((t0 >> 16) * sy) >> 12) << 16);
	R21 = ((((t1 << 16) >> 16) * sz) >> 12) & 0xFFFF;
	R13 = (((t1 >> 16) * sx) >> 12) << 16;
	R23 = ((((t2 << 16) >> 16) * sy) >> 12) & 0xFFFF;
	R22 = (((t2 >> 16) * sz) >> 12) << 16;
	R32 = ((((v0 << 16) >> 16) * sx) >> 12) & 0xFFFF;
	R31 = (((v0 >> 16)  * sy) >> 12) << 16;
	R33 = ((((v1 << 16) >> 16) * sz) >> 12);

	if (bStoreInMatrix)
	{
		Matrix->m00 = R11;
		Matrix->m01 = R12;
		Matrix->m02 = R13;
		Matrix->m10 = R21;
		Matrix->m11 = R22;
		Matrix->m12 = R23;
		Matrix->m20 = R31;
		Matrix->m21 = R32;
		Matrix->m22 = R33;
	}//locret_77E68
}

void mPushMatrix()//764D0(<), 78514(<) (F)
{
	++Matrix;
	Matrix->m00 = R11;
	Matrix->m01 = R12;
	Matrix->m02 = R13;
	Matrix->m10 = R21;
	Matrix->m11 = R22;
	Matrix->m12 = R23;
	Matrix->m20 = R31;
	Matrix->m21 = R32;
	Matrix->m22 = R33;
	Matrix->tx = TRX;
	Matrix->ty = TRY;
	Matrix->tz = TRZ;
}

void mPopMatrix()//76520(<), 78564(<) (F)
{
	mLoadMatrix(--Matrix);
}

void mUnitMatrix()
{
	UNIMPLEMENTED();
}

void mPushUnitMatrix()//76534(<), 78578(<)
{
	setrot(++Matrix, 0x1000, 0, 0x1000, 0, 0x1000);
}

void mTranslate()//76558(<) (!)
{
	UNIMPLEMENTED();
}

void mTranslateAbsXYZ(long x, long y, long z)
{
	int t0 = ((int*)MatrixStack)[5];
	int t1 = ((int*)MatrixStack)[6];
	int t2 = ((int*)MatrixStack)[7];
	TRX = 0;
	TRY = 0;
	TRZ = 0;
	x -= t0;
	y -= t1;
	z -= t2;

	mTranslateXYZ(x, y, z);
}

void mTranslateXYZ(long x, long y, long z)//7658C(<), 785D0(<) (!)
{
	int t0;
	int t1;
	int t2;

	int t3;
	int t4;
	int t5;

	t4 = y >> 15;
	if (y < 0)
	{
		y = -y;
		t4 = y >> 15;
		y &= 0x7FFF;
		t4 = -t4;
		y = -y;
	}//loc_765AC
	else
	{
		y &= 0x7FFF;
	}

	//loc_765B0 :
	t5 = z >> 15;
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
		//loc_765D0
		z &= 0x7FFF;
	}
	//loc_765D4
	t3 = x >> 15;
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

	t0 = t3 << 3;
	if (t3 < 0)
	{
		t3 = -t3;
		t3 <<= 3;
		t0 = -t3;
	}
	//loc_7663C
	t1 = t4 << 3;
	if (t4 < 0)
	{
		t4 = -t4;
		t4 <<= 3;
		t1 = -t4;
	}
	//loc_76650
	t2 = t5 << 3;
	if (t5 < 0)
	{
		t5 = -t5;
		t5 <<= 3;
		t2 = -t5;
	}//loc_76664

	t3 = MAC1;
	t4 = MAC2;
	t5 = MAC3;

	t0 += t3;
	t1 += t4;
	t2 += t5;

	TRX = t0;
	TRY = t1;
	TRZ = t2;

	Matrix->tx = t0;
	Matrix->ty = t1;
	Matrix->tz = t2;
}

void mRotX(long rx)//7669C (F)
{
	int t0;
	int t1;
	int t2;
	int t3;
	int t4;
	int t5;
	int t6;

	rx = (rx >> 2) & 0x3FFC;

	if (rx != 0)
	{
		//loc_766B4
		t5 = (rcossin_tbl[rx >> 1] & 0xFFFF) | ((rcossin_tbl[rx >> 1 | 1] & 0xFFFF ) << 16);

		VX0 = (0xFFFF0000 & t5) & 0xFFFF;
		VY0 = ((0xFFFF0000 & t5) >> 16) & 0xFFFF;
		VZ0 = t5 & 0xFFFF;

		t0 = ((R12 << 16) | (R11 & 0xFFFF)) & 0xFFFF;
		t1 = ((R21 << 16) | (R13 & 0xFFFF)) & 0xFFFF0000;
		t3 = ((R32 << 16) | (R31 & 0xFFFF)) & 0xFFFF;

		docop2(0x486012);

		t6 = t5 >> 16;
		t5 <<= 16;
		t5 = -t5;

		VX1 = t5;
		VY1 = (t5 >> 16) & 0xFFFF;
		VZ1 = t6;

		t4 = MAC1;
		t2 = MAC2 & 0xFFFF;
		t5 = MAC3;

		docop2(0x48E012);

		t0 |= t4 << 16;
		t3 |= t5 << 16;

		t5 = MAC1 & 0xFFFF;
		t6 = MAC2;
		t4 = MAC3;

		t1 |= t5;
		t2 |= t6 << 16;
		SetRotation(t0, t1, t2, t3, t4);
	}
}

void mRotY(long ry)//76744 (F)
{
	int t0;
	int t1;
	int t2;
	int t3;
	int t4;
	int t5;
	int t6;
	int t7;

 	ry = (ry >> 2) & 0x3FFC;

	if (ry != 0)
	{
		t5 = (rcossin_tbl[ry >> 1] & 0xFFFF) | ((rcossin_tbl[ry >> 1 | 1] & 0xFFFF) << 16);
		t6 = (t5 >> 16) & 0xFFFF;
		t5 &= 0xFFFF;
		t2 = -t5;
		VX0 = t6;
		VY0 = (t5 >> 16) & 0xFFFF;
		VZ0 = t2;

		t0 = ((R12 << 16) | (R11 & 0xFFFF)) & 0xFFFF0000;
		t2 = ((R23 << 16) | (R22 & 0xFFFF)) & 0xFFFF;
		t3 = ((R32 << 16) | (R31 & 0xFFFF)) & 0xFFFF0000;

		docop2(0x486012);

		VX1 = t5;
		VY1 = (t5 >> 16) & 0xFFFF;
		VZ1 = t6;

		t4 = MAC1 & 0xFFFF;
		t1 = MAC2;
		t5 = MAC3 & 0xFFFF;

		docop2(0x48E012);

		t0 |= t4;
		t3 |= t5;

		t5 = MAC1 & 0xFFFF;
		t6 = MAC2;
		t4 = MAC3;

		t1 = (t1 << 16) | (t5);
		t2 |= t6 << 16;

		SetRotation(t0, t1, t2, t3, t4);
	}
}

void mRotYXZ(short y, short x, short z)//767E8 (F)
{
	mRotY(y);
	mRotX(x);
	mRotZ(z);
}

void SetRotation_I(int t0, int t1, int t2, int t3, int t4)
{
	L11 = t0 & 0xFFFF;
	L12 = (t0 >> 16) & 0xFFFF;
	L13 = t1 & 0xFFFF;
	L21 = (t1 >> 16) & 0xFFFF;
	L22 = t2 & 0xFFFF;
	L23 = (t2 >> 16) & 0xFFFF;
	L31 = t3 & 0xFFFF;
	L32 = (t3 >> 16) & 0xFFFF;
	L33 = t4;

	((int*)iMatrix)[0] = t0;
	((int*)iMatrix)[1] = t1;
	((int*)iMatrix)[2] = t2;
	((int*)iMatrix)[3] = t3;
	((int*)iMatrix)[4] = t4;
}

void mRotZ(long rz)//76804 (F)
{
	int t0;
	int t1;
	int t2;
	int t3;
	int t4;
	int t5;
	int t6;
	int t7;
	int a0;

	rz = (rz >> 2) & 0x3FFC;

	if (rz != 0)
	{
		//loc_7681C
		t0 = (rcossin_tbl[rz >> 1] & 0xFFFF) | ((rcossin_tbl[rz >> 1 | 1] & 0xFFFF) << 16);
		t1 = ((t0 >> 16) & 0xFFFF) | (t0 << 16);
		
		VX0 = (t1 & 0xFFFF);
		VY0 = ((t1 >> 16) & 0xFFFF);
		VZ0 = 0;

		t1 = ((R21 << 16) | (R13 & 0xFFFF)) & 0xFFFF;
		t2 = ((R23 << 16) | (R22 & 0xFFFF)) & 0xFFFF0000;
		t4 = R33;

		docop2(0x486012);

		t3 = t0 & 0xFFFF0000;
		t0 &= 0xFFFF;
		t0 = -t0;
		t0 &= 0xFFFF;
		t0 |= t3;

		VX1 = t0;
		VY1 = (t0 >> 16) & 0xFFFF;
		VZ1 = 0;

		t0 = MAC1 & 0xFFFF;
		t5 = MAC2;
		t3 = MAC3 & 0xFFFF;

		docop2(0x48E012);

		t5 <<= 16;
		t1 |= t5;

		t5 = MAC1;
		t6 = MAC2 & 0xFFFF;
		a0 = MAC3;

		t0 |= t5 << 16;
		t2 |= t6;
		t3 |= a0 << 16;

		SetRotation(t0, t1, t2, t3, t4);
	}
}

void iRotY(int ry)//76E60
{
	ry = (ry >> 2) & 0x3FFC;

	if (ry == 0)
	{
		return;
	}

	//loc_76E78
	int t5 = (rcossin_tbl[ry >> 1] & 0xFFFF) | ((rcossin_tbl[ry >> 1 | 1] & 0xFFFF) << 16);
	int t6 = t5 >> 16;
	t5 &= 0xFFFF;
	int t2 = -t5;
	VX0 = t6 & 0xFFFF;
	VY0 = (t6 >> 16) & 0xFFFF;
	VZ0 = t2;

	int t0 = L11 | (L12 << 16);
	t2 = L22 | (L23 << 16);
	int t3 = L31 | (L32 << 16);

	docop2(0x4A6012);

	VX1 = t5 & 0xFFFF;
	VY1 = (t5 >> 16) & 0xFFFF;
	VZ1 = t6;

	t0 &= 0xFFFF0000;
	t2 &= 0xFFFF;
	t3 &= 0xFFFF0000;

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

	SetRotation_I(t0, t1, t2, t3, t4);
}

void iRotX(int rx)
{
	rx = (rx >> 2) & 0x3FFC;

	if (rx == 0)
	{
		return;
	}

	int t5 = (rcossin_tbl[rx >> 1] & 0xFFFF) | ((rcossin_tbl[rx >> 1 | 1] & 0xFFFF) << 16);
	int t6 = 0xFFFF0000 & t5;
	VX0 = t6 & 0xFFFF;
	VY0 = (t6 >> 16) & 0xFFFF;
	VZ0 = t5;

	int t0 = L11 | (L12 << 16);
	int t1 = L13 | (L21 << 16);
	int t3 = L31 | (L32 << 16);

	docop2(0x4A6012);
	t6 = t5 >> 16;
	t5 <<= 16;
	t5 = -t5;

	VX1 = t5 & 0xFFFF;
	VY1 = (t5 >> 16) & 0xFFFF;
	VZ1 = t6;

	t0 &= 0xFFFF;
	t1 &= 0xFFFF0000;
	t3 &= 0xFFFF;

	int t4 = MAC1;
	int t2 = MAC2;
	t5 = MAC3;

	docop2(0x4AE012);

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

	SetRotation_I(t0, t1, t2, t3, t4);
}

void iRotZ(int rz)//76F04
{
	rz = (rz >> 2) & 0x3FFC;

	if (rz == 0)
	{
		return;
	}

	int t0 = (rcossin_tbl[rz >> 1] & 0xFFFF) | ((rcossin_tbl[rz >> 1 | 1] & 0xFFFF) << 16);

	int t1 = t0 >> 16;
	int t2 = t0 << 16;
	t1 |= t2;

	VX0 = t1 & 0xFFFF;
	VY0 = (t1 >> 16) & 0xFFFF;
	VZ0 = 0;

	t1 = L13 | (L21 << 16);
	t2 = L22 | (L23 << 16);
	int t4 = L33;

	docop2(0x4A6012);

	int t3 = t0 & 0xFFFF0000;
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

	docop2(0x4AE012);

	t2 &= 0xFFFF0000;
	t0 &= 0xFFFF;
	t5 <<= 16;
	t1 |= t5;
	t3 &= 0xFFFF;

	t5 = MAC1;
	int t6 = MAC2;
	int t8 = MAC3;

	t5 <<= 16;
	t0 |= t5;
	t6 &= 0xFFFF;
	t2 |= t6;
	t8 <<= 16;
	t3 |= t8;

	SetRotation_I(t0, t1, t2, t3, t4);
}


void iRotPackedYXZ(long a0)//76FDC(<)
{
	iRotY((a0 >> 4) & 0xFFC0);
	iRotX((a0 >> 14) & 0xFFC0);
	iRotZ((a0 << 6) & 0xFFC0);
}

void iRotSuperPackedYXZ(short** a0, long a1)//7700C(<)
{
	unsigned short* a2;
	int v0;
	int at;
	int a00;

	a2 = (unsigned short*)a0[0];
	v0 = *a2;

	if (a1 != 0)
	{
		do
		{
			v0 = *a2;
			a1--;
			a2++;

			if (!(v0 & 0xC000))
			{
				a2++;
			}//0x7702C
		} while (a1 != 0);

		v0 = *a2++;

	}//0x77038
	a2++;
	at = v0 >> 14;

	if (at-- != 0)
	{
		a0[0] = (short*)a2;

		if (at-- != 0)
		{
			if (at != 0)
			{
				iRotZ((v0 & 0xFFF) << 4);
			}//0x77064
			iRotY((v0 & 0xFFF) << 4);
		}
		//0x7706C
		iRotX((v0 & 0xFFF) << 4);
	}//0x77078

	at = *a2++;
	a0[0] = (short*)a2;

	iRotPackedYXZ((v0 << 16) | at);
}

void mRotSuperPackedYXZ(short** a0, long a1)//768BC
{
	unsigned short* a2;
	int v0;
	int at;
	a2 = (unsigned short*)a0[0];
	v0 = *a2;

	if (a1 != 0)
	{
		//loc_768C4
		do
		{
			a2++;
			a1--;

			if (!(v0 & 0xC000))
			{
				a2++;
			}//loc_768DC

		} while (a1 != 0);

		v0 = *a2;

	}//loc_768E8

	a2++;
	at = (v0 >> 14);
	if (at-- != 0)
	{
		a0[0] = (short*)a2;

		if (at-- != 0)
		{
			if (at == 0)
			{
				mRotY((v0 & 0xFFF) << 4);
				return;
			}
			else
			{
				mRotZ((v0 & 0xFFF) << 4);
				return;
			}
		}//loc_76914

		mRotX((v0 & 0xFFF) << 4);
		return;
	}//loc_76928

	at = *a2++;
	a0[0] = (short*)a2;

	mRotY((((v0 << 16) | at) >> 4) & 0xFFC0);
	mRotX((((v0 << 16) | at) >> 14) & 0xFFC0);
	mRotZ((((v0 << 16) | at) & 0x3FF) << 6);
}

void mRotPackedYXZ(long yxz)//7693C (F)
{
	UNIMPLEMENTED();
}

void SetRotation(int t0, int t1, int t2, int t3, int t4)//7696C(<) (F)
{
	R11 = (t0 & 0xFFFF);
	R12 = (t0 >> 16) & 0xFFFF;
	R13 = (t1 & 0xFFFF);
	R21 = (t1 >> 16) & 0xFFFF;
	R22 = (t2 & 0xFFFF);
	R23 = (t2 >> 16) & 0xFFFF;
	R31 = (t3 & 0xFFFF);
	R32 = (t3 >> 16) & 0xFFFF;
	R33 = t4;

	((int*)&Matrix->m00)[0] = t0;
	((int*)&Matrix->m02)[0] = t1;
	((int*)&Matrix->m11)[0] = t2;
	((int*)&Matrix->m20)[0] = t3;
	((int*)&Matrix->m22)[0] = t4;
}

void setrot(struct MATRIX3D* m, long t0, long t1, long t2, long t3, long t4)//76970 TOCHECK
{
	R11 = t0 & 0xFFFF;
	R12 = t0 >> 16;
	
	R13 = t1 & 0xFFFF;
	R21 = t1 >> 16;
	
	R22 = t2 & 0xFFFF;
	R23 = t2 >> 16;
	
	R31 = t3 & 0xFFFF;
	R32 = t3 >> 16;

	R33 = t4;

	((int*)Matrix)[0] = t0;
	((int*)Matrix)[1] = t1;
	((int*)Matrix)[2] = t2;
	((int*)Matrix)[3] = t3;
	((int*)Matrix)[4] = t4;
}

void mLoadMatrix(struct MATRIX3D* m)//7699C(<), 789E0(<) (F)
{
	R11 = m->m00;
	R12 = m->m01;
	R13 = m->m02;
	R21 = m->m10;
	R22 = m->m11;
	R23 = m->m12;
	R31 = m->m20;
	R32 = m->m21;
	R33 = m->m22;
	TRX = m->tx;
	TRY = m->ty;
	TRZ = m->tz;
	return;
}

void mCopyMatrix(struct MATRIX3D* m)//769E4(<), 78A28(<) (F)
{
	TRX = ((int*)m)[5];
	TRY = ((int*)m)[6];
	TRZ = ((int*)m)[7];

	((int*)Matrix)[5] = ((int*)m)[5];
	((int*)Matrix)[6] = ((int*)m)[6];
	((int*)Matrix)[7] = ((int*)m)[7];

	setrot(Matrix, ((int*)m)[0], ((int*)m)[1], ((int*)m)[2], ((int*)m)[3], ((int*)m)[4]);
}

void ASM_GetBounds()//76A28
{
	UNIMPLEMENTED();
}

void GetBounds()//76A28
{
	UNIMPLEMENTED();
}

void mSetTrans(long x, long y, long z)//76AF4(<), 78B38(<)
{
	TRX = x;
	TRY = y;
	TRZ = z;
	Matrix->tx = x;
	Matrix->ty = y;
	Matrix->tz = z;
}

void mClipBoundingBox(short* bounds)//76B14
{
	UNIMPLEMENTED();
}

void InitInterpolation(long frac, long rate, struct MATRIX3D* m)//76CB4(<) 
{
	int t0 = RBK;
	int t1 = GBK;
	int t2 = BBK;

	iFrac = frac;
	iRate = rate;
	iMatrix = m;

	iAmbientR = t0;
	iAmbientG = t1;
	iAmbientB = t2;

	t0 = R11 | (R12 << 16);
	t1 = R13 | (R21 << 16);
	t2 = R22 | (R23 << 16);
	int t3 = R31 | (R32 << 16);
	int t4 = R33;
	int t5 = TRX;
	int t6 = TRY;
	int t7 = TRZ;

	L11 = R11;
	L12 = R12;
	R13 = L13;
	R21 = L21;
	L22 = R22;
	L23 = R23;
	L31 = R31;
	L32 = R32;
	L33 = R33;

	RBK = TRX;
	GBK = TRY;
	BBK = TRZ;

	((int*)m)[0] = t0;
	((int*)m)[1] = t1;
	((int*)m)[2] = t2;
	((int*)m)[3] = t3;
	((int*)m)[4] = t4;
	((int*)m)[5] = t5;
	((int*)m)[6] = t6;
	((int*)m)[7] = t7;
}

void iPushMatrix0()//76D3C(<), ?(<) (F)
{
	UNIMPLEMENTED();
}

void iPushMatrix()//76D3C(<), ?(<) (F)
{
	int t0 = L11 | (L12 << 16);
	int t1 = L13 | (L21 << 16);
	int t2 = L22 | (L23 << 16);
	int t3 = L31 | (L32 << 16);
	int t4 = L33;
	int t5 = RBK;
	int t6 = GBK;
	int t7 = BBK;

	++iMatrix;

	((int*)iMatrix)[0] = t0;
	((int*)iMatrix)[1] = t1;
	((int*)iMatrix)[2] = t2;
	((int*)iMatrix)[3] = t3;
	((int*)iMatrix)[4] = t4;
	((int*)iMatrix)[5] = t5;
	((int*)iMatrix)[6] = t6;
	((int*)iMatrix)[7] = t7;

	mPushMatrix();
}

void iPopMatrix0()
{
	UNIMPLEMENTED();
}

void iPopMatrix()//76D8C(<), ?(<)
{
	UNIMPLEMENTED();
}

void mPushMatrix0()//764D0 (F)
{
	UNIMPLEMENTED();
}

void mmPushMatrix(int* fp)//81BBC(<) (F)
{
	int* a0 = &fp[20];

	int t0 = R11 | (R12 << 16);
	int t1 = R13 | (R21 << 16);
	int t2 = R22 | (R23 << 16);
	int t3 = R31 | (R32 << 16);
	int t4 = R33;
	int t5 = TRX;
	int t6 = TRY;
	int t7 = TRZ;

	a0 += 8;

	a0[0] = t0;
	a0[1] = t1;
	a0[2] = t2;
	a0[3] = t3;
	a0[4] = t4;
	a0[5] = t5;
	a0[6] = t6;
	a0[7] = t7;

	fp[20] = (int)a0;
}

void SetRoomBounds(tr_room_portal* portal, int room_number, struct room_info* parent)
{
	UNIMPLEMENTED();
}

void GetRoomBoundsAsm(short room_number)//77E70(<), 79EB4(<) ///@TODO check if in right file
{
	int scratchPad[256];
	struct room_info* r;//a0
	int t1;
	int t2;
	int t3;
	int s2;
	int s3;
	int a0;
	short* s4;
	int s6;
	int at;
	int t5;
	int t7;
	int t4;
	int t6;
	int t8;
	int v0;
	int s5;
	int fp = 0;
	int t0;
	short* s7;
	int a1;
	short* a2;
	int a3;
	struct room_info* a33;
	int* t44;
	int v1;
	int t9;
	int* t55;
	short* t00;

	S_MemSet((char*)& scratchPad[0], 0, 1024);

	s2 = 0;
	s3 = 1;
	s4 = (short*)&scratchPad[63];
	s5 = 0;
	fp = outside;
	((char*)&scratchPad)[0] = room_number;
	r = &room[room_number];

	((int*)&r->test_left)[0] = 0x1FF0000;
	((int*)&r->test_top)[0] = 0xEF0000;
	r->bound_active = 2;

	//t6 = &CamPos
	t1 = TRX;///@BEGIN OPT1
	t2 = TRY;
	t3 = TRZ;

	scratchPad[44] = t1;
	scratchPad[45] = t2;
	scratchPad[46] = t3;///@END OPT1

	t1 = CamPos.x;
	t2 = CamPos.y;
	t3 = CamPos.z;

	scratchPad[47] = t1;
	scratchPad[48] = t2;
	scratchPad[49] = t3;

loc_77F18:
	if (s2 != s3)
	{
		//t0 = ((char*)&scratchPad)[s2]
		s6 = ((unsigned char*)& scratchPad)[s2];
		s2++;
		s2 &= 0x7F;
		
		r = &room[s6];

		v0 = r->bound_active - 2;

		t1 = ((int*)&r->left)[0];
		t3 = ((int*)&r->top)[0];
		t5 = ((int*)&r->test_left)[0];
		t7 = ((int*)&r->test_top)[0];

		t2 = t1 >> 16;
		t1 &= 0xFFFF;

		t4 = t3 >> 16;
		t3 &= 0xFFFF;

		t6 = t5 >> 16;
		t5 &= 0xFFFF;

		t8 = t7 >> 16;
		t7 &= 0xFFFF;

		if (t5 < t1)
		{
			t1 = t5;
		}
		
		//loc_77F84
		if (t6 > t2)
		{
			t2 = t6;
		}//loc_77F90

		if (t7 < t3)
		{
			t3 = t7;
		}//loc_77F9C

		t6 = t2 << 16;
		if (t8 > t4)
		{
			t4 = t8;
		}//loc_77FA8

		t5 = t1 | t6;
		t6 = t4 << 16;
		t6 |= t3;

		((int*)&r->left)[0] = t5;
		((int*)&r->top)[0] = t6;

		if (!((r->bound_active - 2) & 1))
		{
			*s4++ = s6;
			s5++;
		}//loc_77FD4

		r->bound_active = (r->bound_active - 2) | 1;
		fp |= (r->flags & 8);

		s7 = r->door;

		t0 = r->x;
		t1 = r->y;
		if (s7 == NULL)
		{
			goto loc_77F18;
		}

		t2 = r->z;

		t3 = t0 >> 15;
		if (t0 < 0)
		{
			t0 = -t0;
			t3 = t0 >> 15;
			t0 &= 0x7FFF;
			t3 = -t3;
			t0 = -t0;
		}
		else
		{
			t0 &= 0x7FFF;
		}

		//loc_7801C
		t4 = t1 >> 15;
		if (t1 < 0)
		{
			t1 = -t1;
			t4 = t1 >> 15;
			t1 &= 0x7FFF;
			t4 = -t4;
			t1 = -t1;
		}
		else
		{
			t1 &= 0x7FFF;
		}

		//loc_78040
		t5 = t2 >> 15;
		if (t2 < 0)
		{
			t2 = -t2;
			t5 = t2 >> 15;
			t2 &= 0x7FFF;
			t5 = -t5;
			t2 = -t2;
		}
		else
		{
			t2 &= 0x7FFF;
		}

		//loc_78064
		IR1 = t3;
		IR2 = t4;
		IR3 = t5;

		docop2(0x41E012);

		t3 = ((int*)&scratchPad)[44];
		t4 = ((int*)&scratchPad)[45];
		t5 = ((int*)&scratchPad)[46];

		TRX = t3;
		TRY = t4;
		TRZ = t5;

		t3 = MAC1;
		t4 = MAC2;
		t5 = MAC3;

		IR1 = t0;
		IR2 = t1;
		IR3 = t2;

		docop2(0x498012);

		t0 = t3 << 3;
		if (t3 < 0)
		{
			t3 = -t3;
			t3 <<= 3;
			t0 = -t3;
		}

		t1 = t4 << 3;
		if (t4 < 0)
		{
			t4 = -t4;
			t4 <<= 3;
			t1 = -t4;
		}

		t2 = t5 << 3;
		if (t5 < 0)
		{
			t5 = -t5;
			t5 <<= 3;
			t2 = -t5;
		}

		//loc_780E8
		t3 = MAC1;
		t4 = MAC2;
		t5 = MAC3;

		t0 += t3;
		t1 += t4;
		t2 += t5;

		TRX = t0;
		TRY = t1;
		TRZ = t2;

		v0 = *s7++;

		//loc_78114
		do
		{
			a1 = *s7++;
			t0 = s7[0];

			t1 = r->x;
			t2 = s7[3];

			if (t0 != 0)
			{
				t3 = scratchPad[47];
				t1 += t2;
				t1 -= t3;
				t0 ^= t1;

				if (t1 != 0)
				{
					a2 = s7;

					if (t0 < 0)
					{
						goto loc_781A8;
					}
				}
			}
			else
			{
				//loc_7814C
				t0 = s7[1];
				t1 = r->y;
				t2 = s7[4];

				if (t0 != 0)
				{
					t3 = scratchPad[48];
					t1 += t2;
					t1 -= t3;
					t0 ^= t1;

					if (t1 != 0)
					{
						a2 = s7;

						if (t0 < 0)
						{
							goto loc_781A8;
						}
					}
				}
				else
				{
					//loc_7817C
					t0 = s7[2];
					t1 = r->z;
					t2 = s7[5];

					if (t0 != 0)
					{
						t3 = scratchPad[49];
						t1 += t2;
						t1 -= t3;
						t0 ^= t1;

						if (t1 != 0)
						{
							a2 = s7;
							if (t0 < 0)
							{
							loc_781A8:
								a33 = &room[a1];
								t0 = ((int*)& a33->left)[0];
								t2 = ((int*)& r->test_left)[0];
								t4 = ((int*)& a33->top)[0];
								t6 = ((int*)& r->test_top)[0];

								t1 = t0 >> 16;
								t0 &= 0xFFFF;

								t3 = t2 >> 16;
								t2 &= 0xFFFF;

								t5 = t4 >> 16;
								t4 &= 0xFFFF;

								t7 = t6 >> 16;
								t6 &= 0xFFFF;

								if (t0 >= t2 || t1 < t3 || t4 >= t6 || t5 < t7)
								{
									//loc_78208
									t0 = t3;
									t1 = t2;
									t2 = t7;
									t3 = t6;
									t44 = &scratchPad[32];
									t5 = 0;
									t6 = 0;
									v1 = 3;

								loc_78228:
									t7 = ((unsigned short*)a2)[3];
									t9 = ((unsigned short*)a2)[4];
									t8 = ((unsigned short*)a2)[5];
									t9 <<= 16;
									t7 |= t9;

									VX0 = t7 & 0xFFFF;
									VY0 = t7 >> 16;
									VZ0 = t8;
									a2 += 3;

									docop2(0x480012);

									t7 = IR1;
									t8 = IR2;
									t9 = IR3;

									docop2(0x180001);
									t44[0] = t7;
									t44[1] = t8;
									t44[2] = t9;
									t44 += 3;

									if (t9 < 0)
									{
										t5++;
										goto loc_782C8;
									}

									//loc_78278
									t7 = SXY2;
									t8 = t7 >> 16;

									if (t9 > 0x4FFF)
									{
										t6++;
									}

									//loc_7828C
									t7 <<= 16;
									t7 >>= 16;

									if (t7 < t0)
									{
										t0 = t7;
									}

									//loc_782A4
									if (t7 > t1)
									{
										t1 = t7;
									}//loc_782B0

									if (t8 < t2)
									{
										t2 = t8;
									}
									//loc_782BC
									if (t8 > t3)
									{
										t3 = t8;
									}

								loc_782C8:
									if (v1-- != 0)
									{
										goto loc_78228;
									}


									t44 = &scratchPad[32];
									v1 = 3;
									if (t5 != 4 && t6 != 4)
									{
										t55 = &t44[9];

										if (t5 != 0)
										{
											//loc_782EC
											do
											{
												t6 = t44[2];
												t7 = t55[2];

												t8 = (t6 < 1) ? 1 : 0 ^ (t7 < 1) ? 1 : 0;
												t6 = t44[0];

												if (t8 != 0)
												{
													t7 = t55[0];
													t8 = (t6 < 0) ? 1 : 0 & (t7 < 0) ? 1 : 0;

													//t8 = 0 < t6 ? 1 : 0
													if (t8 != 0)
													{
														t0 = 0;
														goto loc_7833C;
													}
													else
													{
														//loc_78328
														t8 = (0 < t6) ? 1 : 0 & (0 < t7) ? 1 : 0;
														t1 = 0x1FF;
														if (t8 == 0)
														{
															t0 = 0;
														}
loc_7833C:
														t6 = t44[1];
														t7 = t55[1];
														t8 = (t6 < 0) ? 1 : 0 & (t7 < 0) ? 1 : 0;

														//t8 = 0 < t6 ? 1 : 0
														if (t8 != 0)
														{
															t2 = 0;
														}
														else
														{
															//loc_78360
															t8 = (0 < t6) ? 1 : 0 & (0 < t7) ? 1 : 0;
															t3 = 239;
															if (t8 == 0)
															{
																t2 = 0;
															}
														}
													}
												}
												//loc_78374
												t55 = t44;
												t44 += 3;

											} while (v1--);
										}
										//loc_78384
										t4 = ((int*)& r->test_left)[0];
										t6 = ((int*)& r->test_top)[0];

										t5 = t4 >> 16;
										t4 &= 0xFFFF;

										t7 = t6 >> 16;
										t6 &= 0xFFFF;

										if (t0 < t4)
										{
											t0 = t4;
										}

										//loc_783AC
										if (t5 < t1)
										{
											t1 = t5;
										}
										//loc_783B8
										if (t2 < t6)
										{
											t2 = t6;
										}
										//loc_783C4
										at = t0 - t1;
										if (t7 < t3)
										{
											t3 = t7;
										}
										//loc_783D0
										if (at < 0)
										{
											at = t2 - t3;
											v1 = a33->bound_active;
											if (at < 0)
											{
												at = v1 & 2;
												v1 |= 2;
												if (at == 0)
												{
													((char*)& scratchPad)[s3] = a1;
													s3++;
													s3 &= 0x7F;
													t1 <<= 16;
													t0 |= t1;
													t3 <<= 16;
													t2 |= t3;
													((int*)&a33->test_left)[0] = t0;
													((int*)&a33->test_top)[0] = t2;
													a33->bound_active = v1;
												}
												else
												{
													//loc_7841C
													t4 = ((int*)& a33->test_left)[0];
													t6 = ((int*)& a33->test_top)[0];
													t5 = t4 >> 16;
													t4 &= 0xFFFF;
													t7 = t6 >> 16;
													t6 &= 0xFFFF;

													if (t0 < t4)
													{
														t4 = t0;
													}//loc_78444

													if (t5 < t1)
													{
														t5 = t1;
													}
													//loc_78450
													if (t2 < t6)
													{
														t6 = t2;
													}

													//loc_7845C
													t5 <<= 16;
													if (t7 < t3)
													{
														t7 = t3;
													}
													//loc_78468
													t4 |= t5;
													t7 <<= 16;
													t6 |= t7;

													((int*)&a33->test_left)[0] = t4;
													((int*)&a33->test_top)[0] = t6;
												}
											}//loc_7847C
										}//loc_7847C
									}//loc_7847C
								}//loc_7847C
							}//loc_7847C
						}//loc_7847C
					}//loc_7847C
				}//loc_7847C
			}
			//loc_7847C
			v0--;
			s7 += 15;
		}while (v0 > 0);

		goto loc_77F18;

	}//loc_78490

	t00 = &draw_rooms[0];
	s4 = (short*)&scratchPad[63];
	v0 = s5 - 1;
	s5 = 0;

	//loc_784A4
	do
	{
		a1 = *s4++;
		*t00++ = a1;
		s5++;
	} while (v0-- > 0);

	number_draw_rooms = s5;
	outside = fp;
}

void phd_GetVectorAngles(long dx, long dy, long dz, short* angles)//77928 (F)
{
	int t0, t1, t2;

	t0 = dx;
	t1 = dy;
	t2 = dz;

	angles[0] = phd_atan_asm(dz, dx);
	goto loc_7795C;

loc_77950:
	t0 >>= 2;
	t1 >>= 2;
	t2 >>= 2;

loc_7795C:
	if (((t0 << 16) >> 16) != t0)
	{
		goto loc_77950;
	}

	if (((t1 << 16) >> 16) != t1)
	{
		goto loc_77950;
	}

	if (((t2 << 16) >> 16) != t2)
	{
		goto loc_77950;
	}

	IR1 = t0;
	IR2 = t2;

	docop2(0xA00428);

	int v0 = phd_atan_asm(mSqrt(MAC1 + MAC2), t1);

	if (t1 > 0 && (v0 << 16) > 0 || t1 < 0 && (v0 << 16) < 0)
	{
		v0 = -v0;
	}

	angles[1] = v0;
}

void phd_LookAt(long xsrc, long ysrc, long zsrc, long xtar, long ytar, long ztar, long roll)//(F)
{
	short temp;

	CamPos.x = xsrc;
	CamPos.y = ysrc;
	CamPos.z = zsrc;

	viewer.x_pos = xsrc;
	viewer.y_pos = ysrc;
	viewer.z_pos = zsrc;
	viewer.z_rot = roll;

	phd_GetVectorAngles(xtar - xsrc, ytar - ysrc, ztar - zsrc, &viewer.x_rot);

	temp = viewer.y_rot;
	viewer.y_rot = viewer.x_rot;
	viewer.x_rot = temp;

	phd_GenerateW2V(&viewer);
}

void phd_GenerateW2V(struct PHD_3DPOS* view)//(F)
{
	int t0, t1, t2, t3, t4, t5, t6, v0, v1, a0, a1, a2, a3, at;

	a2 = view->x_rot;
	v1 = view->y_rot;

	t0 = SIN(a2);
	t2 = SIN(v1);

	a1 = view->z_rot;
	t4 = (t0 * t2) >> 12;

	t3 = COS(v1);
	t1 = SIN(a1);

	t5 = t4 * t1;

	phd_mxptr = &matrix_stack[0];

	v1 = t0 * t3;
	v0 = COS(a2);
	t0 = -t0;
	matrix_stack[9] = t0;
	w2v_matrix[9] = t0;

	t6 = v0 * t1;
	a1 = COS(a1);

	v1 >>= 12;
	t6 >>= 12;
	matrix_stack[1] = t6;
	w2v_matrix[1] = t6;

	t6 = (v1 * t1) >> 12;
	a3 = (t2 * a1) >> 12;
	t6 -= a3;

	matrix_stack[2] = t6;
	w2v_matrix[2] = t6;

	t6 = t4 * a1;

	a3 = view->x_pos;
	t4 = view->y_pos;
	a0 = view->z_pos;

	matrix_stack[3] = a3;
	w2v_matrix[3] = a3;
	
	matrix_stack[7] = t4;
	w2v_matrix[7] = t4;

	a3 = t3 * t1;

	matrix_stack[11] = a0;
	w2v_matrix[11] = a0;

	t4 = (v0 * a1) >> 14;
	t0 = (v0 * a1) >> 12;

	w2v_matrix[5] = t0;
	a2 = (v0 * t2) >> 12;

	t0 -= t4;

	matrix_stack[8] = a2;
	w2v_matrix[8] = a2;
	matrix_stack[5] = t0;

	a2 = (v0 * t3) >> 12;
	t6 >>= 12;

	matrix_stack[10] = a2;
	w2v_matrix[10] = a2;

	t0 = v1 * a1;
	a3 >>= 12;
	t6 -= a3;

	a2 = t2 * t1;
	w2v_matrix[4] = t6;
	at = t6 >> 2;
	t6 -= at;
	matrix_stack[4] = t6;

	t0 >>= 12;
	v0 = a2 >> 12;
	t0 += v0;
	w2v_matrix[6] = t0;
	at = t0 >> 2;
	t0 -= at;
	matrix_stack[6] = t0;
	v0 = t5 >> 12;

	v1 = (t3 * a1) >> 12;
	v0 += v1;
	matrix_stack[0] = v0;
	w2v_matrix[0] = v0;
}

long phd_atan_asm(long x, long y)// (F)
{
	int a2, a3, v0;

	if (x == 0 && y == 0)
	{
		return 0;
	}

	a2 = 0;
	if (x < 0)
	{
		a2 = 4;
		x = -x;
	}
	//loc_77A64
	if (y < 0)
	{
		a2 += 2;
		y = -y;
	}

	v0 = x;
	if (x < y)
	{
		a2 += 1;
		x = y;
		y = v0;
	}
	else
	{
		//loc_77A90
		goto loc_77A98;
	}

loc_77A90:
	y >>= 1;
	x >>= 1;

loc_77A98:
	v0 = (y << 16) >> 16;
	if (v0 != y)
	{
		goto loc_77A90;

	}//loc_77A90

	v0 = y << 11;
	a3 = (v0 / x);

	v0 = atanOctantTab[a2];
	x = atanTab[a3];

	v0 = x + v0;
	if (v0 < 0)
	{
		v0 = -v0;
	}

	return v0;
}

void mRotBoundingBoxNoPersp(short* bounds, short* tbounds)
{
	UNIMPLEMENTED();
}

void iTranslateXYZ2(short x, short y, short z, short x2, short y2, short z2)//7709C (F)
{
	int t0;
	int t1;
	int t2;
	int t3;
	int t4;
	int t5;
	int t6;
	int a3;
	int a1;
	int a2;
	int t7;
	int t8;

	mTranslateXYZ(x, y, z);

	t0 = x2 >> 15;
	if (x2 < 0)
	{
		x2 = -x2;
		t0 = x2 >> 15;
		x2 &= 0x7FFF;
		t0 = -t0;
		x2 = -x2;
	}
	else
	{
		//loc_770D0
		x2 &= 0x7FFF;
	}

	t1 = y2 >> 15;
	//loc_770D4
	if (y2 < 0)
	{
		y2 = -y2;
		t1 = y2 >> 15;
		y2 &= 0x7FFF;
		t1 = -t1;
		y2 = -y2;
	}
	else
	{
		//loc_770F4
		y2 &= 0x7FFF;
	}

	t2 = z2 >> 15;
	if (z2 < 0)
	{
		z2 = -z2;
		t2 = z2 >> 15;
		z2 &= 0x7FFF;
		t2 = -t2;
		z2 = -z2;
	}
	else
	{
		//loc_77118
		z2 &= 0x7FFF;
	}

	IR1 = t0;
	IR2 = t1;
	IR3 = t2;

	docop2(0x43E012);

	//v0 = iMatrix
	t6 = MAC1;
	a3 = IR1;
	a1 = IR2;
	a2 = IR3;
	t7 = MAC2;
	t8 = MAC3;

	docop2(0x4BE012);

	t3 = t6 << 3;
	if (t6 < 0)
	{
		t6 = -t6;
		t6 <<= 3;
		t3 = -t6;
	}
	//loc_77164
	t4 = t7 << 3;
	if (t7 < 0)
	{
		t7 = -t7;
		t7 <<= 3;
		t4 = -t7;
	}
	//loc_77178
	t5 = t8 << 3;
	if (t8 < 0)
	{
		t8 = -t8;
		t8 <<= 3;
		t5 = -t8;
	}
	
	//loc_7718C
	t6 = MAC1;
	t7 = MAC2;
	t8 = MAC3;

	t3 += t6;
	t4 += t7;
	t5 += t8;

	t0 = RBK;
	t1 = GBK;
	t2 = BBK;

	t0 += t3;
	t1 += t4;
	t2 += t5;

	RBK = t0;
	GBK = t1;
	BBK = t2;

	iMatrix->tx = t0;
	iMatrix->ty = t1;
	iMatrix->tz = t2;
}

void iTranslateXYZ(long x, long y, long z)//77090 (F)
{
	iTranslateXYZ2(x, y, z, x, y, z);
}

long GetFrames(struct ITEM_INFO* item/*$a0*/, short* frames[]/*a1*/, int* rate/*$a2*/)//8582C
{
	struct ANIM_STRUCT* anim;
	int t1;
	int t2;

	anim = &anims[item->anim_number];

	*rate = (anim->interpolation & 0xFF);
	t1 = (item->frame_number - anim->frame_base) / (anim->interpolation & 0xFF);
	t2 = (item->frame_number - anim->frame_base) % (anim->interpolation & 0xFF);

	frames[0] = &anim->frame_ptr[t1 * (anim->interpolation >> 8)];
	frames[1] = &anim->frame_ptr[(t1 * (anim->interpolation >> 8)) + (anim->interpolation >> 8)];

	if (t2 == 0)
	{
		return 0;
	}

	//loc_8589C
	if (anim->frame_end < (t1 * (anim->interpolation & 0xFF)) + (anim->interpolation & 0xFF))
	{
		*rate = anim->frame_end - ((t1 * (anim->interpolation & 0xFF)) + (anim->interpolation & 0xFF)) - (anim->interpolation & 0xFF);
	}

	return t2;
}