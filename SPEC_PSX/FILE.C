#include "FILE.H"

#include "CD.H"

#include <sys/types.h>
#include <LIBCD.H>
#include <STDIO.H>
#if !DISC_VERSION
#include <LIBSN.H>
#endif

int FILE_Load(char* szFileName, void* pDest)//5E528, 5E5D8(<) (F) (*) (*)
{
#if DISC_VERSION
	CdlFILE fp;
	char buf[80];
	
	DEL_ChangeCDMode(0);

	sprintf(buf, "\\%s;1", szFileName);

	CdSearchFile(&fp, buf);

	cdCurrentSector = CdPosToInt(&fp.pos);
	
	return DEL_CDFS_Read((char*)pDest, fp.size);
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

unsigned long FILE_Length(char* szFileName)//5E60C, 5E578(<) (F) (*) (*)
{
#if DISC_VERSION
	CdlFILE fp;
	char buf[80];

	DEL_ChangeCDMode(0);
	sprintf(buf, "\\%s;1", szFileName);

	if (CdSearchFile(&fp, buf))
	{
		return fp.size;
	}
	else
	{
		return -1;
	}

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

#if !DISC_VERSION
int FILE_Read(char* pDest, int nItemSize, int nItems, int nHandle)//5E6A8(<), ? (F) (*)
{
	int nAmount = nItems * nItemSize;
	return PCread(nHandle, pDest, nAmount);
}
#endif

void RelocateModule(unsigned long Module, unsigned long* RelocData)//5E6D4(<), 5F430(<) (F) (*)
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