#include "TRAPS.H"

#include "CONTROL.H"
#include "EFFECTS.H"
#include "ITEMS.H"
#include "LARA.H"
#include "OBJECTS.H"
#include "SPECIFIC.H"
#include "TOMB4FX.H"

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

static struct PHD_VECTOR FloorTrapDoorPos = { 0, 0, 0xFFFFFD71 }; // offset 0xA16B8
static short FloorTrapDoorBounds[12] = // offset 0xA16C4
{
	0xFF00, 0x0100, 0x0000, 0x0000, 0xFC00, 0xFF00, 0xF8E4, 0x071C, 0xEAAC, 0x1554, 
	0xF8E4, 0x071C
};
static struct PHD_VECTOR CeilingTrapDoorPos = { 0, 0x420, 0xFFFFFE20 }; // offset 0xA16DC
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

int OnTwoBlockPlatform(struct ITEM_INFO* item, long x, long z)//5BB80, 5BFFC
{
	S_Warn("[OnTwoBlockPlatform] - Unimplemented!\n");
	return 0;
}

void TwoBlockPlatformCeiling(struct ITEM_INFO* item, long x, long y, long z, long* height)//5BB08, 5BF84
{
	S_Warn("[TwoBlockPlatformCeiling] - Unimplemented!\n");
	return;
}

void TwoBlockPlatformFloor(struct ITEM_INFO* item, long x, long y, long z, long* height)//5BA80, 5BEFC
{
	S_Warn("[TwoBlockPlatformFloor] - Unimplemented!\n");
	return;
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

void LavaBurn(struct ITEM_INFO* item)//5AD78, 5B1F4
{
	if (item->hit_points >= 0 && lara.water_status != 3)
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

void LaraBurn()//5ACE4, 5B160
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

void FlameControl(short fx_number)//5AA6C, 5AEE8
{
	S_Warn("[FlameControl] - Unimplemented!\n");
	return;
}

void FlameEmitter3Control(short item_number)//5A38C, 5A808
{
	S_Warn("[FlameEmitter3Control] - Unimplemented!\n");
	return;
}

void FlameEmitter2Control(short item_number)//5A1BC, 5A638
{
	S_Warn("[FlameEmitter2Control] - Unimplemented!\n");
	return;
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

void FallingBlockCeiling(struct ITEM_INFO* item, long x, long y, long z, long* height)//596D4, 59B50
{
	S_Warn("[FallingBlockCeiling] - Unimplemented!\n");
	return;
}

void FallingBlockFloor(struct ITEM_INFO* item, long x, long y, long z, long* height)//59674, 59AF0
{
	S_Warn("[FallingBlockFloor] - Unimplemented!\n");
	return;
}

void FallingBlock(short item_number)//59558, 599D4
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

void OpenTrapDoor(struct ITEM_INFO* item)//58A1C, 58EBC
{
	S_Warn("[OpenTrapDoor] - Unimplemented!\n");
	return;
}