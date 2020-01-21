#include "COLLIDE_S.H"

#include "CAMERA.H"
#include "COLLIDE.H"
#include "CONTROL.H"
#include "LARA.H"
#include "DRAW.H"
#include "GAMEFLOW.H"
#include "SPECIFIC.H"
#include "GETSTUFF.H"
#include "ROOMLOAD.H"
#include "SETUP.H"

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
	short room_number;//var_18

	room_number = item->room_number;
	item->floor = GetHeight(GetFloor(item->pos.x_pos, item->pos.y_pos + height, item->pos.z_pos, &room_number), lara_item->pos.x_pos, item->pos.y_pos + height, lara_item->pos.z_pos);
	if (item->room_number != room_number)
	{
		ItemNewRoom(lara.item_number, room_number);
	}//loc_7C5F4
}

void ItemNewRoom(short item_num, short room_number)
{
	UNIMPLEMENTED();
}

int FindGridShift(int a0, int a1)
{
	int v1 = a0 >> 10;
	int v0 = a1 >> 10;

	if (v1 == v0)
	{
		return 0;
	}
	//loc_7BA4C
	a0 &= 0x3FF;
	if (v1 >= v0)
	{
		return a0 ^ -1;///@TODO check nor
	}
	else
	{
		return 1025 - a0;
	}
}

int CollideStaticObjects(struct COLL_INFO* coll, long xpos, long ypos, long zpos, short room_number/*arg_10*/, long objheight /*arg_14*/)
{
	short var_48;
	struct room_info* r;//$v0
	int s2;
	int s1;
	int s0;
	int a2;
	short* door;//$a0
	short t5;//t5
	short a1;
	int t4;
	int t9;
	int scratchPad[1024];
	short* t0 = (short*)&scratchPad[0];
	short* t8;
	struct room_info* r2;
	struct MESH_INFO* t1;
	struct static_info* static_mesh;//$t0
	int t3;
	int t2;
	int a0;
	int v1;
	int t6;
	int t7;

	//v1 = room_number
	t9 = 1;
	//s3 = coll
	//s4 = ypos
	coll->hit_static = 0;
	//a0 = room
	r = &room[room_number];
	var_48 = room_number;
	door = r->door;
	//v0 = coll->radius
	//v1 = objheight
	t0[0] = room_number;///@FIXME check if correct room_number is loaded here caller has multiple
	s2 = xpos - coll->radius;
	s1 = xpos + coll->radius;
	s0 = ypos - objheight;
	a2 = zpos - coll->radius;
	zpos += coll->radius;

	if (door != NULL)
	{
		t5 = *door++;
		if (t5 > 0)
		{
			//loc_7BADC
			do
			{
				t4 = 0;
				t0 = (short*)&scratchPad[0];
				a1 = *door;

				//loc_7BAE8
				do
				{
					if (*t0++ == a1)
					{
						break;
					}

					t4++;

				} while (t4 < t9);
				//loc_7BB08
				//t0 = $sp
				t0 = (short*)&scratchPad[0];
				if (t4 == t9)
				{
					t0[t9++] = a1;
				}//loc_7BB20
				door += 16;
			} while (--t5 > 0);
		}
		//loc_7BB2C
	}
	//loc_7BB2C
	t5 = 0;
	t8 = (short*)&scratchPad[0];

	//loc_7BB34
	do
	{
		//v0 = t8[0]
		r2 = &room[t8[0]];

		t4 = r2->num_meshes;
		t1 = r2->mesh;
		//a1 = static_objects

		if (t4 > 0)
		{
			//loc_7BB60
			do
			{
				//at = t1->Flags & 1
				//v0 = t1->static_number

				if ((t1->Flags & 0x1))
				{
					static_mesh = &static_objects[t1->static_number];
					//t6 = static_mesh->z_minc
					//t7 = static_mesh->z_maxc
					//at = static_mesh->x_maxc
					//v0 = static_mesh->x_minc
					//t2 = t1->x
					//v1 = t1->z
					//v1 = t1->y_rot
					//a0 = 16384
					//a0 = -32768
					if (t1->y_rot == 16384)
					{
						//loc_7BBC8
						t3 = t1->x + static_mesh->z_minc;
						t2 = t1->x + static_mesh->z_maxc;
						a0 = t1->y_rot - static_mesh->x_maxc;
						v1 = t1->y_rot - static_mesh->x_minc;
					}
					else if (t1->y_rot == -32768)
					{
						//loc_7BBDC
						t3 = t1->x - static_mesh->x_maxc;
						t2 = t1->x - static_mesh->x_minc;
						a0 = t1->y_rot - static_mesh->z_maxc;
						v1 = t1->y_rot - static_mesh->z_minc;
					}
					else if (t1->y_rot == -16384)
					{
						//loc_7BBF0
						t3 = t1->x - static_mesh->z_maxc;
						t2 = t1->x - static_mesh->z_minc;
						a0 = t1->y_rot - static_mesh->x_minc;
						v1 = t1->z - static_mesh->x_maxc;
					}
					else
					{
						t3 = t1->x + static_mesh->x_minc;
						t2 = t1->x + static_mesh->x_maxc;
						a0 = t1->z + static_mesh->z_minc;
						v1 = t1->y_rot + static_mesh->z_maxc;
					}

					//loc_7BC00
					//t6 = static_mesh->y_minc
					//v0 = t1->y
					//t7 = static_mesh->y_maxc
					t6 = t1->y + static_mesh->y_minc;
					t7 = t1->y + static_mesh->y_maxc;

					if (t3 < s1 && s2 < t2 && t6 < ypos && s0 < t7 && a0 < zpos && a2 < v1)
					{
						coll->hit_static = 1;
						return 1;
					}
				}
				//loc_7BC50

				t4--;
				t1++;
			} while (t4 > 0);
		}
		//loc_7BC5C
		t5++;
		t8++;
	} while (t5 < t9);

	return 0;
}

///@ret $s1
int sub_7B948(struct COLL_INFO* coll/*s5*/, long x /*s3*/, long y/*s6*/, long z/*s4*/, short* room_number /*a3*/, long ypos/*arg_78*/, int objheight, short* ceiling /*a2*/)
{
	struct FLOOR_INFO* floor;//$s2
	short height;//$s1

	//s0 = ra
	floor = GetFloor(x, y, z, room_number);
	height = GetHeight(floor, x, y, z);

	//v1 = ypos

	if (height != -32512)
	{
		height -= ypos;
	}
	//loc_7B988
	*ceiling = GetCeiling(floor, x, y, z);

	//v1 = ypos
	if (*ceiling != -32512)
	{
		*ceiling -= objheight;
	}

	//loc_7B9B0
	//a0 = height_type
	//v1 = coll->flags
	//at = 1
	//v0 = a0 - 2
	//v0 = -32512
	if (coll->slopes_are_walls == 1 && (unsigned)height_type - 2 < 2 && height < 0)
	{
		//loc_7BA28
		return -32512;
	}
	//loc_7B9DC
	if (coll->slopes_are_pits && (unsigned)height_type - 2 < 2 && height > 0)
	{
		return 512;
	}//loc_7B9FC

	if (coll->lava_is_pit && height > 0 && trigger_index != NULL)
	{
		if ((trigger_index[0] & 0x1F) == 5)
		{
			return 512;
		}
	}
	
	return height;
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
		if((y + 512) >= (f->floor << 8))
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

void GetCollisionInfo(struct COLL_INFO* coll, long xpos, long ypos, long zpos, short room_number, long objheight)
{
	int fp;
	short room_num;//0x70+var_58
	short var_56;//0x70+var_56
	int room_num2;//0x70+var_54
	struct FLOOR_INFO* floor;//$s2
	int y;//0x70+var_38
	short height;//$s1
	short ceiling;//$a2
	int var_2C;//0x70+var_2C
	unsigned short tilt_type;//$v0
	int s0;//$s0
	int s7;//$s7
	int var_50;//0x70+var_50
	int var_44;//0x70+var_44
	int var_30;
	int var_34;
	int var_5C;
	short var_60;
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
	coll->coll_type = 0;
	coll->shift.x = 0;
	coll->shift.y = 0;
	coll->shift.z = 0;
	coll->quadrant = ((coll->facing + 8192) & 0xFFFF) >> 14;
	//at = room_number
	//a0 = xpos
	//v0 = ypos - objheight
	//v1 = objheight - ypos
	//a2 = zpos
	//s6 = (ypos - objheight) - 160
	//a1 = s6
	room_num2 = room_number;
	room_num = room_number;
	y = ypos - objheight;
	floor = GetFloor(xpos, (ypos - objheight) - 160, zpos, &room_num);
	height = GetHeight(floor, xpos, (ypos - objheight) - 160, zpos);

	if (height != -32512)
	{
		height -= ypos;
	}
	//loc_7B2F4
	ceiling = GetCeiling(floor, xpos, (ypos - objheight) - 160, zpos);
	var_2C = ((ypos - 160) - objheight) - lara_item->fallspeed;

	if (ceiling != -32512)
	{
		ceiling -= y;
	}
	//loc_7B328
	//v0 = height_type
	//v1 = trigger_index
	//a3 = lara_item
	coll->mid_floor = height;
	coll->mid_ceiling = ceiling;
	coll->mid_type = height_type;
	coll->trigger = trigger_index;
	tilt_type = GetTiltType(floor, xpos, lara_item->pos.y_pos, zpos);
	//v1 = tile_type >> 8
	coll->tilt_x = tilt_type;//&0xFF
	coll->tilt_z = tilt_type >> 8;

	//at = coll->quadrant
	//v0 = coll->facing
	//v1 = coll->radius
	//a0 = rcossin_tbl
	//v0 = rcossin_tbl[coll->facing]

	if (coll->quadrant == 0)
	{
		//loc_7B3BC
		var_50 = -coll->radius;
		var_44 = coll->radius;
		zfront = coll->radius;
		s7 = coll->radius;
		s0 = coll->radius;
		xfront = (SIN(coll->facing) * -coll->radius) >> W2V_SHIFT;
	}
	else if (coll->quadrant - 1 == 0)
	{
		//loc_7B3E0
		var_50 = coll->radius;
		var_44 = -coll->radius;
		xfront = coll->radius;
		s0 = coll->radius;
		s7 = coll->radius;
		zfront = (COS(coll->facing) * coll->radius) >> W2V_SHIFT;
	}
	else if (coll->quadrant - 2 == 0)
	{
		//loc_7B404
		var_50 = coll->radius;
		var_44 = -coll->radius;
		zfront = coll->facing;
		s7 = coll->facing;
		s0 = coll->facing;
		xfront = (SIN(coll->facing) * coll->radius) >> W2V_SHIFT;
	}
	else if (coll->quadrant - 3 == 0)
	{
		//loc_7B434
		var_50 = -coll->radius;
		var_44 = coll->radius;
		xfront = -coll->radius;
		s0 = -coll->radius;
		s7 = -coll->radius;
		zfront = (COS(coll->facing) * coll->radius) >> W2V_SHIFT;
	}
	else
	{
		s0 = 0;
		s7 = 0;
		var_50 = 0;
		var_44 = 0;
		zfront = 0;
		xfront = 0;
	}

	//v0 = xfront
	//s3 = xpos + xfront
	//v1 = zfront
	//s4 = zpos + zfront

	if (fp)
	{
		room_num = room_number;
 	}
	//loc_7B488
	floor = GetFloor(xpos + xfront, (ypos - objheight) - 160, zpos + zfront, &room_num);
	height = GetHeight(floor, xpos + xfront, (ypos - objheight) - 160, zpos + zfront);

	if (height != -32512)
	{
		height -= ypos;
	}
	//loc_7B4CC
	ceiling = GetCeiling(floor, xpos + xfront, var_2C, zpos + zfront);

	if (ceiling != -32512)
	{
		ceiling -= y;
	}
	//v0 = height_type
	coll->front_ceiling = ceiling;
	coll->front_floor = height;
	coll->front_type = height_type;
	//a0 = xfront
	//a1 = ypos - 160
	//a2 = zfront

	floor = GetFloor(xpos + xfront + xfront, (ypos - objheight) - 160, zpos + zfront + zfront, &room_num);

	//a1 = xfront
	//a3 = zfront
	height = GetHeight(floor, xpos + xfront + xfront, (ypos - objheight) - 160, zpos + zfront + zfront);
	if (height != -32512)
	{
		height -= ypos;
	}
	//loc_7B558
	//a0 = coll->flags
	//a1 = coll->front_type
	//a2 = coll->front_floor
	//a3 = coll->mid_floor

	//v0 = -32767
	if (coll->slopes_are_walls && (unsigned)coll->front_type - 2 < 2 &&
		coll->front_floor < coll->mid_floor && height < coll->front_floor &&
		coll->front_floor < 0)
	{
		//loc_7B5E0
		coll->front_floor = -32767;
	}
	//loc_7B598
	//v0 = 0x200
	else if (coll->slopes_are_pits && (unsigned)coll->front_type - 2 < 2 &&
		coll->mid_floor < coll->front_floor)
	{
		//loc_7B5E0
		coll->front_floor = 512;
	}
	else if (coll->lava_is_pit && coll->front_floor > 0 && trigger_index != NULL)//loc_7B5B4
	{
		if ((trigger_index[0] & 0x1F) == 5)
		{
			coll->front_floor = 512;
		}
	}
	//loc_7B5E4
	//v1 = xpos
	//a0 = var_50
	//v0 = zpos
	//at = room_num2
	//s3 = xpos + var_50
	//s4 = zpos + s0
	var_56 = room_num2;
	height = sub_7B948(coll, xpos + var_50, (ypos - objheight) - 160, zpos + s0, &var_56, ypos, y, &ceiling);
	coll->left_floor = height;
	coll->left_ceiling = ceiling;
	coll->left_type = height_type;

	height = sub_7B948(coll, xpos + var_50, (ypos - objheight) - 160, zpos + s0, &room_num, ypos, y, &ceiling);
	coll->left_floor2 = height;
	coll->left_ceiling2 = ceiling;
	coll->left_type2 = height_type;

	var_34 = xpos + var_50;
	var_30 = zpos + s0;

	//v0 = xpos
	//v1 = zpos
	//a0 = var_44
	//at = room_num2

	//s3 = xpos + s7
	//s4 = zpos + var_44
	var_56 = room_num2;
	//a3 = &var_56
	height = sub_7B948(coll, xpos + s7, ypos - 160, zpos + var_44, &var_56, ypos, y, &ceiling);
	coll->right_floor = height;
	coll->right_ceiling = ceiling;
	coll->right_type = height_type;

	height = sub_7B948(coll, xpos + s7, ypos - 160, zpos + var_44, &room_num, ypos, y, &ceiling);
	coll->right_floor2 = height;
	coll->right_ceiling2 = ceiling;
	coll->right_type2 = height_type;

	//s1 = xpos + s7
	//s0 = zpos + var_44
	//a1 = xpos
	//a2 = ypos
	//v0 = room_num
	//a3 = zpos
	//v1 = objheight
	//a0 = coll
	var_5C = objheight;
	var_60 = room_num;
	CollideStaticObjects(coll, xpos, ypos, zpos, room_number, objheight);

	//t0 = xpos
	//t1 = zpos
	//t2 = coll->quadrant
	//v0 = coll->mid_floor

	//at = 1
	if (coll->mid_floor == -32512)
	{
		//loc_7B6BC
		coll->coll_type = 1;
		coll->shift.x = coll->old.x - xpos;
		coll->shift.y = coll->old.y - ypos;
		coll->shift.z = coll->old.z - zpos;
		return;
	}
	else
	{
		//loc_7B6EC
		//v1 = coll->mid_ceiling
		//at = coll->mid_floor - coll->mid_ceiling
		if ((coll->mid_floor - coll->mid_ceiling) <= 0)
		{
			//loc_7B6BC
			coll->coll_type = 32;
			coll->shift.x = coll->old.x - xpos;
			coll->shift.y = coll->old.y - ypos;
			coll->shift.z = coll->old.z - zpos;
			return;
		}
		else if (coll->mid_ceiling >= 0)
		{
			coll->shift.y = coll->mid_ceiling;
			coll->coll_type = 8;
			coll->hit_ceiling = 1;
		}

		//loc_7B720
		//v0 = coll->front_floor
		//a2 = coll->bad_pos
		//a1 = coll->bad_neg
		//v1 = coll->front_ceiling
		//a0 = coll->bad_ceiling
		//slt     $at, $v1, $a0
		if (coll->bad_pos < coll->front_floor || coll->front_floor < coll->bad_neg ||
			coll->bad_ceiling < coll->front_ceiling)
		{
			//loc_7B750
			//v0 = (unsigned)(coll->front_type - 3) < 2
			//v0 = 1
			if ((unsigned)(coll->front_type - 3) < 2)
			{
				//loc_7B768
				coll->shift.x = coll->old.x - xpos;
				coll->shift.z = coll->old.z - zpos;
				coll->coll_type = 1;
				return;
			}
			//loc_7B788
			if (coll->quadrant == 0)
			{
				//loc_7B7B0
				coll->shift.x = coll->old.x - xpos;
				FindGridShift(zpos + zfront, zpos);
				coll->coll_type = 1;
				return;
			}
			else if (coll->quadrant - 1 == 0)
			{
				//loc_7B7D4
				coll->shift.x = FindGridShift(xpos + xfront, xpos);
				coll->shift.z = coll->old.z + zpos;
				coll->coll_type = 1;
				return;
			}
			else if (coll->quadrant - 2 == 0)
			{
				//loc_7B7B0
				coll->shift.x = coll->old.x - xpos;
				FindGridShift(zpos + zfront, zpos);
				coll->coll_type = 1;
				return;
			}
			else if (coll->quadrant - 3 == 0)
			{
				//loc_7B7D4
				coll->shift.x = FindGridShift(xpos + xfront, xpos);
				coll->shift.z = coll->old.z - zpos;
				coll->coll_type = 1;
				return;
			}
			else
			{
				coll->coll_type = 1;
				return;
			}
		}
		else if (coll->front_ceiling >= coll->bad_ceiling)
		{
			//loc_7B6BC
			coll->coll_type = 16;
			coll->shift.x = coll->old.x - xpos;
			coll->shift.y = coll->old.y - ypos;
			coll->shift.z = coll->old.z - zpos;
			return;
		}

		//loc_7B7F8
		//v1 = coll->left_floor
		//v0 = coll->left_ceiling
		if (coll->bad_pos < coll->left_floor || coll->left_floor < coll->bad_neg ||
			coll->bad_ceiling < coll->left_ceiling)
		{
			//v1 = coll->left_type
			if (coll->left_type == 4)
			{
				//loc_7B768
				coll->shift.x = coll->old.x - xpos;
				coll->shift.z = coll->old.z - zpos;
				coll->coll_type = 2;
				return;
			}
			else if (coll->quadrant == 0)
			{
				//loc_7B85C
				coll->shift.x = FindGridShift(var_34, xpos - xfront);
				coll->coll_type = 2;
				return;
			}
			else if (coll->quadrant - 1 == 0)
			{
				//loc_7B874
				coll->shift.z = FindGridShift(var_30, zpos - zfront);
				coll->coll_type = 2;
				return;
			}
			else if (coll->quadrant - 2 == 0)
			{
				//loc_7B85C
				coll->shift.x = FindGridShift(var_34, xpos - xfront);
				coll->coll_type = 2;
				return;

			}
			else if (coll->quadrant - 3 == 0)
			{
				//loc_7B874
				coll->shift.z = FindGridShift(var_30, zpos - zfront);
				coll->coll_type = 2;
				return;
			}
			else
			{
				coll->coll_type = 2;
				return;
			}
		}
		//loc_7B88C
		//v1 = coll->right_floor
		//v0 = coll->right_ceiling

		if (coll->bad_pos < coll->right_floor || coll->right_floor < coll->bad_neg ||
			coll->bad_ceiling < coll->right_ceiling)
		{
			//loc_7B8B0
			//v1 = coll->right_type
			//v0 = 4
			if (coll->right_type == 4)
			{
				//loc_7B768
			}
			else if (coll->quadrant == 0)
			{
				//loc_7B8E8
				coll->bad_ceiling = FindGridShift(xpos + s7, xpos + xfront);
				coll->coll_type = 4;
				return;
			}
			else if (coll->quadrant - 1 == 0)
			{
				//loc_7B900
				coll->shift.z = FindGridShift(zpos + var_44, zpos + zfront);
				coll->coll_type = 4;
				return;
			}
			else if (coll->quadrant - 2 == 0)
			{
				//loc_7B8E8
				coll->bad_ceiling = FindGridShift(xpos + s7, xpos + xfront);
				coll->coll_type = 4;
				return;
			}
			else if (coll->quadrant - 3 == 0)
			{
				//loc_7B900
				coll->shift.z = FindGridShift(zpos + var_44, zpos + zfront);
				coll->coll_type = 4;
				return;
			}
			else
			{
				coll->coll_type = 4;
				return;
			}
		}
		//loc_7B918
	}
	//loc_7B918
	return;
}
