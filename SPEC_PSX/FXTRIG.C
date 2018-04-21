#include "FXTRIG.H"

#include "SPECIFIC.H"

#include <STDIO.H>

#if 0
void PrintString(unsigned short x, unsigned short y, unsigned char colourFlag, char* string, unsigned short flag)//8DB4C, 8FB90
{

	long s0, s4, s3, at, s6, s2, v0;
	char* s5;
	unsigned short buf[64];//TODO check size
						   ///@TODO unk is type (3 is red) also as byte
	s0 = x;
	s4 = y;
	s3 = colourFlag & 0xFF;
	s5 = string;
	s6 = 0xA000;//?????$50($sp)
	at = GnFrameCounter;

	at &= 0x10;
	if (s6 & 0x2000 && GnFrameCounter & 0x10)
	{
		return;
	}

	//loc_8DBA0
	ScaleFlag = (s6 >> 12) & 1;

	v0 = GetStringLength(string, 0, &buf[0]);///@FIXME - ret is 65 on first call (Retail)

											 //Unpick @sub_8DD90
	if (s6 & 0x8000)
	{
		s2 = s0 - (v0 >> 1);
	}
	else if (s6 & 0x4000)
	{
		s2 = s0 - v0;
	}
	else
	{
		s2 = s0;
	}
	//@ret jr ra +0x190(base 0x8FC000)
	//0x0008FD9C (RETAIL)

	a0 = *s5++;
	//v0 = 0xA;

	if (a0 == 0)
	{
		//sb, 0 1284(gp)
		return;
	}

	//0x8FC08
	//v0 = 0x20
	if (a0 == 0xA)
	{
		//v0 = *s5;
		//a1 = sp+0x12
		//a0 = s5;
		//if(v0 == a0)
		//{
		//$sp+0x10 = 0;

		//}
	}

	if (a0 == 0x20)
	{
	}

	if (a0 == 0x9)
	{

	}

	if (a0 < 0x14)
	{

	}

	if (a0 - 0x80 < 0x2E)
	{

	}
	//loc_8DCDC
#if 0
	move	$a0, $s5
		move	$a1, $zero
		jal	sub_8DEDC
		addiu	$a2, $sp, 0x40 + var_30
		jal	sub_8DD90
		addiu	$ra, 0x190

		loc_8DBC4:
	bne	$a0, $v0, loc_8DC14
		li	$v0, 0x20
		lbu	$v0, 0($s5)
		addiu	$a1, $sp, 0x40 + var_2E
		bne	$v0, $a0, loc_8DBE8
		move	$a0, $s5
		sh	$zero, 0x40 + var_30($sp)
		j	loc_8DD54
		addiu	$s4, 0x10

		loc_8DBE8:
	jal	sub_8DEDC
		addiu	$a2, $sp, 0x40 + var_2C
		jal	sub_8DD90
		lhu	$v1, 0x40 + var_30($sp)
		lhu	$v0, 0x40 + var_2E($sp)
		lhu	$a0, 0x40 + var_2C($sp)
		subu	$v1, $v0
		addiu	$v1, 2
		addu	$s4, $v1
		j	loc_8DD54
		sh	$a0, 0x40 + var_30($sp)

		loc_8DC14:
	bne	$a0, $v0, loc_8DC30
		li	$v0, 9
		andi	$v0, $s6, 0x1000
		bnez	$v0, loc_8DD54
		addiu	$s2, 6
		j	loc_8DD54
		addiu	$s2, 2

		loc_8DC30:
	bne	$a0, $v0, loc_8DC40
		sltiu	$v0, $a0, 0x14
		j	loc_8DD54
		addiu	$s2, 0x28

		loc_8DC40 :
		beqz	$v0, loc_8DC50
		addiu	$v0, $a0, -1
		j	loc_8DD54
		andi	$s3, $v0, 0xFF

		loc_8DC50 :
		addiu	$v0, $a0, -0x80
		sltiu	$v1, $v0, 0x2E
		beqz	$v1, loc_8DCDC
		sll	$v0, 1
		la	$t1, aUEAAAAEEEAAEOO  #	" u^e\\a]a^a[a\\{ e]e^e[|^|]|[A^A]E\\   "...
		addu	$t1, $v0
		lbu	$v1, -1($t1)
		la	$s1, (loc_92020 + 1)
		sll	$v0, $v1, 3
		subu	$v0, $v1
		addu	$s1, $v0
		move	$a0, $s2
		move	$a1, $s4
		move	$a2, $s3
		jal	sub_8DDBC
		move	$a3, $s1
		lbu	$v1, 0($t1)
		li	$at, 0x20
		beq	$v1, $at, loc_8DD3C
		sll	$v0, $v1, 3
		subu	$v0, $v1
		la	$a3, (loc_92020 + 1)
		addu	$a3, $v0, $a3
		lb	$a0, 2($s1)
		lb	$a1, 4($s1)
		sra	$a0, 1
		addu	$a0, $s2
		addiu	$a0, -3
		addu	$a1, $s4, $a1
		move	$a2, $s3
		jal	sub_8DDBC
		addiu	$ra, 0x60

		loc_8DCDC:
	sll	$v0, $a0, 3
		subu	$v0, $a0
		sltiu	$at, $a0, 0x20
		beqz	$at, loc_8DD20
		move	$a2, $s3
		la	$v1, word_9230E
		addiu	$a0, -0x18
		sltiu	$a0, 4
		bnez	$a0, loc_8DD0C
		addu	$s1, $v0, $v1
		move	$a2, $zero

		loc_8DD0C :
	move	$a0, $s2
		move	$a1, $s4
		move	$a3, $s1
		jal	sub_8DDBC
		addiu	$ra, 0x1C

		loc_8DD20 :
		la	$a0, (loc_92020 + 1)
		addu	$s1, $v0, $a0
		move	$a0, $s2
		move	$a1, $s4
		jal	sub_8DDBC
		move	$a3, $s1

		loc_8DD3C :
	lbu	$v1, 2($s1)
		andi	$v0, $s6, 0x1000
		beqz	$v0, loc_8DD50
		srl	$v0, $v1, 2
		subu	$v1, $v0

		loc_8DD50 :
	addu	$s2, $v1

		loc_8DD54 :
	lbu	$a0, 0($s5)
		addiu	$s5, 1
		bnez	$a0, loc_8DBC4
		li	$v0, 0xA
		sb	$zero, 0x1A8C($gp)

		loc_8DD68 :
		lw	$ra, 0x40 + var_4($sp)
		lw	$s6, 0x40 + var_8($sp)
		lw	$s5, 0x40 + var_C($sp)
		lw	$s4, 0x40 + var_10($sp)
		lw	$s3, 0x40 + var_14($sp)
		lw	$s2, 0x40 + var_18($sp)
		lw	$s1, 0x40 + var_1C($sp)
		lw	$s0, 0x40 + var_20($sp)
		jr	$ra
		addiu	$sp, 0x40
#endif

//#else
	printf("PrintString - X:%d Y:%d C:%d - %s\n", x, y, colourFlag, string);

}
#endif
void SetGunFlash(short gun_type)
{
	S_Warn("[SetGunFlash] - Unimplemented!\n");
}
