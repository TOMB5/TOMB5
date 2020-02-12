#include "LARA1.H"

#include "DELSTUFF.H"
#include "LARA.H"
#include "MATHS.H"
#include "DRAW.H"
#include "SETUP.H"
#include "GTEREG.H"

void sub_2C(struct ITEM_INFO* item);

void DrawLara()
{
	sub_2C(lara_item);
}

void sub_1330(struct ITEM_INFO* item)
{
	struct object_info* object = &objects[item->object_number];
	//S_PrintNiceShadow(object->shadow_size, GLaraShadowframe, 0);
}

void sub_2C(struct ITEM_INFO* item)
{
	int i;
	int underwater_node = 0;//$v1
	int a1 = 0;
	int v0;
	int at;
	int v1;
	struct CVECTOR a0;
	int* s0;
	int a00;
	int j;//$t6

	//v0 = item->hit_points
	if (item->hit_points > 0)
	{
		sub_1330();
	}
	//loc_6C
	mPushMatrix();
	CalculateObjectLightingLara();
	//a0 = LaraNodeUnderwater
	a1 = 0;
	//a2 = 14
	//loc_8C
	//v0 = LaraNodeUnderwater[0];
	//a2--;
	for (i = 0; i < 15; i++)
	{
		if(LaraNodeUnderwater[i])
		{
			underwater_node = LaraNodeUnderwater[i];
			break;
		}
		a1 = 1;
	}
	//loc_A0
	if (a1 == 0)
	{
		v0 = RBK >> 5;
		at = GBK >> 5;
		v1 = BBK >> 5;

		if (v0 >= 0xFF)
		{
			v0 = 0xFF;
		}

		if (v1 >= 0xFF)
		{
			v1 = 0xFF;
		}

		if (at >= 0xFF)
		{
			at = 0xFF;
		}

		//loc_E4
		if (a1 >= 0xFF)
		{
			a1 = 0xFF;
		}

		//loc_F0
		at <<= 8;
		v1 <<= 16;
		v0 |= v1;
		v0 |= at;

		((int*)&LaraNodeAmbient[0].r)[0] = v0;
	}
	//loc_104
	//s5 = db.polyptr
	//s6 = db.ot[1]
	//s3 = lara_item
	s0 = &lara_mesh_sweetness_table[0];
	//s1 = &lara_matrices
	//s2 = 0xF
	//s4 = &NodesToStashFromScratch
	//s3 = lara_item->mesh_bits >> 16;

	//loc_138
	for(i = 0; i < 15; i++)///@TODO check < 15
	{
		int t0 = ((int*)& lara_matrices[i])[0];
		int t1 = ((int*)& lara_matrices[i])[1];
		int t2 = ((int*)& lara_matrices[i])[2];
		int t3 = ((int*)& lara_matrices[i])[3];

		R11 = t0 & 0xFFFF;
		R12 = (t0 >> 16) & 0xFFFF;

		R13 = t1 & 0xFFFF;
		R21 = (t1 >> 16) & 0xFFFF;

		R22 = t2 & 0xFFFF;
		R23 = (t2 >> 16) & 0xFFFF;

		R31 = t3 & 0xFFFF;
		R32 = (t3 >> 16) & 0xFFFF;

		t0 = ((int*)& lara_matrices[0])[4];
		t1 = ((int*)& lara_matrices[0])[5];
		t2 = ((int*)& lara_matrices[0])[6];
		t3 = ((int*)& lara_matrices[0])[7];

		R33 = t0;
		TRX = t1;
		TRY = t2;
		TRZ = t3;
		//a0 = &LaraNodeUnderwater[0];
		//a1 = 0xF - 
		if (LaraNodeUnderwater[a1 - 15])
		{
			a0 = LaraNodeAmbient[1];
		}
		else
		{
			a0 = LaraNodeAmbient[0];
		}
		//loc_1A0
		RBK = (((int*)& a0.r)[0] & 0xFF) << 4;
		GBK = ((((int*)& a0.r)[0] >> 4) & 0xFF0);
		BBK = ((((int*)& a0.r)[0] >> 12) & 0xFF0);

		a00 = *s0++;
		//v1 = &lara.mesh_ptrs[0];
		//a00 = &lara.mesh_ptrs[lara_mesh_sweetness_table[0]]
		//v0 = (lara_item->mesh_bits >> 16) & (1 << 0xF)

		if ((lara_item->mesh_bits >> 16) & (1 << 0xF))
		{
			//sub_658(lara.mesh_ptrs[lara_mesh_sweetness_table[0]]);

		}//loc_1FC

		//s2--;
		//int t7 = &NodesToStashFromScratch[0];
		int t6 = 4;
		//t0 = &tsv_buffer[0]
		//t1 = &SkinVertNums[0];

		//loc_218
		for (j = 0; j < 4; j++)
		{
			if (NodesToStashFromScratch[i][j] != 255)
			{
				//sub_C1C(NodesToStashFromScratch[i][j]);
			}
			else
			{
				//loc_238
				break;
			}
		}
	}
	//loc_238
#if 0
		lw      $s4, 0x1A94($gp)
		li      $s0, 0xA092C
		lh      $v0, 0x1F26C2
		lw      $v1, 0x204C($gp)
		sll     $v0, 2
		addu    $s1, $v1, $v0
		addiu   $s1, 8
		li      $s3, 0xA0910
		li      $s2, 0xE
		lw      $s4, 8($s4)

		loc_278:                                 # CODE XREF : sub_2C + 3F0↓j
		li      $v0, 1
		sllv    $v0, $s2
		and $v0, $s4, $v0
		beqz    $v0, loc_410
		nop
		li      $a0, 0xA2640
		li      $a2, 0xA0984
		li      $a1, 0xE
		subu    $a1, $s2
		addu    $a2, $a1
		lbu     $v0, 0($a2)
		nop
		add     $a0, $v0
		lbu     $v0, 0($a0)
		nop
		beqz    $v0, loc_2C8
		lw      $a0, 0x2084($gp)
		lw      $a0, 0x2088($gp)

		loc_2C8:                                 # CODE XREF : sub_2C + 290↑j
		nop
		andi    $v0, $a0, 0xFF
		sll     $v0, 4
		ctc2    $v0, $13
		srl     $v0, $a0, 4
		andi    $v0, 0xFF0
		ctc2    $v0, $14
		srl     $v0, $a0, 12
		andi    $v0, 0xFF0
		ctc2    $v0, $15
		lbu     $t2, 0($s0)
		li      $t0, 0x1ECDC0
		li      $t1, 0x1FA108
		jal     sub_C6C
		lbu     $a0, 0($s3)
		jal     sub_C6C
		lbu     $a0, 1($s3)
		sltiu   $at, $t2, 0xFF
		beqz    $at, loc_408
		sll     $v0, $t2, 5
		lbu     $v1, 1($s0)
		li      $t0, 0xA5D3C
		addu    $v0, $t0, $v0
		sll     $v1, 5
		addu    $v1, $t0, $v1
		lw      $t0, 0($v1)
		lw      $t1, 4($v1)
		lw      $t2, 8($v1)
		lw      $t3, 0xC($v1)
		lw      $t4, 0x10($v1)
		lw      $t5, 0x14($v1)
		lw      $t6, 0x18($v1)
		lw      $t7, 0x1C($v1)
		lh      $a0, 8($v0)
		sll     $a1, $t2, 16
		sra     $a1, 16
		mult    $a0, $a1
		lh      $a1, 2($v0)
		lh      $a2, 2($v1)
		mflo    $a0
		sra     $at, $a0, 1
		addu    $a0, $at
		mult    $a1, $a2
		lh      $a1, 0xE($v0)
		lh      $a2, 0xE($v1)
		mflo    $at
		addu    $a0, $at
		ctc2    $t0, $0
		mult    $a1, $a2
		ctc2    $t1, $1
		ctc2    $t2, $2
		ctc2    $t3, $3
		ctc2    $t4, $4
		ctc2    $t5, $5
		ctc2    $t6, $6
		ctc2    $t7, $7
		mflo    $a1
		addu    $a0, $a1
		sra     $a0, 12
		mult    $a0, $a0
		move    $t0, $a0
		mflo    $a0
		lui     $a1, 0x100
		jal     mSqrt
		subu    $a0, $a1, $a0
		move    $a0, $t0
		jal     phd_atan_asm
		move    $a1, $v0
		li      $at, 0xD
		beq     $s2, $at, loc_3F8
		li      $at, 0xA
		bne     $s2, $at, loc_3FC
		nop

		loc_3F8 : # CODE XREF : sub_2C + 3BC↑j
		negu    $v0, $v0

		loc_3FC : # CODE XREF : sub_2C + 3C4↑j
		sra     $a0, $v0, 1
		jal     sub_CBC
		negu    $a0, $a0

		loc_408 : # CODE XREF : sub_2C + 2EC↑j
		jal     sub_658
		lw      $a0, 0($s1)

		loc_410 : # CODE XREF : sub_2C + 258↑j
		addiu   $s1, 8
		addiu   $s2, -1
		addiu   $s3, 2
		bnez    $s2, loc_278
		addiu   $s0, 2
		addiu   $s4, 1
		bnez    $s4, loc_538
		addiu   $s6, -4
		lbu     $v0, 0x208C($gp)
		nop
		beqz    $v0, loc_444
		lw      $a0, 0x2084($gp)
		lw      $a0, 0x2088($gp)

		loc_444:                                 # CODE XREF : sub_2C + 40C↑j
		nop
		andi    $v0, $a0, 0xFF
		sll     $v0, 4
		ctc2    $v0, $13
		srl     $v0, $a0, 4
		andi    $v0, 0xFF0
		ctc2    $v0, $14
		srl     $v0, $a0, 12
		andi    $v0, 0xFF0
		ctc2    $v0, $15
		lhu     $v0, 0x5304($gp)
		li      $v1, 0x1F2480
		sll     $v0, 6
		addu    $v0, $v1
		lh      $v0, 2($v0)
		lw      $v1, 0x204C($gp)
		sll     $v0, 2
		addu    $s0, $v1, $v0
		addiu   $s0, 0x20  # ' '
		li      $v1, 0xA5D5C
		lw      $t0, 0($v1)
		lw      $t1, 4($v1)
		lw      $t2, 8($v1)
		lw      $t3, 0xC($v1)
		lw      $t4, 0x10($v1)
		lw      $t5, 0x14($v1)
		lw      $t6, 0x18($v1)
		lw      $t7, 0x1C($v1)
		ctc2    $t0, $0
		ctc2    $t1, $1
		ctc2    $t2, $2
		ctc2    $t3, $3
		ctc2    $t4, $4
		ctc2    $t5, $5
		ctc2    $t6, $6
		ctc2    $t7, $7
		jal     sub_658
		lw      $a0, 0($s0)
		addiu   $s0, 0x20  # ' '
		li      $v1, 0xA5DBC
		lw      $t0, 0($v1)
		lw      $t1, 4($v1)
		lw      $t2, 8($v1)
		lw      $t3, 0xC($v1)
		lw      $t4, 0x10($v1)
		lw      $t5, 0x14($v1)
		lw      $t6, 0x18($v1)
		lw      $t7, 0x1C($v1)
		ctc2    $t0, $0
		ctc2    $t1, $1
		ctc2    $t2, $2
		ctc2    $t3, $3
		ctc2    $t4, $4
		ctc2    $t5, $5
		ctc2    $t6, $6
		ctc2    $t7, $7
		jal     sub_658
		lw      $a0, 0($s0)

		loc_538:                                 # CODE XREF : sub_2C + 3FC↑j
		lhu     $v0, 0x5254($gp)
		li      $v1, 0x1F2480
		beqz    $v0, loc_5D0
		sll     $v0, 6
		addu    $v0, $v1
		lw      $a2, 4($v0)
		lw      $v1, 0x2030($gp)
		sll     $a2, 2
		addu    $a2, $v1
		lh      $v0, 2($v0)
		lw      $v1, 0x204C($gp)
		sll     $v0, 2
		addu    $s0, $v1, $v0
		li      $v1, 0xA5E1C
		lw      $t0, 0($v1)
		lw      $t1, 4($v1)
		lw      $t2, 8($v1)
		lw      $t3, 0xC($v1)
		lw      $t4, 0x10($v1)
		lw      $t5, 0x14($v1)
		lw      $t6, 0x18($v1)
		lw      $t7, 0x1C($v1)
		ctc2    $t0, $0
		ctc2    $t1, $1
		ctc2    $t2, $2
		ctc2    $t3, $3
		ctc2    $t4, $4
		ctc2    $t5, $5
		ctc2    $t6, $6
		ctc2    $t7, $7
		lw      $a0, 0xD4($a2)
		lw      $a1, 0xD8($a2)
		jal     sub_1358
		lw      $a2, 0xDC($a2)
		jal     sub_658
		lw      $a0, 0x70($s0)

		loc_5D0:                                 # CODE XREF : sub_2C + 518↑j
		jal     0x76520
		nop
		lbu     $v0, 0xA2648
		nop
		beqz    $v0, loc_5F0
		lw      $a0, 0x2084($gp)
		lw      $a0, 0x2088($gp)

		loc_5F0:                                 # CODE XREF : sub_2C + 5B8↑j
		nop
		andi    $v0, $a0, 0xFF
		sll     $v0, 4
		ctc2    $v0, $13
		srl     $v0, $a0, 4
		andi    $v0, 0xFF0
		ctc2    $v0, $14
		srl     $v0, $a0, 12
		andi    $v0, 0xFF0
		ctc2    $v0, $15
		jal     sub_E38
		nop
		jal     sub_1184
		nop
		sw      $s5, 0x3644($gp)
		lw      $ra, 0x60 + var_50($sp)
		lw      $s0, 0x60 + var_4C($sp)
		lw      $s1, 0x60 + var_48($sp)
		lw      $s2, 0x60 + var_44($sp)
		lw      $s3, 0x60 + var_40($sp)
		lw      $s4, 0x60 + var_3C($sp)
		lw      $s5, 0x60 + var_38($sp)
		lw      $s6, 0x60 + var_34($sp)
		lw      $s7, 0x60 + var_30($sp)
		jr      $ra
		addiu   $sp, 0x60
		# End of function sub_2C
#endif
}