#ifndef FILE_H
#define FILE_H

#include "WINMAIN.H"
#include <cstdio>

extern FILE *FileOpen(const char *filename);
extern int FileClose(FILE *fp);

#endif
