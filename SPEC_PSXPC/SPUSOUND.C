#include "SPUSOUND.H"

#include "SOUND.H"
#include "SPECIFIC.H"

short DepthTable[5] =
{
	0x0000, 0x1000, 0x1800, 0x4000, 0x7FFF
};

short CurrentReverb;
int LnSamplesLoaded;
long LlVABAddr;
unsigned char LabSampleType[MAX_SOUND_SLOTS];
unsigned char LabFreeChannel[MAX_SOUND_SLOTS];
int LnFreeChannels;
static unsigned char LabSPUMallocArea[16];
unsigned long LadwSampleAddr[256];

void SPU_Init()//62650(<), 62D34(<) (F)
{
	S_Warn("[SPU_Init] - Unimplemented!\n");
	return;
}

void SPU_FreeSamples()//62610, 62CF4
{
	S_Warn("[SPU_FreeSamples] - Unimplemented!\n");
}

void SPU_FreeChannel(int channel_index)//91668, 936AC (F)
{
	LabSampleType[channel_index] = 0;
	LabFreeChannel[LnFreeChannels++] = channel_index;
}

void S_SetReverbType(int Reverb)//91CF4, 93D40
{
	if (Reverb != CurrentReverb)
	{
		CurrentReverb = Reverb;
	}
}

int SPU_UpdateStatus()//915FC, 93640
{
	int i = 0;
	char status[MAX_SOUND_SLOTS];

	return LnFreeChannels;
}

unsigned char SPU_AllocChannel()//915B0, 935F4
{
	if (LnFreeChannels == 0)
	{
		if (SPU_UpdateStatus() != 0)
		{
			return -1;
		}
	}

	//loc_915DC

	return LabFreeChannel[--LnFreeChannels];
}