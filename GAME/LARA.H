#ifndef LARA_H
#define LARA_H

#include "PSXTYPES.H"

#define LARA_DRAW_TYPE_NORMAL   1
#define LARA_DRAW_TYPE_YOUNG    2
#define LARA_DRAW_TYPE_BUNHEAD  3
#define LARA_DRAW_TYPE_OFFICE   4
#define LARA_DRAW_TYPE_ARTIC    5


extern short angle; // offset 0xA0650
extern short elevation; // offset 0xA0652
extern struct ITEM_INFO *lara_item; // offset 0xA2048
extern unsigned short DashTimer; // offset 0xA2044
extern struct lara_info lara; // offset 0xA57DC

#endif