#ifndef TOMB4FX_H
#define TOMB4FX_H

#include "SPECTYPES.H"

extern char flare_table[121]; // offset 0x92A6C
extern char LaserSightActive; // offset 0xA09FC
extern char LaserSightCol; // offset 0xA09FD
extern long next_fire_spark; // offset 0xA0A0C
extern long next_smoke_spark; // offset 0xA0A10
extern long next_gunshell; // offset 0xA0A18
extern long next_bubble; // offset 0xA0A1C
extern long next_drip; // offset 0xA0A20
extern long next_blood; // offset 0xA0A14
extern long next_spider;
extern struct NODEOFFSET_INFO NodeOffsets[16]; // offset 0xA0A24
extern short FlashFadeR; // offset 0xA0A04
extern short FlashFadeG; // offset 0xA0A06
extern short FlashFadeB; // offset 0xA0A08
extern short FlashFader; // offset 0xA0A0A
extern short ScreenFade; // offset 0xA09F0
extern short dScreenFade; // offset 0xA09F2
extern short ScreenFadeSpeed; // offset 0xA09F4
extern short ScreenFadeBack; // offset 0xA09F6
extern short ScreenFadedOut; // offset 0xA09F8
extern short ScreenFading; // offset 0xA09FA
extern short FadeScreenHeight; // offset 0xA09FE
extern short DestFadeScreenHeight; // offset 0xA0A00
extern short FadeClipSpeed; // offset 0xA0A02
extern long LaserSightX; // offset 0xA3268
extern long LaserSightY; // offset 0xA326C
extern long LaserSightZ; // offset 0xA3270
extern struct GUNFLASH_STRUCT Gunflashes[4]; // offset 0xA31D8
extern struct PHD_VECTOR NodeVectors[16]; // offset 0xA3274
extern struct FIRE_SPARKS fire_spark[20]; // offset 0xA94FC
extern struct SMOKE_SPARKS smoke_spark[32]; // offset 0xA8F7C
extern struct GUNSHELL_STRUCT Gunshells[24]; // offset 0xA7DFC
extern struct BLOOD_STRUCT blood[32]; // offset 0xA88FC
extern struct BUBBLE_STRUCT Bubbles[40]; // offset 0xA80FC
extern struct DRIP_STRUCT Drips[32]; // offset 0xA85FC
extern struct SHOCKWAVE_STRUCT ShockWaves[16]; // offset 0xA7C3C
extern struct FIRE_LIST fires[32]; // offset 0xA8D7C

extern void SetFadeClip(short height, short speed);
extern void UpdateFadeClip();
extern void SetScreenFadeOut(long fadespeed, long fadeback);
extern void SetScreenFadeIn(long fadespeed);
extern int GetFreeDrip();
extern int GetFreeSmokeSpark();
extern int GetFreeSpark();
extern int GetFreeBubble();
extern void CreateBubble(struct PHD_VECTOR* pos, short room_num, int a3, int a4, int a5, int a6, int a7, int a8);
extern void TriggerShatterSmoke(int x, int y, int z);
extern void TriggerBlood(int x, int y, int z, int direction, int speed);
extern void TriggerExplosionBubble(int x, int y, int z, short room_num);
extern void TriggerExplosionSparks(int x, int y, int z, int a4, int a5, int a6, short room_no);
extern void Fade();
extern void SetUpLensFlare(long x, long y, long z, struct GAME_VECTOR* bulb);
extern int ExplodingDeath2(short item_number, long mesh_bits, short Flags);
extern void DrawLensFlares(struct ITEM_INFO *item);
extern void TriggerLightningGlow(long x, long y, long z, long rgb);
extern void trig_actor_gunflash(struct MATRIX3D *matrix, struct PHD_VECTOR *pos);
extern void TriggerFenceSparks(long x, long y, long z, long kill, long crane);
extern void ControlElectricFence(short item_number);
extern void ControlTeleporter(short item_number);
extern void DrawWeaponMissile(struct ITEM_INFO *item);
extern void TriggerLaraDrips();
extern void DoBloodSplat(int x, int y, int z, short speed, short direction, short room_num);
extern void TriggerRicochetSpark(struct GAME_VECTOR* pos, int angle, int num, int a4);
extern void Richochet(struct GAME_VECTOR* pos);
extern void TriggerLightning(struct PHD_VECTOR* a1, struct PHD_VECTOR* a2, char a3, int a4, char a5, char a6, char a7);
extern void TriggerCoinGlow();
extern int GetFreeSpider();
extern void TriggerSmallSplash(int x, int y, int z, int num);

#endif