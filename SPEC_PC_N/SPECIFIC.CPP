#define _X86_
#define _USE_32BIT_TIME_T
#include <cstddef>
#include <time.h>
#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <debugapi.h>
#include "STYPES.H"
#include "INCLUDE.H"
#include "SPECTYPES.H"
#include "SOUND.H"
#include "DS.H"

#ifdef __cplusplus
extern "C" {
#endif

void S_Warn(const char* warning_message, ...)
{
	char buf[1024];
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);

	sprintf(buf, "[%02d:%02d:%02d] ", tm.tm_hour, tm.tm_min, tm.tm_sec);

	va_list argptr;
	va_start(argptr, warning_message);
	vsprintf(buf, warning_message, argptr);
	va_end(argptr);

	int len = strlen(buf);
	if (buf[len - 1] != '\n')
	{
		buf[len] = '\n';
		buf[len + 1] = 0;
	}

	OutputDebugString(buf);
	printf(buf);
}

void S_CDPlay(sint16 nTrack, int tMode)
{
	Log(LT_Enter, "S_CDPlay: nTrack=%d; tMode=%d", nTrack, tMode);

	//if (!Option_Music_Volume)
		return;
/*
#ifndef DUDE_DEMO
#ifndef DEMO
	MCI_PLAY_PARMS pp;
	cdtrack = nTrack;
	nTrack = GetRealTrack(nTrack);

	OpenCD();

	// start track
	pp.dwFrom = MCI_MAKE_TMSF(nTrack, 0, 0, 0);
	pp.dwTo = MCI_MAKE_TMSF(nTrack + 1, 0, 0, 0);
	if (mciSendCommand(wDeviceID, MCI_PLAY, MCI_FROM | MCI_TO, (DWORD)&pp))
		Log(LT_Error, "Can't play track %d", nTrack);

	CloseCD();

	// set looping flag if need be
	if (tMode)
		cd_looping = nTrack;
#endif
#endif
	*/
}

void S_SoundStopSample(sint32 handle)
{
	if (!sound_active)
		return;
	DS_StopSample(handle);
}

void S_SoundStopAllSamples(void)
{
	if (!sound_active)
		return;
	DS_StopAllSamples();
}


#ifdef __cplusplus
}
#endif