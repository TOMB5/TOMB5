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

void DS_AdjustPan(int nHandle,int nPan)// (F)
{
	IDirectSoundBuffer* pBuffer=LaPlayBuffer[nHandle].buf;
	if (pBuffer)
	{
		if (nPan > 16384)
			nPan = 32768 - nPan;
		else if (nPan < -16384)
			nPan = -32768 - nPan;

		DX_TRY(pBuffer->SetPan(nPan / 16));
	}
}

int DS_StartSample(int nSample, int nVolume, int nPitch, int nPan, DWORD dwFlags)// (F)
{
	int nChannel=DS_GetFreeChannel();
	if (nChannel<0)
		return -1;

	IDirectSoundBuffer* pBuffer;
	if (DX_TRY(App.lpDS->DuplicateSoundBuffer(L_DSBuffer[nSample].buf,&pBuffer)))
		return -1;

	if (DX_TRY(pBuffer->SetVolume(nVolume)) ||
		DX_TRY(pBuffer->SetCurrentPosition(0)))
		return -1;

	LaPlayBuffer[nChannel].buf=pBuffer;
	LaPlayBuffer[nChannel].samplePlaying=nSample;

	DS_AdjustPitch(nChannel, nPitch);
	DS_AdjustPan(nChannel, nPan);

	pBuffer->Stop();
	DX_TRY(pBuffer->Play(0, 0, dwFlags));

	return nChannel;
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