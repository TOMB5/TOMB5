#include "LARA2GUN.H"

#include "SPECIFIC.H"
#include "LARA.H"
#include "LARAFIRE.H"
#ifdef PC_VERSION
#include "GAME.H"
#else
#include "SETUP.H"
#include "PSXINPUT.H"
#endif
#include "DRAW.H"
#include "OBJECTS.H"
#include "EFFECTS.H"
#include "CONTROL.H"
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

void undraw_pistols(int weapon_type /*s3*/)//444A4
{
	struct PISTOL_DEF* p; // $s2
	short anil; // $s1
	short anir; // $s0

	//a3 = lara
	//v1 = lara.gun_type
	anil = lara.left_arm.frame_number;
	p = &PistolTable[lara.gun_type];
	//a1 = p->RecoilAnim

	//a1 = anil < p->RecoilAnim
	if (anil >= p->RecoilAnim)
	{
		anil = p->Draw1Anim2;
	}
	else
	{
		//loc_44508
		if (anil > 0 && anil < p->Draw1Anim)
		{
			//v0 = p->Draw1Anim
			//v0 = anil < p->Draw1Anim ? 1 : 0
			//v0 = anil - 1
			//v1 = lara.left_arm.x_rot
			//a0 = lara.left_arm.y_rot / anil
			//a1 = lara.left_arm.y_rot
			lara.left_arm.x_rot -= lara.left_arm.x_rot / anil;
			lara.left_arm.y_rot -= lara.left_arm.y_rot / anil;
			anil = anil - 1;
		}
		else
		{
			//loc_44584
			//v0 = lara
			if (anil == 0)
			{
				lara.left_arm.z_rot = 0;
				lara.left_arm.y_rot = 0;
				lara.left_arm.x_rot = 0;
				anil = p->RecoilAnim - 1;
			}
			else
			{
				//loc_445A4
				//v0 = p->Draw1Anim
				if (p->Draw1Anim < anil && anil < p->RecoilAnim)
				{
					//v0 = p->RecoilAnim
					anil -= 1;
					//v1 = p->Draw2Anim - 1
					if (anil == p->Draw2Anim - 1)
					{
						undraw_pistol_mesh_left(weapon_type);
						SoundEffect(SFX_LARA_HOLSTER_AWAY, &lara_item->pos, 0);
					}
				}
			}
		}
	}
	//loc_44608
	//s0 = &lara.left_arm
	set_arm_info(&lara.left_arm, anil);
	//a2 = &lara
	anir = lara.right_arm.frame_number;
	//v0 = p->RecoilAnim

	if (anir >= p->RecoilAnim)
	{
		anir = p->Draw1Anim2;
	}
	else
	{
		//loc_44640
		if (anir > 0 && anir < p->Draw1Anim)
		{
			//v0 = p->Draw1Anim
			//v0 = lara.right_arm.x_rot / anir
			lara.right_arm.x_rot -= lara.right_arm.x_rot / anir;
			//a0 = lara.right_arm.y_rot / anir
			lara.right_arm.y_rot -= lara.right_arm.y_rot / anir;
			anir = anir - 1;
		}
		else
		{
			//v0 = &lara
			//loc_446BC
			if (anir == 0)
			{
				//v1 = p->RecoilAnim
				lara.right_arm.z_rot = 0;
				lara.right_arm.y_rot = 0;
				lara.right_arm.x_rot = 0;
				anir = p->RecoilAnim - 1;
			}
			else
			{
				//loc_446DC
				//v0 = p->Draw1Anim
				if (p->Draw1Anim < anir && anir < p->RecoilAnim)
				{
					//v0 = p->RecoilAnim
					anir -= 1;

					if (anir == p->Draw2Anim - 1)
					{
						undraw_pistol_mesh_right(weapon_type);
						SoundEffect(SFX_LARA_HOLSTER_AWAY, &lara_item->pos, 0);
					}
				}
				//loc_44740
			}
		}
	}

	//s3 = &lara.right_arm
	set_arm_info(&lara.right_arm, anir);

	//v0 = p->Draw1Anim
	if (anil == p->Draw1Anim && anir == p->Draw1Anim)
	{
		lara.gun_status = 0;
		lara.left_arm.frame_number = 0;
		lara.right_arm.frame_number = 0;
		lara.target = NULL;
		lara.right_arm.lock = 0;
		lara.left_arm.lock = 0;
	}
	//loc_44780

	if (!(input & IN_LOOK))
	{
		//a2 = &lara
		//v1 = lara.left_arm.y_rot
		if (lara.left_arm.y_rot + lara.right_arm.y_rot < 0)
		{
			lara.head_y_rot = (lara.left_arm.y_rot + lara.right_arm.y_rot + 3) >> 2;
			lara.torso_y_rot = (lara.left_arm.y_rot + lara.right_arm.y_rot + 3) >> 2;
		}
		else
		{
			//loc_447B4
			lara.head_y_rot = (lara.left_arm.y_rot + lara.right_arm.y_rot) >> 2;
			lara.torso_y_rot = (lara.left_arm.y_rot + lara.right_arm.y_rot) >> 2;
		}

		//a0 = lara.left_arm.x_rot
		//v1 = lara.right_arm.x_rot
		if (lara.left_arm.x_rot + lara.right_arm.x_rot < 0)
		{
			lara.head_x_rot = (lara.left_arm.x_rot + lara.right_arm.x_rot + 3) >> 2;
			lara.torso_x_rot = (lara.left_arm.x_rot + lara.right_arm.x_rot + 3) >> 2;
		}
		else
		{
			lara.head_x_rot = (lara.left_arm.x_rot + lara.right_arm.x_rot) >> 2;
			lara.torso_x_rot = (lara.left_arm.x_rot + lara.right_arm.x_rot) >> 2;
		}
	}
	//loc_447E4
}

void draw_pistols(int weapon_type)//443B4, 44818 (F)
{
	struct PISTOL_DEF* p = &PistolTable[lara.gun_type];//$a1
	short ani = lara.left_arm.frame_number + 1;//$s1

	//a3 = p->Draw1Anim

	//v0 = p->RecoilAnim
	if (ani < p->Draw1Anim || p->RecoilAnim - 1 < ani)
	{
		//loc_44420
		ani = p->Draw1Anim;
	}
	else
	{

		//loc_44428
		if (ani == p->Draw2Anim)
		{
			draw_pistol_meshes(weapon_type);
			//a1 = lara_item
			//a0 = 6
			//a2 = 0;
			SoundEffect(SFX_LARA_HOLSTER_DRAW, &lara_item->pos, 0);
			//s0 = &lara.right_arm.frame_base
		}//loc_44460
		else if (ani == p->RecoilAnim - 1)
		{
			ready_pistols(weapon_type);
			ani = 0;
		}
	}

	set_arm_info(&lara.right_arm, ani);
	set_arm_info(&lara.left_arm, ani);
}

void set_arm_info(struct lara_arm* arm/*a3*/, int frame/*a1*/)//44308, 4476C (F)
{
	struct PISTOL_DEF* def = &PistolTable[lara.gun_type];//$a2
	int anim_base = objects[def->ObjectNum].anim_index;//$a0

	if (frame < def->Draw1Anim)
	{
		arm->anim_number = anim_base;
		//j loc_44388
	}
	else
	{
		//loc_44358
		if (frame >= def->Draw2Anim)
		{
			if (frame >= def->RecoilAnim)
			{
				//loc_44384
				arm->anim_number = anim_base + 3;
			}
			else
			{
				//loc_44384
				arm->anim_number = anim_base + 2;
			}
		}
		else
		{
			//loc_44384
			arm->anim_number = anim_base + 1;
		}
	}

	arm->frame_number = frame;
	arm->frame_base = anims[arm->anim_number].frame_ptr;
}
