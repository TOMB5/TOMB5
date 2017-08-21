#include "EFFECTS.H"
#include "SPECIFIC.H"
#include "CONTROL.H"
#include "GAMEFLOW.H"
#include "LARA.H"

long wf = 256;
short next_fx_free;
short next_fx_active;
int number_sound_effects;
struct OBJECT_VECTOR* sound_effects;
struct FX_INFO* effects;

void TL_12(struct ITEM_INFO *item)//39E3C, 3A33C
{
	S_Warn("[TL_12] - Unimplemented!\n");
}

void TL_11(struct ITEM_INFO *item)//39DF0, 3A2F0
{
	S_Warn("[TL_11] - Unimplemented!\n");
}

void TL_10(struct ITEM_INFO *item)//39DA4, 3A2A4
{
	S_Warn("[TL_10] - Unimplemented!\n");
}

void TL_9(struct ITEM_INFO *item)//39D54, 3A254
{
	S_Warn("[TL_9] - Unimplemented!\n");
}

void TL_8(struct ITEM_INFO *item)//39D04, 3A204
{
	S_Warn("[TL_8] - Unimplemented!\n");
}

void TL_7(struct ITEM_INFO *item)//39CB4, 3A1B4
{
	S_Warn("[TL_7] - Unimplemented!\n");
}

void TL_6(struct ITEM_INFO *item)//39C64, 3A164
{
	S_Warn("[TL_6] - Unimplemented!\n");
}

void TL_5(struct ITEM_INFO *item)//39C14, 3A114
{
	S_Warn("[TL_5] - Unimplemented!\n");
}

void TL_4(struct ITEM_INFO *item)//39BC4, 3A0C4
{
	S_Warn("[TL_4] - Unimplemented!\n");
}

void TL_3(struct ITEM_INFO *item)//39B74, 3A074
{
	S_Warn("[TL_3] - Unimplemented!\n");
}

void TL_2(struct ITEM_INFO *item)//39B24, 3A024
{
	S_Warn("[TL_2] - Unimplemented!\n");
}

void TL_1(struct ITEM_INFO *item)//39AD8, 39FD8
{
	S_Warn("[TL_1] - Unimplemented!\n");
}

void ClearSpidersPatch(struct ITEM_INFO *item)//39AA4, 39FA4
{
	S_Warn("[ClearSpidersPatch] - Unimplemented!\n");
}

void reset_hair(struct ITEM_INFO *item)//39A84, 39F84
{
	S_Warn("[reset_hair] - Unimplemented!\n");
}

void invisibility_off(struct ITEM_INFO *item)//39A6C(<), 39F6C(<) (F)
{
	item->status = 1;
}

void invisibility_on(struct ITEM_INFO *item)//39A58(<), 39F58(<) (F)
{
	item->status = 3;
}

void SetFog(struct ITEM_INFO *item)//39A44(<), 39F44(<) (F)
{
	flipeffect = -1;
}

void shoot_left_gun(struct ITEM_INFO *item)//39A34, 39F34
{
	S_Warn("[shoot_left_gun] - Unimplemented!\n");
}

void shoot_right_gun(struct ITEM_INFO *item)//39A24, 39F24
{
	S_Warn("[shoot_right_gun] - Unimplemented!\n");
}

void lara_hands_free(struct ITEM_INFO *item)//39A18, 39F18
{
	S_Warn("[lara_hands_free] - Unimplemented!\n");
}

void KillActiveBaddies(struct ITEM_INFO *item)//39938, 39E38
{
	S_Warn("[KillActiveBaddies] - Unimplemented!\n");
}

void ResetTest(struct ITEM_INFO *item)//39738, 39C38
{
	S_Warn("[ResetTest] - Unimplemented!\n");
}

void LaraLocationPad(struct ITEM_INFO *item)//39710(<), 39C10(<) (F)
{
	flipeffect = -1;
	lara.location = TriggerTimer;
	lara.locationPad = TriggerTimer;
}

void LaraLocation(struct ITEM_INFO *item)//396D0, 39BD0
{
	S_Warn("[LaraLocation] - Unimplemented!\n");
}

void ExplosionFX(struct ITEM_INFO *item)//39694, 39B94
{
	S_Warn("[ExplosionFX] - Unimplemented!\n");
}

void SwapCrowbar(struct ITEM_INFO *item)//39638, 39B38
{
	S_Warn("[SwapCrowbar] - Unimplemented!\n");
}

void ActivateKey(struct ITEM_INFO *item)//39624(<), 39B24(<) (F)
{
	KeyTriggerActive = 1;
}

void ActivateCamera(struct ITEM_INFO *item)//39610(<), 39B10(<) (F)
{
	KeyTriggerActive = 2;
}

void PoseidonSFX(struct ITEM_INFO *item)//395E0, 39AE0
{
	S_Warn("[PoseidonSFX] - Unimplemented!\n");
}

void RubbleFX(struct ITEM_INFO *item)//39534, 39A34
{
	S_Warn("[RubbleFX] - Unimplemented!\n");
}

void SoundFlipEffect(struct ITEM_INFO *item)//39500, 39A00
{
	S_Warn("[SoundFlipEffect] - Unimplemented!\n");
}

void floor_shake_effect(struct ITEM_INFO *item)//39410, 39910
{
	S_Warn("[floor_shake_effect] - Unimplemented!\n");
}

void turn180_effect(struct ITEM_INFO *item)//393F4(<), 398F4(<) (F)
{
	item->pos.y_rot -= 0x8000;
	item->pos.x_rot = -item->pos.x_rot;
}

void finish_level_effect(struct ITEM_INFO *item)//393D4(<), 398D4(<) (F)
{
	gfLevelComplete = gfCurrentLevel + 1;
}

void void_effect(struct ITEM_INFO *item)//393CC, 398CC
{
	S_Warn("[void_effect] - Unimplemented!\n");
}

void WaterFall(short item_number)//39294, 39794
{
	S_Warn("[WaterFall] - Unimplemented!\n");
}

void SoundEffects()//39190, 39690
{
	S_Warn("[SoundEffects] - Unimplemented!\n");
}
