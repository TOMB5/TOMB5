#include "CALCLARA.H"

void S_SetupClutAdder(long unk)
{
#if PSX_VERSION
	__asm__ volatile("ctc2 %0, $28": "=r" (unk) : );
#endif
}