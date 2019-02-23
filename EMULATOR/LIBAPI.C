#include "LIBAPI.H"

#include "EMULATOR_GLOBALS.H"
#include "EMULATOR.H"

int sp = 0;

long SetRCnt(long spec, unsigned short target, long mode)
{
	if (spec >= 3)
		return 0;

	counters[spec].Target = target;
	counters[spec].I2 = mode;
	
	return 1;
}

long GetRCnt(long spec)
{
	if (spec > 3)
		return 0;

	return counters[spec].Value;
}

long ResetRCnt(long spec)
{
	if (spec >= 3)
		return 0;

	counters[spec].Value = 0;

	return 1;
}

long StartRCnt(long spec)
{
	if (spec >= 3)
		return 0;

	counters[spec].IsStopped = FALSE;

	return 1;
}

long StopRCnt(long spec)
{
	if (spec >= 3)
		return 0;

	counters[spec].IsStopped = TRUE;

	return 1;
}
#undef OpenEvent
long OpenEvent(unsigned long unk00, long, long, long(*func)())
{
	UNIMPLEMENTED();
	return 0;
}

long CloseEvent(long unk00)
{
	UNIMPLEMENTED();
	return 0;
}

long WaitEvent(long unk00)
{
	UNIMPLEMENTED();
	return 0;
}

long TestEvent(long unk00)
{
	UNIMPLEMENTED();
	return 0;
}

long EnableEvent(long unk00)
{
	UNIMPLEMENTED();
	return 0;
}

long DisableEvent(long unk00)
{
	UNIMPLEMENTED();
	return 0;
}

void DeliverEvent(unsigned long unk00, unsigned long)
{
	UNIMPLEMENTED();
}

void UnDeliverEvent(unsigned long unk00, unsigned long)
{
	UNIMPLEMENTED();
}

long OpenTh(long(*func)(), unsigned long, unsigned long)
{
	UNIMPLEMENTED();
	return 0;
}

int CloseTh(long unk00)
{
	UNIMPLEMENTED();
	return 0;
}

int ChangeTh(long unk00)
{
	UNIMPLEMENTED();
	return 0;
}

long open(char* unk00, unsigned long)
{
	UNIMPLEMENTED();
	return 0;
}

long close(long unk00)
{
	UNIMPLEMENTED();
	return 0;
}

long lseek(long unk00, long, long)
{
	UNIMPLEMENTED();
	return 0;
}

long read(long unk00, void *, long)
{
	UNIMPLEMENTED();
	return 0;
}

long write(long unk00, void *, long)
{
	UNIMPLEMENTED();
	return 0;
}

long ioctl(long unk00, long, long)
{
	UNIMPLEMENTED();
	return 0;
}

struct DIRENTRY* firstfile(char* unk00, struct DIRENTRY *)
{
	UNIMPLEMENTED();
	return 0;
}

struct DIRENTRY* nextfile(struct DIRENTRY* unk00)
{
	UNIMPLEMENTED();
	return 0;
}

long erase(char* unk00)
{
	UNIMPLEMENTED();
	return 0;
}

long undelete(char* unk00)
{
	UNIMPLEMENTED();
	return 0;
}

long format(char* unk00)
{
	UNIMPLEMENTED();
	return 0;
}
long rename(char* unk00, char *)
{
	UNIMPLEMENTED();
	return 0;
}

long cd(char* unk00)
{
	UNIMPLEMENTED();
	return 0;
}

long LoadTest(char*  unk00, struct EXEC *)
{
	UNIMPLEMENTED();
	return 0;
}

long Load(char * unk00, struct EXEC *)
{
	UNIMPLEMENTED();
	return 0;
}

long Exec(struct EXEC * unk00, long, char **)
{
	UNIMPLEMENTED();
	return 0;
}

long LoadExec(char * unk00, unsigned long, unsigned long)
{
	UNIMPLEMENTED();
	return 0;
}

long InitPAD(char * unk00, long, char *, long)
{
	UNIMPLEMENTED();
	return 0;
}

long StartPAD()
{
	UNIMPLEMENTED();
	return 0;
}

void StopPAD()
{
	UNIMPLEMENTED();
}

void EnablePAD()
{
	UNIMPLEMENTED();
}

void DisablePAD()
{
	UNIMPLEMENTED();
}

void FlushCache()
{
	UNIMPLEMENTED();
}

void ReturnFromException()
{
	UNIMPLEMENTED();
}

int  EnterCriticalSection()
{
	UNIMPLEMENTED();
	return 0;
}

void ExitCriticalSection()
{
	UNIMPLEMENTED();
}

void Exception()
{
	UNIMPLEMENTED();
}

void SwEnterCriticalSection()
{
	UNIMPLEMENTED();
}
void SwExitCriticalSection()
{
	UNIMPLEMENTED();
}

unsigned long SetSp(unsigned long newsp)//(F)
{
	unsigned long old_sp = sp;
	sp = newsp;
	return old_sp;
}

unsigned long GetSp()
{
	UNIMPLEMENTED();
	return 0;
}

unsigned long GetGp()
{
	UNIMPLEMENTED();
	return 0;
}

unsigned long GetCr()
{
	UNIMPLEMENTED();
	return 0;
}

unsigned long GetSr()
{
	UNIMPLEMENTED();
	return 0;
}

unsigned long GetSysSp()
{
	UNIMPLEMENTED();
	return 0;
}

long SetConf(unsigned long, unsigned long, unsigned long)
{
	UNIMPLEMENTED();
	return 0;
}

void GetConf(unsigned long *, unsigned long *, unsigned long *)
{
	UNIMPLEMENTED();
}

long _get_errno(void)
{
	UNIMPLEMENTED();
	return 0;
}

long _get_error(long)
{
	UNIMPLEMENTED();
	return 0;
}

void SystemError(char, long)
{
	UNIMPLEMENTED();
}

void SetMem(long)
{
	UNIMPLEMENTED();
}

long Krom2RawAdd(unsigned long)
{
	UNIMPLEMENTED();
	return 0;
}

long Krom2RawAdd2(unsigned short)
{
	UNIMPLEMENTED();
	return 0;
}

void _96_init(void)
{
	UNIMPLEMENTED();
}

void _96_remove(void)
{
	UNIMPLEMENTED();
}

void _boot(void)
{
	UNIMPLEMENTED();
}

void ChangeClearPAD(long)
{
	UNIMPLEMENTED();
}

void InitCARD(long val)
{
	UNIMPLEMENTED();
}

long StartCARD()
{
	UNIMPLEMENTED();
	return 0;
}

long StopCARD()
{
	UNIMPLEMENTED();
	return 0;
}

void _bu_init()
{
	UNIMPLEMENTED();
}

long _card_info(long chan)
{
	UNIMPLEMENTED();
	return 0;
}

long _card_clear(long chan)
{
	UNIMPLEMENTED();
	return 0;
}

long _card_load(long chan)
{
	UNIMPLEMENTED();
	return 0;
}

long _card_auto(long val)
{
	UNIMPLEMENTED();
	return 0;
}

void _new_card()
{
	UNIMPLEMENTED();
}

long _card_status(long drv)
{
	UNIMPLEMENTED();
	return 0;
}

long _card_wait(long drv)
{
	UNIMPLEMENTED();
	return 0;
}

unsigned long _card_chan(void)
{
	UNIMPLEMENTED();
	return 0;
}

long _card_write(long chan, long block, unsigned char *buf)
{
	UNIMPLEMENTED();
	return 0;
}

long _card_read(long chan, long block, unsigned char *buf)
{
	UNIMPLEMENTED();
	return 0;
}

long _card_format(long chan)
{
	UNIMPLEMENTED();
	return 0;
}
