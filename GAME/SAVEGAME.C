#include "SAVEGAME.H"

#include "CONTROL.H"
#include "GAMEFLOW.H"
#include "SPECIFIC.H"
#include "TYPES.H"

#include <string.h>

char FromTitle;
char JustLoaded;
char* MGSaveGamePtr;
static int SGcount;
static char* SGpoint;
struct savegame_info savegame;

void sgRestoreGame()//55B88, 55FEC (F)
{
	SGcount = 0;
#ifdef PSX_VERSION
	SGpoint = &MGSaveGamePtr[436];
#else
	SGpoint = &MGSaveGamePtr[sizeof(savegame_info)];
#endif
	GameTimer = savegame.Game.Timer;
	gfCurrentLevel = savegame.CurrentLevel;

	RestoreLevelData(1);
	RestoreLaraData(1);
}

void sgSaveGame()//55AF8(<), 55F5C(<)
{
#ifdef PSX_VERSION
	SGpoint = &MGSaveGamePtr[436];
#else
	SGpoint = &MGSaveGamePtr[sizeof(savegame_info)];
#endif

	SGcount = 0;

	savegame.CurrentLevel = gfCurrentLevel;
	SaveLevelData(1);

	savegame.Game.Timer = GameTimer;
	SaveLaraData();

	MGSaveGamePtr[7678] = GetRandomControl();
	
#ifdef PSX_VERSION
	memcpy(&MGSaveGamePtr, &savegame, 436);
#else
	memcpy(&MGSaveGamePtr, &savegame, sizeof(savegame_info));
#endif
	savegame.Checksum = GameTimer;

	return;
}

void RestoreLevelData(int FullSave)//54B08, 54F6C
{
	S_Warn("[RestoreLevelData] - Unimplemented!\n");
}

void SaveLevelData(int FullSave)//53AAC, 53F10
{
	S_Warn("[SaveLevelData] - Unimplemented!\n");
}

void RestoreLaraData(int FullSave)//538D0, 53D34
{
	S_Warn("[RestoreLaraData] - Unimplemented!\n");
}

void SaveLaraData()//53738, 53B9C
{
	S_Warn("[SaveLaraData] - Unimplemented!\n");
}

int CheckSumValid(char *buffer)//53720(<), 53B84(<) (F)
{
	return *(short*)buffer ^ *(short*)(buffer + 0x1DFE) < 1;
}

void ReadSG(char* pointer, int size)//536E0, 53B44 (F)
{
	SGcount += size;
	
	if (size > 0)
	{
		while (size-- > 0)
		{
			*pointer++ = *SGpoint++;
		}
	}

	return;
}

void WriteSG(char* pointer, int size)//536A0, 53B04
{
	SGcount += size;

	if (size > 0)
	{
		while (size-- > 0)
		{
			*SGpoint++ = *pointer++;
		}
	}
}