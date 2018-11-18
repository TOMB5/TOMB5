#ifndef CODEWAD_H
#define CODEWAD_H

#include <stdio.h>
#include "IO.H"

#define NUM_OVERLAYS 59

struct fileEntry
{
	unsigned int binData[2];//Offset, Size
	unsigned int relData[2];//Offset, Size
	unsigned int moduleIndex;
};

extern void CODEWAD_Unpack(const char* fileName);
extern void CODEWAD_DumpOverlay(char* fileName, IO::StreamReader* reader, unsigned int* entry);

#endif