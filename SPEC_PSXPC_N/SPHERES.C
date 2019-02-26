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

int IsRoomOutside(long x, long y, long z)
{
	//s3 = x
	//s2 = y
	//s4 = z

	//v1 = x >> 12;
	//a0 = z >> 12;

	///@TODO take actual PSX code really. this is PC stuff
	short off, room_num;
	struct FLOOR_INFO* floor;
	short height, ceiling;
	struct room_info* r;

	if (x < 0 || z < 0)
		return -2;

	off = OutsideRoomOffsets[(z / 4096) + 27 * (x / 4096)];

	if (off == -1)
		return -2;

	if (off >= 0)
	{
		char* ptr = &OutsideRoomTable[off];


		if (*ptr == -1)
			return -2;

		while (TRUE)
		{
			r = &room[*ptr];
			if (y >= r->maxceiling && y <= r->minfloor)
			{
				if (z >= r->z + 1024 && z <= (r->x_size / 1024) + r->z - 1024)
				{
					if (x >= r->x + 1024 && x <= (r->y_size / 1024) + r->x - 1024)
						break;
				}
			}
			ptr++;

			if (*ptr == -1)
				return -2;
		}

		IsRoomOutsideNo = room_num = *ptr;
	}
	else
	{
		r = &room[off & 0x7fff];

		if (y < r->maxceiling || y > r->minfloor)
			return -2;

		if (z < r->z + 1024 || z > r->x_size / 1024 + r->z - 1024)
			return -2;

		if (x < r->x + 1024 || x > r->y_size / 1024 + r->x - 1024)
			return -2;

		IsRoomOutsideNo = room_num = off & 0x7fff;
	}

	floor = GetFloor(x, y, z, &room_num);

	height = GetHeight(floor, x, y, z);
	if (height == -32512 || y > height)
		return -2;

	ceiling = GetCeiling(floor, x, y, z);

	if (y >= ceiling)
		return (r->flags & RF_WIND_BLOWS_PONYTAIL || r->flags & RF_FILL_WATER) ? 1 : -3;

	return -2;
}