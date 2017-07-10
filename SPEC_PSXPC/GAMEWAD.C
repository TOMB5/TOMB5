#include "GAMEWAD.H"

#include "CD.H"
#include "FILE.H"
#include "MALLOC.H"

#include <assert.h>

struct GAMEWAD_header gwHeader;

int gwLba = 0;
int dword_A563C;
int dword_A5620;

int GAMEWAD_InitialiseFileEntry(int fileID /*$a0*/)//*, 5E3C0(<)
{
	//DEL_ChangeCDMode(0);

	int relativeFileSector = gwHeader.entries[fileID].fileOffset / CD_SECTOR_SIZE;

#ifdef PSX
	dword_A5620 = dword_A563C = gwLba + relativeFileSector;
#else
	dword_A5620 = dword_A563C = relativeFileSector;
#endif

	return gwHeader.entries[fileID].fileSize;
}

void GAMEWAD_Load(int fileSize, char* ptr)//*, 5E414(<)
{
	//jal sub_5E650 //DEL_ChangeCDMode(?);

	FILE* fileHandle = fopen(GAMEWAD_FILENAME, "rb");
	assert(fileHandle);
	fseek(fileHandle, dword_A5620 * CD_SECTOR_SIZE, SEEK_SET);

	int numSectorsToRead = fileSize / CD_SECTOR_SIZE;

	if (numSectorsToRead != 0)
	{
		//jal sub_6915C //CdIntToPos(?, ?);
		//jal sub_6956C //CdControlF(0);
		//jal sub_69C4C //CdRead(?, ?, ?);

		for(int i = 0; i < numSectorsToRead; i++)
		{
			//jal sub_69DE8 //CdReadSync(?);
			ptr += fread(ptr, 1, CD_SECTOR_SIZE, fileHandle);
		}
		
		dword_A5620 += numSectorsToRead;
	}

	//Another chunk that is not multiple of 2048 bytes exists, read it
	if ((fileSize & 0x7FF) != 0)
	{

#ifdef PSX
		//jal sub_6915C //CdIntToPos(?, ?);
		//jal sub_6956C //CdControlF(?);
		//jal sub_69C4C //CdRead(?, ?, ?);
		//jal sub_69DE8 //CdReadSync(?);
#endif

		ptr += fread(ptr, 1, fileSize - (numSectorsToRead * CD_SECTOR_SIZE), fileHandle);
		fclose(fileHandle);
		dword_A5620++;
	}

	fclose(fileHandle);
}

//Looks like seek
void GAMEWAD_SeekCurrent(int size /*$a0*/)//*, 5E54C(<)
{
	dword_A5620 = dword_A563C + (size / CD_SECTOR_SIZE);
}