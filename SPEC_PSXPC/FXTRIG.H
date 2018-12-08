#ifndef FXTRIG_H
#define FXTRIG_H

extern void PrintString(unsigned short x, unsigned short y, unsigned char colourFlag, char* string, unsigned short flag);
extern void SetGunFlash(short gun_type);
extern void DoBloodSplat(long x, long y, long z, int random, short y_rot, short room_number);
extern void TriggerRicochetSpark(struct GAME_VECTOR* hit_pos, short y_rot, int unk00, int unk01);

#endif