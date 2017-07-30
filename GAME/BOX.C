#include "BOX.H"

#include "SPECIFIC.H"

int number_boxes;
struct box_info* boxes;
unsigned short* overlap;
short* ground_zone[5][2];
unsigned short testclip;
unsigned short loops;

void AlertNearbyGuards(ITEM_INFO* item)
{
	S_Warn("[AlertNearbyGuards] - Unimplemented!\n");
}
