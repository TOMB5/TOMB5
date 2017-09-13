#include "ROOMLOAD.H"
#include "SPECIFIC.H"
#include "ITEMS.H"
#include "CONTROL.H"
#include "malloc.h"
#include "DRAW.H"
#include "BOX.H"
#include "GAMEFLOW.H"
#include "GAME.H"

long AnimFilePos;
long AnimFileLen;
short* floor_data;
short* mesh_base;
FILE* fp_level;
char* lvDataPtr;
DWORD num_items;
DWORD dword_51CAC0[32];

inline uint8_t readByte(char** ptr)
{
	const uint8_t ret = *(uint8_t*)*ptr;
	*ptr += 1;
	return ret;
}

inline uint16_t readWord(char** ptr)
{
	const uint16_t ret = *(uint16_t*)*ptr;
	*ptr += 2;
	return ret;
}

inline int16_t readSWord(char** ptr)
{
	const int16_t ret = *(int16_t*)*ptr;
	*ptr += 2;
	return ret;
}

inline uint32_t readDword(char** ptr)
{
	const uint32_t ret = *(uint32_t*)*ptr;
	*ptr += 4;
	return ret;
}

inline int32_t readSDword(char** ptr)
{
	const int32_t ret = *(int32_t*)*ptr;
	*ptr += 4;
	return ret;
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
	sub_4DEB10(2, "LoadItems");

	num_items = readDword(&lvDataPtr);

	if (num_items == 0) return;

	items = (struct ITEM_INFO*)game_malloc(256 * sizeof(struct ITEM_INFO));
	level_items = num_items;
	sub_43E380();

	for (int it = 0; it < num_items; it++)
	{
		struct ITEM_INFO* item = &items[it];

		item->object_number = readWord(&lvDataPtr);
		item->room_number = readWord(&lvDataPtr);
		item->pos.x_pos = readDword(&lvDataPtr);
		item->pos.y_pos = readDword(&lvDataPtr);
		item->pos.z_pos = readDword(&lvDataPtr);
		item->pos.y_rot = readWord(&lvDataPtr);
		item->shade = readWord(&lvDataPtr);
		item->trigger_flags = readWord(&lvDataPtr);
		item->flags = readWord(&lvDataPtr);
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

