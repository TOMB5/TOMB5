#include "SETUP.H"

#include "CONTROL.H"
#include "GAMEWAD.H"
#include "MALLOC.H"

struct PSXHeader
{
	unsigned int version;
	unsigned int unk00;
	unsigned int unk01;
	unsigned int unk03;

	unsigned int unk04;
	unsigned int unk05;
	unsigned int unk06;
	unsigned int unk07;

	unsigned int unk08;
	unsigned int unk09;
	unsigned int unk10;
	unsigned int unk11;

	unsigned short unk12;
	unsigned short unk12_0;
	unsigned int unk13;
	unsigned int unk14;
	unsigned int unk15;

	unsigned int unk16;
	unsigned int unk17;
	unsigned int unk18;
	unsigned int unk19;

	unsigned int unk20;
	unsigned int unk21;
	unsigned int unk22;
	unsigned int unk23;

	unsigned int unk24;
	unsigned int unk25;
	unsigned int unk26;
	unsigned int unk27;

	unsigned int unk28;
	unsigned int unk29;
	unsigned int unk30;
	unsigned int unk31;

	unsigned int unk32;
	unsigned int unk33;
	unsigned int unk34;
	unsigned int unk35;

	unsigned int unk36;
	unsigned int unk37;
	unsigned int unk38;
	unsigned int unk39;

	unsigned int unk40;
	unsigned int unk41;
	unsigned int unk42;
	unsigned int unk43;

	unsigned int unk44;
	unsigned int unk45;
	unsigned int unk46;
	unsigned int unk47;

	unsigned int unk48;
	unsigned int unk49;
	unsigned int unk50;
	unsigned int unk51;

	unsigned int unk52;
	unsigned int unk53;
	unsigned int unk54;
	unsigned int unk55;

	unsigned int unk56;
};

char setupBuff[SETUP_MOD_FILE_SIZE];

char dword_A3C18;
int dword_A616C;

void sub_B3B50()//?, B3B50(<)
{
	struct PSXHeader psxHeader;
	int v0 = 0x1F0000;
	int s5 = v0 - 0x1630;
	int a0 = s5;
	int a1 = 0xE4;//228, sizeof level file header
	v0 = 0x000A0000;
	
	/*
	sw sp
	*/
	
	//0xB3B90
	//jal sub_5E414
	//v0_0x28B9 = 0;
	int test = sizeof(PSXHeader);
	char buff[228];
	//it's not loaded properly into buff cause GAMEWAD_Load is unfinished todo
	
	//Read up the PSX file header into buff.
	GAMEWAD_Load(sizeof(PSXHeader), (char*)&psxHeader); //seems to pass 0xE4 as size

	//The level file's header is now loaded
	v0 = 0x000A0000;
	//s7 is psxHeader;

	unsigned short v1 = psxHeader.unk12;
	a1 = 0x000A0000;
	v1 &= 7;
	LaraDrawType = v1;

	a0 = *(int*)&psxHeader.unk12;
	v1 = 0x000A0000;
	v0 = a0 << 3;
	v0 &= 3;
	a0 <<= 5;
	WeatherType = v0;

	v0 = psxHeader.unk09;
	a0 &= 3;

	if (v0 != 0)
	{
		//?
		dword_A3C18 = a0;
	}

	a0 = v0 << 2;

	int s2 = 0x000A0000;
	dword_A616C = 0;
	char* s11 = game_malloc(a0);//jal sub_5F544
	//0xB3C44

}
