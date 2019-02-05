#ifndef FILE_H
#define FILE_H

#include <stdio.h>

extern int FILE_Load(char* szFileName, void* pDest);
extern unsigned long FILE_Length(char* szFileName);
#if !DISC_VERSION
extern int FILE_Read(char* pDest, int nItemSize, int nItems, uintptr_t nHandle);
#endif
extern void RelocateModule(uintptr_t Module, unsigned int* RelocData);

#endif