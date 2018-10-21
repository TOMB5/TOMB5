#include "SPUSOUND.H"

#include "SFX.H"
#include "SOUND.H"

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


void SPU_FreeSamples()//62610, 62CF4 (F) (*)
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

void SPU_Init()//62650(<), 62D34(<) (F) (*)
{
	int nChannel;
	
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
	for(nChannel = 0; nChannel < MAX_SOUND_SLOTS; nChannel++)
	{
		SPU_FreeChannel(nChannel);
	}
	
	LlVABAddr = 0;
	LnSamplesLoaded = 0;

	return;
}