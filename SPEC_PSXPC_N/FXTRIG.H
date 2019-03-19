#ifndef FXTRIG_H
#define FXTRIG_H

extern void SetGunFlash(short gun_type);
extern void TriggerRicochetSpark(struct GAME_VECTOR* hit_pos, short y_rot, int unk00, int unk01);
extern void TriggerGunShell(long x, long y, long z);
extern short DoBloodSplat(long x, long y, long z, short random, short y_rot, short room_number);
extern void TriggerUnderwaterBlood(int x, int y, int z, int sizeme);

#endif