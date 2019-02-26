#include "LIBSN.H"

#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include "EMULATOR_GLOBALS.H"

uintptr_t fileHandle = 0;

int PCinit()
{
	UNIMPLEMENTED();
	return 0;
}

uintptr_t PCopen(char* name, int flags, int perms)
{
	//TOMB5 hack for CUTSEQ.JIZ
	if (name[0] == '\\')
	{
		++name;
	}

	switch (flags)
	{
	case 0:
		fileHandle = (uintptr_t)fopen(name, "rb");
		break;
	case 1:
		fileHandle = (uintptr_t)fopen(name, "wb");
		break;
	case 2:
		fileHandle = (uintptr_t)fopen(name, "rwb");
		break;
	}
	
	return fileHandle == 0 ? -1 : fileHandle;
}

int PCcreat(char* name, int perms)
{
	UNIMPLEMENTED();
	return 0;
}

int PClseek(uintptr_t fd, int offset, int mode)
{
	fseek((FILE*)fd, offset, mode);
	return ftell((FILE*)fd);
}

int PCread(uintptr_t fd, char* buff, int len)
{
	return fread(buff, 1, len, (FILE*)fd);
}

int PCwrite(uintptr_t fd, char* buff, int len)
{
	return fwrite(buff, len, 1, (FILE*)fd);
}

int PCclose(uintptr_t fd)
{
	return fclose((FILE*)fd);
}
