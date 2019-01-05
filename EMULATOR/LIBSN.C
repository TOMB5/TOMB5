#include "LIBSN.H"

#include <stdio.h>
#include <assert.h>

int fileHandle = 0;

int PCinit()
{
	assert(0);
	return 0;
}

int PCopen(char* name, int flags, int perms)
{
	switch (flags)
	{
	case 0:
		fileHandle = (int)fopen(name, "rb");
		break;
	case 1:
		fileHandle = (int)fopen(name, "wb");
		break;
	case 2:
		fileHandle = (int)fopen(name, "rwb");
		break;
	}
	
	return fileHandle == 0 ? -1 : fileHandle;
}

int PCcreat(char* name, int perms)
{
	assert(0);
	return 0;
}

int PClseek(int fd, int offset, int mode)
{
	return fseek((FILE*)fileHandle, offset, mode);
}

int PCread(int fd, char* buff, int len)
{
	return fread(buff, len, 1, (FILE*)fileHandle);
}

int PCwrite(int fd, char* buff, int len)
{
	return fwrite(buff, len, 1, (FILE*)fileHandle);
}

int PCclose(int fd)
{
	return fclose((FILE*)fd);
}
