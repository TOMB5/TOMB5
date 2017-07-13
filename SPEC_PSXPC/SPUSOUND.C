#include "SPUSOUND.H"

extern short DepthTable[5];
extern short CurrentReverb;
extern int LnSamplesLoaded;
extern long LlVABAddr;
extern struct SpuVoiceAttr sva;
extern unsigned char LabSampleType[24];
extern unsigned char LabFreeChannel[24];
extern int LnFreeChannels;
static unsigned char LabSPUMallocArea[16];
extern unsigned long LadwSampleAddr[256];

void SPU_Init()
{

}

void S_SetReverbType(int Reverb /*$a0*/)//91CF4, *
{
	if (Reverb != CurrentReverb)
	{
		CurrentReverb = Reverb;
		//jal	sub_6B768 // SpuSetReverbModeDepth(DepthTable[Reverb],?);
		//jal	sub_6B850 //SpuSetReverb(1); //SPU_ON
	}
}