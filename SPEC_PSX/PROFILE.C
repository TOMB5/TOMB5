#include "PROFILE.H"

#include "GPU.H"
#include "SPECIFIC.H"

#include <LIBAPI.H>

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

void ProfileCallBack()//6194C, * (F)
{
#ifndef PAELLA
	drawCount = GetRCnt(RCntCNT1) / divisor;
	return;
#endif
}

void ProfileInit(int scale)//61978, * (F)
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

void ProfileStartCount()//61A0C, * (F)
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

void ProfileReadCount()//61A48(<), * (F)
{
#ifndef PAELLA
	int lastCount = currentCount;

	currentCount = GetRCnt(RCntCNT1);

	finalCount = (currentCount - lastCount) / divisor;

	return;
#endif
}

void ProfileAddOT(unsigned long* ot)//61A90, *
{
	int count = 0;//$t0
	long a0;

	//t3 = ot
	if (nummarks > 0)
	{
		//a3 = &db;
		//loc_61AD0
		while (count < nummarks)
		{
			if ((unsigned long) &db.polyptr[0] > (unsigned long)&db.polybuf_limit[0])
			{
				return;
			}

			db.polyptr[3] = 4;
			db.polyptr[7] = 33;
			db.polyptr[4] = 50;
			db.polyptr[5] = 50;
			db.polyptr[6] = 150;
			*(short*) &db.polyptr[10] = 20;
			*(short*) &db.polyptr[14] = 20;
			*(short*) &db.polyptr[18] = 30;

			*(short*) &db.polyptr[12] = count * grid + 29;
			*(short*) &db.polyptr[8] = count * grid + 21;
			*(short*) &db.polyptr[16] = count * grid + 25;

			count++;

			*(long*) &db.polyptr[0] = *(long*) &db.polyptr[0] & 0xFF000000 | ot[0] & 0xFFFFFF;
			*(long*) &ot = ot[0] & 0xFF000000 | (unsigned long) db.polyptr & 0xFFFFFF;
			db.polyptr += 0x14;
		}
	}
	//loc_61B78
#if 0
		slt	$v1, $t0, $v1
		addiu	$v0, 0x14
		bnez	$v1, loc_61AD0
		

		loc_61B78:
		lw	$v0, 0x40D4($gp)
		nop
		blez	$v0, locret_61C8C
		move	$t0, $zero
		lui	$v0, 0xA
		addiu	$t2, $v0, 0x3BF0
		li	$t6, 0x19
		li	$t5, 0x21
		li	$t1, 0xFFFFFF
		lui	$t4, 0xFF00
		li	$t7, 5

		loc_61BA8:
		lw	$a3, 8($t2)
		lw	$v0, 0x10($t2)
		nop
		sltu	$v0, $a3, $v0
		beqz	$v0, locret_61C8C
		li	$v0, 0x29
		sll	$a2, $t0, 3
		addiu	$a0, $gp, 0x40D8
		addu	$a0, $a2, $a0
		sb	$t7, 3($a3)
		sb	$v0, 7($a3)
		lbu	$v0, 0($a0)
		nop
		sb	$v0, 4($a3)
		lbu	$v1, 1($a0)
		addiu	$a1, $gp, 0x40DE
		sb	$v1, 5($a3)
		lbu	$v0, 2($a0)
		addu	$a1, $a2, $a1
		sb	$v0, 6($a3)
		addiu	$v0, $gp, 0x40DC
		lhu	$v1, 0($a1)
		addu	$a2, $v0
		sh	$t6, 0xA($a3)
		sh	$v1, 8($a3)
		lhu	$v1, 0($a1)
		lhu	$v0, 0($a2)
		sh	$t6, 0xE($a3)
		addu	$v1, $v0
		sh	$v1, 0xC($a3)
		lhu	$a0, 0($a1)
		sh	$t5, 0x12($a3)
		sh	$a0, 0x10($a3)
		lhu	$v0, 0($a1)
		lhu	$v1, 0($a2)
		nop
		addu	$v0, $v1
		lw	$v1, 0($a3)
		addiu	$t0, 1
		sh	$t5, 0x16($a3)
		sh	$v0, 0x14($a3)
		lw	$v0, 0($t3)
		and $v1, $t4
		and	$v0, $t1
		or $v1, $v0
		and	$v0, $a3, $t1
		sw	$v1, 0($a3)
		lw	$a0, 0($t3)
		lw	$v1, 0x40D4($gp)
		and $a0, $t4
		or $a0, $v0
		sw	$a0, 0($t3)
		lw	$v0, 8($t2)
		slt	$v1, $t0, $v1
		addiu	$v0, 0x18
		bnez	$v1, loc_61BA8
		sw	$v0, 8($t2)

		locret_61C8C:
	jr	$ra
		nop
#endif
	S_Warn("[ProfileAddOT] - Unimplemented!\n");
}

void ProfileRGB(int r, int g, int b)//61C94, * (F)
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
	//char count;//$a2
	S_Warn("[ProfileAddDrawOT] - Unimplemented!\n");
}


