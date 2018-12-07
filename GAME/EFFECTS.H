#ifndef EFFECTS_H
#define EFFECTS_H

#include "SPECTYPES.H"

extern long wf;
extern short next_fx_free;
extern short next_fx_active;
extern int number_sound_effects;
extern struct OBJECT_VECTOR* sound_effects;
extern struct FX_INFO* effects;
extern void(*effect_routines[])(struct ITEM_INFO* item);

extern void TL_12(struct ITEM_INFO* item);
extern void TL_11(struct ITEM_INFO* item);
extern void TL_10(struct ITEM_INFO* item);
extern void TL_9(struct ITEM_INFO* item);
extern void TL_8(struct ITEM_INFO* item);
extern void TL_7(struct ITEM_INFO* item);
extern void TL_6(struct ITEM_INFO* item);
extern void TL_5(struct ITEM_INFO* item);
extern void TL_4(struct ITEM_INFO* item);
extern void TL_3(struct ITEM_INFO* item);
extern void TL_2(struct ITEM_INFO* item);
extern void TL_1(struct ITEM_INFO* item);
extern void reset_hair(struct ITEM_INFO* item);
extern void invisibility_off(struct ITEM_INFO* item);
extern void invisibility_on(struct ITEM_INFO* item);
extern void SetFog(struct ITEM_INFO* item);
extern void shoot_left_gun(struct ITEM_INFO* item);
extern void shoot_right_gun(struct ITEM_INFO* item);
extern void lara_hands_free(struct ITEM_INFO* item);
extern void KillActiveBaddies(struct ITEM_INFO* item);
extern void ResetTest(struct ITEM_INFO* item);
extern void LaraLocationPad(struct ITEM_INFO* item);
extern void LaraLocation(struct ITEM_INFO* item);
extern void ExplosionFX(struct ITEM_INFO* item);
extern void SwapCrowbar(struct ITEM_INFO* item);
extern void ActivateKey(struct ITEM_INFO* item);
extern void ActivateCamera(struct ITEM_INFO* item);
extern void PoseidonSFX(struct ITEM_INFO* item);
extern void RubbleFX(struct ITEM_INFO* item);
extern void SoundFlipEffect(struct ITEM_INFO* item);
extern void floor_shake_effect(struct ITEM_INFO* item);
extern void turn180_effect(struct ITEM_INFO* item);
extern void finish_level_effect(struct ITEM_INFO* item);
extern void void_effect(struct ITEM_INFO* item);
extern void WaterFall(short item_number);
extern void SoundEffects();
extern long SoundEffect(short sample_index, struct PHD_3DPOS* pos, int arg2);
extern void StopSoundEffect(short sample_index);
extern void LaraBubbles(struct ITEM_INFO* item);
extern void AddFootprint(struct ITEM_INFO* item);

#endif