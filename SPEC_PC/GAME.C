#include "GAME.H"
#include "SPECIFIC.H"
#include "MALLOC.H"
#include "OBJECTS.H"
#include "GAMEFLOW.H"
#include "ROOMLOAD.H"
#include "WINMAIN.H"
#include "ERROR.H"
#include "PCSOUND.H"
#include <process.h>
#include "SOUND.H"

struct object_info objects[NUMBER_OBJECTS];
struct static_info static_objects[NUMBER_STATIC_OBJECTS];

void GameClose()
{
	int v0; // eax@2

	sub_4DEB10(2, "GameClose");
	FreeSoundThings();
	FreeLevel();
	if (vertexBuffer)
	{
		v0 = vertexBuffer->lpVtbl->Release(vertexBuffer);
		sub_4DEB10(4, "Released %s @ %x - RefCnt = %d", "Dest VB", vertexBuffer, v0);
		vertexBuffer = 0;
	}
	else
	{
		sub_4DEB10(1, "%s Attempt To Release NULL Ptr", "Dest VB");
	}
	free(dword_D9AB34);
	if (ptr)
		free(ptr);
	if (bufSource)
		free(bufSource);
	free(malloc_buffer);
	free(gfScriptFile);
	free(gfStringOffset);
}

void *sub_40299B()
{
	S_Warn("[*sub_40299B] - Unimplemented!\\n");
	return NULL;
}

signed int sub_40215D()
{
	signed int result; // eax@2

	if (ptr_ctx->flags & 0x80)
	{
		word_C713D0 = 2048;
		word_D6866C = 2048;
		result = 128;
		word_C717E4 = 128;
		word_C713D8 = 128;
	}
	else
	{
		word_C713D0 = 256;
		word_D6866C = 256;
		result = 8;
		word_C717E4 = 8;
		word_C713D8 = 8;
	}
	return result;
}

char GameInitialise()
{
	D3DVERTEXBUFFERDESC vb;
	sub_4DEB10(2, "GameInitialise");
	vb.dwCaps = 0;
	vb.dwSize = 16;
	vb.dwFVF = 452;
	vb.dwNumVertices = 0x2000;
	int res = ptr_ctx->d3d->lpVtbl->CreateVertexBuffer(ptr_ctx->d3d, &vb, &vertexBuffer, 4, 0);
	sub_40179E(res);
	init_game_malloc();
	dword_D9AB34 = malloc(32768u);
	ptr_ctx->dword_D9AC38 = 0;
	dword_D9ADE8 = 0;
	ptr_ctx->dword_D9AC34 = ptr_ctx->graphicsAdapters[ptr_ctx->curGfxAdapt]
		.accelAdapters[ptr_ctx->curAccelAdapt]
		.displayModes[ptr_ctx->curDispMode]
		.width;
	dword_D9AB18 = ptr_ctx->graphicsAdapters[ptr_ctx->curGfxAdapt]
		.accelAdapters[ptr_ctx->curAccelAdapt]
		.displayModes[ptr_ctx->curDispMode]
		.height;
	sub_40299B();
	sub_40215D();
	return 1;
}

void sub_4D3150()
{
	;
}

unsigned __stdcall GameMain(void* data)
{
	/*signed int v1; // esi@2

	sub_4DEB10(2, "GameMain");
	if (GameInitialise())
	{
		sub_4A7EE0();
		HWInitialise();
		sub_48F0E0(0, 0, ptr_ctx->width, ptr_ctx->height, 20, 20480, 80);
		sub_480F00();
		TIME_Init();
		byte_D9AC19 = 1;
		v1 = sub_4D30E0(&word_878654);
		ResetSoundThings();
		sub_4D1AD0();
		if (!ptr_ctx->opt_DisableSound)
			SOUND_Init();
		DoGameflow();
		GameClose();
		ResetSoundThings();
		if (v1)
			sub_4D3150();
		PostMessageA(hWnd, 0x10u, 0, 0);
		dword_876C40 = 0;
		_endthreadex(1u);
	}
	return 1;*/
	
	S_Warn("[GameMain] - Unimplemented!\n");
	return 0;
}
