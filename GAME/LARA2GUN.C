#include "LARA2GUN.H"

#include "SPECIFIC.H"
#include "LARA.H"
#include "LARAFIRE.H"
#ifdef PC_VERSION
#include "GAME.H"
#else
#include "SETUP.H"
#endif
#include "DRAW.H"
#include "OBJECTS.H"

static struct PISTOL_DEF PistolTable[4] =
{
	{ LARA, 0, 0, 0, 0 },
	{ PISTOLS_ANIM, 4, 5, 0xD, 0x18 },
	{ REVOLVER_ANIM , 7, 8, 0xF, 0x1D },
	{ UZI_ANIM, 4, 5, 0xD, 0x18 }
};

void AnimatePistols(int weapon_type)
{
	S_Warn("[AnimatePistols] - Unimplemented!\n");
}

void PistolHandler(int weapon_type)
{
	S_Warn("[PistolHandler] - Unimplemented!\n");
}

void undraw_pistol_mesh_right(int weapon_type)//44968(<), 44DCC(<) (F)
{
	WeaponObject(weapon_type);
	lara.mesh_ptrs[LM_RHAND] = meshes[objects[LARA].mesh_index + 20];
	switch (weapon_type)
	{
	case 1:
		lara.holster = 14;
		break;
	case 3:
		lara.holster = 15;
		break;
	case 2:
		lara.holster = 16;
		break;
	}
}

void undraw_pistol_mesh_left(int weapon_type)//448F0(<), 44D54(<) (F)
{
	if(weapon_type != 2)
	{
		WeaponObject(weapon_type);
		lara.mesh_ptrs[LM_LHAND] = meshes[objects[LARA].mesh_index + 26];
		switch (weapon_type)
		{
		case 1:
			lara.holster = 14;
			break;
		case 3:
			lara.holster = 15;
			break;
		}
	}
}

void draw_pistol_meshes(int weapon_type)
{
	S_Warn("[draw_pistol_meshes] - Unimplemented!\n");
}

void ready_pistols(int weapon_type)
{
	S_Warn("[ready_pistols] - Unimplemented!\n");
}

void undraw_pistols(int weapon_type)
{
	S_Warn("[undraw_pistols] - Unimplemented!\n");
}

void draw_pistols(int weapon_type)
{
	S_Warn("[draw_pistols] - Unimplemented!\n");
}

void set_arm_info(struct lara_arm* arm, int frame)
{
	S_Warn("[set_arm_info] - Unimplemented!\n");
}