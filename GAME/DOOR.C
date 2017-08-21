#include "DOOR.H"

#include "PSXTYPES.H"
#include "SPECIFIC.H"

static struct PHD_VECTOR DoubleDoorPos;
static struct PHD_VECTOR PullDoorPos;
static struct PHD_VECTOR PushDoorPos;
static struct PHD_VECTOR KickDoorPos;
static struct PHD_VECTOR UnderwaterDoorPos;
static struct PHD_VECTOR CrowbarDoorPos;
static short PushPullKickDoorBounds[12];
static short UnderwaterDoorBounds[12];
static short CrowbarDoorBounds[12];
long ClosedDoors[32];
char LiftDoor;

void ProcessClosedDoors()//2BDE8, 2C110
{
	S_Warn("[ProcessClosedDoors] - Unimplemented!\n");
}

void SequenceDoorControl(short item_number)//2BC28, 2BF50
{
	S_Warn("[SequenceDoorControl] - Unimplemented!\n");
}

void UnderwaterDoorCollision(short item_num, struct ITEM_INFO *l, struct COLL_INFO *coll)//2BA38, 2BD60
{
	S_Warn("[UnderwaterDoorCollision] - Unimplemented!\n");
}

void DoubleDoorCollision(short item_num, struct ITEM_INFO *l, struct COLL_INFO *coll)//2B854, 2BB7C
{
	S_Warn("[DoubleDoorCollision] - Unimplemented!\n");
}

void PushPullKickDoorCollision(short item_num, struct ITEM_INFO *l, struct COLL_INFO *coll)//2B5A0, 2B8C8
{
	S_Warn("[PushPullKickDoorCollision] - Unimplemented!\n");
}

void PushPullKickDoorControl(short item_number)//2B508, 2B830
{
	S_Warn("[PushPullKickDoorControl] - Unimplemented!\n");
}

void DoorCollision(short item_num, struct ITEM_INFO *l, struct COLL_INFO *coll)//2B150, 2B478
{
	S_Warn("[DoorCollision] - Unimplemented!\n");
}

void DoorControl(short item_number)//2AD74, 2B09C
{
	S_Warn("[DoorControl] - Unimplemented!\n");
}

void OpenThatDoor(struct DOORPOS_DATA *d, struct DOOR_DATA *dd)//2AB8C, 2AEB4
{
	S_Warn("[OpenThatDoor] - Unimplemented!\n");
}

void ShutThatDoor(struct DOORPOS_DATA *d, struct DOOR_DATA *dd)//2AA88, 2ADB0
{
	S_Warn("[ShutThatDoor] - Unimplemented!\n");
}
