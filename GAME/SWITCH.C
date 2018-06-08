#include "SWITCH.H"

#include "CONTROL.H"
#include "EFFECTS.H"
#include "GAMEFLOW.H"
#include INPUT_H
#include "SOUND.H"
#include "SPECIFIC.H"
#include "LARA.H"
#include "COLLIDE.H"
#include "DRAW.H"
#include "CAMERA.H"
#include "ITEMS.H"

#ifdef PC_VERSION
#include "GAME.H"
#else
#include "SETUP.H"
#endif

unsigned char SequenceUsed[6];
unsigned char SequenceResults[3][3][3];
unsigned char Sequences[3];
unsigned char CurrentSequence;

static short Switch2Bounds[12] = // offset 0xA14B4
{
	0xFC00, 0x0400, 0xFC00, 0x0400, 0xFC00, 0x0200, 0xC720, 0x38E0, 0xC720, 0x38E0,
	0xC720, 0x38E0
};
static struct PHD_VECTOR Switch2Position = { 0, 0, 108 }; // offset 0xA14CC
static short TurnSwitchBoundsA[12] = // offset 0xA14D8
{
	0x0200, 0x0380, 0x0000, 0x0000, 0xFE00, 0x0000, 0xF8E4, 0x071C, 0xEAAC, 0x1554, 
	0xF8E4, 0x071C
};
static struct PHD_VECTOR TurnSwitchPos = { 650, 0, 138 }; // offset 0xA14F0
static short TurnSwitchBoundsC[12] = // offset 0xA14FC
{
	0x0200, 0x0380, 0x0000, 0x0000, 0x0000, 0x0200, 0xF8E4, 0x071C, 0xEAAC, 0x1554, 
	0xF8E4, 0x071C
};
static struct PHD_VECTOR TurnSwitchPosA = { 650, 0, -138 }; // offset 0xA1514
static struct PHD_VECTOR CogSwitchPos = { 0, 0, -856 }; // offset 0xA1520
static short CogSwitchBounds[12] = // offset 0xA152C
{
	0xFE00, 0x0200, 0x0000, 0x0000, 0xFA00, 0xFE00, 0xF8E4, 0x071C, 0xEAAC, 0x1554, 
	0xF8E4, 0x071C
};
static struct PHD_VECTOR RailSwitchPos = { 0, 0, -550 }; // offset 0xA1544
static short RailSwitchBounds[12] = // offset 0xA1550
{
	0xFF00, 0x0100, 0x0000, 0x0000, 0xFD00, 0xFE00, 0xF8E4, 0x071C, 0xEAAC, 0x1554, 
	0xF8E4, 0x071C
};
static struct PHD_VECTOR RailSwitchPos2 = { 0, 0, 550 }; // offset 0xA1568
static short RailSwitchBounds2[12] = // offset 0xA1574
{
	0xFF00, 0x0100, 0x0000, 0x0000, 0x0200, 0x0300, 0xF8E4, 0x071C, 0xEAAC, 0x1554, 
	0xF8E4, 0x071C
};
static short JumpSwitchBounds[12] = // offset 0xA158C
{
	0xFF80, 0x0080, 0xFF00, 0x0100, 0x0180, 0x0200, 0xF8E4, 0x071C, 0xEAAC, 0x1554,
	0xF8E4, 0x071C
};
static struct PHD_VECTOR JumpSwitchPos = { 0, -208, 256 }; // offset 0xA15A4
static struct PHD_VECTOR CrowbarPos = { -89, 0, -328 }; // offset 0xA15B0
static short CrowbarBounds[12] = // offset 0xA15BC
{
	0xFF00, 0x0100, 0x0000, 0x0000, 0xFE00, 0xFF00, 0xF8E4, 0x071C, 0xEAAC, 0x1554, 
	0xF8E4, 0x071C
};
static struct PHD_VECTOR CrowbarPos2 = { 89, 0, 328 }; // offset 0xA15D4
static short CrowbarBounds2[12] = // offset 0xA15E0
{
	0xFF00, 0x0100, 0x0000, 0x0000, 0x0100, 0x0200, 0xF8E4, 0x071C, 0xEAAC, 0x1554, 
	0xF8E4, 0x071C
};
static short FullBlockSwitchBounds[12] = // offset 0xA15F8
{
	0xFE80, 0x0180, 0x0000, 0x0100, 0x0000, 0x0200, 0xF8E4, 0x071C, 0xEAAC, 0x1554,
	0xF8E4, 0x071C
};
static struct PHD_VECTOR FullBlockSwitchPos = { 0, 0, 0 }; // offset 0xA1610
static short PulleyBounds[12] = // offset 0xA161C
{
	0xFF00, 0x0100, 0x0000, 0x0000, 0xFE00, 0x0200, 0xF8E4, 0x071C, 0xEAAC, 0x1554, 
	0xF8E4, 0x071C
};
static struct PHD_VECTOR PulleyPos = { 0, 0, -148 }; // offset 0xA1634
static struct PHD_VECTOR CrowDovePos = { 0, 0, -400 }; // offset 0xA1640
static short UnderwaterSwitchBounds[12] = // offset 0xA164C
{
	0xFF00, 0x0100, 0xFB00, 0xFE00, 0xFE00, 0x0000, 0xC720, 0x38E0, 0xC720, 0x38E0, 
	0xC720, 0x38E0
};
static short UnderwaterSwitchBounds2[12] = // offset 0xA1664
{
	0xFF00, 0x0100, 0xFB00, 0xFE00, 0x0000, 0x0200, 0xC720, 0x38E0, 0xC720, 0x38E0,
	0xC720, 0x38E0
};
static struct PHD_VECTOR UnderwaterSwitchPos = { 0, -736, -416 }; // offset 0xA167C
static struct PHD_VECTOR UnderwaterSwitchPos2 = { 0, -736, 416 }; // offset 0xA1688
static short SwitchBounds[12] = // offset 0xA1694
{
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xF8E4, 0x071C, 0xEAAC, 0x1554, 
	0xF8E4, 0x071C
};
static struct PHD_VECTOR SwitchPos = { 0, 0, 0 }; // offset 0xA16AC

void ProcessExplodingSwitchType8(struct ITEM_INFO* item)//58958, 58DF8 (F)
{
	struct PHD_VECTOR pos;
	pos.x = 0;
	pos.y = 0;
	pos.z = 0;
	GetJointAbsPosition(item, &pos, 0);
	TestTriggersAtXYZ(pos.x, pos.y, pos.z, item->room_number, 1, 0);
	ExplodeItemNode(item, objects[item->object_number].nmeshes - 1, 0, 64);
	item->mesh_bits |= 1 << ((objects[item->object_number].nmeshes & 0xFF) - 2);
}

void CrowDoveSwitchCollision(short item_num, struct ITEM_INFO* l, struct COLL_INFO* coll)//58740, 58BE0
{
	S_Warn("[CrowDoveSwitchCollision] - Unimplemented!\n");
	return;
}

void CrowDoveSwitchControl(short item_number)//58674(<), 58B14 (F)
{
	struct ITEM_INFO* item = &items[item_number];

	if ((item->mesh_bits & 2))
	{
		ExplodeItemNode(item, 1, 0, 0x100);
		SoundEffect(SFX_RAVENSWITCH_EXP, &item->pos, 0);
		item->mesh_bits = 5;
		RemoveActiveItem(item_number);
	}
	else
	{
		//0x586F0
		if (item->current_anim_state == 0)
		{
			item->goal_anim_state = 1;
		}

		//0x58704
		AnimateItem(item);

		if (item->current_anim_state == 0)
		{
			item->pos.y_rot += 16384;
		}
	}
}

void CogSwitchCollision(short item_num, struct ITEM_INFO* l, struct COLL_INFO* coll)//58354, 587F4
{
	S_Warn("[CogSwitchCollision] - Unimplemented!\n");
	return;
}

void CogSwitchControl(short item_num)//581D8, 58678
{
	S_Warn("[CogSwitchControl] - Unimplemented!\n");
	return;
}

void FullBlockSwitchCollision(short item_num, struct ITEM_INFO* l, struct COLL_INFO* coll)//57FB8, 58458
{
	S_Warn("[FullBlockSwitchCollision] - Unimplemented!\n");
	return;
}

void FullBlockSwitchControl(short item_number)//57EB8, 58358
{
	S_Warn("[FullBlockSwitchControl] - Unimplemented!\n");
	return;
}

void CrowbarSwitchCollision(short item_num, struct ITEM_INFO* l, struct COLL_INFO* coll)//57ACC, 57F6C
{
	S_Warn("[CrowbarSwitchCollision] - Unimplemented!\n");
	return;
}

void JumpSwitchCollision(short item_num, struct ITEM_INFO* l, struct COLL_INFO* coll)//57980, 57E20
{
	S_Warn("[JumpSwitchCollision] - Unimplemented!\n");
	return;
}

void RailSwitchCollision(short item_num, struct ITEM_INFO* l, struct COLL_INFO* coll)//576F4, 57B94
{
	S_Warn("[RailSwitchCollision] - Unimplemented!\n");
	return;
}

void TurnSwitchCollision(short item_num, struct ITEM_INFO* l, struct COLL_INFO* coll)//57210, 576B0 (F)
{
	struct ITEM_INFO* item = &items[item_num];
	int flag = 0;
	if (item->current_anim_state
		&& input & IN_ACTION
		&& l->current_anim_state == STATE_LARA_STOP
		&& l->anim_number == ANIMATION_LARA_STAY_IDLE
		&& !l->gravity_status
		&& lara.gun_status == LG_NO_ARMS
		|| lara.IsMoving && lara.GeneralPtr == (void*)item_num)
	{
		short ItemNos[8];
		if(TestLaraPosition(TurnSwitchBoundsA, item, l))
		{
			if(MoveLaraPosition(&TurnSwitchPosA, item, l))
			{		
				l->anim_number = ANIMATION_LARA_ROUND_HANDLE_GRAB_COUNTERCLOCKWISE;
				l->frame_number = anims[ANIMATION_LARA_ROUND_HANDLE_GRAB_COUNTERCLOCKWISE].frame_base;
				item->anim_number = objects[item->object_number].anim_index + 4;
				item->frame_number = anims[item->anim_number].frame_base;
				item->item_flags[0] = 1;
				ForcedFixedCamera.x = item->pos.x_pos - (1024 * SIN(item->pos.y_rot) >> W2V_SHIFT);
				ForcedFixedCamera.z = item->pos.z_pos - (1024 * COS(item->pos.y_rot) >> W2V_SHIFT);
				lara.IsMoving = 0;
				lara.head_y_rot = 0;
				lara.head_x_rot = 0;
				lara.torso_y_rot = 0;
				lara.torso_x_rot = 0;
				lara.gun_status = LG_HANDS_BUSY;
				l->current_anim_state = ANIMATION_LARA_TRY_HANG_SOLID;
				UseForcedFixedCamera = TRUE;
				ForcedFixedCamera.y = item->pos.y_pos - 2048;
				ForcedFixedCamera.room_number = item->room_number;
				AddActiveItem(item_num);
				item->status = ITEM_ACTIVE;
				item->item_flags[1] = 0;
				if(GetSwitchTrigger(item, ItemNos, 0))
				{
					if(!TriggerActive(&items[ItemNos[0]]))
					{
						items[ItemNos[0]].anim_number = objects[items[ItemNos[0]].object_number].anim_index;
						items[ItemNos[0]].frame_number = anims[items[ItemNos[0]].anim_number].frame_base;
					}
				}
				return;
			}
			lara.GeneralPtr = (void *)item_num;
		}
		else
		{
			l->pos.y_rot ^= (int)ANGLE(180);
			if (TestLaraPosition(TurnSwitchBoundsC, item, l))
			{
				if (MoveLaraPosition(&TurnSwitchPos, item, l))
				{
					l->anim_number = 319;
					flag = 1;
					l->frame_number = anims[319].frame_base;
					item->item_flags[0] = 2;
					ForcedFixedCamera.x = item->pos.x_pos + (1024 * SIN(item->pos.y_rot) >> W2V_SHIFT);
					ForcedFixedCamera.z = item->pos.z_pos + (1024 * COS(item->pos.y_rot) >> W2V_SHIFT);
				}
				else
				{
					lara.GeneralPtr = (void *)item_num;
				}
			}
			else if (lara.IsMoving && lara.GeneralPtr == (void *)item_num)
			{
				lara.IsMoving = FALSE;
				lara.gun_status = LG_NO_ARMS;
			}
			l->pos.y_rot ^= 0x8000u;
			if (flag)
			{
				lara.IsMoving = 0;
				lara.head_y_rot = 0;
				lara.head_x_rot = 0;
				lara.torso_y_rot = 0;
				lara.torso_x_rot = 0;
				lara.gun_status = LG_HANDS_BUSY;
				l->current_anim_state = ANIMATION_LARA_TRY_HANG_SOLID;
				UseForcedFixedCamera = TRUE;
				ForcedFixedCamera.y = item->pos.y_pos - 2048;
				ForcedFixedCamera.room_number = item->room_number;
				AddActiveItem(item_num);
				item->status = ITEM_ACTIVE;
				item->item_flags[1] = 0;
				if (GetSwitchTrigger(item, ItemNos, 0))
				{
					if (!TriggerActive(&items[ItemNos[0]]))
					{
						items[ItemNos[0]].anim_number = objects[items[ItemNos[0]].object_number].anim_index + 4;
						items[ItemNos[0]].frame_number = anims[items[ItemNos[0]].anim_number].frame_base;
					}
				}
				return;
			}
		}
	}

	if (coll->enable_baddie_push && TestBoundsCollide(item, l, coll->radius))
	{
		GlobalCollisionBounds[0] = -512;
		GlobalCollisionBounds[1] = 512;
		GlobalCollisionBounds[2] = -512;
		GlobalCollisionBounds[3] = 0;
		GlobalCollisionBounds[4] = -512;
		GlobalCollisionBounds[5] = 512;
		ItemPushLara(item, l, coll, 0, 2);
		GlobalCollisionBounds[0] = 256;
		GlobalCollisionBounds[1] = 1024;
		GlobalCollisionBounds[4] = -128;
		GlobalCollisionBounds[5] = 128;
		ItemPushLara(item, l, coll, 0, 2);
	}
}

void TurnSwitchControl(short item_num)//56E9C, 5733C
{
	S_Warn("[TurnSwitchControl] - Unimplemented!\n");
	return;
}

void PulleyCollision(short item_num, struct ITEM_INFO* l, struct COLL_INFO* coll)//56C98, 57138
{
	S_Warn("[PulleyCollision] - Unimplemented!\n");
	return;
}

void UnderwaterSwitchCollision(short item_num, struct ITEM_INFO* l, struct COLL_INFO* coll)//56A2C, 56ECC
{
	S_Warn("[UnderwaterSwitchCollision] - Unimplemented!\n");
	return;
}

void SwitchCollision2(short item_num, struct ITEM_INFO* l, struct COLL_INFO* coll)//568C0, 56D60
{
	S_Warn("[SwitchCollision2] - Unimplemented!\n");
	return;
}

void SwitchCollision(short item_num, struct ITEM_INFO* l, struct COLL_INFO* coll)//56470, 56910
{
	S_Warn("[SwitchCollision] - Unimplemented!\n");
	return;
}

void SwitchControl(short item_number)//5623C, 566DC
{
	S_Warn("[SwitchControl] - Unimplemented!\n");
	return;
}

void TestTriggersAtXYZ(long x, long y, long z, short room_number, int heavy, int flags)//561A8(<), 56648(<) (F)
{
	GetHeight(GetFloor(x, y, z, &room_number), x, y, z);
	TestTriggers(trigger_index, heavy, flags);
	return;
}

int GetKeyTrigger(struct ITEM_INFO* item)//56080(<), 56520(<) (F)
{
	short* data;

	if (item->object_number == 7)
	{
		if (gfCurrentLevel == LVL5_ESCAPE_WITH_THE_IRIS)
		{
			return 1;
		}
	}//loc_560B8

	GetHeight(GetFloor(item->pos.x_pos, item->pos.y_pos, item->pos.z_pos, &item->room_number), item->pos.x_pos, item->pos.y_pos, item->pos.z_pos);

	data = trigger_index;
	if (data == NULL)
	{
		return 0;
	}//loc_56194

	if ((*data & 0x1F) != 4 && (*data & 0x8000) == 0)
	{
		++data;
		//loc_56118
		if ((*data & 0x1F) != 4)
		{
			if ((*data & 0x8000))
			{
				--data;
			}
			else
			{
				++data;
			}
		}
		//loc_56138
	}
	//loc_56138
	if (!(*data += 2 & 4))
	{
		return 0;
	}

	//loc_56154
	do
	{
		if ((*data & 0x3FFF) >> 10 == 0)
		{
			if (item == &items[(*data & 0x3FF) << 3])
			{
				return 1;
			}
		}//loc_56188
	} while ((*data++ & 0x8000) == 0);

	return 0;
}

int GetSwitchTrigger(struct ITEM_INFO* item, short* ItemNos, long AttatchedToSwitch)//55F4C, 563EC (F)
{
	short* data = trigger_index;

	GetHeight(GetFloor(item->pos.x_pos, item->pos.y_pos, item->pos.z_pos, &item->room_number),
		item->pos.x_pos, item->pos.y_pos, item->pos.z_pos);

	if (data != NULL)
	{
		while ((*data & 0x1F) != 4 && !(*data & 0x8000))
			data++;

		if (*data & 4)
		{
			short num = 0;
			
			do
			{
				data += 2;

				if (!(*data & 0x3C00) && item != &items[*data & 0x3FF])
				{
					ItemNos[num] = *data & 0x3FF;
					num++;
				}
			} while (!(*data & 0x8000));

			return num;
		}
	}

	return 0;
}

int SwitchTrigger(short item_num, short timer)//55DE4, 56284
{
	S_Warn("[SwitchTrigger] - Unimplemented!\n");
	return 0;
}