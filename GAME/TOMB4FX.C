#include "TOMB4FX.H"

#include "SPECIFIC.H"
#include "EFFECT2.H"
#include "LARA.H"
#include "DELSTUFF.H"
#include "CONTROL.H"
#include "DRAW.H"

char flare_table[121] =
{
	0x60, 0x50, 0x00, 0x06, 0x00, 0x1F, 0x30, 0x20, 0x20, 0x0A, 0xFA, 0x1F, 0x20, 0x18, 
	0x18, 0x12, 0xFF, 0x1F, 0x50, 0x68, 0x40, 0x05, 0xFD, 0x1E, 0x40, 0x40, 0x40, 0x14, 
	0x00, 0x20, 0x60, 0x38, 0x38, 0x0E, 0x00, 0x0B, 0x50, 0x28, 0x20, 0x09, 0x00, 0x1D, 
	0x10, 0x18, 0x28, 0x02, 0x05, 0x1F, 0x08, 0x08, 0x18, 0x07, 0x08, 0x1F, 0x08, 0x10, 
	0x20, 0x04, 0x0A, 0x1F, 0x30, 0x18, 0x00, 0x02, 0x0D, 0x1F, 0x28, 0x60, 0x48, 0x01, 
	0x10, 0x0B, 0x28, 0x60, 0x48, 0x03, 0x14, 0x0B, 0x20, 0x10, 0x00, 0x06, 0x16, 0x1F, 
	0x20, 0x10, 0x00, 0x09, 0x17, 0x1E, 0x20, 0x10, 0x00, 0x03, 0x18, 0x1F, 0x20, 0x30, 
	0x18, 0x04, 0x1A, 0x1F, 0x08, 0x28, 0x70, 0x03, 0x1B, 0x0B, 0x08, 0x10, 0x00, 0x0A, 
	0x1D, 0x1E, 0x10, 0x10, 0x18, 0x11, 0x1F, 0x1D, 0xFF
};

char LaserSightActive;
char LaserSightCol;
long next_fire_spark;
long next_smoke_spark;
long next_gunshell;
long next_bubble;
long next_drip;
long next_blood;

struct NODEOFFSET_INFO NodeOffsets[16] = // offset 0xA0A24
{
	{ -0x10, 0x28, 0xA0, -0xE, 0 },
	{ -0x10, -8, 0xA0, 0, 0 },
	{ 0, 0, 0x100, 8, 0 },
	{ 0, 0, 0x100, 0x11, 0 },
	{ 0, 0, 0x100, 0x1A, 0 },
	{ 0, 0x90, 0x28, 0xA, 0 },
	{ -0x28, 0x40, 0x168, 0xE, 0 },
	{ 0, -0x258, -0x28, 0, 0 },
	{ 0, 0x20, 0x10, 9, 0 },
	{ 0 },
	{ 0 },
	{ 0 },
	{ 0 },
	{ 0 },
	{ 0 },
	{ 0 }
};

short FlashFadeR;
short FlashFadeG;
short FlashFadeB;
short FlashFader;
short ScreenFade;
short dScreenFade;
short ScreenFadeSpeed;
short ScreenFadeBack;
short ScreenFadedOut;
short ScreenFading;
short FadeScreenHeight;
short DestFadeScreenHeight;
short FadeClipSpeed;
long LaserSightX;
long LaserSightY;
long LaserSightZ;
struct GUNFLASH_STRUCT Gunflashes[4]; // offset 0xA31D8
struct PHD_VECTOR NodeVectors[16]; // offset 0xA3274
struct FIRE_SPARKS fire_spark[20]; // offset 0xA94FC
struct SMOKE_SPARKS smoke_spark[32]; // offset 0xA8F7C
struct GUNSHELL_STRUCT Gunshells[24]; // offset 0xA7DFC
struct BLOOD_STRUCT blood[32]; // offset 0xA88FC
struct BUBBLE_STRUCT Bubbles[40]; // offset 0xA80FC
struct DRIP_STRUCT Drips[32]; // offset 0xA85FC
struct SHOCKWAVE_STRUCT ShockWaves[16]; // offset 0xA7C3C
struct FIRE_LIST fires[32]; // offset 0xA8D7C

void SetFadeClip(short height, short speed)//34A8C(<), 34F8C(<) (F)
{
	DestFadeScreenHeight = height;
	FadeClipSpeed = speed;

	return;
}

void UpdateFadeClip()//34A9C(<), 34F9C(<)
{
	if (DestFadeScreenHeight < FadeScreenHeight)
	{
		if (DestFadeScreenHeight < FadeScreenHeight - FadeClipSpeed)
		{
			FadeScreenHeight = DestFadeScreenHeight;
		}
	}
	else if(FadeScreenHeight < DestFadeScreenHeight)
	{
		if(DestFadeScreenHeight < FadeScreenHeight + FadeClipSpeed)
		{
			FadeScreenHeight = DestFadeScreenHeight;
		}
	}

	return;
}

void SetScreenFadeOut(long fadespeed, long fadeback)//34B14(<), 35014(<) (F)
{
	if (!ScreenFading)
	{
		ScreenFading = 1;
		ScreenFade = 0;
		dScreenFade = 255;
		ScreenFadeSpeed = fadespeed;
		ScreenFadeBack = fadeback;
		ScreenFadedOut = 0;
	}

	return;
}

void SetScreenFadeIn(long fadespeed)//34B48(<), 35048(<) (F)
{
	if(!ScreenFading)
	{
		ScreenFading = 1;
		ScreenFade = 255;
		dScreenFade = 0;
		ScreenFadeSpeed = fadespeed;
		ScreenFadedOut = 0;
	}

	return;
}

int GetFreeDrip()
{
	S_Warn("[GetFreeDrip] - Unimplemented!\n");
	return 0;

#if 0
	int var_8, var_C, var_10;

	if ((wibble & 0xF) != 0) return;

	auto t6 = 0xE;

	auto t7 = &lara.wet[14];

	loc_8CEB4:

	auto t8 = t7[0];

	auto v0 = &LaraNodeUnderwater[0];

	v0 += t6;

	if (t8 == 0) goto loc_8CFC4;

	v0 = v0[0];

	if (v0 != 0) goto loc_8CFC4;

	v0 = GetRandomControl();

	v0 &= 0x1FF;

	if (v0 >= t8) goto loc_8CFC4;

	v0 &= 0x1F;

	v0 -= 0x10;

	v0 = GetRandomControl();
	var_10 = v0;

	v0 &= 0xF;

	v0 += 0x10;

	v0 = GetRandomControl();
	var_C = v0;
	v0 &= 0x1F;
	v0 -= 0x10;

	auto a0 = &var_10;

	auto a1 = t6;

	var_8 = GetLaraJointPos((int)a0, a1);


	loc_8CFC4:
	t6--;
	t7--;
	if (t6 >= 0) goto loc_8CEB4;
#endif

}

int GetFreeSmokeSpark()
{
	S_Warn("[GetFreeSmokeSpark] - Unimplemented!\n");
	return 0;
}

int GetFreeSpark()
{
	S_Warn("[GetFreeSpark] - Unimplemented!\n");
	return 0;
}

int GetFreeBubble()//8BEAC(<), 8DEF0(<) (F)
{
	struct BUBBLE_STRUCT* bub = &Bubbles[next_bubble];
	int bub_num = next_bubble;

	while (bub->size != 0)
	{
		if (bub_num == 39)
		{
			bub = &Bubbles[0];
			bub_num = 0;
		}
		else
		{
			bub_num++;
			bub++;
		}

		if (++bub_num >= 40)
		{
			break;
		}
	}

	next_bubble = bub_num + 1;
	if (bub_num + 1 >= 40)
		next_bubble = 0;
	return bub_num;
}

void CreateBubble(struct PHD_VECTOR* pos, short room_num, int a3, int a4, int flags, int xv, int yv, int zv)//8BF14(<), 8DF58(<) (F)
{
	struct BUBBLE_STRUCT* v9;
	long size;

	GetFloor(pos->x, pos->y, pos->z, &room_num);

	if (room[room_num].flags & RF_FILL_WATER)
	{
		v9 = &Bubbles[GetFreeBubble()];
		v9->pos = *pos;
		v9->room_number = room_num;
		v9->speed = GetRandomControl() + 64;
		v9->shade = 0;
		size = 2 * (a3 + (a4 & GetRandomControl()));
		v9->size = size;
		v9->dsize = 16 * size;
		v9->vel = (GetRandomControl() & 0x1F) + 32;
		v9->Flags = flags;
		v9->Xvel = xv;
		v9->Yvel = yv;
		v9->Zvel = zv;
	}
}

void TriggerShatterSmoke(int x, int y, int z)//8AA14(<), 8CA58(<) (F)
{
	struct SMOKE_SPARKS* smoke;

	smoke = &smoke_spark[GetFreeSmokeSpark()];
	smoke->On = 1;
	smoke->sShade = 0;
	smoke->ColFadeSpeed = 4;
	smoke->dShade = (GetRandomControl() & 0x1F) + 64;
	smoke->FadeToBlack = 24 - (GetRandomControl() & 7);
	smoke->TransType = 2;
	smoke->Life = smoke->sLife = (GetRandomControl() & 7) + 48;
	smoke->x = (GetRandomControl() & 0x1F) + x - 16;
	smoke->y = (GetRandomControl() & 0x1F) + y - 16;
	smoke->z = (GetRandomControl() & 0x1F) + z - 16;
	smoke->Xvel = 2 * (GetRandomControl() & 0x1FF) - 512;
	smoke->Yvel = 2 * (GetRandomControl() & 0x1FF) - 512;
	smoke->Zvel = 2 * (GetRandomControl() & 0x1FF) - 512;
	smoke->Friction = 7;
	if (GetRandomControl() & 1)
	{
		smoke->Flags = 16;
		smoke->RotAng = GetRandomControl() & 0xFFF;
		if (GetRandomControl() & 1)
			smoke->RotAdd = -64 - (GetRandomControl() & 0x3F);
		else
			smoke->RotAdd = (GetRandomControl() & 0x3F) + 64;
	}
	else if (room[lara_item->room_number].flags & RF_WIND_BLOWS_PONYTAIL)
	{
		smoke->Flags = 256;
	}
	else
	{
		smoke->Flags = 0;
	}
	smoke->Gravity = -4 - (GetRandomControl() & 3);
	smoke->MaxYvel = -4 - (GetRandomControl() & 3);
	smoke->dSize = (GetRandomControl() & 0x3F) + 64;
	smoke->sSize = smoke->dSize >> 3;
	smoke->Size = smoke->dSize >> 3;
}

void TriggerBlood(int x, int y, int z, int direction, int speed)
{
	S_Warn("[TriggerBlood] - Unimplemented!\\n");
}

void TriggerExplosionBubble(int x, int y, int z, short room_num)
{
	S_Warn("[TriggerExplosionBubble] - Unimplemented!\\n");
}

void TriggerExplosionSparks(int x, int y, int z, int a4, int a5, int a6, short room_no)
{
	S_Warn("[TriggerExplosionSparks] - Unimplemented!\\n");
}
