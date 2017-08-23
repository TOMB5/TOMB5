#include "SWITCH.H"

#include "CONTROL.H"
#include "SPECIFIC.H"

unsigned char SequenceUsed[6];
unsigned char SequenceResults[3][3][3];
unsigned char Sequences[3];
unsigned char CurrentSequence;

void ProcessExplodingSwitchType8(struct ITEM_INFO *item)//58958, 58DF8
{
	S_Warn("[ProcessExplodingSwitchType8] - Unimplemented!\n");
}

void CrowDoveSwitchCollision(short item_num, struct ITEM_INFO *l, struct COLL_INFO *coll)//58740, 58BE0
{
	S_Warn("[CrowDoveSwitchCollision] - Unimplemented!\n");
}

void CrowDoveSwitchControl(short item_number)//58674, 58B14
{
	S_Warn("[CrowDoveSwitchControl] - Unimplemented!\n");
}

void CogSwitchCollision(short item_num, struct ITEM_INFO *l, struct COLL_INFO *coll)//58354, 587F4
{
	S_Warn("[CogSwitchCollision] - Unimplemented!\n");
}

void CogSwitchControl(short item_num)//581D8, 58678
{
	S_Warn("[CogSwitchControl] - Unimplemented!\n");
}

void FullBlockSwitchCollision(short item_num, struct ITEM_INFO *l, struct COLL_INFO *coll)//57FB8, 58458
{
	S_Warn("[FullBlockSwitchCollision] - Unimplemented!\n");
}

void FullBlockSwitchControl(short item_number)//57EB8, 58358
{
	S_Warn("[FullBlockSwitchControl] - Unimplemented!\n");
}

void CrowbarSwitchCollision(short item_num, struct ITEM_INFO *l, struct COLL_INFO *coll)//57ACC, 57F6C
{
	S_Warn("[CrowbarSwitchCollision] - Unimplemented!\n");
}

void JumpSwitchCollision(short item_num, struct ITEM_INFO *l, struct COLL_INFO *coll)//57980, 57E20
{
	S_Warn("[JumpSwitchCollision] - Unimplemented!\n");
}

void RailSwitchCollision(short item_num, struct ITEM_INFO *l, struct COLL_INFO *coll)//576F4, 57B94
{
	S_Warn("[RailSwitchCollision] - Unimplemented!\n");
}

void TurnSwitchCollision(short item_num, struct ITEM_INFO *l, struct COLL_INFO *coll)//57210, 576B0
{
	S_Warn("[TurnSwitchCollision] - Unimplemented!\n");
}

void TurnSwitchControl(short item_num)//56E9C, 5733C
{
	S_Warn("[TurnSwitchControl] - Unimplemented!\n");
}

void PulleyCollision(short item_num, struct ITEM_INFO *l, struct COLL_INFO *coll)//56C98, 57138
{
	S_Warn("[PulleyCollision] - Unimplemented!\n");
}

void UnderwaterSwitchCollision(short item_num, struct ITEM_INFO *l, struct COLL_INFO *coll)//56A2C, 56ECC
{
	S_Warn("[UnderwaterSwitchCollision] - Unimplemented!\n");
}

void SwitchCollision2(short item_num, struct ITEM_INFO *l, struct COLL_INFO *coll)//568C0, 56D60
{
	S_Warn("[SwitchCollision2] - Unimplemented!\n");
}

void SwitchCollision(short item_num, struct ITEM_INFO *l, struct COLL_INFO *coll)//56470, 56910
{
	S_Warn("[SwitchCollision] - Unimplemented!\n");
}

void SwitchControl(short item_number)//5623C, 566DC
{
	S_Warn("[SwitchControl] - Unimplemented!\n");
}

void TestTriggersAtXYZ(long x, long y, long z, short room_number, int heavy, int flags)//561A8(<), 56648(<)
{
	int s4 = x;
	int s3 = y;
	int s2 = z;

	int s1 = heavy;
	int s0 = flags;
	int a3 = room_number;

#if 0
	jal	sub_78954//GetFloor();
	nop
	move	$a0, $v0
	move	$a1, $s4
	move	$a2, $s3
	move	$a3, $s2
	jal	sub_78C74//GetHeight($v0@GetFloor();, x, y, z);
#endif


	TestTriggers(trigger_index, heavy, flags);
	S_Warn("[TestTriggersAtXYZ] - Unimplemented!\n");
	return;
}

int GetKeyTrigger(struct ITEM_INFO *item)//56080, 56520
{
	S_Warn("[GetKeyTrigger] - Unimplemented!\n");
	return 0;
}

int GetSwitchTrigger(struct ITEM_INFO *item, short *ItemNos, long AttatchedToSwitch)//55F4C, 563EC
{
	S_Warn("[GetSwitchTrigger] - Unimplemented!\n");
	return 0;
}

int SwitchTrigger(short item_num, short timer)//55DE4, 56284
{
	S_Warn("[SwitchTrigger] - Unimplemented!\n");
	return 0;
}