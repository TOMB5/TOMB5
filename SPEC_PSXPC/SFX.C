#include "SFX.H"

#include "SPECIFIC.H"
#include "SOUND.H"
#include "SPUSOUND.H"

void SPU_Play()//91518
{
	S_Warn("[SPU_Play] - Unimplemented!\n");
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

	//SpuGetAllKeysStatus(&status[0]);

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

	//SpuGetKeyStatus(1);

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

void SPU_Stop()
{

}

void S_SetReverbType(int reverb)//91CF4, 93D40 (F)
{
	if (reverb != CurrentReverb)
	{
		CurrentReverb = reverb;
	}
}

void SPU_StopAll()//91D44 (F)
{
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

	//status = (char)(SpuGetKeyStatus(1 << handle) -1);

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

	//SpuSetVoicePitch(handle, nPitch / 64);
}

int S_SoundSetPanAndVolume(int nhandle, int nPan, int nVolume, int distance)//914E4
{
	if (GtSFXEnabled)
	{
		//CalcVolumes_ASM(distance, nVolume, nVolume, nPan);
	}

	return 0;
}

void GetPanVolume(struct SoundSlot* slot)
{
	S_Warn("[GetPanVolume] - Unimplemented!\n");
}
