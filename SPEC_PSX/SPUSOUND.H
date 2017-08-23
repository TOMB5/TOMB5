#ifndef SPUSOUND_H
#define SPUSOUND_H

#include "SPECTYPES.H"

#include <LIBSPU.H>

extern short DepthTable[5];
extern short CurrentReverb;
extern int LnSamplesLoaded;
extern long LlVABAddr;
extern SpuVoiceAttr sva;
extern unsigned char LabSampleType[];
extern unsigned char LabFreeChannel[];
extern int LnFreeChannels;
extern unsigned long LadwSampleAddr[256];

extern void SPU_FreeSamples();
extern void SPU_Init();
extern void SPU_FreeChannel(int channel_index);
extern void S_SetReverbType(int Reverb);
extern int SPU_UpdateStatus();
extern unsigned char SPU_AllocChannel();

#endif