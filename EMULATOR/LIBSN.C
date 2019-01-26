#include "LIBSN.H"

#include <stdio.h>
#include <assert.h>

int fileHandle = 0;

int PCinit()
{
	
	return 0;
}

int PCopen(char* name, int flags, int perms)
{
	//TOMB5 hack for CUTSEQ.JIZ
	if (name[0] == '\\')
	{
		++name;
	}

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
	
	return 0;
}

int PClseek(int fd, int offset, int mode)
{
	fseek((FILE*)fd, offset, mode);
	return ftell((FILE*)fd);
}

int PCread(int fd, char* buff, int len)
{
	return fread(buff, 1, len, (FILE*)fd);
}

int PCwrite(int fd, char* buff, int len)
{
	return fwrite(buff, len, 1, (FILE*)fd);
}

int PCclose(int fd)
{
	return fclose((FILE*)fd);
}
