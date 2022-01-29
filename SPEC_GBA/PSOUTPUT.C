#include "PSOUTPUT.H"

#include "PSXINPUT.H"
#include "SAVEGAME.H"
#include "STYPES.H"

static struct VIBRATION vib[2];

void SetupPadVibration(short num, short acc, short lev, short sus, int dec, int len)//604A4(<), 6101C(<) (F) (*) (D)
{
	struct VIBRATION* v = &vib[num];

	v->Acc = acc;
	v->Lev = lev;
	v->Flag = 0;
	v->Rate = 0;
	v->Vib = 0;
	v->Sus = len - sus;
	v->Dec = dec;
	v->Len = len;
}

void VibratePad()//604EC(<), 61064(<) (F) (*) (D)
{
	int i;
	struct VIBRATION* v = &vib[0];

	if (DualShock == 0 || savegame.VibrateOn == 0)
	{
		//loc_60510
		Motors[0] = 0;
		Motors[1] = 0;
		return;
	}

	//loc_6052C
	for (i = 0; i < 2; i++, v++)
	{
		if (v->Len != 0)
		{
			if (v->Flag == 0)
			{
				v->Rate += v->Acc;

				if (v->Rate >= v->Lev)
				{
					v->Rate = v->Lev;
					v->Flag = 1;
				}//loc_605DC
			}
			else if (v->Flag == 1)
			{
				//loc_60588
				if (v->Len <= v->Sus)
				{
					v->Flag = 2;
				}//loc_605DC
			}
			else if (v->Flag == 2)
			{
				//loc_605AC
				v->Rate -= v->Dec;

				if (v->Rate << 16 < 0)
				{
					v->Rate = 0;
					v->Flag = 3;
				}//loc_605DC
			}

			//loc_605DC
			v->Vib += v->Rate;

			if (i != 0)
			{
				if (v->Vib >> 8 != 0)
				{
					Motors[1] = v->Vib >> 8;
					v->Vib &= 0xFF;
				}//loc_60650
				else
				{
					//loc_60618
					Motors[1] = 0;
				}//loc_60650
			}
			else
			{
				//loc_60628
				if (v->Vib >> 12 != 0)
				{
					Motors[0] = 1;
					v->Vib -= 4096;
				}
				else
				{
					//loc_60648
					Motors[0] = 0;
				}
			}

			//loc_60650
			v->Len--;
		}
		else
		{
			//loc_60664
			Motors[i] = 0;
		}
	}
}