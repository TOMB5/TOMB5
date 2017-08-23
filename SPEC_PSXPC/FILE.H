#ifndef FILE_H
#define FILE_H

#include <stdio.h>

int FILE_Load(char* szFileName, void* pDest);
int FILE_Read(void* pDest, int nItemSize, int nItems, FILE* nHandle);//5E6A8, 

unsigned long FILE_Length(char* szFileName);
void RelocateModule(unsigned long Module, unsigned long* RelocData);

#endif