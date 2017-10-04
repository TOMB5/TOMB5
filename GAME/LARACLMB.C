#include "LARACLMB.H"

#include "CAMERA.H"
#include "CONTROL.H"
#include "LARA.H"
#include INPUT_H
#include "SPECIFIC.H"

static short LeftIntRightExtTab[4] = // offset 0xA0B7C
{
	0x0800, 0x0100, 0x0200, 0x0400
};
static short LeftExtRightIntTab[4] = // offset 0xA0B84
{
	0x0200, 0x0400, 0x0800, 0x0100
};

short GetClimbTrigger(long x, long y, long z, short room_number)//46E38, 4729C
{
	S_Warn("[GetClimbTrigger] - Unimplemented!\n");
	return 0;
}

void lara_col_climbend(struct ITEM_INFO* item, struct COLL_INFO* coll)//46E30(<), 47294(<) (F)
{
	return;
}

void lara_as_climbend(struct ITEM_INFO* item, struct COLL_INFO* coll)//46DF8(<), 4725C(<) (F)
{
	coll->enable_baddie_push = 0;
	coll->enable_spaz = 0;
	camera.flags = 1;
	camera.target_angle = ANGLE(-45);
}

void lara_col_climbdown(struct ITEM_INFO* item, struct COLL_INFO* coll)//46BD0, 47034
{
	S_Warn("[lara_col_climbdown] - Unimplemented!\n");
}

void lara_as_climbdown(struct ITEM_INFO* item, struct COLL_INFO* coll)//46BA4(<), 47008(<) (F)
{
	coll->enable_baddie_push = 0;
	coll->enable_spaz = 0;
	camera.target_elevation = ANGLE(-45);
}

void lara_col_climbing(struct ITEM_INFO* item, struct COLL_INFO* coll)//469B0, 46E14
{
	S_Warn("[lara_col_climbing] - Unimplemented!\n");
}

void lara_as_climbing(struct ITEM_INFO* item, struct COLL_INFO* coll)//46984(<), 46DE8(<) (F)
{
	coll->enable_baddie_push = 0;
	coll->enable_spaz = 0;
	camera.target_elevation = ANGLE(30);
}

void lara_col_climbright(struct ITEM_INFO* item, struct COLL_INFO* coll)//46908(<), 46D6C(<) (F)
{
	S_Warn("[lara_col_climbright] - Unimplemented!\n");
	return;

#if 0
	// DAMN IT why is this casting pointers to int and then treating the ints as pos vectors fml
	// todo someone needs to decompile this (at least the functions calls)
	// they seem wrong af both on psx mips and pc asm / pseudocode
	int shift;
	if (!LaraCheckForLetGo(item, coll))
	{
		lara.move_angle = item->pos.y_rot + (90 * TRDEGREE);
		//LaraDoClimbLeftRight(item, coll, 
			//LaraTestClimbPos(item, coll->radius, coll->radius + 120, -512, 512, (int *)coll), shift); // todo it may be wrong af
	}
#endif
}

void lara_as_climbright(struct ITEM_INFO* item, struct COLL_INFO* coll)//468B8(<), 46D1C(<) (F)
{
	coll->enable_baddie_push = 0;
	coll->enable_spaz = 0;
	camera.target_angle = ANGLE(30);
	camera.target_elevation = ANGLE(-15);
	if (!(input & (IN_RIGHT | IN_RSTEP)))
		item->goal_anim_state = STATE_LARA_LADDER_IDLE;
}

void lara_col_climbleft(struct ITEM_INFO* item, struct COLL_INFO* coll)//46834(<), 46C98(<) (F)
{
	if (!LaraCheckForLetGo(item, coll))
	{
		lara.move_angle = item->pos.y_rot - ANGLE(90);
		//LaraDoClimbLeftRight(item, coll,
			//LaraTestClimbPos(item, coll->radius, -(coll->radius + 120), -512, 512, (int *)&coll), (int)coll); // todo it may be wrong af
	}
}

void lara_as_climbleft(struct ITEM_INFO* item, struct COLL_INFO* coll)//467E4(<), 46C48(<) (F)
{
	coll->enable_baddie_push = 0;
	coll->enable_spaz = 0;
	camera.target_angle = ANGLE(-30);
	camera.target_elevation = ANGLE(-15);
	if (!(input & (IN_LEFT | IN_LSTEP)))
		item->goal_anim_state = STATE_LARA_LADDER_IDLE;
}

void lara_col_climbstnc(struct ITEM_INFO* item, struct COLL_INFO* coll)//464E8, 4694C
{
	S_Warn("[lara_col_climbstnc] - Unimplemented!\n");
}

void lara_as_climbstnc(struct ITEM_INFO* item, struct COLL_INFO* coll)//463F0, 46854
{
	S_Warn("[lara_as_climbstnc] - Unimplemented!\n");
}

int LaraTestClimbPos(struct ITEM_INFO* item, int front, int right, int origin, int height, int* shift)//462F8, 4675C
{
	S_Warn("[LaraTestClimbPos] - Unimplemented!\n");
	return 0;
}

void LaraDoClimbLeftRight(struct ITEM_INFO* item, struct COLL_INFO* coll, int result, int shift)//46100, 46564
{
	S_Warn("[LaraDoClimbLeftRight] - Unimplemented!\n");
}

int LaraClimbRightCornerTest(struct ITEM_INFO* item, struct COLL_INFO* coll)//45DE4, 46248
{
	S_Warn("[LaraClimbRightCornerTest] - Unimplemented!\n");
	return 0;
}

int LaraClimbLeftCornerTest(struct ITEM_INFO* item, struct COLL_INFO* coll)//45ABC, 45F20
{
	S_Warn("[LaraClimbLeftCornerTest] - Unimplemented!\n");
	return 0;
}

int LaraTestClimb(int x, int y, int z, int xfront, int zfront, int item_height, int item_room, int* shift)//457F0, 45C54
{
	S_Warn("[LaraTestClimb] - Unimplemented!\n");
	return 0;
}

int LaraTestClimbUpPos(struct ITEM_INFO* item, int front, int right, int* shift, int* ledge)//45530, 45994
{
	S_Warn("[LaraTestClimbUpPos] - Unimplemented!\n");
	return 0;
}

long LaraCheckForLetGo(struct ITEM_INFO* item, struct COLL_INFO* coll)//45434, 45898
{
	S_Warn("[LaraCheckForLetGo] - Unimplemented!\n");
	return 0;
}