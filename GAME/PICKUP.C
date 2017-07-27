#include "PICKUP.H"

#include "ITEMS.H"

void RegeneratePickups()//515AC, 51A10
{
	struct ITEM_INFO* item;
	short objnum; // $v1
	short lp; // $v1
	short *ammo; // $v0
}

void CollectCarriedItems(struct ITEM_INFO* item)
{
	struct ITEM_INFO* pickup; // $s0
	short pickup_number; // $s1

#if 0

		//move	$s3, $a0
		pickup_number = item->carried_item;
		int v0 = -1;
		
		if (pickup_number != -1)
		{
			int s2 = -1;
			v0 = pickup_number << 3;

			loc_533CC:
			v0 += pickup_number;
			pickup = &items[0];
			v0 <<= 4;
			s0 += v0;

			//AddDisplayPickup(pickup->object_number);
			//KillItem(pickup->object_number);

			pickup_number = pickup->carried_item;
			sll	$v0, $s1, 3
			bne	$s1, $s2, loc_533CC
			
		}

		item->carried_item = -1;
#endif
}