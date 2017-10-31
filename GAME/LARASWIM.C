#include "LARASWIM.H"

#include "CAMERA.H"
#include "COLLIDE.H"
#include "CONTROL.H"
#include "DRAW.H"
#include "EFFECT2.H"
#include INPUT_H
#include "LARA.H"
#include "LARAFIRE.H"
#include "SPECIFIC.H"
#include "SPECTYPES.H"

struct SUBSUIT_INFO subsuit;
char SubHitCount = 0;

void LaraWaterCurrent(struct COLL_INFO* coll)//4CD34, 4D198
{
	S_Warn("[LaraWaterCurrent] - Unimplemented!\n");
}

long GetWaterDepth(long x, long y, long z, short room_number)//4CA38, 4CE9C
{
	S_Warn("[GetWaterDepth] - Unimplemented!\n");
	return 0;
}

void lara_col_waterroll(struct ITEM_INFO* item, struct COLL_INFO* coll)//4CA18(<), 4CE7C(<) (F)
{
	LaraSwimCollision(item, coll);
}

void lara_col_uwdeath(struct ITEM_INFO* item, struct COLL_INFO* coll)//4C980(<), 4CDE4(<) (F)
{
	int wh;
	item->hit_points = -1;
	lara.air = -1;
	lara.gun_status = LG_HANDS_BUSY;
	wh = GetWaterHeight(item->pos.x_pos, item->pos.y_pos, item->pos.z_pos, item->room_number);
	if (wh != -32512)
	{
		if (wh < item->pos.y_pos - 100)
			item->pos.y_pos -= 5;
	}
	LaraSwimCollision(item, coll);
}

void lara_col_dive(struct ITEM_INFO* item, struct COLL_INFO* coll)//4C960(<), 4CDC4(<) (F)
{
	LaraSwimCollision(item, coll);
}

void lara_col_tread(struct ITEM_INFO* item, struct COLL_INFO* coll)//4C940(<), 4CDA4(<) (F)
{
	LaraSwimCollision(item, coll);
}

void lara_col_glide(struct ITEM_INFO* item, struct COLL_INFO* coll)//4C920(<), 4CD84(<) (F)
{
	LaraSwimCollision(item, coll);
}

void lara_col_swim(struct ITEM_INFO* item, struct COLL_INFO* coll)//4C900(<), 4CD64(<) (F)
{
	LaraSwimCollision(item, coll);
}

void lara_as_waterroll(struct ITEM_INFO* item, struct COLL_INFO* coll)//4C8F8(<), 4CD5C(<) (F)
{
	item->fallspeed = 0;
}

void lara_as_uwdeath(struct ITEM_INFO* item, struct COLL_INFO* coll)//4C884(<), 4CCE8(<) (F)
{
	lara.look = 0;

	item->fallspeed -= 8;
	if (item->fallspeed <= 0)
		item->fallspeed = 0;

	if(item->pos.x_rot < ANGLE(-2) || item->pos.x_rot > ANGLE(2))
	{
		if (item->pos.x_rot >= 0)
			item->pos.x_rot -= ANGLE(2);
		else
			item->pos.x_rot += ANGLE(2);
	}
	else
	{
		item->pos.x_rot = 0;
	}
}

void lara_as_dive(struct ITEM_INFO* item, struct COLL_INFO* coll)//4C854, 4CCB8 (F)
{
	if (input & IN_UP)
	{
		item->pos.x_rot -= ANGLE(1);
	}
}

void lara_as_tread(struct ITEM_INFO* item, struct COLL_INFO* coll)//4C730, 4CB94 (F)
{
	if (item->hit_points <= 0)
	{
		item->goal_anim_state = STATE_LARA_WATER_DEATH;

		return;
	}
	
	if (input & IN_ROLL && LaraDrawType != LARA_DIVESUIT)
	{
		item->current_anim_state = STATE_LARA_UNDERWATER_TURNAROUND;
		item->anim_number = ANIMATION_LARA_UNDERWATER_ROLL_BEGIN;
		item->frame_number = anims[ANIMATION_LARA_UNDERWATER_ROLL_BEGIN].frame_base;
	}
	else
	{
		if (input & IN_LOOK)
			LookUpDown();

		if (LaraDrawType == LARA_DIVESUIT)
			SwimTurnSubsuit(item);
		else
			SwimTurn(item);

		if (input & IN_JUMP)
			item->goal_anim_state = STATE_LARA_UNDERWATER_FORWARD;

		item->fallspeed -= 6;

		if (item->fallspeed < 0)
			item->fallspeed = 0;

		if (lara.gun_status == LG_HANDS_BUSY)
			lara.gun_status = LG_NO_ARMS;
	}
}

void lara_as_glide(struct ITEM_INFO* item, struct COLL_INFO* coll)//4C634(<), 4CA98(<) (F)
{
	if (item->hit_points <= 0)
	{
		item->goal_anim_state = STATE_LARA_WATER_DEATH;

		return;
	}

	if (input & IN_ROLL)
	{
		if (LaraDrawType != LARA_DIVESUIT)
		{
			item->current_anim_state = STATE_LARA_UNDERWATER_TURNAROUND;
			item->anim_number = ANIMATION_LARA_UNDERWATER_ROLL_BEGIN;
			item->frame_number = anims[ANIMATION_LARA_UNDERWATER_ROLL_BEGIN].frame_base;
			return;
		}
	}
	else if (LaraDrawType != LARA_DIVESUIT)
	{
		SwimTurn(item);
	}
	else
	{
		SwimTurnSubsuit(item);
	}

	if (input & IN_JUMP)
		item->goal_anim_state = STATE_LARA_UNDERWATER_FORWARD;

	item->fallspeed -= 6;
	if (item->fallspeed < 0)
		item->fallspeed = 0;

	if (item->fallspeed <= 133)
		item->goal_anim_state = STATE_LARA_UNDERWATER_STOP;
}

void lara_as_swim(struct ITEM_INFO* item, struct COLL_INFO* coll)//4C548(<), 4C9AC(<) (F)
{
	if (item->hit_points <= 0)
	{
		item->goal_anim_state = STATE_LARA_WATER_DEATH;

		return;
	}

	if (input & IN_ROLL)
	{
		if (LaraDrawType != LARA_DIVESUIT)
		{
			item->current_anim_state = STATE_LARA_UNDERWATER_TURNAROUND;
			item->anim_number = ANIMATION_LARA_UNDERWATER_ROLL_BEGIN;
			item->frame_number = anims[ANIMATION_LARA_UNDERWATER_ROLL_BEGIN].frame_base;
			return;
		}
	}
	else if (LaraDrawType != LARA_DIVESUIT)
	{
		SwimTurn(item);
	}
	else
	{
		SwimTurnSubsuit(item);
	}

	item->fallspeed += 8;

	if (item->fallspeed > 200)
		item->fallspeed = 200;

	if (!(input & IN_JUMP))
		item->goal_anim_state = STATE_LARA_UNDERWATER_INERTIA;
}

void lara_as_swimcheat(struct ITEM_INFO* item, struct COLL_INFO* coll)//4C3A8, 4C80C (F)
{
	if (input & IN_UP)
	{
		item->pos.x_rot -= ANGLE(3);
	}
	else if (input & IN_DOWN)
	{
		item->pos.x_rot += ANGLE(3);
	}

	if (input & IN_LEFT)
	{
		lara.turn_rate -= 613;

		if (lara.turn_rate < ANGLE(-6))
			lara.turn_rate = ANGLE(-6);
	}
	else if (input & IN_RIGHT)
	{
		lara.turn_rate += 613;

		if (lara.turn_rate > ANGLE(6))
			lara.turn_rate = ANGLE(6);
	}

	if (input & IN_ACTION)
	{
		TriggerDynamic(item->pos.x_pos, item->pos.y_pos, item->pos.z_pos, 31, 255, 255, 255);
	}

	if (input & IN_OPTION)
	{
		lara.turn_rate = ANGLE(-12);
	}

	if (input & IN_JUMP)
	{
		item->fallspeed += 16;

		if (item->fallspeed > 400)
			item->fallspeed = 400;
	}
	else
	{
		if (item->fallspeed >= 8)
			item->fallspeed -= item->fallspeed >> 3;
		else
			item->fallspeed = 0;
	}
}

void LaraUnderWater(struct ITEM_INFO* item, struct COLL_INFO* coll)//4BFB4, 4C418 (F)
{
	coll->bad_pos = 32512;
	coll->bad_neg = -400;
	coll->bad_ceiling = 400;

	coll->old.x = item->pos.x_pos;
	coll->old.y = item->pos.y_pos;
	coll->old.z = item->pos.z_pos;

	coll->slopes_are_walls = 0;
	coll->slopes_are_pits = 0;
	coll->lava_is_pit = 0;

	coll->enable_baddie_push = TRUE;
	coll->enable_spaz = FALSE;

	coll->radius = 300;
	coll->trigger = 0;

	if (input & IN_LOOK && lara.look)
		LookLeftRight();
	else
		ResetLook();

	lara.look = TRUE;

	lara_control_routines[item->current_anim_state](item, coll);

	if (LaraDrawType == LARA_DIVESUIT)
	{
		lara.turn_rate = CLAMPADD(lara.turn_rate, ANGLE(-0.5), ANGLE(0.5));
	}
	else
	{
		lara.turn_rate = CLAMPADD(lara.turn_rate, ANGLE(-2), ANGLE(2));
	}

	item->pos.y_rot += lara.turn_rate;

	if (LaraDrawType == LARA_DIVESUIT)
		UpdateSubsuitAngles();

	item->pos.z_rot = CLAMPADD(item->pos.z_rot, ANGLE(-2), ANGLE(2));
	item->pos.x_rot = CLAMPADD(item->pos.x_rot, ANGLE(-85), ANGLE(85));

	if (LaraDrawType == LARA_DIVESUIT)
	{
		item->pos.z_rot = CLAMP(item->pos.z_rot, ANGLE(-44), ANGLE(44));
	}
	else
	{
		item->pos.z_rot = CLAMP(item->pos.z_rot, ANGLE(-22), ANGLE(22));
	}

	if (lara.current_active && lara.water_status != LW_FLYCHEAT)
		LaraWaterCurrent(coll);

	AnimateLara(item);
	
	item->pos.x_pos += COS(item->pos.x_rot) * (item->fallspeed * SIN(item->pos.y_rot) >> W2V_SHIFT >> 2) >> W2V_SHIFT;
	item->pos.y_pos -= item->fallspeed * SIN(item->pos.x_rot) >> W2V_SHIFT >> 2;
	item->pos.z_pos += COS(item->pos.x_rot) * (item->fallspeed * COS(item->pos.y_rot) >> W2V_SHIFT >> 2) >> W2V_SHIFT;

	LaraBaddieCollision(item, coll);

	lara_collision_routines[item->current_anim_state](item, coll);

	UpdateLaraRoom(item, 0);

	LaraGun();

	TestTriggers(coll->trigger, 0, 0);
}

void UpdateSubsuitAngles()//4BD20, 4C184
{
	S_Warn("[UpdateSubsuitAngles] - Unimplemented!\n");
}

void SwimTurnSubsuit(struct ITEM_INFO* item)//4BBDC, 4C040 (F)
{
	if (item->pos.y_pos < 14080)
		subsuit.YVel += (14080 - item->pos.y_pos) >> 4;

	if (input & IN_UP && item->pos.x_rot > ANGLE(-85))
	{
		subsuit.dXRot = ANGLE(-45);
	}
	else if(input & IN_DOWN && item->pos.x_rot < ANGLE(85))
	{
		subsuit.dXRot = ANGLE(45);
	}
	else
	{
		subsuit.dXRot = 0;
	}

	if (input & IN_LEFT)
	{
		lara.turn_rate -= 136;

		if (lara.turn_rate < ANGLE(-6))
			lara.turn_rate = ANGLE(-6);

		item->pos.z_rot -= ANGLE(3);
	}
	else if (input & IN_RIGHT)
	{
		lara.turn_rate += 136;

		if (lara.turn_rate > ANGLE(6))
			lara.turn_rate = ANGLE(6);

		item->pos.z_rot += ANGLE(3);
	}
}

void SwimTurn(struct ITEM_INFO* item)//4BAF4(<), 4BF58(<) (F)
{
	if (input & IN_UP)
	{
		item->pos.x_rot -= ANGLE(2);
	}
	else if (input & IN_DOWN)
	{
		item->pos.x_rot += ANGLE(2);
	}

	if (input & IN_LEFT)
	{
		lara.turn_rate -= 409;
		if (lara.turn_rate < ANGLE(-6))
			lara.turn_rate = ANGLE(-6);
		item->pos.z_rot -= ANGLE(3);
	}
	else if (input & IN_RIGHT)
	{
		lara.turn_rate += 409;
		if (lara.turn_rate > ANGLE(6))
			lara.turn_rate = ANGLE(6);
		item->pos.z_rot += ANGLE(3);
	}
}

void LaraSwimCollision(struct ITEM_INFO* item, struct COLL_INFO* coll)//4B608, 4BA6C
{
	S_Warn("[LaraSwimCollision] - Unimplemented!\n");
}

void LaraTestWaterDepth(struct ITEM_INFO* item, struct COLL_INFO* coll)//4B4F8, 4B95C
{
	S_Warn("[LaraTestWaterDepth] - Unimplemented!\n");
}