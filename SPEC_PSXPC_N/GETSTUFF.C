#include "GETSTUFF.H"

#include "SPECIFIC.H"

long DIVFP(long A, long B)
{
	return (A / (B >> 8)) << 8;
}

long MULFP(long A, long B)
{
	unsigned long long result = (long long)((long long)(int)A * (long long)(int)B);
	return ((result >> 32) << 16) | ((result & 0xFFFFFFFF) >> 16);
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
