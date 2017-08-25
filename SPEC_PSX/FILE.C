#include "FILE.H"

#include "CD.H"
#include "SPECIFIC.H"

#include <sys/types.h>
#include <libcd.h>
#include <stdio.h>

int FILE_Load(char* szFileName, void* pDest)//5E528, 5E5D8
{
	char buf[10];
	unsigned long dwFileSize = -1;
	
	DEL_ChangeCDMode(0);

	sprintf(buf, "\\%s;1", szFileName);

	if (CdSearchFile(&fp, buf) == 0)
	{
		printf("FILE_Load: '%s' Could not open!\n", szFileName);
	}

	cdCurrentSector = CdPosToInt(&fp.pos); //sw	$v0, 0x2E0C($gp)
	printf("Read Size: %i\n", fp.size);
	CD_Read(pDest, fp.size);

	return fp.size;
}

int FILE_Read(void* pDest, int nItemSize, int nItems, int nHandle)//5E6A8, 
{
	return 0;
}

unsigned long FILE_Length(char* szFileName)//5E60C, 5E578
{
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
}

void RelocateModule(unsigned long Module, unsigned long* RelocData)
{
	//TODO
}