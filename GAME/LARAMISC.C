#include "LARAMISC.H"

#include "SPECIFIC.H"
#include "LARA.H"
#include "CONTROL.H"
#include "DRAW.H"
#include "LARASWIM.H"

#include INPUT_H

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

static struct COLL_INFO *coll = &mycoll; // offset 0xA0B8C
short SubsuitAir = 0; // offset 0xA122E
struct COLL_INFO mycoll;
short cheat_hit_points; // offset 0xA3828

void GetLaraDeadlyBounds()//4B408, 4B86C
{
	S_Warn("[GetLaraDeadlyBounds] - Unimplemented!\n");
}

void DelAlignLaraToRope(struct ITEM_INFO* item)//4B3D8, 4B83C
{
	S_Warn("[DelAlignLaraToRope] - Unimplemented!\n");
}

void InitialiseLaraAnims(struct ITEM_INFO* item)//4B340, 4B7A4
{
	S_Warn("[InitialiseLaraAnims] - Unimplemented!\n");
}

void InitialiseLaraLoad(short item_num)//4B308, 4B76C (F)
{
	lara.item_number = item_num;
	lara_item = &items[item_num];
}

void LaraControl(short item_number)//4A838, 4AC9C
{
	S_Warn("[LaraControl] - Unimplemented!\n");
}

void LaraCheat(struct ITEM_INFO* item, struct COLL_INFO* coll)//4A790(<), 4ABF4(<) (F)
{
	lara_item->hit_points = 1000;
	LaraUnderWater(item, coll);
	if (input & IN_WALK)
	{
		if (!(input & IN_LOOK))
		{
			lara.water_status = 0;
			item->frame_number = anims[ANIMATION_LARA_STAY_SOLID].frame_base;
			item->anim_number = ANIMATION_LARA_STAY_SOLID;
			item->pos.z_rot = 0;
			item->pos.x_rot = 0;
			lara.torso_y_rot = 0;
			lara.torso_x_rot = 0;
			lara.head_y_rot = 0;
			lara.head_x_rot = 0;
			lara.gun_status = 0;
			LaraInitialiseMeshes();
			lara.mesh_effects = 0;
			lara_item->hit_points = cheat_hit_points;
		}
	}
}

void LaraInitialiseMeshes()//4A684, 4AAE8
{
	S_Warn("[LaraInitialiseMeshes] - Unimplemented!\n");
}