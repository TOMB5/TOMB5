#include "LARAFIRE.H"

#include "GAMEFLOW.H"
#include "LARA.H"
#include "OBJECTS.H"
#include "SPECIFIC.H"

struct GAME_VECTOR bum_vdest;
struct GAME_VECTOR bum_vsrc;
struct PHD_3DPOS bum_view;
struct ITEM_INFO* TargetList[8];
struct ITEM_INFO* LastTargets[8];
static short HoldStates[18] =
{
	0x0000, 0x0001, 0x0002, 0x0004, 0x0006, 0x0007, 0x0010, 0x0014, 0x0016, 0x0015, 
	0x0041, 0x0027, 0x0028, 0x0029, 0x0047, 0x0069, 0x006A, 0xFFFF
};
struct WEAPON_INFO weapons[9] =
{
	{ { ANGLE(0), ANGLE(0), ANGLE(0), ANGLE(0) },{ ANGLE(0), ANGLE(0), ANGLE(0), ANGLE(0) },{ ANGLE(0), ANGLE(0), ANGLE(0), ANGLE(0) }, 0x0000, 0x0000, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x0000 },
	{ { 54616, ANGLE(60), 54616, ANGLE(60) },{ 34596, ANGLE(60), 50976, ANGLE(80) },{ 54616, ANGLE(170), 50976, ANGLE(80) }, 0x071C, 0x05B0, 0x028A, 0x2000, 0x01, 0x09, 0x03, 0x00, 0x0008 },
	{ { 54616, ANGLE(60), 54616, ANGLE(60) },{ 63716, ANGLE(10), 50976, ANGLE(80) },{ ANGLE(0), ANGLE(0), ANGLE(0), ANGLE(0) }, 0x071C, 0x02D8, 0x028A, 0x2000, 0x15, 0x10, 0x03, 0x00, 0x0079 },
	{ { 54616, ANGLE(60), 54616, ANGLE(60) },{ 34596, ANGLE(60), 50976, ANGLE(80) },{ 54616, ANGLE(170), 50976, ANGLE(80) }, 0x071C, 0x05B0, 0x028A, 0x2000, 0x01, 0x03, 0x03, 0x00, 0x002B },
	{ { 54616, ANGLE(60), 55526, ANGLE(55) },{ 50976, ANGLE(80), 53706, ANGLE(65) },{ 50976, ANGLE(80), 53706, ANGLE(65) }, 0x071C, 0x0000, 0x01F4, 0x2000, 0x03, 0x09, 0x03, 0x0A, 0x002D },
	{ { 54616, ANGLE(60), 55526, ANGLE(55) },{ 50976, ANGLE(80), 53706, ANGLE(65) },{ 50976, ANGLE(80), 53706, ANGLE(65) }, 0x071C, 0x02D8, 0x01F4, 0x3000, 0x04, 0x00, 0x03, 0x10, 0x0000 },
	{ { 54616, ANGLE(60), 55526, ANGLE(55) },{ 50976, ANGLE(80), 53706, ANGLE(65) },{ 50976, ANGLE(80), 53706, ANGLE(65) }, 0x071C, 0x05B0, 0x01F4, 0x2000, 0x05, 0x00, 0x02, 0x0A, 0x0000 },
	{ { ANGLE(0), ANGLE(0), ANGLE(0), ANGLE(0) },{ ANGLE(0), ANGLE(0), ANGLE(0), ANGLE(0) },{ ANGLE(0), ANGLE(0), ANGLE(0), ANGLE(0) }, 0x0000, 0x0000, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x0000 },
	{ { 60076, ANGLE(30), 55526, ANGLE(55) },{ 60076, ANGLE(30), 55526, ANGLE(55) },{ 60076, ANGLE(30), 55526, ANGLE(55) }, 0x071C, 0x05B0, 0x0190, 0x2000, 0x03, 0x00, 0x02, 0x00, 0x002B },
};

short* get_current_ammo_pointer(int num)//4965C, 49AC0
{
	S_Warn("[get_current_ammo_pointer] - Unimplemented!\n");
	return 0;
}

void DoProperDetection(short item_number, long x, long y, long z, long xv, long yv, long zv)//48984, 48DE8
{
	S_Warn("[DoProperDetection] - Unimplemented!\n");
}

int WeaponObjectMesh(int weapon_type)//488F4, 48D58
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

void HitTarget(struct ITEM_INFO* item, struct GAME_VECTOR* hitpos, int damage, int grenade)//486E0, 48B44
{
	S_Warn("[HitTarget] - Unimplemented!\n");
}

int FireWeapon(int weapon_type, struct ITEM_INFO* target, struct ITEM_INFO* src, short* angles)//48328, 4878C
{
	S_Warn("[FireWeapon] - Unimplemented!\n");
	return 0;
}

void AimWeapon(struct WEAPON_INFO* winfo, struct lara_arm* arm)//4826C, 486D0
{
	S_Warn("[AimWeapon] - Unimplemented!\n");
}

void find_target_point(struct ITEM_INFO* item, struct GAME_VECTOR* target)//48150, 485B4
{
	S_Warn("[find_target_point] - Unimplemented!\n");
}

void LaraGetNewTarget(struct WEAPON_INFO* winfo)//47B28, 47F8C
{
	S_Warn("[LaraGetNewTarget] - Unimplemented!\n");
}

void LaraTargetInfo(struct WEAPON_INFO* winfo)//4789C, 47D00
{
	S_Warn("[LaraTargetInfo] - Unimplemented!\n");
}

void InitialiseNewWeapon()//4772C, 47B90
{
	S_Warn("[InitialiseNewWeapon] - Unimplemented!\n");
}

void LaraGun()//46F28, 4738C
{
	S_Warn("[LaraGun] - Unimplemented!\n");
}

int CheckForHoldingState(int state)//46EE4, 47348
{
	S_Warn("[CheckForHoldingState] - Unimplemented!\n");
	return 0;
}