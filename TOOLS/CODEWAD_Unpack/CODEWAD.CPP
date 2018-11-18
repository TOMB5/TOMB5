#include "CODEWAD.H"
#include "FILES.H"
#include "IO.H"

#include <stdio.h>
#include <stdlib.h>
#include <string>

char wadHeader[NUM_OVERLAYS*sizeof(fileEntry)];

void CODEWAD_Unpack(const char* fileName)
{
	fileEntry* entry = (fileEntry*)&wadHeader[0];
	
	IO::StreamReader reader(fileName);
	if (!reader.m_isOpen)
	{
		printf("Warning: failed to open file: %s\n", fileName);
		return;
	}

	reader.readRaw(&wadHeader[0], NUM_OVERLAYS*sizeof(fileEntry));

	for(int i = 0; i < NUM_OVERLAYS; i++)
	{
		char nameBin[32];
		char nameRel[32];

		memset(&nameBin[0], 0, 32);
		memset(&nameRel[0], 0, 32);

		strcat(&nameBin[0], cwFileNames[i]); 
		strcat(&nameRel[0], cwFileNames[i]); 

		strcat(&nameBin[0], ".BIN"); 
		strcat(&nameRel[0], ".REL"); 

		printf("Name: %s, Name: %s Index: %i\n", &nameBin[0], &nameRel[0], entry[i].moduleIndex);

		CODEWAD_DumpOverlay(&nameBin[0], &reader, &entry[i].binData[0]);
		CODEWAD_DumpOverlay(&nameRel[0], &reader, &entry[i].relData[0]);

		printf("Offset: %i, Size: %i Index: %i\n", entry[i].binData[0], entry[i].binData[1], entry[i].moduleIndex);
	}

	reader.close();
}

void CODEWAD_DumpOverlay(char* fileName, IO::StreamReader* reader, unsigned int* entry)
{
	IO::StreamWriter writer(fileName);

	char* buffer = new char[entry[1]];

	reader->seek(entry[0]);
	reader->readRaw(&buffer[0], entry[1]);
	writer.write(buffer, entry[1]);
	writer.close();

	delete[] buffer;
}


