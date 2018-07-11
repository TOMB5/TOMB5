#include "GAME.H"
#include "GLOBAL.H"
#include "DISPLAY.H"
#include "DIRECTX.H"
#include "INIT.H"

struct object_info objects[NUMBER_OBJECTS];
struct static_info static_objects[NUMBER_STATIC_OBJECTS];
LPDIRECT3DVERTEXBUFFER vertex_buffer;

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

	return true;
}

unsigned __stdcall GameMain(void* data)
{
	Log(LT_Enter, "GameMain");

	if (!GameInitialise())
	{
		return 0;
	}

	/*InitialiseFunctionTable();
	HWInitialise();*/
	InitWindow(0, 0, App.width, App.height, 20, 20480, 80);

	return true;
}