#include "MATHS.H"

long phd_sqrt_asm(long val) // (F)
{
	long root = 0;
	long remainder = val;
	long place = 0x40000000;

	do
	{
		if (remainder >= root + place)
		{
			remainder -= root + place;
			root |= place << 1;
		}

		place >>= 2;
		root >>= 1;
	} while (place);

	return root;
}