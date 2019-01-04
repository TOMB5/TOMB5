#include "LARA1GUN.H"

#include "BOX.H"
#include "CONTROL.H"
#include "SAVEGAME.H"
#include "SPECIFIC.H"
#ifdef PC_VERSION
#include "GAME.H"
#else
#include "SETUP.H"
#endif
#include "TOMB4FX.H"
#include "TRAPS.H"
#include "DRAW.H"
#include "LARA.H"
#include "LARAFIRE.H"
#include "MISC.H"
#include "OBJECTS.H"
#include "ITEMS.H"

char HKTimer = 0;
char HKShotsFired = 0;

void TriggerGrapplingEffect(long x, long y, long z)//44138(<), ? (F)
{
	long size;
	long lp;
	struct SMOKE_SPARKS* sptr;

	//loc_4416C
	for(lp = 0; lp < 24; lp++)
	{
		sptr = &smoke_spark[GetFreeSmokeSpark()];
		sptr->On = 1;

		sptr->sShade = (GetRandomControl() & 0xF) + 40;
		sptr->dShade = (GetRandomControl() & 0xF) + 64;
		sptr->ColFadeSpeed = 4;
		sptr->FadeToBlack = 16;

		sptr->Life = sptr->sLife = (GetRandomControl() & 3) + 40;
		sptr->TransType = 2;

		sptr->x = x + (GetRandomControl() & 0x1F) - 16;
		sptr->y = y + (GetRandomControl() & 0x1F) - 16;
		sptr->z = z + (GetRandomControl() & 0x1F) - 16;

		sptr->Xvel = ((GetRandomControl() & 0x1FF) - 256) << 1;
		sptr->Zvel = ((GetRandomControl() & 0x1FF) - 256) << 1;

		if (lp < 12)
		{
			sptr->Yvel = (GetRandomControl() & 0x1F);
			sptr->Friction = 64;
		}
		else
		{
			//loc_4426C
			sptr->Yvel = (GetRandomControl() & 0x1FF) + 256;
			sptr->Friction = 82;
		}

		//loc_44284
		sptr->Flags = 16;
		sptr->RotAng = (GetRandomControl() & 0xFFF);
		sptr->RotAdd = (GetRandomControl() & 0x40) - 32;
		sptr->MaxYvel = 0;
		sptr->Gravity = 0;

		size = (GetRandomControl() & 0xF) + 48;

		sptr->dSize = size << 1;
		sptr->sSize = size >> 2;
		sptr->Size = size >> 2;
		sptr->mirror = 0;
	}
}

void DoGrenadeDamageOnBaddie(struct ITEM_INFO* baddie, struct ITEM_INFO* item)//43FB0(<), ? (F)
{
	if (!(baddie->flags & 0x8000))
	{
		if (baddie == lara_item && baddie->hit_points > 0)
		{
			baddie->hit_points -= 50;

			if (!(room[item->room_number].flags & RF_FILL_WATER) && baddie->hit_points < 51)
			{
				LaraBurn();
			}//loc_44128
		}
		else
		{
			//loc_4404C
			if (item->item_flags[2] == 0)
			{
				baddie->hit_status = 1;

				if (!objects[baddie->object_number].undead)
				{
					HitTarget(baddie, NULL, 30, 1);

					if (baddie != lara_item)
					{
						savegame.Game.AmmoHits++;

						if (baddie->hit_points <= 0)
						{
							savegame.Level.Kills++;
							CreatureDie((baddie - items), 1);
						}//loc_44128
					}//loc_44128
				}//loc_44128
			}//loc_44128
		}
	}//loc_44128
}

void AnimateShotgun(int weapon_type)
{
	UNIMPLEMENTED();
}

void undraw_shotgun(int weapon_type)//436B0(<), 43B14(<) (F)
{
	struct ITEM_INFO* item = &items[lara.weapon_item];
	AnimateItem(item);

	if (item->status == ITEM_DEACTIVATED)
	{
		lara.gun_status = LG_NO_ARMS;
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
		if (item->current_anim_state == STATE_LARA_JUMP_FORWARD)
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
		item->goal_anim_state = STATE_LARA_RUN_FORWARD;
		item->current_anim_state = STATE_LARA_RUN_FORWARD;
		item->room_number = NO_ROOM;

		lara.left_arm.frame_base = lara.right_arm.frame_base = objects[item->object_number].frame_base;
	}
	else
	{
		item = &items[lara.weapon_item];
	}

	AnimateItem(item);

	if (item->current_anim_state != STATE_LARA_WALK_FORWARD &&
		item->current_anim_state != STATE_LARA_TURN_RIGHT_SLOW)
	{
		if (item->frame_number - anims[item->anim_number].frame_base == weapons[weapon_type].draw_frame)
		{
			draw_shotgun_meshes(weapon_type);
		}
		else if (lara.water_status == LW_UNDERWATER)
		{
			item->goal_anim_state = STATE_LARA_TURN_RIGHT_SLOW;
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
	UNIMPLEMENTED();
}

void CrossbowHitSwitchType78(struct ITEM_INFO* item, struct ITEM_INFO* target, int MustHitLastNode)
{
	UNIMPLEMENTED();
}

void FireCrossbow(struct PHD_3DPOS* Start)
{
	UNIMPLEMENTED();
}

void FireHK(int running)
{
	UNIMPLEMENTED();
}

void FireShotgun()
{
	UNIMPLEMENTED();
}

void RifleHandler(int weapon_type)
{
	UNIMPLEMENTED();
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