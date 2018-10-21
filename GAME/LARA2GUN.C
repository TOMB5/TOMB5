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
#include "EFFECTS.H"
#include "SOUND.H"

static struct PISTOL_DEF PistolTable[4] =
{
	{ LARA, 0, 0, 0, 0 },
	{ PISTOLS_ANIM, 4, 5, 0xD, 0x18 },
	{ REVOLVER_ANIM , 7, 8, 0xF, 0x1D },
	{ UZI_ANIM, 4, 5, 0xD, 0x18 }
};

void AnimatePistols(int weapon_type)
{
	UNIMPLEMENTED();
}

void PistolHandler(int weapon_type)
{
	UNIMPLEMENTED();
}

void undraw_pistol_mesh_right(int weapon_type)//44968(<), 44DCC(<) (F)
{
	WeaponObject(weapon_type);
	lara.mesh_ptrs[LM_RHAND] = meshes[objects[LARA].mesh_index + 2 * LM_RHAND];
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
		lara.mesh_ptrs[LM_LHAND] = meshes[objects[LARA].mesh_index + 2 * LM_LHAND];
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

void draw_pistol_meshes(int weapon_type)// (F)
{
	lara.holster = LARA_HOLSTERS;
	lara.mesh_ptrs[LM_RHAND] = meshes[objects[WeaponObjectMesh(weapon_type)].mesh_index + 2 * LM_RHAND];

	if (weapon_type != WEAPON_REVOLVER)
	{
		lara.mesh_ptrs[LM_LHAND] = meshes[objects[WeaponObjectMesh(weapon_type)].mesh_index + 2 * LM_LHAND];
	}
}

void ready_pistols(int weapon_type)// (F)
{
	lara.gun_status = LG_READY;
	lara.left_arm.z_rot = 0;
	lara.left_arm.y_rot = 0;
	lara.left_arm.x_rot = 0;
	lara.right_arm.z_rot = 0;
	lara.right_arm.y_rot = 0;
	lara.right_arm.x_rot = 0;
	lara.right_arm.frame_number = 0;
	lara.left_arm.frame_number = 0;
	lara.target = 0;
	lara.right_arm.lock = 0;
	lara.left_arm.lock = 0;
	lara.right_arm.frame_base = lara.left_arm.frame_base = objects[WeaponObject(weapon_type)].frame_base;
}

void undraw_pistols(int weapon_type)
{
	UNIMPLEMENTED();
}

void draw_pistols(int weapon_type)// (F)
{
	struct PISTOL_DEF* p = &PistolTable[lara.gun_type];
	short ani = lara.left_arm.frame_number + 1;

	if (ani < p->Draw1Anim || ani > p->RecoilAnim - 1)
	{
		ani = p->Draw1Anim;
	}
	else if (ani == p->Draw2Anim)
	{
		draw_pistol_meshes(weapon_type);
		SoundEffect(SFX_LARA_HOLSTER_DRAW, &lara_item->pos, 0);
	}
	else if (ani == p->RecoilAnim - 1)
	{
		ready_pistols(weapon_type);
		ani = 0;
	}

	set_arm_info(&lara.right_arm, ani);
	set_arm_info(&lara.left_arm, ani);
}

void set_arm_info(struct lara_arm* arm, int frame)// (F)
{
	struct PISTOL_DEF* def = &PistolTable[lara.gun_type];
	int anim_base = objects[def->ObjectNum].anim_index;

	if (frame >= def->Draw1Anim)
	{
		if (frame >= def->Draw2Anim)
		{
			if (frame >= def->RecoilAnim)
			{
				anim_base += 3;
			}
			else
			{
				anim_base += 2;
			}
		}
		else
		{
			anim_base += 1;
		}
	}

	arm->anim_number = anim_base;
	arm->frame_number = frame;
	arm->frame_base = anims[anim_base].frame_ptr;
}