#include "SHADOWS.H"

#ifndef USE_ASM
long OptimiseOTagR(unsigned long* ot, int nOTSize)//86CC4(<), 88D08(<)
{
	unsigned long* a1;
	unsigned long* a3;
	unsigned long v0;
	unsigned long* v1;
	long at = 0;

	if (nOTSize < 8)
	{
		return 0;
	}

	a1 = &ot[nOTSize - 1];
	v1 = &ot[1];
	v0 = a1[0];

	//loc_86CE4
	do
	{
		a1--;

		if ((unsigned long*)v0 == a1)
		{
			a3 = a1 - 1;
			if (a1 == ot)
			{
				return at;
			}

			//loc_86CF4
			do
			{
				v0 = a1[0];
				a1--;
				if (a1 == v1)
				{
					break;
				}

				at++;
			} while ((unsigned long*) v0 == a1);

			//loc_86D08
			a3[0] = v0;
		}
		v0 = a1[0];
	} while (a1 != ot);

	//loc_86D0C
	return at;
}
#endif