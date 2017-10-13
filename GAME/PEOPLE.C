#include "PEOPLE.H"

#include "SPECIFIC.H"

int ShotLara(ITEM_INFO* item, AI_info* info, BITE_INFO* gun, short extra_rotation, int damage)//50C74, 510D8
{
	S_Warn("[ShotLara] - Unimplemented!\n");
	return 0;
}

short GunMiss(long x, long y, long z, short speed, int yrot, int room_number)//50B58, 50FBC
{
	S_Warn("[GunMiss] - Unimplemented!\n");
	return 0;
}

short GunHit(long x, long y, long z, short speed, int yrot, int room_number)//50A3C, 50EA0
{
	S_Warn("[GunHit] - Unimplemented!\n");
	return 0;
}

short GunShot(long x, long y, long z, short speed, int yrot, int room_number)//50A34(<), 50E98(<) (F)
{
	return -1;
}

int Targetable(ITEM_INFO* item, AI_info* info)//508EC, 50D50
{
	S_Warn("[Targetable] - Unimplemented!\n");
	return 0;
}

int TargetVisible(ITEM_INFO* item, AI_info* info)//507DC, 50C40
{
	S_Warn("[TargetVisible] - Unimplemented!\n");
	return 0;
}