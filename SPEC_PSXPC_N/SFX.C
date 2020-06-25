#include "SFX.H"

#include "SOUND.H"
#include "SPUSOUND.H"
#include "SPECIFIC.H"

#include <LIBSPU.H>

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

void SPU_FreeChannel(int channel_index)//91668, 936AC (F)
{
	LabSampleType[channel_index] = 0;
	LabFreeChannel[LnFreeChannels++] = channel_index;
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
	//v0 = sound_active
	if (sound_active != 0)
	{
		//s0 = 0;
		//s2 = sample_infos
		//s1 = &LaSlot[0]

		//loc_91DAC
		for (int i = 0; i < MAX_SOUND_SLOTS; i++)
		{
			//v0 = LaSlot[0].nSampleInfo

			if (LaSlot[i].nSampleInfo >= 0)
			{
				//v0 = sample_infos[LaSlot[0].nSampleInfo].flags
				if ((sample_infos[LaSlot[i].nSampleInfo].flags & 0x3) == 3)
				{
					//a2 = LaSlot[0].nVolume
					//a0 = s0
					if (LaSlot[i].nVolume != 0)
					{
						S_SoundSetPanAndVolume(i, LaSlot[i].nPan, LaSlot[i].nVolume & 0xFFFF, LaSlot[i].distance);
						S_SoundSetPitch(i, LaSlot[i].nPitch);
						LaSlot[i].nVolume = 0;
					}
					else
					{
						//loc_91E08
						S_SoundStopSample(i);
						LaSlot[i].nSampleInfo = -1;
					}
				}
				else
				{
					//loc_91E1C
					if (!S_SoundSampleIsPlaying(i))
					{
						S_SoundStopSample(i);
						LaSlot[i].nSampleInfo = -1;
					}
					else
					{
						//a0 = LaSlot[0].pos.x | LaSlot[0].pos.y |LaSlot[0].pos.z
						//a1 = 
						//a2 = 

						if ((LaSlot[i].pos.x | LaSlot[i].pos.y | LaSlot[i].pos.z) != 0)
						{
							GetPanVolume(&LaSlot[i]);
							S_SoundSetPanAndVolume(i, LaSlot[i].nPan, LaSlot[i].nVolume, LaSlot[i].distance);
						}
						//loc_91E64
					}
				}
			}//loc_91E64
		}
	}//loc_91E74
}

void SOUND_Stop()
{
	UNIMPLEMENTED();
}

int PlaySample(int a0, int volume_left, int volume_right, int a3, int arg_10, int t1, int t2)//914C8(<), 9350C(<)
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

int S_SoundPlaySample(int a0, int a1, int a2, int a3, int arg_10)//91480(<), ?
{
	if (GtSFXEnabled)
	{
		int t1 = a0;
		int t2 = a1;
		a0 = arg_10;
		PlaySample(a0, a1, a2, a3, 1, t1, t2);
	}
	else
	{
		return -3;
	}
}

void S_SoundSetPitch(int handle, int nPitch)
{
	UNIMPLEMENTED();
}

int S_SoundSetPanAndVolume(int nhandle, int nPan, int nVolume, int distance)
{
	UNIMPLEMENTED();
	return 0;
}

void GetPanVolume(struct SoundSlot* slot)
{
	UNIMPLEMENTED();
}