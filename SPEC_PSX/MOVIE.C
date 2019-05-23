#include "MOVIE.H"

#include "CONTROL.H"
#include <LIBETC.H>

int S_PlayFMV(int sequence, int flag)//*, (<)5E7A0
{
	DISPENV disp;//interp@var_48
	//s1 = fmv_index
	//s2 = flag; //maybe skippable?
	//v0 = 7;

	if (sequence != FMV_NEXT_GENERATION_PREVIEW)
	{
		//v0 = 1
		if (FmvSceneTriggered & (1 << sequence))
		{
			return 1;
		}

		FmvSceneTriggered |= (1 << sequence);
	}

	//5E7F8
	FMV_InitialiseVRAM();

	VSync(0);

	SetDefDispEnv(&disp, 0, 0, 480, 240);

	//a2 = disp.disp.w 
	//v1 = 0x55555556
	//a2 = disp.disp.w * 2
#if 0
		mult    $a2, $v1
		addiu   $a0, $sp, 0x60 + var_48
		addiu   $a1, $s0, 0x5EE0
		lhu     $a3, 0xFA($a1)
		lhu     $t0, 0xFE($a1)
		li      $v0, 1
		sb      $v0, 0x60 + var_37($sp)
		sra     $a2, 31
		sh      $a3, 0x60 + var_3E($sp)
		sh      $t0, 0x60 + var_3A($sp)
		mfhi    $v1
		subu    $v1, $a2
		jal     PutDispEnv
		sh      $v1, 0x60 + disp.disp.w($sp)

		sll     $v1, $s1, 2
		addiu   $v0, $gp, 0x2E4C
		addu    $v1, $v0
		li      $a0, 0xFFFFFFFF
		lw      $v1, 0($v1)
		nop
		bne     $v1, $a0, loc_5E894
		move    $s5, $s0
		j       loc_5EBBC
		move    $v0, $zero

		loc_5E894 :
	move    $a0, $v1
		addiu   $s0, $sp, 0x60 + var_28
		jal     sub_6915C
		move    $a1, $s0
		li      $v1, 0xB2940
		lui     $v0, 2
		sw      $v1, 0x2EBC($gp)
		addu    $v1, $v0
		sw      $v1, 0x2E6C($gp)
		addiu   $v1, 0x2D00
		move    $a1, $zero
		lui     $a2, 2
		sll     $v0, $s1, 1
		addiu   $a3, $gp, 0xB10
		addu    $v0, $a3
		lw      $a0, 0x2EBC($gp)
		lhu     $t0, 0($v0)
		sw      $v1, 0x2E70($gp)
		sh      $t0, 0x2EBA($gp)
		jal     sub_5F5C8
		la      $a2, loc_25A00
		bnez    $s2, loc_5E920
		nop
		jal     sub_5F4F8
		nop
		lui     $a0, 2
		jal     sub_5F544
		la      $a0, loc_20400
		lui     $a0, 2
		sw      $v0, 0x2E74($gp)
		jal     sub_5F544
		la      $a0, loc_20400
		j       loc_5E944
		nop

		loc_5E920 :
	jal     sub_2D430
		nop
		lui     $a0, 2
		jal     sub_2D454
		la      $a0, loc_20400
		lui     $a0, 2
		sw      $v0, 0x2E74($gp)
		jal     sub_2D454
		la      $a0, loc_20400

		loc_5E944 :
	sw      $v0, 0x2E78($gp)
		move    $a1, $zero
		lui     $a2, 4
		lw      $a0, 0x2E74($gp)
		jal     sub_5F5C8
		la      $a2, loc_40800
		addiu   $a0, $gp, 0x2E7C
		move    $a1, $zero
		move    $a2, $zero
		move    $a3, $zero
		li      $v0, 0xF0
		jal     sub_5EBE0
		sw      $v0, 0x60 + var_50($sp)
		move    $a0, $s0
		lui     $a1, 6
		jal     sub_5EC3C
		la      $a1, sub_5ECB4
		jal     sub_656F0
		nop
		addiu   $s3, $gp, 0x2E7C
		addiu   $s2, $gp, 0x2E88
		j       loc_5E9BC
		nop

		loc_5E9A0 :
	lwl     $v0, 0x60 + var_25($sp)
		lwr     $v0, 0x60 + var_28($sp)
		nop
		swl     $v0, 0x60 + var_2D($sp)
		swr     $v0, 0x60 + var_30($sp)
		jal     sub_5F018
		addiu   $a0, $sp, 0x60 + var_30

		loc_5E9BC :
	addiu   $a0, $gp, 0x2E7C
		jal     sub_5EDFC
		nop
		li      $v1, 0xFFFFFFFF
		beq     $v0, $v1, loc_5E9A0
		nop
		sb      $zero, 0x2EB8($gp)
		jal     sub_5F060
		move    $a0, $zero
		li      $s4, 1
		li      $s1, 0xFFFFFFFF

		loc_5E9E8:
	lw      $v0, 0x2E84($gp)
		nop
		sll     $v0, 2
		addu    $v0, $s3
		lw      $a0, 0($v0)
		jal     sub_6D508
		li      $a1, 3
		lh      $a1, 0x2EAC($gp)
		lh      $v1, 0x2EAE($gp)
		nop
		mult    $a1, $v1
		lw      $v0, 0x2E90($gp)
		nop
		sll     $v0, 2
		addu    $v0, $s2
		lw      $a0, 0($v0)
		mflo    $a1
		srl     $v1, $a1, 31
		addu    $a1, $v1
		jal     sub_6D584
		sra     $a1, 1
		j       loc_5EA84
		nop

		loc_5EA44 :
	jal     sub_66E7C
		addiu   $a0, $sp, 0x60 + var_30
		lhu     $v1, 0x2EBA($gp)
		nop
		slt     $v1, $v0
		bnez    $v1, loc_5EA68
		addiu   $a0, $sp, 0x60 + var_30
		bgtz    $v0, loc_5EA7C
		nop

		loc_5EA68 :
	lwl     $v0, 0x60 + var_25($sp)
		lwr     $v0, 0x60 + var_28($sp)
		nop
		swl     $v0, 0x60 + var_2D($sp)
		swr     $v0, 0x60 + var_30($sp)

		loc_5EA7C :
		jal     sub_5F018
		nop

		loc_5EA84 :
	addiu   $a0, $gp, 0x2E7C
		jal     sub_5EDFC
		nop
		beq     $v0, $s1, loc_5EA44
		nop
		addiu   $a0, $gp, 0x2E7C
		jal     sub_5EF84
		move    $a1, $zero
		jal     sub_6A1FC
		move    $a0, $zero
		addiu   $a0, $sp, 0x60 + var_48
		move    $a1, $zero
		li      $a3, 0x1E0
		lw      $v1, 0x2EA4($gp)
		li      $v0, 0xF0
		sw      $v0, 0x60 + var_50($sp)
		sltiu   $v1, 1
		sll     $a2, $v1, 4
		subu    $a2, $v1
		jal     sub_6AF3C
		sll     $a2, 4
		lui     $a1, 0x5555
		lh      $a2, 0x60 + disp.disp.w($sp)
		li      $a1, 0x55555556
		sll     $a2, 1
		mult    $a2, $a1
		addiu   $a0, $sp, 0x60 + var_48
		addiu   $v1, $s5, 0x5EE0
		lhu     $a3, 0xFA($v1)
		lhu     $t0, 0xFE($v1)
		li      $v0, 1
		sb      $v0, 0x60 + var_37($sp)
		sra     $a2, 31
		sh      $a3, 0x60 + var_3E($sp)
		sh      $t0, 0x60 + var_3A($sp)
		mfhi    $a1
		subu    $a1, $a2
		jal     PutDispEnv
		sh      $a1, 0x60 + disp.disp.w($sp)
		lbu     $v1, 0x2EB8($gp)
		li      $s0, 1
		beq     $v1, $s0, loc_5EB80
		nop
		sw      $s0, dword_A3B0C
		jal     S_UpdateInput
		nop
		lbu     $v0, byte_A335A
		nop
		beqz    $v0, loc_5E9E8
		nop
		lw      $v1, dword_800A6020
		nop
		andi    $v0, $v1, 0x4009
		beqz    $v0, loc_5E9E8
		andi    $v0, $v1, 9
		sw      $zero, 0x2EB4($gp)
		sb      $s0, 0x2EB8($gp)
		beqz    $v0, loc_5EB80
		nop
		li      $s4, 2

		loc_5EB80:
	jal     sub_5F060//custom core code
		li      $a0, 1
		jal     sub_5F160//unknown
		nop
		jal     sub_6D5A4//unknown
		move    $a0, $zero
		jal     sub_66D70//unknown
		nop
		li      $a0, 9
		move    $a1, $zero
		jal     CdControlB
		move    $a2, $zero
		sw      $zero, dword_A3B0C
		move    $v0, $s4

		loc_5EBBC :
	lw      $ra, 0x60 + var_8($sp)
		lw      $s5, 0x60 + var_C($sp)
		lw      $s4, 0x60 + var_10($sp)
		lw      $s3, 0x60 + var_14($sp)
		lw      $s2, 0x60 + var_18($sp)
		lw      $s1, 0x60 + var_1C($sp)
		lw      $s0, 0x60 + var_20($sp)
		jr      $ra
		addiu   $sp, 0x60
#endif

	return -1;//TODO @retval
}


void FMV_InitialiseVRAM()//*, 5F160(<) (F)
{
	RECT rect;

	rect.x = 0;
	rect.y = 0;
	rect.w = 512;
	rect.h = 256;

	ClearImage(&rect, 0, 0, 0);

	rect.y = 240;
	ClearImage(&rect, 0, 0, 0);

	DrawSync(0);

	return;
}