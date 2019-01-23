#include "LIBAPI.H"

#include <assert.h>

int sp = 0;

long SetRCnt(unsigned long unk00, unsigned short, long)
{
	
	return 0;
}

long GetRCnt(unsigned long unk00)
{
	
	return 0;
}

long ResetRCnt(unsigned long unk00)
{
	
	return 0;
}

long StartRCnt(unsigned long unk00)
{
	
	return 0;
}

long StopRCnt(unsigned long unk00)
{
	
	return 0;
}

long OpenEvent(unsigned long unk00, long, long, long(*func)())
{
	
	return 0;
}

long CloseEvent(long unk00)
{
	
	return 0;
}

long WaitEvent(long unk00)
{
	
	return 0;
}

long TestEvent(long unk00)
{
	
	return 0;
}

long EnableEvent(long unk00)
{
	
	return 0;
}

long DisableEvent(long unk00)
{
	
	return 0;
}

void DeliverEvent(unsigned long unk00, unsigned long)
{
	
}

void UnDeliverEvent(unsigned long unk00, unsigned long)
{
	
}

long OpenTh(long(*func)(), unsigned long, unsigned long)
{
	
	return 0;
}

int CloseTh(long unk00)
{
	
	return 0;
}

int ChangeTh(long unk00)
{
	
	return 0;
}

long open(char* unk00, unsigned long)
{
	
	return 0;
}

long close(long unk00)
{
	
	return 0;
}

long lseek(long unk00, long, long)
{
	
	return 0;
}

long read(long unk00, void *, long)
{
	
	return 0;
}

long write(long unk00, void *, long)
{
	
	return 0;
}

long ioctl(long unk00, long, long)
{
	
	return 0;
}

struct DIRENTRY* firstfile(char* unk00, struct DIRENTRY *)
{
	
	return 0;
}

struct DIRENTRY* nextfile(struct DIRENTRY* unk00)
{
	
	return 0;
}

long erase(char* unk00)
{
	
	return 0;
}

long undelete(char* unk00)
{
	
	return 0;
}

long format(char* unk00)
{
	
	return 0;
}
long rename(char* unk00, char *)
{
	
	return 0;
}

long cd(char* unk00)
{
	
	return 0;
}

long LoadTest(char*  unk00, struct EXEC *)
{
	
	return 0;
}

long Load(char * unk00, struct EXEC *)
{
	
	return 0;
}

long Exec(struct EXEC * unk00, long, char **)
{
	
	return 0;
}

long LoadExec(char * unk00, unsigned long, unsigned long)
{
	
	return 0;
}

long InitPAD(char * unk00, long, char *, long)
{
	
	return 0;
}

long StartPAD()
{
	
	return 0;
}

void StopPAD()
{
	
}

void EnablePAD()
{
	
}

void DisablePAD()
{
	
}

void FlushCache()
{
	
}

void ReturnFromException()
{
	
}

int  EnterCriticalSection()
{
	
	return 0;
}

void ExitCriticalSection()
{
	
}

void Exception()
{
	
}

void SwEnterCriticalSection()
{
	
}
void SwExitCriticalSection()
{
	
}

unsigned long SetSp(unsigned long newsp)//(F)
{
	unsigned long old_sp = sp;
	sp = newsp;
	return old_sp;
}

unsigned long GetSp()
{
	
	return 0;
}

unsigned long GetGp()
{
	
	return 0;
}

unsigned long GetCr()
{
	
	return 0;
}

unsigned long GetSr()
{
	
	return 0;
}

unsigned long GetSysSp()
{
	
	return 0;
}

long SetConf(unsigned long, unsigned long, unsigned long)
{
	
	return 0;
}

void GetConf(unsigned long *, unsigned long *, unsigned long *)
{
	
}

long _get_errno(void)
{
	
	return 0;
}

long _get_error(long)
{
	
	return 0;
}

void SystemError(char, long)
{
	
}

void SetMem(long)
{
	
}

long Krom2RawAdd(unsigned long)
{
	
	return 0;
}

long Krom2RawAdd2(unsigned short)
{
	
	return 0;
}

void _96_init(void)
{
	
}

void _96_remove(void)
{
	
}

void _boot(void)
{
	
}

void ChangeClearPAD(long)
{
	
}

void InitCARD(long val)
{
	
}

long StartCARD()
{
	
	return 0;
}

long StopCARD()
{
	
	return 0;
}

void _bu_init()
{
	
}

long _card_info(long chan)
{
	
	return 0;
}

long _card_clear(long chan)
{
	
	return 0;
}

long _card_load(long chan)
{
	
	return 0;
}

long _card_auto(long val)
{
	
	return 0;
}

void _new_card()
{
	
}

long _card_status(long drv)
{
	
	return 0;
}

long _card_wait(long drv)
{
	
	return 0;
}

unsigned long _card_chan(void)
{
	
	return 0;
}

long _card_write(long chan, long block, unsigned char *buf)
{
	
	return 0;
}

long _card_read(long chan, long block, unsigned char *buf)
{
	
	return 0;
}

long _card_format(long chan)
{
	
	return 0;
}
