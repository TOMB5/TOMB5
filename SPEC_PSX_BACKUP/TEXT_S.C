#include "TEXT_S.H"

#include "GPU.H"
#include "SPECIFIC.H"
#include "TEXT.H"
#include "TYPES.H"

char aUEAAAAEEEAAEOO[] = { 0x75,0x5E,0x65,0x5C,0x61,0x5D,0x61,0x5E,0x61,0x5B,0x61,0x5C,0x7B,0x20,0x65,0x5D,0x65,0x5E,0x65,0x5B,0x7C,0x5E,0x7C,0x5D,0x7C,0x5B,0x41,0x5E,0x41,0x5D,0x45,0x5C,0x20,0x20,0x20,0x20,0x6F,0x5D,0x6F,0x5E,0x6F,0x5B,0x75,0x5D,0x75,0x5B,0x79,0x5E,0x4F,0x5E,0x55,0x5E,0x20,0x20,0x4F,0x5C,0x20,0x20,0x20,0x20,0x20,0x20,0x61,0x5C,0x7C,0x5C,0x6F,0x5C,0x75,0x5C,0x6E,0x5F,0x4E,0x5F,0x20,0x20,0x20,0x20,0x7D,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x7E,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
long word_9230E;
char loc_92020[] = { 0x10,0x04,0x00,0x21,0x10,0x43,0x00,0x00,0x00,0x52,0x84,0x74,0x33,0x83,0x8F,0xC0,0x10,0x12,0x00,0x21,0x10,0x43,0x00,0x06,0x00,0x42,0x94,0x0B,0x00,0x10,0x3C,0x90 };

//char*, unsigned short*, unsigned short*
#ifndef USE_ASM
long GetStringLength(char* string, unsigned short* a1, unsigned short* a2)//8DEDC(<), 8FF20(<)
{
	char c;
	long t0, t1, t2, t3, t5, v0;
	t5 = 0;
	t0 = 0;
	t2 = 0xFFFFFC00;

	c = *string++;//c = a3
	t1 = 0x400;

	if (c != 0 || c != 10)
	{
		t3 = ScaleFlag;
		//t6 = &AccentTable[0][0];
		//t4 = &CharDef[0];

		//loc_8DF18
		while (string[0] != 10 || string[0] != 0)
		{
			if (c == 32)
			{
				t0 += 8;
				if (t3 != 0)
				{
					t0 -= 2;
				}
			}
			else if (c == 9)
			{
				//loc_8DF30
				t0 += 40;

				if (!(t1 < -11))
				{
					t1 = -12;
				}

				if (t2 < 2)
				{
					t2 = 2;
				}
			}
			else if (c > 19)
			{
				//loc_8DF5C
				if (c < 0x20)
				{
					//v0 = (c << 3) - c;
					//v0 += 0x206;
					//a3 = v0 + t4
					sizeof(struct CHARDEF);
				}
				else
				{
					//loc_8DF7C
					//v1 = c - 0x80;
					//v0 = v1 < 0x2E ? 1 : 0;
					//v0 = v1 << 1;
					if (c - 0x80 < 0x2E)
					{
						//v0 += t6;
						//a3 = v0[0];
						t5 = 1;
					}//loc_8DF98

					 //v0 = a3 << 3;
					 //v0 -= a3;
					 //v0 -= 0xE7;
					 //a3 = v0 + t4;
				}

				//loc_8DFA8

			}
		}
	}

	//loc_8DFFC
	if (a1 != 0 && t5 == 0)
	{
		//loc_8E010
		*a1 = t1;
	}
	else if (a1 != 0 && t1 != 0)
	{
		t1 -= 4;
	}

	//loc_8E014
	if (a2 != 0)
	{
		*a2 = t2;
	}

	*a1 = t1;

	return t0;
}


void GetStringDimensions(char* string, unsigned short* w, unsigned short* h)//8E028(<), 9006C(<) (F)
{
	unsigned short sw;//18
	unsigned short sh;//16
	long t9;//t9
	long t7;//t7
	char c;//a0
	long v0;

	t9 = GetStringLength(string, &sw, &sh);
	c = *string++;

	while (c != 0)
	{
		t7 = (sh - sw) + 2;

		//loc_8E070
		if (c == 0xA)
		{
			if (*string != 0xA)
			{
				//loc_8E094
				if (*string != 0x0)
				{
					v0 = GetStringLength(string, &sw, &sh);
					t7 = (t7 + 2) + (sh - sw);

					if (t9 < v0 != 0)
					{
						t9 = v0;
					}
				}
			}
			else
			{
				t7 += 16;
			}
		}

		//loc_8E0CC
		c = *string++;
	}
	
	//loc_8E0DC
	*h = t7;
	*w = t9;
}

void DrawChar(unsigned short a0, unsigned short a1, unsigned short a2, struct CHARDEF* a3)//8DDBC(<), 8FE00(<) (F)
{
	struct CVECTOR* TopShade;//$v0
	struct CVECTOR* BottomShade;//$at
	long v1;

	a2 &= 0xFFFF;

	if ((unsigned long) &db.polyptr[0] < (unsigned long) &db.polybuf_limit[0])
	{
		TopShade = &FontShades[a2][a3->TopShade];
		BottomShade = &FontShades[a2][a3->BottomShade];

		*(long*) &db.polyptr[4] = *(long*) &TopShade->r;
		*(long*) &db.polyptr[28] = *(long*) &BottomShade->r;
		*(long*) &db.polyptr[16] = *(long*) &TopShade->r;
		*(long*) &db.polyptr[40] = *(long*) &BottomShade->r;

		((char*) db.polyptr)[7] = 0x3C;//#define TAG_PGT4                    0x3C

		*(short*) &db.polyptr[14] = 4197;
		*(short*) &db.polyptr[26] = 41;
		//sizeof(POLY_GT4);

		v1 = a3->w;
		a1 += a3->YOffset;

		if (ScaleFlag != 0)
		{
			v1 = (a3->w >> 2) - a3->w + 1;
		}

		//loc_8DE5C
		*(short*) &db.polyptr[8] = a0;
		*(short*) &db.polyptr[10] = a1;
		*(short*) &db.polyptr[20] = a0 + v1;
		*(short*) &db.polyptr[22] = a1;

		*(short*) &db.polyptr[32] = a0;
		*(short*) &db.polyptr[34] = a1 + a3->h;
		*(short*) &db.polyptr[44] = a0 + v1;
		*(short*) &db.polyptr[46] = a1 + a3->h;

		*(char*) &db.polyptr[12] = a3->w;
		*(char*) &db.polyptr[13] = a3->v;
		*(char*) &db.polyptr[24] = a3->u + a3->v;
		*(char*) &db.polyptr[25] = a3->v;

		*(char*) &db.polyptr[36] = a3->u;
		*(char*) &db.polyptr[37] = a3->v + a3->h;
		*(char*) &db.polyptr[48] = a3->u + a3->w;
		*(char*) &db.polyptr[49] = a3->v + a3->h;

		*(long*) &db.polyptr[0] = db.ot[0] | 0x0C000000;
		db.ot[0] = (unsigned long) db.polyptr;

		db.polyptr += sizeof(POLY_GT4);

	}//locret_8DED4
}

#endif