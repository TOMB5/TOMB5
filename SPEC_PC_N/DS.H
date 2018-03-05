#ifndef DS_H
#define DS_H

int DS_StartSample(int nSample, int nVolume, int nPitch, int nPan, DWORD dwFlags);
void DS_StopSample(int nHandle);
void DS_StopAllSamples();

#endif