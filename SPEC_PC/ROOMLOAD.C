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

long AnimFilePos;
long AnimFileLen;
short* floor_data;
short* mesh_base;
FILE* fp_level;
char* lvDataPtr;
DWORD num_items;
DWORD dword_51CAC0[32];

#define AllocT(d, s, n) d = (s*)game_malloc(sizeof(s) * n)
#define AllocReadT(d, s, n) AllocT(d, s, n);OnlyReadT(d, s, n)
#define OnlyReadT(d, s, n) readBytes(d, sizeof(s) * n)

#define Alloc(d, s, n) d = (struct s*)game_malloc(sizeof(struct s) * n)
#define AllocRead(d, s, n) Alloc(d, s, n);OnlyRead(d, s, n)
#define OnlyRead(d, s, n) readBytes(d, sizeof(struct s) * n)

#define AddPtr(p, t, n) p = (t*)((char*)(p) + (ptrdiff_t)(n)); 

inline uint8_t readByte()
{
	const uint8_t ret = *(uint8_t*)lvDataPtr;
	lvDataPtr += 1;
	return ret;
}

inline int8_t readSByte()
{
	const int8_t ret = *(int8_t*)lvDataPtr;
	lvDataPtr += 1;
	return ret;
}

inline uint16_t readWord()
{
	const uint16_t ret = *(uint16_t*)lvDataPtr;
	lvDataPtr += 2;
	return ret;
}

inline int16_t readSWord()
{
	const int16_t ret = *(int16_t*)lvDataPtr;
	lvDataPtr += 2;
	return ret;
}

inline uint32_t readDword()
{
	const uint32_t ret = *(uint32_t*)lvDataPtr;
	lvDataPtr += 4;
	return ret;
}

inline int32_t readSDword()
{
	const int32_t ret = *(int32_t*)lvDataPtr;
	lvDataPtr += 4;
	return ret;
}

inline void readBytes(void* dst, unsigned int count)
{
	qmemcpy(dst, lvDataPtr, count);
	lvDataPtr += count;
}

void FreeItemsShit(int num)
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
			curItem->active = 0;
			curItem++;
		} while (v1 < num);
		curItem->next_item = -1;
	}
}

void sub_43E380()
{
	memset(dword_51CAC0, 0, 32 * sizeof(DWORD));
}

void LoadItems()
{
	Log(2, "LoadItems");

	num_items = readDword();

	if (num_items == 0) return;
	Alloc(items, ITEM_INFO, 256);
	level_items = num_items;
	sub_43E380();

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
				&& !(gfCurrentLevel == 4 && (r == 19 || r == 23 || r == 16)))
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

	number_spotcams = readWord();

	if (number_spotcams != 0)
	{
		OnlyRead(SpotCam, SPOTCAM, number_spotcams);
	}
}

void LoadBoxes()
{
	Log(2, "LoadBoxes");

	number_boxes = readDword();
	AllocRead(boxes, box_info, 8);

	int numOverlaps = readDword();
	AllocReadT(overlap, uint16_t, numOverlaps);

	S_Warn("[LoadBoxes] - Zone loading unimplemented!\n");

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
void ReadRoom(struct room_info *rooms, /*tr5_room*/struct room_info *roomData)
{
	AddPtr(roomData->door, short, roomData + 1);
	AddPtr(roomData->floor, struct FLOOR_INFO, roomData + 1);
	AddPtr(roomData->light, struct LIGHTINFO, roomData + 1);
	AddPtr(roomData->mesh, struct MESH_INFO, roomData + 1);
	AddPtr(roomData->Separator4, void, roomData + 1);	
	AddPtr(roomData->LayerOffset, struct tr5_room_layer, roomData + 1);
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

short sub_4916C0()
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

		ReadRoom(&room[i], roomData);
	}

	number_rooms = numRooms;

	S_Warn("[sub_4916C0] - Unimplemented!\\n");
	return 0;
}

int sub_4774D0()
{
	S_Warn("[sub_4774D0] - Unimplemented!\\n");
	return 0;
}


void LoadRooms()
{
	Log(2, "LoadRooms");

	wibble = 0;
	NumRoomLights = 0;
	dword_7E7FE8 = 0;

	sub_4916C0();
	sub_4774D0();

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

void S_LoadLevelFile(int Name)
{
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

