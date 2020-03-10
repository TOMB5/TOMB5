#include "SFX.H"

#include "SOUND.H"
#include "SPUSOUND.H"
#include "SPECIFIC.H"

long SPU_Play(long sample_index, short volume_left, short volume_right, short pitch, int arg_10)
{
	long channel;

	sva.volume.left = volume_left;
	sva.volume.right = volume_right;
	sva.pitch = pitch >> 6;
	sva.addr = LadwSampleAddr[sample_index];

	if (sample_index < LnSamplesLoaded)
	{
		channel = SPU_AllocChannel();
		if (channel >= 0)
		{
			LabSampleType[channel] = arg_10;
			sva.mask = 0x93;
			sva.voice = 1 << channel;
			SpuSetKeyOnWithAttr(&sva);
			return channel;
		}
		else
		{
			return -1;
		}
	}
	else
	{
		return -2;
	}
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

void SPU_StopAll()
{
	UNIMPLEMENTED();
}

void SPU_FreeChannel(int channel_index)
{
	UNIMPLEMENTED();
}

void S_SoundStopSample(int handle)
{
	UNIMPLEMENTED();
}

void S_SetReverbType(int reverb)
{
	UNIMPLEMENTED();
}

void S_SoundStopAllSamples()
{
	UNIMPLEMENTED();
}

void SOUND_EndScene()
{
	UNIMPLEMENTED();
}

void SOUND_Stop()
{
	UNIMPLEMENTED();
}

int PlaySample(int a0, int volume_left, int volume_right, int a3, int arg_10, int t1, int t2)
{
	//CalcVolumes_ASM();//prolly modifies t1 and t2
	SPU_Play(t1, volume_left, volume_right, t2, arg_10);
	UNIMPLEMENTED();
	return 0;//?
}

int S_SoundPlaySampleLooped(int a0, int a1, int a2, int a3, int arg_10)
{
	if (GtSFXEnabled)
	{
		return PlaySample(arg_10, a1, a2, a3, 2, a0, a2);
	}
	else
	{
		return -3;
	}
}