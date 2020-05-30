#include "LIBSPU.H"
#include "LIBETC.H"
#include <stdio.h>
#include "EMULATOR.H"
#include "LIBAPI.H"

#include <string.h>

#define SPU_CENTERNOTE (-32768 / 2)

short _spu_voice_centerNote[24] =
{
	SPU_CENTERNOTE, SPU_CENTERNOTE, SPU_CENTERNOTE, SPU_CENTERNOTE, SPU_CENTERNOTE, SPU_CENTERNOTE, SPU_CENTERNOTE, SPU_CENTERNOTE, SPU_CENTERNOTE, SPU_CENTERNOTE,
	SPU_CENTERNOTE, SPU_CENTERNOTE, SPU_CENTERNOTE, SPU_CENTERNOTE, SPU_CENTERNOTE, SPU_CENTERNOTE, SPU_CENTERNOTE, SPU_CENTERNOTE, SPU_CENTERNOTE, SPU_CENTERNOTE,
	SPU_CENTERNOTE, SPU_CENTERNOTE, SPU_CENTERNOTE, SPU_CENTERNOTE
};

SpuCommonAttr dword_424;//Might be wrong struct, need to check
int _spu_isCalled = 0;
int _spu_FiDMA = 0;///@TODO decl as extern find initial value
int _spu_EVdma = 0;
int _spu_rev_flag = 0;
int _spu_rev_reserve_wa = 0;
int _spu_rev_offsetaddr = 0;
int _spu_rev_startaddr = 0;
int _spu_AllocBlockNum = 0;
int _spu_AllocLastNum = 0;
int _spu_memList = 0;
int _spu_trans_mode = 0;
int _spu_transMode = 0;
int _spu_keystat = 0;
int _spu_RQmask = 0;
int _spu_RQvoice = 0;
int _spu_env = 0;
char spu[440];//0x1F801C00 is base address
short* _spu_RXX = (short*)&spu[0];
int _spu_mem_mode_plus = 3;
void* _spu_transferCallback = NULL;///@TODO initial value check
int _spu_inTransfer = 0;///@TODO initial value check
unsigned short _spu_tsa = 0;

void SpuGetAllKeysStatus(char* status)
{
	//loc_2EC
	for (int i = 0; i < 24; i++, status++)
	{
		if ((_spu_keystat & (1 << i)))
		{
			if ((unsigned short)_spu_RXX[i << 3 + 6] != 0)
			{
				*status = 1;
			}
			else
			{
				*status = 3;
			}
		}
		else
		{
			//loc_330
			if ((unsigned short)_spu_RXX[i << 3 + 6] != 0)
			{
				*status = 2;
			}
			else
			{
				//loc_340
				*status = 0;
			}
		}
	}
}

void SpuSetVoiceAttr(SpuVoiceAttr* arg)//
{
    //s0 = arg
    int a0 = 0;
    int a1 = 0;
    int a2 = 0;
    //s1 = arg->mask
    //s5 = &_spu_voice_centerNote[0];
    //s2 = s1 < 1 ? 1 : 0;

    //loc_238
    for(int i = 0; i < 24; i++)
    {
        //v0 = 1
        //v1 = arg->voice
        //v0 = 1 << i
        //v1 = arg->voice & (1 << i);

        if ((arg->voice & (1 << i)))
        {
            //s3 = i << 3
            if ((arg->mask < 1) || (arg->mask & 0x10))
            {
                //loc_264
                //v0 = i << 4
                //v1 = &_spu_RXX[0];
                //a0 = arg->pitch
                _spu_RXX[(i << 3) + 2] = arg->pitch;
            }
            //loc_27C
            if (arg->mask < 1 || (arg->mask & 0x40))
            {
                _spu_voice_centerNote[i] = arg->sample_note;
            }
            //loc_298
            if (arg->mask < 1 || (arg->mask & 0x20))
            {
                //a1 = _spu_voice_centerNote[i] & 0xFF
                //a3 = arg->note
                //a0 = _spu_voice_centerNote[i] >> 8
                //a2 = arg->note >> 8
                //a3 = arg->note & 0xFF
                //v0 = _spu_note2pitch((_spu_voice_centerNote[i] >> 8), (_spu_voice_centerNote[i] & 0xFF), (arg->note >> 8), (arg->note & 0xFF));
                UNIMPLEMENTED();
                //_spu_RXX[(i << 3) + 2] = v0;
            }
            //loc_2D8
            if (arg->mask < 1 || (arg->mask & 0x1))
            {
                //v0 = arg->volume.left
                //a0 = 0
                //a1 = arg->volume.left & 0x7FFF
                //v0 = arg->mask & 4

                if (!(arg->mask & 0x4))
                {
                    //v0 = arg->volmode.left
                    switch (arg->volmode.left)
                    {
                    case 1:
                        //loc_33C
                        a0 = 0x8000;
                        break;
                    case 2:
                        //loc_344
                        a0 = 0x9000;
                        break;
                    case 3:
                        //loc_34C
                        a0 = 0xA000;
                        break;
                    case 4:
                        //loc_354
                        a0 = 0xB000;
                        break;
                    case 5:
                        //loc_35C
                        a0 = 0xC000;
                        break;
                    case 6:
                        //loc_364
                        a0 = 0xD000;
                        break;
                    case 7:
                        //loc_36C
                        a0 = 0xE000;
                        break;
                    }
                }
                //def_334
                if (a0 != 0)
                {
                    //v1 = arg->volume.left
                    if (arg->volume.left >= 128)
                    {
                        a1 = 127;
                    }
                    else if (arg->volume.left < 0)
                    {
                        a1 = 0;
                    }
                }
                //loc_3A0
                //v0 = &_spu_RXX[0];
                //v1 = &spu_RXX[i << 3];

                //v0 = a1 | a0
                _spu_RXX[(i << 3)] = a1 | a0;
            }//loc_3B8

            if ((arg->mask < 1) || (arg->mask & 0x2))
            {
                //v0 = arg->volume.right
                //a0 = 0
                //a1 = v0 & 0x7FFF

                if ((arg->mask < 1) || (arg->mask & 0x8))
                {
                    switch (arg->volmode.right)
                    {
                    case 1:
                        //loc_41C
                        a0 = 0x8000;
                        break;
                    case 2:
                        //loc_424
                        a0 = 0x9000;
                        break;
                    case 3:
                        //loc_42C
                        a0 = 0xA000;
                        break;
                    case 4:
                        //loc_434
                        a0 = 0xB000;
                        break;
                    case 5:
                        //loc_43C
                        a0 = 0xC000;
                        break;
                    case 6:
                        //loc_444
                        a0 = 0xD000;
                        break;
                    case 7:
                        //loc_44C
                        a0 = 0xE000;
                        break;
                    }
                }

                //def_414
                if (a0 != 0)
                {
                    if (arg->volume.right >= 128)
                    {
                        a1 = 127;
                    }
                    else if (arg->volume.right < 0)
                    {
                        a1 = 0;
                    }
                }//loc_480

                //v0 = &_spu_RXX[0];
                //v1 = &_spu_RXX[i << 3];
                _spu_RXX[(i << 3) + 1] = a1 | a0;
            }//loc_498

            if ((arg->mask < 1) || (arg->mask & 0x80))
            {
                UNIMPLEMENTED();
                //_spu_FsetRXXa(((i << 3) | 3), arg->addr);
            }
            //loc_4B4
            if ((arg->mask < 1) || (arg->mask & 0x10000))
            {
                UNIMPLEMENTED();
                //_spu_FsetRXXa((i << 3) | 7, arg->loop_addr);
            }//loc_4D4

            if ((arg->mask < 1) || (arg->mask & 0x20000))
            {
                _spu_RXX[i << 3] = arg->adsr1;
            }

            //loc_500
            if ((arg->mask < 1) || (arg->mask & 0x40000))
            {
                _spu_RXX[i << 3] = arg->adsr2;
            }
            //loc_52C

            if ((arg->mask < 1) || (arg->mask & 0x800))
            {
                //a1 = arg->ar
                if (arg->ar >= 128)
                {
                    a1 = 127;
                }

                a2 = 0;

                if ((arg->mask < 1) || (arg->mask & 0x100))
                {
                    //v1 = arg->a_mode
                    //v0 = 5
                    if (arg->a_mode == 5)
                    {
                        a2 = 128;
                    }
                }//loc_57C

                //v0 = &_spu_RXX[0];
                //s3 = &_spu_RXX[i << 3];
                //v0 = _spu_RXX[(i << 3) + 4];
                //v1 = _spu_RXX[(i << 3) + 4] & 0xFF;
                //v0 = ((a1 | a2) << 8)
                _spu_RXX[(i << 3) + 4] = (_spu_RXX[(i << 3) + 4] & 0xFF) | ((a1 | a2) << 8);

            }//loc_5A8

            if ((arg->mask < 1) || arg->mask & 0x1000)
            {
                a1 = arg->dr;
                if (arg->dr >= 16)
                {
                    a1 = 15;
                }//loc_5D0

                _spu_RXX[(i << 3) + 4] = (_spu_RXX[(i << 3) + 4] & 0xFF0F) | (a1 << 4);

            }//loc_5F4

            if ((arg->mask < 1) || (arg->mask & 0x2000))
            {
                a1 = arg->sr;

                if (arg->sr >= 128)
                {
                    a1 = 127;
                }

                a2 = 256;

                if ((arg->mask < 1) || (arg->mask & 0x200))
                {
                    //v1 = arg->s_mode
                    if ((arg->s_mode) == 5)
                    {
                        //loc_674
                        a2 = 512;
                    }
                    else if (arg->s_mode >= 6)
                    {
                        //loc_658
                        if (arg->s_mode == 7)
                        {
                            //loc_67C
                            a2 = 768;
                        }
                    }
                    else if (arg->s_mode == 1)
                    {
                        //loc_66C
                        a2 = 0;
                    }
                }//loc_680
                //v0 = _spu_RXX[(i << 3) + 5];
                //v1 = (_spu_RXX[(i << 3) + 5] & 0x3F) | ((a1 | a2) << 6);
                //v0 = ((a1 | a2) << 6)
                _spu_RXX[(i << 3) + 5] = (_spu_RXX[(i << 3) + 5] & 0x3F) | ((a1 | a2) << 6);
            }//loc_6AC

            if ((arg->mask < 1) || (arg->mask & 0x4000))
            {
                a1 = arg->rr;

                if (arg->rr >= 32)
                {
                    a1 = 31;
                }
                //loc_6D4
                a2 = 0;

                if ((arg->mask < 1) || (arg->mask & 0x400))
                {
                    //v1 = arg->r_mode
                    if (arg->r_mode != 3 && arg->r_mode == 7)
                    {
                        a2 = 32;
                    }//loc_704
                }//loc_704

                //a0 = &_spu_RXX[(i << 3) + 5];
                _spu_RXX[(i << 3) + 5] = (_spu_RXX[(i << 3) + 5] & 0xFFC0) | (a1 | a2);
                //v1 = (a1 | a2)
            }//loc_728

            if ((arg->mask < 1) || arg->mask & 0x8000)
            {
                a1 = arg->sl;
                if ((arg->sl >= 16))
                {
                    a1 = 15;
                }//loc_750

                //v0 = _spu_RXX
                _spu_RXX[(i << 3) + 4] = (_spu_RXX[(i << 3) + 4] & 0xFFF0) | a1;
            }//loc_774
        }//loc_774
    }

    ///@? Not sure what the below is doing yet.
    int scratchPad[256];

    scratchPad[9] = 1;
    scratchPad[10] = 0;

    while (scratchPad[10] < 2)
    {
        //loc_794
        scratchPad[9] <<= 13;
        scratchPad[10]++;
    }
}

void SpuSetKey(long on_off, unsigned long voice_bit)
{
	UNIMPLEMENTED();
}

void SpuSetKeyOnWithAttr(SpuVoiceAttr* attr)//(F)
{
	SpuSetVoiceAttr(attr);
	SpuSetKey(1, attr->voice);
}

long SpuGetKeyStatus(unsigned long voice_bit)
{
	int a1 = -1;

	//loc_210
	for (int i = 0; i < 24; i++)
	{
		int v0 = 1 << i;

		if ((voice_bit & (1 << i)))
		{
			//loc_240
			if (i != -1)
			{
				//loc_248
				if ((_spu_keystat & (1 << i)) == 0)
				{
					return (0 < (unsigned short)_spu_RXX[i << 3 + 6]) << 1;
				}
				else
				{
					if ((unsigned short)_spu_RXX[i << 3 + 6] == 0)
					{
						return 3;
					}
					else
					{
						return 1;
					}
				}
			}
			else
			{
				return -1;
			}
		}
	}
	if (a1 != -1)
	{
		//loc_248
		if ((_spu_keystat & (1 << a1)) == 0)
		{
			return (0 < (unsigned short)_spu_RXX[a1 << 3]) << 1;
		}
		else
		{
			if ((unsigned short)_spu_RXX[a1 << 3] == 0)
			{
				return 3;
			}
			else
			{
				return 1;
			}
		}
	}
	else
	{
		return -1;
	}

	return 0;
}

void _spu_t(int mode, int flag)
{
	UNIMPLEMENTED();
}

void _spu_Fw(unsigned char* addr, unsigned long size)
{
	//v0 = _spu_transMode
	//s1 = addr
	//s0 = size

	if (_spu_trans_mode == 0)
	{
		//v0 = _spu_tsa
		//a1 = _spu_mem_mode_plus
		//a0 = 2
		_spu_t(2, _spu_tsa << _spu_mem_mode_plus);
		///@TODO check if a1 is modified in spu_t
	}
	//loc_A84
#if 0
jal     _spu_t
sllv    $a1, $v0, $a1

jal     _spu_t
li      $a0, 1

li      $a0, 3
move    $a1, $s1
jal     _spu_t
move    $a2, $s0
j       loc_A94
move    $v0, $s0

loc_A84:
move    $a0, $s1
jal     sub_480
move    $a1, $s0
move    $v0, $s0

loc_A94:
lw      $ra, 0x20+var_8($sp)
lw      $s1, 0x20+var_C($sp)
lw      $s0, 0x20+var_10($sp)
jr      $ra
addiu   $sp, 0x20
 # End of function _spu_Fw
#endif
}

unsigned long SpuWrite(unsigned char* addr, unsigned long size)
{
	if (0x7EFF0 < size)
	{
		size = 0x7EFF0;
	}
	
	//loc_228
	_spu_Fw(addr, size);

	if (_spu_transferCallback == NULL)
	{
		_spu_inTransfer = 0;
	}

	return size;
}

long SpuSetTransferMode(long mode)
{
	long mode_fix = mode == 0 ? 0 : 1;

	//trans_mode = mode;
	//transMode = mode_fix;

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

void _SpuDataCallback(int a0)
{
	UNIMPLEMENTED();
}

void SpuStart()//(F)
{
	long event = 0;

	if (_spu_isCalled == 0)
	{
		_spu_isCalled = 1;
		EnterCriticalSection();
		_SpuDataCallback(_spu_FiDMA);
		//event = OpenEvent(HwSPU, EvSpCOMP, EvMdNOINTR, NULL);
		_spu_EVdma = event;
		EnableEvent(event);
		ExitCriticalSection();
	}
	//loc_348
}

void _spu_init(int a0)
{
	UNIMPLEMENTED();
}

void _spu_FsetRXX(int a0, int a1, int a2)//(F)
{
	if (a2 == 0)
	{
		_spu_RXX[a0] = a1;
	}
	else
	{
		_spu_RXX[a0] = a1 >> _spu_mem_mode_plus;
	}
}

void _SpuInit(int a0)
{
	ResetCallback();
	_spu_init(a0);

	if (a0 == 0)
	{
		for (int i = 0; i < sizeof(_spu_voice_centerNote) / sizeof(short); i++)
		{
			_spu_voice_centerNote[i] = SPU_CENTERNOTE;
		}
	}
	//loc_240
	SpuStart();

	_spu_rev_flag = 0;
	_spu_rev_reserve_wa = 0;
	dword_424.mask = 0;
	dword_424.mvol.left = 0;
	dword_424.mvol.right = 0;
	dword_424.mvolmode.left = 0;
	dword_424.mvolmode.right = 0;
	dword_424.mvolx.left = 0;
	dword_424.mvolx.right = 0;
	_spu_rev_offsetaddr = _spu_rev_startaddr;
	_spu_FsetRXX(209, _spu_rev_startaddr, 0);
	_spu_AllocBlockNum = 0;
	_spu_AllocLastNum = 0;
	_spu_memList = 0;
	_spu_trans_mode = 0;
	_spu_transMode = 0;
	_spu_keystat = 0;
	_spu_RQmask = 0;
	_spu_RQvoice = 0;
	_spu_env = 0;
}

void SpuInit(void)
{
	_SpuInit(0);
}

long SpuSetMute(long on_off)
{
	UNIMPLEMENTED();
	return 0;
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

void SpuSetCommonAttr(SpuCommonAttr* attr)
{
	UNIMPLEMENTED();
}

long SpuInitMalloc(long num, char* top)//(F)
{
	if (num > 0)
	{
		//loc_214
		((int*)top)[0] = 0x40001010;
		_spu_memList = (uintptr_t)top;
		_spu_AllocLastNum = 0;
		_spu_AllocBlockNum = num;
		((int*)top)[1] = (0x10000000 << _spu_mem_mode_plus) - 0x1010;
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
	//MasterVolume.VolumeLeft.Raw = mvol_left;
	//MasterVolume.VolumeRight.Raw = mvol_right;
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
