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

void SOUND_Stop()//920A4(<), 940F0(<) (F)
{
	int i;

	if (sound_active != 0)
	{
		for (i = 0; i < MAX_SOUND_SLOTS; i++)
		{
			LaSlot[i].nSampleInfo = -1;
		}

		S_SoundStopAllSamples();
	}
}

void SOUND_EndScene()//91D80(<) ? (F)
{
	struct SoundSlot* slot;//$s1
	long i;//$s0

	if (!sound_active)
	{
		return;
	}

	//loc_91DAC
	for (i = 0, slot = &LaSlot[i]; i < 24; i++, slot++)
	{
		if (slot->nSampleInfo >= 0)
		{
			if ((sample_infos[slot->nSampleInfo].flags & 3) == 3)
			{
				if (slot->nVolume != 0)
				{
					S_SoundSetPanAndVolume(i, slot->nPan, slot->nVolume & 0xFFFF, slot->distance);
					S_SoundSetPitch(i, slot->nPitch);
					slot->nVolume = 0;
				}
				else
				{
					//loc_91E08
					S_SoundStopSample(i);
					slot->nSampleInfo = -1;
				}
			}
			else
			{
				//loc_91E1C
				if (S_SoundSampleIsPlaying(0) == 0)
				{
					slot->nSampleInfo = -1;
				}
				else
				{
					if ((slot->pos.x | slot->pos.y | slot->pos.z) != 0)
					{
						GetPanVolume(slot);
						S_SoundSetPanAndVolume(i, slot->nPan, slot->nVolume, slot->distance);
					}//loc_91E64
				}
			}
		}//loc_91E64
	}
}