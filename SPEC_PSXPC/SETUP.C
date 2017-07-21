#include "SETUP.H"

#include "BOX.H"
#include "CONTROL.H"
#include "DRAW.H"
#include "GAMEWAD.H"
#include "GPU.H"
#include "LOAD_LEV.H"
#include "LOT.H"
#include "MALLOC.H"
#include "ROOMLOAD.H"
#include "SPOTCAM.H"

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
int* dword_A6170;
int* dword_A5FF8;
int* dword_A50FC;
int* dword_A5370;
int* dword_A5374;
int* dword_AD390;
short dword_A6178;
int dword_A50F0;
short dword_A6174;
int dword_3EE4;

int dword_A33D0[512];//FIXME
char objects[32360];
char dword_1EF1D0[0x780];

#define PSX_HEADER_LENGTH 228

//FIXME find original struct!
unsigned long LevelRelocPtr[128];

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
	unsigned int size, i, j;

	InItemControlLoop = 0;

	//Read up the PSX file header into RelocPtr buff.
	GAMEWAD_Read(PSX_HEADER_LENGTH, (char*) &LevelRelocPtr);

	LaraDrawType = LevelRelocPtr[12] & 7;
	WeatherType = (LevelRelocPtr[12] << 3) & 3;
	dword_A3C18 = (LevelRelocPtr[12] >> 5) & 3;//?

	//We only want to send sound effect audio data if there are sound effects!
	if (LevelRelocPtr[9] != 0)
	{
		dword_A616C = 0;//?

		//Allocate enough memory to store the sound pointers
		ptr = game_malloc(LevelRelocPtr[9] * sizeof(unsigned long));

		//Reading in soundpointers
		GAMEWAD_Read(LevelRelocPtr[9] * sizeof(unsigned long), ptr);

		//Allocating enough memory for the 8000hz vag soundwad
		ptr = game_malloc(LevelRelocPtr[10]);

		GAMEWAD_Read(LevelRelocPtr[10], ptr);

		//unsigned long a0 = LevelRelocPtr[9];
		//unsigned long a3 = LevelRelocPtr[10];

		//Send audio to SPU?
		//sub_B3974(LevelRelocPtr[9], LevelRelocPtr[10], ptr);

		//Free audio data from malloc_buffer
		game_free(LevelRelocPtr[9] * sizeof(unsigned long));
		game_free(LevelRelocPtr[10]);
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

	dword_A6090 = LevelRelocPtr[11];//FIXME LHU
	dword_A60BC = dword_A5620;//FIXME = 0x803! sw @sub_60D20 > $gp(38A8)

	AnimFileLen = LevelRelocPtr[26];
	ptr = game_malloc(AnimFileLen);
	frames = (short*) ptr;
	GAMEWAD_Read(AnimFileLen, ptr);

	ptr = game_malloc(LevelRelocPtr[14]);
	GAMEWAD_Read(LevelRelocPtr[14], ptr);

	number_rooms = *(((unsigned short*) &LevelRelocPtr[11]) + 1);//0xB3D28

	room = (struct room_info*)ptr;

	ptr += ((number_rooms * sizeof(unsigned long)) + number_rooms) * 16;//16 sizeof room_header?

	if (number_rooms > 0)
	{
		for (i = 0; i < number_rooms; i++)
		{
			struct room_info* r = &room[i];
			int* a1 = (int*) &ptr[4];

			size = *(unsigned int*) &r->data;
			r->data = (short*) ptr;
			ptr += size;

			///@TODO Unknown const 24.
			for (j = 0; j < 24; j++)
			{
				a1[j] += *(int*) r;//CHECKME possibly broken by refactor
			}

			size = *(unsigned int*) &r->door;
			r->door = (short*) ptr;
			ptr += size;

			size = *(unsigned int*) &r->floor;
			r->floor = (struct FLOOR_INFO*)ptr;
			ptr += size;

			size = *(unsigned int*) &r->light;
			r->light = (struct LIGHTINFO*)ptr;
			ptr += size;

			size = *(unsigned int*) &r->mesh;
			r->mesh = (struct MESH_INFO*)ptr;
			ptr += size;
		}
	}

	dword_A60B0 = (int*) ptr;//?
	ptr += LevelRelocPtr[15];

	dword_A3CF4 = (int*) ptr;//?
	ptr += 0x5B4;//?

	dword_A3B50 = (int*) ptr;//?
	ptr += LevelRelocPtr[16];

	dword_A60F8 = (int*) ptr;//?
	ptr += LevelRelocPtr[17];

	mesh_base = (short*) ptr;
	ptr += LevelRelocPtr[19];

	meshes = (short**) ptr;
	ptr += LevelRelocPtr[20];

	anims = (struct ANIM_STRUCT*)ptr;
	ptr += LevelRelocPtr[21];

	dword_A4014 = (int*) ptr;//?
	ptr += LevelRelocPtr[22];

	dword_A3FFC = (int*) ptr;//?
	ptr += LevelRelocPtr[23];

	dword_A4038 = (int*) ptr;//?
	ptr += LevelRelocPtr[24];

	v1 = LevelRelocPtr[25];
	bones = (long*) ptr;
	ptr += LevelRelocPtr[25];

	if ((LevelRelocPtr[18] & 0xFFFF) > 0)//CHECK
	{
		//Relocating mesh ptrs
		for (i = 0; i < (LevelRelocPtr[18] & 0xFFFF) * sizeof(short); i++)
		{
			//Ptr to current mesh ptr
			int* meshPointer = (int*) &meshes[i];
			*meshPointer >>= 0x1F;
			*meshPointer >>= 1;//&?
			*meshPointer <<= 1;
			*meshPointer += *(int*) mesh_base;
		}

		v0 = *(((short*) (&LevelRelocPtr[18])) + 1);

		if (v0 > 0)//blez 0xB3F14
		{
			//Relocate anim frame ptrs
			for (int i = 0; i < *(((short*) (&LevelRelocPtr[18])) + 1); i++)
			{
				short* currentAnimFrame = frames + *(int*) &anims[i];
				*(int*) &anims[i] = *(int*) currentAnimFrame;
			}
		}

		int a0 = 0x9000;
		dword_A6170 = (int*) ptr;
		ptr += LevelRelocPtr[30];

		v0 = LevelRelocPtr[27];
		short t3 = LevelRelocPtr[47];//FIXME lhu
		int t2 = LevelRelocPtr[38];

		/*
		 * Object Textures
		 */
		psxtextinfo = (struct PSXTEXTSTRUCT*)ptr;
		ptr += LevelRelocPtr[27];

		psxspriteinfo = (struct PSXSPRITESTRUCT*)ptr;
		ptr += LevelRelocPtr[28];

		dword_A5FF8 = (int*) ptr;
		ptr += LevelRelocPtr[29];

		dword_A50FC = (int*) ptr;
		ptr += LevelRelocPtr[31];

		dword_A5370 = (int*) ptr;
		ptr += 0x384;//TODO unknown const *actually, this is size of sound map indices!

		dword_A5374 = (int*) ptr;
		ptr += LevelRelocPtr[32];//0xB3FD0

		items = (struct ITEM_INFO*)ptr;
		ptr += 0x9000;//TODO unknown const

		v0 = t3 << 16;
		v0 >>= 16;
		int a3 = LevelRelocPtr[31] >> 4;

		AIObjects = (struct AIOBJECT*)ptr;

		v1 = v0 << 1;
		v1 += v0;
		v1 <<= 3;
		ptr += v1;

		boxes = (struct box_info*)ptr;
		ptr += LevelRelocPtr[36];

		dword_AD390 = (int*) ptr;
		ptr += LevelRelocPtr[37];

		ground_zone[0][0] = (short*) ptr;
		ptr += LevelRelocPtr[38];

		ground_zone[1][0] = (short*) ptr;
		ptr += LevelRelocPtr[39];

		ground_zone[2][0] = (short*) ptr;
		ptr += LevelRelocPtr[40];

		ground_zone[3][0] = (short*) ptr;
		ptr += LevelRelocPtr[41];

		ground_zone[4][0] = (short*) ptr;
		ptr += LevelRelocPtr[42];

		ground_zone[0][1] = (short*) ptr;
		ptr += LevelRelocPtr[38];

		ground_zone[1][1] = (short*) ptr;
		ptr += LevelRelocPtr[39];

		ground_zone[2][1] = (short*) ptr;
		ptr += LevelRelocPtr[40];

		ground_zone[3][1] = (short*) ptr;
		ptr += LevelRelocPtr[41];

		ground_zone[4][1] = (short*) ptr;
		ptr += LevelRelocPtr[42];

		dword_A6178 = LevelRelocPtr[13];//FIXME LHU @ RELOCPTR
		dword_A50F0 = LevelRelocPtr[31] >> 4;
		dword_A6174 = LevelRelocPtr[13];//FIXME LHU

		level_items = *(((unsigned short*) &LevelRelocPtr[12]) + 1);
		nAIObjects = LevelRelocPtr[47];//FIXME LHU

		number_boxes = LevelRelocPtr[35];

		if (number_boxes > 0)//0xB40B4
		{
			//Set blocked flag on each overlapping box that is last in list.
			for (i = 0; i < number_boxes; i++)
			{
				if (boxes[i].overlap_index & BOX_LAST)
				{
					boxes[i].overlap_index |= BOX_BLOCKED;
				}
			}
		}

		//^Verified^***************************************************************

		//0x1F2480 objects FIXME unknown type
		int a11 = 0x7E68;
		int s4 = 63;
		dword_A33D0[25] = *(int*) ptr;
		ptr += LevelRelocPtr[45];

		int a2 = LevelRelocPtr[43];
		short a33 = LevelRelocPtr[44];

		SpotCam = (struct SPOTCAM*) ptr;
		dword_3EE4 = LevelRelocPtr[43];//?

		number_spotcams = LevelRelocPtr[44];
		number_cameras = LevelRelocPtr[43];

		GAMEWAD_Read(32360, &objects[0]);

		for (i = 0; i < 63; i++)
		{
			RelocPtr[i] = NULL;
		}

		if (LevelRelocPtr[48] != 0)
		{
			GAMEWAD_ReaderPositionToCurrent();
			GAMEWAD_Read(0x780, &dword_1EF1D0[0]);

			if (LevelRelocPtr[48] > 0)
			{
#if 0
				int s4 = 0;//0xB4184
				//v0 = 0x1F0000
				//s7 = v0 - 0x630;
				for (i = 0; i < LevelRelocPtr[48]; i++)//s4 is i
				{
					unsigned long* v0 = &LevelRelocPtr[s4];
					t3 = *(char*) &v0[49];//0xF
					int s0 = t3 * sizeof(unsigned int);
					s0 += t3;
					s0 *= 4;//0x12C
					char* tmp = &dword_1EF1D0[s0];

					int s3 = *(int*) &tmp[4];
					a0 = s3;
					char* s2 = game_malloc(s3);//@S3/a0

					a0 = *(int*) &tmp[0];
					GAMEWAD_Seek(a0);
					GAMEWAD_Read(s3, s2);

					s3 = *(int*) &tmp[12];
					s2 = game_malloc(s3);
					a0 = *(int*) &tmp[8];
					GAMEWAD_Seek(a0);
					GAMEWAD_Read(s3, s2);//5E414

					//0xB41F4
					char* a00 = s2;
					//RelocateModule(s2); //Probably ai code
					game_free(s3);

					int s4 = 0;
					s4++;

					int* v00 = (int*) tmp[10];//7
					int v11 = LevelRelocPtr[48];//5
					//v00 <<= 2;
					//v00 += s7;

					v00[0] = (int) s2;
				}
#endif

			}

		}//0xB4228

		int testing3 = 0;
		testing3++;
	}
}//0xB4730 is end jalr v0

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