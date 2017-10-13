#ifndef LARACLMB_H
#define LARACLMB_H

#include "SPECTYPES.H"

extern short GetClimbTrigger(long x, long y, long z, short room_number);
extern void lara_col_climbend(ITEM_INFO* item, COLL_INFO* coll);
extern void lara_as_climbend(ITEM_INFO* item, COLL_INFO* coll);
extern void lara_col_climbdown(ITEM_INFO* item, COLL_INFO* coll);
extern void lara_as_climbdown(ITEM_INFO* item, COLL_INFO* coll);
extern void lara_col_climbing(ITEM_INFO* item, COLL_INFO* coll);
extern void lara_as_climbing(ITEM_INFO* item, COLL_INFO* coll);
extern void lara_col_climbright(ITEM_INFO* item, COLL_INFO* coll);
extern void lara_as_climbright(ITEM_INFO* item, COLL_INFO* coll);
extern void lara_col_climbleft(ITEM_INFO* item, COLL_INFO* coll);
extern void lara_as_climbleft(ITEM_INFO* item, COLL_INFO* coll);
extern void lara_col_climbstnc(ITEM_INFO* item, COLL_INFO* coll);
extern void lara_as_climbstnc(ITEM_INFO* item, COLL_INFO* coll);
extern int LaraTestClimbPos(ITEM_INFO* item, int front, int right, int origin, int height, int* shift);
extern void LaraDoClimbLeftRight(ITEM_INFO* item, COLL_INFO* coll, int result, int shift);
extern int LaraClimbRightCornerTest(ITEM_INFO* item, COLL_INFO* coll);
extern int LaraClimbLeftCornerTest(ITEM_INFO* item, COLL_INFO* coll);
extern int LaraTestClimb(int x, int y, int z, int xfront, int zfront, int item_height, int item_room, int* shift);
extern int LaraTestClimbUpPos(ITEM_INFO* item, int front, int right, int* shift, int* ledge);
extern long LaraCheckForLetGo(ITEM_INFO* item, COLL_INFO* coll);

#endif