#include "LARASURF.H"

#include "CAMERA.H"
#include "COLLIDE.H"
#include "CONTROL.H"
#include "DRAW.H"
#include "LARA.H"
#include "LARAFIRE.H"
#include "SPECIFIC.H"
#include INPUT_H
#include "LARASWIM.H"

#if PSX_VERSION
#include "COLLIDE_S.H"
#endif

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

	coll->bad_pos = -BAD_HEIGHT;
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

#if PSX_VERSION
	item->pos.x_pos += item->fallspeed * SIN(lara.move_angle) >> 14;
	item->pos.z_pos += item->fallspeed * COS(lara.move_angle) >> 14;
#elif PC_VERSION
	item->pos.x_pos += item->fallspeed * SIN(lara.move_angle) >> W2V_SHIFT;
	item->pos.z_pos += item->fallspeed * COS(lara.move_angle) >> W2V_SHIFT;
#endif

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
	int hdif; // $s2
	short angle; // $s0

	//v1 = coll->coll_type
	//s1 = item
	if (coll->coll_type == 1)
	{
		//v0 = input

		if (!(input & IN_ACTION))
		{
			return 0;
		}

		//a0 = coll->left_floor2
		//v1 = coll->right_floor2

		if (coll->left_floor2 - coll->right_floor2 >= 0 && coll->left_floor2 - coll->right_floor2 < 0x3C ||
			coll->right_floor2 - coll->left_floor2 >= 0 < 0x3C)
		{
			//a0 = lara
			//v1 = lara.gun_status

			if (lara.gun_status != 0)
			{
				if (lara.gun_status != 4 || lara.gun_type != 7)
				{
					return 0;
				}
			}
			//loc_4D2C4

			if (coll->front_ceiling > 0)
			{
				return 0;
			}

			//v0 = coll->mid_ceiling
			if (coll->mid_ceiling >= -0x17F)
			{
				return 0;
			}

			hdif = coll->front_floor + 0x2BC;
			if (coll->front_floor + 0x4BB >= 0x33C)
			{
				return 0;
			}

			angle = item->pos.y_rot;

			//v0 = ((angle + 0x18E2) & 0xFFFF);

			if ((unsigned)((angle + 0x18E2) & 0xFFFF) < 0x31C5)
			{
				angle = 0;
			}
			else
			{
				if ((unsigned)(angle - 0x271E) < 0x31C5)
				{
					angle = 0x4000;
				}
				else
				{
					if (angle >= 0x671D || angle < -0x671C)
					{
						angle = -0x8000;
					}
					else
					{
						if (((angle + 0x58E2) & 0xFFFF) < 0x31C5)
						{
							angle = -0x4000;
						}
					}
				}
			}

			//loc_4D368
			if ((angle & 0x3FFF) != 0)
			{
				return 0;
			}
		}
		else
		{
			//loc_4D374
			return 0;
		}
	}
	else
	{
		//loc_4D374
		return 0;
	}
	
	//loc_4D37C
	//v0 = (item->pos.y_pos - 5) + hdif
	//a1 = -381
	item->pos.y_pos = (item->pos.y_pos - 5) + hdif;
	UpdateLaraRoom(item, -381);
	//v0 = -0x4000

	if (angle != -0x4000)
	{
		if (angle - 0x3FFF == 0)
		{
			//loc_4D3B8
			if (angle == 0)
			{
				//loc_4D3D0
				item->pos.z_pos = (item->pos.z_pos & -1024) + 0x464;
				//j loc_4D428
			}
			else if (angle == 0x4000)
			{
				//loc_4D3E8
				//v1 = -1024
				item->pos.x_pos = (item->pos.x_pos & -1024) + 0x464;
				//j loc_4D424
			}
		}
		else if(angle == -0x8000)
		{
			//loc_4D3FC
			//v0 = hdif < -0x80 ? 1 : 0
			item->pos.z_pos = (item->pos.z_pos & -1024) - 0x64;
			//j loc_4D428
		}
	}
	else
	{
		//loc_4D414
		item->pos.x_pos = (item->pos.x_pos & -1024) - 0x64;
	}

	//loc_4D428
	//loc_4D42C
	//v1 = 0x6F
	if (hdif < -0x80)
	{
		//v0 = anims
		//v1 = item->anim_number
		//a0 = anims[ANIMATION_LARA_CLIMB_OUT_OF_WATER].frame_base
		item->anim_number = ANIMATION_LARA_CLIMB_OUT_OF_WATER;
		item->frame_number = anims[ANIMATION_LARA_CLIMB_OUT_OF_WATER].frame_base;
	}
	else if (hdif < 0x80)
	{
		//loc_4D44C
		item->anim_number = ANIMATION_LARA_ONWATER_TO_LAND_LOW;
		item->frame_number = anims[ANIMATION_LARA_ONWATER_TO_LAND_LOW].frame_base;
	}
	else
	{
		//loc_4D470
		item->anim_number = ANIMATION_LARA_ONWATER_TO_WADE;
		item->frame_number = anims[ANIMATION_LARA_ONWATER_TO_WADE].frame_base;
	}
	//loc_4D48C
	//v0 = 1
	//v1 = 0x37
	//a0 = 2
	//a1 = &lara
	item->current_anim_state = STATE_LARA_ONWATER_EXIT;
	//v1 = 1
	item->goal_anim_state = STATE_LARA_STOP;
	item->pos.y_rot = angle;
	lara.gun_status = 1;
	item->gravity_status = 0;
	item->pos.z_rot = 0;
	item->pos.x_rot = 0;
	item->speed = 0;
	item->fallspeed = 0;
	lara.water_status = 0;

	return 1;
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

	lara.water_status = LW_WADE;

	return 1;
}
