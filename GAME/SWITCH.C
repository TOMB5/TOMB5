#include "SWITCH.H"

#include "CONTROL.H"
#include "SPECIFIC.H"

#ifdef PC_VERSION
#include "GAME.H"
#else
#include "SETUP.H"
#endif

unsigned char SequenceUsed[6];
unsigned char SequenceResults[3][3][3];
unsigned char Sequences[3];
unsigned char CurrentSequence;

static short Switch2Bounds[12] = // offset 0xA14B4
{
	0xFC00, 0x0400, 0xFC00, 0x0400, 0xFC00, 0x0200, 0xC720, 0x38E0, 0xC720, 0x38E0,
	0xC720, 0x38E0
};
static struct PHD_VECTOR Switch2Position = { 0, 0, 0x6C }; // offset 0xA14CC
static short TurnSwitchBoundsA[12] = // offset 0xA14D8
{
	0x0200, 0x0380, 0x0000, 0x0000, 0xFE00, 0x0000, 0xF8E4, 0x071C, 0xEAAC, 0x1554, 
	0xF8E4, 0x071C
};
static struct PHD_VECTOR TurnSwitchPos = { 0x28A, 0, 0x8A }; // offset 0xA14F0
static short TurnSwitchBoundsC[12] = // offset 0xA14FC
{
	0x0200, 0x0380, 0x0000, 0x0000, 0x0000, 0x0200, 0xF8E4, 0x071C, 0xEAAC, 0x1554, 
	0xF8E4, 0x071C
};
static struct PHD_VECTOR TurnSwitchPosA = { 0x28A, 0, 0xFFFFFF76 }; // offset 0xA1514
static struct PHD_VECTOR CogSwitchPos = { 0, 0, 0xFFFFFCA8 }; // offset 0xA1520
static short CogSwitchBounds[12] = // offset 0xA152C
{
	0xFE00, 0x0200, 0x0000, 0x0000, 0xFA00, 0xFE00, 0xF8E4, 0x071C, 0xEAAC, 0x1554, 
	0xF8E4, 0x071C
};
static struct PHD_VECTOR RailSwitchPos = { 0, 0, 0xFFFFFDDA }; // offset 0xA1544
static short RailSwitchBounds[12] = // offset 0xA1550
{
	0xFF00, 0x0100, 0x0000, 0x0000, 0xFD00, 0xFE00, 0xF8E4, 0x071C, 0xEAAC, 0x1554, 
	0xF8E4, 0x071C
};
static struct PHD_VECTOR RailSwitchPos2 = { 0, 0, 0x226 }; // offset 0xA1568
static short RailSwitchBounds2[12] = // offset 0xA1574
{
	0xFF00, 0x0100, 0x0000, 0x0000, 0x0200, 0x0300, 0xF8E4, 0x071C, 0xEAAC, 0x1554, 
	0xF8E4, 0x071C
};
static short JumpSwitchBounds[12] = // offset 0xA158C
{
	0xFF80, 0x0080, 0xFF00, 0x0100, 0x0180, 0x0200, 0xF8E4, 0x071C, 0xEAAC, 0x1554,
	0xF8E4, 0x071C
};
static struct PHD_VECTOR JumpSwitchPos = { 0, 0xFFFFFF30, 0x100 }; // offset 0xA15A4
static struct PHD_VECTOR CrowbarPos = { 0xFFFFFFA7, 0, 0xFFFFFEB8 }; // offset 0xA15B0
static short CrowbarBounds[12] = // offset 0xA15BC
{
	0xFF00, 0x0100, 0x0000, 0x0000, 0xFE00, 0xFF00, 0xF8E4, 0x071C, 0xEAAC, 0x1554, 
	0xF8E4, 0x071C
};
static struct PHD_VECTOR CrowbarPos2 = { 0x59, 0, 0x148 }; // offset 0xA15D4
static short CrowbarBounds2[12] = // offset 0xA15E0
{
	0xFF00, 0x0100, 0x0000, 0x0000, 0x0100, 0x0200, 0xF8E4, 0x071C, 0xEAAC, 0x1554, 
	0xF8E4, 0x071C
};
static short FullBlockSwitchBounds[12] = // offset 0xA15F8
{
	0xFE80, 0x0180, 0x0000, 0x0100, 0x0000, 0x0200, 0xF8E4, 0x071C, 0xEAAC, 0x1554,
	0xF8E4, 0x071C
};
static struct PHD_VECTOR FullBlockSwitchPos = { 0, 0, 0 }; // offset 0xA1610
static short PulleyBounds[12] = // offset 0xA161C
{
	0xFF00, 0x0100, 0x0000, 0x0000, 0xFE00, 0x0200, 0xF8E4, 0x071C, 0xEAAC, 0x1554, 
	0xF8E4, 0x071C
};
static struct PHD_VECTOR PulleyPos = { 0, 0, 0xFFFFFF6C }; // offset 0xA1634
static struct PHD_VECTOR CrowDovePos = { 0, 0, 0xFFFFFE70 }; // offset 0xA1640
static short UnderwaterSwitchBounds[12] = // offset 0xA164C
{
	0xFF00, 0x0100, 0xFB00, 0xFE00, 0xFE00, 0x0000, 0xC720, 0x38E0, 0xC720, 0x38E0, 
	0xC720, 0x38E0
};
static short UnderwaterSwitchBounds2[12] = // offset 0xA1664
{
	0xFF00, 0x0100, 0xFB00, 0xFE00, 0x0000, 0x0200, 0xC720, 0x38E0, 0xC720, 0x38E0,
	0xC720, 0x38E0
};
static struct PHD_VECTOR UnderwaterSwitchPos = { 0, 0xFFFFFD20, 0xFFFFFE60 }; // offset 0xA167C
static struct PHD_VECTOR UnderwaterSwitchPos2 = { 0, 0xFFFFFD20, 0x1A0 }; // offset 0xA1688
static short SwitchBounds[12] = // offset 0xA1694
{
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xF8E4, 0x071C, 0xEAAC, 0x1554, 
	0xF8E4, 0x071C
};
static struct PHD_VECTOR SwitchPos = { 0, 0, 0 }; // offset 0xA16AC

void ProcessExplodingSwitchType8(struct ITEM_INFO* item)//58958, 58DF8 (F)
{
	struct PHD_VECTOR pos;
	pos.x = 0;
	pos.y = 0;
	pos.z = 0;
	GetJointAbsPosition(item, &pos, 0);
	TestTriggersAtXYZ(pos.x, pos.y, pos.z, item->room_number, 1, 0);
	ExplodeItemNode(item, objects[item->object_number].nmeshes - 1, 0, 64);
	item->mesh_bits |= 1 << ((objects[item->object_number].nmeshes & 0xFF) - 2);
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