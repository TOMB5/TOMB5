#include "EFFECT2.H"

#include "SPECIFIC.H"
#include "GAMEFLOW.H"
#include "LARA.H"
#include "CONTROL.H"
#include "DRAW.H"
#include "TOMB4FX.H"

long wibble;
long SplashCount;
long KillEverythingFlag;
long next_spark;

unsigned char TES_extra_tab[] =
{
	0x00, 0x04, 0x07, 0x0A, 0x00, 0x00
};

long DeadlyBounds[6];
struct SPLASH_STRUCT splashes[4];
struct RIPPLE_STRUCT ripples[32];
struct DYNAMIC dynamics[64];
struct SPLASH_SETUP splash_setup;
struct SP_DYNAMIC spark_dynamics[8];
long SmokeWeapon;
long SmokeWindX;
long SmokeWindZ;
long SmokeCountL;
long SmokeCountR;
struct SPARKS spark[128];

void ControlEnemyMissile(short fx_number)//342D0, 347D0
{
	S_Warn("[ControlEnemyMissile] - Unimplemented!\n");
}

void ControlSmokeEmitter(short item_number)//338B8, 33DB8
{
	S_Warn("[ControlSmokeEmitter] - Unimplemented!\n");
}

void KillEverything()//338AC(<), 33DAC(<) (F)
{
	KillEverythingFlag = 0;
}

void KillAllCurrentItems(short item_number)//3389C, 33D9C
{
	S_Warn("[KillAllCurrentItems] - Unimplemented!\n");
}

void TriggerDartSmoke(long x, long y, long z, long xv, long zv, long hit)//335B8, 33AB8
{
	S_Warn("[TriggerDartSmoke] - Unimplemented!\n");
}

void TriggerWaterfallMist(long x, long y, long z, long angle)//331B4, 336B4
{
	S_Warn("[TriggerWaterfallMist] - Unimplemented!\n");
}

void TriggerSuperJetFlame(struct ITEM_INFO* item, long yvel, long deadly)//32EAC, 333AC
{
	S_Warn("[TriggerSuperJetFlame] - Unimplemented!\n");
}

void DetatchSpark(long num, long type)//32D8C, 3328C
{
	S_Warn("[DetatchSpark] - Unimplemented!\n");
}

void TriggerGunSmoke(long x, long y, long z, long xv, long yv, long zv, int a7, int a8, int a9)
{
	struct SMOKE_SPARKS* spark = &smoke_spark[GetFreeSmokeSpark()];
	unsigned char life, size;

	spark->On = 1;
	spark->sShade = 0;
	spark->dShade = 4 * a9;
	spark->ColFadeSpeed = 4;
	spark->FadeToBlack = 32 - 16 * a7;
	life = (GetRandomControl() & 3) + 40;
	spark->Life = life;
	spark->sLife = life;
	if ((a8 == 1 || a8 == 2 || a8 == 3) && spark->dShade > 64)
		spark->dShade = 64;
	spark->TransType = 2;
	spark->x = (GetRandomControl() & 0x1F) + x - 16;
	spark->y = (GetRandomControl() & 0x1F) + y - 16;
	spark->z = (GetRandomControl() & 0x1F) + z - 16;
	if (a7)
	{
		spark->Xvel = (GetRandomControl() & 0x3FF) + xv - 512;
		spark->Yvel = (GetRandomControl() & 0x3FF) + yv - 512;
		spark->Zvel = (GetRandomControl() & 0x3FF) + zv - 512;
	}
	else
	{
		spark->Xvel = ((GetRandomControl() & 0x1FF) - 256) >> 1;
		spark->Yvel = ((GetRandomControl() & 0x1FF) - 256) >> 1;
		spark->Zvel = ((GetRandomControl() & 0x1FF) - 256) >> 1;
	}
	spark->Friction = 4;
	if (GetRandomControl() & 1)
	{
		if (room[lara_item->room_number].flags & 0x20)
			spark->Flags = 272;
		else
			spark->Flags = 16;
		spark->RotAng = GetRandomControl() & 0xFFF;
		if (GetRandomControl() & 1)
			spark->RotAdd = -16 - (GetRandomControl() & 0xF);
		else
			spark->RotAdd = (GetRandomControl() & 0xF) + 16;
	}
	else if (room[lara_item->room_number].flags & 0x20)
	{
		spark->Flags = 256;
	}
	else
	{
		spark->Flags = 0;
	}
	spark->Gravity = -2 - (GetRandomControl() & 1);
	spark->MaxYvel = -2 - (GetRandomControl() & 1);
	size = (GetRandomControl() & 0xF) - (a8 != 5 ? 24 : 0) + 48;
	if (a7)
	{
		spark->sSize = size >> 1;
		spark->Size = size >> 1;
		size = 2 * (size + 4);
	}
	else
	{
		spark->sSize = size >> 2;
		spark->Size = size >> 2;
	}
	spark->dSize = size;
	if (gfLevelFlags & GF_LVOP_MIRROR_USED  && lara_item->room_number == gfMirrorRoom)
	{
		spark->mirror = 1;
	}
	else
	{
		spark->mirror = 0;
	}
}

void TriggerDynamic(long x, long y, long z, int a4, int a5, int a6, int a7)
{
	S_Warn("[TriggerDynamic] - Unimplemented!\n");
}

