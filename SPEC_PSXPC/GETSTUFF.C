#include "GETSTUFF.H"

#include "SPECIFIC.H"

long DIVFP(long A, long B)
{
	return (A / (B >> 8)) << 8;
}

long MULFP(long A, long B)
{
	if (A && B != 0)
	{
		return ((A % B) << 16) | ((A * B) >> 16);
	}
	else
	{
		return ((A * B) >> 16);
	}
}

int xLOS(struct GAME_VECTOR* start, struct GAME_VECTOR* target)
{
	UNIMPLEMENTED();
	return 0;
}

int zLOS(struct GAME_VECTOR* start, struct GAME_VECTOR* target)
{
	UNIMPLEMENTED();
	return 0;
}
