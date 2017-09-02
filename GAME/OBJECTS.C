#include "OBJECTS.H"
#include "SPECIFIC.H"
#include "CONTROL.H"
#include "EFFECTS.H"
#include <stddef.h>

struct BITE_INFO EnemyBites[9];
int AnimatingWaterfallsVOffset;

void HybridCollision(short item_num, struct ITEM_INFO* laraitem, struct COLL_INFO* coll)
{
	S_Warn("[HybridCollision] - Unimplemented!\n");
}

void DrawBaddieGunFlash(struct ITEM_INFO* item)
{
	S_Warn("[DrawBaddieGunFlash] - Unimplemented!\n");
}

void CutsceneRopeControl(short item_number)
{
	S_Warn("[CutsceneRopeControl] - Unimplemented!\n");
}

void ControlXRayMachine(short item_number)
{
	S_Warn("[ControlXRayMachine] - Unimplemented!\n");
}

void ParallelBarsCollision(short item_num, struct ITEM_INFO* l, struct COLL_INFO* coll)
{
	S_Warn("[ParallelBarsCollision] - Unimplemented!\n");
}

void TightRopeCollision(short item_num, struct ITEM_INFO* l, struct COLL_INFO* coll)
{
	S_Warn("[TightRopeCollision] - Unimplemented!\n");
}

void ControlWaterfall(short item_number)//4FBC4(<), 50028(<) (F)
{
	struct ITEM_INFO* item = &items[item_number];
	TriggerActive(item);

	if (item_number != 0)
	{
		item->status = 1;

		if (item->trigger_flags == 0x29C)
		{
			SoundEffect(344, &item->pos, 0);
		}
		else if (item->trigger_flags == 0x309)
		{
			SoundEffect(79, &item->pos, 0);
		}
	}
	else
	{
		if (item->trigger_flags == 2 || item->trigger_flags == 0x29C)
		{
			item->status = 3;
		}
	}
}

void AnimateWaterfalls()
{
	S_Warn("[AnimateWaterfalls] - Unimplemented!\n");
}

void ControlTriggerTriggerer(short item_number)
{
	S_Warn("[ControlTriggerTriggerer] - Unimplemented!\n");
}

void PoleCollision(short item_num, struct ITEM_INFO* l, struct COLL_INFO* coll)
{
	S_Warn("[PoleCollision] - Unimplemented!\n");
}

void ControlAnimatingSlots(short item_number)
{
	S_Warn("[ControlAnimatingSlots] - Unimplemented!\n");
}

void BridgeTilt2Ceiling(struct ITEM_INFO* item, long x, long y, long z, long* height)//4F0FC(<), 4F560(<) (F)
{
	long level = item->pos.y_pos + (GetOffset(item, x, z) >> 1);

	if (level >= y)
	{
		*height = level;
	}
}

void BridgeTilt2Floor(struct ITEM_INFO* item, long x, long y, long z, long* height)//4F090(<), 4F4F4(<) (F)
{
	long level = item->pos.y_pos + (GetOffset(item, x, z) >> 1);

	if (level >= y)
	{
		*height = level;
		height_type = 0;
		OnObject = 1;
	}
}

void BridgeTilt1Ceiling(struct ITEM_INFO* item, long x, long y, long z, long* height)//4F038(<), 4F49C(<) (F)
{
	long level = item->pos.y_pos + (GetOffset(item, x, z) >> 2);

	if (level >= y)
	{
		*height = level;
	}
}

long GetOffset(struct ITEM_INFO* item, long x, long z)
{
	S_Warn("[GetOffset] - Unimplemented!\n");
	return 0;
}

void BridgeTilt1Floor(struct ITEM_INFO* item, long x, long y, long z, long* height)//4EFCC(<), 4F430(<) (F)
{
	long level = item->pos.y_pos + (GetOffset(item, x, z) >> 2);

	if (level >= y)
	{
		*height = level;
		height_type = 0;
		OnObject = 1;
	}
}

void BridgeFlatCeiling(struct ITEM_INFO* item, long x, long y, long z, long* height)//4EF58(<), 4F3BC(<) (F)
{
	if (item->pos.y_pos >= y)
	{
		*height = item->pos.y_pos + 256;
	}
}

void BridgeFlatFloor(struct ITEM_INFO* item, long x, long y, long z, long* height)//4EF1C(<), 4F380(<) (F)
{
	if (item->pos.y_pos >= y)
	{
		*height = item->pos.y_pos;
		height_type = 0;
		OnObject = 1;
	}
}

void SmashObjectControl(short item_number)//4EEF8(<), 4F35C(<) (F)
{
	SmashObject(item_number << 16);
}

void SmashObject(short item_number)//4EDB0, 4F214
{
	S_Warn("[SmashObject] - Unimplemented!\n");
}

void EarthQuake(short item_number)
{
	S_Warn("[EarthQuake] - Unimplemented!\n");
}
