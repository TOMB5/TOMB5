#ifndef SPUSOUND_H
#define SPUSOUND_H

struct SpuVolume
{
	short left;
	short right;
};

struct SpuVoiceAttr
{
	unsigned long voice;
	unsigned long mask;
	struct SpuVolume volume;
	struct SpuVolume volmode;
	struct SpuVolume volumex;
	unsigned short pitch;
	unsigned short note;
	unsigned short sample_note;
	short envx;
	unsigned long addr;
	unsigned long loop_addr;
	long a_mode;
	long s_mode;
	long r_mode;
	unsigned short ar;
	unsigned short dr;
	unsigned short sr;
	unsigned short rr;
	unsigned short sl;
	unsigned short adsr1;
	unsigned short adsr2;
};

extern void SPU_Init();
extern void S_SetReverbType(int Reverb);

#endif