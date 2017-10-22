#ifndef FILE_H
#define FILE_H

#include <stdio.h>

int FILE_Load(char* szFileName, void* pDest);
#if INTERNAL
int FILE_Read(char* pDest, int nItemSize, int nItems, int nHandle);
#endif
unsigned long FILE_Length(char* szFileName);
void RelocateModule(unsigned long Module, unsigned long* RelocData);

#endif