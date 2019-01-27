#include "TEXT_S.H"

#include "CONTROL.H"
#include "SPECIFIC.H"
#include "GPU.H"
#include "TEXT.H"
#include "TYPES.H"
#include "..\SPEC_PSX\TEXT_S.H"
#include <assert.h>

//char*, unsigned short*, unsigned short*
#if 1

void PrintString(unsigned short x, unsigned short y, unsigned char colourFlag, char* string, unsigned short flag)//8DB4C, 8FB90
{
	char c;
	unsigned short var_2E;
	unsigned short var_2C;
	unsigned short var_30;
	int s2 = 0;
	//s0 = a0
	//s4 = a1
	int s3 = colourFlag;
	//s5 = string
	//s6 = flag
	//at = GnFrameCounter

	if ((flag & 0x2000) && (GnFrameCounter & 0x10))
	{
		//loc_8DD68
		return;
	}
	//loc_8DBA0
	//v0 = (flag >> 12) & 1;
	ScaleFlag = (flag >> 12) & 1;
	GetStringLength(string, 0, &var_30);

	c = *string++;
	if (c != 0)
	{
		//v0 = 0x20
		do
		{
			if (c == 0xA)
			{
				//v0 = *string
				//a1 = &var_2E

				if (c == *string)
				{
					//a0 = string
					//var_30 = 0
					y += 16;
					//j loc_8DD54
				}
				else
				{
					//loc_8DBE8
					GetStringLength(string, &var_2E, &var_2C);
					//jal sub_8DD90
					//v1 = var_30
					//v0 = var_2E
					//a0 = var_2C
					//v1 -= v0
					//v1 += 2;
					//y += v1;
					//var_30 = a0;
					//j       loc_8DD54
				}
			}//v0 = 0x9
			else if (c == 0x20)
			{
				//loc_8DC14
				if (!(flag & 0x1000))
				{
					s2 += 2;
				}
				else
				{
					s2 += 6;
				}
				//j loc_8DD54
			}
			else if (c == 0x9)
			{
				//loc_8DC30
				s2 += 0x28;
				//j loc_8DD54
			}//v0 = c - 1
			else if (c < 0x14)
			{
				s3 = (c - 1) & 0xFF;
				//j       loc_8DD54
			}
			else
			{
				//v0 = c - 0x80
				//v0 <<= 1;
				if ((c - 0x80) < 0x2E)
				{
					//t1 = &aUEAAAAEEEAAEOO[(c- 0x80) << 1];
					//v1 = t1[-1]
					//s1 = &loc_92020[1];

					//v0 = v1 << 3;
					//v0 -= v1;
					//s1 += v0

					///DrawChar(s2, y, s3, s1);

					//v1 = t1[0]
					//at = 0x20
					//v0 = v1 << 3
					///if (t1[0] == 0x20)
					{
						//jmp loc_8DD3C? continue?
					}

					//v0 -= v1
					//a3 = &loc_92020[1];
					//a3 = v0 + a3;

					//a0 = ((s1[2] >> 1) + s2) - 3;
					//a1 = s4 + s1[4]

					///DrawChar(a0, a1, a2, a3);
					//addiu   $ra, 0x60  ***************** check where i land!
				}
				else//CHECKME might not be else case see above addiu ra
				{
					//loc_8DCDC
					//v0 = c << 3
					//v0 -= c
					//at = a0 < 0x20 ? 1 : 0
					//a2 = s3
					if (c < 0x20)
					{
						//v1 = &word_9230E
						c -= 0x18;
						//a0 = a0 < 4 ? 1 : 0
						//s1 = v0 + v1
						if (c > 3)
						{
							///DrawChar(s2, s4, 0, s1);
							//addiu ra 0x1C ***************checkme
						}//loc_8DD0C
						else
						{
							///DrawChar(s2, s4, s3, s1);
							//addiu ra 0x1C ***************checkme
						}
					}
					//loc_8DD20
					//a0 = &loc_92020[1];
					//s1 = v0 + a0;
					///DrawChar(s2, s4, s3, s1);

					//v1 = s1[2]
					if ((flag & 0x1000))
					{
						//v1 -= s1[2] >> 2

					}//loc_8DD50

					//s2 += v1
				}
			}
			//loc_8DD54
			c = *string++;
		}while (c != 0);
	}

	ScaleFlag = 0;
}

int GetStringLength(char* string, unsigned short* a1, unsigned short* a2)//8DEDC(<), 8FF20(<)
{
	int t5 = 0;
	int t0 = 0;
	int t2 = -1024;
	char c = *string++;//a3
	int t1 = 1024;
	int a3 = 0;
	int t3 = 0;
	int v0 = 0;
	struct CHARDEF* a33;

	if (c != 0)
	{
		if (c != 0xA)
		{
			t3 = ScaleFlag;

			//loc_8DF18
		loc_8DF18:
			if (c == 0x20)
			{
				if (ScaleFlag != 0)
				{
					t0 -= 2;
				}
				else
				{
					t0 += 8;
				}
			}
			else if (c == 0x9)
			{
				//loc_8DF30
				t0 += 0x28;

				if (t1 > -0xA)
				{
					t1 = -12;
				}//loc_8DF4C

				if (t2 < 2)
				{
					t2 = 2;
				}
			}
			else if (c > 0x13)
			{
				//loc_8DF5C
				if (c < 0x20)
				{
					a33 = &CharDef[c + 74];
				}
				else
				{
					//loc_8DF7C
					if ((unsigned int)(c - 0x80) < 0x2E)
					{
						a3 = AccentTable[0][c - 0x80];
						t5 = 1;
						assert(0);//Not debugged, colliding register type here!
					}

					//loc_8DF98
					a33 = &CharDef[c - 33];
				}
				//loc_8DFA8
				v0 = a33->w;

				if (t3 != 0)
				{
					v0 = a33->w - (a33->w >> 2);
				}

				//loc_8DFB8
				t0 += v0;

				if (a33->YOffset < t1)
				{
					t1 = a33->YOffset;
				}//loc_8DFD4

				if (t2 < a33->YOffset + a33->h)
				{
					t2 = a33->YOffset + a33->h;
				}
			}
			//loc_8DFE4
			c = *string++;

			//v0 = 0xA
			if (c != 0)
			{
				//v0 = 0x20
				if (c != 0xA)
				{
					goto loc_8DF18;
				}
			}//loc_8DFFC
		}//loc_8DFFC
	}
	//loc_8DFFC
	if (a1 != NULL)
	{
		if (t5 != 0)
		{
			t1 -= 4;
		}//loc_8E010

		*a1 = t1;
	}//loc_8E014

	if (a2 != NULL)
	{
		*a2 = t2;
	}

	return t0;
}

void GetStringDimensions(char* string, unsigned short* w, unsigned short* h)
{
	UNIMPLEMENTED();
}
#endif

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

		db.polyptr += 0x18;//sizeof(POLY_GT4);

	}//locret_8DED4
}

void UpdatePulseColour()
{

}