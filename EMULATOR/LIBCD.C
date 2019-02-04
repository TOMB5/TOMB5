#include "LIBCD.H"

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define DISC_IMAGE_FILENAME "TOMB5.BIN"

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

int mfhi(int a, int b)
{
	unsigned long long temp = (long long)((long long)(int)a * (long long)(int)b);

	int lo = temp & 0xffffffff;
	int hi = temp >> 32;
	return ((temp >> 32) & 0xFFFFFFFF);
}

CdlLOC* CdIntToPos(int i, CdlLOC* p)
{
	CdlLOC* v0;
 	int v1 = 0x1B4E81B5;
	i += 150;
	v1 = mfhi(i, v1);
	v0 = p;
	int a1 = 0x88888889;
	int a3 = v1 >> 3;
	v1 = i >> 31;
	a3 -= v1;
	int a2 = mfhi(a3, a1);
	int t1 = 0x66666667;
	a1 = a3 << 2;
	a1 += a3;
	v1 = a1 << 4;
	v1 -= a1;
	i -= v1;
	a1 = mfhi(i, t1);
	v1 = a3 >> 31;
	int t0 = a2 + a3;
	t0 >>= 5;
	t0 -= v1;
	v1 = t0 << 4;
	v1 -= t0;
	v1 <<= 2;
	a3 -= v1;
	int t3 = mfhi(a3, t1);
	v1 = i >> 31;
	a1 >>= 2;
	a1 -= v1;
	a2 = a1 << 4;
	v1 = a1 << 2;
	v1 += a1;
	v1 <<= 1;
	i -= v1;
	a2 += i;
	v1 = a3 >> 31;
	t1 = mfhi(t0 , t1);
	v0->sector = a2;
	i = t3 >> 2;
	i -= v1;
	a1 = i << 4;
	v1 = i << 2;
	v1 += i;
	v1 <<= 1;
	a3 -= v1;
	a1 += a3;
	v1 = t0 >> 31;
	v0->second = a1;
	i = t1 >> 2;
	i -= v1;
	a1 = i << 4;
	v1 = i << 2;
	v1 += i;
	v1 <<= 1;
	t0 -= v1;
	a1 += t0;
	v0->minute = a1;
	return v0;
}

int CdControl(u_char com, u_char * param, u_char * result)
{
	CdlFILE* cd = (CdlFILE*)param;
	
	switch (com)
	{
	case CdlSetloc:
		fseek(openFile, CdPosToInt(&cd->pos)*sectorSize, SEEK_SET);
		break;
	default:
		printf("Uhandled command!\n");
		break;
	}
	return 0;
}

int CdControlB(u_char com, u_char* param, u_char* result)
{
	CdlFILE* cd = (CdlFILE*)param;

	switch (com)
	{
	case CdlSetloc:
		fseek(openFile, CdPosToInt(&cd->pos)*sectorSize, SEEK_SET);
		break;
	default:
		printf("Uhandled command!\n");
		break;
	}

	return 0;
}

int CdControlF(u_char com, u_char * param)
{
	CdlFILE* cd = (CdlFILE*)param;
	
	switch (com)
	{
	case CdlSetloc:
		fseek(openFile, CdPosToInt(&cd->pos)*sectorSize, SEEK_SET);
		break;
	default:
		printf("Uhandled command!\n");
		break;
	}
	return 0;
}

int CdPosToInt(CdlLOC* p)
{
	int v1 = p->minute;
	int a2 = p->second;

	int a1 = v1 >> 4;
	int v0 = a1 << 2;
	v0 += a1;
	v0 <<= 1;
	v1 &= 0xF;
	v0 += v1;

	a1 = v0 << 4;
	a1 -= v0;
	a1 <<= 2;

	v1 = a2 >> 4;
	v0 = v1 << 2;
	v0 += v1;
	v0 <<= 1;
	a2 &= 0xF;

	v0 += a2;
	a1 += v0;
	v1 = a1 << 2;
	v1 += a1;
	v0 = v1 << 4;

	a1 = p->sector;
	v0 -= v1;
	int a0 = a1 >> 4;
	v1 = a0 << 2;
	v1 += a0;
	v1 <<= 1;
	a1 &= 0xF;
	v1 += a1;
	v0 += v1;

	return v0 - 150;
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
	return 0;
}

int CdSync(int mode, u_char * result)
{
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
	}

	return 1;
}

int CdLastCom(void)
{
	return 0;
}
