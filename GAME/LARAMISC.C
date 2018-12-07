#include "LARAMISC.H"

#include "SPECIFIC.H"
#include "LARA.H"
#if PSX_VERSION || PSXPC_VERSION
#include "CALCLARA.H"
#include "MATHS.H"
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
#include <string.h>

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

enum headings
{
	NORTH,
	EAST,
	SOUTH,
	WEST
};

enum height_types
{
	WALL,
	SMALL_SLOPE,
	BIG_SLOPE,
	DIAGONAL,
	SPLIT_TRI
};

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
	UNIMPLEMENTED();
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