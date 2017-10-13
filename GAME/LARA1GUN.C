#include "LARA1GUN.H"

#include "SPECIFIC.H"
#ifdef PC_VERSION
#include "GAME.H"
#else
#include "SETUP.H"
#endif
#include "DRAW.H"
#include "LARA.H"
#include "LARAFIRE.H"
#include "OBJECTS.H"

char HKTimer = 0;
char HKShotsFired = 0;

void TriggerGrapplingEffect(long x, long y, long z)
{
	S_Warn("[TriggerGrapplingEffect] - Unimplemented!\n");
}

void DoGrenadeDamageOnBaddie(ITEM_INFO* baddie, ITEM_INFO* item)
{
	S_Warn("[DoGrenadeDamageOnBaddie] - Unimplemented!\n");
}

void AnimateShotgun(int weapon_type)
{
	S_Warn("[AnimateShotgun] - Unimplemented!\n");
}

void undraw_shotgun(int weapon_type)
{
	S_Warn("[undraw_shotgun] - Unimplemented!\n");
}

void draw_shotgun(int weapon_type)
{
	S_Warn("[draw_shotgun] - Unimplemented!\n");
}

void ControlCrossbow(short item_number)
{
	S_Warn("[ControlCrossbow] - Unimplemented!\n");
}

void CrossbowHitSwitchType78(ITEM_INFO* item, ITEM_INFO* target, int MustHitLastNode)
{
	S_Warn("[CrossbowHitSwitchType78] - Unimplemented!\n");
}

void FireCrossbow(PHD_3DPOS* Start)
{
	S_Warn("[FireCrossbow] - Unimplemented!\n");
}

void FireHK(int running)
{
	S_Warn("[FireHK] - Unimplemented!\n");
}

void FireShotgun()
{
	S_Warn("[FireShotgun] - Unimplemented!\n");
}

void RifleHandler(int weapon_type)
{
	S_Warn("[RifleHandler] - Unimplemented!\n");
}

void ready_shotgun(int weapon_type)//424E0(<), 42934(<) (F)
{
	object_info* object;

	lara.gun_status = 4;
	lara.left_arm.z_rot = 0;
	lara.left_arm.y_rot = 0;
	lara.left_arm.x_rot = 0;

	lara.right_arm.z_rot = 0;
	lara.right_arm.x_rot = 0;
	lara.right_arm.y_rot = 0;

	lara.right_arm.frame_number = 0;
	lara.left_arm.frame_number = 0;

	lara.right_arm.lock = 0;
	lara.left_arm.lock = 0;
	lara.target = NULL;

	object = &objects[WeaponObject(weapon_type)];//v1

	lara.right_arm.frame_base = object->frame_base;
	lara.left_arm.frame_base = object->frame_base;

	return;
}

void undraw_shotgun_meshes(int weapon_type)//42498(<), 428EC(<) (F)
{
	lara.back_gun = WeaponObject(weapon_type);
	lara.mesh_ptrs[LM_RHAND] = meshes[objects[LARA].mesh_index + 20];
}

void draw_shotgun_meshes(int weapon_type)//42444(<), 42898(<) (F)
{
	lara.back_gun = 0;
	lara.mesh_ptrs[LM_RHAND] = meshes[objects[WeaponObjectMesh(weapon_type)].mesh_index + 20];
}