#include "COLLIDE_S.H"

#include "CONTROL.H"
#include "LARA.H"
#include "DRAW.H"
#include "GAMEFLOW.H"
#include "SPECIFIC.H"
#include "GETSTUFF.H"
#include "ROOMLOAD.H"

void UpdateSky()//7CE88(<), 7EECC(<) (F)
{
	int v1;

	v1 = SkyPos + gfLayer1Vel;

	if ((gfLevelFlags & GF_LVOP_LAYER1_USED))
	{
		if (v1 < 0)
		{
			v1 += 3280;
		}
		else if(v1 > 3280)
		{
			//loc_7CEB0
			v1 -= 3280;
		}

		SkyPos = v1;
	}//loc_7CEC0

	if ((gfLevelFlags & GF_LVOP_LAYER2_USED))
	{
		v1 = SkyPos2 + gfLayer2Vel;

		if (v1 < 0)
		{
			v1 += 3280;
		}
		else if (v1 > 3280)
		{
			v1 -= 3280;
		}

		SkyPos2 = v1;

	}//locret_7CEFC
}

void UpdateLaraRoom(struct ITEM_INFO* item, int height)
{
	UNIMPLEMENTED();
}

void ItemNewRoom(short item_num, short room_number)
{
	UNIMPLEMENTED();
}

unsigned short GetTiltType(struct FLOOR_INFO* floor, long x, long y, long z)
{
	struct room_info* r;//$a1
	struct FLOOR_INFO* f = floor;//$t1
	unsigned short* fd;//$a0
	int a0;
	int v1;

	while(f->pit_room != 255 && CheckNoColFloorTriangle(f, x, z) - 1)
	{
		//loc_7B094
		r = &room[f->pit_room];
		f = &r->floor[((z - r->z) >> 10) + (((x - r->x) >> 10)* r->x_size)];
	}

	//loc_7B100
	if (f->index != 0)
	{
		if((y - 512) >= (f->floor << 8))
		{
			fd = (unsigned short*)&floor_data[f->index];

			if ((fd[0] & 0x1F) == 2)
			{
				return fd[1];
			}

			//loc_7B14C
			if (((fd[0] & 0x1F) - 7) < 2 || (fd[0] & 0x1F) - 11 < 4)
			{
				//loc_7B164
				if ((fd[0] & 0x1F) == 7 || (fd[0] & 0x1F) == 11 || (fd[0] & 0x1F) == 12)
				{
					//loc_7B1A8
					if ((0x400 - (z & 0x3FF)) < (x & 0x3FF))
					{
						//loc_7B1C4
						a0 = fd[1] - (fd[1] & 0xF);
						v1 = fd[1] - ((fd[1] >> 8) & 0xF);
					}
					else
					{
						a0 = ((fd[1] >> 8) & 0xF) - ((fd[1] >> 4) & 0xF);
						v1 = (fd[1] & 0xF) - ((fd[1] >> 4) & 0xF);
					}
				}
				else
				{
					//loc_7B1D0
					if ((z & 0x3FF) < (x & 0x3FF))
					{
						//loc_7B1E4
						a0 = ((fd[1] >> 12) & 0xF) - (fd[1] & 0xF);
						v1 = (fd[1] & 0xF) - ((fd[1] >> 4) & 0xF);
					}
					else
					{
						a0 = ((fd[1] >> 8) & 0xF) - ((fd[1] >> 4) & 0xF);
						v1 = ((fd[1] >> 12) & 0xF) - ((fd[1] >> 8) & 0xF);
					}
				}

				//loc_7B1EC
				return ((a0 << 8) | (v1 & 0xFF) << 16) >> 16;
			}
			else
			{
				return 0;
			}
		}//loc_7B204
	}//loc_7B204

	return 0;
}

int GetCollisionInfo(struct COLL_INFO* coll, long xpos, long ypos, long zpos, short room_number, long objheight)
{
	int fp;
	short room_num;//0x70+var_58
	int room_num2;//0x70+var_54
	struct FLOOR_INFO* floor;//$s2
	int y;//0x70+var_38
	short height;//$s1
	short ceiling;//$a2
	int fallspeed;//0x70+var_2C
	//s5 = coll
	//v0 = objheight
	fp = 0;

	if (objheight < 0)
	{
		fp = 1;
		objheight = -objheight;
	}
	//loc_7B264
	//t3 = coll->facing
	//t0 = lara_item
	//v0 = ((coll->facing + 8192) & 0xFFFF) >> 14;
	//s0 = lara_item->fallspeed
	coll->old_anim_state = 0;
	coll->shift.x = 0;
	coll->shift.y = 0;
	coll->shift.z = 0;
	coll->quadrant = ((coll->facing + 8192) & 0xFFFF) >> 14;
	//at = room_number
	//a0 = xpos
	//v0 = ypos
	//v1 = objheight - ypos
	//a2 = zpos
	//s6 = ypos - 160
	//a1 = s6
	room_num = room_number;
	room_num2 = room_number;
	y = ypos;
	floor = GetFloor(xpos, ypos - 160, zpos, &room_num);
	height = GetHeight(floor, xpos, ypos - 160, zpos);

	if (height != -32512)
	{
		height -= ypos;
	}
	//loc_7B2F4
	ceiling = GetCeiling(floor, xpos, (ypos - 160) - lara_item->fallspeed, zpos);
	fallspeed = lara_item->fallspeed;

	if (ceiling != -32512)
	{
		ceiling -= ypos;
	}
	//loc_7B328
	//v0 = height_type
	//v1 = trigger_index
	//a3 = lara_item
	coll->mid_floor = height;
	coll->mid_ceiling = ceiling;
	coll->mid_type = height_type;
	coll->trigger = trigger_index;
	GetTiltType(floor, xpos, lara_item->pos.y_pos, zpos);
#if 0
sra     $v1, $v0, 8
sb      $v0, 0x80($s5)
sb      $v1, 0x81($s5)
lh      $at, 0x78($s5)
lhu     $v0, 0x76($s5)
lw      $v1, 0x48($s5)
la      $a0, dword_9A8C8
srl     $v0, 2
andi    $v0, 0x3FFC
addu    $v0, $a0
beqz    $at, loc_7B3BC
addiu   $at, -1
beqz    $at, loc_7B3E0
addiu   $at, -1
beqz    $at, loc_7B404
addiu   $at, -1
beqz    $at, loc_7B434
move    $s0, $zero
move    $s7, $zero
sw      $zero, 0x70+var_50($sp)
sw      $zero, 0x70+var_44($sp)
sw      $zero, 0x1EE0($gp)
j       loc_7B460
sw      $zero, 0x1EE4($gp)

loc_7B3BC:
lh      $a0, 0($v0)
negu    $v0, $v1
mult    $a0, $v1
sw      $v0, 0x70+var_50($sp)
sw      $v1, 0x70+var_44($sp)
sw      $v1, 0x1EE0($gp)
move    $s7, $v1
j       loc_7B424
move    $s0, $v1

loc_7B3E0:
lh      $a0, 2($v0)
negu    $v0, $v1
mult    $a0, $v1
sw      $v1, 0x70+var_50($sp)
sw      $v0, 0x70+var_44($sp)
sw      $v1, 0x1EE4($gp)
move    $s0, $v1
j       loc_7B454
move    $s7, $v1

loc_7B404:
lh      $a0, 0($v0)
negu    $v0, $v1
mult    $a0, $v1
sw      $v1, 0x70+var_50($sp)
sw      $v0, 0x70+var_44($sp)
sw      $v0, 0x1EE0($gp)
move    $s7, $v0
move    $s0, $v0

loc_7B424:
mflo    $a0
sra     $a0, 12
j       loc_7B460
sw      $a0, 0x1EE4($gp)

loc_7B434:
lh      $a0, 2($v0)
negu    $v0, $v1
mult    $a0, $v1
sw      $v0, 0x70+var_50($sp)
sw      $v1, 0x70+var_44($sp)
sw      $v0, 0x1EE4($gp)
move    $s0, $v0
move    $s7, $v0

loc_7B454:
mflo    $a0
sra     $a0, 12
sw      $a0, 0x1EE0($gp)

loc_7B460:
lw      $v0, 0x1EE4($gp)
lw      $s3, 0x70+arg_4($sp)
lw      $v1, 0x1EE0($gp)
lw      $s4, 0x70+arg_C($sp)
addu    $s3, $v0
beqz    $fp, loc_7B488
addu    $s4, $v1
lh      $at, 0x70+arg_10($sp)
nop
sh      $at, 0x70+var_58($sp)

loc_7B488:
move    $a0, $s3
move    $a1, $s6
move    $a2, $s4
jal     sub_78954
addiu   $a3, $sp, 0x70+var_58
move    $s2, $v0
move    $a0, $s2
move    $a1, $s3
move    $a2, $s6
jal     sub_78C74
move    $a3, $s4
li      $at, 0xFFFF8100
beq     $v0, $at, loc_7B4CC
move    $s1, $v0
lw      $v1, 0x70+arg_8($sp)
nop
subu    $s1, $v1

loc_7B4CC:
move    $a0, $s2
move    $a1, $s3
lw      $a2, 0x70+var_2C($sp)
jal     sub_79060
move    $a3, $s4
li      $at, 0xFFFF8100
beq     $v0, $at, loc_7B4F8
move    $a2, $v0
lw      $a0, 0x70+var_38($sp)
nop
subu    $a2, $a0

loc_7B4F8:
lw      $v0, 0x1C6C($gp)
sw      $a2, 0x10($s5)
sw      $s1, 0xC($s5)
sw      $v0, 0x14($s5)
lw      $a0, 0x1EE4($gp)
move    $a1, $s6
lw      $a2, 0x1EE0($gp)
addu    $a0, $s3, $a0
addu    $a2, $s4, $a2
jal     sub_78954
addiu   $a3, $sp, 0x70+var_58
lw      $a1, 0x1EE4($gp)
move    $a0, $v0
lw      $a3, 0x1EE0($gp)
move    $a2, $s6
addu    $a1, $s3, $a1
jal     sub_78C74
addu    $a3, $s4, $a3
li      $at, 0xFFFF8100
beq     $v0, $at, loc_7B558
move    $s1, $v0
lw      $v0, 0x70+arg_8($sp)
nop
subu    $s1, $v0

loc_7B558:
lw      $a0, 0x84($s5)
lw      $a1, 0x14($s5)
lw      $a2, 0xC($s5)
lw      $a3, 0($s5)
andi    $at, $a0, 3
beqz    $at, loc_7B598
addiu   $a1, -2
sltiu   $v0, $a1, 2
beqz    $v0, loc_7B598
slt     $v0, $a2, $a3
beqz    $v0, loc_7B598
slt     $v0, $s1, $a2
beqz    $v0, loc_7B598
nop
bltz    $a2, loc_7B5E0
li      $v0, 0xFFFF8001

loc_7B598:
andi    $at, $a0, 4
beqz    $at, loc_7B5B4
sltiu   $v0, $a1, 2
beqz    $v0, loc_7B5B4
slt     $v0, $a3, $a2
bnez    $v0, loc_7B5E0
li      $v0, 0x200

loc_7B5B4:
andi    $v0, $a0, 8
beqz    $v0, loc_7B5E4
lw      $v0, 0x1B3C($gp)
blez    $a2, loc_7B5E4
li      $at, 5
beqz    $v0, loc_7B5E4
lhu     $v1, 0($v0)
nop
andi    $v1, 0x1F
bne     $v1, $at, loc_7B5E4
li      $v0, 0x200

loc_7B5E0:
sw      $v0, 0xC($s5)

loc_7B5E4:
lw      $v1, 0x70+arg_4($sp)
lw      $a0, 0x70+var_50($sp)
lw      $v0, 0x70+arg_C($sp)
lw      $at, 0x70+var_54($sp)
addu    $s3, $v1, $a0
addu    $s4, $v0, $s0
sh      $at, 0x70+var_56($sp)
jal     sub_7B948
addiu   $a3, $sp, 0x70+var_56
sw      $s1, 0x18($s5)
sw      $a2, 0x1C($s5)
sw      $a0, 0x20($s5)
jal     sub_7B948
addiu   $a3, $sp, 0x70+var_58
sw      $s1, 0x30($s5)
sw      $a2, 0x34($s5)
sw      $a0, 0x38($s5)
sw      $s3, 0x70+var_34($sp)
sw      $s4, 0x70+var_30($sp)
lw      $v0, 0x70+arg_4($sp)
lw      $v1, 0x70+arg_C($sp)
lw      $a0, 0x70+var_44($sp)
lw      $at, 0x70+var_54($sp)
addu    $s3, $v0, $s7
addu    $s4, $v1, $a0
sh      $at, 0x70+var_56($sp)
jal     sub_7B948
addiu   $a3, $sp, 0x70+var_56
sw      $s1, 0x24($s5)
sw      $a2, 0x28($s5)
sw      $a0, 0x2C($s5)
jal     sub_7B948
addiu   $a3, $sp, 0x70+var_58
sw      $s1, 0x3C($s5)
sw      $a2, 0x40($s5)
sw      $a0, 0x44($s5)
move    $s1, $s3
move    $s0, $s4
lw      $a1, 0x70+arg_4($sp)
lw      $a2, 0x70+arg_8($sp)
lh      $v0, 0x70+var_58($sp)
lw      $a3, 0x70+arg_C($sp)
lw      $v1, 0x70+arg_14($sp)
move    $a0, $s5
sw      $v1, 0x70+var_5C($sp)
jal     sub_7BA68
sw      $v0, 0x70+var_60($sp)
lw      $t0, 0x70+arg_4($sp)
lw      $t1, 0x70+arg_C($sp)
lh      $t2, 0x78($s5)
lw      $v0, 0($s5)
li      $at, 0xFFFF8100
bne     $v0, $at, loc_7B6EC
li      $at, 1

loc_7B6BC:
lw      $v0, 0x64($s5)
lw      $v1, 0x68($s5)
lw      $a0, 0x6C($s5)
lw      $a1, 0x70+arg_8($sp)
subu    $v0, $t0
subu    $v1, $a1
subu    $a0, $t1
sh      $at, 0x7A($s5)
sw      $v0, 0x58($s5)
sw      $v1, 0x5C($s5)
j       loc_7B918
sw      $a0, 0x60($s5)

loc_7B6EC:
lw      $v1, 4($s5)
nop
subu    $at, $v0, $v1
blez    $at, loc_7B6BC
li      $at, 0x20
bltz    $v1, loc_7B720
nop
lw      $v0, 0x84($s5)
li      $at, 8
sw      $v1, 0x5C($s5)
sh      $at, 0x7A($s5)
ori     $v0, 0x40
sw      $v0, 0x84($s5)

loc_7B720:
lw      $v0, 0xC($s5)
lw      $a2, 0x4C($s5)
lw      $a1, 0x50($s5)
lw      $v1, 0x10($s5)
lw      $a0, 0x54($s5)
slt     $at, $a2, $v0
bnez    $at, loc_7B750
slt     $at, $v0, $a1
bnez    $at, loc_7B750
slt     $at, $a0, $v1
beqz    $at, loc_7B7F8
slt     $at, $v1, $a0

loc_7B750:
lw      $v0, 0x14($s5)
nop
addiu   $v0, -3
sltiu   $v0, 2
beqz    $v0, loc_7B788
li      $v0, 1

loc_7B768:
lw      $a1, 0x64($s5)
lw      $v1, 0x6C($s5)
subu    $a1, $t0
subu    $v1, $t1
sw      $a1, 0x58($s5)
sw      $v1, 0x60($s5)
j       loc_7B918
sh      $v0, 0x7A($s5)

loc_7B788:
beqz    $t2, loc_7B7B0
addiu   $v1, $t2, -1
beqz    $v1, loc_7B7D4
addiu   $v1, -1
beqz    $v1, loc_7B7B0
addiu   $v1, -1
beqz    $v1, loc_7B7D4

loc_7B7A4:
li      $v0, 1
j       loc_7B918
sh      $v0, 0x7A($s5)

loc_7B7B0:
lw      $a0, 0x1EE0($gp)
lw      $v0, 0x64($s5)
move    $a1, $t1
addu    $a0, $a1, $a0
subu    $v0, $t0
jal     sub_7BA34
sw      $v0, 0x58($s5)
j       loc_7B7A4
sw      $v0, 0x60($s5)

loc_7B7D4:
lw      $a0, 0x1EE4($gp)
move    $a1, $t0
jal     sub_7BA34
addu    $a0, $a1, $a0
lw      $v1, 0x6C($s5)
sw      $v0, 0x58($s5)
subu    $v1, $t1
j       loc_7B7A4
sw      $v1, 0x60($s5)

loc_7B7F8:
beqz    $at, loc_7B6BC
li      $at, 0x10
lw      $v1, 0x18($s5)
lw      $v0, 0x1C($s5)
slt     $at, $a2, $v1
bnez    $at, loc_7B824
slt     $at, $v1, $a1
bnez    $at, loc_7B824
slt     $v0, $a0, $v0
beqz    $v0, loc_7B88C
nop

loc_7B824:
lw      $v1, 0x20($s5)
li      $v0, 4
beq     $v1, $v0, loc_7B768
li      $v0, 2
beqz    $t2, loc_7B85C
addiu   $v1, $t2, -1
beqz    $v1, loc_7B874
addiu   $v1, -1
beqz    $v1, loc_7B85C
addiu   $v1, -1
beqz    $v1, loc_7B874

loc_7B850:
li      $v0, 2
j       loc_7B918
sh      $v0, 0x7A($s5)

loc_7B85C:
lw      $a1, 0x1EE4($gp)
lw      $a0, 0x70+var_34($sp)
jal     sub_7BA34
addu    $a1, $t0, $a1
j       loc_7B850
sw      $v0, 0x58($s5)

loc_7B874:
lw      $a1, 0x1EE0($gp)
lw      $a0, 0x70+var_30($sp)
jal     sub_7BA34
addu    $a1, $t1, $a1
j       loc_7B850
sw      $v0, 0x60($s5)

loc_7B88C:
lw      $v1, 0x24($s5)
lw      $v0, 0x28($s5)
slt     $at, $a2, $v1
bnez    $at, loc_7B8B0
slt     $at, $v1, $a1
bnez    $at, loc_7B8B0
slt     $at, $a0, $v0
beqz    $at, loc_7B918
nop

loc_7B8B0:
lw      $v1, 0x2C($s5)
li      $v0, 4
beq     $v1, $v0, loc_7B768
li      $v0, 4
beqz    $t2, loc_7B8E8
addiu   $v1, $t2, -1
beqz    $v1, loc_7B900
addiu   $v1, -1
beqz    $v1, loc_7B8E8
addiu   $v1, -1
beqz    $v1, loc_7B900

loc_7B8DC:
li      $v0, 4
j       loc_7B918
sh      $v0, 0x7A($s5)

loc_7B8E8:
lw      $a1, 0x1EE4($gp)
move    $a0, $s1
jal     sub_7BA34
addu    $a1, $t0, $a1
j       loc_7B8DC
sw      $v0, 0x58($s5)

loc_7B900:
lw      $a1, 0x1EE0($gp)
move    $a0, $s0
jal     sub_7BA34
addu    $a1, $t1, $a1
j       loc_7B8DC
sw      $v0, 0x60($s5)

loc_7B918:
lw      $ra, 0x70+var_4($sp)
lw      $fp, 0x70+var_8($sp)
lw      $s7, 0x70+var_C($sp)
lw      $s6, 0x70+var_10($sp)
lw      $s5, 0x70+var_14($sp)
lw      $s4, 0x70+var_18($sp)
lw      $s3, 0x70+var_1C($sp)
lw      $s2, 0x70+var_20($sp)
lw      $s1, 0x70+var_24($sp)
lw      $s0, 0x70+var_28($sp)
jr      $ra
addiu   $sp, 0x70
#endif
	return 0;
}
