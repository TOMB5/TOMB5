#include "PHD_MATH.H"

#include "LOAD_LEV.H"
#include "SPECIFIC.H"

#include <INLINE_C.H>

long phd_sqrt_asm(long val)//83B30(<), ?
{
#if 0
	 //mtc2	$a0, $30
	
	if (val != 0)
	{
		//0x1F0000
	}

	 li	$v0, 0x1F
	 mfc2	$v1, $31
	 li	$at, 0xFFFFFFFE
	 and $v1, $at
	 sub	$v0, $v1
	 sra	$v0, 1
	 addi	$at, $v1, -0x18
	 bltz	$at, loc_83B64
	 lui	$a1, 0xA
	 j	loc_83B70
	 sllv	$a0, $at

	 loc_83B64 :
	 li	$at, 0x18
	 sub	$at, $v1
	 srav	$a0, $at

	 loc_83B70 :
	 ori	$a1, 0x1AA4
	 addi	$a0, -0x40
	 sll	$a0, 1
	 addu	$a0, $a1
	 lh	$a0, 0($a0)
	 nop
	 sllv	$a0, $v0
		 
	locret_83B8C :
	jr	$ra
	 srl	$v0, $a0, 12
#endif
	return 0;
}

void ScaleCurrentMatrix(long a0, long sx, long sy, long sz)
{
	S_Warn("[ScaleCurrentMatrix] - Unimplemented!\n");
}

void mPushUnitMatrix()
{
	S_Warn("[mPushUnitMatrix] - Unimplemented!\n");
}

void mLoadMatrix(struct MATRIX3D* m)
{
	gte_SetRotMatrix(m);
	gte_SetTransMatrix(m);
	return;
}

void mPopMatrix()//76520(<), (<)
{
	mLoadMatrix(--Matrix);
}

void mSetTrans(long x, long y, long z)//76AF4(<), 78B38(<) 
{
	gte_ldtr(x, y, z);

	Matrix->tx = x;
	Matrix->ty = y;
	Matrix->tz = z;
}
