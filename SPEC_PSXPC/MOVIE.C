#include "MOVIE.H"

#include "CONTROL.H"

int S_PlayFMV(int sequence, int flag)//*, (<)5E7A0
{
	//DISPENV disp[2];
	//s1 = fmv_index
	//s2 = a1; //maybe skippable?
	//v0 = 7;
	
	if (sequence != 7)
	{
		//v0 = 1
		if (FmvSceneTriggered & (1 << sequence))
		{
			return 1;
		}

		FmvSceneTriggered |= (1 << sequence);
	}
	
	//5E7F8
	FMV_InitialiseScreen();
	
	//VSync(0);
	//env.disp.w = 240;
	//SetDefDispEnv(&disp[0], 0, 0, 480, 0);//FIXME not producing correct data!

#if 0
	
	lui	$v1, 0x5555
	lh	$a2, 0x60 + var_44($sp)
	li	$v1, 0x55555556
	sll	$a2, 1
	mult	$a2, $v1
	addiu	$a0, $sp, 0x60 + var_48
	addiu	$a1, $s0, 0x5EE0//A3BF0 (db)
	lhu	$a3, 0xFA($a1)
	lhu	$t0, 0xFE($a1)
	li	$v0, 1
	sb	$v0, 0x60 + var_37($sp)
	sra	$a2, 31
	sh	$a3, 0x60 + var_3E($sp)
	sh	$t0, 0x60 + var_3A($sp)
	mfhi	$v1
	subu	$v1, $a2
	//PutDispEnv();//PutDispEnv(DISPENV *env);
	sh	$v1, 0x60 + var_44($sp)
	sll	$v1, $s1, 2
	addiu	$v0, $gp, 0x2E4C
	addu	$v1, $v0
	li	$a0, 0xFFFFFFFF
	lw	$v1, 0($v1)
	nop
	bne	$v1, $a0, loc_5E894
	move	$s5, $s0
	j	loc_5EBBC
	move	$v0, $zero
#endif

	return -1;//TODO
}

void FMV_InitialiseScreen()//*, 5F160(<) (F)
{
#if 0
	RECT rect;

	r.x = 0;
	r.y = 0;
	r.w = 512;
	r.h = 256;

	ClearImage(&rect, 0, 0, 0);

	rect.y = 240;
	ClearImage(&rect, 0, 0, 0);

	DrawSync(0);

#endif
	return;
}
