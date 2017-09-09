#ifndef FILE_H
#define FILE_H

#include <stdio.h>

extern FILE *FileOpen(const char *filename);
extern int FileClose(FILE *fp);
extern int LoadFile(char* szFileName, void** pDest);
extern int FILE_Read(void* pDest, int nItemSize, int nItems, FILE* nHandle);
extern unsigned long FileLength(FILE* nHandle);
extern size_t fread_ex(void *ptr, size_t size, size_t count, FILE *stream);

#endif
