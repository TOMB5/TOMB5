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

int _spu_EVdma;
int dword_A0F90;
int _spu_trans_mode;
int _spu_rev_flag;
int _spu_rev_reserve_wa;
int _spu_rev_offsetaddr;
int _spu_rev_attr;
int dword_A0FA8;
short word_A0FAC;
short word_A0FAE;
int dword_A0FB0;
int dword_A0FB4;
int dword_A0FB8;
int dword_A0FBC;
int dword_A0FC0[11] =
{
	0xC000C000, 0x00C000C0, 0xC000C000, 0x00C000C0, 0xC000C000, 0x00C000C0, 0xC000C000, 0x00C000C0, 0xC000C000, 0x00C000C0, 0xC000C000
};
int dword_A13F0;
int _spu_isCalled;
int _spu_AllocBlockNum;
int _spu_AllocLastNum;
int _spu_memList;
int _spu_rev_startaddr = 0xFFFE;
int _spu_rev_param[18];
int _spu_RXX = 0x1F801C00;
int dword_A1700 = 0x1F8010C0;
int dword_A1704 = 0x1F8010C4;
int dword_A1708 = 0x1F8010C8;
int dword_A170C = 0x1F8010F0;
int dword_A1710 = 0x1F801014;
int _spu_tsa;
int _spu_transMode;
int _spu_addrMode;
int _spu_mem_mode = 2;
int _spu_mem_mode_plus = 3;
int _spu_mem_mode_unit = 8;
int _spu_mem_mode_unitM = 7;
int _spu_inTransfer = 1;
SpuTransferCallbackProc _spu_transferCallback;
SpuIRQCallbackProc _spu_IRQCallback;
int dword_A173C[4] = { 0x7070707, 0x7070707, 0x7070707, 0x7070707 };
int dword_A174C;
int dword_A1750;
int dword_A1754;
int dword_A1758 = 0x1F801070;
int dword_A1768 = 0x1F801040;

void SPU_Init()//62650(<), 62D34(<) (F)
{
	int i = 0;//$s0
#ifdef PSX_VERSION
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

#ifdef PSX_VERSION
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

void _SpuIsInAllocateArea_(int arg0)//734D0(<), 71ABC(<) (F)
{
	_SpuIsInAllocateArea(arg0 << _spu_mem_mode_plus);
}

void _SpuIsInAllocateArea(int arg0)//73450, 71A3C
{
	S_Warn("[_SpuIsInAllocateArea] - Unimplemented!\\n");
}
