#include "DOOR.H"

#include "SPECTYPES.H"
#include "SPECIFIC.H"

static struct PHD_VECTOR DoubleDoorPos = { 0, 0, 0xDC };
static struct PHD_VECTOR PullDoorPos = { 0xFFFFFF37, 0, 0x142 };
static struct PHD_VECTOR PushDoorPos = { 0xC9, 0, 0xFFFFFD42 };
static struct PHD_VECTOR KickDoorPos = { 0, 0, 0xFFFFFC6B };
static struct PHD_VECTOR UnderwaterDoorPos = { 0xFFFFFF05, 0xFFFFFDE4, 0xFFFFFFD2 };
static struct PHD_VECTOR CrowbarDoorPos = { 0xFFFFFE64, 0, 0x100 };

static short PushPullKickDoorBounds[12] =
{
	0xFE80, 0x0180, 0x0000, 0x0000, 0xFC00, 0x0200, 0xF8E4, 0x071C, 0xEAAC, 0x1554, 0xF8E4, 0x071C
};

static short UnderwaterDoorBounds[12] =
{
	0xFF00, 0x0100, 0xFC00, 0x0000, 0xFC00, 0x0000, 0xC720, 0x38E0, 0xC720, 0x38E0, 0xC720, 0x38E0
};

static short CrowbarDoorBounds[12] =
{
	0xFE00, 0x0200, 0xFC00, 0x0000, 0x0000, 0x0200, 0xC720, 0x38E0, 0xC720, 0x38E0, 0xC720, 0x38E0
};

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