#include "DRAW.H"

#include "SPECIFIC.H"
#include "SPECTYPES.H"
#include <stddef.h>

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

long GetFrames(struct ITEM_INFO* item/*$a0*/, short* frames[]/*a1*/, long* rate/*$a2*/)//8582C
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

short* GetBoundsAccurate(struct ITEM_INFO* item/*a0*/)//858F8, 8793C
{
	short* var_10[2];//$a1
	long var_8[2];//$a2
	short* a2;
	int a1;
	if (GetFrames(item, &var_10[0], &var_8[0]) == 0)
	{
		return NULL;// t4;//? Well you can tell this was written by hand in mips, smh, nice optimisation
	}
	

	//loc_8591C
	a2 = &interpolated_bounds[0];
	a1 = 6;

	//loc_85928
#if 0//Error, t5 = unknown, t4 = unknown. probably gonna have to ref
	lh	$v0, 0($t5)
	lh	$a0, 0($t4)
	addiu	$a1, -1
	subu	$v0, $a0
	mult	$v0, $t0
	mflo	$v1
	addiu	$t5, 2
	addiu	$t4, 2
	div	$v1, $a3
	addiu	$a2, 2
	mflo	$v0
	addu	$a0, $v0
	bnez	$a1, loc_85928
	sh	$a0, -2($a2)
	addiu	$v0, $a2, -0xC
#endif

	return NULL;
}

void UpdateSkyLightning()
{
	S_Warn("[UpdateSkyLightning] - Unimplemented!\n");
}

void DrawSkyMesh(short* mesh)
{
	S_Warn("[DrawSkyMesh] - Unimplemented!\n");
}

void DrawFlatSky_ASM(struct CVECTOR colour, short pos, long flags)
{
	S_Warn("[DrawFlatSky_ASM] - Unimplemented!\n");
}

void DrawMoon()
{
	S_Warn("[DrawMoon] - Unimplemented!\n");
}

void DrawGunflashes()
{
	S_Warn("[DrawGunflashes] - Unimplemented!\n");
}

short* GetBestFrame(struct ITEM_INFO* item)// (F)s
{
	short* frm[2];
	long rate;
	const int ret = GetFrames(item, frm, &rate);

	if (ret > (rate >> 1))
		return frm[1];
	else
		return frm[0];
}