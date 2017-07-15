#include "SETUP.H"

#include "CONTROL.H"
#include "DRAW.H"
#include "GAMEWAD.H"
#include "GPU.H"
#include "LOAD_LEV.H"
#include "MALLOC.H"
#include "ROOMLOAD.H"

#include <assert.h>
#include <stddef.h>

//temp
#include <stdio.h>

char setupBuff[SETUP_MOD_FILE_SIZE];

char dword_A3C18;
int dword_A616C;
int dword_A6F0C = 0;
int dword_A6E90;
int dword_A5620;
short dword_A6090;
int dword_A60BC;
int* dword_A60B0;
int* dword_A3CF4;
int* dword_A3B50;
int* dword_A60F8;
int* dword_A4014;
int* dword_A3FFC;
int* dword_A4038;

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
	char* ptr = NULL;
	unsigned long size;
	int i, j;

	InItemControlLoop = 0;

	//Read up the PSX file header into buff.
	GAMEWAD_Read(PSX_HEADER_LENGTH, (char*) &RelocPtr);

	LaraDrawType = RelocPtr[12] & 7;
	WeatherType = (RelocPtr[12] << 3) & 3;
	dword_A3C18 = (RelocPtr[12] >> 5) & 3;//?

	//We only want to send sound effect audio data if there are sound effects!
	if (RelocPtr[9] != 0)
	{
		dword_A616C = 0;//?

		//Allocate enough memory to store the sound pointers
		ptr = game_malloc(RelocPtr[9] * sizeof(unsigned long));

		//Reading in soundpointers
		GAMEWAD_Read(RelocPtr[9] * sizeof(unsigned long), ptr);

		//Allocating enough memory for the 8000hz vag soundwad
		ptr = game_malloc(RelocPtr[10]);

		GAMEWAD_Read(RelocPtr[10], ptr);

		//unsigned long a0 = RelocPtr[9];
		//unsigned long a3 = RelocPtr[10];

		//Send audio to SPU?
		//sub_B3974(RelocPtr[9], RelocPtr[10], ptr);

		//Free audio data from malloc_buffer
		game_free(RelocPtr[9] * sizeof(unsigned long));
		game_free(RelocPtr[10]);
	}

	//? 2 tpages?
	ptr = game_malloc(0x40000);

	int v1 = 0x200;
	int v0 = 0x100;

	///@TODO Unknown const 2.
	for (int i = 0; i < 2; i++)
	{
		GAMEWAD_Read(0x40000, ptr);

		LOAD_DrawEnable(0);

#ifdef PSX
		//4bit textures?
		//LoadImage(ptr); //jal sub_6B1C4
		//DrawSync(0); //jal sub_6B144
#endif

		LOAD_DrawEnable(1);

		//v0 += 0x100; //?
	}

	game_free(0x40000);

	dword_A6090 = RelocPtr[11];//FIXME LHU
	dword_A60BC = dword_A5620;//FIXME = 0x803! sw @sub_60D20 > $gp(38A8)

	AnimFileLen = RelocPtr[26];
	ptr = game_malloc(AnimFileLen);
	frames = (short*) ptr;
	GAMEWAD_Read(AnimFileLen, ptr);

	ptr = game_malloc(RelocPtr[14]);
	GAMEWAD_Read(RelocPtr[14], ptr);

	number_rooms = *(((unsigned short*) &RelocPtr[11]) + 1);//0xB3D28

	room = (struct room_info*)ptr;

	ptr += ((number_rooms * sizeof(unsigned long)) + number_rooms) * 16;//16 sizeof room_header?

	if (number_rooms > 0)
	{
		for (i = 0; i < number_rooms; i++)
		{
			int* a1 = (int*) &ptr[4];

			struct room_info* r = &room[i];

			size = (int) r->data;
			r->data = (short*) ptr;
			ptr += size;

			//Floor data
			///@TODO Unknown const 24.
			for (j = 0; j < 24; j++, a1++)
			{
				*a1 += *(int*) r;
			}

			size = (unsigned long) r->door;
			r->door = (short*) ptr;
			ptr += size;

			size = (unsigned long) r->floor;
			r->floor = (struct FLOOR_INFO*)ptr;
			ptr += size;

			size = (unsigned long) r->light;
			r->light = (struct LIGHTINFO*)ptr;
			ptr += size;

			size = (unsigned long) r->mesh;
			r->mesh = (struct MESH_INFO*)ptr;
			ptr += size;
		}
	}
	dword_A60B0 = (int*) ptr;//?
	ptr += RelocPtr[15];

	dword_A3CF4 = (int*) ptr;//?
	ptr += 0x5B4;//?

	dword_A3B50 = (int*) ptr;//?
	ptr += RelocPtr[16];

	dword_A60F8 = (int*) ptr;//?
	ptr += RelocPtr[17];

	mesh_base = (short*) ptr;//?
	ptr += RelocPtr[19];

	meshes = (short**) ptr;//?
	ptr += RelocPtr[20];

	anims = (struct ANIM_STRUCT*)ptr;
	ptr += RelocPtr[21];

	dword_A4014 = (int*) ptr;//?
	ptr += RelocPtr[22];

	dword_A3FFC = (int*) ptr;//?
	ptr += RelocPtr[23];

	dword_A4038 = (int*) ptr;//?
	ptr += RelocPtr[24];

	v1 = RelocPtr[25];
	bones = (long*) ptr;

	//^Verified^***************************************************************

#if 0
	v0 = *(short*) &RelocPtr[18];
	v0 *= 2;

	//END
	char* s00 = ptr;

	if (v0 > 0)
	{
		short** dbug;
		for (int i = 0; i < RelocPtr[18] * sizeof(short); i++)
		{
			short* a11 = mesh_base;

			short** a00 = meshes;

			short v000 = (short) *a00;//?

			v1 = v000 << 0x1F;
			v000 += v1;
			v000 >>= 1;
			v000 <= 1;
			short* v0000 = v000 + a11;

			*a00 = v0000;//ILLEGAL

			v1 = *(short*) &RelocPtr[18];
			v1 <<= 1;
			//v1 = v1 < s4 ? 1 : 0;

			a00 += 4;
			dbug = a00;///@critical fix me, illegal ptr
		}


		v0 = *(((short*) (&RelocPtr[18])) + 1);

		if (v0 > 0)//blez 0xB3F14
		{
			short* a111111 = frames;//fixme bad ptr
			struct ANIM_STRUCT* a000000 = anims;

			for (int i = 0; i < *(((short*) (&RelocPtr[18])) + 1); i++, a000000++)
			{
				short* v00000 = frames + *(int*) a000000;
				//*(int*) a000000 = *(int*) v00000;

			}//bne 0xB3F4C
		}

		v1 = RelocPtr[30];
		int a0 = 0x9000;
		//0xA6170 = s00 sw
		v0 = RelocPtr[27];
		short t3 = RelocPtr[47];
		int t2 = RelocPtr[38];

		s00 += v1;///@fixme illegal ptr SHOULD NOW POINT TO OBJ TEXTRS!

		/*
		 * Object Textures
		 */
		psxtextinfo = (struct PSXTEXTSTRUCT*)s00;
		s00 += v0;

		v1 = RelocPtr[28];
		int a3 = RelocPtr[31];
		psxspriteinfo = (struct PSXSPRITESTRUCT*)s00;
		s00 += v1;

		v1 = RelocPtr[29];

		//sw A5FF8 s00
		s00 += v1;

		//sw A50FC s00
		s00 += a3;

		//sw A5370 s00
		s00 += 0x384;

		v1 = RelocPtr[32];
		//sw A5374 s00

		a3 >>= 4;
		s00 += v1;

		items = (struct ITEM_INFO*)s00;

		s00 += a0;

		int testing9 = 0;
		testing9++;

		v0 = t3;

		//0xBFE4

	}
//0xB4730 is end jalr v0
#endif
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