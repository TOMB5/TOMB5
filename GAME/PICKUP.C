#include "PICKUP.H"
#include "SPECIFIC.H"

struct PHD_VECTOR OldPickupPos;
unsigned char RPickups[16];
unsigned char NumRPickups;
short SearchOffsets[4] =
{
	0x00A0, 0x6000, 0x0060, 0xA000
};
short SearchAnims[4] =
{
	0x01D0, 0xD101, 0x01D1, 0xD201
};
short SearchCollectFrames[4] =
{
	0x00B4, 0x6400, 0x0064, 0x9900
};

void MonitorScreenCollision(short item_num, struct ITEM_INFO *l, struct COLL_INFO *coll)//53428, 5388C
{
	S_Warn("[MonitorScreenCollision] - Unimplemented!\n");
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

void SearchObjectCollision(short item_num, struct ITEM_INFO *l, struct COLL_INFO *coll)//53080, 534E4
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

void PuzzleHoleCollision(short item_num, struct ITEM_INFO *l, struct COLL_INFO *coll)//52520, 52984
{
	S_Warn("[PuzzleHoleCollision] - Unimplemented!\n");
}

void PuzzleDoneCollision(short item_num, struct ITEM_INFO *l, struct COLL_INFO *coll)//524C8, 5292C
{
	S_Warn("[PuzzleDoneCollision] - Unimplemented!\n");
}

void KeyHoleCollision(short item_num, struct ITEM_INFO *l, struct COLL_INFO *coll)//52188, 525EC
{
	S_Warn("[KeyHoleCollision] - Unimplemented!\n");
}

void PickUpCollision(short item_num, struct ITEM_INFO *l, struct COLL_INFO *coll)//516C8, 51B2C
{
	S_Warn("[PickUpCollision] - Unimplemented!\n");
}


void RegeneratePickups()//515AC, 51A10
{
	struct ITEM_INFO* item;
	short objnum; // $v1
	short lp; // $v1
	short *ammo; // $v0
}

void AnimatingPickUp(short item_number)//51450, 518B4
{
	S_Warn("[AnimatingPickUp] - Unimplemented!\n");
}

short *FindPlinth(struct ITEM_INFO *item)//51200, 51664
{
	S_Warn("[FindPlinth] - Unimplemented!\n");
	return 0;
}

void PuzzleDone(struct ITEM_INFO *item, short item_num)//51004, 51468
{
	S_Warn("[PuzzleDone] - Unimplemented!\n");
}

