#include "LARAFIRE.H"
#include "GAMEFLOW.H"
#include "SPECIFIC.H"

struct GAME_VECTOR bum_vdest;
struct GAME_VECTOR bum_vsrc;
struct PHD_3DPOS bum_view;
struct ITEM_INFO *TargetList[8];
struct ITEM_INFO *LastTargets[8];
struct WEAPON_INFO weapons[9];

short *get_current_ammo_pointer(int num)//4965C, 49AC0
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
	S_Warn("[WeaponObjectMesh] - Unimplemented!\n");
	return 0;
}

int WeaponObject(int weapon_type)//48898, 48CFC
{
	S_Warn("[WeaponObject] - Unimplemented!\n");
	return 0;
}

void HitTarget(struct ITEM_INFO *item, struct GAME_VECTOR *hitpos, int damage, int grenade)//486E0, 48B44
{
	S_Warn("[HitTarget] - Unimplemented!\n");
}

int FireWeapon(int weapon_type, struct ITEM_INFO *target, struct ITEM_INFO *src, short *angles)//48328, 4878C
{
	S_Warn("[FireWeapon] - Unimplemented!\n");
	return 0;
}

void AimWeapon(struct WEAPON_INFO *winfo, struct lara_arm *arm)//4826C, 486D0
{
	S_Warn("[AimWeapon] - Unimplemented!\n");
}

void find_target_point(struct ITEM_INFO *item, struct GAME_VECTOR *target)//48150, 485B4
{
	S_Warn("[find_target_point] - Unimplemented!\n");
}

void LaraGetNewTarget(struct WEAPON_INFO *winfo)//47B28, 47F8C
{
	S_Warn("[LaraGetNewTarget] - Unimplemented!\n");
}

void LaraTargetInfo(struct WEAPON_INFO *winfo)//4789C, 47D00
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
