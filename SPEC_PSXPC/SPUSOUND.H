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
extern void SPU_FreeSamples();
extern void S_SetReverbType(int Reverb);
extern void SPU_FreeChannel(int channel_index);
extern int SPU_UpdateStatus();
extern unsigned char SPU_AllocChannel();
extern void _SpuIsInAllocateArea_(int arg0);
extern void _SpuIsInAllocateArea(int arg0);
extern void SpuSetReverb(int a);
extern void SpuSetReverbModeParam(int a);
extern void SpuSetReverbDepth(int a);
extern void SpuSetReverbVoice(int a, int b);
extern void SpuIsTransferCompleted(long a);
extern void SpuInit();

#endif