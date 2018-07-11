#include "TIME.H"
#define _X86_
#include <profileapi.h>
#include "STYPES.H"
#include "INCLUDE.H"

double LdFreq;
LARGE_INTEGER LdUnk;

void TIME_Reset()
{
	QueryPerformanceCounter(&LdUnk);
}

bool TIME_Init()
{
	Log(LT_Enter, "TIME_Init");

	LARGE_INTEGER freq;

	if (!QueryPerformanceFrequency(&freq))
		return false;

	LdFreq = freq.QuadPart / 60.0;

	TIME_Reset();

	return true;
}
