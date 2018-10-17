#include "DRAWOBJ.H"

#include "SPECIFIC.H"

#include <INLINE_C.H>

#ifndef USE_ASM && PSX_VERSION
void MakeMono(unsigned short* s, unsigned char* d)//7F9E4
{
	S_Warn("[MakeMono] - Unimplemented!\n");
}

void InitObjGTE()
{
#ifdef PAELLA
	S_Warn("[InitObjGTE] - Unimplemented!\n");
#else
	__asm__ volatile ("li $0, 0xAA;");
	__asm__ volatile ("ctc2	$0, $29;");
	__asm__ volatile ("li $0, 0x80A;");
	__asm__ volatile ("ctc2	$0, $30;");
	gte_ldfcdir(0, 0, 0);
#endif
}

#endif