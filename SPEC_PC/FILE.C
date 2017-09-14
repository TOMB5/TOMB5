#include "FILE.H"
#include "SPECIFIC.H"

FILE *FileOpen(const char *filename)
{
	FILE *fp;
	char fn[80]; 

	memset(&fn, 0, 80u);
	fn[0] = 0;
	fn[1] = 0;
	fn[2] = 0;
	strcat(fn, filename);

	Log(5, "FileOpen - %s", fn);
	fp = fopen(fn, "rb");
	if (!fp)
		Log(1, "Unable To Open %s", fn);

	return fp;
}

int FileClose(FILE *fp)
{
	Log(2, "FileClose");
	return fclose(fp);
}

size_t fread_ex(void *ptr, size_t size, size_t count, FILE *stream)
{
	size_t ret;

	_lock_file(stream);
	ret = fread(ptr, size, count, stream);
	_unlock_file(stream);

	return ret;
}

int LoadFile(char* szFileName, void** pDest)
{
	FILE* fp;
	int len, read;

	Log(2, "LoadFile");
	Log(5, "File - %s", szFileName);

	fp = FileOpen(szFileName);
	if (!fp)
		return 0;

	len = FileLength(fp);

	if (!*pDest)
		*pDest = malloc(len);

	read = fread_ex(*pDest, 1, len, fp);

	Log(5, "Read - %d FileSize - %d", read, len);

	if (read != len)
	{
		Log(1, "Error Reading File");
		FileClose(fp);
		free(*pDest);
		return 0;
	}

	FileClose(fp);
	return len;
}

int FILE_Read(void* pDest, int nItemSize, int nItems, FILE* nHandle)
{
	S_Warn("[FILE_Read] - Unimplemented!\n");
	return 0;
}


unsigned long FileLength(FILE* nHandle)
{
	unsigned long ret;

	fseek(nHandle, 0, SEEK_END);
	ret = ftell(nHandle);
	fseek(nHandle, 0, SEEK_SET);

	return ret;
}