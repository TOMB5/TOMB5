#include "FLMTORCH.H"

#include "SPECIFIC.H"

static short FireBounds[12] =
{
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xF8E4, 0x071C, 0xEAAC, 0x1554, 0xF8E4, 0x071C
};

short torchroom = 255;

void FlameTorchControl(short item_number)//3A8F4, 3ADF4
{
	S_Warn("[FlameTorchControl] - Unimplemented!\n");
}

void GetFlameTorch()//3A830, 3AD30
{
	S_Warn("[GetFlameTorch] - Unimplemented!\n");
}

void DoFlameTorch()//3A3CC, 3A8CC
{
	S_Warn("[DoFlameTorch] - Unimplemented!\n");
}

void FireCollision(short item_num, struct ITEM_INFO *l, struct COLL_INFO *coll)//3A068, 3A568
{
	S_Warn("[FireCollision] - Unimplemented!\n");
}

void TriggerTorchFlame(short item_number, long Node)//39E88, 3A388
{
	S_Warn("[TriggerTorchFlame] - Unimplemented!\n");
}