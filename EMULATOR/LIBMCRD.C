#include "LIBMCRD.H"
#include "LIBETC.H"

#include <stdio.h>
#include <assert.h>
#include <string.h>

#define MC_HEADER_FRAME_INDEX (0)

int bIsInitialised = 0;
int bCanUseMemoryCardFuncs = 0;
int memoryCardStatus = -1;

FILE* memoryCards[2];
int memoryCardsNew[2];

long memoryCardCmds = -1;
long memoryCardResult = -1;

void MemCardInit(long val)
{
	bIsInitialised = 1;
	bCanUseMemoryCardFuncs = 0;
	memoryCardStatus = -1;
	memoryCardCmds = -1;
	memoryCardResult = -1;
	memoryCardsNew[0] = 1;
	memoryCardsNew[1] = 1;
}

void MemCardEnd()
{
	if (!bCanUseMemoryCardFuncs)
		return;

}

void MemCardStart()
{
	bCanUseMemoryCardFuncs = 1;
}

void MemCardStop()
{
	if (!bCanUseMemoryCardFuncs)
		return;

	bCanUseMemoryCardFuncs = 0;
	memoryCardStatus = -1;
	memoryCardCmds = -1;
	memoryCardResult = -1;
	memoryCardsNew[0] = 1;
	memoryCardsNew[1] = 1;

	if (memoryCards[0] != NULL)
	{
		fclose(memoryCards[0]);
	}

	if (memoryCards[1] != NULL)
	{
		fclose(memoryCards[1]);
	}
}

long MemCardExist(long chan)
{
	if (!bCanUseMemoryCardFuncs)
		return 0;

	char buf[16];
	sprintf(&buf[0], "%d.MCD", chan);
	memoryCards[chan] = fopen(&buf[0], "rb");

	memoryCardCmds = McFuncExist;

	if (memoryCards[chan] == NULL)
	{
		memoryCardStatus = -1;//CHECKME
		memoryCardResult = McErrCardNotExist;//CHECKME
		return 0;
	}
	else
	{
		fclose(memoryCards[chan]);

		if (memoryCardResult == McErrNewCard)
		{
			memoryCardResult = McErrNone;
			memoryCardStatus = 0;
		}
		else
		{
			memoryCardResult = McErrNewCard;
			memoryCardStatus = 1;
		}
	}

	
	return 1;
}

long MemCardAccept(long chan)
{
	if (!bCanUseMemoryCardFuncs)
		return 0;

	char buf[16];
	sprintf(&buf[0], "%d.MCD", chan);
	memoryCards[chan] = fopen(&buf[0], "rb");
	memoryCardCmds = McFuncAccept;

	unsigned int fileMagic = 0;
	fread(&fileMagic, 4, 1, memoryCards[chan]);

	//Is this card formatted?
	if (fileMagic != 0x0000434D)
	{
		//If not, this is a new card!
		memoryCardResult = McErrNewCard;
		memoryCardsNew[chan] = 0;
		return 0;
	}

	memoryCardResult = 3;
	memoryCardStatus = 1;
	return 1;
}
long MemCardOpen(long chan, char* file, long flag)
{
	
	return 0;
}

void MemCardClose()
{
	
}

long MemCardReadData(unsigned long* adrs, long ofs, long bytes)
{
	memoryCardCmds = McFuncReadData;
	return 0;
}

long MemCardReadFile(long chan, char* file, unsigned long* adrs, long ofs, long bytes)
{
	memoryCardCmds = McFuncReadFile;
	return 0;
}

long MemCardWriteData(unsigned long* adrs, long ofs, long bytes)
{
	memoryCardCmds = McFuncWriteData;
	return 0;
}

long MemCardWriteFile(long chan, char* file, unsigned long* adrs, long ofs, long bytes)
{
	memoryCardCmds = McFuncWriteFile;

	return 0;
}

long MemCardCreateFile(long chan, char* file, long blocks)
{
	
	return 0;
}

long MemCardDeleteFile(long chan, char* file)
{
	
	return 0;
}

long MemCardFormat(long chan)
{
	
	return 0;
}

long MemCardUnformat(long chan)
{
	
	return 0;
}

long MemCardSync(long mode, long* cmds, long* rslt)
{
	if (mode == 1)
	{
		if (memoryCardCmds != -1)
		{
			*cmds = memoryCardCmds;
		}

		if (memoryCardResult != -1)
		{
			*rslt = memoryCardResult;
		}

		return memoryCardStatus;
	}

	return 0;
}

MemCB MemCardCallback(MemCB func)
{
	
	return 0;
}

long MemCardGetDirentry(long chan, char* name, struct DIRENTRY* dir, long* files, long ofs, long max)
{

#pragma pack(push,1)
	struct MemoryCardFrame
	{
		unsigned int attr;
		unsigned int size;
		unsigned short unknown;
		char name[20];
		char padding[98];
	};
#pragma pack(pop)
	//Read all
	fseek(memoryCards[chan], 0, SEEK_SET);

	if (strcmp(name, "*") == 0)
	{
		for (int i = 0, head = -64; i < 16; i++, head += 128)
		{
			MemoryCardFrame frame;
			fread(&frame, sizeof(MemoryCardFrame), 1, memoryCards[chan]);

			if (i > MC_HEADER_FRAME_INDEX && frame.name[0] != '\0')
			{
				memcpy(dir->name, &frame.name, 20);
				dir->attr = frame.attr & 0xF0;
				dir->size = frame.size;
				dir->next = (struct DIRENTRY*)9;
				dir->head = head;
				dir->system[0] = 9;
				dir++;
				files[0]++;
			}
		}
	}
	memoryCardCmds = McFuncExist;
	memoryCardResult = 0;
	memoryCardStatus = 1;

	return 0;
}
