#ifndef ROOMLOAD_H
#define ROOMLOAD_H

extern long AnimFilePos;
extern long AnimFileLen;
extern short* floor_data;
extern short* mesh_base;

extern void S_LoadLevelFile(int Name);
extern void FreeLevel();

#endif