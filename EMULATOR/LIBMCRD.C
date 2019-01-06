#include "LIBMCRD.H"

#include <assert.h>

void MemCardInit(long val)
{
	assert(0);
}

void MemCardEnd()
{
	assert(0);
}

void MemCardStart()
{
	assert(0);
}

void MemCardStop()
{
	assert(0);

}
long MemCardExist(long chan)
{
	assert(0);
	return 0;
}

long MemCardAccept(long chan)
{
	assert(0);
	return 0;
}
long MemCardOpen(long chan, char* file, long flag)
{
	assert(0);
	return 0;
}

void MemCardClose()
{
	assert(0);
}

long MemCardReadData(unsigned long* adrs, long ofs, long bytes)
{
	assert(0);
	return 0;
}

long MemCardReadFile(long chan, char* file, unsigned long* adrs, long ofs, long bytes)
{
	assert(0);
	return 0;
}

long MemCardWriteData(unsigned long* adrs, long ofs, long bytes)
{
	assert(0);
	return 0;
}

long MemCardWriteFile(long chan, char* file, unsigned long* adrs, long ofs, long bytes)
{
	assert(0);
	return 0;
}

long MemCardCreateFile(long chan, char* file, long blocks)
{
	assert(0);
	return 0;
}

long MemCardDeleteFile(long chan, char* file)
{
	assert(0);
	return 0;
}

long MemCardFormat(long chan)
{
	assert(0);
	return 0;
}

long MemCardUnformat(long chan)
{
	assert(0);
	return 0;
}

long MemCardSync(long mode, long* cmds, long* rslt)
{
	assert(0);
	return 0;
}

MemCB MemCardCallback(MemCB func)
{
	assert(0);
	return 0;
}

long MemCardGetDirentry(long chan, char* name, struct DIRENTRY* dir, long* files, long ofs, long max)
{
	assert(0);
	return 0;
}
