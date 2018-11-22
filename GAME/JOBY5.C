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

short data[] __attribute__((section(".header"))) =
{
	0,
	0
};
#endif

void CODEWAD_Joby5_Func1()
{
#if PC_VERSION || PSXPC_VERSION
	static short data[2];
#endif

	if (!(GlobalCounter & 0x1FF))
	{
		SoundEffect(0xEA, 0, 0x1008);
	}
	
	//loc_38
	if (data[0] > 0)
	{
		++data[0];
	}
	
	//loc_54
	if (data[0] > 0x1C2 && !(GetRandomControl() & 0x1FF))
	{
		data[0] = -(GetRandomControl() & 0x1F) - 32;
		data[1] = 0;
	}//loc_A0
	else
	{
		if (data[0] < 0)
		{
			if (data[1] < ABS(data[0]))
			{
				data[1]++;
				camera.bounce = -(data[1] / data[1]);
			}
			else
			{
				//loc_104
				GetRandomControl();
				camera.bounce = -(GetRandomControl() / ABS(data[0]));
				data[0]++;
			}
		}
	}
	//loc_14C

	return;
}