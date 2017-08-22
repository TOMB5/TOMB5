#include "OBJECTS.H"
#include "SPECIFIC.H"

struct BITE_INFO EnemyBites[9];
int AnimatingWaterfallsVOffset;

void HybridCollision(short item_num, struct ITEM_INFO *laraitem, struct COLL_INFO *coll)
{
	S_Warn("[HybridCollision] - Unimplemented!\\n");
}

void DrawBaddieGunFlash(struct ITEM_INFO *item)
{
	S_Warn("[DrawBaddieGunFlash] - Unimplemented!\\n");
}

void CutsceneRopeControl(short item_number)
{
	S_Warn("[CutsceneRopeControl] - Unimplemented!\\n");
}

void ControlXRayMachine(short item_number)
{
	S_Warn("[ControlXRayMachine] - Unimplemented!\\n");
}

void ParallelBarsCollision(short item_num, struct ITEM_INFO *l, struct COLL_INFO *coll)
{
	S_Warn("[ParallelBarsCollision] - Unimplemented!\\n");
}

void TightRopeCollision(short item_num, struct ITEM_INFO *l, struct COLL_INFO *coll)
{
	S_Warn("[TightRopeCollision] - Unimplemented!\\n");
}

void ControlWaterfall(short item_number)
{
	S_Warn("[ControlWaterfall] - Unimplemented!\\n");
}

void AnimateWaterfalls()
{
	S_Warn("[AnimateWaterfalls] - Unimplemented!\\n");
}

void ControlTriggerTriggerer(short item_number)
{
	S_Warn("[ControlTriggerTriggerer] - Unimplemented!\\n");
}

void PoleCollision(short item_num, struct ITEM_INFO *l, struct COLL_INFO *coll)
{
	S_Warn("[PoleCollision] - Unimplemented!\\n");
}

void ControlAnimatingSlots(short item_number)
{
	S_Warn("[ControlAnimatingSlots] - Unimplemented!\\n");
}

void BridgeTilt2Ceiling(struct ITEM_INFO *item, long x, long y, long z, long *height)
{
	S_Warn("[BridgeTilt2Ceiling] - Unimplemented!\\n");
}

void BridgeTilt2Floor(struct ITEM_INFO *item, long x, long y, long z, long *height)
{
	S_Warn("[BridgeTilt2Floor] - Unimplemented!\\n");
}

void BridgeTilt1Ceiling(struct ITEM_INFO *item, long x, long y, long z, long *height)
{
	S_Warn("[BridgeTilt1Ceiling] - Unimplemented!\\n");
}

long GetOffset(struct ITEM_INFO *item, long x, long z)
{
	S_Warn("[GetOffset] - Unimplemented!\\n");
	return 0;
}

void BridgeTilt1Floor(struct ITEM_INFO *item, long x, long y, long z, long *height)
{
	S_Warn("[BridgeTilt1Floor] - Unimplemented!\\n");
}

void BridgeFlatCeiling(struct ITEM_INFO *item, long x, long y, long z, long *height)
{
#if 0
	int v1 = item->pos.y_pos;
	y = v1 < y ? 1 : 0;
	if(y != 0)
	{
		v1 += 0x100;
		int v0 = arg_10;
		*v0 = v1;
	}
#endif
	S_Warn("[BridgeFlatCeiling] - Unimplemented!\\n");
}

void BridgeFlatFloor(struct ITEM_INFO *item, long x, long y, long z, long *height)
{
	S_Warn("[BridgeFlatFloor] - Unimplemented!\\n");
}

void SmashObjectControl(short item_number)//4EEF8(<), 4F35C(<) (F)
{
	SmashObject(item_number << 16);
}

void SmashObject(short item_number)//4EDB0, 4F214
{
	S_Warn("[SmashObject] - Unimplemented!\\n");
}

void EarthQuake(short item_number)
{
	S_Warn("[EarthQuake] - Unimplemented!\\n");
}
