#include "FXTRIG.H"

#include "CONTROL.H"
#include "EFFECT2.H"
#include "GPU.H"
#include "SPECIFIC.H"
#include "TEXT.H"
#include "MISC.H"

#include <stdio.h>
#include "DRAW.H"
#include "DELTAPAK.H"
#include "TOMB4FX.H"

void SetGunFlash(short gun_type)
{
	UNIMPLEMENTED();
}

void TriggerRicochetSpark(struct GAME_VECTOR* hit_pos, short y_rot, int unk00, int unk01)
{
	UNIMPLEMENTED();
}

void TriggerGunShell(long x, long y, long z)
{
	UNIMPLEMENTED();
}

void TriggerUnderwaterBlood(int x, int y, int z, int sizeme)// (F)
{
	int i;

	for (i = 0; i < 32; i++)
	{
		if (!(ripples[i].flags & 1))
		{
			ripples[i].flags = 0x31;
			ripples[i].init = 1;
			ripples[i].life = (GetRandomControl() & 7) - 16;
			ripples[i].size = sizeme;
			ripples[i].x = (GetRandomControl() & 0x3F) + x - 32;
			ripples[i].y = y;
			ripples[i].z = (GetRandomControl() & 0x3F) + z - 32;
			return;
		}
	}
}

short DoBloodSplat(long x, long y, long z, short random, short y_rot, short room_number)
{
	GetFloor(x, y, z, &room_number);

	if (room[room_number].flags & RF_FILL_WATER)
		TriggerUnderwaterBlood(x, y, z, random);
	else
		TriggerBlood(x, y, z, y_rot >> 4, random);

	return -1;
}