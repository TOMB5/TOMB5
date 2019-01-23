#include "LIBMCRD.H"

#include <assert.h>

void MemCardInit(long val)
{
	
}

void MemCardEnd()
{
	
}

void MemCardStart()
{
	
}

void MemCardStop()
{
	

}
long MemCardExist(long chan)
{
	
	return 0;
}

long MemCardAccept(long chan)
{
	
	return 0;
}
long MemCardOpen(long chan, char* file, long flag)
{
	
	return 0;
}

void MemCardClose()
{
	
}

long MemCardReadData(unsigned long* adrs, long ofs, long bytes)
{
	
	return 0;
}

long MemCardReadFile(long chan, char* file, unsigned long* adrs, long ofs, long bytes)
{
	
	return 0;
}

long MemCardWriteData(unsigned long* adrs, long ofs, long bytes)
{
	
	return 0;
}

long MemCardWriteFile(long chan, char* file, unsigned long* adrs, long ofs, long bytes)
{
	
	return 0;
}

long MemCardCreateFile(long chan, char* file, long blocks)
{
	
	return 0;
}

long MemCardDeleteFile(long chan, char* file)
{
	
	return 0;
}

long MemCardFormat(long chan)
{
	
	return 0;
}

long MemCardUnformat(long chan)
{
	
	return 0;
}

long MemCardSync(long mode, long* cmds, long* rslt)
{
	
	return 0;
}

MemCB MemCardCallback(MemCB func)
{
	
	return 0;
}

long MemCardGetDirentry(long chan, char* name, struct DIRENTRY* dir, long* files, long ofs, long max)
{
	
	return 0;
}
