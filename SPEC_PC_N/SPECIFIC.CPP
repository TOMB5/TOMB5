#define _X86_
#define _USE_32BIT_TIME_T
#include <cstddef>
#include <time.h>
#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <debugapi.h>
#include "STYPES.H"
#include "INCLUDE.H"
#include "SPECTYPES.H"
#include "SOUND.H"
#include "DS.H"
#include "GLOBAL.H"
#include "DIRECTX.H"
#include "TIME.H"
#include "DRAWPRIMITIVE.H"
#include "DEBUG.H"

void DebugPrint(const char* message)
{
	char buf[1024];
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);

	sprintf(buf, "[%02d:%02d:%02d] ", tm.tm_hour, tm.tm_min, tm.tm_sec);

	strcpy(buf, message);

	int len = strlen(buf);

	if (buf[len - 1] != '\n')
	{
		buf[len] = '\n';
		buf[len + 1] = 0;
	}

	OutputDebugString(buf);
	printf(buf);
	fprintf(fplog, buf);
	fflush(fplog);
}

#ifdef __cplusplus
extern "C" {
#endif

	

void S_Warn(const char* warning_message, ...)
{
	char buf[1024];
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);

	sprintf(buf, "[%02d:%02d:%02d] ", tm.tm_hour, tm.tm_min, tm.tm_sec);

	va_list argptr;
	va_start(argptr, warning_message);
	vsprintf(buf, warning_message, argptr);
	va_end(argptr);

	Log_backend(LT_Info, buf);

	DebugPrint(buf);
}

void S_CDPlay(sint16 nTrack, int tMode)
{
	Log(LT_Enter, "S_CDPlay: nTrack=%d; tMode=%d", nTrack, tMode);

	Unimpl();

	//if (!Option_Music_Volume)
		return;
/*
#ifndef DUDE_DEMO
#ifndef DEMO
	MCI_PLAY_PARMS pp;
	cdtrack = nTrack;
	nTrack = GetRealTrack(nTrack);

	OpenCD();

	// start track
	pp.dwFrom = MCI_MAKE_TMSF(nTrack, 0, 0, 0);
	pp.dwTo = MCI_MAKE_TMSF(nTrack + 1, 0, 0, 0);
	if (mciSendCommand(wDeviceID, MCI_PLAY, MCI_FROM | MCI_TO, (DWORD)&pp))
		Log(LT_Error, "Can't play track %d", nTrack);

	CloseCD();

	// set looping flag if need be
	if (tMode)
		cd_looping = nTrack;
#endif
#endif
	*/
}

void S_CDStop(void)
{
	Unimpl();
}

void S_SoundStopSample(sint32 handle)
{
	if (!sound_active)
		return;

	DS_StopSample(handle);
}

void S_SoundStopAllSamples(void)
{
	if (!sound_active)
		return;

	DS_StopAllSamples();
}

void		S_DumpScreenFrame()
{
	Unimpl();
}

long		S_DumpScreen()
{
	// todo
	int last = Sync();
	int off = last;
	if (last < 2)
	{
		int rev = 2 - last;
		off = 2;
		do
		{
			while (!Sync());
			rev--;
		} while (rev);
	}
	GnFrameCounter++;

	DDCopyBitmap(App.lpFrontBuffer, "uk.bmp");
	DDCopyBitmap(App.lpBackBuffer, "france.bmp");

	EndScene();
	DXShowFrame();
	App.sceneDone = true;

	return off;
}
void S_LoadBar()
{
	Unimpl();
}
void S_InitLoadBar(int size)
{
	Unimpl();
}

bool Decompress(void* buf, void* compressed, int compSize, int uncompSize)
{
	Unimpl();
	return false;
}

unsigned short *AnimTextureRanges; // offset 0xA4670
unsigned short nAnimUVRanges; // offset 0xA4660

void SetFogColor(uint8_t r, uint8_t g, uint8_t b)
{
	App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_FOGCOLOR, GENRGB(r, g, b));
}

void ClearFXFogBulbs()
{
	
}

void SetFade(int a1, int a2)
{
	Unimpl();
}

void S_InitialiseScreen()
{
	Unimpl();
}

BYTE IsVolumetric()
{
	return App.tVolumetricShadows;
}

void S_AnimateTextures(long nFrames)
{
	Unimpl();
}

void S_OutputPolyList()
{
	Unimpl();
}

void S_CalculateStaticMeshLight(int x, int y, int z, int shade, room_info* room)
{
	Unimpl();
}

void S_CalculateLight(long x, long y, long z, short room, ITEM_LIGHT* light)
{
	
}

void S_CDLoop()
{
	Unimpl();
}

	int S_LoadSave(int input, int in_inventory)
{
		Unimpl();
		return 0;
}

	int S_DisplayPauseMenu(int a1)
{
		Unimpl(); 
	return 0;
}

	int S_PauseMenu()
{
		Unimpl();
		return 0;
}

#ifdef __cplusplus
}
#endif