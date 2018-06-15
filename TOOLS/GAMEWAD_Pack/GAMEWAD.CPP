#include "GAMEWAD.H"

#include "FILES.H"
#include "IO.H"

#include <cstdio>

namespace TombRaiderChronicles
{
	static GAMEWAD_header gameWad;

	void PackGamewad()
	{
		int currentOffset = 0;

		IO::StreamWriter writer(GAMEWAD_FILENAME);
		char* modData = NULL;

		for (auto i = 0; i < NUM_GAMEWAD_FILE_ENTRIES; i++)
		{
			writer.seek(currentOffset);

			if (i == NONE)
			{
				//SETUP.MOD
				IO::StreamReader reader(gwFileNames[i]);
				if (reader.m_isOpen)
				{
					gameWad.entries[i].fileSize = (int)reader.m_length;
					gameWad.entries[i].fileOffset = currentOffset;
					currentOffset++;//HACK
					currentOffset = (currentOffset + 0x7FF) & ~0x7FF;
					
					if (modData == NULL)
					{
						modData = new char[gameWad.entries[i].fileSize];
						reader.readRaw(modData, gameWad.entries[i].fileSize);
					}

					reader.close();
				}
			}
			else if (i > CUTSEQ && i < RESERVED_17)
			{
				gameWad.entries[i].fileOffset = currentOffset;
				char buf[32];
				sprintf_s(buf, "%s.RAW", gwFileNames[i]);
				IO::StreamReader loadScreenReader(buf);
				char* loadScreenData = new char[(int)loadScreenReader.m_length];
				loadScreenReader.readRaw(loadScreenData, (int)loadScreenReader.m_length);
				gameWad.entries[i].fileSize += loadScreenReader.m_length;
				loadScreenReader.close();
				memset(&buf[0], 0, sizeof(buf));
				writer.write(loadScreenData, (int)loadScreenReader.m_length);
				delete[] loadScreenData;

				sprintf_s(buf, "%s_CD.RAW", gwFileNames[i]);
				IO::StreamReader loadCdReader(buf);
				char* loadCdData = new char[(int)loadCdReader.m_length];
				loadCdReader.readRaw(loadCdData, (int)loadCdReader.m_length);
				gameWad.entries[i].fileSize += loadCdReader.m_length;
				loadCdReader.close();
				memset(&buf[0], 0, sizeof(buf));
				writer.write(loadCdData, (int)loadCdReader.m_length);
				delete[] loadCdData;

				gameWad.entries[i].fileSize += gameWad.entries[NONE].fileSize;
				writer.write(modData, (int)gameWad.entries[NONE].fileSize);

				gameWad.entries[i].fileSize = (gameWad.entries[i].fileSize + 0x7FF) & ~0x7FF;
				writer.seek(((int)writer.m_pos + 0x7FF) & ~0x7FF);

				sprintf_s(buf, "%s.PSX", gwFileNames[i]);
				IO::StreamReader levelReader(buf);
				char* levelData = new char[(int)levelReader.m_length];
				levelReader.readRaw(levelData, (int)levelReader.m_length);
				gameWad.entries[i].fileSize += levelReader.m_length;
				levelReader.close();
				writer.write(levelData, (int)levelReader.m_length);
				delete[] levelData;

				gameWad.entries[i].fileSize = (gameWad.entries[i].fileSize + 0x7FF) & ~0x7FF;
				writer.seek(((int)writer.m_pos + 0x7FF) & ~0x7FF);
				IO::StreamReader codeReader("DATA\\CODE.WAD");
				char* codeData = new char[(int)codeReader.m_length];
				codeReader.readRaw(codeData, (int)codeReader.m_length);
				gameWad.entries[i].fileSize += 0x6901C;
				codeReader.close();
				writer.write(codeData, (int)codeReader.m_length);
				delete[] codeData;

				currentOffset += gameWad.entries[i].fileSize;
				currentOffset = (currentOffset + 0x7FF) & ~0x7FF;
			}
			else if (i > RESERVED_40 && i < UNKNOWN_49)
			{
				gameWad.entries[i].fileOffset = currentOffset;
				char buf[32];
				sprintf_s(buf, "%s.RAW", gwFileNames[i]);
				IO::StreamReader loadScreenReader(buf);
				char* loadScreenData = new char[(int)loadScreenReader.m_length];
				loadScreenReader.readRaw(loadScreenData, (int)loadScreenReader.m_length);
				gameWad.entries[i].fileSize += loadScreenReader.m_length;
				loadScreenReader.close();
				memset(&buf[0], 0, sizeof(buf));
				writer.write(loadScreenData, (int)loadScreenReader.m_length);
				delete[] loadScreenData;

				sprintf_s(buf, "%s_CD.RAW", gwFileNames[i]);
				IO::StreamReader loadCdReader(buf);
				char* loadCdData = new char[(int)loadCdReader.m_length];
				loadCdReader.readRaw(loadCdData, (int)loadCdReader.m_length);
				gameWad.entries[i].fileSize += loadCdReader.m_length;
				loadCdReader.close();
				memset(&buf[0], 0, sizeof(buf));
				writer.write(loadCdData, (int)loadCdReader.m_length);
				delete[] loadCdData;

				currentOffset += gameWad.entries[i].fileSize;
				currentOffset = (currentOffset + 0x7FF) & ~0x7FF;
			}
			else
			{
				//CUTSEQ.JIZ
				IO::StreamReader reader(gwFileNames[i]);
				if (reader.m_isOpen)
				{
					int dataSize = (int)reader.m_length;
					char* fileData = new char[dataSize];
					reader.readRaw(fileData, dataSize);
					gameWad.entries[i].fileSize = dataSize;
					gameWad.entries[i].fileOffset = currentOffset;
					currentOffset = (currentOffset + dataSize + 0x7FF) & ~0x7FF;
					writer.write(fileData, dataSize);
					delete[] fileData;
					reader.close();
				}
			}
		}

		sprintf(&gameWad.reserved[0], "TR5 DATA FILE (C) 2000 Core Design... 'gamewad.asm' Compiled by Del - %s %s", __DATE__, __TIME__);

		writer.seek(0);
		writer.write(&gameWad, sizeof(GAMEWAD_header));
		writer.close();
		delete[] modData;
	}
}
