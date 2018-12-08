#include "SPHERE.H"

#include "LARA.H"
#include "SPECIFIC.H"

#if PSX_VERSION || PSXPC_VERSION
#include "SPHERES.H"
#endif

char GotLaraSpheres;
int NumLaraSpheres;
struct SPHERE LaraSpheres[15];
struct SPHERE Slist[34];

int TestCollision(struct ITEM_INFO* item, struct ITEM_INFO* laraitem)//55C3C(<), 560DC(<) (F)
{
	int num1;
	int num2;
	int x1;
	int y1;
	int z1;
	int r1;
	int x;
	int y;
	int z;
	int r;
	int i;
	int j;
	unsigned long flags;
	struct SPHERE* ptr1;
	struct SPHERE* ptr2;

	num1 = GetSpheres(item, &Slist[0], 1);
	flags = 0;

	if (laraitem != item)
	{
		GotLaraSpheres = 0;
	}

	//loc_55C8C
	if (!GotLaraSpheres)
	{
		NumLaraSpheres = num2 = GetSpheres(laraitem, &LaraSpheres[0], 1);

		if (laraitem == lara_item)
		{
			GotLaraSpheres = 1;
		}
	}
	else
	{
		//loc_55CD0
		num2 = NumLaraSpheres;
	}

	laraitem->touch_bits = 0;

	//loc_55CD8
	ptr1 = &Slist[0];

	for (i = 0; i < num1; i++, ptr1++)
	{
		r1 = ptr1->r;

		if (r1 > 0)
		{
			ptr2 = &LaraSpheres[0];

			x1 = ptr1->x;
			y1 = ptr1->y;
			z1 = ptr1->z;

			//loc_55D1C
			for (j = 0; j < num2; j++, ptr2++)
			{
				r += r1;

				if (ptr2->r > 0)
				{
					x = (ptr2->x - x1) * ptr2->x;
					y = (ptr2->y - y1) * ptr2->y;
					z = (ptr2->z - z1) * ptr2->z;
					r *= r;

					if (x + y + z < r)
					{
						flags |= (1 << i);
						laraitem->touch_bits |= (1 << j);
					}//loc_55D14
				}//loc_55D14
			}
		}
	}
	//loc_55DBC
	item->touch_bits = flags;

	return flags;
}