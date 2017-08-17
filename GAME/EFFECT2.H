#ifndef EFFECT2_H
#define EFFECT2_H

#include "PSXTYPES.H"


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

#endif