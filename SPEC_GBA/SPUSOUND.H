#ifndef SPUSOUND_H
#define SPUSOUND_H

#include <LIBSPU.H>

#define MAX_NUM_SOUND_EFFECTS 256

extern short DepthTable[5];
extern short CurrentReverb;
extern int LnSamplesLoaded;
extern long LlVABAddr;
extern SpuVoiceAttr sva;
extern unsigned char LabSampleType[];
extern unsigned char LabFreeChannel[];
extern int LnFreeChannels;
extern unsigned long LadwSampleAddr[];

extern void SPU_FreeSamples();
extern void SPU_Init();

#endif