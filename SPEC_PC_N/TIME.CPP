#include "TIME.H"
#define _X86_
#include <profileapi.h>
#include "STYPES.H"
#include "INCLUDE.H"

double LdSync, LdFreq;
LARGE_INTEGER LdUnk;

void TIME_Reset()// (F)
{
	QueryPerformanceCounter(&LdUnk);
}

bool TIME_Init()// (F)
{
	Log(LT_Enter, "TIME_Init");

	LARGE_INTEGER freq;

	if (!QueryPerformanceFrequency(&freq))
		return false;

	LdFreq = freq.QuadPart / 60.0;

	TIME_Reset();

	return true;
}

int Sync()// (F)
{
	int nFrames;
	LARGE_INTEGER ct;
	double dCounter;
	QueryPerformanceCounter(&ct);
	dCounter = (double)ct.LowPart + (double)ct.HighPart*(double)0xffffffff;
	dCounter /= LdFreq;
	nFrames = long(dCounter) - long(LdSync);
	LdSync = dCounter;
	return nFrames;
}