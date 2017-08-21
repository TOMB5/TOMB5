#include "SAVEGAME.H"

#include "GAMEFLOW.H"
#include "SPECIFIC.H"

char FromTitle;
char JustLoaded;
char* MGSaveGamePtr;
static int SGcount;
static char* SGpoint;
struct savegame_info savegame;

void sgRestoreGame()//55B88, 55FEC (F)
{
	SGcount = 0;
	SGpoint = &MGSaveGamePtr[436];

	GameTimer = savegame.Game.Timer;
	gfCurrentLevel = savegame.CurrentLevel;

	RestoreLevelData(1);
	RestoreLaraData(1);
}

void sgSaveGame()//55AF8, 55F5C
{
	S_Warn("[sgSaveGame] - Unimplemented!\n");
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

int CheckSumValid(char* buffer)//53720, 53B84
{
	return (*(short*) buffer[0]) ^ (*(short*) buffer[7678]) < 1 ? 1 : 0;
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
	S_Warn("[WriteSG] - Unimplemented!\n");
}

