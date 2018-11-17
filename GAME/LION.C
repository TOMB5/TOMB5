#include "LION.H"

#include "DRAW.H"
#include "BOX.H"
#include "LARA.H"
#include "OBJECTS.H"
#include "SETUP.H"
#include "CONTROL.H"
#include "TOMB4FX.H"
#include "SPECTYPES.H"


struct BITE_INFO LION_BITE_1 = { 0x0FFFFFFFE, 0x0FFFFFFF6, 0x0FA, 0x15 };
struct BITE_INFO LION_BITE_2 = { 0x0FFFFFFFE, 0x0FFFFFFF6, 0x84, 0x15 };

void InitialiseLion(short item_num)
{
	struct ITEM_INFO* item = &items[item_num];
	
	InitialiseCreature(item_num);
	item->anim_number = objects[LION].anim_index;
	item->frame_number = anims[objects[LION].anim_index].frame_base;
	item->goal_anim_state = 1;
	item->current_anim_state = 1;
}
