#include "SAVEGAME.H"
#include "SPECIFIC.H"

char FromTitle;
char JustLoaded;
char* MGSaveGamePtr;
static int SGcount;
static char* SGpoint;
struct savegame_info savegame;

void sgRestoreGame()//55B88, 55FEC
{
	S_Warn("[sgRestoreGame] - Unimplemented!\n");
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

int CheckSumValid(char *buffer)//53720, 53B84
{
	S_Warn("[CheckSumValid] - Unimplemented!\n");
	return 0;
}

void ReadSG(void *pointer, int size)//536E0, 53B44
{
	S_Warn("[ReadSG] - Unimplemented!\n");
}

void WriteSG(void *pointer, int size)//536A0, 53B04
{
	S_Warn("[WriteSG] - Unimplemented!\n");
}

