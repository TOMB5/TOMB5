#include "SOUND.H"

#include "GAMEFLOW.H"
#include "SPECIFIC.H"

int sound_active;
short* sample_lut;
struct SAMPLE_INFO* sample_infos;
struct SoundSlot LaSlot[MAX_SOUND_SLOTS];

void SayNo()//55BE0, 56044
{
	int fx = 2;

	if (Gameflow->Language == FRENCH)
	{
		fx = 348;
	}
	else if (Gameflow->Language == JAPAN)
	{
		fx = 349;
	}

	//SoundEffect(fx, 0, 2); //$a0, $a1, $a2

	return;
}

void SOUND_Init()//920DC, 94128
{
	int i;

	for (i = 0; i < MAX_SOUND_SLOTS; i++)
	{
		LaSlot[i].nSampleInfo = -1;
	}

	sound_active = 1;
}

void SOUND_Stop()//920A4, 940F0
{
	int i;

	if (sound_active != 0)
	{
		for (i = 0; i < MAX_SOUND_SLOTS; i++)
		{
			LaSlot[i].nSampleInfo = -1;
		}

#ifndef PC_VERSION
		S_SoundStopAllSamples();
#endif
	}
}