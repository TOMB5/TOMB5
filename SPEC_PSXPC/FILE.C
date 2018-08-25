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
	unsigned int* rel;

	if (*RelocData != -1)
	{
		do
		{
			rel = (unsigned int*)(Module + (*RelocData & -4));

			switch (*RelocData++ & 3)
			{
			case 0:
				//loc_5E738
				((unsigned int*)rel)[0] += Module;
				break;
			case 1:
				//loc_5E744
				((unsigned short*)rel)[0] = (Module + *RelocData++ + 0x8000) >> 16;
				break;
			case 2:
				//loc_5E760:
				((unsigned short*)rel)[0] += Module;
				break;
			case 3:
				//loc_5E774
				((unsigned int*)rel)[0] += ((Module << 4) >> 6);
				break;
			}
		} while (*RelocData != -1);
	}//locret_5E794
}