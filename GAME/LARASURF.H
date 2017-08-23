#ifndef LARASURF_H
#define LARASURF_H

#include "SPECTYPES.H"

extern void lara_col_surfright(struct ITEM_INFO *item, struct COLL_INFO *coll);
extern void lara_col_surfleft(struct ITEM_INFO *item, struct COLL_INFO *coll);
extern void lara_col_surfback(struct ITEM_INFO *item, struct COLL_INFO *coll);
extern void lara_col_surfswim(struct ITEM_INFO *item, struct COLL_INFO *coll);
extern void lara_as_surftread(struct ITEM_INFO *item, struct COLL_INFO *coll);
extern void lara_as_surfright(struct ITEM_INFO *item, struct COLL_INFO *coll);
extern void lara_as_surfleft(struct ITEM_INFO *item, struct COLL_INFO *coll);
extern void lara_as_surfback(struct ITEM_INFO *item, struct COLL_INFO *coll);
extern void lara_as_surfswim(struct ITEM_INFO *item, struct COLL_INFO *coll);
extern void LaraSurface(struct ITEM_INFO *item, struct COLL_INFO *coll);
extern void LaraSurfaceCollision(struct ITEM_INFO *item, struct COLL_INFO *coll);
extern int LaraTestWaterClimbOut(struct ITEM_INFO *item, struct COLL_INFO *coll);
extern int LaraTestWaterStepOut(struct ITEM_INFO *item, struct COLL_INFO *coll);

#endif