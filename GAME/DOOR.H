#ifndef DOOR_H
#define DOOR_H

#include "STYPES.H"

extern char LiftDoor;
extern long ClosedDoors[32];

extern void ProcessClosedDoors();
extern void SequenceDoorControl(short item_number);
extern void UnderwaterDoorCollision(short item_num, struct ITEM_INFO* l, struct COLL_INFO* coll);
extern void DoubleDoorCollision(short item_num, struct ITEM_INFO* l, struct COLL_INFO* coll);
extern void PushPullKickDoorCollision(short item_num, struct ITEM_INFO* l, struct COLL_INFO* coll);
extern void PushPullKickDoorControl(short item_number);
extern void DoorCollision(short item_num, struct ITEM_INFO* l, struct COLL_INFO* coll);
extern void DoorControl(short item_number);
extern void OpenThatDoor(struct DOORPOS_DATA* d, struct DOOR_DATA* dd);
extern void ShutThatDoor(struct DOORPOS_DATA* d, struct DOOR_DATA* dd);

#endif
