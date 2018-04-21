#ifndef FILE_H
#define FILE_H

#ifdef __cplusplus
extern "C" {
#endif

	int 		S_LoadLevelFile(int Name);
	int LoadFile(char* szFileName, void** pDest);
	int FindCdDrive(void);


#ifdef __cplusplus
}
#endif

extern short* floor_data;
extern short* mesh_base;

extern int AnimFileLen;

#endif