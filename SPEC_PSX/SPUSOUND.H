#ifndef SPUSOUND_H
#define SPUSOUND_H

#include "SPECTYPES.H"

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
extern unsigned long LadwSampleAddr[256];

extern void SPU_FreeSamples();
extern void SPU_Init();
extern void SPU_FreeChannel(int channel_index);
extern void S_SetReverbType(int reverb);
extern int SPU_UpdateStatus();
extern long SPU_AllocChannel();
extern void SPU_StopAll();

#endif