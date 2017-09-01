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

void DropBaddyPickups(struct ITEM_INFO* item)
{
	S_Warn("[DropBaddyPickups] - Unimplemented!\\n");
}

int MoveCreature3DPos(struct PHD_3DPOS* srcpos, struct PHD_3DPOS* destpos, int velocity, short angdif, int angadd)
{
	S_Warn("[MoveCreature3DPos] - Unimplemented!\\n");
	return 0;
}

void CreatureYRot(struct PHD_3DPOS* srcpos, short angle, short angadd)
{
	S_Warn("[CreatureYRot] - Unimplemented!\\n");
}

short SameZone(struct creature_info* creature, struct ITEM_INFO* target_item)
{
	S_Warn("[SameZone] - Unimplemented!\\n");
	return 0;
}

void FindAITargetObject(struct creature_info* creature, short obj_num)
{
	S_Warn("[FindAITargetObject] - Unimplemented!\\n");
}

void GetAITarget(struct creature_info* creature)
{
	S_Warn("[GetAITarget] - Unimplemented!\\n");
}

short AIGuard(struct creature_info* creature)
{
	S_Warn("[AIGuard] - Unimplemented!\\n");
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
	S_Warn("[AlertAllGuards] - Unimplemented!\\n");
}

void CreatureKill(struct ITEM_INFO* item, int kill_anim, int kill_state, short lara_anim)
{
	S_Warn("[CreatureKill] - Unimplemented!\\n");
}

int CreatureVault(short item_number, short angle, int vault, int shift)
{
	S_Warn("[CreatureVault] - Unimplemented!\\n");
	return 0;
}

short CreatureEffectT(struct ITEM_INFO* item, struct BITE_INFO* bite, short damage, short angle, short* generate)
{
	S_Warn("[CreatureEffectT] - Unimplemented!\\n");
	return 0;
}

short CreatureEffect(struct ITEM_INFO* item, struct BITE_INFO* bite, short* generate)
{
	S_Warn("[CreatureEffect] - Unimplemented!\\n");
	return 0;
}

void CreatureUnderwater(struct ITEM_INFO* item, long depth)
{
	S_Warn("[CreatureUnderwater] - Unimplemented!\\n");
}

void CreatureFloat(short item_number)
{
	S_Warn("[CreatureFloat] - Unimplemented!\\n");
}

void CreatureJoint(struct ITEM_INFO* item, short joint, short required)
{
	S_Warn("[CreatureJoint] - Unimplemented!\\n");
}

void CreatureTilt(struct ITEM_INFO* item, short angle)//24418(<), 24624(<) (F)
{
	angle = (angle << 2) - item->pos.z_rot;
	
	if(angle < -(3 * TRDEG))
		angle = -(3 * TRDEG);
	else if (angle > (3 * TRDEG))
		angle = (3 * TRDEG);

	if (ABS(item->pos.z_rot) - (15 * TRDEG) > (15 * TRDEG))
	{
		angle >>= 1;
	}
	
	item->pos.z_rot += angle; // todo in orig code (mips) z_rot is lhu'd into v0 as unsigned, here i skipped that part, maybe it'll break
}

short CreatureTurn(struct ITEM_INFO* item, short maximum_turn)
{
	S_Warn("[CreatureTurn] - Unimplemented!\\n");
	return 0;
}

int CreatureAnimation(short item_number, short angle, short tilt)
{
	S_Warn("[CreatureAnimation] - Unimplemented!\\n");
	return 0;
}

void CreatureDie(short item_number, int explode)
{
	S_Warn("[CreatureDie] - Unimplemented!\\n");
}

int BadFloor(long x, long y, long z, long box_height, long next_height, int room_number, struct lot_info* LOT)
{
	S_Warn("[BadFloor] - Unimplemented!\\n");
	return 0;
}

int CreatureCreature(short item_number)
{
	S_Warn("[CreatureCreature] - Unimplemented!\\n");
	return 0;
}

enum target_type CalculateTarget(struct PHD_VECTOR* target, struct ITEM_INFO* item, struct lot_info* LOT)
{
	S_Warn("[CalculateTarget] - Unimplemented!\\n");
	return NO_TARGET;
}

void CreatureMood(struct ITEM_INFO* item, struct AI_info* info, int violent)
{
	S_Warn("[CreatureMood] - Unimplemented!\\n");
}

void GetCreatureMood(struct ITEM_INFO* item, struct AI_info* info, int violent)
{
	S_Warn("[GetCreatureMood] - Unimplemented!\\n");
}

int ValidBox(struct ITEM_INFO* item, short zone_number, short box_number)
{
	S_Warn("[ValidBox] - Unimplemented!\\n");
	return 0;
}

int EscapeBox(struct ITEM_INFO* item, struct ITEM_INFO* enemy, short box_number)
{
	S_Warn("[EscapeBox] - Unimplemented!\\n");
	return 0;
}

void TargetBox(struct lot_info* LOT, short box_number)
{
	S_Warn("[TargetBox] - Unimplemented!\\n");
}

int UpdateLOT(struct lot_info* LOT, int expansion)
{
	S_Warn("[UpdateLOT] - Unimplemented!\\n");
	return 0;
}

int SearchLOT(struct lot_info* LOT, int expansion)
{
	S_Warn("[SearchLOT] - Unimplemented!\\n");
	return 0;
}

void CreatureAIInfo(struct ITEM_INFO* item, struct AI_info* info)
{
	S_Warn("[CreatureAIInfo] - Unimplemented!\\n");
}

int CreatureActive(short item_number)
{
	S_Warn("[CreatureActive] - Unimplemented!\\n");
	return 0;
}

void InitialiseCreature(short item_number)
{
	S_Warn("[InitialiseCreature] - Unimplemented!\\n");
}

int StalkBox(struct ITEM_INFO* item, struct ITEM_INFO* enemy, short box_number)
{
	S_Warn("[StalkBox] - Unimplemented!\\n");
	return 0;
}

