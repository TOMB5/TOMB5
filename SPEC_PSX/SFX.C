#include "SFX.H"

#include "SPECIFIC.H"
#include "SOUND.H"
#include "SPUSOUND.H"

long SPU_Play(long sample_index, short volume_left, short volume_right, short pitch)//91518(<) ?
{
	long channel;

	sva.volume.left = volume_left;
	sva.volume.right = volume_right;
	sva.pitch = pitch / 64;
	sva.addr = LadwSampleAddr[sample_index];

	if (sample_index > LnSamplesLoaded)
	{
		return -2;
	}

	channel = SPU_AllocChannel();
	if (channel < 0)
	{
		return -1;
	}

	//lw	$v0, 0x18 + arg_10($sp)//?
	//LabSampleType[channel] = v0;
	
	sva.mask = (SPU_COMMON_MVOLL | SPU_COMMON_MVOLR | SPU_COMMON_RVOLL | SPU_COMMON_CDVOLR);
	sva.voice = (1 << channel);
	SpuSetKeyOnWithAttr(&sva);

	return channel;
}

long SPU_AllocChannel()//915B0, 935F4 (F)
{
	if (LnFreeChannels == 0)
	{
		if (SPU_UpdateStatus() == 0)
		{
			return -1;
		}
	}

	//loc_915DC
	return LabFreeChannel[--LnFreeChannels];
}

int SPU_UpdateStatus()//915FC, 93640 (F)
{
	int i;
	char status[MAX_SOUND_SLOTS];

	SpuGetAllKeysStatus(&status[0]);

	for (i = 0; i < MAX_SOUND_SLOTS; i++)
	{
		if (status[i] - 1 > 1 && LabSampleType[i] != 0)
		{
			SPU_FreeChannel(i);
		}
	}

	return LnFreeChannels;
}

void SPU_Status(long a0)//91708
{
	//s0 = a0;
	//a0 = 0 + 1;

	SpuGetKeyStatus(1);

	//a0 <<= s0;
}

void SPU_FreeChannel(int channel_index)//91668, 936AC (F)
{
	LabSampleType[channel_index] = 0;
	LabFreeChannel[LnFreeChannels++] = channel_index;
}

void S_StopSoundSample()
{

}

void SPU_Stop(long channel)//916A0(<)
{
	long a2;

	if (LabSampleType[channel] != 0)
	{
		SPU_FreeChannel(channel);
	}
	
	//loc_916CC
	SpuSetVoiceVolume(0, 0, 0);

	//a2 = lw a2, $14(sp); //?
	SpuSetKey(0, 1 << a2);
}

void S_SetReverbType(int reverb)//91CF4, 93D40 (F)
{
	if (reverb != CurrentReverb)
	{
		CurrentReverb = reverb;

		SpuSetReverbModeDepth(DepthTable[reverb], DepthTable[reverb]);
		SpuSetReverb(SPU_ON);
	}
}

void SPU_StopAll()//91D44 (F)
{
	SpuSetKey(SPU_OFF, SPU_ALLCH);

	while (SPU_UpdateStatus() != MAX_SOUND_SLOTS);
	
	return;
}

void S_SoundStopSample(int handle)//91690(<), 936D4(<)
{
	if (GtSFXEnabled == 0)
	{
		return;
	}

	if (LabSampleType[handle] != 0)
	{
		SPU_FreeChannel(handle);
	}

	//loc_916CC
	SpuSetVoiceVolume(handle, 0, 0);
	SpuSetKey(SPU_OFF, SPU_0CH);
}

void S_SoundStopAllSamples()//91D34, 93D80
{
	if (GtSFXEnabled == 0)
	{
		return;
	}

	SPU_StopAll();
}

int S_SoundSampleIsPlaying(int handle)//916F8(<), 9373C(<)
{
	char status;

	if (GtSFXEnabled == 0)
	{
		return 0;
	}

	status = (char)(SpuGetKeyStatus(1 << handle) -1);

	if (status < 2 || LabSampleType[handle] == 0)
	{
		return LabSampleType[handle];
	}

	SPU_FreeChannel(handle);

	return 0;
}

void S_SoundSetPitch(int handle, int nPitch)//91768(<), 937AC(<)
{
	if (GtSFXEnabled == 0)
	{
		return;
	}

	SpuSetVoicePitch(handle, nPitch / 64);
}

void S_SoundSetPanAndVolume(int nhandle, int nPan, int nVolume, int distance)
{
	S_Warn("[S_SoundSetPanAndVolume] - Unimplemented!\n");
}

void GetPanVolume(struct SoundSlot* slot)
{
	S_Warn("[GetPanVolume] - Unimplemented!\n");
}
