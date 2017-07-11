#include "SETUP.H"

#include "CONTROL.H"
#include "GAMEWAD.H"
#include "MALLOC.H"

#include <assert.h>

char setupBuff[SETUP_MOD_FILE_SIZE];

char dword_A3C18;
int dword_A616C;
int dword_A6F0C = 0;

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

	//it's not loaded properly into buff cause GAMEWAD_Load is unfinished todo
	
	//Read up the PSX file header into buff.
	GAMEWAD_Read(sizeof(PSXHeader), (char*)&psxHeader); //seems to pass 0xE4 as size

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

	a1 = psxHeader.unk09;

	//0xB3C44
	char* a00 = s11;

	GAMEWAD_Read(a1 << 2, a00);

	a0 = psxHeader.soundWadSize;

	char* v00 = game_malloc(a0);

	char* s0 = v00;

	a1 = psxHeader.soundWadSize;
	a00 = s0;

	GAMEWAD_Read(a1, s0);
	//Above is jal at 0xB3C0C

	dump_game_malloc();

	char* a11 = s11;

	a0 = psxHeader.unk09;
	int a3 = psxHeader.soundWadSize;

	sub_B3974(&psxHeader, s11);

	int test = 0;
	test++;

}

void sub_B3974(struct PSXHeader* psxHeader, char* ptr)
{
	int s2 = psxHeader->unk09;
	char* s5 = ptr;//ptr to script end in gamemalloc
	char* s3 = NULL;//TODO: ptr to last gamemalloc alloc
	int s1 = psxHeader->soundWadSize;

	int v0 = s2 < 257 ? 1 : 0;//257 max?

	if (v0 != 0)
	{
		int v0 = 0x00080000;//max sound wad size

		v0 = v0 < s1 ? 1 : 0;

		int v00 = 0x000A0000;
		if (v0 != 0)
		{
			//0xB39B8
		}

		//FIXME
		int v1 = dword_A6F0C;
		int s4 = v0;
		if (v1 != 0)
		{
			//0xB39D0
		}
		//jal sub_71164

	}

	//0xB39BC

}