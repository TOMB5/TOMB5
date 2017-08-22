#include "FILE.H"

#include "CD.H"
#include "SPECIFIC.H"

#ifdef PSX
	#include <sys/types.h>
	#include <libcd.h>
#endif

#include <stdio.h>

int FILE_Load(char* szFileName, void* pDest)//5E528, 5E5D8
{
#ifdef PSXPC_VERSION
	FILE* fileHandle = NULL;
	long dwFileSize = 0;
	unsigned long dwBytesRead = 0;
#else
	char buf[10];
	unsigned long dwFileSize = -1;
#endif

#ifdef PSXPC_VERSION
	printf("Open\n");
	fileHandle = fopen(szFileName, "rb");

	if (fileHandle != NULL)
	{
		printf("Seek\n");
		fseek(fileHandle, 0, SEEK_END);
		dwFileSize = ftell(fileHandle);
		fseek(fileHandle, 0, SEEK_SET);

		printf("Read\n");
		dwBytesRead = fread(pDest, 1, dwFileSize, fileHandle);

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
#else
	DEL_ChangeCDMode(0);

	sprintf(buf, "\\%s;1", szFileName);

	if (CdSearchFile(&fp, buf) == 0)
	{
		printf("FILE_Load: '%s' Could not open!\n", szFileName);
	}

	cdCurrentSector = CdPosToInt(&fp.pos); //sw	$v0, 0x2E0C($gp)
	printf("Read Size: %i\n", fp.size);
	CD_Read(fp.size, pDest);

	return fp.size;
#endif
}

#ifdef PSXPC_VERSION
int FILE_Read(void* pDest, int nItemSize, int nItems, FILE* nHandle)//5E6A8, 
{
	return fread(pDest, nItemSize, nItems, nHandle);
}

#else
int FILE_Read(void* pDest, int nItemSize, int nItems, int nHandle)//5E6A8, 
{
	return 0;
}
#endif

unsigned long FILE_Length(char* szFileName)//5E60C, 5E578
{
#ifdef PSXPC_VERSION
	FILE* fileHandle = NULL;
	unsigned long dwFileSize = -1;

	printf("Open\n");
	fileHandle = fopen(szFileName, "rb");

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
#else
	char buf[10];
	unsigned long dwFileSize = -1;

	DEL_ChangeCDMode(0);
	sprintf(buf, "\\%s;1", szFileName);
	
	if (CdSearchFile(&fp, buf))
	{
		dwFileSize = fp.size;
	}

	printf("%s, len = %i\n", buf, dwFileSize);

	return dwFileSize;
#endif
}

void RelocateModule(unsigned long Module, unsigned long* RelocData)
{
	//TODO
}