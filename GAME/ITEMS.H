#ifndef ITEMS_H
#define ITEMS_H

#include "STYPES.H"

enum item_flags
{
	IFLAG_UNK40 = (1 << 6),		 // 0x0040
	IFLAG_CLEAR_BODY = (1 << 7), // 0x0080
	IFLAG_INVISIBLE = (1 << 8),  // 0x0100
	IFLAG_REVERSE = (1 << 14),	 // 0x4000
	IFLAG_KILLED = (1 << 15),    // 0x8000
	IFLAG_ACTIVATION_MASK = 0x3E00 // bits 9-13
};

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
#if PC_VERSION
extern void ItemNewRoom(short item_num, short room_number);
#endif
#endif