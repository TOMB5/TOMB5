#ifndef SAVEGAME_H
#define SAVEGAME_H

#include "SPECTYPES.H"

extern char FromTitle;
extern char JustLoaded;
extern char* MGSaveGamePtr;
extern struct savegame_info savegame;

extern void sgRestoreGame();
extern void sgSaveGame();
extern void RestoreLevelData(int FullSave);
extern void SaveLevelData(int FullSave);
extern void RestoreLaraData(int FullSave);
extern void SaveLaraData();
extern int CheckSumValid(char* buffer);
extern void ReadSG(char* pointer, int size);
extern void WriteSG(char* pointer, int size);

#endif