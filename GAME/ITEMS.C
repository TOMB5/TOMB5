#include "ITEMS.H"

int level_items;
short next_item_free;
short next_item_active;
short GlobalPulleyFrigItem;
struct ITEM_INFO* items;

void InitialiseItemArray(int numitems)//418E8, 41D3C
{
	next_item_active = -1;

	struct ITEM_INFO* item = &items[0];
	
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