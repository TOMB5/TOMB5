#include "GAME.H"
#include "SPECIFIC.H"
#include "MALLOC.H"
#include "OBJECTS.H"
#include "GAMEFLOW.H"
#include "ROOMLOAD.H"
#include "WINMAIN.H"
#include "ERROR.H"

struct object_info objects[NUMBER_OBJECTS];
struct static_info static_objects[NUMBER_STATIC_OBJECTS];

void GameClose()
{
	/*int v0; // eax@2

	sub_4DEB10(2, "GameClose");
	sub_402F8B();
	FreeLevel();
	if (dword_D9AAC8)
	{
		v0 = (*(int(__stdcall **)(int))(*(_DWORD *)dword_D9AAC8 + 8))(dword_D9AAC8);
		sub_4DEB10(4, "Released %s @ %x - RefCnt = %d", "Dest VB", dword_D9AAC8, v0);
		dword_D9AAC8 = 0;
	}
	else
	{
		sub_4DEB10(1, "%s Attempt To Release NULL Ptr", "Dest VB");
	}
	free(dword_D9AB34);
	if (ptr)
		free(ptr);
	if (dword_57A008)
		free(dword_57A008);
	free(malloc_buffer);
	free(gfScriptFile);
	free(gfStringOffset);
	*/
	S_Warn("[GameClose] - Unimplemented!\n");
}

char GameInitialise()
{
	D3DVERTEXBUFFERDESC vb;
	sub_4DEB10(2, "GameInitialise");
	vb.dwCaps = 0;
	vb.dwSize = 16;
	vb.dwFVF = 452;
	vb.dwNumVertices = 0x2000;
	int res = ptr_crctx->d3d->lpVtbl->CreateVertexBuffer(ptr_crctx->d3d, &vb, &vertexBuffer, 4, 0);
	sub_40179E(res);
	init_game_malloc();

	S_Warn("[GameInitialise] - Unimplemented!\n");
	return 0;
}

unsigned __stdcall GameMain(void* data)
{
	S_Warn("[GameMain] - Unimplemented!\n");
	return 0;
}
