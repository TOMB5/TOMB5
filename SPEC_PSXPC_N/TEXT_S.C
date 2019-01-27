#include "TEXT_S.H"

#include "CONTROL.H"
#include "SPECIFIC.H"
#include "GPU.H"
#include "TEXT.H"
#include "TYPES.H"
#include "..\SPEC_PSX\TEXT_S.H"

//char*, unsigned short*, unsigned short*
#if 1

void PrintString(unsigned short x, unsigned short y, unsigned char colourFlag, char* string, unsigned short flag)
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

			}//loc_8DCDC
		}
	}

	ScaleFlag = 0;



#if 0

	loc_8DC50 :
			  sltiu   $v1, $v0, 0x2E
				  beqz    $v1, loc_8DCDC
				  sll     $v0, 1
				  la      $t1, aUEAAAAEEEAAEOO  # " u^e\\a]a^a[a\\{ e]e^e[|^|]|[A^A]E\\   "...
				  addu    $t1, $v0
				  lbu     $v1, -1($t1)
				  la      $s1, (loc_92020 + 1)
				  sll     $v0, $v1, 3
				  subu    $v0, $v1
				  addu    $s1, $v0
				  move    $a0, $s2
				  move    $a1, $s4
				  move    $a2, $s3
				  jal     sub_8DDBC
				  move    $a3, $s1
				  lbu     $v1, 0($t1)
				  li      $at, 0x20
				  beq     $v1, $at, loc_8DD3C
				  sll     $v0, $v1, 3
				  subu    $v0, $v1
				  la      $a3, (loc_92020 + 1)
				  addu    $a3, $v0, $a3
				  lb      $a0, 2($s1)
				  lb      $a1, 4($s1)
				  sra     $a0, 1
				  addu    $a0, $s2
				  addiu   $a0, -3
				  addu    $a1, $s4, $a1
				  move    $a2, $s3
				  jal     sub_8DDBC
				  addiu   $ra, 0x60

				  loc_8DCDC:
			  sll     $v0, $a0, 3
				  subu    $v0, $a0
				  sltiu   $at, $a0, 0x20
				  beqz    $at, loc_8DD20
				  move    $a2, $s3
				  la      $v1, word_9230E
				  addiu   $a0, -0x18
				  sltiu   $a0, 4
				  bnez    $a0, loc_8DD0C
				  addu    $s1, $v0, $v1
				  move    $a2, $zero

				  loc_8DD0C :
			  move    $a0, $s2
				  move    $a1, $s4
				  move    $a3, $s1
				  jal     sub_8DDBC
				  addiu   $ra, 0x1C

				  loc_8DD20 :
				  la      $a0, (loc_92020 + 1)
				  addu    $s1, $v0, $a0
				  move    $a0, $s2
				  move    $a1, $s4
				  jal     sub_8DDBC
				  move    $a3, $s1

				  loc_8DD3C :
			  lbu     $v1, 2($s1)
				  andi    $v0, $s6, 0x1000
				  beqz    $v0, loc_8DD50
				  srl     $v0, $v1, 2
				  subu    $v1, $v0

				  loc_8DD50 :
			  addu    $s2, $v1

				  loc_8DD54 :
			  lbu     $a0, 0($s5)
				  addiu   $s5, 1
				  bnez    $a0, loc_8DBC4
				  li      $v0, 0xA
				  sb      $zero, 0x1A8C($gp)

				  loc_8DD68 :
				  lw      $ra, 0x40 + var_4($sp)
				  lw      $s6, 0x40 + var_8($sp)
				  lw      $s5, 0x40 + var_C($sp)
				  lw      $s4, 0x40 + var_10($sp)
				  lw      $s3, 0x40 + var_14($sp)
				  lw      $s2, 0x40 + var_18($sp)
				  lw      $s1, 0x40 + var_1C($sp)
				  lw      $s0, 0x40 + var_20($sp)
				  jr      $ra
				  addiu   $sp, 0x40

#endif
}

int GetStringLength(char* string, unsigned short* a1, unsigned short* a2)//8DEDC(<), 8FF20(<)
{
	int t5 = 0;
	int t0 = 0;
	char c = *string++;//a3
	int t2 = -1024;
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
			else if (c < 0x14)
			{
				//loc_8DF5C
				if (c < 0x20)
				{
					a33 = &CharDef[c + 74];
				}
				else
				{
					//loc_8DF7C
					if ((c - 0x80) < 0x2E)
					{
						a3 = AccentTable[0][c - 0x80];
						t5 = 1;
					}

					//loc_8DF98
					a33 = &CharDef[a3 - 33];
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