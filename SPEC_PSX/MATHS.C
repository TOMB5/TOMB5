#include "MATHS.H"

#include "LOAD_LEV.H"
#include "SPECIFIC.H"

#include INLINE_H

#ifdef PAELLA
#define gte_rldlzc( r0 )
#else
#define gte_rldlzc( r0 ) __asm__ volatile (			\
	"mfc2	%0, $31"					\
	:							\
	: "r"( r0 ) )
#endif

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
		gte_rldlzc(v1);

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

void setrot(struct MATRIX3D* m, long m00, long m02, long m11, long m20, long m22)
{
	//TODO not same as original but will do the same for now
	*(long*) &m->m00 = m00;//t0
	*(long*) &m->m02 = m02;//t1
	*(long*) &m->m11 = m11;//t2
	*(long*) &m->m20 = m20;//t3
	*(long*) &m->m22 = m22;//t4

	gte_SetRotMatrix(m);
}

void mPushUnitMatrix()//76534(<), 78578(<)
{
	setrot(++Matrix, 4096, 0, 4096, 0, 4096);
}

void mLoadMatrix(struct MATRIX3D* m)//7699C(<), 789E0(<)
{
	gte_SetRotMatrix(m);
	gte_SetTransMatrix(m);
	return;
}

void mPushMatrix()//764D0(<), 78514(<)
{
	gte_ReadRotMatrix(++Matrix);
}

void iPushMatrix(struct MATRIX3D* m)//81E60(<), 83EA4(<)
{
	gte_ReadLightMatrix(++m);
	//mmPushMatrix(m);
}

void mPopMatrix()//76520(<), 78564(<)
{
	mLoadMatrix(--Matrix);
}

void iPopMatrix(struct MATRIX3D* m, struct MATRIX3D* m2)//81EB0(<), 83EF4(<)
{
	mLoadMatrix(--m);
	m2--;
	gte_SetLightMatrix(m);
}

void mSetTrans(long x, long y, long z)//76AF4(<), 78B38(<) 
{
	gte_ldtr(x, y, z);

	Matrix->tx = x;
	Matrix->ty = y;
	Matrix->tz = z;
}

void mTranslateXYZ(long x, long y, long z)//7658C(<), 785D0(<)
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
	sw	$t0, 0x14($v0)
	sw	$t1, 0x18($v0)
	jr	$ra
	sw	$t2, 0x1C($v0)*/
#endif
	

	S_Warn("[mTranslateXYZ] - Unimplemented!\n");
}

void mTranslateAbsXYZ(long x, long y, long z)
{
	S_Warn("[mTranslateAbsXYZ] - Unimplemented!\n");
}

void mRotY(long ry)
{
	S_Warn("[mRotY] - Unimplemented!\n");
}

//Note: Original code is less optimal than this implementation.
void mCopyMatrix(struct MATRIX3D* m)//769E4(<), 78A28(<) (F)
{
	gte_ldtr(m->tx, m->ty, m->tz);
	Matrix->tx = m->tx;
	Matrix->ty = m->ty;
	Matrix->tz = m->tz;
	setrot(Matrix, 0, 0, 0, 0, 0);
}
