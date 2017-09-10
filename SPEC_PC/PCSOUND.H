#ifndef PCSOUND_H
#define PCSOUND_H

#include "SPECIFIC.H"
#include "MMREG.H"
#include <MSAcm.h>

#include <dsound.h>


#pragma pack(push, 1)
struct sound_shit
{
	LPDIRECTSOUNDBUFFER buf; // pos 0 s 4
	DWORD field1; // pos 4 s 8
	DWORD field2; // pos 8 s 4
};
#pragma pop

struct sound_shit samples[32];

DWORD bufLockLength;
LPDIRECTSOUNDBUFFER other_buf;
LPDIRECTSOUNDNOTIFY notify_thing;
DWORD bufMaxLength;
HACMSTREAM has;
BYTE* buf_lockAudioPtr1;
DWORD buf_lockAudioBytes1;
DWORD pdwOutputBytes;
ACMSTREAMHEADER acmHeader1;
ACMSTREAMHEADER acmHeader2;
ACMSTREAMHEADER acmHeader3;
ACMSTREAMHEADER acmHeader4;

BYTE ACMInited;
HACMDRIVERID hadid;
HACMDRIVER had;
BYTE* bufSource;
void* ptr;
WAVEFORMATEX pwfxDst;
extern WAVEFORMATEX pwfxSrc;

extern char ResetSoundThings();
extern void FreeSoundThings();

#endif