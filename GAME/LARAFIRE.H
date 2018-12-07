#ifndef LARAFIRE_H
#define LARAFIRE_H

#include "SPECTYPES.H"

extern struct GAME_VECTOR bum_vdest;
extern struct GAME_VECTOR bum_vsrc;
extern struct PHD_3DPOS bum_view;
extern struct ITEM_INFO* TargetList[8];
extern struct ITEM_INFO* LastTargets[8];
extern struct WEAPON_INFO weapons[9];

extern short* get_current_ammo_pointer(int num);
extern void DoProperDetection(short item_number, long x, long y, long z, long xv, long yv, long zv);
extern int WeaponObjectMesh(int weapon_type);
extern int WeaponObject(int weapon_type);
extern void HitTarget(struct ITEM_INFO* item, struct GAME_VECTOR* hitpos, int damage, int grenade);
extern int FireWeapon(int weapon_type, struct ITEM_INFO* target, struct ITEM_INFO* src, short* angles);
extern void AimWeapon(struct WEAPON_INFO* winfo, struct lara_arm* arm);
extern void find_target_point(struct ITEM_INFO* item, struct GAME_VECTOR* target);
extern void LaraGetNewTarget(struct WEAPON_INFO* winfo);
extern void LaraTargetInfo(struct WEAPON_INFO* winfo);
extern void InitialiseNewWeapon();
extern void LaraGun();

#endif
