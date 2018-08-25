#include "GAME.H"
#include "GLOBAL.H"
#include "DISPLAY.H"
#include "DIRECTX.H"
#include "INIT.H"
#include "NEWSHIT.H"
#include "GAMEFLOW.H"
#include "SOUND.H"
#include "DRAWPRIMITIVE.H"

object_info objects[NUMBER_OBJECTS];
static_info static_objects[NUMBER_STATIC_OBJECTS];
LPDIRECT3DVERTEXBUFFER vertex_buffer;
bool game_running;

bool GameInitialise()
{
	Log(LT_Enter, "GameInitialise");

	D3DVERTEXBUFFERDESC buf;
	DXInit(buf);
	buf.dwCaps = 0;
	buf.dwFVF = D3DFVF_TLVERTEX;
	buf.dwNumVertices = 0x2000;

	DX_TRY(App.lpD3D->CreateVertexBuffer(&buf, &vertex_buffer, D3DFVF_XYZRHW, nullptr));

	init_game_malloc();

	App.dword_D9AC38 = 0;
	App.dword_D9AC34 = CUR_DM.w;
	// todo

	init_water_table();

	//InitFX();

	return true;
}

void ClearSurfaces()
{
	D3DRECT rect;

	rect.x1 = App.GnWindowRect.left;
	rect.y1 = App.GnWindowRect.top;
	rect.x2 = App.GnWindowRect.left + App.GnWindowRect.right;
	rect.y2 = App.GnWindowRect.top + App.GnWindowRect.bottom;

	if (App.Flags & WA_BACK_BUFFER)
	{
		DX_TRY(App.lpViewPort->Clear2(1, &rect, 3, 0, 1.0, 0));
	}
	else
	{
		// todo
	}

	S_DumpScreen();

	if (App.Flags & WA_BACK_BUFFER)
	{
		DX_TRY(App.lpViewPort->Clear2(1, &rect, 3, 0, 1.0, 0));
	}
	else
	{
		// todo
	}

	S_DumpScreen();
}

void GameClose()
{
	Log(LT_Enter, "GameClose");

	//ACMClose();

	//FreeLevel();

	DXRelease(vertex_buffer, "Dest VB");

	//free(dword_D9AB34);

	/*if (ptr)
		free(ptr);

	if (bufSource)
		free(bufSource);*/

	free(malloc_buffer);
	free(gfScriptFile);
	free(gfStringOffset);
}

void HWInitialise()
{
	Log(2, "HWInitialise");
	App.lpD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_DISABLE);
	App.lpD3DDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
	App.lpD3DDevice->SetTextureStageState(2, D3DTSS_COLOROP, D3DTOP_DISABLE);
	App.lpD3DDevice->SetTextureStageState(3, D3DTSS_COLOROP, D3DTOP_DISABLE);
	App.lpD3DDevice->SetTextureStageState(4, D3DTSS_COLOROP, D3DTOP_DISABLE);
	App.lpD3DDevice->SetTextureStageState(5, D3DTSS_COLOROP, D3DTOP_DISABLE);
	App.lpD3DDevice->SetTextureStageState(6, D3DTSS_COLOROP, D3DTOP_DISABLE);
	App.lpD3DDevice->SetTextureStageState(7, D3DTSS_COLOROP, D3DTOP_DISABLE);
	App.lpD3DDevice->SetTextureStageState(0, D3DTSS_TEXCOORDINDEX, 0);

	if (App.tBilinearFilter)
	{
		App.lpD3DDevice->SetTextureStageState(0, D3DTSS_MINFILTER, D3DTFN_LINEAR);
		App.lpD3DDevice->SetTextureStageState(0, D3DTSS_MIPFILTER, D3DTFP_NONE);
		App.lpD3DDevice->SetTextureStageState(0, D3DTSS_MAGFILTER, D3DTFG_LINEAR);
	}
	else
	{
		App.lpD3DDevice->SetTextureStageState(0, D3DTSS_MAGFILTER, D3DTFG_POINT);
		App.lpD3DDevice->SetTextureStageState(0, D3DTSS_MINFILTER, D3DTFN_POINT);
		App.lpD3DDevice->SetTextureStageState(0, D3DTSS_MIPFILTER, D3DTFP_NONE);
	}

	App.lpD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	App.lpD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
	App.lpD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	App.lpD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	App.lpD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	App.lpD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
	App.lpD3DDevice->SetTextureStageState(0, D3DTSS_TEXCOORDINDEX, 0);


	App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, FALSE);
	App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_SPECULARENABLE, TRUE);
	App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_CULLMODE, D3DCULL_NONE);
	DX_TRY(App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ZENABLE, TRUE));
	DX_TRY(App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ZWRITEENABLE, TRUE));
	DX_TRY(App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_TEXTUREPERSPECTIVE, TRUE));
	App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_TEXTUREMAPBLEND, D3DTBLEND_MODULATEALPHA);
	App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_FILLMODE, D3DFILL_SOLID);
	App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_DITHERENABLE, TRUE);
	App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ALPHAREF, 0);
	App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ALPHAFUNC, D3DCMP_NOTEQUAL);
	App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA);
	App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA);
	App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ALPHATESTENABLE, FALSE);


	DX_TRY(App.lpD3DDevice->SetLightState(D3DLIGHTSTATE_AMBIENT, 0));
	DX_TRY(App.lpD3DDevice->SetLightState(D3DLIGHTSTATE_COLORVERTEX, 0));
	DX_TRY(App.lpD3DDevice->SetLightState(D3DLIGHTSTATE_COLORMODEL, D3DCOLOR_RGB));
	DX_TRY(App.lpD3DDevice->SetLightState(D3DLIGHTSTATE_FOGMODE, D3DFOG_LINEAR));
	//DX_TRY(App.lpD3DDevice->SetLightState(D3DLIGHTSTATE_FOGSTART, LODWORD(flt_50A438)));
	//DX_TRY(App.lpD3DDevice->SetLightState(D3DLIGHTSTATE_FOGEND, LODWORD(flt_50A43C)));


	App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_FOGCOLOR, RGBA_MAKE(0, 0, 0, 255));
	App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_FOGENABLE, TRUE);
}

unsigned __stdcall GameMain(void* data)
{
	Log(LT_Enter, "GameMain");

	if (!GameInitialise())
	{
		return 0;
	}

	InitialiseFunctionTable();
	HWInitialise();
	InitWindow(0, 0, App.width, App.height, 20, 20480, 80);
	//InitFont();
	TIME_Init();
	App.byte_D9AC19 = 1;
	// todo
	S_CDStop();
	ClearSurfaces();
	if (!App.tDisableSound)
		SOUND_Init();
	DoGameflow();
	GameClose();
	S_CDStop();
	PostMessageA(App.WindowHandle, WM_CLOSE, 0, 0);
	game_running = false;

	return true;
}

void do_boot_screen(int language)
{
	Log(2, "do_boot_screen");

	switch (language)
	{
	case LNG_ENGLISH:
	case LNG_DUTCH:
		DDCopyBitmap(App.lpBackBuffer, "uk.bmp");
		S_DumpScreen();
		DDCopyBitmap(App.lpBackBuffer, "uk.bmp");
		break;
	case LNG_FRENCH:
		DDCopyBitmap(App.lpBackBuffer, "france.bmp");
		S_DumpScreen();
		DDCopyBitmap(App.lpBackBuffer, "france.bmp");
		break;
	case LNG_GERMAN:
		DDCopyBitmap(App.lpBackBuffer, "germany.bmp");
		S_DumpScreen();
		DDCopyBitmap(App.lpBackBuffer, "germany.bmp");
		break;
	case LNG_ITALIAN:
		DDCopyBitmap(App.lpBackBuffer, "italy.bmp");
		S_DumpScreen();
		DDCopyBitmap(App.lpBackBuffer, "italy.bmp");
		break;
	case LNG_SPANISH:
		DDCopyBitmap(App.lpBackBuffer, "spain.bmp");
		S_DumpScreen();
		DDCopyBitmap(App.lpBackBuffer, "spain.bmp");
		break;
	case LNG_US:
		DDCopyBitmap(App.lpBackBuffer, "usa.bmp");
		S_DumpScreen();
		DDCopyBitmap(App.lpBackBuffer, "usa.bmp");
		break;
	case LNG_JAPAN:
		DDCopyBitmap(App.lpBackBuffer, "japan.bmp");
		S_DumpScreen();
		DDCopyBitmap(App.lpBackBuffer, "japan.bmp");
		break;
	}
}

void UpdateSky()
{
	Unimpl();
}