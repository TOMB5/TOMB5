#include "PCSOUND.H"
#include "SPECIFIC.H"
#include <MSAcm.h>
#include <MMREG.H>
#include <dsound.h>
#include "SPECTYPES.H"
#include <stdio.h>

WAVEFORMATEX pwfxSrc = { WAVE_FORMAT_ADPCM, 2, 44100, 44359, 2048, 4, 0x20 };

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
			sub_4DEB10(4, "Released %s @ %x - RefCnt = %d", "Notification", notify_thing, v0);
			notify_thing = 0;
		}
		else
		{
			sub_4DEB10(1, "%s Attempt To Release NULL Ptr", "Notification");
		}
		if (other_buf)
		{
			v1 = other_buf->lpVtbl->Release(other_buf);
			sub_4DEB10(4, "Released %s @ %x - RefCnt = %d", "Stream Buffer", other_buf, v1);
			other_buf = 0;
			LeaveCriticalSection(&CriticalSection);
		}
		else
		{
			sub_4DEB10(1, "%s Attempt To Release NULL Ptr", "Stream Buffer");
			LeaveCriticalSection(&CriticalSection);
		}
	}
}