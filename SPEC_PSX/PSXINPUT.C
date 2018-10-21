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
#include <STDIO.H>
#include <ASSERT.H>
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
struct GouraudBarColourSet healthBarColourSet;
struct GouraudBarColourSet poisonBarColourSet;
struct GouraudBarColourSet airBarColourSet;
struct GouraudBarColourSet dashBarColourSet;

int dword_A1894;
int dword_A1890;
int dword_A1898;

void S_UpdateInput()//5F628(<), 6038C(<)
{
#ifndef PAELLA
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
	static int send;
	int v1 = 0;

	in = 0;

	if (SayNoCount != 0)
	{
		SayNoCount--;
	}

	//loc_5F650
	state = PadGetState(0);
	type = PadInfoMode(0, 1, 0);
	PadConnected = 0;
	if (state == 0)
	{
		if (type != 4 || type != 7)
		{
			//loc_5F688
			RawPad = 0;
			PadConnected = 0;
			RawEdge = 0;
			input = 0;

			dword_A1894 = 0;//static? sw
			dword_A1890 = 0;//static? sw
			reset_count = 0;
			return;
		}
	}

	//loc_5F6AC
	if (SetDebounce != 0)
	{
		dbinput = inputBusy;
		RawEdge = RawPad;
	}

	//loc_5F6D0
	PadConnected = 1;
	RawPad = (GPad1.data.pad ^ -1) & 0xFFFF;
	if (SetDebounce != 0)
	{
		RawEdge ^= RawPad;
		RawEdge &= RawPad;
	}

	//loc_5F704
	if (RawEdge & 1)
	{
		dword_A1894 = 1;//static? sw
	}

	//loc_5F71C
	if (RawPad & 1)
	{
		if (RawPad & 0x800)
		{
			if (lara_item->current_anim_state - 80 < 2 || lara_item->current_anim_state == 0x54 && lara_item->current_anim_state == 0x55 || lara_item->current_anim_state == 0x56 || lara_item->current_anim_state == 0x58)
			{
				//loc_5F780
				if (lara_item->pos.x_pos != OldPickupPos.x || lara_item->pos.y_pos != OldPickupPos.y || lara_item->pos.z_pos != OldPickupPos.z)
				{
					if (SayNoCount == 0)
					{
						SayNoCount = 30;

						OldPickupPos.x = lara_item->pos.x_pos;
						OldPickupPos.y = lara_item->pos.y_pos;
						OldPickupPos.z = lara_item->pos.z_pos;

						SayNo();
					}//loc_5F81C
				}//5F81C
			}
			else
			{
				//loc_5F818
				in = 0x8000;
			}

			//loc_5F81C
			dword_A1894 = 0;
			RawPad &= -513;
		}
		//loc_5F830
		if (RawPad & 8)
		{
			reset_count++;

			if (RawPad > 0x30)
			{
				reset_flag = 0;
			}

			dword_A1894 = 0;
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
		if (dword_A1894 != 0)
		{
			in = 0x100;
		}

		//loc_5F89C
		reset_count = 0;
		dword_A1894 = 0;

		if (RawEdge & 8)
		{
			in |= 0x2000;
		}//loc_5F8B0
	}

	//loc_5F8B0
	if (RawPad & 0x4000)
	{
		in |= 0x10000;
	}//loc_5F8C8

	if (RawPad & 0x1000)
	{
		in |= 0x20000;
	}//loc_5F8D8

	if (RawPad & 0x8000)
	{
		in |= pad_cons[savegame.ControlOption].pad_square;
	}//loc_5F904

	if (RawPad & 0x2000)
	{
		in |= pad_cons[savegame.ControlOption].pad_circle;
	}//loc_5F930

	if (RawPad & 0x1000)//merge?
	{
		in |= pad_cons[savegame.ControlOption].pad_triangle;
	}//loc_5F958

	if (RawPad & 0x4000)//merge?
	{
		in |= pad_cons[savegame.ControlOption].pad_cross;
	}//loc_5F980

	if (RawPad & 0x400)
	{
		in |= pad_cons[savegame.ControlOption].pad_L1;
	}//loc_5F9AC

	if (RawPad & 0x100)
	{
		in |= pad_cons[savegame.ControlOption].pad_L2;
	}//loc_5F9D8

	if (RawPad & 0x800)
	{
		in |= pad_cons[savegame.ControlOption].pad_R1;
	}//loc_5FA04

	if (RawPad & 0x200)
	{
		in |= pad_cons[savegame.ControlOption].pad_R2;
	}
	//loc_5FA30

	if (type == 7)///@TODO
	{
		if (RawPad & 2)
		{
			in |= pad_cons[savegame.ControlOption].pad_square;
		}//loc_5FA70

		if (RawPad & 4)
		{
			in |= pad_cons[savegame.ControlOption].pad_cross;
		}//loc_5FA9C

		//v1 = in & 0x280;
		if (in & 0x200)
		{
			assert(0);
			//lbu	$v1, 0x3F7E($gp) (GPad1+0x6)
			//v1 = GPad1.data.mouse.xOffset;
			//v0 = 0x7F;
			//v0 -= v1;
			//v0 <<= 24;
			//a0 = v0 >> 24;
			//v1 = in & 0x80;
			//v1 <<= 24;
			//v0 = a0 < 0x21 ? 1 : 0;
			//a1 = v1 >> 24;
			//if (a0 < 0x21)
			{
				//loc_5FAE4
			}
			//else if (a0 > 0x5F)
			{
				in |= 4;
				//loc_5FAFC
			}
			//else
			{
				in |= 4;
			}
		}//loc_5FB8C

		if (in & 0x280 == 0x80 && BinocularRange == 0 && !(in & 3))
		{
			if (in & 4)
			{
				in &= -5;
				in |= 0x400;
			}
			else
			{
				//loc_5FBD0
				if (in & 8)
				{
					in &= -9;
					in |= 0x800;
				}//loc_5FBE4
			}
			//loc_5FBE4
		}//loc_5FBE8

		if (!(in & 0x200) && BinocularRange != 0)
		{
			//loc_5FC04
			///@FIXME GPad1+5 invalid!
			assert(0);
#if 0
			//v1 = GPad1.data.mouse.yOffset;

			loc_5FC04:
			lbu	$v0, 0x3F7D($gp)
			li	$v1, 0x7F
			subu	$v1, $v0
			sll	$v1, 24
			sra	$a0, $v1, 24
			slti	$v0, $a0, 0x21
			bnez	$v0, loc_5FC40
			addiu	$v0, $a0, -0x20
			sll	$v1, $v0, 5
			addu	$v1, $v0
			sll	$v1, 1
			negu	$v1, $v1
			sw	$v1, 0x3FD0($gp)
			j	loc_5FC6C
			lui	$v0, 0x800

			loc_5FC40:
			slti	$v0, $a0, -0x20
			beqz	$v0, loc_5FC78
			addiu	$v0, $a0, 0x20
			sll	$v1, $v0, 2
			addu	$v1, $v0
			sll	$v1, 2
			addu	$v1, $v0
			sll	$v1, 1
			negu	$v1, $v1
			sw	$v1, 0x3FD0($gp)
			lui	$v0, 0x1000
			
			loc_5FC6C:
			ori	$v0, 0x200
			j	loc_5FC7C
			or $s0, $v0

			loc_5FC78 :
			sw	$zero, 0x3FD0($gp)

			loc_5FC7C :
			lbu	$v0, 0x3F7C($gp)
			li	$v1, 0x7F
			subu	$v1, $v0
			sll	$v1, 24
			sra	$a0, $v1, 24
			slti	$v0, $a0, 0x21
			bnez	$v0, loc_5FCC4
			slti	$v0, $a0, -0x20
			addiu	$v0, $a0, -0x20
			sll	$v1, $v0, 2
			addu	$v1, $v0
			sll	$v1, 2
			addu	$v1, $v0
			sll	$v1, 2
			subu	$v0, $v1
			sw	$v0, 0x3FD4($gp)
			j	loc_5FCEC
			lui	$v1, 0x400

			loc_5FCC4:
			beqz	$v0, loc_5FCF8
			addiu	$v0, $a0, 0x20
			sll	$v1, $v0, 2
			addu	$v1, $v0
			sll	$v1, 2
			addu	$v1, $v0
			sll	$v1, 2
			subu	$v0, $v1
			sw	$v0, 0x3FD4($gp)
			lui	$v1, 0x200

			loc_5FCEC:
			ori	$v1, 0x200
			j	loc_5FCFC
			or $s0, $v1

			loc_5FCF8 :
			sw	$zero, 0x3FD4($gp)

			loc_5FCFC :
			andi	$v0, $s0, 0xF
#endif
		}

	}//loc_5FD00

	if (in & 0xF)
	{
		if (RawPad & 0x10)
		{
			in |= 1;
		}
		else if (RawPad & 0x40)
		{
			//loc_5FD24
			in |= 2;
		}//loc_5FD34

		if (RawPad & 0x80)
		{
			in |= 4;
		}
		else if (RawPad & 0x20)
		{
			//loc_5FD4C
			in |= 8;
		}

		//loc_5FD58
		if (in & 0x280 == 0x80 && BinocularRange == 0 && !(in & 3))
		{
			if (in & 4)
			{
				in &= -5;
				in |= 0x400;
			}
			else
			{
				//loc_5FDA0
				if (in & 8)
				{
					in &= -9;
					in |= 0x800;
				}
			}//loc_5FDB4
		}//loc_5FDB8
	}//loc_5FDB8

	if (in & 0x200)
	{
		if (lara_item->current_anim_state != 2 && lara_item->goal_anim_state == 2)
		{
			//loc_5FDEC
			if (in & 0xF)
			{
				dword_A1898 = 0x64;
			}
			else if (type == 7)
			{
				dword_A1898 = 0x64;
			}
		}//loc_5FE04

		if (dword_A1898 < 6)
		{
			dword_A1898++;
			in &= -513;
			//loc_5FE58
			pos = 0;
		}
		else
		{
			//loc_5FE28
			dword_A1898 = 0x64;
		}
	}
	else
	{
		//loc_5FE38
		if (dword_A1898 != 0 && dword_A1898 != 0x64)
		{
			in |= 0x8000;
		}

		dword_A1898 = 0;
	}

	//loc_5FE5C
	if (PadInfoMode(0, 1, 2) != 0)
	{
		DualShock = 1;
		if (state != 1 && state != 4)
		{
			//loc_5FE88
			send = 0;
		}

		//loc_5FE8C
		if (send == 0)
		{
			if (state == 2)
			{
				//loc_5FEC4
				send = 1;
			}
			else if (state == 6)
			{
				PadSetActAlign(0, &align[0]);
			}

		}//loc_5FED4
	}
	else
	{
		//loc_5FEE8
		DualShock = 0;
	}

	//loc_5FEEC
	if (RawPad == 0xC600)
	{
		in |= 0x10000;
	}//loc_5FF00

	//Edge2 = Pad2.3;
#if DEBUG_VERSION
	assert(0);
	if (GPad2.transStatus != 0xFF)
	{
#if 0
		lhu	$v0, 0x3F9E($gp)
			nop
			nor	$v0, $zero, $v0
			andi	$v0, 0xFFFF
			sw	$v0, 0x3F68($gp)
#endif
	}
	else
	{
		//loc_5FF34
		//Pad2.3 = 0;
	}

	//loc_5FF38
	//Edge2 = Pad2.3 & (Edge2 ^ Pad2.3);
	//Edge2 = v1;

	//v0 = Edge2 & 0x40;
	if (Edge2 & 0x10)
	{
		gfRequiredStartPos = 0;
		gfLevelComplete = gfCurrentLevel + 1;
	}//loc_5FF7C

	//v0 = Edge2 & 0x20;
	if (Edge2 & 0x40)
	{
		gfRequiredStartPos = 0;
		gfLevelComplete = gfCurrentLevel - 1;
	}//loc_5FFA4

	if (Edge2 & 0x20)
	{
		gfRequiredStartPos = 0;
		gfLevelComplete = gfCurrentLevel + 1;
	}//loc_5FFC8

	//v1 = Gameflow;//int flags
	//v0 = 0xA000
	if (Gameflow->CheatEnabled)
	{
		if (RawPad == 0xC600)
		{
			in |= 0x10000;
		}//loc_60004

		if (RawPad == 0xA000)
		{
			in |= 0x20000;
		}

	}//loc_60010

	//v0 = Pad2.3;
	//v1 = 0xA0000
#if 0
	if (Pad2.3 & 0x800)
	{
		S_Warn("[S_UpdateInput] - Break 0x400!\n");

	}//loc_6002C
#endif
#endif

	inputBusy = in;
	if (lara.has_fired)
	{
		input = 0x1E00230F & in;
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

		if (Gameflow->DemoDisc)
		{
			reset_flag = 0;
		}
	}//loc_600CC

	return;
#endif
}