#ifndef LARACLMB_H
#define LARACLMB_H

#include "SPECTYPES.H"

extern short GetClimbTrigger(long x, long y, long z, short room_number);
extern void lara_col_climbend(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_as_climbend(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_col_climbdown(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_as_climbdown(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_col_climbing(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_as_climbing(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_col_climbright(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_as_climbright(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_col_climbleft(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_as_climbleft(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_col_climbstnc(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern void lara_as_climbstnc(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern int LaraTestClimbPos(struct ITEM_INFO* item, int front, int right, int origin, int height, int *shift);
extern void LaraDoClimbLeftRight(struct ITEM_INFO* item, struct COLL_INFO* coll, int result, int shift);
extern int LaraClimbRightCornerTest(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern int LaraClimbLeftCornerTest(struct ITEM_INFO* item, struct COLL_INFO* coll);
extern int LaraTestClimb(int x, int y, int z, int xfront, int zfront, int item_height, int item_room, int *shift);
extern int LaraTestClimbUpPos(struct ITEM_INFO* item, int front, int right, int *shift, int *ledge);
extern long LaraCheckForLetGo(struct ITEM_INFO* item, struct COLL_INFO* coll);

#endif