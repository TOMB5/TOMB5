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
	case WEAPON_PISTOLS:
		lara.holster = LARA_HOLSTERS_PISTOLS;
		break;
	case WEAPON_REVOLVER:
		lara.holster = LARA_HOLSTERS_REVOLVER;
		break;
	case WEAPON_UZI:
		lara.holster = LARA_HOLSTERS_UZIS;
		break;	
	}
}

void undraw_pistol_mesh_left(int weapon_type)//448F0(<), 44D54(<) (F)
{
	if(weapon_type != WEAPON_REVOLVER)
	{
		WeaponObject(weapon_type);
		lara.mesh_ptrs[LM_LHAND] = meshes[objects[LARA].mesh_index + 26];
		switch (weapon_type)
		{
		case WEAPON_PISTOLS:
			lara.holster = LARA_HOLSTERS_PISTOLS;
			break;
		case WEAPON_UZI:
			lara.holster = LARA_HOLSTERS_UZIS;
			break;
		}
	}
}

void draw_pistol_meshes(int weapon_type)
{
	lara.holster = LARA_HOLSTERS;
	lara.mesh_ptrs[LM_RHAND] = meshes[objects[WeaponObjectMesh(weapon_type)].mesh_index + 20];

	if (weapon_type != WEAPON_REVOLVER)
	{
		lara.mesh_ptrs[LM_LHAND] = meshes[objects[WeaponObjectMesh(weapon_type)].mesh_index + 26];
	}
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