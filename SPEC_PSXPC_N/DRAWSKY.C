#include "DRAWSKY.H"

#include "GAMEFLOW.H"
#include "GPU.H"
#include "OBJECTS.H"
#include "SETUP.H"
#include "GTEREG.H"
#include "MISC.H"

void DrawSkyMesh(short* mesh)
{
	int s7;
	char* s5;
	unsigned long* t9;
	int v0;
	int s6;
	int a1;
	int scratchPad[256];
	int* a2;
	int at;
	int v1;
	int t0;
	int t1;
	int t2;
	int t3;
	int t4;
	int t5;
	int* a0;
	int a3;
	int t8;
	int t7;
	int t6;

	s7 = gfLevelFlags & 0x200;
	s5 = db.polyptr;
	t9 = db.ot;
	v0 = ((int*)mesh)[2];
#if defined(USE_32_BIT_ADDR)
	s6 = t9[2563*2];
#else
	s6 = t9[2563];
#endif
	mesh += 6;
	a1 = v0 >> 16;
	v0 &= 0xFF;
	a1 += (int)mesh;
	a2 = &scratchPad[0];
	at = v0 << 3;
	v1 = v0;

	t0 = ((int*)mesh)[0];
	t1 = ((int*)mesh)[1];
	t2 = ((int*)mesh)[2];
	t3 = ((int*)mesh)[3];
	t4 = ((int*)mesh)[4];
	t5 = ((int*)mesh)[5];

	//loc_7DD00
	do
	{
		VX0 = (t0 & 0xFFFF);
		VY0 = (t0 >> 16) & 0xFFFF;
		VZ0 = t1;

		VX1 = (t2 & 0xFFFF);
		VY1 = (t2 >> 16) & 0xFFFF;
		VZ1 = t3;

		VX2 = (t4 & 0xFFFF);
		VY2 = (t4 >> 16) & 0xFFFF;
		VZ2 = t5;

		mesh += 12;
		v0 -= 3;

		docop2(0x280030);

		t0 = ((int*)mesh)[0];
		t1 = ((int*)mesh)[1];
		t2 = ((int*)mesh)[2];
		t3 = ((int*)mesh)[3];
		t4 = ((int*)mesh)[4];
		t5 = ((int*)mesh)[5];

		a2[0] = SXY0;
		a2[1] = SXY1;
		a2[2] = SXY2;
		a2 += 3;
	} while (v0 > 0);

	a0 = &scratchPad[0];
	struct PSXTEXTSTRUCT* a22 = &psxtextinfo[0];
	v0 = ((int*)a1)[0];
	a3 = 0xF80000;
	at = v0 >> 16;
	DQA = at;
	v0 &= 0xFFFF;
	a1 += 4;
	if (v0 != 0)
	{
		t5 = ((int*)s5)[-4164];
	}
	//loc_7DD78
	v0 = DQA;
	t0 = ((int*)a1)[0];

	if (v0 != 0)
	{
loc_7DD84:
		a1 += 4;
		v1 = 1;
		//loc_7DD8C
		do
		{
			t1 = ((int*)a1)[0];
			v0--;
			t4 = (t1 >> 22) & 0x3FC;
			t4 += (int)a0;
			t8 = (t1 >> 14) & 0x3FC;
			t8 += (int)a0;
			t7 = (t1 >> 6) & 0x3FC;
			t7 += (int)a0;
			t6 = (t1 << 2) & 0x3FC;
			t6 += (int)a0;

			SXY0 = ((int*)t6)[0];
			SXY1 = ((int*)t7)[0];
			SXY2 = ((int*)t8)[0];

			docop2(0x1400006);
			t6 = 0x3C808080;

			t4 = ((int*)t4)[0];
			at = MAC0;

			t5 = (t0 & 0xFFF) << 4;
			t0 >>= 16;

			if (at >= 0)
			{
				t1 = SXY0;
				t2 = SXY1;
				t3 = SXY2;

				at = HorClipXY(t1, t2, t3, t4);

				if (at == 0)
				{
					t5 += (int)a22;

#if defined(USE_32_BIT_ADDR)
					((int*)s5)[3] = SXY0;
					((int*)s5)[6] = SXY1;
					((int*)s5)[9] = SXY2;
					((int*)s5)[12] = t4;
#else
					((int*)s5)[2] = SXY0;
					((int*)s5)[5] = SXY1;
					((int*)s5)[8] = SXY2;
					((int*)s5)[11] = t4;
#endif

					t4 = ((int*)t5)[2];
					at = DQB;

					t2 = ((int*)t5)[0];
					t3 = ((int*)t5)[1];
					t5 = ((int*)t5)[3];

					t2 -= at;

					at = ((t4 >> 16) & 0x200) << 16;

					t6 |= at;
					t3 &= 0xFF9FFFFF;

					if (s7 == 0)
					{
						at = 0x400000;
					}
					else
					{
						at = 0x200000;
					}

					//loc_7DE64
					t3 |= at;

					at = t6;
					if (!(v0 < 16))
					{
						if (s7 == 0)
						{
							at = 0;
						}//loc_7DE80
					}//loc_7DE80

#if defined(USE_32_BIT_ADDR)
					((int*)s5)[2] = t6;
					((int*)s5)[5] = t6;
					((int*)s5)[8] = at;
					((int*)s5)[11] = at;
					((int*)s5)[4] = t2;
					((int*)s5)[7] = t3;
					((int*)s5)[10] = t4;
					((int*)s5)[13] = t5;

#else
					((int*)s5)[1] = t6;
					((int*)s5)[4] = t6;
					((int*)s5)[7] = at;
					((int*)s5)[10] = at;
					((int*)s5)[3] = t2;
					((int*)s5)[6] = t3;
					((int*)s5)[9] = t4;
					((int*)s5)[12] = t5;
#endif

					at = 0xC000000;
					t2 = s6 | at;
#if defined(USE_32_BIT_ADDR)
					setlen(s5, at >> 24);
					addPrim(s6, s5);
					s5 += sizeof(POLY_GT4);
#else
					((int*)s5)[0] = t2;
					s6 = (int)s5;
					s5 += 0x34;
#endif
				}//loc_7DEB4
			}//loc_7DEB4

			a1 += 4;
			if (v0 == 0)
			{
				goto loc_7DECC;//break
			}

		} while (v1--);

		t0 = ((int*)a1)[0];
		goto loc_7DD84;//while true
	}
loc_7DECC:
	db.polyptr = s5;
#if defined(USE_32_BIT_ADDR)
	t9[2563*2] = s6;
#else
	t9[2563] = s6;
#endif
}

int HorClipXY(int t1, int t2, int t3, int t4)//7DF00, ? (F)
{
	int s0;
	int s1;
	int s2;
	int s3;
	int s4;

	s0 = RGB1;
	s1 = RGB2;

	if (!(t1 < s0) || !(t2 < s0) || !(t3 < s0) || !(t4 < s0))
	{
		//loc_7DF28
		if (t1 < s1 || t2 < s1 || t3 < s1 || t4 < s1)
		{
			//loc_7DF48
			s2 = t1 << 16;
			s3 = t2 << 16;
			s0 = t3 << 16;
			s4 = R | (G << 8) | (B << 16) | (CODE << 24);
			s1 = t4 << 16;

			if (!(s2 < s4) || !(s3 < s4) || !(s0 < s4) || !(s1 < s4))
			{
				//loc_7DF7C
				s4 = RGB0;

				if (s2 < s4 || s3 < s4 || s0 < s4 || s1 < s4)
				{
					return 0;
				}//locret_7DFB4
			}//locret_7DFB4
		}//locret_7DFB4
	}//locret_7DFB4

	return 1;
}

void DrawFlatSky_ASM(CVECTOR layer, short pos, int flags)
{
	int scratchPad[256];
	int* t0 = &scratchPad[0];
	unsigned long t4;
	int v0;
	struct PSXSPRITESTRUCT* t1;
	int t8;
	int t7;
	int t6;
	int s1;
	int t2;
	int at;
	int s0;
	int t3;
	int t9;

	S_MemSet((char*)&scratchPad[0], 0, 1024);

	t0[20] = pos;
	((short*)t0)[37] = flags;

	t9 = ((int*)&layer)[0];
#if defined(USE_32_BIT_ADDR)
	t4 = db.ot[2563*2];
#else
	t4 = db.ot[2563];
#endif
	v0 = objects[SKY_GRAPHICS].mesh_index;//Offset by 2
	t1 = &psxspriteinfo[objects[SKY_GRAPHICS].mesh_index];
	t8 = 0;

	//loc_7E010
	do
	{
		t7 = ((int*)&t1->clut)[0];

		((char*)&scratchPad[0])[28] = t1->u1;
		((char*)&scratchPad[0])[4] = t1->u1;
		((char*)&scratchPad[0])[36] = t1->u1 + 32;
		((char*)&scratchPad[0])[12] = t1->u1 + 32;
		((char*)&scratchPad[0])[13] = t1->v1;
		((char*)&scratchPad[0])[5] = t1->v1;
		((char*)&scratchPad[0])[37] = t1->v1 + 32;
		((char*)&scratchPad[0])[29] = t1->v1 + 32;

		t6 = t7 << 16;
		t7 >>= 16;
		t7 <<= 16;
		s1 = 0;

		//loc_7E054
		do
		{
			t2 = t0[20];
			t2 -= 8200;
			t2 += s1;

			if ((t8 & 1))
			{
				t2 += 1640;
			}

			//loc_7E06C
			s0 = 0;

			//loc_7E070
			do
			{
				t3 = s0 - 4920;
				if ((t8 & 2))
				{
					t3 += 1640;
				}

				//loc_7E080
				VZ0 = t3;
				at = t3 + 820;
				VZ1 = at;
				at += 820;
				VZ2 = at;

				((short*)t0)[36] = t2;

				VX0 = t0[18] & 0xFFFF;
				VY0 = t0[18] >> 16;

				VX1 = t0[18] & 0xFFFF;
				VY1 = t0[18] >> 16;

				VX2 = t0[18] & 0xFFFF;
				VY2 = t0[18] >> 16;

				at = t2 + 820;
				((short*)t0)[36] = at;
				docop2(0x280030);

				t0[0] = SXY0;
				t0[6] = SXY1;
				t0[12] = SXY2;

				VX0 = t0[18] & 0xFFFF;
				VY0 = t0[18] >> 16;

				VX1 = t0[18] & 0xFFFF;
				VY1 = t0[18] >> 16;

				VX2 = t0[18] & 0xFFFF;
				VY2 = t0[18] >> 16;

				at += 820;
				((short*)t0)[36] = at;
				docop2(0x280030);

				t0[2] = SXY0;
				t0[8] = SXY1;
				t0[14] = SXY2;

				VX0 = t0[18] & 0xFFFF;
				VY0 = t0[18] >> 16;

				VX1 = t0[18] & 0xFFFF;
				VY1 = t0[18] >> 16;

				VX2 = t0[18] & 0xFFFF;
				VY2 = t0[18] >> 16;

				s0 += 3280;

				docop2(0x280030);

				t0[4] = SXY0;
				t0[10] = SXY1;
				t0[16] = SXY2;

				DrawSubdivChunk(&t0[0], t6, t7, &t4, (int*)&layer);
				DrawSubdivChunk(&t0[2], t6, t7, &t4, (int*)&layer);
				DrawSubdivChunk(&t0[6], t6, t7, &t4, (int*)&layer);
				DrawSubdivChunk(&t0[8], t6, t7, &t4, (int*)&layer);

			} while (s0 != 9840);

			at = s1 != 9840 ? 1 : 0;
			s1 += 3280;
		} while (at != 0);

		t8 += 1;
		t1++;
	} while (t8 < 4);

#if defined(USE_32_BIT_ADDR)
	db.ot[2563*2] = t4;
#else
	db.ot[2563] = t4;
#endif
}

void DrawSubdivChunk(int* a3, int t6, int t7, unsigned long* t4, int* t9)
{
	int at;
	int a1;
	int a2;
	int v1;
	int a0;

	SXY0 = a3[0];
	SXY1 = a3[2];
	SXY2 = a3[6];

	docop2(0x1400006);

	if (SkyClipXY(a3[0], a3[2], a3[6], a3[8]) == 0)
	{
		at = MAC0;
		SXY2 = a3[8];

		if (at >= 0)
		{
			docop2(0x1400006);
			at = MAC0;
			a2 = ((unsigned short*)a3)[2];

#if defined(USE_32_BIT_ADDR)
			((int*)db.polyptr)[3] = a3[0];

#else
			((int*)db.polyptr)[2] = a3[0];
#endif
			if (at >= 0)
			{
#if defined(USE_32_BIT_ADDR)
				((int*)db.polyptr)[5] = a3[2];
				((int*)db.polyptr)[7] = a3[6];
				((int*)db.polyptr)[9] = a3[8];
				
#else
				((int*)db.polyptr)[4] = a3[2];
				((int*)db.polyptr)[6] = a3[6];
				((int*)db.polyptr)[8] = a3[8];
#endif
				at = a2 + 0x1F;
				v1 = a2 + 0x1F00;
				a0 = v1 + 0x1F;

				a2 |= t6;
				at |= t7;

#if defined(USE_32_BIT_ADDR)
				((int*)db.polyptr)[4] = a2;
				((int*)db.polyptr)[6] = at;
				((short*)db.polyptr)[16] = v1;
				((short*)db.polyptr)[20] = a0;
#else
				((int*)db.polyptr)[3] = a2;
				((int*)db.polyptr)[5] = at;
				((short*)db.polyptr)[14] = v1;
				((short*)db.polyptr)[18] = a0;
#endif
#if defined(USE_32_BIT_ADDR)
				((unsigned int*)db.polyptr)[2] = *t9;
				setlen(db.polyptr, 9);
				addPrim(*t4, db.polyptr);
				db.polyptr += sizeof(POLY_GT3);
#else
				* t4 |= 0x9000000;
				((unsigned int*)db.polyptr)[0] = *t4;
				((unsigned int*)db.polyptr)[1] = *t9;
				*t4 = (unsigned int)db.polyptr;
				db.polyptr += 0x28;
#endif
			}
		}//locret_7E21C
	}//locret_7E21C
}

int SkyClipXY(int v0, int v1, int a0, int a1)
{
	int s2 = RGB1;
	int s3 = RGB2;
	int s4;
	int s5;
	int s6;

	if (!(v0 < s2) || !(v1 < s2) || !(a0 < s2) || !(a1 < s2))
	{
		if (v0 < s3 || v1 < s3 || a0 < s3 || a1 < s3)
		{
			//loc_7E26C
			s4 = v0 << 16;
			s5 = v1 << 16;
			s2 = a0 << 16;
			s6 = R | (G << 8) | (B << 16) | (CODE << 24);
			s3 = a1 << 16;

			if (!(s4 < s6) || !(s5 < s6) || !(s2 < s6) || !(s3 < s6))
			{
				//loc_7E2A0
				s6 = RGB0;
				if (s4 < s6 || s5 < s6 || s2 < s6 || s3 < s6)
				{
					return 0;
				}//locret_7E2D8
			}//locret_7E2D8
		}//locret_7E2D8
	}//locret_7E2D8
	return 1;
}