#include "SPUSOUND.H"

#include "SFX.H"
#include "SOUND.H"
#include "SPECIFIC.H"

short DepthTable[5] =
{
	0x0000, 0x1000, 0x1800, 0x4000, 0x7FFF
};

//Number of times SPU malloc can be called.
#define MAX_SPU_MALLOC_CALLS 1
#define SPU_MALLOC_RECSIZ 8

short CurrentReverb;
int LnSamplesLoaded;
long LlVABAddr;
//SpuVoiceAttr sva;
unsigned char LabSampleType[MAX_SOUND_SLOTS];
unsigned char LabFreeChannel[MAX_SOUND_SLOTS];
int LnFreeChannels;
static unsigned char LabSPUMallocArea[SPU_MALLOC_RECSIZ * (MAX_SPU_MALLOC_CALLS + 1)];
unsigned long LadwSampleAddr[MAX_NUM_SOUND_EFFECTS];

void SPU_FreeSamples()//62610, 62CF4 (F) (*)
{
	//SPU_StopAll();

	if (LnSamplesLoaded != 0)
	{
		//SpuFree(LlVABAddr);
	}

	LlVABAddr = 0;
	LnSamplesLoaded = 0;

	return;
}

void SPU_Init()//62650(<), 62D34(<) (F) (*)
{
	int nChannel;

	LnFreeChannels = 0;

	//loc_626B4
	for (nChannel = 0; nChannel < MAX_SOUND_SLOTS; nChannel++)
	{
		//SPU_FreeChannel(nChannel);
	}

	LlVABAddr = 0;
	LnSamplesLoaded = 0;

	return;
}