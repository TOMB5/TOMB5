#include "INCLUDE.H"

#pragma comment (lib, "dsound.lib")

#define NUMBER_SOUND_BUFFERS 256
#define NUMBER_SOUND_PLAY_BUFFERS 32

local IDirectSoundBuffer* LaPlayBuffer[NUMBER_SOUND_PLAY_BUFFERS];
local int LnSamplePlaying[NUMBER_SOUND_PLAY_BUFFERS];
local int LanSampleFrequency[NUMBER_SOUND_BUFFERS];
void DS_StopSample(int nHandle)// (F)
{
	if (nHandle >= 0)
	{
		auto buf = LaPlayBuffer[nHandle].buf;
		if (buf)
		{
			DX_TRY(buf->Stop());
			DX_TRY(buf->Release());
			LaPlayBuffer[nHandle].samplePlaying = 0;
			LaPlayBuffer[nHandle].buf = nullptr;
		}
	}
}

bool DS_IsChannelPlaying(int nChannel)// (F)
{
	IDirectSoundBuffer* pBuffer = LaPlayBuffer[nChannel].buf;

	if (!pBuffer)
		return false;

	DWORD dwStatus;

	if (!DX_TRY(pBuffer->GetStatus(&dwStatus)))
	{
		if (dwStatus & DSBSTATUS_PLAYING)
			return true;

		DS_StopSample(nChannel);
	}

	return false;
}

int DS_GetFreeChannel()// (f)
{
	for (int i = 0; i < ArraySize(LaPlayBuffer); i++)
		if (!DS_IsChannelPlaying(i))
			return i;

	return -1;
}

void DS_AdjustPitch(int nHandle,int nPitch)// (F)
{
	IDirectSoundBuffer* pBuffer=LaPlayBuffer[nHandle].buf;
	if (pBuffer)
	{
		int nFrequency = CLAMP(nPitch * 22050.0 / 65536.0, 100, 100000);
		DX_TRY(pBuffer->SetFrequency(nFrequency));
	}
}

void DS_StopAllSamples()
{
	for (int nChannel = 0; nChannel < ArraySize(LaPlayBuffer); ++nChannel)
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
sint32 S_SoundSampleIsPlaying(sint32 handle)
{
	Unimpl();
	return 0;
}

void S_SoundSetPitch(sint32 handle, int nPitch)
{
	Unimpl();
}
#ifdef __cplusplus
}
#endif