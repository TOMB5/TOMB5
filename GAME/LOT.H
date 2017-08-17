#ifndef LOT_H
#define LOT_H

#include "PSXTYPES.H"

extern int slots_used;
extern short nAIObjects;
extern struct AIOBJECT* AIObjects;
extern struct creature_info* baddie_slots;

extern void InitialiseSlot(short item_number, int slot);

#endif