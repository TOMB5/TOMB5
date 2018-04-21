#include "FILE.H"

#include "CD.H"
#include "SPECIFIC.H"

#include <stdio.h>

int FILE_Load(char* szFileName, void* pDest)//5E528, 5E5D8(<) (F) (*) (?)
{
#if 0
	long dwFileSize = 0;
	FILE* fileHandle = NULL;

	fileHandle = fopen(szFileName, "rb");
	fseek(fileHandle, 0, SEEK_END);
	dwFileSize = ftell(fileHandle);
	fseek(fileHandle, 0, SEEK_SET);
	fclose(fileHandle);
	return DEL_CDFS_Read((char*)pDest, dwFileSize);//Bug: Always set to read from GAMEWAD. Pass fp or name (ugly solution).
#else
	FILE* fileHandle = NULL;
	long dwFileSize = 0;
	unsigned long dwBytesRead = 0;

	printf("Open\n");
	fileHandle = fopen(szFileName, "rb");

	if (fileHandle == NULL)
	{
		printf("FILE_Load: '%s' Could not open!\n", szFileName);
		S_ExitSystem("Can't open file");
	}

	printf("Seek\n");
	fseek(fileHandle, 0, SEEK_END);
	dwFileSize = ftell(fileHandle);
	fseek(fileHandle, 0, SEEK_SET);

	printf("Read\n");
	dwBytesRead = fread(pDest, 1, dwFileSize, fileHandle);

	printf("Close\n");
	fclose(fileHandle);

	return dwFileSize == dwBytesRead;
#endif
}

unsigned long FILE_Length(char* szFileName)//5E60C, 5E578(<) (F) (*) (?)
{
	FILE* fileHandle = NULL;
	unsigned long dwFileSize = -1;

	printf("Open\n");
	fileHandle = fopen(szFileName, "rb");

	if (fileHandle == NULL)
	{
		printf("FILE_Length: '%s' Could not find!\n", szFileName);
		return -1;
	}

	printf("Seek\n");
	fseek(fileHandle, 0, SEEK_END);
	dwFileSize = ftell(fileHandle);

	printf("Close\n");
	fclose(fileHandle);

	return dwFileSize;
}

int FILE_Read(char* pDest, int nItemSize, int nItems, FILE* nHandle)//5E6A8(<), ? (F)
{
	return fread(pDest, nItemSize, nItems, nHandle);
}

void RelocateModule(unsigned long Module, unsigned long* RelocData)//5E6D4(<), 5F430(<) (F)
{
	unsigned long* pModule = NULL;
	unsigned long RelocationType = 0;

	//loc_5E700
	while (*RelocData != -1)
	{
		RelocationType = *RelocData & 3;
		pModule = (unsigned long*)(Module + (*RelocData++ & -4));

		if (RelocationType == 0)
		{
			*(unsigned long*) pModule += Module;
		}
		else if(RelocationType == 1)
		{
			*(unsigned short*) pModule = (*RelocData++ + Module + 0x8000) / 65536;
		}
		else if(RelocationType == 2)
		{
			*(unsigned short*) pModule += Module;
		}
		else if(RelocationType == 3)
		{
			*(unsigned long*) pModule += Module / sizeof(unsigned long);
		}
	}
}