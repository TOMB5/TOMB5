#include "FXTRIG.H"

#include "SPECIFIC.H"

#include <stdio.h>

void PrintString(unsigned short x, unsigned short y, unsigned char colourFlag, char* string, unsigned short flag)//8DB4C, 8FB90
{
	printf("PrintString - X:%d Y:%d C:%d - %s\n", x, y, colourFlag, string);
}

void SetGunFlash(short gun_type)
{
	UNIMPLEMENTED();
}

void DoBloodSplat(long x, long y, long z, int random, short y_rot, short room_number)
{
	UNIMPLEMENTED();
}

void TriggerRicochetSpark(struct GAME_VECTOR* hit_pos, short y_rot, int unk00, int unk01)
{
	UNIMPLEMENTED();
}
