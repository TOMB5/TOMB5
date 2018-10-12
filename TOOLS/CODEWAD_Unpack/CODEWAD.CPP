#include "CODEWAD.H"
#include "FILES.H"

#include <stdio.h>
#include <stdlib.h>
#include <string>

char wadHeader[NUM_OVERLAYS*sizeof(fileEntry)];

void CODEWAD_Unpack(const char* fileName)
{
	FILE* f = fopen(fileName, "rb");
	fileEntry* entry = (fileEntry*)&wadHeader[0];
	int i;
	

	if(f == NULL)
	{
		printf("Failed to open file: %s\n", fileName);
		return;
	}

	fread(&wadHeader[0], 1, NUM_OVERLAYS*sizeof(fileEntry), f);

	for(i = 0; i < NUM_OVERLAYS; i++)
	{
		char nameBin[32];
		char nameRel[32];

		memset(&nameBin[0], 0, 32);
		memset(&nameRel[0], 0, 32);

		strcat(&nameBin[0], cwFileNames[i]); 
		strcat(&nameRel[0], cwFileNames[i]); 

		strcat(&nameBin[0], ".BIN"); 
		strcat(&nameRel[0], ".REL"); 

		printf("Name: %s, Name: %s\n", &nameBin[0], &nameRel[0]);

		CODEWAD_DumpOverlay(&nameBin[0], f, &entry[i].binData[0]);
		CODEWAD_DumpOverlay(&nameRel[0], f, &entry[i].relData[0]);

		printf("Offset: %i, Size: %i\n", entry[i].binData[0], entry[i].binData[1]);
	}

	fclose(f);
}

void CODEWAD_DumpOverlay(char* fileName, FILE* fr, unsigned int* entry)
{
	FILE* f = fopen(fileName, "wb");

	char* buffer = new char[entry[1]];

	fseek(fr, entry[0], SEEK_SET);
	fread(&buffer[0], 1, entry[1], fr);
	fwrite(&buffer[0], 1, entry[1], f);
	fclose(f);

	delete[] buffer;
}


