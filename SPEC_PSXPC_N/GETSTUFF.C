#include "GETSTUFF.H"

#include "DRAW.H"
#include "CONTROL.H"
#include "OBJECTS.H"
#include "ROOMLOAD.H"
#include "SPECIFIC.H"
#include "TEXT_S.H"
#include "SETUP.H"

#include <assert.h>

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

	if ((v1 & 0x1F) == 2 || (unsigned)((v1 & 0x1F) - 7) < 2 || (unsigned)((v1 & 0x1F) - 11) < 4)
	{
		if ((v1 & 0x8000))
		{
			return -1;
		}

		v1 = fd[1];
		fd += 2;
	}
	//loc_78828
	if ((v1 & 0x1F) == 3 || (unsigned)((v1 & 0x1F) - 9) < 2 || (unsigned)((v1 & 0x1F) - 15) < 4)
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
	if ((v1 & 0x1F) == 1)
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
	unsigned short* fd;//$v1
	unsigned short data;//$v1

	x &= 0x3FF;

	if (!floor->index)
	{
		return 0;
	}

	fd = (unsigned short*)&floor_data[floor->index];
	data = fd[0];

	z &= 0x3FF;

	if ((unsigned)((data & 0x1F) - 0xB) >= 4)
	{
		return 0;
	}

	if ((data & 0x1F) == 0xB)
	{
		if (0x400 - z >= x)
		{
			return -1;
		}
	}

	//loc_78C24
	if ((data & 0x1F) == 0xC)
	{
		if (0x400 - z < x)
		{
			return -1;
		}
	}

	//loc_78C40
	if ((data & 0x1F) == 0xD)
	{
		if (z >= x)
		{
			return -1;
		}
	}

	//loc_78C54
	if ((data & 0x1F) == 0xE)
	{
		if (z < x)
		{
			return -1;
		}
	}

	return 1;
}

long CheckNoColCeilingTriangle(struct FLOOR_INFO* floor, long x, long z)//(F)
{
	unsigned short* fd;//$v1
	unsigned short data;//$a0

	x &= 0x3FF;

	if (!floor->index)
		return 0;

	fd = (unsigned short*)&floor_data[floor->index];
	data = fd[0];

	z &= 0x3FF;

	if ((data & 0x1F) == 2 || (unsigned)((data & 0x1F) - 7) < 2 || (unsigned)((data & 0x1F) - 0xB) < 4)
	{
		//loc_788C0
		if ((data & 0x8000))
		{
			return 0;
		}

		data = fd[2];
	}
	
	//loc_788D4
	if ((unsigned)((data & 0x1F) - 0xF) >= 4)
	{
		return 0;
	}

	if ((data & 0x1F) == 0xF)
	{
		if ((0x400 - z) >= x)
		{
			return -1;
		}
	}

	//loc_78904
	if ((data & 0x1F) == 0x10)
	{
		if ((0x400 - z) < x)
		{
			return -1;
		}
	}

	//loc_78920
	if ((data & 0x1F) == 0x11)
	{
		if (z >= x)
		{
			return -1;
		}
	}

	//loc_78934
	if ((data & 0x1F) == 0x12)
	{
		if ((z < x))
		{
			return -1;
		}
	}

	//loc_78948
	return 1;
}

struct FLOOR_INFO* GetFloor(long x, long y, long z, short* room_number)//(F)
{
	struct room_info* r = NULL;
	struct FLOOR_INFO* floor = NULL;//$t1
	int dz;
	int dx;
	char door;//$a0
	int v0;

	//loc_78974:
	do
	{
		r = &room[*room_number];//$t2
		dz = ((z - r->z) >> 10);//$a1
		dx = ((x - r->x) >> 10);//$v1

		if (dz > 0)
		{
			if (dz < (r->x_size - 1))
			{
				//loc_789EC
				if (dx >= 0)
				{
					//loc_789FC
					if (!(dx < (r->y_size)))
					{
						dx = (r->y_size) - 1;
					}
				}
				else
				{
					//j loc_78A0C
					dx = 0;
				}
			}
			else if (dx > 0)
			{
				//loc_789D4
				dz = r->x_size - 1;

				if ((((r->y_size) - 2) < dx))
				{
					dx = ((r->y_size) - 2);
				}
			}
			else
			{
				dz = r->x_size - 1;
				dx = 1;
			}
		}
		else if (dx <= 0)
		{
			//loc_789CC
			dz = 0;
			dx = 1;
		}
		else
		{
			//loc_789D4
			dz = 0;
			if (!(((r->y_size) - 2) < dx))
			{
				dx = ((r->y_size) - 2);
			}
		}

		//loc_78A0C
		floor = &r->floor[dz + (dx * r->x_size)];
		door = GetDoor(floor);

		if (door != -1)
		{
			*room_number = door;
		}
	} while (door != -1);

	//loc_78A50
	if (y >= floor->floor << 8)
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
			if (y >= room->minfloor)
			{
				return floor;
			}
		}
		//loc_78AAC
		*room_number = floor->pit_room;
		r = &room[floor->pit_room];
		//v0 = z - v0
		floor = &r->floor[(((x - r->x) >> 10) * r->x_size) + ((z - r->z) >> 10)];	
		
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
			if (y >= r->y)
			{
				return floor;
			}
		}

		//loc_78B60
		*room_number = floor->sky_room;
		r = &room[floor->sky_room];
		floor = &r->floor[(((z - r->z) >> 10) + (((x - r->x) >> 10)) * r->x_size)];
	
	} while (y < (floor->ceiling << 8));

	return floor;
}

void GC_adjust_height(unsigned char a0, unsigned char a1, unsigned char a2, int t4, int t5, int* t7/*ret*/)
{
	int v0;

	v0 = t5 & 0x3FF;
	if (a1 < 0)
	{
		v0 = (v0 * a1) >> 2;
		*t7 += v0;
	}

	//loc_79408
	v0 = 0x3FF;
	v0 -= t5;
	v0 &= 0x3FF;
	v0 = (v0 * a1) >> 2;
	t7 -= v0;

	//loc_79424
	v0 = 0x3FF;
	if (a2 < 0)
	{
		v0 -= t4;
		v0 &= 0x3FF;
		v0 = (v0 * a2) >> 2;
		t7 += v0;
		return;
	}
	//loc_79448
	v0 = t4 & 0x3FF;
	v0 = (v0 * a2) >> 2;
	t7 -= v0;
	return;
}

short GetCeiling(struct FLOOR_INFO* floor, int x, int y, int z)
{
	struct room_info* r;//$a0
	struct FLOOR_INFO* f;//$s0
	unsigned short* fd;//$s0
	unsigned short a0;
	unsigned short v1;
	int a1;
	int a2;
	int t7;
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
	t7 = f->ceiling << 8;
	//v1 = f->index << 1
	//v0 = -32512

	if ((f->ceiling << 8) != -32512)
	{
		if(f->index != 0)
		{
			//s0 = floor_data
			//v0 = 2
			fd = (unsigned short*)&floor_data[f->index];
			a0 = *fd++;
			if ((a0 & 0x1F) != 2 || (a0 & 0x1F) - 7 < 2 || (a0 & 0x1F) - 11 < 4)
			{
				//loc_79154
				if ((a0 & 0x8000))
				{
					a0 = fd[1];
					fd += 2;
					//s2 = a0 & 0x1F
					///goto loc_792BC;
				}
				else
				{
					a0 = fd[1];
					fd += 2;
					//s2 = a0 & 0x1F
				}
			}
			//loc_7916C
			if ((a0 & 0x1F) == 3)
			{
				//loc_7924C
				//Below todo pass as args
				///lb      $a1, 1($s0)
				///j       loc_79244
				///lb      $a2, 0($s0)
				GC_adjust_height(a0, ((char*)&fd)[1], ((char*)&fd)[0], x, z, &t7);
				//j loc_792BC
			}
			else if ((a0 & 0x1F) - 9 < 2 || (a0 & 0x1F) - 15 < 4)
			{
				//loc_7918C
				//a2 = x & 0x3FF
				v1 = fd[0];
				//a1 = z & 0x3FF
				//t1 = -(fd[0] & 0xF)
				//t0 = -((fd[0] >> 4) & 0xF);
				//a3 = -((fd[0] >> 8) & 0xF);
				//v1 = -(fd[0] >> 12);
				//v0 = 9

				if ((a0 & 0x1F) == 9 || (a0 & 0x1F) - 15  < 2)
				{
					//loc_791D4
					//v0 = (1024 - (z & 1023));
					if ((1024 - (z & 1023)) < (x & 1023))
					{
						//loc_791F8
						a0 >>= 5;
						a1 = -(fd[0] >> 12) - -(fd[0] & 0xF);
						a2 = -(fd[0] & 0xF) - -((fd[0] >> 4) & 0xF);
						//j       loc_79228
					}
					else
					{
						//loc_791F8
						a0 >>= 10;
						a1 = -((fd[0] >> 8) & 0xF) - -((fd[0] >> 4) & 0xF);
						a2 = -(fd[0] >> 12) - -((fd[0] >> 8) & 0xF);
						//j       loc_79228
					}
				}//loc_79204
				else if (z & 0x3FF < x & 0x3FF)
				{
					//loc_79220
					a0 >>= 5;
					a1 = -(fd[0] >> 12) - -(fd[0] & 0xF);
					a2 = -(fd[0] >> 12) - -((fd[0] >> 8) & 0xF);
				}
				else
				{
					a0 >>= 10;
					a1 = -((fd[0] >> 8) & 0xF) - -((fd[0] >> 4) & 0xF);
					a2 = -(fd[0] & 0xF) - -((fd[0] >> 4) & 0xF);
				}
				//loc_79228
				a0 &= 0x1F;

				if ((a0 & 0x10))
				{
					a0 |= -0x10;
				}
				//loc_7923C
				a0 <<= 8;
				t7 += a0;

				GC_adjust_height(a0, a1, a2, x, z, &t7);
				//j loc_792BC
			}
		}
		//loc_792BC
		//v1 = floor->pit_room
		f = floor;
		while (f->pit_room != 0xFF)
		{
			//loc_79258
			if (CheckNoColFloorTriangle(floor, x, z) == 1)
			{
				break;
			}

			r = &room[f->pit_room];
			f = &r->floor[((z - r->z) >> 10) + ((x - r->x) >> 10) * r->x_size];
		}
		//loc_792CC
		//v0 = floor->index
		//v1 = floor_data
		if (floor->index == 0)
		{
			return t7;
		}

		fd = (unsigned short*)&floor_data[floor->index];

loc_792E0:
		unsigned short s2 = *fd++;
		unsigned short v0 = (s2) & 0x1F;
		unsigned short s1;

		switch (v0)
		{
		case 1:
		case 2:
		case 3:
		case 7:
		case 8:
		case 9:
		case 10:
		case 11:
		case 12:
		case 13:
		case 14:
		case 15:
		case 16:
		case 17:
		case 18:
			//loc_79314
			//j loc_793C8
			break;
		case 4:
			//loc_79318
			fd++;
loc_7931C:
			s1 = *fd++;
			v0 = s1 & 0x3FFF;

			//v0 = 0xC
			if ((v0 >> 10) != 0)
			{
				if ((v0 >> 10) == 0xC || (v0 >> 10) == 0x1)
				{
					//loc_79344
					s1 = *fd++;
				}
			}
			else
			{
				//loc_79350
				//a0 = items
				v1 = s1 & 0x3FF;
				struct ITEM_INFO* item = &items[s1 & 0x3FF];//$a0
				//v0 = item->flags & 0x8000
				//v1 = item->object_number

				if (!(item->flags & 0x8000))
				{
					struct object_info* object = &objects[item->object_number];

					if (object->ceiling != NULL)
					{
						///@CHECKME args?!?!?
						object->ceiling(item, x, y, z, NULL);
					}
				}//loc_793C0
			}
			//loc_793C0

			if (!(s1 & 0x8000))
				goto loc_7931C;

		case 5:
		case 6:
		case 19:
		case 20:
		case 21:
			//loc_793C8
			if (!(s2 & 0x8000))
				goto loc_792E0;
			break;
		}

		//loc_793D0
		return t7;

	}//loc_793D4

	return -32512;
}

void WE_GOT_AN_ERROR()
{
	assert(0);
}

void GH_adjust_height(int a1, int s4, short* t7, int a2, int s3)
{
	int v0;

	v0 = s4 & 0x3FF;
	if (a1 < 0)
	{
		v0 = (v0 * a1) >> 2;
		*t7 -= v0;
	}

	//loc_79008
	v0 = 0x3FF;
	v0 -= s4;
	v0 &= 0x3FF;
	v0 *= a1;
	v0 >>= 2;
	*t7 += v0;

	//loc_79024
	v0 = s3 & 0x3FF;
	if (a2 < 0)
	{
		v0 = (v0 * a2) >> 2;
		*t7 -= v0;
		return;
	}//loc_79040

	v0 = 0x3FF;
	v0 -= s3;
	v0 &= 0x3FF;
	v0 = (v0 * a2) >> 2;
	*t7 += v0;
}

short GetHeight(struct FLOOR_INFO* floor, int x, int y, int z)//78C74(<), 7ACB8(<) (F)
{
	struct room_info* r;//$a0
	struct FLOOR_INFO* f;//$s0
	unsigned short* fd;//$s1
	unsigned short value;//$s2
	short ret;//$t7 @ret
	unsigned short trigger_value;//$s0
	struct ITEM_INFO* item;//$a0
	struct object_info* object;//$v0
	int height;
	unsigned short v1;//$v1

	//s0 = floor
	//s3 = x
	OnObject = 0;
	height_type = 0;
	tiltyoff = 0;
	tiltxoff = 0;
	//s4 = z
	f = floor;

	//loc_78CB4
	while (f->pit_room != 0xFF)
	{
		if (CheckNoColFloorTriangle(f, x, z) == 1)
			break;//loc_78D28

		r = &room[f->pit_room];
		f = &r->floor[((z - r->z) >> 10) + (((x - r->x) >> 10) * r->x_size)];
	}

	//loc_78D28
	ret = f->floor << 8;
	//v0 = -32512

	if ((f->floor << 8) == -32512)
	{
		return ret;
	}

	//v1 = f->index
	//v1 <<= 1;
	trigger_index = NULL;

	if (f->index == 0)
	{
		return ret;
	}

	fd = (unsigned short*)&floor_data[f->index];

	//loc_78D60
	do
	{
		value = *fd++;

		//v0 = value & 0x1F
		//v1 = v0 - 1
		//v0 = v1 < 0x15 ? 1 : 0
		//v0 = v1 << 2

		switch ((value & 0x1F))
		{
		case DOOR_TYPE:
		case ROOF_TYPE:
		case SPLIT3:
		case SPLIT4:
		case NOCOLC1T:
		case NOCOLC1B:
		case NOCOLC2T:
		case NOCOLC2B://COMPLETE
		{
			//loc_78EEC
			fd++;
			break;
		}
		case TILT_TYPE://COMPLETE
		{
			//loc_78EA0
			unsigned char a1 = ((unsigned char*)fd)[1];
			unsigned char a2 = ((unsigned char*)fd)[0];

			//loc_78EB4
			tiltxoff = a1;
			tiltyoff = a1;

			if (ABS(a1) < 3)
			{
				if (ABS(a2) < 3)
				{
					height_type = 1;
					GH_adjust_height(a1, z, &ret, a2, x);
				}
				else
				{
					height_type = 2;
					GH_adjust_height(a1, z, &ret, a2, x);
				}
			}
			else
			{
				//loc_78EE4
				height_type = 2;
				GH_adjust_height(a1, z, &ret, a2, x);
			}
			fd++;
			break;
		}
		case TRIGGER_TYPE://COMPLETE
		{
			//loc_78F0C
			fd++;

			if (trigger_index == 0)
			{
				trigger_index = (short*)&fd[-2];
			}
			//loc_78F20
			do
			{
				trigger_value = *fd++;

				if (((trigger_value & 0x3FFF) >> 10) == 0xC || ((trigger_value & 0x3FFF) >> 10) == 0x1)
				{
					trigger_value = *fd++;
					continue;
				}
				//loc_78F54
				item = &items[trigger_value & 0x3FF];

				if (!(item->flags & 0x8000))
				{
					object = &objects[item->object_number];

					if (object->floor != NULL)
					{
						object->floor(item, x, y, z, &height);
					}//loc_78FB8
				}//loc_78FB8
			} while (!(trigger_value & 0x8000));
			break;
		}
		case LAVA_TYPE://COMPLETE
		{
			//loc_78F00
			trigger_index = (short*)--fd;
			break;
		}
		case CLIMB_TYPE:
		case MONKEY_TYPE:
		case TRIGTRIGGER_TYPE:
		case MINER_TYPE://COMPLETE
		{
			//loc_78EF4
			if (trigger_index == NULL)
			{
				trigger_index = (short*)&fd[-1];
			}
			break;
		}
		case SPLIT1:
		case SPLIT2:
		case NOCOLF1T:
		case NOCOLF1B:
		case NOCOLF2T:
		case NOCOLF2B:
		{
			//loc_78D94
			//v0 = 4
			v1 = *fd;
			//a0 = value & 0x1F;
			height_type = 4;
			int t0 = v1 & 0xF;
			int a3 = (v1 >> 4) & 0xF;
			int a2 = (v1 >> 8) & 0xF;
			int t1 = z & 0x3FF;
			int t2 = x & 0x3FF;
			//v0 = 7
			int a1;
			int v0;

			v1 >>= 12;
			if ((value & 0x1F) == 7 || (value & 0x1F) - 11 < 2)
			{
				//loc_78DD8
				v0 = value >> 10;
				if (0x400 - t1 < t2)
				{
					//loc_78DF8
					a1 = a2 - a3;
					a2 = t0 - a3;
					//j loc_78E2C
				}
				else
				{
					//loc_78DF8
					v0 = value >> 5;
					a1 = v1 - t0;
					a2 = v1 - a2;
					//j loc_78E2C
				}
			}
			else
			{
				//loc_78E08
				v0 = value >> 10;
				if (t1 < t2)
				{
					//loc_78E20
					a1 = a2 - a3;
					a2 = v1 - a2;
					//j       loc_78E2C
				}
				else
				{
					v0 = value >> 5;
					a1 = v1 - t0;
					a2 = t0 - a3;
				}
			}

			//loc_78E2C
			tiltxoff = a1;
			tiltyoff = a2;

			v0 &= 0x1F;

			int at = -16;
			if ((v0 & 0x10))
			{
				v0 |= at;
			}
			//loc_78E48
			v0 <<= 8;
			ret += v0;

			if (!(ABS(a1) < 3))
			{
				//loc_78E90
				height_type = 3;
			}
			else if(!(ABS(2) < 3))
			{
				//loc_78E90
				height_type = 3;
			}
			else if (height_type != 4)
			{
				height_type = 1;
			}

			//loc_78E94
			fd++;
			GH_adjust_height(a1, z, &ret, a2, x);
			break;
		}
		default:
			WE_GOT_AN_ERROR();
			break;
		}

		//loc_78FC0
	} while (!(value & 0x8000));

	return ret;
}
