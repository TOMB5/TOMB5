#include "PROFILE.H"
#include "SPECIFIC.H"

#if WIN32 || WIN64
	#include <windows.h>
#endif

static struct SCALE scales[] =
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
	UNIMPLEMENTED();
}

void ProfileRGB(int r, int g, int b)//61C94, *
{
	UNIMPLEMENTED();
}

void ProfileAddOT(unsigned long* ot)//61A90, *
{
	UNIMPLEMENTED();
}

void ProfileReadCount()//61A48, *
{
	UNIMPLEMENTED();
}

void ProfileStartCount()//61A0C, *
{
	UNIMPLEMENTED();
}

void ProfileInit(int scale)//61978, ?
{
	UNIMPLEMENTED();
}

void ProfileCallBack()//6194C, *
{
	UNIMPLEMENTED();
}

