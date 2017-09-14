#include "PCSOUND.H"
#include "SPECIFIC.H"
#include <MSAcm.h>
#include <MMREG.H>
#include <dsound.h>
#include "SPECTYPES.H"
#include <stdio.h>
#include "ERROR.H"
#include "WINMAIN.H"

WAVEFORMATEX pwfxSrc = { WAVE_FORMAT_ADPCM, 2, 44100, 44359, 2048, 4, 0x20 };
WAVEFORMATEX stru_516400 = { WAVE_FORMAT_ADPCM, 1, 22050, 11155, 512, 4, 0x20 };
WAVEFORMATEX stru_86BEC8;
ACMSTREAMHEADER stru_86BE70;

char ResetSoundThings()
{
	char result; // al@1

	result = ACMInited;
	if (ACMInited)
	{
		result = (char)stream;
		if (stream)
		{
			memset(ptr, 0, 0x37000u);
			other_buf->lpVtbl->Stop(other_buf);
			other_buf->lpVtbl->SetCurrentPosition(other_buf, 0);
			while (byte_57A01C)
				;
			result = fclose(stream);
			stream = 0;
			dword_57A018 = 0;
			dword_510B18 = 7;
			XATrack = -1;
		}
	}
	return result;
}

void FreeSoundThings()
{
	int v0; // eax@3
	int v1; // eax@6

	if (ACMInited)
	{
		EnterCriticalSection(&CriticalSection);
		ResetSoundThings();
		CloseHandle(Handles);
		CloseHandle(dword_579FA4);
		acmStreamUnprepareHeader(has, &acmHeader1, 0);
		acmStreamUnprepareHeader(has, &acmHeader2, 0);
		acmStreamUnprepareHeader(has, &acmHeader3, 0);
		acmStreamUnprepareHeader(has, &acmHeader4, 0);
		acmStreamClose(has, 0);
		acmDriverClose(had, 0);
		if (notify_thing)
		{
			v0 = notify_thing->lpVtbl->Release(notify_thing);
			Log(4, "Released %s @ %x - RefCnt = %d", "Notification", notify_thing, v0);
			notify_thing = 0;
		}
		else
		{
			Log(1, "%s Attempt To Release NULL Ptr", "Notification");
		}
		if (other_buf)
		{
			v1 = other_buf->lpVtbl->Release(other_buf);
			Log(4, "Released %s @ %x - RefCnt = %d", "Stream Buffer", other_buf, v1);
			other_buf = 0;
			LeaveCriticalSection(&CriticalSection);
		}
		else
		{
			Log(1, "%s Attempt To Release NULL Ptr", "Stream Buffer");
			LeaveCriticalSection(&CriticalSection);
		}
	}
}

HACMSTREAM phas;

void StreamOpen()
{
	stru_86BEC8.wFormatTag = 1;
	stru_86BEC8.cbSize = 0;
	stru_86BEC8.nChannels = 1;
	stru_86BEC8.nAvgBytesPerSec = 44100;
	stru_86BEC8.nSamplesPerSec = 22050;
	stru_86BEC8.nBlockAlign = 2;
	stru_86BEC8.wBitsPerSample = 16;
	const MMRESULT v0 = acmStreamOpen(&phas, had, &stru_516400, &stru_86BEC8, 0, 0, 0, 0);
	dword_86BEC4 = v0;
	if (v0)
		Log(1, "Stream Open %d", v0);
	dword_86CC78 = malloc(0x40000u);
	void *v1 = malloc(0x4005Au);
	dword_86BEDC = v1;
	memset(&stru_86BE70, 0, sizeof(stru_86BE70));
	stru_86BE70.pbSrc = (char *)v1 + 90;
	stru_86BE70.cbStruct = 84;
	stru_86BE70.cbSrcLength = 0x40000;
	stru_86BE70.cbDstLength = 0x40000;
	stru_86BE70.pbDst = (LPBYTE)dword_86CC78;
	const MMRESULT v2 = acmStreamPrepareHeader(phas, &stru_86BE70, 0);
	dword_86BEC4 = v2;
	Log(1, "Prepare Stream %d", v2);
}

char StreamClose()
{
	MMRESULT v0; // eax@1
	MMRESULT v1; // eax@3

	stru_86BE70.cbSrcLength = 0x40000;
	v0 = acmStreamUnprepareHeader(phas, &stru_86BE70, 0);
	dword_86BEC4 = v0;
	if (v0)
		Log(1, "UnPrepare Stream %d", v0);
	v1 = acmStreamClose(phas, 0);
	dword_86BEC4 = v1;
	if (v1)
		Log(1, "Stream Close %d", v1);
	free(dword_86CC78);
	free(dword_86BEDC);
	return 1;
}

char __cdecl DXCreateSampleADPCM(char *a1, int a2, int a3, int a4)
{
	char result; // al@2
	MMRESULT v5; // eax@5
	int v6; // eax@7
	int v7; // eax@9
	int v8; // eax@11
	struct IDirectSoundBuffer *v9; // edx@11
	int v10; // eax@11
	struct IDirectSoundBuffer *v11; // [sp+44h] [bp-30h]@7
	void *v12; // [sp+48h] [bp-2Ch]@9
	int v13; // [sp+4Ch] [bp-28h]@9
	DSBUFFERDESC v14; // [sp+50h] [bp-24h]@7

	Log(8, "DXCreateSampleADPCM");
	if (ptr_ctx->dsound)
	{
		if (*((_DWORD *)a1 + 6) != 22050)
			Log(1, "Incorrect SamplesPerSec");
		stru_86BE70.cbSrcLength = a2 - *((_WORD *)a1 + 18) - 58;
		v5 = acmStreamConvert(phas, &stru_86BE70, 0x14u);
		dword_86BEC4 = v5;
		if (v5)
			Log(1, "Stream Convert %d", v5);
		memset(&v14, 0, 0x24u);
		v14.dwReserved = 0;
		v14.dwSize = 36;
		v14.dwFlags = 226;
		v14.dwBufferBytes = a3 - 32;
		v14.lpwfxFormat = &stru_86BEC8;
		v6 = ptr_ctx->dsound->lpVtbl->CreateSoundBuffer(ptr_ctx->dsound, &v14, &v11, 0);
		if (sub_40179E(v6))
		{
			Log(1, "Unable To Create Sound Buffer");
			result = 0;
		}
		else
		{
			v7 = v11->lpVtbl->Lock(
				v11,
				0,
				a3 - 32,
				&v12,
				&v13,
				0,
				0,
				0);
			if (sub_40179E(v7))
			{
				Log(1, "Unable To Lock Sound Buffer");
				result = 0;
			}
			else
			{
				qmemcpy(v12, dword_86CC78, a3 - 32);
				v8 = v11->lpVtbl->Unlock(v11, v12, v13, 0, 0);
				sub_40179E(v8);
				v9 = v11;
				v10 = 3 * a4;
				dword_86BEF4[v10] = stru_86BEC8.nSamplesPerSec;
				dword_86BEF0[v10] = v9;
				result = 1;
			}
		}
	}
	else
	{
		result = 0;
	}
	return result;
}