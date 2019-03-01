#include "MATHS.H"

#include "LOAD_LEV.H"
#include "SPECIFIC.H"

#include <INLINE_C.H>
#include "3D_GEN.H"
#include "CAMERA.H"
#include "DRAW.H"

void mQuickW2VMatrix()
{
	MatrixSP = 0;
	Matrix = &MatrixStack[0];

	Matrix->m00 = phd_mxptr[M00];
	Matrix->m01 = phd_mxptr[M01];
	Matrix->m02 = phd_mxptr[M02];
	Matrix->m10 = phd_mxptr[M10];
	Matrix->m11 = phd_mxptr[M11];
	Matrix->m12 = phd_mxptr[M12];
	Matrix->m20 = phd_mxptr[M20];
	Matrix->m21 = phd_mxptr[M21];
	Matrix->m22 = phd_mxptr[M22];
	Matrix->tx = phd_mxptr[M03];
	Matrix->ty = phd_mxptr[M13];
	Matrix->tz = phd_mxptr[M23];


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
	Matrix->m00 *= sx / 4096.0f;
	Matrix->m10 *= sx / 4096.0f;
	Matrix->m20 *= sx / 4096.0f;

	Matrix->m01 *= sy / 4096.0f;
	Matrix->m11 *= sy / 4096.0f;
	Matrix->m21 *= sy / 4096.0f;

	Matrix->m02 *= sz / 4096.0f;
	Matrix->m12 *= sz / 4096.0f;
	Matrix->m22 *= sz / 4096.0f;
}

void mPushMatrix()//764D0(<), 78514(<) (F) (START)
{
	/*gte_ReadRotMatrix(*/++Matrix;/*);*/
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
	MATRIX3D* mat = Matrix;

	mat->tx = mat->m00 * x + mat->m01 * y + mat->m02 * z >> 12;
	mat->ty = mat->m10 * x + mat->m11 * y + mat->m12 * z >> 12;
	mat->tz = mat->m20 * x + mat->m21 * y + mat->m22 * z >> 12;

	mLoadMatrix(mat);
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

void mRotSuperPackedYXZ(short* a0, long a1)//768BC
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

void GetRoomBoundsAsm(short room_number)//
{
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
