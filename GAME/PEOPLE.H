#ifndef PEOPLE_H
#define PEOPLE_H

#include "SPECTYPES.H"

extern int ShotLara(struct ITEM_INFO* item, struct AI_info* info, struct BITE_INFO* gun, short extra_rotation, int damage);
extern short GunMiss(long x, long y, long z, short speed, int yrot, int room_number);
extern short GunHit(long x, long y, long z, short speed, int yrot, int room_number);
extern short GunShot(long x, long y, long z, short speed, int yrot, int room_number);
extern int Targetable(struct ITEM_INFO* item, struct AI_info* info);
extern int TargetVisible(struct ITEM_INFO* item, struct AI_info* info);

#endif