#include "TOMB4FX.H"

#include "SPECIFIC.H"
char flare_table[121]; // offset 0x92A6C
char LaserSightActive; // offset 0xA09FC
char LaserSightCol; // offset 0xA09FD
long next_fire_spark; // offset 0xA0A0C
long next_smoke_spark; // offset 0xA0A10
long next_gunshell; // offset 0xA0A18
long next_bubble; // offset 0xA0A1C
long next_drip; // offset 0xA0A20
long next_blood; // offset 0xA0A14
//struct NODEOFFSET_INFO NodeOffsets[16]; // offset 0xA0A24
short FlashFadeR; // offset 0xA0A04
short FlashFadeG; // offset 0xA0A06
short FlashFadeB; // offset 0xA0A08
short FlashFader; // offset 0xA0A0A
short ScreenFade; // offset 0xA09F0
short dScreenFade; // offset 0xA09F2
short ScreenFadeSpeed; // offset 0xA09F4
short ScreenFadeBack; // offset 0xA09F6
short ScreenFadedOut; // offset 0xA09F8
short ScreenFading; // offset 0xA09FA
short FadeScreenHeight; // offset 0xA09FE
short DestFadeScreenHeight; // offset 0xA0A00
short FadeClipSpeed; // offset 0xA0A02
long LaserSightX; // offset 0xA3268
long LaserSightY; // offset 0xA326C
long LaserSightZ; // offset 0xA3270
//struct GUNFLASH_STRUCT Gunflashes[4]; // offset 0xA31D8
//struct PHD_VECTOR NodeVectors[16]; // offset 0xA3274
//struct FIRE_SPARKS fire_spark[20]; // offset 0xA94FC
//struct SMOKE_SPARKS smoke_spark[32]; // offset 0xA8F7C
//struct GUNSHELL_STRUCT Gunshells[24]; // offset 0xA7DFC
//struct BLOOD_STRUCT blood[32]; // offset 0xA88FC
//struct BUBBLE_STRUCT Bubbles[40]; // offset 0xA80FC
//struct DRIP_STRUCT Drips[32]; // offset 0xA85FC
//struct SHOCKWAVE_STRUCT ShockWaves[16]; // offset 0xA7C3C
//struct FIRE_LIST fires[32]; // offset 0xA8D7C

void SetFadeClip(short height, short speed)
{
	S_Warn("[SetFadeClip] - Unimplemented!");
}

void SetScreenFadeOut(long fadespeed, long fadeback)
{
	S_Warn("[SetScreenFadeOut] - Unimplemented!");
}