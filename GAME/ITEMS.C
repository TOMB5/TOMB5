#include "ITEMS.H"

#include "CONTROL.H"
#include "DRAW.H"
#include "OBJECTS.H"
#ifdef PC_VERSION
#include "GAME.H"
#include "INIT.H"
#else
#include "SETUP.H"
#endif
#include "SPECIFIC.H"
#include "SPECTYPES.H"
#include <stddef.h>
#include <assert.h>
#include "EFFECTS.H"
#include "MALLOC.H"
#include "EFFECT2.H"
#include "LARA.H"

int level_items;
short next_item_free;
short next_item_active;
short GlobalPulleyFrigItem;

void EffectNewRoom(short fx_num, short room_number)//42320, 42774 (F)
{
	if(InItemControlLoop)
	{
		ItemNewRooms[ItemNewRoomNo][0] = fx_num;
		ItemNewRooms[ItemNewRoomNo][1] = room_number;
		ItemNewRoomNo++;
	}
	else
	{
		struct FX_INFO* fx = &effects[fx_num];
		struct room_info* r = &room[fx->room_number];

		if (r->fx_number == fx_num)
		{
			r->fx_number = fx->next_fx;
		}
		else if(r->fx_number != -1)
		{
			short linknum;
			for (linknum = effects[r->fx_number].next_fx; linknum != -1; linknum = effects[linknum].next_fx)
			{
				if (linknum == fx_num)
				{
					effects[r->fx_number].next_fx = fx->next_fx;
					break;
				}
			}
		}

		fx->room_number = room_number;
		fx->next_fx = room[room_number].fx_number;
		room[room_number].fx_number = fx_num;
	}
}

void KillEffect(short fx_num)//42178, 425CC (F)
{
	if (InItemControlLoop)
	{
		ItemNewRooms[ItemNewRoomNo][0] = fx_num | 0x8000;
		ItemNewRoomNo++;
	}
	else
	{
		struct FX_INFO* fx = &effects[fx_num];		

		DetatchSpark(fx_num, 128);

		if (next_fx_active == fx_num)
		{
			next_fx_active = fx->next_active;
		}
		else if (next_fx_active != -1)
		{
			short linknum;
			for (linknum = effects[next_fx_active].next_active; linknum != -1; linknum = effects[linknum].next_active)
			{
				if (linknum == fx_num)
				{
					effects[linknum].next_active = fx->next_active;
					break;
				}
			}
		}

		if (room[fx->room_number].fx_number == fx_num)
		{
			room[fx->room_number].fx_number = fx->next_fx;
		}
		else if (room[fx->room_number].fx_number != -1)
		{
			short linknum;
			for (linknum = effects[room[fx->room_number].fx_number].next_fx; linknum != -1; linknum = effects[linknum].next_fx)
			{
				if (linknum == fx_num)
				{
					effects[room[fx->room_number].fx_number].next_fx = fx->next_fx;
					break;
				}
			}
		}

		fx->next_fx = next_fx_free;
		next_fx_free = fx_num;
	}
}

short CreateEffect(short room_num)//420E0(<), 42534(<) (F)
{
	struct room_info* r;
	struct FX_INFO* fx;
	short fx_num = next_fx_free;

	if (next_fx_free != -1)
	{
		fx = &effects[next_fx_free];
		next_fx_free = fx->object_number;
		r = &room[room_num];
		fx->room_number = room_num;
		fx->next_fx = r->fx_number;
		r->fx_number = fx_num;
		fx->next_active = next_fx_active;
		next_fx_active = fx_num;
		fx->shade = GRAY555;
	}

	return fx_num;
}

void InitialiseFXArray(int allocmem)//4207C(<), 424D0(<) (F)
{
	int i;
	struct FX_INFO* fx;

	if (allocmem)
		effects = (struct FX_INFO*)game_malloc(24 * sizeof(struct FX_INFO));

	fx = effects;
	next_fx_active = -1;
	next_fx_free = 0;
	for (i = 1; i <= 24; i++)
	{
		fx->next_fx = i++;
		++fx;
	}
	fx->next_fx = -1;
}

void AddActiveItem(short item_num)//41FEC(<), 42440(<) (F)
{
	struct ITEM_INFO* item;

	item = &items[item_num];

	item->flags |= 0x20;

	if (objects[item->object_number].control == NULL)//Bug: Always zero due to incomplete level data relocation
	{
		item->status = ITEM_INACTIVE;
		return;
	}

	if (!item->active)
	{
		item->active = TRUE;
		item->next_active = next_item_active;
		next_item_active = item_num;
	}
}

void RemoveDrawnItem(short item_num)//41F48, 4239C (F)
{
	struct ITEM_INFO* item = &items[item_num];

	if (room[item->room_number].item_number == item_num)
	{
		room[item->room_number].item_number = item->next_item;
	}
	else if (room[item->room_number].item_number != -1)
	{
		short linknum;
		for (linknum = items[room[item->room_number].item_number].next_item; linknum != -1; linknum = items[linknum].next_item)
		{
			if (linknum == item_num)
			{
				items[linknum].next_item = items[item_num].next_item;
				break;
			}
		}
	}
}

void RemoveActiveItem(short item_num)//41E98, 422EC (F)
{
	if (items[item_num].active)
	{
		items[item_num].active = FALSE;

		if (next_item_active == item_num)
		{
			next_item_active = items[item_num].next_active;
		}
		else if(next_item_active != -1)
		{
			short linknum;
			for (linknum = items[next_item_active].next_active; linknum != -1; linknum = items[linknum].next_active)
			{
				if (linknum == item_num)
				{
					items[linknum].next_active = items[item_num].next_active;
					break;
				}
			}
		}
	}
}

void InitialiseItem(short item_num)//41BEC(<), 42040 (F)
{
	struct ITEM_INFO* item;
	struct room_info* r;
	struct FLOOR_INFO* floor;
	
	item = &items[item_num];
	item->anim_number = objects[item->object_number].anim_index;
	item->frame_number = anims[item->anim_number].frame_base;

	item->required_anim_state = 0;
	item->goal_anim_state = anims[item->anim_number].current_anim_state;
	item->current_anim_state = anims[item->anim_number].current_anim_state;

	item->pos.z_rot = 0;
	item->pos.x_rot = 0;

	item->fallspeed = 0;
	item->speed = 0;

	item->item_flags[3] = 0;
	item->item_flags[2] = 0;
	item->item_flags[1] = 0;
	item->item_flags[0] = 0;

	item->active = FALSE;
	item->status = ITEM_INACTIVE;
	item->gravity_status = FALSE;
	item->hit_status = FALSE;
	item->collidable = TRUE;
	item->looked_at = FALSE;
	item->dynamic_light = FALSE;
	item->poisoned = FALSE;
	item->ai_bits = 0;
	item->really_active = FALSE;

	item->timer = 0;

	item->hit_points = objects[item->object_number].hit_points;
	
	if (item->object_number == HK_ITEM || 
		item->object_number == HK_AMMO_ITEM || 
		item->object_number == CROSSBOW_ITEM || 
		item->object_number == REVOLVER_ITEM)
	{
		item->mesh_bits = 1;
	}
	else
	{
		item->mesh_bits = 0xFFFFFFFF;
	}

	item->touch_bits = 0;
	item->after_death = 0;
	item->fired_weapon = 0;
	item->data = NULL;

	if (item->flags & IFLAG_INVISIBLE)
	{
		item->flags &= ~IFLAG_INVISIBLE;
		item->status = ITEM_INVISIBLE;
	}
	else if (objects[item->object_number].intelligent)
	{
		item->status = ITEM_INVISIBLE;
	}

	if ((item->flags & IFLAG_ACTIVATION_MASK) == IFLAG_ACTIVATION_MASK)
	{
		item->flags &= ~IFLAG_ACTIVATION_MASK;
		item->flags |= IFLAG_REVERSE;
		AddActiveItem(item_num);
		item->status = ITEM_ACTIVE;
	}

	r = &room[item->room_number];

	item->next_item = r->item_number;
	r->item_number = item_num;

	floor = &r->floor[((item->pos.z_pos - r->z) / SECTOR(1)) + (((item->pos.x_pos - r->x) / SECTOR(1)) * r->x_size)];

	item->floor = floor->floor * 256;
	item->box_number = floor->box;

	if (objects[item->object_number].initialise != NULL)
	{
		objects[item->object_number].initialise(item_num);
	}

#if PSXENGINE
	item->il.Light[3].pad = 0;
#endif

#if PC_VERSION
	item->il.room_num = -1;
	item->light_room_num = -1;

	item->unk_thing = 0;

	item->num_lights_1 = 0;
	item->num_lights_2 = 0;

	item->il.room_ambient = r->ambient;

	item->ptr_lights_1 = item->lights_1;
	item->ptr_lights_2 = item->lights_2;
#endif
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

void KillItem(short item_num)//41950, 41DA4 (F)
{
	if (InItemControlLoop)
	{
		ItemNewRooms[ItemNewRoomNo][0] = item_num | 0x8000;
		ItemNewRoomNo++;
	}
	else
	{
		struct ITEM_INFO* item = &items[item_num];

		DetatchSpark(item_num, 128);

		item->active = FALSE;
		item->really_active = FALSE;

		if (next_item_active == item_num)
		{
			next_item_active = item->next_active;
		}
		else if (next_item_active != -1)
		{
			short linknum;
			for (linknum = items[next_item_active].next_active; linknum != -1; linknum = items[linknum].next_active)
			{
				if (linknum == item_num)
				{
					items[linknum].next_active = item->next_active;
					break;
				}
			}
		}

		if (item->room_number != 255)
		{
			if (room[item->room_number].item_number == item_num)
			{
				room[item->room_number].item_number = item->next_item;
			}
			else if (room[item->room_number].item_number != -1)
			{
				short linknum;
				for (linknum = items[room[item->room_number].item_number].next_item; linknum != -1; linknum = items[linknum].next_item)
				{
					if (linknum == item_num)
					{
						items[room[item->room_number].item_number].next_item = item->next_item;
						break;
					}
				}
			}
		}

		if (item == lara.target)
		{
			lara.target = NULL;
		}

		if (item_num >= level_items)
		{
			item->next_item = next_item_free;
			next_item_free = item_num;
		}
		else
		{
			item->flags |= IFLAG_KILLED;
		}
	}
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
			item->active = FALSE;
		}
	}

	item->next_item = -1;
	return;
}

void ItemNewRoom(short item_num, short room_number)//7C608(<), 7E64C(<) (F)
{
	if (InItemControlLoop)
	{
		ItemNewRooms[ItemNewRoomNo][0] = item_num;
		ItemNewRooms[ItemNewRoomNo][1] = room_number;
		ItemNewRoomNo++;
	}
	else
	{
		struct ITEM_INFO* item = &items[item_num];

		if (item->room_number != 255)
		{
			struct room_info* r = &room[item->room_number];

			if (r->item_number == item_num)
			{
				r->item_number = item->next_item;
			}
			else if (r->item_number != -1)
			{
				short linknum;
				for (linknum = items[r->item_number].next_item; linknum != -1; linknum = items[linknum].next_item)
				{
					if (linknum == item_num)
					{
						items[r->item_number].next_item = item->next_item;
						break;
					}
				}
			}
		}

		item->room_number = room_number;
		item->next_item = room[room_number].item_number;
		room[room_number].item_number = item_num;
	}
}
