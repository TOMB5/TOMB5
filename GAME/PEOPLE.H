#ifndef PEOPLE_H
#define PEOPLE_H

#include "SPECTYPES.H"

extern int ShotLara(ITEM_INFO* item, AI_info* info, BITE_INFO* gun, short extra_rotation, int damage);
extern short GunMiss(long x, long y, long z, short speed, int yrot, int room_number);
extern short GunHit(long x, long y, long z, short speed, int yrot, int room_number);
extern short GunShot(long x, long y, long z, short speed, int yrot, int room_number);
extern int Targetable(ITEM_INFO* item, AI_info* info);
extern int TargetVisible(ITEM_INFO* item, AI_info* info);

#endif