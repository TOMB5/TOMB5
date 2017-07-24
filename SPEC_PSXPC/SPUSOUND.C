#include "SPUSOUND.H"

short DepthTable[5];
short CurrentReverb;
int LnSamplesLoaded;
long LlVABAddr;
struct SpuVoiceAttr sva;
unsigned char LabSampleType[24];
unsigned char LabFreeChannel[24];
extern int LnFreeChannels;
static unsigned char LabSPUMallocArea[16];
unsigned long LadwSampleAddr[256];

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