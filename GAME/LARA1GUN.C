#include "LARA1GUN.H"

#include "CONTROL.H"
#include "SPECIFIC.H"
#ifdef PC_VERSION
#include "GAME.H"
#else
#include "SETUP.H"
#endif
#include "DRAW.H"
#include "LARA.H"
#include "LARAFIRE.H"
#include "OBJECTS.H"
#include "ITEMS.H"

char HKTimer = 0;
char HKShotsFired = 0;

void TriggerGrapplingEffect(long x, long y, long z)
{
	S_Warn("[TriggerGrapplingEffect] - Unimplemented!\n");
}

void DoGrenadeDamageOnBaddie(struct ITEM_INFO* baddie, struct ITEM_INFO* item)
{
	S_Warn("[DoGrenadeDamageOnBaddie] - Unimplemented!\n");
}

void AnimateShotgun(int weapon_type)
{
	S_Warn("[AnimateShotgun] - Unimplemented!\n");
}

void undraw_shotgun(int weapon_type)//436B0(<), 43B14(<) (F)
{
	struct ITEM_INFO* item = &items[lara.weapon_item];
	AnimateItem(item);

	if (item->status == 2)
	{
		lara.gun_status = 0;
		lara.target = NULL;
		lara.right_arm.lock = 0;
		lara.left_arm.lock = 0;
		KillItem(lara.weapon_item);
		lara.weapon_item = -1;
		lara.right_arm.frame_number = 0;
		lara.left_arm.frame_number = 0;
	}//loc_43750
	else
	{
		if (item->current_anim_state == 3)
		{
			if (anims[item->anim_number].frame_base == item->frame_number - 21)
			{
				undraw_shotgun_meshes(weapon_type);
			}
		}//loc_43798
	}

	lara.right_arm.frame_base = anims[item->frame_number].frame_ptr;
	lara.left_arm.frame_base = anims[item->frame_number].frame_ptr;

	lara.right_arm.frame_number = item->frame_number - anims[item->anim_number].frame_base;
	lara.left_arm.frame_number = item->frame_number - anims[item->anim_number].frame_base;

	lara.right_arm.anim_number = item->anim_number;
	lara.left_arm.anim_number = item->anim_number;
}

void draw_shotgun(int weapon_type)// (F)
{
	struct ITEM_INFO* item;

	if (lara.weapon_item == -1)
	{		
		lara.weapon_item = CreateItem();
		item = &items[lara.weapon_item];
		item->object_number = WeaponObject(weapon_type);
		item->anim_number = objects[item->object_number].anim_index;
		item->frame_number = anims[item->anim_number].frame_base;
		item->status = ITEM_ACTIVE;
		item->goal_anim_state = 1;
		item->current_anim_state = 1;
		item->room_number = 255;

		lara.left_arm.frame_base = lara.right_arm.frame_base = objects[item->object_number].frame_base;
	}
	else
	{
		item = &items[lara.weapon_item];
	}

	AnimateItem(item);

	if (item->current_anim_state != 0 && 
		item->current_anim_state != 6)
	{
		if (item->frame_number - anims[item->anim_number].frame_base == weapons[weapon_type].draw_frame)
		{
			draw_shotgun_meshes(weapon_type);
		}
		else if (lara.water_status == LW_UNDERWATER)
		{
			item->goal_anim_state = 6;
		}
	}
	else
	{
		ready_shotgun(weapon_type);
	}

	lara.left_arm.frame_base = lara.right_arm.frame_base = anims[item->anim_number].frame_ptr;
	lara.left_arm.frame_number = lara.right_arm.frame_number = item->frame_number - anims[item->anim_number].frame_base;
	lara.left_arm.anim_number = lara.right_arm.anim_number = item->anim_number;
}

void ControlCrossbow(short item_number)
{
	S_Warn("[ControlCrossbow] - Unimplemented!\n");
}

void CrossbowHitSwitchType78(struct ITEM_INFO* item, struct ITEM_INFO* target, int MustHitLastNode)
{
	S_Warn("[CrossbowHitSwitchType78] - Unimplemented!\n");
}

void FireCrossbow(struct PHD_3DPOS* Start)
{
	S_Warn("[FireCrossbow] - Unimplemented!\n");
}

void FireHK(int running)
{
	S_Warn("[FireHK] - Unimplemented!\n");
}

void FireShotgun()
{
	S_Warn("[FireShotgun] - Unimplemented!\n");
}

void RifleHandler(int weapon_type)
{
	S_Warn("[RifleHandler] - Unimplemented!\n");
}

void ready_shotgun(int weapon_type)//424E0(<), 42934(<) (F)
{
	struct object_info* object;

	lara.gun_status = LG_READY;
	lara.left_arm.z_rot = 0;
	lara.left_arm.y_rot = 0;
	lara.left_arm.x_rot = 0;

	lara.right_arm.z_rot = 0;
	lara.right_arm.x_rot = 0;
	lara.right_arm.y_rot = 0;

	lara.right_arm.frame_number = 0;
	lara.left_arm.frame_number = 0;

	lara.right_arm.lock = 0;
	lara.left_arm.lock = 0;
	lara.target = NULL;

	object = &objects[WeaponObject(weapon_type)];//v1

	lara.right_arm.frame_base = object->frame_base;
	lara.left_arm.frame_base = object->frame_base;

	return;
}

void undraw_shotgun_meshes(int weapon_type)//42498(<), 428EC(<) (F)
{
	lara.back_gun = WeaponObject(weapon_type);
	lara.mesh_ptrs[LM_RHAND] = meshes[objects[LARA].mesh_index + 2 * LM_RHAND];
}

void draw_shotgun_meshes(int weapon_type)//42444(<), 42898(<) (F)
{
	lara.back_gun = WEAPON_NONE;
	lara.mesh_ptrs[LM_RHAND] = meshes[objects[WeaponObjectMesh(weapon_type)].mesh_index + 2 * LM_RHAND];
}