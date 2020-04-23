#ifndef DS_H
#define DS_H

#include "SPECTYPES.H"

struct sound_thing
{
	IDirectSoundBuffer* buf;
	int samples_per_sec;
	int samplePlaying;
};

#define NUMBER_SOUND_BUFFERS 256
#define NUMBER_SOUND_PLAY_BUFFERS 32

extern sound_thing LaPlayBuffer[NUMBER_SOUND_PLAY_BUFFERS], L_DSBuffer[NUMBER_SOUND_BUFFERS];

int DS_StartSample(int nSample, int nVolume, int nPitch, int nPan, DWORD dwFlags);

void DS_StopSample(int nHandle);

void DS_StopAllSamples();

void CDDA_SetMasterVolume(int nVolume);

#endif