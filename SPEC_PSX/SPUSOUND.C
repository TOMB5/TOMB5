#include "SPUSOUND.H"

#include "SOUND.H"
#include "SPECIFIC.H"

#include <sys/types.h>
#include <LIBSPU.H>

short DepthTable[] =
{
	0x0000, 0x0000, 0x1000, 0x0010, 0x1800
};

//Number of times SPU malloc can be called.
#define MAX_SPU_MALLOC_CALLS 1

short CurrentReverb;
int LnSamplesLoaded;
long LlVABAddr;
SpuVoiceAttr sva;
unsigned char LabSampleType[MAX_SOUND_SLOTS];
unsigned char LabFreeChannel[MAX_SOUND_SLOTS];
int LnFreeChannels;
static unsigned char LabSPUMallocArea[SPU_MALLOC_RECSIZ * (MAX_SPU_MALLOC_CALLS + 1)];
unsigned long LadwSampleAddr[MAX_NUM_SOUND_EFFECTS];


void SPU_FreeSamples()//62610, 62CF4
{
	SPU_StopAll();
	
	if(LnSamplesLoaded != 0)
	{
		SpuFree(LlVABAddr);
	}

	LlVABAddr = 0;
	LnSamplesLoaded = 0;
	
	return;
}

void SPU_Init()//62650(<), 62D34(<) (F)
{
	int nChannel = 0;
	
	SpuInit();
	SpuInitMalloc(MAX_SPU_MALLOC_CALLS, (char*)&LabSPUMallocArea[0]);
	SpuSetTransferMode(SPU_TRANSFER_BY_DMA);
	SpuSetCommonMasterVolume(0x3FFF, 0x3FFF);
	SpuSetReverbModeType(SPU_REV_MODE_STUDIO_B | SPU_REV_MODE_CLEAR_WA);
	SpuSetReverbModeDepth(0x1FFF, 0x1FFF);
	SpuSetReverbVoice(SPU_ON, SPU_ALLCH);
	SpuSetReverb(SPU_ON);

	LnFreeChannels = 0;

	//loc_626B4
	while (nChannel < MAX_SOUND_SLOTS)
	{
		SPU_FreeChannel(nChannel++);
	}
	
	return;
}

void SPU_FreeChannel(int channel_index)//91668, 936AC (F)
{
	LabSampleType[channel_index] = 0;
	LabFreeChannel[LnFreeChannels++] = channel_index;
}

void S_SetReverbType(int reverb)//91CF4, 93D40
{
	if (reverb != CurrentReverb)
	{
		CurrentReverb = reverb;

		SpuSetReverbModeDepth(DepthTable[reverb], DepthTable[reverb]);
		SpuSetReverb(SPU_ON);
	}
}

void SPU_StopAll()
{
	int ret;

	SpuSetKey(SPU_OFF, SPU_ALLCH);
	
	do
	{
		ret = SPU_UpdateStatus();
	}
	while (ret != MAX_SOUND_SLOTS);
}

int SPU_UpdateStatus()//915FC, 93640
{
	int i = 0;
	char status[MAX_SOUND_SLOTS];

	SpuGetAllKeysStatus(&status[0]);

	//loc_9161C
	for (i = 0; i < MAX_SOUND_SLOTS; i++)
	{
		if ((status[i] - 1) < 2 && LabSampleType[i] != 0)
		{
			SPU_FreeChannel(i);
		}
	}
	
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