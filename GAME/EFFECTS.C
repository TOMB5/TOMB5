#include "EFFECTS.H"

#include "CAMERA.H"

#include "CONTROL.H"
#include "DELTAPAK.H"
#include "DRAW.H"
#include "GAMEFLOW.H"
#include "HAIR.H"
#include "ITEMS.H"
#include "LARA.H"
#include "LOT.H"
#include "OBJECTS.H"

#include "SAVEGAME.H"
#ifdef PC_VERSION
#include "GAME.H"
#include "GLOBAL.H"
#else
#include "ROOMLOAD.H"
#include "SETUP.H"
#include <SFX.H>
#include "CD.H"
#endif
#include "SOUND.H"
#include "SPECIFIC.H"
#include "SPECTYPES.H"

#include <stddef.h>
#include "TOMB4FX.H"

#include <string.h>

#if PSX_VERSION || PSXPC_VERSION
#include "MISC.H"
#endif


long wf = 256;
short next_fx_free;
short next_fx_active;
int number_sound_effects;
struct OBJECT_VECTOR* sound_effects;
struct FX_INFO* effects;

void(*effect_routines[59])(struct ITEM_INFO* item) =
{
	turn180_effect,
	floor_shake_effect,
	PoseidonSFX,
	LaraBubbles,
	finish_level_effect,
	ActivateCamera,
	ActivateKey,
	RubbleFX,
	SwapCrowbar,
	void_effect,
	SoundFlipEffect,
	ExplosionFX,
	lara_hands_free,
	void_effect,
	void_effect,
	void_effect,
	shoot_right_gun,
	shoot_left_gun,
	void_effect,
	void_effect,
	void_effect,
	invisibility_on,
	invisibility_off,
	void_effect,
	void_effect,
	void_effect,
	reset_hair,
	void_effect,
	SetFog,
	void_effect,
	LaraLocation,
	ClearSpidersPatch,
	AddFootprint,
	ResetTest,
	void_effect,
	void_effect,
	void_effect,
	void_effect,
	void_effect,
	void_effect,
	void_effect,
	void_effect,
	void_effect,
	void_effect,
	void_effect,
	LaraLocationPad,
	KillActiveBaddies,
	TL_1,
	TL_2,
	TL_3,
	TL_4,
	TL_5,
	TL_6,
	TL_7,
	TL_8,
	TL_9,
	TL_10,
	TL_11,
	TL_12,
};

void TL_12(struct ITEM_INFO* item)//39E3C, 3A33C (F)
{
	if (savegame.TLCount == 11)
	{
		IsAtmospherePlaying = 0;
		S_CDPlay(CDA_XA5_TL_12, 0);
		savegame.TLCount = 12;
	}
}

void TL_11(struct ITEM_INFO* item)//39DF0, 3A2F0 (F)
{
	if (savegame.TLCount == 10)
	{
		IsAtmospherePlaying = 0;
		S_CDPlay(CDA_XA1_TL_10B, 0);
		savegame.TLCount = 11;
	}
}

void TL_10(struct ITEM_INFO* item)//39DA4, 3A2A4 (F)
{
	if (savegame.TLCount == 9)
	{
		IsAtmospherePlaying = 0;
		S_CDPlay(CDA_XA2_TL_10A, 0);
		savegame.TLCount = 10;
	}
}

void TL_9(struct ITEM_INFO* item)//39D54, 3A254 (F)
{
	if (savegame.TLCount < 9)
	{
		IsAtmospherePlaying = 0;
		S_CDPlay(CDA_XA1_TL_11, 0);
		savegame.TLCount = 9;
	}
}

void TL_8(struct ITEM_INFO* item)//39D04, 3A204 (F)
{
	if (savegame.TLCount < 8)
	{
		IsAtmospherePlaying = 0;
		S_CDPlay(CDA_XA1_TL_08, 0);
		savegame.TLCount = 8;
	}
}

void TL_7(struct ITEM_INFO* item)//39CB4, 3A1B4 (F)
{
	if (savegame.TLCount < 7)
	{
		IsAtmospherePlaying = 0;
		S_CDPlay(CDA_XA7_TL_07, 0);
		savegame.TLCount = 7;
	}
}

void TL_6(struct ITEM_INFO* item)//39C64, 3A164 (F)
{
	if (savegame.TLCount < 6)
	{
		IsAtmospherePlaying = 0;
		S_CDPlay(CDA_XA3_TL_06, 0);
		savegame.TLCount = 6;
	}
}

void TL_5(struct ITEM_INFO* item)//39C14, 3A114 (F)
{
	if (savegame.TLCount < 5)
	{
		IsAtmospherePlaying = 0;
		S_CDPlay(CDA_XA1_TL_05, 0);
		savegame.TLCount = 5;
	}
}

void TL_4(struct ITEM_INFO* item)//39BC4, 3A0C4 (F)
{
	if (savegame.TLCount < 4)
	{
		IsAtmospherePlaying = 0;
		S_CDPlay(CDA_XA5_TL_04, 0);
		savegame.TLCount = 4;
	}
}

void TL_3(struct ITEM_INFO* item)//39B74, 3A074 (F)
{
	if (savegame.TLCount < 3)
	{
		IsAtmospherePlaying = 0;
		S_CDPlay(CDA_XA3_TL_03, 0);
		savegame.TLCount = 3;
	}
}

void TL_2(struct ITEM_INFO* item)//39B24, 3A024 (F)
{
	if (savegame.TLCount < 2)
	{
		IsAtmospherePlaying = 0;
		S_CDPlay(CDA_XA1_TL_02, 0);
		savegame.TLCount = 2;
	}
}

void TL_1(struct ITEM_INFO* item)//39AD8, 39FD8 (F)
{
	if (savegame.TLCount < 1)
	{
		IsAtmospherePlaying = 0;
		S_CDPlay(CDA_XA2_TL_01, 0);
		savegame.TLCount = 1;
	}
}

void ClearSpidersPatch(struct ITEM_INFO* item)//39AA4(<), 39FA4(<) (F)
{
	ClearSpiders();
}

void reset_hair(struct ITEM_INFO* item)//39A84(<), 39F84(<) (F)
{
	InitialiseHair();
}

void invisibility_off(struct ITEM_INFO* item)//39A6C(<), 39F6C(<) (F)
{
	item->status = ITEM_ACTIVE;
}

void invisibility_on(struct ITEM_INFO* item)//39A58(<), 39F58(<) (F)
{
	item->status = ITEM_INVISIBLE;
}

void SetFog(struct ITEM_INFO* item)//39A44(<), 39F44(<) (F)
{
	flipeffect = -1;
}

void shoot_left_gun(struct ITEM_INFO* item)//39A34(<), 39F34(<) (F)
{
	lara.left_arm.flash_gun = 3;
}

void shoot_right_gun(struct ITEM_INFO* item)//39A24(<), 39F24(<) (F)
{
	lara.right_arm.flash_gun = 3;
}

void lara_hands_free(struct ITEM_INFO* item)//39A18(<), 39F18(<) (F)
{
	lara.gun_status = LG_NO_ARMS;
}

void KillActiveBaddies(struct ITEM_INFO* item)//39938(<), 39E38(<) (F)
{
	struct ITEM_INFO* target_item;
	short item_num;

	if (next_item_active != -1)
	{
		item_num = next_item_active;

		do
		{
			target_item = &items[item_num];

			if (objects[target_item->object_number].intelligent)
			{
				target_item->status = ITEM_INVISIBLE;

				if (*(int*)&item != 0xABCDEF)
				{
					RemoveActiveItem(item_num);
					DisableBaddieAI(item_num);
					target_item->flags |= IFLAG_INVISIBLE;
				}
			}

			item_num = target_item->next_active;
		} while (item_num != -1);
	}

	flipeffect = -1;
}

void ResetTest(struct ITEM_INFO* item)//39738, 39C38
{
	short item_num; // $s1
	short room_num; // $t1
	struct ITEM_INFO* target_item; // $s0

	item_num = next_item_active;
	//v0 = -1
	if (item_num != -1)
	{
		//s2 = &objects

		//loc_39768
		target_item = &items[item_num];
		//v0 = &objects[target_item->object_number];

	}//loc_39914

#if 0
		lw      $v1, 0x30($v0)
		nop
		srl     $v1, 17
		andi    $v1, 1
		beqz    $v1, loc_39904
		move    $a0, $s1
		lw      $v0, 0x84($s0)
		nop
		ori     $v0, 6
		jal     sub_41E98
		sw      $v0, 0x84($s0)
		jal     sub_4DEC0
		move    $a0, $s1
		li      $v0, 0xFFFFC1FF
		lw      $a3, 0x84($s0)
		lhu     $v1, 0x38($s0)
		lhu     $a2, 0x36($s0)
		and $a3, $v0
		andi    $t1, $v1, 0xFF
		sll     $v1, 16
		sra     $v1, 24
		sll     $v1, 8
		sll     $a0, $t1, 2
		addu    $a0, $t1
		lw      $v0, dword_800A24DC
		sll     $a0, 4
		addu    $a0, $v0
		sll     $v0, $a2, 16
		sra     $v0, 24
		sll     $v0, 10
		andi    $a2, 0xFF
		lw      $a1, 0x20($a0)
		sll     $a2, 10
		addu    $v1, $a1
		sw      $v1, 0x44($s0)
		lw      $v1, 0x14($a0)
		lhu     $a1, 0x34($s0)
		addu    $v0, $v1
		addiu   $v0, 0x200
		sll     $v1, $a1, 1
		andi    $v1, 0x3E00
		or $a3, $v1
		sw      $v0, 0x40($s0)
		lw      $t0, 0x1C($a0)
		lhu     $v0, 0x8E($s0)
		lh      $v1, 0xC($s0)
		andi    $a1, 0xFF
		sw      $a3, 0x84($s0)
		sh      $a1, 0x3A($s0)
		addu    $a2, $t0
		addiu   $a2, 0x200
		sh      $v0, 0x4E($s0)
		li      $v0, 0x57
		bne     $v1, $v0, loc_39878
		sw      $a2, 0x48($s0)
		lhu     $v0, 0x15E6($s2)
		j       loc_398BC
		sh      $v0, 0x14($s0)

		loc_39878:
	li      $v0, 0x27
		bne     $v1, $v0, loc_39890
		lui     $v1, 1
		lhu     $v0, 0x9E6($s2)
		j       loc_398B4
		addiu   $v0, 6

		loc_39890:
	lw      $v0, 0x870($s2)
		nop
		and     $v0, $v1
		beqz    $v0, loc_398B0
		nop
		lhu     $v0, 0x866($s2)
		j       loc_398BC
		sh      $v0, 0x14($s0)

		loc_398B0:
	lhu     $v0, 0x966($s2)

		loc_398B4 :
		nop
		sh      $v0, 0x14($s0)

		loc_398BC :
		lh      $a0, 0x14($s0)
		li      $v1, 1
		sh      $v1, 0xE($s0)
		sh      $v1, 0x10($s0)
		lw      $v1, dword_800A25E0
		sll     $v0, $a0, 2
		addu    $v0, $a0
		sll     $v0, 3
		addu    $v0, $v1
		lhu     $a0, 0x18($v0)
		lh      $v1, 0x18($s0)
		nop
		beq     $v1, $t1, loc_39904
		sh      $a0, 0x16($s0)
		move    $a0, $s1
		jal     sub_7C608
		move    $a1, $t1

		loc_39904 :
	lh      $s1, 0x1C($s0)
		li      $v0, 0xFFFFFFFF
		bne     $s1, $v0, loc_39768
		sll     $v1, $s1, 3

		loc_39914 :
		lw      $ra, 0x20 + var_4($sp)
		lw      $s2, 0x20 + var_8($sp)
		lw      $s1, 0x20 + var_C($sp)
		lw      $s0, 0x20 + var_10($sp)
		li      $v0, 0xFFFFFFFF
		sw      $v0, dword_A0724
		jr      $ra
		addiu   $sp, 0x20
#endif
		UNIMPLEMENTED();
}

void LaraLocationPad(struct ITEM_INFO* item)//39710(<), 39C10(<) (F)
{
	flipeffect = -1;

	lara.location = TriggerTimer;
	lara.locationPad = TriggerTimer;
}

void LaraLocation(struct ITEM_INFO* item)//396D0(<), 39BD0(<) (F)
{
	flipeffect = -1;

	lara.location = TriggerTimer;
	if (lara.highest_location < TriggerTimer)
		lara.highest_location = TriggerTimer;
}

void ExplosionFX(struct ITEM_INFO* item)//39694(<), 39B94(<) (F)
{
	SoundEffect(SFX_EXPLOSION1, NULL, 0);
	camera.bounce = -75;
	flipeffect = -1;
}

void SwapCrowbar(struct ITEM_INFO* item)//39638(<), 39B38(<) (F)
{
	short* tmp = meshes[objects[LARA].mesh_index + 2 * LM_RHAND];

	if (lara.mesh_ptrs[LM_RHAND] == tmp)
	{
		lara.mesh_ptrs[LM_RHAND] = meshes[objects[CROWBAR_ANIM].mesh_index + 2 * LM_RHAND];
	}
	else lara.mesh_ptrs[LM_RHAND] = tmp;
}

void ActivateKey(struct ITEM_INFO* item)//39624(<), 39B24(<) (F)
{
	KeyTriggerActive = 1;
}

void ActivateCamera(struct ITEM_INFO* item)//39610(<), 39B10(<) (F)
{
	KeyTriggerActive = 2;
}

void PoseidonSFX(struct ITEM_INFO* item)//395E0(<), 39AE0(<) (F)
{
	SoundEffect(SFX_J_GRAB_OPEN, NULL, 0);
	flipeffect = -1;
}

void RubbleFX(struct ITEM_INFO* item)//39534(<), 39A34(<) (F)
{
	struct ITEM_INFO* eq = find_a_fucking_item(EARTHQUAKE);

	if (eq)
	{
		AddActiveItem(eq - items);
		eq->status = ITEM_ACTIVE;
		eq->flags |= IFLAG_ACTIVATION_MASK;
	}
	else
	{
		camera.bounce = -150;
	}

	flipeffect = -1;
}

void SoundFlipEffect(struct ITEM_INFO* item)//39500(<), 39A00(<) (F)
{
	SoundEffect(TriggerTimer, NULL, 0);
	flipeffect = -1;
}

void floor_shake_effect(struct ITEM_INFO* item)//39410, 39910 (F)
{
	int x = abs(item->pos.x_pos - camera.pos.x);
	int y = abs(item->pos.y_pos - camera.pos.y);     
	int z = abs(item->pos.z_pos - camera.pos.z);

	if (z < SECTOR(16))
	{
		camera.bounce = 66 * ((x * x + y * y + z * z / 256) / SECTOR(1024) - 1);
	}
}

void turn180_effect(struct ITEM_INFO* item)//393F4(<), 398F4(<) (F)
{
	item->pos.y_rot -= ANGLE(180);
	item->pos.x_rot = -item->pos.x_rot;
}

void finish_level_effect(struct ITEM_INFO* item)//393D4(<), 398D4(<) (F)
{
	gfLevelComplete = gfCurrentLevel + 1;
}

void void_effect(struct ITEM_INFO* item)//393CC(<), 398CC(<) (F)
{
}

void WaterFall(short item_number)//39294, 39794
{
	UNIMPLEMENTED();
}

void SoundEffects()//39190(<), 39690 (F)
{
	struct OBJECT_VECTOR* sound;
	int i;

	sound = &sound_effects[0];

	if (number_sound_effects > 0)
	{
		//loc_391B8
		for (i = number_sound_effects; i > 0; i--, sound++)
		{
			//loc_39224
			if ((flip_stats[((sound_effects[i].flags & 0x1F) & 1) | ((sound_effects[i].flags & 0x1F) & 2) + ((((sound_effects[i].flags & 0x1F) >> 2) & 1) << 1) + (((sound_effects[i].flags & 0x1F) >> 2) & 1) + (((sound_effects[i].flags & 0x1F) >> 1) & 4) + (((sound_effects[i].flags & 0x1F) >> 4) << 2) + ((sound_effects[i].flags & 0x1F) >> 4)] & 0x40) || (flip_stats[((sound_effects[i].flags & 0x1F) & 1) | ((sound_effects[i].flags & 0x1F) & 2) + ((((sound_effects[i].flags & 0x1F) >> 2) & 1) << 1) + (((sound_effects[i].flags & 0x1F) >> 2) & 1) + (((sound_effects[i].flags & 0x1F) >> 1) & 4) + (((sound_effects[i].flags & 0x1F) >> 4) << 2) + ((sound_effects[i].flags & 0x1F) >> 4)] & 0x80))///@FIXME Macro
			{
				SoundEffect(sound->data, (struct PHD_3DPOS*)&sound, 0);
			}
			//loc_39238
		}
	}
	//loc_39244
	//v0 = 0x90000
	if (flipeffect != -1)
	{
		effect_routines[flipeffect](NULL);
	}//loc_39274

	SOUND_EndScene();
}

#if PSXPC_VERSION
long SoundEffect(short sample_index, struct PHD_3DPOS* pos, int arg2)//91780(<), 937C4(!)
{
	long r;
	long dx;
	long dy;
	long dz;
	long rx;
	long ry;
	long rz;
	int v0;
	int at = 0;
	int s4;

	struct SVECTOR direction;

#if !INTERNAL
	//lw	$at, 0x3FC($gp)
#endif

#if BETA_VERSION
	if (sound_active)
#else
	if (sound_active && at == 0)
#endif
	{
		//locret_91CEC
		return 0;
	}//locret_93D38

	 //s4 = a2;
	 //s7 = a1;
	if (!(arg2 & 2))
	{
		if ((arg2 & 1) != (room[camera.pos.room_number].flags & 1))
		{
			//loc_91CC4
			return 0;
		}
	}

	//loc_917F0
	//No sound is in the sound wad for this sample index. Get out!
	if (sample_lut[sample_index] == -1)
	{
		sample_lut[sample_index] = -2;
		//loc_91810
		return 0;
	}

	//loc_91818
	if (sample_lut[sample_index] == -2)
	{
		//loc_91CC4
		return 0;
	}

	sizeof(struct SAMPLE_INFO);
#if 0
	s5 = sample_infos[sample_lut[sample_index]];

	if (sample_infos[sample_lut[sample_index]].randomness != 0)
	{
		if (sample_infos[sample_lut[sample_index]].randomness < GetRandomDraw())
		{
			return 0;
		}
	}

	//loc_91854
	t0 = (sample_infos[sample_lut[sample_index]].radius * 1024 + 1024) * (sample_infos[sample_lut[sample_index]].radius * 1024 + 1024);
	//s1 = 0
	if (pos != NULL)
	{
#if 0
		a1 dy = pos->y_pos - camera.pos.y_pos;
		t8 dx = pos->x_pos - camera.pos.x_pos;
		t9 dz = pos->z_pos - camera.pos.z_pos;

		if (dx < -t0 || t0 < t0 || dy < -t0 || dy < t0 || dz < -t0 || dz < t0)
		{
			return 0;
		}

		negu	$v1, $t0

#if PSX_VERSION
			__asm__ volatile ("mtc2 dx, $9");
		__asm__ volatile ("mtc2 dy, $10");
		__asm__ volatile ("mtc2 dz, $11");

		__asm__ volatile ("cop2 0xA00428");
		__asm__ volatile ("mfc2 rx, $25");//moved to v0
		__asm__ volatile ("mfc2 ry, $26");//moved to v1
		__asm__ volatile ("mfc2 rz, $27");//moved to $s3 (0)
#endif

		rx += sy;
		rz += rx;//add all

		if (arg2 < rz)
		{
			return 0;
		}

		if (-1 < rz)
		{
			//loc_9191C
			rz = phd_sqrt_asm(rz) - 1024;
		}
		else
		{
			rz = 0;//s3
		}

		//loc_91928

#endif
	}//loc_91950
#endif

	UNIMPLEMENTED();
}
#endif

void StopSoundEffect(short sample_index)//91FF8(<), 94044(<) (F)
{
	int i;
	short sound_wad_index = sample_lut[sample_index];

	if (sound_active == 0)
	{
		return;
	}

	//loc_92050
	for (i = 0; i < MAX_SOUND_SLOTS; i++)
	{
		if(LaSlot[i].nSampleInfo > sound_wad_index || LaSlot[i].nSampleInfo > sound_wad_index + ((sample_infos[sound_wad_index].flags >> 2) & 0xF))
		{
			LaSlot[i].nSampleInfo = -1;
			S_SoundStopSample(i);
		}
	}
}

void ClearSpiders()// (F)
{
	if (objects[SPIDER].loaded)
	{
		memset(Spiders, 0, 64 * sizeof(struct SPIDER_STRUCT));
		next_spider = 0;
		flipeffect = -1;
	}
}

void LaraBubbles(struct ITEM_INFO* item)// (F)
{
	struct PHD_VECTOR pos;
	int num, i;

	SoundEffect(SFX_LARA_BUBBLES, &item->pos, 1);

	pos.x = 0;

	if (LaraDrawType == LARA_DIVESUIT)
	{
		pos.y = -192;
		pos.z = -160;

		GetLaraJointPos(&pos, 7);
	}
	else
	{
		pos.y = -4;
		pos.z = 64;

		GetLaraJointPos(&pos, 8);
	}

	num = (GetRandomControl() & 1) + 2;

	for (i = 0; i < num; i++)
	{
		CreateBubble(&pos, item->room_number, 8, 7, 0, 0, 0, 0);
	}
}

void AddFootprint(struct ITEM_INFO* item)
{
	UNIMPLEMENTED();
}