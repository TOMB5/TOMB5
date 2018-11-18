#include "PEOPLE.H"

#include "CONTROL.H"
#include "SPECIFIC.H"
#include "LARA.H"
#include "SOUND.H"
#include "EFFECTS.H"
#include "DRAW.H"
#include "OBJECTS.H"
#include "TOMB4FX.H"

#if PSX_VERSION || PSXPC_VERSION
#include "MISC.H"
#endif


int ShotLara(struct ITEM_INFO* item, struct AI_info* info, struct BITE_INFO* gun, short extra_rotation, int damage)//50C74, 510D8
{
	UNIMPLEMENTED();
	return 0;
}

short GunMiss(long x, long y, long z, short speed, int yrot, int room_number)//50B58, 50FBC (F)
{
	struct GAME_VECTOR pos;

	pos.x = lara_item->pos.x_pos + ((GetRandomControl() - 0x4000) << 9) / 0x7FFF;
	pos.y = lara_item->floor;
	pos.z = lara_item->pos.z_pos + ((GetRandomControl() - 0x4000) << 9) / 0x7FFF;
	pos.room_number = lara_item->room_number;

	Richochet(&pos);

	return GunShot(x, y, z, speed, yrot, room_number);
}

short GunHit(long x, long y, long z, short speed, int yrot, int room_number)//50A3C, 50EA0 (F)
{
	struct PHD_VECTOR pos;

	pos.x = 0;
	pos.y = 0;
	pos.z = 0;

	GetJointAbsPosition(lara_item, &pos, (25 * GetRandomControl()) >> 15);

	DoBloodSplat(pos.x, pos.y, pos.z, (GetRandomControl() & 3) + 3, lara_item->pos.y_rot, lara_item->room_number);
	SoundEffect(SFX_LARA_INJURY_RND, &lara_item->pos, 0);

	return GunShot(x, y, z, speed, yrot, room_number);
}

short GunShot(long x, long y, long z, short speed, int yrot, int room_number)//50A34(<), 50E98(<) (F)
{
	return -1;
}

int Targetable(struct ITEM_INFO* item, struct AI_info* info)//508EC, 50D50 (F)
{
	struct creature_info* creature = (struct creature_info*)item->data;
	struct ITEM_INFO* enemy = creature->enemy;

	if (enemy != NULL && enemy->hit_points > 0 && enemy->data != NULL && 
		info->ahead && info->distance < 0x4000000)
	{
		struct GAME_VECTOR start, target;

		short* bounds = GetBestFrame(item);

		start.x = item->pos.x_pos;
		if (item->object_number == SNIPER)
			start.y = item->pos.y_pos - 768;
		else
			start.y = item->pos.y_pos + ((bounds[3] + 3 * bounds[2]) >> 2);
		start.z = item->pos.z_pos;
		start.room_number = item->room_number;

		bounds = GetBestFrame(enemy);

		target.x = enemy->pos.x_pos;
		target.y = enemy->pos.y_pos + ((bounds[3] + 3 * bounds[2]) >> 2);
		target.z = enemy->pos.z_pos;

		return LOS(&start, &target);
	}

	return 0;
}

int TargetVisible(struct ITEM_INFO* item, struct AI_info* info)//507DC, 50C40
{
	UNIMPLEMENTED();
	return 0;
}