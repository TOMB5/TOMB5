#include "LION.H"

#include "DRAW.H"
#include "BOX.H"
#include "LARA.H"
#include "OBJECTS.H"
#include "SETUP.H"
#include "CONTROL.H"
#include "TOMB4FX.H"
#include "SPECTYPES.H"

#if PSX_VERSION || PSXPC_VERSION
#include "MISC.H"
#endif

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

void LionControl(short item_num)
{
	short angle;
	short required;
	char *data;
	struct ITEM_INFO* item;
	short Lion_Object;
	short Lion_DefaultAnim;
	short Creature_Turn;
	short Creature_Angle;
	short requiredAngle;
	short requiredAnimState;
	int v9;
	int v10;
	struct AI_info info;

	data = (char*)items[item_num].data;
	item = &items[item_num];
	if (CreatureActive(item_num))
	{
		requiredAngle = 0;
		Creature_Angle = 0;
		angle = 0;
		required = 0;
		data = (char *)items[item_num].data;
		item = &items[item_num];
		if (items[item_num].hit_points <= 0)
		{
			item->hit_points = 0;
			if (item->current_anim_state != 5)
			{
				Lion_Object = objects[57].anim_index + (GetRandomControl() & 1) + 7;
				item->anim_number = Lion_Object;
				Lion_DefaultAnim = anims[Lion_Object].frame_base;
				item->current_anim_state = 5;
				item->frame_number = Lion_DefaultAnim;
			}
			CreatureTilt(item, angle);
			CreatureJoint(item, 0, requiredAngle);
			CreatureJoint(item, 1, required);
			CreatureAnimation(item_num, Creature_Angle, 0);
			return;
		}
		CreatureAIInfo(item, &info);
		if (info.ahead)
			required = info.angle;
		GetCreatureMood(item, &info, 1);
		CreatureMood(item, &info, 1);
		Creature_Turn = CreatureTurn(item, *((unsigned short *)data + 4));
		Creature_Angle = Creature_Turn;
		requiredAngle = -16 * Creature_Turn;
		switch (item->current_anim_state)
		{
		case 1:
			*((unsigned short *)data + 4) = 0;
			requiredAnimState = item->required_anim_state;
			if (requiredAnimState)
			{
				item->goal_anim_state = requiredAnimState;
				CreatureTilt(item, angle);
				CreatureJoint(item, 0, requiredAngle);
				CreatureJoint(item, 1, required);
				CreatureAnimation(item_num, Creature_Angle, 0);
				return;
			}
			if (!*(unsigned long *)(data + 14))
			{
				if (!(GetRandomControl() & 0x3F))
					item->goal_anim_state = 2;
				CreatureTilt(item, angle);
				CreatureJoint(item, 0, requiredAngle);
				CreatureJoint(item, 1, required);
				CreatureAnimation(item_num, Creature_Angle, 0);
				return;
			}
			if (info.ahead)
			{
				if (item->touch_bits & 0x200048)
				{
					item->goal_anim_state = 7;
					CreatureTilt(item, angle);
					CreatureJoint(item, 0, requiredAngle);
					CreatureJoint(item, 1, required);
					CreatureAnimation(item_num, Creature_Angle, 0);
					return;
				}
				if (info.distance < 0x100000)
				{
					item->goal_anim_state = 4;
					CreatureTilt(item, angle);
					CreatureJoint(item, 0, requiredAngle);
					CreatureJoint(item, 1, required);
					CreatureAnimation(item_num, Creature_Angle, 0);
					return;
				}
			}
			item->goal_anim_state = 3;
			CreatureTilt(item, angle);
			CreatureJoint(item, 0, requiredAngle);
			CreatureJoint(item, 1, required);
			CreatureAnimation(item_num, Creature_Angle, 0);
			return;
		case 2:
			v9 = *(unsigned long *)(data + 14);
			*((unsigned short *)data + 4) = 364;
			if (!v9)
				if (GetRandomControl() < 128)
				{
					item->required_anim_state = 6;
					item->goal_anim_state = 1;
				}
			item->goal_anim_state = 1;
			CreatureTilt(item, angle);
			CreatureJoint(item, 0, requiredAngle);
			CreatureJoint(item, 1, required);
			CreatureAnimation(item_num, Creature_Angle, 0);
			return;
		case 3:
			*((unsigned short *)data + 4) = 910;
			v10 = *(unsigned long *)(data + 14);
			angle = Creature_Turn;
			if (v10)
			{
				if (info.ahead && info.distance < 0x100000)
				{
					item->goal_anim_state = 1;
				}
				else if (item->touch_bits & 0x200048 && info.ahead)
				{
					item->goal_anim_state = 1;
				}
				else if (v10 != 2)
				{
					if (GetRandomControl() < 128)
					{
						item->required_anim_state = 6;
						item->goal_anim_state = 1;
					}
				}
			}
			else
			{
				item->goal_anim_state = 1;
			}
			CreatureTilt(item, angle);
			CreatureJoint(item, 0, requiredAngle);
			CreatureJoint(item, 1, required);
			CreatureAnimation(item_num, Creature_Angle, 0);
			return;
		case 4:
			if (!item->required_anim_state && item->touch_bits & 0x200048)
			{
				lara_item->hit_points -= 200;
				//*((unsigned long *)&lara_item->pointer2 + 1) |= 0x10u;
				//CreatureEffectT(item,&LION_BITE_1,10,item->pos.y_rot,(__int16(__cdecl *)(int, int, int, __int16, __int16, __int16))DoBloodSplat);
				item->required_anim_state = 1;
			}
			CreatureTilt(item, angle);
			CreatureJoint(item, 0, requiredAngle);
			CreatureJoint(item, 1, required);
			CreatureAnimation(item_num, Creature_Angle, 0);
			return;
		case 7:
			*((unsigned short *)data + 4) = 182;
			if (!item->required_anim_state && item->touch_bits & 0x200048)
			{
				//CreatureEffectT(item,&LION_BITE_2,10,item->pos.y_rot,(__int16(__cdecl *)(int, int, int, __int16, __int16, __int16))DoBloodSplat);
				lara_item->hit_points -= 60;
				//*((unsigned long *)&lara_item->pointer2 + 1) |= 0x10u;
				item->required_anim_state= 1;
			}
			CreatureTilt(item, angle);
			CreatureJoint(item, 0, requiredAngle);
			CreatureJoint(item, 1, required);
			CreatureAnimation(item_num, Creature_Angle, 0);
			return;
		default:
			CreatureTilt(item, angle);
			CreatureJoint(item, 0, requiredAngle);
			CreatureJoint(item, 1, required);
			CreatureAnimation(item_num, Creature_Angle, 0);
			return;
		}
	}
}