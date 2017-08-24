#ifndef COLLIDE_H
#define COLLIDE_H

#include "SPECTYPES.H"

extern long zfront;
extern long xfront;
extern short GlobalCollisionBounds[6];
extern char LM[15];

extern void TestForObjectOnLedge(struct ITEM_INFO *item, struct COLL_INFO *coll);
extern void TriggerLaraBlood();
extern void GenericSphereBoxCollision(short item_num, struct ITEM_INFO *laraitem, struct COLL_INFO *coll);
extern int ItemPushLaraStatic(struct ITEM_INFO *laraitem, short *bounds, struct PHD_3DPOS *pos, struct COLL_INFO *coll);
extern int TestBoundsCollideStatic(short *bounds, struct PHD_3DPOS *pos, long radius);
extern void TrapCollision(short item_num, struct ITEM_INFO *laraitem, struct COLL_INFO *coll);
extern void AIPickupCollision(short item_num, struct ITEM_INFO *laraitem, struct COLL_INFO *coll);
extern void CreatureCollision(short item_num, struct ITEM_INFO *laraitem, struct COLL_INFO *coll);
extern void LaraBaddieCollision(struct ITEM_INFO *laraitem, struct COLL_INFO *coll);
extern void ShiftItem(struct ITEM_INFO *item, struct COLL_INFO *coll);
extern int GetCollisionInfo(struct COLL_INFO *coll, long xpos, long ypos, long zpos, short room_number, long objheight);

#endif