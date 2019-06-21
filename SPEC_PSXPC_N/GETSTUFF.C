#include "GETSTUFF.H"

#include "ROOMLOAD.H"
#include "SPECIFIC.H"

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
	return 0;
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

long CheckNoColFloorTriangle(struct FLOOR_INFO* floor, long x, long z)
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

	//v0 = 0x400//1024?
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

long CheckNoColCeilingTriangle(struct FLOOR_INFO* floor, long x, long z)
{
	return 0;
}

struct FLOOR_INFO* GetFloor(long x, long y, long z, short* room_number)
{
	struct room_info* room;
	struct FLOOR_INFO* floor;
	int v1;
	int dz;
	int dx;
	int a1;
	int a0;
	char door;
	int v0;

loc_78974:
	room = &room[*room_number];

	dz = ((z - room->z) >> 10);
	dx = ((x - room->x) >> 10);

	if (dz > 0)
	{
		//loc_789B4
		if (dz < (room->x_size & 0xFFFF) - 1)
		{
			//loc_789EC
			if (dx >= 0)
			{
				//loc_789FC
				if (dx > (room->x_size >> 16))
				{
					v1 = (room->x_size & 0xFFFF) - 1;
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
			a0 = (room->x_size >> 16) - 2;

			if ((room->x_size >> 16) - 2 < dx)
			{
				v1 = (room->x_size >> 16) - 2;
			}
		}
		else
		{
			//loc_789CC
			v1 = 1;
		}
	}
	else if (dx > 0)
	{
		dz = 0;
		//loc_789D4
		a0 = (room->x_size >> 16) - 2;

		if ((room->x_size >> 16) - 2 < dx)
		{
			v1 = (room->x_size >> 16) - 2;
		}
	}
	else
	{
		v1 = 1;
	}

	floor = &room->floor[dz + (v1 * (room->x_size & 0xFFFF))];
	door = GetDoor(floor);

	//v1 = door
	if (door != -1)
	{
		*room_number = door;
		goto loc_78974;
	}

	//loc_78A50
	if (y > floor->floor << 8)
	{
loc_78A68:
		if (floor->pit_room == -1)
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
		room = &room[floor->pit_room];
		floor = &room->floor[((z - room->z) >> 10) + room->x * ((x - room->x) >> 10)];

		if (y < floor->floor << 8)
		{
			return floor;
		}

		goto loc_78A68;

	}//loc_78BB0

	//loc_78B1C

	while (y < floor->ceiling << 8)
	{
		if (floor->sky_room == -1)
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
		*room_number = floor->sky_room;
		room = &room[floor->sky_room];
		floor = &room->floor[((z - room->z) >> 10) + ((x - room->x) >> 10) * room->x_size];
	}

	return floor;
}
