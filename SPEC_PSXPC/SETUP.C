#include "SETUP.H"

#include "CONTROL.H"
#include "DRAW.H"
#include "GAMEWAD.H"
#include "LOAD_LEV.H"
#include "MALLOC.H"
#include "ROOMLOAD.H"

#include <assert.h>

char setupBuff[SETUP_MOD_FILE_SIZE];

char dword_A3C18;
int dword_A616C;
int dword_A6F0C = 0;
int dword_A6E90;
int dword_A5620;
short dword_A6090;
int dword_A60BC;

#define PSX_HEADER_LENGTH 228

/*
 * [FUNCTIONALITY] - RelocateLevel.
 * Relocates all game data pointers from the level file to be loaded back into the engine.
 * Note: The GAMEWAD reader must be initialised to a level file entry.
 * Note: The GAMEWAD reader's position must point to the level file data.
 * Note: This code is part of the SETUP.MOD module.
 */

void RelocateLevel()//?, B3B50(<)
{
	unsigned long* s5 = &RelocPtr[0];
	int v00 = 0x000A0000;//?
	
	//(char*)0xA28B9 = 0;

	//Read up the PSX file header into buff.
	GAMEWAD_Read(PSX_HEADER_LENGTH, (char*)&RelocPtr);

	LaraDrawType = ((unsigned short)RelocPtr[12]) & 7;
	WeatherType = (RelocPtr[12] << 3) & 3;
	dword_A3C18 = (RelocPtr[12] >> 5) & 3;

	if (RelocPtr[9] != 0)
	{
		dword_A616C = 0;

		//Possibly num sounds and sound ptrs
		char* ptr = game_malloc(RelocPtr[9] * sizeof(unsigned long));
		GAMEWAD_Read(RelocPtr[9] * sizeof(unsigned long), ptr);

		//Soundwad
		ptr = game_malloc(RelocPtr[10]);
		GAMEWAD_Read(RelocPtr[10], ptr);

		//unsigned long a0 = RelocPtr[9];
		//unsigned long a3 = RelocPtr[10];

		//Send audio to SPU?
		//a2 = s0;
		//sub_B3974(RelocPtr[9], RelocPtr[10], ptr);

		//dword_A616C = v0;//FIXME v0 is 1 from where?
		
		//Free audio data from malloc_buffer
		game_free(RelocPtr[9] * sizeof(unsigned long));
		game_free(RelocPtr[10]);
	}

	///0xB3C44
	//? 2 tpages?
	char* ptr = game_malloc(0x40000);
	
	int v1 = 0x200;
	int v0 = 0x100;

	for (int s4 = 1; s4 > -1; s4--)
	{
		char* a0 = ptr;

		GAMEWAD_Read(0x40000, ptr);

		LOAD_DrawEnable(0);//jal sub_5FFA8

#ifdef PSX
	//4bit textures
	//LoadImage(ptr); //jal sub_6B1C4
	//DrawSync(0); //jal sub_6B144
#endif

		LOAD_DrawEnable(1);//jal sub_5FFA8

		v0 += 0x100;
	}
	//loop end 0xB3CBC
	game_free(0x40000);//0xB3CC4

	unsigned long a0 = RelocPtr[26];//0x50868
	unsigned short a1 = RelocPtr[11];//0x100
	int a2 = dword_A5620;//todo 0x803 find sw or init
	dword_A6090 = RelocPtr[11];
	dump_game_malloc();

	dword_A60BC = a2;

	char* a00 = game_malloc(RelocPtr[26]);

	unsigned long a11 = RelocPtr[26];

	//frames = v0;//A25F4, A3FF8

	//fixme loading wrong data
	GAMEWAD_Read(a0, a00);

	AnimFileLen = RelocPtr[26];
	char* s00 = game_malloc(RelocPtr[14]);//0x7FEE0

	//s0 = v0
	a1 = RelocPtr[14];
	GAMEWAD_Read(RelocPtr[14], s00);

	dump_game_malloc();

	unsigned short a000 = *(((unsigned short*)&RelocPtr[11])+1);

	int s4 = 0;

	room = (struct room_info*)s00;
	

	v1 = a000 << 16;
	v1 >>= 16;//why?

	v0 = v1 << 2;
	v0 += v1;
	v0 <<= 4;
	s00 += v0;

	number_rooms = a0;//A4030 = 

	//number_rooms = v1
	if (v1 > 0)
	{
		//a3 = s1 //"
		//t4 = v0;//0x000A
		int t2 = 0;
		int t1 = 0;
		int t0 = 0;

		//TODO for loop each room
		//but why? is the data stored elsewhere?
		{
		char* a11 = s00;
		struct room_info* v0 = room;
		a11 += 4;
		v0 = (struct room_info*)((char*) v0 + t0);
		int t3 = *(int*) v0;//word 0x5d4
		int a2 = t1;
		v0->data = (short*) s00;

		s00 += t3;
		//filling buffer with ptrs
		//FIXME? iter num tpages?
		for (int t33 = 23; t33 >= 0; t33--)
		{
			v0 = room;

			v1 = *(int*) a11;

			v0 = (struct room_info*)((char*) v0 + a2);//useless

			a0 = *(int*) v0;

			t3--;

			v1 += a0;
			*(int*) a11 = v1;
			a11 += 4;
		}//0xB3AC bgez

		//0xB3DB0
		int test2 = 0;
		test2++;

		t1 += 0x50;
		struct room_info* v11 = room;
		short v0000 = number_rooms;

		v1 += t2;
		t3 = (unsigned long) v11->door;
		t0 += 0x50;
		v11->door = (short*) s00;
		s00 += t3;

		t3 = (unsigned long) v11->floor;
		s4 += 1;//should be 0
		v11->floor = (struct FLOOR_INFO*)s00;
		s00 += t3;

		t3 = (unsigned long) v11->light;
		t2 += 0x50;//should be 0
		v11->light = (struct LIGHTINFO*)s00;
		s00 += t3;

		t3 = (unsigned long) v11->mesh;
		v11->mesh = (struct MESH_INFO*)s00;
		s00 += t3;
	}//bne 0xB3E00
	
	}

	//0xB3E0C

	
	//0xB4730 is end jalr v0
}

//Possibly send audio data to SPU
void sub_B3974(unsigned long numSounds, unsigned long soundWadSize, char* ptr)
{
#if 0
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
			assert(0);
			//0xB39B8
		}

		//FIXME
		int v1 = dword_A6F0C;
		int s4 = v0;
		if (v1 != 0)
		{
			assert(0);
			//0xB39D0
		}
		//possible memcpy
		//jal sub_71164

		int s0 = 0x000A000;
		v1 = -1;

		if (v0 == v1)
		{
			//j 0xB39BC
		}

		dword_A6E90 = v0;
		int a0 = 1;
		//jal 0x70CE0

		a0 = dword_A6E90;
		//jal 0x7259C

		//a0 = s3;//malloc_ptr
		//a1 = s1;
		//jal 0x72690
		a0 = 1;
		//jal 0x70CE0
		if (s2 <= 0)
		{
			//jal0xB3A50
		}

		//0xB3A3A
		for (int i = 0; i, 0; i++)
		{
			//load word from game_malloc
			//LadwSampleAddr[i] = *game_malloc+i*sizeof(unsigned int);
		}


	}

	//0xB39BC
#endif
}