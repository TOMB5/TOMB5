#include "EFFECT2.H"

#include "SPECIFIC.H"
#include "GAMEFLOW.H"
#include "LARA.H"
#include "CONTROL.H"
#include "DRAW.H"
#include "TOMB4FX.H"
#include "EFFECTS.H"

#ifdef PC_VERSION
#include "GAME.H"
#else
#include "SETUP.H"
#endif

#if PSX_VERSION || PSXPC_VERSION
#include "MISC.H"
#endif


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
	UNIMPLEMENTED();
}

void ControlSmokeEmitter(short item_number)//338B8, 33DB8
{
	UNIMPLEMENTED();
}

void KillEverything()//338AC(<), 33DAC(<) (F)
{
	KillEverythingFlag = 0;
}

void KillAllCurrentItems(short item_number)//3389C, 33D9C (F)
{
	KillEverythingFlag = 1;
}

void TriggerDartSmoke(long x, long y, long z, long xv, long zv, long hit)//335B8, 33AB8
{
	UNIMPLEMENTED();
}

void TriggerWaterfallMist(long x, long y, long z, long angle)//331B4, 336B4
{
	UNIMPLEMENTED();
}

void TriggerSuperJetFlame(struct ITEM_INFO* item, long yvel, long deadly)//32EAC, 333AC (F)
{
	long dx = lara_item->pos.x_pos - item->pos.x_pos;
	long dz = lara_item->pos.z_pos - item->pos.z_pos;

	if (abs(dx) <= 16384 && abs(dz) <= 16384)
	{
		long size = (GetRandomControl() & 0x1FF) - yvel;
		struct SPARKS* sptr = &spark[GetFreeSpark()];

		if (size < 512)
			size = 512;

		sptr->On = 1;

		sptr->sR = sptr->sG = (GetRandomControl() & 0x1F) + 48;
		sptr->sB = (GetRandomControl() & 0x3F) - 64;

		sptr->dR = (GetRandomControl() & 0x3F) - 64;
		sptr->dG = (GetRandomControl() & 0x3F) - 128;
		sptr->dB = 32;
		

		sptr->ColFadeSpeed = 8;
		sptr->FadeToBlack = 8;
		sptr->TransType = 2;

		sptr->Life = sptr->sLife = (size >> 9) + (GetRandomControl() & 7) + 16;

		sptr->x = (GetRandomControl() & 0x1F) + item->pos.x_pos - 16;
		sptr->y = (GetRandomControl() & 0x1F) + item->pos.y_pos - 16;
		sptr->z = (GetRandomControl() & 0x1F) + item->pos.z_pos - 16;

		sptr->Friction = 51;
		sptr->MaxYvel = 0;
		
		sptr->Flags = 538;
		if (deadly)
			sptr->Flags = 539;
		sptr->Scalar = 2;

		sptr->dSize = (GetRandomControl() & 0xF) + (size >> 6) + 16;
		sptr->sSize = sptr->Size = sptr->dSize >> 1;

		if ((-(item->trigger_flags & 0xFF) & 7) == 1)
		{
			sptr->Gravity = -16 - (GetRandomControl() & 0x1F);
			sptr->Xvel = (GetRandomControl() & 0xFF) - 128;
			sptr->Yvel = -size;
			sptr->Zvel = (GetRandomControl() & 0xFF) - 128;
			sptr->dSize += sptr->dSize >> 2;
			return;
		}

		sptr->y -= 64;
		sptr->Gravity = -((size >> 9) + GetRandomControl() % (size >> 8));
		sptr->Yvel = (GetRandomControl() & 0xFF) - 128;
		sptr->Xvel = (GetRandomControl() & 0xFF) - 128;
		sptr->Zvel = (GetRandomControl() & 0xFF) - 128;

		if (item->pos.y_rot == 0)
		{
			sptr->Zvel = -(size - (size >> 2));
		}
		else if (item->pos.y_rot == ANGLE(90))
		{
			sptr->Xvel = -(size - (size >> 2));
		}
		else if (item->pos.y_rot == ANGLE(-180))
		{
			sptr->Zvel = size - (size >> 2);
		}
		else
		{
			sptr->Xvel = size - (size >> 2);
		}
	}
}

void DetatchSpark(long num, long type)//32D8C, 3328C (F)
{
	struct FX_INFO* fx = &effects[num];
	struct ITEM_INFO* item = &items[num];	
	struct SPARKS* sptr = &spark[0];

	long lp;
	for(lp = 0; lp < 1024; lp++, sptr++)
	{
		if (sptr->On && sptr->Flags & type && sptr->FxObj == num)
		{
			if (type == 64)
			{
				sptr->x += fx->pos.x_pos;
				sptr->y += fx->pos.y_pos;
				sptr->z += fx->pos.z_pos;

				sptr->Flags &= 0xBF;
			}
			else if(type == 128)
			{
				sptr->x += item->pos.x_pos;
				sptr->y += item->pos.y_pos;
				sptr->z += item->pos.z_pos;

				sptr->Flags &= 0x7F;
			}
		}
	}
}

void TriggerGunSmoke(long x, long y, long z, long xv, long yv, long zv, int a7, int a8, int a9)//8D6D4(<), 8F718(<) (F)
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
		if (room[lara_item->room_number].flags & RF_WIND_BLOWS_PONYTAIL)
			spark->Flags = 272;
		else
			spark->Flags = 16;
		spark->RotAng = GetRandomControl() & 0xFFF;
		if (GetRandomControl() & 1)
			spark->RotAdd = -16 - (GetRandomControl() & 0xF);
		else
			spark->RotAdd = (GetRandomControl() & 0xF) + 16;
	}
	else if (room[lara_item->room_number].flags & RF_WIND_BLOWS_PONYTAIL)
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

void TriggerDynamic(long x, long y, long z, int falloff, int r, int g, int b)
{
	UNIMPLEMENTED();
}

void TriggerFireFlame(int x, int y, int z, int fxObj, signed int a5)
{
	UNIMPLEMENTED();
}

void TriggerFontFire(struct ITEM_INFO* item, int a2, int a3)
{
	UNIMPLEMENTED();
}
void TriggerHydraMissileFlame(struct PHD_VECTOR* pos, long x, long y, long z)
{
	UNIMPLEMENTED();
}

void TriggerRomanGodMissileFlame(struct PHD_VECTOR* pos, long fx_number)
{
	UNIMPLEMENTED();
}

void TriggerTorpedoSteam(struct PHD_VECTOR *pos, struct PHD_VECTOR *a2, int a3)// (F)
{
	struct SPARKS*  sptr = &spark[GetFreeSpark()];
	long size;

	sptr->On = 1;

	sptr->sR = 32;
	sptr->sG = 32;
	sptr->sB = 32;

	sptr->dR = 128;
	sptr->dG = 128;
	sptr->dB = 128;

	sptr->ColFadeSpeed = 2;
	sptr->FadeToBlack = 8;
	sptr->TransType = 2;

	sptr->Life = sptr->sLife = (GetRandomControl() & 7) + 16;

	sptr->x = (GetRandomControl() & 0x1F) + pos->x - 16;
	sptr->y = (GetRandomControl() & 0x1F) + pos->y - 16;
	sptr->z = (GetRandomControl() & 0x1F) + pos->z - 16;

	sptr->Xvel = a2->x + (GetRandomControl() & 0x7F) - pos->x - 64;
	sptr->Yvel = a2->y + (GetRandomControl() & 0x7F) - pos->y - 64;
	sptr->Zvel = a2->z + (GetRandomControl() & 0x7F) - pos->z - 64;

	sptr->Friction = 51;
	sptr->Gravity = -4 - (GetRandomControl() & 3);
	sptr->MaxYvel = 0;
	sptr->Scalar = 2 - a3;
	sptr->Flags = 538;

	sptr->RotAng = GetRandomControl() & 0xFFF;
	sptr->RotAdd = (GetRandomControl() & 0x3F) - 32;

	size = (GetRandomControl() & 0xF) + 32;
	sptr->sSize = size;
	sptr->Size = size;
	sptr->dSize = 2 * size;
}

void TriggerSubMist(struct PHD_VECTOR *pos, struct PHD_VECTOR *a4, int a5)// (F)
{
	struct SPARKS*  sptr = &spark[GetFreeSpark()];
	int v3 = 0;
	int size;
	if (a5 < 0)
	{
		a5 = -a5;
		v3 = 2;
	}

	sptr->sR = 32;
	sptr->sG = 32;
	sptr->sB = 32;

	sptr->On = 1;

	sptr->dR = 160;
	sptr->dG = 160;
	sptr->dB = 160;

	sptr->ColFadeSpeed = 2;
	sptr->FadeToBlack = 6;
	sptr->TransType = 2;

	sptr->Life = sptr->sLife = (GetRandomControl() & 7) - a5 + 16;

	sptr->x = (GetRandomControl() & 0x1F) + pos->x - 16;
	sptr->y = (GetRandomControl() & 0x1F) + pos->y - 16;
	sptr->z = (GetRandomControl() & 0x1F) + pos->z - 16;

	sptr->Xvel = a4->x + (GetRandomControl() & 0x7F) - pos->x - 64;
	sptr->Yvel = a4->y + (GetRandomControl() & 0x7F) - pos->y - 64;
	sptr->Zvel = a4->z + (GetRandomControl() & 0x7F) - pos->z - 64;

	sptr->Friction = 0;
	sptr->Def = (objects[DEFAULT_SPRITES].mesh_index & 0xFF) + (v3 != 0 ? 17 : 13);
	sptr->MaxYvel = 0;
	sptr->Gravity = -4 - (GetRandomControl() & 3);
	sptr->Scalar = 1;

	if (v3)
	{
		sptr->Flags = 26;

		sptr->RotAng = GetRandomControl() & 0xFFF;
		sptr->RotAdd = (GetRandomControl() & 0xF) - 8;

		size = (GetRandomControl() & 0xF) + 2 * a5 + 8;
		sptr->sSize = size;
		sptr->Size = size;
		sptr->dSize = 2 * size;
	}
	else
	{
		sptr->Flags = 10;

		size = (GetRandomControl() & 3) + a5 + 4;
		sptr->dSize = size;
		sptr->sSize = size >> 1;
		sptr->Size = size >> 1;
	}
}

void TriggerEngineEffects()
{
	UNIMPLEMENTED();
}

void TriggerAirBubbles()// (F)
{
	struct PHD_VECTOR pos, v8;
	struct SPARKS* sptr;
	long size;

	pos.x = 0;
	pos.y = -192;
	pos.z = -160;
	GetLaraJointPos(&pos, 7);

	v8.x = 0;
	v8.y = -192;
	v8.z = -512 - (GetRandomControl() & 0x7F);
	GetLaraJointPos(&v8, 7);

	sptr = &spark[GetFreeSpark()];

	sptr->sR = 32;
	sptr->sG = 32;
	sptr->sB = 32;

	sptr->On = 1;

	sptr->dR = -96;
	sptr->dG = -96;
	sptr->dB = -96;

	sptr->ColFadeSpeed = 2;
	sptr->FadeToBlack = 6;
	sptr->TransType = 2;

	sptr->Life = sptr->sLife = (GetRandomControl() & 7) + 16;

	sptr->x = (GetRandomControl() & 0x1F) + pos.x - 16;
	sptr->y = (GetRandomControl() & 0x1F) + pos.y - 16;
	sptr->z = (GetRandomControl() & 0x1F) + pos.z - 16;

	sptr->Xvel = (GetRandomControl() & 0x7F) - pos.x + v8.x - 64;
	sptr->Yvel = (GetRandomControl() & 0x7F) - pos.y + v8.y - 64;
	sptr->Zvel = (GetRandomControl() & 0x7F) - pos.z + v8.z - 64;

	sptr->Friction = 0;
	sptr->Def = (objects[458].mesh_index & 0xFF) + 17;
	sptr->MaxYvel = 0;
	sptr->Gravity = -4 - (GetRandomControl() & 3);

	sptr->Scalar = 1;
	sptr->Flags = 26;

	sptr->RotAng = GetRandomControl() & 0xFFF;
	sptr->RotAdd = (GetRandomControl() & 0xF) - 8;

	size = (GetRandomControl() & 0xF) + 16;
	sptr->sSize = size;
	sptr->Size = size;
	sptr->dSize = 2 * size;
}

void FlamingHell(struct PHD_VECTOR* pos)
{
	struct SPARKS* sptr = &spark[GetFreeSpark()];

	long yvel = MAX(512, (GetRandomControl() & 0x1FF) - 128);

	long tmp = (GetRandomControl() & 0x1F) + 48;
	long size;
	
	sptr->sR = tmp;
	sptr->sG = tmp;
	sptr->sB = (GetRandomControl() & 0x3F) - 64;

	sptr->dR = (GetRandomControl() & 0x3F) - 64;
	sptr->dG = (GetRandomControl() & 0x3F) - 128;
	sptr->dB = 32;

	sptr->ColFadeSpeed = 8;
	sptr->FadeToBlack = 8;
	sptr->TransType = 2;

	sptr->Life = sptr->sLife = (GetRandomControl() & 0x3F) + 90;

	sptr->x = GetRandomControl() + pos->x - 128;
	sptr->y = GetRandomControl() + pos->y - 256;
	sptr->z = GetRandomControl() + pos->z - 128;

	sptr->Xvel = (GetRandomControl() & 0xFF) - 128;
	sptr->Yvel = -(yvel & 0xFFFF);
	sptr->Zvel = (GetRandomControl() & 0xFF) - 128;

	sptr->Friction = 51;
	sptr->MaxYvel = 0;
	sptr->Gravity = -16 - (GetRandomControl() & 0x1F);

	sptr->Scalar = 2;
	sptr->Flags = 538;

	size = (GetRandomControl() & 0xF) + (yvel >> 6) + 16;
	sptr->sSize = size >> 1;
	sptr->Size = size >> 1;
	sptr->dSize = size;
}