#include "LARAMISC.H"

#include "SPECIFIC.H"
#include "LARA.H"
#if PSX_VERSION || PSXPC_VERSION
#include "CALCLARA.H"
#include "MATHS.H"
#include "FXTRIG.H"
#include "LARASURF.H"
#include "GETSTUFF.H"
#include "COLLIDE.H"
#endif
#include "CONTROL.H"
#include "DRAW.H"
#include "EFFECT2.H"
#include "LARASWIM.H"

#ifdef PC_VERSION
#include "GAME.H"
#else
#include "SETUP.H"
#endif

#include INPUT_H
#include "OBJECTS.H"
#include "GAMEFLOW.H"
#include "HEALTH.H"
#include "NEWINV2.H"
#include "LARAFIRE.H"
#include "SPOTCAM.H"
#if !SAT_VERSION
#include <string.h>
#endif

#include <STDIO.H>

#if DEBUG_VERSION
char* states[131] =
{
	"WALK", "RUN", "STOP", "F JUMP", "POSE", "FASTBACK", "TURN R", "TURN L", "DEATH", 
	"FASTFALL", "HANG", "REACH", "SPLAT", "TREAD", "LAND", "COMPRESS", "BACK", "SWIM", 
	"GLIDE", "NULL", "FAST TURN", "STEP RIGHT", "STEP LEFT", "ROLL2", "SLIDE", "BJUMP", 
	"RJUMP", "LJUMP", "UP JUMP", "FALL BACK", "HANG LEFT", "HANG RIGHT", "SLIDE BACK", 
	"SURF TREAD", "SURF SWIM", "DIVE", "PUSHBLOCK", "PULLBLOCK", "PPREADY", "PICKUP", 
	"SWITCHON", "SWITCHOFF", "USE-KEY", "USE-PUZZLE", "UW_DEATH", "ROLL", "SPECIAL", 
	"SURFBACK", "SURFLEFT", "SURFRIGHT", "USE MIDAS", "DIE MIDAS", "SWANDIVE", "FASTDIVE", 
	"GYMNAST", "WATER OUT", "CLIMB STANCE", "CLIMBING", "CLIMB LEFT", "CLIMB END", 
	"CLIMB RIGHT", "CLIMB DOWN", "LARATEST1", "LARATEST2", "LARATEST3", "WADE", 
	"WATER-ROLL", "PICKUP FLARE", "TWIST", "KICK", "DEATHSLIDE", "DUCK", "DUCKROLL", 
	"DASH", "DASHDIVE", "HANG2", "MONKEYSWING", "MONKEYL", "MONKEYR", "MONKEY180", "ALL4S", 
	"CRAWL", "HANGTURNL", "HANGTURNR", "ALL4TURNL", "ALL4TURNR", "CRAWLBACK", "HANG2DUCK", 
	"CRAWL2HANG", "CONTROLLED", "CROWBAR", "?", "BLOCKSWITCH", "LIFT TRAPDOOR", 
	"PULL TRAPDOOR", "TURN SWITCH", "COG SWITCH", "RAIL SWITCH", "HIDDEN PICKUP", "ON POLE", 
	"POLE UP", "POLE DOWN", "POLE LEFT", "POLE RIGHT", "PULLEY", "DUCKROTL", "DUCKROTR", 
	"CORNEREXTL", "CORNEREXTR", "CORNERINTL", "CORNERINTR", "ON ROPE", "UP ROPE", "DOWN ROPE", 
	"SWING FWD", "SWING BACK", "116", "OPEN DOUBLE DOORS", "SWIMCHEAT", "TROPEPOSE", 
	"TROPETURN", "TROPEWALK", "TROPEFALL_L", "TROPEFALL_R", "TROPEGETON", "TROPEGETOFF", 
	"CROWDOVE", "TROPEUNDOFALL", "PBARS_SPIN", "PBARS_LEAPOFF", "LAST"
};

char* quadrant_names[4] =
{
	"NORTH", "EAST", "SOUTH", "WEST"
};

char* gunstates[6] =
{
	"ARMLESS", "HANDSBUSY", "DRAW", "UNDRAW", "READY", "SPECIAL"
};

char* waterstates[5] =
{
	"ABOVEWATER", "UNDERWATER", "SURFACE", "CHEAT", "WADE"
};

char* guntypes[9] =
{
	"UNARMED", "PISTOLS", "MAGNUMS", "UZIS", "SHOTGUN", "M16", "ROCKET", "HARPOON", "FLARE"
};

char* coll_typess[8] =
{
	"NONE", "FRONT", "LEFT", "RIGHT", "TOP", "TOPBOTTOM", "TOPFRONT", "CLAMP"
};

char* htypes[4] =
{
	"WALL", "SMALL_SLOPE", "BIG_SLOPE", "DIAGONAL"
};
#endif

static struct COLL_INFO *coll = &mycoll; // offset 0xA0B8C
short SubsuitAir = 0; // offset 0xA122E
struct COLL_INFO mycoll;
short cheat_hit_points; // offset 0xA3828

void GetLaraDeadlyBounds()//4B408(<), 4B86C (F)
{
#if PSX_VERSION || PSXPC_VERSION///@TODO PC subs not there yet.
	short* bounds;
	short tbounds[6];

	bounds = GetBoundsAccurate(lara_item);
	mPushUnitMatrix();
	mRotYXZ(lara_item->pos.y_rot, lara_item->pos.x_rot, lara_item->pos.z_rot);
	mSetTrans(0, 0, 0);
	mRotBoundingBoxNoPersp(bounds, &tbounds[0]);
	mPopMatrix();

	DeadlyBounds[0] = lara_item->pos.x_pos + tbounds[0];
	DeadlyBounds[1] = lara_item->pos.x_pos + tbounds[1];
	DeadlyBounds[2] = lara_item->pos.y_pos + tbounds[2];
	DeadlyBounds[3] = lara_item->pos.y_pos + tbounds[3];
	DeadlyBounds[4] = lara_item->pos.z_pos + tbounds[4];
	DeadlyBounds[5] = lara_item->pos.z_pos + tbounds[5];
#else
	UNIMPLEMENTED();
#endif
}

void DelAlignLaraToRope(struct ITEM_INFO* item)//4B3D8, 4B83C
{
	UNIMPLEMENTED();
}

void InitialiseLaraAnims(struct ITEM_INFO* item)//4B340(<), 4B7A4 (F)
{
	if (room[item->room_number].flags & RF_FILL_WATER)
	{
		lara.water_status = LW_UNDERWATER;
		item->goal_anim_state = STATE_LARA_UNDERWATER_STOP;
		item->current_anim_state = STATE_LARA_UNDERWATER_STOP;
		item->fallspeed = 0;
		item->anim_number = ANIMATION_LARA_UNDERWATER_IDLE;
		item->frame_number = anims[ANIMATION_LARA_UNDERWATER_IDLE].frame_base;
	}
	else
	{
		lara.water_status = LW_ABOVE_WATER;
		item->goal_anim_state = STATE_LARA_STOP;
		item->current_anim_state = STATE_LARA_STOP;
		item->anim_number = ANIMATION_LARA_STAY_SOLID;
		item->frame_number = anims[ANIMATION_LARA_STAY_SOLID].frame_base;
	}
}

void InitialiseLaraLoad(short item_num)//4B308, 4B76C (F)
{
	lara.item_number = item_num;
	lara_item = &items[item_num];
}

void LaraControl(short item_number)//4A838, 4AC9C
{
	long oldx; // $s7
	long oldy; // $fp
	long oldz; // stack offset -44
	struct ITEM_INFO* item; // $s0
	int wh; // $s3
	int wd; // $s4
	int hfw; // $s2
	int room_water_state; // $s5
	short room_number; // stack offset -48

	//a1 = &lara
	//a0 = lara.bitfield
	//v1 = lara.IsMoving
	//v0 = lara.MoveCount & 0xFF
	//v1 = lara.MoveCount + 1;

	item = lara_item;

	if (lara.IsMoving)
	{
		if (++lara.MoveCount > 90)
		{
			lara.IsMoving = 0;
			lara.gun_status = 0;
		}//loc_4A8B0
	}//loc_4A8B0

	//a1 = &lara
	if (!bDisableLaraControl)
	{
		//v1 = &lara
		lara.locationPad = -128;
	}//loc_4A8D0

	oldx = lara_item->pos.x_pos;//s7
	oldy = lara_item->pos.y_pos;//fp
	oldz = lara_item->pos.z_pos;//a0

	//a0 = lara_item
	if (lara.gun_status == 1 && lara_item->current_anim_state == 2 &&
		lara_item->goal_anim_state == 2 && lara_item->anim_number == 0x67 &&
		lara_item->gravity_status == 0)
	{
		lara.gun_status = 0;
	}//loc_4A944

	//a0 = &lara
	if (item->current_anim_state != 0x49 && DashTimer < 120)
	{
		DashTimer++;
	}//loc_4A978

	lara.IsDucked = 0;
	//v0 = &room[item->room_number]
	room_water_state = room[item->room_number].flags & RF_FILL_WATER;
	wd = GetWaterDepth(item->pos.x_pos, item->pos.y_pos, item->pos.z_pos, item->room_number);
	wh = GetWaterHeight(item->pos.x_pos, item->pos.y_pos, item->pos.z_pos, item->room_number);

	hfw = -32152;
	if (wh != -32152)
	{
		hfw = item->pos.y_pos - wh;
	}//loc_4A9F0
	lara.water_surface_dist = -hfw;
	WadeSplash(item, wh, wd);
	//s1 = &lara
	//a2 = lara.water_status

	if (lara.water_status == 1)
	{
		//loc_4AD88
	}//v0 = 2
	else if (lara.water_status > 1)
	{
		//loc_4AA34
		if (lara.water_status == 2)
		{
			//loc_4ACCC
		}//v0 = 0xFFFFF05C
		else if (lara.water_status == 4)
		{
			//loc_4AB94

		}
	}
	else if (lara.water_status == 0)
	{
		//loc_4AA4C
	}
	//slti    $v0, $s2, 0x100
	//j       loc_4AF90

#if 0
		loc_4AA4C :
	bnez    $v0, loc_4AF90
		slti    $v0, $s4, 0x1DB
		bnez    $v0, loc_4AB60
		slti    $v0, $s2, 0x101
		beqz    $s5, loc_4AB90
		move    $a1, $zero
		li      $v0, 0x708
		lw      $a0, dword_800A2048
		li      $a2, 0xFFFFFFF7
		sh      $v0, 0x16($s1)
		sh      $v1, 0xC($s1)
		lw      $v0, 0x84($s0)
		lw      $v1, 0x44($s0)
		and $v0, $a2
		addiu   $v1, 0x64
		sw      $v0, 0x84($s0)
		jal     UpdateLaraRoom
		sw      $v1, 0x44($s0)
		jal     StopSoundEffect
		li      $a0, 0x1E
		lh      $v1, 0xE($s0)
		li      $v0, 0x34
		bne     $v1, $v0, loc_4AABC
		li      $v0, 0x35
		move    $a0, $s0
		j       loc_4AACC
		li      $v0, 0xFFFFE002

		loc_4AABC:
	bne     $v1, $v0, loc_4AAF0
		li      $v0, 0xFFFFE002
		move    $a0, $s0
		li      $v0, 0xFFFFC392

		loc_4AACC :
		li      $v1, 0x23
		sh      $v0, 0x4C($s0)
		jal     AnimateLara
		sh      $v1, 0x10($s0)
		lh      $v0, 0x20($s0)
		nop
		sll     $v0, 1
		j       loc_4AB38
		sh      $v0, 0x20($s0)

		loc_4AAF0:
	lw      $v1, dword_800A25E0
		sh      $v0, 0x4C($s0)
		li      $v0, 0x70
		lh      $a0, 0x20($s0)
		lhu     $a1, 0x1198($v1)
		li      $v1, 0x23
		sh      $v1, 0xE($s0)
		li      $v1, 0x11
		sh      $v0, 0x14($s0)
		sll     $v0, $a0, 1
		addu    $v0, $a0
		sh      $v1, 0x10($s0)
		srl     $v1, $v0, 31
		addu    $v0, $v1
		sra     $v0, 1
		sh      $v0, 0x20($s0)
		sh      $a1, 0x16($s0)

		loc_4AB38:
	lw      $a0, dword_800A2048
		addiu   $v0, $s6, 0x57DC
		sh      $zero, 0xAE($v0)
		sh      $zero, 0xB0($v0)
		sh      $zero, 0xA8($v0)
		jal     Splash
		sh      $zero, 0xAA($v0)
		j       loc_4AB94
		li      $v0, 0xFFFFF05C

		loc_4AB60:
	bnez    $v0, loc_4AB94
		li      $v0, 0xFFFFF05C
		li      $v1, 4
		sh      $v1, 0xC($s1)
		lw      $v0, 0x84($s0)
		nop
		srl     $v0, 3
		andi    $v0, 1
		bnez    $v0, loc_4AB94
		li      $v0, 0xFFFFF05C
		li      $v0, 2
		sh      $v0, 0x10($s0)

		loc_4AB90:
	li      $v0, 0xFFFFF05C

		loc_4AB94 :
		sh      $v0, word_800A23E2
		slti    $v1, $s2, 0x100
		beqz    $v1, loc_4ABC4
		addiu   $v0, $s6, 0x57DC
		sh      $zero, 0xC($v0)
		lh      $v1, 0xE($s0)
		li      $v0, 0x41
		bne     $v1, $v0, loc_4AF90
		li      $v0, 1
		j       loc_4AF90
		sh      $v0, 0x10($s0)

		loc_4ABC4:
	slti    $v0, $s2, 0x2DB
		bnez    $v0, loc_4AF90
		addiu   $a0, $s6, 0x57DC
		li      $v1, 2
		sh      $v1, 0xC($a0)
		lw      $v0, 0x44($s0)
		addiu   $v1, $s2, -1
		subu    $v0, $v1
		lh      $v1, 0xE($s0)
		sw      $v0, 0x44($s0)
		li      $v0, 0x10
		bne     $v1, $v0, loc_4AC10
		nop
		lw      $v0, dword_800A25E0
		li      $v1, 0x8C
		lhu     $a0, 0x15F8($v0)
		j       loc_4AC6C
		li      $v0, 0x2F

		loc_4AC10:
	li      $v0, 0x15
		bne     $v1, $v0, loc_4AC34
		nop
		lw      $v0, dword_800A25E0
		li      $v1, 0x90
		lhu     $a0, 0x1698($v0)
		j       loc_4AC6C
		li      $v0, 0x31

		loc_4AC34:
	li      $v0, 0x16
		bne     $v1, $v0, loc_4AC58
		li      $v1, 0x74
		lw      $v0, dword_800A25E0
		li      $v1, 0x8F
		lhu     $a0, 0x1670($v0)
		j       loc_4AC6C
		li      $v0, 0x30

		loc_4AC58:
	lw      $v0, dword_800A25E0
		nop
		lhu     $a0, 0x1238($v0)
		li      $v0, 0x22

		loc_4AC6C :
		sh      $v1, 0x14($s0)
		sh      $v0, 0x10($s0)
		sh      $v0, 0xE($s0)
		sh      $a0, 0x16($s0)
		move    $a0, $s0
		lw      $v0, 0x84($s0)
		li      $v1, 0xFFFFFFF7
		and $v0, $v1
		lw      $v1, dword_800A2048
		move    $a1, $zero
		sh      $zero, 0x20($s0)
		sw      $v0, 0x84($s0)
		addiu   $v0, $s6, 0x57DC
		sh      $zero, 0x18($v0)
		sh      $zero, 0x50($v1)
		sh      $zero, 0x4C($s0)
		sh      $zero, 0xAE($v0)
		sh      $zero, 0xB0($v0)
		sh      $zero, 0xA8($v0)
		jal     UpdateLaraRoom
		sh      $zero, 0xAA($v0)
		j       loc_4AF90
		nop

		loc_4ACCC :
	bnez    $s5, loc_4AF90
		slti    $v0, $s2, 0x101
		bnez    $v0, loc_4AD18
		li      $v0, 0x22
		li      $v0, 4
		sh      $v0, 0xC($s1)
		li      $v0, 0x67
		lw      $v1, dword_800A25E0
		move    $a0, $s0
		sh      $v0, 0x14($s0)
		lhu     $a1, 0x1030($v1)
		li      $v0, 0x41
		sh      $a2, 0xE($s0)
		sh      $v0, 0x10($s0)
		jal     AnimateItem
		sh      $a1, 0x16($s0)
		j       loc_4AD5C
		nop

		loc_4AD18 :
	lw      $v1, anims
		sh      $zero, 0xC($s1)
		lh      $a1, 0x20($s0)
		lhu     $a0, 0x568($v1)
		li      $v1, 3
		sh      $v0, 0x14($s0)
		sh      $v1, 0x10($s0)
		sh      $v1, 0xE($s0)
		bgez    $a1, loc_4AD48
		sh      $a0, 0x16($s0)
		addiu   $a1, 3

		loc_4AD48:
	lw      $v0, 0x84($s0)
		sra     $v1, $a1, 2
		sh      $v1, 0x1E($s0)
		ori     $v0, 8
		sw      $v0, 0x84($s0)

		loc_4AD5C :
		lw      $v0, lara_item
		sh      $zero, 0x20($s0)
		sh      $zero, 0x50($v0)
		addiu   $v0, $s6, 0x57DC
		sh      $zero, 0x4C($s0)
		sh      $zero, 0xAE($v0)
		sh      $zero, 0xB0($v0)
		sh      $zero, 0xA8($v0)
		j       loc_4AF90
		sh      $zero, 0xAA($v0)

		loc_4AD88:
	addiu   $a3, $sp, 0x40 + var_30
		lw      $a0, 0x40($s0)
		lw      $a2, 0x48($s0)
		lw      $a1, 0x44($s0)
		lh      $v0, 0x18($s0)
		addiu   $a1, -0x100
		jal     GetFloor
		sh      $v0, 0x40 + var_30($sp)
		lh      $v1, 0x40 + var_30($sp)
		lw      $a0, room
		sll     $v0, $v1, 2
		addu    $v0, $v1
		sll     $v0, 4
		addu    $v0, $a0
		lhu     $v1, 0x4E($v0)
		li      $v0, 0xFFFF8100
		beq     $s4, $v0, loc_4AE70
		andi    $v1, 1
		bgez    $s2, loc_4ADE0
		move    $v0, $s2
		negu    $v0, $v0

		loc_4ADE0 :
	slti    $v0, 0x100
		beqz    $v0, loc_4AE70
		nop
		bnez    $v1, loc_4AE70
		li      $a3, 0x72
		lh      $v1, 0x14($s0)
		nop
		beq     $v1, $a3, loc_4AE70
		li      $v0, 0x77
		beq     $v1, $v0, loc_4AE70
		move    $a0, $s0
		li      $v0, 2
		sh      $v0, 0xC($s1)
		addiu   $v0, $s3, 1
		lw      $v1, dword_800A25E0
		move    $a1, $zero
		sw      $v0, 0x44($s0)
		lhu     $a2, 0x11E8($v1)
		lw      $v1, dword_800A2048
		li      $v0, 0x21
		sh      $v0, 0x10($s0)
		sh      $v0, 0xE($s0)
		li      $v0, 0xB
		sh      $a3, 0x14($s0)
		sh      $zero, 0x20($s0)
		sh      $a2, 0x16($s0)
		sh      $v0, 0x18($s1)
		sh      $zero, 0x50($v1)
		sh      $zero, 0x4C($s0)
		sh      $zero, 0xAE($s1)
		sh      $zero, 0xB0($s1)
		sh      $zero, 0xA8($s1)
		j       loc_4AEFC
		sh      $zero, 0xAA($s1)

		loc_4AE70:
	bnez    $s5, loc_4AF90
		li      $v0, 0xFFFF8100
		beq     $s4, $v0, loc_4AF24
		addiu   $a2, $s6, 0x57DC
		bgez    $s2, loc_4AE8C
		move    $v0, $s2
		negu    $v0, $v0

		loc_4AE8C :
	slti    $v0, 0x100
		beqz    $v0, loc_4AF24
		move    $a0, $s0
		li      $a1, 0xFFFFFE83
		addiu   $a2, $s6, 0x57DC
		lw      $v1, dword_800A25E0
		li      $v0, 2
		sh      $v0, 0xC($a2)
		sw      $s3, 0x44($s0)
		lhu     $a3, 0x11E8($v1)
		li      $v1, 0x21
		sh      $v1, 0x10($s0)
		sh      $v1, 0xE($s0)
		lw      $v1, dword_800A2048
		li      $v0, 0x72
		sh      $v0, 0x14($s0)
		li      $v0, 0xB
		sh      $zero, 0x20($s0)
		sh      $a3, 0x16($s0)
		sh      $v0, 0x18($a2)
		sh      $zero, 0x50($v1)
		sh      $zero, 0x4C($s0)
		sh      $zero, 0xAE($a2)
		sh      $zero, 0xB0($a2)
		sh      $zero, 0xA8($a2)
		sh      $zero, 0xAA($a2)

		loc_4AEFC:
	jal     sub_7C58C
		nop
		li      $a0, 0x24
		lw      $a1, dword_800A2048
		li      $a2, 2
		jal     sub_91780
		addiu   $a1, 0x40
		j       loc_4AF90
		nop

		loc_4AF24 :
	lw      $v1, dword_800A25E0
		li      $v0, 0x22
		sh      $zero, 0xC($a2)
		lh      $a1, 0x20($s0)
		lhu     $a0, 0x568($v1)
		li      $v1, 3
		sh      $v0, 0x14($s0)
		sh      $v1, 0x10($s0)
		sh      $v1, 0xE($s0)
		bgez    $a1, loc_4AF58
		sh      $a0, 0x16($s0)
		addiu   $a1, 3

		loc_4AF58:
	sra     $v0, $a1, 2
		sh      $v0, 0x1E($s0)
		lw      $v0, 0x84($s0)
		lw      $v1, dword_800A2048
		sh      $zero, 0x20($s0)
		ori     $v0, 8
		sw      $v0, 0x84($s0)
		sh      $zero, 0x50($v1)
		sh      $zero, 0x4C($s0)
		sh      $zero, 0xAE($a2)
		sh      $zero, 0xB0($a2)
		sh      $zero, 0xA8($a2)
		sh      $zero, 0xAA($a2)

		loc_4AF90:
	lh      $v1, 0x18($s0)
		lw      $a0, dword_800A24DC
		sll     $v0, $v1, 2
		addu    $v0, $v1
		sll     $v0, 4
		addu    $v0, $a0
		lbu     $a0, 0x34($v0)
		jal     sub_91CF4
		nop
		lh      $v0, 0x22($s0)
		nop
		bgtz    $v0, loc_4B020
		addiu   $v0, $s6, 0x57DC
		li      $v0, 0xFFFFFFFF
		addiu   $s1, $s6, 0x57DC
		sh      $v0, 0x22($s0)
		lh      $v0, 0x1A($s1)
		nop
		bnez    $v0, loc_4AFEC
		nop
		jal     sub_5DCD0
		nop

		loc_4AFEC :
	lhu     $v0, 0x1A($s1)
		lw      $v1, dword_800A2048
		addiu   $a0, $v0, 1
		sh      $a0, 0x1A($s1)
		lhu     $v0, 0x28($v1)
		nop
		andi    $v0, 0x100
		beqz    $v0, loc_4B01C
		addiu   $v0, $a0, 1
		j       loc_4B2D8
		sh      $v0, 0x1A($s1)

		loc_4B01C:
	addiu   $v0, $s6, 0x57DC

		loc_4B020 :
		lh      $v1, 0xC($v0)
		nop
		sltiu   $v0, $v1, 5      # switch 5 cases
		beqz    $v0, def_4B04C   # jumptable 0004B04C default case
		lui     $s1, 0xB
		la      $v0, jpt_4B04C
		sll     $v1, 2
		addu    $v1, $v0
		lw      $a0, 0($v1)
		nop
		jr      $a0              # switch jump
		nop

		loc_4B054 : # jumptable 0004B04C cases 0, 4
		addiu   $a0, $s6, 0x57DC
		lw      $v0, 0x44($a0)
		nop
		andi    $v0, 0x200
		beqz    $v0, loc_4B0B0
		nop
		lh      $v0, 0x22($s0)
		nop
		bltz    $v0, loc_4B0F0
		nop
		lhu     $v0, 0x16($a0)
		nop
		addiu   $v0, -1
		sh      $v0, 0x16($a0)
		sll     $v0, 16
		bgez    $v0, loc_4B0F0
		li      $v1, 0xFFFFFFFF
		sh      $v1, 0x16($a0)
		lhu     $v0, 0x22($s0)
		nop
		addiu   $v0, -5
		j       loc_4B0F0
		sh      $v0, 0x22($s0)

		loc_4B0B0:
	lh      $v0, 0x16($a0)
		lhu     $v1, 0x16($a0)
		slti    $v0, 0x708
		beqz    $v0, loc_4B0F0
		nop
		lh      $v0, 0x22($s0)
		nop
		bltz    $v0, loc_4B0F0
		addiu   $v0, $v1, 0xA
		sh      $v0, 0x16($a0)
		sll     $v0, 16
		sra     $v0, 16
		slti    $v0, 0x709
		bnez    $v0, loc_4B0F0
		li      $v0, 0x708
		sh      $v0, 0x16($a0)

		loc_4B0F0:
	move    $a0, $s0
		lw      $a1, 0x5D8($gp)
		jal     sub_14228
		lui     $s1, 0xB
		j       def_4B04C        # jumptable 0004B04C default case
		nop

		loc_4B108 : # jumptable 0004B04C case 1
		lh      $v0, 0x22($s0)
		nop
		bltz    $v0, loc_4B204
		lui     $s1, 0xB
		lbu     $v1, byte_800A220C
		li      $v0, 5
		bne     $v1, $v0, loc_4B198
		addiu   $v1, $s6, 0x57DC
		jal     sub_20E34
		li      $a0, 0x28
		beqz    $v0, loc_4B1A8
		addiu   $a0, $s6, 0x57DC
		lbu     $v1, 0x34($a0)
		lhu     $v0, 0xC7A($gp)
		addiu   $v1, 8
		addu    $v0, $v1
		sh      $v0, 0xC7A($gp)
		sll     $v0, 16
		sra     $v0, 16
		slti    $v0, 0x51
		bnez    $v0, loc_4B1AC
		nop

		loc_4B164 :
	lhu     $v1, 0x16($a0)
		lhu     $v0, 0xC7A($gp)
		addiu   $v1, -1
		addiu   $v0, -0x50
		sh      $v1, 0x16($a0)
		sh      $v0, 0xC7A($gp)
		sll     $v0, 16
		sra     $v0, 16
		slti    $v0, 0x51
		beqz    $v0, loc_4B164
		nop
		j       loc_4B1AC
		addiu   $a0, $s6, 0x57DC

		loc_4B198:
	lhu     $v0, 0x16($v1)
		nop
		addiu   $v0, -1
		sh      $v0, 0x16($v1)

		loc_4B1A8 :
		addiu   $a0, $s6, 0x57DC

		loc_4B1AC :
		lh      $v0, 0x16($a0)
		nop
		bgez    $v0, loc_4B204
		li      $v0, 5
		lbu     $v1, byte_800A220C
		nop
		bne     $v1, $v0, loc_4B1E8
		nop
		lbu     $v1, 0x34($a0)
		nop
		sltiu   $v0, $v1, 0xFB
		beqz    $v0, loc_4B1E8
		addiu   $v0, $v1, 4
		sb      $v0, 0x34($a0)

		loc_4B1E8:
	addiu   $a0, $s6, 0x57DC
		li      $v1, 0xFFFFFFFF
		sh      $v1, 0x16($a0)
		lhu     $v0, 0x22($s0)
		nop
		addiu   $v0, -5
		sh      $v0, 0x22($s0)

		loc_4B204:
	lw      $a1, 0x5D8($gp)
		jal     sub_4BFB4
		move    $a0, $s0
		j       def_4B04C        # jumptable 0004B04C default case
		nop

		loc_4B218 : # jumptable 0004B04C case 2
		lh      $v0, 0x22($s0)
		nop
		bltz    $v0, loc_4B250
		addiu   $v1, $s6, 0x57DC
		lhu     $v0, 0x16($v1)
		nop
		addiu   $v0, 0xA
		sh      $v0, 0x16($v1)
		sll     $v0, 16
		sra     $v0, 16
		slti    $v0, 0x709
		bnez    $v0, loc_4B250
		li      $v0, 0x708
		sh      $v0, 0x16($v1)

		loc_4B250:
	move    $a0, $s0
		lw      $a1, 0x5D8($gp)
		jal     sub_4D684
		lui     $s1, 0xB
		j       def_4B04C        # jumptable 0004B04C default case
		nop

		loc_4B268 : # jumptable 0004B04C case 3
		move    $a0, $s0
		lw      $a1, 0x5D8($gp)
		jal     sub_4A790
		lui     $s1, 0xB

		def_4B04C:               # jumptable 0004B04C default case
		lw      $v0, 0x40($s0)
		nop
		subu    $v0, $s7
		mult    $v0, $v0
		lw      $v1, 0x44($s0)
		mflo    $v0
		subu    $v1, $fp
		nop
		mult    $v1, $v1
		lw      $a0, 0x48($s0)
		lw      $a1, 0x40 + var_2C($sp)
		mflo    $v1
		subu    $a0, $a1
		nop
		mult    $a0, $a0
		addu    $v0, $v1
		mflo    $a0
		jal     sub_779DC
		addu    $a0, $v0, $a0
		addiu   $a0, $s1, -0x4C24
		lw      $v1, 0x188($a0)
		nop
		addu    $v1, $v0
		sw      $v1, 0x188($a0)

		loc_4B2D8:
	lw      $ra, 0x40 + var_4($sp)
		lw      $fp, 0x40 + var_8($sp)
		lw      $s7, 0x40 + var_C($sp)
		lw      $s6, 0x40 + var_10($sp)
		lw      $s5, 0x40 + var_14($sp)
		lw      $s4, 0x40 + var_18($sp)
		lw      $s3, 0x40 + var_1C($sp)
		lw      $s2, 0x40 + var_20($sp)
		lw      $s1, 0x40 + var_24($sp)
		lw      $s0, 0x40 + var_28($sp)
		jr      $ra
		addiu   $sp, 0x40
#endif
#if 1 //CONTROLS_TEST
		if (lara.water_status == 1)
		{

		}

	if ((RawPad & 0x10))
	{
		camera.pos.x += 0x20;
		lara_item->pos.x_pos += 0x20;
	}
	if ((RawPad & 0x40))
	{
		camera.pos.x -= 0x20;
		lara_item->pos.x_pos -= 0x20;
	}

	if ((RawPad & 0x80))
	{
		camera.pos.z -= 0x20;
		lara_item->pos.z_pos -= 0x20;
	}

	if ((RawPad & 0x20))
	{
		camera.pos.z += 0x20;
		lara_item->pos.z_pos += 0x20;
	}

	if ((RawPad & 0x100))
	{
		camera.pos.y -= 0x20;
		lara_item->pos.y_pos -= 0x20;
	}

	if ((RawPad & 0x400))
	{
		camera.pos.y += 0x20;
		lara_item->pos.y_pos += 0x20;
	}

	if ((RawPad & IN_R2) && (RawPad & IN_DPAD_UP))
	{
		camera.pos.room_number++;
		camera.pos.room_number %= number_rooms;
		//lara_item->pos.y_rot += 0x40;
	}
	if ((RawPad & IN_R2) && (RawPad & IN_DPAD_DOWN))
	{
		camera.pos.room_number--;
		if (camera.pos.room_number < 0)
		{
			camera.pos.room_number = 0;
		}
		//lara_item->pos.y_rot += 0x40;
	}
	/*struct FLOOR_INFO* floor;
	short rn = camera.pos.room_number;
	floor = GetFloor(camera.pos.x, camera.pos.y, camera.pos.z, &rn);
	int height = GetHeight(floor, camera.pos.x, camera.pos.y, camera.pos.z);
	UpdateLaraRoom(lara_item, height);
	if (floor != NULL)
	{
		camera.pos.room_number = rn;
	}*/

	//item->pos.x_pos += (SIN(lara.move_angle) * item->speed) >> W2V_SHIFT;
	//item->pos.z_pos += (COS(lara.move_angle) * item->speed) >> W2V_SHIFT;
#endif
}

void LaraCheat(struct ITEM_INFO* item, struct COLL_INFO* coll)//4A790(<), 4ABF4(<) (F)
{
	lara_item->hit_points = 1000;
	LaraUnderWater(item, coll);
	if (input & IN_WALK)
	{
		if (!(input & IN_LOOK))
		{
			lara.water_status = LW_ABOVE_WATER;
			item->frame_number = anims[ANIMATION_LARA_STAY_SOLID].frame_base;
			item->anim_number = ANIMATION_LARA_STAY_SOLID;
			item->pos.z_rot = 0;
			item->pos.x_rot = 0;
			lara.torso_y_rot = 0;
			lara.torso_x_rot = 0;
			lara.head_y_rot = 0;
			lara.head_x_rot = 0;
			lara.gun_status = LG_NO_ARMS;
			LaraInitialiseMeshes();
			lara.mesh_effects = 0;
			lara_item->hit_points = cheat_hit_points;
		}
	}
}

void LaraInitialiseMeshes()//4A684, 4AAE8 (F)
{
	int i;
	for(i = 0; i < 15; i++)
	{
		lara.mesh_ptrs[i] = meshes[objects[LARA].mesh_index + 2 * i] = meshes[objects[LARA_SKIN].mesh_index + 2 * i];
	}

	if (gfCurrentLevel >= LVL5_GALLOWS_TREE && gfCurrentLevel <= LVL5_OLD_MILL)
	{
		lara.mesh_ptrs[LM_TORSO] = meshes[objects[ANIMATING6_MIP].mesh_index + 2 * LM_TORSO];
	}

	if (lara.gun_type == WEAPON_HK)
	{
		lara.back_gun = WEAPON_HK;
	}
	else if (!lara.shotgun_type_carried)
	{
		if (lara.hk_type_carried)
		{
			lara.back_gun = WEAPON_HK;
		}
	}
	else
	{
		lara.back_gun = WEAPON_UZI;
	}

	lara.gun_status = LG_NO_ARMS;
	lara.left_arm.frame_number = 0;
	lara.right_arm.frame_number = 0;
	lara.target = 0;
	lara.right_arm.lock = 0;
	lara.left_arm.lock = 0;
}

void InitialiseLara(int restore)
{
	int i;
	short item;
	short gun;

	if (lara.item_number == -1)
		return;

	item = lara.item_number;

	lara_item->data = &lara;
	lara_item->collidable = FALSE;

	if (restore)
	{
		struct lara_info backup;
		memcpy(&backup, &lara, sizeof(lara));
		memset(&lara, 0, sizeof(lara));
		memcpy(&lara.pistols_type_carried, &backup.pistols_type_carried, 59);
	}
	else
	{
		memset(&lara, 0, sizeof(lara));
	}

	lara.look = TRUE;
	lara.item_number = item;
	lara.hit_direction = -1;
	lara.air = 1800;
	lara.weapon_item = -1;
	PoisonFlag = 0;
	lara.dpoisoned = 0;
	lara.poisoned = 0;
	lara.water_surface_dist = 100;
	lara.holster = 14;
	lara.location = -1;
	lara.highest_location = -1;
	lara.RopePtr = -1;
	lara_item->hit_points = 1000;

	for(i = 0; i < gfNumPickups; i++)
	{
		DEL_picked_up_object(convert_invobj_to_obj(gfPickups[i]));
	}

	gfNumPickups = 0;

	lara.gun_status = LG_NO_ARMS;

	gun = WEAPON_NONE;

	if (!(gfLevelFlags & GF_LVOP_YOUNG_LARA) && objects[PISTOLS_ITEM].loaded)
		gun = WEAPON_PISTOLS;

	if ((gfLevelFlags & GF_LVOP_TRAIN) && objects[HK_ITEM].loaded && (lara.hk_type_carried & WTYPE_PRESENT))
		gun = WEAPON_HK;

	lara.last_gun_type = lara.gun_type = lara.request_gun_type = gun;

	LaraInitialiseMeshes();

	lara.skelebob = 0;

	if (objects[PISTOLS_ITEM].loaded)
		lara.pistols_type_carried = WTYPE_PRESENT | WTYPE_AMMO_1;

	lara.binoculars = WTYPE_PRESENT;

	if (!restore)
	{
		if (objects[FLARE_INV_ITEM].loaded)
			lara.num_flares = 3;

		lara.num_small_medipack = 3;
		lara.num_large_medipack = 1;
	}

	lara.num_pistols_ammo = -1;

	InitialiseLaraAnims(lara_item);

	DashTimer = 120;

	for (i = 0; i < gfNumTakeaways; i++)
	{
		NailInvItem(convert_invobj_to_obj(gfTakeaways[i]));
	}

	gfNumTakeaways = 0;

	weapons[WEAPON_REVOLVER].damage = gfCurrentLevel >= LVL5_BASE ? 15 : 6;

	switch(gfCurrentLevel)
	{
	case 6u:
		lara.pickupitems &= 0xFFF7u;

		lara.puzzleitems[0] = 10;
		return;
	case 5u:
		lara.pickupitems = 0;
		lara.pickupitemscombo = 0;
		lara.keyitems = 0;
		lara.keyitemscombo = 0;
		lara.puzzleitemscombo = 0;

		memset(lara.puzzleitems, 0, 12);
		return;
	case 7u:	
		lara.pickupitems = 0;

		lara.puzzleitems[0] = 0;
		return;
	case 0xCu:
		lara.pickupitems &= 0xFFFEu;

		lara.puzzleitems[2] = 0;
		lara.puzzleitems[3] = 0;
		break;
	case 0xEu:
		lara.pickupitems &= 0xFFFDu;
		break;
	default:
		if (gfCurrentLevel < LVL5_THIRTEENTH_FLOOR || gfCurrentLevel > LVL5_RED_ALERT)
			lara.pickupitems &= 0xFFF7u;
		return;
	}

	lara.bottle = 0;
	lara.wetcloth = CLOTH_MISSING;
}