#include "ITEMS.H"

#include "CONTROL.H"
#include "DRAW.H"
#include "OBJECTS.H"
#include "SETUP.H"
#include "SPECIFIC.H"

#include <stddef.h>
#include <assert.h>

int level_items;
short next_item_free;
short next_item_active;
short GlobalPulleyFrigItem;

void EffectNewRoom(short fx_num, short room_number)//42320, 42774
{
	S_Warn("[EffectNewRoom] - Unimplemented!\\n");
}

void KillEffect(short fx_num)//42178, 425CC
{
	S_Warn("[KillEffect] - Unimplemented!\\n");
}

short CreateEffect(short room_num)//420E0, 42534
{
	S_Warn("[CreateEffect] - Unimplemented!\\n");
	return 0;
}

void InitialiseFXArray(int allocmem)//4207C, 424D0
{
	S_Warn("[InitialiseFXArray] - Unimplemented!\\n");
}

void AddActiveItem(short item_num)//41FEC(<), 42440(<)
{
	struct ITEM_INFO* item;

	item = &items[item_num];

	item->flags |= 0x20;
	//int test = item->object_number << 6;
	if (*(int*)&objects[(item->object_number << 6) + 0x10] == 0)//Bug: Always zero due to incomplete level data relocation
	{
		item->meshswap_meshbits &= -7;
		return;
	}

	if (!(item->active))
	{
		item->active = 1;
		item->next_active = next_item_active;
		next_item_active = item_num;
	}

	return;
}

void RemoveDrawnItem(short item_num)//41F48, 4239C
{
	S_Warn("[RemoveDrawnItem] - Unimplemented!\\n");
}

void RemoveActiveItem(short item_num)//41E98, 422EC
{
	short linknum; // $v1
	struct ITEM_INFO* a1 = &items[item_num];
	//int a2 = *(int*)a1->active;
	int v0;
	short test = 1;
	test &= -2;

	v0 = -2;
	if (a1->active)///@FIXME wrong flags, must finish InitialiseItem();
	{
		assert(0);
		linknum = next_item_active;

		a1->meshswap_meshbits &= -2;

		if (next_item_active == (item_num << 3))//check
		{
			next_item_active = a1->next_active;
		}
		else
		{
			//loc_41F08
			int v0 = -1;
			int v1 = next_item_active;

			if (next_item_active != -1)
			{
#if 0
				assert(0);
				int a3 = -1;
				int v0 = v1 << 3;

				//loc_41F1C

				struct ITEM_INFO* a1 = &items[next_item_active];

				while (v1 != -1)
				{
					v1 = a1->next_active;

					if (v1 == item_num)
					{
						//loc_41EF0
					}
				}
#endif
			}

			//loc_41F1C
		}

	}//locret_41EE8

	return;
}

void InitialiseItem(short item_num)//41BEC(<), 42040
{
	struct ITEM_INFO* item;
	struct room_info* r;
	struct FLOOR_INFO* floor;
	
	item = &items[item_num];
	item->anim_number = *(short*) &objects[(item->object_number << 6) + 0x26];
	item->frame_number = anims[item->anim_number].frame_base;

	item->required_anim_state = 0;
	item->pos.z_rot = 0;
	item->pos.x_rot = 0;
	item->fallspeed = 0;
	item->speed = 0;
	item->item_flags[3] = 0;
	item->item_flags[2] = 0;
	item->item_flags[1] = 0;
	item->item_flags[0] = 0;

	item->meshswap_meshbits &= -7;
	item->meshswap_meshbits &= -2;
	item->meshswap_meshbits &= -129;
	item->meshswap_meshbits &= -15873;
	item->meshswap_meshbits &= -16385;
	item->meshswap_meshbits &= -65;
	item->meshswap_meshbits &= -17;
	item->meshswap_meshbits &= -9;

	item->goal_anim_state = anims[item->anim_number].current_anim_state;
	item->current_anim_state = anims[item->anim_number].current_anim_state;

	item->meshswap_meshbits |= 0x20;
	item->meshswap_meshbits &= -257;
	item->timer = 0;

	item->hit_points = *(short*) &objects[(item->object_number << 6) + 0x28];

	
	if ((item->object_number - HK_ITEM) < UZI_ANIM || item->object_number == CROSSBOW_ITEM || item->object_number == REVOLVER_ITEM)
	{
		item->mesh_bits = 1;
	}
	else
	{
		item->mesh_bits = -1;
	}

	item->touch_bits = 0;
	item->after_death = 0;
	item->fired_weapon = 0;
	item->data = NULL;

	if ((item->flags & 0x100))
	{
		item->flags &= ~0x100;
		item->meshswap_meshbits |= 6;
	}
	else if (((*(int*) &objects[(item->object_number << 6) + 0x30]) >> 17) & 1)
	{
		item->meshswap_meshbits |= 6;
	}

	if ((item->flags & 0x3E00) == 0x3E00)
	{
		item->flags &= ~0x3E00;
		item->flags |= 0x4000;
		AddActiveItem(item_num);
		item->meshswap_meshbits &= -7;
		item->meshswap_meshbits |= 2;
	}

	r = &room[item->room_number];

	item->next_item = r->item_number;
	r->item_number = item_num;

	floor = &r->floor[((item->pos.z_pos - r->z) / 1024) + (((item->pos.x_pos - r->x) / 1024) * r->x_size)];

	item->floor = floor->floor * 256;
	item->box_number = floor->box;

	if ((*(int*) &objects[(item->object_number << 6) + 0xC]) != 0)
	{
		S_Warn("[InitialiseItem] - Unimplemented condition!\n");
		//jalr *(int*) &objects[(item->object_number << 6) + 0xC];
	}

	item->il.Light[3].pad = 0;
	
	return;
}

short CreateItem()//41BAC(<), 42000(<) (F)
{
	short item_num = 0;

	if (next_item_free == -1) return -1;

	item_num = next_item_free;
	items[next_item_free].flags = 0;
	next_item_free = items[next_item_free].next_item;
	return item_num;
}

void KillItem(short item_num)//41950, 41DA4
{
	short linknum;
	struct ITEM_INFO* item;

	return;
}

void InitialiseItemArray(int numitems)//418E8(<), 41D3C(<) (F)
{
	int i;
	struct ITEM_INFO* item;

	item = &items[level_items];
	next_item_active = -1;
	next_item_free = level_items;

	if (level_items + 1 < numitems)
	{
		for (i = level_items + 1; i < numitems; i++, item++)
		{
			item->next_item = i;
			item->meshswap_meshbits &= -2;
		}
	}

	item->next_item = -1;
	return;
}