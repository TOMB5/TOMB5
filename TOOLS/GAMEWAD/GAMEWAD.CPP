#include "GAMEWAD.H"

#include "FILES.H"
#include "IO.H"

#include <cstdio>

namespace TombRaiderChronicles
{
	static GAMEWAD_header gameWad;

	void InitialiseGamewadToc()
	{
		int currentOffset = 0;

		for (auto i = 0; i < NUM_GAMEWAD_FILE_ENTRIES; i++)
		{
			IO::StreamReader reader(gwFileNames[i]);

			if (reader.m_isOpen)
			{
				gameWad.entries[i].fileSize = reader.m_length;
				gameWad.entries[i].fileOffset = currentOffset;
				
				//Hack SETUP.MOD is not written to first entry, only size is stored thus we don't want to alter currentOffset with this hack.
				if (i == 0)
				{
					reader.m_length = 1;
				}
				//HACK Inject loading screen image before [level.psx] and CODE.WAD

				currentOffset = ((currentOffset + reader.m_length) + (CD_SECTOR_SIZE - 1)) & ~(CD_SECTOR_SIZE - 1);
			}

			reader.close();
		}

		sprintf(&gameWad.reserved[0], "TR5 DATA FILE (C) 2000 Core Design... 'gamewad.asm' Compiled by Del - %s %s", __DATE__, __TIME__);
	}

	void WriteGamewad()
	{
		IO::StreamWriter writer(GAMEWAD_FILENAME);
		writer.write(gameWad);
		writer.close();
	}
}
