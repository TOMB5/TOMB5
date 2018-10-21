#include "PROFILE.H"

#include "GPU.H"

#include <LIBAPI.H>

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

void ProfileCallBack()//6194C, * (F) (*)
{
#ifndef PAELLA
	drawCount = GetRCnt(RCntCNT1) >> divisor;
	return;
#endif
}

void ProfileInit(int scale)//61978, * (F) (*)
{
#ifndef PAELLA
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
#endif
}

void ProfileStartCount()//61A0C, * (F) (*)
{
#ifndef PAELLA
	ResetRCnt(RCntCNT1);
	StartRCnt(RCntCNT1);

	profile_xcnt = 25;
	currentCount = 0;
	numprof = 0;

	return;
#endif
}

void ProfileReadCount()//61A48(<), * (F) (*)
{
#ifndef PAELLA
	int lastCount = currentCount;

	currentCount = GetRCnt(RCntCNT1);

	finalCount = (currentCount - lastCount) >> divisor;

	return;
#endif
}

void ProfileAddOT(unsigned long* ot)//61A90, * (F)
{
#ifndef PAELLA
	int count;

	if (nummarks > 0)
	{
		//loc_61AD0
		for (count = 0; count < nummarks; count++)
		{
			if ((unsigned long) &db.polyptr[0] > (unsigned long)&db.polybuf_limit[0])
			{
				return;
			}

			setlen(db.polyptr, 4);
			setcode(db.polyptr, 0x21);
			setRGB0((POLY_F3*)db.polyptr, 50, 50, 150);

			*(short*) &db.polyptr[10] = 20;//y0
			*(short*) &db.polyptr[14] = 20;//clut
			*(short*) &db.polyptr[18] = 30;//y1

			*(short*) &db.polyptr[12] = count * grid + 29;
			*(short*) &db.polyptr[8] = count * grid + 21;
			*(short*) &db.polyptr[16] = count * grid + 25;

			*(long*) &db.polyptr[0] = *(long*) &db.polyptr[0] & 0xFF000000 | ot[0] & 0xFFFFFF;
			*(long*) &ot = ot[0] & 0xFF000000 | (unsigned long) db.polyptr & 0xFFFFFF;
			db.polyptr += 0x14;
		}
	}

	//loc_61B78
	if (numprof > 0)
	{
		for (count = 0; count < numprof; count++)
		{
			if ((unsigned long) db.polyptr < (unsigned long) db.polybuf_limit)
			{
				setlen(db.polyptr, 5);
				setcode(db.polyptr, 0x29);
				setRGB0((POLY_F4*)db.polyptr, ProfileInfo[count].r, ProfileInfo[count].g, ProfileInfo[count].b);

				((short*) db.polyptr)[10] = 0x19;
				((short*) db.polyptr)[4] = ProfileInfo[count].profile_xcnt;
				((short*) db.polyptr)[7] = 0x19;
				((short*) db.polyptr)[6] = ProfileInfo[count].profile_xcnt + ProfileInfo[count].finalcnt;
				((short*) db.polyptr)[9] = 0x21;
				((short*) db.polyptr)[8] = ProfileInfo[count].profile_xcnt;
				((short*) db.polyptr)[11] = 0x21;
				((short*) db.polyptr)[10] = ProfileInfo[count].profile_xcnt + ProfileInfo[count].finalcnt;

				((long*) db.polyptr)[0] = (((long*) db.polyptr)[0] & 0xFF000000) | (ot[0] & 0xFFFFFF);
				ot[0] = (ot[0] & 0xFF000000) | ((unsigned long) db.polyptr & 0xFFFFFF);

				db.polyptr += 0x18;
			}
		}
	}
#endif
}

void ProfileRGB(int r, int g, int b)//61C94, * (F)
{
#ifndef PAELLA
	ProfileReadCount();

	ProfileInfo[numprof].r = r;
	ProfileInfo[numprof].g = g;
	ProfileInfo[numprof].b = b;

	ProfileInfo[numprof].finalcnt = finalCount;
	ProfileInfo[numprof].profile_xcnt = profile_xcnt;

	profile_xcnt += finalCount;
	numprof++;
#endif
	return;
}

void ProfileAddDrawOT(unsigned long* ot)//61D1C, *
{
#ifndef PAELLA
	char count = 0;

	if (nummarks > 0)
	{
		//loc_61D5C
		for (count = 0; count < nummarks; count++)
		{
			if ((unsigned long) db.polyptr < (unsigned long) db.polybuf_limit)
			{
				setlen(db.polyptr, 4);
				setcode(db.polyptr, 0x21);
				setRGB0((POLY_F3*)db.polyptr, 50, 50, 150);

				((short*) db.polyptr)[5] = 48;
				((short*) db.polyptr)[3] = 48;
				((short*) db.polyptr)[9] = 39;

				((short*) db.polyptr)[6] = (count * grid) + 0x1D;
				((short*) db.polyptr)[4] = (count * grid) + 0x15;
				((short*) db.polyptr)[8] = (count * grid) + 0x19;

				((long*) db.polyptr)[0] &= 0xFF000000;
				((long*) db.polyptr)[0] |= ot[0] & 0xFFFFFF;

				ot[0] = ot[0] & 0xFF000000 | ((long) db.polyptr & 0xFFFFFF);
				db.polyptr += 0x14;
			}
			else
			{
				//locret_61EE0
				return;
			}
		}
	}

	//loc_61E08
	if ((unsigned long) db.polyptr < (unsigned long) db.polybuf_limit)
	{
		setlen(db.polyptr, 8);
		setcode(db.polyptr, 0x39);
		setRGB0((POLY_G4*)db.polyptr, 0, 200, 0);
		setRGB1((POLY_G4*)db.polyptr, 200, 0, 0);
		setRGB2((POLY_G4*)db.polyptr, 0, 200, 0);
		setRGB3((POLY_G4*)db.polyptr, 200, 0, 0);

		((short*) db.polyptr)[5] = 36;//y0
		((short*) db.polyptr)[9] = 36;
		((short*) db.polyptr)[4] = 25;

		((short*) db.polyptr)[12] = 25;
		((short*) db.polyptr)[13] = 44;
		((short*) db.polyptr)[17] = 44;
		
		((short*) db.polyptr)[8] = drawCount + 25;
		((short*) db.polyptr)[16] = drawCount + 25;

		((long*) db.polyptr)[0] &= 0xFF000000;
		((long*) db.polyptr)[0] |= ot[0] & 0xFFFFFF;

		ot[0] = ot[0] & 0xFF000000 | (long) db.polyptr & 0xFFFFFF;
		db.polyptr += sizeof(POLY_G4);
		
	}
#endif
}


