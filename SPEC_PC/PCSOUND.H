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
extern WAVEFORMATEX stru_86BEC8;
extern ACMSTREAMHEADER stru_86BE70;
void* dword_86CC78;
void* dword_86BEDC;
MMRESULT dword_86BEC4;
LPDIRECTSOUNDBUFFER* dword_86BEF0;
int* dword_86BEF4;
DWORD numSampleInfos;
extern char ResetSoundThings();
extern void FreeSoundThings();
extern void StreamOpen();
extern char __cdecl DXCreateSampleADPCM(char *a1, int a2, int a3, int a4);
extern char StreamClose();
extern int DXDSCreate();
extern void InitACM();

#endif