#ifndef LARASWIM_H
#define LARASWIM_H

#include "SPECTYPES.H"

extern SUBSUIT_INFO subsuit;
extern char SubHitCount;

extern void LaraWaterCurrent(COLL_INFO* coll);
extern long GetWaterDepth(long x, long y, long z, short room_number);
extern void lara_col_waterroll(ITEM_INFO* item, COLL_INFO* coll);
extern void lara_col_uwdeath(ITEM_INFO* item, COLL_INFO* coll);
extern void lara_col_dive(ITEM_INFO* item, COLL_INFO* coll);
extern void lara_col_tread(ITEM_INFO* item, COLL_INFO* coll);
extern void lara_col_glide(ITEM_INFO* item, COLL_INFO* coll);
extern void lara_col_swim(ITEM_INFO* item, COLL_INFO* coll);
extern void lara_as_waterroll(ITEM_INFO* item, COLL_INFO* coll);
extern void lara_as_uwdeath(ITEM_INFO* item, COLL_INFO* coll);
extern void lara_as_dive(ITEM_INFO* item, COLL_INFO* coll);
extern void lara_as_tread(ITEM_INFO* item, COLL_INFO* coll);
extern void lara_as_glide(ITEM_INFO* item, COLL_INFO* coll);
extern void lara_as_swim(ITEM_INFO* item, COLL_INFO* coll);
extern void lara_as_swimcheat(ITEM_INFO* item, COLL_INFO* coll);
extern void LaraUnderWater(ITEM_INFO* item, COLL_INFO* coll);
extern void UpdateSubsuitAngles();
extern void SwimTurnSubsuit(ITEM_INFO* item);
extern void SwimTurn(ITEM_INFO* item);
extern void LaraSwimCollision(ITEM_INFO* item, COLL_INFO* coll);
extern void LaraTestWaterDepth(ITEM_INFO* item, COLL_INFO* coll);

#endif