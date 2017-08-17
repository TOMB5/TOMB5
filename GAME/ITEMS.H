#ifndef ITEMS_H
#define ITEMS_H

#include "PSXTYPES.H"

extern int level_items;
extern short next_item_free;
extern short next_item_active;
extern short GlobalPulleyFrigItem;

extern void InitialiseItemArray(int numitems);
extern void RemoveActiveItem(short item_num);
extern void InitialiseItem(short item_num);
extern void AddActiveItem(short item_num);

#endif