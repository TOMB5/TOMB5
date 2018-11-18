#include "CODEWAD.H"
#include "FILES.H"
#include "IO.H"
#include "CD.H"

#include <stdio.h>
#include <stdlib.h>
#include <string>

char wadHeader[NUM_OVERLAYS * sizeof(fileEntry)];

void CODEWAD_Pack(const char* fileName)
{
	fileEntry* entry = (fileEntry*)&wadHeader[0];
	int currentOffset = (sizeof(wadHeader) + (CD_SECTOR_SIZE - 1) & ~(CD_SECTOR_SIZE - 1));
	IO::StreamWriter writer("CODE.WAD");

	for (int i = 0; i < NUM_OVERLAYS; i++, entry++)
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

		IO::StreamReader readerBin(&nameBin[0]);
		IO::StreamReader readerRel(&nameRel[0]);
		
		if (!readerBin.m_isOpen)
		{
			printf("Warning: failed to open file: %s\n", &nameBin[0]);
			return;
		}

		if (!readerRel.m_isOpen)
		{
			printf("Warning: failed to open file: %s\n", &nameRel[0]);
			return;
		}
		
		entry->moduleIndex = moduleIndices[i];

		currentOffset = (currentOffset + (CD_SECTOR_SIZE - 1) & ~(CD_SECTOR_SIZE - 1));
		entry->binData[0] = currentOffset;
		entry->binData[1] = readerBin.m_length;
		currentOffset += entry->binData[1];

		currentOffset = (currentOffset + (CD_SECTOR_SIZE - 1) & ~(CD_SECTOR_SIZE - 1));
		entry->relData[0] = currentOffset;
		entry->relData[1] = readerRel.m_length;
		currentOffset += entry->relData[1];

		CODEWAD_WriteOverlay(&writer, &readerBin, entry->binData[0]);
		CODEWAD_WriteOverlay(&writer, &readerRel, entry->relData[0]);

		printf("Offset: %i, Size: %i\n", entry[i].binData[0], entry[i].binData[1]);

		readerBin.close();
		readerRel.close();
	}

	writer.seek(0);
	writer.write(wadHeader, sizeof(wadHeader));
	writer.close();
}

void CODEWAD_WriteOverlay(IO::StreamWriter* writer, IO::StreamReader* reader, unsigned int offset)
{
	char* buffer = new char[reader->m_length];
	reader->readRaw(&buffer[0], reader->m_length);
	writer->seek(offset);
	writer->write(buffer, reader->m_length);
	delete[] buffer;
}


