#include "GAME.H"
#include "SPECIFIC.H"
#include "../GAME/MALLOC.H"

extern void GameClose()
{
	/*int v0; // eax@2

	sub_4DEB10(2, "GameClose");
	sub_402F8B();
	j_FreeLevel();
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
	free(dword_E5C2EC);
	free(dword_E5C2AC);*/

	S_Warn("[GameClose] - Unimplemented!\n");
}

extern char GameInitialise()
{
	S_Warn("[GameInitialise] - Unimplemented!\n");
}

extern int GameMain(int a1, int a2)
{
	S_Warn("[GameMain] - Unimplemented!\n");
}
