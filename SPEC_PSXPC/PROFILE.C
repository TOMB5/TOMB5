#include "PROFILE.H"
#include "SPECIFIC.H"

#if WIN32 || WIN64
	#include <windows.h>
#endif

static struct SCALE scales[3] =
{
	{ 260, 0, 2 },
	{ 130, 1, 3 },
	{ 65, 2, 5 }
};

char ProfileDraw;
int numprof;
static unsigned long EHbl;
static int grid;
static short divisor;
static short nummarks;
static short finalCount;
static short currentCount;
static short drawCount;
static short profile_xcnt;
struct COCKSUCK ProfileInfo[32];

void ProfileAddDrawOT(unsigned long* ot)//61D1C, *
{
	S_Warn("[ProfileAddDrawOT] - Unimplemented!\n");
}

void ProfileRGB(int r, int g, int b)//61C94, *
{
	S_Warn("[ProfileRGB] - Unimplemented!\n");
}

void ProfileAddOT(unsigned long* ot)//61A90, *
{
	S_Warn("[ProfileAddOT] - Unimplemented!\n");
}

void ProfileReadCount()//61A48, *
{
	S_Warn("[ProfileReadCount] - Unimplemented!\n");
}

void ProfileStartCount()//61A0C, *
{
	S_Warn("[ProfileStartCount] - Unimplemented!\n");
}

void ProfileInit(int scale)//61978, ?
{
	S_Warn("[ProfileInit] - Unimplemented!\n");
}

void ProfileCallBack()//6194C, *
{
	S_Warn("[ProfileCallBack] - Unimplemented!\n");
}

