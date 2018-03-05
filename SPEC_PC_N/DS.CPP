#include "INCLUDE.H"

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
		LaPlayBuffer[nHandle] = 0;
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
			LaPlayBuffer[nChannel] = 0;
		}
	}
}