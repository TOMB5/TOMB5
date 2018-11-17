#include "MISSILE.H"

#include "ITEMS.H"
#include "SPECIFIC.H"
#include "EFFECTS.H"
#include "CONTROL.H"
#include "CAMERA.H"
#include "SOUND.H"
#include "TOMB4FX.H"
#include "DRAW.H"
#include "DEBRIS.H"

#if PSX_VERSION || PSXPC_VERSION
#include "MISC.H"
#endif


struct ITEM_LIGHT fxil;

void ControlBodyPart(short fx_number)//4E600, 4EA64 (F)
{
	struct FX_INFO* fx = &effects[fx_number];
	int ox = fx->pos.x_pos;
	int oy = fx->pos.y_pos;
	int oz = fx->pos.z_pos;
	short room_number;
	struct FLOOR_INFO* floor;
	int height, ceiling;
	if (fx->counter <= 0)
	{
		if (fx->speed != 0)
			fx->pos.x_rot += 4 * fx->fallspeed;

		fx->fallspeed += 6;
	}
	else
	{
		if (fx_number & 1)
		{
			fx->pos.x_rot += 2 * (GetRandomControl() % (62 - fx->counter));
			fx->pos.z_rot -= 2 * (GetRandomControl() % (62 - fx->counter));
		}
		else
		{
			fx->pos.x_rot -= 2 * (GetRandomControl() % (62 - fx->counter));
			fx->pos.z_rot += 2 * (GetRandomControl() % (62 - fx->counter));
		}

		if (--fx->counter < 8)
			fx->fallspeed += 2;
	}

	fx->pos.y_pos += fx->fallspeed;
	fx->pos.z_pos += (fx->speed * 4 * COS(fx->pos.y_rot) >> W2V_SHIFT);
	fx->pos.x_pos += (fx->speed * 4 * SIN(fx->pos.y_rot) >> W2V_SHIFT);

	room_number = fx->room_number;

	floor = GetFloor(fx->pos.x_pos, fx->pos.y_pos, fx->pos.z_pos, &room_number);
	if (fx->counter == 0)
	{
		ceiling = GetCeiling(floor, fx->pos.x_pos, fx->pos.y_pos, fx->pos.z_pos);
		if (fx->pos.y_pos < ceiling)
		{
			fx->pos.y_pos = ceiling;
			fx->fallspeed = -fx->fallspeed;
			fx->speed -= fx->speed >> 3;
		}

		height = GetHeight(floor, fx->pos.x_pos, fx->pos.y_pos, fx->pos.z_pos);
		if (fx->pos.y_pos >= height)
		{
			if (fx->flag2 & 1)
			{
				fx->pos.x_pos = ox;
				fx->pos.y_pos = oy;
				fx->pos.z_pos = oz;

				if (fx->flag2 & 0x200)
					ExplodeFX(fx, -2, 32);
				else
					ExplodeFX(fx, -1, 32);

				KillEffect(fx_number);

				if (fx->flag2 & 0x800)
					SoundEffect(SFX_ROCK_FALL_LAND, &fx->pos, 0);
				return;
			}

			if (oy <= height)
			{
				fx->fallspeed = fx->fallspeed;
				if (fx->fallspeed <= 32)
					fx->fallspeed = 0;
				else
					fx->fallspeed = -fx->fallspeed >> 2;
			}
			else
			{
				fx->pos.y_rot -= ANGLE(180);
				fx->pos.x_pos = ox;
				fx->pos.z_pos = oz;
			}

			fx->speed -= fx->speed >> 2;
			if (abs(fx->speed) < 4)
				fx->speed = 0;
			fx->pos.y_pos = oy;
		}

		if (fx->speed == 0 && ++fx->flag1 > 32)
		{
			KillEffect(fx_number);
			return;
		}

		if (fx->flag2 & 2 && GetRandomControl() & 1)
		{
			DoBloodSplat(
				(GetRandomControl() & 0x3F) + fx->pos.x_pos - 32, 
				(GetRandomControl() & 0x1F) + fx->pos.y_pos - 16, 
				(GetRandomControl() & 0x3F) + fx->pos.z_pos - 32, 
				1, 2 * GetRandomControl(), fx->room_number);
		}
	}

	if (room_number != fx->room_number)
		EffectNewRoom(fx_number, room_number);
}

int ExplodeFX(struct FX_INFO* fx, int NoXZVel, long bits)//4E4E0, 4E944 (F)
{
	short** meshpp = &meshes[fx->frame_number];

	ShatterItem.YRot = fx->pos.y_rot;
	ShatterItem.meshp = *meshpp;
	ShatterItem.Sphere.x = fx->pos.x_pos;
	ShatterItem.Sphere.y = fx->pos.y_pos;
	ShatterItem.Sphere.z = fx->pos.z_pos;
	ShatterItem.Bit = 0;
	ShatterItem.Flags = fx->flag2 & 0x1400;

	if (fx->flag2 & 0x2000)
		DebrisFlags = 1;

	ShatterObject(&ShatterItem, 0, bits, fx->room_number, NoXZVel);

	DebrisFlags = 0;

	return 1;
}