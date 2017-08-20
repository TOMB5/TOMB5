#include "MEMCARD.H"

#include "SPECIFIC.H"

#ifdef PSX
	#include <LIBMCRD.H>
#endif

unsigned char mcInit;
unsigned char mcStatus;
unsigned long mcNumFiles;
unsigned char mcBlocksFree;
char mcFileNames[7][20];
int mcFileLengths[7];
static unsigned char mcActualStatus;

void mcDir()//61EE8
{
	int i; // $s3
	int j; // $s4
	int k; // $s1
	struct DIRENTRY* dir;

#if 0

	sub_61EE8:

			 var_20 = -0x20
				 var_1C = -0x1C
				 var_18 = -0x18
				 var_14 = -0x14
				 var_10 = -0x10
				 var_C = -0xC
				 var_8 = -8
				 var_4 = -4

				 addiu	$sp, -0x30
				 move	$a0, $zero
				 la	$a1, dword_A1AA0
				 lui	$v0, 0x1F
				 sw	$s2, 0x30 + var_10($sp)
				 addiu	$s2, $v0, -0x3240
				 move	$a2, $s2
				 sw	$s0, 0x30 + var_18($sp)
				 li	$s0, 0xF
				 addiu	$a3, $gp, 0x41E0
				 sw	$ra, 0x30 + var_4($sp)
				 sw	$s4, 0x30 + var_8($sp)
				 sw	$s3, 0x30 + var_C($sp)
				 sw	$s1, 0x30 + var_14($sp)
				 sw	$zero, 0x30 + var_20($sp)
				 jal	sub_6B08C
				 sw	$s0, 0x30 + var_1C($sp)
				 move	$s4, $zero
				 move	$s3, $zero
				 lw	$v0, 0x41E0($gp)
				 sb	$s0, 0x41DC($gp)
				 beqz	$v0, loc_62028
				 move	$s1, $zero
				 move	$s0, $s2
				 addiu	$s2, $gp, 0x41E4

				 loc_61F50:
			 lw	$v0, 0x18($s0)
				 nop
				 addiu	$v1, $v0, 0x1FFF
				 bgez	$v1, loc_61F68
				 move	$a1, $s0
				 addiu	$v1, $v0, 0x3FFE

				 loc_61F68:
			 sra	$v1, 13
				 lbu	$v0, 0x41DC($gp)
				 lw	$a0, dword_800A202C
				 subu	$v0, $v1
				 sb	$v0, 0x41DC($gp)
				 lhu	$v1, 0x194($a0)
				 lw	$a0, dword_800A203C
				 li	$a2, 0xC
				 jal	sub_68A84
				 addu	$a0, $v1
				 bnez	$v0, loc_62014
				 nop
				 lwl	$v0, 3($s0)
				 lwr	$v0, 0($s0)
				 lwl	$v1, 7($s0)
				 lwr	$v1, 4($s0)
				 lwl	$a0, 0xB($s0)
				 lwr	$a0, 8($s0)
				 lwl	$a1, 0xF($s0)
				 lwr	$a1, 0xC($s0)
				 swl	$v0, 3($s2)
				 swr	$v0, 0($s2)
				 swl	$v1, 7($s2)
				 swr	$v1, 4($s2)
				 swl	$a0, 0xB($s2)
				 swr	$a0, 8($s2)
				 swl	$a1, 0xF($s2)
				 swr	$a1, 0xC($s2)
				 lwl	$v0, 0x13($s0)
				 lwr	$v0, 0x10($s0)
				 nop
				 swl	$v0, 0x13($s2)
				 swr	$v0, 0x10($s2)
				 addiu	$s2, 0x14
				 sll	$v0, $s4, 2
				 addiu	$s4, 1
				 addiu	$s1, 1
				 addiu	$v1, $gp, 0x4274
				 lw	$a0, 0x18($s0)
				 addu	$v0, $v1
				 sw	$a0, 0($v0)

				 loc_62014:
			 lw	$v0, 0x41E0($gp)
				 addiu	$s3, 1
				 sltu	$v0, $s3, $v0
				 bnez	$v0, loc_61F50
				 addiu	$s0, 0x28

				 loc_62028 :
				 lw	$ra, 0x30 + var_4($sp)
				 lw	$s4, 0x30 + var_8($sp)
				 lw	$s3, 0x30 + var_C($sp)
				 lw	$s2, 0x30 + var_10($sp)
				 sw	$s1, 0x41E0($gp)
				 lw	$s1, 0x30 + var_14($sp)
				 lw	$s0, 0x30 + var_18($sp)
				 jr	$ra
				 addiu	$sp, 0x30
				 # End of function sub_61EE8
#endif

}

void mcOpen(int sync)//6204C(<), 62730(<) (F)
{
	int i;

	mcInit = 1;
	mcNumFiles = 0;
	mcBlocksFree = 0;
	mcStatus = 4;
	mcActualStatus = 0;

#ifdef PSX
	MemCardStart();
#endif

	if (sync != 0)
	{
		for (i = 0; i < 4; i++)
		{
			//loc_62084
			mcGetStatus();
#ifdef PSX
			VSync(0);
#endif
		}
	}

	//loc_6209C
	return;
}

void mcClose()//620AC
{
#ifdef PSX
	MemCardStop();

	mcInit = 0;
#else
	S_Warn("[mcClose] - Unimplemented\n");
#endif

	return;
}

unsigned char mcGetStatus()//620CC, 
{
	long stat; // $a0
	unsigned long cmd; // stack offset -16
	unsigned long res; // stack offset -12
#if 0

	sub_620CC:

			 var_10 = -0x10
				 var_C = -0xC
				 var_8 = -8
				 var_4 = -4

				 addiu	$sp, -0x20
				 li	$a0, 1
				 addiu	$a1, $sp, 0x20 + var_10
				 addiu	$a2, $sp, 0x20 + var_C
				 sw	$ra, 0x20 + var_4($sp)
				 jal	sub_6B2FC
				 sw	$s0, 0x20 + var_8($sp)
				 move	$a0, $v0
				 beqz	$a0, loc_62130
				 li	$v0, 3
				 bgtz	$a0, loc_62110
				 li	$v0, 1
				 li	$v0, 0xFFFFFFFF
				 beq	$a0, $v0, loc_62120
				 nop
				 j	loc_622C4
				 nop

				 loc_62110 :
			 beq	$a0, $v0, loc_62178
				 li	$v0, 2
				 j	loc_622C4
				 nop

				 loc_62120 :
			 jal	sub_6A360
				 move	$a0, $zero
				 j	loc_622C4
				 nop

				 loc_62130 :
			 lw	$v1, 0x20 + var_10($sp)
				 nop
				 bne	$v1, $v0, loc_62150
				 li	$v0, 6
				 li	$v0, 5
				 sb	$v0, 0x4270($gp)
				 j	loc_622C4
				 nop

				 loc_62150 :
			 bne	$v1, $v0, loc_62164
				 li	$v0, 2
				 sb	$v1, 0x4270($gp)
				 j	loc_622C4
				 nop

				 loc_62164 :
			 bne	$v1, $v0, loc_622C4
				 li	$v0, 4
				 sb	$v0, 0x4270($gp)
				 j	loc_622C4
				 nop

				 loc_62178 :
			 lw	$v1, 0x20 + var_10($sp)
				 nop
				 beq	$v1, $v0, loc_62210
				 sltiu	$v0, $v1, 3
				 beqz	$v0, loc_621A0
				 li	$s0, 3
				 beq	$v1, $a0, loc_621B8
				 nop
				 j	loc_622C4
				 nop

				 loc_621A0 :
			 beq	$v1, $s0, loc_6227C
				 li	$v0, 6
				 beq	$v1, $v0, loc_62298
				 nop
				 j	loc_622C4
				 nop

				 loc_621B8 :
			 lw	$v1, 0x20 + var_C($sp)
				 nop
				 beqz	$v1, loc_621D8
				 li	$v0, 3
				 beq	$v1, $v0, loc_621EC
				 li	$v0, 1
				 j	loc_62204
				 nop

				 loc_621D8 :
			 lbu	$v0, 0x41D8($gp)
				 nop
				 sb	$v0, 0x4270($gp)
				 j	loc_622C4
				 nop

				 loc_621EC :
			 jal	sub_6A6E4
				 move	$a0, $zero
				 li	$v1, 4
				 sb	$v1, 0x4270($gp)
				 j	loc_622C4
				 nop

				 loc_62204 :
			 sb	$v0, 0x4270($gp)
				 j	loc_622C4
				 nop

				 loc_62210 :
			 lw	$a0, 0x20 + var_C($sp)
				 li	$v0, 3
				 beq	$a0, $v0, loc_62248
				 sltiu	$v0, $a0, 4
				 beqz	$v0, loc_62238
				 li	$v0, 4
				 beqz	$a0, loc_6228C
				 li	$v0, 3
				 j	loc_6226C
				 nop

				 loc_62238 :
			 beq	$a0, $v0, loc_6225C
				 li	$v0, 3
				 j	loc_6226C
				 nop

				 loc_62248 :
			 jal	sub_61EE8
				 nop
				 sb	$zero, 0x41D8($gp)
				 j	loc_6228C
				 nop

				 loc_6225C :
			 sb	$v1, 0x4270($gp)
				 sb	$v1, 0x41D8($gp)
				 j	loc_622C4
				 nop

				 loc_6226C :
			 sb	$v0, 0x4270($gp)
				 sb	$v0, 0x41D8($gp)
				 j	loc_622C4
				 nop

				 loc_6227C :
			 lw	$v0, 0x20 + var_C($sp)
				 nop
				 bnez	$v0, loc_622B8
				 nop

				 loc_6228C :
			 sb	$zero, 0x4270($gp)
				 j	loc_622C4
				 nop

				 loc_62298 :
			 lw	$v0, 0x20 + var_C($sp)
				 nop
				 bnez	$v0, loc_622B8
				 nop
				 jal	sub_61EE8
				 nop
				 j	loc_6228C
				 nop

				 loc_622B8 :
			 jal	sub_6A6E4
				 move	$a0, $zero
				 sb	$s0, 0x4270($gp)

				 loc_622C4 :
				 lbu	$v0, 0x4270($gp)
				 lw	$ra, 0x20 + var_4($sp)
				 lw	$s0, 0x20 + var_8($sp)
				 jr	$ra
				 addiu	$sp, 0x20
				 # End of function sub_620CC
#endif

				 return -1;
}

long mcFormat()//622D8(<), 629BC(<) (F)
{
	unsigned long cmd;
	unsigned long res;

#ifdef PSX
	MemCardSync(0, &cmd, &res);

	res = MemCardFormat(0);
	if (res == 0)
	{
		mcActualStatus = 0;
		mcDir();
	}
#else
	S_Warn("[mcFormat] - Unimplemented!\n");
#endif

	//loc_6230C
	return res;
}