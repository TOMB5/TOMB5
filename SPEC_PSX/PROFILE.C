#include "PROFILE.H"
#include "SPECIFIC.H"

#include <LIBAPI.H>

static struct SCALE scales[3] =
{
	{ 0x104, 0, 2 },
	{ 0x82, 1, 3 },
	{ 0x41, 2, 5 }
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

void ProfileAddDrawOT(unsigned long *ot)//61D1C, *
{
	S_Warn("[ProfileAddDrawOT] - Unimplemented!\n");
}

void ProfileRGB(int r, int g, int b)//61C94, *
{
	S_Warn("[ProfileRGB] - Unimplemented!\n");
}

void ProfileAddOT(unsigned long *ot)//61A90, *
{
	S_Warn("[ProfileAddOT] - Unimplemented!\n");
}

void ProfileReadCount()//61A48(<), *
{
	int lastCount = currentCount;

	currentCount = GetRCnt(0xF2000001);

	finalCount = (currentCount - lastCount) / divisor;

	return;
}

void ProfileStartCount()//61A0C, *
{
	S_Warn("[ProfileStartCount] - Unimplemented!\n");
}

void ProfileInit(int scale)//61978, ? (F)
{
	grid = scales[scale].xgrid;
	nummarks = scales[scale].nummarks;
	divisor = scales[scale].scalefactor;
	
	EnterCriticalSection();

	EHbl = OpenEvent(0xF2000001, 2, 0x2000, 0);

	EnableEvent(EHbl);

	SetRCnt(0xF2000001, 0xFA00, 0x1000);

	DrawSyncCallback(&ProfileCallBack);

	ExitCriticalSection();

	return;
}

void ProfileCallBack()//6194C, * (F)
{
	drawCount = GetRCnt(0xF2000001) / divisor;
	return;
}