#include "LARAFIRE.H"

#include "EFFECTS.H"
#include "GAMEFLOW.H"
#include "LARA.H"
#include "OBJECTS.H"
#include "SPECIFIC.H"
#include "LARA2GUN.H"
#include "LARA1GUN.H"
#include "DRAW.H"
#include "LARAFLAR.H"
#include "SAVEGAME.H"
#include "SOUND.H"
#include "TOMB4FX.H"
#include "FLMTORCH.H"
#include "CONTROL.H"
#include "CAMERA.H"

#ifdef PC_VERSION
#include "GAME.H"
#include "CONTROL.H"
#else
#include "SETUP.H"
#include "MISC.H"
#include "FXTRIG.H"
#include "PSXINPUT.H"
#endif

struct GAME_VECTOR bum_vdest;
struct GAME_VECTOR bum_vsrc;
struct PHD_3DPOS bum_view;
struct ITEM_INFO* TargetList[8];
struct ITEM_INFO* LastTargets[8];
static short HoldStates[18] =
{
	0, 1, 2, 4, 6, 7, 16, 20, 22, 21, 65, 39, 40, 41, 71, 105, 106, -1
};
struct WEAPON_INFO weapons[9] =
{
	{ { ANGLE(0), ANGLE(0), ANGLE(0), ANGLE(0) },{ ANGLE(0), ANGLE(0), ANGLE(0), ANGLE(0) },{ ANGLE(0), ANGLE(0), ANGLE(0), ANGLE(0) }, 0x0000, 0x0000, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x0000 },
	{ { -10920, ANGLE(60), -10920, ANGLE(60) },{ -30940, ANGLE(60), -14560, ANGLE(80) },{ -10920, ANGLE(170), -14560, ANGLE(80) }, 0x071C, 0x05B0, 0x028A, 0x2000, 0x01, 0x09, 0x03, 0x00, 0x0008 },
	{ { -10920, ANGLE(60), -10920, ANGLE(60) },{ -1820, ANGLE(10), -14560, ANGLE(80) },{ ANGLE(0), ANGLE(0), ANGLE(0), ANGLE(0) }, 0x071C, 0x02D8, 0x028A, 0x2000, 0x15, 0x10, 0x03, 0x00, 0x0079 },
	{ { -10920, ANGLE(60), -10920, ANGLE(60) },{ -30940, ANGLE(60), -14560, ANGLE(80) },{ -10920, ANGLE(170), -14560, ANGLE(80) }, 0x071C, 0x05B0, 0x028A, 0x2000, 0x01, 0x03, 0x03, 0x00, 0x002B },
	{ { -10920, ANGLE(60), -10010, ANGLE(55) },{ -14560, ANGLE(80), -11830, ANGLE(65) },{ -14560, ANGLE(80), -11830, ANGLE(65) }, 0x071C, 0x0000, 0x01F4, 0x2000, 0x03, 0x09, 0x03, 0x0A, 0x002D },
	{ { -10920, ANGLE(60), -10010, ANGLE(55) },{ -14560, ANGLE(80), -11830, ANGLE(65) },{ -14560, ANGLE(80), -11830, ANGLE(65) }, 0x071C, 0x02D8, 0x01F4, 0x3000, 0x04, 0x00, 0x03, 0x10, 0x0000 },
	{ { -10920, ANGLE(60), -10010, ANGLE(55) },{ -14560, ANGLE(80), -11830, ANGLE(65) },{ -14560, ANGLE(80), -11830, ANGLE(65) }, 0x071C, 0x05B0, 0x01F4, 0x2000, 0x05, 0x00, 0x02, 0x0A, 0x0000 },
	{ { ANGLE(0), ANGLE(0), ANGLE(0), ANGLE(0) },{ ANGLE(0), ANGLE(0), ANGLE(0), ANGLE(0) },{ ANGLE(0), ANGLE(0), ANGLE(0), ANGLE(0) }, 0x0000, 0x0000, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x0000 },
	{ { -5460, ANGLE(30), -10010, ANGLE(55) },{ -5460, ANGLE(30), -10010, ANGLE(55) },{ -5460, ANGLE(30), -10010, ANGLE(55) }, 0x071C, 0x05B0, 0x0190, 0x2000, 0x03, 0x00, 0x02, 0x00, 0x002B },
};

short* get_current_ammo_pointer(int num)//4965C(<), 49AC0 (F)
{
	short* ammo;

	switch (num)
	{
	case WEAPON_REVOLVER:
		//loc_496AC
		ammo = &lara.num_revolver_ammo;
		break;
	case WEAPON_UZI:
		//loc_496B8
		ammo = &lara.num_uzi_ammo;
		break;
	case WEAPON_SHOTGUN:
		//loc_49688
		if ((lara.shotgun_type_carried & 8))
		{
			ammo = &lara.num_shotgun_ammo1;
		}
		else
		{
			ammo = &lara.num_shotgun_ammo2;
		}
		break;
	case WEAPON_HK:
		//loc_496C4
		ammo = &lara.num_hk_ammo1;
		break;
	case WEAPON_CROSSBOW:
		//loc_496D0
		if ((lara.crossbow_type_carried & 8))
		{
			ammo = &lara.num_crossbow_ammo1;
		}
		else
		{
			ammo = &lara.num_crossbow_ammo2;
		}
		break;
	default:
		ammo = &lara.num_pistols_ammo;
		break;
	}

	return ammo;
}

void DoProperDetection(short item_number, long x, long y, long z, long xv, long yv, long zv)//48984, 48DE8
{
	UNIMPLEMENTED();
}

int WeaponObjectMesh(int weapon_type)//488F4, 48D58 (F)
{
	switch (weapon_type)
	{
	case WEAPON_REVOLVER:
		return (lara.sixshooter_type_carried & WTYPE_LASERSIGHT) != 0 ? LARA_REVOLVER_LASER : REVOLVER_ANIM;
	case WEAPON_UZI:
		return UZI_ANIM;
	case WEAPON_SHOTGUN:
		return SHOTGUN_ANIM;
	case WEAPON_HK:
		return HK_ANIM;
	case WEAPON_CROSSBOW:
		return  (lara.crossbow_type_carried & WTYPE_LASERSIGHT) != 0 ? LARA_CROSSBOW_LASER : CROSSBOW_ANIM;
	default:
		return PISTOLS_ANIM;
	}
}

int WeaponObject(int weapon_type)//48898(<), 48CFC(<) (F)
{
	switch (weapon_type)
	{
	case WEAPON_REVOLVER:
		return REVOLVER_ANIM;
	case WEAPON_UZI:
		return UZI_ANIM;
	case WEAPON_SHOTGUN:
		return SHOTGUN_ANIM;
	case WEAPON_HK:
		return HK_ANIM;
	case WEAPON_CROSSBOW:
		return CROSSBOW_ANIM;
	default:
		return PISTOLS_ANIM;
	}
}

void HitTarget(struct ITEM_INFO* item, struct GAME_VECTOR* hitpos, int damage, int grenade)//486E0(<), 48B44(<) (F)
{
	struct object_info* obj; // $s2

	item->hit_status = 1;
	obj = &objects[item->object_number];

	if (item->data != NULL && item != lara_item)
	{
		((int*)item->data)[3] |= 0x10;
	}//loc_48758

	if (hitpos != NULL && obj->HitEffect != 0)
	{
		if (obj->HitEffect == 4)//*(int*)obj->bite_offset & 0x4000000
		{
			DoBloodSplat(hitpos->x, hitpos->y, hitpos->z, (GetRandomControl() & 3) + 3, item->pos.y_rot, item->room_number);
		}
		else if (obj->HitEffect == 3)//*(int*)obj->bite_offset & 0xC000000
		{
			//loc_487B4
			TriggerRicochetSpark(hitpos, lara_item->pos.y_rot, 3, 0);
		}
		else if (obj->HitEffect == 1)//*(int*)obj->bite_offset & 0x8000000
		{
			TriggerRicochetSpark(hitpos, lara_item->pos.y_rot, 3, -5);
			SoundEffect(SFX_SWORD_GOD_HITMET, &item->pos, SFX_DEFAULT);
		}
	}//loc_48810

	if (obj->undead && grenade == 0 && item->hit_points != -16384)
	{
		return;
	}//loc_4883C

	if (item->hit_points > 0 && damage > item->hit_points)
	{
		savegame.Level.Kills++;
	}//loc_48868

	item->hit_points -= damage;
}

int FireWeapon(int weapon_type, struct ITEM_INFO* target, struct ITEM_INFO* src, short* angles)//48328, 4878C
{
	UNIMPLEMENTED();
	return 0;
}

void AimWeapon(struct WEAPON_INFO* winfo, struct lara_arm* arm)//4826C, 486D0
{
	UNIMPLEMENTED();
}

void find_target_point(struct ITEM_INFO* item, struct GAME_VECTOR* target)//48150, 485B4
{
	UNIMPLEMENTED();
}

void LaraGetNewTarget(struct WEAPON_INFO* winfo)//47B28, 47F8C
{
	UNIMPLEMENTED();
}

void LaraTargetInfo(struct WEAPON_INFO* winfo)//4789C, 47D00
{
	UNIMPLEMENTED();
}

void InitialiseNewWeapon()//4772C, 47B90 (F)
{
	lara.left_arm.frame_number = 0;
	lara.left_arm.x_rot = 0;
	lara.left_arm.y_rot = 0;
	lara.left_arm.z_rot = 0;
	lara.left_arm.lock = 0;
	lara.left_arm.flash_gun = 0;

	lara.right_arm.frame_number = 0;
	lara.right_arm.x_rot = 0;
	lara.right_arm.y_rot = 0;
	lara.right_arm.z_rot = 0;
	lara.right_arm.lock = 0;
	lara.right_arm.flash_gun = 0;

	lara.target = NULL;

	switch (lara.gun_type)
	{
	case WEAPON_PISTOLS:
	case WEAPON_UZI:
		lara.left_arm.frame_base = lara.right_arm.frame_base = objects[PISTOLS_ANIM].frame_base;
		if (lara.gun_status)
			draw_pistol_meshes(lara.gun_type);
		break;

	case WEAPON_REVOLVER:
	case WEAPON_SHOTGUN:
	case WEAPON_HK:
		lara.left_arm.frame_base = lara.right_arm.frame_base = objects[WeaponObject(lara.gun_type)].frame_base;
		if (lara.gun_status)
			draw_shotgun_meshes(lara.gun_type);
		break;

	case WEAPON_FLARE:
		lara.left_arm.frame_base = lara.right_arm.frame_base = objects[FLARE_ANIM].frame_base;
		if (lara.gun_status)
			draw_flare_meshes();
		break;

	default:
		lara.left_arm.frame_base = lara.right_arm.frame_base = anims[lara_item->anim_number].frame_ptr;
		break;
	}
}

static int CheckForHoldingState(int state)//46EE4, 47348 (F)
{
	short* holds = HoldStates;

	do
	{
		if (*holds < 0)
			return FALSE;

		++holds;
	} while (*holds != state);

	return TRUE;
}

void LaraGun()//46F28, 4738C
{
	//a1 = &lara
	//v1 = lara.left_arm.flash_gun
	//v0 = lara.left_arm.flash_gun

	if (lara.left_arm.flash_gun > 0)
	{
		lara.left_arm.flash_gun--;
	}

	//loc_46F5C
	if (lara.right_arm.flash_gun > 0)
	{
		lara.right_arm.flash_gun--;
	}
	//loc_46F70
	if (lara.gun_type == 8)
	{
		DoFlameTorch();
		return;
		//j       def_475A0
	}
	else
	{
		//loc_46F90
		//a2 = lara_item
		if (lara_item->hit_points <= 0)
		{
			lara.gun_status = 0;
			//j       loc_472B8
		}
		else
		{
			//loc_46FB4
			//v0 = 4;
			if (lara.gun_status == 0)
			{
				//v0 = 0x80000
				if ((input & IN_DRAW))
				{
					lara.request_gun_type = lara.last_gun_type;
				}
				if ((input & IN_FLARE))
				{
					//loc_46FE8
					if (!(gfLevelFlags & 0x1))
					{
						if (lara_item->current_anim_state == STATE_LARA_CROUCH_IDLE &&
							lara_item->anim_number != ANIMATION_LARA_CROUCH_IDLE)
						{
							return;
						}
						//loc_4702C
						if (lara.gun_type == WEAPON_FLARE && lara.left_arm.frame_number == 0)
						{
							lara.gun_status = 3;
						}
						else
						{
							//loc_47050
							//v1 = lara.num_flares
							//a0 = lara.num_flares
							if (lara.num_flares != 0)
							{
								if (lara.num_flares == -1)
								{
									lara.request_gun_type = WEAPON_FLARE;
								}
								else
								{
									lara.num_flares--;
								}
							}
						}
					}//loc_47070
				}//loc_47070

				if ((input & IN_DRAW) || lara.request_gun_type != lara.gun_type)
				{
					//v0 = lara_item
					//a0 = lara_item->current_anim_state
					//a1 = &lara
					if (lara_item->current_anim_state == 0x47 || lara_item->current_anim_state == 0x69 || lara_item->current_anim_state == 0x6A &&
						lara.request_gun_type == 4 || lara.request_gun_type == 6 || lara.request_gun_type == 5)
					{
						//loc_470C8
						//v0 = &lara
						//a0 = lara.request_gun_type
						//a1 = &lara
						//loc_470EC
						//a0 = &lara
						if (lara.gun_type == WEAPON_FLARE)
						{
							lara.request_gun_type = lara.gun_type;
						}
					}
					else
					{
						//loc_47108
						//v1 = lara.request_gun_type
						//s0 = &lara
						//v0 = 4
						if (lara.request_gun_type == WEAPON_FLARE || lara.water_status == 0 || (lara.water_status == 4 && -weapons[lara.gun_type].gun_height < lara.water_surface_dist))
						{
							//v1 = lara.gun_type
							//a0 = &weapons[lara.gun_type];
							//v1 = -weapons[lara.gun_type].gun_height
							//v0 = lara.water_surface_dist
							//v1 = &lara
							//s0 = &lara
							//loc_47170
							if (lara.gun_type == WEAPON_FLARE)
							{
								CreateFlare(FLARE_ITEM, 0);
								undraw_flare_meshes();
								lara.flare_control_left = FALSE;
								lara.current_active = FALSE;
							}
							//loc_471A4

							lara.gun_type = lara.request_gun_type;
							InitialiseNewWeapon();
							lara.gun_status = 2;
							lara.right_arm.frame_number = 0;
							lara.left_arm.frame_number = 0;
						}
						//loc_471C4
						//a1 = lara.request_gun_type
						//a0 = lara.gun_type
						lara.last_gun_type = lara.request_gun_type;
						if (lara.gun_type == WEAPON_FLARE)
						{
							lara.request_gun_type = lara.gun_type;
						}
						else
						{
							lara.gun_type = lara.request_gun_type;
						}
					}
				}
				//loc_472BC
			}
			else
			{
				//loc_471E8
				//v0 = 1
				if (lara.gun_status == 4)
				{
					//v0 = 3
					if ((input & IN_DRAW) || lara.request_gun_type == lara.gun_type && lara.water_status != 0 &&
						lara.water_status != 7 || lara.water_surface_dist < -weapons[lara.request_gun_type].gun_height)
					{
						//loc_47268
						lara.gun_status = 3;
						//a0 = &weapons[lara.request_gun_type];
						//v1 = -weapons[lara.request_gun_type].gun_height;
						//v0 = lara.water_surface_dist
						//v0 = 3
						//j loc_472B8
						//loc_472B8
					}
					//loc_472B8
				}
				else
				{
					//loc_47270
					//v0 = &lara
					if (lara.gun_status == 1)
					{
						if ((input & IN_FLARE) && lara_item->current_anim_state == STATE_LARA_CRAWL_IDLE)
						{
							if (lara_item->anim_number == ANIMATION_LARA_CRAWL_IDLE)
							{
								lara.request_gun_type = WEAPON_FLARE;
							}
						}
						//loc_472B8
					}
					//loc_472BC
				}
			}
		}
		//loc_472B8
		//v0 = &lara
		switch (lara.gun_status)
		{
		case 0:
			//loc_475D8
			//s0 = &lara
			//v1 = lara.gun_type
			if (lara.gun_type == 7)
			{
				//v0 = lara_item
				//a0 = lara_item->current_anim_state
				//v1 = -2
				if (CheckForHoldingState(lara_item->current_anim_state))
				{
					//v1 = lara.flags
					if (!lara.flare_control_left)
					{
						lara.left_arm.frame_number = 95;
						lara.flare_control_left = TRUE;
						//j loc_47674
					}
					else
					{
						//loc_47630
						//v0 = lara.left_arm.frame_number
						//v1 = lara.left_arm.frame_number
						if (lara.left_arm.frame_number != 0)
						{
							lara.left_arm.frame_number++;

							if (lara.left_arm.frame_number == 110)
							{
								lara.left_arm.frame_number = 0;
							}
						}//loc_47670
					}
				}
				else
				{
					//loc_47660
					lara.flare_control_left = FALSE;
				}

				//loc_47670
				//s0 = &lara
				DoFlareInHand(lara.flare_age);
				set_flare_arm(lara.left_arm.frame_number);
			}
			//def_475A0
			break;
		case 1:
			//loc_47694
			//s0 = &lara
			//v1 = lara.gun_type
			if (lara.gun_type == 7)
			{
				//v0 = meshes + objects[FLARE_ANIM].mesh_index[26]
				//a0 = meshes
				//a1 = lara.mesh_ptrs[13]

				if (lara.mesh_ptrs[12] == meshes[objects[FLARE_ANIM].mesh_index] + 26)
				{
					//a1 = -2
					;
					//v1 = lara.flags
					//a0 = lara.flare_age
					lara.flare_control_left = FALSE;
					lara.flare_control_left |= CheckForHoldingState(lara_item->current_anim_state) & 1;
					DoFlareInHand(lara.flare_age);
					set_flare_arm(lara.left_arm.frame_number);
				}
				//def_475A0
			}
			//def_475A0
			break;
		case 2:
			//loc_472EC
			//a0 = &lara
			//v0 = 7
			//v1 = lara.gun_type
			//a1 = lara.gun_type
			if (lara.gun_type != WEAPON_FLARE && lara.gun_type != WEAPON_NONE)
			{
				lara.last_gun_type = lara.gun_type;
			}
			//loc_47310
			//a1=  &lara
			switch (lara.gun_type)
			{
			case 1:
			case 2:
			case 3:
				//loc_47350
				//v1 = camera.type
				if (camera.type != CINEMATIC_CAMERA && camera.type != LOOK_CAMERA && camera.type != HEAVY_CAMERA)
				{
					camera.type = COMBAT_CAMERA;
				}

				draw_pistols(lara.gun_type);
				return;
				break;
			case 4:
			case 5:
			case 6:
				//loc_47394
				if (camera.type != CINEMATIC_CAMERA && camera.type != LOOK_CAMERA && camera.type != HEAVY_CAMERA)
				{
					camera.type = COMBAT_CAMERA;
				}
				//loc_473C0
				draw_shotgun(lara.gun_type);
				return;
				break;
			case 7:
				//loc_4747C
				draw_flare();
				return;
				break;
			}

			//def_47348
			lara.gun_status = 0;

			break;
		case 3:
			//loc_473E0
			//a2 = &lara
			//v0 = meshes + objects[LARA].mesh_index
			//a0 = meshes
			//v1 = lara.gun_status
			//a1 = meshes + objects[LARA].mesh_index + 28

			lara.mesh_ptrs[14] = meshes[objects[LARA].mesh_index] + 28;

			switch (lara.gun_status)
			{
			case 1:
			case 2:
			case 3:
				//loc_4743C
				//v0 = &lara
				undraw_pistols(lara.gun_type);
				break;
			case 4:
			case 5:
			case 6:
				//loc_47454
				undraw_shotgun(lara.gun_type);
				break;
			case 7:
				//loc_4746C
				undraw_flare();
				break;
			}

			break;
		case 4:
			//loc_4748C
			//v0 = input
			if ((input & IN_ACTION))
			{
				//v1 = objects[LARA_SCREAM].mesh_index
				lara.mesh_ptrs[14] = meshes[objects[LARA_SCREAM].mesh_index] + 28;
			}
			else
			{
				//loc_474B8
				lara.mesh_ptrs[14] = meshes[objects[LARA].mesh_index] + 28;
			}
			//a0 = [meshes + v1] + 28
			if (camera.type != CINEMATIC_CAMERA && camera.type != LOOK_CAMERA && camera.type != HEAVY_CAMERA)
			{
				camera.type = COMBAT_CAMERA;
			}
			//loc_4750C
			if ((input & IN_ACTION) && get_current_ammo_pointer(lara.gun_type)[0] == 0)
			{
				if (objects[PISTOLS_ITEM].loaded)
				{
					lara.request_gun_type = WEAPON_PISTOLS;
				}
				else
				{
					lara.request_gun_type = WEAPON_NONE;
				}
			}
			else
			{
				//loc_47568
				//v0 = &lara
				//v1 = lara.gun_type
				switch (lara.gun_type)
				{
				case 1:
				case 3:
					//loc_475A8
					PistolHandler(lara.gun_type);
					break;
				case 2:
				case 4:
				case 5:
				case 6:
					//loc_475C0
					RifleHandler(lara.gun_type);
					break;
				}
			}

			break;
		case 5:
			//loc_4747C
			break;
				}

		//def_475A0

			}
		
}