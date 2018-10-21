#ifndef FILE_H
#define FILE_H
#include <cstdio>
#include "SPECTYPES.H"
#ifdef __cplusplus
extern "C" {
#endif

	int 		S_LoadLevelFile(int Name);
	int LoadFile(char* szFileName, void** pDest);
	int FindCdDrive(void);
	FILE* FileOpen(const char *filename);
	int FileClose(FILE* fp);
	unsigned long FileLength(FILE* nHandle);
	void FreeD3DLights();
	void FreeLevel();
	NEW_CUTSCENE* FetchCutData(int num);

#ifdef __cplusplus
}
#endif

extern short* floor_data;
extern short* mesh_base;

extern int num_pages;
extern bool levelLoading;

extern int AnimFileLen;

#endif