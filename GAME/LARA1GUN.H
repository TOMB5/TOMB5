#ifndef LARAONEGUN_H
#define LARAONEGUN_H

extern char HKTimer;
extern char HKShotsFired;

extern void TriggerGrapplingEffect(long x, long y, long z);
extern void DoGrenadeDamageOnBaddie(struct ITEM_INFO *baddie, struct ITEM_INFO *item);
extern void AnimateShotgun(int weapon_type);
extern void undraw_shotgun(int weapon_type);
extern void draw_shotgun(int weapon_type);
extern void ControlCrossbow(short item_number);
extern void CrossbowHitSwitchType78(struct ITEM_INFO *item, struct ITEM_INFO *target, int MustHitLastNode);
extern void FireCrossbow(struct PHD_3DPOS *Start);
extern void FireHK(int running);
extern void FireShotgun();
extern void RifleHandler(int weapon_type);
extern void ready_shotgun(int weapon_type);
extern void undraw_shotgun_meshes(int weapon_type);
extern void draw_shotgun_meshes(int weapon_type);

#endif