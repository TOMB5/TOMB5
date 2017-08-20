#include "TOMB4FX.H"

#include "SPECIFIC.H"

char flare_table[121];
char LaserSightActive;
char LaserSightCol;
long next_fire_spark;
long next_smoke_spark;
long next_gunshell;
long next_bubble;
long next_drip;
long next_blood;
struct NODEOFFSET_INFO NodeOffsets[16]; // offset 0xA0A24
short FlashFadeR;
short FlashFadeG;
short FlashFadeB;
short FlashFader;
short ScreenFade;
short dScreenFade;
short ScreenFadeSpeed;
short ScreenFadeBack;
short ScreenFadedOut;
short ScreenFading;
short FadeScreenHeight;
short DestFadeScreenHeight;
short FadeClipSpeed;
long LaserSightX;
long LaserSightY;
long LaserSightZ;
struct GUNFLASH_STRUCT Gunflashes[4]; // offset 0xA31D8
struct PHD_VECTOR NodeVectors[16]; // offset 0xA3274
struct FIRE_SPARKS fire_spark[20]; // offset 0xA94FC
struct SMOKE_SPARKS smoke_spark[32]; // offset 0xA8F7C
struct GUNSHELL_STRUCT Gunshells[24]; // offset 0xA7DFC
struct BLOOD_STRUCT blood[32]; // offset 0xA88FC
struct BUBBLE_STRUCT Bubbles[40]; // offset 0xA80FC
struct DRIP_STRUCT Drips[32]; // offset 0xA85FC
struct SHOCKWAVE_STRUCT ShockWaves[16]; // offset 0xA7C3C
struct FIRE_LIST fires[32]; // offset 0xA8D7C

void SetFadeClip(short height, short speed)//34A8C(<), 34F8C(<) (F)
{
	DestFadeScreenHeight = height;
	FadeClipSpeed = speed;
}

void SetScreenFadeOut(long fadespeed, long fadeback)//34B14(<), 35014(<) (F)
{
	if (!ScreenFading)
	{
		ScreenFading = 1;
		ScreenFade = 0;
		dScreenFade = 255;
		ScreenFadeSpeed = fadespeed;
		ScreenFadeBack = fadeback;
		ScreenFadedOut = 0;
	}
}

void SetScreenFadeIn(long fadespeed)//34B48(<), 35048(<) (F)
{
	if(!ScreenFading)
	{
		ScreenFading = 1;
		ScreenFade = 255;
		dScreenFade = 0;
		ScreenFadeSpeed = fadespeed;
		ScreenFadedOut = 0;
	}
}
