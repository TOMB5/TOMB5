#include "LIBSPU.H"
#include "LIBETC.H"
#include <stdio.h>
#include "EMULATOR.H"

#include <string.h>

enum VV_Phase
{
	PHASE_NORMAL = 0,
	PHASE_INVERTED = 1
};

enum VV_SweepMode
{
	SWEEP_INCREASE = 0,
	SWEEP_DECREASE = 1
};

enum VV_SweepSlope
{
	SLOPE_LINEAR = 0,
	SLOPE_EXPONENTIAL = 1
};

enum VD_Pitch
{
	PITCH_MINUS3 = 0x0200,
	PITCH_MINUS2 = 0x0400,
	PITCH_MINUS1 = 0x0800,
	PITCH_ORIG   = 0x1000,
	PITCH_PLUS1  = 0x2000,
	PITCH_PLUS2  = 0x3fff
};

union VoiceVolume
{
	struct
	{
		unsigned short Volume : 14;
		unsigned short Phase : 1;
	} VolumeMode;

	struct
	{
		unsigned short Volume : 7;
		unsigned short _pad : 5;
		unsigned short Phase : 1;
		unsigned short Mode : 1;
		unsigned short Slope : 1;
	} SweepMode;

	unsigned short Raw;
};

struct VoiceData
{
	union VoiceVolume VolumeLeft;
	union VoiceVolume VolumeRight;

	unsigned short Pitch;

	unsigned short StartAddress;

	unsigned short SustainLevel : 4;
	unsigned short DecayRate : 4;
	unsigned short AttackRate : 7;
	unsigned short AttackMode : 1; // lin or exp

	unsigned short ReleaseRate : 5;
	unsigned short DecreaseMode : 1; // lin or exp
	unsigned short SustainRate : 7;
	unsigned short _pad : 1;
	unsigned short SustainRateMode : 1; // inc or dec
	unsigned short SustainRateSlope : 1; // lin or exp

	unsigned short CurrentADSRVolume;

	unsigned short RepeatAddress;
};

struct VoiceData Voices[24]; // 0x1F801C00

struct ReverbDepthInfo
{
	unsigned short Volume : 15;
	unsigned short Phase : 1;
};

struct
{
	union VoiceVolume VolumeLeft;
	union VoiceVolume VolumeRight;
} MasterVolume; // 1f801d80

struct
{
	struct
	{
		unsigned short Volume : 15;
		unsigned short Phase : 1;
	} Left, Right;
} ReverbDepth; // 1f801d84 

unsigned int SPU_DELAY = 0x200931E1; // 1F801014h

int AllocBlockNum = 0;
int AllocLastNum = 0;
char* memList = NULL;
int EVdma = 0;
int keystat = 0;
int trans_mode = 0;
int rev_flag = 0;
int rev_reserve_wa = 0;
int rev_offsetaddr = 0;
int rev_attr = 0;
int dword_9EE7C = 0;
short word_9EE80 = 0;
short word_9EE82 = 0;
int dword_9EE84 = 0;
int dword_9EE88 = 0;
int RQvoice = 0;
int RQmask = 0;
int voice_centerNote[12] =
{
	-1073692672, -1073692672, -1073692672, -1073692672, -1073692672, -1073692672,
	-1073692672, -1073692672, -1073692672, -1073692672, -1073692672, -1073692672
};
int zerobuf[256] = { 0 };
int env = 0;
int isCalled = 0;
int startAddr[20] =
{
	65534, 64296, 64536, 63224, 61956, 
	59972, 52640, 53240, 53240, 63616, 
	2, 1240, 984, 2312, 3580, 
	5564, 7896, 12296, 12296, 1920
};
unsigned int DMAControlRegister = 0;
unsigned int DMA1 = 0;
unsigned int DMA2 = 0;
unsigned int DMA3 = 0;
void* RXX[6] = 
{
	&Voices, &DMA1, &DMA2, &DMA3, &DMAControlRegister, &SPU_DELAY
};
short tsa[2] = { 0, 0 };
int transMode = 0;
int addrMode = 0;
int mem_mode = 2;
int mem_mode_plus = 3;
int mem_mode_unit = 8;
int mem_mode_unitM = 7;
int inTransfer = 1;
int transferCallback = 0;
int IRQCallback = 0;
char* spu_buf;
long spu_b_size = 0;


unsigned long SpuWrite(unsigned char * addr, unsigned long size)
{
	//eprintf("SPU WRITE size=%d\n", size);
	//memcpy(spu_buf, addr, size);
	//spu_b_size = size;
	UNIMPLEMENTED();
	return 0;
}

long SpuSetTransferMode(long mode)
{
	long mode_fix = mode == 0 ? 0 : 1;

	trans_mode = mode;
	transMode = mode_fix;

	return mode_fix;
}

unsigned long SpuSetTransferStartAddr(unsigned long addr)
{
	UNIMPLEMENTED();
	return 0;
}

long SpuIsTransferCompleted(long flag)
{
	UNIMPLEMENTED();
	return 0;
}

void SpuInit(void)
{
	eprintf("SpuInit\n");
	ResetCallback();
	UNIMPLEMENTED();
	spu_buf = NULL;/* (char*)malloc(1024 * 1024)*/;
}

long SpuSetReverb(long on_off)
{
	UNIMPLEMENTED();
	return 0;
}

unsigned long SpuSetReverbVoice(long on_off, unsigned long voice_bit)
{
	UNIMPLEMENTED();
	return 0;
}

void SpuSetCommonAttr(SpuCommonAttr * attr)
{
	UNIMPLEMENTED();
}

long SpuInitMalloc(long num, char * top)
{
	if (num > 0)
	{
		memList = top;
		AllocLastNum = 0;
		AllocBlockNum = num;
		*((int*)memList) = mem_mode_plus = 0x4000 | 0x1010;
		*((int*)memList + 1) = 0x4000;
	}

	return num;
}

long SpuMalloc(long size)
{
	return 0/*(long)(uintptr_t)malloc(size)*/;
}

long SpuMallocWithStartAddr(unsigned long addr, long size)
{
	UNIMPLEMENTED();
	return 0;
}

void SpuFree(unsigned long addr)
{
	/*free((void*)(uintptr_t)addr)*/;
}

void SpuSetCommonMasterVolume(short mvol_left, short mvol_right)// (F)
{
	MasterVolume.VolumeLeft.Raw = mvol_left;
	MasterVolume.VolumeRight.Raw = mvol_right;
}

long SpuSetReverbModeType(long mode)
{
	UNIMPLEMENTED();
	return 0;
}

void SpuSetReverbModeDepth(short depth_left, short depth_right)
{
	UNIMPLEMENTED();
}
