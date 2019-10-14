#include "GETSTUFF.H"

#include "DRAW.H"
#include "CONTROL.H"
#include "OBJECTS.H"
#include "ROOMLOAD.H"
#include "SPECIFIC.H"
#include "TEXT_S.H"

long DIVFP(long A, long B)
{
	return (A / (B >> 8)) << 8;
}

long MULFP(long A, long B)
{
	unsigned long long result = (long long)((long long)(int)A * (long long)(int)B);
	return ((result >> 32) << 16) | ((result & 0xFFFFFFFF) >> 16);
}

char GetDoor(struct FLOOR_INFO* floor)
{
	unsigned short* fd;//$a0
	unsigned short v1;//$v1

	if (floor->index == 0)
	{
		//locret_78870
		return -1;
	}

	fd = (unsigned short*)&floor_data[floor->index];
	v1 = *fd++;

	if ((v1 & 0x1F) == 2 || (v1 & 0x1F) - 7 < 2 || (v1 & 0x1F) - 11 < 4)
	{
		if ((v1 & 0x8000))
		{
			return -1;
		}

		v1 = fd[1];
		fd += 2;
	}
	//loc_78828
	if ((v1 & 0x1F) == 3 || (v1 & 0x1F) - 9 < 2 || (v1 & 0x1F) - 15 < 4)
	{
		//loc_78848
		if ((v1 & 0x8000))
		{
			return -1;
		}

		v1 = fd[1];
		fd += 2;
	}
	//loc_7885C
	if ((v1 & 0x1F))
	{
		return fd[0];
	}

	return -1;
}

int xLOS(struct GAME_VECTOR* start, struct GAME_VECTOR* target)
{
	UNIMPLEMENTED();
	return 0;
}

int zLOS(struct GAME_VECTOR* start, struct GAME_VECTOR* target)
{
	UNIMPLEMENTED();
	return 0;
}

long CheckNoColFloorTriangle(struct FLOOR_INFO* floor, long x, long z)//(F)
{
	x &= 0x3FF;
	if (!(floor->index))
	{
		return 0;
	}

	z &= 0x3FF;

	if ((floor_data[floor->index] & 0x1F) - 11 > 3)
	{
		return 0;
	}

	if ((floor_data[floor->index] & 0x1F) == 11 && (1024 - z) > x)
	{
		return -1;
	}

	//loc_78C24
	if ((floor_data[floor->index] & 0x1F) == 12 && (1024 - z) < x)
	{
		return -1;
	}

	//loc_78C40
	if ((floor_data[floor->index] & 0x1F) == 13 && z > x)
	{
		return -1;
	}

	//loc_78C54
	if ((floor_data[floor->index] & 0x1F) == 14 && z < x)
	{
		return -1;
	}

	return 1;
}

long CheckNoColCeilingTriangle(struct FLOOR_INFO* floor, long x, long z)//(F)
{
	int at;
	int a0;
	short* v1;

	x &= 0x3FF;

	if (!floor->index)
	{
		return 0;
	}

	v1 = &floor_data[floor->index];
	a0 = floor_data[floor->index];

	z &= 0x3FF;

	at = (floor_data[floor->index] & 0x1F);

	if (at == 2 && at - 7 > 1 && at - 11 < 4)
	{
		//loc_788C0
		if ((a0 & 0x8000))
		{
			return 0;
		}

		a0 = v1[2];
	}
	//loc_788D4
	at = a0 & 0x1F;//v1

	if (at - 15 > 14)
	{
		return 0;
	}

	if (at == 15 && (1024 - z) > x)
	{
		return -1;
	}

	//loc_78904
	if (at == 16 && 1024 - z < x)
	{
		return -1;
	}

	if (at == 17 && z > x)
	{
		return -1;
	}

	if (at == 18 && z < x)
	{
		return -1;
	}

	return 1;
}

struct FLOOR_INFO* GetFloor(long x, long y, long z, short* room_number)//(F)
{
	struct room_info* r = NULL;
	struct FLOOR_INFO* floor = NULL;
	int v1;
	int dz;
	int dx;
	int a1;
	int a0 = 0;///@REMOVE ME this is hack crash fix.
	char door;
	int v0;
	char str[64];

loc_78974:
	r = &room[*room_number];
	dz = ((z - r->z) >> 10);
	dx = ((x - r->x) >> 10);

#if 1//DEBUG_CAM
	//return &r->floor[0];
#endif

	if (dz > 0)
	{
		//loc_789B4
		if (dz < r->x_size - 1)
		{
			//loc_789EC
			if (dx >= 0)
			{
				//loc_789FC
				if (dx > (r->y_size))
				{
					dx = r->x_size - 1;
				}
			}
			else
			{
				v1 = 0;
			}
		}
		else if (dx > 0)
		{
			dz = a0;
			//loc_789CC
			//loc_789D4
			a0 = (r->x_size >> 16) - 2;

			if ((r->x_size >> 16) - 2 < dx)
			{
				dx = (r->x_size >> 16) - 2;
			}
		}
		else
		{
			//loc_789CC
			dx = 1;
		}
	}
	else if (dx > 0)
	{
		dz = 0;
		//loc_789D4
		a0 = (r->x_size >> 16) - 2;

		if ((r->x_size >> 16) - 2 < dx)
		{
			dx = (r->x_size >> 16) - 2;
		}
	}
	else
	{
		dx = 1;
	}

	floor = &r->floor[dz + (dx * r->x_size)];
	door = GetDoor(floor);
	sprintf(str, "DOOR %d\n", door);
	PrintString(20, 210, 1, str, 0);

	if (door != -1)
	{
		*room_number = door;
		goto loc_78974;
	}

	//loc_78A50
	if (y > floor->floor << 8)
	{
loc_78A68:
		if (floor->pit_room == 255)
		{
			return floor;
		}

		v0 = CheckNoColFloorTriangle(floor, x, z);

		if (v0 == 1)
		{
			return floor;
		}

		if (v0 == -1)
		{
			if (y > room->minfloor)
			{
				return floor;
			}
		}
		//loc_78AAC
		*room_number = floor->pit_room;
		r = &room[floor->pit_room];
		//v0 = z - v0
		floor = &room->floor[(((x - r->x) >> 10) * r->x_size) + ((z - r->z) >> 10)];	
		
		if (y < (floor->floor << 8))
		{
			return floor;
		}

		goto loc_78A68;

	}//loc_78BB0

	if (y > (floor->ceiling << 8))
	{
		return floor;
	}

	do
	{
		//loc_78B1C
		if (floor->sky_room == 255)
		{
			return floor;
		}

		v0 = CheckNoColCeilingTriangle(floor, x, z);

		if (v0 == 1)
		{
			return floor;
		}

		if (v0 == -1)
		{
			if (y > room->y)
			{
				return floor;
			}
		}

		//loc_78B60
		*room_number = floor->sky_room;///@FIXME illegal room number, reporting 255 here
		r = &room[floor->sky_room];
		floor = &r->floor[(((z - r->z) >> 10) + ((x - r->x) >> 10)) * r->x_size];
	
	} while (y < (floor->ceiling << 8));

	return floor;
}

short GetCeiling(struct FLOOR_INFO* floor, int x, int y, int z)
{
	struct room_info* r;//$a0
	struct FLOOR_INFO* f;//$s0

	//s1 = floor
	//t4 = x
	//t5 = z
	f = floor;

	//loc_790F0
	while (f->sky_room != 0xFF)
	{
		//loc_7908C
		if (CheckNoColCeilingTriangle(floor, x, z) == 1)
		{
			break;
		}

		r = &room[f->sky_room];
		f = &r->floor[((z - r->z) >> 10) + (((x - r->x) >> 10) * r->x_size)];
	}
	//loc_79100
#if 0
loc_79100:
lb      $t7, 7($s0)
lhu     $v1, 0($s0)
li      $v0, 0xFFFF8100
sll     $t7, 8
beq     $t7, $v0, loc_793D4
sll     $v1, 1
beqz    $v1, loc_792BC
nop
lw      $s0, 0x4004($gp)
li      $v0, 2
addu    $s0, $v1
lhu     $a0, 0($s0)
addiu   $s0, 2
andi    $s2, $a0, 0x1F
beq     $s2, $v0, loc_79154
addiu   $v0, $s2, -7
sltiu   $v0, 2
bnez    $v0, loc_79154
addiu   $v0, $s2, -0xB
sltiu   $v0, 4
beqz    $v0, loc_7916C

loc_79154:
andi    $at, $a0, 0x8000
lhu     $a0, 2($s0)
addiu   $s0, 4
andi    $s2, $a0, 0x1F
sll     $at, 16
bnez    $at, loc_792BC

loc_7916C:
li      $v0, 3
beq     $s2, $v0, loc_7924C
addiu   $v0, $s2, -9
sltiu   $v0, 2
bnez    $v0, loc_7918C
addiu   $v0, $s2, -0xF
sltiu   $v0, 4
beqz    $v0, loc_792BC

loc_7918C:
andi    $a2, $t4, 0x3FF
lhu     $v1, 0($s0)
andi    $a1, $t5, 0x3FF
andi    $t1, $v1, 0xF
srl     $t0, $v1, 4
andi    $t0, 0xF
srl     $a3, $v1, 8
andi    $a3, 0xF
srl     $v1, 12
negu    $t1, $t1
negu    $t0, $t0
negu    $a3, $a3
negu    $v1, $v1
li      $v0, 9
beq     $s2, $v0, loc_791D4
addiu   $v0, $s2, -0xF
sltiu   $v0, 2
beqz    $v0, loc_79204

loc_791D4:
li      $v0, 0x400
subu    $v0, $a1
slt     $v0, $a2
bnez    $v0, loc_791F8
srl     $a0, 5
srl     $a0, 5
subu    $a1, $a3, $t0
j       loc_79228
subu    $a2, $v1, $a3

loc_791F8:
subu    $a1, $v1, $t1
j       loc_79228
subu    $a2, $t1, $t0

loc_79204:
slt     $v0, $a1, $a2
bnez    $v0, loc_79220
srl     $a0, 5
srl     $a0, 5
subu    $a1, $a3, $t0
j       loc_79228
subu    $a2, $t1, $t0

loc_79220:
subu    $a1, $v1, $t1
subu    $a2, $v1, $a3

loc_79228:
andi    $a0, 0x1F
andi    $at, $a0, 0x10
beqz    $at, loc_7923C
li      $at, 0xFFFFFFF0
or      $a0, $at

loc_7923C:
sll     $a0, 8
addu    $t7, $a0

loc_79244:
jal     sub_793EC
addiu   $ra, 0x70

loc_7924C:
lb      $a1, 1($s0)
j       loc_79244
lb      $a2, 0($s0)

loc_79258:
move    $a1, $t4
jal     sub_78BD0
move    $a2, $t5
li      $v1, 1
beq     $v0, $v1, loc_792CC
nop
lbu     $v1, 4($s1)
lw      $a0, 0x1F28($gp)
sll     $v0, $v1, 2
addu    $v0, $v1
sll     $v0, 4
addu    $a0, $v0
lw      $v0, 0x14($a0)
lh      $v1, 0x28($a0)
subu    $v0, $t4, $v0
sra     $v0, 10
mult    $v0, $v1
lw      $v0, 0x1C($a0)
lw      $v1, 8($a0)
subu    $v0, $t5, $v0
sra     $v0, 10
mflo    $t1
addu    $v0, $t1
sll     $v0, 3
addu    $s1, $v1, $v0

loc_792BC:
lbu     $v1, 4($s1)
li      $v0, 0xFF
bne     $v1, $v0, loc_79258
move    $a0, $s1

loc_792CC:
lhu     $v0, 0($s1)
lw      $v1, 0x4004($gp)
beqz    $v0, loc_793D0
sll     $v0, 1
addu    $s0, $v1, $v0

loc_792E0:
lhu     $s2, 0($s0)
addiu   $s0, 2
andi    $v0, $s2, 0x1F
addiu   $v1, $v0, -1     # switch 21 cases
sltiu   $v0, $v1, 0x15
beqz    $v0, def_7930C   # jumptable 00078D8C default case
sll     $v0, $v1, 2
lw      $v0, jpt_7930C($v0)
nop
jr      $v0              # switch jump
nop

loc_79314:               # jumptable 0007930C cases 1-3,7-18
j       loc_793C8

loc_79318:               # jumptable 0007930C case 4
addiu   $s0, 2

loc_7931C:
lhu     $s1, 0($s0)
addiu   $s0, 2
andi    $v0, $s1, 0x3FFF
srl     $v1, $v0, 10
beqz    $v1, loc_79350
li      $v0, 0xC
beq     $v1, $v0, loc_79344
li      $v0, 1
bne     $v1, $v0, loc_793C0
nop

loc_79344:
lhu     $s1, 0($s0)
j       loc_793C0
addiu   $s0, 2

loc_79350:
lw      $a0, 0x1B38($gp)
andi    $v1, $s1, 0x3FF
sll     $v0, $v1, 7
sll     $v1, 4
addu    $v0, $v1
addu    $a0, $v0
lh      $v0, 0x28($a0)
lh      $v1, 0xC($a0)
andi    $v0, 0x8000
bnez    $v0, loc_793C0
sll     $v1, 6
li      $a2, 0x1F2480
addu    $v1, $a2
lw      $v0, 0x18($v1)
move    $a3, $t5
beqz    $v0, loc_793C0
move    $a1, $t4
sw      $t4, 0x40+var_14($sp)
sw      $t5, 0x40+var_10($sp)
sw      $t7, 0x40+var_28($sp)
lw      $a2, 0x40+var_C($sp)
addiu   $at, $sp, 0x40+var_28
jalr    $v0
sw      $at, 0x40+var_30($sp)
lw      $t7, 0x40+var_28($sp)
lw      $t4, 0x40+var_14($sp)
lw      $t5, 0x40+var_10($sp)

loc_793C0:
andi    $v0, $s1, 0x8000
beqz    $v0, loc_7931C

loc_793C8:               # jumptable 0007930C cases 5,6,19-21
andi    $v0, $s2, 0x8000
beqz    $v0, loc_792E0

loc_793D0:
move    $v0, $t7

loc_793D4:
lw      $ra, 0x40+var_8($sp)
lw      $s2, 0x40+var_18($sp)
lw      $s1, 0x40+var_1C($sp)
lw      $s0, 0x40+var_20($sp)
jr      $ra
addiu   $sp, 0x40
#endif

	return 0;
}

short GetHeight(struct FLOOR_INFO* floor, int x, int y, int z)//78C74(<), 7ACB8(<) (F)
{
	struct room_info* r;//a0
	short* fd;//s1
	short value;

#if 1//DEBUG_CAM
	return 0;
#endif

#if 1
	//s0 = floor
	//s3 = x
	OnObject = 0;
	height_type = 0;
	tiltyoff = 0;
	tiltxoff = 0;
	//s4 = z
	//loc_78D18:
	while (floor->pit_room != 0xFF)
	{
		//loc_78CB4
		if (CheckNoColFloorTriangle(floor, x, z) == 1)
		{
			break;
		}

		r = &room[floor->pit_room];
		floor = &r->floor[((z - r->z) >> 10) + (((x - r->x) >> 10) * r->x_size)];
	}
	//loc_78D28
	//t7 = floor->floor << 8
	//v0 = -32512

	if ((floor->floor << 8) == -32512)
	{
		return -32512;
	}
	//loc_78FCC
	//v1 = floor->index << 1
	trigger_index = NULL;

	//v0 = floor->floor << 8
	if ((floor->index << 1) == 0)
	{
		return (floor->floor << 8);
	}

	//s1 = floor_data
	fd = &floor_data[floor->index];

	//loc_78D60
	//s2 = *fd++;
	//v0 = s2 & 0x1F
	//v1 = v0 - 1

	switch (*fd++ & 0x1F)//CHECKME at end of loop do we *fd++ if so then leave as is
	{
	case DOOR_TYPE:
	case ROOF_TYPE:
	case SPLIT3:
	case SPLIT4:
	case NOCOLC1T:
	case NOCOLC1B:
	case NOCOLC2T:
	case NOCOLC2B:
		break;
	case TILT_TYPE:
	{
		//loc_78EA0
		//a1 = fd[1]
		//a2 = fd[0]
		//loc_78EB4
		tiltxoff = ABS(fd[1]);//v0
		tiltyoff = fd[0];

		//v0 = v0 < 3 ? 1 : 0

#if 0
		slti    $v0, 3
			beqz    $v0, loc_78EE4
			li      $v0, 2
			bgez    $a2, loc_78ED4
			move    $v0, $a2
			negu    $v0, $v0

			loc_78ED4 :
		slti    $v0, 3
			bnez    $v0, loc_78EE4
			li      $v0, 1
			li      $v0, 2

			loc_78EE4 :
			jal     sub_78FEC
			sw      $v0, 0x1C6C($gp)

			loc_78EEC : # jumptable 00078D8C cases 1, 3, 9, 10, 15 - 18
			j       loc_78FC0
			addiu   $s1, 2

			loc_78EF4:               # jumptable 00078D8C cases 6, 19 - 21
			lw      $v0, 0x1B3C($gp)
			nop
			bnez    $v0, loc_78FC0

			loc_78F00 : # jumptable 00078D8C case 5
			addiu   $v0, $s1, -2
			j       loc_78FC0
			sw      $v0, 0x1B3C($gp)
#endif
			break;
	}
	case TRIGGER_TYPE:
		//loc_78F0C
		//v0 = trigger_index
		fd++;
		if (trigger_index == NULL)
		{
			trigger_index = &fd[-1];
		}
		//loc_78F20
		//s0 = *fd++
		//v1 = (*fd++ & 0x3FFF) >> 10

		value = (*fd++ & 0x3FFF) >> 10;//v1

		if (value == 0)
		{
			//loc_78F54

		}
		else if (value == 12 || value == 1)
		{
			//loc_78F48
		}

#if 0///@? check pc for this, too complicated.
		beqz    $v1, loc_78F54
			li      $v0, 0xC
			beq     $v1, $v0, loc_78F48
			li      $v0, 1
			bne     $v1, $v0, loc_78FB8
			nop

			loc_78F48 :
		lhu     $s0, 0($s1)
			j       loc_78FB8
			addiu   $s1, 2

			loc_78F54 :
			lw      $a0, 0x1B38($gp)
			andi    $v1, $s0, 0x3FF
			sll     $v0, $v1, 7
			sll     $v1, 4
			addu    $v0, $v1
			addu    $a0, $v0
			lh      $v1, 0xC($a0)
			lh      $v0, 0x28($a0)
			li      $t0, 0x1F2480
			andi    $v0, 0x8000
			bnez    $v0, loc_78FB8
			sll     $v1, 6
			addu    $v0, $t0, $v1
			lw      $v0, 0x14($v0)
			move    $a1, $s3
			beqz    $v0, loc_78FB8
			move    $a3, $s4
			lw      $a2, 0x68 + var_48($sp)
			addiu   $at, $sp, 0x68 + var_50
			sw      $t7, 0x68 + var_50($sp)
			sw      $at, 0x68 + var_58($sp)
			jalr    $v0
			nop
			lw      $t7, 0x68 + var_50($sp)
#endif
			break;
	case LAVA_TYPE:
	{
		//loc_78F00
		trigger_index = &fd[-1];
		//j       loc_78FC0
		break;
	}
	case CLIMB_TYPE:
	case MONKEY_TYPE:
	case TRIGTRIGGER_TYPE:
	case MINER_TYPE:
	{
		//loc_78EF4
		if (trigger_index == NULL)
		{
			trigger_index = &fd[-1];
		}
		//j       loc_78FC0
		break;
	}
	case SPLIT1:
	case SPLIT2:
	case NOCOLF1T:
	case NOCOLF1B:
	case NOCOLF2T:
	case NOCOLF2B:
		//loc_78D94
		break;
	}

#if 0
	loc_78D94 : # jumptable 00078D8C cases 7, 8, 11 - 14
		li      $v0, 4
		lhu     $v1, 0($s1)
		andi    $a0, $s2, 0x1F
		sw      $v0, 0x1C6C($gp)
		andi    $t0, $v1, 0xF
		sra     $a3, $v1, 4
		andi    $a3, 0xF
		sra     $a2, $v1, 8
		andi    $a2, 0xF
		andi    $t1, $s4, 0x3FF
		andi    $t2, $s3, 0x3FF
		li      $v0, 7
		beq     $a0, $v0, loc_78DD8
		srl     $v1, 12
		addiu   $v0, $a0, -0xB
		sltiu   $v0, 2
		beqz    $v0, loc_78E08

		loc_78DD8 :
				li      $v0, 0x400
					subu    $v0, $t1
					slt     $v0, $t2
					bnez    $v0, loc_78DF8
					srl     $v0, $s2, 10
					subu    $a1, $a2, $a3
					j       loc_78E2C
					subu    $a2, $t0, $a3

					loc_78DF8 :
				srl     $v0, $s2, 5
					subu    $a1, $v1, $t0
					j       loc_78E2C
					subu    $a2, $v1, $a2

					loc_78E08 :
				slt     $v0, $t1, $t2
					bnez    $v0, loc_78E20
					srl     $v0, $s2, 10
					subu    $a1, $a2, $a3
					j       loc_78E2C
					subu    $a2, $v1, $a2

					loc_78E20 :
				srl     $v0, $s2, 5
					subu    $a1, $v1, $t0
					subu    $a2, $t0, $a3

					loc_78E2C :
				sw      $a1, 0x1ACC($gp)
					sw      $a2, 0x1AD0($gp)
					andi    $v0, 0x1F
					andi    $at, $v0, 0x10
					beqz    $at, loc_78E48
					li      $at, 0xFFFFFFF0
					or $v0, $at

					loc_78E48 :
				sll     $v0, 8
					addu    $t7, $v0
					bgez    $a1, loc_78E5C
					move    $v0, $a1
					negu    $v0, $v0

					loc_78E5C :
				slti    $v0, 3
					beqz    $v0, loc_78E90
					li      $v0, 3
					bgez    $a2, loc_78E74
					move    $v0, $a2
					negu    $v0, $v0

					loc_78E74 :
				slti    $v0, 3
					beqz    $v0, loc_78E90
					li      $v0, 3
					lw      $v1, 0x1C6C($gp)
					li      $v0, 4
					beq     $v1, $v0, loc_78E94
					li      $v0, 1

					loc_78E90:
				sw      $v0, 0x1C6C($gp)

					loc_78E94 :
					addiu   $s1, 2
					jal     sub_78FEC
					addiu   $ra, 0x120



					loc_78F0C : # jumptable 00078D8C case 4
					lw      $v0, 0x1B3C($gp)
					addiu   $s1, 2
					bnez    $v0, loc_78F20
					addiu   $v0, $s1, -4
					sw      $v0, 0x1B3C($gp)

					loc_78F20:
						lhu     $s0, 0($s1)
							addiu   $s1, 2
							andi    $v0, $s0, 0x3FFF
							srl     $v1, $v0, 10
							beqz    $v1, loc_78F54
							li      $v0, 0xC
							beq     $v1, $v0, loc_78F48
							li      $v0, 1
							bne     $v1, $v0, loc_78FB8
							nop

							loc_78F48 :
						lhu     $s0, 0($s1)
							j       loc_78FB8
							addiu   $s1, 2

							loc_78F54 :
							lw      $a0, 0x1B38($gp)
							andi    $v1, $s0, 0x3FF
							sll     $v0, $v1, 7
							sll     $v1, 4
							addu    $v0, $v1
							addu    $a0, $v0
							lh      $v1, 0xC($a0)
							lh      $v0, 0x28($a0)
							li      $t0, 0x1F2480
							andi    $v0, 0x8000
							bnez    $v0, loc_78FB8
							sll     $v1, 6
							addu    $v0, $t0, $v1
							lw      $v0, 0x14($v0)
							move    $a1, $s3
							beqz    $v0, loc_78FB8
							move    $a3, $s4
							lw      $a2, 0x68 + var_48($sp)
							addiu   $at, $sp, 0x68 + var_50
							sw      $t7, 0x68 + var_50($sp)
							sw      $at, 0x68 + var_58($sp)
							jalr    $v0
							nop
							lw      $t7, 0x68 + var_50($sp)

							loc_78FB8:
						andi    $v0, $s0, 0x8000
							beqz    $v0, loc_78F20

							loc_78FC0 :
						andi    $v0, $s2, 0x8000
							beqz    $v0, loc_78D60
							move    $v0, $t7

							loc_78FCC :
						lw      $ra, 0x68 + var_4($sp)
							lw      $s4, 0x68 + var_18($sp)
							lw      $s3, 0x68 + var_1C($sp)
							lw      $s2, 0x68 + var_20($sp)
							lw      $s1, 0x68 + var_24($sp)
							lw      $s0, 0x68 + var_28($sp)
							jr      $ra
							addiu   $sp, 0x68
#endif
#else
	UNIMPLEMENTED();
#endif
	return 0;
}
