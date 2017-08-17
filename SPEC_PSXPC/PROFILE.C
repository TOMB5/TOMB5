#include "PROFILE.H"

#if (WIN32 || WIN64) && 1//Internal
	#include <windows.h>
#endif

static struct SCALE scales[3];
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

void ProfileInit(int scale)//61978, ?
{
#if 0//WIN32 || WIN64
	struct SCALE* s = &scales[scale];
	int v1 = s->xgrid;
	int v0 = s->nummarks;
	int a1 = s->scalefactor;

	grid = v1;
	nummarks = v0;
	divisor = a1;
	EnterCriticalSection();

	li	$a0, 0xF2000001
	li	$a1, 2
	li	$a2, 0x2000
	jal	sub_6A224
	move	$a3, $zero
	sw	$v0, 0x40C0($gp)
	jal	sub_6A214
	move	$a0, $v0
	li	$a0, 0xF2000001
	li	$a1, 0xFA00
	jal	sub_6A0D8
	li	$a2, 0x1000
	lui	$a0, 6
	DrawSyncCallback((void*) ProfileCallBack);
	ExitCriticalSection();
	return;
#endif
}
