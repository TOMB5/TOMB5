#include "LION.H"

#include "DRAW.H"
#include "BOX.H"
#include "LARA.H"
#include "OBJECTS.H"
#include "SETUP.H"
#include "CONTROL.H"
#include "TOMB4FX.H"
#include "STYPES.H"

#include "EFFECTS.H"
#if PC_VERSION
#include "GAME.H"
#include "FXTRIG.H"
#endif

#if PSX_VERSION || PSXPC_VERSION || SAT_VERSION
#include "MISC.H"
#include "FXTRIG.H"
#endif

struct BITE_INFO LION_BITE_1 = { -2, -10, 0x0FA, 0x15 };
struct BITE_INFO LION_BITE_2 = { -2, -10, 0x84, 0x15 };

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
	struct creature_info* crinfo;

	if (CreatureActive(item_num))
	{
		requiredAngle = 0;
		Creature_Angle = 0;
		angle = 0;
		required = 0;
		crinfo = (struct creature_info*)items[item_num].data;
		item = &items[item_num];
		if (items[item_num].hit_points <= 0)
		{
			item->hit_points = 0;
			if (item->current_anim_state != 5)
			{
				Lion_Object = objects[LION].anim_index + (GetRandomControl() & 1) + 7;
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
		Creature_Turn = CreatureTurn(item, crinfo->maximum_turn);
		Creature_Angle = Creature_Turn;
		requiredAngle = -16 * Creature_Turn;
		switch (item->current_anim_state)
		{
		case 1:
			crinfo->maximum_turn = 0;
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
			if (crinfo->mood == BORED_MOOD)
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
			crinfo->maximum_turn = ANGLE(2);
			if (crinfo->mood == BORED_MOOD)
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
			crinfo->maximum_turn = ANGLE(5);
			angle = Creature_Turn;
			if (crinfo->mood == BORED_MOOD)
			{
				if (info.ahead && info.distance < 0x100000)
				{
					item->goal_anim_state = 1;
				}
				else if (item->touch_bits & 0x200048 && info.ahead)
				{
					item->goal_anim_state = 1;
				}
				else if (crinfo->mood != ESCAPE_MOOD)
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
				lara_item->hit_status = TRUE;
				CreatureEffectT(item, &LION_BITE_1, 10, item->pos.y_rot, DoBloodSplat);
				item->required_anim_state = 1;
			}
			CreatureTilt(item, angle);
			CreatureJoint(item, 0, requiredAngle);
			CreatureJoint(item, 1, required);
			CreatureAnimation(item_num, Creature_Angle, 0);
			return;
		case 7:
			crinfo->maximum_turn = ANGLE(1);
			if (!item->required_anim_state && item->touch_bits & 0x200048)
			{
				CreatureEffectT(item,&LION_BITE_2,10,item->pos.y_rot, DoBloodSplat);
				lara_item->hit_points -= 60;
				lara_item->hit_status = TRUE;
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