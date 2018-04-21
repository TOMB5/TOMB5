#include "PCSOUND.H"
#include "SPECIFIC.H"
#include <MSAcm.h>
#include <MMREG.H>
#include <dsound.h>
#include "SPECTYPES.H"
#include <stdio.h>
#include "ERROR.H"
#include "WINMAIN.H"
#include "DIRECTX.H"
#include "SOUND.H"
#include "CONTROL.H"
#include "CD.H"
#include "FILE.H"
#pragma comment (lib, "Msacm32.lib")
#pragma comment (lib, "dsound.lib")
WAVEFORMATEX pwfxSrc = { WAVE_FORMAT_ADPCM, 2, 44100, 44359, 2048, 4, 0x20 };
WAVEFORMATEX stru_516400 = { WAVE_FORMAT_ADPCM, 1, 22050, 11155, 512, 4, 0x20 };
WAVEFORMATEX stru_86BEC8;
ACMSTREAMHEADER stru_86BE70;
DWORD dword_874968;
DWORD NumSamples[] = { 11025, 22050, 44100 };
DWORD dword_86CC7C;
LPDIRECTSOUNDBUFFER DSSoundBuffer;
DWORD opt_MusicVolume = 40;
DWORD opt_SFXVolume = 80;
DWORD opt_ControlMethod;
DWORD opt_SoundQuality = 1;
HANDLE dword_579FA8;
char S_CDStop()
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

void ACMClose()
{
	int v0; // eax@3
	int v1; // eax@6

	if (ACMInited)
	{
		EnterCriticalSection(&CriticalSection);
		S_CDStop();
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


char __cdecl SetSoundOutputFormat(int a1, char a2)
{
	int v2; // eax@4
	char result; // al@5
	WAVEFORMATEX v4; // [sp+4h] [bp-14h]@3

	if ((a2 || dword_86CC7C != a1)
		&& (dword_86CC7C = a1,
			v4.wFormatTag = 1,
			v4.nChannels = 2,
			v4.nSamplesPerSec = a1,
			v4.nAvgBytesPerSec = 4 * a1,
			v4.nBlockAlign = 4,
			v4.wBitsPerSample = 16,
			v4.cbSize = 0,
			S_SoundStopAllSamples(),
			DSSoundBuffer)
		&& (v2 = DSSoundBuffer->lpVtbl->SetFormat(DSSoundBuffer, &v4), sub_40179E(v2)))
	{
		Log(1, "Can't set sound output format to %d", v4.nSamplesPerSec);
		result = 0;
	}
	else
	{
		result = 1;
	}
	return result;
}

char DXSetOutputFormat()
{
	int v0; // eax@1
	char result; // al@2
	DSBUFFERDESC v2; // [sp+4h] [bp-24h]@1


	Log(2, "DXSetOutputFormat");
	memset(&v2, 0, 0x24u);
	v2.dwSize = 36;
	v2.dwFlags = 1;
	v0 = dxctx.dsound->lpVtbl->CreateSoundBuffer(dxctx.dsound, &v2, &DSSoundBuffer, 0);
	if (sub_40179E(v0))
	{
		Log(1, "Can't Get Primary Sound Buffer");
		result = 0;
	}
	else
	{
		SetSoundOutputFormat(NumSamples[opt_SoundQuality], 0);
		DSSoundBuffer->lpVtbl->Play(DSSoundBuffer, 0, 0, 1);
		result = 1;
	}
	return result;
}

int DXDSCreate()
{
	int v0; // eax@1
	int v1; // eax@1
	signed int result; // eax@1

	Log(2, "DXDSCreate");
	v0 = DirectSoundCreate(
		ptr_ctx->soundCards[ptr_ctx->curSoundCard].field1,
		&dxctx.dsound,
		0);
	sub_40179E(v0);
	v1 = dxctx.dsound->lpVtbl->SetCooperativeLevel(dxctx.dsound, hWnd, 3);
	sub_40179E(v1);
	DXSetOutputFormat();
	result = 1;
	sound_active = 1;
	return result;
}

void __cdecl sub_4027DE(void *a1, int a2)
{
	byte_57A01C = 1;
	EnterCriticalSection(&CriticalSection);
	LeaveCriticalSection(&CriticalSection);
	if (!stream)
		goto LABEL_17;
	if (a2 != XATrack || a2 == -1)
	{
		Log(0, "Not Current Track %d", a2);
		goto LABEL_17;
	}
	memset(a1, 0, 0x5800u);
	if (!stream)
	{
	LABEL_17:
		byte_57A01C = 0;
		byte_579FE4 = 0;
		return;
	}
	fread_ex(a1, 1u, 0x5800u, stream);
	if (!stream /*|| !(stream->_flag & 0x10)*/) // TODO MAY BREAK
		goto LABEL_9;
	if (dword_579E30 == 1)
	{
		fseek(stream, 90, 0);
	LABEL_9:
		byte_57A01C = 0;
		byte_579FE4 = 1;
		return;
	}
	if (++dword_57A018 <= 8)
		goto LABEL_9;
	dword_57A018 = 0;
	if (dword_579E30 == 2)
	{
		byte_57A01C = 0;
		byte_579FE4 = 0;
		S_CDStop();
	}
	else
	{
		if (!CurrentAtmosphere || IsAtmospherePlaying)
			goto LABEL_9;
		byte_57A01C = 0;
		byte_579FE4 = 0;
		S_CDStop();
		S_CDPlay(CurrentAtmosphere, 1);
	}
}

int StartAddress()
{
	DWORD i; // esi@1
	int v1; // eax@10
	DWORD v3; // [sp+34h] [bp-8h]@10
	void* v4; // [sp+38h] [bp-4h]@10

	for (i = WaitForMultipleObjects(2u, &Handles, 0, 0xFFFFFFFF);
		i != -1;
		i = WaitForMultipleObjects(2u, &Handles, 0, 0xFFFFFFFF))
	{
		EnterCriticalSection(&CriticalSection);
		if (!i && other_buf)
		{
			qmemcpy(bufSource, dword_579FD4, 0x5800u);
			if (XATrack == -1)
				memset(bufSource, 0, 0x5800u);
			else
				sub_4027DE(dword_579FD4, XATrack);
			if (byte_579FE4)
			{
				dword_579FD4 = (char *)dword_579FD4 + 22528;
				if ((signed int)dword_579FD4 >= (signed int)ptr + 225280)
					dword_579FD4 = ptr;
				other_buf->lpVtbl->Lock(
					other_buf,
					dword_579FD8,
					bufMaxLength,
					&v4,
					&v3,
					0,
					0,
					0);
				acmStreamConvert(has, &acmHeader1 + dword_579E4C, 4u);
				other_buf->lpVtbl->Unlock(
					other_buf,
					v4,
					v3,
					0,
					0);
				v1 = v3 + dword_579FD8;
				dword_579FD8 += v3;
				if (dword_579FD8 >= (unsigned int)bufLockLength)
					dword_579FD8 = v1 - bufLockLength;
				dword_579E4C = ((_BYTE)dword_579E4C + 1) & 3;
			}
		}
		LeaveCriticalSection(&CriticalSection);
		if (!other_buf)
			break;
	}
	return 0;
}
int __stdcall fnCallback(HACMDRIVERID arghadid, int a2, int a3)
{
	int result; // eax@2
	struct tACMDRIVERDETAILSA padd; // [sp+Ch] [bp-398h]@1

	memset(&padd, 0, sizeof(padd));
	padd.cbStruct = 920;
	acmDriverDetailsA(arghadid, &padd, 0);
	if (!strcmp(padd.szShortName, "MS-ADPCM"))
	{
		hadid = arghadid;
		result = 0;
	}
	else
	{
		result = 1;
	}
	return result;
}


int SetupNotifications()
{
	int v0; // edi@1
	char *v1; // esi@1
	signed int v2; // ebx@1
	HANDLE v3; // edx@2
	int v4; // esi@5
	int result; // eax@6
	DWORD ThreadId; // [sp+Ch] [bp-2Ch]@3
	int v7; // [sp+10h] [bp-28h]@1
	HANDLE v8; // [sp+14h] [bp-24h]@1
	char v9[16]; // [sp+18h] [bp-20h]@1
	int v10; // [sp+28h] [bp-10h]@3
	int v11; // [sp+30h] [bp-8h]@3
	HANDLE v12; // [sp+34h] [bp-4h]@3

	v0 = bufMaxLength;
	Handles = CreateEventA(0, 0, 0, 0);
	dword_579FA4 = CreateEventA(0, 0, 0, 0);
	v7 = v0;
	v8 = Handles;
	Log(8, "Set notifies for position %lu", v0);
	v1 = v9;
	v2 = 3;
	do
	{
		v3 = Handles;
		*(_DWORD *)v1 = v0 + *((_DWORD *)v1 - 2);
		*((_DWORD *)v1 + 1) = v3;
		Log(8, "Set notifies for positions %lu", *(_DWORD *)v1);
		v1 += 8;
		--v2;
	} while (v2);
	v11 = -1;
	--v10;
	v12 = dword_579FA4;
	dword_579FA8 = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)StartAddress, 0, 0, &ThreadId);
	if (!dword_579FA8)
		Log(1, "Create Notification Thread failed");
	v4 = (*((int(__stdcall **)(_DWORD, _DWORD, _DWORD))notify_thing->lpVtbl + 3))(notify_thing, 5, &v7);
	if (v4)
	{
		CloseHandle(Handles);
		CloseHandle(dword_579FA4);
		result = v4;
		dword_579FA4 = 0;
		Handles = 0;
	}
	else
	{
		Log(8, "Setup Notifications OK");
		result = 0;
	}
	return result;
}


void ACMInit()
{
	unsigned int v3; // esi@1
	int v5; // eax@5
	int v6; // eax@5
	int v7; // [sp+0h] [bp-2Ch]@0
	LPDIRECTSOUNDNOTIFY *notify_shit; // [sp+4h] [bp-28h]@5
	DWORD cbwfx = 0;
	DSBUFFERDESC v9; // [sp+8h] [bp-24h]@5

	v3 = acmGetVersion();
	InitializeCriticalSection(&CriticalSection);
	ACMInited = 0;
	Log(8, "ACM Version %u.%.02u", v3 >> 24, (unsigned __int8)(v3 >> 16));
	acmDriverEnum(fnCallback, 0, 0);
	if (hadid)
	{
		if (acmDriverOpen(&had, hadid, 0))
		{
			Log(1, "*** Failed To Open Driver MS-ADPCM Driver ***");
		}
		else
		{
			bufSource = (BYTE *)malloc(22528u);
			ptr = malloc(225280u);
			pwfxDst.wFormatTag = WAVE_FORMAT_PCM;
			acmMetrics(NULL, ACM_METRIC_MAX_SIZE_FORMAT, &cbwfx);
			pwfxSrc.cbSize = 2;
			int gg = acmFormatSuggest(had, &pwfxSrc, &pwfxDst, cbwfx, ACM_FORMATSUGGESTF_WFORMATTAG);
			memset(&v9, 0, 36u);
			bufLockLength = 358336;
			bufMaxLength = 89584;
			v9.dwSize = 36;
			v9.dwFlags = DSBCAPS_LOCSOFTWARE
				| DSBCAPS_CTRLFREQUENCY
				| DSBCAPS_CTRLPAN
				| DSBCAPS_CTRLVOLUME
				| DSBCAPS_CTRLPOSITIONNOTIFY
				| DSBCAPS_GETCURRENTPOSITION2;
			v9.dwBufferBytes = 358336;
			v9.lpwfxFormat = &pwfxDst;
			int o = ptr_ctx->dsound->lpVtbl->CreateSoundBuffer(
				ptr_ctx->dsound,
				&v9,
				&other_buf,
				0);
			notify_shit = &notify_thing;
			other_buf->lpVtbl->QueryInterface(
				other_buf,
				&IID_IDirectSoundNotify,
				&notify_thing);
			SetupNotifications();
			acmStreamOpen(&has, had, &pwfxSrc, &pwfxDst, 0, 0, 0, 0);
			acmStreamSize(has, 22528u, &pdwOutputBytes, 0);
			notify_shit = 0;
			v5 = other_buf->lpVtbl->Lock(
				other_buf,
				0,
				bufLockLength,
				&buf_lockAudioPtr1,
				&buf_lockAudioBytes1,
				0,
				0,
				0);
			sub_40179E(v5);
			memset(buf_lockAudioPtr1, 0, bufLockLength);
			memset(&acmHeader1, 0, sizeof(acmHeader1));
			memset(&acmHeader2, 0, sizeof(acmHeader2));
			memset(&acmHeader3, 0, sizeof(acmHeader3));
			memset(&acmHeader4, 0, sizeof(acmHeader4));
			acmHeader1.pbSrc = bufSource;
			acmHeader2.pbSrc = bufSource;
			acmHeader3.pbSrc = bufSource;
			acmHeader4.pbSrc = bufSource;
			acmHeader1.cbDstLength = pdwOutputBytes;
			acmHeader2.cbDstLength = pdwOutputBytes;
			acmHeader2.pbDst = &buf_lockAudioPtr1[bufMaxLength];
			acmHeader3.cbDstLength = pdwOutputBytes;
			acmHeader4.cbDstLength = pdwOutputBytes;
			acmHeader1.cbStruct = 84;
			acmHeader1.cbSrcLength = 22528;
			acmHeader1.pbDst = buf_lockAudioPtr1;
			acmHeader2.cbStruct = 84;
			acmHeader2.cbSrcLength = 22528;
			acmHeader3.cbStruct = 84;
			acmHeader3.cbSrcLength = 22528;
			acmHeader3.pbDst = &buf_lockAudioPtr1[2 * bufMaxLength];
			acmHeader4.cbStruct = 84;
			acmHeader4.cbSrcLength = 22528;
			acmHeader4.pbDst = &buf_lockAudioPtr1[3 * bufMaxLength];
			acmStreamPrepareHeader(has, &acmHeader1, 0);
			acmStreamPrepareHeader(has, &acmHeader2, 0);
			acmStreamPrepareHeader(has, &acmHeader3, 0);
			acmStreamPrepareHeader(has, &acmHeader4, 0);
			notify_shit = 0;
			v6 = other_buf->lpVtbl->Unlock(
				other_buf,
				buf_lockAudioPtr1,
				bufLockLength,
				0,
				0);
			sub_40179E(v6);
			ACMInited = 1;
		}
	}
	else
	{
		Log(1, "*** Unable To Locate MS-ADPCM Driver ***");
	}
}
