#ifndef SPUSOUND_H
#define SPUSOUND_H

#include "PSXTYPES.H"

extern short DepthTable[5];
extern short CurrentReverb;
extern int LnSamplesLoaded;
extern long LlVABAddr;
extern struct SpuVoiceAttr sva;
extern unsigned char LabSampleType[];
extern unsigned char LabFreeChannel[];
extern int LnFreeChannels;
extern unsigned long LadwSampleAddr[256];

extern void SPU_Init();
extern void S_SetReverbType(int Reverb);
extern void SPU_FreeChannel(int channel_index);
extern int SPU_UpdateStatus();
extern unsigned char SPU_AllocChannel();

#endif