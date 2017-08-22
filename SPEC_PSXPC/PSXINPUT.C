#include "PSXINPUT.H"

#include "CONTROL.H"

static struct pad_configs pad_cons[5] =
{
	{ 0x20000000, 0x40000000, 0x200, 0x80, 0x20, 0x10, 0x1000, 0x40 },
	{ 0x200, 0x80, 0x20000000, 0x40000000, 0x1000, 0x20, 0x40, 0x10 },
	{ 0x40000000, 0x20000000, 0x80, 0x200, 0x10, 0x1000, 0x40, 0x20 },
	{ 0x20000000, 0x40000000, 0x20, 0x80, 0x200, 0x40, 0x10, 0x1000 },
	{ 0x1000, 0x20, 0x10, 0x40, 0x40000000, 0x200, 0x20000000, 0x80 }
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
struct ControllerPacket GPad1;
struct ControllerPacket GPad2;
unsigned long Edge2;
struct GouraudBarColourSet healthBarColourSet;
struct GouraudBarColourSet poisonBarColourSet;
struct GouraudBarColourSet airBarColourSet;
struct GouraudBarColourSet dashBarColourSet;

int dword_A1894;
int dword_A1890;

void S_UpdateInput()//5F628, 6038C
{
	int a0, a1, a2, v0, s1, s2;
#if 0
	// line 2, offset 0x5f628
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
#endif

	if (SayNoCount != 0)
	{
		SayNoCount--;
	}//loc_5F650

	//loc_5F650

#ifdef PSX_VERSION
	PadGetState(0);
#endif

	a0 = 0;
	a1 = 1;
	a2 = 0;
	
	v0 = 0;
	s1 = v0;
#ifdef PSX_VERSION
	s1 = v0;
	PadInfoMode();
#endif

	s2 = v0 & 0xFF;
	if (s1 == 0 || (s2 != 4) || (s2 != 2))
	{
		//loc_5F688
		RawPad = 0;
		PadConnected = 0;
		RawEdge = 0;
		input = 0;
		dword_A1894 = 0;//pause_db?
		dword_A1890 = 0;//option_db?
		reset_count = 0;

		//loc_600CC
		return;
	}

	//loc_5F6AC
	if (SetDebounce != 0)
	{
		dbinput = inputBusy;
		RawEdge = RawPad;

	}//loc_5F6D0

	//loc_5F6D0
	v0 = GPad1.data.pad;
	PadConnected = 1;

}