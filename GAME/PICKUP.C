#include "PICKUP.H"

#include "COLLIDE.H"
#include "CONTROL.H"
#include "DRAW.H"
#include "LARA.H"
#include INPUT_H
#include "SPECIFIC.H"
#include "SWITCH.H"

static short PickUpBounds[12] = // offset 0xA1338
{
	0xFF00, 0x0100, 0xFF38, 0x00C8, 0xFF00, 0x0100, 0xF8E4, 0x071C, 0x0000, 0x0000, 
	0x0000, 0x0000
};
static PHD_VECTOR PickUpPosition = { 0, 0, 0xFFFFFF9C }; // offset 0xA1350
static short HiddenPickUpBounds[12] = // offset 0xA135C
{
	0xFF00, 0x0100, 0xFF9C, 0x0064, 0xFCE0, 0xFF00, 0xF8E4, 0x071C, 0xEAAC, 0x1554, 
	0x0000, 0x0000
};
static PHD_VECTOR HiddenPickUpPosition = { 0, 0, 0xFFFFFD4E }; // offset 0xA1374
static short CrowbarPickUpBounds[12] = // offset 0xA1380
{
	0xFF00, 0x0100, 0xFF9C, 0x0064, 0x00C8, 0x0200, 0xF8E4, 0x071C, 0xEAAC, 0x1554, 
	0x0000, 0x0000
};
static PHD_VECTOR CrowbarPickUpPosition = { 0, 0, 0xD7 }; // offset 0xA1398
static short JobyCrowPickUpBounds[12] = // offset 0xA13A4
{
	0xFE00, 0x0000, 0xFF9C, 0x0064, 0x0000, 0x0200, 0xF8E4, 0x071C, 0xEAAC, 0x1554, 
	0x0000, 0x0000
};
static PHD_VECTOR JobyCrowPickUpPosition = { 0xFFFFFF20, 0, 0xF0 }; // offset 0xA13BC
static short PlinthPickUpBounds[12] = // offset 0xA13C8
{
	0xFF00, 0x0100, 0xFD80, 0x0280, 0xFE01, 0x0000, 0xF8E4, 0x071C, 0xEAAC, 0x1554, 
	0x0000, 0x0000
};
static PHD_VECTOR PlinthPickUpPosition = { 0, 0, 0xFFFFFE34 }; // offset 0xA13E0
static short PickUpBoundsUW[12] = // offset 0xA13EC
{
	0xFE00, 0x0200, 0xFE00, 0x0200, 0xFE00, 0x0200, 0xE002, 0x1FFE, 0xE002, 0x1FFE, 
	0xE002, 0x1FFE
};
static PHD_VECTOR PickUpPositionUW = { 0, 0xFFFFFF38, 0xFFFFFEA2 }; // offset 0xA1404
static short KeyHoleBounds[12] = // offset 0xA1410
{
	0xFF00, 0x0100, 0x0000, 0x0000, 0x0000, 0x019C, 0xF8E4, 0x071C, 0xEAAC, 0x1554, 
	0xF8E4, 0x071C
};
static PHD_VECTOR KeyHolePosition = { 0, 0, 0x138 }; // offset 0xA1428
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
static PHD_VECTOR SOPos = { 0, 0, 0 }; // offset 0xA1464
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
static PHD_VECTOR MSPos = { 0, 0, 0 }; // offset 0xA14A0
unsigned char NumRPickups; // offset 0xA390C
unsigned char RPickups[16];
PHD_VECTOR OldPickupPos;

void MonitorScreenCollision(short item_num, ITEM_INFO* l, COLL_INFO* coll)//53428(<), 5388C(<) (F)
{
	ITEM_INFO* item;
	short* bounds;

	item = &items[item_num];
	if (l->anim_number == 197 && l->frame_number == anims[197].frame_base + 24)
		TestTriggersAtXYZ(item->pos.x_pos, item->pos.y_pos, item->pos.z_pos, item->room_number, 1, 0);

	if ((!(input & 0x40)
		|| l->current_anim_state != 2
		|| l->anim_number != 103
		|| lara.gun_status
		|| item->status != 0)
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
				l->current_anim_state = 40;
				l->anim_number = 197;
				l->frame_number = anims[197].frame_base;
				lara.IsMoving = 0;
				lara.head_y_rot = 0;
				lara.head_x_rot = 0;
				lara.torso_y_rot = 0;
				lara.torso_x_rot = 0;
				lara.gun_status = 1;
				item->flags |= 0x20u;
				item->status = 1;
			}
			else
			{
				lara.GeneralPtr = (void *)item_num;
			}
		}
		else if (lara.IsMoving && lara.GeneralPtr == (void *)item_num)
		{
			lara.IsMoving = 0;
			lara.gun_status = 0;
		}
	}
}

void CollectCarriedItems(ITEM_INFO* item)//5339C, 53800
{
	ITEM_INFO* pickup; // $s0
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

void SearchObjectCollision(short item_num, ITEM_INFO* l, COLL_INFO* coll)//53080, 534E4
{
	S_Warn("[SearchObjectCollision] - Unimplemented!\n");
}

void SearchObjectControl(short item_number)//52D54, 531B8
{
	S_Warn("[SearchObjectControl] - Unimplemented!\n");
}

int PickupTrigger(short item_num)//52CC0, 53124
{
	S_Warn("[PickupTrigger] - Unimplemented!\n");
	return 0;
}

int KeyTrigger(short item_num)//52C14, 53078
{
	S_Warn("[KeyTrigger] - Unimplemented!\n");
	return 0;
}

void PuzzleHoleCollision(short item_num, ITEM_INFO* l, COLL_INFO* coll)//52520, 52984
{
	S_Warn("[PuzzleHoleCollision] - Unimplemented!\n");
}

void PuzzleDoneCollision(short item_num, ITEM_INFO* l, COLL_INFO* coll)//524C8, 5292C
{
	S_Warn("[PuzzleDoneCollision] - Unimplemented!\n");
}

void KeyHoleCollision(short item_num, ITEM_INFO* l, COLL_INFO* coll)//52188, 525EC
{
	S_Warn("[KeyHoleCollision] - Unimplemented!\n");
}

void PickUpCollision(short item_num, ITEM_INFO* l, COLL_INFO* coll)//516C8, 51B2C
{
	S_Warn("[PickUpCollision] - Unimplemented!\n");
}

void RegeneratePickups()//515AC, 51A10
{
	ITEM_INFO* item;
	short objnum; // $v1
	short lp; // $v1
	short* ammo; // $v0
}

void AnimatingPickUp(short item_number)//51450, 518B4
{
	S_Warn("[AnimatingPickUp] - Unimplemented!\n");
}

short* FindPlinth(ITEM_INFO* item)//51200, 51664
{
	S_Warn("[FindPlinth] - Unimplemented!\n");
	return 0;
}

void PuzzleDone(ITEM_INFO* item, short item_num)//51004, 51468
{
	S_Warn("[PuzzleDone] - Unimplemented!\n");
}