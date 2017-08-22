#ifndef SPUSOUND_H
#define SPUSOUND_H

#include "PSXTYPES.H"

extern short DepthTable[5];
extern short CurrentReverb;
extern int LnSamplesLoaded;
extern long LlVABAddr;
extern struct SpuVoiceAttr sva;
extern unsigned char LabSampleType[];
extern unsigned char LabFreeChannel[];
extern int LnFreeChannels;
extern unsigned long LadwSampleAddr[256];

extern int _spu_EVdma;
extern int dword_A0F90;
extern int _spu_trans_mode;
extern int _spu_rev_flag;
extern int _spu_rev_reserve_wa;
extern int _spu_rev_offsetaddr;
extern int _spu_rev_attr;
extern int dword_A0FA8;
extern short word_A0FAC;
extern short word_A0FAE;
extern int dword_A0FB0;
extern int dword_A0FB4;
extern int dword_A0FB8;
extern int dword_A0FBC;
extern int dword_A0FC0[11];
extern int dword_A13F0;
extern int _spu_isCalled;
extern int _spu_AllocBlockNum;
extern int _spu_AllocLastNum;
extern int _spu_memList;
extern int _spu_rev_startaddr;
extern int _spu_rev_param[18];
extern int _spu_RXX;
extern int dword_A1700;
extern int dword_A1704;
extern int dword_A1708;
extern int dword_A170C;
extern int dword_A1710;
extern int _spu_tsa;
extern int _spu_transMode;
extern int _spu_addrMode;
extern int _spu_mem_mode;
extern int _spu_mem_mode_plus;
extern int _spu_mem_mode_unit;
extern int _spu_mem_mode_unitM;
extern int _spu_inTransfer;
extern SpuTransferCallbackProc _spu_transferCallback;
extern SpuIRQCallbackProc _spu_IRQCallback;
extern int dword_A173C[4];
extern int dword_A174C;
extern int dword_A1750;
extern int dword_A1754;
extern int dword_A1758;
extern int dword_A1768;

extern void SPU_Init();
extern void SPU_FreeSamples();
extern void S_SetReverbType(int Reverb);
extern void SPU_FreeChannel(int channel_index);
extern int SPU_UpdateStatus();
extern unsigned char SPU_AllocChannel();
extern void _SpuIsInAllocateArea_(int arg0);
extern void _SpuIsInAllocateArea(int arg0);
extern void SpuSetReverb(int a);
extern void SpuSetReverbModeParam(int a);
extern void SpuSetReverbDepth(int a);
extern void SpuSetReverbVoice(int a, int b);
extern void SpuIsTransferCompleted(long a);
extern void SpuInit();

#endif