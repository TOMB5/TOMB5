#include "SFX.H"

#include "SPECIFIC.H"

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
	SPU_Play(t1, volume_left, volume_right, t2);
	UNIMPLEMENTED();
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