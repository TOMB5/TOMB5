#include "LARA.H"

#include "SPECIFIC.H"
#include "PSXINPUT.H"

static short LeftClimbTab[4] = // offset 0xA0638
{
	0x0200, 0x0002, 0x0400, 0x0004
};

static short RightClimbTab[4] = // offset 0xA0640
{
	0x0800, 0x0008, 0x0100, 0x0001
};

short angle; // offset 0xA0650
short elevation; // offset 0xA0652
struct ITEM_INFO* lara_item; // offset 0xA2048
unsigned short DashTimer; // offset 0xA2044
struct lara_info lara; // offset 0xA57DC

void lara_as_pbleapoff(struct ITEM_INFO *item, struct COLL_INFO *coll)//1D244, 1D3D8
{
	S_Warn("[lara_as_pbleapoff] - Unimplemented!\n");
}

void lara_as_parallelbars(struct ITEM_INFO *item, struct COLL_INFO *coll)//1D220(<), 1D3B4(<) (F)
{
	if((input & 0x40) == 0)
	{
		item->goal_anim_state = 0x81;
	}
}

void lara_as_trfall(struct ITEM_INFO *item, struct COLL_INFO *coll)//1D03C, 1D1D0
{
	S_Warn("[lara_as_trfall] - Unimplemented!\n");
}

void lara_as_trwalk(struct ITEM_INFO *item, struct COLL_INFO *coll)//1CEDC, 1D070
{
	S_Warn("[lara_as_trwalk] - Unimplemented!\n");
}

void lara_as_trpose(struct ITEM_INFO *item, struct COLL_INFO *coll)//1CDE8, 1CF7C
{
	S_Warn("[lara_as_trpose] - Unimplemented!\n");
}

void GetTighRopeFallOff(long Regularity)//1CD28, 1CEBC
{
	S_Warn("[GetTighRopeFallOff] - Unimplemented!\n");
}

void LookLeftRight()//1CB80, 1CD14
{
	S_Warn("[LookLeftRight] - Unimplemented!\n");
}

void LookUpDown()//1C9D8, 1CB6C
{
	S_Warn("[LookUpDown] - Unimplemented!\n");
}

void ResetLook()//1C920, 1CA54
{
	S_Warn("[ResetLook] - Unimplemented!\n");
}

void lara_col_jumper(struct ITEM_INFO *item, struct COLL_INFO *coll)//1C860, 1C994
{
	S_Warn("[lara_col_jumper] - Unimplemented!\n");
}

void lara_default_col(struct ITEM_INFO *item, struct COLL_INFO *coll)//1C80C, 1C940
{
	S_Warn("[lara_default_col] - Unimplemented!\n");
}

void lara_col_wade(struct ITEM_INFO *item, struct COLL_INFO *coll)//1C61C, 1C750
{
	S_Warn("[lara_col_wade] - Unimplemented!\n");
}

void lara_col_fastdive(struct ITEM_INFO *item, struct COLL_INFO *coll)//1C558, 1C68C
{
	S_Warn("[lara_col_fastdive] - Unimplemented!\n");
}

void lara_col_swandive(struct ITEM_INFO *item, struct COLL_INFO *coll)//1C4A0, 1C5D4
{
	S_Warn("[lara_col_swandive] - Unimplemented!\n");
}

void lara_col_roll2(struct ITEM_INFO *item, struct COLL_INFO *coll)//1C384, 1C4B8
{
	S_Warn("[lara_col_roll2] - Unimplemented!\n");
}

void lara_col_roll(struct ITEM_INFO *item, struct COLL_INFO *coll)//1C2B0, 1C3E4
{
	S_Warn("[lara_col_roll] - Unimplemented!\n");
}

void lara_col_slideback(struct ITEM_INFO *item, struct COLL_INFO *coll)//1C284, 1C3B8
{
	S_Warn("[lara_col_slideback] - Unimplemented!\n");
}

void lara_col_fallback(struct ITEM_INFO *item, struct COLL_INFO *coll)//1C1B4, 1C2E8
{
	S_Warn("[lara_col_fallback] - Unimplemented!\n");
}

void lara_col_leftjump(struct ITEM_INFO *item, struct COLL_INFO *coll)//1C188, 1C2BC
{
	S_Warn("[lara_col_leftjump] - Unimplemented!\n");
}

void lara_col_rightjump(struct ITEM_INFO *item, struct COLL_INFO *coll)//1C15C, 1C290
{
	S_Warn("[lara_col_rightjump] - Unimplemented!\n");
}

void lara_col_backjump(struct ITEM_INFO *item, struct COLL_INFO *coll)//1C130, 1C264
{
	S_Warn("[lara_col_backjump] - Unimplemented!\n");
}

void lara_col_slide(struct ITEM_INFO *item, struct COLL_INFO *coll)//1C108(<), 1C23C(<) (F)
{
	lara.move_angle = item->pos.y_rot;
	lara_slide_slope(item, coll);
	return;
}

void lara_col_stepleft(struct ITEM_INFO *item, struct COLL_INFO *coll)//1C0E8, 1C21C
{
	S_Warn("[lara_col_stepleft] - Unimplemented!\n");
}

void lara_col_stepright(struct ITEM_INFO *item, struct COLL_INFO *coll)//1BFB0, 1C0E4
{
	S_Warn("[lara_col_stepright] - Unimplemented!\n");
}

void lara_col_back(struct ITEM_INFO *item, struct COLL_INFO *coll)//1BE38, 1BF6C
{
	S_Warn("[lara_col_back] - Unimplemented!\n");
}

void lara_col_compress(struct ITEM_INFO *item, struct COLL_INFO *coll)//1BD30, 1BE64
{
	S_Warn("[lara_col_compress] - Unimplemented!\n");
}

void lara_col_land(struct ITEM_INFO *item, struct COLL_INFO *coll)//1BD10, 1BE44
{
	S_Warn("[lara_col_land] - Unimplemented!\n");
}

void lara_col_splat(struct ITEM_INFO *item, struct COLL_INFO *coll)//1BC74, 1BDA8
{
	S_Warn("[lara_col_splat] - Unimplemented!\n");
}

void lara_col_fastfall(struct ITEM_INFO *item, struct COLL_INFO *coll)//1BB88, 1BCBC
{
	S_Warn("[lara_col_fastfall] - Unimplemented!\n");
}

void lara_col_death(struct ITEM_INFO *item, struct COLL_INFO *coll)//1BADC, 1BC10
{
	S_Warn("[lara_col_death] - Unimplemented!\n");
}

void lara_col_turn_l(struct ITEM_INFO *item, struct COLL_INFO *coll)//1BABC, 1BBF0
{
	S_Warn("[lara_col_turn_l] - Unimplemented!\n");
}

void lara_col_turn_r(struct ITEM_INFO *item, struct COLL_INFO *coll)//1B9C4, 1BAF8
{
	S_Warn("[lara_col_turn_r] - Unimplemented!\n");
}

void lara_col_fastback(struct ITEM_INFO *item, struct COLL_INFO *coll)//1B89C, 1B9D0
{
	S_Warn("[lara_col_fastback] - Unimplemented!\n");
}

void lara_col_pose(struct ITEM_INFO *item, struct COLL_INFO *coll)//1B87C, 1B9B0
{
	S_Warn("[lara_col_pose] - Unimplemented!\n");
}

void lara_col_run(struct ITEM_INFO *item, struct COLL_INFO *coll)//1B64C, 1B780
{
	S_Warn("[lara_col_run] - Unimplemented!\n");
}

void lara_col_walk(struct ITEM_INFO *item, struct COLL_INFO *coll)//1B3E8, 1B51C
{
	S_Warn("[lara_col_walk] - Unimplemented!\n");
}

void lara_as_pulley(struct ITEM_INFO *item, struct COLL_INFO *coll)//1B288, 1B3BC
{
	S_Warn("[lara_as_pulley] - Unimplemented!\n");
}

void lara_col_turnswitch(struct ITEM_INFO *item, struct COLL_INFO *coll)//1B1B4, 1B2E8
{
	S_Warn("[lara_col_turnswitch] - Unimplemented!\n");
}

void lara_as_controlledl(struct ITEM_INFO *item, struct COLL_INFO *coll)//1B180, 1B2B4
{
	S_Warn("[lara_as_controlledl] - Unimplemented!\n");
}

void lara_as_controlled(struct ITEM_INFO *item, struct COLL_INFO *coll)//1B0FC, 1B230
{
	S_Warn("[lara_as_controlled] - Unimplemented!\n");
}

void lara_as_deathslide(struct ITEM_INFO *item, struct COLL_INFO *coll)//1B038, 1B16C
{
	S_Warn("[lara_as_deathslide] - Unimplemented!\n");
}

void lara_as_wade(struct ITEM_INFO *item, struct COLL_INFO *coll)//1AF10, 1B044
{
	S_Warn("[lara_as_wade] - Unimplemented!\n");
}

void lara_as_waterout(struct ITEM_INFO *item, struct COLL_INFO *coll)//1AEE4, 1B018
{
	S_Warn("[lara_as_waterout] - Unimplemented!\n");
}

void lara_as_gymnast(struct ITEM_INFO *item, struct COLL_INFO *coll)//1AEC8(<), 1AFFC(<) (F)
{
	item->hit_status = 0;
	item->collidable = 0;
}

void lara_as_fastdive(struct ITEM_INFO *item, struct COLL_INFO *coll)//1AE4C, 1AF80
{
	S_Warn("[lara_as_fastdive] - Unimplemented!\n");
}

void lara_as_swandive(struct ITEM_INFO *item, struct COLL_INFO *coll)//1AE08, 1AF3C
{
	S_Warn("[lara_as_swandive] - Unimplemented!\n");
}

void lara_as_special(struct ITEM_INFO *item, struct COLL_INFO *coll)//1ADDC, 1AF10
{
	S_Warn("[lara_as_special] - Unimplemented!\n");
}

void lara_as_usepuzzle(struct ITEM_INFO *item, struct COLL_INFO *coll)//1AD18, 1AE4C
{
	S_Warn("[lara_as_usepuzzle] - Unimplemented!\n");
}

void lara_as_usekey(struct ITEM_INFO *item, struct COLL_INFO *coll)//1ACBC, 1ADF0
{
	S_Warn("[lara_as_usekey] - Unimplemented!\n");
}

void lara_as_switchoff(struct ITEM_INFO *item, struct COLL_INFO *coll)//1AC54, 1AD88
{
	S_Warn("[lara_as_switchoff] - Unimplemented!\n");
}

void lara_as_switchon(struct ITEM_INFO *item, struct COLL_INFO *coll)//1ABEC, 1AD20
{
	S_Warn("[lara_as_switchon] - Unimplemented!\n");
}

void lara_as_pickupflare(struct ITEM_INFO *item, struct COLL_INFO *coll)//1AB5C, 1AC90
{
	S_Warn("[lara_as_pickupflare] - Unimplemented!\n");
}

void lara_as_pickup(struct ITEM_INFO *item, struct COLL_INFO *coll)//1AB00, 1AC34
{
	S_Warn("[lara_as_pickup] - Unimplemented!\n");
}

void lara_as_ppready(struct ITEM_INFO *item, struct COLL_INFO *coll)//1AABC, 1ABF0
{
	S_Warn("[lara_as_ppready] - Unimplemented!\n");
}

void lara_as_pullblock(struct ITEM_INFO *item, struct COLL_INFO *coll)//1AA60, 1AB94
{
	S_Warn("[lara_as_pullblock] - Unimplemented!\n");
}

void lara_as_pushblock(struct ITEM_INFO *item, struct COLL_INFO *coll)//1AA04, 1AB38
{
	S_Warn("[lara_as_pushblock] - Unimplemented!\n");
}

void lara_as_slideback(struct ITEM_INFO *item, struct COLL_INFO *coll)//1A9E0(<), 1AB14(<) (F)
{
	if((input & 0x11) == 0x10)
	{
		item->goal_anim_state = 0x19;
	}
}

void lara_as_fallback(struct ITEM_INFO *item, struct COLL_INFO *coll)//1959C, 196D0
{
	S_Warn("[lara_as_fallback] - Unimplemented!\n");
}

void lara_as_leftjump(struct ITEM_INFO *item, struct COLL_INFO *coll)//1A92C, 1AA60
{
	S_Warn("[lara_as_leftjump] - Unimplemented!\n");
}

void lara_as_rightjump(struct ITEM_INFO *item, struct COLL_INFO *coll)//1A8C4, 1A9F8
{
	S_Warn("[lara_as_rightjump] - Unimplemented!\n");
}

void lara_as_backjump(struct ITEM_INFO *item, struct COLL_INFO *coll)//1A854, 1A988
{
	S_Warn("[lara_as_backjump] - Unimplemented!\n");
}

void lara_as_slide(struct ITEM_INFO *item, struct COLL_INFO *coll)//1A824, 1A958
{
	S_Warn("[lara_as_slide] - Unimplemented!\n");
}

void lara_as_stepleft(struct ITEM_INFO *item, struct COLL_INFO *coll)//1A750, 1A884
{
	S_Warn("[lara_as_stepleft] - Unimplemented!\n");
}

void lara_as_stepright(struct ITEM_INFO *item, struct COLL_INFO *coll)//1A67C, 1A7B0
{
	S_Warn("[lara_as_stepright] - Unimplemented!\n");
}

void lara_col_fastturn(struct ITEM_INFO *item, struct COLL_INFO *coll)//1A65C, 1A790
{
	S_Warn("[lara_col_fastturn] - Unimplemented!\n");
}

void lara_as_fastturn(struct ITEM_INFO *item, struct COLL_INFO *coll)//1A5F8, 1A72C
{
	S_Warn("[lara_as_fastturn] - Unimplemented!\n");
}

void lara_as_null(struct ITEM_INFO *item, struct COLL_INFO *coll)//1A5DC(<), 1A710(<) (F)
{
	coll->enable_baddie_push = 0; // todo maybe it's item instead of coll
	coll->enable_spaz = 0;
	return;
}

void lara_as_back(struct ITEM_INFO *item, struct COLL_INFO *coll)//1A4F0, 1A624
{
	S_Warn("[lara_as_back] - Unimplemented!\n");
}

void lara_as_compress(struct ITEM_INFO *item, struct COLL_INFO *coll)//1A35C, 1A490
{
	S_Warn("[lara_as_compress] - Unimplemented!\n");
}

void lara_as_splat(struct ITEM_INFO *item, struct COLL_INFO *coll)//1A340(<), 1A474(<) (F)
{
	lara.look = 0;
}

void lara_as_intcornerr(struct ITEM_INFO *item, struct COLL_INFO *coll)//1A2EC, 1A420
{
	S_Warn("[lara_as_intcornerr] - Unimplemented!\n");
}

void lara_as_intcornerl(struct ITEM_INFO *item, struct COLL_INFO *coll)//1A298, 1A3CC
{
	S_Warn("[lara_as_intcornerl] - Unimplemented!\n");
}

void lara_as_extcornerr(struct ITEM_INFO *item, struct COLL_INFO *coll)//1A244, 1A378
{
	S_Warn("[lara_as_extcornerr] - Unimplemented!\n");
}

void lara_as_extcornerl(struct ITEM_INFO *item, struct COLL_INFO *coll)//1A1F0, 1A324
{
	S_Warn("[lara_as_extcornerl] - Unimplemented!\n");
}

void SetCornerAnim(struct ITEM_INFO *item, struct COLL_INFO *coll, short rot, short flip)//1A090, 1A1C4
{
	S_Warn("[SetCornerAnim] - Unimplemented!\n");
}

void lara_col_hangright(struct ITEM_INFO *item, struct COLL_INFO *coll)//1A038, 1A16C
{
	S_Warn("[lara_col_hangright] - Unimplemented!\n");
}

void lara_as_hangright(struct ITEM_INFO *item, struct COLL_INFO *coll)//19FEC, 1A120
{
	S_Warn("[lara_as_hangright] - Unimplemented!\n");
}

void lara_col_hangleft(struct ITEM_INFO *item, struct COLL_INFO *coll)//19F94, 1A0C8
{
	S_Warn("[lara_col_hangleft] - Unimplemented!\n");
}

void lara_as_hangleft(struct ITEM_INFO *item, struct COLL_INFO *coll)//19F48, 1A07C
{
	S_Warn("[lara_as_hangleft] - Unimplemented!\n");
}

void lara_col_hang(struct ITEM_INFO *item, struct COLL_INFO *coll)//19AC8, 19BFC
{
	S_Warn("[lara_col_hang] - Unimplemented!\n");
}

void lara_as_hang(struct ITEM_INFO *item, struct COLL_INFO *coll)//19A28, 19B5C
{
	S_Warn("[lara_as_hang] - Unimplemented!\n");
}

int CanLaraHangSideways(struct ITEM_INFO *item, struct COLL_INFO *coll, short angle)//19930, 19A64
{
	S_Warn("[CanLaraHangSideways] - Unimplemented!\n");
	return 0;
}

void lara_void_func(struct ITEM_INFO *item, struct COLL_INFO *coll)//19928(<), 19A5C(<) (F)
{
	return;
}

void lara_as_fastfall(struct ITEM_INFO *item, struct COLL_INFO *coll)//198BC, 199F0
{
	S_Warn("[lara_as_fastfall] - Unimplemented!\n");
}

void lara_as_death(struct ITEM_INFO *item, struct COLL_INFO *coll)//19830, 19964
{
	S_Warn("[lara_as_death] - Unimplemented!\n");
}

void lara_as_turn_l(struct ITEM_INFO *item, struct COLL_INFO *coll)//1972C, 19860
{
	S_Warn("[lara_as_turn_l] - Unimplemented!\n");
}

void lara_as_turn_r(struct ITEM_INFO *item, struct COLL_INFO *coll)//19628, 1975C
{
	S_Warn("[lara_as_turn_r] - Unimplemented!\n");
}

void lara_as_fastback(struct ITEM_INFO *item, struct COLL_INFO *coll)//1959C, 196D0
{
	S_Warn("[lara_as_fastback] - Unimplemented!\n");
}

void lara_as_run(struct ITEM_INFO *item, struct COLL_INFO *coll)//192EC, 19420
{
	S_Warn("[lara_as_run] - Unimplemented!\n");
}

void lara_as_walk(struct ITEM_INFO *item, struct COLL_INFO *coll)//191B8, 192EC
{
	S_Warn("[lara_as_walk] - Unimplemented!\n");
}

void lara_col_reach(struct ITEM_INFO *item, struct COLL_INFO *coll)//18D0C, 18E40
{
	S_Warn("[lara_col_reach] - Unimplemented!\n");
}

void lara_as_reach(struct ITEM_INFO *item, struct COLL_INFO *coll)//18CE0, 18E14
{
	S_Warn("[lara_as_reach] - Unimplemented!\n");
}

void lara_col_forwardjump(struct ITEM_INFO *item, struct COLL_INFO *coll)//18B88, 18CBC
{
	S_Warn("[lara_col_forwardjump] - Unimplemented!\n");
}

void lara_as_forwardjump(struct ITEM_INFO *item, struct COLL_INFO *coll)//18A34, 18B68
{
	S_Warn("[lara_as_forwardjump] - Unimplemented!\n");
}

void lara_col_upjump(struct ITEM_INFO *item, struct COLL_INFO *coll)//1853C, 18670
{
	S_Warn("[lara_col_upjump] - Unimplemented!\n");
}

void lara_as_upjump(struct ITEM_INFO *item, struct COLL_INFO *coll)//1851C(<), 18650(<) (F)
{
	if (item->fallspeed >= 132)
	{
		item->goal_anim_state = 9;
	}
}

void lara_col_stop(struct ITEM_INFO *item, struct COLL_INFO *coll)//18444, 18578
{
	S_Warn("[lara_col_stop] - Unimplemented!\n");
}

void lara_as_stop(struct ITEM_INFO *item, struct COLL_INFO *coll)//17E94, 17FC8
{
	S_Warn("[lara_as_stop] - Unimplemented!\n");
}

void lara_as_climbroped(struct ITEM_INFO *item, struct COLL_INFO *coll)//17E64, 17F98
{
	S_Warn("[lara_as_climbroped] - Unimplemented!\n");
}

void lara_as_climbrope(struct ITEM_INFO *item, struct COLL_INFO *coll)//17D9C, 17ED0
{
	S_Warn("[lara_as_climbrope] - Unimplemented!\n");
}

void lara_col_ropefwd(struct ITEM_INFO *item, struct COLL_INFO *coll)//17B74, 17CA8
{
	S_Warn("[lara_col_ropefwd] - Unimplemented!\n");
}

void lara_as_roper(struct ITEM_INFO *item, struct COLL_INFO *coll)//17B14, 17C48
{
	S_Warn("[lara_as_roper] - Unimplemented!\n");
}

void lara_as_ropel(struct ITEM_INFO *item, struct COLL_INFO *coll)//17AB4, 17BE8
{
	S_Warn("[lara_as_ropel] - Unimplemented!\n");
}

void lara_col_rope(struct ITEM_INFO *item, struct COLL_INFO *coll)//179A8, 17ADC
{
	S_Warn("[lara_col_rope] - Unimplemented!\n");
}

void lara_as_rope(struct ITEM_INFO *item, struct COLL_INFO *coll)//17958, 17A8C
{
	S_Warn("[lara_as_rope] - Unimplemented!\n");
}

void ApplyVelocityToRope(int node, unsigned short angle, unsigned short n)//178E4, 17A18
{
	S_Warn("[ApplyVelocityToRope] - Unimplemented!\n");
}

void UpdateRopeSwing(struct ITEM_INFO *item)//17508, 1763C
{
	S_Warn("[UpdateRopeSwing] - Unimplemented!\n");
}

void JumpOffRope(struct ITEM_INFO *item)//17424, 17558
{
	S_Warn("[JumpOffRope] - Unimplemented!\n");
}

void FallFromRope(struct ITEM_INFO *item)//17394, 174C8
{
	S_Warn("[FallFromRope] - Unimplemented!\n");
}

void lara_col_poledown(struct ITEM_INFO *item, struct COLL_INFO *coll)//171A0, 172D4
{
	S_Warn("[lara_col_poledown] - Unimplemented!\n");
}

void lara_col_poleup(struct ITEM_INFO *item, struct COLL_INFO *coll)//170D8, 1720C
{
	S_Warn("[lara_col_poleup] - Unimplemented!\n");
}

void lara_as_poleright(struct ITEM_INFO *item, struct COLL_INFO *coll)//1707C, 171B0
{
	S_Warn("[lara_as_poleright] - Unimplemented!\n");
}

void lara_as_poleleft(struct ITEM_INFO *item, struct COLL_INFO *coll)//17020, 17154
{
	S_Warn("[lara_as_poleleft] - Unimplemented!\n");
}

void lara_col_polestat(struct ITEM_INFO *item, struct COLL_INFO *coll)//16DFC, 16F30
{
	S_Warn("[lara_col_polestat] - Unimplemented!\n");
}

void lara_col_monkey180(struct ITEM_INFO *item, struct COLL_INFO *coll)//16DDC, 16F10
{
	S_Warn("[lara_col_monkey180] - Unimplemented!\n");
}

void lara_as_monkey180(struct ITEM_INFO *item, struct COLL_INFO *coll)//16DB8, 16EEC
{
	S_Warn("[lara_as_monkey180] - Unimplemented!\n");
}

void lara_as_hangturnr(struct ITEM_INFO *item, struct COLL_INFO *coll)//16D64, 16E98
{
	S_Warn("[lara_as_hangturnr] - Unimplemented!\n");
}

void lara_col_hangturnlr(struct ITEM_INFO *item, struct COLL_INFO *coll)//16C94, 16DC8
{
	S_Warn("[lara_col_hangturnlr] - Unimplemented!\n");
}

void lara_as_hangturnl(struct ITEM_INFO *item, struct COLL_INFO *coll)//16C40, 16D74
{
	S_Warn("[lara_as_hangturnl] - Unimplemented!\n");
}

void lara_col_monkeyr(struct ITEM_INFO *item, struct COLL_INFO *coll)//16B9C, 16CD0
{
	S_Warn("[lara_col_monkeyr] - Unimplemented!\n");
}

void lara_as_monkeyr(struct ITEM_INFO *item, struct COLL_INFO *coll)//16B24, 16C58
{
	S_Warn("[lara_as_monkeyr] - Unimplemented!\n");
}

void lara_col_monkeyl(struct ITEM_INFO *item, struct COLL_INFO *coll)//16A80, 16BB4
{
	S_Warn("[lara_col_monkeyl] - Unimplemented!\n");
}

void lara_as_monkeyl(struct ITEM_INFO *item, struct COLL_INFO *coll)//16A0C, 16B40
{
	S_Warn("[lara_as_monkeyl] - Unimplemented!\n");
}

void lara_col_monkeyswing(struct ITEM_INFO *item, struct COLL_INFO *coll)//16828, 1695C
{
	S_Warn("[lara_col_monkeyswing] - Unimplemented!\n");
}

void lara_as_monkeyswing(struct ITEM_INFO *item, struct COLL_INFO *coll)//1670C, 16840
{
	S_Warn("[lara_as_monkeyswing] - Unimplemented!\n");
}

void lara_col_hang2(struct ITEM_INFO *item, struct COLL_INFO *coll)//163DC, 16510
{
	S_Warn("[lara_col_hang2] - Unimplemented!\n");
}

void lara_as_hang2(struct ITEM_INFO *item, struct COLL_INFO *coll)//1630C, 16440
{
	S_Warn("[lara_as_hang2] - Unimplemented!\n");
}

short TestMonkeyRight(struct ITEM_INFO *item, struct COLL_INFO *coll)//161EC, 16320
{
	S_Warn("[TestMonkeyRight] - Unimplemented!\n");
	return 0;
}

short TestMonkeyLeft(struct ITEM_INFO *item, struct COLL_INFO *coll)//160CC, 16200
{
	S_Warn("[TestMonkeyLeft] - Unimplemented!\n");
	return 0;
}

short GetDirOctant(long rot)//160B4(<), 161E8(<) (F)
{
	return (rot < 0 ? -rot : rot) - 0x2000 < 0x4001; // todo: use ABS
}

void MonkeySwingSnap(struct ITEM_INFO *item, struct COLL_INFO *coll)//1605C, 16190
{
	S_Warn("[MonkeySwingSnap] - Unimplemented!\n");
}

void MonkeySwingFall(struct ITEM_INFO *item)//16004, 16138
{
	S_Warn("[MonkeySwingFall] - Unimplemented!\n");
}

void lara_col_dashdive(struct ITEM_INFO *item, struct COLL_INFO *coll)//15E5C, 15F90
{
	S_Warn("[lara_col_dashdive] - Unimplemented!\n");
}

void lara_as_dashdive(struct ITEM_INFO *item, struct COLL_INFO *coll)//15E1C, 15F50
{
	S_Warn("[lara_as_dashdive] - Unimplemented!\n");
}

void lara_col_dash(struct ITEM_INFO *item, struct COLL_INFO *coll)//15C50, 15D84
{
	S_Warn("[lara_col_dash] - Unimplemented!\n");
}

void lara_as_dash(struct ITEM_INFO *item, struct COLL_INFO *coll)//15A28, 15B5C
{
	S_Warn("[lara_as_dash] - Unimplemented!\n");
}

void lara_col_crawl2hang(struct ITEM_INFO *item, struct COLL_INFO *coll)//15770, 158A4
{
	S_Warn("[lara_col_crawl2hang] - Unimplemented!\n");
}

void lara_col_crawlb(struct ITEM_INFO *item, struct COLL_INFO *coll)//15614, 15748
{
	S_Warn("[lara_col_crawlb] - Unimplemented!\n");
}

void lara_as_crawlb(struct ITEM_INFO *item, struct COLL_INFO *coll)//154F0, 15624
{
	S_Warn("[lara_as_crawlb] - Unimplemented!\n");
}

void lara_as_all4turnr(struct ITEM_INFO *item, struct COLL_INFO *coll)//15484, 155B8
{
	S_Warn("[lara_as_all4turnr] - Unimplemented!\n");
}

void lara_col_all4turnlr(struct ITEM_INFO *item, struct COLL_INFO *coll)//153FC, 15530
{
	S_Warn("[lara_col_all4turnlr] - Unimplemented!\n");
}

void lara_as_all4turnl(struct ITEM_INFO *item, struct COLL_INFO *coll)//15390, 154C4
{
	S_Warn("[lara_as_all4turnl] - Unimplemented!\n");
}

void lara_col_crawl(struct ITEM_INFO *item, struct COLL_INFO *coll)//1523C, 15370
{
	S_Warn("[lara_col_crawl] - Unimplemented!\n");
}

void lara_as_crawl(struct ITEM_INFO *item, struct COLL_INFO *coll)//150F4, 15228
{
	S_Warn("[lara_as_crawl] - Unimplemented!\n");
}

void lara_col_all4s(struct ITEM_INFO *item, struct COLL_INFO *coll)//14B40, 14C74
{
	S_Warn("[lara_col_all4s] - Unimplemented!\n");
}

void lara_as_all4s(struct ITEM_INFO *item, struct COLL_INFO *coll)//14970, 14A78
{
	S_Warn("[lara_as_all4s] - Unimplemented!\n");
}

void lara_col_duck(struct ITEM_INFO *item, struct COLL_INFO *coll)//147C4, 148CC
{
	S_Warn("[lara_col_duck] - Unimplemented!\n");
}

void lara_as_duck(struct ITEM_INFO *item, struct COLL_INFO *coll)//14688, 14738
{
	S_Warn("[lara_as_duck] - Unimplemented!\n");
}

void lara_col_ducklr(struct ITEM_INFO *item, struct COLL_INFO *coll)//14534, 145E4
{
	S_Warn("[lara_col_ducklr] - Unimplemented!\n");
}

void lara_as_duckr(struct ITEM_INFO *item, struct COLL_INFO *coll)//144E0, 14590
{
	S_Warn("[lara_as_duckr] - Unimplemented!\n");
}

void lara_as_duckl(struct ITEM_INFO *item, struct COLL_INFO *coll)//1448C, 1453C
{
	S_Warn("[lara_as_duckl] - Unimplemented!\n");
}

void LaraAboveWater(struct ITEM_INFO *item, struct COLL_INFO *coll)//14228, 142D8
{
	S_Warn("[LaraAboveWater] - Unimplemented!\n");
}

int TestHangSwingIn(struct ITEM_INFO *item, short angle)//14104, 141B4
{
	S_Warn("[TestHangSwingIn] - Unimplemented!\n");
	return 0;
}

int LaraHangLeftCornerTest(struct ITEM_INFO *item, struct COLL_INFO *coll)//13C24, 13CD4
{
	S_Warn("[LaraHangLeftCornerTest] - Unimplemented!\n");
	return 0;
}

int LaraHangRightCornerTest(struct ITEM_INFO *item, struct COLL_INFO *coll)//13738, 137E8
{
	S_Warn("[LaraHangRightCornerTest] - Unimplemented!\n");
	return 0;
}

int IsValidHangPos(struct ITEM_INFO *item, struct COLL_INFO *coll)//135BC, 1366C
{
	S_Warn("[IsValidHangPos] - Unimplemented!\n");
	return 0;
}

int LaraHangTest(struct ITEM_INFO *item, struct COLL_INFO *coll)//12F34, 12FE4
{
	S_Warn("[LaraHangTest] - Unimplemented!\n");
	return 0;
}

void SnapLaraToEdgeOfBlock(struct ITEM_INFO *item, struct COLL_INFO *coll, short angle)//12E54, 12F04
{
	S_Warn("[SnapLaraToEdgeOfBlock] - Unimplemented!\n");
}

int LaraTestHangOnClimbWall(struct ITEM_INFO *item, struct COLL_INFO *coll)//12C54, 12D04
{
	S_Warn("[LaraTestHangOnClimbWall] - Unimplemented!\n");
	return 0;
}

void LaraSlideEdgeJump(struct ITEM_INFO *item, struct COLL_INFO *coll)//12B18, 12BC8
{
	S_Warn("[LaraSlideEdgeJump] - Unimplemented!\n");
}

void LaraDeflectEdgeJump(struct ITEM_INFO *item, struct COLL_INFO *coll)//12904, 129B4
{
	S_Warn("[LaraDeflectEdgeJump] - Unimplemented!\n");
}

void lara_slide_slope(struct ITEM_INFO *item, struct COLL_INFO *coll)//127BC, 1286C
{
	S_Warn("[lara_slide_slope] - Unimplemented!\n");
}

void LaraCollideStop(struct ITEM_INFO *item, struct COLL_INFO *coll)//126F0, 127A0
{
	S_Warn("[LaraCollideStop] - Unimplemented!\n");
}

int TestWall(struct ITEM_INFO *item, long front, long right, long down)//12550, 12600
{
	S_Warn("[TestWall] - Unimplemented!\n");
	return 0;
}

int TestLaraVault(struct ITEM_INFO *item, struct COLL_INFO *coll)//120C0, 12170
{
	S_Warn("[TestLaraVault] - Unimplemented!\n");
	return 0;
}

int LaraTestClimbStance(struct ITEM_INFO *item, struct COLL_INFO *coll)//11F78, 12028
{
	S_Warn("[LaraTestClimbStance] - Unimplemented!\n");
	return 0;
}

int LaraTestEdgeCatch(struct ITEM_INFO *item, struct COLL_INFO *coll, long *edge)//11E60, 11F10
{
	S_Warn("[LaraTestEdgeCatch] - Unimplemented!\n");
	return 0;
}

int LaraDeflectEdgeDuck(struct ITEM_INFO *item, struct COLL_INFO *coll)//11DC0, 11E70
{
	S_Warn("[LaraDeflectEdgeDuck] - Unimplemented!\n");
	return 0;
}

int LaraDeflectEdge(struct ITEM_INFO *item, struct COLL_INFO *coll)//11D18, 11DC8
{
	S_Warn("[LaraDeflectEdge] - Unimplemented!\n");
	return 0;
}

int LaraHitCeiling(struct ITEM_INFO *item, struct COLL_INFO *coll)//11C94, 11D44
{
	S_Warn("[LaraHitCeiling] - Unimplemented!\n");
	return 0;
}

int LaraLandedBad(struct ITEM_INFO *l, struct COLL_INFO *coll)//11BD8, 11C88
{
	S_Warn("[LaraLandedBad] - Unimplemented!\n");
	return 0;
}

int LaraFallen(struct ITEM_INFO *item, struct COLL_INFO *coll)//11B6C, 11C1C
{
	S_Warn("[LaraFallen] - Unimplemented!\n");
	return 0;
}

int TestLaraSlide(struct ITEM_INFO *item, struct COLL_INFO *coll)//11998, 11A48
{
	S_Warn("[TestLaraSlide] - Unimplemented!\n");
	return 0;
}

short LaraCeilingFront(struct ITEM_INFO *item, short ang, long dist, long h)//1189C, 1194C
{
	S_Warn("[LaraCeilingFront] - Unimplemented!\n");
	return 0;
}

short LaraFloorFront(struct ITEM_INFO *item, short ang, long dist)//117B0, 11860
{
	S_Warn("[LaraFloorFront] - Unimplemented!\n");
	return 0;
}

void GetLaraCollisionInfo(struct ITEM_INFO *item, struct COLL_INFO *coll)//11764, 11814
{
	S_Warn("[GetLaraCollisionInfo] - Unimplemented!\n");
}