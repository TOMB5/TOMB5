#include "TOMB4FX.H"

#if PSX_VERSION
#include "CALCLARA.H"
#endif

#include "SPECIFIC.H"
#include "EFFECT2.H"
#include "LARA.H"
#include "OBJECTS.H"
#include "DELSTUFF.H"
#include "CONTROL.H"
#include "DRAW.H"

#include "CAMERA.H"

#include "EFFECTS.H"
#include "DELTAPAK.H"
#include "SOUND.H"
#ifdef PC_VERSION
#include "GLOBAL.H"
#include "GAME.H"
#else
#include "SETUP.H"
#include "DRAWPHAS.H"
#include "MATHS.H"
#endif

#if PSX_VERSION || PSXPC_VERSION
#include "MISC.H"
#endif


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

char LaserSightActive = 0;
char LaserSightCol = 0;
long next_fire_spark = 1;
long next_smoke_spark = 0;
long next_gunshell = 0;
long next_bubble = 0;
long next_drip = 0;
long next_blood = 0;
long next_spider = 0;

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

void UpdateFadeClip()//34A9C(<), 34F9C(<) (F)
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
	struct DRIP_STRUCT* drip = &Drips[next_drip];
	int drip_num = next_drip;
	short min_life = 4095;
	short min_index = 0;
	short count = 0;
	while (drip->On)
	{
		if (drip->Life < min_life)
		{
			min_index = drip_num;
			min_life = drip->Life;
		}

		if (drip_num == 31)
		{
			drip = &Drips[0];
			drip_num = 0;
		}
		else
		{
			drip_num++;
			drip++;
		}

		if (++count >= 32)
		{
			next_drip = (min_index + 1) % 32;
			return min_index;
		}
	}

	next_drip = (drip_num + 1) % 32;
	return drip_num;
}

void TriggerLaraDrips()// (F)
{
	int i;
	struct PHD_VECTOR pos;
	struct DRIP_STRUCT* dptr;

	if (!(wibble & 0xF))
	{
		for(i = 14; i >= 0; i--)
		{
			if (lara.wet[i] && !LaraNodeUnderwater[14 - i] && (GetRandomControl() & 0x1FF) < lara.wet[i])
			{
				
				pos.x = (GetRandomControl() & 0x1F) - 16;
				pos.y = (GetRandomControl() & 0xF) + 16;
				pos.z = (GetRandomControl() & 0x1F) - 16;

				dptr = &Drips[GetFreeDrip()];
				GetLaraJointPos(&pos, i);
				dptr->x = pos.x;
				dptr->y = pos.y;
				dptr->z = pos.z;
				dptr->On = 1;
				dptr->R = (GetRandomControl() & 7) + 16;
				dptr->G = (GetRandomControl() & 7) + 24;
				dptr->B = (GetRandomControl() & 7) + 32;
				dptr->Yvel = (GetRandomControl() & 0x1F) + 32;
				dptr->Gravity = (GetRandomControl() & 0x1F) + 32;
				dptr->Life = (GetRandomControl() & 0x1F) + 8;
				dptr->RoomNumber = lara_item->room_number;

				lara.wet[i] -= 4;
			}
		}
	}
}

int GetFreeSmokeSpark()// (F)
{
	struct SMOKE_SPARKS* spark = &smoke_spark[next_smoke_spark];
	int spark_num = next_smoke_spark;
	short min_life = 4095;
	short min_index = 0;
	short count = 0;
	while (spark->On)
	{
		if (spark->Life < min_life)
		{
			min_index = spark_num;
			min_life = spark->Life;
		}

		if (spark_num == 31)
		{
			spark = &smoke_spark[0];
			spark_num = 0;
		}
		else
		{
			spark_num++;
			spark++;
		}

		if (++count >= 32)
		{
			next_smoke_spark = (min_index + 1) % 32;
			return min_index;
		}
	}

	next_smoke_spark = (spark_num + 1) % 32;
	return spark_num;
}

int GetFreeSpark()//8B2F8(<), 8D33C(<) (F)
{
	long lp;
	struct SPARKS* sptr;
	struct SPARKS* fsptr;
	long free = next_spark;

	sptr = &spark[free];

	for (lp = 0; lp < 0x80; lp++, sptr++)
	{
		if (!sptr->On)
		{

			next_spark = (free + 1) & 0x7F;
			sptr->Def = objects[DEFAULT_SPRITES].mesh_index;
			sptr->extras = 0;
			sptr->Dynamic = -1;
			return free;

		}
		
		//loc_8B35C
		if (free++ == 0x7F)
		{
			sptr = (struct SPARKS*)&temp_rotation_buffer[0];
			free = 0;
		}
	}

	sptr = &spark[0];

	//loc_8B394
	for (lp = 0; lp < 0x80; ++lp, sptr++)
	{
		if (sptr->Life < 0xFFF && sptr->Dynamic == -1 && !(sptr->Flags & 0x20))
		{
			free = lp - 1;
			fsptr = sptr;
		}//loc_8B3C8
	}

	next_spark = (free + 1) & 0x7F;
	fsptr->Def = objects[DEFAULT_SPRITES].mesh_index;
	fsptr->extras = 0;
	fsptr->Dynamic = -1;

	return free;

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

int GetFreeBlood()// (F)
{
	struct BLOOD_STRUCT* bptr = &blood[next_blood];
	int bptr_num = next_blood;
	int min_life = 4095;
	int min_life_num = 0;
	int count = 0;
	
	while(bptr->On)
	{
		if (bptr->Life < min_life)
		{
			min_life_num = bptr_num;
			min_life = bptr->Life;
		}

		if (bptr_num == 31)
		{
			bptr = &blood[0];
			bptr_num = 0;
		}
		else
		{
			bptr++;
			bptr_num++;
		}

		if (++count >= 32)
		{
			next_blood = (min_life_num + 1) & 31;
			return min_life_num;
		}
	}

	next_blood = (bptr_num + 1) & 31;
	return bptr_num;
}

void TriggerBlood(int x, int y, int z, int a4, int num)// (F)
{
	int i;
	struct BLOOD_STRUCT* bptr;
	int a;
	int b;
	int size;

	for(i = 0; i < num; i++)
	{
		bptr = &blood[GetFreeBlood()];
		bptr->On = 1;
		bptr->sShade = 0;
		bptr->ColFadeSpeed = 4;
		bptr->FadeToBlack = 8;
		bptr->dShade = (GetRandomControl() & 0x3F) + 48;
		bptr->Life = bptr->sLife = (GetRandomControl() & 7) + 24;
		bptr->x = (GetRandomControl() & 0x1F) + x - 16;
		bptr->y = (GetRandomControl() & 0x1F) + y - 16;
		bptr->z = (GetRandomControl() & 0x1F) + z - 16;
		a = (a4 == -1
			? GetRandomControl() & 0xFFFF
			: (GetRandomControl() & 0x1F) + a4 - 16) & 0xFFF;
		b = GetRandomControl() & 0xF;
		bptr->Zvel = b * rcossin_tbl[2 * a + 1] >> 7;
		bptr->Xvel = -(b * rcossin_tbl[2 * a]) >> 7;
		bptr->Friction = 4;
		bptr->Yvel = -((GetRandomControl() & 0xFF) + 128);
		bptr->RotAng = GetRandomControl() & 0xFFF;
		bptr->RotAdd = (GetRandomControl() & 0x3F) + 64;
		if (GetRandomControl() & 1)
			bptr->RotAdd = -bptr->RotAdd;
		bptr->Gravity = (GetRandomControl() & 0x1F) + 31;
		size = (GetRandomControl() & 7) + 8;
		bptr->sSize = bptr->Size = size;
		bptr->dSize = size >> 2;
	}
}

void TriggerExplosionBubble(int x, int y, int z, short room_num)// (F)
{
	int i;
	struct PHD_VECTOR pos;
	int size;
	struct SPARKS* sptr;
	int dx = lara_item->pos.x_pos - x;
	int dz = lara_item->pos.z_pos - z;

	if (dx >= -16384 && dx <= 16384 && dz >= -16384 && dz <= 16384)
	{
		sptr = &spark[GetFreeSpark()];
		sptr->sR = 128;
		sptr->dR = 128;
		sptr->dG = 128;
		sptr->dB = 128;
		sptr->On = 1;
		sptr->Life = 24;
		sptr->sLife = 24;
		sptr->sG = 64;
		sptr->sB = 0;
		sptr->ColFadeSpeed = 8;
		sptr->FadeToBlack = 12;
		sptr->TransType = 2;
		sptr->x = x;
		sptr->y = y;
		sptr->z = z;
		sptr->Xvel = 0;
		sptr->Yvel = 0;
		sptr->Zvel = 0;
		sptr->Friction = 0;
		sptr->Flags = 2058;
		sptr->Scalar = 3;
		sptr->Gravity = 0;
		sptr->Def = objects[DEFAULT_SPRITES].mesh_index + 13;
		sptr->MaxYvel = 0;
		size = (GetRandomControl() & 7) + 63;
		sptr->sSize = size >> 1;
		sptr->Size = size >> 1;
		sptr->dSize = 2 * size;

		for(i = 0; i < 8; i++)
		{
			pos.x = (GetRandomControl() & 0x1FF) + x - 256;
			pos.y = (GetRandomControl() & 0x7F) + y - 64;
			pos.z = (GetRandomControl() & 0x1FF) + z - 256;
			CreateBubble(&pos, room_num, 6, 15, 0, 0, 0, 0);
		}
	}
}

void TriggerExplosionSmokeEnd(int x, int y, int z, int a4)// (F)
{
	struct SPARKS* sptr = &spark[GetFreeSpark()];
	int size;
	sptr->On = 1;
	if (a4)
	{
		sptr->sR = 0;
		sptr->sG = 0;
		sptr->sB = 0;
		sptr->dR = 192;
		sptr->dG = 192;
		sptr->dB = 208;
	}
	else
	{
		sptr->dR = 64;
		sptr->sR = 144;
		sptr->sG = 144;
		sptr->sB = 144;
		sptr->dG = 64;
		sptr->dB = 64;
	}

	sptr->ColFadeSpeed = 8;
	sptr->FadeToBlack = 64;
	sptr->Life = sptr->sLife = (GetRandomControl() & 0x1F) + 96;
	if (a4)
		sptr->TransType = 2;
	else
		sptr->TransType = 3;
	sptr->x = (GetRandomControl() & 0x1F) + x - 16;
	sptr->y = (GetRandomControl() & 0x1F) + y - 16;
	sptr->z = (GetRandomControl() & 0x1F) + z - 16;
	sptr->Xvel = ((GetRandomControl() & 0xFFF) - 2048) >> 2;
	sptr->Yvel = (GetRandomControl() & 0xFF) - 128;
	sptr->Zvel = ((GetRandomControl() & 0xFFF) - 2048) >> 2;
	if (a4)
	{
		sptr->Friction = 20;
		sptr->Yvel >>= 4;
		sptr->y += 32;
	}
	else
	{
		sptr->Friction = 6;
	}
	sptr->Flags = 538;
	sptr->RotAng = GetRandomControl() & 0xFFF;
	if (GetRandomControl() & 1)
		sptr->RotAdd = -((GetRandomControl() & 0xF) + 16);
	else
		sptr->RotAdd = (GetRandomControl() & 0xF) + 16;
	sptr->Scalar = 3;
	if (a4)
	{
		sptr->MaxYvel = 0;
		sptr->Gravity = 0;
	}
	else
	{
		sptr->Gravity = -3 - (GetRandomControl() & 3);
		sptr->MaxYvel = -4 - (GetRandomControl() & 3);
	}
	size = (GetRandomControl() & 0x1F) + 128;
	sptr->dSize = size;
	sptr->sSize = size >> 2;
	sptr->Size = size >> 2;
}

void TriggerExplosionSparks(int x, int y, int z, int a4, int a5, int a6, short room_no)
{
	UNIMPLEMENTED();
}

int GetFreeShockwave()// (F)
{
	int i;

	for(i = 0; i < 16; i++)
	{
		if (!ShockWaves[i].life)
			return i;
	}

	return -1;
}

void TriggerShockwave(struct PHD_3DPOS* pos, short inner_rad, short outer_rad, int speed, char r, char g, char b, char life, short angle, short flags)// (F)
{
	int s = GetFreeShockwave();
	struct SHOCKWAVE_STRUCT* sptr;

	if (s != -1)
	{
		sptr = &ShockWaves[s];

		sptr->x = pos->x_pos;
		sptr->y = pos->y_pos;
		sptr->z = pos->z_pos;
		sptr->InnerRad = inner_rad;
		sptr->OuterRad = outer_rad;
		sptr->XRot = angle;
		sptr->Flags = flags;
		sptr->Speed = speed;
		sptr->r = r;
		sptr->g = g;
		sptr->b = b;
		sptr->life = life;

		SoundEffect(SFX_IMP_STONE_HIT, pos, 0);
	}
}

void Fade()//34B78(<), 35078(<) (F)
{
	if (dScreenFade != 0)
	{
		if (dScreenFade > ScreenFade)
		{
			ScreenFade = ScreenFadeSpeed + ScreenFade;

			if (ScreenFade < dScreenFade)
			{
				ScreenFade = dScreenFade;

				if (ScreenFade > dScreenFade)
				{
					ScreenFadedOut = 1;

					if (ScreenFadeBack == 0)
					{
						//loc_34C30
						ScreenFading = 0;
					}

					dScreenFade = 0;
					ScreenFadeBack = 0;
				}//loc_34C34
			}//loc_34C34
		}
		else
		{
			//loc_34BFC
			ScreenFade -= ScreenFadeSpeed;
			if (ScreenFade < dScreenFade)
			{
				//loc_34C30
				ScreenFade = dScreenFade;
			}//loc_34C34
		}
	}
	else
	{
		//loc_34BF0

		if (dScreenFade < ScreenFade)
		{
			//loc_34BFC
			ScreenFade -= ScreenFadeSpeed;
			if (ScreenFade < dScreenFade)
			{
				//loc_34C30
				ScreenFade = dScreenFade;
			}//loc_34C34
		}//loc_34C34
	}

	//loc_34C34
	if(ScreenFade == 0 && dScreenFade == 0)
	{
		return;
	}

	//loc_34C4C
#if PSX_VERSION
	 DrawPsxTile(0, 0xF00200, (dScreenFade << 16) | (ScreenFade << 8) | ScreenFade | 0x62000000, 2);
#else
	// todo add DrawPsxTile on spec_psxpc and spec_pc
	//DrawPsxTile(0, window_width | (window_height << 16), (dScreenFade << 16) | (ScreenFade << 8) | ScreenFade);
#endif
}

void SetUpLensFlare(long x, long y, long z, struct GAME_VECTOR* bulb)
{
	UNIMPLEMENTED();
}

int ExplodingDeath2(short item_number, long mesh_bits, short Flags)
{
	UNIMPLEMENTED();
	return 0;
}

void DrawLensFlares(struct ITEM_INFO *item)// (F)
{
	struct GAME_VECTOR pos;

	pos.x = item->pos.x_pos;
	pos.y = item->pos.y_pos;
	pos.z = item->pos.z_pos;
	pos.room_number = item->room_number;

	SetUpLensFlare(0, 0, 0, &pos);
}

void TriggerLightningGlow(long x, long y, long z, long rgb)// (F)
{
	long size;
	struct SPARKS* sptr = &spark[GetFreeSpark()];

	sptr->dG = GREEN(rgb);
	sptr->sG = GREEN(rgb);
	sptr->Life = 4;
	sptr->sLife = 4;
	sptr->dR = RED(rgb);
	sptr->sR = RED(rgb);
	sptr->ColFadeSpeed = 2;
	sptr->TransType = 2;
	sptr->x = x;
	sptr->On = 1;
	sptr->dB = BLUE(rgb);
	sptr->sB = BLUE(rgb);
	sptr->FadeToBlack = 0;
	sptr->y = y;
	sptr->z = z;
	sptr->Zvel = 0;
	sptr->Yvel = 0;
	sptr->Xvel = 0;
	sptr->Flags = 10;
	sptr->Scalar = 3;
	sptr->MaxYvel = 0;
	sptr->Def = objects[DEFAULT_SPRITES].mesh_index + 11;
	sptr->Gravity = 0;
	size = ALPHA(rgb) + (GetRandomControl() & 3);
	sptr->dSize = size;
	sptr->sSize = size;
	sptr->Size = size;
}

void trig_actor_gunflash(struct MATRIX3D* matrix, struct PHD_VECTOR* pos)//(F)
{
#if PSX_VERSION//Likely different for PC
	struct GUNFLASH_STRUCT* fx;
	long lp;

	fx = &Gunflashes[0];

	//loc_36638:
	for (lp = 0; lp < 4; lp++, fx++)
	{
		if (!fx->on)
		{
			fx->on = 1;
			mPushMatrix();
			mCopyMatrix(matrix);
			mTranslateXYZ(pos->x, pos->y, pos->z);
			mRotX(-13680);
			snaff_current_gte_matrix_V1(&fx->matrix);
			mPopMatrix();
			break;
		}
	}
#endif
}

void TriggerFenceSparks(long x, long y, long z, long kill, long crane)//(F)
{
	struct SPARKS* sptr;

	sptr = &spark[GetFreeSpark()];
	sptr->On = 1;
	sptr->sR = (GetRandomControl() & 0x3F) - 0x40;
	sptr->sG = (GetRandomControl() & 0x3F) - 0x40;
	sptr->sB = (GetRandomControl() & 0x3F) - 0x40;

	sptr->dR = GetRandomControl() | 0xC0;
	sptr->ColFadeSpeed = 16;
	sptr->G = 8;
	sptr->dG = sptr->sR >> 1;
	sptr->dB = sptr->sR >> 2;

	sptr->Life = (GetRandomControl() & 7) + 24;
	sptr->sLife = (GetRandomControl() & 7) + 24;
	sptr->TransType = 2;
	sptr->Dynamic = -1;

	sptr->x = x;
	sptr->y = y;
	sptr->z = z;

	sptr->Xvel = ((GetRandomControl() & 0xFF) - 128) << 2;
	sptr->Yvel = (GetRandomControl() & 0xF) - ((kill << 5) + 8) + (crane << 4);
	sptr->Zvel = ((GetRandomControl() & 0xFF) - 128) << 2;

	if (crane != 0)
	{
		sptr->Friction = 5;
	}
	else
	{
		sptr->Friction = 4;
	}

	//loc_365C4
	sptr->Flags = 0;
	sptr->Gravity = (GetRandomControl() & 0xF) + ((crane << 4) + 16);
	sptr->MaxYvel = 0;
}

void ControlElectricFence(short item_number)
{
	UNIMPLEMENTED();
}

void ControlTeleporter(short item_number)
{
	UNIMPLEMENTED();
}

void DrawWeaponMissile(struct ITEM_INFO *item)
{
	UNIMPLEMENTED();
}

void DoBloodSplat(int x, int y, int z, short speed, short direction, short room_num)// (F)
{
	GetFloor(x, y, z, &room_num);
	if (room[room_num].flags & RF_FILL_WATER)
	{
		TriggerUnderwaterBlood(x, y, z, speed);
	}
	else
	{
		TriggerBlood(x, y, z, direction, speed);
	}
}

void TriggerRicochetSpark(struct GAME_VECTOR* pos, int angle, int num, int a4)
{
	UNIMPLEMENTED();
}

void Richochet(struct GAME_VECTOR* pos)// (F)
{
	TriggerRicochetSpark(pos, mGetAngle(pos->z, pos->x, lara_item->pos.z_pos, lara_item->pos.x_pos) >> 4, 3, 0);
	SoundEffect(SFX_LARA_RICOCHET, (struct PHD_3DPOS*)pos, 0);
}

void TriggerLightning(struct PHD_VECTOR* a1, struct PHD_VECTOR* a2, char a3, int a4, char a5, char a6, char a7)
{
	UNIMPLEMENTED();
}

void TriggerCoinGlow()
{
	UNIMPLEMENTED();
}

int GetFreeSpider()// (F)
{
	struct SPIDER_STRUCT* peter = &Spiders[next_spider];
	int peter_num = next_spider;
	int count = 0;

	while (peter->On)
	{
		if (peter_num == 63)
		{
			peter = &Spiders[0];
			peter_num = 0;
		}
		else
		{
			peter++;
			peter_num++;
		}

		if (++count >= 64)
			return -1;
	}

	next_spider = (peter_num + 1) & 63;
	return peter_num;
}

void TriggerSmallSplash(int x, int y, int z, int num)// (F)
{
	int i;
	int angle;

	for(i = 0; i < num; i++)
	{
		struct SPARKS* sptr = &spark[GetFreeSpark()];

		sptr->On = 1;

		sptr->sR = 64;
		sptr->sG = 64;
		sptr->sB = 64;

		sptr->dR = 32;
		sptr->dG = 32;
		sptr->dB = 32;

		sptr->ColFadeSpeed = 4;
		sptr->FadeToBlack = 8;

		sptr->Life = 24;
		sptr->sLife = 24;

		sptr->TransType = 2;

		angle = GetRandomControl() << 3;

		sptr->Xvel = -SIN(angle) >> 5;		
		sptr->Yvel = -640 - (GetRandomControl() & 0xFF);
		sptr->Zvel = COS(angle) >> 5;

		sptr->Friction = 5;	
		sptr->Flags = 0;

		sptr->x = x + (sptr->Xvel >> 3);
		sptr->y = y - (sptr->Yvel >> 5);
		sptr->z = z + (sptr->Zvel >> 3);

		sptr->MaxYvel = 0;
		sptr->Gravity = (GetRandomControl() & 0xF) + 64;
	}
}