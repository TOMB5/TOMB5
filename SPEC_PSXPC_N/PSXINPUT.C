#include "PSXINPUT.H"

#include "CAMERA.H"
#include "CONTROL.H"
#include "GAMEFLOW.H"
#include "LARA.H"
#include "PICKUP.H"
#include "SAVEGAME.H"
#include "SOUND.H"
#include "SPECIFIC.H"
#include <LIBPAD.H>
#if PSXPC_TEST
#include <stdio.h>
#include "EMULATOR.H"
#elif PSX_VERSION
#include <STDIO.H>
#endif
#include <assert.h>
#include "FXTRIG.H"

static struct pad_configs pad_cons[5] =
{
	{ IN_DUCK, IN_SPRINT, IN_LOOK, IN_WALK, IN_DRAW, IN_JUMP, IN_ROLL, IN_ACTION },
	{ IN_LOOK, IN_WALK, IN_DUCK, IN_SPRINT, IN_ROLL, IN_DRAW, IN_ACTION, IN_JUMP },
	{ IN_SPRINT, IN_DUCK, IN_WALK, IN_LOOK, IN_JUMP, IN_ROLL, IN_ACTION, IN_DRAW },
	{ IN_DUCK, IN_SPRINT, IN_DRAW, IN_WALK, IN_LOOK, IN_ACTION, IN_JUMP, IN_ROLL },
	{ IN_ROLL, IN_DRAW, IN_JUMP, IN_ACTION, IN_SPRINT, IN_LOOK, IN_DUCK, IN_WALK }
};

unsigned char DualShock;
unsigned char PadConnected;
short reset_count;
char SayNoCount;

static unsigned char align[6] =
{
	0x00, 0x01, 0xFF, 0xFF, 0xFF, 0xFF
};

long input;
long dbinput;
long dbinput2;
long inputBusy;
long RawPad;
long RawEdge;
unsigned char Motors[2];
long LaraLookY;
long LaraLookX;
volatile ControllerPacket GPad1;
volatile ControllerPacket GPad2;
unsigned long Edge2;
struct GouraudBarColourSet healthBarColourSet =
{
	{64, 96, 128, 96, 64},
	{0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0},
	{128, 192, 255, 192, 128},
	{0, 0, 0, 0, 0}
};
struct GouraudBarColourSet poisonBarColourSet =
{
	{96, 176, 240, 176, 96},
	{96, 176, 240, 176, 96},
	{0, 0, 0, 0, 0},
	{96, 176, 240, 176, 96},
	{96, 176, 240, 176, 96},
	{0, 0, 0, 0, 0}
};
struct GouraudBarColourSet airBarColourSet =
{
	{0, 0, 0, 0, 0},
	{113, 146, 113, 93, 74},
	{123, 154, 123, 107, 91},
	{0, 0, 0, 0, 0},
	{113, 146, 113, 93, 74},
	{0, 0, 0, 0, 0}
};
struct GouraudBarColourSet dashBarColourSet =
{
	{144, 192, 240, 192, 144},
	{0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0},
	{144, 192, 240, 192, 144},
	{144, 192, 240, 192, 144},
	{0, 0, 0, 0, 0}
};

int dword_A1894;
int dword_A1890;
int dword_A1898;

void S_UpdateInput()//5F628(<), 6038C(<)
{
	int state; // $s1
	unsigned char type; // $s2
	unsigned long in; // $s0
	static unsigned long Pad2; // offset 0x0
	static int pause_db; // offset 0xc
	static int option_db; // offset 0x10
	static char LookCnt; // offset 0x14
						 // line 151, offset 0x5fa3c
	char pos; // $a0
	char walking; // $a1
				  // line 290, offset 0x5fcfc
				  // line 353, offset 0x5fe70
	static int send; // offset 0x18
					 // line 374, offset 0x5fed4

					 //v0 = SayNoCount

	Emulator_UpdateInput();

	in = 0;

	if (SayNoCount != 0)
	{
		SayNoCount--;
	}

	//loc_5F650
	state = PadGetState(0);
	type = PadInfoMode(0, InfoModeCurID, 0);

	if (state != 0)
	{
		if (type == 4 || type == 7)
		{
			//loc_5F6AC
			if (SetDebounce != 0)
			{
				dbinput = inputBusy;
				RawEdge = RawPad;
			}
		}
	}
	else
	{
		//loc_5F688
		RawPad = 0;
		PadConnected = 0;
		RawEdge = 0;
		input = 0;
		option_db = 0;
		pause_db = 0;
		reset_count = 0;
		return;
	}
	//loc_5F6D0
	PadConnected = 1;
	RawPad = (GPad1.data.pad ^ -1) & 0xFFFF;

	if (SetDebounce != 0)
	{
		RawEdge = (RawEdge ^ RawPad) & RawPad;
	}//loc_5F704

	if ((RawEdge & IN_UNK1))
	{
		option_db = 1;
	}//loc_5F71C

	if ((RawPad & 1))
	{
		if ((RawPad & 0x800))
		{
			if (lara_item->current_anim_state - 0x50 < 2 || lara_item->current_anim_state == 0x54 ||
				lara_item->current_anim_state == 0x55 || lara_item->current_anim_state || 0x56 ||
				lara_item->current_anim_state == 0x58)
			{
				//loc_5F780
				if (OldPickupPos.x != lara_item->pos.x_pos || OldPickupPos.y != lara_item->pos.y_pos ||
					OldPickupPos.z != lara_item->pos.z_pos)
				{
					//loc_5F7C8
					if (SayNoCount == 0)
					{
						SayNoCount = 30;
						OldPickupPos.x = lara_item->pos.x_pos;
						OldPickupPos.y = lara_item->pos.y_pos;
						OldPickupPos.z = lara_item->pos.z_pos;
						SayNo();
					}
				}
			}
			else
			{
				//loc_5F818
				in = 0x80000;
			}
			//loc_5F81C
			option_db = 0;
			RawPad &= 0xFFFFFDFF;

		}
		//loc_5F830
		if ((RawPad & 8))
		{
			reset_count++;

			if (reset_count > 48)
			{
				reset_flag = 1;
			}
			//loc_5F870
			option_db = 0;
		}
		else
		{
			//loc_5F87C
			reset_count = 0;
		}
	}
	else
	{
		//loc_5F888
		if (option_db != 0)
		{
			in = IN_OPTION;
		}
		//loc_5F89C
		reset_count = 0;
		option_db = 0;

		if ((RawEdge & IN_UNK8))
		{
			in |= IN_PAUSE;
		}
	}
	//loc_5F8B0
	if ((RawPad & IN_CROSS))
	{
		in |= IN_SELECT;
	}

	if ((RawPad & IN_TRIANGLE))
	{
		in |= IN_DESELECT;
	}

	if ((RawPad & IN_SQUARE))
	{
		in |= pad_cons[savegame.ControlOption].pad_square;
	}

	if ((RawPad & IN_CIRCLE))
	{
		in |= pad_cons[savegame.ControlOption].pad_circle;
	}

	if ((RawPad & IN_TRIANGLE))
	{
		in |= pad_cons[savegame.ControlOption].pad_triangle;
	}

	if ((RawPad & IN_CROSS))
	{
		in |= pad_cons[savegame.ControlOption].pad_cross;
	}

	if ((RawPad & IN_L1))
	{
		in |= pad_cons[savegame.ControlOption].pad_L1;
	}

	if ((RawPad & IN_L2))
	{
		in |= pad_cons[savegame.ControlOption].pad_L2;
	}

	if ((RawPad & IN_R1))
	{
		in |= pad_cons[savegame.ControlOption].pad_R1;
	}

	if ((RawPad & IN_R2))
	{
		in |= pad_cons[savegame.ControlOption].pad_R2;
	}

	//loc_5FA30
	if (type == 7)
	{
#if 0
		lw      $a1, 0x3FC4($gp)
			nop
			andi    $v0, $a1, 2
			beqz    $v0, loc_5FA70
			lui     $v1, 9
			lui     $a0, 0xB
			lbu     $v0, byte_800AB3E6
			la      $v1, dword_93F38
			sll     $v0, 5
			addu    $v1, $v0
			lw      $a0, 0x14($v1)
			nop
			or $s0, $a0

			loc_5FA70 :
		andi    $v0, $a1, 4
			beqz    $v0, loc_5FA9C
			lui     $v1, 9
			lui     $a0, 0xB
			lbu     $v0, byte_800AB3E6
			la      $v1, dword_93F38
			sll     $v0, 5
			addu    $v1, $v0
			lw      $a0, 0x1C($v1)
			nop
			or $s0, $a0

			loc_5FA9C :
		andi    $v0, $s0, 0x200
			bnez    $v0, loc_5FB8C
			andi    $v1, $s0, 0x280
			lbu     $v1, 0x3F7E($gp)
			li      $v0, 0x7F
			subu    $v0, $v1
			sll     $v0, 24
			sra     $a0, $v0, 24
			andi    $v1, $s0, 0x80
			sll     $v1, 24
			slti    $v0, $a0, 0x21
			bnez    $v0, loc_5FAE4
			sra     $a1, $v1, 24
			slti    $v0, $a0, 0x60
			beqz    $v0, loc_5FB0C
			ori     $s0, 4
			j       loc_5FAFC
			lui     $v0, 0x100

			loc_5FAE4:
		slti    $v0, $a0, -0x20
			beqz    $v0, loc_5FB0C
			slti    $v0, $a0, -0x5F
			bnez    $v0, loc_5FB0C
			ori     $s0, 8
			lui     $v0, 0x100

			loc_5FAFC:
		and     $v0, $s0, $v0
			bnez    $v0, loc_5FB0C
			nop
			ori     $s0, 0x80

			loc_5FB0C :
			lbu     $v0, 0x3F7F($gp)
			li      $v1, 0x7F
			subu    $v1, $v0
			sll     $v1, 24
			sra     $a0, $v1, 24
			slti    $v0, $a0, 0x21
			bnez    $v0, loc_5FB50
			slti    $v0, $a0, -0x20
			slti    $v0, $a0, 0x60
			beqz    $v0, loc_5FB78
			ori     $s0, 1
			lui     $v0, 0x100
			and $v0, $s0, $v0
			beqz    $v0, loc_5FB70
			nop
			j       loc_5FB78
			nop

			loc_5FB50 :
		beqz    $v0, loc_5FB88
			slti    $v0, $a0, -0x5F
			bnez    $v0, loc_5FB78
			ori     $s0, 2
			lui     $v0, 0x100
			and $v0, $s0, $v0
			bnez    $v0, loc_5FB78
			nop

			loc_5FB70 :
		j       loc_5FB88
			ori     $s0, 0x80

			loc_5FB78 :
			bnez    $a1, loc_5FB8C
			andi    $v1, $s0, 0x280
			li      $v0, 0xFFFFFF7F
			and $s0, $v0

			loc_5FB88 :
		andi    $v1, $s0, 0x280

			loc_5FB8C :
			li      $v0, 0x80
			bne     $v1, $v0, loc_5FBE8
			andi    $v0, $s0, 0x200
			lw      $v0, dword_A0758
			nop
			bnez    $v0, loc_5FBE8
			andi    $v0, $s0, 0x200
			andi    $v0, $s0, 3
			bnez    $v0, loc_5FBE8
			andi    $v0, $s0, 0x200
			andi    $v0, $s0, 4
			beqz    $v0, loc_5FBD0
			li      $v0, 0xFFFFFFFB
			and $v0, $s0, $v0
			j       loc_5FBE4
			ori     $s0, $v0, 0x400

			loc_5FBD0:
		andi    $v0, $s0, 8
			beqz    $v0, loc_5FBE4
			li      $v0, 0xFFFFFFF7
			and $v0, $s0, $v0
			ori     $s0, $v0, 0x800

			loc_5FBE4 :
			andi    $v0, $s0, 0x200

			loc_5FBE8 :
			beqz    $v0, loc_5FC04
			nop
			lw      $v0, dword_A0758
			nop
			beqz    $v0, loc_5FD00
			andi    $v0, $s0, 0xF

			loc_5FC04:
		lbu     $v0, 0x3F7D($gp)
			li      $v1, 0x7F
			subu    $v1, $v0
			sll     $v1, 24
			sra     $a0, $v1, 24
			slti    $v0, $a0, 0x21
			bnez    $v0, loc_5FC40
			addiu   $v0, $a0, -0x20
			sll     $v1, $v0, 5
			addu    $v1, $v0
			sll     $v1, 1
			negu    $v1, $v1
			sw      $v1, 0x3FD0($gp)
			j       loc_5FC6C
			lui     $v0, 0x800

			loc_5FC40:
		slti    $v0, $a0, -0x20
			beqz    $v0, loc_5FC78
			addiu   $v0, $a0, 0x20
			sll     $v1, $v0, 2
			addu    $v1, $v0
			sll     $v1, 2
			addu    $v1, $v0
			sll     $v1, 1
			negu    $v1, $v1
			sw      $v1, 0x3FD0($gp)
			lui     $v0, 0x1000

			loc_5FC6C:
		ori     $v0, 0x200
			j       loc_5FC7C
			or $s0, $v0

			loc_5FC78 :
		sw      $zero, 0x3FD0($gp)

			loc_5FC7C :
			lbu     $v0, 0x3F7C($gp)
			li      $v1, 0x7F
			subu    $v1, $v0
			sll     $v1, 24
			sra     $a0, $v1, 24
			slti    $v0, $a0, 0x21
			bnez    $v0, loc_5FCC4
			slti    $v0, $a0, -0x20
			addiu   $v0, $a0, -0x20
			sll     $v1, $v0, 2
			addu    $v1, $v0
			sll     $v1, 2
			addu    $v1, $v0
			sll     $v1, 2
			subu    $v0, $v1
			sw      $v0, 0x3FD4($gp)
			j       loc_5FCEC
			lui     $v1, 0x400

			loc_5FCC4:
		beqz    $v0, loc_5FCF8
			addiu   $v0, $a0, 0x20
			sll     $v1, $v0, 2
			addu    $v1, $v0
			sll     $v1, 2
			addu    $v1, $v0
			sll     $v1, 2
			subu    $v0, $v1
			sw      $v0, 0x3FD4($gp)
			lui     $v1, 0x200

			loc_5FCEC:
		ori     $v1, 0x200
			j       loc_5FCFC
			or $s0, $v1

			loc_5FCF8 :
		sw      $zero, 0x3FD4($gp)

			loc_5FCFC :
			andi    $v0, $s0, 0xF
#endif
	}
	//loc_5FD00
	if (!(in & 0xF))
	{
		if ((RawPad & IN_DPAD_UP))
		{
			in |= IN_FORWARD;
		}//loc_5FD24
		else if ((RawPad & IN_DPAD_DOWN))
		{
			in |= IN_BACK;
		}

		//loc_5FD34
		if ((RawPad & IN_DPAD_LEFT))
		{
			in |= IN_LEFT;
		}//loc_5FD4C
		else if ((RawPad & IN_DPAD_RIGHT))
		{
			in |= IN_RIGHT;
		}

		if ((in & (IN_LOOK | IN_WALK)) == IN_WALK && BinocularRange == 0 &&
			!(in & (IN_FORWARD | IN_BACK)))
		{
			if ((in & IN_LEFT))
			{
				in = (in & 0xFFFFFFFB) | IN_LSTEP;
			}//loc_5FDA0
			else if ((in & IN_RIGHT))
			{
				in = (in & 0xFFFFFFF7) | IN_RSTEP;
			}
		}//loc_5FDB8
	}//loc_5FDB8

	if ((in & IN_LOOK))
	{
		if (lara_item->current_anim_state == 2 || lara_item->goal_anim_state == 2)
		{
			//loc_5FDEC
			if ((in & 0xF) || type == 7)
			{
				LookCnt = 100;
			}//loc_5FE04
		}//loc_5FE04

		if (LookCnt < 6)
		{
			LookCnt++;
			in &= 0xFFFFFDFF;
		}//loc_5FE28
		else
		{
			LookCnt = 100;
		}
	}
	else
	{
		//loc_5FE38
		if (LookCnt != 0 && LookCnt != 100)
		{
			in |= IN_UNK31;
		}

		//loc_5FE54
		LookCnt = 0;
	}
	//loc_5FE58

	//loc_5FE5C
	if (PadInfoMode(0, InfoModeCurExID, 0) != 0)
	{
		DualShock = 1;

		if (state == 1 || state == 4)
		{
			//loc_5FE88
			send = 0;
		}
		//loc_5FE8C
		if (send == 0)
		{
			if (state == 2 || state == 6 && PadSetActAlign(0, &align[0]) != 0)
			{
				send = 1;
			}
		}
		else
		{
			//loc_5FED4
			PadSetAct(0, &Motors[0], 2);
		}
	}
	else
	{
		//loc_5FEE8
		DualShock = 0;
	}

	//loc_5FEEC
	if ((RawPad == (IN_R2 | IN_L1 | IN_CROSS | IN_SQUARE)))
	{
		in |= IN_CHEAT;
	}
	//loc_5FF00
#if PROT_VERSION
	Edge2 = Pad2;

	if (GPad2.transStatus != -1)
	{
		Pad2 = (GPad2.data.pad ^ -1) & 0xFFFF;
	}
	else
	{
		//loc_5FF34
		Pad2 = 0;
	}

	//loc_5FF38
	Edge2 = (Edge2 ^ Pad2) & Pad2;


#if DEBUG_VERSION
	if ((Edge2 & 0x10) != 0)
	{
		gfRequiredStartPos = 0;
		gfLevelComplete = gfCurrentLevel + 1;
	}

	if ((Edge2 & 0x40) != 0)
	{
		gfRequiredStartPos = 0;
		gfLevelComplete = gfCurrentLevel - 1;
	}

	if ((Edge2 & 0x20) != 0)
	{
		gfRequiredStartPos = 0;
		gfLevelComplete = gfCurrentLevel + 1;
	}

	//loc_5FFC8
	if (Gameflow->CheatEnabled)
	{
		if (RawPad == (IN_R2 | IN_L1 | IN_CROSS | IN_SQUARE))
		{
			in |= IN_CHEAT;
		}//loc_60004

		if (RawPad == (IN_CIRCLE | IN_SQUARE))
		{
			in |= IN_D;
		}//loc_60010
	}//loc_60010
#endif

	if ((Pad2 & 0x800))
	{
		assert(0);
	}
	//loc_6002C
#endif

	inputBusy = in;

	if (lara.Busy)
	{
		input = in & 0x1E00230F;
	}
	else
	{
		//loc_60054
		input = in;
	}

	//loc_60058
	if (SetDebounce != 0)
	{
		dbinput = (dbinput ^ inputBusy) & inputBusy;
	}//loc_60084

	dbinput2 = dbinput;

	if (gfGameMode == 1)
	{
		dbinput = 0;
		input = 0;

		if (!Gameflow->DemoDisc)
		{
			reset_flag = 0;
		}
	}

	//loc_600CC
	return;
}