#include "SOUND.H"

#include "SPECIFIC.H"

int sound_active;
short* sample_lut;
struct SAMPLE_INFO* sample_infos;
struct SoundSlot LaSlot[MAX_SOUND_SLOTS];

void SayNo()
{
//	int fx; // $a0
}

void SOUND_Stop()//920A4, ?
{
	if (sound_active != 0)
	{
		for (int i = 0; i < MAX_SOUND_SLOTS; i++)
		{
			LaSlot[i].nSampleInfo = -1;
		}

		//S_SoundStopAllSamples();
	}
}