#ifndef FILE_H
#define FILE_H

#include <stdio.h>

int FILE_Load(char* szFileName, void* pDest);
#ifndef PSX
int FILE_Read(void* pDest, int nItemSize, int nItems, FILE* nHandle);//5E6A8, 
#else
int FILE_Read(void* pDest, int nItemSize, int nItems, int nHandle);//5E6A8, 
#endif

unsigned long FILE_Length(char* szFileName);
void RelocateModule(unsigned long Module, unsigned long* RelocData);

#endif