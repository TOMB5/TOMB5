#include "JOBY5.H"

#include "CAMERA.H"
#include "CONTROL.H"
#include "EFFECTS.H"
#include "MISC.H"

#if PSX_VERSION
void* func[] __attribute__((section(".header"))) =
{
	&CODEWAD_Joby5_Func1,
};

short hData[] __attribute__((section(".header"))) =
{
	0,
};

unsigned short data[] __attribute__((section(".data"))) =
{
	0,
};
#endif

void CODEWAD_Joby5_Func1()
{
#if PSX_VERSION

	if (!(GlobalCounter & 0x1FF))
	{
		SoundEffect(0xEA, 0, 0x1008);
	}
	
	//loc_38
	if (hData[0] > 0)
	{
		++hData[0];
	}
	
	//loc_54
	if (hData[0] > 0x1C2 && !(GetRandomControl() & 0x1FF))
	{
		hData[0] = -(GetRandomControl() & 0x1F) - 32;
		data[0] = 0;
	}//loc_A0
	else
	{
		if (hData[0] < 0)
		{
			if (data[0] < ABS(hData[0]))
			{
				data[0]++;
				camera.bounce = -(data[0] / data[0]);
			}
			else
			{
				//loc_104
				camera.bounce = -(GetRandomControl() / ABS(hData[0]));
				hData[0]++;
			}
		}
	}
	//loc_14C
#endif
	return;
}