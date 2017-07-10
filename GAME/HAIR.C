#include "HAIR.H"

void InitialiseHair()//3AC70, 3B170
{
#if 0
	int i; // $a3
	int j; // $a2
	long *bone; // $a1
	struct HAIR_STRUCT *hptr; // $a0

	int a2 = 0;
	int v0 = 0x000B0000;
	int t6 = hairs+176;//hptr
	int t1 = 0xFFFFC000;
	int* t5 = &first_hair;
	int t4 = 1;
	int v0 = 0x001F0000;
	//? lw	$v1, dword_801F2C04, 0x1F2480 objects
	long* t3 = bones;//bone
	//long t2 = v1 << 2;

	//int a1 = t3 + t2;
	a1 += 16;
	v0 = a2 << 3;
	v0 -= a2;
	v0 <<= 5;
	a0 = v0 + t6;
	t0 = a2 + 1;
	a3 = 5;
	v0 = a2 << 2;
	v0 += 5;

	/*
	sh	$zero, 0xE($a0)
	sh	$t1, 0xC($a0)
	sw	$t4, 0($v0)
	*/

	/*
	loc_3ACD0://loop a3 j
	lw	$v0, 4($a1)
	nop
	sw	$v0, 0($a0)
	lw	$v1, 8($a1)
	addiu	$a3, -1
	sw	$v1, 4($a0)
	lw	$v0, 0xC($a1)
	addiu	$a1, 0x10
	sh	$t1, 0xC($a0)

	$a0 seems t0 be some meshtree/movable ptr
	sh	$zero, 0x10($a0)
	sh	$zero, 0xE($a0)
	sw	$zero, 0x1C($a0)
	sw	$zero, 0x18($a0)
	sw	$zero, 0x14($a0)
	sw	$v0, 8($a0)
	bgez	$a3, loc_3ACD0

	addiu	$a0, 0x20
	move	$a2, $t0
	slti	$v0, $a2, 2
	bnez	$v0, loc_3ACA0
	addu	$a1, $t3, $t2
	*/
#endif
}