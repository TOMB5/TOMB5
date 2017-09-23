#include "BOX.H"

#include "CONTROL.H"
#include "DRAW.H"
#include "ITEMS.H"
#include "LOT.H"
#include "SPECIFIC.H"

#include <stddef.h>

int number_boxes;
struct box_info* boxes;
unsigned short* overlap;
short* ground_zone[5][2];
unsigned short testclip;
unsigned short loops;

void DropBaddyPickups(struct ITEM_INFO* item)//259BC(<), 25BC8(<)
{
	short pickup_number;
	short room_number;
	struct ITEM_INFO* pickup;

	pickup_number = item->carried_item;

	if (pickup_number == -1)
	{
		return;
	}

	do
	{
		pickup = &items[pickup_number];
		pickup->pos.x_pos = (item->pos.x_pos & 0xFFFFFC00) | 0x200;
		pickup->pos.z_pos = (item->pos.z_pos & 0xFFFFFC00) | 0x200;
		room_number = item->room_number;

		pickup->pos.y_pos = GetHeight(GetFloor(pickup->pos.x_pos, item->pos.y_pos, pickup->pos.z_pos, &room_number), pickup->pos.x_pos, item->pos.y_pos, pickup->pos.z_pos);
		pickup->pos.y_pos -= GetBoundsAccurate(item)[3];

		//pickup->pos.y_pos -= bounds[3]; //old

		ItemNewRoom(pickup_number, item->room_number);

	} while (pickup_number != -1);
}

int MoveCreature3DPos(struct PHD_3DPOS* srcpos, struct PHD_3DPOS* destpos, int velocity, short angdif, int angadd)
{
	S_Warn("[MoveCreature3DPos] - Unimplemented!\n");
	return 0;
}

void CreatureYRot(struct PHD_3DPOS* srcpos, short angle, short angadd)
{
	S_Warn("[CreatureYRot] - Unimplemented!\n");
}

short SameZone(struct creature_info* creature, struct ITEM_INFO* target_item)//255F8(<), ?
{
	struct room_info* r;
	short* zone;
	struct ITEM_INFO* item;

	item = &items[creature->item_num];

	zone = ground_zone[creature->LOT.zone][flip_status];

	r = &room[item->room_number];
	item->box_number = r->floor[((item->pos.z_pos - r->z) / 1024) + ((item->pos.x_pos - r->x) / 1024) * r->x_size].box;

	r = &room[target_item->room_number];
	target_item->box_number = r->floor[(target_item->pos.z_pos - r->z) / 1024 + ((target_item->pos.x_pos - r->x) / 1024) * r->x_size].box;
	
	return (zone[item->box_number] == zone[target_item->box_number]);
}

void FindAITargetObject(struct creature_info* creature, short obj_num)
{
	S_Warn("[FindAITargetObject] - Unimplemented!\n");
}

void GetAITarget(struct creature_info* creature)
{
	S_Warn("[GetAITarget] - Unimplemented!\n");
}

short AIGuard(struct creature_info* creature)
{
	S_Warn("[AIGuard] - Unimplemented!\n");
	return 0;
}


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

void AlertAllGuards(short item_number)
{
	S_Warn("[AlertAllGuards] - Unimplemented!\n");
}

void CreatureKill(struct ITEM_INFO* item, int kill_anim, int kill_state, short lara_anim)
{
	S_Warn("[CreatureKill] - Unimplemented!\n");
}

int CreatureVault(short item_number, short angle, int vault, int shift)
{
	S_Warn("[CreatureVault] - Unimplemented!\n");
	return 0;
}

short CreatureEffectT(struct ITEM_INFO* item, struct BITE_INFO* bite, short damage, short angle, short* generate)
{
	S_Warn("[CreatureEffectT] - Unimplemented!\n");
	return 0;
}

short CreatureEffect(struct ITEM_INFO* item, struct BITE_INFO* bite, short* generate)
{
	S_Warn("[CreatureEffect] - Unimplemented!\n");
	return 0;
}

void CreatureUnderwater(struct ITEM_INFO* item, long depth)
{
	S_Warn("[CreatureUnderwater] - Unimplemented!\n");
}

void CreatureFloat(short item_number)
{
	S_Warn("[CreatureFloat] - Unimplemented!\n");
}

void CreatureJoint(struct ITEM_INFO* item, short joint, short required)
{
	S_Warn("[CreatureJoint] - Unimplemented!\n");
}

void CreatureTilt(struct ITEM_INFO* item, short angle)//24418(<), 24624(<) (F)
{
	angle = (angle << 2) - item->pos.z_rot;
	
	if(angle < ANGLE(-3))
		angle = ANGLE(-3);
	else if (angle > ANGLE(3))
		angle = ANGLE(3);

	if (ABS(item->pos.z_rot) - ANGLE(15) > ANGLE(15))
	{
		angle >>= 1;
	}
	
	item->pos.z_rot += angle; // todo in orig code (mips) z_rot is lhu'd into v0 as unsigned, here i skipped that part, maybe it'll break
}

short CreatureTurn(struct ITEM_INFO* item, short maximum_turn)
{
	S_Warn("[CreatureTurn] - Unimplemented!\n");
	return 0;
}

int CreatureAnimation(short item_number, short angle, short tilt)
{
	S_Warn("[CreatureAnimation] - Unimplemented!\n");
	return 0;
}

void CreatureDie(short item_number, int explode)
{
	S_Warn("[CreatureDie] - Unimplemented!\n");
}

int BadFloor(long x, long y, long z, long box_height, long next_height, int room_number, struct lot_info* LOT)
{
	S_Warn("[BadFloor] - Unimplemented!\n");
	return 0;
}

int CreatureCreature(short item_number)
{
	S_Warn("[CreatureCreature] - Unimplemented!\n");
	return 0;
}

enum target_type CalculateTarget(struct PHD_VECTOR* target, struct ITEM_INFO* item, struct lot_info* LOT)
{
	S_Warn("[CalculateTarget] - Unimplemented!\n");
	return NO_TARGET;
}

void CreatureMood(struct ITEM_INFO* item, struct AI_info* info, int violent)
{
	S_Warn("[CreatureMood] - Unimplemented!\n");
}

void GetCreatureMood(struct ITEM_INFO* item, struct AI_info* info, int violent)
{
	S_Warn("[GetCreatureMood] - Unimplemented!\n");
}

int ValidBox(struct ITEM_INFO* item, short zone_number, short box_number)//222A4(<), ?
{
	struct box_info* box;
	struct creature_info* creature;
	short* zone;

	creature = (struct creature_info*)item->data;
	zone = ground_zone[creature->LOT.zone][flip_status];

	if (creature->LOT.fly == 0 && zone[box_number] != zone_number)
	{
		return 0;
	}

	box = &boxes[box_number];

	if (box->overlap_index & creature->LOT.block_mask)
	{
		return 0;
	}

	if ((item->pos.z_pos > (box->left * 1024)) || ((box->right  * 1024) > item->pos.z_pos) ||
		(item->pos.x_pos > (box->top  * 1024)) || ((box->bottom * 1024) > item->pos.x_pos))
	{
		return 1;
	}

	return 0;
}

int EscapeBox(struct ITEM_INFO* item, struct ITEM_INFO* enemy, short box_number)//221C4(<), ?
{
	struct box_info *box; // $a0
	long x; // $a3
	long z; // $a2


	return 0;
}

void TargetBox(struct lot_info* LOT, short box_number)
{
	S_Warn("[TargetBox] - Unimplemented!\n");
}

int UpdateLOT(struct lot_info* LOT, int expansion)//22034(<), ?
{
	struct box_node* expand;

	if (LOT->required_box != 0x7FF && LOT->required_box != LOT->target_box)
	{
		LOT->target_box = LOT->required_box;
		expand = &LOT->node[LOT->required_box];
		
		if (expand->next_expansion == 0x7FF && LOT->tail != LOT->required_box)
		{
			expand->next_expansion = LOT->head;

			if (LOT->head == LOT->node[LOT->required_box].next_expansion)
			{
				LOT->tail = LOT->target_box;
			}//0x220B8

			LOT->head = LOT->target_box;

		}//0x220C4

		LOT->search_number++;
		expand->search_number = LOT->search_number;
		expand->exit_box = 0x7FF;
	}//220DC

	return SearchLOT(LOT, expansion);
}

int SearchLOT(struct lot_info* LOT, int expansion)
{
	S_Warn("[SearchLOT] - Unimplemented!\n");
	return 0;
}

void CreatureAIInfo(struct ITEM_INFO* item, struct AI_info* info)
{
	S_Warn("[CreatureAIInfo] - Unimplemented!\n");
}

int CreatureActive(short item_number)//218B0(<), ?
{
	struct ITEM_INFO* item = &items[item_number];

	if (item->flags & 0x8000)
	{
		if (item->status != 3)
		{
			return 1;
		}

		if (EnableBaddieAI(item_number, 0) != 0)
		{
			item->status = 2;
			return 1;
		}
	}

	return 0;
}

void InitialiseCreature(short item_number)//21800(<), ?
{
	struct ITEM_INFO* item = &items[item_number];

	item->hit_status = 1;
	item->data = NULL;
	item->draw_room = (((item->pos.z_pos - room[item->room_number].z) / 1024) & 0xFF) | (((item->pos.x_pos - room[item->room_number].mesh->x) / 4) & 0xFF00);
	item->TOSSPAD = item->pos.y_rot & 0xE000;
	item->item_flags[2] = item->room_number | (item->pos.y_pos - room->minfloor);

	return;
}

int StalkBox(struct ITEM_INFO* item, struct ITEM_INFO* enemy, short box_number)
{
	S_Warn("[StalkBox] - Unimplemented!\n");
	return 0;
}

