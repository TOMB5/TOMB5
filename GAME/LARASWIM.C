#include "LARASWIM.H"

#include "CONTROL.H"
#include INPUT_H
#include "SPECIFIC.H"
#include "SPECTYPES.H"
#include "LARA.H"
#include "DRAW.H"

SUBSUIT_INFO subsuit;
char SubHitCount = 0;

void LaraWaterCurrent(COLL_INFO* coll)//4CD34, 4D198
{
	S_Warn("[LaraWaterCurrent] - Unimplemented!\n");
}

long GetWaterDepth(long x, long y, long z, short room_number)//4CA38, 4CE9C
{
	S_Warn("[GetWaterDepth] - Unimplemented!\n");
	return 0;
}

void lara_col_waterroll(ITEM_INFO* item, COLL_INFO* coll)//4CA18(<), 4CE7C(<) (F)
{
	LaraSwimCollision(item, coll);
}

void lara_col_uwdeath(ITEM_INFO* item, COLL_INFO* coll)//4C980(<), 4CDE4(<) (F)
{
	int wh;
	item->hit_points = -1;
	lara.air = -1;
	lara.gun_status = 1;
	wh = GetWaterHeight(item->pos.x_pos, item->pos.y_pos, item->pos.z_pos, item->room_number);
	if (wh != -32512)
	{
		if (wh < item->pos.y_pos - 100)
			item->pos.y_pos -= 5;
	}
	LaraSwimCollision(item, coll);
}

void lara_col_dive(ITEM_INFO* item, COLL_INFO* coll)//4C960(<), 4CDC4(<) (F)
{
	LaraSwimCollision(item, coll);
}

void lara_col_tread(ITEM_INFO* item, COLL_INFO* coll)//4C940(<), 4CDA4(<) (F)
{
	LaraSwimCollision(item, coll);
}

void lara_col_glide(ITEM_INFO* item, COLL_INFO* coll)//4C920(<), 4CD84(<) (F)
{
	LaraSwimCollision(item, coll);
}

void lara_col_swim(ITEM_INFO* item, COLL_INFO* coll)//4C900(<), 4CD64(<) (F)
{
	LaraSwimCollision(item, coll);
}

void lara_as_waterroll(ITEM_INFO* item, COLL_INFO* coll)//4C8F8(<), 4CD5C(<) (F)
{
	item->fallspeed = 0;
}

void lara_as_uwdeath(ITEM_INFO* item, COLL_INFO* coll)//4C884(<), 4CCE8(<) (F)
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

void lara_as_dive(ITEM_INFO* item, COLL_INFO* coll)//4C854, 4CCB8
{
	if (input & IN_UP)
	{
		item->pos.x_rot -= ANGLE(1);
	}
}

void lara_as_tread(ITEM_INFO* item, COLL_INFO* coll)//4C730, 4CB94
{
	S_Warn("[lara_as_tread] - Unimplemented!\n");
}

void lara_as_glide(ITEM_INFO* item, COLL_INFO* coll)//4C634(<), 4CA98(<) (F)
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

void lara_as_swim(ITEM_INFO* item, COLL_INFO* coll)//4C548(<), 4C9AC(<) (F)
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

void lara_as_swimcheat(ITEM_INFO* item, COLL_INFO* coll)//4C3A8, 4C80C
{
	S_Warn("[lara_as_swimcheat] - Unimplemented!\n");
}

void LaraUnderWater(ITEM_INFO* item, COLL_INFO* coll)//4BFB4, 4C418
{
	S_Warn("[LaraUnderWater] - Unimplemented!\n");
}

void UpdateSubsuitAngles()//4BD20, 4C184
{
	S_Warn("[UpdateSubsuitAngles] - Unimplemented!\n");
}

void SwimTurnSubsuit(ITEM_INFO* item)//4BBDC, 4C040
{
	S_Warn("[SwimTurnSubsuit] - Unimplemented!\n");
}

void SwimTurn(ITEM_INFO* item)//4BAF4(<), 4BF58(<) (F)
{
	if (input & IN_UP)
	{
		item->pos.x_rot -= 364;
	}
	else if (input & IN_DOWN)
	{
		item->pos.x_rot += 364;
	}

	if (input & IN_LEFT)
	{
		lara.turn_rate -= 409;
		if (lara.turn_rate < -1092)
			lara.turn_rate = -1092;
		item->pos.z_rot -= 546;
	}
	else if (input & IN_RIGHT)
	{
		lara.turn_rate += 409;
		if (lara.turn_rate > 1092)
			lara.turn_rate = 1092;
		item->pos.z_rot -= 546;
	}
}

void LaraSwimCollision(ITEM_INFO* item, COLL_INFO* coll)//4B608, 4BA6C
{
	S_Warn("[LaraSwimCollision] - Unimplemented!\n");
}

void LaraTestWaterDepth(ITEM_INFO* item, COLL_INFO* coll)//4B4F8, 4B95C
{
	S_Warn("[LaraTestWaterDepth] - Unimplemented!\n");
}