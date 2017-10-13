#ifndef FLMTORCH_H
#define FLMTORCH_H

#include "SPECTYPES.H"

extern short torchroom;

extern void FlameTorchControl(short item_number);
extern void GetFlameTorch();
extern void DoFlameTorch();
extern void FireCollision(short item_num, ITEM_INFO* l, COLL_INFO* coll);
extern void TriggerTorchFlame(short item_number, long Node);

#endif