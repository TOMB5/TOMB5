#ifndef DS_H
#define DS_H

#include "SPECTYPES.H"

int DS_StartSample(int nSample, int nVolume, int nPitch, int nPan, DWORD dwFlags);
void DS_StopSample(int nHandle);
void DS_StopAllSamples();
void CDDA_SetMasterVolume(int nVolume);

#endif