#include "LARA1GUN.H"

#include "BOX.H"
#include "CONTROL.H"
#include "EFFECTS.H"
#include "EFFECT2.H"
#include "SAVEGAME.H"
#include "SOUND.H"
#include "SPECIFIC.H"
#ifdef PC_VERSION
#include "GAME.H"
#else
#include "PSOUTPUT.H"
#include "SETUP.H"
#include "FXTRIG.H"
#endif
#include "TOMB4FX.H"
#include "TRAPS.H"
#include "DRAW.H"
#include "LARA.H"
#include "LARAFIRE.H"
#if PSX_VERSION || PSXPC_VERSION || SAT_VERSION
#include "MISC.H"
#include "CALCLARA.H"
#endif
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

void FireCrossbow(struct PHD_3DPOS* Start)//42E18(<), 4326C(<) (F)
{
	short* ammo;
	struct ITEM_INFO* item;
	short item_number;

	ammo = get_current_ammo_pointer(WEAPON_CROSSBOW);

	if (ammo[0] != 0)
	{
		lara.has_fired = 1;
		lara.Fired = 1;
		item_number = CreateItem();

		if (item_number != -1)
		{
			item = &item[item_number];

			item->object_number = CROSSBOW_BOLT;
			item->shade = -15856;
			item->room_number = lara_item->room_number;
			item->pos.x_pos = Start->x_pos;
			item->pos.y_pos = Start->y_pos;
			item->pos.z_pos = Start->z_pos;

			InitialiseItem(item_number);

			item->pos.x_rot = Start->x_rot;
			item->pos.y_rot = Start->y_rot;
			item->speed = 512;
			item->pos.z_rot = Start->z_rot;

			AddActiveItem(item_number);
#if !BETA_VERSION//Nice last minute bug fix CORE! >_<
			if (ammo[0] != -1)
			{
#endif
				ammo[0]--;
#if !BETA_VERSION
			}
#endif

#if PSX_VERSION || PSXPC_VERSION
			SetupPadVibration(0, 4096, 4096, 2, 1536, 5);
#endif
			SoundEffect(SFX_LARA_CROSSBOW, NULL, 0);
			savegame.Game.AmmoUsed++;
		}//loc_42F60
	}//loc_42F60
}

void FireHK(int running)//42CA8(<), 430FC(<) (F)
{
	short angles[2];

	if (lara.hk_type_carried & 0x8)
	{
		HKTimer = 12;
	}
	else if (lara.hk_type_carried & 0x10)
	{
		//loc_42CE0
		HKShotsFired++;

		if ((HKShotsFired & 0xFF) == 5)
		{
			HKShotsFired = 0;
			HKTimer = 12;
		}//loc_42D14
	}//loc_42D14

	angles[1] = lara.left_arm.x_rot;
	angles[0] = lara.left_arm.y_rot + lara_item->pos.y_rot;

	if (!lara.left_arm.lock)
	{
		angles[1] = lara_item->pos.y_rot + lara.torso_y_rot;
		angles[0] = lara.left_arm.x_rot + lara.torso_x_rot;
	}//loc_42D58

	if (running)
	{
		weapons[WEAPON_HK].shot_accuracy = 0x888;
		weapons[WEAPON_HK].damage = 1;
	}
	else
	{
		//loc_42D74
		weapons[WEAPON_HK].shot_accuracy = 0x2D8;
		weapons[WEAPON_HK].damage = 3;
	}

	if (FireWeapon(WEAPON_HK, lara.target, lara_item, &angles[0]))
	{
		SmokeCountL = 12;
		SmokeWeapon = WEAPON_HK;
#if PSX_VERSION
		TriggerGunShell(1, 369, 5);
#endif
		lara.right_arm.flash_gun = weapons[WEAPON_HK].flash_time;
#if PSX_VERSION
		SetupPadVibration(0, 4096, 4096, 2, 4096, 2);
#endif
	}//loc_42E04
}

void FireShotgun()//429F0(<), 42E44(<) (F)
{
	struct PHD_VECTOR pos;
	short angles[2];
	short dangles[2];
	int i;
	int r;
	int fired;
	int x;
	int y;
	int z;
	int lp;
	int scatter;

	angles[1] = lara.left_arm.x_rot;
	angles[0] = lara.left_arm.y_rot + lara_item->pos.y_rot;

	if (!lara.left_arm.lock)
	{
		angles[0] += lara.torso_y_rot;
		angles[1] += lara.torso_x_rot;
	}
	//loc_42A6C
	fired = 0;

	if (lara.shotgun_type_carried & 8)
	{
		scatter = 1820;
	}
	else
	{
		scatter = 5460;
	}
	//loc_42A88
	//loc_42A98
	for(i = 0; i < 6; i++)
	{
		r = (GetRandomControl() - 16384) * scatter;
		if (r < 0)
		{
			r += 65535;
		}

		//loc_42AB8
		dangles[0] = angles[0] + (r >> 16);

		r = (GetRandomControl() - 16384) * scatter;
		if (r < 0)
		{
			r += 65535;
		}

		//loc_42AE8
		dangles[1] = angles[1] + (r >> 16);

		if (FireWeapon(WEAPON_SHOTGUN, lara.target, lara_item, &dangles[0]))
		{
			fired = 1;
		}
		//loc_42B18
	}

	if (fired)
	{
		pos.x = 0;
		pos.y = 228;
		pos.z = 32;

		GetLaraJointPos(&pos, 11);

		x = pos.x;
		y = pos.y;
		z = pos.z;

		pos.x = 0;
		pos.y = 1508;
		pos.z = 32;

		GetLaraJointPos(&pos, 11);

		SmokeCountL = 32;
		SmokeWeapon = WEAPON_SHOTGUN;

		//s7 = 0xB0000
		if (lara_item->mesh_bits != 0)
		{
			//loc_42BB0
			for(lp = 0; lp < 7; lp++)
			{
				TriggerGunSmoke(x, y, z, pos.x - x, pos.y - y, pos.z - z, 1, SmokeWeapon, 32);
			}
		}//loc_42BFC

		lara.right_arm.flash_gun = weapons[WEAPON_SHOTGUN].flash_time;
		SoundEffect(SFX_EXPLOSION1, &lara_item->pos, 0x1400004);
		SoundEffect(weapons[WEAPON_SHOTGUN].sample_num, &lara_item->pos, 0);
#if PSX_VERSION
		SetupPadVibration(0, 4096, 4096, 2, 1536, 5);
#endif
		savegame.Game.AmmoUsed++;
	}//loc_42C78
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