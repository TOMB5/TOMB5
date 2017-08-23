#include "BOX.H"

#include "CONTROL.H"
#include "LOT.H"
#include "SPECIFIC.H"

int number_boxes;
struct box_info* boxes;
unsigned short* overlap;
short* ground_zone[5][2];
unsigned short testclip;
unsigned short loops;

void AlertNearbyGuards(struct ITEM_INFO* item)//24D20(<), 24F2C(<)
{
	int slot = 4;
	struct creature_info* cinfo = baddie_slots;
	struct ITEM_INFO* target;
	long x = 0;
	long y = 0;
	long z = 0;
	long distance = 0;
	int i = 0;

	//loc_24D3C
	for (i = 0; i < slot; i++)
	{
		if (cinfo->item_num == -1)
		{
			continue;
		}

		target = &items[cinfo->item_num + i];

		//Rooms match, alert the guards!
		if (item->room_number == target->room_number)
		{
			//24DCC
			cinfo->alerted = 1;
			continue;
		}

		x = (target->pos.x_pos - item->pos.x_pos) / 64;
		y = (target->pos.y_pos - item->pos.y_pos) / 64;
		z = (target->pos.z_pos - item->pos.z_pos) / 64;

		distance = (x * x) + (y * y) + (z * z);

		//Though the item is not in the same room.
		//If the distance between them is < 0x1F40, alert the guards!
		if (distance < 0x1F40)
		{
			//24DCC
			cinfo->alerted = 1;
		}
	}

	return;
}
