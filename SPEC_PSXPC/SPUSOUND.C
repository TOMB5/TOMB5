#include "SPUSOUND.H"

#include "SOUND.H"
#include "SPECIFIC.H"

#ifdef PSX
	#include <sys/types.h>
	#include <LIBSPU.H>
#endif

short DepthTable[5] =
{
	0x0000, 0x0000, 0x1000, 0x0010, 0x1800
};
short CurrentReverb;
int LnSamplesLoaded;
long LlVABAddr;
struct SpuVoiceAttr sva;
unsigned char LabSampleType[MAX_SOUND_SLOTS];
unsigned char LabFreeChannel[MAX_SOUND_SLOTS];
int LnFreeChannels;
static unsigned char LabSPUMallocArea[16];
unsigned long LadwSampleAddr[256];

void SPU_Init()//62650(<), 62D34(<) (F)
{
	int i = 0;//$s0
#ifdef PSX
	SpuInit();
	SpuInitMalloc(1, LabSPUMallocArea);
	SpuSetTransferMode(0);
	SpuSetCommonMasterVolume(0x3FFF, 0x3FFF);
	SpuSetReverbModeType(0x103);
	SpuSetReverbModeDepth(0x1FFF, 0x1FFF);
	SpuSetReverbVoice(1, -1);
	SpuSetReverb(1);

	LnFreeChannels = 0;

	//loc_626B4
	while (i < MAX_SOUND_SLOTS)
	{
		SPU_FreeChannel(i++);
	}
#else
	S_Warn("[SPU_Init] - Unimplemented!\n");
#endif
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

void S_SetReverbType(int Reverb /*$a0*/)//91CF4, 93D40
{
	if (Reverb != CurrentReverb)
	{
		CurrentReverb = Reverb;
		//jal	sub_6B768 // SpuSetReverbModeDepth(DepthTable[Reverb],?);
		//jal	sub_6B850 //SpuSetReverb(1); //SPU_ON
	}
}


int SPU_UpdateStatus()//915FC, 93640
{
	int i = 0;
	char status[MAX_SOUND_SLOTS];

#ifdef PSX
	SpuGetAllKeysStatus(&status);

	//loc_9161C
	for (i = 0; i < MAX_SOUND_SLOTS; i++)
	{
		if ((status[i] - 1) < 2 && LabSampleType[i] != 0)
		{
			SPU_FreeChannel(i);
		}
	}
#endif
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
	LnFreeChannels--;
	
	return LabFreeChannel[LnFreeChannels];
}