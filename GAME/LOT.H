#ifndef LOT_H
#define LOT_H

#include "SPECTYPES.H"

extern int slots_used;
extern short nAIObjects;
extern AIOBJECT* AIObjects;
extern creature_info* baddie_slots;

extern void CreateZone(ITEM_INFO* item);
extern void InitialiseSlot(short item_number, int slot);
extern int EnableBaddieAI(short item_number, int Always);
extern void DisableBaddieAI(short item_num);
extern void InitialiseLOTarray(int allocmem);

#endif