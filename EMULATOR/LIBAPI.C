#include "LIBAPI.H"

#include <assert.h>

long SetRCnt(unsigned long unk00, unsigned short, long)
{
	assert(0);
	return 0;
}

long GetRCnt(unsigned long unk00)
{
	assert(0);
	return 0;
}

long ResetRCnt(unsigned long unk00)
{
	assert(0);
	return 0;
}

long StartRCnt(unsigned long unk00)
{
	assert(0);
	return 0;
}

long StopRCnt(unsigned long unk00)
{
	assert(0);
	return 0;
}

long OpenEvent(unsigned long unk00, long, long, long(*func)())
{
	assert(0);
	return 0;
}

long CloseEvent(long unk00)
{
	assert(0);
	return 0;
}

long WaitEvent(long unk00)
{
	assert(0);
	return 0;
}

long TestEvent(long unk00)
{
	assert(0);
	return 0;
}

long EnableEvent(long unk00)
{
	assert(0);
	return 0;
}

long DisableEvent(long unk00)
{
	assert(0);
	return 0;
}

void DeliverEvent(unsigned long unk00, unsigned long)
{
	assert(0);
}

void UnDeliverEvent(unsigned long unk00, unsigned long)
{
	assert(0);
}

long OpenTh(long(*func)(), unsigned long, unsigned long)
{
	assert(0);
	return 0;
}

int CloseTh(long unk00)
{
	assert(0);
	return 0;
}

int ChangeTh(long unk00)
{
	assert(0);
	return 0;
}

long open(char* unk00, unsigned long)
{
	assert(0);
	return 0;
}

long close(long unk00)
{
	assert(0);
	return 0;
}

long lseek(long unk00, long, long)
{
	assert(0);
	return 0;
}

long read(long unk00, void *, long)
{
	assert(0);
	return 0;
}

long write(long unk00, void *, long)
{
	assert(0);
	return 0;
}

long ioctl(long unk00, long, long)
{
	assert(0);
	return 0;
}

struct DIRENTRY* firstfile(char* unk00, struct DIRENTRY *)
{
	assert(0);
	return 0;
}

struct DIRENTRY* nextfile(struct DIRENTRY* unk00)
{
	assert(0);
	return 0;
}

long erase(char* unk00)
{
	assert(0);
	return 0;
}

long undelete(char* unk00)
{
	assert(0);
	return 0;
}

long format(char* unk00)
{
	assert(0);
	return 0;
}
long rename(char* unk00, char *)
{
	assert(0);
	return 0;
}

long cd(char* unk00)
{
	assert(0);
	return 0;
}

long LoadTest(char*  unk00, struct EXEC *)
{
	assert(0);
	return 0;
}

long Load(char * unk00, struct EXEC *)
{
	assert(0);
	return 0;
}

long Exec(struct EXEC * unk00, long, char **)
{
	assert(0);
	return 0;
}

long LoadExec(char * unk00, unsigned long, unsigned long)
{
	assert(0);
	return 0;
}

long InitPAD(char * unk00, long, char *, long)
{
	assert(0);
	return 0;
}

long StartPAD()
{
	assert(0);
	return 0;
}

void StopPAD()
{
	assert(0);
}

void EnablePAD()
{
	assert(0);
}

void DisablePAD()
{
	assert(0);
}

void FlushCache()
{
	assert(0);
}

void ReturnFromException()
{
	assert(0);
}

int  EnterCriticalSection()
{
	assert(0);
	return 0;
}

void ExitCriticalSection()
{
	assert(0);
}

void Exception()
{
	assert(0);
}

void SwEnterCriticalSection()
{
	assert(0);
}
void SwExitCriticalSection()
{
	assert(0);
}

unsigned long SetSp(unsigned long)
{
	assert(0);
	return 0;
}

unsigned long GetSp()
{
	assert(0);
	return 0;
}

unsigned long GetGp()
{
	assert(0);
	return 0;
}

unsigned long GetCr()
{
	assert(0);
	return 0;
}

unsigned long GetSr()
{
	assert(0);
	return 0;
}

unsigned long GetSysSp()
{
	assert(0);
	return 0;
}

long SetConf(unsigned long, unsigned long, unsigned long)
{
	assert(0);
	return 0;
}

void GetConf(unsigned long *, unsigned long *, unsigned long *)
{
	assert(0);
}

long _get_errno(void)
{
	assert(0);
	return 0;
}

long _get_error(long)
{
	assert(0);
	return 0;
}

void SystemError(char, long)
{
	assert(0);
}

void SetMem(long)
{
	assert(0);
}

long Krom2RawAdd(unsigned long)
{
	assert(0);
	return 0;
}

long Krom2RawAdd2(unsigned short)
{
	assert(0);
	return 0;
}

void _96_init(void)
{
	assert(0);
}

void _96_remove(void)
{
	assert(0);
}

void _boot(void)
{
	assert(0);
}

void ChangeClearPAD(long)
{
	assert(0);
}

void InitCARD(long val)
{
	assert(0);
}

long StartCARD()
{
	assert(0);
	return 0;
}

long StopCARD()
{
	assert(0);
	return 0;
}

void _bu_init()
{
	assert(0);
}

long _card_info(long chan)
{
	assert(0);
	return 0;
}

long _card_clear(long chan)
{
	assert(0);
	return 0;
}

long _card_load(long chan)
{
	assert(0);
	return 0;
}

long _card_auto(long val)
{
	assert(0);
	return 0;
}

void _new_card()
{
	assert(0);
}

long _card_status(long drv)
{
	assert(0);
	return 0;
}

long _card_wait(long drv)
{
	assert(0);
	return 0;
}

unsigned long _card_chan(void)
{
	assert(0);
	return 0;
}

long _card_write(long chan, long block, unsigned char *buf)
{
	assert(0);
	return 0;
}

long _card_read(long chan, long block, unsigned char *buf)
{
	assert(0);
	return 0;
}

long _card_format(long chan)
{
	assert(0);
	return 0;
}
