#ifndef BOX_H
#define BOX_H

#include "SPECTYPES.H"

#define BOX_BLOCKED (1 << 14)
#define BOX_LAST    (1 << 15)

extern int number_boxes;
extern struct box_info* boxes;
extern unsigned short* overlap;
extern short* ground_zone[5][2];
extern unsigned short testclip;
extern unsigned short loops;

extern void AlertNearbyGuards(struct ITEM_INFO* item);

#endif