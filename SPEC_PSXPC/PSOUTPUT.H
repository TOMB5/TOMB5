#ifndef PSOUTPUT_H
#define PSOUTPUT_H

struct VIBRATION
{
	short Rate;
	short Len;
	short Lev;
	short Acc;
	short Dec;
	short Sus;
	short Flag;
	short Vib;
};

void SetupPadVibration(short num, short acc, short lev, short sus, int dec, int len);

#endif