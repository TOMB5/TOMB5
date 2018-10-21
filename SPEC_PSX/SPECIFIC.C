#include "SPECIFIC.H"

#include "3D_OBJ.H"
#include "CAMERA.H"
#include "CD.H"
#include "MISC.H"
#include "GPU.H"
#include "PROFILE.H"
#include "PSXINPUT.H"
#include "REQUEST.H"
#include "SAVEGAME.H"
#include "SFX.H"
#include "SOUND.H"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include <sys\types.h>
#include <LIBSPU.H>

static struct REQUESTER PauseReq = { 0xA4, 0x08, 0x03, 0x00, 0x05, 0x08, 0x03, 0x0A, 0x00, { 0xDE, 0xDF, 0xE0, 0x00, 0x00 } };
static struct REQUESTER AdjustReq = { 0xE6, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,{ 0x00, 0x00, 0x00, 0x00, 0x00 } };
static struct REQUESTER QuitReq = { 0xE2, 0x08, 0x02, 0x01, 0x02, 0x00, 0x00, 0x00, 0x00,{ 0xA0, 0xA1, 0x00, 0x00, 0x00 } };
static struct REQUESTER StatisticsReq = { 0xB2, 0x08, 0x01, 0x01, 0x05, 0x00, 0x00, 0x00, 0x01,{ 0xEE, 0x00, 0x00, 0x00, 0x00 } };

static unsigned short PadStrings[5][8] =
{
	{ 0x00BC, 0xBE00, 0x00BE, 0xBD00, 0x00BD, 0xBF00, 0x00BF, 0xC100 },
	{ 0x00BC, 0xBE00, 0x00BE, 0xBD00, 0x00BD, 0xBF00, 0x00BF, 0xC100 },
	{ 0x00BC, 0xBE00, 0x00BE, 0xBD00, 0x00BD, 0xBF00, 0x00BF, 0xC100 },
	{ 0x00BC, 0xBE00, 0x00BE, 0xBD00, 0x00BD, 0xBF00, 0x00BF, 0xC100 },
	{ 0x00BC, 0xBE00, 0x00BE, 0xBD00, 0x00BD, 0xBF00, 0x00BF, 0xC100 }
};

static unsigned char PauseMenuNum;
unsigned short AnimComp;
short AnimatingTexturesVOffset;
struct REQUESTER SettingsReq = { 0xE0, 0x08, 0x05, 0x00, 0x05, 0x00, 0x03, 0x03, 0x00,{ 0xE4, 0xE5, 0xE7, 0xE3, 0xEB } };
struct REQUESTER ConfigReq = { 0xE7, 0x08, 0x03, 0x01, 0x05, 0x00, 0x00, 0x02, 0x01,{ 0xED, 0xE8, 0xE9, 0x00, 0x00 } };
unsigned char SoundFXVolume;
unsigned short nAnimTextureRanges;
unsigned short* AnimTextureRanges;
unsigned short nAnimUVRanges;
int GtSFXEnabled;
short AnimatingTexturesV[16][8][3];

void S_control_screen_position()//6068C(<), 61204(<)
{
	if (input & 1)
	{
		savegame.ScreenY--;

		if ((savegame.ScreenY << 16) < 0)
		{
			savegame.ScreenY = 0;
		}
	}
	else if (input & 2)
	{
		//loc_606D0
		savegame.ScreenY++;

		if (savegame.ScreenY > 40)
		{
			savegame.ScreenY = 40;
		}
	}

	//loc_60708
	if (input & 4)
	{
		savegame.ScreenX--;

		if (savegame.ScreenX < -10)
		{
			savegame.ScreenX = -10;
		}

	}
	else if (input & 8)
	{
		//loc_60750
		savegame.ScreenX++;

		if (savegame.ScreenX > 32)
		{
			savegame.ScreenX = 32;
		}
	}

	//loc_60784
	GPU_SetScreenPosition(savegame.ScreenX, savegame.ScreenY);
}

long S_DumpScreen()//607A8(<), 61320(<) (F)
{
	return GPU_FlipNoIdle();
}

void S_ExitSystem(char* exit_message)//607C8, * (F)
{
	SetSp(0x801FFFE0);

	printf("\n Exit Message: %s\n", exit_message);

	while (1)
	{
		SetDispMask(0);
		SetDispMask(1);
	}
}

void DisplayConfig(int x, int y)//6080C, 61340
{
	//{ // line 4, offset 0x6084c
	unsigned short* wp; // $s1
						//} // line 4, offset 0x6084c
						//{ // line 39, offset 0x60b2c
	char buf[80]; // stack offset -128
	int seconds; // $s0
				 //} // line 98, offset 0x60f04

				 //fp = y;
				 //x = sw	$a0, 0xA0 + arg_0($sp)
	if (PauseMenuNum == 20)
	{
		//a0 = 0x70;
		//s5 = y & 0xFFFF;
		//a1 = s5;
		//a2 = 2;
		//a3 = A1A58//?
		//lui	$v0, 0xB
		//li	$s0, 0x8000
		//s1 = savegame.ControlOption;
		//v0 = &PadStrings[0][0];

		((long*) &buf[16])[0] = 0x8000;
		wp = &PadStrings[0][savegame.ControlOption];
		//PrintString(112, y & 0xFFFF, 2, a3);

		//la	$a3, dword_A1A5C
		//PrintString(112, ((long*) &buf[18])[0], 2, a3);

	}

	//loc_60B2C
#if 0

	addiu	$s2, $fp, 0xA0 + var_90 + 2
		andi	$s2, 0xFFFF
		move	$a1, $s2


		jal	sub_8DB4C//PrintString()//PrintString()
		sw	$s0, 0xA0 + var_90($sp)

		li	$a0, 0x190
		move	$a1, $s5
		li	$a2, 2
		la	$a3, dword_A1A60
		jal	sub_8DB4C//PrintString()
		sw	$s0, 0xA0 + var_90($sp)

		li	$a0, 0x190
		move	$a1, $s2
		li	$a2, 2
		la	$a3, dword_A1A64
		jal	sub_8DB4C//PrintString()
		sw	$s0, 0xA0 + var_90($sp)

		li	$a0, 0x70
		addiu	$s3, $fp, 0xA0 + var_7C
		andi	$s3, 0xFFFF
		move	$a1, $s3
		li	$a2, 2
		la	$a3, dword_A1A68
		jal	sub_8DB4C//PrintString()
		sw	$s0, 0xA0 + var_90($sp)

		li	$a0, 0x70
		addiu	$s4, $fp, 0xA0 + var_6A
		andi	$s4, 0xFFFF
		move	$a1, $s4
		li	$a2, 2
		la	$a3, dword_A1A6C
		jal	sub_8DB4C//PrintString()
		sw	$s0, 0xA0 + var_90($sp)

		li	$a0, 0x190
		move	$a1, $s3
		li	$a2, 2
		la	$a3, dword_A1A70
		jal	sub_8DB4C//PrintString()
		sw	$s0, 0xA0 + var_90($sp)

		li	$a0, 0x190
		move	$a1, $s4
		li	$a2, 2
		la	$a3, dword_A1A74
		jal	sub_8DB4C//PrintString()
		sw	$s0, 0xA0 + var_90($sp)

		li	$a0, 0x8C
		move	$a1, $s5
		lhu	$v0, 0($s1)
		lw	$v1, dword_800A202C
		lw	$a3, dword_800A203C
		sll	$v0, 1
		addu	$v0, $v1
		lhu	$t0, 0($v0)
		li	$a2, 5
		sw	$zero, 0xA0 + var_90($sp)
		jal	sub_8DB4C//PrintString()
		addu	$a3, $t0
		li	$a0, 0x8C
		move	$a1, $s2
		lhu	$v0, 2($s1)
		lw	$v1, dword_800A202C
		lw	$a3, dword_800A203C
		sll	$v0, 1
		addu	$v0, $v1
		lhu	$t0, 0($v0)
		li	$a2, 5
		sw	$zero, 0xA0 + var_90($sp)
		jal	sub_8DB4C//PrintString()
		addu	$a3, $t0
		li	$a0, 0x174
		move	$a1, $s5
		li	$a2, 5
		lhu	$v0, 4($s1)
		lw	$v1, dword_800A202C
		lw	$a3, dword_800A203C
		sll	$v0, 1
		addu	$v0, $v1
		lhu	$t0, 0($v0)
		li	$s0, 0x4000
		sw	$s0, 0xA0 + var_90($sp)
		jal	sub_8DB4C//PrintString()
		addu	$a3, $t0
		li	$a0, 0x174
		move	$a1, $s2
		lhu	$v0, 6($s1)
		lw	$v1, dword_800A202C
		lw	$a3, dword_800A203C
		sll	$v0, 1
		addu	$v0, $v1
		lhu	$t0, 0($v0)
		li	$a2, 5
		sw	$s0, 0xA0 + var_90($sp)
		jal	sub_8DB4C//PrintString()
		addu	$a3, $t0
		li	$a0, 0x8C
		move	$a1, $s3
		lhu	$v0, 8($s1)
		lw	$v1, dword_800A202C
		lw	$a3, dword_800A203C
		sll	$v0, 1
		addu	$v0, $v1
		lhu	$t0, 0($v0)
		li	$a2, 5
		sw	$zero, 0xA0 + var_90($sp)
		jal	sub_8DB4C//PrintString()
		addu	$a3, $t0
		li	$a0, 0x8C
		move	$a1, $s4
		lhu	$v0, 0xA($s1)
		lw	$v1, dword_800A202C
		lw	$a3, dword_800A203C
		sll	$v0, 1
		addu	$v0, $v1
		lhu	$t0, 0($v0)
		li	$a2, 5
		sw	$zero, 0xA0 + var_90($sp)
		jal	sub_8DB4C//PrintString()
		addu	$a3, $t0
		li	$a0, 0x174
		move	$a1, $s3
		lhu	$v0, 0xC($s1)
		lw	$v1, dword_800A202C
		lw	$a3, dword_800A203C
		sll	$v0, 1
		addu	$v0, $v1
		lhu	$t0, 0($v0)
		li	$a2, 5
		sw	$s0, 0xA0 + var_90($sp)
		jal	sub_8DB4C//PrintString()
		addu	$a3, $t0
		li	$a0, 0x174
		move	$a1, $s4
		lhu	$v0, 0xE($s1)
		lw	$v1, dword_800A202C
		lw	$a3, dword_800A203C
		sll	$v0, 1
		addu	$v0, $v1
		lhu	$t0, 0($v0)
		li	$a2, 5
		sw	$s0, 0xA0 + var_90($sp)
		jal	sub_8DB4C//PrintString()
		addu	$a3, $t0
		j	loc_60F04
		nop

		loc_60B2C :
	li	$v0, 0x88888889
		lw	$s0, dword_A1FF8
		andi	$s2, $fp, 0xFFFF
		multu	$s0, $v0
		lw	$v0, 0xA0 + arg_0($sp)
		move	$a1, $s2
		andi	$v0, 0xFFFF
		move	$a0, $v0
		sw	$v0, 0xA0 + var_30($sp)
		lw	$v0, dword_800A202C
		lw	$a3, dword_800A203C
		lhu	$v1, 0x170($v0)
		li	$a2, 5
		sw	$zero, 0xA0 + var_90($sp)
		addu	$a3, $v1
		mfhi	$s0
		jal	sub_8DB4C//PrintString()
		srl	$s0, 4
		addiu	$s4, $fp, 0xA0 + var_90 + 2
		andi	$s4, 0xFFFF
		move	$a1, $s4
		lw	$a0, 0xA0 + var_30($sp)
		lw	$v0, dword_800A202C
		lw	$a3, dword_800A203C
		lhu	$v1, 0x166($v0)
		li	$a2, 5
		sw	$zero, 0xA0 + var_90($sp)
		jal	sub_8DB4C//PrintString()
		addu	$a3, $v1
		addiu	$s7, $fp, 0xA0 + var_7C
		andi	$s7, 0xFFFF
		move	$a1, $s7
		lw	$a0, 0xA0 + var_30($sp)
		lw	$v0, dword_800A202C
		lw	$a3, dword_800A203C
		lhu	$v1, 0x168($v0)
		li	$a2, 5
		sw	$zero, 0xA0 + var_90($sp)
		jal	sub_8DB4C//PrintString()
		addu	$a3, $v1
		addiu	$s5, $fp, 0xA0 + var_6A
		andi	$s5, 0xFFFF
		move	$a1, $s5
		lw	$a0, 0xA0 + var_30($sp)
		lw	$v0, dword_800A202C
		lw	$a3, dword_800A203C
		lhu	$v1, 0x16E($v0)
		li	$a2, 5
		sw	$zero, 0xA0 + var_90($sp)
		jal	sub_8DB4C//PrintString()
		addu	$a3, $v1
		addiu	$s6, $fp, 0xA0 + var_58
		andi	$s6, 0xFFFF
		move	$a1, $s6
		lw	$a0, 0xA0 + var_30($sp)
		lw	$v0, dword_800A202C
		lw	$a3, dword_800A203C
		lhu	$v1, 0x16A($v0)
		li	$a2, 5
		sw	$zero, 0xA0 + var_90($sp)
		jal	sub_8DB4C//PrintString()
		addu	$a3, $v1
		li	$a2, 0xC22E4507
		mult	$s0, $a2
		lui	$t3, 0x91A2
		mfhi	$a2
		li	$t2, 0x88888889
		mult	$s0, $t2
		li	$t3, 0x91A2B3C5
		sra	$t4, $s0, 31
		addu	$a2, $s0
		sra	$a2, 16
		subu	$a2, $t4
		sll	$v0, $a2, 1
		addu	$v0, $a2
		sll	$v1, $v0, 4
		subu	$v1, $v0
		sll	$t0, $v1, 4
		subu	$t0, $v1
		mfhi	$t1
		sll	$t0, 7
		subu	$t0, $s0, $t0
		mult	$t0, $t3
		addiu	$a0, $sp, 0xA0 + var_80
		lui	$a1, 0xA
		lw	$v0, dword_800A202C
		lw	$a3, dword_800A203C
		lhu	$v1, 0x172($v0)
		la	$a1, aDSD_2d_2d	 # "%d %s %d:%.2d:%.2d"
		addu	$a3, $v1
		addu	$t1, $s0
		mfhi	$t3
		sra	$t1, 5
		subu	$t1, $t4
		mult	$t1, $t2
		sll	$v0, $t1, 4
		subu	$v0, $t1
		sll	$v0, 2
		subu	$s0, $v0
		sra	$v1, $t1, 31
		sw	$s0, 0xA0 + var_88($sp)
		addu	$t3, $t0
		sra	$t3, 11
		sra	$t0, 31
		subu	$t3, $t0
		sw	$t3, 0xA0 + var_90($sp)
		mfhi	$t2
		addu	$t2, $t1
		sra	$t2, 5
		subu	$t2, $v1
		sll	$v0, $t2, 4
		subu	$v0, $t2
		sll	$v0, 2
		subu	$t1, $v0
		jal	sub_68654
		sw	$t1, 0xA0 + var_8C($sp)
		li	$s1, 0x200
		move	$a1, $s2
		li	$a2, 5
		addiu	$a3, $sp, 0xA0 + var_80
		lw	$v0, 0xA0 + arg_0($sp)
		li	$s3, 0x4000
		sw	$s3, 0xA0 + var_90($sp)
		subu	$s1, $v0
		andi	$s1, 0xFFFF
		jal	sub_8DB4C//PrintString()
		move	$a0, $s1
		lui	$a2, 0x271A
		li	$s2, 0xAB3DC
		lw	$v0, 0x188($s2)
		li	$a2, 0x271A45A7
		mult	$v0, $a2
		addiu	$a0, $sp, 0xA0 + var_80
		la	$a1, aDm	 # "%dm"
		sra	$v0, 31
		mfhi	$a2
		sra	$a2, 6
		jal	sub_68654
		subu	$a2, $v0
		move	$a0, $s1
		move	$a1, $s4
		li	$a2, 5
		addiu	$a3, $sp, 0xA0 + var_80
		jal	sub_8DB4C//PrintString()
		sw	$s3, 0xA0 + var_90($sp)
		addiu	$a0, $sp, 0xA0 + var_80
		la	$s0, aD		 # "%d"
		lw	$a2, 0x18C($s2)
		jal	sub_68654
		move	$a1, $s0
		move	$a0, $s1
		move	$a1, $s7
		li	$a2, 5
		addiu	$a3, $sp, 0xA0 + var_80
		jal	sub_8DB4C//PrintString()
		sw	$s3, 0xA0 + var_90($sp)
		addiu	$a0, $sp, 0xA0 + var_80
		lbu	$a2, 0x197($s2)
		jal	sub_68654
		move	$a1, $s0
		move	$a0, $s1
		move	$a1, $s5
		li	$a2, 5
		addiu	$a3, $sp, 0xA0 + var_80
		jal	sub_8DB4C//PrintString()
		sw	$s3, 0xA0 + var_90($sp)
		addiu	$a0, $sp, 0xA0 + var_80
		lui	$a1, 0xA
		lbu	$a2, 0x196($s2)
		jal	sub_68654
		la	$a1, aD36	 # "%d / 36"
		move	$a0, $s1
		move	$a1, $s6
		li	$a2, 5
		addiu	$a3, $sp, 0xA0 + var_80
		jal	sub_8DB4C//PrintString()
		sw	$s3, 0xA0 + var_90($sp)
		li	$a0, 0x100
		addiu	$a1, $fp, 0xA0 + var_3E
		andi	$a1, 0xFFFF
		li	$a2, 8
		lw	$v0, dword_800A202C
		lw	$a3, dword_800A203C
		lhu	$v1, 0x162($v0)
		li	$s0, 0x8000
		sw	$s0, 0xA0 + var_90($sp)
		jal	sub_8DB4C//PrintString()
		addu	$a3, $v1
		li	$v0, 0xC0C0C0
		addiu	$a1, $fp, 0xA0 + var_3C
		andi	$a1, 0xFFFF
		li	$a2, 0x100
		lw	$a0, 0xA0 + var_30($sp)
		lw	$v1, 0xA0 + arg_0($sp)
		li	$a3, 1
		sw	$zero, 0xA0 + var_90($sp)
		sw	$v0, 0xA0 + var_8C($sp)
		subu	$a2, $v1
		sll	$a2, 1
		jal	sub_5EECC
		andi	$a2, 0xFFFE
		li	$a0, 1
		jal	sub_5EE78
		li	$a1, 1
		li	$a0, 0x100
		addiu	$a1, $fp, 0xA0 + var_2A
		andi	$a1, 0xFFFF
		la	$v1, dword_A1FB0
		lbu	$a2, byte_A1FA8
		lw	$a3, dword_800A203C
		addu	$a2, $v1
		lbu	$v0, 0($a2)
		lw	$v1, dword_800A202C
		sll	$v0, 1
		addu	$v0, $v1
		lhu	$t0, 0($v0)
		li	$a2, 5
		sw	$s0, 0xA0 + var_90($sp)
		jal	sub_8DB4C//PrintString()
		addu	$a3, $t0

		loc_60F04 :
	lw	$ra, 0xA0 + var_4($sp)
		lw	$fp, 0xA0 + var_8($sp)
		lw	$s7, 0xA0 + var_C($sp)
		lw	$s6, 0xA0 + var_10($sp)
		lw	$s5, 0xA0 + var_14($sp)
		lw	$s4, 0xA0 + var_18($sp)
		lw	$s3, 0xA0 + var_1C($sp)
		lw	$s2, 0xA0 + var_20($sp)
		lw	$s1, 0xA0 + var_24($sp)
		lw	$s0, 0xA0 + var_28($sp)
		jr	$ra
		addiu	$sp, 0xA0
		# End of function sub_6080C
#endif

		UNIMPLEMENTED();
}

int DoPauseMenu()//60F34, 61A68
{
	UNIMPLEMENTED();
	return 0;
}

void gInit()//615CC(<), 6210C(<) (F)
{
	SOUND_Stop();
	XAFadeRate = 32;
	XAReqVolume = 0;

#if DEBUG_VERSION
	ProfileDraw = 0;
#endif
	CreateMonoScreen();

	if (XAVolume != 0)
	{
		do
		{
			XAReqVolume = 0;
		} while (XAVolume != 0);
	}

	S_CDPause();
	S_SetReverbType(1);
	camera.number_frames = 2;

	return;
}

short S_Death()//61658, 622C8
{
	UNIMPLEMENTED();
	return 0;
}

void DisplayStatsUCunt()//61928(<), 625A8(<) (F)
{
	Requester(&StatisticsReq);
}

void S_Warn(const char* warning_message)//*
{
	printf(warning_message);
#ifndef NDEBUG
	//assert(0);
#endif
}