#include "TRAPS.H"

#include "DRAW.H"
#include "CONTROL.H"
#include "EFFECTS.H"
#include "ITEMS.H"
#include "LARA.H"
#include "OBJECTS.H"
#include "SPECIFIC.H"
#include "TOMB4FX.H"
#include "EFFECT2.H"
#include "SOUND.H"
#include "COLLIDE.H"

short SPDETyoffs[8] =
{
	0x0400, 0x0200, 0x0200, 0x0200, 0x0000, 0x0200, 0x0200, 0x0200
};

unsigned char Flame3xzoffs[16][2] =
{
	{ 0x09, 0x09 },
	{ 0x18, 0x09 },
	{ 0x28, 0x09 },
	{ 0x37, 0x09 },
	{ 0x09, 0x18 },
	{ 0x18, 0x18 },
	{ 0x28, 0x18 },
	{ 0x37, 0x18 },
	{ 0x09, 0x28 },
	{ 0x18, 0x28 },
	{ 0x28, 0x28 },
	{ 0x37, 0x28 },
	{ 0x09, 0x37 },
	{ 0x18, 0x37 },
	{ 0x28, 0x37 },
	{ 0x37, 0x37 }
};

short SPyoffs[8] =
{
	0xFC00, 0x0000, 0xFE00, 0x0000, 0x0000, 0x0000, 0xFE00, 0x0000
};

short SPxzoffs[8] =
{
	0x0000, 0x0000, 0x0200, 0x0000, 0x0000, 0x0000, 0xFE00, 0x0000
};

static struct PHD_VECTOR FloorTrapDoorPos = { 0, 0, -655 }; // offset 0xA16B8
static short FloorTrapDoorBounds[12] = // offset 0xA16C4
{
	0xFF00, 0x0100, 0x0000, 0x0000, 0xFC00, 0xFF00, 0xF8E4, 0x071C, 0xEAAC, 0x1554, 
	0xF8E4, 0x071C
};
static struct PHD_VECTOR CeilingTrapDoorPos = { 0, 1056, -480 }; // offset 0xA16DC
static short CeilingTrapDoorBounds[12] = // offset 0xA16E8
{
	0xFF00, 0x0100, 0x0000, 0x0384, 0xFD00, 0xFF00, 0xF8E4, 0x071C, 0xEAAC, 0x1554, 
	0xF8E4, 0x071C
};

void ControlExplosion(short item_number)//5C8BC, 5CD38
{
	S_Warn("[ControlExplosion] - Unimplemented!\n");
	return;
}

void ControlRaisingBlock(short item_number)//5C56C, 5C9E8
{
	S_Warn("[ControlRaisingBlock] - Unimplemented!\n");
	return;
}

void ControlScaledSpike(short item_number)//5C000, 5C47C
{
	S_Warn("[ControlScaledSpike] - Unimplemented!\n");
	return;
}

int TestBoundsCollideTeethSpikes(struct ITEM_INFO* item)//5BE64, 5C2E0
{
	S_Warn("[TestBoundsCollideTeethSpikes] - Unimplemented!\n");
	return 0;
}

void ControlTwoBlockPlatform(short item_number)//5BC7C, 5C0F8
{
	S_Warn("[ControlTwoBlockPlatform] - Unimplemented!\n");
	return;
}

int OnTwoBlockPlatform(struct ITEM_INFO* item, long x, long z)//5BB80, 5BFFC (F)
{
	int tx = item->pos.x_pos >> 10;
	int tz = item->pos.z_pos >> 10;

	if (item->mesh_bits == 0)
		return FALSE;

	x >>= 10;
	z >>= 10;

	if (item->pos.y_rot == 0 && (x == tx || x == tx - 1) && (z == tz || z == tz + 1))
		return TRUE;

	if (item->pos.y_rot == ANGLE(-180) && (x == tx || x == tx + 1) && (z == tz || z == tz - 1))
		return TRUE;

	if (item->pos.y_rot == ANGLE(90) && (z == tz || z == tz - 1) && (x == tx || x == tx + 1))
		return TRUE;

	if (item->pos.y_rot == ANGLE(-90) && (z == tz || z == tz - 1) && (x == tx || x == tx - 1))
		return TRUE;

	return FALSE;
}

void TwoBlockPlatformCeiling(struct ITEM_INFO* item, long x, long y, long z, long* height)//5BB08, 5BF84 (F)
{
	if (OnTwoBlockPlatform(item, x, z))
	{
		if (y > item->pos.y_pos + 32 && item->pos.y_pos > *height)
		{
			*height = item->pos.y_pos + 256;
		}
	}
}

void TwoBlockPlatformFloor(struct ITEM_INFO* item, long x, long y, long z, long* height)//5BA80, 5BEFC (F)
{
	if (OnTwoBlockPlatform(item, x, z))
	{
		if (y <= item->pos.y_pos + 32 && item->pos.y_pos < *height)
		{
			*height = item->pos.y_pos;
			OnObject = 1;
			height_type = WALL;
		}
	}
}

void DrawScaledSpike(struct ITEM_INFO* item)//5B854, 5BCD0
{
	S_Warn("[DrawScaledSpike] - Unimplemented!\n");
	return;
}

void RollingBallCollision(short item_number, struct ITEM_INFO* laraitem, struct COLL_INFO* coll)//5B750, 5BBCC
{
	S_Warn("[RollingBallCollision] - Unimplemented!\n");
	return;
}

void ControlRollingBall(short item_number)//5AE08, 5B284
{
	S_Warn("[ControlRollingBall] - Unimplemented!\n");
	return;
}

void LavaBurn(struct ITEM_INFO* item)//5AD78, 5B1F4 (F)
{
	if (item->hit_points >= 0 && lara.water_status != LW_FLYCHEAT)
	{
		short room_number = item->room_number;

		if (item->floor == GetHeight(GetFloor(item->pos.x_pos, 32000, item->pos.z_pos, &room_number),
			item->pos.x_pos, 32000, item->pos.z_pos))
		{
			item->hit_points = -1;
			item->collidable = TRUE;
			LaraBurn();
		}
	}
}

void LaraBurn()//5ACE4, 5B160 (F)
{
	if (!lara.burn && !lara.BurnSmoke)
	{
		short fx = CreateEffect(lara_item->room_number);
		if (fx != -1)
		{
			effects[fx].object_number = FLAME;
			lara.burn = TRUE;
		}
	}
}

void FlameControl(short fx_number)//5AA6C, 5AEE8 (F)
{
	struct FX_INFO* fx = &effects[fx_number];
	int y;
	int i;
	for(i = NUM_LARA_MESHES; i > 0; i--)
	{
		if (!(wibble & 0xC))
		{
			fx->pos.x_pos = 0;
			fx->pos.y_pos = 0;
			fx->pos.z_pos = 0;

			GetLaraJointPos((struct PHD_VECTOR*)&fx->pos, i - 1);

			if (lara.BurnCount)
			{
				if (!--lara.BurnCount)
					lara.BurnSmoke = TRUE;
			}

			TriggerFireFlame(fx->pos.x_pos, fx->pos.y_pos, fx->pos.z_pos, -1, 255 - lara.BurnSmoke);
		}
	}

	if (!lara.BurnSmoke)
	{
		const int r = (GetRandomControl() & 0x3F) + 192;
		const int g = (GetRandomControl() & 0x1F) + 96;

		if (lara.BurnBlue == 0)
		{
			TriggerDynamic(lara_item->pos.x_pos, lara_item->pos.y_pos, lara_item->pos.z_pos, 13, r, g, 0);
		}
		else if (lara.BurnBlue == 128)
		{
			TriggerDynamic(lara_item->pos.x_pos, lara_item->pos.y_pos, lara_item->pos.z_pos, 13, 0, g, r);
		}
		else if (lara.BurnBlue == 256)
		{
			TriggerDynamic(lara_item->pos.x_pos, lara_item->pos.y_pos, lara_item->pos.z_pos, 13, 0, r, g);
		}
	}

	if (lara_item->room_number != fx->room_number)
		EffectNewRoom(fx_number, lara_item->room_number);

	y = GetWaterHeight(fx->pos.x_pos, fx->pos.y_pos, fx->pos.z_pos, fx->room_number);

	if (y == -32512 || fx->pos.y_pos <= y || lara.BurnBlue != 0)
	{
		SoundEffect(SFX_LOOP_FOR_SMALL_FIRES, &fx->pos, 0);

		lara_item->hit_points -= 7;
		lara_item->hit_status = TRUE;
	}
	else
	{
		KillEffect(fx_number);

		lara.burn = FALSE;
	}
}

void FlameEmitter3Control(short item_number)//5A38C, 5A808
{
	S_Warn("[FlameEmitter3Control] - Unimplemented!\n");
	return;
}

void FlameEmitter2Control(short item_number)//5A1BC, 5A638 (F)
{
	struct ITEM_INFO* item = &items[item_number];

	if (TriggerActive(item))
	{
		if (item->trigger_flags < 0)
		{
			if (item->item_flags[0])
			{
				if (item->item_flags[0] == 1)
				{
					FlipMap(-item->trigger_flags);
					flipmap[-item->trigger_flags] ^= 0x3E00u;
					item->item_flags[0] = 2;
				}
			}
			else
			{
				if (item->trigger_flags < -100)
					item->trigger_flags = item->trigger_flags + 100;

				item->item_flags[0] = 1;
			}
		}
		else
		{
			if (item->trigger_flags != 2)
			{
				if (item->trigger_flags == 123)
					AddFire(item->pos.x_pos, item->pos.y_pos, item->pos.z_pos, 1, item->room_number, item->item_flags[3]);
				else
					AddFire(item->pos.x_pos, item->pos.y_pos, item->pos.z_pos, 1 - item->trigger_flags, item->room_number, item->item_flags[3]);
			}

			if (item->trigger_flags == 0 || item->trigger_flags == 2)
			{
				int r = (GetRandomControl() & 0x3F) + 192;
				int g = (GetRandomControl() & 0x1F) + 96;

				if (item->item_flags[3])
				{
					r = r * item->item_flags[3] >> 8;
					g = g * item->item_flags[3] >> 8;
				}

				TriggerDynamic(item->pos.x_pos, item->pos.y_pos, item->pos.z_pos, 10, r, g, 0);
			}

			SoundEffect(SFX_LOOP_FOR_SMALL_FIRES, &item->pos, 0);
		}
	}
}

void FlameEmitterControl(short item_number)//59D18, 5A194
{
	S_Warn("[FlameEmitterControl] - Unimplemented!\n");
	return;
}

void DartsControl(short item_num)//59AD4, 59F50
{
	S_Warn("[DartsControl] - Unimplemented!\n");
	return;
}

void DartEmitterControl(short item_num)//5988C, 59D08
{
	S_Warn("[DartEmitterControl] - Unimplemented!\n");
	return;
}

void FallingCeiling(short item_number)//59720, 59B9C
{
	S_Warn("[FallingCeiling] - Unimplemented!\n");
	return;
}

void FallingBlockCeiling(struct ITEM_INFO* item, long x, long y, long z, long* height)//596D4, 59B50 (F)
{
	int tx = item->pos.x_pos >> 10;
	int tz = item->pos.z_pos >> 10;

	x >>= 10;
	z >>= 10;

	if (x == tx && z == tz)
	{
		if (item->pos.y_pos < y)
		{
			*height = item->pos.y_pos + 256;
		}
	}
}

void FallingBlockFloor(struct ITEM_INFO* item, long x, long y, long z, long* height)//59674, 59AF0 (F)
{
	int tx = item->pos.x_pos >> 10;
	int tz = item->pos.z_pos >> 10;

	x >>= 10;
	z >>= 10;

	if (x == tx && z == tz)
	{
		if (item->pos.y_pos >= y)
		{
			*height = item->pos.y_pos + 256;
			height_type = WALL;
			OnObject = 1;
		}
	}
}

void FallingBlock(short item_number)//59558, 599D4 (F)
{
	struct ITEM_INFO* item = &items[item_number];

	if (item->trigger_flags)
	{
		item->trigger_flags--;
	}
	else
	{
		if (!item->item_flags[0])
		{
			item->mesh_bits = -2;
			ExplodingDeath2(item_number, -1, 15265);
			item->item_flags[0]++;
		}
		else
		{
			if (item->item_flags[0] >= 60)
			{
				KillItem(item_number);
			}
			else
			{
				if (item->item_flags[0] >= 52)
				{
					item->item_flags[1] += 2;			
					item->pos.y_pos += item->item_flags[1];
				}
				else
				{
					if (!(GetRandomControl() % (0x3E - item->item_flags[0])))
						item->pos.y_pos += (GetRandomControl() & 3) + 1;
				}
				item->item_flags[0]++;
			}
		}
	}
}

void FallingBlockCollision(short item_number, struct ITEM_INFO* l, struct COLL_INFO* coll)//5947C, 598F8
{
	S_Warn("[FallingBlockCollision] - Unimplemented!\n");
	return;
}

void TrapDoorCollision(short item_num, struct ITEM_INFO* l, struct COLL_INFO* coll)//593F8, 59874
{
	S_Warn("[TrapDoorCollision] - Unimplemented!\n");
	return;
}

void CeilingTrapDoorCollision(short item_num, struct ITEM_INFO* l, struct COLL_INFO* coll)//5912C, 595A8
{
	S_Warn("[CeilingTrapDoorCollision] - Unimplemented!\n");
	return;
}

void FloorTrapDoorCollision(short item_num, struct ITEM_INFO* l, struct COLL_INFO* coll)//58E80, 592FC
{
	S_Warn("[FloorTrapDoorCollision] - Unimplemented!\n");
	return;
}

void TrapDoorControl(short item_number)//58D08, 59184
{
	S_Warn("[TrapDoorControl] - Unimplemented!\n");
	return;
}

void CloseTrapDoor(struct ITEM_INFO* item)//58B68, 59008
{
	S_Warn("[CloseTrapDoor] - Unimplemented!\n");

}

void OpenTrapDoor(struct ITEM_INFO* item)//58A1C(<), 58EBC (F)
{
	long x;
	long z;
	struct room_info* r;
	struct FLOOR_INFO* floor;
	unsigned short pitsky;

	r = &room[item->room_number];
	x = room->x;
	z = room->z;

	floor = &r->floor[((item->pos.z_pos - z) >> 10) + (((item->pos.x_pos - x) >> 10) * room->x_size)];
	pitsky = item->item_flags[3];

	if (z == x)
	{
		floor->pit_room = pitsky;
		r = &room[pitsky & 0xFF];
		floor = &r->floor[((item->pos.z_pos - room->z) >> 10) + (((item->pos.x_pos - r->x) >> 10) * r->x_size)];
		floor->sky_room = pitsky >> 8;
	}
	else
	{
		//loc_58AFC
		floor->sky_room = pitsky >> 8;
		r = &room[(pitsky >> 8) & 0xFF];
		floor = &r->floor[((item->pos.z_pos - r->z) >> 10) + (((item->pos.x_pos - r->x) >> 10) * r->x_size)];
		floor->pit_room = pitsky;
	}

	//locret_58B60
	item->item_flags[2] = 0;
	return;
}