#include "GETSTUFF.H"

#ifndef USE_ASM
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
#endif