#include "LIBCD.H"

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "EMULATOR_GLOBALS.H"

#define DISC_IMAGE_FILENAME "TOMB5.BIN"

#define DECODE_BCD(x) (((x) >> 4) * 10 + ((x) & 0xF))
#define ENCODE_BCD(x) ((((x) / 10) << 4) | ((x) % 10))

FILE* openFile = NULL;

typedef struct commandQueue
{
	unsigned int mode;
	unsigned char* p;
	unsigned int processed;
	unsigned int count;
};

#define COMMAND_QUEUE_SIZE 256

commandQueue comQueue[COMMAND_QUEUE_SIZE];
commandQueue* comStart = &comQueue[0];
commandQueue* comEnd = &comQueue[COMMAND_QUEUE_SIZE-1];
int comQueueIndex = 0;
int comQueueCount = 0;
int currentSector = 0;
int sectorSize = 2352;//TODO obtain properly from cue sheet
int lastCom = 0;

#pragma pack(push, 1)
struct TOC
{
	unsigned char tocEntryLength;
	unsigned char extEntryLength;
	unsigned int sectorPosition[2];
	unsigned int fileSize[2];
	unsigned char date[7];
	unsigned char flags;
	unsigned char fileUnitSize;
	unsigned char interleaveGapSize;
	unsigned short volSeqNum[2];
	unsigned char nameLength;
};

struct Sector
{
	unsigned char	sync[12];	/// Sync pattern (usually 00 FF FF FF FF FF FF FF FF FF FF 00)
	unsigned char	addr[3];	/// Sector address (see below for encoding details)
	unsigned char	mode;		/// Mode (usually 2 for Mode 2 Form 1/2 sectors)
	unsigned char	subHead[8];	/// Sub-header (00 00 08 00 00 00 08 00 for Form 1 data sectors)
	unsigned char	data[2048];	/// Data (form 1)
	unsigned char	edc[4];		/// Error-detection code (CRC32 of data area)
	unsigned char	ecc[276];	/// Error-correction code (uses Reed-Solomon ECC algorithm)
};
#pragma pack(pop)

CdlFILE* CdSearchFile(CdlFILE* fp, char* name)
{
	memset(fp, 0, sizeof(CdlFILE));

	if (name[0] == '\\')
	{
		name++;
	}

	if (openFile != NULL)
	{
		fseek(openFile, 22 * sectorSize, SEEK_SET);

		int tocLocalOffset = 0;
		Sector sector;
		fread(&sector, sizeof(Sector), 1, openFile);
		TOC* toc = (TOC*)&sector.data[0];
		while (toc->tocEntryLength != 0)
		{
			if (strcmp((char*)&sector.data[tocLocalOffset + sizeof(TOC)], name) == 0)
			{
				memcpy(&fp->name[0], (char*)&sector.data[tocLocalOffset + sizeof(TOC)], strlen(name));
				fp->size = toc->fileSize[0];
				fseek(openFile, toc->sectorPosition[0] * sectorSize, SEEK_SET);
				fread(&sector, sizeof(Sector), 1, openFile);
				fp->pos.minute = sector.addr[0];
				fp->pos.second = sector.addr[1];
				fp->pos.sector = sector.addr[2];


#if _DEBUG
				printf("CDSearchFile() Found %s\n", name);
#endif
				return fp;
			}
			tocLocalOffset += toc->tocEntryLength;
			toc = (TOC*)&sector.data[tocLocalOffset];
		}
	}

	return NULL;
}

CdlLOC* CdIntToPos(int i, CdlLOC* p)
{
	i += 150;
	p->sector = ENCODE_BCD(i % 75);
	int rem = i / 75;
	p->second = ENCODE_BCD(rem % 60);
	p->minute = ENCODE_BCD(rem / 60);
	return p;
}

int CdControl(u_char com, u_char * param, u_char * result)
{
	CdlFILE* cd = (CdlFILE*)param;

	lastCom = com;

	switch (com)
	{
	case CdlSetloc:
		fseek(openFile, CdPosToInt(&cd->pos)*sectorSize, SEEK_SET);
		break;
	default:
		printf("Unhandled command 0x%02X!\n", com);
		break;
	}

	return 0;
}

int CdControlB(u_char com, u_char* param, u_char* result)
{
	CdlFILE* cd = (CdlFILE*)param;

	lastCom = com;

	switch (com)
	{
	case CdlSetloc:
		fseek(openFile, CdPosToInt(&cd->pos)*sectorSize, SEEK_SET);
		break;
	default:
		printf("Unhandled command 0x%02X!\n", com);
		break;
	}

	return 0;
}

int CdControlF(u_char com, u_char * param)
{
	CdlFILE* cd = (CdlFILE*)param;

	lastCom = com;

	switch (com)
	{
	case CdlSetloc:
		fseek(openFile, CdPosToInt(&cd->pos)*sectorSize, SEEK_SET);
		break;
	default:
		printf("Unhandled command 0x%02X!\n", com);
		break;
	}

	return 0;
}

int CdPosToInt(CdlLOC* p)
{
	return (75 * (60 * DECODE_BCD(p->minute) + DECODE_BCD(p->second))) + DECODE_BCD(p->sector) - 150;
}

int CdRead(int sectors, u_long* buf, int mode)
{
	if (comQueueIndex == COMMAND_QUEUE_SIZE)
		comQueueIndex = 0;

	comStart[comQueueIndex].mode = CdlReadS;
	comStart[comQueueIndex].p = (unsigned char*)buf;
	comStart[comQueueIndex].processed = 0;
	comStart[comQueueIndex].count = sectors;
	comQueueCount++;
	comQueueIndex++;
	return 0;
}

int CdReadSync(int mode, u_char* result)
{
	for (int i = 0; i < comQueueCount; i++)
	{
		if (comQueue[i].processed == 0)
		{
			Sector sector;
			fread(&sector, sizeof(Sector), 1, openFile);

			memcpy(comQueue[i].p, &sector.data[0], 2048);
			comQueue[i].p += 2048;

			if (--comQueue[i].count == 0)
			{
				comQueue[i].processed = 1;
				break;
			}
			
			return 1;
		}
	}
	return 0;
}

int CdSetDebug(int level)
{
	UNIMPLEMENTED();
	return 0;
}

int CdSync(int mode, u_char * result)
{
	UNIMPLEMENTED();
	return 0;
}

int CdInit(void)
{
	memset(&comQueue, 0, sizeof(comQueue));
	currentSector = 0;
	openFile = fopen(DISC_IMAGE_FILENAME, "rb");

	if (openFile == NULL)
	{
		printf("Error: CdInit() Failed to open disc image file! %s\n", DISC_IMAGE_FILENAME);
		return 0;
	}

	return 1;
}

int CdLastCom(void)
{
	return lastCom;
}
