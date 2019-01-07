#include "SOUND.H"

#include "GAMEFLOW.H"
#include "SPECIFIC.H"
#include "EFFECTS.H"
#if !PC_VERSION
#include "SFX.H"
#else
#include "GLOBAL.H"
#endif
#include "SPECTYPES.H"
#include <stddef.h>

int sound_active = 0;
short* sample_lut;
struct SAMPLE_INFO* sample_infos;
struct SoundSlot LaSlot[MAX_SOUND_SLOTS];

void SayNo()//55BE0(<), 56044(<) (F)
{
	int fx = SFX_LARA_NO;

	if (Gameflow->Language == LNG_FRENCH)
	{
		fx = SFX_LARA_NO_FRENCH;
	}
	else if (Gameflow->Language == LNG_JAPAN)
	{
		fx = SFX_LARA_NO_JAPANESE;
	}

	SoundEffect(fx, NULL, SFX_ALWAYS);

	return;
}

void SOUND_Init()//920DC(<), 94128(<) (F)
{
	int i;

	for (i = 0; i < MAX_SOUND_SLOTS; i++)
	{
		LaSlot[i].nSampleInfo = -1;
	}

	sound_active = 1;
}

#if PSXPC_VERSION
void SOUND_Stop()//920A4(<), 940F0(<) (F)
{
	int i;

#if PSXPC_VERSION
	return;///@FIXME infinite loop PSXPC
#endif

	if (sound_active != 0)
	{
		for (i = 0; i < MAX_SOUND_SLOTS; i++)
		{
			LaSlot[i].nSampleInfo = -1;
		}

		S_SoundStopAllSamples();
	}
}
#endif