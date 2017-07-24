#include "ITEMS.H"

#include "CONTROL.H"

int level_items;
short next_item_free;
short next_item_active;
short GlobalPulleyFrigItem;

void InitialiseItemArray(int numitems)//418E8(<), 41D3C(<)
{
	next_item_active = -1;

	struct ITEM_INFO* item = &items[0];
	
#if 0
	int a2 = level_items;
	int a1 = level_items;
	int v0 = ((a2 << 3) + level_items) << 4;
#endif

	//FIXME: Ugly
	item = (struct ITEM_INFO*)(char*)item + (((level_items << 3) + level_items) << 4);

	next_item_free = level_items;

	if ((level_items + 1) < numitems)
	{
		for (int i = (level_items + 1); i < numitems; i++, item++)
		{
			item->next_item = i;

			//FIXME: Union flags.
			*(int*)item->active &= -2;
		}
	}
	
	//Last
	item->next_item = -1;
}

void RemoveActiveItem(short item_num)//41E98, 422EC
{
	//short linknum; // $v1
	struct ITEM_INFO* a1 = &items[item_num];
	int v0 = a1->active;

	if (a1->active != 0)
	{
		*(int*)a1->active &= -2;
		v0 = *(int*) a1->active;

		if (next_item_active == item_num)
		{
			next_item_active = items[item_num].next_active;
			return;
		}//0x4235C

		if (next_item_active == -1)//CHECK
		{
			next_item_active = -1;
			return;
		}

		struct ITEM_INFO* a2 = &items[0];
		int a3 = -1;
		v0 = next_item_active << 3;

		while (next_item_active != -1)
		{
			v0 += -1;
			v0 <<= 4;
			struct ITEM_INFO* a11 = (struct ITEM_INFO*)(((char*) a2) + v0);
			a11->next_active = next_item_active;
			v0 = next_item_active << 3;
			v0 += next_item_active;

			if (next_item_active == item_num)
			{
				v0 <<= 4;
				struct ITEM_INFO* v00 = (struct ITEM_INFO*)(((char*) a2) + v0);
				v00->next_active = next_item_active;
				return;
			}//0x42344
		}
	}//0x4233C

	next_item_active = -2;
	return;
}