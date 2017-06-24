#ifndef FILE_H
#define FILE_H

int FILE_Load(char* szFileName, void* pDest);
int FILE_Read(void* pDest, int nItemSize, int nItems, int nHandle);
unsigned long FILE_Length(char* szFileName);
void RelocateModule(unsigned long Module, unsigned long* RelocData);

#endif