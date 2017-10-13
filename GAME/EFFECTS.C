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
OBJECT_VECTOR* sound_effects;
FX_INFO* effects;

void TL_12(ITEM_INFO* item)//39E3C, 3A33C
{
	if (savegame.TLCount == 11)
	{
		IsAtmospherePlaying = 0;
		S_CDPlay(CDA_XA5_TL_12, 0);
		savegame.TLCount = 12;
	}
}

void TL_11(ITEM_INFO* item)//39DF0, 3A2F0
{
	if (savegame.TLCount == 10)
	{
		IsAtmospherePlaying = 0;
		S_CDPlay(CDA_XA1_TL_10B, 0);
		savegame.TLCount = 11;
	}
}

void TL_10(ITEM_INFO* item)//39DA4, 3A2A4
{
	if (savegame.TLCount == 9)
	{
		IsAtmospherePlaying = 0;
		S_CDPlay(CDA_XA2_TL_10A, 0);
		savegame.TLCount = 10;
	}
}

void TL_9(ITEM_INFO* item)//39D54, 3A254
{
	if (savegame.TLCount < 9)
	{
		IsAtmospherePlaying = 0;
		S_CDPlay(CDA_XA1_TL_11, 0);
		savegame.TLCount = 9;
	}
}

void TL_8(ITEM_INFO* item)//39D04, 3A204
{
	if (savegame.TLCount < 8)
	{
		IsAtmospherePlaying = 0;
		S_CDPlay(CDA_XA1_TL_08, 0);
		savegame.TLCount = 8;
	}
}

void TL_7(ITEM_INFO* item)//39CB4, 3A1B4
{
	if (savegame.TLCount < 7)
	{
		IsAtmospherePlaying = 0;
		S_CDPlay(CDA_XA7_TL_07, 0);
		savegame.TLCount = 7;
	}
}

void TL_6(ITEM_INFO* item)//39C64, 3A164
{
	if (savegame.TLCount < 6)
	{
		IsAtmospherePlaying = 0;
		S_CDPlay(CDA_XA3_TL_06, 0);
		savegame.TLCount = 6;
	}
}

void TL_5(ITEM_INFO* item)//39C14, 3A114
{
	if (savegame.TLCount < 5)
	{
		IsAtmospherePlaying = 0;
		S_CDPlay(CDA_XA1_TL_05, 0);
		savegame.TLCount = 5;
	}
}

void TL_4(ITEM_INFO* item)//39BC4, 3A0C4
{
	if (savegame.TLCount < 4)
	{
		IsAtmospherePlaying = 0;
		S_CDPlay(CDA_XA5_TL_04, 0);
		savegame.TLCount = 4;
	}
}

void TL_3(ITEM_INFO* item)//39B74, 3A074
{
	if (savegame.TLCount < 3)
	{
		IsAtmospherePlaying = 0;
		S_CDPlay(CDA_XA3_TL_03, 0);
		savegame.TLCount = 3;
	}
}

void TL_2(ITEM_INFO* item)//39B24, 3A024
{
	if (savegame.TLCount < 2)
	{
		IsAtmospherePlaying = 0;
		S_CDPlay(CDA_XA1_TL_02, 0);
		savegame.TLCount = 2;
	}
}

void TL_1(ITEM_INFO* item)//39AD8, 39FD8
{
	if (savegame.TLCount < 1)
	{
		IsAtmospherePlaying = 0;
		S_CDPlay(CDA_XA2_TL_01, 0);
		savegame.TLCount = 1;
	}
}

void ClearSpidersPatch(ITEM_INFO* item)//39AA4, 39FA4
{
	S_Warn("[ClearSpidersPatch] - Unimplemented!\n");
}

void reset_hair(ITEM_INFO* item)//39A84(<), 39F84(<) (F)
{
	InitialiseHair();
}

void invisibility_off(ITEM_INFO* item)//39A6C(<), 39F6C(<) (F)
{
	item->status = 1;
}

void invisibility_on(ITEM_INFO* item)//39A58(<), 39F58(<) (F)
{
	item->status = 3;
}

void SetFog(ITEM_INFO* item)//39A44(<), 39F44(<) (F)
{
	flipeffect = -1;
}

void shoot_left_gun(ITEM_INFO* item)//39A34(<), 39F34(<) (F)
{
	lara.left_arm.flash_gun = 3;
}

void shoot_right_gun(ITEM_INFO* item)//39A24(<), 39F24(<) (F)
{
	lara.right_arm.flash_gun = 3;
}

void lara_hands_free(ITEM_INFO* item)//39A18(<), 39F18(<) (F)
{
	lara.gun_status = 0;
}

void KillActiveBaddies(ITEM_INFO* item)//39938(<), 39E38(<) (F)
{
	ITEM_INFO* target_item;
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

void ResetTest(ITEM_INFO* item)//39738, 39C38
{
	S_Warn("[ResetTest] - Unimplemented!\n");
}

void LaraLocationPad(ITEM_INFO* item)//39710(<), 39C10(<) (F)
{
	flipeffect = -1;

	lara.location = TriggerTimer;
	lara.locationPad = TriggerTimer;
}

void LaraLocation(ITEM_INFO* item)//396D0(<), 39BD0(<) (F)
{
	flipeffect = -1;

	lara.location = TriggerTimer;
	if (lara.highest_location < TriggerTimer)
		lara.highest_location = TriggerTimer;
}

void ExplosionFX(ITEM_INFO* item)//39694(<), 39B94(<) (F)
{
	SoundEffect(SFX_EXPLOSION1, NULL, 0);
	camera.bounce = -75;
	flipeffect = -1;
}

void SwapCrowbar(ITEM_INFO* item)//39638(<), 39B38(<) (F)
{
	short* tmp = meshes[objects[LARA].mesh_index + 20];

	if (lara.mesh_ptrs[LM_RHAND] == tmp)
	{
		lara.mesh_ptrs[LM_RHAND] = meshes[objects[CROWBAR_ANIM].mesh_index + 20];
	}
	else lara.mesh_ptrs[LM_RHAND] = tmp;
}

void ActivateKey(ITEM_INFO* item)//39624(<), 39B24(<) (F)
{
	KeyTriggerActive = 1;
}

void ActivateCamera(ITEM_INFO* item)//39610(<), 39B10(<) (F)
{
	KeyTriggerActive = 2;
}

void PoseidonSFX(ITEM_INFO* item)//395E0(<), 39AE0(<) (F)
{
	SoundEffect(238, NULL, 0);
	flipeffect = -1;
}

void RubbleFX(ITEM_INFO* item)//39534(<), 39A34(<) (F)
{
	ITEM_INFO* eq = find_a_fucking_item(EARTHQUAKE);

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

void SoundFlipEffect(ITEM_INFO* item)//39500(<), 39A00(<) (F)
{
	SoundEffect(TriggerTimer, NULL, 0);
	flipeffect = -1;
}

void floor_shake_effect(ITEM_INFO* item)//39410, 39910
{
	S_Warn("[floor_shake_effect] - Unimplemented!\n");
}

void turn180_effect(ITEM_INFO* item)//393F4(<), 398F4(<) (F)
{
	item->pos.y_rot -= ANGLE(180);
	item->pos.x_rot = -item->pos.x_rot;
}

void finish_level_effect(ITEM_INFO* item)//393D4(<), 398D4(<) (F)
{
	gfLevelComplete = gfCurrentLevel + 1;
}

void void_effect(ITEM_INFO* item)//393CC(<), 398CC(<) (F)
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

void SoundEffect(short sfxid, PHD_3DPOS* pos, int arg2)
{
	S_Warn("[SoundEffect] - Unimplemented!\n");
}

void StopSoundEffect(int arg1)
{
	S_Warn("[StopSoundEffect] - Unimplemented!\n");
}
