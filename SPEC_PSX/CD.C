#include "CD.H"

#include "CONTROL.H"
#include "SPECIFIC.H"

#include <assert.h>
#include <string.h>
#include <stdio.h>

#include <sys/types.h>
#include <LIBCD.H>
#include <LIBSPU.H>

//Number of XA files on disc (XA1-17.XA)
#define NUM_XA_FILES 17

#define XA_FILE_NAME "\\XA%d.XA;1"

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

CdlFILE fp;

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

		CdControlF(0xD, &io);
		
		XAFlag++;

		break;
	}
	case 2:
	{
		//loc_5D980
		XAReplay();
		XAReqVolume = XAMasterVolume;
		XAFlag++;
		
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
		
		break;
	}
	case 5:
	{
		//loc_5DA18
		VSync(-1);
		
		if (XAFlag & 7)
		{
			ret = CdSync(0, &io[0]);
			if (ret == 5)
			{
				XAReplay();
			}
			else if (ret == 2)
			{
				if (XACurPos < XAEndPos)
				{
					//loc_5DAEC
					if (CdLastCom() == 0x11);
					{
						cnt = CdPosToInt(&io[5]);

						if (cnt > 0)
						{
							XACurPos = cnt;
						}

						CdControlF(&io[5], 0);
					}
				}
				else if (XARepeat == 0)
				{
					//loc_5DA84
					if (CurrentAtmosphere == 0)
					{
						CdControlB(9, 0, 0);
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
		}

		break;
	}
	default:
		break;
	}

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
	return;
}

void InitNewCDSystem()//5DDE8, 5E264(<) (F)
{
	char buf[10];
	int i = 0;
	long local_wadfile_header[512];

	DEL_ChangeCDMode(0);
	
	CdSearchFile(&fp, GAMEWAD_FILENAME);//662F0
	CdControlB(CdlSetloc, &fp, 0);//6956C
	CdRead(1, &local_wadfile_header, 0x80); //69C4C

	while (CdReadSync(1, 0) > 0)
	{
		VSync(0);
	}

	memcpy(&gwHeader, &local_wadfile_header, 512);//5F6AC

	gwLba = CdPosToInt(&fp.pos);//66270

	//loc_5E2E8
	for (i = 0; i < NUM_XA_FILES; i++)
	{
		sprintf(buf, XA_FILE_NAME, i + 1);
		
		CdSearchFile(&fp, buf);

		XATrackList[i][0] = CdPosToInt(&fp.pos);
		XATrackList[i][1] = XATrackList[i][0] + ((fp.size + 0x7FF) / CD_SECTOR_SIZE);
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

		param[0] = CdlModeSpeed;
		CdControlB(CdlSetmode, param, 0);
		VSync(3);
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
		
		param[0] = CdlModeSpeed;
		CdControlB(CdlSetmode, param, 0);
		VSync(3);
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
		CdControlB(CdlSetmode, &param[0], 0);
		VSync(3);
		CdControlB(0x9, 0, 0);
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

	CdControlB(CdlPause, 0, 0);

	XAReqTrack = -1;
	XATrack = -1;

	DEL_ChangeCDMode(0);
	return;
}

void S_CDPause()//5DD14(<), 5E190(<) (F)
{
	if(XATrack > 0)
	{
		CdControlF(CdlPause, 0);
	}

	return;
}

void CDDA_SetMasterVolume(int nVolume)//5DDC4(<), 5E240(<) (F)
{
	XAMasterVolume = nVolume;
	CDDA_SetVolume(nVolume);
}

void CDDA_SetVolume(int nVolume)//5D7FC(<), 5DC78(<) (F)
{
	SpuCommonAttr attr;
	
	attr.cd.volume.left = nVolume * 64;
	attr.cd.volume.right = nVolume * 64;
	attr.mask = SPU_COMMON_CDVOLL | SPU_COMMON_CDVOLR | SPU_COMMON_CDMIX;
	attr.cd.mix = SPU_ON;
	
	SpuSetCommonAttr(&attr);
}

void XAReplay()//5D838(<), 5DCB4(<)
{
	CdlLOC loc;

	CdIntToPos(XAStartPos, &loc);
	
	if (CdControl(0x1B, &loc, 0) == 1)
	{
		XACurPos = XAStartPos;
	}

	return;
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

	DEL_ChangeCDMode(0);
	cdCurrentSector = cdStartSector = gwLba + relativeFileSector;

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

void CD_Read(int fileSize/*$s1*/, char* ptr/*$a0*/)//*, 5E414(<) (F)
{
	int i;
	int numSectorsToRead;
	unsigned char param[4];

	DEL_ChangeCDMode(0);

	numSectorsToRead = fileSize / CD_SECTOR_SIZE;

	if (numSectorsToRead > 1)
	{
		printf("%i\n", 0xDEAD, "DEAD!!!\n");
	}

	if (numSectorsToRead != 0)
	{
		CdIntToPos(cdCurrentSector, &fp.pos);//6915C
		CdControlB(CdlSetloc, &fp, 0);//sub_6956C
		CdRead(numSectorsToRead, ptr, 0x80);

		while (CdReadSync(1, 0) > 0)
		{
			VSync(0);//6A1FC
		}

		cdCurrentSector += numSectorsToRead;
	}

	//Another chunk that is not multiple of 2048 bytes exists, read it
	if ((fileSize & 0x7FF) != 0)//%
	{
		printf("Last chunk! Sector %i\n", fp.pos);
		CdIntToPos(cdCurrentSector, &fp.pos);//6915C
		CdControlB(CdlSetloc, &fp, 0);//sub_6956C
		CdRead(1, ptr, 0x80);//jal sub_69C4C //CdRead(?, ?, ?);

		while (CdReadSync(1, 0) > 0)
		{
			VSync(0);//6A1FC
		}
		printf("CD SYNCED\n", fp.pos);
		
		cdCurrentSector++;
	}
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