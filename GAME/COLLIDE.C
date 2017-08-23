#include "COLLIDE.H"

#include "SPECIFIC.H"

long zfront;
long xfront;
short GlobalCollisionBounds[6];

char LM[] =
{
	0, 1, 2, 3, 4, 5, 6, 7, 9, 10, 11, 12, 13, 14, 8
};

void TestForObjectOnLedge(struct ITEM_INFO *item, struct COLL_INFO *coll)//2A940, 2AB68
{
	S_Warn("[TestForObjectOnLedge] - Unimplemented!\n");
}

void TriggerLaraBlood()//2A838, 2AA60
{
	S_Warn("[TriggerLaraBlood] - Unimplemented!\n");
}

void GenericSphereBoxCollision(short item_num, struct ITEM_INFO *laraitem, struct COLL_INFO *coll)//2A5EC, 2A814
{
	S_Warn("[GenericSphereBoxCollision] - Unimplemented!\n");
}

int ItemPushLaraStatic(struct ITEM_INFO *laraitem, short *bounds, struct PHD_3DPOS *pos, struct COLL_INFO *coll)//2A2D8, 2A500
{
	S_Warn("[ItemPushLaraStatic] - Unimplemented!\n");
	return 0;
}

int TestBoundsCollideStatic(short *bounds, struct PHD_3DPOS *pos, long radius)//2A140, 2A368
{
	S_Warn("[TestBoundsCollideStatic] - Unimplemented!\n");
	return 0;
}

void TrapCollision(short item_num, struct ITEM_INFO *laraitem, struct COLL_INFO *coll)//2A098, 2A2C0
{
	S_Warn("[TrapCollision] - Unimplemented!\n");
}

void AIPickupCollision(short item_num, struct ITEM_INFO *laraitem, struct COLL_INFO *coll)//2A03C, 2A264
{
	S_Warn("[AIPickupCollision] - Unimplemented!\n");
}

void CreatureCollision(short item_num, struct ITEM_INFO *laraitem, struct COLL_INFO *coll)//29E10, 2A024
{
	S_Warn("[CreatureCollision] - Unimplemented!\n");
}

void LaraBaddieCollision(struct ITEM_INFO *laraitem, struct COLL_INFO *coll)//29A44, 29C58
{
	S_Warn("[LaraBaddieCollision] - Unimplemented!\n");
}