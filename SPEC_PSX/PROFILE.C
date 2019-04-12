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

#if DEBUG_VERSION

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
	int count = 0;

	if (nummarks > 0)
	{
		//loc_61AD0
		for (; count < nummarks; count++)
		{
			if ((unsigned long)db.polyptr < (unsigned long)db.polybuf_limit)
			{
				POLY_F3* ptr = (POLY_F3*)db.polyptr;

				setPolyF3(ptr);
				setShadeTex(ptr, TRUE);

				setRGB0(ptr, 50, 50, 150);

				setXY3(ptr,
					(count * grid) + 21, 20,
					(count * grid) + 29, 20,
					(count * grid) + 25, 30);

				addPrim(ot, ptr);

				db.polyptr += sizeof(POLY_F3);
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
				POLY_F4* ptr = (POLY_F4*)db.polyptr;

				setPolyF4(ptr);
				setShadeTex(ptr, TRUE);

				setRGB0(ptr,
					ProfileInfo[count].r,
					ProfileInfo[count].g,
					ProfileInfo[count].b);

				setXY4(ptr,
					ProfileInfo[count].profile_xcnt, 25,
					ProfileInfo[count].profile_xcnt + ProfileInfo[count].finalcnt, 25,
					ProfileInfo[count].profile_xcnt, 33,
					ProfileInfo[count].profile_xcnt + ProfileInfo[count].finalcnt, 33);

				addPrim(ot, ptr);

				db.polyptr += sizeof(POLY_F4);
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
				POLY_F3* ptr = (POLY_F3*)db.polyptr;

				setPolyF3(ptr);
				setShadeTex(ptr, TRUE);

				setRGB0(ptr, 50, 50, 150);

				setXY3(ptr,
					(count * grid) + 21, 48,
					(count * grid) + 29, 48,
					(count * grid) + 25, 39);

				addPrim(ot, ptr);

				db.polyptr += sizeof(POLY_F3);
			}
			else
			{
				return;
			}
		}
	}

	if ((unsigned long)db.polyptr < (unsigned long)db.polybuf_limit)
	{

		POLY_G4* ptr = (POLY_G4*)db.polyptr;

		setPolyG4(ptr);
		setShadeTex(ptr, TRUE);

		setRGB0(ptr, 0, 200, 0);
		setRGB1(ptr, 200, 0, 0);
		setRGB2(ptr, 0, 200, 0);
		setRGB3(ptr, 200, 0, 0);

		setXY4(ptr,
			25, 36,
			drawCount + 25, 36,
			25, 44,
			drawCount + 25, 44);

		addPrim(ot, ptr);

		db.polyptr += sizeof(POLY_G4);

	}//locret_61EE0
}

#endif