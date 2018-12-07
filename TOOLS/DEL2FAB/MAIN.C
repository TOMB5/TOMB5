#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int dword_12B477C;
char *off_41B0C8[3] = { "ERROR :", "ERROR : dmalloc failed ", "ERROR :" };
int dword_41B0C4[] = { 0 };
int num_mallocs = 0;
int num_frees = 0;

int sub_4024B0(char* fileName, FILE* outFile);
void* tool_malloc(size_t size);
void tool_free(void* p);

void checkError(int a1, char* a2)//checkError?
{
	char* v2;

	if (a1 == 1)
	{
		v2 = strerror(dword_12B477C);
		printf("\n%s %s (%s)\n", off_41B0C8[0], v2, a2);
	}
	else
	{
		printf("\n%s %s\n", dword_41B0C4[a1], a2);
	}
	exit(1);
}

int main(int argc, char** argv, const char** envp)
{
	FILE* f;
	int fileLength;
	unsigned int alignedFileLength;
	char fileName[72];

	strcpy(fileName, argv[1]);
	strcat(fileName, ".MOD");
	f = fopen(fileName, "wb");
	fseek(f, 8, 0);
	strcpy(fileName, argv[1]);
	strcat(fileName, ".BIN");
	fileLength = sub_4024B0(fileName, f);
	alignedFileLength = (fileLength + 3) & 0xFFFFFFFC;
	fseek(f, alignedFileLength - fileLength, 1);
	strcpy(fileName, argv[1]);
	strcat(fileName, ".REL");
	fileLength = sub_4024B0(fileName, f);
	fseek(f, 0, 0);
	fwrite(&alignedFileLength, 4u, 1u, f);
	fwrite(&fileLength, 4u, 1u, f);
	fclose(f);
	exit(0);
	
	return 1;
}

int sub_4024B0(char* fileName, FILE* outFile)
{
	FILE* f;
	int fileLength;
	void* pMemory;

	f = fopen(fileName, "rb");
	
	if (f == NULL)
	{
		checkError(1, fileName);
	}
	
	fseek(f, 0, SEEK_END);
	fileLength = ftell(f);
	fseek(f, 0, SEEK_SET);
	pMemory = tool_malloc(fileLength);

	if (pMemory == NULL)
	{
		checkError(2, "(dat)");
	}

	fread(pMemory, 1, fileLength, f);
	fwrite(pMemory, 1, fileLength, outFile);
	tool_free(pMemory);
	fclose(f);
	return fileLength;
}

void* tool_malloc(size_t size)
{
	++num_mallocs;
	return malloc(size);
}

void tool_free(void* p)//sub_403190
{
	++num_frees;
	free(p);
}