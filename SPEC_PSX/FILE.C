#include "FILE.H"

#include "SPECIFIC.H"

#include <stdio.h>

int FILE_Load(char* szFileName, void* pDest)
{
	printf("Open\n");
	FILE* fileHandle = fopen(szFileName, "rb");

	if (fileHandle != NULL)
	{
		printf("Seek\n");
		fseek(fileHandle, 0, SEEK_END);
		long dwFileSize = ftell(fileHandle);
		fseek(fileHandle, 0, SEEK_SET);

		printf("Read\n");
		unsigned long dwBytesRead = fread(pDest, 1, dwFileSize, fileHandle);

		printf("Close\n");
		fclose(fileHandle);

		return dwBytesRead;
	}
	else
	{
		printf("FILE_Load: '%s' Could not open!\n", szFileName);
		S_ExitSystem("FILE_Load: '%s' Could not open!\n");
		printf("Can't open file");//?
	}

	return 0;
}

int FILE_Read(void* pDest, int nItemSize, int nItems, int nHandle)
{
	//TODO
	return -1;
}

unsigned long FILE_Length(char* szFileName)
{
	unsigned long dwFileSize = -1;

	printf("Open\n");
	FILE* fileHandle = fopen(szFileName, "rb");

	if (fileHandle != NULL)
	{
		printf(".");//?
		printf("Seek\n");
		fseek(fileHandle, 0, SEEK_END);
		dwFileSize = ftell(fileHandle);

		printf("Close\n");
		fclose(fileHandle);
	}
	else
	{
		printf("FILE_Length: '%s' Could not find!\n", szFileName);
	}

	return dwFileSize;
}

void RelocateModule(unsigned long Module, unsigned long* RelocData)
{
	//TODO
}