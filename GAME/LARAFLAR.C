#include "LARAFLAR.H"

#include "SPECIFIC.H"
#include "LARA.H"

#include <stddef.h>

void FlareControl(short item_number)//4A418, 4A87C
{
	S_Warn("[FlareControl] - Unimplemented!\n");
}

void ready_flare()//4A3E4(<), 4A848(<) (F)
{
	lara.gun_status = 0;
	lara.left_arm.z_rot = 0;
	lara.left_arm.y_rot = 0;
	lara.left_arm.x_rot = 0;
	lara.right_arm.z_rot = 0;
	lara.right_arm.y_rot = 0;
	lara.right_arm.x_rot = 0;
	lara.right_arm.lock = 0;
	lara.left_arm.lock = 0;
	lara.target = NULL;
}

void undraw_flare_meshes()//4A3BC, 4A820
{
	S_Warn("[undraw_flare_meshes] - Unimplemented!\n");
}

void draw_flare_meshes()//4A394, 4A7F8
{
	S_Warn("[draw_flare_meshes] - Unimplemented!\n");
}

void undraw_flare()//4A108, 4A56C
{
	S_Warn("[undraw_flare] - Unimplemented!\n");
}

void draw_flare()//49F74, 4A3D8
{
	S_Warn("[draw_flare] - Unimplemented!\n");
}

void set_flare_arm(int frame)//49ED4, 4A338
{
	S_Warn("[set_flare_arm] - Unimplemented!\n");
}

void CreateFlare(short object, int thrown)//49BBC, 4A020
{
	S_Warn("[CreateFlare] - Unimplemented!\n");
}

void DrawFlareInAir(struct ITEM_INFO *item)//49A8C, 49EF0
{
	S_Warn("[DrawFlareInAir] - Unimplemented!\n");
}

void DoFlareInHand(int flare_age)//49984, 49DE8
{
	S_Warn("[DoFlareInHand] - Unimplemented!\n");
}

int DoFlareLight(struct PHD_VECTOR *pos, int flare_age)//49708, 49B6C
{
	S_Warn("[DoFlareLight] - Unimplemented!\n");
	return 0;
}