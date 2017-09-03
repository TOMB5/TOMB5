#include "COLLIDE.H"

#include "CONTROL.H"
#include "ITEMS.H"
#include "LARA.H"
#include "SPECIFIC.H"

#include <stddef.h>

long zfront;
long xfront;
short GlobalCollisionBounds[6];

char LM[] =
{
	0, 1, 2, 3, 4, 5, 6, 7, 9, 10, 11, 12, 13, 14, 8
};

void TestForObjectOnLedge(struct ITEM_INFO* item, struct COLL_INFO* coll)//2A940, 2AB68
{
	S_Warn("[TestForObjectOnLedge] - Unimplemented!\n");
}

void TriggerLaraBlood()//2A838, 2AA60
{
	S_Warn("[TriggerLaraBlood] - Unimplemented!\n");
}

void GenericSphereBoxCollision(short item_num, struct ITEM_INFO* laraitem, struct COLL_INFO* coll)//2A5EC, 2A814
{
	S_Warn("[GenericSphereBoxCollision] - Unimplemented!\n");
}

int ItemPushLaraStatic(struct ITEM_INFO* laraitem, short* bounds, struct PHD_3DPOS* pos, struct COLL_INFO* coll)//2A2D8, 2A500
{
	S_Warn("[ItemPushLaraStatic] - Unimplemented!\n");
	return 0;
}

int TestBoundsCollideStatic(short* bounds, struct PHD_3DPOS* pos, long radius)//2A140, 2A368
{
	S_Warn("[TestBoundsCollideStatic] - Unimplemented!\n");
	return 0;
}

void TrapCollision(short item_num, struct ITEM_INFO* laraitem, struct COLL_INFO* coll)//2A098, 2A2C0
{
	S_Warn("[TrapCollision] - Unimplemented!\n");
}

void AIPickupCollision(short item_num, struct ITEM_INFO* laraitem, struct COLL_INFO* coll)//2A03C, 2A264
{
	S_Warn("[AIPickupCollision] - Unimplemented!\n");
}

void CreatureCollision(short item_num, struct ITEM_INFO* laraitem, struct COLL_INFO* coll)//29E10, 2A024
{
	S_Warn("[CreatureCollision] - Unimplemented!\n");
}

void LaraBaddieCollision(struct ITEM_INFO* laraitem, struct COLL_INFO* coll)//29A44, 29C58
{
	S_Warn("[LaraBaddieCollision] - Unimplemented!\n");
}

void ShiftItem(struct ITEM_INFO* item, struct COLL_INFO* coll)//7BEEC(<), 7DF30(<) (F)
{
	item->pos.x_pos += coll->shift.x;
	item->pos.y_pos += coll->shift.y;
	item->pos.z_pos += coll->shift.z;
	coll->shift.x = coll->shift.y = coll->shift.z = 0;
}

int GetCollisionInfo(struct COLL_INFO* coll, long xpos, long ypos, long zpos, short room_number, long objheight)
{
	S_Warn("[GetCollisionInfo] - Unimplemented!\n");
	return 0;
}

void UpdateLaraRoom(struct ITEM_INFO* item, int height)//7C58C(<), 7E5D0(<) (F)
{
	short room_number = item->room_number;
	struct FLOOR_INFO* floor = GetFloor(item->pos.x_pos, item->pos.y_pos + height, item->pos.z_pos, &room_number);

	item->floor = GetHeight(floor, item->pos.x_pos, item->pos.y_pos + height, item->pos.z_pos);
	if (item->room_number != room_number)
	{
		ItemNewRoom(lara.item_number, room_number);
	}
}

void ObjectCollision(short item_num, struct ITEM_INFO* lara_item, struct COLL_INFO* coll)
{
	S_Warn("[ObjectCollision] - Unimplemented!\n");
}

int TestLaraPosition(short* bounds, struct ITEM_INFO* item, struct ITEM_INFO* lara_item)
{
	S_Warn("[TestLaraPosition] - Unimplemented!\n");
	return 0;
}

int MoveLaraPosition(struct PHD_VECTOR* vector, struct ITEM_INFO* item, struct ITEM_INFO* lara_item)
{
	S_Warn("[MoveLaraPosition] - Unimplemented!\n");
	return 0;
}

