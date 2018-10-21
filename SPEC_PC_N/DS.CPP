#include "INCLUDE.H"

#pragma comment (lib, "dsound.lib")

#define NUMBER_SOUND_BUFFERS 256
#define NUMBER_SOUND_PLAY_BUFFERS 32

local IDirectSoundBuffer* LaPlayBuffer[NUMBER_SOUND_PLAY_BUFFERS];
local int LnSamplePlaying[NUMBER_SOUND_PLAY_BUFFERS];
local int LanSampleFrequency[NUMBER_SOUND_BUFFERS];

void DS_StopSample(int nHandle)
{
	if (nHandle<0)
		return;
	IDirectSoundBuffer* pBuffer = LaPlayBuffer[nHandle];
	if (pBuffer)
	{
		DX_TRY(pBuffer->Stop());
		pBuffer->Release();
		LaPlayBuffer[nHandle] = nullptr;
	}
}

void DS_StopAllSamples()
{
	for (int nChannel = 0; nChannel<ArraySize(LaPlayBuffer); ++nChannel)
	{
		IDirectSoundBuffer* pBuffer = LaPlayBuffer[nChannel];
		if (pBuffer)
		{
			DX_TRY(pBuffer->Stop());
			pBuffer->Release();
			LaPlayBuffer[nChannel] = nullptr;
		}
	}
}

void CDDA_SetMasterVolume(int nVolume) // (F)
{
	
}

#ifdef __cplusplus
extern "C" {
#endif
	sint32		S_SoundSampleIsPlaying(sint32 handle)
	{
		Unimpl();
		return 0;
	}

	void		S_SoundSetPitch(sint32 handle, int nPitch)
	{
		Unimpl();
	}
#ifdef __cplusplus
}
#endif