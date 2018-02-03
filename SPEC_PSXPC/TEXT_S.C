#include "TEXT_S.H"

#include "GPU.H"
#include "TEXT.H"
#include "TYPES.H"

//char*, unsigned short*, unsigned short*
#if 1
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