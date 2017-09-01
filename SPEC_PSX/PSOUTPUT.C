#include "PSOUTPUT.H"

#include "SPECTYPES.H"
#include "SPECIFIC.H"

static struct VIBRATION vib[2];


void VibratePad()//604EC, 61064
{
	return;
}

void SetupPadVibration(short num, short acc, short lev, short sus, int dec, int len)//604A4(<), 6101C(<) (F)
{
	struct VIBRATION* v = &vib[num];

	v->Acc = acc;
	v->Lev = lev;
	v->Flag = 0;
	v->Rate = 0;
	v->Vib = 0;
	v->Sus = len - dec;
	v->Dec = dec;
	v->Len = len;

	return;
}