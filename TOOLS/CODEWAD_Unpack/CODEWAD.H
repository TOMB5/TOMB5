#ifndef CODEWAD_H
#define CODEWAD_H

#include <stdio.h>

#define NUM_OVERLAYS 59

typedef struct
{
	unsigned int binData[2];//Offset, Size
	unsigned int relData[2];//Offset, Size
	unsigned int padding;
}fileEntry;

extern void CODEWAD_Unpack(const char* fileName);
extern void CODEWAD_DumpOverlay(char* fileName, FILE* fr, unsigned int* entry);

#endif