#include "ANIMITEM.H"

#include <LIBGTE.H>
#include "GTEREG.H"

int GetBounds(int t0, int a2, int a3, int t1, int t2, int v0, int a0, int a1, int t3, int t4, int t5)//8139C
{
	if (t0 < a2)
	{
		a2 = t0;
	}

	//loc_813AC
	if (t0 >= a3)
	{
		a3 = t0;
	}

	//loc_813B8
	if (t1 < a2)
	{
		a2 = t1;
	}

	//loc_813C4
	if (t1 >= a3)
	{
		a3 = t1;
	}

	if (t2 < a2)
	{
		a3 = t2;
	}

	//loc_813DC
	t0 <<= 16;
	if (t2 >= a3)
	{
		a3 = t2;
	}

	//loc_813E8
	t1 <<= 16;
	t2 <<= 16;

	if (t0 < a0)
	{
		a0 = t0;
	}

	if (t0 >= a1)
	{
		a1 = t0;
	}

	if (t1 < a0)
	{
		a0 = t1;
	}

	if (t1 >= a1)
	{
		a1 = t1;
	}

	if (t2 < a0)
	{
		a0 = t2;
	}

	if (t2 >= a1)
	{
		a1 = t2;
	}

	if (t3 < 0x5000)
	{
		v0 = 1;
	}

	if (t4 < 0x5000)
	{
		v0 = 1;
	}

	if (t5 < 0x5000)
	{
		v0 = 1;
	}

	return v0;
}

int mClipBoundingBox2(short* bounds)//811FC
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
		VX0 = at & 0xFFFF;
		VY0 = at >> 16;
		VZ0 = t2;

		at = t3 | t1;
		VX1 = at & 0xFFFF;
		VY1 = at >> 16;
		VZ1 = t2;

		at = t0 | t4;
		VX2 = at & 0xFFFF;
		VY2 = at >> 16;
		VZ2 = t2;

		//v1 = ra

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
	}

#if 0
jal     sub_8139C
nop
mfc2    $t0, $12
mfc2    $t1, $13
mfc2    $t2, $14
mfc2    $t3, $17
mfc2    $t4, $18
mfc2    $t5, $19
mtc2    $t9, $0
mtc2    $t8, $1
mtc2    $t9, $2
addi    $t3, -0x21
cop2    0x280030
addi    $t4, -0x21
jal     sub_8139C
addi    $t5, -0x21
mfc2    $t0, $12
mfc2    $t1, $13
mfc2    $t3, $17
mfc2    $t4, $18
addi    $t3, -0x21
addi    $t4, -0x21
move    $t2, $t1
jal     sub_8139C
move    $t5, $t4
move    $ra, $v1
lh      $t0, arg_92($fp)
lh      $t1, arg_96($fp)
lh      $t2, arg_90($fp)
lh      $t3, arg_94($fp)
sra     $a0, 16
sra     $a1, 16
sra     $a2, 16
sra     $a3, 16
move    $v1, $v0
beqz    $v1, locret_81394
move    $v0, $zero
slt     $at, $t0, $a0
bnez    $at, locret_81394
slt     $at, $t1, $a2
bnez    $at, locret_81394
slt     $at, $a1, $t2
bnez    $at, locret_81394
slt     $at, $a3, $t3
bnez    $at, locret_81394
nop
slti    $at, $v1, 9
bnez    $at, locret_81394
li      $v0, 0xFFFFFFFF
slt     $at, $a0, $t2
bnez    $at, locret_81394
slt     $at, $a2, $t3
bnez    $at, locret_81394
slt     $at, $t0, $a1
bnez    $at, locret_81394
slt     $at, $t1, $a3
bnez    $at, locret_81394
nop
li      $v0, 1

locret_81394:
jr      $ra
nop
#endif
	return v0;
}
