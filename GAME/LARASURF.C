#include "LARASURF.H"

#include "CAMERA.H"
#include "COLLIDE.H"
#include "CONTROL.H"
#include "DRAW.H"
#include "LARA.H"
#include "LARAFIRE.H"

#include INPUT_H

#include "SPECIFIC.H"
#include "LARASWIM.H"


void lara_col_surftread(struct ITEM_INFO* item, struct COLL_INFO* coll)//4DDBC(<), 4E220(<) (F)
{
	if (item->goal_anim_state == STATE_LARA_UNDERWATER_FORWARD)
	{
		item->goal_anim_state = STATE_LARA_UNDERWATER_DIVING;
		item->anim_number = ANIMATION_LARA_FREE_FALL_TO_UNDERWATER_ALTERNATE;
		item->pos.x_rot = ANGLE(-45);
		item->frame_number = anims[ANIMATION_LARA_FREE_FALL_TO_UNDERWATER_ALTERNATE].frame_base;
		item->fallspeed = 80;
		lara.water_status = LW_UNDERWATER;
	}
	lara.move_angle = item->pos.y_rot;
	LaraSurfaceCollision(item, coll);
}

void lara_col_surfright(struct ITEM_INFO* item, struct COLL_INFO* coll)//4DD90(<), 4E1F4(<) (F)
{
	lara.move_angle = item->pos.y_rot + ANGLE(90);
	LaraSurfaceCollision(item, coll);
}

void lara_col_surfleft(struct ITEM_INFO* item, struct COLL_INFO* coll)//4DD64(<), 4E1C8(<) (F)
{
	lara.move_angle = item->pos.y_rot - ANGLE(90);
	LaraSurfaceCollision(item, coll);
}

void lara_col_surfback(struct ITEM_INFO* item, struct COLL_INFO* coll)//4DD38(<), 4E19C(<) (F)
{
	lara.move_angle = item->pos.y_rot - ANGLE(180);
	LaraSurfaceCollision(item, coll);
}

void lara_col_surfswim(struct ITEM_INFO* item, struct COLL_INFO* coll)//4DCE8(<), 4E14C(<) (F)
{
	coll->bad_neg = -384;
	lara.move_angle = item->pos.y_rot;
	LaraSurfaceCollision(item, coll);
	LaraTestWaterClimbOut(item, coll);
}

void lara_as_surftread(struct ITEM_INFO* item, struct COLL_INFO* coll)//4DBA0, 4E004 (F)
{
	item->fallspeed -= 4;
	if (item->fallspeed < 0)
		item->fallspeed = 0;

	if (item->hit_points <= 0)
	{
		item->goal_anim_state = STATE_LARA_WATER_DEATH;

		return;
	}
	
	if (input & IN_LOOK)
	{
		LookUpDown();
		return;
	}

	if (input & IN_LEFT)
	{
		item->pos.y_rot -= ANGLE(4);
	}
	else if (input & IN_RIGHT)
	{
		item->pos.y_rot += ANGLE(4);
	}

	if(input & IN_FORWARD)
	{
		item->goal_anim_state = STATE_LARA_ONWATER_FORWARD;
	}
	else if(input & IN_BACK)
	{
		item->goal_anim_state = STATE_LARA_ONWATER_BACK;
	}

	if (input & IN_LSTEP)
	{
		item->goal_anim_state = STATE_LARA_ONWATER_LEFT;
	}
	else if(input & IN_RSTEP)
	{
		item->goal_anim_state = STATE_LARA_ONWATER_RIGHT;
	}

	if (input & IN_JUMP)
	{
		if (++lara.dive_count == 10)
			item->goal_anim_state = STATE_LARA_UNDERWATER_FORWARD;
	}
	else
	{
		lara.dive_count = 0;
	}
}

void lara_as_surfright(struct ITEM_INFO* item, struct COLL_INFO* coll)//4DAF8, 4DF5C (F)
{
	if (item->hit_points <= 0)
	{
		item->goal_anim_state = STATE_LARA_WATER_DEATH;

		return;
	}
	
	lara.dive_count = 0;

	if (input & IN_LEFT)
	{
		item->pos.y_rot -= ANGLE(2);
	}
	else if (input & IN_RIGHT)
	{
		item->pos.y_rot += ANGLE(2);
	}

	if (!(input & IN_RSTEP))
	{
		item->goal_anim_state = STATE_LARA_ONWATER_STOP;
	}

	item->fallspeed += 8;
	if (item->fallspeed > 60)
		item->fallspeed = 60;
}

void lara_as_surfleft(struct ITEM_INFO* item, struct COLL_INFO* coll)//4DA50(<), 4DEB4(<) (F)
{
	if (item->hit_points <= 0)
	{
		item->goal_anim_state = STATE_LARA_WATER_DEATH;

		return;
	}
	
	lara.dive_count = 0;
		
	if (input & IN_LEFT)
	{
		item->pos.y_rot -= ANGLE(2);
	}
	else if (input & IN_RIGHT)
	{
		item->pos.y_rot += ANGLE(2);
	}

	if (!(input & IN_LSTEP))
	{
		item->goal_anim_state = STATE_LARA_ONWATER_STOP;
	}

	item->fallspeed += 8;
	if (item->fallspeed > 60)
		item->fallspeed = 60;
}

void lara_as_surfback(struct ITEM_INFO* item, struct COLL_INFO* coll)//4D9A8(<), 4DE0C(<) (F)
{
	if (item->hit_points <= 0)
	{
		item->goal_anim_state = STATE_LARA_WATER_DEATH;

		return;
	}
	
	lara.dive_count = 0;

	if (input & IN_LEFT)
	{
		item->pos.y_rot -= ANGLE(2);
	}
	else if (input & IN_RIGHT)
	{
		item->pos.y_rot += ANGLE(2);
	}

	if (!(input & IN_BACK))
	{
		item->goal_anim_state = STATE_LARA_ONWATER_STOP;
	}

	item->fallspeed += 8;
	if (item->fallspeed > 60)
		item->fallspeed = 60;
}

void lara_as_surfswim(struct ITEM_INFO* item, struct COLL_INFO* coll)//4D8E4(<), 4DD48(<) (F)
{
	if (item->hit_points <= 0)
	{
		item->goal_anim_state = STATE_LARA_WATER_DEATH;

		return;
	}
	
	lara.dive_count = 0;

	if (input & IN_LEFT)
	{
		item->pos.y_rot -= ANGLE(4);
	}
	else if (input & IN_RIGHT)
	{
		item->pos.y_rot += ANGLE(4);
	}

	if (!(input & IN_FORWARD))
		item->goal_anim_state = STATE_LARA_ONWATER_STOP;
	if (input & IN_JUMP)
		item->goal_anim_state = STATE_LARA_ONWATER_STOP;

	item->fallspeed += 8;
	if (item->fallspeed > 60)
		item->fallspeed = 60;
}

void LaraSurface(struct ITEM_INFO* item, struct COLL_INFO* coll)//4D684, 4DAE8 (F)
{
	camera.target_elevation = ANGLE(-22);

	coll->bad_pos = 32512;
	coll->bad_neg = -128;
	coll->bad_ceiling = 100;

	coll->old.x = item->pos.x_pos;
	coll->old.y = item->pos.y_pos;
	coll->old.z = item->pos.z_pos;

	coll->slopes_are_walls = 0;
	coll->slopes_are_pits = 0;
	coll->lava_is_pit = 0;

	coll->enable_baddie_push = FALSE;
	coll->enable_spaz = FALSE;
	
	coll->radius = 100;
	coll->trigger = 0;

	if (input & IN_LOOK && lara.look)
		LookLeftRight();
	else
		ResetLook();

	lara.look = TRUE;

	lara_control_routines[item->current_anim_state](item, coll);

	item->pos.z_rot = CLAMPADD(item->pos.z_rot, ANGLE(-2), ANGLE(2));

	if (lara.current_active && lara.water_status != LW_FLYCHEAT)
		LaraWaterCurrent(coll);

	AnimateLara(item);

	item->pos.x_pos += item->fallspeed * SIN(lara.move_angle) >> W2V_SHIFT;
	item->pos.z_pos += item->fallspeed * COS(lara.move_angle) >> W2V_SHIFT;

	LaraBaddieCollision(item, coll);

	lara_collision_routines[item->current_anim_state](item, coll);

	UpdateLaraRoom(item, 100);

	LaraGun();

	TestTriggers(coll->trigger, 0, 0);
}

void LaraSurfaceCollision(struct ITEM_INFO* item, struct COLL_INFO* coll)//4D4F0(<), 4D954(<) (F)
{
	coll->facing = lara.move_angle;
	GetCollisionInfo(coll, item->pos.x_pos, item->pos.y_pos + 700, item->pos.z_pos, item->room_number, 800);
	ShiftItem(item, coll);
	if (coll->coll_type & (CT_FRONT | CT_TOP | CT_TOP_FRONT | CT_CLAMP) || 
		coll->mid_floor < 0 && (coll->mid_type == BIG_SLOPE || coll->mid_type == DIAGONAL))
	{
		item->fallspeed = 0;
		item->pos.x_pos = coll->old.x;
		item->pos.y_pos = coll->old.y;
		item->pos.z_pos = coll->old.z;
	}
	else if (coll->coll_type == CT_LEFT)
	{
		item->pos.y_rot += ANGLE(5);
	}
	else if (coll->coll_type == CT_RIGHT)
	{
		item->pos.y_rot -= ANGLE(5);
	}
	if (GetWaterHeight(item->pos.x_pos, item->pos.y_pos, item->pos.z_pos, item->room_number) - item->pos.y_pos > -100)
	{
		LaraTestWaterStepOut(item, coll);
	}
	else
	{
		item->goal_anim_state = STATE_LARA_UNDERWATER_FORWARD;
		item->current_anim_state = STATE_LARA_UNDERWATER_DIVING;
		item->anim_number = ANIMATION_LARA_FREE_FALL_TO_UNDERWATER_ALTERNATE;
		item->pos.x_rot = ANGLE(-90);
		item->frame_number = anims[ANIMATION_LARA_FREE_FALL_TO_UNDERWATER_ALTERNATE].frame_base;
		item->fallspeed = 80;
		lara.water_status = LW_UNDERWATER;
	}
}

int LaraTestWaterClimbOut(struct ITEM_INFO* item, struct COLL_INFO* coll)//4D22C, 4D690
{
	UNIMPLEMENTED();
	return 0;
}

int LaraTestWaterStepOut(struct ITEM_INFO* item, struct COLL_INFO* coll)//4D100, 4D564 (F)
{
	if (coll->coll_type == CT_FRONT || coll->mid_type == BIG_SLOPE || coll->mid_type == DIAGONAL || coll->mid_floor >= 0)
	{
		return 0;
	}

	if (coll->mid_floor >= -128)
	{
		if (item->goal_anim_state == STATE_LARA_ONWATER_LEFT)
		{
			item->goal_anim_state = STATE_LARA_WALK_LEFT;
		}
		else if (item->goal_anim_state == STATE_LARA_ONWATER_RIGHT)
		{
			item->goal_anim_state = STATE_LARA_WALK_RIGHT;
		}
		else
		{
			item->anim_number = ANIMATION_LARA_WADE;
			item->frame_number = anims[ANIMATION_LARA_WADE].frame_base;
			item->goal_anim_state = STATE_LARA_WADE_FORWARD;
			item->current_anim_state = STATE_LARA_WADE_FORWARD;	
		}
	}
	else
	{
		item->anim_number = ANIMATION_LARA_ONWATER_TO_WADE_DEEP;
		item->frame_number = anims[ANIMATION_LARA_ONWATER_TO_WADE_DEEP].frame_base;
		item->current_anim_state = STATE_LARA_ONWATER_EXIT;
		item->goal_anim_state = STATE_LARA_STOP;
	}

	item->pos.y_pos += coll->front_floor + 695;

	UpdateLaraRoom(item, -381);

	item->pos.z_rot = 0;
	item->pos.x_rot = 0;

	item->gravity_status = TRUE;
	item->speed = 0;
	item->fallspeed = 0;

	lara.water_status = 4;

	return 1;
}
