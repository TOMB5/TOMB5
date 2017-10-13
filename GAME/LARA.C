#include "LARA.H"

#include "SPECIFIC.H"
#include "CAMERA.H"
#include "CONTROL.H"
#include "EFFECTS.H"
#include "COLLIDE.H"
#include "DRAW.H"
#include INPUT_H
#include "SOUND.H"

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

void lara_as_pbleapoff(struct ITEM_INFO* item, struct COLL_INFO* coll)//1D244, 1D3D8
{
	S_Warn("[lara_as_pbleapoff] - Unimplemented!\n");
}

void lara_as_parallelbars(struct ITEM_INFO* item, struct COLL_INFO* coll)//1D220(<), 1D3B4(<) (F)
{
	if(!(input & IN_ACTION))
	{
		item->goal_anim_state = STATE_LARA_BARS_JUMP;
	}
}

void lara_as_trfall(struct ITEM_INFO* item, struct COLL_INFO* coll)//1D03C, 1D1D0
{
	S_Warn("[lara_as_trfall] - Unimplemented!\n");
}

void lara_as_trwalk(struct ITEM_INFO* item, struct COLL_INFO* coll)//1CEDC, 1D070
{
	S_Warn("[lara_as_trwalk] - Unimplemented!\n");
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
	if (lara.gun_status != 1 && !lara.left_arm.lock && !lara.right_arm.lock)
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
	if (lara.gun_status != 1 && !lara.left_arm.lock && !lara.right_arm.lock)
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

		if (lara.gun_status == 1 || lara.left_arm.lock || lara.right_arm.lock)
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

void lara_col_wade(struct ITEM_INFO* item, struct COLL_INFO* coll)//1C61C, 1C750
{
	S_Warn("[lara_col_wade] - Unimplemented!\n");
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

void lara_col_roll2(struct ITEM_INFO* item, struct COLL_INFO* coll)//1C384, 1C4B8
{
	S_Warn("[lara_col_roll2] - Unimplemented!\n");
}

void lara_col_roll(struct ITEM_INFO* item, struct COLL_INFO* coll)//1C2B0, 1C3E4
{
	lara.move_angle = item->pos.y_rot;

	coll->bad_pos = 32512;
	coll->bad_neg = -384;
	coll->bad_ceiling = 0;

	item->gravity_status = 0;
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

void lara_col_stepright(struct ITEM_INFO* item, struct COLL_INFO* coll)//1BFB0, 1C0E4
{
	S_Warn("[lara_col_stepright] - Unimplemented!\n");
}

void lara_col_back(struct ITEM_INFO* item, struct COLL_INFO* coll)//1BE38, 1BF6C
{
	S_Warn("[lara_col_back] - Unimplemented!\n");
}

void lara_col_compress(struct ITEM_INFO* item, struct COLL_INFO* coll)//1BD30, 1BE64
{
	S_Warn("[lara_col_compress] - Unimplemented!\n");
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

void lara_col_fastfall(struct ITEM_INFO* item, struct COLL_INFO* coll)//1BB88, 1BCBC
{
	S_Warn("[lara_col_fastfall] - Unimplemented!\n");
}

void lara_col_death(struct ITEM_INFO* item, struct COLL_INFO* coll)//1BADC(<), 1BC10(<) (F)
{
	StopSoundEffect(30);

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

void lara_col_turn_r(struct ITEM_INFO* item, struct COLL_INFO* coll)//1B9C4, 1BAF8
{
	S_Warn("[lara_col_turn_r] - Unimplemented!\n");
}

void lara_col_fastback(struct ITEM_INFO* item, struct COLL_INFO* coll)//1B89C, 1B9D0
{
	S_Warn("[lara_col_fastback] - Unimplemented!\n");
}

void lara_col_pose(struct ITEM_INFO* item, struct COLL_INFO* coll)//1B87C(<), 1B9B0(<) (F)
{
	lara_col_stop(item, coll);
}

void lara_col_run(struct ITEM_INFO* item, struct COLL_INFO* coll)//1B64C, 1B780
{
	S_Warn("[lara_col_run] - Unimplemented!\n");
}

void lara_col_walk(struct ITEM_INFO* item, struct COLL_INFO* coll)//1B3E8, 1B51C
{
	S_Warn("[lara_col_walk] - Unimplemented!\n");
}

void lara_as_pulley(struct ITEM_INFO* item, struct COLL_INFO* coll)//1B288, 1B3BC
{
	S_Warn("[lara_as_pulley] - Unimplemented!\n");
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
	lara.look = 0;
	coll->enable_baddie_push = 0;
	coll->enable_spaz = 0;
}

void lara_as_controlled(struct ITEM_INFO* item, struct COLL_INFO* coll)//1B0FC(<), 1B230(<) (F)
{
	lara.look = 0;
	coll->enable_baddie_push = 0;
	coll->enable_spaz = 0;
	if (item->frame_number == anims[item->anim_number].frame_end - 1)
	{
		lara.gun_status = 0;
		if (UseForcedFixedCamera)
			UseForcedFixedCamera = 0;
	}
}

void lara_as_deathslide(struct ITEM_INFO* item, struct COLL_INFO* coll)//1B038, 1B16C
{
	S_Warn("[lara_as_deathslide] - Unimplemented!\n");
}

void lara_as_wade(struct ITEM_INFO* item, struct COLL_INFO* coll)//1AF10, 1B044
{
	S_Warn("[lara_as_wade] - Unimplemented!\n");
}

void lara_as_waterout(struct ITEM_INFO* item, struct COLL_INFO* coll)//1AEE4(<), 1B018(<) (F)
{
	coll->enable_baddie_push = 0;
	coll->enable_spaz = 0;
	camera.flags = 1;
}

void lara_as_gymnast(struct ITEM_INFO* item, struct COLL_INFO* coll)//1AEC8(<), 1AFFC(<) (F)
{
	coll->enable_baddie_push = 0;
	coll->enable_spaz = 0;
}

void lara_as_fastdive(struct ITEM_INFO* item, struct COLL_INFO* coll)//1AE4C(<), 1AF80(<) (F)
{
	if (input & IN_ROLL && item->goal_anim_state == STATE_LARA_SWANDIVE_END)
		item->goal_anim_state = STATE_LARA_JUMP_ROLL;
	coll->enable_baddie_push = 1;
	coll->enable_spaz = 0;
	item->speed = (item->speed * 95) / 100;
}

void lara_as_swandive(struct ITEM_INFO* item, struct COLL_INFO* coll)//1AE08(<), 1AF3C(<) (F)
{
	coll->enable_baddie_push = 1;
	coll->enable_spaz = 0;
	if (item->fallspeed > LARA_FREEFALL_SPEED && item->goal_anim_state != STATE_LARA_UNDERWATER_DIVING)
		item->goal_anim_state = STATE_LARA_SWANDIVE_END;
}

void lara_as_special(struct ITEM_INFO* item, struct COLL_INFO* coll)//1ADDC(<), 1AF10(<) (F)
{
	camera.flags = 1;
	camera.target_angle = ANGLE(170);
	camera.target_elevation = ANGLE(-25);
}

void lara_as_usepuzzle(struct ITEM_INFO* item, struct COLL_INFO* coll)//1AD18(<), 1AE4C(<) (F)
{
	lara.look = 0;

	coll->enable_baddie_push = 0;
	coll->enable_spaz = 0;

	camera.target_angle = ANGLE(-80);
	camera.target_elevation = ANGLE(-25);
	camera.target_distance = SECTOR;

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
	coll->enable_baddie_push = 0;
	coll->enable_spaz = 0;
	camera.target_angle = ANGLE(-80);
	camera.target_elevation = -4550;
	camera.target_distance = SECTOR;
}

void lara_as_switchoff(struct ITEM_INFO* item, struct COLL_INFO* coll)//1AC54(<), 1AD88(<) (F)
{
	lara.look = 0;
	coll->enable_baddie_push = 0;
	coll->enable_spaz = 0;
	camera.target_angle = ANGLE(80);
	camera.target_elevation = ANGLE(-25);
	camera.target_distance = SECTOR;
	camera.speed = 6;
}

void lara_as_switchon(struct ITEM_INFO* item, struct COLL_INFO* coll)//1ABEC(<), 1AD20(<) (F)
{
	lara.look = 0;
	coll->enable_baddie_push = 0;
	coll->enable_spaz = 0;
	camera.target_angle = ANGLE(80);
	camera.target_elevation = ANGLE(-25);
	camera.target_distance = SECTOR;
	camera.speed = 6;
}

void lara_as_pickupflare(struct ITEM_INFO* item, struct COLL_INFO* coll)//1AB5C(<), 1AC90(<) (F)
{
	lara.look = 0;
	coll->enable_baddie_push = 0;
	coll->enable_spaz = 0;
	camera.target_angle = ANGLE(130);
	camera.target_elevation = ANGLE(-15);
	camera.target_distance = SECTOR;
	if (item->frame_number = anims[item->anim_number].frame_end - 1)
		lara.gun_status = 0;
}

void lara_as_pickup(struct ITEM_INFO* item, struct COLL_INFO* coll)//1AB00(<), 1AC34(<) (F)
{
	lara.look = 0;
	coll->enable_baddie_push = 0;
	coll->enable_spaz = 0;
	camera.target_angle = ANGLE(-130);
	camera.target_elevation = ANGLE(-15);
	camera.target_distance = SECTOR;
}

void lara_as_ppready(struct ITEM_INFO* item, struct COLL_INFO* coll)//1AABC(<), 1ABF0(<) (F)
{
	coll->enable_baddie_push = 0;
	coll->enable_spaz = 0;
	camera.target_angle = ANGLE(75);
	if(!(input & IN_ACTION))
		item->goal_anim_state = STATE_LARA_STOP;
}

void lara_as_pullblock(struct ITEM_INFO* item, struct COLL_INFO* coll)//1AA60(<), 1AB94(<) (F)
{
	lara.look = 0;
	coll->enable_baddie_push = 0;
	coll->enable_spaz = 0;
	camera.flags = 1;
	camera.target_angle = ANGLE(35);
	camera.target_elevation = -4550;
}

void lara_as_pushblock(struct ITEM_INFO* item, struct COLL_INFO* coll)//1AA04(<), 1AB38(<) (F)
{
	lara.look = 0;
	coll->enable_baddie_push = 0;
	coll->enable_spaz = 0;
	camera.flags = 1;
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
		if (!lara.gun_status)
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
	if (item->hit_points > 0)
	{
		if (!lara.IsMoving)
		{

			if (!(input & IN_LSTEP))
			{
				item->goal_anim_state = STATE_LARA_STOP;
			}

			if (input & IN_LEFT)
			{
				lara.turn_rate -= 409;
				if (lara.turn_rate < -728)
					lara.turn_rate = -728;
			}
			else if (input & IN_RIGHT)
			{
				lara.turn_rate += 409;
				if (lara.turn_rate > 728)
					lara.turn_rate = 728;
			}
		}
	}
	else
	{
		item->goal_anim_state = STATE_LARA_STOP;
	}
}

void lara_as_stepright(struct ITEM_INFO* item, struct COLL_INFO* coll)//1A67C(<), 1A7B0(<) (F)
{
	if (item->hit_points > 0)
	{
		if (!lara.IsMoving)
		{

			if (!(input & IN_RSTEP))
			{
				item->goal_anim_state = STATE_LARA_STOP;
			}

			if (input & IN_LEFT)
			{
				lara.turn_rate -= 409;
				if (lara.turn_rate < -728)
					lara.turn_rate = -728;
			}
			else if (input & IN_RIGHT)
			{
				lara.turn_rate += 409;
				if (lara.turn_rate > 728)
					lara.turn_rate = 728;
			}
		}
	}
	else
	{
		item->goal_anim_state = STATE_LARA_STOP;
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
		lara.turn_rate = 1456;
		if (input & IN_RIGHT)
			return;

		item->goal_anim_state = STATE_LARA_STOP;
	}
	else
	{
		lara.turn_rate = -1456;
		if (input & IN_LEFT)
			return;

		item->goal_anim_state = STATE_LARA_STOP;
	}
}

void lara_as_null(struct ITEM_INFO* item, struct COLL_INFO* coll)//1A5DC(<), 1A710(<) (F)
{
	coll->enable_baddie_push = 0;
	coll->enable_spaz = 0;
	return;
}

void lara_as_back(struct ITEM_INFO* item, struct COLL_INFO* coll)//1A4F0(<), 1A624(<) (F)
{
	if (item->hit_points > 0)
	{
		if (!lara.IsMoving)
		{
			if ((input & IN_DOWN) && ((input & IN_WALK) || lara.water_status == 4))
				item->goal_anim_state = STATE_LARA_WALK_BACK;
			else
				item->goal_anim_state = STATE_LARA_STOP;

			if (input & IN_LEFT)
			{
				lara.turn_rate -= 409;
				if (lara.turn_rate < -728)
					lara.turn_rate = -728;
			}
			else if (input & IN_RIGHT)
			{
				lara.turn_rate += 409;
				if (lara.turn_rate > 728)
					lara.turn_rate = 728;
			}
		}
	}
	else
	{
		item->goal_anim_state = STATE_LARA_STOP;
	}
}

void lara_as_compress(struct ITEM_INFO* item, struct COLL_INFO* coll)//1A35C, 1A490
{
	S_Warn("[lara_as_compress] - Unimplemented!\n");
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

void SetCornerAnim(struct ITEM_INFO* item, struct COLL_INFO* coll, short rot, short flip)//1A090, 1A1C4
{
	S_Warn("[SetCornerAnim] - Unimplemented!\n");
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
	coll->enable_baddie_push = 0;
	coll->enable_spaz = 0;
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
	coll->enable_baddie_push = 0;
	coll->enable_spaz = 0;
	camera.target_angle = 0;
	camera.target_elevation = ANGLE(-45);
	if (!(input & (IN_LEFT | IN_LSTEP)))
		item->goal_anim_state = STATE_LARA_HANG;
}

void lara_col_hang(struct ITEM_INFO* item, struct COLL_INFO* coll)//19AC8, 19BFC
{
	S_Warn("[lara_col_hang] - Unimplemented!\n");
}

void lara_as_hang(struct ITEM_INFO* item, struct COLL_INFO* coll)//19A28, 19B5C
{
	lara.IsClimbing = 0;
	if (item->hit_points > 0)
	{
		if (input & IN_LOOK)
			LookUpDown();

		coll->enable_baddie_push = 0;
		coll->enable_spaz = 0;

		camera.target_angle = 0;
		camera.target_elevation = ANGLE(-45);
	}
	else
	{
		item->goal_anim_state = STATE_LARA_STOP;
	}
}

int CanLaraHangSideways(struct ITEM_INFO* item, struct COLL_INFO* coll, short angle)//19930, 19A64
{
	S_Warn("[CanLaraHangSideways] - Unimplemented!\n");
	return 0;
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
	coll->enable_baddie_push = 0;
	coll->enable_spaz = 0;
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

	if (lara.gun_status != 4 || lara.water_status == 4)
	{
		if (lara.turn_rate < -728)
		{
			if (input & IN_WALK)
				lara.turn_rate = -728;
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

	if (lara.gun_status != 4 || lara.water_status == 4)
	{
		if (lara.turn_rate > 728)
		{
			if (input & IN_WALK)
				lara.turn_rate = 728;
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
		if (lara.turn_rate < -1092)
			lara.turn_rate = -1092;
	}
	else if(input & IN_RIGHT)
	{
		lara.turn_rate += 409;
		if (lara.turn_rate > 1092)
			lara.turn_rate = 1092;
	}
}

void lara_as_run(struct ITEM_INFO* item, struct COLL_INFO* coll)//192EC, 19420
{
	S_Warn("[lara_as_run] - Unimplemented!\n");
}

void lara_as_walk(struct ITEM_INFO* item, struct COLL_INFO* coll)//191B8(<), 192EC(<) (F)
{
	if (item->hit_points > 0)
	{
		if (!lara.IsMoving)
		{
			if (input & IN_LEFT)
			{
				lara.turn_rate -= 409;
				if (lara.turn_rate < -728)
					lara.turn_rate = -728;
			}
			else if (input & IN_RIGHT)
			{
				lara.turn_rate += 409;
				if (lara.turn_rate > 728)
					lara.turn_rate = 728;
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
	else
	{
		item->goal_anim_state = STATE_LARA_STOP;
	}
}

void lara_col_reach(struct ITEM_INFO* item, struct COLL_INFO* coll)//18D0C, 18E40
{
	S_Warn("[lara_col_reach] - Unimplemented!\n");
}

void lara_as_reach(struct ITEM_INFO* item, struct COLL_INFO* coll)//18CE0(<), 18E14(<) (F)
{
	camera.target_angle = ANGLE(85);
	if (item->fallspeed > LARA_FREEFALL_SPEED)
		item->goal_anim_state = STATE_LARA_FREEFALL;
}

void lara_col_forwardjump(struct ITEM_INFO* item, struct COLL_INFO* coll)//18B88, 18CBC
{
	S_Warn("[lara_col_forwardjump] - Unimplemented!\n");
}

void lara_as_forwardjump(struct ITEM_INFO* item, struct COLL_INFO* coll)//18A34, 18B68
{
	S_Warn("[lara_as_forwardjump] - Unimplemented!\n");
}

void lara_col_upjump(struct ITEM_INFO* item, struct COLL_INFO* coll)//1853C, 18670
{
	S_Warn("[lara_col_upjump] - Unimplemented!\n");
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

void lara_as_stop(struct ITEM_INFO* item, struct COLL_INFO* coll)//17E94, 17FC8
{
	S_Warn("[lara_as_stop] - Unimplemented!\n");
}

void lara_as_climbroped(struct ITEM_INFO* item, struct COLL_INFO* coll)//17E64, 17F98
{
	S_Warn("[lara_as_climbroped] - Unimplemented!\n");
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

void lara_col_ropefwd(struct ITEM_INFO* item, struct COLL_INFO* coll)//17B74, 17CA8
{
	S_Warn("[lara_col_ropefwd] - Unimplemented!\n");
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

void lara_col_rope(struct ITEM_INFO* item, struct COLL_INFO* coll)//179A8, 17ADC
{
	S_Warn("[lara_col_rope] - Unimplemented!\n");
}

void lara_as_rope(struct ITEM_INFO* item, struct COLL_INFO* coll)//17958(<), 17A8C(<) (F)
{
	if (!(input & IN_ACTION))
		FallFromRope(item);

	if (input & IN_LOOK)
		LookUpDown();
}

void ApplyVelocityToRope(int node, unsigned short angle, unsigned short n)//178E4, 17A18
{
	S_Warn("[ApplyVelocityToRope] - Unimplemented!\n");
}

void UpdateRopeSwing(struct ITEM_INFO* item)//17508, 1763C
{
	S_Warn("[UpdateRopeSwing] - Unimplemented!\n");
}

void JumpOffRope(struct ITEM_INFO* item)//17424, 17558
{
	S_Warn("[JumpOffRope] - Unimplemented!\n");
}

void FallFromRope(struct ITEM_INFO* item)//17394, 174C8
{
	S_Warn("[FallFromRope] - Unimplemented!\n");
}

void lara_col_poledown(struct ITEM_INFO* item, struct COLL_INFO* coll)//171A0, 172D4
{
	S_Warn("[lara_col_poledown] - Unimplemented!\n");
}

void lara_col_poleup(struct ITEM_INFO* item, struct COLL_INFO* coll)//170D8(<), 1720C(<) (F)
{
	short room_num;

	coll->enable_baddie_push = 0;
	coll->enable_spaz = 0;

	if (input & IN_LOOK)
		LookUpDown();

	if (!(input & IN_ACTION) || !(input & IN_UP) || item->hit_points <= 0)
		item->goal_anim_state = STATE_LARA_POLE_IDLE;

	room_num = item->room_number;

	if (item->pos.y_pos - 
		GetCeiling(GetFloor(item->pos.x_pos, item->pos.y_pos, item->pos.z_pos, &room_num),
		item->pos.x_pos, item->pos.y_pos, item->pos.z_pos) < SECTOR)
		item->goal_anim_state = STATE_LARA_POLE_IDLE;
}

void lara_as_poleright(struct ITEM_INFO* item, struct COLL_INFO* coll)//1707C(<), 171B0(<) (F)
{
	coll->enable_baddie_push = 0;
	coll->enable_spaz = 0;
	if (!(input & IN_RIGHT) || !(input & IN_ACTION) || (input & (IN_UP | IN_DOWN)) || item->hit_points <= 0)
		item->goal_anim_state = STATE_LARA_POLE_IDLE;
	else
		item->pos.y_rot -= 256;
}

void lara_as_poleleft(struct ITEM_INFO* item, struct COLL_INFO* coll)//17020(<), 17154(<) (F)
{
	coll->enable_baddie_push = 0;
	coll->enable_spaz = 0;
	if (!(input & IN_LEFT) || !(input & IN_ACTION) || (input & (IN_UP | IN_DOWN)) || item->hit_points <= 0)
		item->goal_anim_state = STATE_LARA_POLE_IDLE;
	else
		item->pos.y_rot += 256;
}

void lara_col_polestat(struct ITEM_INFO* item, struct COLL_INFO* coll)//16DFC, 16F30
{
	S_Warn("[lara_col_polestat] - Unimplemented!\n");
}

void lara_col_monkey180(struct ITEM_INFO* item, struct COLL_INFO* coll)//16DDC, 16F10
{
	S_Warn("[lara_col_monkey180] - Unimplemented!\n");
}

void lara_as_monkey180(struct ITEM_INFO* item, struct COLL_INFO* coll)//16DB8(<), 16EEC(<) (F)
{
	coll->enable_baddie_push = 0;
	coll->enable_spaz = 0;
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
	if (item->hit_points > 0)
	{
		lara.torso_y_rot = 0;
		lara.torso_x_rot = 0;

		coll->enable_baddie_push = 0;
		coll->enable_spaz = 0;

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
	else
	{
		item->goal_anim_state = STATE_LARA_MONKEYSWING_IDLE;
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
	if (item->hit_points > 0)
	{
		lara.torso_y_rot = 0;
		lara.torso_x_rot = 0;

		coll->enable_baddie_push = 0;
		coll->enable_spaz = 0;

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
	else
	{
		item->goal_anim_state = STATE_LARA_MONKEYSWING_IDLE;
	}
}

void lara_col_monkeyswing(struct ITEM_INFO* item, struct COLL_INFO* coll)//16828, 1695C
{
	S_Warn("[lara_col_monkeyswing] - Unimplemented!\n");
}

void lara_as_monkeyswing(struct ITEM_INFO* item, struct COLL_INFO* coll)//1670C, 16840
{
	S_Warn("[lara_as_monkeyswing] - Unimplemented!\n");
}

void lara_col_hang2(struct ITEM_INFO* item, struct COLL_INFO* coll)//163DC, 16510
{
	S_Warn("[lara_col_hang2] - Unimplemented!\n");
}

void lara_as_hang2(struct ITEM_INFO* item, struct COLL_INFO* coll)//1630C(<), 16440(<) (F)
{
	if (item->hit_points > 0)
	{
		coll->enable_baddie_push = 0;
		coll->enable_spaz = 0;

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
	else
	{
		item->goal_anim_state = STATE_LARA_STOP;
	}
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
	if (ABS(coll->mid_ceiling - coll->front_ceiling) > 50)
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
	if (ABS(coll->mid_ceiling - coll->front_ceiling) > 50)
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
	return ABS(rot) >= ANGLE(45) && ABS(rot) <= ANGLE(135);
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

	lara.gun_status = 0;
}

void lara_col_dashdive(struct ITEM_INFO* item, struct COLL_INFO* coll)//15E5C, 15F90
{
	S_Warn("[lara_col_dashdive] - Unimplemented!\n");
}

void lara_as_dashdive(struct ITEM_INFO* item, struct COLL_INFO* coll)//15E1C(<), 15F50(<) (F)
{
	if (item->goal_anim_state != STATE_LARA_DEATH && 
		item->goal_anim_state != STATE_LARA_STOP && 
		item->goal_anim_state != STATE_LARA_RUN_FORWARD && 
		item->fallspeed > LARA_FREEFALL_SPEED)
		item->goal_anim_state = STATE_LARA_FREEFALL;
}

void lara_col_dash(struct ITEM_INFO* item, struct COLL_INFO* coll)//15C50, 15D84
{
	S_Warn("[lara_col_dash] - Unimplemented!\n");
}

void lara_as_dash(struct ITEM_INFO* item, struct COLL_INFO* coll)//15A28, 15B5C
{
	S_Warn("[lara_as_dash] - Unimplemented!\n");
}

void lara_col_crawl2hang(struct ITEM_INFO* item, struct COLL_INFO* coll)//15770, 158A4
{
	S_Warn("[lara_col_crawl2hang] - Unimplemented!\n");
}

void lara_col_crawlb(struct ITEM_INFO* item, struct COLL_INFO* coll)//15614, 15748
{
	S_Warn("[lara_col_crawlb] - Unimplemented!\n");
}

void lara_as_crawlb(struct ITEM_INFO* item, struct COLL_INFO* coll)//154F0, 15624
{
	S_Warn("[lara_as_crawlb] - Unimplemented!\n");
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

void lara_col_all4turnlr(struct ITEM_INFO* item, struct COLL_INFO* coll)//153FC, 15530
{
	GetCollisionInfo(coll, item->pos.x_pos, item->pos.y_pos, item->pos.z_pos, item->room_number, 400);
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

void lara_col_crawl(struct ITEM_INFO* item, struct COLL_INFO* coll)//1523C, 15370
{
	S_Warn("[lara_col_crawl] - Unimplemented!\n");
}

void lara_as_crawl(struct ITEM_INFO* item, struct COLL_INFO* coll)//150F4, 15228
{
	S_Warn("[lara_as_crawl] - Unimplemented!\n");
}

void lara_col_all4s(struct ITEM_INFO* item, struct COLL_INFO* coll)//14B40, 14C74
{
	S_Warn("[lara_col_all4s] - Unimplemented!\n");
}

void lara_as_all4s(struct ITEM_INFO* item, struct COLL_INFO* coll)//14970, 14A78
{
	S_Warn("[lara_as_all4s] - Unimplemented!\n");
}

void lara_col_duck(struct ITEM_INFO* item, struct COLL_INFO* coll)//147C4, 148CC
{
	S_Warn("[lara_col_duck] - Unimplemented!\n");
}

void lara_as_duck(struct ITEM_INFO* item, struct COLL_INFO* coll)//14688, 14738
{
	S_Warn("[lara_as_duck] - Unimplemented!\n");
}

void lara_col_ducklr(struct ITEM_INFO* item, struct COLL_INFO* coll)//14534, 145E4
{
	S_Warn("[lara_col_ducklr] - Unimplemented!\n");
}

void lara_as_duckr(struct ITEM_INFO* item, struct COLL_INFO* coll)//144E0(<), 14590(<) (F)
{
	coll->enable_spaz = 0;
	if ((input & 0x20000004) != 0x20000004 || item->hit_points <= 0)
		item->goal_anim_state = STATE_LARA_CROUCH_IDLE;
	item->pos.y_rot += ANGLE(1.5);
}

void lara_as_duckl(struct ITEM_INFO* item, struct COLL_INFO* coll)//1448C(<), 1453C(<) (F)
{
	coll->enable_spaz = 0;
	if ((input & 0x20000004) != 0x20000004 || item->hit_points <= 0)
		item->goal_anim_state = STATE_LARA_CROUCH_IDLE;
	item->pos.y_rot -= ANGLE(1.5);
}

void LaraAboveWater(struct ITEM_INFO* item, struct COLL_INFO* coll)//14228, 142D8
{
	S_Warn("[LaraAboveWater] - Unimplemented!\n");
}

int TestHangSwingIn(struct ITEM_INFO* item, short angle)//14104, 141B4
{
	S_Warn("[TestHangSwingIn] - Unimplemented!\n");
	return 0;
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

int IsValidHangPos(struct ITEM_INFO* item, struct COLL_INFO* coll)//135BC, 1366C
{
	S_Warn("[IsValidHangPos] - Unimplemented!\n");
	return 0;
}

int LaraHangTest(struct ITEM_INFO* item, struct COLL_INFO* coll)//12F34, 12FE4
{
	S_Warn("[LaraHangTest] - Unimplemented!\n");
	return 0;
}

void SnapLaraToEdgeOfBlock(struct ITEM_INFO* item, struct COLL_INFO* coll, short angle)//12E54, 12F04
{
	S_Warn("[SnapLaraToEdgeOfBlock] - Unimplemented!\n");
}

int LaraTestHangOnClimbWall(struct ITEM_INFO* item, struct COLL_INFO* coll)//12C54, 12D04
{
	S_Warn("[LaraTestHangOnClimbWall] - Unimplemented!\n");
	return 0;
}

void LaraSlideEdgeJump(struct ITEM_INFO* item, struct COLL_INFO* coll)//12B18, 12BC8
{
	S_Warn("[LaraSlideEdgeJump] - Unimplemented!\n");
}

void LaraDeflectEdgeJump(struct ITEM_INFO* item, struct COLL_INFO* coll)//12904, 129B4
{
	S_Warn("[LaraDeflectEdgeJump] - Unimplemented!\n");
}

void lara_slide_slope(struct ITEM_INFO* item, struct COLL_INFO* coll)//127BC, 1286C
{
	S_Warn("[lara_slide_slope] - Unimplemented!\n");
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

int TestWall(struct ITEM_INFO* item, long front, long right, long down)//12550, 12600
{
	S_Warn("[TestWall] - Unimplemented!\n");
	return 0;
}

int TestLaraVault(struct ITEM_INFO* item, struct COLL_INFO* coll)//120C0, 12170
{
	S_Warn("[TestLaraVault] - Unimplemented!\n");
	return 0;
}

int LaraTestClimbStance(struct ITEM_INFO* item, struct COLL_INFO* coll)//11F78, 12028
{
	S_Warn("[LaraTestClimbStance] - Unimplemented!\n");
	return 0;
}

int LaraTestEdgeCatch(struct ITEM_INFO* item, struct COLL_INFO* coll, long* edge)//11E60, 11F10
{
	S_Warn("[LaraTestEdgeCatch] - Unimplemented!\n");
	return 0;
}

int LaraDeflectEdgeDuck(struct ITEM_INFO* item, struct COLL_INFO* coll)//11DC0, 11E70
{
	S_Warn("[LaraDeflectEdgeDuck] - Unimplemented!\n");
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

int LaraHitCeiling(struct ITEM_INFO* item, struct COLL_INFO* coll)//11C94, 11D44
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

		return 1;
	}
	else
	{
		return 0;
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

	return 0;
}

int LaraFallen(struct ITEM_INFO* item, struct COLL_INFO* coll)//11B6C, 11C1C
{
	S_Warn("[LaraFallen] - Unimplemented!\n");
	return 0;
}

int TestLaraSlide(struct ITEM_INFO* item, struct COLL_INFO* coll)//11998, 11A48
{
	S_Warn("[TestLaraSlide] - Unimplemented!\n");
	return 0;
}

short LaraCeilingFront(struct ITEM_INFO* item, short ang, long dist, long h)//1189C, 1194C
{
	S_Warn("[LaraCeilingFront] - Unimplemented!\n");
	return 0;
}

short LaraFloorFront(struct ITEM_INFO* item, short ang, long dist)//117B0, 11860
{
	S_Warn("[LaraFloorFront] - Unimplemented!\n");
	return 0;
}

void GetLaraCollisionInfo(struct ITEM_INFO* item, struct COLL_INFO* coll)//11764(<), 11814(<) (F)
{
	coll->facing = lara.move_angle;
	GetCollisionInfo(coll, item->pos.x_pos, item->pos.y_pos, item->pos.z_pos, item->room_number, 762);
}

int GetLaraJointPos(struct PHD_VECTOR* arg1, int arg2)
{
	S_Warn("[GetLaraJointPos] - Unimplemented!\n");
	return 0;
}

void AnimateLara(struct ITEM_INFO* item)
{
	S_Warn("[AnimateLara] - Unimplemented!\n");
}

void SetLaraUnderwaterNodes()
{
	S_Warn("[SetLaraUnderwaterNodes] - Unimplemented!\n");
}