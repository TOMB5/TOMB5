#include "SETUP.H"

#include "3D_OBJ.H"
#include "BOX.H"
#include "CD.H"
#include "CONTROL.H"
#include "CODEWAD.H"
#include "DELTAPAK.H"
#include "DRAW.H"
#include "DRAWPHAS.H"
#include "DOOR.H"
#include "EFFECTS.H"
#include "EFFECT2.H"
#include "FILE.H"
#include "FLMTORCH.H"
#include "GAMEFLOW.H"
#include "GPU.H"
#include "HAIR.H"
#include "HEALTH.H"
#include "ITEMS.H"
#include "LARA.H"
#include "LARAFIRE.H"
#include "LARAMISC.H"
#include "LOAD_LEV.H"
#include "LOT.H"
#include "MALLOC.H"
#include "MATHS.H"
#include "MISC.H"
#include "NEWINV2.H"
#include "OBJECTS.H"
#include "OBJLIGHT.H"
#include "PICKUP.H"
#include "ROOMLOAD.H"
#include "SAVEGAME.H"
#include "SPECIFIC.H"
#include "SPOTCAM.H"
#include "SOUND.H"
#include "SPUSOUND.H"
#include "SWITCH.H"
#include "TOMB4FX.H"
#include "TYPES.H"
#include "TYPEDEFS.H"
#include "SPECTYPES.H"

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#if !DISC_VERSION
#include <LIBSN.H>
#endif
#include <LIBSPU.H>
#include <LIBGTE.H>
#if RELOC
void* setupFunc[] __attribute__((section(".header"))) = 
{ 
	(void*)0x100,//Unknown
	(void*)0x200,//Unknown
	(void*)0x300,//Unknown
	(void*)0x400,//Unknown
	(void*)0x500,//Unknown
	&RelocateLevel
};
#endif

RECT dword_BD7F4[] = { 0x00440240, 0x00390040 };

int LoadSoundEffects(int numSoundEffects, long* pSoundWadLengths, char* pSoundData, int soundWadSize)//(F)
{
#ifndef NO_SOUND

	int i;

	if (numSoundEffects > MAX_NUM_SOUND_EFFECTS || soundWadSize > 524288)
	{
		return 0;
	}

	if (LnSamplesLoaded != 0)
	{
		SPU_FreeSamples();
	}//loc_9C

	LlVABAddr = SpuMalloc(soundWadSize);
	if (LlVABAddr == -1)
	{
		return 0;
	}

	SpuIsTransferCompleted(SPU_TRANSFER_WAIT);
	SpuSetTransferStartAddr(LlVABAddr);
	SpuWrite((unsigned char*)pSoundData, soundWadSize);
	SpuIsTransferCompleted(SPU_TRANSFER_WAIT);

	if (numSoundEffects > 0)
	{
		for (i = 0; i < numSoundEffects; i++)
		{
			LadwSampleAddr[i] = LlVABAddr + pSoundWadLengths[i];
		}
	}//loc_110

	LnSamplesLoaded = numSoundEffects;

	return 1;

#else
	return 0;
#endif
}

void sub_B3A7C(int a0)
{
	struct PSXSPRITESTRUCT* spr = &psxspriteinfo[objects[MISC_SPRITES].mesh_index];

	envmap_data[0] = spr->tpage << 16 | spr->clut;
	envmap_data[1] = (spr->u1 + 32) & 0xFF | (spr->v1 + 32) & 0xFF << 8;
	spr++;

	envmap_data[2] = spr->tpage << 16 | spr->clut;
	envmap_data[3] = (spr->u1 + 32) & 0xFF | (spr->v1 + 32) & 0xFF << 8;
	spr++;

	envmap_data[4] = spr->tpage << 16 | spr->clut;
	envmap_data[5] = (spr->u1 + 32) & 0xFF | (spr->v1 + 32) & 0xFF << 8;
}

/*
 * [FUNCTIONALITY] - RelocateLevel.
 * Relocates all game data pointers from the level file to be loaded back into the engine.
 * Note: The GAMEWAD reader must be initialised to a level file entry.
 * Note: The GAMEWAD reader's position must point to the level file data.
 * Note: This code is part of the SETUP.MOD module.
 */
#if DISC_VERSION
void RelocateLevel()//?(<), B3B50(<) (F)
#else
void RelocateLevel(int nHandle)//?, B3B50(<)
#endif
{
	struct Level* level;
	RECT tex[2];
	char* ptr = NULL;
	char* ptr2 = NULL;
	int size, i, j;
	long* relocationPtr = NULL;
	long gunType;

	InItemControlLoop = 0;

#if DISC_VERSION
	DEL_CDFS_Read((char*)&tsv_buffer[0], sizeof(struct Level));
#else
	FILE_Read((char*)&tsv_buffer[0], sizeof(struct Level), 1, nHandle);
#endif

	level = (struct Level*)&tsv_buffer[0];

#if DEBUG_VERSION
	if (level->objectVersion != PSX_FILE_VERSION)
	{
		printf("Wrong Version Number!!!\n");
		printf("Game Ver: %d  Level Ver: %d\n", OBJECT_VERSION, level->objectVersion);
	}
#endif

	LaraDrawType = level->laraDrawType;
	WeatherType = level->weatherType;
	RoomDrawType = level->roomDrawType;

#if !DISC_VERSION
	PClseek(nHandle, level->offsetSoundPointers, 0);
#endif

	if (level->numSoundEffects != 0)
	{
		GtSFXEnabled = 0;
		ptr = game_malloc(level->numSoundEffects * sizeof(int));

#if DISC_VERSION
		DEL_CDFS_Read(ptr, level->numSoundEffects * sizeof(int));
#else
		FILE_Read(ptr, sizeof(int), level->numSoundEffects, nHandle);
		PClseek(nHandle, level->offsetSoundData, 0);
#endif
		ptr2 = game_malloc(level->soundWadLength);

#if DISC_VERSION
		DEL_CDFS_Read(ptr2, level->soundWadLength);
#else
		FILE_Read(ptr, level->soundWadLength, sizeof(char), nHandle);
#endif
		GtSFXEnabled = LoadSoundEffects(level->numSoundEffects, (long*)ptr, ptr2, level->soundWadLength);//LoadSoundEffects

		game_free(level->numSoundEffects * sizeof(int));
		game_free(level->soundWadLength);

	}//R loc_304, IB loc_36C

#if !DISC_VERSION
	PClseek(nHandle, level->offsetTextiles, 0);
#endif

	ptr = game_malloc(0x40000);///@TODO macro size

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
	tex[0].x = 512;//x position of textile data in VRAM
	tex[0].y = 0;
	tex[0].w = 512;//Width of VRAM texture space
	tex[0].h = 256;//Height of tpage

	//loc_340, loc_3B4
	for (i = 1; i >= 0; i--)///@CHECK
	{
#if DISC_VERSION
		DEL_CDFS_Read(ptr, 0x40000);
#else
		FILE_Read(ptr, 1, 0x40000, nHandle);
#endif
		LOAD_DrawEnable(0);

		LoadImage(&tex[0], (unsigned long*)ptr);

		DrawSync(0);

		LOAD_DrawEnable(1);

		tex[0].y += 256;
	}

	game_free(0x40000);

	ClutStartY = level->clutStartY;

#if !DISC_VERSION
	PClseek(nHandle, level->offsetAnimFrames, 0);
	AnimFilePos = level->offsetAnimFrames;
#else
	AnimFilePos = cdCurrentSector;
#endif

	ptr = game_malloc(level->frameDataLength);
	frames = (short*)ptr;

#if DISC_VERSION
	DEL_CDFS_Read(ptr, level->frameDataLength);
#else
	FILE_Read(ptr, 1, level->frameDataLength, nHandle);
#endif

	AnimFileLen = level->frameDataLength;

#if !DISC_VERSION
	PClseek(nHandle, level->offsetRoomInfo, 0);
#endif

	ptr = game_malloc(level->roomInfoLength);

#if DISC_VERSION
	DEL_CDFS_Read(ptr, level->roomInfoLength);
#else
	FILE_Read(ptr, 1, level->roomInfoLength, nHandle);
#endif

	room = (struct room_info*)ptr;
	ptr += sizeof(struct room_info) * level->numRooms;

	number_rooms = level->numRooms;

	if (level->numRooms > 0)
	{
		//loc_4D4
		for(i = 0; i < number_rooms; i++)
		{
#if UNOPTIMISED//Original
			ptr2 = ptr;
			ptr2 += 4;

			size = (int)room[i].data;
			room[i].data = (short*)ptr;
			ptr += size;

			//loc_4F8:
			for (j = 23; j >= 0; j--)
			{
				((int*)ptr2)[1 + j] += (int)room[i].data;
			}
#else
			size = (int)room[i].data;
			room[i].data = (short*)ptr;
			
			//loc_4F8:
			for (j = 23; j >= 0; j--)
			{
				((int*)ptr)[1 + j] += (int)room[i].data;
			}

			ptr += size;
#endif

			size = (int)room[i].door;
			room[i].door = (short*)ptr;
			ptr += size;

			size = (int)room[i].floor;
			room[i].floor = (struct FLOOR_INFO*)ptr;
			ptr += size;

			size = (int)room[i].light;
			room[i].light = (struct LIGHTINFO*)ptr;
			ptr += size;

			size = (int)room[i].mesh;
			room[i].mesh = (struct MESH_INFO*)ptr;
			ptr += size;
		}
	}//loc_570

	floor_data = (short*)ptr;
	ptr += level->floorDataLength;

	OutsideRoomOffsets = (short*)ptr;
	ptr += 1460;

	OutsideRoomTable = ptr;
	ptr += level->outsideRoomTableLength;

	RoomBBoxes = (struct SVECTOR*)ptr;
	ptr += level->roomBoundingBoxesLength;

	mesh_base = (short*)ptr;
	ptr += level->meshBaseLength;

	meshes = (short**)ptr;
	ptr += level->meshesLength;

	anims = (struct ANIM_STRUCT*)ptr;
	ptr += level->animsLength;

	changes = (struct CHANGE_STRUCT*)ptr;
	ptr += level->changesLength;

	ranges = (struct RANGE_STRUCT*)ptr;
	ptr += level->rangesLength;

	commands = (short*)ptr;
	ptr += level->commandsLength;

	bones = (long*)ptr;
	ptr += level->bonesLength;

	if (level->numBones * 2 > 0)
	{
		for (i = 0; i < level->numBones * 2; i++)
		{
			((int*)meshes)[i] += (int)mesh_base + ((((int)meshes[i] + ((int)meshes[i] >> 31)) >> 1) << 1);
		}
	}
	//loc_674

	if (level->numAnims > 0)
	{
		for (i = 0; i < level->numAnims; i++)
		{
			(int)anims[i].frame_ptr += (int)frames;
		}
	}//loc_6BC

	AnimTextureRanges = (unsigned short*)ptr;
	ptr += level->animTextureRangesLength;

	psxtextinfo = (struct PSXTEXTSTRUCT*)ptr;
	ptr += level->textureInfoLength;

	psxspriteinfo = (struct PSXSPRITESTRUCT*)ptr;
	ptr += level->spriteInfoLength;

	RoomTextInfo = (struct MMTEXTURE*)ptr;
	ptr += level->mmTextureInfoLength;

	sound_effects = (struct OBJECT_VECTOR*)ptr;
	ptr += level->soundEffectInfoLength;

	sample_lut = (short*)ptr;
	ptr += 900;

	sample_infos = (struct SAMPLE_INFO*)ptr;
	ptr += level->sampleInfoLength;

	items = (struct ITEM_INFO*)ptr;
	ptr += 0x9000;

	AIObjects = (struct AIOBJECT*)ptr;
	ptr += sizeof(struct AIOBJECT) * level->numAIObjects;

	boxes = (struct box_info*)ptr;
	ptr += level->boxesLength;

	overlap = (unsigned short*)ptr;
	ptr += level->overlapsLength;

	ground_zone[0][0] = (short*)ptr;
	ptr += level->groundZoneLength;

	ground_zone[1][0] = (short*)ptr;
	ptr += level->groundZone2Length;

	ground_zone[2][0] = (short*)ptr;
	ptr += level->groundZone3Length;

	nAnimTextureRanges = level->numAnimTextureRanges;
	number_sound_effects = level->soundEffectInfoLength / sizeof(struct OBJECT_VECTOR);
	nAnimUVRanges = level->numAnimUVRanges;
	level_items = level->numLevelItems;
	nAIObjects = level->numAIObjects;

	ground_zone[3][0] = (short*)ptr;
	ptr += level->groundZone4Length;

	ground_zone[4][0] = (short*)ptr;
	ptr += level->groundZone5Length;

	ground_zone[0][1] = (short*)ptr;
	ptr += level->groundZoneLength;
	
	ground_zone[1][1] = (short*)ptr;
	ptr += level->groundZone2Length;

	ground_zone[2][1] = (short*)ptr;
	ptr += level->groundZone3Length;

	ground_zone[3][1] = (short*)ptr;
	ptr += level->groundZone4Length;

	ground_zone[4][1] = (short*)ptr;
	ptr += level->groundZone5Length;

	number_boxes = level->numBoxes;

	if (level->numBoxes > 0)
	{
		for (i = level->numBoxes; i != 0; i--)
		{
			if ((boxes[i].overlap_index & BOX_LAST))
			{
				boxes[i].overlap_index |= BOX_BLOCKED;
			}
		}
	}//loc_854

	camera.fixed = (struct OBJECT_VECTOR*)ptr;
	ptr += level->fixedCameraLength;

	SpotCam = (struct SPOTCAM*)ptr;
	NumFixedCameras = level->numFixedCameras;
	number_spotcams = level->numSpotCameras;
	number_cameras = level->numFixedCameras;

#if DISC_VERSION
	DEL_CDFS_Read((char*)&objects, NUMBER_OBJECTS * sizeof(struct object_info) + NUMBER_STATIC_OBJECTS * sizeof(struct static_info) + 480 + 480);
#else
	PClseek(nHandle, level->offsetObjects, 0);
	FILE_Read((char*)&objects, 1, NUMBER_OBJECTS * sizeof(struct object_info) + NUMBER_STATIC_OBJECTS * sizeof(struct static_info) + 480 + 480, nHandle);
	PCclose(nHandle);
#endif

	for (i = 63; i >= 0; i--)
	{
		RelocPtr[i] = NULL;
	}

	if (level->numAiModules != 0)
	{
#if DISC_VERSION
		FRIG_CD_POS_TO_CUR();
		DEL_CDFS_Read((char*)&tsv_buffer[256], 1920);
#else
		nHandle = PCopen("DATA\\CODE.WAD", 0, 0);
		FILE_Read((char*)&tsv_buffer[256], 20, 96, nHandle);
#endif

		if (level->numAiModules > 0)
		{
			//loc_938
			for(i = 0; i < level->numAiModules; i++)
			{
				relocationPtr = (long*)((char*)&tsv_buffer[256] + (level->aiModuleIndices[i] * 20));
				///relocationPtr = (long*)&((char*)&tsv_buffer)[level->aiModuleIndices[i] * 20];
				ptr = game_malloc(relocationPtr[1]);

#if DISC_VERSION
				DEL_CDFS_Seek(relocationPtr[0]);
				DEL_CDFS_Read(ptr, relocationPtr[1]);
#else
				PClseek(nHandle, relocationPtr[0], 0);
				FILE_Read(ptr, 1, relocationPtr[1], nHandle);
#endif
				ptr2 = game_malloc(relocationPtr[3]);

#if DISC_VERSION
				DEL_CDFS_Seek(relocationPtr[2]);
				DEL_CDFS_Read(ptr2, relocationPtr[3]);
#else
				FILE_Read(ptr2, 1, relocationPtr[3], nHandle);
#endif
				RelocateModule((unsigned long)ptr, (unsigned long*)ptr2);

				game_free(relocationPtr[3]);

				RelocPtr[relocationPtr[4]] = (unsigned long*)ptr;
			}
		}
		//loc_9F0
#if !DISC_VERSION
		PCclose(nHandle);
#endif
	}//loc_9F8

	//B4228
	InitialiseFXArray(1);
	InitialiseLOTarray(1);
	InitialiseObjects();
	InitialiseClosedDoors();///sub_7BC4();//InitialiseClosedDoors();
	InitialiseItemArray(256);

	GlobalPulleyFrigItem = -1;

	if (level_items > 0)
	{
		//loc_A3C
		for(i = 0; i < level_items; i++)
		{
			InitialiseItem(i);
		}
	}
	//loc_A5C

	sub_B9DA8();

	if (number_rooms > 0)
	{
		//loc_A84
		for(i = 0; i < number_rooms; i++)
		{
			if (room[i].num_meshes > 0)
			{
				struct FLOOR_INFO* t1;
				struct box_info* v0;

				//loc_A9C
				for (j = room[i].num_meshes; j > 0; j--)
				{
					t1 = &room[i].floor[((room[i].mesh[j].z - room[i].z) >> 10) + ((room[i].mesh[j].x - room[i].x) >> 10) * room[i].x_size];
					v0 = &boxes[t1->box];
					if (!(v0->overlap_index & BOX_BLOCKED))
					{
						if (gfCurrentLevel == LVL5_BASE && i != 0x13 && i != 0x17 && i != 0x10)
						{
							struct static_info* v1 = &static_objects[room[i].mesh[j].static_number];
							//loc_B30
							if ((t1->floor << 8) < ((room[i].mesh[j].y - v1->y_maxc) + 512) && (room[i].mesh[j].y - v1->y_minc) < (t1->floor << 8))
							{
								if (v1->x_maxc != 0 && v1->x_minc != 0 && v1->z_maxc != 0 && v1->z_minc != 0 && !((v1->x_maxc ^ v1->x_minc) & 0x8000) && !((v1->z_maxc ^ v1->z_minc) & 0x8000))
								{
									//loc_BE8
									room[i].floor[((room[i].mesh[j].z - room[i].z) >> 10) + ((room[i].mesh[j].x - room[i].x) >> 10) * room[i].x_size].stopper = 1;
								}
							}//loc_C20
						}//loc_C20
					}//loc_C20
				}
			}//loc_C2C
		}
	}//loc_C3C

	InitialiseResidentCut(gfResidentCut[0], gfResidentCut[1], gfResidentCut[2], gfResidentCut[3]);
	
	GLOBAL_default_sprites_ptr = &psxspriteinfo[objects[DEFAULT_SPRITES].mesh_index];

	sub_B3A7C(0xB);

	GLOBAL_gunflash_meshptr = meshes[objects[GUN_FLASH].mesh_index];

	if (objects[SEARCH_OBJECT1].loaded && objects[SEARCH_OBJECT1_MIP].loaded)
	{
		((int*)meshes[objects[SEARCH_OBJECT1].mesh_index])[1] = ((int*)meshes[objects[SEARCH_OBJECT1_MIP].mesh_index])[0];
	}//loc_CF4


	//a3 = &AnimatingWaterfallsV
	//v1 = 0xA0000
	//a2 = &AnimatingWaterfalls
	//v0 = &objects
	//a1 = &objects[WATERFALL1];
	//s4 = 5;
	//t1 = meshes
	//t0 = psxtextinfo

	//loc_D20
	for (i = 5; i >= 0; i--)
	{
		if (objects[WATERFALL1 + i].loaded)
		{
			short* meshptr;//a0
			meshptr = meshes[objects[WATERFALL1 + i].mesh_index];
			meshptr += 6;//0xC for next itr?
			meshptr += meshptr[5] << 16 >> 17;
			((int*)AnimatingWaterfalls[i])[0] = (int)&psxtextinfo[meshptr[2] << 4];//why << 4? 1<<4=16!
			AnimatingWaterfallsV[i] = ((char*)&psxtextinfo[meshptr[2] << 4])[1];//why << 4? 1<<4=16!
		}//loc_D84
	}

#if 1
	MonitorScreenTI = NULL;
#else
	///@FIXME check 
	//Retail: sw      $zero, 0xA6F5C
	//Beta: sw      $zero, 0xA5534
#endif
	//a0 = &objects

	if (objects[MONITOR_SCREEN].loaded)
	{
		short* meshptr;//v1
		short* meshptr_2;//a1
		short v0;
		short t0;

		//s4 = 0
		//v0 = objects[MONITOR_SCREEN].mesh_index
		//v1 = meshes
		meshptr = meshes[objects[MONITOR_SCREEN].mesh_index];

		meshptr_2 = (short*)meshptr[0];
		//v0 = meshptr_2[5];
		meshptr_2 += 6;
		//v1 = meshptr_2[5] << 16 >> 17
		meshptr_2 += meshptr_2[5] << 16 >> 17;

		v0 = meshptr_2[0];
		t0 = meshptr_2[1];

		meshptr_2 += 2;
		//a3 = 0

		meshptr_2 += meshptr_2[0] << 1;
		meshptr_2 += v0 + 3 >> 2 << 1;

		if (t0 > 0)
		{
			//v1 = 0xA0000
			//v0 = (meshptr_2[0] & 0xFFFF) << 3;
			//a0 = psxtextinfo[(meshptr_2[0] & 0xFFFF)];
			///@TODO can't find a2.....
		}//loc_EA4


	}//loc_EE4

	//sub_68C0();//InitialiseCutseq();

#if RELOC
	if (RelocPtr[MOD_STARS] != NULL)
	{
		((VOIDFUNCVOID*)RelocPtr[MOD_STARS][0])();
	}//loc_DFC, loc_F14
#else
	//Unimplemented
#endif

#if DISC_VERSION && !BETA_VERSION

	if (gfCurrentLevel == LVL5_TITLE && Gameflow->Language - 1 < 2)
	{
		tex[0] = dword_BD7F4[0];
		tex[1] = dword_BD7F4[1];

		ptr = game_malloc(0x2000);

		LOAD_DrawEnable(0);

		if (Gameflow->Language == 2)
		{
			DEL_CDFS_OpenFile(UNKNOWN_50);
		}//loc_EA0
		else if (Gameflow->Language == 1)
		{
			DEL_CDFS_OpenFile(UNKNOWN_49);
		}

		DEL_CDFS_Read(ptr, 7296);

		LoadImage(&tex[0], (unsigned long*)ptr);

		DrawSync(0);

		LOAD_DrawEnable(1);
	}//loc_EDC

#endif

	if (gfCurrentLevel == LVL5_ESCAPE_WITH_THE_IRIS)
	{
		inventry_objects_list[7].yoff = 4;
		inventry_objects_list[7].yrot = -16384;
		inventry_objects_list[7].xrot = 8448;
		inventry_objects_list[7].zrot = 16384;
		inventry_objects_list[7].flags = 10;

		inventry_objects_list[8].yoff = -16384;
		inventry_objects_list[8].xrot = 8448;
		inventry_objects_list[8].zrot = 16384;
		inventry_objects_list[8].flags = 10;
	}
	else
	{
		//loc_F30
		inventry_objects_list[7].yoff = 0;
		inventry_objects_list[7].yrot = 0;
		inventry_objects_list[7].xrot = -16384;
		inventry_objects_list[7].zrot = 0;
		inventry_objects_list[7].flags = 2;

		inventry_objects_list[8].yoff = 0;
		inventry_objects_list[8].xrot = -16384;
		inventry_objects_list[8].zrot = 0;
		inventry_objects_list[8].flags = 2;
	}

	if (gfCurrentLevel == LVL5_TITLE)
	{
		MGSaveGamePtr = game_malloc(8192);
		FromTitle = 1;
	}//loc_F94
}

void InitialiseObjects()//?(<), B96EC(<) sub_5DE0
{
	int i;

	//loc_5E5C
	for (i = MISC_SPRITES; i >= 0; i--)
	{
		objects[i].initialise = NULL;
		objects[i].collision = NULL;
		objects[i].control = NULL;
		objects[i].draw_routine = NULL;
		objects[i].ceiling = NULL;
		objects[i].floor = NULL;
		objects[i].pivot_length = 0;
		objects[i].radius = 10;
		objects[i].shadow_size = 0;
		objects[i].hit_points = -16384;
		objects[i].explodable_meshbits = 0;
		objects[i].draw_routine_extra = 0;
		objects[i].object_mip = 0;
		objects[i].using_drawanimating_item = 1;
		objects[i].water_creature = 0;
		objects[i].intelligent = 0;
		objects[i].save_mesh = 0;
		objects[i].save_anim = 0;
		objects[i].save_flags = 0;
		objects[i].save_hitpoints = 0;
		objects[i].save_position = 0;

		(int)objects[i].frame_base += (int)frames;
	}

	sub_B5328();
	sub_B84F0();
	sub_B7E04();
	InitialiseHair();
	InitialiseCutseq();

	NumRPickups = 0;
	CurrentSequence = 0;

	SequenceResults[0][2][1] = 1;
	SequenceResults[1][0][2] = 2;
	SequenceResults[1][2][0] = 3;
	SequenceResults[2][0][1] = 4;
	SequenceResults[2][1][0] = 5;

	for (i = 0; i < 6; i++)
	{
		SequenceUsed[i] = 0;
	}

	if (gfNumMips != 0)
	{
		for (i = 0; i < gfNumMips; i++)
		{
			objects[((gfMips[i] & 0xF) << 1) | ANIMATING1].object_mip = (gfMips[i] & 0xF0) << 6;
		}
	}//0xB98B8

	if (gfCurrentLevel == LVL5_STREETS_OF_ROME)
	{
		find_a_fucking_item(ANIMATING10);
	}

	if (gfCurrentLevel == LVL5_OLD_MILL)
	{
		find_a_fucking_item(ANIMATING16)->mesh_bits = 0;
	}//B98F0

	if (objects[RAT].loaded)
	{
		Rats = (struct RAT_STRUCT*)game_malloc(sizeof(struct RAT_STRUCT) * 32);
	}//B9914

	if (objects[BAT].loaded)
	{
		Bats = (struct BAT_STRUCT*)game_malloc(sizeof(struct BAT_STRUCT) * 64);
	}//B9938

	if (objects[SPIDER].loaded)
	{
		Spiders = (struct SPIDER_STRUCT*)game_malloc(sizeof(struct SPIDER_STRUCT) * 64);
	}
}//0xB996C

void sub_B5328()
{
	struct object_info* object = &objects[LARA];

	object->shadow_size = 160;
	object->initialise = &InitialiseLaraLoad;
	object->hit_points = 1000;
	object->draw_routine = NULL;

	object->using_drawanimating_item = 0;
	object->save_hitpoints = 1;
	object->save_position = 1;
	object->save_flags = 1;
	object->save_anim = 1;

	//TODO illegal data @ offset 0
	object = &objects[HAIR];

	//t6 = a1 (0x1F0000)
	if (object->loaded)
	{
		object->intelligent = 1;
		object->HitEffect = 0;
		object->HitEffect = 1;
		object->initialise = NULL;//FIXME sub_ 0xBC5C4,0xBC550
								  //TODO assert
								  //TODO
								  //a1 = RelocPtr[5];
								  //v0 = &CreatureCollision
								  //0xB53D8
	}//0xB54A8

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

///Initialise Game?
void sub_B9DA8()//?(<), B9DA8(<)
{
	SeedRandomDraw(0xD371F947);
	SeedRandomControl(0xD371F947);

	wibble = 0;
	torchroom = 255;

	sub_B4A40();
	InitialiseSqrtTable();

	InGameCnt = 0;

	InitialiseAnimatedTextures();
	InitialiseFootPrints();
	InitialiseBinocularGraphics();
	InitialiseTargetGraphics();
	InitialiseFlipMaps();

	if (gfCurrentLevel == LVL5_THIRTEENTH_FLOOR || gfCurrentLevel == LVL5_BASE || gfCurrentLevel == LVL5_GALLOWS_TREE || gfCurrentLevel == LVL5_STREETS_OF_ROME && gfInitialiseGame != 0)
	{
		//B9E50
		InitialiseLaraCarriedItems(0);
	}
	else
	{
		//B9E60
		InitialiseLaraCarriedItems(1);
	}
	//B9E68
	sub_B9974();
	sub_B9B84();

	SeedRandomDraw(0xD371F947);
	SeedRandomControl(0xD371F947);

	return;
}

void sub_B4A40()//(<), B4A40(<)
{
	long rand;
	//a0 = 0x10000
	rand = rand_2;//v0 @ 0x10(sp)

	SeedRandomDraw(0x1D96D);

	//fp = 0
	//s5 = &WaterTable
	//a0 = s5;

}

void InitialiseSqrtTable()//?(<), B4D14(<)
{
	int i;

	for (i = 0; i < 1024; i++)
	{
		OurSqrt[i] = phd_sqrt_asm(i);
	}

	return;
}

void InitialiseAnimatedTextures()//?(<), B4904(<)
{
	int i;
	unsigned short* animTexRange = &AnimTextureRanges[0];
#if 0
	//000B4B50 3C03000A lui     v1, $A
	//v0 = nAnimUVRanges;
	//a1 = AnimTextureRanges;
	if (nAnimUVRanges == 0)
	{
		return;
	}

	//a0 = 0;
	//t4 = RoomTextInfo;
	for (i = 0; i < nAnimUVRanges; i++)
	{
		//v1 = AnimTextureRanges[0];
		animTexRange++;
		//if(AnimTextureRanges[0] > -1)
		{
			//t1 = t4;
			//t3 = AnimatingTexturesV;
			//v0 = i << 1;
			//v0 += i;
			//t0 = v0 << 4;
			while (v1 >= 0)
			{
				//a3 = animTexRange++;
				//a2 = v1 - 1;
				//v0 = v1 << 1;
				//v0 += v1;
				//v0 <<= 1;
				//v0 += t0;
				//a0 = v0 + t3;
				//v1 = *animTexRange++;
				//v0 = v1 << 1;
				//v0 += v1;
				//v0 <<= 4;
				//v1 = t1 + v0;
				//while(a1 >= 0)
				{
					//a1 -= 1;
					//v0 = v1[1]//byte
					//v1 += 16;//sizeof what?
					//v0 = a0[0];
					//a0 += 2;
				}

				//v1 = a2;
				//a1 = a3;
			}
		}
	}

	return;
#endif
}

void InitialiseFootPrints()//?(<), B52FC(<)
{
	int i;

	for (i = 0; i < 32; i++)
	{
		FootPrint[i].Active = 0;
	}

	return;
}

void InitialiseBinocularGraphics()//?(<), B4E28(<)
{
	sizeof(struct object_info);

#if 0
	000B5074 3C040020 lui     a0, $20
		000B5078 3C05000A lui     a1, $A


		binoculars_mesh_ptr = meshes[objects[BINOCULAR_GRAPHICS].mesh_index];//$a0

	if ()//TODO reconstruct struct.

		000B5098 90820008 lbu     v0, $8(a0)
		000B509C 00000000 nop
		000B50A0 10400021 beq     v0, 0, $B5128
		000B50A4 2484000C addiu   a0, $C
		000B50A8 3C075555 li      a3, $55555556
		000B50B0 3C069249 li      a2, $92492493
		000B50B8 00402821 addu    a1, v0, 0
		000B50BC 94830000 lhu     v1, $0(a0)
		000B50C0 00000000 nop
		000B50C4 00031C00 sll     v1, $10
		000B50C8 00031403 sra     v0, v1, $10
		000B50CC 00470018 mult    v0, a3
		000B50D0 00031FC3 sra     v1, $1F
		000B50D4 00001010 mfhi    v0
		000B50D8 00431023 subu    v0, v1
		000B50DC 24420100 addiu   v0, $100
		000B50E0 A4820000 sh      v0, $0(a0)
		000B50E4 24840002 addiu   a0, $2
		000B50E8 84820000 lh      v0, $0(a0)
		000B50EC 00000000 nop
		000B50F0 00021900 sll     v1, v0, $4
		000B50F4 00621823 subu    v1, v0
		000B50F8 00031840 sll     v1, $1
		000B50FC 00660018 mult    v1, a2
		000B5100 24A5FFFF subiu   a1, $1
		000B5104 00001010 mfhi    v0
		000B5108 00431021 addu    v0, v1
		000B510C 000211C3 sra     v0, $7
		000B5110 00031FC3 sra     v1, $1F
		000B5114 00431023 subu    v0, v1
		000B5118 24420078 addiu   v0, $78
		000B511C A4820000 sh      v0, $0(a0)
		000B5120 14A0FFE6 bne     a1, 0, $B50BC
		000B5124 24840006 addiu   a0, $6
		000B5128 03E00008 jr      ra
#endif
}

void InitialiseTargetGraphics()//(<), B4D64(<)
{
	int i;
	int v0;
	int v1;
	struct MESH_STRUCT* mesh;

	target_mesh_ptr = meshes[objects[TARGET_GRAPHICS].mesh_index];
	mesh = (struct MESH_STRUCT*)target_mesh_ptr;

	if (mesh->unk03 == 0)
	{
		return;
	}

	for (i = 0; i < mesh->unk03; i++, mesh++)
	{
		//a1 = mesh->unk03

		//v0 = mesh->unk00;
		//v1 = v0 << 2;//shift shrt.
		//v1 += v0;
		//v1 <<= 4;
		//v0 = v1 * 0x2AAAAAAB;
		//v1 >>= 0x1F;
		//v0 >>= 4;
		//v0 -= v1;
		//v0 += 0x100;
		//mesh->unk00 = v0;

		v1 = (((mesh->unk01 << 4) - mesh->unk01) << 2) >> 0x1F;
		v0 = (((((mesh->unk01 << 4) - mesh->unk01) << 2) * 0x92492493) + (((mesh->unk01 << 4) - mesh->unk01) << 2)) >> 7;
		v0 -= v1;
		v0 += 0x78;
		mesh->unk01 = v0;
	}

	return;
}

void InitialiseFlipMaps()//?(<), B9D30(<)//InitialiseGameFlags
{
	int i;

	for (i = 0; i < 10; i++)
	{
		flipmap[i] = 0;
		flip_stats[i] = 0;
	}

	flip_status = 0;
	flipeffect = 1;

	for (i = 0; i < sizeof(cd_flags); i++)
	{
		cd_flags[i] = 0;
	}

	IsAtmospherePlaying = 0;
	camera.underwater = 0;
}

//InitialiseLaraCarriedItems
void InitialiseLaraCarriedItems(long keep_carried_items)
{
	long i;
	long gun_type;
	struct lara_info lara_backup;

	if (lara.item_number == -1)
	{
		return;
	}

	lara_item->meshswap_meshbits &= 0xFFDF;
	lara_item->data = &lara;
		
	if (keep_carried_items)
	{
		//$B51C0
		memcpy(&lara_backup, &lara, sizeof(struct lara_info));
		memset(&lara, 0, sizeof(struct lara_info));
		memcpy(&lara.pistols_type_carried, &lara_backup.pistols_type_carried, 59);
	}
	else
	{
		memset(&lara, 0, sizeof(struct lara_info));
	}

	lara.item_number = lara.item_number;//?


	lara.air = 0x708;
	lara.hit_direction = -1;
	lara.weapon_item = -1;
	PoisonFlag = 0;
	lara.holster = 0xE;
	lara.RopePtr = -1;
	lara.water_surface_dist = 0x64;
	lara.dpoisoned = 0;
	lara.poisoned = 0;
	lara.location = -1;
	lara.highest_location = -1;
	lara.Unused1 = 1;

	//a0 = 0xA0000;
	//s3= lara_item
	lara_item->hit_points = 0x3E8;

	for (i = 0; i < gfNumPickups; i++)
	{
		DEL_picked_up_object(convert_invobj_to_obj(gfPickups[i]));
	}//$B52AC

	gfNumPickups = 0;
	if (!(gfLevelFlags & 1) && objects[PISTOLS_ITEM].loaded)
	{
		gun_type = 1;
	}
	else
	{
		//$B52D8
		gun_type = 0;
	}
	
	//v0 = &objects
	if ((gfLevelFlags & 0x80) && objects[HK_ITEM].loaded)
	{
		//v1 = lara
		if ((lara.hk_type_carried & 1))
		{
			gun_type = 5;
		}//$B531C
	}//$B531C

	//s1 = lara;
	lara.gun_status = 0;
	lara.last_gun_type = gun_type;
	lara.gun_type = gun_type;
	lara.request_gun_type = gun_type;

	LaraInitialiseMeshes();
	
	//a0 = &objects
	lara.skelebob = 0;

	//objects[PISTOLS_ITEM]

	if (objects[PISTOLS_ITEM].loaded)
	{
		lara.pistols_type_carried = 9;
	}//$B5354

	lara.binoculars = 1;

#if 0
	000B535C 8FA20198 lw      v0, $198(sp)
	000B5360 00000000 nop
	000B5364 1440000B bne     v0, 0, $B5394
	000B5368 00000000 nop
	000B536C 8C8258F0 lw      v0, $58F0(a0)
	000B5370 00000000 nop
	000B5374 00431024 and v0, v1
	000B5378 10400002 beq     v0, 0, $B5384
	000B537C 24020003 addiu   v0, 0, $3
	000B5380 A6220146 sh      v0, $146(s1)		
#endif
	
	lara.num_small_medipack = 3;
	lara.num_large_medipack = 1;

	lara.num_pistols_ammo = -1;
	InitialiseLaraAnims(lara_item);

	//s0 = 0;
	//v1 = 0x78
	//a0 = gfNumTakeaways;
	//v0 = 0xA0000
	DashTimer = 120;

	if (gfNumTakeaways != 0)
	{
		for (i = 0; i < gfNumTakeaways; i++)
		{
			convert_invobj_to_obj(gfTakeaways[i]);
			NailInvItem(gfTakeaways[i]);
		}
	}//$B53F8

	gfNumTakeaways = 0;

	if (gfCurrentLevel < LVL5_BASE)
	{
		weapons[1].damage = 6;
	}
	else
	{
		//$B541C
		weapons[1].damage = 15;
	}

	if (gfCurrentLevel == LVL5_DEEPSEA_DIVE)
	{
		lara.puzzleitems[0] = 10;
	}//$B5450

	if (gfCurrentLevel == LVL5_SUBMARINE)
	{
		lara.pickupitems = 0;
		lara.pickupitemscombo = 0;
		lara.keyitems = 0;
		lara.keyitemscombo = 0;
		lara.puzzleitemscombo = 0;

		for (i = 0; i < 0xB; i++)
		{
			lara.puzzleitems[i] = 0;
		}
	}

	if (gfCurrentLevel == LVL5_SINKING_SUBMARINE)
	{
		lara.puzzleitems[0] = 0;
		lara.pickupitems = 0;
	}//$B54A8

	if (gfCurrentLevel == LVL5_ESCAPE_WITH_THE_IRIS)
	{
		lara.puzzleitems[2] = 0;
		lara.puzzleitems[3] = 0;
		lara.pickupitems &= -2;
	}

	if (gfCurrentLevel == LVL5_RED_ALERT)
	{
		lara.pickupitems &= -3;
	}

	if (gfCurrentLevel - 0xB < 4)
	{
		lara.bottle = 0;
		lara.wetcloth = 0;
	}

	lara.pickupitems &= -9;
}

void sub_B9974()
{
}

void InitialiseCutseq()//?(<), BA194(<) (F)
{
	cutseq_num = 0;
	cutseq_trig = 0;
	GLOBAL_playing_cutseq = 0;
	GLOBAL_cutseq_frame = 0;

	SetFadeClip(0, 1);
}

void sub_B9B84()
{
	struct ITEM_INFO* item;
	struct AIOBJECT* ai_object;//$a2
	int i;
	int j;
	int t0;
	int v0;

	if (level_items > 0)
	{
		//loc_62CC
		for(i = 1; i < level_items; i++)///@CHECK
		{
			if (objects[items[i].object_number].intelligent)
			{
				items[i].meshswap_meshbits &= 0xC1FF;

				if (nAIObjects > 0)
				{
					t0 = 0x10000;
					ai_object = &AIObjects[0];
					//loc_6318
					while ((t0 >> 16) < (nAIObjects >> 16))///@CHECK $t0 maybe opt'd
					{
						v0 = t0;

						if (ABS(ai_object->x - items[i].pos.x_pos) < 512 &&
							ABS(ai_object->z - items[i].pos.z_pos) < 512 &&
							ai_object->room_number == items[i].room_number &&
							ai_object->object_number < AI_PATROL2)
						{
#if 1
							((int*)&items[i])[33] = ((((int*)&items[i])[33] & 0xFFFFC1FF) | ((((1 << (ai_object->object_number - 0x17A)) | ((int*)&items[i])[33] >> 9)) & 0x1F) << 9);
#else
							items[i].meshswap_meshbits &= 0xC1FF;
							items[i].meshswap_meshbits >>= 9;
							items[i].meshswap_meshbits |= 1 << (ai_object->object_number - 0x17A) & 0x1F << 9;
#endif
							items[i].item_flags[3] = ai_object->trigger_flags;

							if (ai_object->object_number != AI_GUARD)
							{
								ai_object->room_number = 255;
							}
						}//loc_63D8

						++ai_object;
						t0 += 0x10000;
					}

					//loc_63B4
					items[i].TOSSPAD = items[i].item_flags[3] | item[i].ai_bits;
				}
			}//loc_63F0
		}//loc_6410
	}//loc_6420
}

void InitialiseResidentCut(unsigned char a0, unsigned char a1, unsigned char a2, unsigned char a3)//?(<), B9EA0(<) (F)
{
	int i;
	int s0;
	int s1;
	int s2;
	char* s3;
	char* s4;
	char* s5;
	char* s6;
	int s7;
	int mallocSize;//$a0
	int nHandle;
	int residentData[4];

	residentData[0] = a0;//0x38(sp)
	residentData[1] = a1;//0x3C(sp)
	residentData[2] = a2;//0x40(sp)
	residentData[3] = a3;//0x44(sp)

	if ((a0 | a1 | a2 | a3))
	{
		lastcamnum = -1;
		GLOBAL_playing_cutseq = 0;
		cutseq_trig = 0;

		//loc_6614
		for (i = 46; i >= 0; i--)
		{
			cutseq_resident_addresses[i].packed_data = NULL;
		}

#if DISC_VERSION
		DEL_CDFS_OpenFile(CUTSEQ);
		DEL_CDFS_Read((char*)&tsv_buffer[0], 2048);
#else
		nHandle = PCopen("\\CUTSEQ.JIZ", 0, 0);
		FILE_Read((char*)&tsv_buffer[0], 1, 2048, nHandle);
#endif
		s3 = ReadResidentData(residentData[0], nHandle);
		s4 = ReadResidentData(residentData[1], nHandle);
		s5 = ReadResidentData(residentData[2], nHandle);
		s6 = ReadResidentData(residentData[3], nHandle);

		s7 = 0;
		s2 = 0;
		s1 = 0;
		s0 = 0;

		if (s3 != NULL)
		{
			s0 = sub_BA148((short*)s3);
		}
		//loc_66C0
		if (s4 != NULL)
		{
			s1 = sub_BA148((short*)s4);
		}
		//loc_66D4
		if (s5 != NULL)
		{
			s2 = sub_BA148((short*)s5);
		}
		//loc_66E8
		if (s6 != NULL)
		{
			s7 = sub_BA148((short*)s6);
		}

		//loc_66FC
		mallocSize = 0;

		if (s0 > 0)
		{
			mallocSize = s0;
		}

		//loc_6708
		if (mallocSize < s1)
		{
			mallocSize = s1;
		}//loc_671C

		if (mallocSize < s2)
		{
			mallocSize = s2;
		}//loc_672C

		if (mallocSize < s7)
		{
			mallocSize = s7;
		}

		//loc_6738
		GLOBAL_resident_depack_buffers = game_malloc(mallocSize);

		if (residentData[0] != 0)
		{
			cutseq_resident_addresses[residentData[0]].packed_data = s3;
		}

		//loc_6764
		if (residentData[1] != 0)
		{
			cutseq_resident_addresses[residentData[1]].packed_data = s4;
		}
		//loc_6788
		if (residentData[2] != 0)
		{
			cutseq_resident_addresses[residentData[2]].packed_data = s5;
		}
		//loc_67A4
		if (residentData[3] != 0)
		{
			cutseq_resident_addresses[residentData[3]].packed_data = s6;
		}
	}//loc_67C8
}

char* ReadResidentData(int residentIndex, int nHandle)//(<), BA0DC(<) (F)
{
	char* ptr;

	if (residentIndex != 0)
	{
#if DISC_VERSION
		DEL_CDFS_Seek(tsv_buffer[residentIndex].xy);
#else
		PClseek(nHandle, tsv_buffer[residentIndex].xy, 0);
#endif
		ptr = game_malloc(tsv_buffer[residentIndex].rgz);

#if DISC_VERSION
		DEL_CDFS_Read(ptr, tsv_buffer[residentIndex].rgz);
#else
		FILE_Read(ptr, sizeof(char), tsv_buffer[residentIndex].rgz, nHandle);
#endif
		return ptr;
	}

	return NULL;
}

long sub_BA148(short* ptr)
{
	int i;//$a1
	long addr = 0;//$a2
	short v1;

	GLOBAL_cutme = (struct NEW_CUTSCENE*)ptr;

	if (ptr[0] > 0)
	{
		//loc_6894
		for(i = ptr[0]; i != 0; i--)
		{
			v1 = ptr[15] + 1;
			ptr += 4;
			addr += (((((v1 + 1) << 2) + v1 + 1) << 2) + v1 + 1) << 2;///@FIXME * sizeof x
		}
	}//locret_68C0

	return addr + 0xA8;
}
