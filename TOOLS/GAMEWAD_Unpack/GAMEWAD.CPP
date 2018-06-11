#include "GAMEWAD.H"

#include "FILES.H"
#include "IO.H"

#include <cstdio>

namespace TombRaiderChronicles
{
	static GAMEWAD_header gameWad;

	void UnpackGamewad(const char* fileName)
	{
		IO::StreamReader reader(fileName);
		if (!reader.m_isOpen)
		{
			printf("Warning: failed to open file: %s\n", fileName);
		}
		char* fileData = new char[NUM_GAMEWAD_FILE_ENTRIES * sizeof(GAMEWAD_entry)];
		reader.readRaw(fileData, NUM_GAMEWAD_FILE_ENTRIES * sizeof(GAMEWAD_entry));
		GAMEWAD_entry* entry = (GAMEWAD_entry*)fileData;

		for (int i = 0; i < NUM_GAMEWAD_FILE_ENTRIES; i++, entry++)
		{
			
			printf("%i\n", entry->fileOffset);
		}

		delete[] fileData;
	}
}
