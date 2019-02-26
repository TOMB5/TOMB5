#ifndef LOT_H
#define LOT_H

#include "STYPES.H"

extern int slots_used;
extern short nAIObjects;
extern struct AIOBJECT* AIObjects;
extern struct creature_info* baddie_slots;

extern void CreateZone(struct ITEM_INFO* item);
extern void InitialiseSlot(short item_number, int slot);
extern int EnableBaddieAI(short item_number, int Always);
extern void DisableBaddieAI(short item_num);
extern void InitialiseLOTarray(int allocmem);
extern void ClearLOT(struct lot_info* LOT);

#endif