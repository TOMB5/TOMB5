#include "EFFECT2.H"
#include "SPECIFIC.H"

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

void ControlEnemyMissile(short fx_number)//342D0, 347D0
{
	S_Warn("[ControlEnemyMissile] - Unimplemented!\n");
}

void ControlSmokeEmitter(short item_number)//338B8, 33DB8
{
	S_Warn("[ControlSmokeEmitter] - Unimplemented!\n");
}

void KillEverything()//338AC(<), 33DAC(<) (F)
{
	KillEverythingFlag = 0;
}

void KillAllCurrentItems(short item_number)//3389C, 33D9C
{
	S_Warn("[KillAllCurrentItems] - Unimplemented!\n");
}

void TriggerDartSmoke(long x, long y, long z, long xv, long zv, long hit)//335B8, 33AB8
{
	S_Warn("[TriggerDartSmoke] - Unimplemented!\n");
}

void TriggerWaterfallMist(long x, long y, long z, long angle)//331B4, 336B4
{
	S_Warn("[TriggerWaterfallMist] - Unimplemented!\n");
}

void TriggerSuperJetFlame(struct ITEM_INFO *item, long yvel, long deadly)//32EAC, 333AC
{
	S_Warn("[TriggerSuperJetFlame] - Unimplemented!\n");
}

void DetatchSpark(long num, long type)//32D8C, 3328C
{
	S_Warn("[DetatchSpark] - Unimplemented!\n");
}
