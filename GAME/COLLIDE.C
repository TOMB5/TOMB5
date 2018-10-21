#include "COLLIDE.H"

#include "CONTROL.H"
#include "ITEMS.H"
#include "LARA.H"
#include "OBJECTS.H"
#include "SPECIFIC.H"
#include "SPECTYPES.H"
#include <stddef.h>
#include "TOMB4FX.H"
#include "SPHERE.H"

long zfront;
long xfront;
short GlobalCollisionBounds[6];

char LM[] =
{
	LJ_HIPS,
	LJ_LTHIGH,
	LJ_LSHIN,
	LJ_LFOOT,
	LJ_RTHIGH,
	LJ_RSHIN,
	LJ_RFOOT,
	LJ_TORSO,
	LJ_RINARM,
	LJ_ROUTARM,
	LJ_RHAND,
	LJ_LINARM,
	LJ_LOUTARM,
	LJ_LHAND,
	LJ_HEAD,
};

void TestForObjectOnLedge(struct ITEM_INFO* item, struct COLL_INFO* coll)//2A940, 2AB68
{
	UNIMPLEMENTED();
}

void TriggerLaraBlood()//2A838, 2AA60 (F)
{
	struct PHD_VECTOR vec;
	int node = 1;
	int i;
	for(i = 0; i < 15; i++)
	{
		if (node & lara_item->touch_bits)
		{
			vec.x = (GetRandomControl() & 0x1F) - 16;
			vec.y = (GetRandomControl() & 0x1F) - 16;
			vec.z = (GetRandomControl() & 0x1F) - 16;

			GetLaraJointPos(&vec, LM[i]);
			DoBloodSplat(vec.x, vec.y, vec.z, (GetRandomControl() & 7) + 8, 2 * GetRandomControl(), lara_item->room_number);
		}

		node <<= 1;
	}
}

void GenericSphereBoxCollision(short item_num, struct ITEM_INFO* laraitem, struct COLL_INFO* coll)//2A5EC, 2A814
{
	UNIMPLEMENTED();
}

int ItemPushLaraStatic(struct ITEM_INFO* laraitem, short* bounds, struct PHD_3DPOS* pos, struct COLL_INFO* coll)//2A2D8, 2A500
{
	UNIMPLEMENTED();
	return 0;
}

int TestBoundsCollideStatic(short* bounds, struct PHD_3DPOS* pos, long radius)//2A140, 2A368
{
	UNIMPLEMENTED();
	return 0;
}

void AIPickupCollision(short item_num, struct ITEM_INFO* laraitem, struct COLL_INFO* coll)//2A03C(<), 2A264 (F)
{
	struct ITEM_INFO* item = &items[item_num];

	if (item->object_number == SWITCH_TYPE7 && !(item->mesh_bits & 1))
	{
		item->active = TRUE;
		item->status = ITEM_ACTIVE;
	}
}

void TrapCollision(short item_num, struct ITEM_INFO* laraitem, struct COLL_INFO* coll)//2A098(<), 2A2C0 (F)
{
	struct ITEM_INFO* item = &items[item_num];

	if (item->status == ITEM_ACTIVE)
	{
		if (TestBoundsCollide(item, laraitem, coll->radius) == 0)
		{
			return;
		}

		ObjectCollision(item_num, lara_item, coll);
	}
	else if(item->status == ITEM_INVISIBLE)
	{
		//0x2A110
		ObjectCollision(item_num, lara_item, coll);
	}

	//0x2A128
}

void CreatureCollision(short item_num, struct ITEM_INFO* laraitem, struct COLL_INFO* coll)//29E10, 2A024
{
	UNIMPLEMENTED();
}

void LaraBaddieCollision(struct ITEM_INFO* laraitem, struct COLL_INFO* coll)//29A44, 29C58
{
	UNIMPLEMENTED();
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
	UNIMPLEMENTED();
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

void ObjectCollision(short item_num, struct ITEM_INFO* lara_item, struct COLL_INFO* coll)// (F)
{
	struct ITEM_INFO* item = &items[item_num];

	if (TestBoundsCollide(&items[item_num], lara_item, coll->radius) && TestCollision(item, lara_item))
	{
		if (coll->enable_baddie_push)
			ItemPushLara(item, lara_item, coll, 0, 1);
	}
}

int TestLaraPosition(short* bounds, struct ITEM_INFO* item, struct ITEM_INFO* lara_item)
{
	UNIMPLEMENTED();
	return 0;
}

int MoveLaraPosition(struct PHD_VECTOR* vector, struct ITEM_INFO* item, struct ITEM_INFO* lara_item)
{
	UNIMPLEMENTED();
	return 0;
}

int TestBoundsCollide(struct ITEM_INFO* item, struct ITEM_INFO* laraitem, long radius)
{
	UNIMPLEMENTED();
	return 0;
}

int ItemPushLara(struct ITEM_INFO* item, struct ITEM_INFO* laraitem, struct COLL_INFO* coll, int spaz, int big_push)
{
	UNIMPLEMENTED();
	return 0;
}

int GetCollidedObjects(struct ITEM_INFO* a1, long a2, int a3, struct ITEM_INFO** a4, struct MESH_INFO** a5, int a6)
{
	UNIMPLEMENTED();
	return 0;
}