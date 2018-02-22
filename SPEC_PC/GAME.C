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
#include "DIRECTX.H"

struct object_info objects[NUMBER_OBJECTS];
struct static_info static_objects[NUMBER_STATIC_OBJECTS];

void GameClose()
{
	int v0; // eax@2

	Log(2, "GameClose");
	ACMClose();
	FreeLevel();
	if (vertexBuffer)
	{
		v0 = vertexBuffer->lpVtbl->Release(vertexBuffer);
		Log(4, "Released %s @ %x - RefCnt = %d", "Dest VB", vertexBuffer, v0);
		vertexBuffer = 0;
	}
	else
	{
		Log(1, "%s Attempt To Release NULL Ptr", "Dest VB");
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

void *init_water_table()
{
	S_Warn("[*sub_40299B] - Unimplemented!\n");
	return NULL;
}

signed int InitFX()
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
	Log(2, "GameInitialise");
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
		.D3DInfo[ptr_ctx->curAccelAdapt]
		.DisplayMode[ptr_ctx->curDispMode]
		.w;
	dword_D9AB18 = ptr_ctx->graphicsAdapters[ptr_ctx->curGfxAdapt]
		.D3DInfo[ptr_ctx->curAccelAdapt]
		.DisplayMode[ptr_ctx->curDispMode]
		.h;
	init_water_table();
	InitFX();
	return 1;
}

void sub_4D3150()
{
	;
}

void sub_4D34C1()
{
	sub_4DA111(&ptr_ctx->dword_D9ABFD);
}

int BeginScene()
{
	if (ptr_ctx->isInScene)
		Log(1, "Already In Scene");
	ptr_ctx->isInScene = 1;
	ptr_ctx->dword_D9AC01 = 0;
	if (ptr_ctx->dword_D9ABFD)
		sub_4D34C1();
	return ptr_ctx->d3d_dev->lpVtbl->BeginScene(ptr_ctx->d3d_dev);
}

int EndScene()
{
	ptr_ctx->isInScene = 0;
	return ptr_ctx->d3d_dev->lpVtbl->EndScene(ptr_ctx->d3d_dev);
}

BOOL __cdecl sub_4010E1(float *a1, float *a2, float *a3)
{
	return (a1[1] - a2[1]) * (*a3 - *a2) - (a3[1] - a2[1]) * (*a1 - *a2) < 0.0;
}

int __cdecl sub_40303A(int a1, int a2, int a3, int a4, int a5, int a6, int a7)
{
	S_Warn("[sub_40303A] - Unimplemented!\n");
	return 0;
}

int __cdecl sub_402BDF(int a1, int a2, int a3, int a4, int a5, int a6)
{
	S_Warn("[sub_402BDF] - Unimplemented!\n");
	return 0;
}

int __cdecl sub_401A6E(int a1, int a2, int a3, int a4, int a5, int a6, int a7)
{
	S_Warn("[sub_401A6E] - Unimplemented!\n");
	return 0;
}

int __cdecl sub_40138E(int a1, int a2, int a3, int a4, int a5, int a6)
{
	S_Warn("[sub_40138E] - Unimplemented!\n");
	return 0;
}

struct D3DTEXTUREINFO *__cdecl sub_4025D6(int a1, int a2, __int16 a3)
{
	S_Warn("[sub_4025D6] - Unimplemented!\n");
	return NULL;
}

int __cdecl sub_402626(int a1, int a2, int a3, int a4, int a5, int a6, int a7)
{
	S_Warn("[sub_402626] - Unimplemented!\n");
	return 0;
}

int __cdecl sub_401F41(int a1, int a2, int a3, int a4, int a5, int a6)
{
	S_Warn("[sub_401F41] - Unimplemented!\n");
	return 0;
}


void InitialiseFunctionTable()
{
	ptr_BeginScene = BeginScene;
	ptr_EndScene = EndScene;
	dword_876C14 = sub_4010E1;
	if (ptr_ctx->buf_z)
	{
		dword_876C08 = sub_40303A;
		dword_876C10 = sub_402BDF;
		dword_876C04 = sub_401A6E;
		dword_876BFC = sub_40138E;
		dword_876C00 = sub_4025D6;
	}
	else
	{
		dword_876C08 = sub_402626;
		dword_876C10 = sub_401F41;
		dword_876C04 = sub_402626;
		dword_876BFC = sub_401F41;
		dword_876C00 = sub_4025D6;
	}
}

int __cdecl sub_401DD4(LPDIRECT3DDEVICE3 a1, int a2, LPD3DRECT a3, char a4, int a5)
{
	if (a1 && a4 & 1)
		memset32(*(void **)(a1 + 20), a5, dword_D9BB8C * dword_D9BB88);
	return 0;
}

DWORD dword_C71370;
int __cdecl sub_4BD5B0(int a1, int a2, int a3, int a4)
{
	/*int result; // eax@1
	int v5; // edi@3
	int *v6; // esi@5
	int v7; // ebx@6
	int v8; // ST18_4@6
	int v9; // edx@6
	int v10; // ecx@6
	bool v11; // sf@6
	unsigned __int8 v12; // of@6
	int v13; // [sp+10h] [bp+10h]@4

	result = HIDWORD(qword_D9AAB0) | qword_D9AAB0;
	if (qword_D9AAB0)
	{
		v5 = a3;
		sub_401D0C(a3, a4, 2, 320);
		result = dword_C71370;
		if (dword_C71370 > 0)
		{
			result = dword_C71370 - 1;
			v13 = 0;
			if (dword_C71370 - 1 > 0)
			{
				v6 = (int *)&unk_C71208;
				do
				{
					v7 = 320 * (v6[1] - *(v6 - 2)) / (signed int)qword_D9AAB0 + v5;
					//j_nullsub_10(*v6, 320 * (v6[1] - *(v6 - 2)) % (signed int)qword_D9AAB0);
					v8 = *v6;
					//j_nullsub_10(v10, v9);
					result = v13 + 1;
					v6 += 3;
					v12 = __OFSUB__(v13 + 1, dword_C71370 - 1);
					v11 = v13 + 1 - (dword_C71370 - 1) < 0;
					v5 = v7;
					++v13;
				} while (v11 ^ v12);
			}
		}
		dword_C71370 = 0;
	}
	else
	{
		dword_C71370 = 0;
	}
	return result;*/
	S_Warn("[sub_4BD5B0] - Unimplemented!\n");
	return 0;
}

int __cdecl TakeScreenshot(LPDIRECTDRAWSURFACE4 *a1, int a2)
{
	S_Warn("[TakeScreenshot] - Unimplemented!\n");
	return 0;
}


int sub_40162C()
{
	int v0; // eax@4
	int v1; // eax@6
	int result; // eax@8
	int v3; // eax@10
	int v4; // eax@11

	if (byte_86BBB4)
		TakeScreenshot(&ptr_ctx->buf_back, "Tomb");
	if (ptr_ctx->buf_primary->lpVtbl->IsLost(ptr_ctx->buf_primary))
	{
		Log(3, "Restored Primary Buffer");
		v0 = ptr_ctx->buf_primary->lpVtbl->Restore(ptr_ctx->buf_primary);
		sub_40179E(v0);
	}
	if (ptr_ctx->buf_back->lpVtbl->IsLost(ptr_ctx->buf_back))
	{
		Log(3, "Restored Back Buffer");
		v1 = ptr_ctx->buf_back->lpVtbl->Restore(ptr_ctx->buf_back);
		sub_40179E(v1);
	}
	if (ptr_ctx->flags & 0x82)
	{
		if (ptr_ctx->flags & 2)
		{
			v3 = ptr_ctx->buf_primary->lpVtbl->Blt(
				ptr_ctx->buf_primary,
				&ptr_ctx->windowPos,
				ptr_ctx->buf_back,
				&ptr_ctx->stru_D9ABBD,
				DDBLT_WAIT,
				NULL);
			result = sub_40179E(v3);
		}
		else
		{
			v4 = ptr_ctx->buf_primary->lpVtbl->Flip(
				ptr_ctx->buf_primary,
				NULL,
				DDFLIP_WAIT);
			result = sub_40179E(v4);
		}
	}
	else
	{
		result = 0;
	}
	return result;
}

signed int sub_4B7DA0()
{
	int v0; // eax@1
	signed int v1; // edi@1
	int v2; // esi@2

			//j_nullsub_19();
	sub_4BD5B0(0, 0, 64, ptr_ctx->height - 32);
	v0 = sub_4D1A40();
	v1 = v0;
	if (v0 < 2)
	{
		v2 = 2 - v0;
		v1 = 2;
		do
		{
			while (!sub_4D1A40())
				;
			--v2;
		} while (v2);
	}
	++GnFrameCounter;
	ptr_EndScene();
	sub_40162C();
	//j_nullsub_19();
	ptr_ctx->dword_D9AC01 = 1;
	return v1;
}


int ClearSurfaces()
{
	int v0; // eax@2
	int v1; // eax@5
	int result; // eax@5
	D3DRECT v3; // [sp+0h] [bp-10h]@1

	v3.x1 = ptr_ctx->stru_D9ABBD.left;
	v3.y1 = ptr_ctx->stru_D9ABBD.top;
	v3.y2 = ptr_ctx->stru_D9ABBD.top + ptr_ctx->stru_D9ABBD.bottom;
	v3.x2 = ptr_ctx->stru_D9ABBD.left + ptr_ctx->stru_D9ABBD.right;
	if (ptr_ctx->flags & 0x80)
	{
		v0 = ptr_ctx->viewport->lpVtbl->Clear2(ptr_ctx->viewport, 1, &v3, 3, 0, 1.0, 0);
		sub_40179E(v0);
	}
	else
	{
		sub_401DD4(ptr_ctx->d3d_dev, 1, &v3, 1, 0);
	}
	sub_4B7DA0();
	if (ptr_ctx->flags & 0x80)
	{
		v1 = ptr_ctx->viewport->lpVtbl->Clear2( ptr_ctx->viewport, 1, &v3, 3, 0, 1.0, 0);
		sub_40179E(v1);
		result = sub_4B7DA0();
	}
	else
	{
		sub_401DD4(ptr_ctx->d3d_dev, 1, &v3, 1, 0);
		result = sub_4B7DA0();
	}
	return result;
}

void __cdecl do_boot_screen(int language)
{
	Log(2, "do_boot_screen");
	switch (language)
	{
	case LNG_ENGLISH:
	case LNG_DUTCH:
		DDCopyBitmap(dxctx.buf_back, "uk.bmp");
		sub_4B7DA0();
		DDCopyBitmap(dxctx.buf_back, "uk.bmp");
		break;
	case LNG_FRENCH:
		DDCopyBitmap(dxctx.buf_back, "france.bmp");
		sub_4B7DA0();
		DDCopyBitmap(dxctx.buf_back, "france.bmp");
		break;
	case LNG_GERMAN:
		DDCopyBitmap(dxctx.buf_back, "germany.bmp");
		sub_4B7DA0();
		DDCopyBitmap(dxctx.buf_back, "germany.bmp");
		break;
	case LNG_ITALIAN:
		DDCopyBitmap(dxctx.buf_back, "italy.bmp");
		sub_4B7DA0();
		DDCopyBitmap(dxctx.buf_back, "italy.bmp");
		break;
	case LNG_SPANISH:
		DDCopyBitmap(dxctx.buf_back, "spain.bmp");
		sub_4B7DA0();
		DDCopyBitmap(dxctx.buf_back, "spain.bmp");
		break;
	case LNG_US:
		DDCopyBitmap(dxctx.buf_back, "usa.bmp");
		sub_4B7DA0();
		DDCopyBitmap(dxctx.buf_back, "usa.bmp");
		break;
	case LNG_JAPAN:
		DDCopyBitmap(dxctx.buf_back, "japan.bmp");
		sub_4B7DA0();
		DDCopyBitmap(dxctx.buf_back, "japan.bmp");
		break;
	default:
		return;
	}
}


unsigned __stdcall GameMain(void* data)
{
	signed int v1; // esi@2

	Log(2, "GameMain");
	if (GameInitialise())
	{
		InitialiseFunctionTable();
		HWInitialise();
		InitWindow(0, 0, ptr_ctx->width, ptr_ctx->height, 20, 20480, 80);
		InitFont();
		TIME_Init();
		ptr_ctx->byte_D9AC19 = 1;
		//v1 = sub_4D30E0(&word_878654);
		S_CDStop();
		ClearSurfaces();
		if (!ptr_ctx->opt_DisableSound)
			SOUND_Init();
		DoGameflow();
		GameClose();
		S_CDStop();
		/*if (v1)
			sub_4D3150();*/ // null sub
		PostMessageA(hWnd, 0x10u, 0, 0);
		dword_876C40 = 0;
		_endthreadex(1u);
	}
	return 1;
	
	S_Warn("[GameMain] - Unimplemented!\n");
	return 0;
}
