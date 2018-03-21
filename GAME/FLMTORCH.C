#include "FLMTORCH.H"

#include "EFFECT2.H"
#include "CONTROL.H"
#include "DRAW.H"
#include "LARA.H"
#include "LARAFLAR.H"
#include "OBJECTS.H"
#if PC_VERSION
#include "GAME.H"
#else
#include "SETUP.H"
#endif
#include "SPECIFIC.H"
#include "TOMB4FX.H"

static short FireBounds[12] =
{
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xF8E4, 0x071C, 0xEAAC, 0x1554, 0xF8E4, 0x071C
};

short torchroom = 255;

void FlameTorchControl(short item_number)//3A8F4, 3ADF4
{
	S_Warn("[FlameTorchControl] - Unimplemented!\n");
}

void GetFlameTorch()//3A830, 3AD30(<) (F)
{
	if (lara.gun_type == 7)
	{
		CreateFlare(FLARE_ITEM, 0);
	}

	//loc_3A864
	lara.gun_status = 4;
	lara.request_gun_type = 8;
	lara.gun_type = 8;
	lara.left_arm.lock = 0;
	lara.left_arm.frame_number = 0;
	lara.left_arm.anim_number = objects[TORCH_ANIM].anim_index;
	lara.flare_control_left = 1;
	lara.left_arm.frame_base = anims[objects[TORCH_ANIM].anim_index].frame_ptr;
	lara.target->touch_bits = ((unsigned long*)meshes[objects[TORCH_ANIM].mesh_index])[26];
}

void DoFlameTorch()//3A3CC, 3A8CC
{
	S_Warn("[DoFlameTorch] - Unimplemented!\n");
}

void FireCollision(short item_num, struct ITEM_INFO* l, struct COLL_INFO* coll)//3A068, 3A568
{
	S_Warn("[FireCollision] - Unimplemented!\n");
}

void TriggerTorchFlame(short item_number, long Node)//39E88, 3A388 (F)
{
	struct SPARKS* sptr = &spark[GetFreeSpark()];
	long size;

	sptr->On = 1;

	sptr->sR = 255;
	sptr->sG = (GetRandomControl() & 0x1F) + 48;
	sptr->sB = 48;

	sptr->dR = (GetRandomControl() & 0x3F) - 64;
	sptr->dG = (GetRandomControl() & 0x3F) + -128;
	sptr->dB = 32;

	sptr->FadeToBlack = 8;
	sptr->ColFadeSpeed = (GetRandomControl() & 3) + 12;

	sptr->TransType = 2;

	sptr->Life = sptr->sLife = (GetRandomControl() & 7) + 24;

	sptr->y = 0;
	sptr->x = (GetRandomControl() & 0xF) - 8;
	sptr->z = (GetRandomControl() & 0xF) - 8;

	sptr->Xvel = (GetRandomControl() & 0xFF) - 128;
	sptr->Yvel = -((GetRandomControl() & 0xF) + 16);
	sptr->Zvel = GetRandomControl() - 128;

	sptr->Friction = 5;
	sptr->Flags = 4762;
	
	sptr->RotAng = GetRandomControl() & 0xFFF;

	if (GetRandomControl() & 1)
		sptr->RotAdd = -((GetRandomControl() & 0xF) + 16);
	else
		sptr->RotAdd = (GetRandomControl() & 0xF) + 16;

	sptr->Gravity = -((GetRandomControl() & 0x1F) + 16);
	sptr->NodeNumber = Node;
	sptr->MaxYvel = -((GetRandomControl() & 7) + 16);
	sptr->FxObj = item_number;
	sptr->Scalar = 1;

	size = (GetRandomControl() & 0x1F) + 80;
	sptr->sSize = size;
	sptr->Size = size;
	sptr->dSize = size >> 3;
}