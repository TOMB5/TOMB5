#include "SWITCH.H"

#include "CONTROL.H"
#include "SPECIFIC.H"

unsigned char SequenceUsed[6];
unsigned char SequenceResults[3][3][3];
unsigned char Sequences[3];
unsigned char CurrentSequence;

static short Switch2Bounds[12]; // offset 0xA14B4
static struct PHD_VECTOR Switch2Position; // offset 0xA14CC
static short TurnSwitchBoundsA[12]; // offset 0xA14D8
static struct PHD_VECTOR TurnSwitchPos; // offset 0xA14F0
static short TurnSwitchBoundsC[12]; // offset 0xA14FC
static struct PHD_VECTOR TurnSwitchPosA; // offset 0xA1514
static struct PHD_VECTOR CogSwitchPos; // offset 0xA1520
static short CogSwitchBounds[12]; // offset 0xA152C
static struct PHD_VECTOR RailSwitchPos; // offset 0xA1544
static short RailSwitchBounds[12]; // offset 0xA1550
static struct PHD_VECTOR RailSwitchPos2; // offset 0xA1568
static short RailSwitchBounds2[12]; // offset 0xA1574
static short JumpSwitchBounds[12]; // offset 0xA158C
static struct PHD_VECTOR JumpSwitchPos; // offset 0xA15A4
static struct PHD_VECTOR CrowbarPos; // offset 0xA15B0
static short CrowbarBounds[12]; // offset 0xA15BC
static struct PHD_VECTOR CrowbarPos2; // offset 0xA15D4
static short CrowbarBounds2[12]; // offset 0xA15E0
static short FullBlockSwitchBounds[12]; // offset 0xA15F8
static struct PHD_VECTOR FullBlockSwitchPos; // offset 0xA1610
static short PulleyBounds[12]; // offset 0xA161C
static struct PHD_VECTOR PulleyPos; // offset 0xA1634
static struct PHD_VECTOR CrowDovePos; // offset 0xA1640
static short UnderwaterSwitchBounds[12]; // offset 0xA164C
static short UnderwaterSwitchBounds2[12]; // offset 0xA1664
static struct PHD_VECTOR UnderwaterSwitchPos; // offset 0xA167C
static struct PHD_VECTOR UnderwaterSwitchPos2; // offset 0xA1688
static short SwitchBounds[12]; // offset 0xA1694
static struct PHD_VECTOR SwitchPos; // offset 0xA16AC

void ProcessExplodingSwitchType8(struct ITEM_INFO* item)//58958, 58DF8
{
	S_Warn("[ProcessExplodingSwitchType8] - Unimplemented!\n");
	return;
}

void CrowDoveSwitchCollision(short item_num, struct ITEM_INFO* l, struct COLL_INFO* coll)//58740, 58BE0
{
	S_Warn("[CrowDoveSwitchCollision] - Unimplemented!\n");
	return;
}

void CrowDoveSwitchControl(short item_number)//58674, 58B14
{
	S_Warn("[CrowDoveSwitchControl] - Unimplemented!\n");
	return;
}

void CogSwitchCollision(short item_num, struct ITEM_INFO* l, struct COLL_INFO* coll)//58354, 587F4
{
	S_Warn("[CogSwitchCollision] - Unimplemented!\n");
	return;
}

void CogSwitchControl(short item_num)//581D8, 58678
{
	S_Warn("[CogSwitchControl] - Unimplemented!\n");
	return;
}

void FullBlockSwitchCollision(short item_num, struct ITEM_INFO* l, struct COLL_INFO* coll)//57FB8, 58458
{
	S_Warn("[FullBlockSwitchCollision] - Unimplemented!\n");
	return;
}

void FullBlockSwitchControl(short item_number)//57EB8, 58358
{
	S_Warn("[FullBlockSwitchControl] - Unimplemented!\n");
	return;
}

void CrowbarSwitchCollision(short item_num, struct ITEM_INFO* l, struct COLL_INFO* coll)//57ACC, 57F6C
{
	S_Warn("[CrowbarSwitchCollision] - Unimplemented!\n");
	return;
}

void JumpSwitchCollision(short item_num, struct ITEM_INFO* l, struct COLL_INFO* coll)//57980, 57E20
{
	S_Warn("[JumpSwitchCollision] - Unimplemented!\n");
	return;
}

void RailSwitchCollision(short item_num, struct ITEM_INFO* l, struct COLL_INFO* coll)//576F4, 57B94
{
	S_Warn("[RailSwitchCollision] - Unimplemented!\n");
	return;
}

void TurnSwitchCollision(short item_num, struct ITEM_INFO* l, struct COLL_INFO* coll)//57210, 576B0
{
	S_Warn("[TurnSwitchCollision] - Unimplemented!\n");
	return;
}

void TurnSwitchControl(short item_num)//56E9C, 5733C
{
	S_Warn("[TurnSwitchControl] - Unimplemented!\n");
	return;
}

void PulleyCollision(short item_num, struct ITEM_INFO* l, struct COLL_INFO* coll)//56C98, 57138
{
	S_Warn("[PulleyCollision] - Unimplemented!\n");
	return;
}

void UnderwaterSwitchCollision(short item_num, struct ITEM_INFO* l, struct COLL_INFO* coll)//56A2C, 56ECC
{
	S_Warn("[UnderwaterSwitchCollision] - Unimplemented!\n");
	return;
}

void SwitchCollision2(short item_num, struct ITEM_INFO* l, struct COLL_INFO* coll)//568C0, 56D60
{
	S_Warn("[SwitchCollision2] - Unimplemented!\n");
	return;
}

void SwitchCollision(short item_num, struct ITEM_INFO* l, struct COLL_INFO* coll)//56470, 56910
{
	S_Warn("[SwitchCollision] - Unimplemented!\n");
	return;
}

void SwitchControl(short item_number)//5623C, 566DC
{
	S_Warn("[SwitchControl] - Unimplemented!\n");
	return;
}

void TestTriggersAtXYZ(long x, long y, long z, short room_number, int heavy, int flags)//561A8(<), 56648(<)
{
	GetHeight(GetFloor(x, y, z, &room_number), x, y, z);
	TestTriggers(trigger_index, heavy, flags);
	return;
}

int GetKeyTrigger(struct ITEM_INFO* item)//56080, 56520
{
	S_Warn("[GetKeyTrigger] - Unimplemented!\n");
	return 0;
}

int GetSwitchTrigger(struct ITEM_INFO* item, short* ItemNos, long AttatchedToSwitch)//55F4C, 563EC
{
	S_Warn("[GetSwitchTrigger] - Unimplemented!\n");
	return 0;
}

int SwitchTrigger(short item_num, short timer)//55DE4, 56284
{
	S_Warn("[SwitchTrigger] - Unimplemented!\n");
	return 0;
}