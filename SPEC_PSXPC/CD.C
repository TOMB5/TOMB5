#include "CD.H"

#include "CONTROL.H"
#include "SPECIFIC.H"

#include <stdio.h>
#include <string.h>
#include <assert.h>

#include <stdio.h>
#include <assert.h>

//Number of XA files on disc (XA1-17.XA)
#define NUM_XA_FILES 17

#define XA_FILE_NAME "XA%d.XA"

unsigned short XATrackClip[] =
{
	0xFF00, 0xFF00, 0xFE80, 0xFF00, 0xFF00, 0xFF00, 0xFF00, 0xFF80,
	0xFF00, 0xFF00, 0xFF00, 0xFF00, 0xFF00, 0xFF00, 0xFF00, 0xFF00,
	0xFE80, 0xFF00, 0xFF00, 0xFF00, 0xFF00, 0xFF00, 0xFF80, 0xFF80,
	0xFE00, 0xFF00, 0xFF00, 0xFF00, 0xFF00, 0xFE00, 0xFF80, 0xFF80,
	0xFF00, 0xFF00, 0xFF80, 0xFF80, 0xFF00, 0xFF00, 0xFF00, 0xFF80,
	0xFF80, 0xFE00, 0xFF80, 0xFF00, 0xFF80, 0xFF80, 0xFF80, 0xFF80,
	0xFF00, 0xFF00, 0xFF80, 0xFF80, 0xFF80, 0xFF80, 0xFF80, 0xFF00,
	0xFE00, 0xFF00, 0xFF80, 0xFF80, 0xFF80, 0xFF80, 0xFF00, 0xFF80,
	0xFE00, 0xFD80, 0xFD80, 0xFE80, 0xFE80, 0xFE80, 0xFF00, 0xFF80,
	0xFA00, 0xFC00, 0xFC00, 0xFC00, 0xFD80, 0xFF00, 0xFE00, 0xFF80,
	0xFE00, 0xFE00, 0xFD80, 0xFE80, 0xFF00, 0xFF00, 0xFF00, 0xFF00,
	0xFA00, 0xFB00, 0xFC00, 0xFB80, 0xFC80, 0xFC80, 0xFF00, 0xFFC0,
	0xFC00, 0xFD00, 0xFD00, 0xFD00, 0xFE80, 0xFE80, 0xFF00, 0xFF80,
	0xF700, 0xF880, 0xF780, 0xFC80, 0xFE80, 0xFE80, 0xFD80, 0xFE80,
	0xEF80, 0xF000, 0xF280, 0xF480, 0xF700, 0xFD80, 0xFD00, 0xFF80,
	0xF880, 0xFD80, 0xFD00, 0xFE00, 0xFE80, 0xFF40, 0xFF80, 0xFF80,
	0xD200, 0xD500, 0xD600, 0xD880, 0xD880, 0xDB80, 0xE900, 0xFE80
};

short XAFadeRate = 8;
int current_cd_mode = -1;
int XACurPos;
int XAEndPos;
short XAVolume;
short XAReqVolume;
short XAMasterVolume;
short XATrack;
short XAReqTrack;
char XAFlag;
char XAWait;
static char XARepeat;
int XAStartPos;
static int XATrackList[17][2];

//Holds all game data file positions or offsets in GAMEWAD.OBJ.
struct GAMEWAD_header gwHeader;

//LBA for the GAMEWAD.OBJ file on disc, this is set by InitNewCDSystem(), CDPosToInt() (See CD.C)
int gwLba = 0;

//Start sector for the current gamewad file entry.
static int cdStartSector = 0;

//Current sector for the gamewad file entry, updated as data is read from disk.
int cdCurrentSector = 0;

void CDDA_SetVolume(int nVolume)//5D7FC(<), 5DC78(<) (F)
{
	S_Warn("[CDDA_SetVolume] - Unimplemented!\n");
}

void XAReplay()//5D838(<), 5DCB4(<)
{
#if 0
	struct CdlLOC loc;
	CdIntToPos(XAStartPos, &loc);

	if(CdControl(0x1B, &loc, 0) == 1)
	{
		XACurPos = XAStartPos;
	}

#endif

	return;
}

void cbvsync()//5D884(<), 5DD00(<)
{
	int ret;//$a1
	unsigned char io[8];//$sp-16
	int cnt;//$v0

	switch (XAFlag - 1)
	{
	case 0:
	{
		if (XAVolume == 0)
		{
			XAFlag++;
		}

		goto dflt;
		break;
	}
	case 1:
	{
		cnt = XATrack = XAReqTrack;
		if (XAReqTrack < 0)
		{
			cnt += 7;
		}

		//loc_5D8F8
		io[0] = 1;
		io[1] = XATrack & 7;

		XAStartPos = XATrackList[cnt][0];
		XAEndPos = XATrackList[cnt][1] + XATrackClip[XAReqTrack];
		XACurPos = XAStartPos;

		XAFlag++;

		//loc_5D8D8
		goto dflt;

		break;
	}
	case 2:
	{
		//loc_5D980
		XAReplay();
		XAReqVolume = XAMasterVolume;
		XAFlag++;

		goto dflt;

		break;
	}
	case 3:
	{
		//loc_5D9AC
		if (XAVolume == XAMasterVolume)
		{
			XAFlag++;
			XAWait = 60;
		}

		goto dflt;

		break;
	}
	case 4:
	{
		//loc_5D9E0
		if (XAWait == 0)
		{
			XAFlag++;
		}

		XAWait--;

		goto dflt;

		break;
	}
	case 5:
	{
		//loc_5DA18
		if (XAFlag & 7)
		{
			if (ret == 5)
			{
				XAReplay();
			}
			else if (ret == 2)
			{
				if (XACurPos < XAEndPos)
				{
					
				}
				else if (XARepeat == 0)
				{
					//loc_5DA84
					if (CurrentAtmosphere == 0)
					{
						XAFlag = 7;
					}
					else
					{
						//loc_5DAB8
						XAVolume = 0;
						XARepeat = 1;
						XAFlag = ret;
						XAReqTrack = CurrentAtmosphere;
						CDDA_SetVolume(0);
						IsAtmospherePlaying = 1;
					}
				}
				else
				{
					XAReplay();
				}
			}

			goto dflt;
		}

		break;
	}
	default:

	dflt:
		//def_5D8B8
		if (XAVolume < XAReqVolume)
		{
			XAVolume += XAFadeRate;
			if (XAVolume < XAReqVolume)
			{
				XAVolume = XAReqVolume;
			}//loc_5DB78

			CDDA_SetVolume(XAVolume);
		}
		else
		{
			//loc_5DB94
			if (XAReqVolume < XAVolume)
			{
				XAVolume -= XAFadeRate;
				if (!(XAReqVolume < XAVolume))
				{
					XAVolume = XAReqVolume;
				}

				//loc_5DBEC
				CDDA_SetVolume(XAVolume);

			}//loc_5DC00
		}

		//loc_5DC00
		break;
	}

	//loc_5DC00
	return;
}

void InitNewCDSystem()//5DDE8, 5E264(<) (F)
{
	char buf[10];
	int i = 0;
	long local_wadfile_header[512];


	FILE* fileHandle = fopen(GAMEWAD_FILENAME, "rb");
	assert(fileHandle);
	fread(&local_wadfile_header, sizeof(struct GAMEWAD_header), 1, fileHandle);
	fclose(fileHandle);

	memcpy(&gwHeader, &local_wadfile_header, sizeof(struct GAMEWAD_header));//5F6AC

	//FIXME: CdPosToInt(); returns LBA for GAMEWAD.OBJ on disc.
	gwLba = 24;

	//loc_5E2E8
	for (i = 0; i < NUM_XA_FILES; i++)
	{
		sprintf(buf, XA_FILE_NAME, i + 1);

		FILE* fileHandle = fopen(buf, "rb");
		assert(fileHandle);
		fseek(fileHandle, 0, SEEK_END);

		XATrackList[i][0] = -1;//FIXME: This value is returned by CdPosToInt(); register is v0. It returns the LBA of the XA file on disc.
		XATrackList[i][1] = XATrackList[i][0] + ((ftell(fileHandle) + 0x7FF) / CD_SECTOR_SIZE);

		fclose(fileHandle);
	}

	XAFlag = 0;
	XAVolume = 0;
	XAReqTrack = -1;
	XATrack = -1;
}

void DEL_ChangeCDMode(int mode)//5DEB0(<), 5E650
{
	unsigned char param[4];

	if (mode == 0)
	{
		if (current_cd_mode == 0)
		{
			return;
		}
		
		current_cd_mode = 0;
	}
	else if (mode == 1)
	{
		//loc_5DEF8
		if (current_cd_mode == mode)
		{
			return;
		}
		
		current_cd_mode = mode;
	}
	else if (mode == 2)
	{
		//loc_5DF20
		if (current_cd_mode == mode)
		{
			return;
		}

		current_cd_mode = mode;
	}

	//loc_5DF58
	return;
}

//Play audio track
void S_CDPlay(short track, int mode)//5DC10(<), 5E08C(<)
{
	unsigned char param[4];

	if (XATrack == -1)
	{
		param[0] = 0xC8;
		DEL_ChangeCDMode(1);
	}

	//loc_5DC70
	if (XATrack != track)
	{
		if (XAReqTrack != track)
		{
			XAReqTrack = track;
			XARepeat = mode;

			if (XAFlag != 0)
			{
				XAFlag = 1;
				XAReqVolume = 0;
			}
			else
			{
				//loc_5DCB4
				XAFlag = 2;
			}
		}
	}
	
	//loc_5DCBC
	return;
}

void S_CDStop()//5DCD0(<), 5E14C(<)
{
	XAFlag = 0;

	XAReqTrack = -1;
	XATrack = -1;

	DEL_ChangeCDMode(0);
	return;
}

void CDDA_SetMasterVolume(int nVolume)//5DDC4(<), 5E240(<) (F)
{
	XAMasterVolume = nVolume;
	CDDA_SetVolume(nVolume);
}

/*
* [FUNCTIONALITY] - CD_InitialiseReaderPosition.
* GAMEWAD_header is already in the memory at this point, we loaded it during InitNewCDSystem() (See CD.C)
* This method initialises the CD's read sector for a specific gamewad entry.
* File ID indices must match GAMEWAD.OBJ, see gw_files enum (GAMEWAD.H)
* Note: A File ID of "NONE" or 0 will initialise the reader position back to 0.
*
* [USAGE]
* @PARAM - [fileID] index into GAMEWAD_header.entries you wish to seek to.
* @RETURN - Filesize of the gamewad entry in bytes.
*/

int CD_InitialiseReaderPosition(int fileID /*$a0*/)//*, 5E3C0(<) (F)
{
	//Converting to multiples CD_SECTOR_SIZE since PSX legacy CD routines require the number of sectors to be read
	//Not the actual file size of the file itself.
	int relativeFileSector = gwHeader.entries[fileID].fileOffset / CD_SECTOR_SIZE;

	cdCurrentSector = cdStartSector = relativeFileSector;

	return gwHeader.entries[fileID].fileSize;
}

/*
* [FUNCTIONALITY] - CD_Read
* It is assumed that prior to calling this you have initialised the cd's
* reader's position to the file entry you wish to read see (CD_InitialiseReaderPosition)
* This method reads data from disc at it's last sectior/read position.
*
* [USAGE]
* @PARAM - [fileSize] the number of bytes you wish to read [ptr] the memory location the data is read to.
*/

void CD_Read(char* pDest, int fileSize)//*, 5E414(<) (F)
{
	int i;
	int numSectorsToRead;
	unsigned char param[4];

	FILE* fileHandle = NULL;

	fileHandle = fopen(GAMEWAD_FILENAME, "rb");
	assert(fileHandle);
	fseek(fileHandle, cdCurrentSector * CD_SECTOR_SIZE, SEEK_SET);

	numSectorsToRead = fileSize / CD_SECTOR_SIZE;

	if (numSectorsToRead != 0)
	{
		for (i = 0; i < numSectorsToRead; i++)
		{
			pDest += fread(pDest, 1, CD_SECTOR_SIZE, fileHandle);
		}

		cdCurrentSector += numSectorsToRead;
	}

	//Another chunk that is not multiple of 2048 bytes exists, read it
	if ((fileSize & 0x7FF) != 0)//%
	{
		pDest += fread(pDest, 1, fileSize - (numSectorsToRead * CD_SECTOR_SIZE), fileHandle);
		cdCurrentSector++;
	}

	fclose(fileHandle);
}

/*
* [FUNCTIONALITY] - CD_Seek
* Seeks from the cd reader's current position.
* Note: Negative numbers will allow backwards traversal.
* [USAGE]
* @PARAM - [offset] the number of bytes you wish to seek (not in sectors).
*/

void CD_Seek(int offset /*$a0*/)//*, 5E54C(<) (F)
{
	cdCurrentSector = cdStartSector + (offset / CD_SECTOR_SIZE);
}

/*
* [FUNCTIONALITY] - CD_ReaderPositionToCurrent
* Updates the cd reader's start sector to current reader position.
*/

void CD_ReaderPositionToCurrent()//*, 5E564(<) (F)
{
	cdStartSector = cdCurrentSector;
}