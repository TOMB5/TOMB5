#include "SETUP.H"

#include "3D_OBJ.H"
#include "BOX.H"
#include "CD.H"
#include "CONTROL.H"
#include "DRAW.H"
#include "EFFECTS.H"
#include "FILE.H"
#include "GPU.H"
#include "ITEMS.H"
#include "LOAD_LEV.H"
#include "LOT.H"
#include "MALLOC.H"
#include "ROOMLOAD.H"
#include "SPECIFIC.H"
#include "SPOTCAM.H"
#include "SOUND.H"
#include "SPUSOUND.H"

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <LIBSPU.H>
#include <LIBGTE.H>

struct object_container objects_raw;
struct object_info* objects = &objects_raw.m_objects[0];
struct static_info* static_objects = &objects_raw.m_static_objects[0];
extern char* SkinVertNums = &objects_raw.m_SkinVertNums[0];
extern char* ScratchVertNums = &objects_raw.m_ScratchVertNums[0];

/*
 * [FUNCTIONALITY] - RelocateLevel.
 * Relocates all game data pointers from the level file to be loaded back into the engine.
 * Note: The GAMEWAD reader must be initialised to a level file entry.
 * Note: The GAMEWAD reader's position must point to the level file data.
 * Note: This code is part of the SETUP.MOD module.
 */
#if INTERNAL
void RelocateLevel(int nHandle)//?, B3B50(<)
#else
void RelocateLevel()
#endif
{
	struct Level* level;
	RECT tex;
	char* ptr = NULL;
	char* ptr2 = NULL;
	unsigned int size, i, j;
	long* relocationPtr = NULL;

#if INTERNAL
	FILE_Read((char*) &tsv_buffer[0], sizeof(struct Level), 1, nHandle);
#else
	CD_Read((char*) &tsv_buffer[0], sizeof(struct Level));
#endif
	//Not done in original
	level = (struct Level*)&tsv_buffer[0];
	InItemControlLoop = 0;

#if INTERNAL
	if (*(int*) &level != PSX_FILE_VERSION)
	{
		printf("Wrong Version Number!!!\n");
		printf("Game Ver: %d  Level Ver: %d\n", OBJECT_VERSION, level->objectVersion);
	}
#endif

	LaraDrawType = level->laraDrawType;
	WeatherType = level->weatherType;
	RoomDrawType = level->roomDrawType;

#if INTERNAL
	PClseek(nHandle, level->offsetSoundPointers, 0);
#endif

	if (level->numSoundEffects != 0)
	{
		GtSFXEnabled = 0;
		ptr2 = ptr = game_malloc(level->numSoundEffects * sizeof(long));

#if INTERNAL
		FILE_Read(ptr, sizeof(long), level->numSoundEffects, nHandle);
		PClseek(nHandle, level->offsetSoundData, 0);
#else
		CD_Read(ptr, level->numSoundEffects * sizeof(long));
#endif

		ptr = game_malloc(level->soundWadLength);

#if INTERNAL
		FILE_Read(ptr, level->soundWadLength, 1, nHandle);
#else
		CD_Read(ptr, level->soundWadLength);
#endif
		GtSFXEnabled = LoadSoundEffects(level->numSoundEffects, (long*)ptr2, ptr, level->soundWadLength);

		game_free(level->numSoundEffects * sizeof(long));
		game_free(level->soundWadLength);
	}

#if INTERNAL
	PClseek(nHandle, level->offsetTextiles, 0);
#endif

	ptr = game_malloc(0x40000);

	/*   PSX VRAM   (H)
	*  --------------------- 1024px
	*  | TL | TR | TPAGE1 |  |
	*  ---------------------  v
	*  | BL | BR | TPAGE2 |
	*  ---------------------
	*(W)1024px-->
	*
	* Loading texture pages+cluts into VRAM (TPAGE1, TPAGE2)
	* 
	*/

	//Setup rect
	//x position of textile data in VRAM
	tex.x = 512;//Screen width
	tex.y = 0;

	//Width of VRAM texture space
	tex.w = 512;

	//Height of tpage
	tex.h = 256;

	for (i = 0; i < 2; i++)
	{
#if INTERNAL
		FILE_Read(ptr, 1, 0x40000, nHandle);
#else
		CD_Read(ptr, 0x40000);
#endif
		LOAD_DrawEnable(0);

		LoadImage(&tex, ptr);

		DrawSync(0);

		LOAD_DrawEnable(1);

		tex.y += 256;
	}

	//000B3F50, 000B3ED4
	game_free(0x40000);

	ClutStartY = level->clutStartY;
	
#if INTERNAL
	PClseek(nHandle, level->offsetAnimFrames, 0);
#else
	//lw      a2, $5620(v0)
	//sw      a2, $60BC(v0)
#endif

	AnimFilePos = level->offsetAnimFrames;
	ptr = game_malloc(level->frameDataLength);
	frames = (short*) ptr;
	
#if INTERNAL
	FILE_Read(ptr, 1, level->frameDataLength, nHandle);
#else
	CD_Read(ptr, level->frameDataLength);
#endif

	AnimFileLen = level->frameDataLength;

#if INTERNAL
	PClseek(nHandle, level->offsetRoomInfo, 0);
#endif

	ptr = game_malloc(level->roomInfoLength);

#if INTERNAL
	FILE_Read(ptr, 1, level->roomInfoLength, nHandle);
#else
	CD_Read(ptr, level->roomInfoLength);
#endif

	room = (struct room_info*)ptr;
	ptr += sizeof(struct room_info) * level->numRooms;

	number_rooms = level->numRooms;

	if (level->numRooms > 0)
	{
		for (i = 0; i < number_rooms; i++)
		{
			size = *(unsigned int*) &room[i].data;
			room[i].data = (short*) ptr;

			for (j = 0; j < 24; j++)
			{
				*(int*) &ptr[4+(j * 4)] += (*(int*) &room[i].data);
			}///@CRITICAL the last relocated pointer seemingly points to invalid memory?!?!?!??

			ptr += size;

			size = *(unsigned int*) &room[i].door;
			room[i].door = (short*) ptr;
			ptr += size;

			size = *(unsigned int*) &room[i].floor;
			room[i].floor = (struct FLOOR_INFO*) ptr;
			ptr += size;

			size = *(unsigned int*) &room[i].light;
			room[i].light = (struct LIGHTINFO*) ptr;
			ptr += size;

			size = *(unsigned int*) &room[i].mesh;
			room[i].mesh = (struct MESH_INFO*) ptr;
			ptr += size;
		}

	}//B40C0, B401C

	floor_data = (short*)ptr;
	ptr += level->floorDataLength;

	OutsideRoomOffsets = (short*)ptr;
	ptr += 1460;

	OutsideRoomTable = ptr;
	ptr += level->outsideRoomTableLength;
	
	RoomBBoxes = (SVECTOR*)ptr;
	ptr += level->roomBoundingBoxesLength;

	mesh_base = (short*) ptr;
	ptr += level->meshBaseLength;

	meshes = (short**) ptr;
	ptr += level->meshesLength;

	anims = (struct ANIM_STRUCT*)ptr;
	ptr += level->animsLength;

	changes = (struct CHANGE_STRUCT*)ptr;
	ptr += level->changesLength;

	ranges = (struct RANGE_STRUCT*)ptr;
	ptr += level->rangesLength;

	commands = (short*) ptr;
	ptr += level->commandsLength;

	bones = (long*) ptr;
	ptr += level->bonesLength;
	
	if (level->numBones * 2)
	{
		for (i = 0; i < level->numBones * 2; i++)
		{
			*(int*) &meshes[i] += *(int*)&mesh_base;//Original game does add *(int*) &meshes[i] >> 0x1F too
		}

	}//B41C4, ?

	//000B41C4
	if (level->numAnims > 0)
	{
		for (i = 0; i < level->numAnims; i++)
		{
			*(int*) &anims[i].frame_ptr += (int) frames;
		}
	}

	AnimTextureRanges = (unsigned short*) ptr;
	ptr += level->animTextureRangesLength;

	psxtextinfo = (struct PSXTEXTSTRUCT*) ptr;
	ptr += level->textureInfoLength;

	psxspriteinfo = (struct PSXSPRITESTRUCT*)ptr;
	ptr += level->spriteInfoLength;

	//maybe mip maps
	RoomTextInfo = (struct MMTEXTURE*)ptr;
	ptr += level->mmTextureInfoLength;

	sound_effects = (struct OBJECT_VECTOR*)ptr;
	ptr += level->soundEffectInfoLength;

	sample_lut = (short*) ptr;
	ptr += 900;//num sound map indices

	sample_infos = (struct SAMPLE_INFO*)ptr;
	ptr += level->sampleInfoLength;

	items = (struct ITEM_INFO*)ptr;
	ptr += 0x9000;

	AIObjects = (struct AIOBJECT*)ptr;
	ptr += sizeof(struct AIOBJECT) * level->numAIObjects;

	boxes = (struct box_info*)ptr;
	ptr += level->boxesLength;
	
	overlap = (unsigned short*) ptr;
	ptr += level->overlapsLength;

	ground_zone[0][0] = (short*) ptr;
	ptr += level->groundZoneLength;

	ground_zone[1][0] = (short*) ptr;
	ptr += level->groundZone2Length;

	ground_zone[2][0] = (short*) ptr;
	ptr += level->groundZone3Length;

	ground_zone[3][0] = (short*) ptr;
	ptr += level->groundZone4Length;

	ground_zone[4][0] = (short*) ptr;
	ptr += level->groundZone5Length;

	ground_zone[0][1] = (short*) ptr;
	ptr += level->groundZoneLength;

	ground_zone[1][1] = (short*) ptr;
	ptr += level->groundZone2Length;

	ground_zone[2][1] = (short*) ptr;
	ptr += level->groundZone3Length;

	ground_zone[3][1] = (short*) ptr;
	ptr += level->groundZone4Length;

	ground_zone[4][1] = (short*) ptr;
	ptr += level->groundZone5Length;

	nAnimTextureRanges = level->numAnimTextureRanges;
	number_sound_effects = level->soundEffectInfoLength / sizeof(struct OBJECT_VECTOR);
	nAnimUVRanges = level->numAnimUVRanges;
	level_items = level->numLevelItems;
	nAIObjects = level->numAIObjects;

	number_boxes = level->numBoxes;
	if (level->numBoxes > 0)
	{
		for (i = 0; i < number_boxes; i++)
		{
			if (boxes[i].overlap_index & BOX_LAST)
			{
				boxes[i].overlap_index |= BOX_BLOCKED;
			}
		}
	}//000B43A4, 000B42F8

	camera.fixed = (struct OBJECT_VECTOR*)ptr;
	ptr += level->frameDataLength;

	SpotCam = (struct SPOTCAM*) ptr;
	NumFixedCameras = level->numFixedCameras;
	number_cameras = level->numFixedCameras;
	number_spotcams = level->numSpotCameras;

#if INTERNAL
	PClseek(nHandle, level->offsetObjects, 0);
	FILE_Read((char*) &objects_raw, 1, sizeof(objects_raw), nHandle);
	PCclose(nHandle);
#else
	CD_Read((char*) &objects_raw, sizeof(objects_raw));
#endif
	
	for (i = 0; i < 64; i++)
	{
		RelocPtr[i] = NULL;
	}

	////^VERIFIED
	//000B4430, 000B4364
	if (level->numAiModuleRelocations != 0)
	{
#if INTERNAL
		nHandle = PCopen("DATA\\CODE.WAD", 0, 0);
		FILE_Read((char*) &tsv_buffer[256], 20, 96, nHandle);
#else
		CD_ReaderPositionToCurrent();
		CD_Read((char*)&tsv_buffer[256], 1920);
#endif

		//Temporary, array size is unknown
		assert(level->numAiModuleRelocations < 6);
		if (level->numAiModuleRelocations != 0)
		{
			for (i = 0; i < level->numAiModuleRelocations; i++)
			{
				relocationPtr = (long*) ((char*) &tsv_buffer[256] + (level->aiModuleIndices[i] * 20));
				ptr = game_malloc(relocationPtr[1]);

#if INTERNAL
				PClseek(nHandle, relocationPtr[0], 0);
				FILE_Read(ptr, 1, relocationPtr[1]), nHandle);
#else
				CD_Seek(relocationPtr[0]);
				CD_Read(ptr, relocationPtr[1]);
#endif
				ptr2 = game_malloc(relocationPtr[3]);

#if INTERNAL
				PClseek(nHandle, relocationPtr[2], 0);
				FILE_Read(ptr, 1, relocationPtr[3], nHandle);
#else
				CD_Seek(relocationPtr[2]);
				CD_Read(ptr2, relocationPtr[3]);
#endif
				RelocateModule((unsigned long) ptr, (unsigned long*) ptr2);

				game_free(relocationPtr[3]);

				RelocPtr[relocationPtr[4]] = (unsigned long*) ptr;
			}
		}

#if INTERNAL
		PCclose(nHandle);
#endif
	}//B4548

	InitialiseFXArray(1);
	InitialiseLOTarray(1);

	//000B4558, 000B4448


}//0xB4730 is end jalr v0

long LoadSoundEffects(int numSounds, long* pSoundWadLengths, char* pSoundData, long soundWadSize)
{
	int i;

	//We have limited the amount of Sound Effects to 255 and the sound wad size.
	//Do not load anything which exceeds our memory budget.
	if (numSounds > MAX_NUM_SOUND_EFFECTS || soundWadSize > 524287)
	{
		return 0;
	}
	
	//Sound samples are loaded (likely from a previously loaded level).
	//Free them.
	if (LnSamplesLoaded != 0)
	{
		SPU_FreeSamples();
	}

	LlVABAddr = SpuMalloc(soundWadSize);
	if(LlVABAddr == -1)
	{
		return 0;
	}

	SpuIsTransferCompleted(SPU_TRANSFER_WAIT);
	SpuSetTransferStartAddr(LlVABAddr);
	SpuWrite(pSoundData, soundWadSize);
	SpuIsTransferCompleted(SPU_TRANSFER_WAIT);

	if (numSounds > 0)
	{
		for (i = 0; i < numSounds; i++)
		{
			LadwSampleAddr[i] = LlVABAddr + pSoundWadLengths[i];
		}
	}

	LnSamplesLoaded = numSounds;

	return 1;
}

//?
//Relocate initial object frame ptrs, see ResetCutanimate()
void sub_B96EC(int unk)
{
	char* a0 = (char*)&objects[0];
	int s0 = 0x02000000;
	short t7 = 10;
	int t6 = -16384;
	int t4 = 0xFEFFFFFF;
	int a1 = 459;//max?
	int t3 = 0xFFFDFFFF;
	int t2 = 0xDFFFFFFF;
	int t1 = 0xFFBFFFFF;
	int t0 = 0xFFDFFFFF;
	int a3 = 0xFFEFFFFF;
	int a2 = 0xFFF70000;
	short* t5 = frames;
	int v0, v1, i;
	int* v11;
	a2 |= 0xFFFF;

	///@TODO sizeof object = 64;
	//@TODO count of objects = 459
	for (i = 0; i < a1; i++)
	{
		v0 = *(int*) &a0[48];//0x00010000
		v1 = *(int*) &a0[8];//0
		*(int*) &a0[12] = 0;
		*(int*) &a0[32] = 0;
		*(int*) &a0[16] = 0;
		*(int*) &a0[28] = 0;
		*(int*) &a0[24] = 0;
		*(int*) &a0[20] = 0;
		*(short*) &a0[42] = 0;
		*(short*) &a0[44] = t7;
		*(short*) &a0[46] = 0;
		*(short*) &a0[40] = t6 & 0xFFFF;//0xc000
		*(int*) &a0[56] = 0;
		*(int*) &a0[52] = 0;
		*(short*) &a0[36] = 0;

		v0 |= s0;
		v0 &= t4;
		v0 &= t3;
		v0 &= t2;
		v0 &= t1;
		v0 &= t0;
		v0 &= a3;
		v0 &= a2;//0x02010000

		v11 = ((int*) t5) + v1;

		*(int*) &a0[48] = v0;
		*(int**) &a0[8] = v11;//check

		a0 += 0x40;
	}

	//sub_B5328();

	//sub_B84F0();

	//sub_B7E04();

	//InitialiseHair() //3AC70, 3B170

	//sub_BA81C

	//0xB97FC

}//0xB996C

void sub_B5328()
{

}

void sub_B84F0()
{

}

void sub_B7E04()
{

}