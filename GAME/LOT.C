#include "LOT.H"
#include "SPECIFIC.H"

int slots_used;
short nAIObjects;
struct AIOBJECT* AIObjects;
struct creature_info* baddie_slots;

void CreateZone(struct ITEM_INFO *item)//4E330, 4E794
{
	S_Warn("[CreateZone] - Unimplemented!\n");
}


//Only called when enemy is triggered
void InitialiseSlot(short item_number /*$s0*/, int slot /*$a1*/)//4E13C, 4E5A0
{
#if 0
	int i; // $s1
	struct creature_info *creature; // $s0

	int a2 = 3;
	int v0 = a1 << 3;//a1 param?
	v0 -= a1;
	v0 <<= 3;
	v0 += a1;
	v0 <<= 2;

	struct creature_info* creature = &baddie_slots[0];//v1

	a0 <<= 16;

	s0 = a0 >> 16;

	int t2 = v1 + v0;
	a1 = t2 + 6;
	v0 = s0 << 3;
	v0 += s0;

	struct creature_info* v1 = &items[0];
	v0 <<= 4;
	s1 = v1 + v0;

	//sw	$t2, 0x3C($s1)
	//sh	$s0, 0xAA($t2)
	//sw	$zero, 0x10($t2)	
	a1[0] = 0; //SHORT//sh	$zero, 0($a1)

	loc_4E19C:
		sh	$zero, 0($a1)
		addiu	$a2, -1
			addiu	$a1, -2
		bgez	$a2, loc_4E19C
		
		li	$v0, 0xB6
		sh	$v0, 8($t2)
		li	$v0, 0x100
		li	$v1, 0xFFFFFE00
		sh	$v0, 0xC4($t2)
		li	$v0, 0x4000
		sh	$v0, 0xC2($t2)
		li	$v0, 1
		li	$t1, 0xFFFFFFFE
		li	$t0, 0xFFFFFFFD
		sw	$v0, 0xE0($t2)
		li	$v0, 0xFFFFFFFB
		li	$a3, 0xFFFFFFF7
		li	$a2, 0xFFFFFFEF
		li	$a0, 0xFFFFFFBF
		sh	$v1, 0xC6($t2)
		lw	$v1, 0xC($t2)
		li	$a1, 0xFFFFFF7F
		sh	$zero, 0xA($t2)
		sw	$zero, 0x14($t2)
		sh	$zero, 0xCE($t2)
		and	$v1, $t1
		and	$v1, $t0
		and	$v1, $v0
		and	$v1, $a3
		and	$v1, $a2
		li	$v0, 0xFFFFFFDF
		and	$v1, $v0
		and	$v1, $a0
		lw	$v0, 0xD0($t2)
		and	$v1, $a1
		sw	$v1, 0xC($t2)
		and	$v0, $t1
		and	$v0, $t0
		and	$v0, $a3
		and	$v0, $a2
		sw	$v0, 0xD0($t2)
		lhu	$v1, 0xC($s1)
		nop
		addiu	$v1, -0x1F
		sll	$v1, 16
		sra	$v1, 16
		sltiu	$v0, $v1, 0x33	 # switch 51 cases
		beqz	$v0, def_4E274	 # jumptable 0004E274 default case
		lui	$v0, 0xA
		la	$v0, jpt_4E274
		sll	$v1, 2
		addu	$v1, $v0
		lw	$a0, 0($v1)
		nop
		jr	$a0		 # switch jump
		nop

	loc_4E27C : # jumptable 0004E274 cases 0, 6, 20, 22
				li	$v0, 0x400
				sh	$v0, 0xC4($t2)
				lw	$v0, 0xD0($t2)
				li	$v1, 0xFFFFFC00
				sh	$v1, 0xC6($t2)
				li	$v1, 3
				sw	$v1, 0xE0($t2)
				ori	$v0, 1
				j	def_4E274	 # jumptable 0004E274 default case
				sw	$v0, 0xD0($t2)

			loc_4E2A4:		 # jumptable 0004E274 case 36
							 li	$v0, 0x400
							 sh	$v0, 0xC4($t2)
							 lw	$v0, 0xD0($t2)
							 li	$v1, 0xFFFFFC00
							 sh	$v1, 0xC6($t2)
							 li	$v1, 3
							 sw	$v1, 0xE0($t2)
							 ori	$v0, 3
							 j	def_4E274	 # jumptable 0004E274 default case
							 sw	$v0, 0xD0($t2)

						 loc_4E2CC:		 # jumptable 0004E274 cases 12, 40, 44, 48, 50
										 li	$v0, 0x5000
										 li	$v1, 0xFFFFB000
										 sh	$v0, 0xC4($t2)
										 li	$v0, 0x10
										 sh	$v1, 0xC6($t2)
										 li	$v1, 4
										 sh	$v0, 0xCE($t2)
										 sw	$v1, 0xE0($t2)

									 def_4E274:		 # jumptable 0004E274 default case
													 jal	sub_4E4A0
													 addiu	$a0, $t2, 0xB8
													 lui	$v0, 0xA
													 lh	$v1, word_800A57DC
													 nop
													 beq	$s0, $v1, loc_4E310
													 nop
													 jal	sub_4E330
													 move	$a0, $s1

												 loc_4E310 :
	lw	$v0, 0xC80($gp)
		lw	$ra, 0x20 + var_8($sp)
		lw	$s1, 0x20 + var_C($sp)
		lw	$s0, 0x20 + var_10($sp)
		addiu	$v0, 1
		sw	$v0, 0xC80($gp)
		jr	$ra
		addiu	$sp, 0x20
		# End of function sub_4E13C

#endif

}

int EnableBaddieAI(short item_number, int Always)//4DF0C, 4E370
{
	S_Warn("[EnableBaddieAI] - Unimplemented!\n");
	return 0;
}

void DisableBaddieAI(short item_num)//4DEC0, 4E324
{
	S_Warn("[DisableBaddieAI] - Unimplemented!\n");
}

void InitialiseLOTarray(int allocmem)//4DE40, 4E2A4
{
	S_Warn("[InitialiseLOTarray] - Unimplemented!\n");
}
