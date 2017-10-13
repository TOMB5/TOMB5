#ifndef EFFECTS_H
#define EFFECTS_H

#include "SPECTYPES.H"

extern long wf;
extern short next_fx_free;
extern short next_fx_active;
extern int number_sound_effects;
extern OBJECT_VECTOR* sound_effects;
extern FX_INFO* effects;

extern void TL_12(ITEM_INFO* item);
extern void TL_11(ITEM_INFO* item);
extern void TL_10(ITEM_INFO* item);
extern void TL_9(ITEM_INFO* item);
extern void TL_8(ITEM_INFO* item);
extern void TL_7(ITEM_INFO* item);
extern void TL_6(ITEM_INFO* item);
extern void TL_5(ITEM_INFO* item);
extern void TL_4(ITEM_INFO* item);
extern void TL_3(ITEM_INFO* item);
extern void TL_2(ITEM_INFO* item);
extern void TL_1(ITEM_INFO* item);
extern void ClearSpidersPatch(ITEM_INFO* item);
extern void reset_hair(ITEM_INFO* item);
extern void invisibility_off(ITEM_INFO* item);
extern void invisibility_on(ITEM_INFO* item);
extern void SetFog(ITEM_INFO* item);
extern void shoot_left_gun(ITEM_INFO* item);
extern void shoot_right_gun(ITEM_INFO* item);
extern void lara_hands_free(ITEM_INFO* item);
extern void KillActiveBaddies(ITEM_INFO* item);
extern void ResetTest(ITEM_INFO* item);
extern void LaraLocationPad(ITEM_INFO* item);
extern void LaraLocation(ITEM_INFO* item);
extern void ExplosionFX(ITEM_INFO* item);
extern void SwapCrowbar(ITEM_INFO* item);
extern void ActivateKey(ITEM_INFO* item);
extern void ActivateCamera(ITEM_INFO* item);
extern void PoseidonSFX(ITEM_INFO* item);
extern void RubbleFX(ITEM_INFO* item);
extern void SoundFlipEffect(ITEM_INFO* item);
extern void floor_shake_effect(ITEM_INFO* item);
extern void turn180_effect(ITEM_INFO* item);
extern void finish_level_effect(ITEM_INFO* item);
extern void void_effect(ITEM_INFO* item);
extern void WaterFall(short item_number);
extern void SoundEffects();
extern void SoundEffect(short sfxid, PHD_3DPOS* pos, int arg2);
extern void StopSoundEffect(int arg1);

#endif