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

#ifdef PC_VERSION
#include "GAME.H"
#include "CONTROL.H"
#else
#include "SETUP.H"
#include "MISC.H"
#include "FXTRIG.H"
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

void LaraGun()//46F28, 4738C
{
	UNIMPLEMENTED();
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
