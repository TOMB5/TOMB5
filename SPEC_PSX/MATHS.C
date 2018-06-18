#include "MATHS.H"

#include "LOAD_LEV.H"
#include "SPECIFIC.H"

#include INLINE_H

#ifndef USE_ASM

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
		while ((dz / 65536) != 0)
		{
			dx /= 2;
			dz /= 2;
		}

		//79724
		result_angle = atanTab[(dz * 2048) / dx];
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
#ifdef PAELLA
	long root = 0;
	long remainder = value;
	long place = 0x40000000;

	do
	{
		if (remainder >= root + place)
		{
			remainder -= root + place;
			root |= place << 1;
		}

		place >>= 2;
		root >>= 1;
	} while (place);

	return root;
#else
	long v0 = 0x1F;
	long v1;
	long at;

	gte_ldlzc(value);

	if (value != 0)
	{
#if PSX_VERSION
		__asm__ volatile("mfc2 %0, $31": "=r" (v1) : );
#endif
		v1 &= 0xFFFFFFFE;
		v0 = (v0 - v1) >> 1;
		at = v1 - 0x18;

		if (v1 - 0x18 < 0)
		{ 
			//loc_85BA8
			value >>= (0x18 - v1);
		}
		else
		{
			value <<= (v1 - 0x18);
		}

		//loc_85BB4
		value = SqrtTable[value - 0x40] << v0;

	}//locret_85BD0

	return value << v0;
#endif
}


void ScaleCurrentMatrix(long a0, long sx, long sy, long sz)
{
	S_Warn("[ScaleCurrentMatrix] - Unimplemented!\n");
}

void mPushMatrix()//764D0(<), 78514(<) (F) (START)
{
	gte_ReadRotMatrix(++Matrix);
}

void mPopMatrix()//76520(<), 78564(<) (F)
{
	mLoadMatrix(--Matrix);
}

void mPushUnitMatrix()//76534(<), 78578(<) (! Incorrect, redo, ida asm is bad)
{
	setrot(++Matrix, 4096, 0, 4096, 0, 4096);
}

void mTranslate()//76558(<) (!)
{

}

void mTranslateAbsXYZ(long x, long y, long z)
{
	S_Warn("[mTranslateAbsXYZ] - Unimplemented!\n");
}

void mTranslateXYZ(long x, long y, long z)//7658C(<), 785D0(<) (!)
{
	if (y < 0)
	{
		//a1 = -a1
		//t4 = a1 >> 15
		//a1 &= 0x7FFF
		//t4 = -t4;
		//a1 = -a1
	}
	else
	{
		//loc_765AC
		//t4 = a1 >> 15;
		y &= 0x7FFF;
	}

	//loc_765B0
	if (z < 0)
	{
		//a2 = -a2;
		//t5 = a2 >> 15;
		//a2 &= 0x7FFF;
		//t5 = -t5;
		//a2 = -a2;
	}
	else
	{
		//loc_765D0
		//t5 = a2 >> 15;
		//a2 &= 0x7FFF;
	}

	//loc_765D4
	if (x < 0)
	{
		//a0 = -a0;
		//t3 = a0 >> 15;
		//a0 &= 0x7FFF;
		//t3 = -t3;
		//a0 = -a0;
	}
	else
	{
		//loc_765F4
		//t3 = a0 >> 15;
		//a0 &= 0x7FFF;
	}

#if 0
	/*loc_765F8:
	mtc2	$t3, $9
	mtc2	$t4, $10
	mtc2	$t5, $11
	nop
	cop2	0x41E012
	mfc2	$t3, $25
	mfc2	$t4, $26
	mtc2	$a0, $9
	mtc2	$a1, $10
	mtc2	$a2, $11
	mfc2	$t5, $27
	cop2	0x498012
	bgez	$t3, loc_7663C
	sll	$t0, $t3, 3
	negu	$t3, $t3
	sll	$t3, 3
	negu	$t0, $t3

	//loc_7663C :
	bgez	$t4, loc_76650
	sll	$t1, $t4, 3
	negu	$t4, $t4
	sll	$t4, 3
	negu	$t1, $t4

	//loc_76650 :
	bgez	$t5, loc_76664
	sll	$t2, $t5, 3
	negu	$t5, $t5
	sll	$t5, 3
	negu	$t2, $t5

	//loc_76664 :
	//mfc2	$t3, $25//gte_mvlvtr?
	mfc2	$t4, $26
	mfc2	$t5, $27
	addu	$t0, $t3
	addu	$t1, $t4
	addu	$t2, $t5
	lw	$v0, 0x1820($gp)
	ctc2	$t0, $5
	ctc2	$t1, $6
	ctc2	$t2, $7
	sw	$t0, 0x14($v0)//gte_sttr
	sw	$t1, 0x18($v0)
	jr	$ra
	sw	$t2, 0x1C($v0)*/
#endif

	S_Warn("[mTranslateXYZ] - Unimplemented!\n");
}

#if 1
void mRotX()//7669C
{

}
#endif

void mRotY(long ry)//76744
{
	ry /= 4;

	if (ry & 0x3FFC)
	{
		//rcossin_tbl[0];
		//loc_7675C
		//t5 = rcossin_tbl[0];//word
		//t6 = rcossin_tbl[1];

		//t2 = -t5;

#if 0
		lui	$t7, 0xFFFF
			neg	$t2, $t5
			mtc2	$t6, $0//?
			mtc2	$t2, $1//?
			cfc2	$t0, $0
			cfc2	$t2, $2
			cfc2	$t3, $3
			cop2	0x486012
			mtc2	$t5, $2
			mtc2	$t6, $3
			and	$t0, $t7
			andi	$t2, 0xFFFF
			and $t3, $t7
			mfc2	$t4, $25
			mfc2	$t1, $26
			mfc2	$t5, $27
			cop2	0x48E012
			andi	$t4, 0xFFFF
			or $t0, $t4
			sll	$t1, 16
			andi	$t5, 0xFFFF
			or $t3, $t5
			mfc2	$t5, $25
			mfc2	$t6, $26
			mfc2	$t4, $27
			andi	$t5, 0xFFFF
			or $t1, $t5
			sll	$t6, 16
			j	loc_7696C
			or $t2, $t6
#endif
	}

	//ret

	S_Warn("[mRotY] - Unimplemented!\n");
}

void mRotYXZ()//767E8
{

}

void mRotZ()//76804
{

}

void mRotSuperPackedYXZ()//768BC
{

}

void mRotPackedYXZ()//7693C
{

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

	gte_SetRotMatrix(m);
}

void mLoadMatrix(struct MATRIX3D* m)//7699C(<), 789E0(<) TOCHECK
{
	gte_SetRotMatrix(m);
	gte_SetTransMatrix(m);
	return;
}

//Note: Original code is less optimal than this implementation.
void mCopyMatrix(struct MATRIX3D* m)//769E4(<), 78A28(<) (F) TOCHECK
{
	gte_ldtr(m->tx, m->ty, m->tz);
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
	gte_ldtr(x, y, z);

	Matrix->tx = x;
	Matrix->ty = y;
	Matrix->tz = z;
}

void mClipBoundingBox()//76B14
{

}

void InitInterpolation(long frac, long rate, struct MATRIX3D* m)//76CB4 
{
	iFrac = frac;
	iRate = rate;
	iMatrix = m;

	gte_ldbkdir(iAmbientR, iAmbientB, iAmbientG);

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
	gte_ReadLightMatrix(++Matrix);
	mPushMatrix();
}

void iPushMatrix(struct MATRIX3D* m)//81E60(<), ?(<) (F)
{
	gte_ReadLightMatrix(++m);
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
	mLoadMatrix(--m);
	m2--;
	gte_SetLightMatrix(m);
}

void mPushMatrix0()//764D0 (F)
{
	gte_ReadRotMatrix(++Matrix);
}

void mmPushMatrix(struct MATRIX3D* m)//81BBC(<) (F)
{
	gte_ReadRotMatrix(++m);
}

void GetRoomBoundsAsm(short room_number)//
{
	S_Warn("[GetRoomBoundsAsm] - Unimplemented!\n");
}

void phd_GetVectorAngles(long dx, long dy, long dz, short* angles)
{
	S_Warn("[phd_GetVectorAngles] - Unimplemented!\n");
}

void phd_LookAt(long x, long y, long z, long tx, long ty, long tz, long croll)
{
	S_Warn("[phd_LookAt] - Unimplemented!\n");
}

long phd_atan_asm(long x, long y)
{
	S_Warn("[phd_atan_asm] - Unimplemented!\n");
}

#endif