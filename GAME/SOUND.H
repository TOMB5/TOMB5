#ifndef SOUND_H
#define SOUND_H

#include "SPECTYPES.H"

#define MAX_SOUND_SLOTS 24

void SayNo();
void SOUND_Init();
void SOUND_Stop();

extern int sound_active;
extern short* sample_lut;
extern struct SAMPLE_INFO* sample_infos;
extern struct SoundSlot LaSlot[MAX_SOUND_SLOTS];

#endif