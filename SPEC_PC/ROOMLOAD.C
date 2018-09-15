#include "ROOMLOAD.H"
#include "SPECIFIC.H"
#include "ITEMS.H"
#include "CONTROL.H"
#include "malloc.h"
#include "DRAW.H"
#include "BOX.H"
#include "GAMEFLOW.H"
#include "GAME.H"
#include "EFFECTS.H"
#include "CAMERA.H"
#include "SPOTCAM.H"
#include "EFFECT2.H"
#include "SOUND.H"
#include "PCSOUND.H"
#include "FILE.H"
#include <process.h>
#include "LOT.H"
#include "WINMAIN.H"
#include "ERROR.H"
#include "DIRECTX.H"
#include "HAIR.H"
#include "SWITCH.H"
#include "PICKUP.H"
#include "TOMB4FX.H"
#include "DELTAPAK.H"
#include "LARA.H"
#include "DOOR.H"

long AnimFilePos;
long AnimFileLen;
short* floor_data;
short* mesh_base;
FILE* fp_level;
char* lvDataPtr;
char* lvDataPtr_orig; // debug purposes shhh
DWORD num_items;
DWORD numLvlMeshes;
struct mesh_vbuf_s
{
	char pad0[4]; // pos 0 size 4
	short* field1; // pos 4 size 4  APPARENTLY object texture index
	char pad[22]; // pos 8 size 22
	LPDIRECT3DVERTEXBUFFER vbuf; // pos 30 size 4
	char pad2[36]; // pos 34 size 36
};
struct mesh_vbuf_s** mesh_vbufs;
struct SPRITE_STRUCT* sprites;
struct OBJECT_TEXTURE* object_textures;
struct OBJECT_TEXTURE* waterfall_textures[6];
float waterfall_y[6];
void* dword_87B0F0;
void* dword_87B0F4;
struct OBJECT_TEXTURE* dword_87497C;
float flt_874980;
#define AllocT(d, s, n) d = (s*)game_malloc(sizeof(s) * (n))
#define AllocReadT(d, s, n) AllocT((d), s, (n));OnlyReadT((d), s, (n))
#define OnlyReadT(d, s, n) readBytes((d), sizeof(s) * (n))

#define Alloc(d, s, n) d = (struct s*)game_malloc(sizeof(struct s) * (n))
#define AllocRead(d, s, n) Alloc((d), s, (n));OnlyRead((d), s, (n))
#define OnlyRead(d, s, n) readBytes((d), sizeof(struct s) * (n))

#define AddPtr(p, t, n) p = (t*)((char*)(p) + (ptrdiff_t)(n)); 

//#define LogCurPos() Log(2, "current pos: %08x", 0x319af7 + (int)(lvDataPtr - lvDataPtr_orig))

inline uint8_t readByte()
{
	const uint8_t ret = *(uint8_t*)lvDataPtr;
	lvDataPtr += 1;
	return ret;
}

inline uint16_t readWord()
{
	const uint16_t ret = *(uint16_t*)lvDataPtr;
	lvDataPtr += 2;
	return ret;
}

inline uint32_t readDword()
{
	const uint32_t ret = *(uint32_t*)lvDataPtr;
	lvDataPtr += 4;
	return ret;
}

inline uint16_t freadWord()
{
	uint16_t ret;
	fread_ex(&ret, 2, 1, fp_level);
	return ret;
}

inline uint32_t freadDword()
{
	uint32_t ret;
	fread_ex(&ret, 4, 1, fp_level);
	return ret;
}

inline void readBytes(void* dst, unsigned int count)
{
	qmemcpy(dst, lvDataPtr, count);
	lvDataPtr += count;
}

inline void freadBytes(unsigned int count)
{
	void* buf = malloc(count);
	fread_ex(buf, 1, count, fp_level);
	free(buf);
}

void InitialiseItemArray_old(int num)
{
	next_item_free = level_items;
	next_item_active = -1;
	int v1 = level_items + 1;
	struct ITEM_INFO *curItem = &items[level_items];
	if (level_items + 1 >= num)
	{
		curItem->next_item = -1;
	}
	else
	{
		do
		{
			curItem->next_item = v1++;
			curItem->active = FALSE;
			curItem++;
		} while (v1 < num);
		curItem->next_item = -1;
	}
}

void InitialiseClosedDoors()
{
	memset(ClosedDoors, 0, 32 * sizeof(DWORD));
}

void LoadItems()
{
	Log(2, "LoadItems");

	num_items = readDword();

	if (num_items == 0) return;
	Alloc(items, ITEM_INFO, 256);
	level_items = num_items;
	InitialiseClosedDoors();
	InitialiseItemArray(256);

	for (int it = 0; it < num_items; it++)
	{
		struct ITEM_INFO* item = &items[it];

		item->object_number = readWord();
		item->room_number = readWord();
		item->pos.x_pos = readDword();
		item->pos.y_pos = readDword();
		item->pos.z_pos = readDword();
		item->pos.y_rot = readWord();
		item->shade = readWord();
		item->trigger_flags = readWord();
		item->flags = readWord();
	}

	for (int it = 0; it < num_items; it++)
	{
		InitialiseItem(it);
	}

	for (int r = 0; r < number_rooms; r++)
	{
		struct MESH_INFO* mesh = room[r].mesh;

		for (int m = 0; m < room[r].num_meshes; m++)
		{
			int sec = ((mesh->z - room[r].z) >> 10) + room[r].x_size * ((mesh->x - room[r].x) >> 10);
			struct FLOOR_INFO* floor = &room[r].floor[sec];

			if (!(boxes[floor->box].overlap_index & 0x4000)
				&& !(gfCurrentLevel == LVL5_BASE && (r == 19 || r == 23 || r == 16)))
			{
				int fl = floor->floor << 2;
				struct static_info* st = &static_objects[mesh->static_number];
				if (fl <= mesh->y - st->y_maxc + 512 
					&& fl < mesh->y - st->y_minc)
				{
					if (st->x_maxc == 0 || st->x_minc == 0 ||
						st->z_maxc == 0 || st->z_minc == 0 ||
						(HIBYTE(st->x_maxc) ^ HIBYTE(st->x_minc) & 0x80 && 
							HIBYTE(st->z_maxc) ^ HIBYTE(st->z_minc) & 0x80))
					{
						floor->box |= 8;
					}
				}
			}
		}
	}
}

void LoadAnimatedTextures()
{
	const int numAnimTex = readDword();
	AllocReadT(AnimTextureRanges, uint16_t, numAnimTex);

	nAnimUVRanges = readByte();
}

void LoadSoundEffects()
{
	Log(2, "LoadSoundEffects");

	number_sound_effects = readDword();
	Log(8, "Number of SFX %d", number_sound_effects);

	if (number_sound_effects)
	{
		AllocRead(sound_effects, OBJECT_VECTOR, number_sound_effects);
	}
}

void LoadCameras()
{
	Log(2, "LoadCameras");

	number_cameras = readDword();

	if (number_cameras != 0)
	{
		AllocRead(camera.fixed, OBJECT_VECTOR, number_cameras);
	}

	number_spotcams = readDword();

	if (number_spotcams != 0)
	{
		OnlyRead(SpotCam, SPOTCAM, number_spotcams);
	}
}

void LoadBoxes()
{
	Log(2, "LoadBoxes");

	number_boxes = readDword();
	AllocRead(boxes, box_info, number_boxes);

	int numOverlaps = readDword();
	AllocReadT(overlap, uint16_t, numOverlaps);

#if FALSE
	short** v3 = ground_zone[4];
	int v4 = number_boxes;
	int v13;
	do
	{
		int v5 = 2 * v4;
		short** v6 = v3 - 8;
		int v21 = 4;
		do
		{
			short* v7 = (short*)game_malloc(v5);
			void* v8 = lvDataPtr;
			unsigned int v9 = 2 * number_boxes;
			char v10 = 2 * number_boxes;
			*v6 = v7;
			v9 >>= 2;
			qmemcpy(v7, v8, 4 * v9);
			char* v12 = (char*)v8 + 4 * v9;
			short* v11 = &v7[2 * v9];
			LOBYTE(v9) = v10;
			v13 = v21;
			qmemcpy(v11, v12, v9 & 3);
			v6 += 2;
			v5 = 2 * number_boxes;
			lvDataPtr = (char*)lvDataPtr + 2 * number_boxes;
			--v21;
		} while (v13 != 1);

		char* v14 = (char*)game_malloc(2 * number_boxes);
		void* v15 = lvDataPtr;
		unsigned int v16 = 2 * number_boxes;
		*v3 = (short*)v14;
		qmemcpy(v14, v15, v16);
		++v3;
	} while ((int)v3 < (int)(ground_zone + 5 * 2));
#endif
	// todo may not work, but gives the same result as code (Core) above on ideone
	for (int i = 0; i < 5; i++)
	{
		AllocReadT(ground_zone[i][0], short, number_boxes);
	}
	// weird workaround because Core's code seem to only read half of the zones
	for (int i = 0; i < 5; i++)
	{
		short* tmp;
		AllocReadT(tmp, short, number_boxes);
		game_free(number_boxes * sizeof(short));
	}

	for (int i = 0; i < number_boxes; i++)
	{
		if (boxes[i].overlap_index & BOX_LAST)
		{
			boxes[i].overlap_index |= BOX_BLOCKED;
		}
	}
}

DWORD dword_7E7FE8;
DWORD NumRoomLights;
/*#pragma pack(push, 1)
struct room_data
{
	uint32_t Separator;     // 0xCDCDCDCD (4 bytes)

	uint32_t EndSDOffset;
	uint32_t StartSDOffset;

	uint32_t Separator2;     // Either 0 or 0xCDCDCDCD

	uint32_t EndPortalOffset;

	struct    // 20 bytes
	{
		int32_t x;             // X-offset of room (world coordinates)
		int32_t y;             // Y-offset of room (world coordinates) - only in TR5
		int32_t z;             // Z-offset of room (world coordinates)
		int32_t yBottom;
		int32_t yTop;
	} room_info;

	uint16_t NumZSectors;
	uint16_t NumXSectors;

	struct CVECTOR RoomColour;   // In ARGB format!

	uint16_t NumLights;
	uint16_t NumStaticMeshes;

	uint8_t  ReverbInfo;
	uint8_t  AlternateGroup;
	uint8_t MeshEffect;
	uint8_t BoundActive;

	short left; // size=0, offset=56
	short right; // size=0, offset=58
	short top; // size=0, offset=60
	short bottom; // size=0, offset=62

	short test_left; // size=0, offset=64
	short test_right; // size=0, offset=66
	short test_top; // size=0, offset=68
	short test_bottom; // size=0, offset=70

	short item_number; // size=0, offset=72
	short fx_number; // size=0, offset=74

	uint16_t AlternateRoom;
	uint16_t Flags;

	uint32_t Unknown1;
	uint32_t Unknown2;     // Always 0
	uint32_t Unknown3;     // Always 0

	uint32_t Separator4;    // 0xCDCDCDCD

	uint16_t Unknown4;
	uint16_t Unknown5;

	float RoomX;
	float RoomY;
	float RoomZ;

	uint32_t Separator5[4]; // Always 0xCDCDCDCD
	uint32_t Separator6;    // 0 for normal rooms and 0xCDCDCDCD for null rooms
	uint32_t Separator7;    // Always 0xCDCDCDCD

	uint32_t NumRoomTriangles;
	uint32_t NumRoomRectangles;

	uint32_t Separator8;     // Always 0

	uint32_t LightDataSize;
	uint32_t NumLights2;    // Always same as NumLights

	uint32_t Unknown6;

	int32_t RoomYTop;
	int32_t RoomYBottom;

	uint32_t NumLayers;

	uint32_t LayerOffset;
	uint32_t VerticesOffset;
	uint32_t PolyOffset;
	uint32_t PolyOffset2;   // Same as PolyOffset

	uint32_t NumVertices;

	uint32_t Separator9[4];  // Always 0xCDCDCDCD
};
#pragma pop*/
void FixUpRoom(struct room_info *rooms, /*tr5_room*/struct room_info *roomData)
{
	AddPtr(roomData->door, short, roomData + 1);
	AddPtr(roomData->floor, struct FLOOR_INFO, roomData + 1);
	AddPtr(roomData->light, struct LIGHTINFO, roomData + 1);
	AddPtr(roomData->mesh, struct MESH_INFO, roomData + 1);
	AddPtr(roomData->Separator4, void, roomData + 1);	
	AddPtr(roomData->LayerOffset, struct ROOMLET, roomData + 1);
	AddPtr(roomData->PolyOffset, void, roomData + 1);
	AddPtr(roomData->PolyOffset2, void, roomData + 1);
	AddPtr(roomData->VerticesOffset, struct tr5_room_vertex, roomData + 1);

	roomData->LightDataSize += (uint32_t)(roomData + 1);

	if ((uint8_t)roomData->door & 1)
	{
		Log(0, "%X", roomData->door);
		roomData->door = 0;
	}

	char* polyOff = roomData->PolyOffset;
	char* polyOff2 = roomData->PolyOffset2;
	char* vertOff = (char*)roomData->VerticesOffset;

	for(int i = 0; i < roomData->NumLayers; i++)
	{
		roomData->LayerOffset[i].PolyOffset = polyOff;
		roomData->LayerOffset[i].PolyOffset2 = polyOff2;
		roomData->LayerOffset[i].VerticesOffset = vertOff;

		polyOff += sizeof(struct tr4_mesh_face3) * roomData->LayerOffset[i].NumLayerTriangles +
			sizeof(struct tr4_mesh_face4) * roomData->LayerOffset[i].NumLayerRectangles;

		polyOff2 += 4 * roomData->LayerOffset[i].NumLayerVertices; // todo find what struct this is

		vertOff += sizeof(struct tr5_room_vertex) * roomData->LayerOffset[i].NumLayerVertices;
	}

	qmemcpy(rooms, roomData, sizeof(struct room_info));

	if (rooms->num_lights > NumRoomLights)
		NumRoomLights = rooms->num_lights;
}

void LoadRoomStream()
{
	readDword(); // read unused value

	int numRooms = readDword(); // todo maybe it's 16 so it'll explode
	Alloc(room, room_info, numRooms);

	for (int i = 0; i < numRooms; i++)
	{
		readDword(); // XELA landmark

		int roomDataSize = readDword();
		char* roomData;
		AllocReadT(roomData, char, roomDataSize);

		FixUpRoom(&room[i], roomData);
	}

	number_rooms = numRooms;
}

DWORD dword_EEF4AC;

int sub_4774D0()
{

	int v0; // ebp@1
	char *v1; // eax@1
	int v2; // eax@1
	int v3; // esi@2
	char *v4; // edx@2
	signed int v5; // ebx@8
	struct room_info *v6; // eax@9
	int v7; // ecx@10
	int v8; // edx@10
	int v9; // esi@11
	signed int v10; // edi@11
	int v11; // eax@23
	int v12; // ecx@23
	BOOL v13; // sf@33
	unsigned __int8 v14; // of@33
	_BYTE *v15; // esi@35
	int v16; // ecx@35
	int result; // eax@35
	int v18; // edi@36
	unsigned int v19; // edx@37
	_BYTE *v20; // ebx@37
	unsigned __int8 v21; // al@37
	char *v22; // eax@43
	int v23; // ecx@45
	BOOL v24; // zf@53
	signed int v25; // [sp+10h] [bp-118h]@6
	unsigned int v26; // [sp+10h] [bp-118h]@35
	signed int v27; // [sp+14h] [bp-114h]@8
	int v28; // [sp+14h] [bp-114h]@36
	int v29; // [sp+18h] [bp-110h]@1
	int v30; // [sp+18h] [bp-110h]@36
	signed int v31; // [sp+1Ch] [bp-10Ch]@10
	signed int v32; // [sp+1Ch] [bp-10Ch]@36
	signed int v33; // [sp+20h] [bp-108h]@7
	signed int v34; // [sp+24h] [bp-104h]@10
	char v35[256]; // [sp+28h] [bp-100h]@1

	v0 = 0;
	v29 = 0;
	OutsideRoomOffsets = (__int16 *)game_malloc(1458);
	v1 = game_malloc(46656);
	dword_EEF4AC = (int)v1;
	memset(v1, 0xFFu, 0xB640u);
	memset(v35, 0, 0xFCu);
	*(_WORD *)&v35[252] = 0;
	v35[254] = 0;
	v2 = number_rooms;
	if (number_rooms > 0)
	{
		v3 = number_rooms;
		v4 = (char *)&room->flipped_room;
		do
		{
			if (*(_WORD *)v4 != -1)
				v35[*(_WORD *)v4] = 1;
			v4 += 208;
			--v3;
		} while (v3);
	}
	v25 = 0;
	do
	{
		v33 = 0;
		do
		{
			v5 = 0;
			v27 = 0;
			if (v2 > 0)
			{
				do
				{
					v6 = &room[v5];
					if (!v35[v5])
					{
						v7 = (v6->z >> 10) + 1;
						v8 = (v6->x >> 10) + 1;
						v31 = 0;
						v34 = 4;
						do
						{
							v9 = v33;
							v10 = 0;
							while (v9 < v7 || v9 >= v6->x_size + v7 - 2 || v0 < v8 || v0 >= v6->y_size + v8 - 2)
							{
								++v10;
								++v9;
								if (v10 >= 4)
									goto LABEL_19;
							}
							v31 = 1;
						LABEL_19:
							++v0;
							--v34;
						} while (v34);
						if (v31)
						{
							v5 = v27;
							if (v27 == 255)
								printf("ERROR : Room 255 fuckeroony - go tell Chris");
							v0 = v25;
							v11 = dword_EEF4AC + (((v33 >> 2) + 27 * (v25 >> 2)) << 6);
							v12 = 0;
							while (*(_BYTE *)(v11 + v12) != -1)
							{
								if (++v12 >= 64)
									goto LABEL_29;
							}
							*(_BYTE *)(v11 + v12) = v27;
							if (v12 > v29)
								v29 = v12;
						LABEL_29:
							if (v12 == 64)
								printf("ERROR : Buffer shittage - go tell Chris");
						}
						else
						{
							v0 = v25;
							v5 = v27;
						}
					}
					v2 = number_rooms;
					v27 = ++v5;
				} while (v5 < number_rooms);
			}
			v14 = __OFSUB__(v33 + 4, 108);
			v13 = v33 - 104 < 0;
			v33 += 4;
		} while (v13 ^ v14);
		v0 += 4;
		v25 = v0;
	} while (v0 < 108);
	v15 = (_BYTE *)dword_EEF4AC;
	v16 = 0;
	v26 = dword_EEF4AC;
	result = 0;
	do
	{
		v18 = v16;
		v30 = result;
		v28 = v16;
		v32 = 27;
		do
		{
			v19 = 0;
			v20 = (_BYTE *)(result + dword_EEF4AC);
			v21 = *(_BYTE *)(result + dword_EEF4AC);
			if (v21 == -1)
				goto LABEL_57;
			do
				++v19;
			while (v20[v19] != -1);
			if (v19)
			{
				if (v19 == 1)
				{
					*(__int16 *)((char *)OutsideRoomOffsets + v18) = v21 | 0x8000;
				}
				else
				{
					v22 = (char *)dword_EEF4AC;
					if (dword_EEF4AC >= (unsigned int)v15)
						goto LABEL_50;
					while (memcmp(v22, v20, v19))
					{
						v23 = 0;
						if (*v22 != -1)
						{
							do
								++v23;
							while (v22[v23] != -1);
						}
						v15 = (_BYTE *)v26;
						v22 += v23 + 1;
						if ((unsigned int)v22 >= v26)
						{
							v18 = v28;
							goto LABEL_50;
						}
					}
					v18 = v28;
					*(__int16 *)((char *)OutsideRoomOffsets + v28) = (_WORD)v22 - dword_EEF4AC;
					v15 = (_BYTE *)v26;
					if ((unsigned int)v22 >= v26)
					{
					LABEL_50:
						*(__int16 *)((char *)OutsideRoomOffsets + v18) = (_WORD)v15 - dword_EEF4AC;
						do
						{
							*v15++ = *v20++;
							--v19;
						} while (v19);
						*v15++ = -1;
						v26 = (unsigned int)v15;
					}
				}
			}
			else
			{
			LABEL_57:
				*(__int16 *)((char *)OutsideRoomOffsets + v18) = -1;
			}
			result = v30 + 64;
			v18 += 2;
			v24 = v32 == 1;
			v30 += 64;
			v28 = v18;
			--v32;
		} while (!v24);
		v16 = v18;
	} while (result < 46656);
	return result;
}

void LoadRooms()
{
	Log(2, "LoadRooms");

	wibble = 0;
	NumRoomLights = 0;
	dword_7E7FE8 = 0;

	LoadRoomStream();
	//sub_4774D0();

	int numFloorData = readDword();
	AllocReadT(floor_data, short, numFloorData);
	Log(0, "Floor Data Size %d @ %x", numFloorData, floor_data);
}

void LoadSamples()
{
	Log(2, "LoadSamples");

	AllocReadT(sample_lut, short, 450);
	
	numSampleInfos = readDword();
	Log(8, "Number Of Sample Infos %d", numSampleInfos);

	if (numSampleInfos == 0)
	{
		Log(1, "No Sample Infos");
		return;
	}

	AllocRead(sample_infos, SAMPLE_INFO, numSampleInfos);

	int numSampleIndices = readDword();

	if (numSampleIndices == 0)
	{
		Log(1, "No Samples");
		return;
	}

	Log(8, "Number Of Samples %d", numSampleIndices);
	int v4;
	fread_ex(&v4, 1, 4, fp_level);

	if (feof(fp_level))
		Log(1, "END OF FILE");

	StreamOpen();

	if (v4 > 0)
	{
		int v2 = 0;
		int v5, v3;
		while (TRUE)
		{
			fread_ex(&v5, 1u, 4u, fp_level);
			fread_ex(&v3, 1u, 4u, fp_level);
			fread_ex(dword_86BEDC, v3, 1u, fp_level);
			if (!DXCreateSampleADPCM(dword_86BEDC, v3, v5, v2))
				break;
			if (++v2 >= v4)
				break;
		}
	}

	StreamClose();
}

void LoadAIObjects()
{
	int num = readDword();

	if (num != 0)
	{
		nAIObjects = num;
		AllocRead(AIObjects, AIOBJECT, nAIObjects);
	}
}

DWORD numTpages;
DWORD dword_D99DA8;
DWORD dword_D99DAC;
DWORD dword_D99DC0;
DWORD dword_D99DC4;
void* texbuf;
BYTE* byte_D99DCC;
DWORD dword_874968;

void sub_491DA0(int a1, int a2, int a3, int a4)
{
	S_Warn("[sub_491DA0] - Unimplemented!\n");
}

float flt_8BBD94;
float flt_8BBD90;
DWORD dword_8BBD64;
DWORD dword_8FBDC0;

int __cdecl S_InitLoadBar(int a1)
{
	int result; // eax@1

	result = a1;
	LODWORD(flt_8BBD94) = 0;
	dword_8BBD64 = a1;
	LODWORD(flt_8BBD90) = 0;
	dword_8FBDC0 = 1;
	return result;
}

void S_LoadBar()
{
	flt_8BBD94 = 100.0 / (double)dword_8BBD64 + flt_8BBD94;
}

void LoadDemoData()
{
	uint16_t numDemoData = readWord();
	// no demo data anymore, count is always 0
}

int numMeshes;
int numAnims;

int CreateSkinningData()
{
	S_Warn("[sub_456AE0] - Unimplemented!\n");
	return 0;
}

void __cdecl sub_42B900(int a1)
{
	S_Warn("[sub_42B900] - Unimplemented!\n");
}

signed int sub_4737C0()
{
	
}

__int16 sub_476360()
{
	
}

char sub_475D40()
{
	
}

int sub_43D8B0()
{
	
}

void InitialiseObjects()
{
	for (int i = 0; i < NUMBER_OBJECTS; i++)
	{
		objects[i].initialise = NULL;
		objects[i].collision = NULL;
		objects[i].control = NULL;

		objects[i].intelligent = 0;
		objects[i].save_position = 0;
		objects[i].save_hitpoints = 0;
		objects[i].save_flags = 0;
		objects[i].save_anim = 0;
		objects[i].water_creature = 0;
		objects[i].save_mesh = 0;
		objects[i].using_drawanimating_item = 1;

		objects[i].draw_routine = sub_42B900;
		objects[i].ceiling = NULL;
		objects[i].floor = NULL;

		objects[i].pivot_length = 0;
		objects[i].radius = 10;
		objects[i].shadow_size = 0;
		objects[i].hit_points = -16384;
		objects[i].explodable_meshbits = NULL;
		objects[i].draw_routine_extra = NULL;

		AddPtr(objects[i].frame_base, short*, frames);

		objects[i].object_mip = 0;
	}

	sub_4737C0();
	sub_476360();
	sub_475D40();
	InitialiseHair();
	sub_43D8B0();

	SequenceUsed[0] = 0;
	SequenceUsed[1] = 0;
	SequenceUsed[2] = 0;
	SequenceUsed[3] = 0;
	SequenceUsed[4] = 0;
	SequenceUsed[5] = 0;

	NumRPickups = 0;

	CurrentSequence = 0;

	SequenceResults[0][1][2] = 0;
	SequenceResults[0][2][1] = 1;
	SequenceResults[1][0][2] = 2;
	SequenceResults[1][2][0] = 3;
	SequenceResults[2][0][1] = 4;
	SequenceResults[2][1][0] = 5;

	for(int i = 0; i < gfNumMips; i++)
	{
		const int mip = (gfMips[i] & 0xF0) << 6;
		const int index = (gfMips[i] & 0xF) << 7;
		objects[ANIMATING1 + 2 * index].object_mip = mip;
	}

	if (objects[RAT].loaded)
		Rats = (struct RAT_STRUCT*)game_malloc(832); // todo find size

	if (objects[BAT].loaded)
		Bats = (struct BAT_STRUCT*)game_malloc(1920);

	if (objects[SPIDER].loaded)
		Spiders = (struct SPIDER_STRUCT*)game_malloc(1664);
}

void ProcessMeshData(int nmeshes)
{
	Log(2, "ProcessMeshData %d", nmeshes);

	numLvlMeshes = nmeshes;

	AllocT(mesh_vbufs, struct mesh_vbuf_s*, nmeshes);
	mesh_base = (short*)malloc_ptr;

	Log(2, "[ProcessMeshData] - Unimplemented!\n");

	Log(2, "End ProcessMeshData");
}

void LoadObjects()
{
	Log(1, "LoadObjects");

	memset(objects, 0, sizeof objects);
	memset(static_objects, 0, sizeof static_objects);

	int numMeshWords = readDword();
	AllocReadT(mesh_base, short, numMeshWords);

	int numMeshPtrs = readDword();
	AllocT(meshes, short*, 2 * numMeshPtrs);
	OnlyReadT(meshes, short*, numMeshPtrs);

	for (int i = 0; i < numMeshPtrs; i++)
	{
		meshes[i] = &mesh_base[(int)meshes[i] / 2];
	}

	numMeshes = numMeshPtrs;

	numAnims = readDword();
	AllocRead(anims, ANIM_STRUCT, numAnims);

	int numChanges = readDword();
	AllocRead(changes, CHANGE_STRUCT, numChanges);

	int numDisps = readDword();
	AllocRead(ranges, RANGE_STRUCT, numDisps);

	int numAnimCmds = readDword();
	AllocReadT(commands, short, numAnimCmds);

	int numBones = readDword();
	AllocReadT(bones, long, numBones);

	int numFrames = readDword();
	AllocReadT(frames, short, numFrames);

	for (int i = 0; i < numAnims; i++)
	{
		AddPtr(anims[i].frame_ptr, short, frames);
	}

	int numModels = readDword();

	for (int i = 0; i < numModels; i++)
	{
		int obj = readDword();

		objects[obj].nmeshes = readWord();
		objects[obj].mesh_index = readWord();
		objects[obj].bone_index = readDword();
		objects[obj].frame_base = readDword();
		objects[obj].anim_index = readWord();

		readWord(); // alignment, always 0xFFEF

		objects[obj].loaded = 1;
	}

	if (LaraDrawType != LARA_DIVESUIT)
		CreateSkinningData();

	for (int i = 0; i < NUMBER_OBJECTS; i++)
	{
		objects[i].mesh_index *= 2;
	}

	// DUPLICATE THE ITEMS
	// before:   meshes = [1, 2, 3, 4, 5, ?, ?, ?, ?, ?]
	// qmemcpy:  meshes = [1, 2, 3, 4, 5, 1, 2, 3, 4, 5]
	// for loop: meshes = [1, 1, 2, 2, 3, 3, 4, 4, 5, 5]

	qmemcpy(&meshes[numMeshes], &meshes[0], sizeof(short*) * numMeshes);

	for (int i = 0; i < numMeshes; i++)
	{
		meshes[2 * i] = meshes[numMeshes + i];
		meshes[2 * i + 1] = meshes[numMeshes + i];
	}

	InitialiseObjects();
	InitialiseClosedDoors();

	int numStatics = readDword();

	for (int i = 0; i < numStatics; i++)
	{
		int meshID = readDword();

		static_objects[meshID].mesh_number = readWord();

		static_objects[meshID].x_minp = readWord();
		static_objects[meshID].x_maxp = readWord();
		static_objects[meshID].y_minp = readWord();
		static_objects[meshID].y_maxp = readWord();
		static_objects[meshID].z_minp = readWord();
		static_objects[meshID].z_maxp = readWord();

		static_objects[meshID].x_minc = readWord();
		static_objects[meshID].x_maxc = readWord();
		static_objects[meshID].y_minc = readWord();
		static_objects[meshID].y_maxc = readWord();
		static_objects[meshID].z_minc = readWord();
		static_objects[meshID].z_maxc = readWord();

		static_objects[meshID].flags = readWord();
	}

	for (int i = 0; i < NUMBER_STATIC_OBJECTS; i++)
	{
		static_objects[i].mesh_number *= 2;
	}

	ProcessMeshData(2 * numMeshes);
}

void* dword_875144;
DWORD useCompression = 1;

void sub_403297(LPDDSURFACEDESC2 a1, LPDIRECTDRAWSURFACE4 a2, int a3, int a4)
{
	S_Warn("[sub_403297] - Unimplemented!\n");
}

_DWORD* __cdecl sub_4D0450(signed int a1, signed int a2, int a3, int a4, void(__cdecl* a5)(int *, int *, int *, int *), int a6)
{
	int v6; // eax@9
	_WORD* v7; // edx@9
	_BYTE* v8; // edi@10
	unsigned int* v9; // ebx@11
	void(__cdecl* v10)(int *, int *, int *, int *); // ebp@11
	struct WINAPP *v11; // esi@11
	unsigned int v12; // eax@13
	unsigned int v13; // edx@13
	struct D3DTEXTUREINFO *v14; // ecx@15
	int v15; // eax@15
	unsigned int v16; // edx@15
	unsigned int v17; // ebp@15
	int v18; // eax@15
	unsigned int v19; // edx@15
	unsigned int v20; // eax@16
	BOOL v21; // cf@20
	DWORD v22; // ebx@23
	int v23; // ebp@24
	DWORD v24; // edi@24
	DWORD v25; // ecx@25
	int v26; // esi@26
	char *v27; // eax@26
	__int16 v28; // di@27
	DWORD v29; // ebx@31
	int v30; // ebp@32
	DWORD v31; // edi@32
	DWORD v32; // ecx@33
	int v33; // esi@34
	char *v34; // eax@34
	int v35; // edi@35
	int v36; // eax@37
	LPDIRECTDRAWSURFACE4 a3a; // [sp+1Ch] [bp-A4h]@1
	int v39; // [sp+20h] [bp-A0h]@11
	int v40; // [sp+24h] [bp-9Ch]@10
	DWORD v41; // [sp+28h] [bp-98h]@12
	int v42; // [sp+2Ch] [bp-94h]@11
	int v43; // [sp+30h] [bp-90h]@13
	int v44; // [sp+34h] [bp-8Ch]@13
	int v45; // [sp+38h] [bp-88h]@10
	int v46; // [sp+3Ch] [bp-84h]@13
	int v47; // [sp+40h] [bp-80h]@13
	struct _DDSURFACEDESC2 a2a; // [sp+44h] [bp-7Ch]@1

	memset(&a2a, 0, sizeof(a2a));
	a3a = 0;
	a2a.dwSize = 124;
	a2a.dwWidth = a1;
	a2a.dwHeight = a2;
	if (a1 < 32 || a2 < 32)
		a3 = 0;
	qmemcpy(
		&a2a.ddpfPixelFormat,
		&ptr_ctx->graphicsAdapters[ptr_ctx->curGfxAdapt].D3DInfo[ptr_ctx->curAccelAdapt].Texture[ptr_ctx->curTexFormat],
		sizeof(a2a.ddpfPixelFormat));
	a2a.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT;
	a2a.ddsCaps.dwCaps = DDSCAPS_TEXTURE;
	if (ptr_ctx->flags & 0x80)
		a2a.ddsCaps.dwCaps2 = DDSCAPS2_TEXTUREMANAGE;
	else
		a2a.ddsCaps.dwCaps = DDSCAPS_TEXTURE | DDSCAPS_SYSTEMMEMORY;
	if (a3)
	{
		a2a.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT | DDSD_MIPMAPCOUNT;
		a2a.dwMipMapCount = a3 + 1;
		a2a.ddsCaps.dwCaps |= DDSCAPS_MIPMAP | DDSCAPS_COMPLEX;
	}
	DXCreateSurface(dxctx.ddraw, &a2a, &a3a);
	v6 = a3a->lpVtbl->Lock(a3a, 0, &a2a, 2048, 0);
	sub_40179E(v6);
	if (a6)
	{
		if (a6 == 2)
		{
			v22 = 0;
			v39 = 256 / a1;
			v7 = a2a.lpSurface;
			if (a2a.dwHeight)
			{
				v23 = a4;
				v24 = a2a.dwWidth;
				v40 = 256 / a2 << 9;
				do
				{
					v25 = 0;
					if (v24)
					{
						v26 = 2 * v39;
						v27 = (char *)v23;
						do
						{
							v28 = *(_WORD *)v27;
							v27 += v26;
							*v7 = v28;
							v24 = a2a.dwWidth;
							++v7;
							++v25;
						} while (v25 < a2a.dwWidth);
					}
					++v22;
					v23 += v40;
				} while (v22 < a2a.dwHeight);
			}
		}
		else if (a6 == 1)
		{
			v29 = 0;
			v39 = 256 / a1;
			v7 = a2a.lpSurface;
			if (a2a.dwHeight)
			{
				v30 = a4;
				v31 = a2a.dwWidth;
				v40 = 256 / a2 << 10;
				do
				{
					v32 = 0;
					if (v31)
					{
						v33 = 4 * v39;
						v34 = (char *)v30;
						do
						{
							v35 = *(_DWORD *)v34;
							v34 += v33;
							*(_DWORD *)v7 = v35;
							v31 = a2a.dwWidth;
							v7 += 2;
							++v32;
						} while (v32 < a2a.dwWidth);
					}
					++v29;
					v30 += v40;
				} while (v29 < a2a.dwHeight);
			}
		}
	}
	else
	{
		v8 = a2a.lpSurface;
		v45 = 0;
		v40 = 256 / a1;
		v7 = (_WORD *)(256 % a2);
		if (a2a.dwHeight)
		{
			v9 = (unsigned int *)a4;
			v10 = a5;
			v11 = ptr_ctx;
			v42 = a4;
			v39 = 256 / a2 << 10;
			do
			{
				v41 = 0;
				if (a2a.dwWidth)
				{
					do
					{
						v12 = *v9;
						v13 = *v9;
						LOBYTE(v46) = *v9 >> 24;
						LOBYTE(v43) = v13 >> 16;
						LOBYTE(v44) = BYTE1(v12);
						LOBYTE(v47) = v12;
						if (v10)
						{
							v10(&v43, &v44, &v47, &v46);
							v11 = ptr_ctx;
						}
						v14 = v11->graphicsAdapters[v11->curGfxAdapt].D3DInfo[v11->curAccelAdapt].Texture;
						v15 = (int)&v14[v11->curTexFormat];
						v16 = ((unsigned int)(unsigned __int8)v46 >> (8 - *(_BYTE *)(v15 + 47)) << *(_BYTE *)(v15 + 51)) | ((unsigned int)(unsigned __int8)v44 >> (8 - *(_BYTE *)(v15 + 45)) << *(_BYTE *)(v15 + 49)) | ((unsigned int)(unsigned __int8)v47 >> (8 - v14[v11->curTexFormat].bbpp) << *(_BYTE *)(v15 + 50));
						v17 = (unsigned int)(unsigned __int8)v43 >> (8 - *(_BYTE *)(v15 + 44));
						LOBYTE(v14) = *(_BYTE *)(v15 + 48);
						v18 = *(_DWORD *)(v15 + 32);
						v19 = (v17 << (char)v14) | v16;
						if (v18 > 0)
						{
							v20 = (unsigned int)(v18 + 7) >> 3;
							do
							{
								*v8++ = v19;
								v19 >>= 8;
								--v20;
							} while (v20);
							v11 = ptr_ctx;
						}
						v10 = a5;
						++v41;
						v9 += v40;
					} while (v41 < a2a.dwWidth);
				}
				v7 = (_WORD *)v39;
				v9 = (unsigned int *)(v39 + v42);
				v21 = v45++ + 1 < a2a.dwHeight;
				v42 += v39;
			} while (v21);
		}
	}
	v36 = a3a->lpVtbl->Unlock(a3a, 0);
	sub_40179E(v36);
	if (a3)
		sub_403297(&a2a, a3a, a4, a3);
	return a3a;
}
void LoadTextures(int numRoom, int numObj, int numBump)
{
	Log(2, "LoadTextures");

	dword_875144 = lvDataPtr;
	numTpages = 1;

	int v85 = 0;
	int depth = 4;

	struct D3DTEXTUREINFO* texf = &ptr_ctx->graphicsAdapters[ptr_ctx->curGfxAdapt]
		.D3DInfo[ptr_ctx->curAccelAdapt]
		.Texture[ptr_ctx->curTexFormat];

	if (texf->rbpp == 5 && texf->gbpp == 5 && texf->bbpp == 5 && texf->abpp == 1)
	{
		v85 = 2;
		depth = 2;

		int uncomp32 = freadDword();
		int comp32 = freadDword();
		if (useCompression)
			fseek(fp_level, comp32, SEEK_CUR);
		else
			fseek(fp_level, uncomp32, SEEK_CUR);

		int uncomp16 = freadDword();
		int comp16 = freadDword();
		texbuf = malloc(comp16);
		lvDataPtr = malloc(uncomp16);

		if (useCompression)
		{
			fread_ex(texbuf, comp16, 1, fp_level);
			Decompress(lvDataPtr, texbuf, comp16, uncomp16);
		}
		else
		{
			fread_ex(lvDataPtr, uncomp16, 1, fp_level);
		}
	}
	else
	{
		if (texf->rbpp == 8 && texf->gbpp == 8 && texf->bbpp == 8 && texf->abpp == 8)
			v85 = 1;

		int uncomp32 = freadDword();
		int comp32 = freadDword();
		texbuf = malloc(comp32);
		lvDataPtr = malloc(uncomp32);

		if (useCompression)
		{
			fread_ex(texbuf, comp32, 1, fp_level);
			Decompress(lvDataPtr, texbuf, comp32, uncomp32);

			int uncomp16 = freadDword();
			int comp16 = freadDword();
			fseek(fp_level, comp16, SEEK_CUR);
		}
		else
		{
			fread_ex(lvDataPtr, comp32, 1, fp_level);

			int uncomp16 = freadDword();
			int comp16 = freadDword();
			fseek(fp_level, uncomp16, SEEK_CUR);
		}
	}

	free(texbuf);

	Log(5, "RTPages %d", numRoom);

	int szRoom = numRoom * depth * TEXTURE_PAGE;
	void* bufRoom;
	AllocReadT(bufRoom, char, szRoom);
	S_LoadBar();

	if (numRoom > 0)
	{
		
	}
}

void LoadSprites()
{
	Log(2, "LoadSprites");

	readDword(); // SPR\0

	int numSpr = readDword();

	Alloc(sprites, SPRITE_STRUCT, numSpr);

	for (int i = 0; i < numSpr; i++)
	{
		sprites[i].tile = readWord() + 1;
		sprites[i].x = readByte();
		sprites[i].y = readByte();
		sprites[i].width = readWord();
		sprites[i].height = readWord();
		sprites[i].left = (readWord() + 1) / 256.0;
		sprites[i].top = (readWord() + 1) / 256.0;
		sprites[i].right = (readWord() - 1) / 256.0;
		sprites[i].bottom = (readWord() - 1) / 256.0;
	}

	int numSprSeqs = readDword();

	for (int i = 0; i < numSprSeqs; i++)
	{
		int spriteID = readDword();
		short negLength = readWord();
		short offset = readWord();
		if (spriteID >= NUMBER_OBJECTS)
		{
			static_objects[spriteID - 460].mesh_number = offset;
		}
		else
		{
			objects[spriteID].nmeshes = negLength;
			objects[spriteID].mesh_index = offset;
			objects[spriteID].loaded = 1;
		}
	}
}

void AdjustUV(int numTex)
{
	Log(2, "AdjustUV");

	S_Warn("[AdjustUV] - Unimplemented!\n");
}

void LoadTextureInfos()
{
	Log(2, "LoadTextureInfos");

	readDword(); // TEX\0

	int numObjTex = readDword();
	Log(5, "Texture Infos : %d", numObjTex);

	Alloc(object_textures, OBJECT_TEXTURE, numObjTex);

	struct tr4_object_texture tex;
	for (int i = 0; i < numObjTex; i++)
	{
		OnlyRead(&tex, tr4_object_texture, 1);

		object_textures[i].attribute = tex.Attribute;
		object_textures[i].tile_and_flag = tex.TileAndFlag & 0x7FFF;
		object_textures[i].new_flags = tex.NewFlags & 0x7FFF;

		for(int j = 0; j < 4; j++)
		{
			object_textures[i].vertices[j].x = tex.Vertices[j].Xpixel / 256.0;
			object_textures[i].vertices[j].y = tex.Vertices[j].Ypixel / 256.0;
		}
	}

	AdjustUV(numObjTex);

	Log(5, "Created %d Texture Pages", numTpages - 1);
}

void sub_4A6AB0()
{
	S_Warn("[sub_4A6AB0] - Unimplemented!\n");
}

void MallocD3DLights()
{
	if (NumRoomLights > 21)
	{
		Log(1, "MAX Room Lights of %d Exceeded - %d", 21, NumRoomLights);
	}

	dword_87B0F0 = game_malloc(168 * NumRoomLights);
	dword_87B0F4 = game_malloc(2688); // todo find the struct
}

void reset_cutseq_vars()
{
	cutseq_num = 0;
	cutseq_trig = 0;
	GLOBAL_playing_cutseq = 0;
	GLOBAL_cutseq_frame = 0;
	SetFadeClip(0, 1);
}

int unknown_libname_1()
{
	S_Warn("[unknown_libname_1] - Unimplemented!\n");
	return 0;
}

void sub_490590()
{
	S_Warn("[sub_490590] - Unimplemented!\n");
}

void sub_4BFD70()
{
	S_Warn("[sub_4BFD70] - Unimplemented!\n");
}

void sub_4779B0()
{
	S_Warn("[sub_4779B0] - Unimplemented!\n");
}

void InitBinocularGraphics()
{
	S_Warn("[InitBinocularGraphics] - Unimplemented!\n");
}

void InitTargetGraphics()
{
	S_Warn("[InitTargetGraphics] - Unimplemented!\n");
}

void sub_477880()
{
	memset(flipmap, 0, 255 * sizeof(int));
	memset(flip_stats, 0, 255 * sizeof(int));
	flipeffect = -1;
	memset(cd_flags, 0, 136);
	flip_status = 0;
	IsAtmospherePlaying = 0;
	camera.underwater = 0;
}

void __cdecl sub_456900(struct ITEM_INFO *item)
{
	if (room[item->room_number].flags & RF_FILL_WATER)
	{
		lara.water_status = LW_UNDERWATER;
		item->fallspeed = 0;
		item->goal_anim_state = STATE_LARA_UNDERWATER_STOP;
		item->current_anim_state = STATE_LARA_UNDERWATER_STOP;
		item->anim_number = ANIMATION_LARA_UNDERWATER_IDLE;
		item->frame_number = anims[ANIMATION_LARA_UNDERWATER_IDLE].frame_base;
	}
	else
	{
		lara.water_status = LW_ABOVE_WATER;
		item->goal_anim_state = STATE_LARA_STOP;
		item->current_anim_state = STATE_LARA_STOP;
		item->anim_number = ANIMATION_LARA_STAY_SOLID;
		item->frame_number = anims[ANIMATION_LARA_STAY_SOLID].frame_base;
	}
}

void sub_473210(int a1)
{
	if (lara.item_number != -1)
	{
		lara_item->data = &lara;
		lara_item->looked_at = 0;
		if (a1)
		{
			
		}

	}
}

void SetupGame()
{
	S_Warn("[SetupGame] - Unimplemented!\n");
}

void CreateD3DLights()
{
	
}

void LoadLevel(const char* filename)
{
	Log(5, "Begin LoadLevel");

	FreeLevel();

	numTpages = 1;
	dword_D99DA8 = 0;
	dword_D99DAC = 0;
	dword_D99DC0 = 0;
	dword_D99DC4 = 0;
	//byte_D99DCC[0] = 0;
	texbuf = NULL;

	lvDataPtr = 0;
	fp_level = FileOpen(filename);

	if (fp_level)
	{
		int version = freadDword();
		int numRoomTex = freadWord();
		int numObjTex = freadWord();
		int numBumpTex = freadWord();

		S_InitLoadBar(numObjTex + numBumpTex + numRoomTex + 20);
		S_LoadBar();

		Log(7, "Process Level Data");
		LoadTextures(numRoomTex, numObjTex, numBumpTex);
		fseek(fp_level, 0x319acf, SEEK_SET);
		LaraDrawType = freadWord() + 1;
		WeatherType = freadWord();
		freadBytes(28); // padding
		Log(0, "%x", ftell(fp_level));
		int uncompSize = freadDword();
		int compSize = freadDword();
		lvDataPtr = malloc(uncompSize);
		lvDataPtr_orig = lvDataPtr;
		Log(0, "%x", ftell(fp_level));
		fread_ex(lvDataPtr, uncompSize, 1, fp_level);

		Log(5, "Rooms");
		LoadRooms();
		S_LoadBar();

		Log(5, "Objects");
		LoadObjects();
		S_LoadBar();

		LoadSprites();
		S_LoadBar();

		LoadCameras();
		S_LoadBar();

		LoadSoundEffects();
		S_LoadBar();

		LoadBoxes();
		S_LoadBar();

		LoadAnimatedTextures();
		S_LoadBar();

		LoadTextureInfos();
		S_LoadBar();

		char* backup = lvDataPtr;
		int numItems = readDword();
		lvDataPtr += 24 * numItems;

		LoadAIObjects();
		char* backup2 = lvDataPtr;
		lvDataPtr = backup;

		LoadItems();
		lvDataPtr = backup2;

		S_LoadBar();
		S_LoadBar();

		LoadDemoData();
		S_LoadBar();

		if (ACMInited && !ptr_ctx->opt_DisableSound)
			LoadSamples();

		free(lvDataPtr_orig);

		S_LoadBar();

		for(int i = WATERFALL1; i <= WATERFALLSS2; i++)
		{
			if (objects[i].loaded)
			{
				struct OBJECT_TEXTURE* tex = &object_textures[mesh_vbufs[objects[i].mesh_index]->field1[4]];
				waterfall_textures[i] = tex;
				waterfall_y[i] = tex->vertices[0].y;
			}
		}

		S_LoadBar();

		sub_4A6AB0();
		S_LoadBar();

		MallocD3DLights();
		CreateD3DLights();
		SetupGame();
		S_LoadBar();
		SetFadeClip(0, 1);
		reset_cutseq_vars();

		if (gfCurrentLevel == LVL5_STREETS_OF_ROME)
			find_a_fucking_item(ANIMATING10)->mesh_bits = 11;

		if (gfCurrentLevel == LVL5_OLD_MILL)
			find_a_fucking_item(ANIMATING16)->mesh_bits = 1;

		if (objects[MONITOR_SCREEN].loaded)
		{
			short* mesh = meshes[objects[MONITOR_SCREEN].mesh_index];
			int v12 = *((int*)mesh + 4);
			int v13 = mesh[7];
			int v10 = 0;
			if (v13 > 0)
			{
				BYTE* v14 = (BYTE*)(v12 + 10);

				while (!(*v14 & 1))
				{
					v10++;
					v14 += 12;
					if (v10 >= v13)
						goto LABEL_20;
				}
				int v15 = 3 * v10;
				*(BYTE*)(v12 + 4 * v15 + 10) &= 0xFE;
				dword_87497C = &object_textures[*(WORD*)(v12 + 4 * v15 + 8) & 0x7FFF];
				flt_874980 = dword_87497C->vertices[0].x;
			}
		}

		LABEL_20:
		FileClose(fp_level);
		unknown_libname_1();
		sub_490590();
		sub_4BFD70();
	}

	sub_491DA0(gfResidentCut[0], gfResidentCut[1], gfResidentCut[2], gfResidentCut[3]);
	dword_874968 = 0;
	//_endthreadex(1u); todo what
}

BYTE byte_87B81C;
DWORD dword_8751CC;
DWORD dword_8751C8;

const char* screens[] =
{
	"SCREENS\\STORY1.STR",
	"SCREENS\\NXG.STR",
	"SCREENS\\STORY2.STR",
	"SCREENS\\GALLERY.STR",
	"SCREENS\\SCREENS.STR"
};

LPDIRECTDRAWSURFACE4 surf_screen;

void LoadScreen(int a2, int num)
{
	FILE* v3; // esi@2
	int v4; // ST24_4@3
	void* v5; // ebx@3
	DWORD v6; // edx@3
	__int16 *v7; // ecx@3
	signed int v8; // esi@3
	__int16 v9; // ax@4
	DDPIXELFORMAT v10; // [sp+8h] [bp-9Ch]@1
	DDSURFACEDESC2 a2a; // [sp+28h] [bp-7Ch]@1

	memset(&a2a, 0, sizeof(a2a));
	memset(&v10, 0, sizeof(v10));
	a2a.dwSize = 124;
	a2a.dwWidth = 640;
	a2a.dwHeight = 480;
	v10.dwSize = 32;
	v10.dwFlags = DDPF_RGB;
	v10.dwRGBBitCount = 16;
	v10.dwRBitMask = 0xF800;
	v10.dwGBitMask = 0x7E0;
	v10.dwBBitMask = 0x1F;
	v10.dwRGBAlphaBitMask = 0;
	qmemcpy(&a2a.ddpfPixelFormat, &v10, sizeof(a2a.ddpfPixelFormat));
	a2a.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT;
	a2a.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY;
	if (DXCreateSurface(ptr_ctx->ddraw, &a2a, &surf_screen) && (v3 = FileOpen(screens[num])) != 0)
	{
		v5 = malloc(0x96000u);
		fseek(v3, 614400 * a2, 0);
		fread_ex(v5, 0x96000u, 1u, v3);
		fclose(v3);
		memset(&a2a, 0, sizeof(a2a));
		a2a.dwSize = 124;
		surf_screen->lpVtbl->Lock(surf_screen, NULL, &a2a, DDLOCK_WAIT | DDLOCK_NOSYSLOCK, 0);
		v6 = a2a.lpSurface;
		v7 = (__int16 *)v5;
		v8 = 307200;
		do
		{
			v9 = *v7;
			++v7;
			v6 += 2;
			--v8;
			*(_WORD *)(v6 - 2) = v9 & 0x1F | 2 * (v9 & 0xFFE0);
		} while (v8);
		surf_screen->lpVtbl->Unlock(surf_screen, NULL);
		free(v5);
		byte_87B81C = 1;
	}
	else
	{
		Log(0, "WHORE!");
	}
}

_DWORD *sub_49D220()
{
	S_Warn("[sub_49D220] - Unimplemented!\n");
	return 0;
}

void sub_4BA100()
{
	S_Warn("[sub_4BA100] - Unimplemented!\n");
}

void sub_4D3D90(int *a1, int *a2)
{
	*a1 = dword_D9BB8C;
	*a2 = dword_D9BB88;
}

void sub_4ACAB0()
{
	if (dxctx.flags & 0x80)
	{
		ptr_ctx->buf_back->lpVtbl->Blt(ptr_ctx->buf_back, NULL, surf_screen, NULL, DDBLT_WAIT, 0);
	}
	else
	{
		DDSURFACEDESC2 surf;
		memset(&surf, 0, sizeof(surf));
		surf.dwSize = 124;
		surf_screen->lpVtbl->Lock(surf_screen, NULL, &surf, DDLOCK_WAIT | DDLOCK_NOSYSLOCK, NULL);

		int w, h;
		sub_4D3D90(&w, &h);

		S_Warn("[sub_4ACAB0] - Unimplemented condition!\n");

		surf_screen->lpVtbl->Unlock(surf_screen, NULL);
	}
}

void sub_4BA090(signed int a1, float **a2)
{
	S_Warn("[sub_4BA090] - Unimplemented!\n");
}
DWORD ThreadId;
DWORD dword_874970;
DWORD dword_874974;
void S_LoadLevelFile(int Name)
{
	Log(2, "S_LoadLevelFile");

	if (!byte_87B81C)
	{
		int v1 = Name;
		if (!Name)
		{
			if (dword_8751CC)
			{
				v1 = dword_8751C8++ % 3 + 15;
			}
			else
			{
				dword_8751CC = 1;
				v1 = -2;
			}
		}
		LoadScreen(v1 + 2, 4);
	}

	char filename[80];
	strcpy(filename, &gfFilenameWad[gfFilenameOffset[Name]]);
	dword_8FBDC0 = 0;
	strcat(filename, ".TRC");
	LoadLevel(filename);
	for(int i = 0; i < 4; i++)
	{
		ptr_BeginScene();
		sub_49D220();
		sub_4BA100();
		sub_4ACAB0();
		//sub_4BA090();


		sub_4D3150();
	}
	/*if (byte_87B81C == 1)
		sub_4025B3();
	dword_874968 = 1;
	dword_874970 = 0;
	dword_874974 = _beginthreadex(0, 0, LoadLevel, filename, 0, &ThreadId);
	while (dword_874968)
	{
		if (dxctx.flags & 0x80 && dword_8FBDC0)
			sub_402F0E();
	}
	if (dxctx.flags & 0x80 && !sub_402F0E())
	{
		while (!sub_402F0E())
			;
	}
	dword_517B88 = 0;*/
	S_Warn("[S_LoadLevelFile] - Unimplemented!\n");
}

void FreeLights()
{
	;
}

void FreeLevel()
{
	S_Warn("[FreeLevel] - Unimplemented!\n");
}

