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

extern void TestForObjectOnLedge(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void TriggerLaraBlood();
extern void GenericSphereBoxCollision(short item_num, struct ITEM_INFO* laraitem, struct COLL_INFO* coll);
extern int ItemPushLaraStatic(struct ITEM_INFO* laraitem, short* bounds, struct PHD_3DPOS* pos, struct COLL_INFO* coll);
extern int TestBoundsCollideStatic(short* bounds, struct PHD_3DPOS* pos, long radius);
extern void TrapCollision(short item_num, struct ITEM_INFO* laraitem, struct COLL_INFO* coll);
extern void AIPickupCollision(short item_num, struct ITEM_INFO* laraitem, struct COLL_INFO* coll);
extern void CreatureCollision(short item_num, struct ITEM_INFO* laraitem, struct COLL_INFO* coll);
extern void LaraBaddieCollision(struct ITEM_INFO* laraitem, struct COLL_INFO* coll);
extern void ShiftItem(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern int GetCollisionInfo(struct COLL_INFO* coll, long xpos, long ypos, long zpos, short room_number, long objheight);
extern void UpdateLaraRoom(struct ITEM_INFO* item, int height);

#endif