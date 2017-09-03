#include "SETUP.H"

#include "3D_OBJ.H"
#include "BOX.H"
#include "CD.H"
#include "CONTROL.H"
#include "DRAW.H"
#include "DOOR.H"
#include "EFFECTS.H"
#include "FILE.H"
#include "GPU.H"
#include "HAIR.H"
#include "ITEMS.H"
#include "LARAMISC.H"
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
void RelocateLevel(FILE* nHandle)//?, B3B50(<)
#else
void RelocateLevel()
#endif
{
	struct Level* level;
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
	if (level->objectVersion != PSX_FILE_VERSION)
	{
		printf("Wrong Version Number!!!\n");
		printf("Game Ver: %d  Level Ver: %d\n", OBJECT_VERSION, level->objectVersion);
	}
#endif

	LaraDrawType = level->laraDrawType;
	WeatherType = level->weatherType;
	RoomDrawType = level->roomDrawType;

#if INTERNAL
	fseek(nHandle, level->offsetSoundPointers, 0);
#endif

	if (level->numSoundEffects != 0)
	{
		GtSFXEnabled = 0;
		ptr2 = ptr = game_malloc(level->numSoundEffects * sizeof(long));

#if INTERNAL
		FILE_Read(ptr, sizeof(long), level->numSoundEffects, nHandle);
		fseek(nHandle, level->offsetSoundData, 0);
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
	fseek(nHandle, level->offsetTextiles, 0);
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

	//looks like loads each textile (0x4000); in size

	//Setup rect
	//x position of textile data in VRAM
	//tex.x = 512;//Screen width
	//tex.y = 0;

	//Width of VRAM texture space
	//tex.w = 512;

	//Height of tpage
	//tex.h = 256;

	for (i = 0; i < 2; i++)
	{
#if INTERNAL
		FILE_Read(ptr, 1, 0x40000, nHandle);
#else
		CD_Read(ptr, 0x40000);
#endif
		LOAD_DrawEnable(0);

		//LoadImage(&tex, ptr);

		//DrawSync(0);

		LOAD_DrawEnable(1);

	//	rect.y += 256;
	}

	//000B3F50, 000B3ED4
	game_free(0x40000);

	ClutStartY = level->clutStartY;
	
#if INTERNAL
	fseek(nHandle, level->offsetAnimFrames, 0);
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
	fseek(nHandle, level->offsetRoomInfo, 0);
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
	}

	//000B41C4
	if (level->numAnims > 0)
	{
		for (i = 0; i < level->numAnims; i++)
		{
			*(int*) &anims[i].frame_ptr += *(int*)&frames;
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
	fseek(nHandle, level->offsetObjects, SEEK_SET);
	FILE_Read((char*) &objects_raw, 1, sizeof(objects_raw), nHandle);
	fclose(nHandle);
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
		nHandle = fopen("DATA\\CODE.WAD", "rb");
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
				fseek(nHandle, relocationPtr[0], 0);
				FILE_Read(ptr, 1, relocationPtr[1], nHandle);
#else
				CD_Seek(relocationPtr[0]);
				CD_Read(ptr, relocationPtr[1]);
#endif
				ptr2 = game_malloc(relocationPtr[3]);

#if INTERNAL
				fseek(nHandle, relocationPtr[2], 0);
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
		fclose(nHandle);
#endif
	}//B4548

	InitialiseFXArray(1);
	InitialiseLOTarray(1);
	//000B4558, 000B4448
	InitialiseObjects();//TODO
	InitialiseClosedDoors();
	InitialiseItemArray(256);

	GlobalPulleyFrigItem = -1;

	if (level_items > 0)
	{
		for (i = 0; i < level_items; i++)
		{
			InitialiseItem(i);
		}
	}
	
	//B45AC
	sub_B9DA8();

#if 0
	if (number_rooms > 0)
	{
		//t5 = room
		//t3 = room.num_meshes
		//t6 = room.mesh
		
		if (room.mesh > 0)//num meshes?
		{
			//s2 = boxes
			//a3 = room.mesh[0].x;
			//t0 = room.x
			//v1 = room.x_size;
			//v0 = ((a3 - t0) / 1024) * room.x_size;
			//a1 = room.mesh[0].z;
			//a2 =room.z
			//a0 = room.floor
			//t8 = room.x_size
			//v1 = (a1 - a2) / 1024;
			//v1 += v0;
			//v1 <<= 3;
			//t1 = a0 + v1;
			//v0 = $2(t1)
			//s0 = a1;
			//v0 >>= 1;//box index shift?
			//v0 &= 0x3FF8;
			//v0 += s2;//box index
			//v1 = $6(v0);
			
			//v1 &= 0x4000
			if (!(v1 & 0x4000))
			{
				//s1 = a0;
				//v1 = gfCurrentLevel;
				//v0 = 4;

				if (s4 == 0x13 || s4 == 0x17 || s4 = 0x10 && gfCurrentLevel == 4)
				{
					//0xB4448
				}
				else
				{
					//0xB4358
				}

			}//b4448


			//end loop is 0xB444C
		}

	}//B478C
#endif

	//sub_B9EA0(gfResidentCut[0], gfResidentCut[1], gfResidentCut[2], gfResidentCut[3]);

	//sub_B3A7C(0xB)

	GLOBAL_default_sprites_ptr = &psxspriteinfo[objects[DEFAULT_SPRITES].mesh_index];
	GLOBAL_gunflash_meshptr = meshes[objects[GUN_FLASH].mesh_index];

	if (objects[SEARCH_OBJECT1].bite_offset & 1)
	{
	}//0xB451C

}//0xB4730 is end jalr v0

long LoadSoundEffects(int numSounds, long* pSoundWadLengths, char* pSoundData, long soundWadSize)
{
#if 1
	int i;

	//We have limited the amount of Sound Effects to 255 and the sound wad size.
	//Do not load anything which exceeds our memory budget.
	//if (numSounds > MAX_NUM_SOUND_EFFECTS || soundWadSize > 524287)
	{
		//return 0;
	}
	
	//Sound samples are loaded (likely from a previously loaded level).
	//Free them.
	if (LnSamplesLoaded != 0)
	{
		//SPU_FreeSamples();
	}

	//LlVABAddr = SpuMalloc(soundWadSize);
	if(LlVABAddr == -1)
	{
		//return 0;
	}

	//SpuIsTransferCompleted(SPU_TRANSFER_WAIT);
	//SpuSetTransferStartAddr(LlVABAddr);
	//SpuWrite(pSoundData, soundWadSize);
	//SpuIsTransferCompleted(SPU_TRANSFER_WAIT);

	if (numSounds > 0)
	{
		for (i = 0; i < numSounds; i++)
		{
			LadwSampleAddr[i] = LlVABAddr + pSoundWadLengths[i];
		}
	}

	LnSamplesLoaded = numSounds;
#endif
	return 0;
}

//?
//Relocate initial object frame ptrs, see ResetCutanimate()
void InitialiseObjects()//?(<), B96EC(<)
{
	int i;

	struct object_info* dbg;

	for (i = 0; i < NUMBER_OBJECTS; i++)
	{
		objects[i].initialise = 0;
		objects[i].collision = 0;
		objects[i].control = 0;
		objects[i].draw_routine = 0;
		objects[i].ceiling = 0;
		objects[i].floor = 0;
		objects[i].pivot_length = 0;
		objects[i].radius = 10;
		objects[i].shadow_size = 0;
		objects[i].hit_points = -16384;
		objects[i].explodable_meshbits = 0;
		objects[i].draw_routine_extra = 0;
		objects[i].object_mip = 0;

		//TODO: Properly toggle bitfields.
		*(int*)&objects[i].bite_offset |= 0x02000000;
		*(int*)&objects[i].bite_offset &= 0xFEFFFFFF;
		*(int*)&objects[i].bite_offset &= 0xFFFDFFFF;
		*(int*)&objects[i].bite_offset &= 0xDFFFFFFF;
		*(int*)&objects[i].bite_offset &= 0xFFBFFFFF;
		*(int*)&objects[i].bite_offset &= 0xFFDFFFFF;
		*(int*)&objects[i].bite_offset &= 0xFFEFFFFF;
		*(int*)&objects[i].bite_offset &= 0xFFF70000;

		*(int*)&objects[i].frame_base += (int) frames;
		dbg = &objects[i];
	}

	sub_B5328();
	sub_B84F0();
	sub_B7E04();
	InitialiseHair();
	//sub_BA81C();


#if 0
		
#endif

}//0xB996C

void sub_B5328()
{
	struct object_info* object = &objects_raw.m_objects[LARA];

	object->shadow_size = 160;
	object->initialise = &InitialiseLaraLoad;
	object->hit_points = 1000;
	object->draw_routine = NULL;
	*(int*) &object->bite_offset &= 0xFDFFFFFF;
	*(int*) &object->bite_offset |= 0x00100000;
	*(int*) &object->bite_offset |= 0x80000;
	*(int*) &object->bite_offset |= 0x00200000;
	*(int*) &object->bite_offset |= 0x00400000;

	//t0 += 0x7C0
	object = &objects_raw.m_objects[HAIR];

	if (*(int*) &object->bite_offset & 0x10000)
	{
		//? Illegal
		//a3 = 0xFFEFFFFF;
		//lui a0, 0xF3FF
		//lhu v0, 0x866(a3);//!
		//object->anim_index = v0;

		//TODO
	}

	//TODO
}
void sub_B84F0()
{

}

void sub_B7E04()
{

}

void InitialiseClosedDoors()//?(<), BB498(<)
{
	int i;

	for (i = 0; i < 32; i++)
	{
		ClosedDoors[i] = 0;
	}

	return;
}

void sub_B9DA8()
{

}