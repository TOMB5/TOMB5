#include "SPECIFIC.H"

#include "3D_OBJ.H"
#include "BUBBLES.H"
#include "CAMERA.H"
#include "CD.H"
#include "CONTROL.H"
#include "EFFECTS.H"
#include "FXTRIG.H"
#include "GAMEFLOW.H"
#include "MEMCARD.H"
#include "MISC.H"
#include "GPU.H"
#include "LARA.H"
#include "LOADSAVE.H"
#include "PROFILE.H"
#include "PSXINPUT.H"
#include "REQUEST.H"
#include "SAVEGAME.H"
#include "SFX.H"
#include "SOUND.H"
#include "TEXT_S.H"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

//#include <SYS/TYPES.H>
#include <LIBSPU.H>
#include <LIBAPI.H>
#include <STRINGS.H>
static struct REQUESTER PauseReq = { STR_PAUSED,  8, 3, 0, 5, 0, 0, 0, 0, { STR_RESUME, STR_QUIT,  STR_GAME_SETTINGS, 0, 0 } };
static struct REQUESTER AdjustReq = { STR_USE_DIRECTIONAL_BUTTONS, 8, 0, 0, 0, 0, 0, 0, 0,{ 0, 0, 0, 0, 0 } };
static struct REQUESTER QuitReq = { STR_CONFIRM_QUIT, 8, 2, 1, 2, 0, 0, 0, 0,{ STR_YES, STR_NO, 0, 0, 0 } };
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
struct REQUESTER SettingsReq = { STR_GAME_SETTINGS, 8, 5, 0, 5, 0, 3, 3, 0,{ STR_SFX_VOLUME, STR_MUSIC_VOLUME, STR_CONFIGURE_CONTROLS, STR_SCREEN_ADJUST, STR_MANUAL_TARGETING } };
struct REQUESTER ConfigReq = { STR_CONFIGURE_CONTROLS, 8, 3, 1, 5, 0, 0, 2, 1,{ STR_ELLIPSIS, STR_CONFIGURATION, STR_VIBRATION_ON, 0, 0 } };
unsigned char SoundFXVolume;
unsigned short nAnimTextureRanges;
unsigned short* AnimTextureRanges;
unsigned short nAnimUVRanges;
int GtSFXEnabled;
short AnimatingTexturesV[16][8][3];

static int dword_A1A58[] = { 0x14, 0x15, 0x17, 0x16, 0x1E, 0x1F, 0x1C, 0x1D };
static char byte_A1F40 = 0;
static char byte_A1F41 = 4;

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
	unsigned short* wp; // $s1
	char buf[80]; // stack offset -128
	int seconds; // $s0

	//fp = y
	//v1 = PauseMenuNum
	//v0 = 0x14

	if (PauseMenuNum == 0x14)
	{
		//a0 = 0x70
		//s5 = y & 0xFFFF
		//a1 = s5
		//a2 = 2
		//a3 = &dword_A1A58[0]//FIXME might not be array?
		//v0 = 0xB0000
		//s0 = 0x8000
		//s1 = savegame.ControlOption
		//v0 = &PadStrings

		PrintString(0x70, y, 2, (char*)&dword_A1A58[0], FF_CENTER);

	}

#if 0
				 li      $a0, 0x70
				 addiu   $s2, $fp, 0xA0 + var_90 + 2
				 andi    $s2, 0xFFFF
				 move    $a1, $s2
				 li      $a2, 2
				 la      $a3, dword_A1A5C
				 jal     sub_8DB4C
				 sw      $s0, 0xA0 + var_90($sp)

				 li      $a0, 0x190
				 move    $a1, $s5
				 li      $a2, 2
				 la      $a3, dword_A1A60
				 jal     sub_8DB4C
				 sw      $s0, 0xA0 + var_90($sp)

				 li      $a0, 0x190
				 move    $a1, $s2
				 li      $a2, 2
				 la      $a3, dword_A1A64
				 jal     sub_8DB4C
				 sw      $s0, 0xA0 + var_90($sp)

				 li      $a0, 0x70
				 addiu   $s3, $fp, 0xA0 + var_7C
				 andi    $s3, 0xFFFF
				 move    $a1, $s3
				 li      $a2, 2
				 la      $a3, dword_A1A68
				 jal     sub_8DB4C
				 sw      $s0, 0xA0 + var_90($sp)

				 li      $a0, 0x70
				 addiu   $s4, $fp, 0xA0 + var_6A
				 andi    $s4, 0xFFFF
				 move    $a1, $s4
				 li      $a2, 2
				 la      $a3, dword_A1A6C
				 jal     sub_8DB4C
				 sw      $s0, 0xA0 + var_90($sp)

				 li      $a0, 0x190
				 move    $a1, $s3
				 li      $a2, 2
				 la      $a3, dword_A1A70
				 jal     sub_8DB4C
				 sw      $s0, 0xA0 + var_90($sp)

				 li      $a0, 0x190
				 move    $a1, $s4
				 li      $a2, 2
				 la      $a3, dword_A1A74
				 jal     sub_8DB4C
				 sw      $s0, 0xA0 + var_90($sp)

				 li      $a0, 0x8C
				 move    $a1, $s5
				 lhu     $v0, 0($s1)
				 lw      $v1, dword_800A202C
				 lw      $a3, dword_800A203C
				 sll     $v0, 1
				 addu    $v0, $v1
				 lhu     $t0, 0($v0)
				 li      $a2, 5
				 sw      $zero, 0xA0 + var_90($sp)
				 jal     sub_8DB4C
				 addu    $a3, $t0

				 li      $a0, 0x8C
				 move    $a1, $s2
				 lhu     $v0, 2($s1)
				 lw      $v1, dword_800A202C
				 lw      $a3, dword_800A203C
				 sll     $v0, 1
				 addu    $v0, $v1
				 lhu     $t0, 0($v0)
				 li      $a2, 5
				 sw      $zero, 0xA0 + var_90($sp)
				 jal     sub_8DB4C
				 addu    $a3, $t0

				 li      $a0, 0x174
				 move    $a1, $s5
				 li      $a2, 5
				 lhu     $v0, 4($s1)
				 lw      $v1, dword_800A202C
				 lw      $a3, dword_800A203C
				 sll     $v0, 1
				 addu    $v0, $v1
				 lhu     $t0, 0($v0)
				 li      $s0, 0x4000
				 sw      $s0, 0xA0 + var_90($sp)
				 jal     sub_8DB4C
				 addu    $a3, $t0

				 li      $a0, 0x174
				 move    $a1, $s2
				 lhu     $v0, 6($s1)
				 lw      $v1, dword_800A202C
				 lw      $a3, dword_800A203C
				 sll     $v0, 1
				 addu    $v0, $v1
				 lhu     $t0, 0($v0)
				 li      $a2, 5
				 sw      $s0, 0xA0 + var_90($sp)
				 jal     sub_8DB4C
				 addu    $a3, $t0

				 li      $a0, 0x8C
				 move    $a1, $s3
				 lhu     $v0, 8($s1)
				 lw      $v1, dword_800A202C
				 lw      $a3, dword_800A203C
				 sll     $v0, 1
				 addu    $v0, $v1
				 lhu     $t0, 0($v0)
				 li      $a2, 5
				 sw      $zero, 0xA0 + var_90($sp)
				 jal     sub_8DB4C
				 addu    $a3, $t0

				 li      $a0, 0x8C
				 move    $a1, $s4
				 lhu     $v0, 0xA($s1)
				 lw      $v1, dword_800A202C
				 lw      $a3, dword_800A203C
				 sll     $v0, 1
				 addu    $v0, $v1
				 lhu     $t0, 0($v0)
				 li      $a2, 5
				 sw      $zero, 0xA0 + var_90($sp)
				 jal     sub_8DB4C
				 addu    $a3, $t0

				 li      $a0, 0x174
				 move    $a1, $s3
				 lhu     $v0, 0xC($s1)
				 lw      $v1, dword_800A202C
				 lw      $a3, dword_800A203C
				 sll     $v0, 1
				 addu    $v0, $v1
				 lhu     $t0, 0($v0)
				 li      $a2, 5
				 sw      $s0, 0xA0 + var_90($sp)
				 jal     sub_8DB4C
				 addu    $a3, $t0

				 li      $a0, 0x174
				 move    $a1, $s4
				 lhu     $v0, 0xE($s1)
				 lw      $v1, dword_800A202C
				 lw      $a3, dword_800A203C
				 sll     $v0, 1
				 addu    $v0, $v1
				 lhu     $t0, 0($v0)
				 li      $a2, 5
				 sw      $s0, 0xA0 + var_90($sp)
				 jal     sub_8DB4C
				 addu    $a3, $t0
				 j       loc_60F04
				 nop

				 loc_60B2C :
			 li      $v0, 0x88888889
				 lw      $s0, dword_A1FF8
				 andi    $s2, $fp, 0xFFFF
				 multu   $s0, $v0
				 lw      $v0, 0xA0 + arg_0($sp)
				 move    $a1, $s2
				 andi    $v0, 0xFFFF
				 move    $a0, $v0
				 sw      $v0, 0xA0 + var_30($sp)
				 lw      $v0, dword_800A202C
				 lw      $a3, dword_800A203C
				 lhu     $v1, 0x170($v0)
				 li      $a2, 5
				 sw      $zero, 0xA0 + var_90($sp)
				 addu    $a3, $v1
				 mfhi    $s0
				 jal     sub_8DB4C
				 srl     $s0, 4
				 addiu   $s4, $fp, 0xA0 + var_90 + 2
				 andi    $s4, 0xFFFF
				 move    $a1, $s4
				 lw      $a0, 0xA0 + var_30($sp)
				 lw      $v0, dword_800A202C
				 lw      $a3, dword_800A203C
				 lhu     $v1, 0x166($v0)
				 li      $a2, 5
				 sw      $zero, 0xA0 + var_90($sp)
				 jal     sub_8DB4C
				 addu    $a3, $v1
				 addiu   $s7, $fp, 0xA0 + var_7C
				 andi    $s7, 0xFFFF
				 move    $a1, $s7
				 lw      $a0, 0xA0 + var_30($sp)
				 lw      $v0, dword_800A202C
				 lw      $a3, dword_800A203C
				 lhu     $v1, 0x168($v0)
				 li      $a2, 5
				 sw      $zero, 0xA0 + var_90($sp)
				 jal     sub_8DB4C
				 addu    $a3, $v1
				 addiu   $s5, $fp, 0xA0 + var_6A
				 andi    $s5, 0xFFFF
				 move    $a1, $s5
				 lw      $a0, 0xA0 + var_30($sp)
				 lw      $v0, dword_800A202C
				 lw      $a3, dword_800A203C
				 lhu     $v1, 0x16E($v0)
				 li      $a2, 5
				 sw      $zero, 0xA0 + var_90($sp)
				 jal     sub_8DB4C
				 addu    $a3, $v1
				 addiu   $s6, $fp, 0xA0 + var_58
				 andi    $s6, 0xFFFF
				 move    $a1, $s6
				 lw      $a0, 0xA0 + var_30($sp)
				 lw      $v0, dword_800A202C
				 lw      $a3, dword_800A203C
				 lhu     $v1, 0x16A($v0)
				 li      $a2, 5
				 sw      $zero, 0xA0 + var_90($sp)
				 jal     sub_8DB4C
				 addu    $a3, $v1
				 li      $a2, 0xC22E4507
				 mult    $s0, $a2
				 lui     $t3, 0x91A2
				 mfhi    $a2
				 li      $t2, 0x88888889
				 mult    $s0, $t2
				 li      $t3, 0x91A2B3C5
				 sra     $t4, $s0, 31
				 addu    $a2, $s0
				 sra     $a2, 16
				 subu    $a2, $t4
				 sll     $v0, $a2, 1
				 addu    $v0, $a2
				 sll     $v1, $v0, 4
				 subu    $v1, $v0
				 sll     $t0, $v1, 4
				 subu    $t0, $v1
				 mfhi    $t1
				 sll     $t0, 7
				 subu    $t0, $s0, $t0
				 mult    $t0, $t3
				 addiu   $a0, $sp, 0xA0 + var_80
				 lui     $a1, 0xA
				 lw      $v0, dword_800A202C
				 lw      $a3, dword_800A203C
				 lhu     $v1, 0x172($v0)
				 la      $a1, aDSD2d2d    # "%d %s %d:%.2d:%.2d"
				 addu    $a3, $v1
				 addu    $t1, $s0
				 mfhi    $t3
				 sra     $t1, 5
				 subu    $t1, $t4
				 mult    $t1, $t2
				 sll     $v0, $t1, 4
				 subu    $v0, $t1
				 sll     $v0, 2
				 subu    $s0, $v0
				 sra     $v1, $t1, 31
				 sw      $s0, 0xA0 + var_88($sp)
				 addu    $t3, $t0
				 sra     $t3, 11
				 sra     $t0, 31
				 subu    $t3, $t0
				 sw      $t3, 0xA0 + var_90($sp)
				 mfhi    $t2
				 addu    $t2, $t1
				 sra     $t2, 5
				 subu    $t2, $v1
				 sll     $v0, $t2, 4
				 subu    $v0, $t2
				 sll     $v0, 2
				 subu    $t1, $v0
				 jal     sub_68654
				 sw      $t1, 0xA0 + var_8C($sp)
				 li      $s1, 0x200
				 move    $a1, $s2
				 li      $a2, 5
				 addiu   $a3, $sp, 0xA0 + var_80
				 lw      $v0, 0xA0 + arg_0($sp)
				 li      $s3, 0x4000
				 sw      $s3, 0xA0 + var_90($sp)
				 subu    $s1, $v0
				 andi    $s1, 0xFFFF
				 jal     sub_8DB4C
				 move    $a0, $s1
				 lui     $a2, 0x271A
				 li      $s2, 0xAB3DC
				 lw      $v0, 0x188($s2)
				 li      $a2, 0x271A45A7
				 mult    $v0, $a2
				 addiu   $a0, $sp, 0xA0 + var_80
				 la      $a1, aDm         # "%dm"
				 sra     $v0, 31
				 mfhi    $a2
				 sra     $a2, 6
				 jal     sub_68654
				 subu    $a2, $v0
				 move    $a0, $s1
				 move    $a1, $s4
				 li      $a2, 5
				 addiu   $a3, $sp, 0xA0 + var_80
				 jal     sub_8DB4C
				 sw      $s3, 0xA0 + var_90($sp)
				 addiu   $a0, $sp, 0xA0 + var_80
				 la      $s0, aD          # "%d"
				 lw      $a2, 0x18C($s2)
				 jal     sub_68654
				 move    $a1, $s0
				 move    $a0, $s1
				 move    $a1, $s7
				 li      $a2, 5
				 addiu   $a3, $sp, 0xA0 + var_80
				 jal     sub_8DB4C
				 sw      $s3, 0xA0 + var_90($sp)
				 addiu   $a0, $sp, 0xA0 + var_80
				 lbu     $a2, 0x197($s2)
				 jal     sub_68654
				 move    $a1, $s0
				 move    $a0, $s1
				 move    $a1, $s5
				 li      $a2, 5
				 addiu   $a3, $sp, 0xA0 + var_80
				 jal     sub_8DB4C
				 sw      $s3, 0xA0 + var_90($sp)
				 addiu   $a0, $sp, 0xA0 + var_80
				 lui     $a1, 0xA
				 lbu     $a2, 0x196($s2)
				 jal     sub_68654
				 la      $a1, aD36        # "%d / 36"
				 move    $a0, $s1
				 move    $a1, $s6
				 li      $a2, 5
				 addiu   $a3, $sp, 0xA0 + var_80
				 jal     sub_8DB4C
				 sw      $s3, 0xA0 + var_90($sp)
				 li      $a0, 0x100
				 addiu   $a1, $fp, 0xA0 + var_3E
				 andi    $a1, 0xFFFF
				 li      $a2, 8
				 lw      $v0, dword_800A202C
				 lw      $a3, dword_800A203C
				 lhu     $v1, 0x162($v0)
				 li      $s0, 0x8000
				 sw      $s0, 0xA0 + var_90($sp)
				 jal     sub_8DB4C
				 addu    $a3, $v1
				 li      $v0, 0xC0C0C0
				 addiu   $a1, $fp, 0xA0 + var_3C
				 andi    $a1, 0xFFFF
				 li      $a2, 0x100
				 lw      $a0, 0xA0 + var_30($sp)
				 lw      $v1, 0xA0 + arg_0($sp)
				 li      $a3, 1
				 sw      $zero, 0xA0 + var_90($sp)
				 sw      $v0, 0xA0 + var_8C($sp)
				 subu    $a2, $v1
				 sll     $a2, 1
				 jal     sub_5EECC
				 andi    $a2, 0xFFFE
				 li      $a0, 1
				 jal     sub_5EE78
				 li      $a1, 1
				 li      $a0, 0x100
				 addiu   $a1, $fp, 0xA0 + var_2A
				 andi    $a1, 0xFFFF
				 la      $v1, dword_A1FB0
				 lbu     $a2, byte_A1FA8
				 lw      $a3, dword_800A203C
				 addu    $a2, $v1
				 lbu     $v0, 0($a2)
				 lw      $v1, dword_800A202C
				 sll     $v0, 1
				 addu    $v0, $v1
				 lhu     $t0, 0($v0)
				 li      $a2, 5
				 sw      $s0, 0xA0 + var_90($sp)
				 jal     sub_8DB4C
				 addu    $a3, $t0

				 loc_60F04 :
			 lw      $ra, 0xA0 + var_4($sp)
				 lw      $fp, 0xA0 + var_8($sp)
				 lw      $s7, 0xA0 + var_C($sp)
				 lw      $s6, 0xA0 + var_10($sp)
				 lw      $s5, 0xA0 + var_14($sp)
				 lw      $s4, 0xA0 + var_18($sp)
				 lw      $s3, 0xA0 + var_1C($sp)
				 lw      $s2, 0xA0 + var_20($sp)
				 lw      $s1, 0xA0 + var_24($sp)
				 lw      $s0, 0xA0 + var_28($sp)
				 jr      $ra
				 addiu   $sp, 0xA0
#endif

		UNIMPLEMENTED();
}

int DoPauseMenu()//60F34(<), 61A68(<) (F)
{
	char* s;
	long result;
	int prompt;
	unsigned short* vol;
	short level;
	/* ??? */
	static int cursor;
	struct REQUESTER* AutoRequester;
	static unsigned char AutoTime;
	static unsigned char AutoFunc;
	/* ??? */

	s = &gfStringWad[gfStringOffset[STR_CONFIGURATION]];

	prompt = 0;
	s[strlen(s) - 1] = savegame.ControlOption + 0x31;

	switch (PauseMenuNum)
	{
	case 0:
		//loc_60FBC
		result = Requester(&PauseReq);

		if (result)
		{
			QuitReq.CursorPos = 1;
			SettingsReq.CursorPos = 0;

			if (savegame.AutoTarget)
			{
				SettingsReq.OptionTxt[4] = STR_AUTOMATIC_TARGETING;
			}
			else
			{
				//loc_61B40
				SettingsReq.OptionTxt[4] = STR_MANUAL_TARGETING;
			}

			//loc_61B40
			if (savegame.VibrateOn)
			{
				ConfigReq.OptionTxt[2] = STR_VIBRATION_ON;
			}
			else
			{
				ConfigReq.OptionTxt[2] = STR_VIBRATION_OFF;
			}

			PauseMenuNum = result + 1;

		}//loc_61B68
		prompt = 2;
		break;
	case 1:
		//loc_6103C
		PauseMenuNum = 0;
		PauseReq.CursorPos = 0;
		return 1;
		break;
	case 2:
		//loc_6105C
		result = Requester(&QuitReq);
		if (result)
		{
			if (result == 0x8000)
			{
				reset_flag = 1;
				return 1;
			}

			PauseMenuNum = 0;

		}//loc_61090

		PrintString(SCREEN_WIDTH, 232, 5, &gfStringWad[gfStringOffset[STR_SELECT]], FF_CENTER);
		break;
	case 3:
		//loc_610C8
		result = Requester(&SettingsReq);

		if (result == 0x8002)
		{
			PauseMenuNum = 20;
			ConfigReq.CursorPos = 1;
			prompt = 3;
		}
		else if (result == 0x8003)
		{
			PauseMenuNum = 10;
			prompt = 3;
		}
		else if (result == 0x8004)
		{
			if (savegame.AutoTarget)
			{
				SettingsReq.OptionTxt[4] = STR_AUTOMATIC_TARGETING;
			}
			else
			{
				SettingsReq.OptionTxt[4] = STR_MANUAL_TARGETING;
			}
			//loc_61144
			savegame.AutoTarget ^= 1;

			//loc_61160
			if (SettingsReq.CursorPos < 2)
			{
				if (SettingsReq.CursorPos != 0)
				{
					vol = &savegame.VolumeCD;
				}
				else
				{
					vol = &savegame.VolumeFX;
				}

				//loc_61198
				level = *vol;
				if ((input & IN_LEFT))
				{
					level -= 10;

					if (level < 0)
					{
						level = 0;
					}
				}//loc_611C8

				if ((input & IN_RIGHT))
				{
					level = *vol + 10;

					if (level > 255)
					{
						level = 255;
					}
				}
				//loc_611EC
				*vol = level;

				if (SettingsReq.CursorPos == 0)
				{
					SoundFXVolume = level;
					SoundEffect(SFX_TICK_TOCK, NULL, 2);
				}
				else
				{
					CDDA_SetMasterVolume(level);
				}
			}//loc_61224
			prompt = 3;
		}
		break;
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
	case 16:
	case 17:
	case 18:
	case 19:
		//loc_614BC
		if (prompt != 0)
		{
			if (prompt == 3)
			{
				PrintString(SCREEN_WIDTH / 2, 232, 5, &gfStringWad[gfStringOffset[STR_SELECT]], FF_CENTER);
				PrintString(496, 232, 5, &gfStringWad[gfStringOffset[STR_BACK]], FF_R_JUSTIFY);
			}
			else if (prompt == 2)
			{
				//61520
				PrintString(SCREEN_WIDTH / 2, 232, 5, &gfStringWad[gfStringOffset[STR_SELECT]], FF_CENTER);
			}
			else
			{
				PrintString(SCREEN_WIDTH / 2, 232, 5, &gfStringWad[gfStringOffset[STR_CANCEL]], FF_CENTER);
			}

			if ((RawEdge & IN_TRIANGLE))
			{
				SoundEffect(SFX_MENU_CHOOSE, NULL, 2);
				PauseMenuNum = 0;
			}
		}
		break;
	case 10:
		//loc_6122C
		Requester(&AdjustReq);

		PrintString(SCREEN_WIDTH / 2, 232, 5, &gfStringWad[gfStringOffset[STR_OK]], FF_CENTER);
		DrawLineV(16, 16, 209, 0, 0x404040, 0);
		DrawLineV(496, 16, 209, 0, 0x404040, 0);
		DrawLineH(16, 16, 481, 0, 0x404040, 0);
		DrawLineH(16, 224, 481, 0, 0x404040, 0);

		S_control_screen_position();

		if ((RawEdge & IN_CROSS))
		{
			SoundEffect(SFX_MENU_CHOOSE, NULL, 2);
		}

		PauseMenuNum = 3;

		break;
	case 20:
		//loc_612F4
		if (DualShock)
		{
			ConfigReq.nOptions = 3;
		}
		else
		{
			//loc_6130C
			ConfigReq.nOptions = 2;
		}

		if (Requester(&ConfigReq) == 0x8002)
		{
			if (ConfigReq.OptionTxt[2] == STR_VIBRATION_OFF)
			{
				savegame.VibrateOn = 1;
				ConfigReq.OptionTxt[2] = STR_VIBRATION_ON;
			}
			else
			{
				//loc_61368
				savegame.VibrateOn = 0;
				ConfigReq.OptionTxt[2] = STR_VIBRATION_OFF;
			}
		}//lov_63170

		if (ConfigReq.CursorPos == 1)
		{
			if ((RawEdge & IN_DPAD_LEFT) && savegame.ControlOption != 0)
			{
				SoundEffect(SFX_MENU_SELECT, NULL, 2);

				if (savegame.ControlOption != 0)
				{
					savegame.ControlOption--;
				}
				else
				{
					savegame.ControlOption = 4;
				}
			}
			else if ((RawEdge & IN_DPAD_RIGHT))
			{
				//613E4
				if (savegame.ControlOption < 4)
				{
					SoundEffect(SFX_MENU_SELECT, NULL, 2);

					if (savegame.ControlOption < 4)
					{
						savegame.ControlOption++;
					}
					else
					{
						//6142C
						savegame.ControlOption = 0;
					}
				}
			}
		}
		else
		{
			//loc_61434
			PrintString(256, 232, 5, &gfStringWad[gfStringOffset[STR_SELECT]], FF_CENTER);
		}

		//61460
		PrintString(496, 232, 5, &gfStringWad[gfStringOffset[STR_BACK]], FF_R_JUSTIFY);

		if ((RawEdge & IN_TRIANGLE))
		{
			SoundEffect(SFX_MENU_CHOOSE, NULL, 0);
			PauseMenuNum = 3;
		}//614BC

		break;
	case 21:
		//loc_62AE0
		if (mcNumFiles == 0)
		{
			Requester(&NoGamesReq);
		}
		else
		{
			PrintString(SCREEN_WIDTH / 2, 32, 8, &gfStringWad[gfStringOffset[STR_SELECT_GAME_TO_LOAD]], FF_CENTER);

			DisplayFiles(cursor, mcNumFiles);

			if ((RawEdge & IN_DPAD_UP) && cursor != 0)
			{
				SoundEffect(SFX_MENU_SELECT, NULL, 0);
				cursor--;
			}//62B9C
			else if ((RawEdge & IN_DPAD_DOWN) && cursor < mcNumFiles)
			{
				SoundEffect(SFX_MENU_SELECT, NULL, 0);
				cursor++;
			}//62BEC
			else if ((RawEdge & IN_CROSS))
			{
				SoundEffect(SFX_MENU_CHOOSE, NULL, 0);

				byte_A1F41 = 7;
				AutoRequester = &LoadingReq;
				AutoTime = 3;
				AutoFunc = 11;
				prompt = 0;

				Requester(AutoRequester);

				if (AutoTime == 0)
				{
					if (AutoFunc == 255)
					{
						//62DC0
						prompt = 0;

						if (prompt != 0)
						{
							PrintString(SCREEN_WIDTH / 2, 232, 5, &gfStringWad[gfStringOffset[STR_CANCEL]], FF_CENTER);

							if ((RawEdge & IN_TRIANGLE))
							{
								byte_A1F40 = 0;
								return -1;
							}

						}//62E14

						return 1;
					}
				}
				//62c6c
			}
		}
		//62DC0
		prompt = 0;

		if (prompt != 0)
		{
			PrintString(SCREEN_WIDTH / 2, 232, 5, &gfStringWad[gfStringOffset[STR_CANCEL]], FF_CENTER);

			if ((RawEdge & IN_TRIANGLE))
			{
				byte_A1F40 = 0;
				return -1;
			}
		}
		//62E14
		break;
	}

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

short S_Death()//61658(<), 622C8(<) (F)
{
	short ret;
	unsigned char flag;
	unsigned char Cursor;

	ret = 0;
	flag = 0;
	Cursor = 0;

	gInit();
	mcOpen(0);

	//loc_6169C, loc_63230C
	while (ret == 0)
	{

#if !BETA_VERSION
		Motors[1] = 0;
		Motors[0] = 0;
#endif

		XAReqVolume = 0;

		GPU_BeginScene();
		SetDebounce = 1;
		S_UpdateInput();
		UpdatePulseColour();
		lara.death_count++;


		if (!PadConnected)
		{
			PrintString(SCREEN_WIDTH / 2, 0x40, 3, &gfStringWad[gfStringOffset[STR_CONTROLLER_REMOVED]], (FF_CENTER | FF_UNK13));
		}
		else
		{
			if (flag == 0)
			{
				//loc_6171C
				if (mcGetStatus() == 0 && mcNumFiles != 0)
				{
					if (Cursor != 0)
					{
						PrintString(SCREEN_WIDTH / 2, 0xC0, 2, &gfStringWad[gfStringOffset[STR_LOAD_GAME_BIS]], FF_CENTER);
					}
					else
					{
						PrintString(SCREEN_WIDTH / 2, 0xC0, 1, &gfStringWad[gfStringOffset[STR_LOAD_GAME_BIS]], FF_CENTER);
					}

					if (Cursor != 0)
					{
						PrintString(SCREEN_WIDTH / 2, 0xD0, 1, &gfStringWad[gfStringOffset[STR_EXIT_TO_TITLE]], FF_CENTER);
					}
					else
					{
						PrintString(SCREEN_WIDTH / 2, 0xD0, 2, &gfStringWad[gfStringOffset[STR_EXIT_TO_TITLE]], FF_CENTER);
					}

					if (Cursor != 0)
					{
						if ((RawEdge & IN_DPAD_UP))
						{
							SoundEffect(SFX_MENU_SELECT, NULL, 2);
							Cursor = 0;
						}
						else if ((RawEdge & IN_CROSS))
						{
							//loc_617E0
							SoundEffect(SFX_MENU_CHOOSE, NULL, 2);
							ret = 1;
						}
					}
					else
					{
						//loc_61800
						if ((RawEdge & IN_DPAD_DOWN))
						{
							SoundEffect(SFX_MENU_SELECT, NULL, 2);
							Cursor = 1;
						}
						else if ((RawEdge & IN_CROSS))
						{
							//loc_617E0
							SoundEffect(SFX_MENU_CHOOSE, NULL, 2);
							flag = 1;
						}
					}
				}
				else
				{
					//loc_6184C
					if (lara.death_count > 300)
					{
						ret = 1;
					}
				}

				//loc_61888
				PrintString(SCREEN_WIDTH / 2, 0x78, 3, &gfStringWad[gfStringOffset[STR_GAME_OVER]], FF_CENTER);
			}
			else if (flag == 1)
			{
				//loc_6189C
				ret = LoadGame();

				if (ret != 0)
				{
					if (ret > 0)
					{
						ret = 2;
					}
					else
					{
						flag = 0;
						ret = 0;
					}
				}
			}
		}

		//loc_618C4
		SOUND_EndScene();
		DrawMonoScreen(0x203040);
		GPU_EndScene();
		camera.number_frames = S_DumpScreen();
	}

	mcClose();
	return ret;
}

void DisplayStatsUCunt()//61928(<), 625A8(<) (F)
{
	Requester(&StatisticsReq);
}

/*
void S_Warn(const char* warning_message)
{
	printf(warning_message);
#ifndef NDEBUG
	//assert(0);
#endif
}*/

void S_CalculateLight(long x, long y, long z, short room, struct ITEM_LIGHT* light)
{
	UNIMPLEMENTED();
}
