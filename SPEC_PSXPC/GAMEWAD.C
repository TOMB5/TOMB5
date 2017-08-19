#include "GAMEWAD.H"

#include "CD.H"

#include <stdio.h>
#include <assert.h>

//Holds all game data file positions or offsets in GAMEWAD.OBJ.
struct GAMEWAD_header gwHeader;

//LBA for the GAMEWAD.OBJ file on disc, this is set by InitNewCDSystem(), CDPosToInt() (See CD.C)
int gwLba = 0;

//Start sector for the current gamewad file entry.
static int gwReaderStartSector = 0;

//Current sector for the gamewad file entry, updated as data is read from disk.
static int gwReaderCurrentSector = 0;

/*
 * [FUNCTIONALITY] - GAMEWAD_InitialiseReaderPosition.
 * GAMEWAD_header is already in the memory at this point, we loaded it during InitNewCDSystem() (See CD.C)
 * This method initialises the GAMEWAD read sector for a specific gamewad entry.
 * File ID indices must match GAMEWAD.OBJ, see gw_files enum (GAMEWAD.H)
 * Note: A File ID of "NONE" or 0 will initialise the reader position back to 0.
 *
 * [USAGE]
 * @PARAM - [fileID] index into GAMEWAD_header.entries you wish to seek to.
 * @RETURN - Filesize of the gamewad entry in bytes.
 */

int GAMEWAD_InitialiseReaderPosition(int fileID /*$a0*/)//*, 5E3C0(<) (F)
{
	//DEL_ChangeCDMode(0);

	//Converting to multiples CD_SECTOR_SIZE since PSX legacy CD routines require the number of sectors to be read
	//Not the actual file size of the file itself.
	int relativeFileSector = gwHeader.entries[fileID].fileOffset / CD_SECTOR_SIZE;

#ifdef PSX
	gwReaderCurrentSector = gwReaderStartSector = gwLba + relativeFileSector;
#else
	gwReaderCurrentSector = gwReaderStartSector = relativeFileSector;
#endif

	return gwHeader.entries[fileID].fileSize;
}

/*
 * [FUNCTIONALITY] - GAMEWAD_Read
 * It is assumed that prior to calling this you have initialised the gamewad
 * reader's position to the file entry you wish to read see (GAMEWAD_InitialiseReaderPosition)
 * This method reads data from GAMEWAD.OBJ at it's last read position.
 *
 * [USAGE]
 * @PARAM - [fileSize] the number of bytes you wish to read [ptr] the initialised memory location the data is read to. 
 */

void GAMEWAD_Read(int fileSize/*$s1*/, char* ptr/*$a0*/)//*, 5E414(<) (F)
{
#ifndef PSX
	FILE* fileHandle = NULL;
	int i;

	//jal sub_5E650 //DEL_ChangeCDMode(?);

	fileHandle = fopen(GAMEWAD_FILENAME, "rb");
	assert(fileHandle);
	fseek(fileHandle, gwReaderCurrentSector * CD_SECTOR_SIZE, SEEK_SET);

	int numSectorsToRead = fileSize / CD_SECTOR_SIZE;

	if (numSectorsToRead != 0)
	{
#ifdef PSX
		//jal sub_6915C //CdIntToPos(?, ?);
		//jal sub_6956C //CdControlF(0);
		//jal sub_69C4C //CdRead(?, ?, ?);
#endif
		for(i = 0; i < numSectorsToRead; i++)
		{
#ifdef PSX
			//jal sub_69DE8 //CdReadSync(?);
#endif
			ptr += fread(ptr, 1, CD_SECTOR_SIZE, fileHandle);
		}
		
		gwReaderCurrentSector += numSectorsToRead;
	}

	//Another chunk that is not multiple of 2048 bytes exists, read it
	if ((fileSize & 0x7FF) != 0)//%
	{

#ifdef PSX
		//jal sub_6915C //CdIntToPos(?, ?);
		//jal sub_6956C //CdControlF(?);
		//jal sub_69C4C //CdRead(?, ?, ?);
		//jal sub_69DE8 //CdReadSync(?);
#endif

		ptr += fread(ptr, 1, fileSize - (numSectorsToRead * CD_SECTOR_SIZE), fileHandle);
		fclose(fileHandle);
		gwReaderCurrentSector++;
	}

	fclose(fileHandle);
#endif
}

/*
 * [FUNCTIONALITY] - GAMEWAD_Seek
 * Seeks from the gamewad reader's current position.
 * Note: Negative numbers will allow backwards traversal.
 * [USAGE]
 * @PARAM - [offset] the number of bytes you wish to seek (not in sectors).
 */

void GAMEWAD_Seek(int offset /*$a0*/)//*, 5E54C(<) (F)
{
	gwReaderCurrentSector = gwReaderStartSector + (offset / CD_SECTOR_SIZE);
}

/*
 * [FUNCTIONALITY] - GAMEWAD_ReaderPositionToCurrent
 * Updates the gamewad reader's start sector to current reader position. 
 */

void GAMEWAD_ReaderPositionToCurrent()//*, 5E564(<) (F)
{
	gwReaderStartSector = gwReaderCurrentSector;
}
