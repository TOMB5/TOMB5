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
#include "SETUP.H"
#include "SPECIFIC.H"

#include <stddef.h>


long wf = 256;
short next_fx_free;
short next_fx_active;
int number_sound_effects;
struct OBJECT_VECTOR* sound_effects;
struct FX_INFO* effects;

void TL_12(struct ITEM_INFO* item)//39E3C, 3A33C
{
	S_Warn("[TL_12] - Unimplemented!\n");
}

void TL_11(struct ITEM_INFO* item)//39DF0, 3A2F0
{
	S_Warn("[TL_11] - Unimplemented!\n");
}

void TL_10(struct ITEM_INFO* item)//39DA4, 3A2A4
{
	S_Warn("[TL_10] - Unimplemented!\n");
}

void TL_9(struct ITEM_INFO* item)//39D54, 3A254
{
	S_Warn("[TL_9] - Unimplemented!\n");
}

void TL_8(struct ITEM_INFO* item)//39D04, 3A204
{
	S_Warn("[TL_8] - Unimplemented!\n");
}

void TL_7(struct ITEM_INFO* item)//39CB4, 3A1B4
{
	S_Warn("[TL_7] - Unimplemented!\n");
}

void TL_6(struct ITEM_INFO* item)//39C64, 3A164
{
	S_Warn("[TL_6] - Unimplemented!\n");
}

void TL_5(struct ITEM_INFO* item)//39C14, 3A114
{
	S_Warn("[TL_5] - Unimplemented!\n");
}

void TL_4(struct ITEM_INFO* item)//39BC4, 3A0C4
{
	S_Warn("[TL_4] - Unimplemented!\n");
}

void TL_3(struct ITEM_INFO* item)//39B74, 3A074
{
	S_Warn("[TL_3] - Unimplemented!\n");
}

void TL_2(struct ITEM_INFO* item)//39B24, 3A024
{
	S_Warn("[TL_2] - Unimplemented!\n");
}

void TL_1(struct ITEM_INFO* item)//39AD8, 39FD8
{
	S_Warn("[TL_1] - Unimplemented!\n");
}

void ClearSpidersPatch(struct ITEM_INFO* item)//39AA4, 39FA4
{
	S_Warn("[ClearSpidersPatch] - Unimplemented!\n");
}

void reset_hair(struct ITEM_INFO* item)//39A84(<), 39F84(<) (F)
{
	InitialiseHair();
	return;
}

void invisibility_off(struct ITEM_INFO* item)//39A6C(<), 39F6C(<) (F)
{
	item->status = 1;
	return;
}

void invisibility_on(struct ITEM_INFO* item)//39A58(<), 39F58(<) (F)
{
	item->status = 3;
	return;
}

void SetFog(struct ITEM_INFO* item)//39A44(<), 39F44(<) (F)
{
	flipeffect = -1;
	return;
}

void shoot_left_gun(struct ITEM_INFO* item)//39A34(<), 39F34(<) (F)
{
	lara.left_arm.flash_gun = 3;
	return;
}

void shoot_right_gun(struct ITEM_INFO* item)//39A24(<), 39F24(<) (F)
{
	lara.right_arm.flash_gun = 3;
	return;
}

void lara_hands_free(struct ITEM_INFO* item)//39A18(<), 39F18(<) (F)
{
	lara.gun_status = 0;
	return;
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
				target_item->status = 3;

#if 0//TODO Linux does not like cast from ptr to int.
				if ((int)item != 0xABCDEF)
				{
					RemoveActiveItem(item_num);
					DisableBaddieAI(item_num);
					target_item->flags |= IFLAG_INVISIBLE;
				}
#endif
			}

			item_num = target_item->next_active;
		} while (item_num != -1);
	}

	flipeffect = -1;
}

void ResetTest(struct ITEM_INFO* item)//39738, 39C38
{
	S_Warn("[ResetTest] - Unimplemented!\n");
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
	SoundEffect(105, NULL, NULL);
	camera.bounce = -75;
	flipeffect = -1;
}

void SwapCrowbar(struct ITEM_INFO* item)//39638(<), 39B38(<) (F)
{
	short* tmp = meshes[objects[LARA].mesh_index + 20];

	if (lara.mesh_ptrs[LM_RHAND] == tmp)
	{
		lara.mesh_ptrs[LM_RHAND] = meshes[objects[CROWBAR_ANIM].mesh_index + 20];
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
	SoundEffect(238, NULL, NULL);
	flipeffect = -1;
}

void RubbleFX(struct ITEM_INFO* item)//39534(<), 39A34(<) (F)
{
	struct ITEM_INFO* eq = find_a_fucking_item(EARTHQUAKE);

	if (eq)
	{
		AddActiveItem(eq - items);
		eq->status = 1;
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
	SoundEffect(TriggerTimer, NULL, NULL);
	flipeffect = -1;
}

void floor_shake_effect(struct ITEM_INFO* item)//39410, 39910
{
	S_Warn("[floor_shake_effect] - Unimplemented!\n");
}

void turn180_effect(struct ITEM_INFO* item)//393F4(<), 398F4(<) (F)
{
	item->pos.y_rot -= ANGLE(180);
	item->pos.x_rot = -item->pos.x_rot;
	return;
}

void finish_level_effect(struct ITEM_INFO* item)//393D4(<), 398D4(<) (F)
{
	gfLevelComplete = gfCurrentLevel + 1;
	return;
}

void void_effect(struct ITEM_INFO* item)//393CC(<), 398CC(<) (F)
{
	return;
}

void WaterFall(short item_number)//39294, 39794
{
	S_Warn("[WaterFall] - Unimplemented!\n");
}

void SoundEffects()//39190, 39690
{
	S_Warn("[SoundEffects] - Unimplemented!\n");
}

void SoundEffect(short arg1, struct PHD_3DPOS* pos, void* arg2)
{
	S_Warn("[SoundEffect] - Unimplemented!\n");
}

void StopSoundEffect(int arg1)
{
	S_Warn("[StopSoundEffect] - Unimplemented!\n");
}
