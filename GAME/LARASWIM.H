#ifndef LARASWIM_H
#define LARASWIM_H

#include "PSXTYPES.H"

extern struct SUBSUIT_INFO subsuit;
extern char SubHitCount;

extern void LaraWaterCurrent(struct COLL_INFO *coll);
extern long GetWaterDepth(long x, long y, long z, short room_number);
extern void lara_col_waterroll(struct ITEM_INFO *item, struct COLL_INFO *coll);
extern void lara_col_uwdeath(struct ITEM_INFO *item, struct COLL_INFO *coll);
extern void lara_col_dive(struct ITEM_INFO *item, struct COLL_INFO *coll);
extern void lara_col_tread(struct ITEM_INFO *item, struct COLL_INFO *coll);
extern void lara_col_glide(struct ITEM_INFO *item, struct COLL_INFO *coll);
extern void lara_col_swim(struct ITEM_INFO *item, struct COLL_INFO *coll);
extern void lara_as_waterroll(struct ITEM_INFO *item, struct COLL_INFO *coll);
extern void lara_as_uwdeath(struct ITEM_INFO *item, struct COLL_INFO *coll);
extern void lara_as_dive(struct ITEM_INFO *item, struct COLL_INFO *coll);
extern void lara_as_tread(struct ITEM_INFO *item, struct COLL_INFO *coll);
extern void lara_as_glide(struct ITEM_INFO *item, struct COLL_INFO *coll);
extern void lara_as_swim(struct ITEM_INFO *item, struct COLL_INFO *coll);
extern void lara_as_swimcheat(struct ITEM_INFO *item, struct COLL_INFO *coll);
extern void LaraUnderWater(struct ITEM_INFO *item, struct COLL_INFO *coll);
extern void UpdateSubsuitAngles();
extern void SwimTurnSubsuit(struct ITEM_INFO *item);
extern void SwimTurn(struct ITEM_INFO *item);
extern void LaraSwimCollision(struct ITEM_INFO *item, struct COLL_INFO *coll);
extern void LaraTestWaterDepth(struct ITEM_INFO *item, struct COLL_INFO *coll);

#endif