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

void mQuickW2VMatrix()//77AEC(<), 79B30(<)
{
	MatrixSP = 0;
	Matrix = &MatrixStack[0];

	((int*)&MatrixStack)[0] = ((short*)&phd_mxptr)[0] | ((short*)&phd_mxptr)[2] << 16;
	((int*)&MatrixStack)[1] = ((short*)&phd_mxptr)[4] | ((short*)&phd_mxptr)[8] << 16;
	((int*)&MatrixStack)[2] = ((short*)&phd_mxptr)[10] | ((short*)&phd_mxptr)[12] << 16;
	((int*)&MatrixStack)[3] = ((short*)&phd_mxptr)[16] | ((short*)&phd_mxptr)[18] << 16;

	R11 = ((short*)&phd_mxptr)[0];
	R12 = ((short*)&phd_mxptr)[2] << 16;

	R13 = ((short*)&phd_mxptr)[4];
	R21 = ((short*)&phd_mxptr)[8] << 16;

	R22 = ((short*)&phd_mxptr)[10];
	R23 = ((short*)&phd_mxptr)[12] << 16;

	R31 = ((short*)&phd_mxptr)[16];
	R32 = ((short*)&phd_mxptr)[18] << 16;

	((short*)&MatrixStack)[8] = ((short*)&phd_mxptr)[20];
	((short*)&MatrixStack)[10] = ((short*)&phd_mxptr)[6];
	((short*)&MatrixStack)[12] = ((short*)&phd_mxptr)[14];
	((short*)&MatrixStack)[14] = ((short*)&phd_mxptr)[22];

	R33 = ((short*)&phd_mxptr)[20];
	TRX = ((short*)&phd_mxptr)[6];
	TRY = ((short*)&phd_mxptr)[14];
	TRZ = ((short*)&phd_mxptr)[22];

	CamGTE.m00 = ((short*)&w2v_matrix)[0];
	CamGTE.m01 = ((short*)&w2v_matrix)[2];
	CamGTE.m02 = ((short*)&w2v_matrix)[4];
	CamGTE.m10 = ((short*)&w2v_matrix)[8];
	CamGTE.m11 = ((short*)&w2v_matrix)[10];
	CamGTE.m12 = ((short*)&w2v_matrix)[12];
	CamGTE.m20 = ((short*)&w2v_matrix)[16];
	CamGTE.m21 = ((short*)&w2v_matrix)[18];
	CamGTE.m22 = ((short*)&w2v_matrix)[20];
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

	t0 = R11;
	t1 = R13;
	t2 = R22;
	v0 = R31;
	v1 = R33;

	R11 = ((((t0 << 16) >> 16) * sx) >> 12) & 0xFFFF;
	R12 = ((((t0 >> 16) * sy) >> 12) << 16);
	R13 = ((((t1 << 16) >> 16) * sz) >> 12) & 0xFFFF;
	R21 = (((t1 >> 16) * sx) >> 12) << 16;
	R22 = ((((t2 << 16) >> 16) * sy) >> 12) & 0xFFFF;
	R23 = (((t2 >> 16) * sz) >> 12) << 16;
	R31 = ((((v0 << 16) >> 16) * sx) >> 12) & 0xFFFF;
	R32 = (((v0 >> 16)  * sy) >> 12) << 16;
	R33 = ((((v1 << 16) >> 16) * sz) >> 12);

	if (bStoreInMatrix)
	{
		Matrix->m00 = R12;
		Matrix->m01 = R11;
		Matrix->m02 = R21;
		Matrix->m10 = R13;
		Matrix->m11 = R23;
		Matrix->m12 = R22;
		Matrix->m20 = R32;
		Matrix->m21 = R31;
		Matrix->m22 = R33;
	}//locret_77E68
}

void mPushMatrix()//764D0(<), 78514(<) (F)
{
	++Matrix;
	Matrix->m00 = R12;
	Matrix->m01 = R11;
	Matrix->m02 = R21;
	Matrix->m10 = R13;
	Matrix->m11 = R23;
	Matrix->m12 = R22;
	Matrix->m20 = R32;
	Matrix->m21 = R31;
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
	UNIMPLEMENTED();
}

void mTranslate()//76558(<) (!)
{
	UNIMPLEMENTED();
}

void mTranslateAbsXYZ(long x, long y, long z)
{
	mTranslateXYZ(x - MatrixStack[0].tx, y - MatrixStack[0].ty, z - MatrixStack[0].tz);
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
	int t5;
	int t0;
	int t6;
	int* rcossin_ptr = (int*)&rcossin_tbl[0];

	rx = (rx >> 2) & 0x3FFC;
	if (rx == 0)
	{
		return;
	}

	//loc_766B4 :
	t5 = rcossin_ptr[rx];//sin and cos?
	//t7 = 0xFFFF0000
	t6 = 0xFFFF0000 & t5;
	VX0 = 0xFFFF0000 & t5;
	VZ0 = rcossin_ptr[rx];

#if 0
	cfc2    t0, r0
	cfc2    t1, r1
	cfc2    t3, r3
	cop2    0x486012
	srl     t6, t5, 16
	sll     t5, 16
	neg     t5, t5
	mtc2    t5, r2
	mtc2    t6, r3
	andi    t0, 0xFFFF
	and t1, t7
	andi    t3, 0xFFFF
	mfc2    t4, r25
	mfc2    t2, r26
	mfc2    t5, r27
	cop2    0x48E012
	sll     t4, 16
	or t0, t4
	andi    t2, 0xFFFF
	sll     t5, 16
	or t3, t5
	mfc2    t5, r25
	mfc2    t6, r26
	mfc2    t4, r27
	andi    t5, 0xFFFF
	or t1, t5
	sll     t6, 16
	j       SetRotation
	or t2, t6
#endif
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

void SetRoomBounds(tr_room_portal* portal, int room_number, struct room_info* parent)
{
	UNIMPLEMENTED();
}

void GetRoomBoundsAsm(short room_number)//77E70(<), 79EB4(<) ///@TODO check if in right file
{
	UNIMPLEMENTED();
}

void phd_GetVectorAngles(long dx, long dy, long dz, short* angles)//77928
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

void phd_LookAt(long xsrc, long ysrc, long zsrc, long xtar, long ytar, long ztar, long roll)
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

void phd_GenerateW2V(struct PHD_3DPOS* view)
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
