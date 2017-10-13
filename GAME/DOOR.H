#ifndef DOOR_H
#define DOOR_H

#include "SPECTYPES.H"

extern char LiftDoor;
extern long ClosedDoors[32];

extern void ProcessClosedDoors();
extern void SequenceDoorControl(short item_number);
extern void UnderwaterDoorCollision(short item_num, ITEM_INFO* l, COLL_INFO* coll);
extern void DoubleDoorCollision(short item_num, ITEM_INFO* l, COLL_INFO* coll);
extern void PushPullKickDoorCollision(short item_num, ITEM_INFO* l, COLL_INFO* coll);
extern void PushPullKickDoorControl(short item_number);
extern void DoorCollision(short item_num, ITEM_INFO* l, COLL_INFO* coll);
extern void DoorControl(short item_number);
extern void OpenThatDoor(DOORPOS_DATA* d, DOOR_DATA* dd);
extern void ShutThatDoor(DOORPOS_DATA* d, DOOR_DATA* dd);

#endif
