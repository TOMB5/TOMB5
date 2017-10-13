#include "SETUP.H"

#include "3D_OBJ.H"
#include "BOX.H"
#include "CD.H"
#include "CONTROL.H"
#include "DELTAPAK.H"
#include "DRAW.H"
#include "DOOR.H"
#include "EFFECTS.H"
#include "EFFECT2.H"
#include "FILE.H"
#include "FLMTORCH.H"
#include "GAMEFLOW.H"
#include "GPU.H"
#include "HAIR.H"
#include "ITEMS.H"
#include "LARA.H"
#include "LARAMISC.H"
#include "LOAD_LEV.H"
#include "LOT.H"
#include "MALLOC.H"
#include "NEWINV2.H"
#include "OBJLIGHT.H"
#include "PHD_MATH.H"
#include "PICKUP.H"
#include "ROOMLOAD.H"
#include "SAVEGAME.H"
#include "SPECIFIC.H"
#include "SPOTCAM.H"
#include "SOUND.H"
#include "SPUSOUND.H"
#include "SWITCH.H"
#include "TOMB4FX.H"
#include "SPECTYPES.H"

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <string>

object_container objects_raw;
object_info* objects = &objects_raw.m_objects[0];
static_info* static_objects = &objects_raw.m_static_objects[0];
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
	Level* level;
	char* ptr = NULL;
	char* ptr2 = NULL;
	unsigned int size, i, j;
	long* relocationPtr = NULL;

#if INTERNAL
	FILE_Read((char*) &tsv_buffer[0], sizeof(Level), 1, nHandle);
#else
	CD_Read((char*) &tsv_buffer[0], sizeof(Level));
#endif
	//Not done in original
	level = (Level*)&tsv_buffer[0];
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
		GtSFXEnabled = LoadSoundEffects(level->numSoundEffects, (long*) ptr2, ptr, level->soundWadLength);

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
	//cdCurrentSector = AnimFilePos;//?
#endif

	AnimFilePos = level->offsetAnimFrames;//Only internal?
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

	room = (room_info*)ptr;
	ptr += sizeof(room_info) * level->numRooms;

	number_rooms = level->numRooms;

	if (level->numRooms > 0)
	{
		for (i = 0; i < number_rooms; i++)
		{
			size = *(unsigned int*) &room[i].data;
			room[i].data = (short*) ptr;

			for (j = 0; j < 24; j++)
			{
				*(int*) &ptr[4 + (j * 4)] += (*(int*) &room[i].data);
			}///@CRITICAL the last relocated pointer seemingly points to invalid memory?!?!?!??

			ptr += size;

			size = *(unsigned int*) &room[i].door;
			room[i].door = (short*) ptr;
			ptr += size;

			size = *(unsigned int*) &room[i].floor;
			room[i].floor = (FLOOR_INFO*) ptr;
			ptr += size;

			size = *(unsigned int*) &room[i].light;
			room[i].light = (LIGHTINFO*) ptr;
			ptr += size;

			size = *(unsigned int*) &room[i].mesh;
			room[i].mesh = (MESH_INFO*) ptr;
			ptr += size;
		}

	}//B40C0, B401C

	floor_data = (short*) ptr;
	ptr += level->floorDataLength;

	OutsideRoomOffsets = (short*) ptr;
	ptr += 1460;

	OutsideRoomTable = ptr;
	ptr += level->outsideRoomTableLength;

	RoomBBoxes = (SVECTOR*) ptr;
	ptr += level->roomBoundingBoxesLength;

	mesh_base = (short*) ptr;
	ptr += level->meshBaseLength;

	meshes = (short**) ptr;
	ptr += level->meshesLength;

	anims = (ANIM_STRUCT*)ptr;
	ptr += level->animsLength;

	changes = (CHANGE_STRUCT*)ptr;
	ptr += level->changesLength;

	ranges = (RANGE_STRUCT*)ptr;
	ptr += level->rangesLength;

	commands = (short*) ptr;
	ptr += level->commandsLength;

	bones = (long*) ptr;
	ptr += level->bonesLength;

	if (level->numBones * 2)
	{
		for (i = 0; i < level->numBones * 2; i++)
		{
			*(int*) &meshes[i] += *(int*) &mesh_base;//Original game does add *(int*) &meshes[i] >> 0x1F too
		}
	}

	//000B41C4
	if (level->numAnims > 0)
	{
		for (i = 0; i < level->numAnims; i++)
		{
			*(int*) &anims[i].frame_ptr += *(int*) &frames;
		}
	}

	AnimTextureRanges = (unsigned short*) ptr;
	ptr += level->animTextureRangesLength;

	psxtextinfo = (PSXTEXTSTRUCT*) ptr;
	ptr += level->textureInfoLength;

	psxspriteinfo = (PSXSPRITESTRUCT*)ptr;
	ptr += level->spriteInfoLength;

	//maybe mip maps
	RoomTextInfo = (MMTEXTURE*)ptr;
	ptr += level->mmTextureInfoLength;

	sound_effects = (OBJECT_VECTOR*)ptr;
	ptr += level->soundEffectInfoLength;

	sample_lut = (short*) ptr;
	ptr += 900;//num sound map indices

	sample_infos = (SAMPLE_INFO*)ptr;
	ptr += level->sampleInfoLength;

	items = (ITEM_INFO*)ptr;
	ptr += 0x9000;

	AIObjects = (AIOBJECT*)ptr;
	ptr += sizeof(AIOBJECT) * level->numAIObjects;

	boxes = (box_info*)ptr;
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
	number_sound_effects = level->soundEffectInfoLength / sizeof(OBJECT_VECTOR);
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

	camera.fixed = (OBJECT_VECTOR*)ptr;
	ptr += level->frameDataLength;

	SpotCam = (SPOTCAM*) ptr;
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
		CD_Read((char*) &tsv_buffer[256], 1920);
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
	InitialiseObjects();//TODO: 4 more unknown subs
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

	InitialiseResidentCut(gfResidentCut[0], gfResidentCut[1], gfResidentCut[2], gfResidentCut[3]);

	//sub_B3A7C(0xB)

	GLOBAL_default_sprites_ptr = &psxspriteinfo[objects[DEFAULT_SPRITES].mesh_index];
	GLOBAL_gunflash_meshptr = meshes[objects[GUN_FLASH].mesh_index];

	//s0 = &objects[0];
	if (objects[SEARCH_OBJECT1].bite_offset & 0x10000 && objects[SEARCH_OBJECT1_MIP].bite_offset & 0x10000)
	{
		//0x2900 is base
		//v0 = objects[SEARCH_OBJECT1].mesh_index;
		//v1 = objects[SEARCH_OBJECT1_MIP].mesh_index;

		//000B4828 00021080 sll     v0, $2
		//000B482C 00031880 sll     v1, $2
		//v1 = meshes[objects[SEARCH_OBJECT1_MIP].mesh_index];
		//000B4834 8C640000 lw      a0, $0(v1)
		//v0 = meshes[objects[SEARCH_OBJECT1].mesh_index];
		//000B483C AC440004 sw      a0, $4(v0)
		//000B4840 3C02000A lui     v0, $A
	}//0xB451C

	//a3 = &AnimatingWaterfallsV[0];
	//a2 = &AnimatingWaterfalls[0];
	//v0 = &objects[0];
	//a1 = &spark[21];
	//s4 = 5;
	//t1 = meshes;
	//t0 = psxtextinfo;

	if (spark[21].NodeNumber & 1)
	{
		assert(0);
	}

	//0xB45AC

	//0xB45V0
#if INTERNAL
	MonitorScreenTI = NULL;
#endif

	//a0, a3 = 0xA0000
	//a1, v0 = 0x1F0000
	//a0 = &objects[0];
#if !INTERNAL
	//sw      0,$6F5C(a3) maybe same as MonitorScreenTI = NULL;
#endif
	if (objects[MONITOR_SCREEN].bite_offset & 0x10000)//000B4904, 000B47E8
	{
		assert(0);
	}//0xB4708

	InitialiseCutseq();

	if (RelocPtr[14] != NULL)
	{
		//jalr ((void*)(RelocPtr[14])[0])
	}//0xB473C

#if 0// !INTERNAL
	000B4948 3C06000A lui     a2, $A
		000B494C 90C23A88 lbu     v0, $3A88(a2)
		000B4950 00000000 nop
		000B4954 14400035 bne     v0, 0, $B4A2C
		000B4958 3C07000A lui     a3, $A
		000B495C 3C11000A lui     s1, $A
		000B4960 8E233A60 lw      v1, $3A60(s1)
		000B4964 00000000 nop
		000B4968 8C620000 lw      v0, $0(v1)
		000B496C 00000000 nop
		000B4970 00021102 srl     v0, $4
		000B4974 30420007 andi    v0, $7
		000B4978 2442FFFF subiu   v0, $1
		000B497C 2C420002 sltiu   v0, v0, $2
		000B4980 1040002A beq     v0, 0, $B4A2C
		000B4984 3C020000 lui     v0, $0
		000B4988 24469EAC subiu   a2, v0, $6154
		000B498C 88C70003 lwl     a3, $3(a2)
		000B4990 98C70000 lwr     a3, $0(a2)
		000B4994 88C30007 lwl     v1, $7(a2)
		000B4998 98C30004 lwr     v1, $4(a2)
		000B499C ABA7001B swl     a3, $1B(sp)
		000B49A0 BBA70018 swr     a3, $18(sp)
		000B49A4 ABA3001F swl     v1, $1F(sp)
		000B49A8 BBA3001C swr     v1, $1C(sp)
		000B49AC 0C017D51 jal     $5F544
		000B49B0 24042000 addiu   a0, 0, $2000
		000B49B4 00002021 addu    a0, 0, 0
		000B49B8 0C017FEA jal     $5FFA8
		000B49BC 00408021 addu    s0, v0, 0
		000B49C0 8E233A60 lw      v1, $3A60(s1)
		000B49C4 00000000 nop
		000B49C8 8C620000 lw      v0, $0(v1)
		000B49CC 24030002 addiu   v1, 0, $2
		000B49D0 00021102 srl     v0, $4
		000B49D4 30440007 andi    a0, v0, $7
		000B49D8 14830005 bne     a0, v1, $B49F0
		000B49DC 24020001 addiu   v0, 0, $1
		000B49E0 0C0178F0 jal     $5E3C0
		000B49E4 24040032 addiu   a0, 0, $32
		000B49E8 080003AB j       $EAC
		000B49EC 02002021 addu    a0, s0, 0
		000B49F0 14820003 bne     a0, v0, $B4A00
		000B49F4 00000000 nop
		000B49F8 0C0178F0 jal     $5E3C0
		000B49FC 24040031 addiu   a0, 0, $31
		000B4A00 02002021 addu    a0, s0, 0
		000B4A04 0C017905 jal     $5E414
		000B4A08 24051C80 addiu   a1, 0, $1C80
		000B4A0C 27A40018 addiu   a0, sp, $18
		000B4A10 0C01AC71 jal     $6B1C4
		000B4A14 02002821 addu    a1, s0, 0
		000B4A18 0C01AC51 jal     $6B144
		000B4A1C 00002021 addu    a0, 0, 0
		000B4A20 0C017FEA jal     $5FFA8
		000B4A24 24040001 addiu   a0, 0, $1
		000B4A28 3C07000A lui     a3, $A
#endif
	if (gfCurrentLevel == LVL5_ESCAPE_WITH_THE_IRIS)
	{
		inventry_objects_list[7].yoff = 4;
		inventry_objects_list[7].yrot = -16384;
		inventry_objects_list[7].xrot = 8448;
		inventry_objects_list[7].zrot = 16384;
		inventry_objects_list[7].flags = 10;

		inventry_objects_list[8].yoff = 4;
		inventry_objects_list[8].yrot = -16384;
		inventry_objects_list[8].xrot = 8448;
		inventry_objects_list[8].zrot = 16384;
	}
	else
	{
		inventry_objects_list[7].yoff = 0;
		inventry_objects_list[7].yrot = 0;
		inventry_objects_list[7].xrot = -16384;
		inventry_objects_list[7].zrot = 0;
		inventry_objects_list[7].flags = 2;

		inventry_objects_list[8].yoff = 0;
		inventry_objects_list[8].yrot = 0;
		inventry_objects_list[8].xrot = -16384;
		inventry_objects_list[8].zrot = 0;
	}

	inventry_objects_list[8].flags = 0;

	if (gfCurrentLevel == LVL5_TITLE)
	{
		MGSaveGamePtr = game_malloc(8192);
		FromTitle = 1;
	}//0xB48D4

	//assert(lara_item);//000A3AA4 appears to be set during InitialiseItem(i)... probably item specific init routines
}//0xB48FC

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

	for (i = 0; i < NUMBER_OBJECTS; i++)
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

		*(int*)&objects[i].frame_base += (ptrdiff_t) frames;
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
			assert(0);
			//FIXME need to extract obj index or analyse this properly when used
			//v0 = 0x1F0000
			//t0 = &objects[0];
			//v0 = ((gfNumMips[i] & 0xF) * 128) | 0x6800;
			//v0 += t0;
			//a0 = (gfNumMips[i] & 0xF0) * 64;
			//object->object_mip = a0;
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

	if (objects[RAT].bite_offset & 0x10000)
	{
		Rats = (RAT_STRUCT*)game_malloc(sizeof(RAT_STRUCT) * 32);
	}//B9914

	if (objects[BAT].bite_offset & 0x10000)
	{
		Bats = (BAT_STRUCT*)game_malloc(sizeof(BAT_STRUCT) * 64);
	}//B9938

	if (objects[SPIDER].bite_offset & 0x10000)
	{
		Spiders = (SPIDER_STRUCT*)game_malloc(sizeof(SPIDER_STRUCT) * 64);
	}

}//0xB996C

//Looks to setup item init ptrs?
void sub_B5328()
{
	sizeof(object_info);
	object_info* object = &objects[LARA];

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
	object = &objects[SAS];

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

	if (gfCurrentLevel == LVL5_THIRTEENTH_FLOOR || gfCurrentLevel == LVL5_BASE ||gfCurrentLevel == LVL5_GALLOWS_TREE || gfCurrentLevel == LVL5_STREETS_OF_ROME && gfInitialiseGame != 0)
	{
		//B9E50
		sub_B4EE4(0);
	}
	else
	{
		//B9E60
		sub_B4EE4(1);
	}
	//B9E68
	sub_B9974();
	//sub_B9B84();

	SeedRandomDraw(0xD371F947);
	SeedRandomControl(0xD371F947);

	return;
}

void sub_B4A40()
{
}

void InitialiseSqrtTable()//?(<), B4D14(<)
{
	int i;

	for (i = 0; i < 1024; i++)
	{
		OurSqrt[i] = 0;// phd_sqrt_asm(i);
	}

	return;
}

void InitialiseAnimatedTextures()//?(<), B4904(<)
{
	int i;
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
	while (a0 < nAnimUVRanges)
	{
		//v1 = AnimTextureRanges[0];
		//a1 += 2;//size of short next anim tex range
		//t2 = a0 + 1;
		//if(AnimTextureRanges[0] > -1)
		{
			//t1 = t4;
			//t3 = AnimatingTexturesV;
			//v0 = a0 << 1;
			//v0 += a0;
			//t0 = v0 << 4;
			while (v1 >= 0)
			{
				//a3 = a1 + 2;
				//a2 = v1 - 1;
				//v0 = v1 << 1;
				//v0 += v1;
				//v0 <<= 1;
				//v0 += t0;
				//a0 = v0 + t3;
				//v1 = a1[0];
				//a1 += 2;//sizeof short
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

		//a0 = t2;
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
	sizeof(object_info);

#if 0
	000B5074 3C040020 lui     a0, $20
	000B5078 3C05000A lui     a1, $A


	binoculars_mesh_ptr = meshes[objects[BINOCULAR_GRAPHICS].mesh_index];//$a0

	if()//TODO reconstruct.

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
	MESH_STRUCT* mesh;

	target_mesh_ptr = meshes[objects[TARGET_GRAPHICS].mesh_index];
	mesh = (MESH_STRUCT*)target_mesh_ptr;

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

void InitialiseFlipMaps()//?(<), B9D30(<)
{
	int i;

	for (i = 0; i < 10; i++)
	{
		flipmap[0] = 0;
		flip_stats[0] = 0;
	}

	flip_status = 0;
	flipeffect = 1;
		
	for (i = 0; i < 136; i++)
	{
		cd_flags[i] = 0;
	}

	IsAtmospherePlaying = 0;
	camera.underwater = 0;
}

//InitialiseLaraCarriedItems
void sub_B4EE4(long keep_carried_items)
{
	return;//************************************************************* temp crashes game cuz unfinished
	int lara_item_number_backup;
	lara_info lara_backup;
	sizeof(lara_info);

	//000B5134 3C02000A lui     v0, $A
	//s1 = &lara;
	lara_item_number_backup = lara.item_number;//$s0
		//v1 = -1;
		//s4 = v0; //0xA0000

	//000B5174 AFA40198 sw      a0, $198(sp) //Critical stored at stckptrv
	if (lara.item_number == -1)
	{
		return;
	}

	//v0 = 0xA0000;
	//s3 = &lara_item;

	//v0=lara_item.flags;//132
	//v1 = -0x21;
	lara_item->data = &lara;
	lara_item->meshswap_meshbits &= 0xFFDF;

	//Possible hack, resets carried items? For specific levels.
	//Should be done in script.
	if (keep_carried_items == 0)
	{
		memset((char*) &lara, 0, sizeof(lara_info));
	}
	else
	{
		memcpy(&lara_backup, &lara, sizeof(lara_info));
		memset((char*) &lara, 0, sizeof(lara_info));
		memcpy(&lara.pistols_type_carried, &lara_backup.pistols_type_carried, 59);
	}

	lara.item_number = lara_item_number_backup;

#if 0
	//s0 = 0;
	//a0 = &lara;
	//a1 = -1;
	//v0 = 0x708
	lara.air = 1800;
	lara.hit_direction = -1;
	lara.weapon_item = -1;
	//000B5204 3C02000A lui     v0, $A
	PoisonFlag = 0;
	//v0 = 0x64;
	//v1 = 0xE;
	lara.holster = 14;
	//v1 = -1;
	lara.RopePtr = -1;
	v1 = 0x3E8;
	//000B522C 3C1E000A lui     fp, $A
	//000B5230 3C16001F lui     s6, $1F
	//000B5234 3C17000A lui     s7, $A
	lara.water_surface_dist = 100;
	000B523C 8C820044 lw      v0, $44(a0)
	000B5240 3C15000A lui     s5, $A
	000B5244 A4800032 sh      0, $32(a0)
	000B5248 A4800030 sh      0, $30(a0)
	000B524C A0850158 sb      a1, $158(a0)
	000B5250 A0850159 sb      a1, $159(a0)
	000B5254 34420004 ori     v0, $4
	000B5258 AC820044 sw      v0, $44(a0)
	000B525C 3C04000A lui     a0, $A
	000B5260 A6630022 sh      v1, $22(s3)
	000B5264 908205D1 lbu     v0, $5D1(a0)
	000B5268 00000000 nop
	000B526C 1040000F beq     v0, 0, $B52AC
	000B5270 00808821 addu    s1, a0, 0
	000B5274 3C02000A lui     v0, $A
	000B5278 24522004 addiu   s2, v0, $2004
	000B527C 02121021 addu    v0, s0, s2
	000B5280 90440000 lbu     a0, $0(v0)
	000B5284 0C0102C2 jal     $40B08
	000B5288 26100001 addiu   s0, $1
	000B528C 00021400 sll     v0, $10
	000B5290 0C00FFAC jal     $3FEB0
	000B5294 00022403 sra     a0, v0, $10
	S000B5298 922205D1 lbu     v0, $5D1(s1)
#endif
}

void sub_B9974()
{
}

void InitialiseCutseq()//?(<), BA194(<)
{
	cutseq_num = 0;
	cutseq_trig = 0;
	GLOBAL_playing_cutseq = 0;
	GLOBAL_cutseq_frame = 0;

	SetFadeClip(0, 1);
}

void InitialiseResidentCut(unsigned char a0, unsigned char a1, unsigned char a2, unsigned char a3)//?, B9EA0
{
	return;
	int i;
	FILE* nHandle;
	int s2;
	int s3;
	int s5;
	int s4;
	int s0;
	int s1;
	int s6;
	int s7;
	int a00;

	if ((a0 | a1 | a2 | a3) == 0)
	{
		//0xBA0AC
		return;
	}

	lastcamnum = -1;
	GLOBAL_playing_cutseq = 0;
	cutseq_trig = 0;

	for (i = 0; i < 46; i++)
	{
		cutseq_resident_addresses[i].packed_data = NULL;
	}

#if INTERNAL
	nHandle = fopen("\\CUTSEQ.JIZ", "rb");
	FILE_Read(&tsv_buffer[0], 1, 2048, nHandle);
#else
	CD_InitialiseReaderPosition(1);
	CD_Read((char*)&tsv_buffer[0], 2048);
#endif

	s2 = sub_BA0DC(a0);
	s3 = sub_BA0DC(a1);
	s5 = sub_BA0DC(a2);
	s4 = sub_BA0DC(a3);

#if INTERNAL
	fclose(nHandle);
#endif

	if (s2 != 0)
	{
		s0 = sub_BA148(s2);
	}//0xB9FA4

	if (s3 != 0)
	{
		s1 = sub_BA148(s3);
	}//0xB9FB8

	if (s5 != 0)
	{
		s6 = sub_BA148(s5);
	}//0xB9FCC

	if (s4 != 0)
	{
		s7 = sub_BA148(s4);
	}//0xB9FE0

	if (s0 > 0)
	{
		a00 = s0;
	}
	else
	{
		a00 = 0;
	}

	if (a00 < s1)
	{

	}//0xBA000

}

long sub_BA0DC(unsigned char a0)
{
	return 0;
}

long sub_BA148(unsigned char a0)
{
	return 0;
}
