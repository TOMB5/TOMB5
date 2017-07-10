#include "TEXT.H"

#include "PSXTYPES.H"

char AccentTable[46][2];
unsigned char PulseCnt;
unsigned char ScaleFlag;

struct CVECTOR FontShades[10][16];

static struct CVECTOR ShadeFromTo[10][2] = 
{
	128, 128, 128, 0, 128, 128, 128, 0, 128, 128, 128, 0, 128, 128, 128, 0,
	128, 128, 128, 0, 128, 128, 128, 0, 128,   0,   0, 0,  64,   0,   0, 0,
	  0,   0, 160, 0,   0,   0,  80, 0,
	
	128, 128, 128, 0,  16,  16,  16, 0, 192, 128,  64, 0,   64,  16,  0, 0, 
	16,  16,  16, 0,  128, 128, 128, 0, 224, 192,   0, 0,   64,  32,  0, 0,
	128,  0,   0, 0,  64,    0,  0, 0
};

void InitFont()//115EC, 1169C
{
#if 0
	// line 2, offset 0x115ec
	int i; // $a0
	int j; // $t6
	
	{ // line 48, offset 0x11630
		unsigned char nr; // $a1
		unsigned char ng; // $v1
		unsigned char nb; // $a2
		unsigned char fr; // $s2
		unsigned char fg; // $s1
		unsigned char fb; // $s0
		{ // line 61, offset 0x116a0
			unsigned short r; // $t1
			unsigned short g; // $t0
			unsigned short b; // $a3
		} // line 74, offset 0x116f8
	} // line 121, offset 0x11728
#endif

#if 0
	int test = sizeof(ShadeFromTo);
	char* testt = &ShadeFromTo[0];

	int a0 = 0;

	char* fp = (char*)&ShadeFromTo + 0x2E;
	char* testing = (char*)&ShadeFromTo[5][1];
	char* s7 = (char*)&ShadeFromTo + 0x30;
	char* s6 = (char*)&ShadeFromTo + 0x31;
	char* s5 = (char*)&ShadeFromTo + 0x32;

	int v0 = 10;
	
	char* s4 = (char*)&FontShades + 0x6F68;

	int s3 = a0 + 1;
	v0 = a0 << 6;

	char* t2 = v0 + s4;

	///*

	int t9 = 0;
	int t8 = 0;
	int t7 = 0;
	int t6 = 0xF;
	
	a0 <<= 3;
	char* v00 = a0 + s7;
	char* v1 = a0 + s6;
	int s2 = v00[0];//first char 0x80
	v00 = a0 + fp;
	int s1 = v1[0];

	v1 = a0 + s5;
	char s0 = v1[0];
	v1 = 0xA05E0;//dword
	char a2 = v00[0];//char
	v00 = a0 + v1;
	v1 = 0xA05b4 + 0x2D;
	char* a00 = v1;
	char v11 = a00[0];
	char a1 = v00[0];

	char t5 = a2 << 4;//colour conversion?
	char t4 = v11 << 4;
	char t3 = a1 << 4;

	a2 = -a2;
	a0 = -v11;
	a1 = -a1;

	v00 = t3 >> 4;
	v11 = t7 >> 4;
	v00 += v11;

	char t1 = v0 & 0xFFFF;
	v11 = t4 >> 4;
	v0 = t8 >> 4;
	v11 += v0;

	char t0 = v11 & 0xFFFF;

	v0 = t5 >> 4;
	v11 = t9 >> 4;
	v0 += v11;

	v11 = t1 < 0x100 ? 1 : 0;

	if (v11 == 0)
	{
		//0x11780
	}
	else
	{
		//0x1178C
	}
#endif

} // line 166, offset 0x11764
