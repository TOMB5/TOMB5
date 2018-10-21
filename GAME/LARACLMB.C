#include "LARACLMB.H"

#include "CAMERA.H"
#include "CONTROL.H"
#include "LARA.H"
#include INPUT_H
#include "SPECIFIC.H"
#include "DRAW.H"

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
	short* data = trigger_index;

	GetHeight(GetFloor(x, y, z, &room_number), x, y, z);

	if (data == NULL)
		return 0;

	if ((*data & 0x1F) == 5)
	{
		if ((*data >> 8) & 0x80)
			return 0;

		data++;
	}

	return (*data & 0x1F) == 6 ? *data : 0;
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

		if (result_r && result_l && input & IN_FORWARD)
		{
			if (result_r < 0 || result_l < 0)
			{
				item->goal_anim_state = STATE_LARA_LADDER_IDLE;

				AnimateLara(item);

				if (abs(ledge_r - ledge_l) <= 120)
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
				item->pos.y_pos += 256 - yshift;
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
	if (!LaraCheckForLetGo(item, coll))
	{
		int shift;

		lara.move_angle = item->pos.y_rot + ANGLE(90);

		LaraDoClimbLeftRight(item, coll, LaraTestClimbPos(item, coll->radius, coll->radius + 120, -512, 512, &shift), shift);
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
	if (!LaraCheckForLetGo(item, coll))
	{
		int shift;

		lara.move_angle = item->pos.y_rot - ANGLE(90);

		LaraDoClimbLeftRight(item, coll, LaraTestClimbPos(item, coll->radius, -(coll->radius + 120), -512, 512, &shift), shift);
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

void lara_col_climbstnc(struct ITEM_INFO* item, struct COLL_INFO* coll)//464E8, 4694C
{
	UNIMPLEMENTED();
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
	UNIMPLEMENTED();
	return 0;
}

int LaraClimbLeftCornerTest(struct ITEM_INFO* item, struct COLL_INFO* coll)//45ABC, 45F20
{
	UNIMPLEMENTED();
	return 0;
}

int LaraTestClimb(int x, int y, int z, int xfront, int zfront, int item_height, int item_room, int* shift)//457F0, 45C54
{
	UNIMPLEMENTED();
	return 0;
}

int LaraTestClimbUpPos(struct ITEM_INFO* item, int front, int right, int* shift, int* ledge)//45530, 45994
{
	UNIMPLEMENTED();
	return 0;
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
