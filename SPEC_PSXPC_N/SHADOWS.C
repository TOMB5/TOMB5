#include "SHADOWS.H"

#include <stdint.h>

void S_DrawGouraudBar(int unk00, int unk01, int unk02, int time, GouraudBarColourSet* colour)
{
	return;
}

long OptimiseOTagR(uintptr_t* ot, int nOTSize)//86CC4(<), 88D08(<)
{
	uintptr_t* a1;
	uintptr_t* a3;
	uintptr_t v0;
	uintptr_t* v1;
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

		if ((uintptr_t*)v0 == a1)
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
			} while ((uintptr_t*) v0 == a1);

			//loc_86D08
			a3[0] = v0;
		}
		v0 = a1[0];
	} while (a1 != ot);

	//loc_86D0C
	return at;
}
