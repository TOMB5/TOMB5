#include "DOOR.H"

#include "SPECTYPES.H"
#include "SPECIFIC.H"
#include "CONTROL.H"
#include "LARA.H"
#include "NEWINV2.H"
#include "../SPEC_PSX/PSXINPUT.H"
#include "COLLIDE.H"
#include "PICKUP.H"
#include "SOUND.H"
#include "DRAW.H"
#include "ITEMS.H"
#include "SPHERE.H"
#include "OBJECTS.H"

static PHD_VECTOR DoubleDoorPos = { 0, 0, 0xDC };
static PHD_VECTOR PullDoorPos = { 0xFFFFFF37, 0, 0x142 };
static PHD_VECTOR PushDoorPos = { 0xC9, 0, 0xFFFFFD42 };
static PHD_VECTOR KickDoorPos = { 0, 0, 0xFFFFFC6B };
static PHD_VECTOR UnderwaterDoorPos = { 0xFFFFFF05, 0xFFFFFDE4, 0xFFFFFFD2 };
static PHD_VECTOR CrowbarDoorPos = { 0xFFFFFE64, 0, 0x100 };

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
	S_Warn("[ProcessClosedDoors] - Unimplemented!\n");
}

void SequenceDoorControl(short item_number)//2BC28, 2BF50
{
	S_Warn("[SequenceDoorControl] - Unimplemented!\n");
}

void UnderwaterDoorCollision(short item_num, ITEM_INFO* l, COLL_INFO* coll)//2BA38, 2BD60
{
	S_Warn("[UnderwaterDoorCollision] - Unimplemented!\n");
}

void DoubleDoorCollision(short item_num, ITEM_INFO* l, COLL_INFO* coll)//2B854, 2BB7C
{
	S_Warn("[DoubleDoorCollision] - Unimplemented!\n");
}

void PushPullKickDoorCollision(short item_num, ITEM_INFO* l, COLL_INFO* coll)//2B5A0, 2B8C8
{
	S_Warn("[PushPullKickDoorCollision] - Unimplemented!\n");
}

void PushPullKickDoorControl(short item_number)//2B508, 2B830
{
	S_Warn("[PushPullKickDoorControl] - Unimplemented!\n");
}

void DoorCollision(short item_num, ITEM_INFO* l, COLL_INFO* coll)//2B150, 2B478
{
	ITEM_INFO* item = &items[item_num];

	if (item->trigger_flags == 2
		&& !(item->status && item->gravity_status)
		&& ((input & IN_ACTION || GLOBAL_inventoryitemchosen == CROWBAR_ITEM)
			&& l->current_anim_state == STATE_LARA_STOP
			&& l->anim_number == ANIMATION_LARA_STAY_IDLE
			&& !l->hit_status
			&& !lara.gun_status
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
				item->status = 1;
				item->goal_anim_state = 1;
				lara.IsMoving = 0;
				lara.gun_status = 1;
				return;
			}
			lara.GeneralPtr = (void *)item_num;
		}
		else if (lara.IsMoving && lara.GeneralPtr == (void *)item_num)
		{
			lara.IsMoving = 0;
			lara.gun_status = 0;
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
	S_Warn("[DoorCollision] - Unimplemented!\n");
}

void DoorControl(short item_number)//2AD74, 2B09C
{
	S_Warn("[DoorControl] - Unimplemented!\n");
}

void OpenThatDoor(DOORPOS_DATA* d, DOOR_DATA* dd)//2AB8C, 2AEB4
{
	S_Warn("[OpenThatDoor] - Unimplemented!\n");
}

void ShutThatDoor(DOORPOS_DATA* d, DOOR_DATA* dd)//2AA88, 2ADB0
{
	S_Warn("[ShutThatDoor] - Unimplemented!\n");
}