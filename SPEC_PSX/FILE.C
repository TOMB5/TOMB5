#include "FILE.H"

#include "CD.H"
#include "SPECIFIC.H"

#include <sys/types.h>
#include <libcd.h>
#include <stdio.h>
#include <libsn.h>

int FILE_Load(char* szFileName, void* pDest)//5E528, 5E5D8(<) (F) (*) (?)
{
#if DISC_VERSION
	CdlFILE fp;
	char buf[10];
	unsigned long dwFileSize = -1;
	
	DEL_ChangeCDMode(0);

	sprintf(buf, "\\%s;1", szFileName);

	CdSearchFile(&fp, buf);

	cdCurrentSector = CdPosToInt(&fp.pos);
	DEL_CDFS_Read((char*)pDest, fp.size);

	return fp.size;
#else
	int nHandle;
	unsigned long dwFileSize;
	unsigned long dwBytesRead;

	printf("Open\n");
	nHandle = PCopen(szFileName, 0, 0);

	if (nHandle < 0)
	{
		printf("FILE_Load: '%s' Could not open!\n", szFileName);
		S_ExitSystem("Can't open file");
	}

	printf("Seek\n");
	dwFileSize = PClseek(nHandle, 0, 2);
	PClseek(nHandle, 0, 0);

	printf("Read\n");
	dwBytesRead = PCread(nHandle, (char*)pDest, dwFileSize);

	printf("Close\n");
	PCclose(nHandle);

	return dwFileSize == dwBytesRead;
#endif
}

unsigned long FILE_Length(char* szFileName)//5E60C, 5E578(<) (F) (*) (?)
{
#if DISC_VERSION
	CdlFILE fp;
	char buf[10];
	unsigned long dwFileSize = -1;

	DEL_ChangeCDMode(0);
	sprintf(buf, "\\%s;1", szFileName);

	if (CdSearchFile(&fp, buf))
	{
		dwFileSize = fp.size;
	}

	return dwFileSize;
#else
	int nHandle;
	unsigned long dwFileSize;

	printf("Open\n");
	nHandle = PCopen(szFileName, 0, 0);

	if (nHandle < 0)
	{
		printf("FILE_Length: '%s' Could not find!\n", szFileName);
		return -1;
	}
	else
	{
		printf("Seek\n");
		dwFileSize = PClseek(nHandle, 0, 2);

		printf("Close\n");
		PCclose(nHandle);

		return dwFileSize;
	}
#endif
}

int FILE_Read(char* pDest, int nItemSize, int nItems, int nHandle)//5E6A8(<), ? (F) (*)
{
	int nAmount = nItems * nItemSize;
	return PCread(nHandle, pDest, nAmount);
}

void RelocateModule(unsigned long Module, unsigned long* RelocData)//5E6D4(<), 5F430(<) (F)
{
	unsigned long* pModule;
	unsigned long RelocationType;

	//loc_5E700
	while (*RelocData != -1)
	{
		RelocationType = *RelocData & 3;
		pModule = (unsigned long*) (Module + (*RelocData++ & -4));

		if (RelocationType == 0)
		{
			*(unsigned long*) pModule += Module;
		}
		else if (RelocationType == 1)
		{
			*(unsigned short*) pModule = (*RelocData++ + Module + 0x8000) / 65536;
		}
		else if (RelocationType == 2)
		{
			*(unsigned short*) pModule += Module;
		}
		else if (RelocationType == 3)
		{
			*(unsigned long*) pModule += Module / sizeof(unsigned long);
		}
	}
}