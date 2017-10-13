#ifndef COLLIDE_H
#define COLLIDE_H

#include "SPECTYPES.H"

enum collision_types
{
	CT_NONE = 0,			   // 0x00
	CT_FRONT = (1 << 0),  // 0x01
	CT_LEFT = (1 << 1),  // 0x02
	CT_RIGHT = (1 << 2),  // 0x04
	CT_TOP = (1 << 3),  // 0x08
	CT_TOP_FRONT = (1 << 4),  // 0x10
	CT_CLAMP = (1 << 5)   // 0x20
};

enum height_types
{
	HT_WALL = 0,
	HT_SLOPE_SMALL = 1,
	HT_SLOPE_BIG = 2
};

extern long zfront;
extern long xfront;
extern short GlobalCollisionBounds[6];
extern char LM[15];

extern void TestForObjectOnLedge(ITEM_INFO* item, COLL_INFO* coll);
extern void TriggerLaraBlood();
extern void GenericSphereBoxCollision(short item_num, ITEM_INFO* laraitem, COLL_INFO* coll);
extern int ItemPushLaraStatic(ITEM_INFO* laraitem, short* bounds, PHD_3DPOS* pos, COLL_INFO* coll);
extern int ItemPushLara(ITEM_INFO* item, ITEM_INFO* laraitem, COLL_INFO* coll, int a4, int a5);
extern int TestBoundsCollideStatic(short* bounds, PHD_3DPOS* pos, long radius);
extern int TestBoundsCollide(ITEM_INFO* item, ITEM_INFO* laraitem, long radius);
extern void TrapCollision(short item_num, ITEM_INFO* laraitem, COLL_INFO* coll);
extern void AIPickupCollision(short item_num, ITEM_INFO* laraitem, COLL_INFO* coll);
extern void CreatureCollision(short item_num, ITEM_INFO* laraitem, COLL_INFO* coll);
extern void LaraBaddieCollision(ITEM_INFO* laraitem, COLL_INFO* coll);
extern void ShiftItem(ITEM_INFO* item, COLL_INFO* coll);
extern int GetCollisionInfo(COLL_INFO* coll, long xpos, long ypos, long zpos, short room_number, long objheight);
extern void UpdateLaraRoom(ITEM_INFO* item, int height);
extern void ObjectCollision(short item_num, ITEM_INFO* lara_item, COLL_INFO* coll);
extern int TestLaraPosition(short* bounds, ITEM_INFO* item, ITEM_INFO* lara_item);
extern int MoveLaraPosition(PHD_VECTOR* vector, ITEM_INFO* item, ITEM_INFO* lara_item);

#endif