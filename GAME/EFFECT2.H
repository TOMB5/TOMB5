#ifndef EFFECT2_H
#define EFFECT2_H

struct SPARKS
{
	long x; // size=0, offset=0
	long y; // size=0, offset=4
	long z; // size=0, offset=8
	short Xvel; // size=0, offset=12
	short Yvel; // size=0, offset=14
	short Zvel; // size=0, offset=16
	short Gravity; // size=0, offset=18
	short RotAng; // size=0, offset=20
	short Flags; // size=0, offset=22
	unsigned char sSize; // size=0, offset=24
	unsigned char dSize; // size=0, offset=25
	unsigned char Size; // size=0, offset=26
	unsigned char Friction; // size=0, offset=27
	unsigned char Scalar; // size=0, offset=28
	unsigned char Def; // size=0, offset=29
	char RotAdd; // size=0, offset=30
	char MaxYvel; // size=0, offset=31
	unsigned char On; // size=0, offset=32
	unsigned char sR; // size=0, offset=33
	unsigned char sG; // size=0, offset=34
	unsigned char sB; // size=0, offset=35
	unsigned char dR; // size=0, offset=36
	unsigned char dG; // size=0, offset=37
	unsigned char dB; // size=0, offset=38
	unsigned char R; // size=0, offset=39
	unsigned char G; // size=0, offset=40
	unsigned char B; // size=0, offset=41
	unsigned char ColFadeSpeed; // size=0, offset=42
	unsigned char FadeToBlack; // size=0, offset=43
	unsigned char sLife; // size=0, offset=44
	unsigned char Life;
	unsigned char TransType;
	unsigned char extras;
	char Dynamic;
	unsigned char FxObj;
	unsigned char RoomNumber;
	unsigned char NodeNumber;
};

struct DYNAMIC
{
	long x; // size=0, offset=0
	long y; // size=0, offset=4
	long z; // size=0, offset=8
	unsigned char on; // size=0, offset=12
	unsigned char r; // size=0, offset=13
	unsigned char g; // size=0, offset=14
	unsigned char b; // size=0, offset=15
	unsigned short falloff; // size=0, offset=16
	unsigned char used; // size=0, offset=18
	unsigned char pad1[1]; // size=1, offset=19
	long FalloffScale; // size=0, offset=20
};

struct SP_DYNAMIC
{
	unsigned char On; // size=0, offset=0
	unsigned char Falloff; // size=0, offset=1
	unsigned char R; // size=0, offset=2
	unsigned char G; // size=0, offset=3
	unsigned char B; // size=0, offset=4
	unsigned char Flags; // size=0, offset=5
	unsigned char Pad[2]; // size=2, offset=6
};

struct RIPPLE_STRUCT
{
	long x; // size=0, offset=0
	long y; // size=0, offset=4
	long z; // size=0, offset=8
	char flags; // size=0, offset=12
	unsigned char life; // size=0, offset=13
	unsigned char size; // size=0, offset=14
	unsigned char init; // size=0, offset=15
};

struct SPLASH_SETUP
{
	long x; // size=0, offset=0
	long y; // size=0, offset=4
	long z; // size=0, offset=8
	short InnerRad; // size=0, offset=12
	short InnerSize; // size=0, offset=14
	short InnerRadVel; // size=0, offset=16
	short InnerYVel; // size=0, offset=18
	short pad1; // size=0, offset=20
	short MiddleRad; // size=0, offset=22
	short MiddleSize; // size=0, offset=24
	short MiddleRadVel; // size=0, offset=26
	short MiddleYVel; // size=0, offset=28
	short pad2; // size=0, offset=30
	short OuterRad; // size=0, offset=32
	short OuterSize; // size=0, offset=34
	short OuterRadVel; // size=0, offset=36
	short pad3; // size=0, offset=38
};

struct SPLASH_STRUCT
{
	long x; // size=0, offset=0
	long y; // size=0, offset=4
	long z; // size=0, offset=8
	short InnerRad; // size=0, offset=12
	short InnerSize; // size=0, offset=14
	short InnerRadVel; // size=0, offset=16
	short InnerYVel; // size=0, offset=18
	short InnerY; // size=0, offset=20
	short MiddleRad; // size=0, offset=22
	short MiddleSize; // size=0, offset=24
	short MiddleRadVel; // size=0, offset=26
	short MiddleYVel; // size=0, offset=28
	short MiddleY; // size=0, offset=30
	short OuterRad; // size=0, offset=32
	short OuterSize; // size=0, offset=34
	short OuterRadVel; // size=0, offset=36
	char flags; // size=0, offset=38
	unsigned char life; // size=0, offset=39
};

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