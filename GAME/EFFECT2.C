#include "EFFECT2.H"

long wibble;
long SplashCount;
long KillEverythingFlag;
long next_spark;
unsigned char TES_extra_tab[6];
long DeadlyBounds[6];
struct SPLASH_STRUCT splashes[4];
struct RIPPLE_STRUCT ripples[32];
struct DYNAMIC dynamics[64];
struct SPLASH_SETUP splash_setup;
struct SP_DYNAMIC spark_dynamics[8];
long SmokeWeapon;
long SmokeWindX;
long SmokeWindZ;
long SmokeCountL;
long SmokeCountR;
struct SPARKS spark[128];