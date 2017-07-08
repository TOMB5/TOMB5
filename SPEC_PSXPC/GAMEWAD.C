#include "GAMEWAD.H"

#include "CD.H"
#include "FILE.H"
#include "MALLOC.H"

struct GAMEWAD_header gwHeader;

int gwAlignment = 0;
int dword_A563C;
int dword_A5620;

int GAMEWAD_InitialiseFileEntry(int fileID /*$a0*/)//*, 5E3C0(<)
{
	//DEL_ChangeCDMode(0);

	int fileOffset = gwHeader.entries[fileID].fileOffset / CD_SECTOR_SIZE;
	dword_A5620 = dword_A563C = gwAlignment + fileOffset;

	return gwHeader.entries[fileID].fileSize;
}

void GAMEWAD_Load(int fileSize, char* ptr)//*, 5E414(<)
{
	//jal sub_5E650 //DEL_ChangeCDMode(?);

	int numBlocksToRead = fileSize / CD_SECTOR_SIZE;

	if (numBlocksToRead != 0)
	{
		//jal sub_6915C //CdIntToPos(?, ?);
		//jal sub_6956C //CdControlF(0);
		//jal sub_69C4C //CdRead(?, ?, ?);

		FILE* fileHandle = fopen(GAMEWAD_FILENAME, "rb");
		fseek(fileHandle, dword_A5620 * CD_SECTOR_SIZE, SEEK_SET);

#if 1 //FIXME: I'm not sure why CdReadSync is reading a completely different file entry (6), possible hardcoded sector? see CdRead();
		char* tmpptr = malloc_ptr;
		while (numBlocksToRead > 0)
		{
			//jal sub_69DE8 //CdReadSync(?);

			//Illegal did not game malloc?
			tmpptr += fread(tmpptr, 1, CD_SECTOR_SIZE, fileHandle);
			numBlocksToRead--;
		}
#endif

		fclose(fileHandle);
		dump_game_malloc();
		dword_A5620 += numBlocksToRead;

		if ((fileSize & 0x7FF) != 0)
		{
			//0x5E4B4
		}

		//0x5E528
	}
}