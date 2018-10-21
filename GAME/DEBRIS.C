#include "DEBRIS.H"

#include "SPECIFIC.H"

struct DEBRIS_STRUCT debris[128];
short DebrisFlags;
long next_debris;

long GetFreeDebris()//366B0(<), 36BB0(<) (F)
{
	struct DEBRIS_STRUCT* dptr;
	long lp = 0;
	long eldestage = -16383;
	long eldestfree = 0;
	long free = next_debris;

	dptr = &debris[free];

	for (lp = 0; lp < 128; lp++)
	{
		if (!dptr->On)
		{
			next_debris = (free + 1) & 0x7F;
			return free;
		}

		if (eldestage < dptr->Yvel)
		{
			eldestfree = free;
			eldestage = dptr->Yvel;
		}

		if (free == 0x7F)
		{
			free = 0;
			dptr = &debris[free];
		}
		else
		{
			dptr++;
		}
	}

	next_debris = (eldestfree + 1) & 0x7F;

	return eldestfree;
}

void TriggerDebris(struct GAME_VECTOR* pos, void* TextInfo, short* Offsets, long* Vels, int rgb)//3675C, 36C5C
{
	UNIMPLEMENTED();
}

void ShatterObject(struct SHATTER_ITEM* ShatterItem, struct MESH_INFO* StaticMesh, short Num, short RoomNumber, int NoXZVel)//36A3C, 36F3C
{
	UNIMPLEMENTED();
}