#include "LARASWIM.H"

#include "SPECIFIC.H"
#include "CAMERA.H"
#include CMATH_H
#include "COLLIDE.H"
#include "CONTROL.H"
#include "DRAW.H"
#include "EFFECT2.H"
#include INPUT_H
#include "LARA.H"
#include "LARAFIRE.H"
#include "STYPES.H"
#include "EFFECTS.H"
#include "SOUND.H"

#if PSXPC_VERSION || PSX_VERSION || SAT_VERSION
#include "BUBBLES.H"
#include "GETSTUFF.H"
#include "COLLIDE_S.H"
#endif

struct SUBSUIT_INFO subsuit;
char SubHitCount = 0;

void LaraWaterCurrent(struct COLL_INFO* coll)//4CD34, 4D198
{
	UNIMPLEMENTED();
}

long GetWaterDepth(long x, long y, long z, short room_number)//4CA38, 4CE9C
{
	int wh; // $s0
	struct room_info* r; // $s0
	struct FLOOR_INFO* floor; // $s1
	short data; // $a0
	int x_floor; // $a1
	int y_floor; // $a0
	unsigned char door;//$a0 ///@fixme ?!?!? should be data

	//loc_4CA80
	do
	{
		r = &room[room_number];

		x_floor = (z - r->z) >> 10;
		y_floor = (x - r->x) >> 10;

		if (x_floor <= 0)
		{
			x_floor = 0;

			if (y_floor <= 0)
			{
				y_floor = 1;
			}
			else
			{
				//loc_4CAB4
				if (r->y_size - 2 < y_floor)
				{
					y_floor = r->y_size - 2;
				}
			}
		}
		else
		{
			//loc_4CAD4
			if (x_floor < r->x_size - 1)
			{
				//loc_4CB1C
				if (y_floor >= 0)
				{
					//loc_4CB2C
					if (y_floor >= r->y_size)
					{
						y_floor = r->y_size - 1;
					}
				}
				else
				{
					y_floor = 0;
				}
			}
			else
			{
				x_floor = r->x_size - 1;

				if (y_floor > 0)
				{
					//loc_4CAFC
					if (r->y_size - 2 < y_floor)
					{
						y_floor = r->y_size - 2;
					}
				}
				else
				{
					y_floor = 1;
				}
			}
		}

		//loc_4CB48
		floor = &r->floor[x_floor + (y_floor * r->x_size)];

		door = GetDoor(floor);

		if (door == 255)
			break;

		room_number = door;
	} while (TRUE);

	//loc_4CB94
	if ((r->flags & RF_FILL_WATER))
	{
		if (floor->sky_room != door)
		{
loc_4CBC4:
			r = &room[floor->sky_room];

			if ((r->flags & RF_FILL_WATER))
			{
				floor = &r->floor[((z - r->z) >> 10) + r->x_size * ((x - r->x) >> 10)];

				if (floor->sky_room != 255)
				{
					goto loc_4CBC4;
				}

				//loc_4CD14
				return 32767;
			}
			else
			{
				//loc_4CC40
				wh = floor->ceiling << 8;
				return GetHeight(GetFloor(x, y, z, &room_number), x, y, z) - wh;
			}
		}
		//loc_4CD14
		return 32767;
	}
	else
	{
		//loc_4CC84
		if (floor->pit_room != door)
		{
			//loc_4CCA0
			do
			{
				r = &room[floor->pit_room];

				if (!(r->flags & RF_FILL_WATER))
				{
					floor = &r->floor[((z - r->z) >> 10) + (r->x_size * ((x - r->x) >> 10))];
				}
				else
				{
					//loc_4CC50
					//loc_4CC5C
					wh = floor->floor << 8;
					return GetHeight(GetFloor(x, y, z, &room_number), x, y, z) - wh;
				}

			} while (floor->pit_room != 255);
		}
	}

	return -32767;
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
	if (input & IN_FORWARD)
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
	if (input & IN_FORWARD)
	{
		item->pos.x_rot -= ANGLE(3);
	}
	else if (input & IN_BACK)
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
#if PC_VERSION
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
	
	item->pos.x_pos += 4 * COS(item->pos.x_rot) * (item->fallspeed * SIN(item->pos.y_rot) >> W2V_SHIFT) >> W2V_SHIFT;
	item->pos.y_pos -= item->fallspeed * 4 * SIN(item->pos.x_rot) >> W2V_SHIFT >> 2;
	item->pos.z_pos += 4 * COS(item->pos.x_rot) * (item->fallspeed * COS(item->pos.y_rot) >> W2V_SHIFT) >> W2V_SHIFT;

	LaraBaddieCollision(item, coll);

	lara_collision_routines[item->current_anim_state](item, coll);

	UpdateLaraRoom(item, 0);

	LaraGun();

	TestTriggers(coll->trigger, 0, 0);
#else

	//s2 = coll
	//v0 = 32512
	//v1 = -400
	coll->bad_pos = 32512;
	//v0 = 400
	//s0 = item
	coll->bad_neg = -400;
	coll->bad_ceiling = 400;
	//v0 = item->pos.x_pos
	//s3 = 0xA0000
	coll->old.x = item->pos.x_pos;
	coll->old.y = item->pos.y_pos;
	coll->old.z = item->pos.z_pos;

	//a0 = -5
	//v0 = 300
	coll->radius = 300;
	//v0 = coll->flags
	//v1 = -4
	coll->trigger = NULL;
	
	coll->slopes_are_walls = 0;
	coll->slopes_are_pits = 0;
	coll->lava_is_pit = 0;
	coll->enable_spaz = 0;
	coll->enable_baddie_push = 1;
	//v1 = 0xF7
	//v1 = input
	//v1 = lara
	if ((input & IN_LOOK) && lara.look)
	{
		LookLeftRight();
	}
	else
	{
		//loc_4C078
		ResetLook();
	}

	//s1 = lara
	//a0 = item

	//loc_4C084
	//v0 = lara->flags
	lara.look = 1;
	//v1 = 0x90000
	//v0 = item->current_anim_state
	//v1 = lara_control_routines
	//v0 = &lara_control_routines[item->current_anim_state];
	//a2 = lara_control_routines[item->current_anim_state];

	lara_control_routines[item->current_anim_state](item, coll);

	//v1 = LaraDrawType
	//v0 = 5

	if (LaraDrawType != 5)
	{
		//v1 = lara.turn_rate
		lara.turn_rate = CLAMPADD2(lara.turn_rate, ANGLE(2), ANGLE(3));
	}
	else
	{
		//loc_4C0FC
		lara.turn_rate = CLAMPADD2(lara.turn_rate, ANGLE(0.5), ANGLE(1));
	}
	
	//loc_4C13C
	//a0 = lara
	item->pos.y_rot += lara.turn_rate;
	//v1 = LaraDrawType

	if (LaraDrawType == 5)
	{
		UpdateSubsuitAngles();
	}
	//loc_4C170
	item->pos.z_rot = CLAMPADDSHIFT(item->pos.z_rot, ANGLE(2), ANGLE(4), ANGLE(0));
	item->pos.x_rot = CLAMPADD3(item->pos.x_rot, ANGLE(0), ANGLE(-85), ANGLE(-85));

	if (LaraDrawType == 5)
	{
		item->pos.z_rot = CLAMPADD2(item->pos.z_rot, ANGLE(0), ANGLE(-44));///@TODO check me
	}
	else
	{
		//loc_4C208
		item->pos.z_rot = CLAMPADD2(item->pos.z_rot, ANGLE(0), ANGLE(-22));///@TODO check me
	}

	//v1 = lara
	//loc_4C234
	//v0 = lara.current_active
	//v0 = 3
	if (lara.current_active != 0)
	{
		if (lara.water_status != 3)
		{
			LaraWaterCurrent(coll);
		}//loc_4C25C
	}//loc_4C25C

	AnimateLara(item);

	//a3 = rcossin_tbl
	//a1 = item->pos.x_rot
	//t0 = lara.fallspeed
	//v1 = ((SIN(item->pos.x_rot) * lara.fallspeed)) >> 14;
	//a0 = item->pos.y_rot
	item->pos.y_pos -= ((SIN((unsigned short)item->pos.x_rot) * item->fallspeed)) >> 14;
	//v1 = (((SIN(item->pos.y_rot) * lara.fallspeed) >> 14) * COS(item->pos.x_rot) >> 12)
	//a2 = COS(item->pos.x_rot)
	item->pos.x_pos += (((SIN((unsigned short)item->pos.y_rot) * item->fallspeed) >> 14) * COS((unsigned short)item->pos.x_rot)) >> 12;
	//v0 = (((COS(item->pos.y_rot) * lara.fallspeed) >> 14) * COS(item->pos.x_rot)) >> 12
	//v1 = 
	//a0 = item
	//a1 = coll
	item->pos.z_pos += (((COS((unsigned short)item->pos.y_rot) * item->fallspeed) >> 14) * COS((unsigned short)item->pos.x_rot)) >> 12;
	LaraBaddieCollision(item, coll);
	//v0 = item->current_anim_state
	lara_collision_routines[item->current_anim_state](item, coll);
	UpdateLaraRoom(item, 0);
	LaraGun();
	TestTriggers(coll->trigger, 0, 0);
#endif
}

void UpdateSubsuitAngles()//4BD20, 4C184 (F)
{
#ifdef PC_VERSION
	if (subsuit.YVel != 0)
	{
		lara_item->pos.y_pos += subsuit.YVel / 4;
		subsuit.YVel = ceil(0.9375 * subsuit.YVel - 1); // YVel * (15/16)
	}

	subsuit.Vel[0] = subsuit.Vel[1] = -4 * lara_item->fallspeed;

	if (subsuit.XRot >= subsuit.dXRot)
	{
		if (subsuit.XRot > subsuit.dXRot)
		{
			if (subsuit.XRot > 0 && subsuit.dXRot < 0)
				subsuit.XRot = ceil(0.75 * subsuit.XRot);

			subsuit.XRot -= ANGLE(2);

			if (subsuit.XRot < subsuit.dXRot)
			{
				subsuit.XRot = subsuit.dXRot;
			}
		}
	}
	else
	{
		if (subsuit.XRot < 0 && subsuit.dXRot > 0)
			subsuit.XRot = ceil(0.75 * subsuit.XRot);

		subsuit.XRot += ANGLE(2);

		if (subsuit.XRot > subsuit.dXRot)
		{
			subsuit.XRot = subsuit.dXRot;
		}
	}

	if (subsuit.dXRot != 0)
	{
		lara_item->pos.x_rot += CLAMP(subsuit.dXRot >> 3, ANGLE(-2), ANGLE(2));
	}

	subsuit.Vel[0] += abs(subsuit.XRot >> 3);
	subsuit.Vel[1] += abs(subsuit.XRot >> 3);

	if (lara.turn_rate > 0)
	{
		subsuit.Vel[0] += 2 * abs(lara.turn_rate);
	}
	else if (lara.turn_rate < 0)
	{
		subsuit.Vel[1] += 2 * abs(lara.turn_rate);
	}

	if (subsuit.Vel[0] > 1536)
		subsuit.Vel[0] = 1536;

	if (subsuit.Vel[1] > 1536)
		subsuit.Vel[1] = 1536;

	if (subsuit.Vel[0] != 0 || subsuit.Vel[1] != 0)
	{
		// todo make the formula clearer
		SoundEffect(SFX_LARA_UNDERWATER_ENGINE, &lara_item->pos, (((subsuit.Vel[0] + subsuit.Vel[1]) * 4) & 0x1F00) + 10);
	}
#endif
}

void SwimTurnSubsuit(struct ITEM_INFO* item)//4BBDC, 4C040 (F)
{
	if (item->pos.y_pos < 14080)
		subsuit.YVel += (14080 - item->pos.y_pos) >> 4;

	if (input & IN_FORWARD && item->pos.x_rot > ANGLE(-85))
	{
		subsuit.dXRot = ANGLE(-45);
	}
	else if(input & IN_BACK && item->pos.x_rot < ANGLE(85))
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
	if (input & IN_FORWARD)
	{
		item->pos.x_rot -= ANGLE(2);
	}
	else if (input & IN_BACK)
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
	UNIMPLEMENTED();
}

void LaraTestWaterDepth(struct ITEM_INFO* item, struct COLL_INFO* coll)//4B4F8(<), 4B95C(<) (F)
{
	int wd;
	struct FLOOR_INFO* floor;
	short room_number;

	room_number = item->room_number;
	floor = GetFloor(item->pos.x_pos, item->pos.y_pos, item->pos.z_pos, &room_number);
	wd = GetWaterDepth(item->pos.x_pos, item->pos.y_pos, item->pos.z_pos, room_number);

	if (wd == -32512)
	{
		item->pos.x_pos = coll->old.x;
		item->pos.y_pos = coll->old.y;
		item->fallspeed = 0;
		item->pos.z_pos = coll->old.z;
	}
	else if(wd < 513)
	{
		//loc_4B580
		item->anim_number = 192;
		item->current_anim_state = 55;
		item->goal_anim_state = 2;
		item->pos.z_rot = 0;
		item->pos.x_rot = 0;
		item->speed = 0;
		item->fallspeed = 0;
		item->gravity_status = 0;
		item->frame_number = anims[192].frame_base;
		lara.water_status = 4;
		item->pos.y_pos = GetHeight(floor, item->pos.x_pos, item->pos.y_pos, item->pos.z_pos);
	}//loc_4B5F0
}