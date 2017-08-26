#ifndef ITEMS_H
#define ITEMS_H

#include "SPECTYPES.H"

extern int level_items;
extern short next_item_free;
extern short next_item_active;
extern short GlobalPulleyFrigItem;

extern void EffectNewRoom(short fx_num, short room_number);
extern void KillEffect(short fx_num);
extern short CreateEffect(short room_num);
extern void InitialiseFXArray(int allocmem);
extern void AddActiveItem(short item_num);
extern void RemoveDrawnItem(short item_num);
extern void RemoveActiveItem(short item_num);
extern void InitialiseItem(short item_num);
extern short CreateItem();
extern void KillItem(short item_num);
extern void InitialiseItemArray(int numitems);
extern void ItemNewRoom(short item_num, short room_number);

#endif