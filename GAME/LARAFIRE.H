#ifndef LARAFIRE_H
#define LARAFIRE_H

#include "SPECTYPES.H"

extern GAME_VECTOR bum_vdest;
extern GAME_VECTOR bum_vsrc;
extern PHD_3DPOS bum_view;
extern ITEM_INFO* TargetList[8];
extern ITEM_INFO* LastTargets[8];
extern WEAPON_INFO weapons[9];

extern short* get_current_ammo_pointer(int num);
extern void DoProperDetection(short item_number, long x, long y, long z, long xv, long yv, long zv);
extern int WeaponObjectMesh(int weapon_type);
extern int WeaponObject(int weapon_type);
extern void HitTarget(ITEM_INFO* item, GAME_VECTOR* hitpos, int damage, int grenade);
extern int FireWeapon(int weapon_type, ITEM_INFO* target, ITEM_INFO* src, short* angles);
extern void AimWeapon(WEAPON_INFO* winfo, lara_arm* arm);
extern void find_target_point(ITEM_INFO* item, GAME_VECTOR* target);
extern void LaraGetNewTarget(WEAPON_INFO* winfo);
extern void LaraTargetInfo(WEAPON_INFO* winfo);
extern void InitialiseNewWeapon();
extern void LaraGun();
extern int CheckForHoldingState(int state);

#endif
