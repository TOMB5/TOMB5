#include "PSOUTPUT.H"
#include "PSXTYPES.H"
#include "SPECIFIC.H"

static struct VIBRATION vib[2];


void VibratePad()//604EC, 61064
{
#if 0
	int i;
	struct VIBRATION *v;
#endif
}

void SetupPadVibration(short num, short acc, short lev, short sus, int dec, int len)//604A4, 6101C
{
#if 0
	struct VIBRATION *v;

	int a0;
	a0 <<= 16;
	a0 >>= 12;


	struct VIBRATION* v0 = &vib[0];
		addiu	$v0, $gp, 0x4088
		addu	$a0, $v0
		sll	$a3, 16
		sra	$a3, 16
		sh	$a1, 6($a0)
		sh	$a2, 4($a0)
		sh	$zero, 0xC($a0)
		sh	$zero, 0($a0)
		sh	$zero, 0xE($a0)
		lh	$v1, arg_14($sp)
		lh	$v0, arg_10($sp)
		subu	$a3, $v1, $a3
		sh	$a3, 0xA($a0)
		sh	$v0, 8($a0)
		sh	$v1, 2($a0)
#endif
}

