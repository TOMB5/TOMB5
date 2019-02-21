#include "PROFILE.H"
#include "SPECIFIC.H"

#include "GPU.H"

#include <LIBAPI.H>

static struct SCALE scales[] =
{
	{ 260, 0, 2 },
	{ 130, 1, 3 },
	{ 65,  2, 5 }
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

void ProfileCallBack()//6194C, * (F) (*) (D)
{
	drawCount = GetRCnt(RCntCNT1) >> divisor;
	return;
}

void ProfileInit(int scale)//61978, * (F) (*) (D)
{
	grid = scales[scale].xgrid;
	nummarks = scales[scale].nummarks;
	divisor = scales[scale].scalefactor;

	EnterCriticalSection();
	EHbl = OpenEvent(RCntCNT1, EvSpINT, EvMdNOINTR, NULL);
	EnableEvent(EHbl);
	SetRCnt(RCntCNT1, 64000, RCntMdINTR);

	DrawSyncCallback(&ProfileCallBack);

	ExitCriticalSection();

	return;
}

void ProfileStartCount()//61A0C, * (F) (*) (D)
{
	ResetRCnt(RCntCNT1);
	StartRCnt(RCntCNT1);

	profile_xcnt = 25;
	currentCount = 0;
	numprof = 0;

	return;
}

void ProfileReadCount()//61A48(<), * (F) (*) (D)
{
	int lastCount = currentCount;

	currentCount = GetRCnt(RCntCNT1);

	finalCount = (currentCount - lastCount) >> divisor;

	return;
}

void ProfileAddOT(unsigned long* ot)//61A90, * (F)
{
	int count;

	if (nummarks > 0)
	{
		//loc_61AD0
		for (count = 0; count < nummarks; count++)
		{
			if ((unsigned long)db.polyptr < (unsigned long)db.polybuf_limit)
			{
				((char*)db.polyptr)[3] = 4;
				((char*)db.polyptr)[7] = 33;
				((char*)db.polyptr)[4] = 50;
				((char*)db.polyptr)[5] = 50;
				((char*)db.polyptr)[6] = 150;
				((short*)db.polyptr)[5] = 20;
				((short*)db.polyptr)[7] = 20;
				((short*)db.polyptr)[9] = 30;
				((short*)db.polyptr)[6] = (count * grid) + 29;
				((short*)db.polyptr)[4] = (count * grid) + 21;
				((short*)db.polyptr)[8] = (count * grid) + 25;
				((unsigned long*)db.polyptr)[0] = (((long*)db.polyptr)[0] & 0xFF000000) | (ot[0] & 0xFFFFFF);
				ot[0] = (ot[0] & 0xFF000000) | (unsigned long)db.polyptr & 0xFFFFFF;
				db.polyptr += 0x14;
			}
			else
			{
				//locret_61C8C
				return;
			}
		}
	}
	//loc_61B78
	if (numprof > 0)
	{
		//loc_61BA8
		for (count = 0; count < numprof; count++)
		{
			if ((unsigned long)db.polyptr < (unsigned long)db.polybuf_limit)
			{
				((char*)db.polyptr)[3] = 5;
				((char*)db.polyptr)[7] = 41;
				((char*)db.polyptr)[4] = ProfileInfo[count].r;
				((char*)db.polyptr)[5] = ProfileInfo[count].g;
				((char*)db.polyptr)[6] = ProfileInfo[count].b;
				((short*)db.polyptr)[5] = 25;
				((short*)db.polyptr)[4] = ProfileInfo[count].profile_xcnt;
				((short*)db.polyptr)[7] = 25;
				((short*)db.polyptr)[6] = ProfileInfo[count].profile_xcnt + ProfileInfo[count].finalcnt;
				((short*)db.polyptr)[9] = 33;
				((short*)db.polyptr)[8] = ProfileInfo[count].profile_xcnt;
				((short*)db.polyptr)[11] = 33;
				((short*)db.polyptr)[10] = ProfileInfo[count].profile_xcnt + ProfileInfo[count].finalcnt;
				((unsigned long*)db.polyptr)[0] = (((unsigned long*)db.polyptr)[0] & 0xFF000000) | (ot[0] & 0xFFFFFF);
				ot[0] = (ot[0] & 0xFF000000) | ((unsigned long)db.polyptr & 0xFFFFFF);
				db.polyptr += 0x18;
			}
			else
			{
				return;
			}
		}
	}
}


void ProfileRGB(int r, int g, int b)//61C94, * (F) (D)
{
	ProfileReadCount();

	ProfileInfo[numprof].r = r;
	ProfileInfo[numprof].g = g;
	ProfileInfo[numprof].b = b;

	ProfileInfo[numprof].finalcnt = finalCount;
	ProfileInfo[numprof].profile_xcnt = profile_xcnt;

	profile_xcnt += finalCount;
	numprof++;
	return;
}

void ProfileAddDrawOT(unsigned long* ot)//61D1C, *
{
	char count = 0;

	if (nummarks > 0)
	{
		//loc_61D5C
		for (count = 0; count < nummarks; count++)
		{
			if ((unsigned long)db.polyptr < (unsigned long)db.polybuf_limit)
			{
				((char*)db.polyptr)[3] = 4;
				((char*)db.polyptr)[7] = 33;
				((char*)db.polyptr)[4] = 50;
				((char*)db.polyptr)[5] = 50;
				((char*)db.polyptr)[6] = 150;
				((short*)db.polyptr)[5] = 48;
				((short*)db.polyptr)[7] = 48;
				((short*)db.polyptr)[9] = 39;
				((short*)db.polyptr)[6] = (count * grid) + 29;
				((short*)db.polyptr)[4] = (count * grid) + 21;
				((short*)db.polyptr)[8] = (count * grid) + 25;
				((unsigned long*)db.polyptr)[0] = (((unsigned long*)db.polyptr)[0] & 0xFF000000) | (ot[0] & 0xFFFFFF);
				ot[0] = (ot[0] & 0xFF000000) | (unsigned long)db.polyptr & 0xFFFFFF;
				db.polyptr += 0x14;
			}
			else
			{
				return;
			}
		}
	}

	if ((unsigned long)db.polyptr < (unsigned long)db.polybuf_limit)
	{
		((char*)db.polyptr)[3] = 8;
		((char*)db.polyptr)[7] = 57;
		((char*)db.polyptr)[4] = 0;
		((char*)db.polyptr)[5] = 200;
		((char*)db.polyptr)[6] = 0;
		((char*)db.polyptr)[12] = 200;
		((char*)db.polyptr)[13] = 0;
		((char*)db.polyptr)[14] = 0;
		((char*)db.polyptr)[20] = 0;
		((char*)db.polyptr)[21] = 200;
		((char*)db.polyptr)[22] = 0;
		((char*)db.polyptr)[28] = 200;
		((char*)db.polyptr)[29] = 0;
		((char*)db.polyptr)[30] = 0;
		((short*)db.polyptr)[5] = 36;
		((short*)db.polyptr)[9] = 36;
		((short*)db.polyptr)[4] = 25;
		((short*)db.polyptr)[12] = 25;
		((short*)db.polyptr)[13] = 44;
		((short*)db.polyptr)[17] = 44;
		((short*)db.polyptr)[8] = drawCount + 25;
		((short*)db.polyptr)[16] = drawCount + 25;
		((unsigned long*)db.polyptr)[0] = (((unsigned long*)db.polyptr)[0] & 0xFF000000) | (ot[0] & 0xFFFFFF);
		ot[0] = (ot[0] & 0xFF000000) | ((unsigned long)db.polyptr & 0xFFFFFF);
		db.polyptr += 0x24;

	}//locret_61EE0
}


