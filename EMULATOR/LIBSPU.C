#include "LIBSPU.H"

unsigned long SpuWrite(unsigned char * addr, unsigned long size)
{
	return 0;
}

long SpuSetTransferMode(long mode)
{
	return 0;
}

unsigned long SpuSetTransferStartAddr(unsigned long addr)
{
	return 0;
}

long SpuIsTransferCompleted(long flag)
{
	return 0;
}

void SpuInit(void)
{
}

long SpuSetReverb(long on_off)
{
	return 0;
}

unsigned long SpuSetReverbVoice(long on_off, unsigned long voice_bit)
{
	return 0;
}

void SpuSetCommonAttr(SpuCommonAttr * attr)
{
}

long SpuInitMalloc(long num, char * top)
{
	return 0;
}

long SpuMalloc(long size)
{
	return 0;
}

long SpuMallocWithStartAddr(unsigned long addr, long size)
{
	return 0;
}

void SpuFree(unsigned long addr)
{
}

void SpuSetCommonMasterVolume(short mvol_left, short mvol_right)
{
}

long SpuSetReverbModeType(long mode)
{
	return 0;
}

void SpuSetReverbModeDepth(short depth_left, short depth_right)
{
}
