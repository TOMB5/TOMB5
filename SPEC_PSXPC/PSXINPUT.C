#include "PSXINPUT.H"

#if 0
static struct pad_configs pad_cons[5];
unsigned char DualShock;
unsigned char PadConnected;
short reset_count;
char SayNoCount;
static unsigned char align[6];
long input;
long dbinput;
long dbinput2;
long inputBusy;
long RawPad;
long RawEdge;
unsigned char Motors[2];
long LaraLookY;
long LaraLookX;
struct ControllerPacket GPad1;
struct ControllerPacket GPad2;
unsigned long Edge2;
struct GouraudBarColourSet healthBarColourSet;
struct GouraudBarColourSet poisonBarColourSet;
struct GouraudBarColourSet airBarColourSet;
struct GouraudBarColourSet dashBarColourSet;

void S_UpdateInput()//5F628, 6038C
{ // line 2, offset 0x5f628
	int state; // $s1
	unsigned char type; // $s2
	unsigned long in; // $s0
	static unsigned long Pad2; // offset 0x0
	static int pause_db; // offset 0xc
	static int option_db; // offset 0x10
	static char LookCnt; // offset 0x14
	{ // line 151, offset 0x5fa3c
		char pos; // $a0
		char walking; // $a1
	} // line 290, offset 0x5fcfc
	{ // line 353, offset 0x5fe70
		static int send; // offset 0x18
	} // line 374, offset 0x5fed4



	int v0 = SayNoCount;
	int s0 = 0;
	int a0 = 0;

	if (v0 != 0)
	{
		///PadGetState();
		a0 = 0;
		a0 = 0;
		int a1 = 1;
		int a2 = 0;

		///PadInfoMode();

		int s1 = v0;

		if (s1 == 0)
		{
#if 0
				sw	$zero, 0x3FC4($gp)
				sb	$zero, 0x12D2($gp)
				sw	$zero, 0x3F6C($gp)
				sw	$zero, 0x3FC8($gp)
				sw	$zero, 0x12E0($gp)
				sw	$zero, 0x12DC($gp)
				sh	$zero, 0x12DA($gp)
				j	loc_600CC
#endif
		}
#if 0
			andi	$s2, $v0, 0xFF
			li	$v0, 4
			beq	$s2, $v0, loc_5F6AC
			li	$v0, 7
			beq	$s2, $v0, loc_5F6AC
			nop
#endif
	}


} // line 474, offset 0x600cc

#endif