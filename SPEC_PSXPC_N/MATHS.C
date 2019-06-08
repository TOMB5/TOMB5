#include "MATHS.H"

#include "LOAD_LEV.H"
#include "SPECIFIC.H"

#include <INLINE_C.H>
#include "3D_GEN.H"
#include "CAMERA.H"
#include "DRAW.H"
#include "GPU.H"
#include "GTEREG.H"

void mQuickW2VMatrix()//77AEC(<), 79B30(<)
{
	//v1 = phd_mxptr
	//a0 = &MatrixStack[0]
	MatrixSP = 0;
	Matrix = &MatrixStack[0];
#if 0
					   sw      a0, Matrix - GP_ADDR(gp)
					   lhu     at, 0(v1)
					   lhu     v0, 4(v1)
					   lhu     a1, 8(v1)
					   lhu     a2, 0x10(v1)
					   sll     v0, 16
					   or at, v0
					   sll     a2, 16
					   or a1, a2
					   lhu     a3, 0x14(v1)
					   lhu     t0, 0x18(v1)
					   lhu     t1, 0x20(v1)
					   lhu     t2, 0x24(v1)
					   sll     t0, 16
					   or a3, t0
					   sll     t2, 16
					   or t1, t2
					   sw      at, 0(a0)
					   sw      a1, 4(a0)
					   sw      a3, 8(a0)
					   sw      t1, 0xC(a0)
					   ctc2    at, r0
					   ctc2    a1, r1
					   ctc2    a3, r2
					   ctc2    t1, r3
					   lhu     at, 0x28(v1)
					   lw      v0, 0xC(v1)
					   lw      a1, 0x1C(v1)
					   lw      a2, 0x2C(v1)
					   sh      at, 0x10(a0)
					   sw      v0, 0x14(a0)
					   sw      a1, 0x18(a0)
					   sw      a2, 0x1C(a0)
					   ctc2    at, r4
					   ctc2    v0, r5
					   ctc2    a1, r6
					   ctc2    a2, r7
					   lhu     v0, w2v_matrix + 0x0 - GP_ADDR(gp)
					   lhu     v1, w2v_matrix + 0x4 - GP_ADDR(gp)
					   lhu     a0, w2v_matrix + 0x8 - GP_ADDR(gp)
					   lhu     a1, w2v_matrix + 0x10 - GP_ADDR(gp)
					   lhu     a2, w2v_matrix + 0x14 - GP_ADDR(gp)
					   lhu     a3, w2v_matrix + 0x18 - GP_ADDR(gp)
					   lhu     t0, w2v_matrix + 0x20 - GP_ADDR(gp)
					   lhu     t1, w2v_matrix + 0x24 - GP_ADDR(gp)
					   lhu     t2, w2v_matrix + 0x28 - GP_ADDR(gp)
					   sh      v0, CamGTE + 0x0 - GP_ADDR(gp)
					   sh      v1, CamGTE + 0x2 - GP_ADDR(gp)
					   sh      a0, CamGTE + 0x4 - GP_ADDR(gp)
					   sh      a1, CamGTE + 0x6 - GP_ADDR(gp)
					   sh      a2, CamGTE + 0x8 - GP_ADDR(gp)
					   sh      a3, CamGTE + 0xA - GP_ADDR(gp)
					   sh      t0, CamGTE + 0xC - GP_ADDR(gp)
					   sh      t1, CamGTE + 0xE - GP_ADDR(gp)
					   jr      ra
					   sh      t2, CamGTE + 0x10 - GP_ADDR(gp)
#endif
}

void gte_sttr(struct PHD_VECTOR* vec)
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

	return value << v0;
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

	return value << v0;
}

void ScaleCurrentMatrix(long a0, long sx, long sy, long sz)
{
	UNIMPLEMENTED();
}

void mPushMatrix()//764D0(<), 78514(<) (F) (START)
{
	++Matrix;
	Matrix->m00 = Matrix[-1].m00;
	Matrix->m01 = Matrix[-1].m01;
	Matrix->m02 = Matrix[-1].m02;
	Matrix->m10 = Matrix[-1].m10;
	Matrix->m11 = Matrix[-1].m11;
	Matrix->m12 = Matrix[-1].m12;
	Matrix->m20 = Matrix[-1].m20;
	Matrix->m21 = Matrix[-1].m21;
	Matrix->m22 = Matrix[-1].m22;
}

void mPopMatrix()//76520(<), 78564(<) (F)
{
	UNIMPLEMENTED();
}

void mUnitMatrix()
{
	UNIMPLEMENTED();
}

void mPushUnitMatrix()//76534(<), 78578(<) (! Incorrect, redo, ida asm is bad)
{
	UNIMPLEMENTED();
}

void mTranslate()//76558(<) (!)
{
	UNIMPLEMENTED();
}

void mTranslateAbsXYZ(long x, long y, long z)
{
	UNIMPLEMENTED();
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

void mRotX(long rx)// (F)
{
	UNIMPLEMENTED();
}

void mRotY(long ry)//76744 (F)
{
	UNIMPLEMENTED();
}

void mRotYXZ(short y, short x, short z)//767E8 (F)
{
	UNIMPLEMENTED();
}


void mRotZ(long rz)//76804 (F)
{
	UNIMPLEMENTED();
}

void mRotSuperPackedYXZ(short** a0, long a1)//768BC
{
	UNIMPLEMENTED();
}

void mRotPackedYXZ(long yxz)//7693C (F)
{
	UNIMPLEMENTED();
}

void SetRotation()//7696C
{
	UNIMPLEMENTED();
}

void setrot(struct MATRIX3D* m, long m00, long m02, long m11, long m20, long m22)//76970 TOCHECK
{
	UNIMPLEMENTED();
}

void mLoadMatrix(struct MATRIX3D* m)//7699C(<), 789E0(<) TOCHECK
{
	UNIMPLEMENTED();
	return;
}

//Note: Original code is less optimal than this implementation.
void mCopyMatrix(struct MATRIX3D* m)//769E4(<), 78A28(<) (F) TOCHECK
{
	UNIMPLEMENTED();
}

void ASM_GetBounds()//76A28
{
	UNIMPLEMENTED();
}

void GetBounds()//76A28
{
	UNIMPLEMENTED();
}

void mSetTrans(long x, long y, long z)//76AF4(<), 78B38(<) TOCHECK
{
	UNIMPLEMENTED();
}

void mClipBoundingBox(short* bounds)//76B14
{
	UNIMPLEMENTED();
}

void InitInterpolation(long frac, long rate, struct MATRIX3D* m)//76CB4 
{
	UNIMPLEMENTED();
}

void iPushMatrix0()//76D3C(<), ?(<) (F)
{
	UNIMPLEMENTED();
}

void iPushMatrix(struct MATRIX3D* m)//81E60(<), ?(<) (F)
{
	UNIMPLEMENTED();
}

void iPopMatrix0()
{
	UNIMPLEMENTED();
}

void iPopMatrix(struct MATRIX3D* m, struct MATRIX3D* m2)//76D8C(<), ?(<) TOCHECK
{
	UNIMPLEMENTED();
}

void mPushMatrix0()//764D0 (F)
{
	UNIMPLEMENTED();
}

void mmPushMatrix(struct MATRIX3D* m)//81BBC(<) (F)
{
	UNIMPLEMENTED();
}

int bound_start = 0;
int bound_end = 0;
int bound_list[128];

void SetRoomBounds(tr_room_portal* portal, int room_number, struct room_info* parent)
{
	UNIMPLEMENTED();
}

void GetRoomBoundsAsm(short room_number)//77E70(<), 79EB4(<) ///@TODO check if in right file
{
	UNIMPLEMENTED();
}

void phd_GetVectorAngles(long dx, long dy, long dz, short* angles)
{
	UNIMPLEMENTED();
}


void phd_LookAt(long xsrc, long ysrc, long zsrc, long xtar, long ytar, long ztar, long roll)
{
	UNIMPLEMENTED();
}

long phd_atan_asm(long x, long y)// (F)
{
	UNIMPLEMENTED();
}

void mRotBoundingBoxNoPersp(short* bounds, short* tbounds)
{
	UNIMPLEMENTED();
}
