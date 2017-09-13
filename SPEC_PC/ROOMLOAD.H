#ifndef ROOMLOAD_H
#define ROOMLOAD_H
#include <stdio.h>
#include "SPECIFIC.H"
extern long AnimFilePos;
extern long AnimFileLen;
extern short* floor_data;
extern short* mesh_base;
extern FILE* fp_level;
extern DWORD dword_51CAC0[32];

extern void S_LoadLevelFile(int Name);
extern void FreeLevel();

#endif