#ifndef SOUND_H
#define SOUND_H

#include "CAMERA.H"

#define MAX_SOUND_SLOTS 24

void SayNo();
void SOUND_Init();
void SOUND_Stop();

struct SAMPLE_INFO
{
	short number;
	unsigned char volume;
	char radius;
	char randomness;
	char pitch;
	short flags;
};

struct SoundSlot
{
	int OrigVolume;
	int nVolume;
	int nPan;
	int nPitch;
	int nSampleInfo;
	unsigned long distance;
	struct PHD_VECTOR pos;
};

extern int sound_active;
extern short* sample_lut;
extern struct SAMPLE_INFO* sample_infos;
extern struct SoundSlot LaSlot[MAX_SOUND_SLOTS];

#endif