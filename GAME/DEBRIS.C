#include "DEBRIS.H"
#include "SPECIFIC.H"

struct DEBRIS_STRUCT debris[128];
short DebrisFlags;
long next_debris;

void ShatterObject(struct SHATTER_ITEM *ShatterItem, struct MESH_INFO *StaticMesh, short Num, short RoomNumber, int NoXZVel)//36A3C, 36F3C
{
	S_Warn("[ShatterObject] - Unimplemented!\n");
}

void TriggerDebris(struct GAME_VECTOR *pos, void *TextInfo, short *Offsets, long *Vels, int rgb)//3675C, 36C5C
{
	S_Warn("[TriggerDebris] - Unimplemented!\n");
}

long GetFreeDebris()//366B0, 36BB0
{
	S_Warn("[GetFreeDebris] - Unimplemented!\n");
	return 0;
}
