#include "LOT.H"

#include "SPECIFIC.H"
#include "MALLOC.H"
#include "BOX.H"
#include "CONTROL.H"
#include "OBJECTS.H"
#include "LARA.H"

#if PC_VERSION
#include "INIT.H"
#endif

int slots_used;
short nAIObjects;
struct AIOBJECT* AIObjects;
struct creature_info* baddie_slots;

//void /*$ra*/ CreateZone(struct ITEM_INFO *item /*$t1*/)
void CreateZone(struct ITEM_INFO* item)//4E330, 4E794
{
	int i; // $a1
	struct creature_info* creature; // $a3
	struct box_node* node; // $a2
	short* zone; // $t0
	short zone_number; // $t2
	short* flip; // $a0
	short flip_number; // $t1
	struct room_info* r; // $a1


#if 0 
	sub_4E330:
			 move	$t1, $a0
				 lh	$v1, 0x18($t1)
				 lw	$a1, dword_800A24DC
				 sll	$v0, $v1, 2
				 addu	$v0, $v1
				 sll	$v0, 4
				 addu	$a1, $v0
				 lw	$v1, 0x40($t1)
				 lw	$v0, 0x14($a1)
				 lh	$a0, 0x28($a1)
				 subu	$v1, $v0
				 sra	$v1, 10
				 mult	$v1, $a0
				 lw	$v0, 0x48($t1)
				 lw	$a0, 0x1C($a1)
				 nop
				 subu	$v0, $a0
				 sra	$v0, 10
				 lw	$a0, 8($a1)
				 mflo	$v1
				 addu	$v0, $v1
				 sll	$v0, 3
				 addu	$v0, $a0
				 lhu	$v1, 2($v0)
				 lw	$a3, 0x3C($t1)
				 srl	$v1, 4
				 andi	$v1, 0x7FF
				 sh	$v1, 0x24($t1)
				 lh	$v0, 0xCE($a3)
				 nop
				 bnez	$v0, loc_4E460
				 move	$a1, $zero
				 li	$v0, 0xA2314
				 li	$v1, 0xA2318
				 lw	$a0, 0xE0($a3)
				 lw	$a2, 0xB8($a3)
				 sll	$a0, 3
				 addu	$v0, $a0, $v0
				 addu	$a0, $v1
				 lw	$t0, 0($v0)
				 lhu	$v0, 0x24($t1)
				 lw	$a0, 0($a0)
				 sll	$v0, 1
				 addu	$v1, $v0, $t0
				 addu	$v0, $a0
				 lh	$t2, 0($v1)
				 lh	$t1, 0($v0)
				 lw	$v0, dword_800A2308
				 nop
				 blez	$v0, locret_4E458
				 sh	$zero, 0xC8($a3)
				 move	$v1, $v0

				 loc_4E410 :
			 lh	$v0, 0($t0)
				 nop
				 beq	$v0, $t2, loc_4E430
				 nop
				 lh	$v0, 0($a0)
				 nop
				 bne	$v0, $t1, loc_4E444
				 nop

				 loc_4E430 :
			 sh	$a1, 6($a2)
				 lhu	$v0, 0xC8($a3)
				 addiu	$a2, 8
				 addiu	$v0, 1
				 sh	$v0, 0xC8($a3)

				 loc_4E444 :
				 addiu	$a1, 1
				 addiu	$t0, 2
				 slt	$v0, $a1, $v1
				 bnez	$v0, loc_4E410
				 addiu	$a0, 2

				 locret_4E458 :
				 jr	$ra
				 nop

				 loc_4E460 :
			 lw	$a2, 0xB8($a3)
				 lw	$a0, dword_800A2308
				 nop
				 blez	$a0, locret_4E458
				 sh	$zero, 0xC8($a3)

				 loc_4E478 :
				 sh	$a1, 6($a2)
				 addiu	$a2, 8
				 addiu	$a1, 1
				 lhu	$v0, 0xC8($a3)
				 slt	$v1, $a1, $a0
				 addiu	$v0, 1
				 bnez	$v1, loc_4E478
				 sh	$v0, 0xC8($a3)
				 jr	$ra
				 nop
				 # End of function sub_4E330
#endif
	UNIMPLEMENTED();
}

//Only called when enemy is triggered
void InitialiseSlot(short item_number /*$s0*/, int slot /*$a1*/)//4E13C, 4E5A0 (F)
{
	struct creature_info* creature = &baddie_slots[slot];
	struct ITEM_INFO* item = &items[item_number];
	item->data = creature;

	creature->item_num = item_number;
	creature->mood = BORED_MOOD;
	creature->joint_rotation[0] = 0;
	creature->joint_rotation[1] = 0;
	creature->joint_rotation[2] = 0;
	creature->joint_rotation[3] = 0;

	creature->alerted = 0;
	creature->head_left = 0;
	creature->head_right = 0;
	creature->reached_goal = 0;
	creature->hurt_by_lara = 0;
	creature->patrol2 = 0;
	creature->jump_ahead = 0;
	creature->monkey_ahead = 0;

	creature->maximum_turn = ANGLE(1);

	creature->flags = 0;
	creature->enemy = 0;

	creature->LOT.can_jump = FALSE;
	creature->LOT.can_monkey = FALSE;

	creature->LOT.is_jumping = FALSE;
	creature->LOT.is_monkeying = FALSE;

	creature->LOT.step = 256;
	creature->LOT.drop = -512;
	creature->LOT.block_mask = 16384;
	creature->LOT.fly = 0;
	creature->LOT.zone = BASIC_ZONE;

	switch (item->object_number)
	{
	case SAS:
	case BLUE_GUARD:
	case MAFIA2:
	case SAILOR:
		creature->LOT.step = SECTOR(1);
		creature->LOT.drop = SECTOR(-1);
		creature->LOT.can_jump = TRUE;
		creature->LOT.zone = HUMAN_ZONE;
		break;

	case HITMAN:
		creature->LOT.step = SECTOR(1);
		creature->LOT.drop = SECTOR(-1);
		creature->LOT.can_jump = TRUE;
		creature->LOT.can_monkey = TRUE;
		creature->LOT.zone = HUMAN_ZONE;
		break;

	case CROW:
	case WILLOWISP:
	case REAPER:
	case GREEN_TEETH:
	case ATTACK_SUB:
		creature->LOT.step = SECTOR(20);
		creature->LOT.drop = SECTOR(-20);
		creature->LOT.fly = 16;
		creature->LOT.zone = FLYER_ZONE;
		break;
	}

	ClearLOT(&creature->LOT);

	if (item_number != lara.item_number)
		CreateZone(item);

	slots_used++;
}

int EnableBaddieAI(short item_number, int Always)//4DF0C, 4E370
{
	/*struct ITEM_INFO* item = &items[item_number];

	if (item->data != NULL)
		return 1;

	if (slots_used >= 5)
	{
		
	}
	else
	{
		int slot;
		for(slot = 0; slot < 5; slot++)
		{
			
		}
	}*/

	UNIMPLEMENTED();
	return 0;
}

void DisableBaddieAI(short item_num)//4DEC0, 4E324 (F)
{
	struct ITEM_INFO* item = &items[item_num];
	struct creature_info* creature = (struct creature_info*)item->data;

	item->data = NULL;

	if (creature)
	{
		creature->item_num = -1;
		slots_used--;
	}
}

void InitialiseLOTarray(int allocmem)//4DE40(<), 4E2A4(<) (F)
{
	int i;

	if (allocmem)
		baddie_slots = (struct creature_info *)game_malloc(5 * sizeof(struct creature_info));
	
	for (i = 0; i < 5; i++)
	{
		baddie_slots[i].item_num = -1;

		if (allocmem)
		{
			baddie_slots[i].LOT.node = (struct box_node*)game_malloc(number_boxes * sizeof(struct box_node));
		}
	}

	slots_used = 0;
}

void ClearLOT(struct lot_info* LOT) // (F)
{
	struct box_node* node;
	int i;

	LOT->tail = 2047;
	LOT->head = 2048;
	LOT->search_number = 0;
	LOT->target_box = 2047;
	LOT->required_box = 2047;

	for(i = 0, node = LOT->node; i < number_boxes; i++, node++)
	{
		node->next_expansion = 2047;
		node->exit_box = 2047;
		node->search_number = 0;
	}
}