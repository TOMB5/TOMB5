#ifndef SFX_H
#define SFX_H

#include "TYPES.H"

extern long SPU_Play(long sample_index, short volume_left, short volume_right, short pitch);
extern long SPU_AllocChannel();
extern int SPU_UpdateStatus();
extern void SPU_Status(long a0);
extern void S_StopSoundSample();
extern void SPU_Stop(long channel);
extern void S_SetReverbType(int reverb);
extern void SPU_StopAll();
extern void S_SoundStopSample(int handle);
extern void S_SoundStopAllSamples();
extern int S_SoundSampleIsPlaying(int handle);
extern void S_SoundSetPitch(int handle, int nPitch);
extern void S_SoundSetPanAndVolume(int nhandle, int nPan, int nVolume, int distance);
extern void GetPanVolume(struct SoundSlot* slot);
extern void SPU_FreeChannel(int channel_index);

#endif