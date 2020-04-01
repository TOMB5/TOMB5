#include "DELSTUFF.H"

#include "SPECIFIC.H"
#include "LARA.H"
#include "SETUP.H"
#include "DRAW.H"
#include "CALCLARA.H"
#include "COLLIDE.H"
#if PC_VERSION
#include "SETUP.H"
#elif PSX_VERSION || PSXPC_VERSION || SAT_VERSION || PS2_VERSION
#include "MATHS.H"
#endif

struct MATRIX3D lara_joint_matrices[15];
struct MATRIX3D lara_matrices[15];
CVECTOR LaraNodeAmbient[2];
short* GLaraShadowframe;
unsigned char LaraNodeUnderwater[15];
long LaraGlobalClipFlag = -1;

char lara_underwater_skin_sweetness_table[15] =
{
	0, 2, 3, 0, 5, 6, 7, 9, 0xA, 0xB, 0xC, 0xD, 0xE, 8, 0
};

int lara_mesh_sweetness_table[15] =
{
	0, 1, 2, 3, 4, 5, 6, 7, 0xE, 8, 9, 0xA, 0xB, 0xC, 0xD
};

unsigned char SkinUseMatrix[14][2] =
{
	{ 0xFF, 0xFF },
	{ 1, 2 },
	{ 0xFF, 0xFF },
	{ 0xFF, 0xFF },
	{ 4, 5 },
	{ 0xFF, 0xFF },
	{ 0xFF, 0xFF },
	{ 0xFF, 0xFF },
	{ 9, 0xA },
	{ 0xFF, 0xFF },
	{ 0xFF, 0xFF },
	{ 0xC, 0xD },
	{ 0xFF, 0xFF },
	{ 0xFF, 0xFF }
};

char NodesToStashToScratch[14][2] =
{
	{ 1, 3 },
	{ 4, 5 },
	{ 6, 7 },
	{ 2, 8 },
	{ 9, 0xA },
	{ 0xB, 0xC },
	{ 0, 0xD },
	{ 0xE, 0x11 },
	{ 0x12, 0x13 },
	{ 0x14, 0x15 },
	{ 0xF, 0x16 },
	{ 0x17, 0x18 },
	{ 0x19, 0x1A },
	{ 0x10, 0x1B }
};

char NodesToStashFromScratch[15][4] =
{
	{ 0, 1, 2, -1 },
	{ 3, 4, -1, 0 },
	{ 5, 6, -1, 0 },
	{ 7, -1, 0, 0 },
	{ 8, 9, -1, 0 },
	{ 0xA, 0xB, -1, 0 },
	{ 0xC, -1, 0, 0 },
	{ 0xD, 0x10, 0xE, 0xF },
	{ 0x1B, 0x1C, 0x22, -1 },
	{ 0x11, 0x12, -1, 0 },
	{ 0x13, 0x14, -1, 0 },
	{ 0x15, -1, 0, 0 },
	{ 0x16, 0x17, -1, 0 },
	{ 0x18, 0x19, -1, 0 },
	{ 0x1A, -1, 0, 0 }
};

char HairRotScratchVertNums[5][12] =
{
	{ 4, 5, 6, 7, -1, 0, 0, 0, 0, 0, 0, 0 },
	{ 5, 6, 7, 4, -1, 0, 0, 0, 0, 0, 0, 0 },
	{ 6, 7, 4, 5, -1, 0, 0, 0, 0, 0, 0, 0 },
	{ 7, 4, 5, 6, -1, 0, 0, 0, 0, 0, 0, 0 },
	{ 4, 5, 6, 7, -1, 0, 0, 0, 0, 0, 0, 0 }
};

void CalcLaraMatrices(int flag)//2C1DC, 2C504
{
#if PC_VERSION
	auto bone = &bones[objects[lara_item->object_number].bone_index];
	short* frm[2];

	if (lara.hit_direction >= 0)
	{
		int anim = -1;

		switch (lara.hit_direction)
		{
		case NORTH:
			anim = lara.IsDucked ? ANIMATION_LARA_CROUCH_SMASH_BACKWARD : ANIMATION_LARA_AH_FORWARD;
			break;
		case EAST:
			anim = lara.IsDucked ? ANIMATION_LARA_CROUCH_SMASH_RIGHT : ANIMATION_LARA_AH_LEFT;
			break;
		case SOUTH:
			anim = lara.IsDucked ? ANIMATION_LARA_CROUCH_SMASH_FORWARD : ANIMATION_LARA_AH_BACKWARD;
			break;
		case WEST:
			anim = lara.IsDucked ? ANIMATION_LARA_CROUCH_SMASH_LEFT : ANIMATION_LARA_AH_RIGHT;
			break;
		}

		frm[0] = &anims[anim].frame_ptr[lara.hit_frame * (anims[anim].interpolation >> 8)];
	}
	else
	{

		int rate;
		long frac = GetFrames(lara_item, frm, &rate);

		if (frac != 0)
		{
			GLaraShadowframe = GetBoundsAccurate(lara_item);
			DEL_CalcLaraMatrices_Interpolated_ASM(frm[0], frm[1], frac, rate, bone, flag);
			return;
		}
	}

	DEL_CalcLaraMatrices_Normal_ASM(frm[0], bone, flag);

#elif PSX_VERSION || PSXPC_TEST
	struct object_info* object;
	short* frame;
	short* frmptr[2];
	int frac;
	int rate;
	struct ITEM_INFO* item;
	long* bone;
	short spaz;
	struct ANIM_STRUCT* anim;
	int size;

	item = lara_item;
	object = &objects[item->object_number];
	bone = &bones[object->bone_index];

	if (lara.hit_direction < 0)
	{
		frac = GetFrames(item, &frmptr[0], &rate);
		if (frac != 0)
		{
			GLaraShadowframe = GetBoundsAccurate(item);
			DEL_CalcLaraMatrices_Interpolated_ASM(frmptr[0], frmptr[1], frac, rate, bone, flag);
			return;
		}
	}//loc_2C2A4

	//loc_2C294
	//loc_2C2A4
	if (lara.hit_direction >= 0)
	{
		if (lara.hit_direction == 1)
		{
			//loc_2C318
			if (lara.IsDucked)
			{
				spaz = 295;
			}
			else
			{
				spaz = 127;
			}
			//loc_2C34C
		}
		else if (lara.hit_direction == 2)
		{
			//loc_2C2FC
			if (lara.IsDucked)
			{
				spaz = 293;
			}
			else
			{
				spaz = 126;
			}
		}
		else if (lara.hit_direction == 0)
		{
			//loc_2C2E0
			if (lara.IsDucked)
			{
				spaz = 294;
			}
			else
			{
				spaz = 125;
			}
		}
		else
		{
			if (lara.IsDucked)
			{
				spaz = 296;
			}
			else
			{
				spaz = 128;
			}
		}

		//loc_2C34C
		anim = &anims[spaz];
		frame = &anim->frame_ptr[(lara.hit_frame * ((anim->interpolation << 16) >> 24))];
		DEL_CalcLaraMatrices_Normal_ASM(frame, bone, flag);
		return;
	}
	//loc_2C390
	DEL_CalcLaraMatrices_Normal_ASM(frmptr[0], bone, flag);
#endif
}