#include "LARAMISC.H"
#include "SPECIFIC.H"

char* states[131];
char* quadrant_names[4];
char* gunstates[6];
char* waterstates[5];
char* guntypes[9];
char* coll_typess[8];
char* htypes[4];
static struct COLL_INFO* coll;
short SubsuitAir;
struct COLL_INFO mycoll;
short cheat_hit_points;

void GetLaraDeadlyBounds()//4B408, 4B86C
{
	S_Warn("[GetLaraDeadlyBounds] - Unimplemented!\n");
}

void DelAlignLaraToRope(struct ITEM_INFO *item)//4B3D8, 4B83C
{
	S_Warn("[DelAlignLaraToRope] - Unimplemented!\n");
}

void InitialiseLaraAnims(struct ITEM_INFO *item)//4B340, 4B7A4
{
	S_Warn("[InitialiseLaraAnims] - Unimplemented!\n");
}

void InitialiseLaraLoad(short item_num)//4B308, 4B76C
{
	

	S_Warn("[InitialiseLaraLoad] - Unimplemented!\n");
}

void LaraControl(short item_number)//4A838, 4AC9C
{
	S_Warn("[LaraControl] - Unimplemented!\n");
}

void LaraCheat(struct ITEM_INFO *item, struct COLL_INFO *coll)//4A790, 4ABF4
{
	S_Warn("[LaraCheat] - Unimplemented!\n");
}

void LaraInitialiseMeshes()//4A684, 4AAE8
{
	S_Warn("[LaraInitialiseMeshes] - Unimplemented!\n");
}
