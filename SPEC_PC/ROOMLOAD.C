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

short sub_4916C0()
{
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

