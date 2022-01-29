#ifndef FILE_H
#define FILE_H

#include <stdio.h>

extern int FILE_Load(char* szFileName, void* pDest);
extern unsigned long FILE_Length(char* szFileName);
#if !DISC_VERSION
extern int FILE_Read(char* pDest, int nItemSize, int nItems, int nHandle);
#endif
extern void RelocateModule(unsigned long Module, unsigned long* RelocData);

#endif