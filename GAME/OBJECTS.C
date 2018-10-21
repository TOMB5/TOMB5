#include "OBJECTS.H"

#include "BOX.H"
#include "COLLIDE.H"
#include "CONTROL.H"
#include "DRAW.H"
#include "EFFECTS.H"
#include "ITEMS.H"
#include "LARA.H"

#if PSXENGINE
#include "SETUP.H"
#include "ROOMLOAD.H"
#endif
#include "SOUND.H"
#include "SPECIFIC.H"
#include "SPECTYPES.H"
#include "TOMB4FX.H"

#include <stddef.h>
#include "SWITCH.H"
#include "EFFECT2.H"
#include "DEBRIS.H"
#include "GAMEFLOW.H"

struct BITE_INFO EnemyBites[9] =
{
	{ 0x14, -0x5F, 0xF0, 0xD },
	{ 0x30, 0, 0xB4, -0xB },
	{ -0x30, 0, 0xB4, 0xE },
	{ -0x37, 5, 0xE1, 0xE },
	{ 0xF, -0x3C, 0xC3, 0xD },
	{ -0x1E, -0x41, 0xFA, 0x12 },
	{ 0, -0x6E, 0x1E0, 0xD },
	{ -0x14, -0x50, 0xBE, -0xA },
	{ 0xA, -0x3C, 0xC8, 0xD }
};
static struct PHD_VECTOR PolePos = {0, 0, -208}; // offset 0xA1238
static struct PHD_VECTOR PolePosR = {0, 0, 0}; // offset 0xA1244
static short PoleBounds[12] = // offset 0xA1250
{
	0xFF00, 0x0100, 0x0000, 0x0000, 0xFE00, 0x0200, 0xF8E4, 0x071C, 0xEAAC, 0x1554, 
	0xF8E4, 0x071C
};
int AnimatingWaterfallsVOffset = 0; // offset 0xA1268
static short TightRopeBounds[12] = // offset 0xA126C
{
	0xFF00, 0x0100, 0x0000, 0x0000, 0xFF00, 0x0100, 0xF8E4, 0x071C, 0xEAAC, 0x1554,
	0xF8E4, 0x071C
};
static struct PHD_VECTOR TightRopePos = {0, 0, 0}; // offset 0xA1284
static short ParallelBarsBounds[12] = // offset 0xA1290
{
	0xFD80, 0x0280, 0x02C0, 0x0340, 0xFFA0, 0x0060, 0xF8E4, 0x071C, 0xEAAC, 0x1554, 0xF8E4, 0x071C
};

void HybridCollision(short item_num, struct ITEM_INFO* laraitem, struct COLL_INFO* coll)
{
	UNIMPLEMENTED();
}

void DrawBaddieGunFlash(struct ITEM_INFO* item)
{
	UNIMPLEMENTED();
}

void CutsceneRopeControl(short item_number)
{
	UNIMPLEMENTED();
}

void ControlXRayMachine(short item_number)// (F)
{
	struct ITEM_INFO* item = &items[item_number];

	if (!TriggerActive(item))
		return;

	if (item->trigger_flags == 0)
	{
		if (item->item_flags[0] == 666)
		{
			if (item->item_flags[1] != 0)
			{
				item->item_flags[1]--;
			}
			else
			{
				item->item_flags[1] = 30;
				SoundEffect(SFX_ALARM, &item->pos, 0);
			}
		}

		if (lara.skelebob)
		{
			if (lara.hk_type_carried & WTYPE_PRESENT)
			{
				TestTriggersAtXYZ(item->pos.x_pos, item->pos.y_pos, item->pos.z_pos, item->room_number, 1, 0);
				item->item_flags[0] = 666;
			}
		}

		return;
	}

	switch(item->trigger_flags)
	{
	case 111:
		if (item->item_flags[0] != 0)
		{
			item->item_flags[0]--;

			if (item->item_flags[0] == 0)
			{
				TestTriggersAtXYZ(item->pos.x_pos, item->pos.y_pos, item->pos.z_pos, item->room_number, 1, 0);
				RemoveActiveItem(item_number);
				item->flags |= IFLAG_INVISIBLE;
			}

			return;
		}

		if (lara.Fired)
			item->item_flags[0] = 15;
		break;

	case 222:
		if (item->item_flags[1] >= 144)
		{
			TestTriggersAtXYZ(item->pos.x_pos, item->pos.y_pos, item->pos.z_pos, item->room_number, 1, 0);
			RemoveActiveItem(item_number);
			item->flags |= IFLAG_INVISIBLE;
			return;
		}

		if (item->item_flags[1] < 128)
		{
			SoundEffect(SFX_LOOP_FOR_SMALL_FIRES, &item->pos, 0);
			TriggerFontFire(&items[item->item_flags[0]], item->item_flags[1], item->item_flags[1] == 0 ? 16 : 1);
		}

		++item->item_flags[1];
		break;

	case 333:
	{
		struct room_info* r = &room[item->room_number];
		struct MESH_INFO* mesh = r->mesh;
		int j;

		for (j = 0; j < r->num_meshes; j++, mesh++)
		{
			if (mesh->Flags & 1)
			{
				if (item->pos.x_pos == mesh->x &&
					item->pos.y_pos == mesh->y &&
					item->pos.z_pos == mesh->z)
				{
					ShatterObject(NULL, mesh, 128, item->room_number, 0);
					mesh->Flags &= ~1;
					SoundEffect(ShatterSounds[gfCurrentLevel - 5][mesh->static_number], (struct PHD_3DPOS*)&mesh->x, 0);
				}
			}
		}

		RemoveActiveItem(item_number);
		item->flags |= IFLAG_INVISIBLE;
		break;
	}

	default:
		TestTriggersAtXYZ(item->pos.x_pos, item->pos.y_pos, item->pos.z_pos, item->room_number, 1, 0);
		RemoveActiveItem(item_number);
		break;
	}
}

void ParallelBarsCollision(short item_num, struct ITEM_INFO* l, struct COLL_INFO* coll)
{
	UNIMPLEMENTED();
}

void TightRopeCollision(short item_num, struct ITEM_INFO* l, struct COLL_INFO* coll)
{
	UNIMPLEMENTED();
}

void ControlWaterfall(short item_number)//4FBC4(<), 50028(<) (F)
{
	struct ITEM_INFO* item = &items[item_number];
	TriggerActive(item);

	if (item_number != 0)
	{
		item->status = ITEM_ACTIVE;

		if (item->trigger_flags == 0x29C)
		{
			SoundEffect(SFX_D_METAL_KICKOPEN, &item->pos, 0);
		}
		else if (item->trigger_flags == 0x309)
		{
			SoundEffect(SFX_WATERFALL_LOOP, &item->pos, 0);
		}
	}
	else
	{
		if (item->trigger_flags == 2 || item->trigger_flags == 0x29C)
		{
			item->status = ITEM_INVISIBLE;
		}
	}
}

void AnimateWaterfalls()//4FABC(<), 4FF20(<)
{
#if PSX_VERSION
	struct PSXTEXTI* Twaterfall;
	long i;
	long speed1;
	long speed2;

	speed1 = (GlobalCounter << 3) - GlobalCounter & 0x3F;
	speed2 = -(GlobalCounter << 2) & 0x3F;

	//loc_4FB00
	for (i = 0; i < 6; i++)
	{
		if (objects[WATERFALL1 + i].loaded)
		{
			Twaterfall = AnimatingWaterfalls[i];

			Twaterfall->v0 = ((char*) &AnimatingWaterfallsV[i])[0] + speed1;
			Twaterfall->v1 = ((char*) &AnimatingWaterfallsV[i])[0] + speed1;
			Twaterfall->v2 = ((char*) &AnimatingWaterfallsV[i])[0] + speed1 & 0x3F;
			Twaterfall->v3 = ((char*) &AnimatingWaterfallsV[i])[0] + speed1 & 0x3F;

			if (i < 4)
			{
				Twaterfall++;
				Twaterfall->v0 = ((char*) &AnimatingWaterfallsV[i])[0] + speed1;
				Twaterfall->v1 = ((char*) &AnimatingWaterfallsV[i])[0] + speed1;
				Twaterfall->v2 = ((char*) &AnimatingWaterfallsV[i])[0] + speed1 & 0x3F;
				Twaterfall->v3 = ((char*) &AnimatingWaterfallsV[i])[0] + speed1 & 0x3F;
			}//loc_4FB98
		}//loc_4FB98

		if (i == 4)
		{
			speed1 = speed2;
		}
	}
#else
	UNIMPLEMENTED();
#endif
}

void ControlTriggerTriggerer(short item_number)
{
	UNIMPLEMENTED();
}

void PoleCollision(short item_num, struct ITEM_INFO* l, struct COLL_INFO* coll)
{
	UNIMPLEMENTED();
}

void ControlAnimatingSlots(short item_number)
{
	UNIMPLEMENTED();
}

void BridgeTilt2Ceiling(struct ITEM_INFO* item, long x, long y, long z, long* height)//4F0FC(<), 4F560(<) (F)
{
	long level = item->pos.y_pos + (GetOffset(item, x, z) >> 1);

	if (level >= y)
	{
		*height = level;
	}
}

void BridgeTilt2Floor(struct ITEM_INFO* item, long x, long y, long z, long* height)//4F090(<), 4F4F4(<) (F)
{
	long level = item->pos.y_pos + (GetOffset(item, x, z) >> 1);

	if (level >= y)
	{
		*height = level;
		height_type = WALL;
		OnObject = 1;
	}
}

void BridgeTilt1Ceiling(struct ITEM_INFO* item, long x, long y, long z, long* height)//4F038(<), 4F49C(<) (F)
{
	long level = item->pos.y_pos + (GetOffset(item, x, z) >> 2);

	if (level >= y)
	{
		*height = level;
	}
}

long GetOffset(struct ITEM_INFO* item, long x, long z)// (F)
{
	if (item->pos.y_rot == 0)
	{
		return (-x) & 0x3FF;
	}
	else if (item->pos.y_rot == ANGLE(-180))
	{
		return x & 0x3FF;
	}
	else if (item->pos.y_rot == ANGLE(90))
	{
		return z & 0x3FF;
	}
	else
	{
		return (-z) & 0x3FF;
	}
}

void BridgeTilt1Floor(struct ITEM_INFO* item, long x, long y, long z, long* height)//4EFCC(<), 4F430(<) (F)
{
	long level = item->pos.y_pos + (GetOffset(item, x, z) >> 2);

	if (level >= y)
	{
		*height = level;
		height_type = WALL;
		OnObject = 1;
	}
}

void BridgeFlatCeiling(struct ITEM_INFO* item, long x, long y, long z, long* height)//4EF58(<), 4F3BC(<) (F)
{
	if (item->pos.y_pos >= y)
	{
		*height = item->pos.y_pos + 256;
	}
}

void BridgeFlatFloor(struct ITEM_INFO* item, long x, long y, long z, long* height)//4EF1C(<), 4F380(<) (F)
{
	if (item->pos.y_pos >= y)
	{
		*height = item->pos.y_pos;
		height_type = WALL;
		OnObject = 1;
	}
}

void SmashObjectControl(short item_number)//4EEF8(<), 4F35C(<) (F)
{
	SmashObject(item_number << 16);
}

void SmashObject(short item_number)//4EDB0, 4F214 (F)
{
	struct ITEM_INFO* item = &items[item_number];
	struct room_info* r = &room[item->room_number];
	int sector = ((item->pos.z_pos - r->z) >> 10) + r->x_size * ((item->pos.x_pos - r->x) >> 10);
	struct box_info* box = &boxes[r->floor[sector].box];
	if (box->overlap_index & BOX_LAST)
	{
		box->overlap_index &= ~BOX_BLOCKED;
	}

	SoundEffect(SFX_SMASH_GLASS, &item->pos, 0);
	item->collidable = 0;
	item->mesh_bits = 0xFFFE;
	ExplodingDeath2(item_number, -1, 257);
	item->flags |= IFLAG_INVISIBLE;
	if (item->status == ITEM_ACTIVE)
		RemoveActiveItem(item_number);
	item->status = ITEM_DEACTIVATED;
}

void EarthQuake(short item_number)
{
	UNIMPLEMENTED();
}
