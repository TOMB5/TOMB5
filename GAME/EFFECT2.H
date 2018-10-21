#ifndef EFFECT2_H
#define EFFECT2_H

#include "SPECTYPES.H"

extern long wibble;
extern long SplashCount;
extern long KillEverythingFlag;
extern long next_spark;
extern unsigned char TES_extra_tab[6];
extern long DeadlyBounds[6];
extern struct SPLASH_STRUCT splashes[4];
extern struct RIPPLE_STRUCT ripples[32];
extern struct DYNAMIC dynamics[64];
extern struct SPLASH_SETUP splash_setup;
extern struct SP_DYNAMIC spark_dynamics[8];
extern long SmokeWeapon;
extern long SmokeWindX;
extern long SmokeWindZ;
extern long SmokeCountL;
extern long SmokeCountR;
extern struct SPARKS spark[128];
extern short angle;

extern void ControlEnemyMissile(short fx_number);
extern void ControlSmokeEmitter(short item_number);
extern void KillEverything();
extern void KillAllCurrentItems(short item_number);
extern void TriggerDartSmoke(long x, long y, long z, long xv, long zv, long hit);
extern void TriggerWaterfallMist(long x, long y, long z, long angle);
extern void TriggerSuperJetFlame(struct ITEM_INFO* item, long yvel, long deadly);
extern void DetatchSpark(long num, long type);
extern void TriggerGunSmoke(long x, long y, long z, long xv, long yv, long zv, int arg7, int arg8, int arg9);
extern void TriggerDynamic(long x, long y, long z, int falloff, int r, int g, int b);
extern void TriggerFireFlame(int x, int y, int z, int fxObj, signed int a5);
extern void TriggerFontFire(struct ITEM_INFO* item, int a2, int a3);
extern void TriggerHydraMissileFlame(struct PHD_VECTOR* pos, long x, long y, long z);
extern void TriggerRomanGodMissileFlame(struct PHD_VECTOR* pos, long fx_number);
extern void TriggerTorpedoSteam(struct PHD_VECTOR *pos, struct PHD_VECTOR *a2, int a3);
extern void TriggerSubMist(struct PHD_VECTOR *pos, struct PHD_VECTOR *a4, int a5);
extern void TriggerEngineEffects();
extern void TriggerAirBubbles();
extern void FlamingHell(struct PHD_VECTOR* pos);

#endif