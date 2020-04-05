#include "ANDY3.H"

#include "CAMERA.H"
#include "CONTROL.H"
#include "EFFECT2.H"
#include "OBJECTS.H"
#include "TOMB4FX.H"

#if PSX_VERSION || PSXPC_VERSION || SAT_VERSION
#include "MISC.H"
#include "SETUP.H"
#include "LOAD_LEV.H"
#elif PC_VERSION
#include "GLOBAL.H"
#include "GAME.H"
#endif

#if PSX_VERSION && RELOC
void* func_andy3[] __attribute__((section(".header"))) =
{
	&CODEWAD_andy3_Func1,
};

#endif

void CODEWAD_andy3_Func1(short item_number)
{
	struct ITEM_INFO* item;
	struct SPARKS* sptr;
	short sine;

	item = &items[item_number];

	if ((((CamRot.vy + 1256) & 0xFFF) & 0x7FF) < 1025)
	{
		sine = rcossin_tbl[(((CamRot.vy + 1256) & 0xFFF) & 0x7FF) << 2]; //s1

		sptr = &spark[GetFreeSpark()];
		sptr->On = 1;
		sptr->sR = (unsigned char)(GetRandomControl() | 0xE0);
		sptr->sG = (unsigned char)((GetRandomControl() & 0xF) - 0x40);
		sptr->dB = 0;
		sptr->dG = 0;
		sptr->dR = 0;
		sptr->ColFadeSpeed = 2;
		sptr->FadeToBlack = 0;
		sptr->Life = 2;
		sptr->sLife = 2;
		sptr->TransType = 2;
		sptr->sR = (sptr->sR * sine) >> 12;
		sptr->sG = (sptr->sG * sine) >> 12;
		sptr->sB = (unsigned char)((((GetRandomControl() & 0x7F) & 0xFF) * sine) >> 12);
		sptr->x = item->pos.x_pos + (rcossin_tbl[((CamRot.vy + 1256) & 0xFFF) << 1] >> 7);
		sptr->y = item->pos.y_pos - 8;
		sptr->Zvel = 0;
		sptr->Yvel = 0;
		sptr->Xvel = 0;
		sptr->Flags = 42;
		sptr->MaxYvel = 0;
		sptr->Gravity = 0;
		sptr->Def = objects[DEFAULT_SPRITES].mesh_index + SPRITE_WRECKING_BALL;
		sptr->dSize = 24;
		sptr->z = item->pos.z_pos + (rcossin_tbl[(((CamRot.vy + 1256) & 0xFFF) << 1) + 1] >> 7);
		sptr->sSize = 24;
		sptr->Size = 24;
	}//loc_1BC

	return;
}