#include "DRAW.H"

#include "CONTROL.H"
#if PSX_VERSION || PSXPC_VERSION
#include "DRAWSPKS.H"
#include "SETUP.H"
#include "MATHS.H"
#endif

#include "OBJECTS.H"

#include "SPECIFIC.H"
#include "SPECTYPES.H"
#include "TOMB4FX.H"
#include <stddef.h>
//#include <INLINE_O.H>

short LightningSFXDelay;
struct room_info* room;
short number_rooms;
long* bones;
struct ANIM_STRUCT* anims;
struct RANGE_STRUCT* ranges;
struct CHANGE_STRUCT* changes;
short** meshes;
short* commands;
short* frames;
short* binoculars_mesh_ptr;
short* target_mesh_ptr;
short SkyPos;
short SkyPos2;
int number_draw_rooms;
short draw_rooms[100];
int number_dynamics;
long camera_underwater;
long gfMirrorZPlane;
unsigned short LightningRGBs[3];
unsigned short LightningRGB[3];
short LightningCount;
short LightningRand;
short dLightningRand;
short interpolated_bounds[6];
short* GLOBAL_gunflash_meshptr;
int CurrentRoom;
unsigned char CreditsDone;
short GlobalRoomNumber;
long outside;
long outside_left;
long outside_right;
long outside_top;
long outside_bottom;
short HorizonClip;
struct door_vbuf vbufdoor[4];
short Sback_gun;
short* SRhandPtr;
short* SLhandPtr;

long GetFrames(struct ITEM_INFO* item/*$a0*/, short* frames[]/*a1*/, int* rate/*$a2*/)//8582C
{
	struct ANIM_STRUCT* anim = &anims[item->anim_number];
	int t3;
	short* t4;

	rate[0] = anim->interpolation;

	t3 = ((item->frame_number - anim->frame_base) / anim->interpolation) * anim->interpolation >> 8;
	t4 = &anim->frame_ptr[t3];

	frames[0] = &anim->frame_ptr[t3];
	frames[1] = &t4[anim->interpolation >> 8];
	if (anim->interpolation == 0)
	{
		return 0;
	}

	t3 = ((item->frame_number - anim->frame_base) / anim->interpolation) * anim->interpolation;

	if (!(anim->frame_end < (t3 + anim->interpolation)))
	{
		return (t3 + anim->interpolation) - anim->interpolation;
	}

	rate[0] = anim->frame_end - anim->interpolation;
	return (item->frame_number - anim->frame_base) / anim->interpolation;
}

void UpdateSkyLightning()//2C0D0(<), ? (F)
{
	long lp;

	if (LightningCount > 0)
	{
		--LightningCount;

		if ((LightningCount << 16) == 0)
		{
			LightningRand = (GetRandomDraw() & 0x7F) + 400;
			dLightningRand = 0;
		}
		else
		{
			//loc_2C118
			dLightningRand = (GetRandomDraw() & 0x1FF);
			LightningRand = ((dLightningRand - LightningRand) >> 1) + LightningRand;
		}
	}
	else
	{
		//loc_2C148
		if (LightningRand < 4)
		{
			//loc_2C174
			LightningRand = 0;
		}
		else
		{
			LightningRand = LightningRand - (LightningRand >> 2);
		}
	}

	//loc_2C18C
	for (lp = 2; lp >= 0; lp--)
	{
		LightningRGBs[lp] += ((LightningRGBs[lp] * LightningRand) >> 8);
		if ((LightningRGBs[lp] & 0xFFFF) > 255)
		{
			LightningRGBs[lp] = 255;
		}
	}
}

void DrawSkyMesh(short* mesh)
{
	S_Warn("[DrawSkyMesh] - Unimplemented!\n");
}

void DrawMoon()
{
	S_Warn("[DrawMoon] - Unimplemented!\n");
}

void SetInventoryLighting(struct MATRIX3D* m)
{
	
#if 0
	gte_ReadRotMatrix(m);
	gte_SetRotMatrix(CamGTE);
	//a0 = CamGTE


	li	$v0, 0xF000F000
		li	$v1, 0x1000
		jal	sub_8F348
		addiu	$a0, $gp, 0x4068
		li	$v0, 0xF0001000
		li	$v1, 0xFFFFF000
		jal	sub_8F348
		addiu	$a0, $gp, 0x406E
		lui	$v0, 0x1000
		li	$v1, 0xFFFFF000
		jal	sub_8F348
		addiu	$a0, $gp, 0x4074
		ctc2	$t0, $0
		ctc2	$t1, $1
		ctc2	$t2, $2
		ctc2	$t3, $3
		ctc2	$t4, $4
		andi	$v0, $t5, 0xFF
		sll	$v0, 4
		andi	$v1, $t6, 0xFF
		sll	$v1, 20
		or $v0, $v1
		ctc2	$v0, $16
		andi	$v0, $t7, 0xFF
		sll	$v0, 4
		andi	$v1, $t5, 0xFF00
		sll	$v1, 12
		or $v0, $v1
		ctc2	$v0, $17
		sra	$v0, $t6, 4
		andi	$v0, 0xFF0
		andi	$v1, $t7, 0xFF00
		sll	$v1, 12
		or $v0, $v1
		ctc2	$v0, $18
		sra	$v0, $t5, 12
		andi	$v0, 0xFF0
		sra	$v1, $t6, 12
		andi	$v1, 0xFF0
		sll	$v1, 16
		or $v0, $v1
		ctc2	$v0, $19
		sra	$v0, $t7, 12
		andi	$v0, 0xFF0
		ctc2	$v0, $20
		andi	$a0, $t8, 0xFF
		sll	$a0, 4
		sra	$a1, $t8, 4
		andi	$a1, 0xFF0
		sra	$a2, $t8, 12
		andi	$a2, 0xFF0
		ctc2	$a0, $13
		ctc2	$a1, $14
		ctc2	$a2, $15
		li	$v0, 0x808080
		mtc2	$v0, $6
		ctc2	$zero, $28
		jr	$t9
#endif

}

void DrawGunflashes()//8A924(<) 8C968(<) (F)
{
#ifdef PC_VERSION
	S_Warn("[DrawGunflashes] - Unimplemented!\n");
#else
	long rand;
	long i;
	short* mesh;

	if (!Gunflashes[0].on)
	{
		return;
	}

	mPushMatrix();
	rand = (GetRandomDraw() & 0x1F);
	
	/*SetInventoryLighting(((GetRandomDraw() & 0xF) + 72) | 0x4000,
		((GetRandomDraw() & 0xF) + 72) | 0x4000,
		((GetRandomDraw() & 0xF) + 72) | 0x4000,
		rand << 16 | rand << 8 | rand);*/

	for (i = 0; i < 4; i++)
	{
		if (Gunflashes[i].on)
		{
			mCopyMatrix(&Gunflashes[i].matrix);
			//mRotZ(GetRandomDraw() << 1);
			mesh = meshes[objects[GUN_FLASH].mesh_index];
			//phd_PutPolygons(((long*) mesh)[0], -1);
			mesh[16] = 0;
		}
	}

	mPopMatrix();
#endif
}

short* GetBestFrame(struct ITEM_INFO* item)// (F)s
{
	short* frm[2];
	int rate;
	const int ret = GetFrames(item, frm, &rate);

	if (ret > (rate >> 1))
		return frm[1];
	else
		return frm[0];
}