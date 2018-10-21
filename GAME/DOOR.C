#include "DOOR.H"

#include "DRAW.H"
#include "COLLIDE.H"
#include "CONTROL.H"
#include "ITEMS.H"
#include "LARA.H"
#include "NEWINV2.H"
#include INPUT_H
#include "PICKUP.H"
#include "SOUND.H"
#include "SPECIFIC.H"
#include "SPECTYPES.H"
#include "SPHERE.H"
#include "SWITCH.H"
#include "OBJECTS.H"

static struct PHD_VECTOR DoubleDoorPos = { 0, 0, 220 };
static struct PHD_VECTOR PullDoorPos = { -201, 0, 322 };
static struct PHD_VECTOR PushDoorPos = { 201, 0, -702 };
static struct PHD_VECTOR KickDoorPos = { 0, 0, -917 };
static struct PHD_VECTOR UnderwaterDoorPos = { -251, -540, -46 };
static struct PHD_VECTOR CrowbarDoorPos = { -412, 0, 256 };

static short PushPullKickDoorBounds[12] =
{
	0xFE80, 0x0180, 0x0000, 0x0000, 0xFC00, 0x0200, 0xF8E4, 0x071C, 0xEAAC, 0x1554, 0xF8E4, 0x071C
};

static short UnderwaterDoorBounds[12] =
{
	0xFF00, 0x0100, 0xFC00, 0x0000, 0xFC00, 0x0000, 0xC720, 0x38E0, 0xC720, 0x38E0, 0xC720, 0x38E0
};

static short CrowbarDoorBounds[12] =
{
	0xFE00, 0x0200, 0xFC00, 0x0000, 0x0000, 0x0200, 0xC720, 0x38E0, 0xC720, 0x38E0, 0xC720, 0x38E0
};

long ClosedDoors[32];
char LiftDoor;

void ProcessClosedDoors()//2BDE8, 2C110
{
	long lp; // $s2
	short room_number; // $s0
	UNIMPLEMENTED();
}

void SequenceDoorControl(short item_number)//2BC28(<), 2BF50(?) (F)
{
	struct ITEM_INFO *item; // $s1
	struct DOOR_DATA *door; // $s0

	item = &items[item_number];
	door = (struct DOOR_DATA*)item->data;

	if (CurrentSequence == 3)
	{
		if (SequenceResults[Sequences[0]][Sequences[1]][Sequences[2]] == item->trigger_flags)
		{
			if (item->current_anim_state == 1)
			{
				item->goal_anim_state = 1;
			}
			else
			{
				//0x2BCDC
				item->goal_anim_state = 0;
			}

			TestTriggersAtXYZ(item->pos.x_pos, item->pos.y_pos, item->pos.z_pos, item->room_number, 0, 0);

		}//0x2BD08

		CurrentSequence = 4;

	}//0x2BD10

	if (item->current_anim_state == item->goal_anim_state)
	{
		if (item->current_anim_state == 1)
		{
			if (door->Opened)
			{
				OpenThatDoor(&door->d1, door);
				OpenThatDoor(&door->d2, door);
				OpenThatDoor(&door->d1flip, door);
				OpenThatDoor(&door->d2flip, door);
				door->Opened = item->current_anim_state;
				door->Opened |= 0x3E00;
			}//0x2BDC8
		}
		else
		{
			//0x2BD78
			if (door->Opened)
			{
				ShutThatDoor(&door->d1, door);
				ShutThatDoor(&door->d2, door);
				ShutThatDoor(&door->d1flip, door);
				ShutThatDoor(&door->d2flip, door);
				door->Opened = 0;
				item->flags &= 0xC1FF;
			}
		}
	}//0x2BDC8

	AnimateItem(item);
}

void UnderwaterDoorCollision(short item_num, struct ITEM_INFO* l, struct COLL_INFO* coll)//2BA38, 2BD60
{
	UNIMPLEMENTED();
}

void DoubleDoorCollision(short item_num, struct ITEM_INFO* l, struct COLL_INFO* coll)//2B854, 2BB7C
{
	UNIMPLEMENTED();
}

void PushPullKickDoorCollision(short item_num, struct ITEM_INFO* l, struct COLL_INFO* coll)//2B5A0, 2B8C8
{
	UNIMPLEMENTED();
}

void PushPullKickDoorControl(short item_number)//2B508(<), 2B830 (F)
{
	struct ITEM_INFO* item; // $s1
	struct DOOR_DATA* door; // $s0

	item = &items[item_number];
	door = (struct DOOR_DATA*)item->data;

	if (!door->Opened)
	{
		OpenThatDoor(&door->d1, door);
		OpenThatDoor(&door->d2, door);
		OpenThatDoor(&door->d1flip, door);
		OpenThatDoor(&door->d2flip, door);
		door->Opened = 1;
	}//0x2B584

	AnimateItem(item);
}

void DoorCollision(short item_num, struct ITEM_INFO* l, struct COLL_INFO* coll)//2B150, 2B478
{
	struct ITEM_INFO* item = &items[item_num];

	if (item->trigger_flags == 2
		&& !(item->status && item->gravity_status)
		&& ((input & IN_ACTION || GLOBAL_inventoryitemchosen == CROWBAR_ITEM)
			&& l->current_anim_state == STATE_LARA_STOP
			&& l->anim_number == ANIMATION_LARA_STAY_IDLE
			&& !l->hit_status
			&& lara.gun_status == LG_NO_ARMS
			|| lara.IsMoving && lara.GeneralPtr == (void *)item_num))
	{
		item->pos.y_rot ^= (short)ANGLE(180);
		if (TestLaraPosition(CrowbarDoorBounds, item, l))
		{
			if (!lara.IsMoving)
			{
				if (GLOBAL_inventoryitemchosen == -1)
				{
					if (have_i_got_object(CROWBAR_ITEM))
					{
						GLOBAL_enterinventory = CROWBAR_ITEM;
						item->pos.y_rot ^= (short)ANGLE(180);
					}
					else
					{
						if (OldPickupPos.x != l->pos.x_pos || OldPickupPos.y != l->pos.y_pos || OldPickupPos.z != l->pos.z_pos)
						{
							OldPickupPos.x = l->pos.x_pos;
							OldPickupPos.y = l->pos.y_pos;
							OldPickupPos.z = l->pos.z_pos;
							SayNo();
						}
						item->pos.y_rot ^= (short)ANGLE(180);
					}
					return;
				}
				if (GLOBAL_inventoryitemchosen != CROWBAR_ITEM)
				{
					item->pos.y_rot ^= (short)ANGLE(180);
					return;
				}
			}
			GLOBAL_inventoryitemchosen = -1;
			if (MoveLaraPosition(&CrowbarDoorPos, item, l))
			{
				l->anim_number = 403;
				l->current_anim_state = STATE_LARA_MISC_CONTROL;
				l->frame_number = anims[403].frame_base;
				item->pos.y_rot ^= (short)ANGLE(180);
				AddActiveItem(item_num);
				item->flags |= IFLAG_ACTIVATION_MASK;
				item->status = ITEM_ACTIVE;
				item->goal_anim_state = 1;
				lara.IsMoving = 0;
				lara.gun_status = LG_HANDS_BUSY;
				return;
			}
			lara.GeneralPtr = (void *)item_num;
		}
		else if (lara.IsMoving && lara.GeneralPtr == (void *)item_num)
		{
			lara.IsMoving = 0;
			lara.gun_status = LG_NO_ARMS;
		}
		item->pos.y_rot ^= (short)ANGLE(180);
	}

	if (TestBoundsCollide(item, l, coll->radius))
	{
		if (TestCollision(item, l))
		{
			if (coll->enable_baddie_push)
			{
				if (!(item->object_number >= LIFT_DOORS1 && item->object_number <= LIFT_DOORS2) || item->item_flags[0])
				{
					ItemPushLara(item, l, coll, 0, 1);
				}
			}
		}
	}
}

void DoorControl(short item_number)//2AD74, 2B09C
{
	UNIMPLEMENTED();
}

void OpenThatDoor(struct DOORPOS_DATA* d, struct DOOR_DATA* dd)//2AB8C, 2AEB4
{
	UNIMPLEMENTED();
}

void ShutThatDoor(struct DOORPOS_DATA* d, struct DOOR_DATA* dd)//2AA88, 2ADB0
{
	UNIMPLEMENTED();
}