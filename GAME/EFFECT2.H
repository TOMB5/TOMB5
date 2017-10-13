#ifndef EFFECT2_H
#define EFFECT2_H

#include "SPECTYPES.H"

extern long wibble;
extern long SplashCount;
extern long KillEverythingFlag;
extern long next_spark;
extern unsigned char TES_extra_tab[6];
extern long DeadlyBounds[6];
extern SPLASH_splashes[4];
extern RIPPLE_ripples[32];
extern DYNAMIC dynamics[64];
extern SPLASH_SETUP splash_setup;
extern SP_DYNAMIC spark_dynamics[8];
extern long SmokeWeapon;
extern long SmokeWindX;
extern long SmokeWindZ;
extern long SmokeCountL;
extern long SmokeCountR;
extern SPARKS spark[128];
extern short angle;

extern void ControlEnemyMissile(short fx_number);
extern void ControlSmokeEmitter(short item_number);
extern void KillEverything();
extern void KillAllCurrentItems(short item_number);
extern void TriggerDartSmoke(long x, long y, long z, long xv, long zv, long hit);
extern void TriggerWaterfallMist(long x, long y, long z, long angle);
extern void TriggerSuperJetFlame(ITEM_INFO* item, long yvel, long deadly);
extern void DetatchSpark(long num, long type);
extern void TriggerGunSmoke(long x, long y, long z, long xv, long yv, long zv, int arg7, int arg8, int arg9);
extern void TriggerDynamic(long x, long y, long z, int a4, int a5, int a6, int a7);

#endif