#include "LARA.H"

static short LeftClimbTab[4]; // offset 0xA0638
static short RightClimbTab[4]; // offset 0xA0640
short angle; // offset 0xA0650
short elevation; // offset 0xA0652
struct ITEM_INFO* lara_item; // offset 0xA2048
unsigned short DashTimer; // offset 0xA2044
struct lara_info lara; // offset 0xA57DC