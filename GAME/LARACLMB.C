#include "LARACLMB.H"

#include "CAMERA.H"
#include "CONTROL.H"
#include "LARA.H"
#include "SPECIFIC.H"
#include INPUT_H
#include "DRAW.H"

#if PSX_VERSION || SAT_VERSION || PSXPC_VERSION
#include "GETSTUFF.H"
#endif

static short LeftIntRightExtTab[4] = // offset 0xA0B7C
{
	0x0800, 0x0100, 0x0200, 0x0400
};
static short LeftExtRightIntTab[4] = // offset 0xA0B84
{
	0x0200, 0x0400, 0x0800, 0x0100
};

short GetClimbTrigger(long x, long y, long z, short room_number)//46E38, 4729C (F)
{
	short* data = NULL;
	//s2 = x
	//s1 = y
	//s0 = z
	GetHeight(GetFloor(x, y, z, &room_number), x, y, z);
	data = trigger_index;

	//v0 = 5
	if (data != NULL)
	{
		//a1 = *data & 0x1F
		if ((*data & 0x1F) == 5)
		{
			if ((*data & 0x8000))
				return 0;
			data++;
		}
		//loc_46EAC
		//a0 = *data
		//v0 = 6
		//v1 - *data & 0x1F
		if ((*data & 0x1F) == 6)
		{
			return *data;
		}
	}
	
	//loc_46EC0
	return 0;
}

void lara_col_climbend(struct ITEM_INFO* item, struct COLL_INFO* coll)//46E30(<), 47294(<) (F)
{
	return;
}

void lara_as_climbend(struct ITEM_INFO* item, struct COLL_INFO* coll)//46DF8(<), 4725C(<) (F)
{
	coll->enable_baddie_push = FALSE;
	coll->enable_spaz = FALSE;

	camera.flags = CF_FOLLOW_CENTER;
	camera.target_angle = ANGLE(-45);
}

void lara_col_climbdown(struct ITEM_INFO* item, struct COLL_INFO* coll)//46BD0, 47034 (F)
{
	int frame;
	int yshift;
	int result_r, result_l;
	int shift_r, shift_l;

	if (LaraCheckForLetGo(item, coll) || item->anim_number != ANIMATION_LARA_LADDER_DOWN)
		return;

	frame = item->frame_number - anims[ANIMATION_LARA_LADDER_DOWN].frame_base;

	switch(frame)
	{
	case 0:
		yshift = 0;
		break;

	case 28:
	case 29:
		yshift = 256;
		break;

	case 57:
		yshift = 512;
		break;

	default:
		return;
	}
	
	item->pos.y_pos += yshift + 256;

	result_r = LaraTestClimbPos(item, coll->radius, coll->radius + 120, -512, 512, &shift_r);
	result_l = LaraTestClimbPos(item, coll->radius, -(coll->radius + 120), -512, 512, &shift_l);

	item->pos.y_pos -= 256;

	if (result_r != 0 && result_l != 0 &&
		result_r != -2 && result_l != -2 &&
		input & IN_BACK)
	{
		if (shift_r && shift_l)
		{
			if (shift_r < 0 != shift_l < 0)
			{
				item->goal_anim_state = STATE_LARA_LADDER_IDLE;
				AnimateLara(item);

				return;
			}

			if (shift_r < 0 && shift_r < shift_l ||
				shift_r > 0 && shift_r > shift_l)
			{
				shift_l = shift_r;
			}
		}

		if (result_r == -1 || result_l == -1)
		{
			item->anim_number = ANIMATION_LARA_LADDER_IDLE;
			item->frame_number = anims[ANIMATION_LARA_LADDER_IDLE].frame_base;

			item->current_anim_state = STATE_LARA_LADDER_IDLE;
			item->goal_anim_state = STATE_LARA_HANG;

			AnimateLara(item);
		}
		else
		{
			item->goal_anim_state = STATE_LARA_LADDER_DOWN;
			item->pos.y_pos -= yshift;
		}
		return;
	}

	item->goal_anim_state = STATE_LARA_LADDER_IDLE;

	if (yshift != 0)
		AnimateLara(item);
}

void lara_as_climbdown(struct ITEM_INFO* item, struct COLL_INFO* coll)//46BA4(<), 47008(<) (F)
{
	coll->enable_baddie_push = FALSE;
	coll->enable_spaz = FALSE;

	camera.target_elevation = ANGLE(-45);
}

void lara_col_climbing(struct ITEM_INFO* item, struct COLL_INFO* coll)//469B0, 46E14 (F)
{
	if (!LaraCheckForLetGo(item, coll) && item->anim_number == ANIMATION_LARA_LADDER_UP)
	{
		int frame = item->frame_number - anims[ANIMATION_LARA_LADDER_UP].frame_base;
		int yshift;
		int result_r, result_l;
		int shift_r, shift_l;
		int ledge_r, ledge_l;

		if (frame == 0)
		{
			yshift = 0;
		}
		else if(frame == 28 || frame == 29)
		{
			yshift = -256;
		}
		else if(frame == 57)
		{
			yshift = -512;
		}
		else
		{
			return;
		}

		item->pos.y_pos += yshift - 256;

		result_r = LaraTestClimbUpPos(item, coll->radius, coll->radius + 120, &shift_r, &ledge_r);
		result_l = LaraTestClimbUpPos(item, coll->radius, coll->radius + 120, &shift_l, &ledge_l);
		
		item->pos.y_pos += 256;

		if (result_r && result_l && input & IN_FORWARD)
		{
			if (result_r < 0 || result_l < 0)
			{
				item->goal_anim_state = STATE_LARA_LADDER_IDLE;

				AnimateLara(item);

				if (ABS(ledge_r - ledge_l) <= 120)
				{
					if (result_r != -1 || result_l != -1)
					{
						item->goal_anim_state = STATE_LARA_UNKNOWN_138;
						item->required_anim_state = STATE_LARA_CROUCH_IDLE;
					}
					else
					{
						item->goal_anim_state = STATE_LARA_GRABBING;
						item->pos.y_pos += (ledge_r + ledge_l) / 2 - 256;
					}
				}
			}
			else
			{
				item->goal_anim_state = STATE_LARA_LADDER_UP;
				item->pos.y_pos -= yshift;
			}
		}
		else
		{
			item->goal_anim_state = STATE_LARA_LADDER_IDLE;

			if (yshift != 0)
				AnimateLara(item);
		}
	}
}

void lara_as_climbing(struct ITEM_INFO* item, struct COLL_INFO* coll)//46984(<), 46DE8(<) (F)
{
	coll->enable_baddie_push = FALSE;
	coll->enable_spaz = FALSE;

	camera.target_elevation = ANGLE(30);
}

void lara_col_climbright(struct ITEM_INFO* item, struct COLL_INFO* coll)//46908(<), 46D6C(<) (F)
{
	int shift = 0;
	int res = 0;

	if (!LaraCheckForLetGo(item, coll))
	{
		lara.move_angle = item->pos.y_rot + ANGLE(90);

		res = LaraTestClimbPos(item, coll->radius, coll->radius + 120, -512, 512, &shift);
		LaraDoClimbLeftRight(item, coll, res, shift);
	}
}

void lara_as_climbright(struct ITEM_INFO* item, struct COLL_INFO* coll)//468B8(<), 46D1C(<) (F)
{
	coll->enable_baddie_push = FALSE;
	coll->enable_spaz = FALSE;

	camera.target_angle = ANGLE(30);
	camera.target_elevation = ANGLE(-15);

	if (!(input & (IN_RIGHT | IN_RSTEP)))
		item->goal_anim_state = STATE_LARA_LADDER_IDLE;
}

void lara_col_climbleft(struct ITEM_INFO* item, struct COLL_INFO* coll)//46834(<), 46C98(<) (F)
{
	int shift = 0;
	int res = 0;

	if (!LaraCheckForLetGo(item, coll))
	{
		lara.move_angle = item->pos.y_rot - ANGLE(90);

		res = LaraTestClimbPos(item, coll->radius, -(coll->radius + 120), -512, 512, &shift);
		LaraDoClimbLeftRight(item, coll, res, shift);
	}
}

void lara_as_climbleft(struct ITEM_INFO* item, struct COLL_INFO* coll)//467E4(<), 46C48(<) (F)
{
	coll->enable_baddie_push = FALSE;
	coll->enable_spaz = FALSE;

	camera.target_angle = ANGLE(-30);
	camera.target_elevation = ANGLE(-15);

	if (!(input & (IN_LEFT | IN_LSTEP)))
		item->goal_anim_state = STATE_LARA_LADDER_IDLE;
}

void lara_col_climbstnc(struct ITEM_INFO* item, struct COLL_INFO* coll)//464E8, 4694C (F)
{
	int result_r; // $s1
	int result_l; // $a1
	int shift_r; // stack offset -40
	int shift_l; // stack offset -32
	int ledge_r; // stack offset -36
	int ledge_l; // stack offset -28
	int v0;

	//s2 = item
	//s3 = coll
	if (!LaraCheckForLetGo(item, coll) && item->anim_number == ANIMATION_LARA_LADDER_IDLE)
	{
		//v1 = input
		if ((input & IN_FORWARD))
		{
			if (item->goal_anim_state == STATE_LARA_GRABBING)
			{
				return;
			}

			//a0 = item
			//a3 = &shift_r
			item->goal_anim_state = STATE_LARA_LADDER_IDLE;
			//a1 = coll->radius
			//v0 = &ledge_r
			//a2 = coll->radius + 120
			result_r = LaraTestClimbUpPos(item, coll->radius, coll->radius + 120, &shift_r, &ledge_r);
			//a0 = item
			//a3 = &shift_l
			//a2 = coll->radius
			//v0 = &ledge_l
			result_l = LaraTestClimbUpPos(item, coll->radius, -(coll->radius + 120), &shift_l, &ledge_l);

			if (result_r == 0 || result_l == 0)
			{
				return;
			}

			if (result_r < 0 || result_l < 0)
			{
				//v0 = ledge_l
				//v1 = ledge_r
				//a0 = ledge_l - ledge_r
				//a2 = ledge_l
				
				if (CLAMPSUB(ledge_l, ledge_r) >= 0x79)
				{
					return;
				}

				//v0 = 0x8A
				if (result_r == -1 && result_l == -1)
				{
					//v0 = 0x13
					item->goal_anim_state = STATE_LARA_GRABBING;
					//v0 = (ledge_l + ledge_r + ((ledge_l + ledge_r) >> 31)) >> 1;
					//v1 = ((ledge_l + ledge_r) >> 31);
					item->pos.y_pos += (item->pos.y_pos - 256) + (ledge_l + ledge_r + ((ledge_l + ledge_r) >> 31)) >> 1;
					return;
				}
				//loc_46620
				//v1 = 0x47
				item->goal_anim_state = STATE_LARA_UNKNOWN_138;
				item->required_anim_state = STATE_LARA_CROUCH_IDLE;

				return;
			}
			//loc_46630
			if (shift_r != 0)
			{
				if (shift_l != 0)
				{
					v0 = shift_r >> 31;
					if (shift_r >= 0)
					{
						v0 ^= 1;
					}
					//loc_4665C
					if (v0 != 0)
					{
						return;
					}

					//v1 = shift_r
					//a0 = shift_l
					if (shift_r < 0 && shift_r < shift_l ||
						shift_r > 0 && shift_l < shift_r)
					{
						//loc_46684
						shift_l = shift_r;
					}
				}
				else
				{
					//loc_46684
					shift_l = shift_r;
				}
			}
			//loc_46688
			//v0 = item->pos.y_pos
			//a0 = shift_l
			//v1 = 0x39
			//j       loc_467B4
			item->goal_anim_state = STATE_LARA_LADDER_UP;
			item->pos.y_pos += shift_l;
			return;
		}
		else if((input & IN_BACK))
		{
			//loc_46698
			if (item->goal_anim_state != STATE_LARA_HANG)
			{
				//a0 = item
				//a3 = -512
				//v0 = 0x38
				//v1 = item->pos.y_pos + 256
				//s0 = 512 sw var_30
				item->goal_anim_state = STATE_LARA_LADDER_IDLE;
				item->pos.y_pos += 256;
				//a1 = coll->left_floor2
				//v0 = &shift_r
				//a2 = coll->left_floor2 + 128
				result_r = LaraTestClimbPos(item, coll->radius, coll->radius + 120, -512, 512, &shift_r);
				//a0 = item
				//a3 = -512
				//s0 = 512
				result_l = LaraTestClimbPos(item, coll->radius, -(coll->radius + 120), -512, 512, &shift_l);

				item->pos.y_pos -= 256;
				if (result_r == 0 || result_l == 0 || result_l == -2 || result_r == -2)
				{
					return;
				}

				//v1 = shift_r
				//a0 = shift_l
				if (shift_r != 0)
				{
					//v0 = 1
					if (shift_l != 0)
					{
						v0 = shift_r >> 31;
						if (shift_l < 0)
						{
							v0 ^= 1;
						}
						//loc_4676C
						if (v0 != 0)
						{
							return;
						}

						if (shift_r < 0 && shift_r < shift_l ||
							shift_r > 0 && shift_l < shift_r)
						{
							shift_l = shift_r;
						}
						//loc_46794
					}
					//loc_4679C
				}
				//loc_46798
				if (result_r != 1 || result_l != 1)
				{
					item->goal_anim_state = STATE_LARA_HANG;
					return;
				}

				//v1 = 0x3D
				//v0 = item->pos.y_pos
				//a0 = shift_l
				item->goal_anim_state = STATE_LARA_LADDER_DOWN;
				item->pos.y_pos += shift_l;
			}
		}
		//loc_467C8
	}
	//loc_467C8
	return;
}

void lara_as_climbstnc(struct ITEM_INFO* item, struct COLL_INFO* coll)//463F0, 46854 (F)
{
	lara.IsClimbing = TRUE;

	coll->enable_spaz = FALSE;
	coll->enable_baddie_push = FALSE;

	camera.target_elevation = ANGLE(-20);

	if (input & IN_LOOK)
	{
		LookUpDown();
	}

	if (input & IN_LEFT || input & IN_LSTEP)
	{
		item->goal_anim_state = STATE_LARA_LADDER_LEFT;

		lara.move_angle = item->pos.y_rot - ANGLE(90);
	}
	else if (input & IN_RIGHT || input & IN_RSTEP)
	{
		item->goal_anim_state = STATE_LARA_LADDER_RIGHT;

		lara.move_angle = item->pos.y_rot + ANGLE(90);
	}
	else if (input & IN_JUMP)
	{
		if (item->anim_number == ANIMATION_LARA_LADDER_IDLE)
		{
			item->goal_anim_state = STATE_LARA_JUMP_BACK;

			lara.gun_status = LG_NO_ARMS;
			lara.move_angle = item->pos.y_rot - ANGLE(180);
		}
	}
}

int LaraTestClimbPos(struct ITEM_INFO* item, int front, int right, int origin, int height, int* shift)//462F8, 4675C (F)
{
	const int angle = (unsigned short)(item->pos.y_rot + ANGLE(45)) >> 14;
	int x = 0;
	int z = 0;
	int xfront = 0;
	int zfront = 0;

	switch (angle)
	{
	case 0:
		x = item->pos.x_pos + right;
		z = item->pos.z_pos + front;
		zfront = 256;
		break;

	case 1:
		x = item->pos.x_pos + front;
		z = item->pos.z_pos - right;
		xfront = 256;
		break;

	case 2:
		x = item->pos.x_pos - right;
		z = item->pos.z_pos - front;
		zfront = -256;
		break;

	case 3:
	default:
		x = item->pos.x_pos - front;
		z = item->pos.z_pos + right;
		xfront = -256;
		break;
	}

	return LaraTestClimb(x, item->pos.y_pos + origin, z, xfront, zfront, height, item->room_number, shift);
}

void LaraDoClimbLeftRight(struct ITEM_INFO* item, struct COLL_INFO* coll, int result, int shift)//46100, 46564 (F)
{
	if (result == 1)
	{
		if (input & IN_LEFT)
		{
			item->goal_anim_state = STATE_LARA_LADDER_LEFT;
		}
		else if (input & IN_RIGHT)
		{
			item->goal_anim_state = STATE_LARA_LADDER_RIGHT;
		}
		else
		{
			item->goal_anim_state = STATE_LARA_LADDER_IDLE;
		}

		item->pos.y_pos += shift;

		return;
	}

	if (result != 0)
	{
		item->goal_anim_state = STATE_LARA_HANG;

		do
		{
			AnimateItem(item);
		} while (item->current_anim_state != STATE_LARA_HANG);

		item->pos.x_pos = coll->old.x;
		item->pos.z_pos = coll->old.z;

		return;
	}

	item->pos.x_pos = coll->old.x;
	item->pos.z_pos = coll->old.z;

	item->goal_anim_state = STATE_LARA_LADDER_IDLE;
	item->current_anim_state = STATE_LARA_LADDER_IDLE;

	if (coll->old_anim_state != STATE_LARA_LADDER_IDLE)
	{
		item->anim_number = ANIMATION_LARA_LADDER_IDLE;
		item->frame_number = anims[ANIMATION_LARA_LADDER_IDLE].frame_base;

		return;
	}

	if (input & IN_LEFT)
	{
		const int flag = LaraClimbLeftCornerTest(item, coll);

		if (flag)
		{
			if (flag <= 0)
			{
				item->anim_number = ANIMATION_LARA_LADDER_AROUND_LEFT_INNER_BEGIN;
				item->frame_number = anims[ANIMATION_LARA_LADDER_AROUND_LEFT_INNER_BEGIN].frame_base;

				item->goal_anim_state = STATE_LARA_CLIMB_CORNER_LEFT_INNER;
				item->current_anim_state = STATE_LARA_CLIMB_CORNER_LEFT_INNER;
			}
			else
			{
				item->anim_number = ANIMATION_LARA_LADDER_AROUND_LEFT_OUTER_BEGIN;
				item->frame_number = anims[ANIMATION_LARA_LADDER_AROUND_LEFT_OUTER_BEGIN].frame_base;

				item->goal_anim_state = STATE_LARA_CLIMB_CORNER_LEFT_OUTER;
				item->current_anim_state = STATE_LARA_CLIMB_CORNER_LEFT_OUTER;
			}

			return;
		}
	}
	else if (input & IN_RIGHT)
	{
		const int flag = LaraClimbRightCornerTest(item, coll);

		if (flag)
		{
			if (flag <= 0)
			{
				item->anim_number = ANIMATION_LARA_LADDER_AROUND_RIGHT_INNER_BEGIN;
				item->frame_number = anims[ANIMATION_LARA_LADDER_AROUND_RIGHT_INNER_BEGIN].frame_base;

				item->goal_anim_state = STATE_LARA_CLIMB_CORNER_RIGHT_INNER;
				item->current_anim_state = STATE_LARA_CLIMB_CORNER_RIGHT_INNER;
			}
			else
			{
				item->anim_number = ANIMATION_LARA_LADDER_AROUND_RIGHT_OUTER_BEGIN;
				item->frame_number = anims[ANIMATION_LARA_LADDER_AROUND_RIGHT_OUTER_BEGIN].frame_base;

				item->goal_anim_state = STATE_LARA_CLIMB_CORNER_RIGHT_OUTER;
				item->current_anim_state = STATE_LARA_CLIMB_CORNER_RIGHT_OUTER;
			}

			return;
		}
	}

	item->anim_number = coll->old_anim_number;
	item->frame_number = coll->old_frame_number;

	AnimateLara(item);
}

int LaraClimbRightCornerTest(struct ITEM_INFO* item, struct COLL_INFO* coll)//45DE4, 46248
{
	int x; // $s1
	int z; // $s0
	int shift; // stack offset -48
	int flag; // $s6
	int oldx; // $s7
	int oldz; // $s4
	short oldy; // $fp
	short angle; // $s3

	//s2 = item
	//arg_4 = coll
	//v1 = item->anim_number
	flag = 0;
	if (item->anim_number != ANIMATION_LARA_LADDER_RIGHT)
	{
		return 0;
	}
	//loc_45E30
	//v0 = (item->pos.y_rot + 0x2000) & 0xFFFF
	oldx = item->pos.x_pos;
	oldy = item->pos.y_rot;
	oldz = item->pos.z_pos;
	angle = ((item->pos.y_rot + 0x2000) & 0xFFFF) >> 14;

	//v1 = -1024
	if (angle == 0 || angle == 2)
	{
		//loc_45E5C
		//v0 = item->pos.x_pos & -1024;
		//a0 = item->pos.z_pos & 1023;
		x = (item->pos.x_pos & -1024) + (item->pos.z_pos & 1023);
		//v1 = (item->pos.z_pos & -1024)
		//v0 = (item->pos.x_pos & 1023)
		z = (item->pos.z_pos & -1024) + (item->pos.x_pos & 1023);
	}
	else
	{
		//loc_45E7C
		//v0 = ((item->pos.x_pos & -1024) + 1024)
		//a0 = (item->pos.z_pos & 1023)
		x = ((item->pos.x_pos & -1024) + 1024) - (item->pos.z_pos & 1023);
		//v1 = ((item->pos.z_pos & -1024) + 1024)
		//v0 = item->pos.x_pos & 1023
		z = ((item->pos.z_pos & -1024) + 1024) - (item->pos.x_pos & 1023);
	}
	//loc_45E9C
	//s5 = (item->pos.z_pos & 1023)
	//GetClimbTrigger(x, item->pos.y_pos, z, item->room_number);
	//v1 = angle << 1
	//a0 = &LeftExtRightIntTab[angle]
	//a1 = LeftExtRightIntTab[angle]
	//var_2C = angle << 1
	if (LeftExtRightIntTab[angle] & GetClimbTrigger(x, item->pos.y_pos, z, item->room_number))
	{
		//a0 = item
		//a1 = lara
		item->pos.x_pos = x;
		lara.CornerX = x;
		item->pos.z_pos = z;
		lara.CornerZ = z;
		item->pos.y_pos += 0x4000;
		lara.move_angle = item->pos.y_pos;
		//v1 = 0x200
		//var_38 = 0x200
		//v1 = coll
		//a3 = -512
		//a1 = coll->radius
		//v0 = &shift
		//var_34 = &shift
		//a2 = coll->radius + 120
		flag = LaraTestClimbPos(item, coll->radius, coll->radius + 120, -512, 512, &shift);
		if (flag != 0)
		{
			//loc_45F40
			flag = -1;
		}
	}
	//loc_45F34
	if (flag == 0)
	{
		//a0 = 0xA0000
		//loc_45F40
		//v0 = lara
		item->pos.x_pos = oldx;
		lara.move_angle = oldy;
		item->pos.y_rot = oldy;
		item->pos.z_pos = oldz;
		if (angle != 2)
		{
			if (angle >= 3)
			{
				//loc_45F78
				if (angle == 3)
				{
					//loc_45FA4
					//a2 = -1024
					//a0 = (item->pos.x_pos & 1023)
					//a1 = -1024
					//v1 = (oldz + 1024) & -1024
					//v0 = (item->pos.x_pos & -1024) - 1024
					x = ((item->pos.x_pos & -1024) - 1024) + (item->pos.z_pos & 1023);
					z = ((oldz + 1024) & -1024) + (item->pos.x_pos & 1023);
					//j       loc_46024
				}
				else
				{
					//loc_45FFC
					//a2 = -1024
					//a1 = item->pos.x_pos
					//v0 = (((item->pos.z_pos) & -1024) - 1024)
					//a0 = (item->pos.x_pos + 1024) & -1024
					//v1 = (item->pos.z_pos & 1023)
					x = ((item->pos.x_pos + 1024) & -1024) + (item->pos.z_pos & 1023);
					z = (((item->pos.z_pos) & -1024) - 1024) + (item->pos.x_pos & 1023);
				}
			}
			else if (angle == 0)
			{
				//loc_45F88
				//a2 = -1024
				//a0 = item->pos.x_pos & 1023
				//a1 = -1024
				//v1 = (((oldz + 1024) & -1024) + 1024)
				//v0 = ((item->pos.x_pos + 1024) & -1024) + 1024;
				//loc_45FE4
				x = (((item->pos.x_pos + 1024) & -1024) + 1024) - (item->pos.z_pos & 1023);
				z = (((oldz + 1024) & -1024) + 1024) - (item->pos.x_pos & 1023);
				//j loc_46024

			}
			else
			{
				//loc_45FFC
				//a2 = -1024
				//a1 = item->pos.x_pos
				//v0 = (((item->pos.z_pos) & -1024) - 1024)
				//a0 = (item->pos.x_pos + 1024) & -1024
				//v1 = (item->pos.z_pos & 1023)
				x = ((item->pos.x_pos + 1024) & -1024) + (item->pos.z_pos & 1023);
				z = (((item->pos.z_pos) & -1024) - 1024) + (item->pos.x_pos & 1023);
			}
		}
		else
		{
			//loc_45FCC
			//a0 = item->pos.x_pos & 1023
			//a1 = -1024
			//v1 = ((oldz - 1024) & -1024) + 1024
			//v0 = ((item->pos.x_pos - 1024) & -1024) + 1024;

			//loc_45FE4
			x = (((item->pos.x_pos - 1024) & -1024) + 1024) - (item->pos.z_pos & 1023);
			z = (((oldz - 1024) & -1024) + 1024) - (item->pos.x_pos & 1023);
			//j loc_46024
		}

		//loc_46024
		//a0 = x
		//a1 = item->pos.y_pos
		//a3 = item->pos.room_number
		//a2 = z
		//a0 = LeftIntRightExtTab[angle]

		if (LeftIntRightExtTab[angle] & GetClimbTrigger(x, item->pos.y_pos, z, item->room_number))
		{
			//a0 = item
			//a1 = &lara
			item->pos.x_pos = x;
			lara.CornerX = x;
			item->pos.z_pos = z;
			lara.CornerZ = z;
			//v0 = item->pos.y_rot - 0x4000
			//v1 = 512
			//var_38 = 512
			item->pos.y_rot -= 0x4000;
			lara.move_angle = item->pos.y_rot;
			//v1 = coll
			//a3 = -512
			//a1 = coll->radius
			//v0 = &shift
			//var_34 = &shift
			//a2 = coll->radius + 120
			flag = LaraTestClimbPos(item, coll->radius, coll->radius + 120, -512, 512, &shift);

			if (flag)
			{
				flag = 1;
			}
		}
		//loc_460B4
	}

	item->pos.x_pos = oldx;
	lara.move_angle = oldy;
	item->pos.y_rot = oldy;
	item->pos.z_pos = oldz;

	//loc_460B8
	return flag;
}

int LaraClimbLeftCornerTest(struct ITEM_INFO* item, struct COLL_INFO* coll)//45ABC, 45F20
{
	UNIMPLEMENTED();
	return 0;
}

int LaraTestClimb(int x, int y, int z, int xfront, int zfront, int item_height, int item_room, int* shift)//457F0, 45C54
{
	int hang; // stack offset -48
	struct FLOOR_INFO* floor; // $s3
	short room_number; // stack offset -56
	short room_number2; //stack -52
	int height; // $s2
	int ceiling; // $v1

	//s5 = shift
	//v0 = 1
	//s7 = x
	//s4 = y
	//fp = z
	*shift = 0;
	//s0 = item_height
	//v1 = lara.climb_status
	//v0 = item_room
	//s1 = xfront
	room_number2 = item_room;
	if (lara.climb_status != FALSE)
	{
		room_number = room_number2;
		floor = GetFloor(x, y - 128, z, &room_number);
		height = GetHeight(floor, x, y, z);

		//v0 = height - 128
		if (height != -32512)
		{
			//v1 = y + item_height
			height = (height - 128) - (y + item_height);

			if (height >= -0x46)
			{
				//s6 = v1
				//a0 = floor
				if (height >= -0x46 < 0)
				{
					*shift = height;
				}

				//loc_458B8
				ceiling = GetCeiling(floor, x, y, z) - y;

				if (ceiling < 0x47)
				{
					//v0 = item_height - height
					if (ceiling > 0)
					{
						if (*shift != 0)
						{
							return FALSE;
						}

						*shift = ceiling;
					}

					//loc_458F8
					//s0 = x + xfront
					if ((item_height + height) < 0x384)
					{
						hang = 0;
					}
					//loc_45908
					floor = GetFloor(x + xfront, y, z + zfront, &room_number);
					height = GetHeight(floor, x + xfront, y, z + zfront);

					if (height != -32512)
					{
						height -= y;
					}
					//loc_45954
					if (height >= 0x47)
					{
						ceiling = GetCeiling(floor, x + xfront, y, z + zfront) - y;
						if (ceiling >= 0x200)
						{
							return TRUE;
						}

						if (ceiling >= 0x1BB)
						{
							//loc_45A60
							if (*shift > 0)
							{
								if (hang)
								{
									return -1;
								}
								else
								{
									return 0;
								}
							}
							else
							{
								*shift = ceiling - 0x200;
							}
						}
						else if (ceiling > 0)
						{
							//loc_45A78
							if (hang)
							{
								return -1;
							}
							else
							{
								return 0;
							}
						}
						else if (ceiling < -0x45 || hang == 0 || *shift > 0)
						{
							return 0;
						}
						else if (ceiling < *shift)
						{
							*shift = ceiling;
						}

						return -1;
					}
	
					//a0 = s7
					if (height > 0)//loc_459CC
					{
						if (*shift < 0)
						{
							return 0;
						}
						else if (*shift < height)
						{
							*shift = height;
						}
					}//loc_459F4
					//a0 = s7
					//a1 = s6
					//a2 = fp
					//v1 = room_number2
					room_number = room_number2;
					GetFloor(x, y + item_height, z, &room_number);
					ceiling = GetCeiling(GetFloor(x + xfront, y + item_height, z + zfront, &room_number), x + xfront, y + item_height, z + zfront);

					if (ceiling == -32512 || height >= ceiling - y || ceiling - y >= 0x200 )
					{
						return 1;
					}
					
					if (ceiling - y < 0x1BB)
					{
						if (hang)
						{
							return -1;
						}
						else
						{
							return 0;
						}
					}
					else
					{
						//loc_45A60
						//v0 = *shift
						if (*shift > 0)
						{
							if (hang)
							{
								return -1;
							}
							else
							{
								return 0;
							}
						}
						else
						{
							*shift = ceiling - 0x200;
							return 1;
						}
					}
				}
				//loc_45A8C
			}//loc_45A88
		}//loc_45A88
	}

	return 0;
}

int LaraTestClimbUpPos(struct ITEM_INFO* item, int front, int right, int* shift, int* ledge)//45530, 45994 (F)
{
	struct FLOOR_INFO* floor; // $fp
	short room_number; // stack offset -48
	int angle; // $v1
	int x; // $s3
	int y; // $s5
	int z; // $s4
	int height; // $s2
	int ceiling; // $v1
	int xfront; // $s0
	int zfront; // $s2

	xfront = 0;
	zfront = 0;

	//s7 = item
	//v0 = item->pos.y_pos
	//v1 = item->pos.y_rot
	y = item->pos.y_pos - 768;
	angle = (((item->pos.y_rot + ANGLE(45)) & 0xFFFF) >> 14);

	switch (angle)
	{
	case 0:
		//loc_455B8
		zfront = 4;
		z = item->pos.z_pos + front;
		x = item->pos.x_pos + right;
		break;
	case 1:
		//loc_455D0
		xfront = 4;
		//v0 = item->pos.x_pos;
		//v1 = item->pos.z_pos
		x = item->pos.x_pos + front;
		z = item->pos.z_pos - right;
		break;
	case 2:
		//loc_455E8
		zfront = -4;
		//v0 = item->pos.z_pos
		//v1 = item->pos.x_pos
		z = item->pos.z_pos - front;
		x = item->pos.x_pos - right;
		break;
	default:
		//loc_45600
		xfront = -4;
		//v0 = item->pos.x_pos
		//v1 = item->pos.z_pos
		x = item->pos.x_pos - front;
		z = item->pos.z_pos + right;
		break;
	}

	//loc_45610
	*shift = 0;
	room_number = item->room_number;
	ceiling = GetCeiling(GetFloor(x, y, z, &room_number), x, y, z) + 256 - y;
	
	if (ceiling >= 0x47)
	{
		return 0;
	}

	//s1 = x + xfront
	if (ceiling > 0)
	{
		*shift = ceiling;
	}
	//loc_45678
	floor = GetFloor(x + xfront, y, z + zfront, &room_number);
	height = GetHeight(floor, x + xfront, y, z + zfront);
	//s6 = z + zfront
	if (height == -32512)
	{
		*ledge = height;
		return 1;
	}
	//loc_456C4
	height -= y;
	//v1 = *ledge
	*ledge = height;

	if (height >= 0x81)
	{
		ceiling = GetCeiling(floor, x + xfront, y, z + zfront) - y;
		if (ceiling >= 512)
		{
			return 1;
		}

		//v1 = height - ceiling
		if (height - ceiling >= 0x2FB)
		{
			*shift = height;
			return -1;
		}
		else if (height - ceiling >= 0x200)
		{
			*shift = height;
			return -2;
		}
	}
	//loc_45734
	//a0 = x
	if (height > 0)
	{
		//v0 = *shift
		if (*shift < height)
		{
			*shift = height;
		}
	}
	//loc_45760
	//s0 = y + 512

	//loc_45764
	room_number = item->room_number;
	GetFloor(x, y + 512, z, &room_number);
	ceiling = GetCeiling(GetFloor(x + xfront, y + 512, z + zfront, &room_number), x + xfront, y + 512, z + zfront) - y;

	if (height < ceiling)
	{
		return ceiling < 512 ? 1 : 0 ^ 1;
	}

	//loc_457BC
	return 1;
}

long LaraCheckForLetGo(struct ITEM_INFO* item, struct COLL_INFO* coll)//45434, 45898 (F)
{
	short room_number = item->room_number;

	item->gravity_status = FALSE;
	item->fallspeed = 0;

	GetHeight(GetFloor(item->pos.x_pos, item->pos.y_pos, item->pos.z_pos, &room_number),
		item->pos.x_pos, item->pos.y_pos, item->pos.z_pos);

	coll->trigger = trigger_index;

	if (input & IN_ACTION && item->hit_points > 0)
		return 0;

	lara.torso_y_rot = 0;
	lara.torso_x_rot = 0;

	lara.head_y_rot = 0;
	lara.head_x_rot = 0;

	item->goal_anim_state = STATE_LARA_JUMP_FORWARD;
	item->current_anim_state = STATE_LARA_JUMP_FORWARD;
	item->anim_number = ANIMATION_LARA_FREE_FALL_FORWARD;
	item->frame_number = anims[ANIMATION_LARA_FREE_FALL_FORWARD].frame_base;

	item->speed = 2;
	item->gravity_status = TRUE;
	item->fallspeed = 1;

	lara.gun_status = LG_NO_ARMS;

	return 1;
}
