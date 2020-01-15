#include "CONTROL_S.H"

#include "CAMERA.H"
#include "COLLIDE_S.H"
#include "DRAW.H"
#include "SPECIFIC.H"

void DrawBinoculars()
{
	S_Warn("[DrawBinoculars] - Unimplemented!\n");
}

void TranslateItem(struct ITEM_INFO* item, unsigned short x, unsigned short y, unsigned short z)
{
	short sin;//$v1
	short cos;//$t0

	cos = COS(item->pos.y_rot);
	sin = SIN(item->pos.y_rot);

	item->pos.x_pos += ((cos * x) + (sin * z)) >> W2V_SHIFT;
	item->pos.y_pos += y;
	item->pos.z_pos += ((-sin * x) + (cos * z)) >> W2V_SHIFT;
}

int GetChange(struct ITEM_INFO* item, struct ANIM_STRUCT* anim)//7D48C
{
	struct CHANGE_STRUCT* change;//$t1
	struct RANGE_STRUCT* range;//$v1
	int i;//$t2
	int j;//$t0

	if (item->current_anim_state == item->goal_anim_state)
	{
		//locret_7D51C
		return 0;
	}

	change = &changes[anim->change_index];
	
	if (anim->number_changes <= 0)
	{
		//locret_7D51C
		return 0;
	}

	//loc_7D4C4
	do
	{
		j = 0;
		if (change->goal_anim_state == item->goal_anim_state && change->number_ranges > 0)
		{
			range = &ranges[change->range_index];

			//loc_7D4E4
			do
			{
				if (item->frame_number < range->start_frame)
				{
					//loc_7D4FC
					j++;
					if (j < change->number_ranges)
					{
						range++;
						continue;
					}
					else
					{
						break;
					}
				}
				else if (range->end_frame >= item->frame_number)
				{
					//loc_7D524
					item->anim_number = range->link_anim_num;
					item->frame_number = range->link_frame_num;
					return 1;
				}
			} while (1);
		}
		//loc_7D50C
		i++;
		change++;
	} while (i < anim->number_changes);

	//locret_7D51C
	return 0;
}

void AnimateLara(struct ITEM_INFO* item /* s1 */)//7D53C(<)
{
	struct ANIM_STRUCT* anim = &anims[item->anim_number];//$s2
	unsigned short* command;//$s0
	unsigned short data;//$v0

	item->frame_number += 1;
	//v0 = anim->number_changes

	if (anim->number_changes > 0 && GetChange(item, anim))
	{
		//v1 = item->anim_number
		//a0 = &anims[item->anim_number];
		anim = &anims[item->anim_number];///@TODO Not really required
		item->current_anim_state = anim->current_anim_state;
	}
	//loc_7D5BC
	//v1 = item->frame_number
	//v0 = anim->frame_end

	if (anim->frame_end < item->frame_number)
	{
		//s3 = anim->number_commands
		//v0 = anim->command_index
		//v1 = commands

		if (anim->number_commands > 0)
		{
			command = (unsigned short*)&commands[anim->command_index];

			//loc_7D5EC
			data = *command++;

			if (data - 1 == 0)
			{
				//loc_7D628
				TranslateItem(item, command[0], command[1], command[2]);
				command += 3;
				UpdateLaraRoom(item, -381);
			}
			else if (data - 2 == 0)
			{
				//loc_7D650
			}
			else if (data - 3 == 0)
			{
				//loc_7D684
			}
			else if (data - 5 == 0 || data - 6 == 0)
			{
				//loc_7D620
			}

			//loc_7D698

		}//loc_7D6A4
	}//loc_7D6D4

#if 0
addiu   $at, $v0, -1
beqz    $at, loc_7D628
addiu   $at, $v0, -2
beqz    $at, loc_7D650
addiu   $at, $v0, -3
beqz    $at, loc_7D684
addiu   $at, $v0, -5
beqz    $at, loc_7D620
addiu   $at, $v0, -6
bnez    $at, loc_7D698
nop

loc_7D620:
j       loc_7D698
addiu   $s0, 4

loc_7D650:
lw      $v1, 0x84($s1)
lhu     $at, 0($s0)
lhu     $v0, 2($s0)
lh      $a0, 0x5232($gp)
addiu   $s0, 4
ori     $v1, 8
sh      $at, 0x20($s1)
sh      $v0, 0x1E($s1)
beqz    $a0, loc_7D698
sw      $v1, 0x84($s1)
sh      $a0, 0x20($s1)
j       loc_7D698
sh      $zero, 0x5232($gp)

loc_7D684:
lh      $v1, 0x522A($gp)
li      $v0, 5
beq     $v1, $v0, loc_7D698
nop
sh      $zero, 0x522A($gp)

loc_7D698:
addiu   $s3, -1
bgtz    $s3, loc_7D5EC
nop

loc_7D6A4:
lh      $at, 0x1C($s2)
lhu     $a0, 0x1E($s2)
lw      $v0, 0x202C($gp)
sh      $at, 0x14($s1)
sh      $a0, 0x16($s1)
sll     $v1, $at, 2
addu    $v1, $at
sll     $v1, 3
addu    $s2, $v0, $v1
lh      $v0, 6($s2)
nop
sh      $v0, 0xE($s1)

loc_7D6D4:
lh      $s3, 0x24($s2)
lh      $v0, 0x26($s2)
lw      $v1, 0x2078($gp)
blez    $s3, loc_7D7C8
sll     $v0, 1
addu    $s0, $v1, $v0

loc_7D6EC:
lhu     $v0, 0($s0)
addiu   $s0, 2
addiu   $at, $v0, -2
beqz    $at, loc_7D7B8
addiu   $at, $v0, -5
beqz    $at, loc_7D720
addiu   $at, $v0, -6
beqz    $at, loc_7D780
addiu   $at, $v0, -1
bnez    $at, loc_7D7BC
nop
j       loc_7D7BC
addiu   $s0, 6

loc_7D720:
lh      $v1, 0x16($s1)
lh      $v0, 0($s0)
lhu     $a0, 2($s0)
bne     $v1, $v0, loc_7D7B8
andi    $a1, $a0, 0xC000
beqz    $a1, loc_7D76C
li      $v0, 0x4000
lw      $v1, 0x5270($gp)
bne     $a1, $v0, loc_7D754
nop
bgez    $v1, loc_7D76C
li      $v0, 0xFFFF8100
beq     $v1, $v0, loc_7D76C

loc_7D754:
li      $v0, 0x8000
bne     $a1, $v0, loc_7D7B8
nop
bgez    $v1, loc_7D7B8
li      $v0, 0xFFFF8100
beq     $v1, $v0, loc_7D7B8

loc_7D76C:
andi    $a0, 0x3FFF
addiu   $a1, $s1, 0x40
li      $a2, 2
jal     sub_91780
addiu   $ra, 0x38

loc_7D780:
lh      $at, 0x16($s1)
lh      $v0, 0($s0)
lui     $v1, 9
bne     $at, $v0, loc_7D7B8
la      $v1, off_92AE8
lhu     $a1, 2($s0)
move    $a0, $s1
andi    $a3, $a1, 0x3FFF
sll     $v0, $a3, 2
addu    $v0, $v1
lw      $a2, 0($v0)
andi    $a1, 0xC000
jalr    $a2
sh      $a1, 0x1AAC($gp)

loc_7D7B8:
addiu   $s0, 4

loc_7D7BC:
addiu   $s3, -1
bgtz    $s3, loc_7D6EC
nop

loc_7D7C8:
lw      $a1, 0x14($s2)
lw      $s0, 0x10($s2)
lh      $t1, 0x16($s1)
lh      $v0, 0x18($s2)
beqz    $a1, loc_7D7EC
subu    $t1, $v0
mult    $a1, $t1
mflo    $v0
addu    $s0, $v0

loc_7D7EC:
lw      $v0, 0x84($s1)
nop
andi    $v0, 8
bnez    $v0, loc_7D828
sra     $s0, 16
lw      $a1, 0xC($s2)
lw      $a0, 8($s2)
beqz    $a1, loc_7D820
sra     $v0, $a0, 16
mult    $a1, $t1
mflo    $v0
addu    $a0, $v0
sra     $v0, $a0, 16

loc_7D820:
j       loc_7D884
sh      $v0, 0x1E($s1)

loc_7D828:
lw      $a2, 0xC($s2)
addiu   $v0, $t1, -1
mult    $a2, $v0
lhu     $a1, 0x1E($s1)
lw      $v1, 8($s2)
mflo    $a0
addu    $a0, $v1, $a0
sra     $v0, $a0, 16
subu    $a1, $v0
addu    $a0, $a2
sra     $v0, $a0, 16
lh      $a0, 0x20($s1)
addu    $a1, $v0
sh      $a1, 0x1E($s1)
slti    $v0, $a0, 0x80
beqz    $v0, loc_7D870
addiu   $v0, $a0, 1
addiu   $v0, $a0, 6

loc_7D870:
sh      $v0, 0x20($s1)
lw      $v1, 0x44($s1)
nop
addu    $v1, $v0
sw      $v1, 0x44($s1)

loc_7D884:
lw      $v1, 0x532C($gp)
li      $v0, 0xFFFFFFFF
beq     $v1, $v0, loc_7D89C
nop
jal     sub_4B3D8
move    $a0, $s1

loc_7D89C:
lw      $v0, 0x526C($gp)
lui     $t0, 9
andi    $v0, 0x20
bnez    $v0, loc_7D934
la      $t0, dword_9A8C8
lhu     $a2, 0x52CE($gp)
lh      $a3, 0x1E($s1)
srl     $at, $a2, 2
andi    $at, 0x3FFC
addu    $at, $t0
lh      $v0, 0($at)
lh      $at, 2($at)
mult    $v0, $a3
lw      $t2, 0x40($s1)
lw      $t3, 0x48($s1)
mflo    $v0
sra     $v0, 12
addu    $t2, $v0
mult    $at, $a3
addiu   $a2, 0x4000
sra     $a2, 2
andi    $a2, 0x3FFC
addu    $a2, $t0
lh      $v1, 0($a2)
lh      $a0, 2($a2)
mflo    $at
sra     $at, 12
addu    $t3, $at
mult    $v1, $s0
mflo    $v1
sra     $v1, $v0, 12
addu    $t2, $v1
mult    $a0, $s0
sw      $t2, 0x40($s1)
mflo    $a0
sra     $a0, 12
addu    $t3, $a0
sw      $t3, 0x48($s1)

loc_7D934:
lw      $ra, 0x24+var_4($sp)
lw      $s3, 0x24+var_8($sp)
lw      $s2, 0x24+var_C($sp)
lw      $s1, 0x24+var_10($sp)
lw      $s0, 0x24+var_14($sp)
jr      $ra
addiu   $sp, 0x24
#endif
	UNIMPLEMENTED();
}