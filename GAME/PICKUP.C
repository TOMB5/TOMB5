#include "PICKUP.H"

#if PSXPC_VERSION || PSX_VERSION
#include "CALCLARA.H"
#endif
#include "COLLIDE.H"
#include "CONTROL.H"
#include "DRAW.H"
#include "EFFECTS.H"
#include "GAMEFLOW.H"
#include "LARA.H"
#include INPUT_H
#include "OBJECTS.H"
#include "SOUND.H"
#include "SPECIFIC.H"
#include "SWITCH.H"
#include "ITEMS.H"
#include "DELTAPAK.H"
#ifdef PC_VERSION
#include "GAME.H"
#else
#include "SETUP.H"
#include "CD.H"
#endif

static short PickUpBounds[12] = // offset 0xA1338
{
	0xFF00, 0x0100, 0xFF38, 0x00C8, 0xFF00, 0x0100, 0xF8E4, 0x071C, 0x0000, 0x0000, 
	0x0000, 0x0000
};
static struct PHD_VECTOR PickUpPosition = { 0, 0, 0xFFFFFF9C }; // offset 0xA1350
static short HiddenPickUpBounds[12] = // offset 0xA135C
{
	0xFF00, 0x0100, 0xFF9C, 0x0064, 0xFCE0, 0xFF00, 0xF8E4, 0x071C, 0xEAAC, 0x1554, 
	0x0000, 0x0000
};
static struct PHD_VECTOR HiddenPickUpPosition = { 0, 0, 0xFFFFFD4E }; // offset 0xA1374
static short CrowbarPickUpBounds[12] = // offset 0xA1380
{
	0xFF00, 0x0100, 0xFF9C, 0x0064, 0x00C8, 0x0200, 0xF8E4, 0x071C, 0xEAAC, 0x1554, 
	0x0000, 0x0000
};
static struct PHD_VECTOR CrowbarPickUpPosition = { 0, 0, 0xD7 }; // offset 0xA1398
static short JobyCrowPickUpBounds[12] = // offset 0xA13A4
{
	0xFE00, 0x0000, 0xFF9C, 0x0064, 0x0000, 0x0200, 0xF8E4, 0x071C, 0xEAAC, 0x1554, 
	0x0000, 0x0000
};
static struct PHD_VECTOR JobyCrowPickUpPosition = { 0xFFFFFF20, 0, 0xF0 }; // offset 0xA13BC
static short PlinthPickUpBounds[12] = // offset 0xA13C8
{
	0xFF00, 0x0100, 0xFD80, 0x0280, 0xFE01, 0x0000, 0xF8E4, 0x071C, 0xEAAC, 0x1554, 
	0x0000, 0x0000
};
static struct PHD_VECTOR PlinthPickUpPosition = { 0, 0, 0xFFFFFE34 }; // offset 0xA13E0
static short PickUpBoundsUW[12] = // offset 0xA13EC
{
	0xFE00, 0x0200, 0xFE00, 0x0200, 0xFE00, 0x0200, 0xE002, 0x1FFE, 0xE002, 0x1FFE, 
	0xE002, 0x1FFE
};
static struct PHD_VECTOR PickUpPositionUW = { 0, 0xFFFFFF38, 0xFFFFFEA2 }; // offset 0xA1404
static short KeyHoleBounds[12] = // offset 0xA1410
{
	0xFF00, 0x0100, 0x0000, 0x0000, 0x0000, 0x019C, 0xF8E4, 0x071C, 0xEAAC, 0x1554, 
	0xF8E4, 0x071C
};
static struct PHD_VECTOR KeyHolePosition = { 0, 0, 0x138 }; // offset 0xA1428
static short PuzzleBounds[12] = // offset 0xA1434
{
	0x0000, 0x0000, 0xFF00, 0x0100, 0x0000, 0x0000, 0xF8E4, 0x071C, 0xEAAC, 0x1554, 
	0xF8E4, 0x071C
};
static short SOBounds[12] = // offset 0xA144C
{
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xF8E4, 0x071C, 0xEAAC, 0x1554, 
	0xF8E4, 0x071C
};
static struct PHD_VECTOR SOPos = { 0, 0, 0 }; // offset 0xA1464
short SearchCollectFrames[4] =
{
	0x00B4, 0x0064, 0x0099, 0x0053
};
short SearchAnims[4] =
{
	0x01D0, 0x01D1, 0x01D2, 0x01D8
};
short SearchOffsets[4] =
{
	0x00A0, 0x0060, 0x00A0, 0x0070
};
static short MSBounds[12] = // offset 0xA1488
{
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xF8E4, 0x071C, 0xEAAC, 0x1554, 
	0xF8E4, 0x071C
};
static struct PHD_VECTOR MSPos = { 0, 0, 0 }; // offset 0xA14A0
unsigned char NumRPickups; // offset 0xA390C
unsigned char RPickups[16];
struct PHD_VECTOR OldPickupPos;

void MonitorScreenCollision(short item_num, struct ITEM_INFO* l, struct COLL_INFO* coll)//53428(<), 5388C(<) (F)
{
	struct ITEM_INFO* item;
	short* bounds;

	item = &items[item_num];
	if (l->anim_number == ANIMATION_LARA_BUTTON_PUSH && l->frame_number == anims[ANIMATION_LARA_BUTTON_PUSH].frame_base + 24)
		TestTriggersAtXYZ(item->pos.x_pos, item->pos.y_pos, item->pos.z_pos, item->room_number, 1, 0);

	if ((!(input & IN_ACTION)
		|| l->current_anim_state != STATE_LARA_STOP
		|| l->anim_number != ANIMATION_LARA_STAY_IDLE
		|| lara.gun_status
		|| item->status != ITEM_INACTIVE)
		&& (!lara.IsMoving || lara.GeneralPtr != (void *)item_num))
	{
		ObjectCollision(item_num, l, coll);
	}
	else
	{
		bounds = GetBoundsAccurate(item);
		MSBounds[0] = bounds[0] - 256;
		MSBounds[1] = bounds[1] + 256;
		MSBounds[4] = bounds[4] - 512;
		MSBounds[5] = bounds[5] + 512;
		MSPos.z = bounds[4] - 256;
		if (TestLaraPosition(MSBounds, item, l))
		{
			if (MoveLaraPosition(&MSPos, item, l))
			{
				l->current_anim_state = STATE_LARA_SWITCH_DOWN;
				l->anim_number = ANIMATION_LARA_BUTTON_PUSH;
				l->frame_number = anims[ANIMATION_LARA_BUTTON_PUSH].frame_base;
				lara.IsMoving = 0;
				lara.head_y_rot = 0;
				lara.head_x_rot = 0;
				lara.torso_y_rot = 0;
				lara.torso_x_rot = 0;
				lara.gun_status = LG_HANDS_BUSY;
				item->flags |= 0x20u;
				item->status = ITEM_ACTIVE;
			}
			else
			{
				lara.GeneralPtr = (void *)item_num;
			}
		}
		else if (lara.IsMoving && lara.GeneralPtr == (void *)item_num)
		{
			lara.IsMoving = 0;
			lara.gun_status = LG_NO_ARMS;
		}
	}
}

void CollectCarriedItems(struct ITEM_INFO* item)//5339C, 53800
{
	struct ITEM_INFO* pickup; // $s0
	short pickup_number; // $s1

#if 0
		//move	$s3, $a0
		pickup_number = item->carried_item;
		int v0 = -1;
		
		if (pickup_number != -1)
		{
			int s2 = -1;
			v0 = pickup_number << 3;

			loc_533CC:
			v0 += pickup_number;
			pickup = &items[0];
			v0 <<= 4;
			s0 += v0;

			//AddDisplayPickup(pickup->object_number);
			//KillItem(pickup->object_number);

			pickup_number = pickup->carried_item;
			sll	$v0, $s1, 3
			bne	$s1, $s2, loc_533CC
			
		}

		item->carried_item = -1;
#endif
}

void SearchObjectCollision(short item_num, struct ITEM_INFO* l, struct COLL_INFO* coll)//53080, 534E4
{
	S_Warn("[SearchObjectCollision] - Unimplemented!\n");
}

void SearchObjectControl(short item_number)//52D54, 531B8
{
	S_Warn("[SearchObjectControl] - Unimplemented!\n");
}

int PickupTrigger(short item_num)//52CC0(<), 53124(<) (F)
{
	struct ITEM_INFO* item = &items[item_num];

	if (item->flags & 0x8000 && item->status != 3 && item->item_flags[3] != 1 && item->trigger_flags & 0x80)
	{
		return 0;
	}

	KillItem(item_num);

	return 1;
}

int KeyTrigger(short item_num)//52C14(<), 53078(<) (F)
{
	struct ITEM_INFO* item = &items[item_num];
	int oldkey;

	if (item->status != 1 && !KeyTriggerActive && lara.gun_status == 1)
	{
		return -1;
	}
	else if (lara.gun_status == 1)
	{
		oldkey = KeyTriggerActive;

		if (!oldkey)
		{
			item->ai_bits & 0x1D;
			item->status = 2;
		}

		KeyTriggerActive = 0;

		return oldkey;
	}

	//locret_52CB8
	return -1;
}

void PuzzleHoleCollision(short item_num, struct ITEM_INFO* l, struct COLL_INFO* coll)//52520, 52984
{
	S_Warn("[PuzzleHoleCollision] - Unimplemented!\n");
}

void PuzzleDoneCollision(short item_num, struct ITEM_INFO* l, struct COLL_INFO* coll)//524C8, 5292C
{
	S_Warn("[PuzzleDoneCollision] - Unimplemented!\n");
}

void KeyHoleCollision(short item_num, struct ITEM_INFO* l, struct COLL_INFO* coll)//52188, 525EC
{
	S_Warn("[KeyHoleCollision] - Unimplemented!\n");
}

void PickUpCollision(short item_num, struct ITEM_INFO* l, struct COLL_INFO* coll)//516C8, 51B2C
{
	S_Warn("[PickUpCollision] - Unimplemented!\n");
}

void RegeneratePickups()//515AC, 51A10
{
	struct ITEM_INFO* item;
	short objnum; // $v1
	short lp; // $v1
	short* ammo; // $v0
}

void AnimatingPickUp(short item_number)//51450(<), 518B4 (F)
{
	struct ITEM_INFO* item;
	short room_number;

	item = &item[item_number];

	if ((item->trigger_flags & 0x3F) == 5)
	{
		item->fallspeed += 6;
		item->pos.y_pos += item->fallspeed;

		room_number = item->room_number;
		GetFloor(item->pos.x_pos, item->pos.y_pos, item->pos.z_pos, &room_number);

		if (item->item_flags[0] < item->pos.y_pos)
		{
			item->pos.y_pos = item->item_flags[0];
			if (item->fallspeed > 64)
			{
				item->fallspeed = -item->fallspeed >> 2;
			}
			else
			{
				//$5150C
				item->trigger_flags &= 0xFFC0;
			}
		}//$5151C
		if (item->room_number != room_number)
		{
			ItemNewRoom(item_number, room_number);
		}//$51598
	}//$51540
	else if ((item->trigger_flags & 0x3F) == 2 || (item->trigger_flags & 0x3F) == 6 ||
		(item->trigger_flags & 0x3F) == 7 || (item->trigger_flags & 0x3F) == 8)
	{
		AnimateItem(item);
	}
	else if ((item->trigger_flags & 0x3F) == 9 || (item->trigger_flags == 0xB))
	{
		//v1 = RelocPtr[45];
		//a1 = v1[0];
		//jalr a1(item_number);
	}
}

short* FindPlinth(struct ITEM_INFO* item)//51200, 51664
{
	S_Warn("[FindPlinth] - Unimplemented!\n");
	return 0;
}

void PuzzleDone(struct ITEM_INFO* item, short item_num)//51004, 51468 (F)
{
	if (item->object_number == PUZZLE_HOLE1 && gfCurrentLevel == LVL5_GALLOWS_TREE)
	{
		IsAtmospherePlaying = 0;
		S_CDPlay(CDA_XA6_SPOOKY03, 0);
		SoundEffect(SFX_HANGMAN_LAUGH_OFFCAM, &item->pos, 0);
	}

	item->object_number += 8; // PUZZLE_HOLEx -> PUZZLE_DONEx

	item->anim_number = objects[item->object_number].anim_index;
	item->frame_number = anims[item->anim_number].frame_base;

	item->required_anim_state = 0;
	item->goal_anim_state = anims[item->anim_number].current_anim_state;
	item->current_anim_state = anims[item->anim_number].current_anim_state;

	AddActiveItem(item_num);

	item->flags |= IFLAG_ACTIVATION_MASK;
	item->status = ITEM_ACTIVE;

	if (item->trigger_flags == 0x3E6 && level_items > 0)
	{
		int i;
		for (i = 0; i < level_items; i++)
		{
			if (items[i].object_number == AIRLOCK_SWITCH
				&& items[i].pos.x_pos == item->pos.x_pos
				&& items[i].pos.z_pos == item->pos.z_pos)
			{
				FlipMap(items[i].speed);
				flipmap[items[i].trigger_flags] ^= IFLAG_ACTIVATION_MASK;
				items[i].status = ITEM_INACTIVE;
				items[i].flags |= 0x20;
			}
		}
	}

	if (item->trigger_flags > 1024)
	{
		cutrot = 0;
		cutseq_num = item->trigger_flags - 1024;
	}
}