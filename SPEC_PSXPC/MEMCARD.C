#include "MEMCARD.H"

#ifdef PSX
	#include <LIBAPI.H>
#endif

void MemCardInit(long val)//67B5C(<), ?
{
#ifdef PSX
	InitCARD(val);
	StartCARD();
#endif
	//_bu_init ?
	return;
}
