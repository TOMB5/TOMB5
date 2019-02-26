#ifndef FLMTORCH_H
#define FLMTORCH_H

#include "STYPES.H"

extern short torchroom;

extern void FlameTorchControl(short item_number);
extern void GetFlameTorch();
extern void DoFlameTorch();
extern void FireCollision(short item_num, struct ITEM_INFO* l, struct COLL_INFO* coll);
extern void TriggerTorchFlame(short item_number, long Node);

#endif