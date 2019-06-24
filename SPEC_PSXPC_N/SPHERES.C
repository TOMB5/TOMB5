#include "SPHERES.H"

#include "DRAW.H"
#include "CONTROL.H"
#include "SPECIFIC.H"
#include "GETSTUFF.H"
#include "GTEREG.H"
#include "LOAD_LEV.H"
#include "SETUP.H"
#include "MATHS.H"
#include <assert.h>

int GetSpheres(struct ITEM_INFO* item, struct SPHERE* sptr, int worldspace)
{
	UNIMPLEMENTED();
	return 0;
}

void GetJointAbsPosition(struct ITEM_INFO* item, struct PHD_VECTOR* pos, int joint)//8E860(<) 908A4(<) (F)
{
	struct object_info* object;//s1
	short* frames[2];//var_38
	int rate;//var_30
	int frac;//s0
	long* bone;//s0
	short* frameptr;//var_2C
	short* frameptr2;//var_28
	short* item_data;
	int t0;
	int t1;
	int t2;
	struct MATRIX3D* mat;//var_24

	object = &objects[item->object_number];
	mat = Matrix;
	frac = GetFrames(item, frames, &rate);
	mPushUnitMatrix();
	mSetTrans(0, 0, 0);
	mRotYXZ(item->pos.y_rot, item->pos.x_rot, item->pos.z_rot);

	item_data = (short*)item->data;
	bone = &bones[object->bone_index];
	
	if (frac == 0)
	{
		frameptr = &frames[0][9];
		mTranslateXYZ(frames[0][6], frames[0][7], frames[0][8]);
		mRotSuperPackedYXZ(&frameptr, 0);

		if (joint > 0)
		{
			//loc_8E92C
			do
			{
				if ((*bone & 1))
				{
					mPopMatrix();
				}//loc_8E94C

				if ((*bone & 2))
				{
					mPushMatrix();
				}
				//loc_8E95C
				mTranslateXYZ(bone[1], bone[2], bone[3]);
				mRotSuperPackedYXZ(&frameptr, 0);

				if (item_data != NULL && (*bone & 0x1C))
				{
					if ((*bone & 0x8))
					{
						mRotY(*item_data++);
					}

					//loc_8E9A0
					if ((*bone & 0x4))
					{
						mRotX(*item_data++);
					}

					//loc_8E9B8
					if ((*bone & 0x10))
					{
						mRotZ(*item_data++);
					}
				}

				bone += 4;

			} while (--joint);
		}
		//loc_8E9D8
		mTranslateXYZ(pos->x, pos->y, pos->z);///@FIXME reporting bad matrix here.
	}
	else
	{
		//Math functions not impl
		assert(0);
#if 0
		//loc_8E9EC
		//a2 = &iMatrixStack[16];
		InitInterpolation(frac, rate, &iMatrixStack[16]);
		//v1 = frames[0]
		//t0 = frames[1]

		//v0 = &frames[0][9]
		frameptr = &frames[0][9];

		//v0 = &frames[1][9]
		iTranslateXYZ2(frames[0][6], frames[0][7], frames[0][8], frames[1][6], frames[1][7], frames[1][8]);
		mRotSuperPackedYXZ(&frameptr, 0);
		//iRotSuperPackedYXZ(&frameptr + 1, 0);

		//s1 = joint
		if (joint > 0)
		{
			//loc_8EA5C
			do
			{
				if ((*bone & 1))
				{
					iPopMatrix();
				}//loc_8EA7C

				if ((*bone & 2))
				{
					iPushMatrix();
				}
				//loc_8EA8C
				iTranslateXYZ(bone[1], bone[2], bone[3]);
				mRotSuperPackedYXZ(&frameptr, 0);
				iRotSuperPackedYXZ(&frameptr2, 0);

				if (item->data != NULL && (*bone & 0x1C) && (*bone & 0x8))
				{
					mRotY(*item_data);
					iRotY(*item_data++);
				}//loc_8EAE8

				if ((*bone & 0x4))
				{
					mRotX(*item_data);
					iRotX(*item_data++);
				}

				if ((*bone & 0x10))
				{
					mRotZ(*item_data);
					iRotZ(*item_data++);
				}
				bone += 4;
			} while (joint--);
		}//loc_8EB38
		iTranslateXYZ(pos->x, pos->y, pos->z);
		InterpolateMatrix();
#endif
	}

	pos->x = item->pos.x_pos + TRX;
	pos->y = item->pos.y_pos + TRY;
	pos->z = item->pos.z_pos + TRZ;

	Matrix = mat;
	mCopyMatrix(mat);

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