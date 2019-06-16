#include "SPHERES.H"

#include "DRAW.H"
#include "CONTROL.H"
#include "SPECIFIC.H"

int GetSpheres(struct ITEM_INFO* item, struct SPHERE* sptr, int worldspace)
{
	UNIMPLEMENTED();
	return 0;
}

void GetJointAbsPosition(struct ITEM_INFO* item, struct PHD_VECTOR* pos, int joint)
{
	UNIMPLEMENTED();
	return;
}

int IsRoomOutside(long x, long y, long z)//(F)
{
	int v1;
	int a0;
	int v0;
	short roomOffset;//v0
	int t0;
	struct room_info* r;//s1
	short room_number;
	struct FLOOR_INFO* floor;//s0
	int h;//v1
	int c;//v0
	int i;
	//s3 = x
	//s2 = y
	//s4 = z

	v1 = x >> 12;
	a0 = z >> 12;

	v0 = v1 << 3;
	v0 -= v1;
	v0 <<= 2;
	v0 -= v1;
	v0 += a0;
	//v1 = OutsideRoomOffsets
	if (x < 0 && z < 0)
	{
		return -2;
	}

	//loc_8EF54
	roomOffset = OutsideRoomOffsets[v0];

	if (roomOffset == -1)
	{
		return -2;
	}

	t0 = roomOffset & 0x7FFF;

	if (roomOffset < 0)
	{
		r = &room[t0];

		if (y < r->maxceiling)
		{
			return -2;
		}

		if (r->minfloor < y)
		{
			return -2;
		}

		if (z < (r->z + 1024))
		{
			return -2;
		}

		if (r->z + ((r->x_size - 1) << 10) < z)
		{
			return -2;
		}

		if (x < (r->x + 1024))
		{
			return -2;
		}

		if (r->x + ((r->y_size - 1) << 10) < x)
		{
			return -2;
		}

		room_number = t0;
		floor = GetFloor(x, y, z, &room_number);
		h = GetHeight(floor, x, y, z);

		if (h == -32512 || h < y)
		{
			return -2;
		}

		c = GetCeiling(floor, x, y, z);

		if (y < c)
		{
			return -2;
		}

		if ((r->flags & (RF_FILL_WATER | RF_WIND_BLOWS_PONYTAIL)))
		{
			return 1;
		}

		return -3;
	}
	else
	{
		//loc_8EFF4
		if (OutsideRoomTable[roomOffset] == -1)
		{
			return -2;
		}

		//loc_8F000
		i = 0;
		while(i++)
		{
			r = &room[OutsideRoomTable[roomOffset]];

			if (y > r->maxceiling && r->minfloor > y &&
				z > (r->z + 1024) && r->z + ((r->x_size - 1) << 10) > z &&
				x > (r->x + 1024) && r->x + ((r->y_size - 1) << 10) > x)
			{
				//loc_8F07C
				IsRoomOutsideNo = OutsideRoomTable[roomOffset];
				room_number = IsRoomOutsideNo;
				floor = GetFloor(x, y, z, &room_number);
				h = GetHeight(floor, x, y, z);

				if (h == -32512 || h < y)
				{
					return -2;
				}

				c = GetCeiling(floor, x, y, z);

				if (y < c)
				{
					return -2;
				}

				if (r->flags & (RF_WIND_BLOWS_PONYTAIL | RF_FILL_WATER))
				{
					return 1;
				}

				return -3;

			}//loc_8F104

			if (OutsideRoomTable[roomOffset + i] == -1)
			{
				return -2;
			}
		}
	}

	return 0;
}