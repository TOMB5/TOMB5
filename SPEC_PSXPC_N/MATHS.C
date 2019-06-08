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
	phd_mxptr = phd_mxptr;
	//v1 = phd_mxptr
	//a0 = MatrixStack
	MatrixSP = 0;
	Matrix = &MatrixStack[0];
	
	//at = ((unsigned short*)phd_mxptr)[0];
#if 0
		lhu     $at, 0($v1)
		lhu     $v0, 4($v1)
		lhu     $a1, 8($v1)
		lhu     $a2, 0x10($v1)
		sll     $v0, 16
		or $at, $v0
		sll     $a2, 16
		or $a1, $a2
		lhu     $a3, 0x14($v1)
		lhu     $t0, 0x18($v1)
		lhu     $t1, 0x20($v1)
		lhu     $t2, 0x24($v1)
		sll     $t0, 16
		or $a3, $t0
		sll     $t2, 16
		or $t1, $t2
		sw      $at, 0($a0)
		sw      $a1, 4($a0)
		sw      $a3, 8($a0)
		sw      $t1, 0xC($a0)
		ctc2    $at, $0
		ctc2    $a1, $1
		ctc2    $a3, $2
		ctc2    $t1, $3
		lhu     $at, 0x28($v1)
		lw      $v0, 0xC($v1)
		lw      $a1, 0x1C($v1)
		lw      $a2, 0x2C($v1)
		sh      $at, 0x10($a0)
		sw      $v0, 0x14($a0)
		sw      $a1, 0x18($a0)
		sw      $a2, 0x1C($a0)
		ctc2    $at, $4
		ctc2    $v0, $5
		ctc2    $a1, $6
		ctc2    $a2, $7
		lhu     $v0, 0x34D4($gp)
		lhu     $v1, 0x34D8($gp)
		lhu     $a0, 0x34DC($gp)
		lhu     $a1, 0x34E4($gp)
		lhu     $a2, 0x34E8($gp)
		lhu     $a3, 0x34EC($gp)
		lhu     $t0, 0x34F4($gp)
		lhu     $t1, 0x34F8($gp)
		lhu     $t2, 0x34FC($gp)
		sh      $v0, 0x4048($gp)
		sh      $v1, 0x404A($gp)
		sh      $a0, 0x404C($gp)
		sh      $a1, 0x404E($gp)
		sh      $a2, 0x4050($gp)
		sh      $a3, 0x4052($gp)
		sh      $t0, 0x4054($gp)
		sh      $t1, 0x4056($gp)
		jr      $ra
		sh      $t2, 0x4058($gp)
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
#if 0
	Matrix->m00 *= vec.vx >> W2V_SHIFT;
	Matrix->m10 *= vec.vx >> W2V_SHIFT;
	Matrix->m20 *= vec.vx >> W2V_SHIFT;

	Matrix->m01 *= vec.vy >> W2V_SHIFT;
	Matrix->m11 *= vec.vy >> W2V_SHIFT;
	Matrix->m21 *= vec.vy >> W2V_SHIFT;

	Matrix->m02 *= vec.vz >> W2V_SHIFT;
	Matrix->m12 *= vec.vz >> W2V_SHIFT;
	Matrix->m22 *= vec.vz >> W2V_SHIFT;
#endif
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
	mLoadMatrix(--Matrix);
}

void mUnitMatrix()
{
	UNIMPLEMENTED();
}

void mPushUnitMatrix()//76534(<), 78578(<) (! Incorrect, redo, ida asm is bad)
{
	mPushMatrix();
	//setrot(++Matrix, 4096, 0, 4096, 0, 4096);
	mUnitMatrix();
}

void mTranslate()//76558(<) (!)
{

}

void mTranslateAbsXYZ(long x, long y, long z)
{
	x -= MatrixStack[0].tx;
	y -= MatrixStack[0].ty;
	z -= MatrixStack[0].tz;

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

void mRotX(long rx)// (F)
{
	if (rx & 0xFFFF)
	{
		short sin = SIN(rx);
		short cos = COS(rx);

		Matrix->m01 = (cos * Matrix->m01 + sin * Matrix->m02) * 4 >> W2V_SHIFT;
		Matrix->m02 = (cos * Matrix->m02 - sin * Matrix->m01) * 4 >> W2V_SHIFT;

		Matrix->m11 = (cos * Matrix->m11 + sin * Matrix->m12) * 4 >> W2V_SHIFT;
		Matrix->m12 = (cos * Matrix->m12 - sin * Matrix->m11) * 4 >> W2V_SHIFT;

		Matrix->m21 = (cos * Matrix->m21 + sin * Matrix->m22) * 4 >> W2V_SHIFT;
		Matrix->m22 = (cos * Matrix->m22 - sin * Matrix->m21) * 4 >> W2V_SHIFT;
	}

	mLoadMatrix(Matrix);
}

void mRotY(long ry)//76744 (F)
{
	if (ry & 0xFFFF)
	{
		short sin = SIN(ry);
		short cos = COS(ry);

		Matrix->m00 = (cos * Matrix->m00 - sin * Matrix->m02) * 4 >> W2V_SHIFT;
		Matrix->m02 = (cos * Matrix->m02 + sin * Matrix->m00) * 4 >> W2V_SHIFT;

		Matrix->m10 = (cos * Matrix->m10 - sin * Matrix->m12) * 4 >> W2V_SHIFT;
		Matrix->m12 = (cos * Matrix->m12 + sin * Matrix->m10) * 4 >> W2V_SHIFT;

		Matrix->m20 = (cos * Matrix->m20 - sin * Matrix->m22) * 4 >> W2V_SHIFT;
		Matrix->m22 = (cos * Matrix->m22 + sin * Matrix->m20) * 4 >> W2V_SHIFT;
	}

	mLoadMatrix(Matrix);
}

void mRotYXZ(short y, short x, short z)//767E8 (F)
{
	mRotY(y);
	mRotX(x);
	mRotZ(z);
}


void mRotZ(long rz)//76804 (F)
{
	if (rz & 0xFFFF)
	{
		short sin = SIN(rz);
		short cos = COS(rz);

		Matrix->m00 = (cos * Matrix->m00 + sin * Matrix->m01) * 4 >> W2V_SHIFT;
		Matrix->m01 = (cos * Matrix->m01 - sin * Matrix->m00) * 4 >> W2V_SHIFT;

		Matrix->m10 = (cos * Matrix->m10 + sin * Matrix->m11) * 4 >> W2V_SHIFT;
		Matrix->m11 = (cos * Matrix->m11 - sin * Matrix->m10) * 4 >> W2V_SHIFT;

		Matrix->m20 = (cos * Matrix->m20 + sin * Matrix->m21) * 4 >> W2V_SHIFT;
		Matrix->m21 = (cos * Matrix->m21 - sin * Matrix->m20) * 4 >> W2V_SHIFT;
	}

	mLoadMatrix(Matrix);
}

void mRotSuperPackedYXZ(short** a0, long a1)//768BC
{
	UNIMPLEMENTED();
}

void mRotPackedYXZ(long yxz)//7693C (F)
{
	long a;

	if ((a = (yxz >> 10 & 1023) << 6))
	{
		mRotY(a);
	}

	if ((a = (yxz >> 20 & 1023) << 6))
	{
		mRotX(a);
	}

	if ((a = (yxz & 1023) << 6))
	{
		mRotZ(a);
	}
}

void SetRotation()//7696C
{
	//gte_SetRotMatrix?
}

void setrot(struct MATRIX3D* m, long m00, long m02, long m11, long m20, long m22)//76970 TOCHECK
{
	//TODO not same as original but will do the same for now
	*(long*) &m->m00 = m00;//t0
	*(long*) &m->m02 = m02;//t1
	*(long*) &m->m11 = m11;//t2
	*(long*) &m->m20 = m20;//t3
	*(long*) &m->m22 = m22;//t4

	//gte_SetRotMatrix(m);
}

void mLoadMatrix(struct MATRIX3D* m)//7699C(<), 789E0(<) TOCHECK
{
	//gte_SetRotMatrix(m);
	//gte_SetTransMatrix(m);
	return;
}

//Note: Original code is less optimal than this implementation.
void mCopyMatrix(struct MATRIX3D* m)//769E4(<), 78A28(<) (F) TOCHECK
{
	//gte_ldtr(m->tx, m->ty, m->tz);
	Matrix->tx = m->tx;
	Matrix->ty = m->ty;
	Matrix->tz = m->tz;
	setrot(Matrix, 0, 0, 0, 0, 0);
}

void ASM_GetBounds()//76A28
{

}

void GetBounds()//76A28
{

}


void mSetTrans(long x, long y, long z)//76AF4(<), 78B38(<) TOCHECK
{
	//gte_ldtr(x, y, z);

	Matrix->tx = x;
	Matrix->ty = y;
	Matrix->tz = z;
}

void mClipBoundingBox(short* bounds)//76B14
{

}

void InitInterpolation(long frac, long rate, struct MATRIX3D* m)//76CB4 
{
	iFrac = frac;
	iRate = rate;
	iMatrix = m;

	//gte_ldbkdir(iAmbientR, iAmbientB, iAmbientG);

#if 0//?
	cfc2	$t0, $0
		cfc2	$t1, $1
		cfc2	$t2, $2
		cfc2	$t3, $3
		cfc2	$t4, $4
		cfc2	$t5, $5
		cfc2	$t6, $6
		cfc2	$t7, $7
		ctc2	$t0, $8
		ctc2	$t1, $9
		ctc2	$t2, $10
		ctc2	$t3, $11
		ctc2	$t4, $12
		ctc2	$t5, $13
		ctc2	$t6, $14
		ctc2	$t7, $15
		sw	$t0, 0($a2)
		sw	$t1, 4($a2)
		sw	$t2, 8($a2)
		sw	$t3, 0xC($a2)
		sw	$t4, 0x10($a2)
		sw	$t5, 0x14($a2)
		sw	$t6, 0x18($a2)
		jr	$ra
		sw	$t7, 0x1C($a2)
#endif
}

void iPushMatrix0()//76D3C(<), ?(<) (F)
{
	/*gte_ReadLightMatrix(*/++Matrix;/*);*/
	mPushMatrix();
}

void iPushMatrix(struct MATRIX3D* m)//81E60(<), ?(<) (F)
{
	/*gte_ReadLightMatrix(*/++m;/*);*/
	mmPushMatrix(m);
}

void iPopMatrix0()
{
	//a0 = Matrix 1820
	//a1 = iMatrix 46AC
	//--Matrix;
	//--iMatrix;
	mLoadMatrix(--Matrix);
	//iLoadMatrix(--iMatrix);

	//TODO
}

void iPopMatrix(struct MATRIX3D* m, struct MATRIX3D* m2)//76D8C(<), ?(<) TOCHECK
{
#if 0
	mLoadMatrix(--m);
	m2--;
	gte_SetLightMatrix(m);
#endif
}

void mPushMatrix0()//764D0 (F)
{
	/*gte_ReadRotMatrix(*/++Matrix;/*);*/
}

void mmPushMatrix(struct MATRIX3D* m)//81BBC(<) (F)
{
	/*gte_ReadRotMatrix(*/++m;/*);*/
}

int bound_start = 0;
int bound_end = 0;
int bound_list[128];

void SetRoomBounds(tr_room_portal* portal, int room_number, struct room_info* parent)
{
	struct room_info* r = &room[room_number];

	if (r->left <= parent->test_left && 
		r->right >= parent->test_right && 
		r->top <= parent->test_top && 
		r->bottom >= parent->test_bottom)
		return;

	int left = parent->test_right;
	int right = parent->test_left;
	int top = parent->test_bottom;
	int bottom = parent->test_top;

	struct door_vbuf* dest = vbufdoor;
	int t5 = 0;
	int t6 = 0;

	for (int i = 0; i < 4; i++, dest++)
	{
		int xv = vbufdoor[i].xv = 
			phd_mxptr[M00] * portal->Vertices[i].x + 
			phd_mxptr[M01] * portal->Vertices[i].y + 
			phd_mxptr[M02] * portal->Vertices[i].z + 
			phd_mxptr[M03];

		int yv = vbufdoor[i].yv =
			phd_mxptr[M10] * portal->Vertices[i].x + 
			phd_mxptr[M11] * portal->Vertices[i].y + 
			phd_mxptr[M12] * portal->Vertices[i].z + 
			phd_mxptr[M13];

		int zv = vbufdoor[i].zv =
			phd_mxptr[M20] * portal->Vertices[i].x + 
			phd_mxptr[M21] * portal->Vertices[i].y + 
			phd_mxptr[M22] * portal->Vertices[i].z + 
			phd_mxptr[M23];

		if (zv > 0)
		{
			if (zv > 20480)
				t6++;

			zv /= phd_persp;

			int xs, ys;

			if (zv)
			{
				xs = xv / zv + 256;
				ys = yv / zv + 120;
			}
			else
			{
				xs = xv >= 0 ? phd_right : phd_left;
				ys = yv >= 0 ? phd_bottom : phd_top;
			}

			if (xs - 1 < left)
				left = xs - 1;

			if (xs + 1 > right)
				right = xs + 1;

			if (ys - 1 < top)
				top = ys - 1;

			if (ys + 1 > bottom)
				bottom = ys + 1;
		}
		else
		{
			t5++;
		}
	}

	if (t5 == 4 || t6 == 4)
		return;

	if (t5 > 0)
	{
		dest = vbufdoor;

		struct door_vbuf* last = dest + 3;

		for (int i = 0; i < 4; i++, last = dest, dest++)
		{
			if (dest->zv < 0 ^ last->zv < 0)
			{
				if (dest->xv < 0 && last->xv < 0)
				{
					left = 0;
				}
				else if (dest->xv > 0 && last->xv > 0)
				{
					right = 511;
				}
				else
				{
					left = 0;
					right = 511;
				}

				if (dest->yv < 0 && last->yv < 0)
				{
					top = 0;
				}
				else if (dest->yv > 0 && last->yv > 0)
				{
					bottom = 239;
				}
				else
				{
					top = 0;
					bottom = 239;
				}
			}
		}
	}

	if (left < parent->test_left)
		left = parent->test_left;

	if (right > parent->test_right)
		right = parent->test_right;

	if (top < parent->test_top)
		top = parent->test_top;

	if (bottom > parent->test_bottom)
		bottom = parent->test_bottom;

	if (left >= right || top >= bottom)
		return;

	if (r->bound_active & 2)
	{
		if (left < r->test_left)
			r->test_left = left;

		if (top < r->test_top)
			r->test_top = top;

		if (right > r->test_right)
			r->test_right = right;

		if (bottom > r->test_bottom)
			r->test_bottom = bottom;
	}
	else
	{
		bound_list[bound_end++ % 128] = room_number;

		r->bound_active |= 2;

		r->test_left = left;
		r->test_right = right;
		r->test_top = top;
		r->test_bottom = bottom;
	}
}

void GetRoomBoundsAsm(short room_number)//77E70(<), 79EB4(<) ///@TODO check if in right file
{
	struct room_info* r;//a0
	char s0[216];
	//s0 = 0x1F8000D8
	//s1 = 0x1F8000DC
	//s2 = 0x1F8000E0
	//s3 = 0x1F8000E4
	//s4 = 0x1F8000E8
	//s5 = 0x1F8000EC
	//s6 = 0x1F8000F0
	//s7 = 0x1F8000F4
	//fp = 0x1F8000F8

	//s0 = 0x1F800000
	//s1 = room
	//s2 = 0
	//s3 = 1
	//s4 = 0x1F8000FC
	//s5 = 0
	//fp = outside
	s0[0] = room_number;
	r = &room[room_number];
	//t0 = 0x1FF0000
	//t1 = 0xEF0000
	//t2 = 2
	r->test_left = 0;
	r->test_right = SCREEN_WIDTH-1;
	r->test_top = 0;
	r->test_bottom = SCREEN_HEIGHT-1;
	r->bound_active = 2;
	//t6 = &CamPos;

	printf("Debug %d %d %d", -CamPos.x, -CamPos.y, -CamPos.z);


#if 0
		cfc2    $t1, $5
		cfc2    $t2, $6
		cfc2    $t3, $7
		sw      $t1, 0xB0($s0)
		sw      $t2, 0xB4($s0)
		sw      $t3, 0xB8($s0)
		lw      $t1, 0($t6)
		lw      $t2, 4($t6)
		lw      $t3, 8($t6)
		sw      $t1, 0xBC($s0)
		sw      $t2, 0xC0($s0)
		sw      $t3, 0xC4($s0)
			
		loc_77F18:
		beq     $s2, $s3, loc_78490
		add     $t0, $s0, $s2
		lbu     $s6, 0($t0)
		addi    $s2, 1
		andi    $s2, 0x7F
		sll     $a0, $s6, 4
		sll     $at, $a0, 2
		add     $a0, $at
		add     $a0, $s1
		lb      $v0, 0x37($a0)
		lw      $t1, 0x38($a0)
		addi    $v0, -2
		lw      $t3, 0x3C($a0)
		lw      $t5, 0x40($a0)
		lw      $t7, 0x44($a0)
		srl     $t2, $t1, 16
		andi    $t1, 0xFFFF
		srl     $t4, $t3, 16
		andi    $t3, 0xFFFF
		srl     $t6, $t5, 16
		andi    $t5, 0xFFFF
		srl     $t8, $t7, 16
		andi    $t7, 0xFFFF
		slt     $at, $t5, $t1
		beqz    $at, loc_77F84
		slt     $at, $t6, $t2
		move    $t1, $t5

				 loc_77F84 :
			 bnez    $at, loc_77F90
				 slt     $at, $t7, $t3
				 move    $t2, $t6

				 loc_77F90 :
			 beqz    $at, loc_77F9C
				 slt     $at, $t8, $t4
				 move    $t3, $t7

				 loc_77F9C :
			 bnez    $at, loc_77FA8
				 sll     $t6, $t2, 16
				 move    $t4, $t8

				 loc_77FA8 :
			 or $t5, $t1, $t6
				 sll     $t6, $t4, 16
				 or $t6, $t3
				 sw      $t5, 0x38($a0)
				 sw      $t6, 0x3C($a0)
				 andi    $at, $v0, 1
				 bnez    $at, loc_77FD4
				 ori     $v0, 1
				 sh      $s6, 0($s4)
				 addi    $s4, 2
				 addi    $s5, 1

				 loc_77FD4:
			 lh      $s6, 0x4E($a0)
				 sb      $v0, 0x37($a0)
				 andi    $s6, 8
				 or $fp, $s6
				 lw      $s7, 4($a0)
				 lw      $t0, 0x14($a0)
				 beqz    $s7, loc_77F18
				 lw      $t1, 0x18($a0)
				 lw      $t2, 0x1C($a0)
				 bgez    $t0, loc_78018
				 sra     $t3, $t0, 15
				 negu    $t0, $t0
				 sra     $t3, $t0, 15
				 andi    $t0, 0x7FFF
				 negu    $t3, $t3
				 j       loc_7801C
				 negu    $t0, $t0

				 loc_78018 :
			 andi    $t0, 0x7FFF

				 loc_7801C :
				 bgez    $t1, loc_7803C
				 sra     $t4, $t1, 15
				 negu    $t1, $t1
				 sra     $t4, $t1, 15
				 andi    $t1, 0x7FFF
				 negu    $t4, $t4
				 j       loc_78040
				 negu    $t1, $t1

				 loc_7803C :
			 andi    $t1, 0x7FFF

				 loc_78040 :
				 bgez    $t2, loc_78060
				 sra     $t5, $t2, 15
				 negu    $t2, $t2
				 sra     $t5, $t2, 15
				 andi    $t2, 0x7FFF
				 negu    $t5, $t5
				 j       loc_78064
				 negu    $t2, $t2

				 loc_78060 :
			 andi    $t2, 0x7FFF

				 loc_78064 :
				 mtc2    $t3, $9
				 mtc2    $t4, $10
				 mtc2    $t5, $11
				 nop
				 cop2    0x41E012
				 lw      $t3, 0xB0($s0)
				 lw      $t4, 0xB4($s0)
				 lw      $t5, 0xB8($s0)
				 ctc2    $t3, $5
				 ctc2    $t4, $6
				 ctc2    $t5, $7
				 mfc2    $t3, $25
				 mfc2    $t4, $26
				 mtc2    $t0, $9
				 mtc2    $t1, $10
				 mtc2    $t2, $11
				 mfc2    $t5, $27
				 cop2    0x498012
				 bgez    $t3, loc_780C0
				 sll     $t0, $t3, 3
				 negu    $t3, $t3
				 sll     $t3, 3
				 negu    $t0, $t3

				 loc_780C0 :
			 bgez    $t4, loc_780D4
				 sll     $t1, $t4, 3
				 negu    $t4, $t4
				 sll     $t4, 3
				 negu    $t1, $t4

				 loc_780D4 :
			 bgez    $t5, loc_780E8
				 sll     $t2, $t5, 3
				 negu    $t5, $t5
				 sll     $t5, 3
				 negu    $t2, $t5

				 loc_780E8 :
			 mfc2    $t3, $25
				 mfc2    $t4, $26
				 mfc2    $t5, $27
				 addu    $t0, $t3
				 addu    $t1, $t4
				 addu    $t2, $t5
				 ctc2    $t0, $5
				 ctc2    $t1, $6
				 ctc2    $t2, $7
				 lh      $v0, 0($s7)
				 addi    $s7, 2

				 loc_78114:
			 lh      $a1, 0($s7)
				 addi    $s7, 2
				 lh      $t0, 0($s7)
				 lw      $t1, 0x14($a0)
				 beqz    $t0, loc_7814C
				 lh      $t2, 6($s7)
				 lw      $t3, 0xBC($s0)
				 add     $t1, $t2
				 sub     $t1, $t3
				 beqz    $t1, loc_7847C
				 xor     $t0, $t1
				 bltz    $t0, loc_781A8
				 move    $a2, $s7
				 j       loc_7847C

				 loc_7814C :
			 lh      $t0, 2($s7)
				 lw      $t1, 0x18($a0)
				 beqz    $t0, loc_7817C
				 lh      $t2, 8($s7)
				 lw      $t3, 0xC0($s0)
				 add     $t1, $t2
				 sub     $t1, $t3
				 beqz    $t1, loc_7847C
				 xor     $t0, $t1
				 bltz    $t0, loc_781A8
				 move    $a2, $s7
				 j       loc_7847C

				 loc_7817C :
			 lh      $t0, 4($s7)
				 lw      $t1, 0x1C($a0)
				 beqz    $t0, loc_7847C
				 lh      $t2, 0xA($s7)
				 lw      $t3, 0xC4($s0)
				 add     $t1, $t2
				 sub     $t1, $t3
				 beqz    $t1, loc_7847C
				 xor     $t0, $t1
				 bgez    $t0, loc_7847C
				 move    $a2, $s7

				 loc_781A8 :
			 sll     $a3, $a1, 4
				 sll     $at, $a3, 2
				 add     $a3, $at
				 add     $a3, $s1
				 lw      $t0, 0x38($a3)
				 lw      $t2, 0x40($a0)
				 lw      $t4, 0x3C($a3)
				 lw      $t6, 0x44($a0)
				 srl     $t1, $t0, 16
				 andi    $t0, 0xFFFF
				 srl     $t3, $t2, 16
				 andi    $t2, 0xFFFF
				 srl     $t5, $t4, 16
				 andi    $t4, 0xFFFF
				 srl     $t7, $t6, 16
				 andi    $t6, 0xFFFF
				 slt     $at, $t0, $t2
				 beqz    $at, loc_78208
				 slt     $at, $t1, $t3
				 bnez    $at, loc_78208
				 slt     $at, $t4, $t6
				 beqz    $at, loc_78208
				 slt     $at, $t5, $t7
				 beqz    $at, loc_7847C

				 loc_78208 :
			 move    $t0, $t3
				 move    $t1, $t2
				 move    $t2, $t7
				 move    $t3, $t6
				 addi    $t4, $s0, 0x80
				 move    $t5, $zero
				 move    $t6, $zero
				 li      $v1, 3

				 loc_78228:
			 lhu     $t7, 6($a2)
				 lhu     $t9, 8($a2)
				 lhu     $t8, 0xA($a2)
				 sll     $t9, 16
				 or $t7, $t9
				 mtc2    $t7, $0
				 mtc2    $t8, $1
				 addi    $a2, 6
				 cop2    0x480012
				 mfc2    $t7, $9
				 mfc2    $t8, $10
				 mfc2    $t9, $11
				 cop2    0x180001
				 sw      $t7, 0($t4)
				 sw      $t8, 4($t4)
				 sw      $t9, 8($t4)
				 bgtz    $t9, loc_78278
				 addi    $t4, 0xC
				 j       loc_782C8
				 addi    $t5, 1

				 loc_78278:
			 slti    $at, $t9, 0x5000
				 mfc2    $t7, $14
				 bnez    $at, loc_7828C
				 sra     $t8, $t7, 16
				 addi    $t6, 1

				 loc_7828C :
				 sll     $t7, 16
				 sra     $t7, 16
				 slt     $at, $t7, $t0
				 beqz    $at, loc_782A4
				 slt     $at, $t7, $t1
				 move    $t0, $t7

				 loc_782A4 :
			 bnez    $at, loc_782B0
				 slt     $at, $t8, $t2
				 move    $t1, $t7

				 loc_782B0 :
			 beqz    $at, loc_782BC
				 slt     $at, $t8, $t3
				 move    $t2, $t8

				 loc_782BC :
			 bnez    $at, loc_782C8
				 nop
				 move    $t3, $t8

				 loc_782C8 :
			 bnez    $v1, loc_78228
				 addi    $v1, -1
				 li      $at, 4
				 beq     $t5, $at, loc_7847C
				 addi    $t4, $s0, 0x80
				 beq     $t6, $at, loc_7847C
				 li      $v1, 3
				 beqz    $t5, loc_78384
				 addi    $t5, $t4, 0x24

				 loc_782EC:
			 lw      $t6, 8($t4)
				 lw      $t7, 8($t5)
				 slti    $t8, $t6, 1
				 slti    $t9, $t7, 1
				 xor $t8, $t9
				 beqz    $t8, loc_78374
				 lw      $t6, 0($t4)
				 lw      $t7, 0($t5)
				 slt     $t8, $t6, $zero
				 slt     $t9, $t7, $zero
				 and     $t8, $t9
				 beqz    $t8, loc_78328
				 slt     $t8, $zero, $t6
				 j       loc_7833C
				 move    $t0, $zero

				 loc_78328 :
			 slt     $t9, $zero, $t7
				 and     $t8, $t9
				 bnez    $t8, loc_7833C
				 li      $t1, 0x1FF
				 move    $t0, $zero

				 loc_7833C :
			 lw      $t6, 4($t4)
				 lw      $t7, 4($t5)
				 slt     $t8, $t6, $zero
				 slt     $t9, $t7, $zero
				 and     $t8, $t9
				 beqz    $t8, loc_78360
				 slt     $t8, $zero, $t6
				 j       loc_78374
				 move    $t2, $zero

				 loc_78360 :
			 slt     $t9, $zero, $t7
				 and     $t8, $t9
				 bnez    $t8, loc_78374
				 li      $t3, 0xEF
				 move    $t2, $zero

				 loc_78374 :
			 move    $t5, $t4
				 addi    $t4, 0xC
				 bnez    $v1, loc_782EC
				 addi    $v1, -1

				 loc_78384 :
				 lw      $t4, 0x40($a0)
				 lw      $t6, 0x44($a0)
				 srl     $t5, $t4, 16
				 andi    $t4, 0xFFFF
				 srl     $t7, $t6, 16
				 andi    $t6, 0xFFFF
				 slt     $at, $t0, $t4
				 beqz    $at, loc_783AC
				 slt     $at, $t5, $t1
				 move    $t0, $t4

				 loc_783AC :
			 beqz    $at, loc_783B8
				 slt     $at, $t2, $t6
				 move    $t1, $t5

				 loc_783B8 :
			 beqz    $at, loc_783C4
				 slt     $at, $t7, $t3
				 move    $t2, $t6

				 loc_783C4 :
			 beqz    $at, loc_783D0
				 sub     $at, $t0, $t1
				 move    $t3, $t7

				 loc_783D0 :
			 bgez    $at, loc_7847C
				 sub     $at, $t2, $t3
				 bgez    $at, loc_7847C
				 lb      $v1, 0x37($a3)
				 add     $t4, $s0, $s3
				 andi    $at, $v1, 2
				 bnez    $at, loc_7841C
				 ori     $v1, 2
				 sb      $a1, 0($t4)
				 addi    $s3, 1
				 andi    $s3, 0x7F
				 sll     $t1, 16
				 or $t0, $t1
				 sll     $t3, 16
				 or $t2, $t3
				 sw      $t0, 0x40($a3)
				 sw      $t2, 0x44($a3)
				 j       loc_7847C
				 sb      $v1, 0x37($a3)

				 loc_7841C:
			 lw      $t4, 0x40($a3)
				 lw      $t6, 0x44($a3)
				 srl     $t5, $t4, 16
				 andi    $t4, 0xFFFF
				 srl     $t7, $t6, 16
				 andi    $t6, 0xFFFF
				 slt     $at, $t0, $t4
				 beqz    $at, loc_78444
				 slt     $at, $t5, $t1
				 move    $t4, $t0

				 loc_78444 :
			 beqz    $at, loc_78450
				 slt     $at, $t2, $t6
				 move    $t5, $t1

				 loc_78450 :
			 beqz    $at, loc_7845C
				 slt     $at, $t7, $t3
				 move    $t6, $t2

				 loc_7845C :
			 beqz    $at, loc_78468
				 sll     $t5, 16
				 move    $t7, $t3

				 loc_78468 :
			 or $t4, $t5
				 sll     $t7, 16
				 or $t6, $t7
				 sw      $t4, 0x40($a3)
				 sw      $t6, 0x44($a3)

				 loc_7847C :
				 addi    $v0, -1
				 bgtz    $v0, loc_78114
				 addi    $s7, 0x1E
				 j       loc_77F18
				 nop

				 loc_78490 :
			 addiu   $t0, $gp, 0x1F30
				 li      $s4, 0x1F8000FC
				 addiu   $v0, $s5, -1
				 move    $s5, $zero

				 loc_784A4 :
			 lh      $a1, 0($s4)
				 addi    $s4, 2
				 sh      $a1, 0($t0)
				 addiu   $t0, 2
				 addiu   $s5, 1
				 bgtz    $v0, loc_784A4
				 addi    $v0, -1
				 sw      $s5, 0x1F2C($gp)
				 sw      $fp, 0x203C($gp)
				 lui     $a0, 0x1F80
				 lw      $s0, 0x1F8000D8
				 lw      $s1, 0x1F8000DC
				 lw      $s2, 0x1F8000E0
				 lw      $s3, 0x1F8000E4
				 lw      $s4, 0x1F8000E8
				 lw      $s5, 0x1F8000EC
				 lw      $s6, 0x1F8000F0
				 lw      $s7, 0x1F8000F4
				 jr      $ra
				 lw      $fp, 0x1F8000F8
				 # End of function sub_77E70
#else
	bound_start = 0;
	bound_end = 1;
	bound_list[0] = room_number;

	while (bound_start != bound_end)
	{
		int current = bound_list[bound_start++ % 128];
		room_info* r = &room[room_number];
		r->bound_active -= 2;

		if (r->test_left < r->left)
			r->left = r->test_left;
		if (r->test_top < r->top)
			r->top = r->test_top;
		if (r->test_right > r->right)
			r->right = r->test_right;
		if (r->test_bottom > r->bottom)
			r->bottom = r->test_bottom;

		if (!(r->bound_active & 1))
		{
			draw_rooms[number_draw_rooms++] = room_number;
			r->bound_active |= 1;

			if (r->flags & RF_SKYBOX_VISIBLE)
				outside = RF_SKYBOX_VISIBLE;
		}

		if (r->flags & RF_SKYBOX_VISIBLE)
		{
			if (r->left < outside_left)
				outside_left = r->left;
			if (r->right > outside_right)
				outside_right = r->right;
			if (r->top < outside_top)
				outside_top = r->top;
			if (r->bottom > outside_bottom)
				outside_bottom = r->bottom;
		}

		mPushMatrix();
		mTranslateAbsXYZ(r->x, r->y, r->z);

		short* door;
		if ((door = r->door))
		{
			tr_room_portal* portal = (tr_room_portal*)(door + 1);
			for (short i = *door++; i > 0; i--, portal++)
			{
				if (portal->Normal.x * (r->x + portal->Vertices[0].x - w2v_matrix[M03]) +
					portal->Normal.y * (r->y + portal->Vertices[0].y - w2v_matrix[M13]) +
					portal->Normal.z * (r->z + portal->Vertices[0].z - w2v_matrix[M23])
					>= 0)
				{
					continue;
				}

				SetRoomBounds(portal, portal->AdjoiningRoom, r);
			}
		}
		mPopMatrix();
	}
#endif
}

void phd_GetVectorAngles(long dx, long dy, long dz, short* angles)
{
	angles[0] = phd_atan_asm(dz, dx);
	while ((int16_t)dx != dx || (int16_t)dy != dy || (int16_t)dz != dz)
	{
		dx >>= 2;
		dy >>= 2;
		dz >>= 2;
	}
	short pitch = phd_atan_asm(phd_sqrt_asm(dx * dx + dz * dz), dy);
	if (dy > 0 && pitch > 0 || dy < 0 && pitch < 0)
		pitch = -pitch;
	angles[1] = pitch;
}


void phd_LookAt(long xsrc, long ysrc, long zsrc, long xtar, long ytar, long ztar, long roll)
{
	short	angles[2];

	CamPos.x = xsrc;
	CamPos.y = ysrc;
	CamPos.z = zsrc;

	viewer.x_pos = xsrc;
	viewer.y_pos = ysrc;
	viewer.z_pos = zsrc;

	viewer.z_rot = roll;

	phd_GetVectorAngles(xtar - xsrc, ytar - ysrc, ztar - zsrc, angles);
	
	viewer.x_rot = angles[1];
	viewer.y_rot = angles[0];
}

long phd_atan_asm(long x, long y)// (F)
{
	if (x || y)
	{
		int octant = 0;

		if (x < 0)
		{
			octant = 4;
			x = -x;
		}
		if (y < 0)
		{
			octant += 2;
			y = -y;
		}

		if (y > x)
		{
			long temp = x;
			x = y;
			y = temp;

			octant++;
		}

		while ((short)y != y)
		{
			y >>= 1;
			x >>= 1;
		}

		y <<= 11;

		if (x == 0)
			x = 1;

		long res = atanOctantTab[octant] + atanTab[y / x];

		if (res < 0)
			res = -res;

		return res;
	}
	else
	{
		return 0; 
	}
}

void mRotBoundingBoxNoPersp(short* bounds, short* tbounds)
{
	S_Warn("[mRotBoundingBoxNoPersp] - Unimplemented!\n");
}

#if 0

0x76DB8 iRotX
0x76E60 iRotY
0x76F04 iRotZ
0x76FBC iRotYXZ
0x76FDC iRotPackedYXZ
0x7700C iRotSuperPackedYXZ
0x77090 iTranslateXYZ
0x7709C iTranslateXYZ2
0x771D8 iLoadMatrix
0x77220 SetRotation_I
0x77250 InterpolateMatrix
0x77580 mResetCols
0x775A0 mNormalise
0x775CC mNormaliseXYZ
#endif
