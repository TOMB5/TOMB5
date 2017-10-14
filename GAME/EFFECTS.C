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
#ifdef PC_VERSION
#include "GAME.H"
#else
#include "SETUP.H"
#endif
#include "SPECIFIC.H"

#include <stddef.h>
#include "OBJECTS.H"
#include "SAVEGAME.H"
#include "CD.H"
#include "SOUND.H"


long wf = 256;
short next_fx_free;
short next_fx_active;
int number_sound_effects;
struct OBJECT_VECTOR* sound_effects;
struct FX_INFO* effects;

void TL_12(struct ITEM_INFO* item)//39E3C, 3A33C
{
	if (savegame.TLCount == 11)
	{
		IsAtmospherePlaying = 0;
		S_CDPlay(CDA_XA5_TL_12, 0);
		savegame.TLCount = 12;
	}
}

void TL_11(struct ITEM_INFO* item)//39DF0, 3A2F0
{
	if (savegame.TLCount == 10)
	{
		IsAtmospherePlaying = 0;
		S_CDPlay(CDA_XA1_TL_10B, 0);
		savegame.TLCount = 11;
	}
}

void TL_10(struct ITEM_INFO* item)//39DA4, 3A2A4
{
	if (savegame.TLCount == 9)
	{
		IsAtmospherePlaying = 0;
		S_CDPlay(CDA_XA2_TL_10A, 0);
		savegame.TLCount = 10;
	}
}

void TL_9(struct ITEM_INFO* item)//39D54, 3A254
{
	if (savegame.TLCount < 9)
	{
		IsAtmospherePlaying = 0;
		S_CDPlay(CDA_XA1_TL_11, 0);
		savegame.TLCount = 9;
	}
}

void TL_8(struct ITEM_INFO* item)//39D04, 3A204
{
	if (savegame.TLCount < 8)
	{
		IsAtmospherePlaying = 0;
		S_CDPlay(CDA_XA1_TL_08, 0);
		savegame.TLCount = 8;
	}
}

void TL_7(struct ITEM_INFO* item)//39CB4, 3A1B4
{
	if (savegame.TLCount < 7)
	{
		IsAtmospherePlaying = 0;
		S_CDPlay(CDA_XA7_TL_07, 0);
		savegame.TLCount = 7;
	}
}

void TL_6(struct ITEM_INFO* item)//39C64, 3A164
{
	if (savegame.TLCount < 6)
	{
		IsAtmospherePlaying = 0;
		S_CDPlay(CDA_XA3_TL_06, 0);
		savegame.TLCount = 6;
	}
}

void TL_5(struct ITEM_INFO* item)//39C14, 3A114
{
	if (savegame.TLCount < 5)
	{
		IsAtmospherePlaying = 0;
		S_CDPlay(CDA_XA1_TL_05, 0);
		savegame.TLCount = 5;
	}
}

void TL_4(struct ITEM_INFO* item)//39BC4, 3A0C4
{
	if (savegame.TLCount < 4)
	{
		IsAtmospherePlaying = 0;
		S_CDPlay(CDA_XA5_TL_04, 0);
		savegame.TLCount = 4;
	}
}

void TL_3(struct ITEM_INFO* item)//39B74, 3A074
{
	if (savegame.TLCount < 3)
	{
		IsAtmospherePlaying = 0;
		S_CDPlay(CDA_XA3_TL_03, 0);
		savegame.TLCount = 3;
	}
}

void TL_2(struct ITEM_INFO* item)//39B24, 3A024
{
	if (savegame.TLCount < 2)
	{
		IsAtmospherePlaying = 0;
		S_CDPlay(CDA_XA1_TL_02, 0);
		savegame.TLCount = 2;
	}
}

void TL_1(struct ITEM_INFO* item)//39AD8, 39FD8
{
	if (savegame.TLCount < 1)
	{
		IsAtmospherePlaying = 0;
		S_CDPlay(CDA_XA2_TL_01, 0);
		savegame.TLCount = 1;
	}
}

void ClearSpidersPatch(struct ITEM_INFO* item)//39AA4, 39FA4
{
	S_Warn("[ClearSpidersPatch] - Unimplemented!\n");
}

void reset_hair(struct ITEM_INFO* item)//39A84(<), 39F84(<) (F)
{
	InitialiseHair();
}

void invisibility_off(struct ITEM_INFO* item)//39A6C(<), 39F6C(<) (F)
{
	item->status = 1;
}

void invisibility_on(struct ITEM_INFO* item)//39A58(<), 39F58(<) (F)
{
	item->status = 3;
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
	lara.gun_status = 0;
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
	SoundEffect(SFX_EXPLOSION1, NULL, 0);
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
	SoundEffect(SFX_J_GRAB_OPEN, NULL, 0);
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
	SoundEffect(TriggerTimer, NULL, 0);
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
	S_Warn("[WaterFall] - Unimplemented!\n");
}

void SoundEffects()//39190, 39690
{
	S_Warn("[SoundEffects] - Unimplemented!\n");
}

void SoundEffect(short sfxid, struct PHD_3DPOS* pos, int arg2)
{
	S_Warn("[SoundEffect] - Unimplemented!\n");
}

void StopSoundEffect(int arg1)
{
	S_Warn("[StopSoundEffect] - Unimplemented!\n");
}
