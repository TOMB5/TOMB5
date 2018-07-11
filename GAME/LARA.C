#include "LARA.H"

#include "SPECIFIC.H"
#include "CALCLARA.H"
#include "CAMERA.H"
#include "CONTROL.H"
#include "EFFECTS.H"
#include "COLLIDE.H"
#include "DELSTUFF.H"
#include "DRAW.H"
#include INPUT_H
#include "SOUND.H"
#include "OBJECTS.H"
#include "LARASWIM.H"
#include "LARASURF.H"
#include "LARACLMB.H"
#include "GAMEFLOW.H"
#include "LARAFIRE.H"
#include "CODEWAD.H"

static short LeftClimbTab[4] = // offset 0xA0638
{
	0x0200, 0x0400, 0x0800, 0x0100
};

static short RightClimbTab[4] = // offset 0xA0640
{
	0x0800, 0x0100, 0x0200, 0x0400
};

short angle = 0; // offset 0xA0650
short elevation = 57346; // offset 0xA0652
struct ITEM_INFO* lara_item; // offset 0xA2048
unsigned short DashTimer; // offset 0xA2044
struct lara_info lara; // offset 0xA57DC

void(*lara_control_routines[NUM_LARA_STATES + 1])(struct ITEM_INFO* item, struct COLL_INFO* coll) =
{
	lara_as_walk,
	lara_as_run,
	lara_as_stop,
	lara_as_forwardjump,
	lara_void_func,
	lara_as_fastback,
	lara_as_turn_r,
	lara_as_turn_l,
	lara_as_death,
	lara_as_fastfall,
	lara_as_hang,
	lara_as_reach,
	lara_as_splat,
	lara_as_tread,
	lara_void_func,
	lara_as_compress,
	lara_as_back,
	lara_as_swim,
	lara_as_glide,
	lara_as_null,
	lara_as_fastturn,
	lara_as_stepright,
	lara_as_stepleft,
	lara_void_func,
	lara_as_slide,
	lara_as_backjump,
	lara_as_rightjump,
	lara_as_leftjump,
	lara_as_upjump,
	lara_as_fallback,
	lara_as_hangleft,
	lara_as_hangright,
	lara_as_slideback,
	lara_as_surftread,
	lara_as_surfswim,
	lara_as_dive,
	lara_as_pushblock,
	lara_as_pullblock,
	lara_as_ppready,
	lara_as_pickup,
	lara_as_switchon,
	lara_as_switchoff,
	lara_as_usekey,
	lara_as_usepuzzle,
	lara_as_uwdeath,
	lara_void_func,
	lara_as_special,
	lara_as_surfback,
	lara_as_surfleft,
	lara_as_surfright,
	lara_void_func,
	lara_void_func,
	lara_as_swandive,
	lara_as_fastdive,
	lara_as_gymnast,
	lara_as_waterout,
	lara_as_climbstnc,
	lara_as_climbing,
	lara_as_climbleft,
	lara_as_climbend,
	lara_as_climbright,
	lara_as_climbdown,
	lara_void_func,
	lara_void_func,
	lara_void_func,
	lara_as_wade,
	lara_as_waterroll,
	lara_as_pickupflare,
	lara_void_func,
	lara_void_func,
	lara_as_deathslide,
	lara_as_duck,
	lara_as_duck,
	lara_as_dash,
	lara_as_dashdive,
	lara_as_hang2,
	lara_as_monkeyswing,
	lara_as_monkeyl,
	lara_as_monkeyr,
	lara_as_monkey180,
	lara_as_all4s,
	lara_as_crawl,
	lara_as_hangturnl,
	lara_as_hangturnr,
	lara_as_all4turnl,
	lara_as_all4turnr,
	lara_as_crawlb,
	lara_as_null,
	lara_as_null,
	lara_as_controlled,
	lara_as_ropel,
	lara_as_roper,
	lara_as_controlled,
	lara_as_controlled,
	lara_as_controlled,
	lara_as_controlledl,
	lara_as_controlledl,
	lara_as_controlled,
	lara_as_pickup,
	lara_as_null,
	lara_as_null,
	lara_as_null,
	lara_as_poleleft,
	lara_as_poleright,
	lara_as_pulley,
	lara_as_duckl,
	lara_as_duckr,
	lara_as_extcornerl,
	lara_as_extcornerr,
	lara_as_intcornerl,
	lara_as_intcornerr,
	lara_as_rope,
	lara_as_climbrope,
	lara_as_climbroped,
	lara_as_rope,
	lara_as_rope,
	lara_void_func,
	lara_as_controlled,
	lara_as_swimcheat,
	lara_as_trpose,
	lara_as_null,
	lara_as_trwalk,
	lara_as_trfall,
	lara_as_trfall,
	lara_as_null,
	lara_as_null,
	lara_as_switchon,
	lara_as_null,
	lara_as_parallelbars,
	lara_as_pbleapoff,
	lara_as_null,
	lara_as_null,
	lara_as_null,
	lara_as_null,
	lara_as_null,
	lara_as_null,
	lara_as_null,
	lara_as_null,
	lara_as_null
};

void(*lara_collision_routines[NUM_LARA_STATES + 1])(struct ITEM_INFO* item, struct COLL_INFO* coll) =
{
	lara_col_walk,
	lara_col_run,
	lara_col_stop,
	lara_col_forwardjump,
	lara_col_pose,
	lara_col_fastback,
	lara_col_turn_r,
	lara_col_turn_l,
	lara_col_death,
	lara_col_fastfall,
	lara_col_hang,
	lara_col_reach,
	lara_col_splat,
	lara_col_tread,
	lara_col_land,
	lara_col_compress,
	lara_col_back,
	lara_col_swim,
	lara_col_glide,
	lara_default_col,
	lara_col_fastturn,
	lara_col_stepright,
	lara_col_stepleft,
	lara_col_roll2,
	lara_col_slide,
	lara_col_backjump,
	lara_col_rightjump,
	lara_col_leftjump,
	lara_col_upjump,
	lara_col_fallback,
	lara_col_hangleft,
	lara_col_hangright,
	lara_col_slideback,
	lara_col_surftread,
	lara_col_surfswim,
	lara_col_dive,
	lara_default_col,
	lara_default_col,
	lara_default_col,
	lara_default_col,
	lara_default_col,
	lara_default_col,
	lara_default_col,
	lara_default_col,
	lara_col_uwdeath,
	lara_col_roll,
	lara_void_func,
	lara_col_surfback,
	lara_col_surfleft,
	lara_col_surfright,
	lara_void_func,
	lara_void_func,
	lara_col_swandive,
	lara_col_fastdive,
	lara_default_col,
	lara_default_col,
	lara_col_climbstnc,
	lara_col_climbing,
	lara_col_climbleft,
	lara_col_climbend,
	lara_col_climbright,
	lara_col_climbdown,
	lara_void_func,
	lara_void_func,
	lara_void_func,
	lara_col_wade,
	lara_col_waterroll,
	lara_default_col,
	lara_void_func,
	lara_void_func,
	lara_void_func,
	lara_col_duck,
	lara_col_duck,
	lara_col_dash,
	lara_col_dashdive,
	lara_col_hang2,
	lara_col_monkeyswing,
	lara_col_monkeyl,
	lara_col_monkeyr,
	lara_col_monkey180,
	lara_col_all4s,
	lara_col_crawl,
	lara_col_hangturnlr,
	lara_col_hangturnlr,
	lara_col_all4turnlr,
	lara_col_all4turnlr,
	lara_col_crawlb,
	lara_void_func,
	lara_col_crawl2hang,
	lara_default_col,
	lara_void_func,
	lara_void_func,
	lara_default_col,
	lara_void_func,
	lara_void_func,
	lara_col_turnswitch,
	lara_void_func,
	lara_void_func,
	lara_default_col,
	lara_col_polestat,
	lara_col_poleup,
	lara_col_poledown,
	lara_void_func,
	lara_void_func,
	lara_default_col,
	lara_col_ducklr,
	lara_col_ducklr,
	lara_default_col,
	lara_default_col,
	lara_default_col,
	lara_default_col,
	lara_col_rope,
	lara_void_func,
	lara_void_func,
	lara_col_ropefwd,
	lara_col_ropefwd,
	lara_void_func,
	lara_void_func,
	lara_col_swim,
	lara_default_col,
	lara_default_col,
	lara_default_col,
	lara_default_col,
	lara_default_col,
	lara_default_col,
	lara_default_col,
	lara_default_col,
	lara_default_col,
	lara_default_col,
	lara_default_col,
	lara_void_func,
	lara_void_func,
	lara_void_func,
	lara_void_func,
	lara_void_func,
	lara_void_func,
	lara_void_func,
	lara_void_func,
	lara_void_func
};

void lara_as_pbleapoff(struct ITEM_INFO* item, struct COLL_INFO* coll)//1D244, 1D3D8 (F)
{
	struct ITEM_INFO* pitem = (struct ITEM_INFO*)lara.GeneralPtr;

	item->gravity_status = TRUE;

	if (item->frame_number == anims[item->anim_number].frame_base)
	{
		long Dist;

		if(item->pos.y_rot == pitem->pos.y_rot)
		{
			Dist = pitem->trigger_flags / 100 - 2;
		}
		else
		{
			Dist = pitem->trigger_flags % 100 - 2;
		}

		item->fallspeed = -(20 * Dist + 64);
		item->speed = 20 * Dist + 58;
	}

	if (item->frame_number == anims[item->anim_number].frame_end)
	{
		item->pos.x_pos += 700 * SIN(item->pos.y_rot) >> W2V_SHIFT;
		item->pos.x_pos += 700 * COS(item->pos.y_rot) >> W2V_SHIFT;

		item->anim_number = ANIMATION_LARA_TRY_HANG_SOLID;
		item->frame_number = anims[ANIMATION_LARA_TRY_HANG_SOLID].frame_base;

		item->goal_anim_state = STATE_LARA_REACH;
		item->current_anim_state = STATE_LARA_REACH;
	}
}

void lara_as_parallelbars(struct ITEM_INFO* item, struct COLL_INFO* coll)//1D220(<), 1D3B4(<) (F)
{
	if(!(input & IN_ACTION))
	{
		item->goal_anim_state = STATE_LARA_BARS_JUMP;
	}
}

void lara_as_trfall(struct ITEM_INFO* item, struct COLL_INFO* coll)//1D03C, 1D1D0 (F)
{
	if (item->anim_number == ANIMATION_LARA_TIGHTROPE_FALL_LEFT || item->anim_number == ANIMATION_LARA_TIGHTROPE_FALL_RIGHT)
	{
		if (item->frame_number == anims[item->anim_number].frame_end)
		{
			struct PHD_VECTOR pos;
			pos.x = 0;
			pos.y = 0;
			pos.z = 0;

			GetLaraJointPos(&pos, 6);

			item->pos.x_pos = pos.x;
			item->pos.y_pos = pos.y + 75;
			item->pos.z_pos = pos.z;

			item->goal_anim_state = STATE_LARA_FREEFALL;
			item->current_anim_state = STATE_LARA_FREEFALL;

			item->anim_number = ANIMATION_LARA_FREE_FALL_LONG;
			item->frame_number = anims[ANIMATION_LARA_FREE_FALL_LONG].frame_base;

			item->fallspeed = 81;
			camera.targetspeed = 16;
		}
	}
	else
	{
		int UndoInput, WrongInput;
		int UndoAnim, UndoFrame;

		if (lara.TightRopeOnCount > 0)
			lara.TightRopeOnCount--;

		if (item->anim_number == ANIMATION_LARA_TIGHTROPE_LOOSE_LEFT)
		{
			UndoInput = IN_RIGHT;
			WrongInput = IN_LEFT;

			UndoAnim = ANIMATION_LARA_TIGHTROPE_RECOVER_LEFT;
		}
		else if (item->anim_number == ANIMATION_LARA_TIGHTROPE_LOOSE_RIGHT)
		{
			UndoInput = IN_LEFT;
			WrongInput = IN_RIGHT;

			UndoAnim = ANIMATION_LARA_TIGHTROPE_RECOVER_RIGHT;
		}
		else
		{
			return;
		}

		UndoFrame = anims[item->anim_number].frame_end + anims[UndoAnim].frame_base - item->frame_number;

		if (input & UndoInput && lara.TightRopeOnCount == 0)
		{
			item->current_anim_state = STATE_LARA_TIGHTROPE_RESTORE_BALANCE;
			item->goal_anim_state = STATE_LARA_TIGHTROPE_IDLE;

			item->anim_number = UndoAnim;
			item->frame_number = UndoFrame;

			lara.TightRopeFall--;
		}
		else
		{
			if (input & WrongInput)
			{
				if (lara.TightRopeOnCount < 10)
					lara.TightRopeOnCount += (GetRandomControl() & 3) + 2;
			}
		}
	}
}

void lara_as_trwalk(struct ITEM_INFO* item, struct COLL_INFO* coll)//1CEDC, 1D070 (F)
{
	if (lara.TightRopeOnCount)
	{
		--lara.TightRopeOnCount;
	}
	else if (lara.TightRopeOff)
	{
		short room_number = item->room_number;

		if (GetHeight(GetFloor(item->pos.x_pos, item->pos.y_pos, item->pos.z_pos, &room_number), 
			item->pos.x_pos, item->pos.y_pos, item->pos.z_pos) == item->pos.y_pos)
		{
			lara.TightRopeOff = 0;
			item->goal_anim_state = STATE_LARA_TIGHTROPE_EXIT;
		}
	}
	else
	{
		GetTighRopeFallOff(127);
	}

	if (lara_item->current_anim_state != STATE_LARA_TIGHTROPE_BALANCING_LEFT)
	{
		if (input & IN_LOOK)
		{
			LookUpDown();
		}

		if (item->goal_anim_state != STATE_LARA_TIGHTROPE_EXIT &&
			(lara.TightRopeFall
			|| (input & IN_DOWN || input & IN_ROLL || !(input & IN_UP)) && !lara.TightRopeOnCount && !lara.TightRopeOff))
		{
			item->goal_anim_state = STATE_LARA_TIGHTROPE_IDLE;
		}
	}
}

void lara_as_trpose(struct ITEM_INFO* item, struct COLL_INFO* coll)//1CDE8(<), 1CF7C(<) (F)
{
	if (input & IN_LOOK)
		LookUpDown();

	GetTighRopeFallOff(127);
	if (lara_item->current_anim_state != STATE_LARA_TIGHTROPE_BALANCING_LEFT)
	{
		if (lara.TightRopeFall)
		{
			if (GetRandomControl() & 1)
				item->goal_anim_state = STATE_LARA_TIGHTROPE_BALANCING_RIGHT;
			else
				item->goal_anim_state = STATE_LARA_TIGHTROPE_BALANCING_LEFT;
		}
		else
		{
			if (input & IN_UP)
			{
				item->goal_anim_state = STATE_LARA_TIGHTROPE_FORWARD;
			}
			else if ((input & IN_ROLL) || (input & IN_DOWN))
			{
				if (item->anim_number == ANIMATION_LARA_TIGHTROPE_STAND)
				{
					item->current_anim_state = STATE_LARA_TIGHTROPE_TURNAROUND;
					item->anim_number = ANIMATION_LARA_TIGHTROPE_TURN;
					item->frame_number = anims[ANIMATION_LARA_TIGHTROPE_TURN].frame_base;
					GetTighRopeFallOff(1);
				}
			}
		}
	}
}

void GetTighRopeFallOff(long Regularity)//1CD28, 1CEBC (F)
{
	if (lara_item->hit_points <= 0 || lara_item->hit_status)
	{
		lara_item->goal_anim_state = STATE_LARA_TIGHTROPE_BALANCING_LEFT;
		lara_item->current_anim_state = STATE_LARA_TIGHTROPE_BALANCING_LEFT;
		lara_item->anim_number = ANIMATION_LARA_TIGHTROPE_FALL_LEFT;
		lara_item->frame_number = anims[ANIMATION_LARA_TIGHTROPE_FALL_LEFT].frame_base;
	}

	if (!lara.TightRopeFall && !(GetRandomControl() & Regularity))
		lara.TightRopeFall = 2 - ((GetRandomControl() & 0xF) != 0);
}

void LookLeftRight()//1CB80, 1CD14 (F)
{
	camera.type = LOOK_CAMERA;
	if (input & IN_LEFT)
	{
		input &= ~IN_LEFT;
		if (lara.head_y_rot > ANGLE(-44))
		{
			if (BinocularRange)
				lara.head_y_rot += ANGLE(2) * (BinocularRange - 1792) / 1536;
			else
				lara.head_y_rot -= ANGLE(2);
		}
	}
	else if (input & IN_RIGHT)
	{
		input &= ~IN_RIGHT;
		if (lara.head_y_rot < ANGLE(44))
		{
			if (BinocularRange)
				lara.head_y_rot += ANGLE(2) * (1792 - BinocularRange) / 1536;
			else
				lara.head_y_rot += ANGLE(2);
		}
	}
	if (lara.gun_status != LG_HANDS_BUSY && !lara.left_arm.lock && !lara.right_arm.lock)
		lara.torso_y_rot = lara.head_y_rot;
}

void LookUpDown()//1C9D8, 1CB6C (F)
{
	camera.type = LOOK_CAMERA;
	if (input & IN_UP)
	{
		input &= ~IN_UP;
		if (lara.head_x_rot > ANGLE(-35))
		{
			if (BinocularRange)
				lara.head_x_rot += ANGLE(2) * (BinocularRange - 1792) / 3072;
			else
				lara.head_x_rot -= ANGLE(2);
		}
	}
	else if (input & IN_DOWN)
	{
		input &= ~IN_DOWN;
		if (lara.head_x_rot < ANGLE(30))
		{
			if (BinocularRange)
				lara.head_x_rot += ANGLE(2) * (1792 - BinocularRange) / 3072;
			else
				lara.head_x_rot += ANGLE(2);
		}
	}
	if (lara.gun_status != LG_HANDS_BUSY && !lara.left_arm.lock && !lara.right_arm.lock)
		lara.torso_x_rot = lara.head_x_rot;
}

void ResetLook()//1C920, 1CA54 (F)
{
	if (camera.type != 2)
	{
		if (lara.head_x_rot <= ANGLE(-2) || lara.head_x_rot >= ANGLE(2))
			lara.head_x_rot = lara.head_x_rot / -8 + lara.head_x_rot;
		else
			lara.head_x_rot = 0;

		if (lara.head_y_rot <= ANGLE(-2) || lara.head_y_rot >= ANGLE(2))
			lara.head_y_rot = lara.head_y_rot / -8 + lara.head_y_rot;
		else
			lara.head_y_rot = 0;

		if (lara.gun_status == LG_HANDS_BUSY || lara.left_arm.lock || lara.right_arm.lock)
		{
			if (!lara.head_x_rot)
				lara.torso_x_rot = 0;
			if (!lara.head_y_rot)
				lara.torso_y_rot = 0;
		}
		else
		{
			lara.torso_y_rot = lara.head_y_rot;
			lara.torso_x_rot = lara.head_x_rot;
		}
	}
}

void lara_col_jumper(struct ITEM_INFO* item, struct COLL_INFO* coll)//1C860(<), 1C994(<) (F)
{
	coll->bad_pos = 32512;
	coll->bad_neg = -384;
	coll->bad_ceiling = 192;

	GetLaraCollisionInfo(item, coll);
	LaraDeflectEdgeJump(item, coll);

	if (item->fallspeed > 0 && coll->mid_floor <= 0)
	{
		if (LaraLandedBad(item, coll))
			item->goal_anim_state = STATE_LARA_DEATH;
		else
			item->goal_anim_state = STATE_LARA_STOP;

		item->fallspeed = 0;
		item->gravity_status = 0;

		if (coll->mid_floor != -32512)
			item->pos.y_pos += coll->mid_floor;
	}
}

void lara_default_col(struct ITEM_INFO* item, struct COLL_INFO* coll)//1C80C(<), 1C940(<) (F)
{
	lara.move_angle = item->pos.y_rot;
	coll->bad_pos = 384;
	coll->bad_neg = -384;
	coll->bad_ceiling = 0;
	coll->slopes_are_pits = 1;
	coll->slopes_are_walls = 1;
	GetLaraCollisionInfo(item, coll);
}

void lara_col_wade(struct ITEM_INFO* item, struct COLL_INFO* coll)//1C61C, 1C750 (F)
{
	lara.move_angle = item->pos.y_rot;

	coll->bad_pos = 32512;
	coll->bad_neg = -384;
	coll->bad_ceiling = 0;

	coll->slopes_are_walls = 1;

	GetLaraCollisionInfo(item, coll);

	if (!LaraHitCeiling(item, coll) && !TestLaraVault(item, coll))
	{
		if (LaraDeflectEdge(item, coll))
		{
			item->pos.z_rot = 0;

			if ((coll->front_type == CT_NONE || coll->front_type == CT_RIGHT) && coll->front_floor < -640)
			{
				item->current_anim_state = STATE_LARA_SPLAT;

				if (item->frame_number >= 0 && item->frame_number <= 9)
				{
					item->anim_number = ANIMATION_LARA_WALL_SMASH_LEFT;
					item->frame_number = anims[ANIMATION_LARA_WALL_SMASH_LEFT].frame_base;
					return;
				}

				if (item->frame_number >= 10 && item->frame_number <= 21)
				{
					item->anim_number = ANIMATION_LARA_WALL_SMASH_RIGHT;
					item->frame_number = anims[ANIMATION_LARA_WALL_SMASH_RIGHT].frame_base;
					return;
				}
			}

			LaraCollideStop(item, coll);
		}

		if (coll->mid_floor >= -384 && coll->mid_floor < -128)
		{
			if (item->frame_number >= 3 && item->frame_number <= 14)
			{
				item->anim_number = ANIMATION_LARA_RUN_UP_STEP_LEFT;
				item->frame_number = anims[ANIMATION_LARA_RUN_UP_STEP_LEFT].frame_base;
			}
			else
			{
				item->anim_number = ANIMATION_LARA_RUN_UP_STEP_RIGHT;
				item->frame_number = anims[ANIMATION_LARA_RUN_UP_STEP_RIGHT].frame_base;
			}
		}

		if (coll->mid_floor < 50)
		{
			if (coll->mid_floor != -32512)
				item->pos.y_pos += coll->mid_floor;
		}
		else
		{
			item->pos.y_pos += 50;
		}
	}
}

void lara_col_fastdive(struct ITEM_INFO* item, struct COLL_INFO* coll)//1C558(<), 1C68C(<) (F)
{
	lara.move_angle = item->pos.y_rot;

	coll->bad_pos = 32512;
	coll->bad_neg = -384;
	coll->bad_ceiling = 192;

	GetLaraCollisionInfo(item, coll);
	LaraDeflectEdgeJump(item, coll);

	if (coll->mid_floor <= 0 && item->fallspeed > 0)
	{
		if (item->fallspeed <= 133)
			item->goal_anim_state = STATE_LARA_STOP;
		else
			item->goal_anim_state = STATE_LARA_DEATH;

		item->fallspeed = 0;
		item->gravity_status = 0;

		if (coll->mid_floor != -32512)
			item->pos.y_pos += coll->mid_floor;
	}
}

void lara_col_swandive(struct ITEM_INFO* item, struct COLL_INFO* coll)//1C4A0(<), 1C5D4(<) (F)
{
	lara.move_angle = item->pos.y_rot;

	coll->bad_pos = 32512;
	coll->bad_neg = -384;
	coll->bad_ceiling = 192;

	GetLaraCollisionInfo(item, coll);
	LaraDeflectEdgeJump(item, coll);

	if (coll->mid_floor <= 0 && item->fallspeed > 0)
	{
		item->goal_anim_state = STATE_LARA_STOP;

		item->fallspeed = 0;
		item->gravity_status = 0;

		if (coll->mid_floor != -32512)
			item->pos.y_pos += coll->mid_floor;
	}
}

void lara_col_roll2(struct ITEM_INFO* item, struct COLL_INFO* coll)//1C384, 1C4B8 (F)
{
	camera.lara_node = 0;

	item->gravity_status = FALSE;
	item->fallspeed = 0;

	lara.move_angle = item->pos.y_rot - ANGLE(180);

	coll->slopes_are_walls = 1;

	coll->bad_pos = 32512;
	coll->bad_neg = -384;
	coll->bad_ceiling = 0;

	GetLaraCollisionInfo(item, coll);

	if (!LaraHitCeiling(item, coll) && !TestLaraSlide(item, coll))
	{
		if (coll->mid_floor <= 200)
		{
			ShiftItem(item, coll);

			if (coll->mid_floor != -32512)
				item->pos.y_pos += coll->mid_floor;
		}
		else
		{
			item->fallspeed = 0;

			item->anim_number = ANIMATION_LARA_FREE_FALL_BACK;
			item->frame_number = anims[ANIMATION_LARA_FREE_FALL_BACK].frame_base;
			item->current_anim_state = STATE_LARA_FALL_BACKWARD;
			item->goal_anim_state = STATE_LARA_FALL_BACKWARD;

			item->gravity_status = TRUE;
		}
	}
}

void lara_col_roll(struct ITEM_INFO* item, struct COLL_INFO* coll)//1C2B0, 1C3E4 (F)
{
	lara.move_angle = item->pos.y_rot;

	coll->bad_pos = 32512;
	coll->bad_neg = -384;
	coll->bad_ceiling = 0;

	item->gravity_status = FALSE;
	item->fallspeed = 0;

	coll->slopes_are_pits = 0;
	coll->slopes_are_walls = 1;

	GetLaraCollisionInfo(item, coll);

	if (!LaraHitCeiling(item, coll))
	{
		if (!TestLaraSlide(item, coll))
		{
			if (!LaraFallen(item, coll))
			{
				ShiftItem(item, coll);

				if (coll->mid_floor != -32512)
					item->pos.y_pos += coll->mid_floor;
			}
		}
	}
}

void lara_col_slideback(struct ITEM_INFO* item, struct COLL_INFO* coll)//1C284(<), 1C3B8(<) (F)
{
	lara.move_angle = item->pos.y_rot - ANGLE(180);
	lara_slide_slope(item, coll);
}

void lara_col_fallback(struct ITEM_INFO* item, struct COLL_INFO* coll)//1C1B4(<), 1C2E8(<) (F)
{
	lara.move_angle = item->pos.y_rot - ANGLE(180);

	coll->bad_pos = 32512;
	coll->bad_neg = -384;
	coll->bad_ceiling = 192;

	GetLaraCollisionInfo(item, coll);
	LaraDeflectEdgeJump(item, coll);

	if (item->fallspeed > 0 && coll->mid_floor <= 0)
	{
		if (LaraLandedBad(item, coll))
			item->goal_anim_state = STATE_LARA_DEATH;
		else
			item->goal_anim_state = STATE_LARA_STOP;

		item->fallspeed = 0;
		item->gravity_status = 0;

		if (coll->mid_floor != -32512)
			item->pos.y_pos += coll->mid_floor;
	}
}

void lara_col_leftjump(struct ITEM_INFO* item, struct COLL_INFO* coll)//1C188(<), 1C2BC(<) (F)
{
	lara.move_angle = item->pos.y_rot - ANGLE(90);
	lara_col_jumper(item, coll);
}

void lara_col_rightjump(struct ITEM_INFO* item, struct COLL_INFO* coll)//1C15C(<), 1C290(<) (F)
{
	lara.move_angle = item->pos.y_rot + ANGLE(90);
	lara_col_jumper(item, coll);
}

void lara_col_backjump(struct ITEM_INFO* item, struct COLL_INFO* coll)//1C130(<), 1C264(<) (F)
{
	lara.move_angle = item->pos.y_rot - ANGLE(180);
	lara_col_jumper(item, coll);
}

void lara_col_slide(struct ITEM_INFO* item, struct COLL_INFO* coll)//1C108(<), 1C23C(<) (F)
{
	lara.move_angle = item->pos.y_rot;
	lara_slide_slope(item, coll);
}

void lara_col_stepleft(struct ITEM_INFO* item, struct COLL_INFO* coll)//1C0E8(<), 1C21C(<) (F)
{
	lara_col_stepright(item, coll);
}

void lara_col_stepright(struct ITEM_INFO* item, struct COLL_INFO* coll)//1BFB0, 1C0E4 (F)
{
	if (item->current_anim_state == STATE_LARA_WALK_RIGHT)
		lara.move_angle = item->pos.y_rot + ANGLE(90);
	else
		lara.move_angle = item->pos.y_rot - ANGLE(90);

	item->gravity_status = FALSE;
	item->fallspeed = 0;

	if (lara.water_status == 4)
		coll->bad_pos = 32512;
	else
		coll->bad_pos = 128;

	coll->slopes_are_walls = 1;
	coll->slopes_are_pits = 1;

	coll->bad_neg = -128;
	coll->bad_ceiling = 0;

	GetLaraCollisionInfo(item, coll);

	if (!LaraHitCeiling(item, coll))
	{
		if (LaraDeflectEdge(item, coll))
			LaraCollideStop(item, coll);

		if (!LaraFallen(item, coll) && !TestLaraSlide(item, coll) && coll->mid_floor != -32512)
			item->pos.y_pos += coll->mid_floor;
	}
}

void lara_col_back(struct ITEM_INFO* item, struct COLL_INFO* coll)//1BE38, 1BF6C (F)
{
	item->gravity_status = FALSE;
	item->fallspeed = 0;

	lara.move_angle = item->pos.y_rot - ANGLE(180);

	if (lara.water_status == 4)
		coll->bad_pos = 32512;
	else
		coll->bad_pos = 384;

	coll->bad_neg = -384;
	coll->bad_ceiling = 0;
	
	coll->slopes_are_pits = 1;
	coll->slopes_are_walls = 1;

	GetLaraCollisionInfo(item, coll);

	if (!LaraHitCeiling(item, coll))
	{
		if (LaraDeflectEdge(item, coll))
			LaraCollideStop(item, coll);

		if (!LaraFallen(item, coll))
		{
			if (coll->mid_floor > 128 && coll->mid_floor < 384)
			{
				if (item->frame_number >= 964 && item->frame_number <= 993)
				{
					item->anim_number = ANIMATION_LARA_WALK_DOWN_BACK_RIGHT;
					item->frame_number = anims[ANIMATION_LARA_WALK_DOWN_BACK_RIGHT].frame_base;
				}
				else
				{
					item->anim_number = ANIMATION_LARA_WALK_DOWN_BACK_LEFT;
					item->frame_number = anims[ANIMATION_LARA_WALK_DOWN_BACK_LEFT].frame_base;
				}
			}

			if (!TestLaraSlide(item, coll) && coll->mid_floor != -32512)
				item->pos.y_pos += coll->mid_floor;
		}
	}
}

void lara_col_compress(struct ITEM_INFO* item, struct COLL_INFO* coll)//1BD30, 1BE64 (F)
{
	item->fallspeed = 0;
	item->gravity_status = FALSE;

	coll->bad_pos = 32512;
	coll->bad_neg = -32512;
	coll->bad_ceiling = 0;

	GetLaraCollisionInfo(item, coll);

	if (!LaraFallen(item, coll))
	{
		if (coll->mid_ceiling > -100)
		{
			item->anim_number = ANIMATION_LARA_STAY_SOLID;
			item->frame_number = anims[ANIMATION_LARA_STAY_SOLID].frame_base;
			item->goal_anim_state = STATE_LARA_STOP;
			item->current_anim_state = STATE_LARA_STOP;
			
			item->speed = 0;
			item->fallspeed = 0;
			item->gravity_status = FALSE;

			item->pos.x_pos = coll->old.x;
			item->pos.y_pos = coll->old.y;
			item->pos.z_pos = coll->old.z;
		}

		if (coll->mid_floor > -256 && coll->mid_floor < 256)
			item->pos.y_pos += coll->mid_floor;
	}
}

void lara_col_land(struct ITEM_INFO* item, struct COLL_INFO* coll)//1BD10(<), 1BE44(<) (F)
{
	lara_col_stop(item, coll);
}

void lara_col_splat(struct ITEM_INFO* item, struct COLL_INFO* coll)//1BC74(<), 1BDA8(<) (F)
{
	lara.move_angle = item->pos.y_rot;

	coll->slopes_are_walls = 1;
	coll->slopes_are_pits = 1;

	coll->bad_pos = 384;
	coll->bad_neg = -384;
	coll->bad_ceiling = 0;

	GetLaraCollisionInfo(item, coll);
	ShiftItem(item, coll);

	if (coll->mid_floor >= -256 && coll->mid_floor <= 256)
		item->pos.y_pos += coll->mid_floor;
}

void lara_col_fastfall(struct ITEM_INFO* item, struct COLL_INFO* coll)//1BB88, 1BCBC (F)
{
	item->gravity_status = TRUE;

	coll->bad_pos = 32512;
	coll->bad_neg = -384;
	coll->bad_ceiling = 192;

	GetLaraCollisionInfo(item, coll);
	LaraSlideEdgeJump(item, coll);

	if (coll->mid_floor <= 0)
	{
		if (LaraLandedBad(item, coll))
		{
			item->goal_anim_state = STATE_LARA_DEATH;
		}
		else
		{
			item->goal_anim_state = STATE_LARA_STOP;
			item->current_anim_state = STATE_LARA_STOP;
			item->anim_number = ANIMATION_LARA_LANDING_HARD;
			item->frame_number = anims[ANIMATION_LARA_LANDING_HARD].frame_base;
		}

		StopSoundEffect(SFX_LARA_FALL);

		item->fallspeed = 0;
		item->gravity_status = FALSE;

		if (coll->mid_floor != -32512)
			item->pos.y_pos += coll->mid_floor;
	}
}

void lara_col_death(struct ITEM_INFO* item, struct COLL_INFO* coll)//1BADC(<), 1BC10(<) (F)
{
	StopSoundEffect(SFX_LARA_FALL);

	lara.move_angle = item->pos.y_rot;
	coll->bad_pos = 384;
	coll->bad_neg = -384;
	coll->bad_ceiling = 0;
	coll->radius = 400;

	GetLaraCollisionInfo(item, coll);
	ShiftItem(item, coll);

	item->hit_points = -1;
	lara.air = -1;

	if (coll->mid_floor != -32512)
		item->pos.y_pos += coll->mid_floor;
}

void lara_col_turn_l(struct ITEM_INFO* item, struct COLL_INFO* coll)//1BABC(<), 1BBF0(<) (F)
{
	lara_col_turn_r(item, coll);
}

void lara_col_turn_r(struct ITEM_INFO* item, struct COLL_INFO* coll)//1B9C4, 1BAF8 (F)
{
	item->fallspeed = 0;
	item->gravity_status = FALSE;

	lara.move_angle = item->pos.y_rot;

	coll->slopes_are_walls = 1;
	coll->slopes_are_pits = 1;
	coll->bad_pos = 384;
	coll->bad_neg = -384;
	coll->bad_ceiling = 0;

	GetLaraCollisionInfo(item, coll);

	if (coll->mid_floor <= 100)
	{
		if (!TestLaraSlide(item, coll) && coll->mid_floor != -32512)
			item->pos.y_pos += coll->mid_floor;
	}
	else
	{
		item->fallspeed = 0;
		item->anim_number = ANIMATION_LARA_FREE_FALL_FORWARD;
		item->frame_number = anims[ANIMATION_LARA_FREE_FALL_FORWARD].frame_base;
		item->current_anim_state = STATE_LARA_JUMP_FORWARD;
		item->goal_anim_state = STATE_LARA_JUMP_FORWARD;
		item->gravity_status = TRUE;
	}
}

void lara_col_fastback(struct ITEM_INFO* item, struct COLL_INFO* coll)//1B89C, 1B9D0 (F)
{
	item->fallspeed = 0;
	item->gravity_status = FALSE;

	lara.move_angle = item->pos.y_rot - ANGLE(180);

	coll->slopes_are_walls = 0;
	coll->slopes_are_pits = 1;

	coll->bad_pos = 32512;
	coll->bad_neg = -384;
	coll->bad_ceiling = 0;

	GetLaraCollisionInfo(item, coll);

	if (!LaraHitCeiling(item, coll))
	{
		if (coll->mid_floor <= 200)
		{
			if (LaraDeflectEdge(item, coll))
				LaraCollideStop(item, coll);

			if (!TestLaraSlide(item, coll) && coll->mid_floor != -32512)
				item->pos.y_pos += coll->mid_floor;
		}
		else
		{
			item->fallspeed = 0;

			item->anim_number = ANIMATION_LARA_FREE_FALL_BACK;
			item->frame_number = anims[ANIMATION_LARA_FREE_FALL_BACK].frame_base;
			item->current_anim_state = STATE_LARA_FALL_BACKWARD;
			item->goal_anim_state = STATE_LARA_FALL_BACKWARD;

			item->gravity_status = TRUE;
		}
	}
}

void lara_col_pose(struct ITEM_INFO* item, struct COLL_INFO* coll)//1B87C(<), 1B9B0(<) (F)
{
	lara_col_stop(item, coll);
}

void lara_col_run(struct ITEM_INFO* item, struct COLL_INFO* coll)//1B64C, 1B780 (F)
{
	lara.move_angle = item->pos.y_rot;

	coll->bad_pos = 32512;
	coll->bad_neg = -384;
	coll->bad_ceiling = 0;

	coll->slopes_are_walls = 1;

	GetLaraCollisionInfo(item, coll);

	if (!LaraHitCeiling(item, coll) && !TestLaraVault(item, coll))
	{
		if (LaraDeflectEdge(item, coll))
		{
			item->pos.z_rot = 0;

			if (item->anim_number != ANIMATION_LARA_STAY_TO_RUN && TestWall(item, 256, 0, -640))
			{
				item->current_anim_state = STATE_LARA_SPLAT;

				if (item->frame_number >= 0 && item->frame_number <= 9)
				{
					item->anim_number = ANIMATION_LARA_WALL_SMASH_LEFT;
					item->frame_number = anims[ANIMATION_LARA_WALL_SMASH_LEFT].frame_base;

					return;
				}

				if (item->frame_number >= 10 && item->frame_number <= 21)
				{
					item->anim_number = ANIMATION_LARA_WALL_SMASH_RIGHT;
					item->frame_number = anims[ANIMATION_LARA_WALL_SMASH_RIGHT].frame_base;

					return;
				}
			}

			LaraCollideStop(item, coll);
		}

		if (!LaraFallen(item, coll))
		{
			if (coll->mid_floor >= -384 && coll->mid_floor < -128)
			{
				if (coll->front_floor == -32512 || coll->front_floor < -384 || coll->front_floor >= -128)
				{
					coll->mid_floor = 0;
				}
				else
				{
					if (item->frame_number >= 3 && item->frame_number <= 14)
					{
						item->anim_number = ANIMATION_LARA_RUN_UP_STEP_LEFT;
						item->frame_number = anims[ANIMATION_LARA_RUN_UP_STEP_LEFT].frame_base;
					}
					else
					{
						item->anim_number = ANIMATION_LARA_RUN_UP_STEP_RIGHT;
						item->frame_number = anims[ANIMATION_LARA_RUN_UP_STEP_RIGHT].frame_base;
					}
				}
			}

			if (!TestLaraSlide(item, coll))
			{
				if (coll->mid_floor < 50)
				{
					if (coll->mid_floor != -32512)
						item->pos.y_pos += coll->mid_floor;
				}
				else
				{
					item->pos.y_pos += 50;
				}
			}
		}
	}
}

void lara_col_walk(struct ITEM_INFO* item, struct COLL_INFO* coll)//1B3E8, 1B51C (F)
{
	item->gravity_status = FALSE;
	item->fallspeed = 0;

	lara.move_angle = item->pos.y_rot;

	coll->bad_pos = 384;
	coll->bad_neg = -384;
	coll->bad_ceiling = 0;

	coll->slopes_are_walls = 1;
	coll->slopes_are_pits = 1;
	coll->lava_is_pit = 1;

	GetLaraCollisionInfo(item, coll);

	if (!LaraHitCeiling(item, coll) && !TestLaraVault(item, coll))
	{
		if (LaraDeflectEdge(item, coll))
		{
			if (item->frame_number >= 29 && item->frame_number <= 47)
			{
				item->anim_number = ANIMATION_LARA_END_WALK_LEFT;
				item->frame_number = anims[ANIMATION_LARA_END_WALK_LEFT].frame_base;
			}
			else
			{
				if (item->frame_number >= 22 && item->frame_number <= 28 || 
					item->frame_number >= 48 && item->frame_number <= 57)
				{
					item->anim_number = ANIMATION_LARA_END_WALK_RIGHT;
					item->frame_number = anims[ANIMATION_LARA_END_WALK_RIGHT].frame_base;
				}
				else
				{
					LaraCollideStop(item, coll);
				}
			}
		}

		if (!LaraFallen(item, coll))
		{
			if (coll->mid_floor > 128)
			{
				if (coll->front_floor == -32512 || coll->front_floor <= 128)
				{
					coll->mid_floor = 0;
				}
				else
				{
					if (item->frame_number >= 28 && item->frame_number <= 45)
					{
						item->anim_number = ANIMATION_LARA_WALK_DOWN_LEFT;
						item->frame_number = anims[ANIMATION_LARA_WALK_DOWN_LEFT].frame_base;
					}
					else
					{
						item->anim_number = ANIMATION_LARA_WALK_DOWN_RIGHT;
						item->frame_number = anims[ANIMATION_LARA_WALK_DOWN_RIGHT].frame_base;
					}
				}
			}
			if (coll->mid_floor >= -384 && coll->mid_floor < -128)
			{
				if (coll->front_floor == -32512 || 
					coll->front_floor < -384 || 
					coll->front_floor >= -128)
				{
					coll->mid_floor = 0;
				}
				else
				{
					if (item->frame_number >= 27 && item->frame_number <= 44)
					{
						item->anim_number = ANIMATION_LARA_WALK_UP_STEP_LEFT;
						item->frame_number = anims[ANIMATION_LARA_WALK_UP_STEP_LEFT].frame_base;
					}
					else
					{
						item->anim_number = ANIMATION_LARA_WALK_UP_STEP_RIGHT;
						item->frame_number = anims[ANIMATION_LARA_WALK_UP_STEP_RIGHT].frame_base;
					}
				}
			}

			if (!TestLaraSlide(item, coll) && coll->mid_floor != -32512)
				item->pos.y_pos += coll->mid_floor;
		}
	}
}

void lara_as_pulley(struct ITEM_INFO* item, struct COLL_INFO* coll)//1B288, 1B3BC (F)
{
	struct ITEM_INFO* p = (struct ITEM_INFO*) lara.GeneralPtr;

	lara.look = FALSE;

	coll->enable_spaz = FALSE;
	coll->enable_baddie_push = FALSE;

	if (input & IN_ACTION && p->trigger_flags)
	{
		item->goal_anim_state = STATE_LARA_PULLEY;
	}
	else
	{
		item->goal_anim_state = STATE_LARA_STOP;
	}

	if (item->anim_number == ANIMATION_LARA_PULLEY_PULL && item->frame_number == anims[ANIMATION_LARA_PULLEY_PULL].frame_base + 44)
	{
		if (p->trigger_flags)
		{
			p->trigger_flags--;

			if (p->trigger_flags)
			{
				if (p->item_flags[2])
				{
					p->item_flags[2] = 0;
					p->status = ITEM_DEACTIVATED;
				}
			}
			else
			{
				if (!p->item_flags[1])
					p->status = ITEM_DEACTIVATED;

				p->item_flags[2] = 1;

				if (p->item_flags[3] >= 0)
					p->trigger_flags = abs(p->item_flags[3]);
				else
					p->item_flags[0] = 1;
			}
		}
	}

	if (item->anim_number == ANIMATION_LARA_PULLEY_UNGRAB && item->frame_number == anims[ANIMATION_LARA_PULLEY_UNGRAB].frame_end - 1)
		lara.gun_status = LG_NO_ARMS;
}

void lara_col_turnswitch(struct ITEM_INFO* item, struct COLL_INFO* coll)//1B1B4(<), 1B2E8(<) (F)
{
	if (coll->old.x != item->pos.x_pos || coll->old.z != item->pos.z_pos)
	{
		if (item->anim_number == ANIMATION_LARA_ROUND_HANDLE_PUSH_LEFT_CONTINUE)
		{
			item->pos.y_rot -= ANGLE(90);

			item->anim_number = ANIMATION_LARA_ROUND_HANDLE_PUSH_LEFT_END;
			item->frame_number = anims[ANIMATION_LARA_ROUND_HANDLE_PUSH_LEFT_END].frame_base;
		}

		if (item->anim_number == ANIMATION_LARA_ROUND_HANDLE_PUSH_RIGHT_CONTINUE)
		{
			item->pos.y_rot += ANGLE(90);

			item->anim_number = ANIMATION_LARA_ROUND_HANDLE_PUSH_RIGHT_END;
			item->frame_number = anims[ANIMATION_LARA_ROUND_HANDLE_PUSH_RIGHT_END].frame_base;
		}
	}
}

void lara_as_controlledl(struct ITEM_INFO* item, struct COLL_INFO* coll)//1B180(<), 1B2B4(<) (F)
{
	lara.look = FALSE;
	coll->enable_baddie_push = FALSE;
	coll->enable_spaz = FALSE;
}

void lara_as_controlled(struct ITEM_INFO* item, struct COLL_INFO* coll)//1B0FC(<), 1B230(<) (F)
{
	lara.look = FALSE;
	coll->enable_baddie_push = FALSE;
	coll->enable_spaz = FALSE;
	if (item->frame_number == anims[item->anim_number].frame_end - 1)
	{
		lara.gun_status = LG_NO_ARMS;
		if (UseForcedFixedCamera)
			UseForcedFixedCamera = 0;
	}
}

void lara_as_deathslide(struct ITEM_INFO* item, struct COLL_INFO* coll)//1B038, 1B16C (F)
{
	short room_number = item->room_number;

	camera.target_angle = ANGLE(70);

	GetHeight(GetFloor(item->pos.x_pos, item->pos.y_pos, item->pos.z_pos, &room_number), 
		item->pos.x_pos, item->pos.y_pos, item->pos.z_pos);

	coll->trigger = trigger_index;

	if (!(input & IN_ACTION))
	{
		item->goal_anim_state = STATE_LARA_JUMP_FORWARD;

		AnimateLara(item);

		lara_item->gravity_status = TRUE;
		lara_item->speed = 100;
		lara_item->fallspeed = 40;

		lara.move_angle = item->pos.y_rot;
	}
}

void lara_as_wade(struct ITEM_INFO* item, struct COLL_INFO* coll)//1AF10, 1B044 (F)
{
	if (item->hit_points <= 0)
	{
		item->goal_anim_state = STATE_LARA_STOP;

		return;
	}

	camera.target_elevation = ANGLE(-22);

	if (input & IN_LEFT)
	{
		lara.turn_rate -= 409;
		if (lara.turn_rate < ANGLE(-8))
			lara.turn_rate = ANGLE(-8);

		item->pos.z_rot -= ANGLE(1.5);
		if (item->pos.z_rot < ANGLE(-11))
			item->pos.z_rot = ANGLE(-11);
	}
	else if (input & IN_RIGHT)
	{
		lara.turn_rate += 409;
		if (lara.turn_rate > ANGLE(8))
			lara.turn_rate = ANGLE(8);

		item->pos.z_rot += ANGLE(1.5);
		if (item->pos.z_rot > ANGLE(11))
			item->pos.z_rot = ANGLE(11);
	}

	if (input & IN_UP)
	{
		if (lara.water_status == LW_ABOVE_WATER)
			item->goal_anim_state = STATE_LARA_RUN_FORWARD;
		else
			item->goal_anim_state = STATE_LARA_WADE_FORWARD;
	}
	else
	{
		item->goal_anim_state = STATE_LARA_STOP;
	}
}

void lara_as_waterout(struct ITEM_INFO* item, struct COLL_INFO* coll)//1AEE4(<), 1B018(<) (F)
{
	coll->enable_baddie_push = FALSE;
	coll->enable_spaz = FALSE;
	camera.flags = CF_FOLLOW_CENTER;
}

void lara_as_gymnast(struct ITEM_INFO* item, struct COLL_INFO* coll)//1AEC8(<), 1AFFC(<) (F)
{
	coll->enable_baddie_push = FALSE;
	coll->enable_spaz = FALSE;
}

void lara_as_fastdive(struct ITEM_INFO* item, struct COLL_INFO* coll)//1AE4C(<), 1AF80(<) (F)
{
	if (input & IN_ROLL && item->goal_anim_state == STATE_LARA_SWANDIVE_END)
		item->goal_anim_state = STATE_LARA_JUMP_ROLL;
	coll->enable_baddie_push = TRUE;
	coll->enable_spaz = FALSE;
	item->speed = (item->speed * 95) / 100;
}

void lara_as_swandive(struct ITEM_INFO* item, struct COLL_INFO* coll)//1AE08(<), 1AF3C(<) (F)
{
	coll->enable_baddie_push = TRUE;
	coll->enable_spaz = FALSE;
	if (item->fallspeed > LARA_FREEFALL_SPEED && item->goal_anim_state != STATE_LARA_UNDERWATER_DIVING)
		item->goal_anim_state = STATE_LARA_SWANDIVE_END;
}

void lara_as_special(struct ITEM_INFO* item, struct COLL_INFO* coll)//1ADDC(<), 1AF10(<) (F)
{
	camera.flags = CF_FOLLOW_CENTER;
	camera.target_angle = ANGLE(170);
	camera.target_elevation = ANGLE(-25);
}

void lara_as_usepuzzle(struct ITEM_INFO* item, struct COLL_INFO* coll)//1AD18(<), 1AE4C(<) (F)
{
	lara.look = FALSE;

	coll->enable_baddie_push = FALSE;
	coll->enable_spaz = FALSE;

	camera.target_angle = ANGLE(-80);
	camera.target_elevation = ANGLE(-25);
	camera.target_distance = SECTOR(1);

	if (item->frame_number == anims[item->anim_number].frame_end)
	{
		if (item->item_flags[0])
		{
			item->anim_number = item->item_flags[0];
			item->current_anim_state = STATE_LARA_MISC_CONTROL;
			item->frame_number = anims[item->item_flags[0]].frame_base;
		}
	}
}

void lara_as_usekey(struct ITEM_INFO* item, struct COLL_INFO* coll)//1ACBC(<), 1ADF0(<) (F)
{
	lara.look = 0;
	coll->enable_baddie_push = FALSE;
	coll->enable_spaz = FALSE;
	camera.target_angle = ANGLE(-80);
	camera.target_elevation = -4550;
	camera.target_distance = SECTOR(1);
}

void lara_as_switchoff(struct ITEM_INFO* item, struct COLL_INFO* coll)//1AC54(<), 1AD88(<) (F)
{
	lara.look = 0;
	coll->enable_baddie_push = FALSE;
	coll->enable_spaz = FALSE;
	camera.target_angle = ANGLE(80);
	camera.target_elevation = ANGLE(-25);
	camera.target_distance = SECTOR(1);
	camera.speed = 6;
}

void lara_as_switchon(struct ITEM_INFO* item, struct COLL_INFO* coll)//1ABEC(<), 1AD20(<) (F)
{
	lara.look = 0;
	coll->enable_baddie_push = FALSE;
	coll->enable_spaz = FALSE;
	camera.target_angle = ANGLE(80);
	camera.target_elevation = ANGLE(-25);
	camera.target_distance = SECTOR(1);
	camera.speed = 6;
}

void lara_as_pickupflare(struct ITEM_INFO* item, struct COLL_INFO* coll)//1AB5C(<), 1AC90(<) (F)
{
	lara.look = 0;
	coll->enable_baddie_push = FALSE;
	coll->enable_spaz = FALSE;
	camera.target_angle = ANGLE(130);
	camera.target_elevation = ANGLE(-15);
	camera.target_distance = SECTOR(1);
	if (item->frame_number = anims[item->anim_number].frame_end - 1)
		lara.gun_status = LG_NO_ARMS;
}

void lara_as_pickup(struct ITEM_INFO* item, struct COLL_INFO* coll)//1AB00(<), 1AC34(<) (F)
{
	lara.look = 0;
	coll->enable_baddie_push = FALSE;
	coll->enable_spaz = FALSE;
	camera.target_angle = ANGLE(-130);
	camera.target_elevation = ANGLE(-15);
	camera.target_distance = SECTOR(1);
}

void lara_as_ppready(struct ITEM_INFO* item, struct COLL_INFO* coll)//1AABC(<), 1ABF0(<) (F)
{
	coll->enable_baddie_push = FALSE;
	coll->enable_spaz = FALSE;
	camera.target_angle = ANGLE(75);
	if(!(input & IN_ACTION))
		item->goal_anim_state = STATE_LARA_STOP;
}

void lara_as_pullblock(struct ITEM_INFO* item, struct COLL_INFO* coll)//1AA60(<), 1AB94(<) (F)
{
	lara.look = 0;
	coll->enable_baddie_push = FALSE;
	coll->enable_spaz = FALSE;
	camera.flags = CF_FOLLOW_CENTER;
	camera.target_angle = ANGLE(35);
	camera.target_elevation = -4550;
}

void lara_as_pushblock(struct ITEM_INFO* item, struct COLL_INFO* coll)//1AA04(<), 1AB38(<) (F)
{
	lara.look = 0;
	coll->enable_baddie_push = FALSE;
	coll->enable_spaz = FALSE;
	camera.flags = CF_FOLLOW_CENTER;
	camera.target_angle = ANGLE(90);
	camera.target_elevation = -4550;
}

void lara_as_slideback(struct ITEM_INFO* item, struct COLL_INFO* coll)//1A9E0(<), 1AB14(<) (F)
{
	if ((input & IN_JUMP) && !(input & IN_UP))
	{
		item->goal_anim_state = STATE_LARA_JUMP_BACK;
	}
}

void lara_as_fallback(struct ITEM_INFO* item, struct COLL_INFO* coll)//1959C(<), 196D0(<) (F)
{
	if (item->fallspeed > LARA_FREEFALL_SPEED)
		item->goal_anim_state = STATE_LARA_FREEFALL;

	if (input & IN_ACTION)
		if (lara.gun_status == LG_NO_ARMS)
			item->goal_anim_state = STATE_LARA_REACH;
}

void lara_as_leftjump(struct ITEM_INFO* item, struct COLL_INFO* coll)//1A92C(<), 1AA60(<) (F)
{
	lara.look = 0;
	if (item->fallspeed <= LARA_FREEFALL_SPEED)
	{
		if (input & IN_RIGHT)
		{
			if (item->goal_anim_state != STATE_LARA_STOP)
				item->goal_anim_state = STATE_LARA_JUMP_ROLL;
		}
	}
	else
	{
		item->goal_anim_state = STATE_LARA_FREEFALL;
	}
}

void lara_as_rightjump(struct ITEM_INFO* item, struct COLL_INFO* coll)//1A8C4(<), 1A9F8(<) (F)
{
	lara.look = 0;
	if(item->fallspeed <= LARA_FREEFALL_SPEED)
	{
		if(input & IN_LEFT)
		{
			if (item->goal_anim_state != STATE_LARA_STOP)
				item->goal_anim_state = STATE_LARA_JUMP_ROLL;
		}
	}
	else
	{
		item->goal_anim_state = STATE_LARA_FREEFALL;
	}
}

void lara_as_backjump(struct ITEM_INFO* item, struct COLL_INFO* coll)//1A854(<), 1A988(<) (F)
{
	camera.target_angle = ANGLE(135);
	if(item->fallspeed <= LARA_FREEFALL_SPEED)
	{
		if(item->goal_anim_state == STATE_LARA_RUN_FORWARD)
		{
			item->goal_anim_state = STATE_LARA_STOP;
		}
		else if((input & IN_UP || input & IN_ROLL) && item->goal_anim_state != STATE_LARA_STOP)
		{
			item->goal_anim_state = STATE_LARA_JUMP_ROLL;
		}
	}
	else
	{
		item->goal_anim_state = STATE_LARA_FREEFALL;
	}
}

void lara_as_slide(struct ITEM_INFO* item, struct COLL_INFO* coll)//1A824(<), 1A958(<) (F)
{
	if ((input & IN_JUMP) && !(input & IN_DOWN))
	{
		item->goal_anim_state = STATE_LARA_STOP;
	}
}

void lara_as_stepleft(struct ITEM_INFO* item, struct COLL_INFO* coll)//1A750(<), 1A884(<) (F)
{
	if (item->hit_points <= 0)
	{
		item->goal_anim_state = STATE_LARA_STOP;

		return;
	}

	if (!lara.IsMoving)
	{
		if (!(input & IN_LSTEP))
		{
			item->goal_anim_state = STATE_LARA_STOP;
		}

		if (input & IN_LEFT)
		{
			lara.turn_rate -= 409;
			if (lara.turn_rate < ANGLE(-4))
				lara.turn_rate = ANGLE(-4);
		}
		else if (input & IN_RIGHT)
		{
			lara.turn_rate += 409;
			if (lara.turn_rate > ANGLE(4))
				lara.turn_rate = ANGLE(4);
		}
	}
}

void lara_as_stepright(struct ITEM_INFO* item, struct COLL_INFO* coll)//1A67C(<), 1A7B0(<) (F)
{
	if (item->hit_points <= 0)
	{
		item->goal_anim_state = STATE_LARA_STOP;

		return;
	}

	if (!lara.IsMoving)
	{
		if (!(input & IN_RSTEP))
		{
			item->goal_anim_state = STATE_LARA_STOP;
		}

		if (input & IN_LEFT)
		{
			lara.turn_rate -= 409;
			if (lara.turn_rate < ANGLE(-4))
				lara.turn_rate = ANGLE(-4);
		}
		else if (input & IN_RIGHT)
		{
			lara.turn_rate += 409;
			if (lara.turn_rate > ANGLE(4))
				lara.turn_rate = ANGLE(4);
		}
	}
}

void lara_col_fastturn(struct ITEM_INFO* item, struct COLL_INFO* coll)//1A65C(<), 1A790(<) (F)
{
	lara_col_stop(item, coll);
}

void lara_as_fastturn(struct ITEM_INFO* item, struct COLL_INFO* coll)//1A5F8(<), 1A72C(<) (F)
{
	if(item->hit_points <= 0)
	{
		item->goal_anim_state = STATE_LARA_STOP;

		return;
	}

	if(lara.turn_rate >= 0)
	{
		lara.turn_rate = ANGLE(8);

		if (input & IN_RIGHT)
			return;

		item->goal_anim_state = STATE_LARA_STOP;
	}
	else
	{
		lara.turn_rate = ANGLE(-8);

		if (input & IN_LEFT)
			return;

		item->goal_anim_state = STATE_LARA_STOP;
	}
}

void lara_as_null(struct ITEM_INFO* item, struct COLL_INFO* coll)//1A5DC(<), 1A710(<) (F)
{
	coll->enable_baddie_push = FALSE;
	coll->enable_spaz = FALSE;
	return;
}

void lara_as_back(struct ITEM_INFO* item, struct COLL_INFO* coll)//1A4F0(<), 1A624(<) (F)
{
	if (item->hit_points <= 0)
	{
		item->goal_anim_state = STATE_LARA_STOP;

		return;
	}

	if (!lara.IsMoving)
	{
		if ((input & IN_DOWN) && ((input & IN_WALK) || lara.water_status == 4))
			item->goal_anim_state = STATE_LARA_WALK_BACK;
		else
			item->goal_anim_state = STATE_LARA_STOP;

		if (input & IN_LEFT)
		{
			lara.turn_rate -= 409;
			if (lara.turn_rate < ANGLE(-4))
				lara.turn_rate = ANGLE(-4);
		}
		else if (input & IN_RIGHT)
		{
			lara.turn_rate += 409;
			if (lara.turn_rate > ANGLE(4))
				lara.turn_rate = ANGLE(4);
		}
	}
}

void lara_as_compress(struct ITEM_INFO* item, struct COLL_INFO* coll)//1A35C, 1A490 (F)
{
	if (lara.water_status != 4)
	{
		if (input & IN_UP && LaraFloorFront(item, item->pos.y_rot, CLICK) >= -384)
		{
			item->goal_anim_state = STATE_LARA_JUMP_FORWARD;
			lara.move_angle = item->pos.y_rot;
		}
		else if (input & IN_LEFT && LaraFloorFront(item, item->pos.y_rot - ANGLE(90), CLICK) >= -384)
		{
			item->goal_anim_state = STATE_LARA_JUMP_RIGHT;
			lara.move_angle = item->pos.y_rot - ANGLE(90);
		}
		else if (input & IN_RIGHT && LaraFloorFront(item, item->pos.y_rot + ANGLE(90), CLICK) >= -384)
		{
			item->goal_anim_state = STATE_LARA_JUMP_LEFT;
			lara.move_angle = item->pos.y_rot + ANGLE(90);
		}
		else if (input & IN_DOWN && LaraFloorFront(item, item->pos.y_rot - ANGLE(180), CLICK) >= -384)
		{
			item->goal_anim_state = STATE_LARA_JUMP_BACK;
			lara.move_angle = item->pos.y_rot - ANGLE(180);
		}
	}
	
	if (item->fallspeed > LARA_FREEFALL_SPEED)
		item->goal_anim_state = STATE_LARA_FREEFALL;
}

void lara_as_splat(struct ITEM_INFO* item, struct COLL_INFO* coll)//1A340(<), 1A474(<) (F)
{
	lara.look = 0;
}

void lara_as_intcornerr(struct ITEM_INFO* item, struct COLL_INFO* coll)//1A2EC(<), 1A420(<) (F)
{
	camera.lara_node = 8;
	camera.target_elevation = ANGLE(33);
	SetCornerAnim(item, coll, ANGLE(90),
		item->anim_number == ANIMATION_LARA_HANG_AROUND_RIGHT_INNER_END ||
		item->anim_number == ANIMATION_LARA_LADDER_AROUND_RIGHT_INNER_END);
}

void lara_as_intcornerl(struct ITEM_INFO* item, struct COLL_INFO* coll)//1A298(<), 1A3CC(<) (F)
{
	camera.lara_node = 8;
	camera.target_elevation = ANGLE(33);
	SetCornerAnim(item, coll, ANGLE(-90),
		item->anim_number == ANIMATION_LARA_HANG_AROUND_LEFT_INNER_END ||
		item->anim_number == ANIMATION_LARA_LADDER_AROUND_LEFT_INNER_END);
}

void lara_as_extcornerr(struct ITEM_INFO* item, struct COLL_INFO* coll)//1A244(<), 1A378(<) (F)
{
	camera.lara_node = 8;
	camera.target_elevation = ANGLE(33);
	SetCornerAnim(item, coll, ANGLE(-90),
		item->anim_number == ANIMATION_LARA_HANG_AROUND_RIGHT_OUTER_END ||
		item->anim_number == ANIMATION_LARA_LADDER_AROUND_RIGHT_OUTER_END);
}

void lara_as_extcornerl(struct ITEM_INFO* item, struct COLL_INFO* coll)//1A1F0(<), 1A324(<) (F)
{
	camera.lara_node = 8;
	camera.target_elevation = ANGLE(33);
	SetCornerAnim(item, coll, ANGLE(90), 
		item->anim_number == ANIMATION_LARA_HANG_AROUND_LEFT_OUTER_END || 
		item->anim_number == ANIMATION_LARA_LADDER_AROUND_LEFT_OUTER_END);
}

void SetCornerAnim(struct ITEM_INFO* item, struct COLL_INFO* coll, short rot, short flip)//1A090, 1A1C4 (F)
{
	if (item->hit_points <= 0)
	{
		item->goal_anim_state = STATE_LARA_JUMP_FORWARD;
		item->current_anim_state = STATE_LARA_JUMP_FORWARD;
		item->anim_number = ANIMATION_LARA_FREE_FALL_FORWARD;
		item->frame_number = anims[ANIMATION_LARA_FREE_FALL_FORWARD].frame_base;

		item->gravity_status = TRUE;
		item->speed = 2;
		item->pos.y_pos += CLICK;
		item->fallspeed = 1;

		lara.gun_status = LG_NO_ARMS;

		item->pos.y_rot += rot / 2;

		return;
	}

	if (flip)
	{
		if (lara.IsClimbing)
		{
			item->anim_number = ANIMATION_LARA_LADDER_IDLE;
			item->frame_number = anims[ANIMATION_LARA_LADDER_IDLE].frame_base;

			item->goal_anim_state = STATE_LARA_LADDER_IDLE;
			item->current_anim_state = STATE_LARA_LADDER_IDLE;
		}
		else
		{
			item->anim_number = ANIMATION_LARA_HANG_IDLE;
			item->frame_number = anims[ANIMATION_LARA_HANG_IDLE].frame_base + 21;

			item->goal_anim_state = STATE_LARA_HANG;
			item->current_anim_state = STATE_LARA_HANG;
		}

		coll->old.x = lara.CornerX;
		item->pos.x_pos = lara.CornerX;

		coll->old.z = lara.CornerZ;
		item->pos.z_pos = lara.CornerZ;

		item->pos.y_rot += rot;
	}
}

void lara_col_hangright(struct ITEM_INFO* item, struct COLL_INFO* coll)//1A038(<), 1A16C(<) (F)
{
	lara.move_angle = item->pos.y_rot + ANGLE(90);
	coll->radius = 102;
	LaraHangTest(item, coll);
	lara.move_angle = item->pos.y_rot + ANGLE(90);
}

void lara_as_hangright(struct ITEM_INFO* item, struct COLL_INFO* coll)//19FEC(<), 1A120(<) (F)
{
	coll->enable_baddie_push = FALSE;
	coll->enable_spaz = FALSE;
	camera.target_angle = 0;
	camera.target_elevation = ANGLE(-45);
	if (!(input & (IN_RIGHT | IN_RSTEP)))
		item->goal_anim_state = STATE_LARA_HANG;
}

void lara_col_hangleft(struct ITEM_INFO* item, struct COLL_INFO* coll)//19F94(<), 1A0C8(<) (F)
{
	lara.move_angle = item->pos.y_rot - ANGLE(90);
	coll->radius = 102;
	LaraHangTest(item, coll);
	lara.move_angle = item->pos.y_rot - ANGLE(90);
}

void lara_as_hangleft(struct ITEM_INFO* item, struct COLL_INFO* coll)//19F48(<), 1A07C(<) (F)
{
	coll->enable_baddie_push = FALSE;
	coll->enable_spaz = FALSE;
	camera.target_angle = 0;
	camera.target_elevation = ANGLE(-45);
	if (!(input & (IN_LEFT | IN_LSTEP)))
		item->goal_anim_state = STATE_LARA_HANG;
}

void lara_col_hang(struct ITEM_INFO* item, struct COLL_INFO* coll)//19AC8, 19BFC (F)
{
	item->fallspeed = 0;
	item->gravity_status = FALSE;

	if (item->anim_number == ANIMATION_LARA_HANG_IDLE && item->frame_number == anims[ANIMATION_LARA_HANG_IDLE].frame_base + 21)
	{
		int flag;

		if (input & IN_LEFT || input & IN_LSTEP)
		{
			if (CanLaraHangSideways(item, coll, ANGLE(-90)))
			{
				item->goal_anim_state = STATE_LARA_SHIMMY_LEFT;

				return;
			}

			flag = LaraHangLeftCornerTest(item, coll);
			if (flag != 0)
			{
				if (flag < 0)
					item->goal_anim_state = STATE_LARA_CLIMB_CORNER_LEFT_INNER;
				else
					item->goal_anim_state = STATE_LARA_CLIMB_CORNER_LEFT_OUTER;

				return;
			}
		}

		if (input & IN_RIGHT || input & IN_RSTEP)
		{
			if (CanLaraHangSideways(item, coll, ANGLE(90)))
			{
				item->goal_anim_state = STATE_LARA_SHIMMY_RIGHT;

				return;
			}

			flag = LaraHangLeftCornerTest(item, coll);
			if (flag != 0)
			{
				if (flag < 0)
					item->goal_anim_state = STATE_LARA_CLIMB_CORNER_RIGHT_INNER;
				else
					item->goal_anim_state = STATE_LARA_CLIMB_CORNER_RIGHT_OUTER;

				return;
			}
		}
	}

	lara.move_angle = item->pos.y_rot;

	LaraHangTest(item, coll);

	if (item->anim_number == ANIMATION_LARA_HANG_IDLE && item->frame_number == anims[ANIMATION_LARA_HANG_IDLE].frame_base + 21)
	{
		TestForObjectOnLedge(item, coll);

		if (input & IN_UP)
		{
			if (coll->front_floor > -850)
			{
				if (coll->front_floor < -650 &&
					coll->front_floor >= coll->front_ceiling &&
					coll->front_floor >= coll->left_ceiling2 && 
					coll->front_floor >= coll->right_ceiling2)
				{
					if (abs(coll->left_floor2 - coll->right_floor2) < 60 && !coll->hit_static)
					{
						if (input & IN_WALK)
						{
							item->goal_anim_state = STATE_LARA_HANDSTAND;
						}
						else if (input & IN_CROUCH)
						{
							item->goal_anim_state = STATE_LARA_CLIMB_TO_CRAWL;
							item->required_anim_state = STATE_LARA_CROUCH_IDLE;
						}
						else
						{
							item->goal_anim_state = STATE_LARA_GRABBING;
						}

						return;
					}
				}

				if (coll->front_floor < -650 &&
					coll->front_floor - coll->front_ceiling >= -256 &&
					coll->front_floor - coll->left_ceiling2 >= -256 &&
					coll->front_floor - coll->right_ceiling2 >= -256 )
				{
					if (abs(coll->left_floor2 - coll->right_floor2) < 60 && !coll->hit_static)
					{
						item->goal_anim_state = STATE_LARA_CLIMB_TO_CRAWL;
						item->required_anim_state = STATE_LARA_CROUCH_IDLE;

						return;
					}
				}
			}

			if (lara.climb_status != 0 &&
				coll->mid_ceiling <= -256 &&
				abs(coll->left_ceiling2 - coll->right_ceiling2) < 60)
			{
				if (LaraTestClimbStance(item, coll))
				{
					item->goal_anim_state = STATE_LARA_LADDER_IDLE;
				}
				else
				{
					item->anim_number = ANIMATION_LARA_LADDER_UP_HANDS;
					item->frame_number = anims[ANIMATION_LARA_LADDER_UP_HANDS].frame_base;

					item->goal_anim_state = STATE_LARA_HANG;
					item->current_anim_state = STATE_LARA_HANG;
				}
			}

			return;
		}

		if (input & IN_DOWN &&
			lara.climb_status != 0 &&
			coll->mid_floor > 344)
		{
			if (LaraTestClimbStance(item, coll))
			{
				item->goal_anim_state = STATE_LARA_LADDER_IDLE;
			}
			else
			{
				item->anim_number = ANIMATION_LARA_LADDER_DOWN_HANDS;
				item->frame_number = anims[ANIMATION_LARA_LADDER_DOWN_HANDS].frame_base;

				item->goal_anim_state = STATE_LARA_HANG;
				item->current_anim_state = STATE_LARA_HANG;
			}
		}
	}
}

void lara_as_hang(struct ITEM_INFO* item, struct COLL_INFO* coll)//19A28, 19B5C (F)
{
	lara.IsClimbing = 0;

	if (item->hit_points <= 0)
	{
		item->goal_anim_state = STATE_LARA_STOP;

		return;
	}

	if (input & IN_LOOK)
		LookUpDown();

	coll->enable_baddie_push = FALSE;
	coll->enable_spaz = FALSE;

	camera.target_angle = 0;
	camera.target_elevation = ANGLE(-45);
}

int CanLaraHangSideways(struct ITEM_INFO* item, struct COLL_INFO* coll, short angle)//19930, 19A64 (F)
{
	const long oldx = item->pos.x_pos;
	const long oldz = item->pos.z_pos;
	long x = item->pos.x_pos;
	long z = item->pos.z_pos;
	int res;

	lara.move_angle = angle + item->pos.y_rot;

	switch ((unsigned short)(lara.move_angle + ANGLE(45)) / (unsigned short)ANGLE(90))
	{
	case 0:
		z += 16;
		break;
	case 1:
		x += 16;
		break;
	case 2:
		z -= 16;
		break;
	case 3:
		x -= 16;
		break;
	}

	item->pos.x_pos = x;
	item->pos.z_pos = z;

	coll->old.y = item->pos.y_pos;

	res = LaraHangTest(item, coll);

	item->pos.x_pos = oldx;
	item->pos.z_pos = oldz;

	lara.move_angle = angle + item->pos.y_rot;

	return !res;
}

void lara_void_func(struct ITEM_INFO* item, struct COLL_INFO* coll)//19928(<), 19A5C(<) (F)
{
	return;
}

void lara_as_fastfall(struct ITEM_INFO* item, struct COLL_INFO* coll)//198BC(<), 199F0(<) (F)
{
	item->speed = (item->speed * 95) / 100;
	if (item->fallspeed == 154)
		SoundEffect(SFX_LARA_FALL, &item->pos, 0);
}

void lara_as_death(struct ITEM_INFO* item, struct COLL_INFO* coll)//19830(<), 19964(<) (F)
{
	lara.look = 0;
	coll->enable_baddie_push = FALSE;
	coll->enable_spaz = FALSE;
	if (BinocularRange)
	{
		BinocularRange = 0;
		LaserSight = 0;
		AlterFOV(ANGLE(80));
		lara_item->mesh_bits = -1;
		lara.Busy = 0;
	}
}

void lara_as_turn_l(struct ITEM_INFO* item, struct COLL_INFO* coll)//1972C(<), 19860(<) (F)
{
	if (item->hit_points <= 0)
	{
		item->goal_anim_state = STATE_LARA_STOP;

		return;
	}

	lara.turn_rate -= 409;

	if (lara.gun_status != LG_READY || lara.water_status == 4)
	{
		if (lara.turn_rate < ANGLE(-4))
		{
			if (input & IN_WALK)
				lara.turn_rate = ANGLE(-4);
			else
				item->goal_anim_state = STATE_LARA_TURN_FAST;
		}
	}
	else
	{
		item->goal_anim_state = STATE_LARA_TURN_FAST;
	}

	if (!(input & IN_UP))
	{
		if (!(input & IN_LEFT))
			item->goal_anim_state = STATE_LARA_STOP;

		return;
	}

	if (lara.water_status == 4)
	{
		item->goal_anim_state = STATE_LARA_WADE_FORWARD;
	}
	else if (input & IN_WALK)
	{
		item->goal_anim_state = STATE_LARA_WALK_FORWARD;
	}
	else
	{
		item->goal_anim_state = STATE_LARA_RUN_FORWARD;
	}
}

void lara_as_turn_r(struct ITEM_INFO* item, struct COLL_INFO* coll)//19628(<), 1975C(<) (F)
{
	if (item->hit_points <= 0)
	{
		item->goal_anim_state = STATE_LARA_STOP;

		return;
	}

	lara.turn_rate += 409;

	if (lara.gun_status != LG_READY || lara.water_status == 4)
	{
		if (lara.turn_rate > ANGLE(4))
		{
			if (input & IN_WALK)
				lara.turn_rate = ANGLE(4);
			else
				item->goal_anim_state = STATE_LARA_TURN_FAST;
		}
	}
	else
	{
		item->goal_anim_state = STATE_LARA_TURN_FAST;
	}

	if (!(input & IN_UP))
	{
		if (!(input & IN_RIGHT))
			item->goal_anim_state = STATE_LARA_STOP;

		return;
	}

	if (lara.water_status == 4)
	{
		item->goal_anim_state = STATE_LARA_WADE_FORWARD;
	}
	else if (input & IN_WALK)
	{
		item->goal_anim_state = STATE_LARA_WALK_FORWARD;
	}
	else
	{
		item->goal_anim_state = STATE_LARA_RUN_FORWARD;
	}
}

void lara_as_fastback(struct ITEM_INFO* item, struct COLL_INFO* coll)//1959C(<), 196D0(<) (F)
{
	item->goal_anim_state = STATE_LARA_STOP;
	if (input & IN_LEFT)
	{
		lara.turn_rate -= 409;
		if (lara.turn_rate < ANGLE(-6))
			lara.turn_rate = ANGLE(-6);
	}
	else if(input & IN_RIGHT)
	{
		lara.turn_rate += 409;
		if (lara.turn_rate > ANGLE(6))
			lara.turn_rate = ANGLE(6);
	}
}

int unknown_dword = 1; // present both on pc and psx, but missing from the symbol table, also only used in lara_as_run

void lara_as_run(struct ITEM_INFO* item, struct COLL_INFO* coll)//192EC, 19420 (F)
{
	if (item->hit_points <= 0)
	{
		item->goal_anim_state = STATE_LARA_DEATH;

		return;
	}

	if (input & IN_ROLL)
	{
		item->anim_number = ANIMATION_LARA_ROLL_BEGIN;
		item->frame_number = anims[ANIMATION_LARA_ROLL_BEGIN].frame_base + 2;

		item->current_anim_state = STATE_LARA_ROLL_FORWARD;
		item->goal_anim_state = STATE_LARA_STOP;

		return;
	}

	if (input & IN_SPRINT && DashTimer)
	{
		item->goal_anim_state = STATE_LARA_SPRINT;

		return;
	}

	if (input & IN_CROUCH &&
		lara.water_status != 4 &&
		(lara.gun_status == LG_NO_ARMS ||
			lara.gun_type == WEAPON_NONE ||
			lara.gun_type == WEAPON_PISTOLS ||
			lara.gun_type == WEAPON_REVOLVER ||
			lara.gun_type == WEAPON_UZI ||
			lara.gun_type == WEAPON_FLARE))
	{
		item->goal_anim_state = STATE_LARA_CROUCH_IDLE;

		return;
	}

	if (input & IN_LEFT)
	{
		lara.turn_rate -= 409;
		if (lara.turn_rate < ANGLE(-8))
			lara.turn_rate = ANGLE(-8);

		item->pos.z_rot -= ANGLE(1.5);
		if (item->pos.z_rot < ANGLE(-11))
			item->pos.z_rot = ANGLE(-11);
	}
	else if(input & IN_RIGHT)
	{
		lara.turn_rate += 409;
		if (lara.turn_rate > ANGLE(8))
			lara.turn_rate = ANGLE(8);

		item->pos.z_rot += ANGLE(1.5);
		if (item->pos.z_rot > ANGLE(11))
			item->pos.z_rot = ANGLE(11);
	}

	if (item->anim_number == ANIMATION_LARA_STAY_TO_RUN)
	{
		unknown_dword = 0;
	}
	else if(item->anim_number != ANIMATION_LARA_RUN || item->frame_number == 4)
	{
		unknown_dword = 1;
	}

	if (input & IN_JUMP && unknown_dword && !item->gravity_status)
	{
		item->goal_anim_state = STATE_LARA_JUMP_FORWARD;
	}
	else if(input & IN_UP)
	{
		if (lara.water_status == 4)
		{
			item->goal_anim_state = STATE_LARA_WADE_FORWARD;
		}
		else if(input & IN_WALK)
		{
			item->goal_anim_state = STATE_LARA_WALK_FORWARD;
		}
		else
		{
			item->goal_anim_state = STATE_LARA_RUN_FORWARD;
		}
	}
	else
	{
		item->goal_anim_state = STATE_LARA_STOP;
	}
}

void lara_as_walk(struct ITEM_INFO* item, struct COLL_INFO* coll)//191B8(<), 192EC(<) (F)
{
	if (item->hit_points <= 0)
	{
		item->goal_anim_state = STATE_LARA_STOP;

		return;
	}

	if (!lara.IsMoving)
	{
		if (input & IN_LEFT)
		{
			lara.turn_rate -= 409;
			if (lara.turn_rate < ANGLE(-4))
				lara.turn_rate = ANGLE(-4);
		}
		else if (input & IN_RIGHT)
		{
			lara.turn_rate += 409;
			if (lara.turn_rate > ANGLE(4))
				lara.turn_rate = ANGLE(4);
		}

		if (input & IN_UP)
		{
			if (lara.water_status == 4)
			{
				item->goal_anim_state = STATE_LARA_WADE_FORWARD;
			}
			else if (input & IN_WALK)
			{
				item->goal_anim_state = STATE_LARA_WALK_FORWARD;
			}
			else
			{
				item->goal_anim_state = STATE_LARA_RUN_FORWARD;
			}
		}
		else 
		{
			item->goal_anim_state = STATE_LARA_STOP;
		}
	}
}

void lara_col_reach(struct ITEM_INFO* item, struct COLL_INFO* coll)//18D0C, 18E40 (F)
{
	if (lara.RopePtr == -1)
	{
		item->gravity_status = TRUE;
	}

	lara.move_angle = item->pos.y_rot;

	coll->bad_pos = 32512;
	coll->bad_neg = 0;
	coll->bad_ceiling = 192;

	GetLaraCollisionInfo(item, coll);

	if (input & IN_ACTION && lara.gun_status == LG_NO_ARMS && !coll->hit_static)
	{
		if (lara.CanMonkeySwing && coll->coll_type == CT_TOP)
		{
			lara.head_y_rot = 0;
			lara.head_x_rot = 0;
			lara.torso_y_rot = 0;
			lara.torso_x_rot = 0;

			item->anim_number = ANIMATION_LARA_OSCILLATE_HANG_ON;
			item->frame_number = anims[ANIMATION_LARA_OSCILLATE_HANG_ON].frame_base;

			item->goal_anim_state = STATE_LARA_MONKEYSWING_IDLE;
			item->current_anim_state = STATE_LARA_MONKEYSWING_IDLE;

			item->gravity_status = FALSE;
			item->speed = 0;
			item->fallspeed = 0;

			lara.gun_status = LG_HANDS_BUSY;

			return;
		}

		if (coll->mid_ceiling <= -384 && 
			coll->mid_floor >= 200 && 
			coll->coll_type == CT_FRONT)
		{
			long edge;
			int edge_catch = LaraTestEdgeCatch(item, coll, &edge);

			if (edge_catch > 0 && !LaraTestHangOnClimbWall(item, coll))
			{
				short angle = item->pos.y_rot;

				if (abs(angle) > ANGLE(35))
				{
					if (angle < 10014 || angle > 22754)
					{
						if (angle >= 26397 || angle <= -26397)
						{
							angle = ANGLE(-180);
						}
						else if (angle >= -22754 && angle <= -10014)
						{
							angle = ANGLE(-90);
						}
					}
					else
					{
						angle = ANGLE(90);
					}
				}
				else
				{
					angle = 0;
				}

				if ((angle & 0x3FFF) == 0)
				{
					short* bounds;

					if (TestHangSwingIn(item, angle))
					{
						lara.head_y_rot = 0;
						lara.head_x_rot = 0;
						lara.torso_y_rot = 0;
						lara.torso_x_rot = 0;

						item->anim_number = ANIMATION_LARA_OSCILLATE_HANG_ON;
						item->frame_number = anims[ANIMATION_LARA_OSCILLATE_HANG_ON].frame_base;

						item->current_anim_state = STATE_LARA_MONKEYSWING_IDLE;
						item->goal_anim_state = STATE_LARA_MONKEYSWING_IDLE;
					}
					else
					{
						item->anim_number = ANIMATION_LARA_HANG_IDLE;
						item->frame_number = anims[ANIMATION_LARA_HANG_IDLE].frame_base;

						item->current_anim_state = STATE_LARA_HANG;
						item->goal_anim_state = STATE_LARA_HANG;
					}

					bounds = GetBoundsAccurate(item);

					if (edge_catch <= 0)
					{
						item->pos.y_pos = edge - bounds[2] - 22;
					}
					else
					{
						item->pos.y_pos += coll->front_floor - bounds[2];

						switch ((unsigned char)(item->pos.y_rot + ANGLE(45)) / (unsigned char)ANGLE(90))
						{
						case 0u:
							item->pos.z_pos = (item->pos.z_pos | 0x3FF) - 100;
							item->pos.x_pos += coll->shift.x;
							break;
						case 2u:
							item->pos.z_pos = (item->pos.z_pos & 0xFFFFFC00) + 100;
							item->pos.x_pos += coll->shift.x;
							break;
						case 1u:
							item->pos.x_pos = (item->pos.x_pos | 0x3FF) - 100;
							item->pos.z_pos += coll->shift.z;
							break;
						case 3u:
							item->pos.x_pos = (item->pos.x_pos & 0xFFFFFC00) + 100;
							item->pos.z_pos += coll->shift.z;
							break;
						default:
							break;
						}
					}

					item->pos.y_rot = angle;

					item->gravity_status = TRUE;
					item->speed = 2;
					item->fallspeed = 1;

					lara.gun_status = LG_HANDS_BUSY;
				}
			}
		}
	}
}

void lara_as_reach(struct ITEM_INFO* item, struct COLL_INFO* coll)//18CE0(<), 18E14(<) (F)
{
	camera.target_angle = ANGLE(85);
	if (item->fallspeed > LARA_FREEFALL_SPEED)
		item->goal_anim_state = STATE_LARA_FREEFALL;
}

void lara_col_forwardjump(struct ITEM_INFO* item, struct COLL_INFO* coll)//18B88, 18CBC (F)
{
	if (item->speed < 0)
		lara.move_angle = item->pos.y_rot - ANGLE(180);
	else
		lara.move_angle = item->pos.y_rot;

	coll->bad_pos = 32512;
	coll->bad_neg = -384;
	coll->bad_ceiling = 192;

	GetLaraCollisionInfo(item, coll);
	LaraDeflectEdgeJump(item, coll);

	if (item->speed < 0)
		lara.move_angle = item->pos.y_rot;

	if (coll->mid_floor <= 0 && item->fallspeed > 0)
	{
		if (LaraLandedBad(item, coll))
		{
			item->goal_anim_state = STATE_LARA_DEATH;
		}
		else if (lara.water_status == 4 || !(input & IN_UP) || input & IN_WALK)
		{
			item->goal_anim_state = STATE_LARA_STOP;
		}
		else
		{
			item->goal_anim_state = STATE_LARA_RUN_FORWARD;
		}

		item->gravity_status = FALSE;
		item->fallspeed = 0;
		item->speed = 0;

		if (coll->mid_floor != -32512)
			item->pos.y_pos += coll->mid_floor;
	}
}

void lara_as_forwardjump(struct ITEM_INFO* item, struct COLL_INFO* coll)//18A34, 18B68 (F)
{
	if (item->goal_anim_state == STATE_LARA_SWANDIVE_BEGIN || 
		item->goal_anim_state == STATE_LARA_REACH)
		item->goal_anim_state = STATE_LARA_JUMP_FORWARD;

	if (item->goal_anim_state != STATE_LARA_DEATH &&
		item->goal_anim_state != STATE_LARA_STOP &&
		item->goal_anim_state != STATE_LARA_RUN_FORWARD)
	{
		if (lara.gun_status == LG_NO_ARMS && input & IN_ACTION)
			item->goal_anim_state = STATE_LARA_REACH;

		if (input & IN_DOWN || input & IN_ROLL)
			item->goal_anim_state = STATE_LARA_JUMP_ROLL;

		if (lara.gun_status == LG_NO_ARMS && input & IN_WALK)
			item->goal_anim_state = STATE_LARA_SWANDIVE_BEGIN;

		if (item->fallspeed > LARA_FREEFALL_SPEED)
			item->goal_anim_state = STATE_LARA_FREEFALL;
	}

	if (input & IN_LEFT)
	{
		lara.turn_rate -= 409;

		if (lara.turn_rate < ANGLE(-3))
			lara.turn_rate = ANGLE(-3);
	}
	else if (input & IN_RIGHT)
	{
		lara.turn_rate += 409;

		if (lara.turn_rate > ANGLE(3))
			lara.turn_rate = ANGLE(3);
	}
}

void lara_col_upjump(struct ITEM_INFO* item, struct COLL_INFO* coll)//1853C, 18670 (F)
{
	if (item->hit_points <= 0)
	{
		item->goal_anim_state = STATE_LARA_STOP;
		return;
	}

	lara.move_angle = item->pos.y_rot;

	coll->bad_pos = 32512;
	coll->bad_neg = -384;
	coll->bad_ceiling = 192;

	coll->facing = item->speed < 0
		? lara.move_angle - ANGLE(180)
		: lara.move_angle;

	GetCollisionInfo(coll, item->pos.x_pos, item->pos.y_pos, item->pos.z_pos, item->room_number, 870);

	if (input & IN_ACTION && lara.gun_status == LG_NO_ARMS && !coll->hit_static)
	{
		if (lara.CanMonkeySwing && coll->coll_type == CT_TOP)
		{
			item->goal_anim_state = STATE_LARA_MONKEYSWING_IDLE;
			item->current_anim_state = STATE_LARA_MONKEYSWING_IDLE;

			item->anim_number = ANIMATION_LARA_MONKEY_GRAB;
			item->frame_number = anims[ANIMATION_LARA_MONKEY_GRAB].frame_base;

			item->gravity_status = FALSE;		
			item->speed = 0;
			item->fallspeed = 0;

			lara.gun_status = LG_HANDS_BUSY;

			MonkeySwingSnap(item, coll);

			return;
		}

		if (coll->coll_type == CT_FRONT && coll->mid_ceiling <= -384)
		{
			long edge;
			const int edge_catch = LaraTestEdgeCatch(item, coll, &edge);

			if (edge_catch)
			{
				if (edge_catch >= 0 || LaraTestHangOnClimbWall(item, coll))
				{
					short angle = item->pos.y_rot;

					if (abs(angle) > ANGLE(35))
					{
						if (angle < 10014 || angle > 22754)
						{
							if (angle >= 26397 || angle <= -26397)
							{
								angle = ANGLE(-180);
							}
							else if (angle >= -22754 && angle <= -10014)
							{
								angle = ANGLE(-90);
							}
						}
						else
						{
							angle = ANGLE(90);
						}
					}
					else
					{
						angle = 0;
					}

					if ((angle & 0x3FFF) == 0)
					{
						short* bounds;

						if (TestHangSwingIn(item, angle))
						{
							item->anim_number = ANIMATION_LARA_MONKEY_GRAB;
							item->frame_number = anims[ANIMATION_LARA_MONKEY_GRAB].frame_base;

							item->goal_anim_state = STATE_LARA_MONKEYSWING_IDLE;
							item->current_anim_state = STATE_LARA_MONKEYSWING_IDLE;
						}
						else
						{
							item->anim_number = ANIMATION_LARA_HANG_IDLE;
							item->frame_number = anims[ANIMATION_LARA_HANG_IDLE].frame_base + 12;

							item->goal_anim_state = STATE_LARA_HANG;
							item->current_anim_state = STATE_LARA_HANG;
						}

						bounds = GetBoundsAccurate(item);

						if (edge_catch <= 0)
							item->pos.y_pos = edge - bounds[2] + 4;
						else
							item->pos.y_pos += coll->front_floor - bounds[2];

						item->pos.x_pos += coll->shift.x;
						item->pos.z_pos += coll->shift.z;

						item->pos.y_rot = angle;

						item->gravity_status = FALSE;
						item->speed = 0;
						item->fallspeed = 0;

						lara.gun_status = LG_HANDS_BUSY;

						lara.torso_y_rot = 0;
						lara.torso_x_rot = 0;

						return;
					}
				}
			}
		}
	}

	ShiftItem(item, coll);

	if (coll->coll_type == CT_CLAMP ||
		coll->coll_type == CT_TOP ||
		coll->coll_type == CT_TOP_FRONT ||
		coll->hit_ceiling)
		item->fallspeed = 1;

	if (coll->coll_type == CT_NONE)
	{
		if (item->fallspeed < -70)
		{
			if (input & IN_UP && item->speed < 5)
			{
				item->speed++;
			}
			else if (input & IN_DOWN && item->speed > -5) 
			{
				item->speed -= 2;
			}
		}
	}
	else
	{
		item->speed = item->speed <= 0 ? -2 : 2;
	}

	if (item->fallspeed > 0 && coll->mid_floor <= 0)
	{
		item->goal_anim_state = LaraLandedBad(item, coll) ? STATE_LARA_DEATH : STATE_LARA_STOP;

		item->gravity_status = FALSE;
		item->fallspeed = 0;

		if (coll->mid_floor != -32512)
			item->pos.y_pos += coll->mid_floor;
	}
}

void lara_as_upjump(struct ITEM_INFO* item, struct COLL_INFO* coll)//1851C(<), 18650(<) (F)
{
	if (item->fallspeed > LARA_FREEFALL_SPEED)
	{
		item->goal_anim_state = STATE_LARA_FREEFALL;
	}
}

void lara_col_stop(struct ITEM_INFO* item, struct COLL_INFO* coll)//18444(<), 18578(<) (F)
{
	lara.move_angle = item->pos.y_rot;

	coll->bad_pos = 384;
	coll->bad_neg = -384;
	coll->bad_ceiling = 0;

	item->gravity_status = 0;
	item->fallspeed = 0;

	coll->slopes_are_pits = 1;
	coll->slopes_are_walls = 1;

	GetLaraCollisionInfo(item, coll);

	if (!LaraHitCeiling(item, coll))
	{
		if (!LaraFallen(item, coll))
		{
			if (!TestLaraSlide(item, coll))
			{
				ShiftItem(item, coll);

				if (coll->mid_floor != -32512)
					item->pos.y_pos += coll->mid_floor;
			}
		}
	}
}

void lara_as_stop(struct ITEM_INFO* item, struct COLL_INFO* coll)//17E94, 17FC8 (F)
{
	short fheight = -32512;
	short rheight = -32512;

	if (item->hit_points <= 0)
	{
		item->goal_anim_state = STATE_LARA_DEATH;

		return;
	}

	if (item->anim_number != ANIMATION_LARA_SPRINT_SLIDE_STAND_RIGHT && 
		item->anim_number != ANIMATION_LARA_SPRINT_SLIDE_STAND_LEFT)
		StopSoundEffect(SFX_LARA_SLIPPING);

	if (input & IN_ROLL && lara.water_status != 4)
	{
		item->anim_number = ANIMATION_LARA_ROLL_BEGIN;
		item->frame_number = anims[ANIMATION_LARA_ROLL_BEGIN].frame_base + 2;

		item->current_anim_state = STATE_LARA_ROLL_FORWARD;
		item->goal_anim_state = STATE_LARA_STOP;

		return;
	}

	if (input & IN_CROUCH &&
		lara.water_status != 4 &&
		item->current_anim_state == STATE_LARA_STOP &&
		(lara.gun_status == LG_NO_ARMS ||
			lara.gun_type == WEAPON_NONE ||
			lara.gun_type == WEAPON_PISTOLS ||
			lara.gun_type == WEAPON_REVOLVER ||
			lara.gun_type == WEAPON_UZI ||
			lara.gun_type == WEAPON_FLARE))
	{
		item->goal_anim_state = STATE_LARA_CROUCH_IDLE;

		return;
	}

	item->goal_anim_state = STATE_LARA_STOP;

	if (input & IN_LOOK)
	{
		LookUpDown();
	}

	if (input & IN_UP)
	{
		fheight = LaraFloorFront(item, item->pos.y_rot, 104);
	}
	else if(input & IN_DOWN)
	{
		rheight = LaraFloorFront(item, item->pos.y_rot - ANGLE(180), 104);
	}

	if (input & IN_LSTEP)
	{
		if (abs(LaraFloorFront(item, item->pos.y_rot - ANGLE(90), 116)) < 128 && 
			height_type != BIG_SLOPE &&
			LaraCeilingFront(item, item->pos.y_rot - ANGLE(90), 116, 762) <= 0)
		{
			item->goal_anim_state = STATE_LARA_WALK_LEFT;
		}
	}
	else if (input & IN_RSTEP)
	{
		if (abs(LaraFloorFront(item, item->pos.y_rot + ANGLE(90), 116)) < 128 && 
			height_type != BIG_SLOPE &&
			LaraCeilingFront(item, item->pos.y_rot + ANGLE(90), 116, 762) <= 0)
		{
			item->goal_anim_state = STATE_LARA_WALK_RIGHT;
		}
	}
	else if (input & IN_LEFT)
	{
		item->goal_anim_state = STATE_LARA_TURN_LEFT_SLOW;
	}
	else if (input & IN_RIGHT)
	{
		item->goal_anim_state = STATE_LARA_TURN_RIGHT_SLOW;
	}

	if (lara.water_status == 4)
	{
		if (input & IN_JUMP)
		{
			item->goal_anim_state = STATE_LARA_JUMP_PREPARE;
		}

		if (input & IN_UP)
		{
			if (abs(fheight) >= 383)
			{
				lara.move_angle = item->pos.y_rot;

				coll->bad_pos = 32512;
				coll->bad_neg = -384;
				coll->bad_ceiling = 0;

				coll->radius = 102;
				coll->slopes_are_walls = 1;

				GetLaraCollisionInfo(item, coll);
				if (!TestLaraVault(item, coll))
					coll->radius = 100;
			}
			else
			{
				lara_as_wade(item, coll);
			}
		}
		else if(input & IN_DOWN && abs(rheight) < 383)
		{
			lara_as_back(item, coll);
		}
	}
	else if(input & IN_JUMP)
	{
		item->goal_anim_state = STATE_LARA_JUMP_PREPARE;
	}
	else if(input & IN_UP)
	{
		const long ceiling = LaraCeilingFront(item, item->pos.y_rot, 104, 762);
		const long height = LaraFloorFront(item, item->pos.y_rot, 104);

		if ((height_type == BIG_SLOPE || height_type == DIAGONAL) && height < 0 || ceiling > 0)
		{
			item->goal_anim_state = STATE_LARA_STOP;

			return;
		}

		if (height >= -256 || fheight >= -256)
		{
			if (input & IN_WALK)
				lara_as_walk(item, coll);
			else
				lara_as_run(item, coll);
		}
		else
		{
			lara.move_angle = item->pos.y_rot;

			coll->bad_pos = 32512;
			coll->bad_neg = -384;
			coll->bad_ceiling = 0;

			coll->radius = 102;
			coll->slopes_are_walls = 1;

			GetLaraCollisionInfo(item, coll);

			if (!TestLaraVault(item, coll))
			{
				coll->radius = 100;

				item->goal_anim_state = STATE_LARA_STOP;
			}
		}
	}
	else if(input & IN_DOWN)
	{
		if (input & IN_WALK)
		{
			if (abs(rheight) < 383 && height_type != BIG_SLOPE)
				lara_as_back(item, coll);
		}
		else if(rheight > -383)
		{
			item->goal_anim_state = STATE_LARA_RUN_BACK;
		}
	}
}

void lara_as_climbroped(struct ITEM_INFO* item, struct COLL_INFO* coll)//17E64, 17F98 (F)
{
	LaraClimbRope(item, coll);
}

void lara_as_climbrope(struct ITEM_INFO* item, struct COLL_INFO* coll)//17D9C(<), 17ED0(<) (F)
{
	if (input & IN_ROLL)
	{
		FallFromRope(item);
	}
	else
	{
		camera.target_angle = ANGLE(30);
		
		if(anims[item->anim_number].frame_end == item->frame_number)
		{
			item->frame_number = anims[item->anim_number].frame_base;

			lara.RopeSegment -= 2;
		}

		if (!(input & IN_UP) || ((lara.RopeSegment >> 16) & 0xFF) <= 4)
			item->goal_anim_state = STATE_LARA_ROPE_IDLE;
	}
}

void lara_col_ropefwd(struct ITEM_INFO* item, struct COLL_INFO* coll)//17B74, 17CA8 (F)
{
	camera.target_distance = SECTOR(2);

	UpdateRopeSwing(item);

	if (item->anim_number == ANIMATION_LARA_ROPE_SWING_FORWARD_SEMIHARD)
	{
		if (input & IN_SPRINT)
		{
			long Vel;

			if (abs(lara.RopeLastX) < 9000)
				Vel = 192 * (9000 - abs(lara.RopeLastX) / 9000);
			else
				Vel = 0;

			ApplyVelocityToRope(lara.RopeSegment - 2, 
				item->pos.y_rot + (lara.RopeDirection != 0 ? 0 : ANGLE(180)), 
				Vel >> 5);
		}

		if (lara.RopeFrame > lara.RopeDFrame)
		{
			lara.RopeFrame -= lara.RopeFrameRate;
			if (lara.RopeFrame < lara.RopeDFrame)
				lara.RopeFrame = lara.RopeDFrame;
		}
		else if (lara.RopeFrame < lara.RopeDFrame)
		{
			lara.RopeFrame += lara.RopeFrameRate;
			if (lara.RopeFrame > lara.RopeDFrame)
				lara.RopeFrame = lara.RopeDFrame;
		}

		item->frame_number = lara.RopeDFrame >> 8;

		if (!(input & IN_SPRINT) &&
			lara.RopeDFrame >> 8 == anims[ANIMATION_LARA_ROPE_SWING_FORWARD_SEMIHARD].frame_base + 32 &&
			lara.RopeMaxXBackward < 6750 && 
			lara.RopeMaxXForward < 6750)
		{
			item->anim_number = ANIMATION_LARA_MONKEY_TO_ROPE_END;
			item->frame_number = anims[ANIMATION_LARA_MONKEY_TO_ROPE_END].frame_base;

			item->current_anim_state = STATE_LARA_ROPE_IDLE;
			item->goal_anim_state = STATE_LARA_ROPE_IDLE;
		}

		if (input & IN_JUMP)
			JumpOffRope(item);
	}
	else if (item->frame_number == anims[ANIMATION_LARA_ROPE_IDLE_TO_SWING].frame_base + 15)
	{
		ApplyVelocityToRope(lara.RopeSegment, item->pos.y_rot, 128);
	}
}

void lara_as_roper(struct ITEM_INFO* item, struct COLL_INFO* coll)//17B14(<), 17C48(<) (F)
{
	if (input & IN_ACTION)
	{
		if (input & IN_LEFT)
		{
			lara.RopeY -= 256;
		}
		else
		{
			item->goal_anim_state = STATE_LARA_ROPE_IDLE;
		}
	}
	else
	{
		FallFromRope(item);
	}
}

void lara_as_ropel(struct ITEM_INFO* item, struct COLL_INFO* coll)//17AB4(<), 17BE8(<) (F)
{
	if (input & IN_ACTION)
	{
		if (input & IN_LEFT)
		{
			lara.RopeY += 256;
		}
		else
		{
			item->goal_anim_state = STATE_LARA_ROPE_IDLE;
		}
	}
	else
	{
		FallFromRope(item);
	}
}

void lara_col_rope(struct ITEM_INFO* item, struct COLL_INFO* coll)//179A8, 17ADC (F)
{
	if (input & IN_ACTION)
	{
		UpdateRopeSwing(item);

		if (input & IN_SPRINT)
		{
			lara.RopeDFrame = (anims[ANIMATION_LARA_ROPE_SWING_FORWARD_SEMIHARD].frame_base + 32) << 8;
			lara.RopeFrame = lara.RopeDFrame;

			item->goal_anim_state = STATE_LARA_ROPE_SWING;
		}
		else if (input & IN_UP && lara.RopeSegment > 4)
		{
			item->goal_anim_state = STATE_LARA_ROPE_CLIMB_UP;
		}
		else if (input & IN_DOWN && lara.RopeSegment < 21)
		{
			item->goal_anim_state = STATE_LARA_ROPE_CLIMB_DOWN;

			lara.RopeFlag = 0;
			lara.RopeCount = 0;
		}
		else if (input & IN_LEFT)
		{
			item->goal_anim_state = STATE_LARA_ROPE_TURN_LEFT;
		}
		else if (input & IN_RIGHT)
		{
			item->goal_anim_state = STATE_LARA_ROPE_TURN_RIGHT;
		}
	}
	else
	{
		FallFromRope(item);
	}
}

void lara_as_rope(struct ITEM_INFO* item, struct COLL_INFO* coll)//17958(<), 17A8C(<) (F)
{
	if (!(input & IN_ACTION))
		FallFromRope(item);

	if (input & IN_LOOK)
		LookUpDown();
}

void ApplyVelocityToRope(int node, unsigned short angle, unsigned short n)//178E4, 17A18 (F)
{
	SetPendulumVelocity(
		n * SIN(angle) >> 2,
		0,
		n * COS(angle) >> 2);
}

void UpdateRopeSwing(struct ITEM_INFO* item)//17508, 1763C
{
	S_Warn("[UpdateRopeSwing] - Unimplemented!\n");
}

void JumpOffRope(struct ITEM_INFO* item)//17424, 17558 (F)
{
	if (lara.RopePtr != -1)
	{
		if (item->pos.x_rot >= 0)
		{
			item->fallspeed = -112;
			item->speed = item->pos.x_rot / 128;
		}
		else
		{
			item->speed = 0;
			item->fallspeed = -20;
		}

		item->pos.x_rot = 0;
		item->gravity_status = TRUE;

		lara.gun_status = LG_NO_ARMS;

		if (item->frame_number - anims[ANIMATION_LARA_ROPE_SWING_FORWARD_SEMIHARD].frame_base > 42)
		{
			item->anim_number = ANIMATION_LARA_ROPE_SWING_TO_TRY_HANG_FRONT2;
		}
		else if (item->frame_number - anims[ANIMATION_LARA_ROPE_SWING_FORWARD_SEMIHARD].frame_base > 21)
		{
			item->anim_number = ANIMATION_LARA_ROPE_SWING_TO_TRY_HANG_MIDDLE;
		}
		else
		{
			item->anim_number = ANIMATION_LARA_ROPE_SWING_TO_TRY_HANG_BACK;
		}

		item->frame_number = anims[item->anim_number].frame_base;

		item->current_anim_state = STATE_LARA_REACH;
		item->goal_anim_state = STATE_LARA_REACH;

		lara.RopePtr = -1;
	}
}

void FallFromRope(struct ITEM_INFO* item)//17394, 174C8 (F)
{
	item->speed = (abs(CurrentPendulum.Velocity.x >> 16) + abs(CurrentPendulum.Velocity.z >> 16)) >> 1; // todo this may explode if the values are negative but im too lazy
	item->pos.x_rot = 0;
	item->pos.y_pos += 320;

	item->anim_number = ANIMATION_LARA_FREE_FALL_FORWARD;
	item->frame_number = anims[ANIMATION_LARA_FREE_FALL_FORWARD].frame_base;
	item->current_anim_state = STATE_LARA_JUMP_FORWARD;
	item->goal_anim_state = STATE_LARA_JUMP_FORWARD;

	item->fallspeed = 0;
	item->gravity_status = TRUE;

	lara.gun_status = LG_NO_ARMS;
	lara.RopePtr = -1;
}

void lara_col_poledown(struct ITEM_INFO* item, struct COLL_INFO* coll)//171A0, 172D4 (F)
{
	coll->enable_spaz = FALSE;
	coll->enable_baddie_push = FALSE;

	if (input & IN_LOOK)
		LookUpDown();

	if (((input & IN_DOWN) ^ (input & IN_ACTION)) || item->hit_points <= 0)
		item->goal_anim_state = STATE_LARA_POLE_IDLE;

	coll->bad_pos = 32512;
	coll->bad_neg = -384;
	coll->bad_ceiling = 0;

	lara.move_angle = item->pos.y_rot;

	coll->slopes_are_walls = 1;

	coll->facing = lara.move_angle;
	coll->radius = 100;

	GetLaraCollisionInfo(item, coll);

	if (coll->mid_floor < 0)
	{
		short room_number = item->room_number;

		item->floor = GetHeight(GetFloor(item->pos.x_pos, item->pos.y_pos, item->pos.z_pos, &room_number), 
			item->pos.x_pos, item->pos.y_pos - 762, item->pos.z_pos);

		item->goal_anim_state = STATE_LARA_POLE_IDLE;

		item->item_flags[2] = 0;
	}

	if (input & IN_LEFT)
	{
		item->pos.y_rot += 256;
	}
	else if (input & IN_RIGHT)
	{
		item->pos.y_rot -= 256;
	}

	if (item->anim_number == ANIMATION_LARA_POLE_CLIMB_DOWN_TO_IDLE)
	{
		item->item_flags[2] -= 1024;
	}
	else
	{
		item->item_flags[2] += 256;
	}

	SoundEffect(SFX_LARA_ROPEDOWN_LOOP, &item->pos, 0);

	item->item_flags[2] = CLAMP(item->item_flags[2], 0, ANGLE(90));

	item->pos.y_pos += item->item_flags[2] >> 8;
}

void lara_col_poleup(struct ITEM_INFO* item, struct COLL_INFO* coll)//170D8(<), 1720C(<) (F)
{
	short room_num;

	coll->enable_baddie_push = FALSE;
	coll->enable_spaz = FALSE;

	if (input & IN_LOOK)
		LookUpDown();

	if (!(input & IN_ACTION) || !(input & IN_UP) || item->hit_points <= 0)
		item->goal_anim_state = STATE_LARA_POLE_IDLE;

	room_num = item->room_number;

	if (item->pos.y_pos - 
		GetCeiling(GetFloor(item->pos.x_pos, item->pos.y_pos, item->pos.z_pos, &room_num),
		item->pos.x_pos, item->pos.y_pos, item->pos.z_pos) < SECTOR(1))
		item->goal_anim_state = STATE_LARA_POLE_IDLE;
}

void lara_as_poleright(struct ITEM_INFO* item, struct COLL_INFO* coll)//1707C(<), 171B0(<) (F)
{
	coll->enable_baddie_push = FALSE;
	coll->enable_spaz = FALSE;
	if (!(input & IN_RIGHT) || !(input & IN_ACTION) || (input & (IN_UP | IN_DOWN)) || item->hit_points <= 0)
		item->goal_anim_state = STATE_LARA_POLE_IDLE;
	else
		item->pos.y_rot -= 256;
}

void lara_as_poleleft(struct ITEM_INFO* item, struct COLL_INFO* coll)//17020(<), 17154(<) (F)
{
	coll->enable_baddie_push = FALSE;
	coll->enable_spaz = FALSE;
	if (!(input & IN_LEFT) || !(input & IN_ACTION) || (input & (IN_UP | IN_DOWN)) || item->hit_points <= 0)
		item->goal_anim_state = STATE_LARA_POLE_IDLE;
	else
		item->pos.y_rot += 256;
}

void lara_col_polestat(struct ITEM_INFO* item, struct COLL_INFO* coll)//16DFC, 16F30 (F)
{
	if (item->hit_points <= 0)
	{
		item->goal_anim_state = STATE_LARA_FREEFALL;

		return;
	}

	coll->enable_spaz = FALSE;
	coll->enable_baddie_push = FALSE;

	if (item->anim_number == ANIMATION_LARA_POLE_IDLE)
	{
		coll->bad_pos = 32512;
		coll->bad_neg = -384;
		coll->bad_ceiling = 192;

		lara.move_angle = item->pos.y_rot;

		coll->facing = lara.move_angle;

		coll->radius = 100;

		coll->slopes_are_walls = 1;

		GetLaraCollisionInfo(item, coll);

		if (input & IN_ACTION)
		{
			item->goal_anim_state = STATE_LARA_POLE_IDLE;

			if (input & IN_LEFT)
			{
				item->goal_anim_state = STATE_LARA_POLE_TURN_LEFT;
			}
			else if (input & IN_RIGHT)
			{
				item->goal_anim_state = STATE_LARA_POLE_TURN_RIGHT;
			}

			if (input & IN_LOOK)
				LookUpDown();

			if (input & IN_UP)
			{
				short room_num = item->room_number;

				if (item->pos.y_pos - GetCeiling(GetFloor(item->pos.x_pos, item->pos.y_pos, item->pos.z_pos, &room_num),
				                                 item->pos.x_pos, item->pos.y_pos, item->pos.z_pos) > SECTOR(1))
				{
					item->goal_anim_state = STATE_LARA_POLE_UP;
				}
			}
			else if (input & IN_DOWN && coll->mid_floor > 0)
			{
				item->goal_anim_state = STATE_LARA_POLE_DOWN;

				item->item_flags[2] = 0;
			}

			if (input & IN_JUMP)
				item->goal_anim_state = STATE_LARA_JUMP_BACK;
		}
		else if (coll->mid_floor <= 0)
		{
			item->goal_anim_state = STATE_LARA_STOP;
		}
		else
		{
			item->pos.x_pos -= (64 * SIN(item->pos.y_rot)) >> W2V_SHIFT;
			item->pos.z_pos -= (64 * COS(item->pos.y_rot)) >> W2V_SHIFT;
		}
	}
}

void lara_col_monkey180(struct ITEM_INFO* item, struct COLL_INFO* coll)//16DDC, 16F10 (F)
{
	lara_col_monkeyswing(item, coll);
}

void lara_as_monkey180(struct ITEM_INFO* item, struct COLL_INFO* coll)//16DB8(<), 16EEC(<) (F)
{
	coll->enable_baddie_push = FALSE;
	coll->enable_spaz = FALSE;
	item->goal_anim_state = STATE_LARA_MONKEYSWING_IDLE;
}

void lara_as_hangturnr(struct ITEM_INFO* item, struct COLL_INFO* coll)//16D64(<), 16E98(<) (F)
{
	if (item->hit_points <= 0
		|| (camera.target_elevation = 1820, 
			lara.torso_y_rot = 0, 
			lara.torso_x_rot = 0, 
			item->pos.y_rot += ANGLE(1.5), 
			!(input & IN_RIGHT)))
	{
		item->goal_anim_state = STATE_LARA_MONKEYSWING_IDLE;
	}
}

void lara_col_hangturnlr(struct ITEM_INFO* item, struct COLL_INFO* coll)//16C94(<), 16DC8(<) (F)
{
	if ((input & IN_ACTION) && lara.CanMonkeySwing)
	{
		coll->bad_pos = 32512;
		coll->bad_neg = -384;
		coll->bad_ceiling = 0;

		lara.move_angle = item->pos.y_rot;
		coll->facing = item->pos.y_rot;

		coll->radius = 100;
		coll->slopes_are_walls = 1;

		GetCollisionInfo(coll, item->pos.x_pos, item->pos.y_pos, item->pos.z_pos, item->room_number, 600);
		MonkeySwingSnap(item, coll);
	}
	else
	{
		MonkeySwingFall(item);
	}
}

void lara_as_hangturnl(struct ITEM_INFO* item, struct COLL_INFO* coll)//16C40(<), 16D74(<) (F)
{
	if (item->hit_points <= 0
		|| (camera.target_elevation = 1820, 
			lara.torso_y_rot = 0,
			lara.torso_x_rot = 0, 
			item->pos.y_rot -= ANGLE(1.5), 
			!(input & IN_LEFT)))
	{
		item->goal_anim_state = STATE_LARA_MONKEYSWING_IDLE;
	}
}

void lara_col_monkeyr(struct ITEM_INFO* item, struct COLL_INFO* coll)//16B9C(<), 16CD0(<) (F)
{
	if ((input & IN_ACTION) && lara.CanMonkeySwing)
	{
		if (TestMonkeyRight(item, coll))
		{
			MonkeySwingSnap(item, coll);
		}
		else
		{
			item->anim_number = ANIMATION_LARA_MONKEY_IDLE;
			item->current_anim_state = STATE_LARA_MONKEYSWING_IDLE;
			item->goal_anim_state = STATE_LARA_MONKEYSWING_IDLE;
			item->frame_number = anims[ANIMATION_LARA_MONKEY_IDLE].frame_base;
		}
	}
	else
	{
		MonkeySwingFall(item);
	}
}

void lara_as_monkeyr(struct ITEM_INFO* item, struct COLL_INFO* coll)//16B24(<), 16C58(<) (F)
{
	if (item->hit_points <= 0)
	{
		item->goal_anim_state = STATE_LARA_MONKEYSWING_IDLE;

		return;
	}

	lara.torso_y_rot = 0;
	lara.torso_x_rot = 0;

	coll->enable_baddie_push = FALSE;
	coll->enable_spaz = FALSE;

	if (input & IN_RSTEP)
	{
		item->goal_anim_state = STATE_LARA_MONKEYSWING_RIGHT;
		camera.target_elevation = ANGLE(10);
	}
	else
	{
		item->goal_anim_state = STATE_LARA_MONKEYSWING_IDLE;
		camera.target_elevation = ANGLE(10);
	}
}

void lara_col_monkeyl(struct ITEM_INFO* item, struct COLL_INFO* coll)//16A80(<), 16BB4(<) (F)
{
	if ((input & IN_ACTION) && lara.CanMonkeySwing)
	{
		if (TestMonkeyLeft(item, coll))
		{
			MonkeySwingSnap(item, coll);
		}
		else
		{
			item->anim_number = ANIMATION_LARA_MONKEY_IDLE;
			item->current_anim_state = STATE_LARA_MONKEYSWING_IDLE;
			item->goal_anim_state = STATE_LARA_MONKEYSWING_IDLE;
			item->frame_number = anims[ANIMATION_LARA_MONKEY_IDLE].frame_base;
		}
	}
	else
	{
		MonkeySwingFall(item);
	}
}

void lara_as_monkeyl(struct ITEM_INFO* item, struct COLL_INFO* coll)//16A0C(<), 16B40(<) (F)
{
	if (item->hit_points <= 0)
	{
		item->goal_anim_state = STATE_LARA_MONKEYSWING_IDLE;

		return;
	}

	lara.torso_y_rot = 0;
	lara.torso_x_rot = 0;

	coll->enable_baddie_push = FALSE;
	coll->enable_spaz = FALSE;

	if (input & IN_LSTEP)
	{
		item->goal_anim_state = STATE_LARA_MONKEYSWING_LEFT;
		camera.target_elevation = ANGLE(10);
	}
	else
	{
		item->goal_anim_state = STATE_LARA_MONKEYSWING_IDLE;
		camera.target_elevation = ANGLE(10);
	}
}

void lara_col_monkeyswing(struct ITEM_INFO* item, struct COLL_INFO* coll)//16828, 1695C (F)
{
	if (input & IN_ACTION && lara.CanMonkeySwing)
	{
		coll->bad_pos = 32512;
		coll->bad_neg = -32512;
		coll->bad_ceiling = 0;

		lara.move_angle = item->pos.y_rot;

		coll->enable_spaz = FALSE;
		coll->enable_baddie_push = FALSE;

		coll->facing = lara.move_angle;
		coll->radius = 100;

		GetCollisionInfo(coll, item->pos.x_pos, item->pos.y_pos, item->pos.z_pos, item->room_number, 600);

		if (coll->coll_type == CT_FRONT
			|| abs(coll->mid_ceiling - coll->front_ceiling) > 50)
		{
			item->anim_number = ANIMATION_LARA_MONKEY_IDLE;
			item->frame_number = anims[ANIMATION_LARA_MONKEY_IDLE].frame_base;

			item->current_anim_state = STATE_LARA_MONKEYSWING_IDLE;
			item->goal_anim_state = STATE_LARA_MONKEYSWING_IDLE;
		}
		else
		{
			if (abs(coll->mid_ceiling - coll->left_ceiling2) <= 50)
			{
				if (abs(coll->mid_ceiling - coll->right_ceiling2) > 50)
				{
					ShiftItem(item, coll);
					item->pos.y_rot -= ANGLE(5);
				}
			}
			else
			{
				ShiftItem(item, coll);
				item->pos.y_rot += ANGLE(5);
			}

			camera.target_elevation = ANGLE(10);
			MonkeySwingSnap(item, coll);
		}
	}
	else
	{
		MonkeySwingFall(item);
	}
}

void lara_as_monkeyswing(struct ITEM_INFO* item, struct COLL_INFO* coll)//1670C, 16840 (F)
{
	if (item->hit_points <= 0)
	{
		item->goal_anim_state = STATE_LARA_MONKEYSWING_IDLE;

		return;
	}

	coll->enable_spaz = FALSE;
	coll->enable_baddie_push = FALSE;

	lara.torso_y_rot = 0;
	lara.torso_x_rot = 0;

	if (input & IN_LOOK)
		LookUpDown();

	if (input & IN_UP)
		item->goal_anim_state = STATE_LARA_MONKEYSWING_FORWARD;
	else
		item->goal_anim_state = STATE_LARA_MONKEYSWING_IDLE;

	if (input & IN_LEFT)
	{
		lara.turn_rate -= 409;

		if (lara.turn_rate < ANGLE(-3))
			lara.turn_rate = ANGLE(-3);
	}
	else if (input & IN_RIGHT)
	{
		lara.turn_rate += 409;

		if (lara.turn_rate > ANGLE(3))
			lara.turn_rate = ANGLE(3);
	}
}

void lara_col_hang2(struct ITEM_INFO* item, struct COLL_INFO* coll)//163DC, 16510 (F)
{
	item->fallspeed = 0;
	item->gravity_status = FALSE;

	if (lara.CanMonkeySwing)
	{
		coll->bad_pos = 32512;
		coll->bad_neg = -32512;
		coll->bad_ceiling = 0;

		coll->slopes_are_walls = 0;

		lara.move_angle = item->pos.y_rot;
		coll->facing = lara.move_angle;

		coll->radius = 100;

		GetCollisionInfo(coll, item->pos.x_pos, item->pos.y_pos, item->pos.z_pos, item->room_number, 600);

		if (input & IN_UP && coll->coll_type != CT_FRONT && abs(coll->mid_ceiling - coll->front_ceiling) < 50)
		{
			item->goal_anim_state = STATE_LARA_MONKEYSWING_FORWARD;
		}
		else if (input & IN_LSTEP && TestMonkeyLeft(item, coll))
		{
			item->goal_anim_state = STATE_LARA_MONKEYSWING_LEFT;
		}
		else if (input & IN_RSTEP && TestMonkeyRight(item, coll))
		{
			item->goal_anim_state = STATE_LARA_MONKEYSWING_RIGHT;
		}
		else if (input & IN_LEFT)
		{
			item->goal_anim_state = STATE_LARA_MONKEYSWING_TURN_LEFT;
		}
		else if (input & IN_RIGHT)
		{
			item->goal_anim_state = STATE_LARA_MONKEYSWING_TURN_RIGHT;	
		}

		MonkeySwingSnap(item, coll);
	}
	else
	{
		LaraHangTest(item, coll);

		if (item->goal_anim_state == STATE_LARA_MONKEYSWING_IDLE)
		{
			TestForObjectOnLedge(item, coll);

			if (!(input & IN_UP) ||
				coll->front_floor <= -850 ||
				coll->front_floor >= -650 ||
				coll->front_floor < coll->front_ceiling ||
				coll->left_floor2 < coll->left_ceiling2 ||
				coll->right_floor2 < coll->right_ceiling2 ||
				coll->hit_static)
			{
				if (!(input & IN_UP) ||
					coll->front_floor <= -850 ||
					coll->front_floor >= -650 ||
					coll->front_floor - coll->front_ceiling < -256 ||
					coll->left_floor2 - coll->left_ceiling2 < -256 ||
					coll->right_floor2 - coll->right_ceiling2 < -256 ||
					coll->hit_static)
				{
					if (input & IN_LEFT || input & IN_LSTEP)
					{
						item->goal_anim_state = STATE_LARA_SHIMMY_LEFT;
					}
					else if(input & IN_RIGHT || input & IN_RSTEP)
					{
						item->goal_anim_state = STATE_LARA_SHIMMY_RIGHT;
					}
				}
				else
				{
					item->goal_anim_state = STATE_LARA_CLIMB_TO_CRAWL;
					item->required_anim_state = STATE_LARA_CROUCH_IDLE;
				}
			}
			else if(input & IN_WALK)
			{
				item->goal_anim_state = STATE_LARA_HANDSTAND;
			}
			else if(input & IN_CROUCH)
			{
				item->goal_anim_state = STATE_LARA_CLIMB_TO_CRAWL;
				item->required_anim_state = STATE_LARA_CROUCH_IDLE;
			}
			else
			{
				item->goal_anim_state = STATE_LARA_GRABBING;
			}
		}
	}
}

void lara_as_hang2(struct ITEM_INFO* item, struct COLL_INFO* coll)//1630C(<), 16440(<) (F)
{
	if (item->hit_points <= 0)
	{
		item->goal_anim_state = STATE_LARA_STOP;

		return;
	}
	
	coll->enable_baddie_push = FALSE;
	coll->enable_spaz = FALSE;

	lara.torso_y_rot = 0;
	lara.torso_x_rot = 0;

	if (lara.CanMonkeySwing)
	{
		if (!(input & IN_ACTION) || item->hit_points <= 0)
			MonkeySwingFall(item);

		camera.target_angle = 0;
		camera.target_elevation = ANGLE(-45);
	}

	if (input & IN_LOOK)
		LookUpDown();
}

short TestMonkeyRight(struct ITEM_INFO* item, struct COLL_INFO* coll)//161EC(<), 16320(<) (F)
{
	short oct;
	coll->bad_pos = 32512;
	coll->bad_neg = -384;
	coll->bad_ceiling = 0;
	lara.move_angle = item->pos.y_rot + ANGLE(90);
	coll->slopes_are_walls = 0;
	coll->facing = lara.move_angle;
	coll->radius = 100;
	GetCollisionInfo(coll, item->pos.x_pos, item->pos.y_pos, item->pos.z_pos, item->room_number, 600);
	if (abs(coll->mid_ceiling - coll->front_ceiling) > 50)
		return 0;
	if (!coll->coll_type)
		return 1;
	oct = GetDirOctant(item->pos.y_rot);
	if (oct)
	{
		if (oct != 1)
			return 1;
		if (coll->coll_type != CT_FRONT && coll->coll_type != CT_RIGHT && coll->coll_type != CT_LEFT)
			return 1;
	}
	else if(coll->coll_type != CT_FRONT)
	{
		return 1;
	}

	return 0;
}

short TestMonkeyLeft(struct ITEM_INFO* item, struct COLL_INFO* coll)//160CC(<), 16200(<) (F)
{
	short oct;
	coll->bad_pos = 32512;
	coll->bad_neg = -32512;
	coll->bad_ceiling = 0;
	lara.move_angle = item->pos.y_rot - ANGLE(90);
	coll->slopes_are_walls = 0;
	coll->facing = lara.move_angle;
	coll->radius = 100;
	GetCollisionInfo(coll, item->pos.x_pos, item->pos.y_pos, item->pos.z_pos, item->room_number, 600);
	if (abs(coll->mid_ceiling - coll->front_ceiling) > 50)
		return 0;
	if (!coll->coll_type)
		return 1;
	oct = GetDirOctant(item->pos.y_rot);
	if(oct)
	{
		if (oct != 1)
			return 1;
		if (coll->coll_type != CT_RIGHT && coll->coll_type != CT_LEFT)
			return 1;
	}
	else
	{
		if (coll->coll_type != CT_FRONT && coll->coll_type != CT_LEFT)
			return 1;
	}

	return 0;
}

short GetDirOctant(long rot)//160B4(<), 161E8(<) (F)
{
	return abs(rot) >= ANGLE(45) && abs(rot) <= ANGLE(135);
}

void MonkeySwingSnap(struct ITEM_INFO* item, struct COLL_INFO* coll)//1605C(<), 16190(<) (F)
{
	short room_num = item->room_number;

	item->pos.y_pos = GetCeiling(GetFloor(item->pos.x_pos, item->pos.y_pos, item->pos.z_pos, &room_num),
		item->pos.x_pos, item->pos.y_pos, item->pos.z_pos) + 704;
}

void MonkeySwingFall(struct ITEM_INFO* item)//16004(<), 16138(<) (F)
{
	item->goal_anim_state = STATE_LARA_JUMP_UP;
	item->current_anim_state = STATE_LARA_JUMP_UP;

	item->anim_number = ANIMATION_LARA_TRY_HANG_VERTICAL;
	item->frame_number = anims[ANIMATION_LARA_TRY_HANG_VERTICAL].frame_base + 9;

	item->speed = 2;
	item->gravity_status = 1;

	item->fallspeed = 1;
	item->pos.y_pos += 256;

	lara.gun_status = LG_NO_ARMS;
}

void lara_col_dashdive(struct ITEM_INFO* item, struct COLL_INFO* coll)//15E5C, 15F90 (F)
{
	if (item->speed < 0)
		lara.move_angle = item->pos.y_rot - ANGLE(180);
	else
		lara.move_angle = item->pos.y_rot;

	coll->bad_pos = 32512;
	coll->bad_neg = -256;
	coll->bad_ceiling = 192;

	coll->slopes_are_walls = 1;

	GetLaraCollisionInfo(item, coll);

	LaraDeflectEdgeJump(item, coll);

	if (!LaraFallen(item, coll))
	{
		if (item->speed < 0)
			lara.move_angle = item->pos.y_rot;

		if (coll->mid_floor <= 0 && item->fallspeed > 0)
		{
			if (LaraLandedBad(item, coll))
			{
				item->goal_anim_state = STATE_LARA_DEATH;
			}
			else if (lara.water_status == 4 || !(input & IN_UP) || input & IN_WALK)
			{
				item->goal_anim_state = STATE_LARA_STOP;
			}
			else
			{
				item->goal_anim_state = STATE_LARA_RUN_FORWARD;
			}

			item->gravity_status = FALSE;
			item->fallspeed = 0;
			item->pos.y_pos += coll->mid_floor;
			item->speed = 0;

			AnimateLara(item);
		}

		ShiftItem(item, coll);

		if (coll->mid_floor != -32512)
			item->pos.y_pos += coll->mid_floor;
	}
}

void lara_as_dashdive(struct ITEM_INFO* item, struct COLL_INFO* coll)//15E1C(<), 15F50(<) (F)
{
	if (item->goal_anim_state != STATE_LARA_DEATH && 
		item->goal_anim_state != STATE_LARA_STOP && 
		item->goal_anim_state != STATE_LARA_RUN_FORWARD && 
		item->fallspeed > LARA_FREEFALL_SPEED)
		item->goal_anim_state = STATE_LARA_FREEFALL;
}

void lara_col_dash(struct ITEM_INFO* item, struct COLL_INFO* coll)//15C50, 15D84 (F)
{
	lara.move_angle = item->pos.y_rot;

	coll->bad_pos = 32512;
	coll->bad_neg = -384;
	coll->bad_ceiling = 0;

	coll->slopes_are_walls = 1;

	GetLaraCollisionInfo(item, coll);

	if (!LaraHitCeiling(item, coll) && !TestLaraVault(item, coll))
	{
		if (LaraDeflectEdge(item, coll))
		{
			item->pos.z_rot = 0;

			if (TestWall(item, 256, 0, -640))
			{
				item->current_anim_state = STATE_LARA_SPLAT;

				item->anim_number = ANIMATION_LARA_WALL_SMASH_LEFT;
				item->frame_number = anims[ANIMATION_LARA_WALL_SMASH_LEFT].frame_base;

				return;
			}

			LaraCollideStop(item, coll);
		}

		if (!LaraFallen(item, coll))
		{
			if (coll->mid_floor >= -384 && coll->mid_floor < -128)
			{
				if (item->frame_number >= 3 && item->frame_number <= 14)
				{
					item->anim_number = ANIMATION_LARA_RUN_UP_STEP_LEFT;
					item->frame_number = anims[ANIMATION_LARA_RUN_UP_STEP_LEFT].frame_base;
				}
				else
				{
					item->anim_number = ANIMATION_LARA_RUN_UP_STEP_RIGHT;
					item->frame_number = anims[ANIMATION_LARA_RUN_UP_STEP_RIGHT].frame_base;
				}
			}

			if (!TestLaraSlide(item, coll))
			{
				if (coll->mid_floor < 50)
				{
					if (coll->mid_floor != -32512)
						item->pos.y_pos += coll->mid_floor;
				}
				else
				{
					item->pos.y_pos += 50;
				}
			}
		}
	}
}

void lara_as_dash(struct ITEM_INFO* item, struct COLL_INFO* coll)//15A28, 15B5C (F)
{
	if (item->hit_points <= 0 || !DashTimer || !(input & IN_SPRINT) || lara.water_status == 4)
	{
		item->goal_anim_state = STATE_LARA_RUN_FORWARD;
		return;
	}

	DashTimer--;

	if (input & IN_CROUCH
		&& (lara.gun_status == LG_NO_ARMS
			|| lara.gun_type == WEAPON_NONE
			|| lara.gun_type == WEAPON_PISTOLS
			|| lara.gun_type == WEAPON_REVOLVER
			|| lara.gun_type == WEAPON_UZI
			|| lara.gun_type == WEAPON_FLARE))
	{
		item->goal_anim_state = STATE_LARA_CROUCH_IDLE;
		return;
	}

	if (input & IN_LEFT)
	{
		lara.turn_rate -= 409;
		if (lara.turn_rate < ANGLE(-4))
			lara.turn_rate = ANGLE(-4);

		item->pos.z_rot -= ANGLE(1.5);
		if (item->pos.z_rot < ANGLE(-16))
			item->pos.z_rot = ANGLE(-16);
	}
	else if (input & IN_RIGHT)
	{
		lara.turn_rate += 409;
		if (lara.turn_rate > ANGLE(4))
			lara.turn_rate = ANGLE(4);

		item->pos.z_rot += ANGLE(1.5);
		if (item->pos.z_rot > ANGLE(16))
			item->pos.z_rot = ANGLE(16);
	}

	if (!(input & IN_JUMP) || item->gravity_status)
	{
		if (input & IN_UP)
		{
			if (input & IN_WALK)
				item->goal_anim_state = STATE_LARA_WALK_FORWARD;
			else
				item->goal_anim_state = STATE_LARA_SPRINT;
		}
		else if (!(input & IN_LEFT) && !(input & IN_RIGHT))
		{
			item->goal_anim_state = STATE_LARA_STOP;
		}
	}
	else
	{
		item->goal_anim_state = STATE_LARA_SPRINT_ROLL;
	}
}

void lara_col_crawl2hang(struct ITEM_INFO* item, struct COLL_INFO* coll)//15770, 158A4 (F)
{
	camera.target_angle = 0;
	camera.target_elevation = ANGLE(-45);

	coll->enable_spaz = FALSE;
	coll->enable_baddie_push = FALSE;

	if (item->anim_number == ANIMATION_LARA_CRAWL_TO_HANG_END)
	{
		int edge_catch;
		long edge;

		item->fallspeed = 512;
		item->pos.y_pos += 255;

		coll->bad_pos = 32512;
		coll->bad_neg = -384;
		coll->bad_ceiling = 192;

		lara.move_angle = item->pos.y_rot;
		coll->facing = lara.move_angle;

		GetCollisionInfo(coll, item->pos.x_pos, item->pos.y_pos, item->pos.z_pos, item->room_number, 870);
		edge_catch = LaraTestEdgeCatch(item, coll, &edge);

		if (edge_catch)
		{
			if (edge_catch >= 0 || LaraTestHangOnClimbWall(item, coll))
			{
				short angle = item->pos.y_rot;

				if (abs(angle) > ANGLE(35))
				{
					if (angle >= 10014 && angle <= 22754)
					{
						angle = ANGLE(90);
					}
					else
					{
						if (abs(angle) >= 26397)
						{
							angle = ANGLE(-180);
						}
						else if(angle >= -22754 && angle <= -10014)
						{
							angle = ANGLE(-90);
						}
					}
				}
				else
				{
					angle = 0;
				}

				if ((angle & 0x3FFF) == 0)
				{
					short* bounds;

					if (TestHangSwingIn(item, angle))
					{
						lara.head_y_rot = 0;
						lara.head_x_rot = 0;
						lara.torso_y_rot = 0;
						lara.torso_x_rot = 0;

						item->anim_number = ANIMATION_LARA_OSCILLATE_HANG_ON;
						item->frame_number = anims[ANIMATION_LARA_OSCILLATE_HANG_ON].frame_base;

						item->current_anim_state = STATE_LARA_MONKEYSWING_IDLE;
						item->goal_anim_state = STATE_LARA_MONKEYSWING_IDLE;
					}
					else
					{
						item->anim_number = ANIMATION_LARA_HANG_IDLE;
						item->frame_number = anims[ANIMATION_LARA_HANG_IDLE].frame_base;

						item->current_anim_state = STATE_LARA_HANG;
						item->goal_anim_state = STATE_LARA_HANG;
					}

					bounds = GetBoundsAccurate(item);

					if (edge_catch <= 0)
					{
						item->pos.y_pos = edge - bounds[2];
					}
					else
					{
						item->pos.y_pos += coll->front_floor - bounds[2];
						item->pos.x_pos += coll->shift.x;
						item->pos.z_pos += coll->shift.z;
					}

					item->pos.y_rot = angle;

					item->gravity_status = TRUE;
					item->speed = 2;
					item->fallspeed = 1;

					lara.gun_status = LG_HANDS_BUSY;
				}
			}
		}
	}
}

void lara_col_crawlb(struct ITEM_INFO* item, struct COLL_INFO* coll)//15614, 15748 (F)
{
	item->gravity_status = FALSE;
	item->fallspeed = 0;

	coll->radius = 250;

	coll->bad_pos = 255;
	coll->bad_neg = -255;
	coll->bad_ceiling = 400;

	coll->slopes_are_pits = 1;
	coll->slopes_are_walls = 1;

	lara.move_angle = item->pos.y_rot - ANGLE(180);

	coll->facing = lara.move_angle;

	GetCollisionInfo(coll, item->pos.x_pos, item->pos.y_pos, item->pos.z_pos, item->room_number, 400);

	if (LaraDeflectEdgeDuck(item, coll))
	{
		item->current_anim_state = STATE_LARA_CRAWL_IDLE;
		item->goal_anim_state = STATE_LARA_CRAWL_IDLE;

		if (item->anim_number != ANIMATION_LARA_CRAWL_IDLE)
		{
			item->anim_number = ANIMATION_LARA_CRAWL_IDLE;
			item->frame_number = anims[ANIMATION_LARA_CRAWL_IDLE].frame_base;
		}
	}
	else if (LaraFallen(item, coll))
	{
		lara.gun_status = LG_NO_ARMS;
	}
	else if (!TestLaraSlide(item, coll))
	{
		ShiftItem(item, coll);

		if (coll->mid_floor != -32512 && coll->mid_floor > -CLICK)
			item->pos.y_pos += coll->mid_floor;

		lara.move_angle = item->pos.y_rot;
	}
}

void lara_as_crawlb(struct ITEM_INFO* item, struct COLL_INFO* coll)//154F0, 15624 (F)
{
	if (item->hit_points <= 0 || lara.water_status == 4)
	{
		item->goal_anim_state = STATE_LARA_CRAWL_IDLE;

		return;
	}
	
	if (input & IN_LOOK)
		LookUpDown();

	coll->enable_spaz = FALSE;
	coll->enable_baddie_push = TRUE;

	lara.torso_y_rot = 0;
	lara.torso_x_rot = 0;

	camera.target_elevation = ANGLE(-23);

	if (input & IN_DOWN)
	{
		if (input & IN_RIGHT)
		{
			lara.turn_rate -= 409;
			if (lara.turn_rate < ANGLE(-3))
				lara.turn_rate = ANGLE(-3);
		}
		else if (input & IN_LEFT)
		{
			lara.turn_rate += 409;
			if (lara.turn_rate > ANGLE(3))
				lara.turn_rate = ANGLE(3);
		}
	}
	else
	{
		item->goal_anim_state = STATE_LARA_CRAWL_IDLE;
	}
}

void lara_as_all4turnr(struct ITEM_INFO* item, struct COLL_INFO* coll)//15484(<), 155B8(<) (F)
{
	if (item->hit_points <= 0
		|| (coll->enable_spaz = 0,
			coll->enable_baddie_push = 1,
			lara.torso_y_rot = 0,
			lara.torso_x_rot = 0,
			camera.target_elevation = ANGLE(-23),
			item->pos.y_rot += ANGLE(1.5),
			!(input & IN_RIGHT)))
	{
		item->goal_anim_state = STATE_LARA_CRAWL_IDLE;
	}
}

void lara_col_all4turnlr(struct ITEM_INFO* item, struct COLL_INFO* coll)//153FC, 15530 (F)
{
	GetCollisionInfo(coll, item->pos.x_pos, item->pos.y_pos, item->pos.z_pos, item->room_number, 400);

	if (!TestLaraSlide(item, coll))
	{
		if (coll->mid_floor != -32512 && coll->mid_floor > -256)
			item->pos.y_pos += coll->mid_floor;
	}
}

void lara_as_all4turnl(struct ITEM_INFO* item, struct COLL_INFO* coll)//15390(<), 154C4(<) (F)
{
	if (item->hit_points <= 0
		|| (coll->enable_spaz = 0,
			coll->enable_baddie_push = 1,
			lara.torso_y_rot = 0,
			lara.torso_x_rot = 0,
			camera.target_elevation = ANGLE(-23),
			item->pos.y_rot -= ANGLE(1.5),
			!(input & IN_LEFT)))
	{
		item->goal_anim_state = STATE_LARA_CRAWL_IDLE;
	}
}

void lara_col_crawl(struct ITEM_INFO* item, struct COLL_INFO* coll)//1523C, 15370 (F)
{
	item->gravity_status = FALSE;
	item->fallspeed = 0;

	lara.move_angle = item->pos.y_rot;

	coll->radius = 200;

	coll->bad_pos = 255;
	coll->bad_neg = -255;
	coll->bad_ceiling = 400;

	coll->slopes_are_pits = 1;
	coll->slopes_are_walls = 1;

	coll->facing = lara.move_angle;

	GetCollisionInfo(coll, item->pos.x_pos, item->pos.y_pos, item->pos.z_pos, item->room_number, -400);

	if (LaraDeflectEdgeDuck(item, coll))
	{
		item->current_anim_state = STATE_LARA_CRAWL_IDLE;
		item->goal_anim_state = STATE_LARA_CRAWL_IDLE;

		if (item->anim_number != ANIMATION_LARA_CRAWL_IDLE)
		{
			item->anim_number = ANIMATION_LARA_CRAWL_IDLE;
			item->frame_number = anims[ANIMATION_LARA_CRAWL_IDLE].frame_base;
		}
	}
	else if (LaraFallen(item, coll))
	{
		lara.gun_status = LG_NO_ARMS;
	}
	else if (!TestLaraSlide(item, coll))
	{
		ShiftItem(item, coll);

		if (coll->mid_floor != -32512 && coll->mid_floor > -256)
			item->pos.y_pos += coll->mid_floor;
	}
}

void lara_as_crawl(struct ITEM_INFO* item, struct COLL_INFO* coll)//150F4, 15228 (F)
{
	if (item->hit_points <= 0 || input & IN_JUMP)
	{
		item->goal_anim_state = STATE_LARA_CRAWL_IDLE;

		return;
	}
	
	if (input & IN_LOOK)
		LookUpDown();

	lara.torso_x_rot = 0;
	lara.torso_y_rot = 0;

	coll->enable_spaz = FALSE;
	coll->enable_baddie_push = TRUE;

	camera.target_elevation = ANGLE(-23);

	if (input & IN_UP
		&& (input & IN_CROUCH || lara.keep_ducked)
		&& lara.water_status != 4)
	{
		if (input & IN_LEFT)
		{
			lara.turn_rate -= 409;

			if (lara.turn_rate < ANGLE(-3))
				lara.turn_rate = ANGLE(-3);
		}
		else if (input & IN_RIGHT)
		{
			lara.turn_rate += 409;

			if (lara.turn_rate > ANGLE(3))
				lara.turn_rate = ANGLE(3);
		}
	}
	else
	{
		item->goal_anim_state = STATE_LARA_CRAWL_IDLE;
	}
}

void lara_col_all4s(struct ITEM_INFO* item, struct COLL_INFO* coll)//14B40, 14C74 (F)
{
	item->fallspeed = 0;
	item->gravity_status = FALSE;

	if (item->goal_anim_state != STATE_LARA_CRAWL_TO_CLIMB)
	{
		lara.move_angle = item->pos.y_rot;
		coll->facing = lara.move_angle;

		coll->radius = 200;
		coll->bad_pos = 255;
		coll->bad_neg = -255;
		coll->bad_ceiling = 400;

		coll->slopes_are_walls = 1;
		coll->slopes_are_pits = 1;

		GetCollisionInfo(coll, item->pos.x_pos, item->pos.y_pos, item->pos.z_pos, item->room_number, 400);

		if (LaraFallen(item, coll))
		{
			lara.gun_status = LG_NO_ARMS;
		}
		else if(!TestLaraSlide(item, coll))
		{
			int slope = abs(coll->left_floor2 - coll->right_floor2);

			lara.keep_ducked = coll->mid_ceiling >= -362;
			ShiftItem(item, coll);

			if (coll->mid_floor != -32512 && coll->mid_floor > -256)
				item->pos.y_pos += coll->mid_floor;

			if (input & IN_CROUCH || lara.keep_ducked &&
				(!(input & IN_UNK19) && !(input & IN_DRAW) || input & IN_UP) &&
				lara.water_status != 4)
			{
				if (item->anim_number == ANIMATION_LARA_CRAWL_IDLE ||
					item->anim_number == ANIMATION_LARA_CROUCH_TO_CRAWL_END)
				{
					if (input & IN_UP)
					{
						if (abs(LaraFloorFront(item, item->pos.y_rot, 256)) < 255 && height_type != BIG_SLOPE)
							item->goal_anim_state = STATE_LARA_CRAWL_FORWARD;
					}
					else if(input & IN_DOWN)
					{
						short height = LaraCeilingFront(item, item->pos.y_rot, -300, 128);
						short heightl = 0;
						short heightr = 0;

						if (height != -32512 && height <= 256)
						{
							if (input & IN_ACTION)
							{
								long x = item->pos.x_pos;
								long z = item->pos.z_pos;

								item->pos.x_pos += 128 * SIN(item->pos.y_rot - ANGLE(90)) >> W2V_SHIFT;
								item->pos.z_pos += 128 * COS(item->pos.y_rot - ANGLE(90)) >> W2V_SHIFT;

								heightl = LaraFloorFront(item, item->pos.y_rot, -300);

								item->pos.x_pos += 256 * SIN(item->pos.y_rot + ANGLE(90)) >> W2V_SHIFT;
								item->pos.z_pos += 256 * COS(item->pos.y_rot + ANGLE(90)) >> W2V_SHIFT;

								heightr = LaraFloorFront(item, item->pos.y_rot, -300);

								item->pos.x_pos = x;
								item->pos.z_pos = z;
							}

							height = LaraFloorFront(item, item->pos.y_rot, -300);

							if (abs(height) >= 255 || height_type == BIG_SLOPE)
							{
								if (input & IN_ACTION)
								{
									if (height > 768 &&
										heightl > 768 &&
										heightr > 768 &&
										slope < 120)
									{
										int tmp;
										struct ITEM_INFO* tmp1;
										struct MESH_INFO* tmp2;
										long x = item->pos.x_pos;
										long z = item->pos.z_pos;

										item->pos.x_pos -= 100 * SIN(coll->facing) >> W2V_SHIFT;
										item->pos.z_pos -= 100 * SIN(coll->facing) >> W2V_SHIFT;

										//tmp = GetCollidedObjects(item, 100, 1, wat, wat, 0);
										S_Warn("[lara_col_all4s] - Warning: Core Design function call shittery\n");
										tmp = GetCollidedObjects(item, 100, 1, &tmp1, &tmp2, 0);

										item->pos.x_pos = x;
										item->pos.z_pos = z;

										if (!tmp)
										{
											switch((unsigned short)(item->pos.y_rot + ANGLE(45)) / (unsigned short)ANGLE(90))
											{
											case 0:
												item->pos.y_rot = 0;
												item->pos.z_pos = (item->pos.z_pos & 0xFFFFFC00) + 225;
												break;
											case 2:
												item->pos.y_rot = -32768;
												item->pos.z_pos = (item->pos.z_pos | 0x3FF) - 225;
												break;
											case 1:
												item->pos.y_rot = 0x4000;
												item->pos.x_pos = (item->pos.x_pos & 0xFFFFFC00) + 225;
												break;
											case 3:
												item->pos.y_rot = -16384;
												item->pos.x_pos = (item->pos.x_pos | 0x3FF) - 225;
												break;
											}

											item->goal_anim_state = STATE_LARA_CRAWL_TO_CLIMB;
										}
									}
								}
							}
							else
							{
								item->goal_anim_state = STATE_LARA_CRAWL_BACK;
							}
						}
					}
					else if (input & IN_LEFT)
					{
						item->anim_number = ANIMATION_LARA_CRAWL_TURN_LEFT;
						item->frame_number = anims[ANIMATION_LARA_CRAWL_TURN_LEFT].frame_base;

						item->current_anim_state = STATE_LARA_CRAWL_TURN_LEFT;
						item->goal_anim_state = STATE_LARA_CRAWL_TURN_LEFT;
					}
					else if (input & IN_RIGHT)
					{
						item->anim_number = ANIMATION_LARA_CRAWL_TURN_RIGHT;
						item->frame_number = anims[ANIMATION_LARA_CRAWL_TURN_RIGHT].frame_base;

						item->current_anim_state = STATE_LARA_CRAWL_TURN_RIGHT;
						item->goal_anim_state = STATE_LARA_CRAWL_TURN_RIGHT;
					}
				}
			}
			else
			{
				item->goal_anim_state = STATE_LARA_CROUCH_IDLE;
			}
		}
	}
}

void lara_as_all4s(struct ITEM_INFO* item, struct COLL_INFO* coll)//14970, 14A78 (F)
{
	if (item->hit_points <= 0)
	{
		item->goal_anim_state = STATE_LARA_DEATH;

		return;
	}
	
	if (input & IN_JUMP)
	{
		if (LaraFloorFront(item, item->pos.y_rot, 768) >= 512 && 
			LaraCeilingFront(item, item->pos.y_rot, 768, 512) != -32512 &&
			LaraCeilingFront(item, item->pos.y_rot, 768, 512) <= 0)
		{
			struct GAME_VECTOR s, d;
			struct MESH_INFO* StaticMesh;
			struct PHD_VECTOR v;

			s.x = lara_item->pos.x_pos;
			s.y = lara_item->pos.y_pos - 96;
			s.z = lara_item->pos.z_pos;
			s.room_number = lara_item->room_number;

			d.x = s.x + (768 * SIN(lara_item->pos.y_rot) >> W2V_SHIFT);
			d.y = s.y + 160;
			d.z = s.z + (768 * COS(lara_item->pos.y_rot) >> W2V_SHIFT);

			if (LOS(&s, &d))
			{
				if (ObjectOnLOS2(&s, &d, &v, &StaticMesh) == 999)
				{
					item->anim_number = ANIMATION_LARA_CRAWL_JUMP_DOWN;
					item->frame_number = anims[ANIMATION_LARA_CRAWL_JUMP_DOWN].frame_base;

					item->goal_anim_state = STATE_LARA_MISC_CONTROL;
					item->current_anim_state = STATE_LARA_MISC_CONTROL;
				}
			}
		}
	}

	if (input & IN_LOOK)
		LookUpDown();

	lara.torso_x_rot = 0;
	lara.torso_y_rot = 0;

	coll->enable_spaz = FALSE;
	coll->enable_baddie_push = TRUE;

	if (item->anim_number == ANIMATION_LARA_CROUCH_TO_CRAWL_BEGIN)
		lara.gun_status = LG_HANDS_BUSY;

	camera.target_elevation = ANGLE(-23);
}

void lara_col_duck(struct ITEM_INFO* item, struct COLL_INFO* coll)//147C4, 148CC (F)
{
	item->gravity_status = FALSE;
	item->fallspeed = 0;

	lara.move_angle = item->pos.y_rot;

	coll->facing = item->pos.y_rot;

	coll->bad_pos = 384;
	coll->bad_neg = -384;
	coll->bad_ceiling = 0;

	coll->slopes_are_walls = 1;

	GetCollisionInfo(coll, item->pos.x_pos, item->pos.y_pos, item->pos.z_pos, item->room_number, 400);

	if (LaraFallen(item, coll))
	{
		lara.gun_status = LG_NO_ARMS;
	}
	else if (!TestLaraSlide(item, coll))
	{
		lara.keep_ducked = coll->mid_ceiling < -362;

		ShiftItem(item, coll);

		if (coll->mid_floor != -32512)
			item->pos.y_pos += coll->mid_floor;

		if (input & IN_CROUCH && lara.water_status != 4 || lara.keep_ducked || item->anim_number != ANIMATION_LARA_CROUCH_IDLE)
		{
			if (input & IN_LEFT)
			{
				item->goal_anim_state = STATE_LARA_CROUCH_TURN_LEFT;
			}
			else if (input & IN_RIGHT)
			{
				item->goal_anim_state = STATE_LARA_CROUCH_TURN_RIGHT;
			}
		}
		else
		{
			item->goal_anim_state = STATE_LARA_STOP;
		}
	}
}

void lara_as_duck(struct ITEM_INFO* item, struct COLL_INFO* coll)//14688, 14738 (F)
{
	short room_num;

	coll->enable_spaz = FALSE;
	coll->enable_baddie_push = TRUE;

	lara.IsDucked = TRUE;

	if (item->hit_points <= 0)
	{
		item->goal_anim_state = STATE_LARA_CRAWL_IDLE;

		return;
	}
	
	room_num = lara_item->room_number;

	if (input & IN_LOOK)
		LookUpDown();

	GetFloor(lara_item->pos.x_pos, lara_item->pos.y_pos, lara_item->pos.z_pos, &room_num);

	if ((input & IN_UP || input & IN_DOWN)
		&& (input & IN_CROUCH || lara.keep_ducked)
		&& lara.gun_status == LG_NO_ARMS
		&& lara.water_status != 4
		&& !(room[room_num].flags & RF_FILL_WATER))
	{

		if ((item->anim_number == ANIMATION_LARA_CROUCH_IDLE || item->anim_number == ANIMATION_LARA_CROUCH_PREPARE) 
			&& !(input & 0x80000 || input & IN_DRAW) 
			&& (lara.gun_type != WEAPON_FLARE || lara.flare_age < 900 && lara.flare_age != 0))
		{
			lara.torso_y_rot = 0;
			lara.torso_x_rot = 0;

			item->goal_anim_state = STATE_LARA_CRAWL_IDLE;
		}
	}
}

void lara_col_ducklr(struct ITEM_INFO* item, struct COLL_INFO* coll)//14534, 145E4 (F)
{
	item->gravity_status = FALSE;
	item->fallspeed = 0;

	lara.move_angle = item->pos.y_rot;

	coll->facing = item->pos.y_rot;
	coll->bad_pos = 384;
	coll->bad_neg = -384;
	coll->bad_ceiling = 0;
	coll->slopes_are_walls = 1;

	GetCollisionInfo(coll, item->pos.x_pos, item->pos.y_pos, item->pos.z_pos, item->room_number, 400);
	
	if (LaraFallen(item, coll))
	{
		lara.gun_status = LG_NO_ARMS;
	}
	else if (!TestLaraSlide(item, coll))
	{
		if (coll->mid_ceiling < -362)
			lara.keep_ducked = FALSE;
		else
			lara.keep_ducked = TRUE;

		ShiftItem(item, coll);

		if (coll->mid_floor != -32512)
			item->pos.y_pos += coll->mid_floor;
	}
}

void lara_as_duckr(struct ITEM_INFO* item, struct COLL_INFO* coll)//144E0(<), 14590(<) (F)
{
	coll->enable_spaz = FALSE;
	if ((input & IN_CROUCH) ^ (input & IN_LEFT) || item->hit_points <= 0)
		item->goal_anim_state = STATE_LARA_CROUCH_IDLE;
	item->pos.y_rot += ANGLE(1.5);
}

void lara_as_duckl(struct ITEM_INFO* item, struct COLL_INFO* coll)//1448C(<), 1453C(<) (F)
{
	coll->enable_spaz = FALSE;
	if ((input & IN_CROUCH) ^ (input & IN_LEFT) || item->hit_points <= 0)
		item->goal_anim_state = STATE_LARA_CROUCH_IDLE;
	item->pos.y_rot -= ANGLE(1.5);
}

void LaraAboveWater(struct ITEM_INFO* item, struct COLL_INFO* coll)//14228, 142D8 (F)
{
	coll->old.x = item->pos.x_pos;
	coll->old.y = item->pos.y_pos;
	coll->old.z = item->pos.z_pos;

	coll->slopes_are_walls = 0;
	coll->slopes_are_pits = 0;
	coll->lava_is_pit = 0;

	coll->enable_baddie_push = TRUE;
	coll->enable_spaz = TRUE;

	coll->old_anim_state = item->current_anim_state;
	coll->old_anim_number = item->anim_number;
	coll->old_frame_number = item->frame_number;

	coll->radius = 100;
	coll->trigger = 0;

	if (input & IN_LOOK && lara.look)
		LookLeftRight();
	else
		ResetLook();

	lara_control_routines[item->current_anim_state](item, coll);

	item->pos.z_rot = CLAMPADD(item->pos.z_rot, ANGLE(-1), ANGLE(1));
	lara.turn_rate = CLAMPADD(lara.turn_rate, ANGLE(-2), ANGLE(2));

	AnimateLara(item);
	LaraBaddieCollision(item, coll);
	lara_control_routines[item->current_anim_state](item, coll);
	UpdateLaraRoom(item, -381);

	if (lara.gun_type == WEAPON_CROSSBOW && !LaserSight && gfLevelFlags & GF_LVOP_TRAIN)
	{
		input &= ~IN_ACTION;
	}

	LaraGun();

	TestTriggers(coll->trigger, 0, 0);
}

int TestHangSwingIn(struct ITEM_INFO* item, short angle)//14104, 141B4 (F)
{
	int x = item->pos.x_pos;
	int y = item->pos.y_pos;
	int z = item->pos.z_pos;
	short room_num = item->room_number;
	struct FLOOR_INFO* floor;
	int h, c;

	if (angle == ANGLE(-180))
	{
		z -= 256;
	}
	else if (angle == ANGLE(-90))
	{
		x -= 256;
	}
	else if(angle == ANGLE(90))
	{
		x += 256;
	}
	else
	{
		z += 256;
	}

	floor = GetFloor(x, y, z, &room_num);
	h = GetHeight(floor, x, y, z);
	c = GetCeiling(floor, x, y, z);

	return h != -32512 && h - y > 0 && c - y < -400 && y - c - 819 > -72;
}

int LaraHangLeftCornerTest(struct ITEM_INFO* item, struct COLL_INFO* coll)//13C24, 13CD4
{
	S_Warn("[LaraHangLeftCornerTest] - Unimplemented!\n");
	return 0;
}

int LaraHangRightCornerTest(struct ITEM_INFO* item, struct COLL_INFO* coll)//13738, 137E8
{
	S_Warn("[LaraHangRightCornerTest] - Unimplemented!\n");
	return 0;
}

int IsValidHangPos(struct ITEM_INFO* item, struct COLL_INFO* coll)//135BC, 1366C (F)
{
	if (LaraFloorFront(item, lara.move_angle, 100) < 200)
		return FALSE;

	switch((unsigned short)(item->pos.y_rot + ANGLE(45)) / (unsigned short)ANGLE(90))
	{
	case 0:
		item->pos.z_pos += 4;
		break;
	case 1:
		item->pos.x_pos += 4;
		break;
	case 2:
		item->pos.z_pos -= 4;
		break;
	case 3:
		item->pos.x_pos -= 4;
		break;
	default:
		break;
	}

	coll->bad_pos = 32512;
	coll->bad_neg = -512;
	coll->bad_ceiling = 0;

	lara.move_angle = item->pos.y_rot;

	GetLaraCollisionInfo(item, coll);

	if (coll->mid_ceiling >= 0 || coll->coll_type != CT_FRONT || coll->hit_static)
		return FALSE;

	return abs(coll->front_floor - coll->right_floor2) < 60;
}

int LaraHangTest(struct ITEM_INFO* item, struct COLL_INFO* coll)//12F34, 12FE4
{
	S_Warn("[LaraHangTest] - Unimplemented!\n");
	return 0;
}

void SnapLaraToEdgeOfBlock(struct ITEM_INFO* item, struct COLL_INFO* coll, short angle)//12E54, 12F04 (F)
{
	if (item->current_anim_state == STATE_LARA_SHIMMY_RIGHT)
	{
		switch(angle)
		{
		case 0:
			item->pos.x_pos = coll->old.x & 0xFFFFFF90 | 0x390;
			return;
		case 1:
			item->pos.z_pos = coll->old.z & 0xFFFFFC70 | 0x70;
			return;
		case 2:
			item->pos.x_pos = coll->old.x & 0xFFFFFC70 | 0x70;
			return;
		case 3:
		default:
			item->pos.z_pos = coll->old.z & 0xFFFFFF90 | 0x390;
			return;
		}
	}

	if (item->current_anim_state == STATE_LARA_SHIMMY_LEFT)
	{
		switch(angle)
		{
		case 0:
			item->pos.x_pos = coll->old.x & 0xFFFFFC70 | 0x70;
			return;
		case 1:
			item->pos.z_pos = coll->old.z & 0xFFFFFF90 | 0x390;
			return;
		case 2:
			item->pos.x_pos = coll->old.x & 0xFFFFFF90 | 0x390;
			return;
		case 3:
		default:
			item->pos.z_pos = coll->old.z & 0xFFFFFC70 | 0x70;
			return;
		}
	}
}

int LaraTestHangOnClimbWall(struct ITEM_INFO* item, struct COLL_INFO* coll)//12C54, 12D04 (F)
{
	short* bounds;
	int shift, result;

	if (lara.climb_status == 0)
		return FALSE;

	if (item->fallspeed < 0)
		return FALSE;

	switch((unsigned short)(item->pos.y_rot + ANGLE(45)) / (unsigned short)ANGLE(90))
	{
	case 0:
	case 2:
		item->pos.z_pos += coll->shift.z;
		break;

	case 1:
	case 3:
		item->pos.x_pos += coll->shift.x;
		break;

	default:
		break;
	}

	bounds = GetBoundsAccurate(item);

	if (lara.move_angle != item->pos.y_rot)
	{
		short l = LaraCeilingFront(item, item->pos.y_rot, 0, 0);
		short r = LaraCeilingFront(item, lara.move_angle, 128, 0);

		if (abs(l - r) > 60)
			return FALSE;
	}

	if (LaraTestClimbPos(item, coll->radius, coll->radius, bounds[2], bounds[3] - bounds[2], &shift) &&
		LaraTestClimbPos(item, coll->radius, -coll->radius, bounds[2], bounds[3] - bounds[2], &shift) &&
		(result = LaraTestClimbPos(item, coll->radius, 0, bounds[2], bounds[3] - bounds[2], &shift)) != 0)
	{
		if (result != 1)
		{
			item->pos.y_pos += shift;
			return TRUE;
		}
	}

	return FALSE;
}

void LaraSlideEdgeJump(struct ITEM_INFO* item, struct COLL_INFO* coll)//12B18, 12BC8 (F)
{
	ShiftItem(item, coll);

	switch (coll->coll_type)
	{
	case CT_LEFT:
		item->pos.y_rot += ANGLE(5);
		break;

	case CT_RIGHT:
		item->pos.y_rot -= ANGLE(5);
		break;

	case CT_TOP:
	case CT_TOP_FRONT:
		if (item->fallspeed <= 0)
			item->fallspeed = 1;
		break;

	case CT_CLAMP:
		item->pos.z_pos -= (100 * COS(coll->facing)) >> W2V_SHIFT;	
		item->pos.x_pos -= (100 * SIN(coll->facing)) >> W2V_SHIFT;

		item->speed = 0;

		coll->mid_floor = 0;

		if (item->fallspeed <= 0)
			item->fallspeed = 16;

		break;
	}
}

void LaraDeflectEdgeJump(struct ITEM_INFO* item, struct COLL_INFO* coll)//12904, 129B4 (F)
{
	ShiftItem(item, coll);

	switch (coll->coll_type)
	{
	case CT_FRONT:
	case CT_TOP_FRONT:
		if (!lara.climb_status || item->speed != 2)
		{
			if (coll->mid_floor <= 512)
			{
				if (coll->mid_floor <= 128)
				{
					item->goal_anim_state = STATE_LARA_GRAB_TO_FALL;
					item->current_anim_state = STATE_LARA_GRAB_TO_FALL;

					item->anim_number = ANIMATION_LARA_LANDING_LIGHT;
					item->frame_number = anims[ANIMATION_LARA_LANDING_LIGHT].frame_base;
				}
			}
			else
			{
				item->goal_anim_state = STATE_LARA_FREEFALL;
				item->current_anim_state = STATE_LARA_FREEFALL;

				item->anim_number = ANIMATION_LARA_SMASH_JUMP;
				item->frame_number = anims[ANIMATION_LARA_SMASH_JUMP].frame_base + 1;
			}

			item->speed /= 4;
			lara.move_angle -= ANGLE(180);

			if (item->fallspeed <= 0)
				item->fallspeed = 1;
		}

		break;
	case CT_TOP:
		if (item->fallspeed <= 0)
			item->fallspeed = 1;

		break;
	case CT_LEFT:
		item->pos.y_rot += ANGLE(5);
		break;
	case CT_RIGHT:
		item->pos.y_rot -= ANGLE(5);
		break;
	case CT_CLAMP:
		item->pos.x_pos -= (100 * SIN(coll->facing)) >> W2V_SHIFT;
		item->pos.z_pos -= (100 * COS(coll->facing)) >> W2V_SHIFT;

		item->speed = 0;
		coll->mid_floor = 0;

		if (item->fallspeed <= 0)
			item->fallspeed = 16;

		break;
	}
}

void lara_slide_slope(struct ITEM_INFO* item, struct COLL_INFO* coll)//127BC, 1286C (F)
{
	coll->bad_pos = 32512;
	coll->bad_neg = -512;
	coll->bad_ceiling = 0;

	GetLaraCollisionInfo(item, coll);

	if (!LaraHitCeiling(item, coll))
	{
		LaraDeflectEdge(item, coll);

		if (coll->mid_floor <= 200)
		{
			TestLaraSlide(item, coll);

			item->pos.y_pos += coll->mid_floor;

			if (abs(coll->tilt_x) <= 2 && abs(coll->tilt_z) <= 2)
			{
				item->goal_anim_state = STATE_LARA_STOP;
				StopSoundEffect(SFX_LARA_SLIPPING);
			}
		}
		else
		{
			if (item->current_anim_state == STATE_LARA_SLIDE_FORWARD)
			{
				item->anim_number = ANIMATION_LARA_FREE_FALL_FORWARD;
				item->frame_number = anims[ANIMATION_LARA_FREE_FALL_FORWARD].frame_base;

				item->current_anim_state = STATE_LARA_JUMP_FORWARD;
				item->goal_anim_state = STATE_LARA_JUMP_FORWARD;
			}
			else
			{
				item->anim_number = ANIMATION_LARA_FREE_FALL_BACK;
				item->frame_number = anims[ANIMATION_LARA_FREE_FALL_BACK].frame_base;

				item->current_anim_state = STATE_LARA_FALL_BACKWARD;
				item->goal_anim_state = STATE_LARA_FALL_BACKWARD;
			}

			StopSoundEffect(SFX_LARA_SLIPPING);

			item->gravity_status = TRUE;
			item->fallspeed = 0;
		}
	}
}

void LaraCollideStop(struct ITEM_INFO* item, struct COLL_INFO* coll)//126F0(<), 127A0(<) (F)
{
	switch (coll->old_anim_state)
	{
	case STATE_LARA_STOP:
	case STATE_LARA_TURN_RIGHT_SLOW:
	case STATE_LARA_TURN_LEFT_SLOW:
	case STATE_LARA_TURN_FAST:
		item->current_anim_state = coll->old_anim_state;
		item->anim_number = coll->old_anim_number;
		item->frame_number = coll->old_frame_number;
		if (input & IN_LEFT)
		{
			item->goal_anim_state = STATE_LARA_TURN_LEFT_SLOW;
		}
		else if (input & IN_RIGHT)
		{
			item->goal_anim_state = STATE_LARA_TURN_RIGHT_SLOW;
		}
		else
		{
			item->goal_anim_state = STATE_LARA_STOP;
		}
		AnimateLara(item);
		break;
	default:
		item->anim_number = ANIMATION_LARA_STAY_SOLID;
		item->frame_number = anims[ANIMATION_LARA_STAY_SOLID].frame_base;
		break;
	}
}

int TestWall(struct ITEM_INFO* item, long front, long right, long down)//12550, 12600 (F)
{
	int x = item->pos.x_pos;
	int y = item->pos.y_pos + down;
	int z = item->pos.z_pos;

	short angle = item->pos.y_rot + ANGLE(45);
	short room_num = item->room_number;

	struct FLOOR_INFO* floor;
	int h, c;

	switch(angle / (unsigned short)ANGLE(90))
	{
	case 0:
		x -= right;
		break;
	case 1:
		z -= right;
		break;
	case 2:
		x += right;
		break;
	case 3:
		z += right;
		break;
	default:
		break;
	}

	GetFloor(x, y, z, &room_num);

	switch (angle / (unsigned short)ANGLE(90))
	{
	case 0:
		z += front;
		break;
	case 1:
		x += front;
		break;
	case 2:
		z -= front;
		break;
	case 3:
		x -= front;
		break;
	default:
		break;
	}

	floor = GetFloor(x, y, z, &room_num);
	h = GetHeight(floor, x, y, z);
	c = GetCeiling(floor, x, y, z);

	if (h == -32512)
		return 1;

	if (y >= h || y <= c)
		return 2;

	return 0;
}

int TestLaraVault(struct ITEM_INFO* item, struct COLL_INFO* coll)//120C0, 12170
{
	S_Warn("[TestLaraVault] - Unimplemented!\n");
	return 0;
}

int LaraTestClimbStance(struct ITEM_INFO* item, struct COLL_INFO* coll)//11F78, 12028
{
	int shift_r, shift_l;

	if (LaraTestClimbPos(item, coll->radius, coll->radius + 120, -700, 512, &shift_r) != 1)
		return FALSE;

	if (LaraTestClimbPos(item, coll->radius, -(coll->radius + 120), -700, 512, &shift_l) != 1)
		return FALSE;

	if (shift_r)
	{
		if (shift_l)
		{
			if (shift_r < 0 != shift_l < 0)
				return FALSE;

			if ((shift_r < 0 && shift_l < shift_r) ||
				(shift_r > 0 && shift_l > shift_r))
			/*if (SIGN(shift_r) == SIGN(shift_l) &&
				abs(shift_l) > abs(shift_r))*/
			{
				item->pos.y_pos += shift_l;
				return TRUE;
			}
		}

		item->pos.y_pos += shift_r;
	}
	else if (shift_l)
	{
		item->pos.y_pos += shift_l;
	}

	return TRUE;
}

int LaraTestEdgeCatch(struct ITEM_INFO* item, struct COLL_INFO* coll, long* edge)//11E60, 11F10
{
	S_Warn("[LaraTestEdgeCatch] - Unimplemented!\n");
	return 0;
}

int LaraDeflectEdgeDuck(struct ITEM_INFO* item, struct COLL_INFO* coll)//11DC0, 11E70 (F)
{
	if (coll->coll_type == CT_FRONT || coll->coll_type == CT_TOP_FRONT)
	{
		ShiftItem(item, coll);

		item->gravity_status = FALSE;
		item->speed = 0;

		return 1;
	}
	else if (coll->coll_type == CT_LEFT)
	{
		ShiftItem(item, coll);
		item->pos.y_rot += ANGLE(2);
	}
	else if (coll->coll_type == CT_RIGHT)
	{
		ShiftItem(item, coll);
		item->pos.y_rot -= ANGLE(2);
	}

	return 0;
}

int LaraDeflectEdge(struct ITEM_INFO* item, struct COLL_INFO* coll)//11D18(<), 11DC8(<) (F)
{
	if (coll->coll_type == CT_FRONT || coll->coll_type == CT_TOP_FRONT)
	{
		ShiftItem(item, coll);

		item->goal_anim_state = 2;
		item->speed = 0;
		item->gravity_status = 0;

		return 1;
	}
	else if (coll->coll_type == CT_LEFT)
	{
		ShiftItem(item, coll);
		item->pos.y_rot += ANGLE(5);
		return 0;
	}
	else
	{
		if (coll->coll_type == CT_RIGHT)
		{
			ShiftItem(item, coll);
			item->pos.y_rot -= ANGLE(5);
		}
		return 0;
	}
}

int LaraHitCeiling(struct ITEM_INFO* item, struct COLL_INFO* coll)//11C94, 11D44 (F)
{
	if (coll->coll_type == CT_TOP || coll->coll_type == CT_CLAMP)
	{
		item->pos.x_pos = coll->old.x;
		item->pos.y_pos = coll->old.y;
		item->pos.z_pos = coll->old.z;

		item->goal_anim_state = STATE_LARA_STOP;
		item->current_anim_state = STATE_LARA_STOP;

		item->anim_number = ANIMATION_LARA_STAY_SOLID;
		item->frame_number = anims[ANIMATION_LARA_STAY_SOLID].frame_base;

		item->speed = 0;
		item->fallspeed = 0;
		item->gravity_status = 0;

		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

int LaraLandedBad(struct ITEM_INFO* item, struct COLL_INFO* coll)//11BD8(<), 11C88(<) (F)
{
	int landspeed = item->fallspeed - 140;

	if (landspeed > 0)
	{
		if (landspeed <= 14)
		{
			item->hit_points += -1000 * landspeed * landspeed / 196;
			return item->hit_points <= 0;
		}
		else
		{
			item->hit_points = -1;
			return item->hit_points <= 0;
		}
	}

	return FALSE;
}

int LaraFallen(struct ITEM_INFO* item, struct COLL_INFO* coll)//11B6C, 11C1C (F)
{
	if (lara.water_status == 4 || coll->mid_floor <= 384)
	{
		return FALSE;
	}
	else
	{
		item->anim_number = ANIMATION_LARA_FREE_FALL_FORWARD;
		item->current_anim_state = STATE_LARA_JUMP_FORWARD;
		item->goal_anim_state = STATE_LARA_JUMP_FORWARD;
		item->frame_number = anims[ANIMATION_LARA_FREE_FALL_FORWARD].frame_base;
		item->fallspeed = 0;
		item->gravity_status = TRUE;
		return TRUE;
	}
}

int TestLaraSlide(struct ITEM_INFO* item, struct COLL_INFO* coll)//11998, 11A48
{
	S_Warn("[TestLaraSlide] - Unimplemented!\n");
	return 0;
}

short LaraCeilingFront(struct ITEM_INFO* item, short ang, long dist, long h)//1189C, 1194C (F)
{
	short room = item->room_number;

	long x = item->pos.x_pos + ((dist * SIN(ang)) >> W2V_SHIFT);
	long y = item->pos.y_pos - h;
	long z = item->pos.z_pos + ((dist * COS(ang)) >> W2V_SHIFT);

	long height = GetHeight(GetFloor(x, y, z, &room), x, y, z);

	if (height != -32512)
		height += h - item->pos.y_pos;

	return height;
}

short LaraFloorFront(struct ITEM_INFO* item, short ang, long dist)//117B0, 11860 (F)
{
	short room = item->room_number;

	long x = item->pos.x_pos + ((dist * SIN(ang)) >> W2V_SHIFT);
	long y = item->pos.y_pos - 762;
	long z = item->pos.z_pos + ((dist * COS(ang)) >> W2V_SHIFT);

	long height = GetHeight(GetFloor(x, y, z, &room), x, y, z);

	if (height != -32512)
		height -= item->pos.y_pos;

	return height;
}

void GetLaraCollisionInfo(struct ITEM_INFO* item, struct COLL_INFO* coll)//11764(<), 11814(<) (F)
{
	coll->facing = lara.move_angle;
	GetCollisionInfo(coll, item->pos.x_pos, item->pos.y_pos, item->pos.z_pos, item->room_number, 762);
}

int GetLaraJointPos(struct PHD_VECTOR* arg1, long arg2)
{
	S_Warn("[GetLaraJointPos] - Unimplemented!\n");
	return 0;
}

void AnimateLara(struct ITEM_INFO* item)
{
	S_Warn("[AnimateLara] - Unimplemented!\n");
}

void SetLaraUnderwaterNodes()//8596C(<), 879B0(<) (F) 
{
	return;//not used yet
#if 0
	struct PHD_VECTOR joint;
	short room_number;//_18
	struct room_info* r;//$a1
	long flags;//$s1
	long current_joint;//$s0

	joint.x = 0;
	joint.y = 0;
	joint.z = 0;

	flags = 0;

	//loc_85988
	for (current_joint = 14; current_joint >= 0; current_joint--)
	{
		GetLaraJointPos(&joint, current_joint);

		room_number = lara_item->room_number;
		GetFloor(joint.x, joint.y, joint.z, &room_number);

		r = &room[room_number];
		LaraNodeUnderwater[current_joint] = r->flags & RF_FILL_WATER;

		if (r->flags & RF_FILL_WATER)
		{
			lara.wet[current_joint] = 0xFC;

			if (!(flags & 1))
			{
				flags |= 1;
				((long*) SRhandPtr)[3] = ((long*) &r->ambient)[0];
			}
		}
		else
		{
			//loc_85A1C
			if (!(flags & 2))
			{
				flags |= 2;
				((long*) SRhandPtr)[2] = ((long*) &r->ambient)[0];
			}
		}
	}
#endif
}

void SetPendulumVelocity(int x, int y, int z)// (F)
{
	if ((CurrentPendulum.node & 0xFFFFFFFE) < 24)
	{
		int val = 4096 / ((12 - (CurrentPendulum.node >> 1)) << 9 >> 8) << 8; // todo make this more beautiful

		x = (x * val) >> 16;
		y = (y * val) >> 16;
		z = (z * val) >> 16;
	}

	CurrentPendulum.Velocity.x += x;
	CurrentPendulum.Velocity.y += y;
	CurrentPendulum.Velocity.z += z;
}

void LaraClimbRope(struct ITEM_INFO* item, struct COLL_INFO* coll)
{
	S_Warn("[LaraClimbRope] - Unimplemented!\n");
}

void FireChaff()
{
	S_Warn("[FireChaff] - Unimplemented!\n");
}

void GetLaraJointPosRot(struct PHD_VECTOR *a1, int a2, int a3, struct SVECTOR *a4)
{
	S_Warn("[GetLaraJointPosRot] - Unimplemented!\n");
}

void DoSubsuitStuff()
{
	S_Warn("[DoSubsuitStuff] - Unimplemented!\n");
}