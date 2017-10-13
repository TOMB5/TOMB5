#ifndef LARASURF_H
#define LARASURF_H

#include "SPECTYPES.H"

extern void lara_col_surftread(ITEM_INFO* item, COLL_INFO* coll);
extern void lara_col_surfright(ITEM_INFO* item, COLL_INFO* coll);
extern void lara_col_surfleft(ITEM_INFO* item, COLL_INFO* coll);
extern void lara_col_surfback(ITEM_INFO* item, COLL_INFO* coll);
extern void lara_col_surfswim(ITEM_INFO* item, COLL_INFO* coll);
extern void lara_as_surftread(ITEM_INFO* item, COLL_INFO* coll);
extern void lara_as_surfright(ITEM_INFO* item, COLL_INFO* coll);
extern void lara_as_surfleft(ITEM_INFO* item, COLL_INFO* coll);
extern void lara_as_surfback(ITEM_INFO* item, COLL_INFO* coll);
extern void lara_as_surfswim(ITEM_INFO* item, COLL_INFO* coll);
extern void LaraSurface(ITEM_INFO* item, COLL_INFO* coll);
extern void LaraSurfaceCollision(ITEM_INFO* item, COLL_INFO* coll);
extern int LaraTestWaterClimbOut(ITEM_INFO* item, COLL_INFO* coll);
extern int LaraTestWaterStepOut(ITEM_INFO* item, COLL_INFO* coll);

#endif