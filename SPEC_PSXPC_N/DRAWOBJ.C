#include "DRAWOBJ.H"

#include "3D_OBJ.H"
#include "DRAWSPKS.H"
#include "SPECIFIC.H"
#include "LIBGPU.H"
#include "GPU.H"
#include "GTEREG.H"
#include "MISC.H"

char* do_the_flat_colursub_poly_quad(char* s0, int s2, int t6, int t7, int t8, int t9, int s4, int s5, int s6, int s7, int t1)
{
	int at;
	int s3;

	((int*)s0)[1] = 0xE1000240;

	at = s2 & 0xFF;

	if (at != 128)
	{
		s3 = t6 & 0xFF;

		at = (t6 >> 8) & 0xFF;
		s3 += at;

		at = (t6 >> 16) & 0xFF;
		s3 += at;

		at = (t7 & 0xFF);
		s3 += at;

		at = (t7 >> 8) & 0xFF;
		s3 += at;

		at = (t7 >> 16) & 0xFF;
		s3 += at;

		at = (t8 & 0xFF);
		s3 += at;

		at = (t8 >> 8) & 0xFF;
		s3 += at;

		at = (t8 >> 16) & 0xFF;
		s3 += at;

		at = (t9 & 0xFF);
		s3 += at;

		at = (t9 >> 8) & 0xFF;
		s3 += at;

		at = (t9 >> 16) & 0xFF;
		s3 += at;

		s3 /= 12;
		s3 += 128;

		if (s3 >= 0x100)
		{
			s3 = 0xFF;
		}

		at = s2 & 0xFF;

		s3 *= at;
		s3 >>= 8;

		if (s3 >= 0x100)
		{
			s3 = 0xFF;
		}

	}//loc_8049C
	else
	{
		s3 = 0xFF;
	}

	((char*)s0)[12] = s3;
	((char*)s0)[13] = s3;
	((char*)s0)[14] = s3;
	((char*)s0)[15] = 0x2A;
	((int*)s0)[3] = 0;
	((int*)s0)[4] = s4;
	((int*)s0)[5] = s5;
	((int*)s0)[6] = s6;
	((int*)s0)[7] = s7;
	at = ((int*)t1)[0];
	((int*)t1)[0] = (int)s0;
	s3 = 0x7000000;
	at |= s3;
	((int*)s0)[0] = (int)at;
	s0 += 0x20;
	return s0;
}

void InitGT4_V2(char* s0, int* s4, int* s3, int t6, int at, int t7, int t8, int t9, int t2, int s5, int t3, int s6, int t4, int s7, int t5)
{
	((int*)s0)[2] = *s4;
	((char*)s0)[7] = 0x3E;

	*s3 = ((t6 & 0xFF) * at) >> 7;
	if (*s3 >= 0x100)
	{
		*s3 = 0xFF;
	}

	//loc_801EC
	((char*)s0)[4] = *s3;
	*s3 = (((t6 >> 8) & 0xFF) * at) >> 7;
	if (*s3 >= 0x100)
	{
		*s3 = 0xFF;
	}

	((char*)s0)[5] = *s3;
	*s3 = (((t6 >> 16) & 0xFF) * at) >> 7;
	if (*s3 >= 0x100)
	{
		*s3 = 0xFF;
	}

	((char*)s0)[6] = *s3;
	*s3 = ((t7 & 0xFF) * at) >> 7;
	if (*s3 >= 0x100)
	{
		*s3 = 0xFF;
	}

	((char*)s0)[16] = *s3;
	*s3 = (((t7 >> 8) & 0xFF) * at) >> 7;
	if (*s3 >= 0x100)
	{
		*s3 = 0xFF;
	}

	((char*)s0)[17] = *s3;
	*s3 = (((t7 >> 16) & 0xFF) * at) >> 7;
	if (*s3 >= 0x100)
	{
		*s3 = 0xFF;
	}

	((char*)s0)[18] = *s3;
	*s3 = ((t8 & 0xFF) * at) >> 7;
	if (*s3 >= 0x100)
	{
		*s3 = 0xFF;
	}

	((char*)s0)[28] = *s3;
	*s3 = (((t8 >> 8) & 0xFF) * at) >> 7;
	if (*s3 >= 0x100)
	{
		*s3 = 0xFF;
	}

	((char*)s0)[29] = *s3;
	*s3 = (((t8 >> 16) & 0xFF) * at) >> 7;
	if (*s3 >= 0x100)
	{
		*s3 = 0xFF;
	}

	((char*)s0)[30] = *s3;
	*s3 = ((t9 & 0xFF) * at) >> 7;
	if (*s3 >= 0x100)
	{
		*s3 = 0xFF;
	}

	((char*)s0)[40] = *s3;
	*s3 = (((t9 >> 8) & 0xFF) * at) >> 7;
	if (*s3 >= 0x100)
	{
		*s3 = 0xFF;
	}

	((char*)s0)[41] = *s3;
	*s3 = (((t9 >> 16) & 0xFF) * at) >> 7;
	if (*s3 >= 0x100)
	{
		*s3 = 0xFF;
	}

	((char*)s0)[42] = *s3;
	((int*)s0)[3] = t2;
	((int*)s0)[5] = s5;
	((int*)s0)[6] = t3;
	((int*)s0)[8] = s6;
	((int*)s0)[9] = t4;
	((int*)s0)[11] = s7;
	((int*)s0)[12] = t5;
	*s4 = ((int*)s0)[3];
}

char* do_the_flat_colursub_poly_tri(char* s0, int s2, int t6, int t7, int t8, int s4, int s5, int s6, int t1)
{
	int at;
	int s3;

	((int*)s0)[1] = 0xE1000240;

	//loc_800CC
	at = s2 & 0xFF;

	if (at != 128)
	{
		s3 = t6 & 0xFF;
		at = (t6 >> 8) & 0xFF;
		s3 += at;
		at = (t6 >> 16) & 0xFF;
		s3 += at;
		at = t7 & 0xFF;
		s3 += at;

		//loc_80100
		at = (t7 >> 8) & 0xFF;
		s3 += at;
		at = (t7 >> 16) & 0xFF;
		s3 += at;
		at = (t8 & 0xFF);
		s3 += at;
		at = (t8 >> 8) & 0xFF;
		s3 += at;
		at = (t8 >> 16) & 0xFF;
		s3 += at;
		s3 /= 9;
		s3 += 128;

		if (s3 >= 0x100)
		{
			s3 = 0xFF;
		}

		at = s2 & 0xFF;
		s3 *= at;
		s3 >>= 8;

		if (s3 >= 0x100)
		{
			s3 = 0xFF;
		}
	}//loc_80178
	else
	{
		s3 = 0xFF;
	}

	((char*)s0)[12] = s3;
	((char*)s0)[13] = s3;
	((char*)s0)[14] = s3;
	((char*)s0)[15] = 34;
	((int*)s0)[2] = 0;
	((int*)s0)[4] = s4;
	((int*)s0)[5] = s5;
	((int*)s0)[6] = s6;
	at = ((int*)t1)[0];
	((int*)t1)[0] = (int)s0;
	at |= 0x6000000;
	((int*)s0)[0] = (int)at;
	s0 += 0x1C;

	return s0;
}

void InitGT3_V2(int* s0, int s4, int* s3, int t6, int at, int t7, int t8, int s5, int t3, int t2, int s6, int t4)
{
	((int*)s0)[3] = s4;
	((char*)s0)[7] = 0x36;
	*s3 = ((t6 & 0xFF) * at) >> 7;
	if (*s3 >= 0x100)
	{
		*s3 = 0xFF;
	}

	//loc_7FF64
	((int*)s0)[4] = *s3;
	*s3 = (((t6 >> 8) & 0xFF) * at) >> 7;
	if (*s3 >= 0x100)
	{
		*s3 = 0xFF;
	}

	//loc_7FF8C
	((char*)s0)[5] = *s3;
	*s3 = (((t6 >> 16) & 0xFF) * at) >> 7;
	if (*s3 >= 0x100)
	{
		*s3 = 0xFF;
	}

	//loc_7FFB4
	((char*)s0)[6] = *s3;
	*s3 = ((t7 & 0xFF) * at) >> 7;
	if (*s3 >= 0x100)
	{
		*s3 = 0xFF;
	}

	//loc_7FFD8
	((char*)s0)[16] = *s3;
	*s3 = (((t7 >> 8) & 0xFF) * at) >> 7;
	if (*s3 >= 0x100)
	{
		*s3 = 0xFF;
	}

	//loc_80000
	((char*)s3)[17] = *s3;
	*s3 = (((t7 >> 16) & 0xFF) * at) >> 7;
	if (*s3 >= 0x100)
	{
		*s3 = 0xFF;
	}

	((char*)s3)[18] = *s3;
	*s3 = ((t8 & 0xFF) * at) >> 7;
	if (*s3 >= 0x100)
	{
		*s3 = 0xFF;
	}

	//loc_8004C
	((char*)s3)[28] = *s3;
	*s3 = (((t8 >> 8) & 0xFF) * at) >> 7;
	if (*s3 >= 0x100)
	{
		*s3 = 0xFF;
	}

	//loc_80074
	((char*)s3)[29] = *s3;
	*s3 = (((t8 >> 16) & 0xFF) * at) >> 7;
	if (*s3 >= 0x100)
	{
		*s3 = 0xFF;
	}

	//loc_8009C
	((char*)s0)[30] = *s3;
	((int*)s0)[3] = t2;
	((int*)s0)[5] = s5;
	((int*)s0)[6] = t3;
	((int*)s0)[8] = s6;
	((int*)s0)[9] = t4;
	((int*)s0)[2] = s4;
}

void InitGT4(char* polyptr, int t6, int s4, int t2, int t7, int s5, int t3, int t8, int s6, int t4, int t9, int s7, int t5)//(F)
{
	((int*)polyptr)[1] = t6;
	((int*)polyptr)[2] = s4;
	((int*)polyptr)[3] = t2;
	((int*)polyptr)[4] = t7;
	((int*)polyptr)[5] = s5;
	((int*)polyptr)[6] = t3;
	((int*)polyptr)[7] = t8;
	((int*)polyptr)[8] = s6;
	((int*)polyptr)[9] = t4;
	((int*)polyptr)[10] = t9;
	((int*)polyptr)[11] = s7;
	((int*)polyptr)[12] = t5;
}

void InitGT3(char* polyptr, int t6, int s4, int t2, int t7, int s5, int t3, int t8, int s6, int t4)//(F)
{
	((int*)polyptr)[1] = t6;
	((int*)polyptr)[2] = s4;
	((int*)polyptr)[3] = t2;
	((int*)polyptr)[4] = t7;
	((int*)polyptr)[5] = s5;
	((int*)polyptr)[6] = t3;
	((int*)polyptr)[7] = t8;
	((int*)polyptr)[8] = s6;
	((int*)polyptr)[9] = t4;
}


void UnpackRGB(int* t2, int* t6, int* fp, int* t3, int* at, int* t7, int* t8)
{
	*t2 = *t6 >> 7;
	*t2 &= *fp;
	*t3 = *t6 >> 10;
	*t3 &= 0xF800;
	*t6 >>= 13;
	*t6 &= 0xF8;
	*t6 |= *t3;
	*t6 |= *t2;
	*at >>= 24;///@checkme
	*at <<= 24;
	*t6 |= *at;
	*t2 = *t7 >> 7;
	*t2 &= *fp;
	*t3 = *t7 >> 10;
	*t3 &= 0xF800;
	*t7 >>= 13;
	*t7 &= 0xF8;
	*t7 |= *t3;
	*t7 |= *t2;
	*t2 = *t8 >> 7;
	*t2 &= *fp;
	*t3 = *t8 >> 10;
	*t3 &= 0xF800;
	*t8 >>= 13;
	*t8 &= 0xF8;
	*t8 |= *t3;
	*t8 |= *t2;
}

void MakeMono(unsigned short* s, unsigned char* d)//7F9E4, 81A28
{
	ZSF3 = 1057;
	int t0 = ((int*)s)[0];
	int v0 = 0x3FFF;
	int v1 = 0xD371F947;
	int t4 = 0x41C64E6D;

	//loc_7FA04
	do
	{
		v1 = (v1 * t4) + 0x3039;
		int t3 = (t0 >> 26) & 0x1F;
		int t2 = (t0 >> 21) & 0x1F;
		int t1 = (t0 >> 16) & 0x1F;

		SZ1 = t3;
		SZ2 = t2;
		SZ3 = t1;

		s += 2;

		docop2(0x158002D);

		t2 = (t0 >> 10) & 0x1F;
		t1 = (t0 >> 5) & 0x1F;
		t0 &= 0x1F;

		SZ1 = t2;
		SZ2 = t1;
		SZ3 = t0;

		t1 = OTZ;

		docop2(0x158002D);

		t0 = ((int*)s)[0];
		int at = OTZ;

		t3 = (v1 >> 16) & 1;
		int t5 = (v1 >> 24) & 1;

		if (!(t1 < 15))
		{
			t1 = 15;
		}
		//loc_7FA8C
		t1 -= t3;
		if (!(at < 15))
		{
			at = 15;
		}

		//loc_7FA98
		at -= t5;
		if (t1 < 0)
		{
			t1 = 0;
		}

		//loc_7FAA4
		t1 <<= 4;
		if (at < 0)
		{
			at = 0;
		}

		//loc_7FAB0
		t1 |= at;
		*d++ = t1;
	} while (v0-- != 0);

	ZSF3 = 0xAA;
}

void InitObjGTE()
{
	ZSF3 = (int)(short)0xAA;
	ZSF4 = (int)(short)0x80;
	RFC = 0;
	GFC = 0;
	BFC = 0;
}

void DrawClippedMesh(int vertcache, short* mesh, MMTEXTURE* text, char* ot, char* prim, char* prim_lim, long fp, long prim_len, long num_tri)
{
	UNIMPLEMENTED();
}

void DrawSubDivMesh()
{
	UNIMPLEMENTED();
}

void initialise_light_matrix()
{
	int t0;
	int t1;
	int t2;
	int t3;
	int t4;
	int t5;
	int t6;
	int t7;
	int at;

	t0 = (R11 & 0xFFFF) | ((R12 & 0xFFFF) << 16);
	t1 = (R13 & 0xFFFF) | ((R21 & 0xFFFF) << 16);
	t2 = (R22 & 0xFFFF) | ((R23 & 0xFFFF) << 16);
	t3 = (R31 & 0xFFFF) | ((R32 & 0xFFFF) << 16);
	t4 = (R33);

	t5 = 0xFFFF0000;
	t6 = t0 & t5;
	t7 = t2 & t5;
	t0 &= 0xFFFF;
	at = t1 & t5;
	t0 |= at;
	t2 &= 0xFFFF;
	at = t3 & t5;
	t2 |= at;
	t1 &= 0xFFFF;
	t1 |= t7;
	t3 &= 0xFFFF;
	t3 |= t6;

	L11 = t0 & 0xFFFF;
	L12 = (t0 >> 16) & 0xFFFF;

	L13 = t3 & 0xFFFF;
	L21 = (t3 >> 16) & 0xFFFF;

	L22 = t2 & 0xFFFF;
	L23 = (t2 >> 16) & 0xFFFF;

	L31 = t1 & 0xFFFF;
	L32 = (t1 >> 16) & 0xFFFF;
	L33 = t4;

	VX0 = LightPos.m00;
	VY0 = LightPos.m01;
	VZ0 = LightPos.m02;

	docop2(0x4A6012);

	VX1 = LightPos.m10;
	VY1 = LightPos.m11;
	VZ1 = LightPos.m12;

	t0 = IR1;
	t2 = IR2;
	t1 = IR3;

	docop2(0x4AE012);

	VX2 = LightPos.m20;
	VY2 = LightPos.m21;
	VZ2 = LightPos.m22;

	t0 &= 0xFFFF;
	t2 <<= 16;
	t0 |= t2;
	t1 &= 0xFFFF;

	t3 = IR1;
	t2 = IR2;
	t4 = IR3;

	docop2(0x4B6012);

	t3 <<= 16;
	t1 |= t3;
	t2 &= 0xFFFF;
	t4 <<= 16;
	t2 |= t4;

	t3 = IR1;
	t5 = IR2;
	t6 = IR3;

	t3 &= 0xFFFF;
	t5 <<= 16;
	t3 |= t5;

	L11 = t0 & 0xFFFF;
	L12 = (t0 >> 16) & 0xFFFF;
	L13 = t1 & 0xFFFF;
	L21 = (t1 >> 16) & 0xFFFF;
	L22 = t2 & 0xFFFF;
	L23 = (t2 >> 16) & 0xFFFF;
	L31 = t3 & 0xFFFF;
	L32 = (t3 >> 16) & 0xFFFF;
	L33 = t4;
}

void phd_PutPolygons_normal(short* mesh, short clip)
{
	int v0;
	int s5;
	int s6;
	int a1;
	int v1;
	int a22;
	int* a2;
	int sp[256];
	int* s7;
	int t0;
	int t1;
	int s4;
	int at;
	int* a3;
	int* s3;
	int t2;
	int t3;
	int t4;
	int t5;
	int t6;
	int t7;
	int t8;
	int* a0;
	char* s0;
	char* s1;
	int fp;
	int gp;
	int t9;

	initialise_light_matrix();

	v0 = ((int*)mesh)[2];
	mesh += 6;
	s5 = clip;
	s6 = v0;
	a1 = v0 >> 16;
	v1 = v0 & 0x8000;
	v0 &= 0xFF;

	if ((s6 & 0x100) != 0)
	{
		a22 = 0x69;
	}
	else
	{
		a22 = 0x7E;
	}

	//loc_7EF28
	a1 += (int)mesh;
	if (v0 >= a22)
	{
		a2 = (int*)& tsv_buffer[0];
	}
	//loc_7EF40
	if ((s6 & 0x100) != 0)
	{
		a2 = &sp[45];
	}
	else
	{
		a2 = &sp[0];
	}

	//loc_7EF4C
	s7 = a2;

	if (v0 != 0)
	{
		t0 = TRZ;
		t1 = 0;
		s4 = t0;
		t0 -= 12288;
		at = v0 << 3;
		if (t0 > 0)
		{
			t1 >>= t0;
		}
		//loc_7EF74
		IR0 = t1;

		if (v1 != 0)
		{
			v1 = v0;
			a3 = (int*)mesh;

			//loc_7EF84
			do
			{
				t0 = ((short*)a3)[3];
				a3 += 2;
				IRGB = t0;
				v1--;
				a2 += 2;

				docop2(0x680029);
				t0 = ORGB;//checkme mfc
				((short*)a2)[-1] = t0;
			} while (v1 != 0);

			a2 = s7;
		}
		else
		{
			//loc_7EFB4
			v1 = v0;
			a3 = (int*)&mesh[at >> 1];
			s3 = a3;

			//loc_7EFBC
			do
			{
				VX0 = a3[0] & 0xFFFF;
				VY0 = a3[0] >> 16;
				VZ0 = a3[1];
				a3 += 2;
				docop2(0xE80413);
				v1--;
				a2 += 2;
				t0 = ORGB;
				((short*)a2)[-1] = t0;
			} while (v1 != 0);

			a2 = s7;
		}
		//loc_7EFE4
		t0 = ((int*)mesh)[0];

		//loc_7EFE8
		t1 = ((int*)mesh)[1];
		t2 = ((int*)mesh)[2];

		//loc_7EFF0
		t3 = ((int*)mesh)[3];
		t4 = ((int*)mesh)[4];
		t5 = ((int*)mesh)[5];

		RFC = (unsigned long)mesh;

		//loc_7F000
		do
		{
			VX0 = t0 & 0xFFFF;
			VY0 = t0 >> 16;
			VZ0 = t1;

			VX1 = t2 & 0xFFFF;
			VY1 = t2 >> 16;
			VZ1 = t3;

			VX2 = t4 & 0xFFFF;
			VY2 = t4 >> 16;
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

			t6 = SZ1;
			t7 = SZ2;
			t8 = SZ3;

			a2[0] = SXY0;
			((short*)a2)[2] = t6;
			a2[2] = SXY1;
			((short*)a2)[6] = t7;
			a2[4] = SXY2;
			((short*)a2)[10] = t8;
			a2 += 6;
		} while (v0 > 0);
	}
	//loc_7F068
	a0 = s7;
	a2 = (int*)psxtextinfo;
	a3 = (int*)db.ot;
	s0 = db.polyptr;
	s1 = db.polybuf_limit;

	v0 = ((int*)a1)[0];
	fp = 0xF80000;
	at = v0 >> 16;
	DQA = at;

	at = s6 & 0xC00;
	s6 &= 0x100;

	if (at)
	{
		///goto DrawMesh_Env;
	}

	s4 -= 0xC00;
	if (s6)
	{
		v0 &= 0xFFFF;
		if (s4 < 0)
		{
			///goto DrawSubDivMesh;
		}
	}
	//loc_7F0A8
	v0 &= 0xFFFF;

	if (s5 < 0)
	{
		///goto DrawClippedMesh;
	}

	gp = 0x9000000;
	a1 += 4;

	if (v0 != 0)
	{
		t0 = ((int*)a1)[0];

loc_7F0C0:
		a1 += 4;
		v1 = 3;

loc_7F0C8:
		t1 = ((int*)a1)[0];
		v0--;
		if ((unsigned int)s0 < (unsigned int)s1)
		{
			t8 = (t1 >> 13) & 0x7F8;
			t8 += (int)a0;
			t7 = (t1 >> 5) & 0x7F8;
			t7 += (int)a0;
			t6 = (t1 << 3) & 0x7F8;
			t6 += (int)a0;

			s4 = ((int*)t6)[0];
			s5 = ((int*)t7)[0];
			s6 = ((int*)t8)[0];

			SXY0 = s4;
			SXY1 = s5;
			SXY2 = s6;

			t5 = t0 & 0xFF;
			t0 >>= 8;

			docop2(0x1400006);

			t6 = ((int*)t6)[1];
			t7 = ((int*)t7)[1];
			t8 = ((int*)t8)[1];

			SZ1 = t6;
			SZ2 = t7;
			SZ3 = t8;

			t1 >>= 16;
			t1 &= 0xF00;
			at = MAC0;
			docop2(0x158002D);

			t5 |= t1;
			if (at >= 0)
			{
				t5 <<= 4;
				t5 += (int)a2;
				t1 = VZ0;

				if (t1 < 0xA02 && t1 >= 0x21)
				{
					t1 <<= 2;
					t4 = ((int*)t5)[2];
					at = t4 << 8;

					UnpackRGB(&t2, &t6, &fp, &t3, &at, &t7, &t8);
					at = DQB;
					t2 = ((int*)t5)[0];
					t3 = ((int*)t5)[1];
					t2 -= at;

					InitGT3(s0, t6, s4, t2, t7, s5, t3, t8, s6, s4);
					t1 += (int)a3;
					t2 = ((int*)t2)[0];
					((int*)t1)[0] = (int)s0;
					t2 |= gp;
					((int*)s0)[0] = t2;
					s0 += 0x28;
				}//loc_7F1AC
			}//loc_7F1AC

			a1 += 4;
			if (v0 != 0)
			{
				if (v1-- != 0)
				{
					goto loc_7F0C8;
				}

				goto loc_7F0C0;
				t0 = ((int*)a1)[0];

			}//loc_7F1C4
		}
		else
		{
			goto loc_7F304;
		}
	}
	//loc_7F1C4
	v0 = DQA;
	gp = 0xC000000;
	t0 = ((int*)a1)[0];

	if (v0 != 0)
	{
loc_7F1D4:
		a1 += 4;
		v1 = 1;

loc_7F1DC:
		t1 = ((int*)a1)[0];
		v0--;

		if ((unsigned int)s0 < (unsigned int)s1)
		{
			t9 = (t1 >> 21) & 0x7F8;
			t8 = (t1 >> 13) & 0x7F8;
			t8 += (int)a0;
			t7 = (t1 >> 5) & 0x7F8;
			t7 += (int)a0;
			t6 = (t1 << 3) & 0x7F8;
			t6 += (int)a0;

			s4 = ((int*)t6)[0];
			s5 = ((int*)t7)[0];
			s6 = ((int*)t8)[0];

			SXY0 = s4;
			SXY1 = s5;
			SXY2 = s6;

			t9 += (int)a0;

			docop2(0x1400006);

			t6 = ((int*)t6)[1];
			t7 = ((int*)t7)[1];
			t8 = ((int*)t8)[1];
			int s77 = ((int*)t9)[0];
			t9 = ((int*)t9)[1];

			SZ0 = t6;
			SZ1 = t7;
			SZ2 = t8;
			SZ3 = t9;
			at = MAC0;
			docop2(0x168002E);

			t5 = t0 & 0xFF;
			t0 >>= 16;
			t5 <<= 4;

			if (at >= 0)
			{
				t5 += (int)a2;
				t2 = t9 >> 7;
				t1 = OTZ;
				t2 &= fp;

				if (t1 < 0xA02 && t1 >= 0x21)
				{
					t1 <<= 2;
					t3 = t9 >> 10;
					t3 &= 0xF800;
					t9 >>= 13;
					t9 &= 0xF8;
					t9 |= t3;
					t9 |= t2;
					t4 = ((int*)t5)[2];
					at = t4;
					UnpackRGB(&t2, &t6, &fp, &t3, &at, &t7, &t8);
					at = DQB;

					t2 = ((int*)t5)[0];
					t3 = ((int*)t5)[1];
					t5 = ((int*)t5)[3];
					t2 -= at;
					InitGT4(s0, t6, s4, t2, t7, s5, t3, t8, s6, t4, t9, s77, t5);
					t1 += (int)a3;
					t2 = ((int*)t1)[0];
					((int*)t1)[0] = (int)s0;
					t2 |= gp;
					((int*)s0)[0] = t2;
					s0 += 0x34;
				}
				//loc_7F2EC
			}
			//loc_7F2EC
			a1 += 4;
			if (v0 != 0)
			{
				if (v1-- != 0)
				{
					goto loc_7F1DC;
				}

				goto loc_7F1D4;
				t0 = ((int*)a1)[0];

			}//loc_7F304
		}//loc_7F304
	}
loc_7F304:
	RFC = 0;
	db.polyptr = s0;
	return;

WANK2:
	return;
}

void phd_PutPolygons_train(short* mesh, long shade)
{
	UNIMPLEMENTED();
}

void phd_PutPolygons(short* mesh, long shade)
{
	phd_PutPolygons_normal(mesh, shade);
}

void phd_PutPolygons_pickup(short* mesh, long shade)
{
	int v0;
	int* a1;
	int t0;
	int t1;
	int t2;
	int t3;
	int t4;
	int t5;
	int t6;
	int t7;
	int t8;
	int at;
	int v1;
	int* a3;
	int sp[256];//0x1F800000
	int* a2;
	int* s7;
	int* a0;
	int fp;
	int s2;
	int s4;
	int s5;
	int s6;
	char* s0;
	int t9;
	int s3;

	initialise_light_matrix();

	v0 = ((int*)mesh)[2];
	mesh += 6;
	a1 = (int*)&mesh[v0 >> 17];
	v0 &= 0xFF;
	a2 = &sp[0];
	s7 = a2;
	t0 = TRZ - 12288;
	t1 = 0;

	at = v0 << 3;

	if (t0 > 0)
	{
		t1 = t0 >> 1;
	}
	//loc_80548
	IR0 = t1;
	v1 = v0;
	a3 = (int*)&mesh[at >> 1];
	t0 = 0x808080;
	R = 128;
	G = 128;
	B = 128;

	//loc_80560
	do
	{
		VX0 = a3[0] & 0xFFFF;
		VY0 = (a3[0] >> 16) & 0xFFFF;
		VZ0 = a3[1];
		a3 += 2;

		docop2(0xE80413);
		v1--;
		a2 += 2;
		t0 = LIM(IR1 >> 7, 0x1F, 0, 0) | (LIM(IR2 >> 7, 0x1F, 0, 0) << 5) | (LIM(IR3 >> 7, 0x1F, 0, 0) << 10);
		((short*)a2)[-1] = t0;
	} while (v1 != 0);

	a2 = s7;

	t0 = ((int*)mesh)[0];
	t1 = ((int*)mesh)[1];
	t2 = ((int*)mesh)[2];
	t3 = ((int*)mesh)[3];
	t4 = ((int*)mesh)[4];
	t5 = ((int*)mesh)[5];

	//loc_805A0
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

		t6 = SZ1;
		t7 = SZ2;
		t8 = SZ3;

		a2[0] = SXY0;
		((short*)a2)[2] = t6;
		a2[2] = SXY1;
		((short*)a2)[6] = t7;
		a2[4] = SXY2;
		((short*)a2)[10] = t8;
		a2 += 6;

	} while (v0 > 0);

	a0 = s7;
	s0 = db.polyptr;
	v0 = a1[0];
	fp = 0xF80000;
	at = v0 >> 16;
	DQA = at;
	v0 &= 0xFFFF;
	s2 = 0x9000000;
	a1 += 1;

	if (v0 != 0)
	{
		t0 = a1[0];

	loc_80640:
		a1 += 1;
		v1 = 3;

	loc_80648:
		t1 = a1[0];
		v0--;

		if ((unsigned long)s0 < (unsigned long)db.polybuf_limit)
		{
			int* t88;
			int* t77;
			int* t66;
			t88 = &a0[((t1 >> 13) & 0x7F8) >> 2];
			t77 = &a0[((t1 >> 5) & 0x7F8) >> 2];
			t66 = &a0[((t1 << 3) & 0x7F8) >> 2];

			s4 = t66[0];
			s5 = t77[0];
			s6 = t88[0];

			SXY0 = s4;
			SXY1 = s5;
			SXY2 = s6;

			t5 = t0 & 0xFF;
			t0 >>= 8;

			docop2(0x1400006);

			t6 = t66[1];
			t7 = t77[1];
			t8 = t88[1];

			SZ1 = t6;
			SZ2 = t7;
			SZ3 = t8;

			t1 >>= 16;
			t1 &= 0xF00;

			at = MAC0;
			docop2(0x158002D);
			t5 |= t1;

			if (at >= 0)
			{
				struct PSXTEXTSTRUCT* t55 = &psxtextinfo[t5];

				t1 = OTZ >> 1;
				at = t1;

				if (at < 256)
				{
					t4 = t55->u2v2pad;
					at = t4 << 8;
					UnpackRGB(&t2, &t6, &fp, &t3, &at, &t7, &t8);
					t2 = t55->u0v0clut;
					t3 = t55->u1v1tpage;
					InitGT3(s0, t6, s4, t2, t7, s5, t3, t8, s6, t4);

					unsigned long* t11 = &db.pickup_ot[t1];
					t2 = t11[0] | s2;
					t11[0] = (unsigned long)s0;
					((unsigned long*)s0)[0] = t2;
					s0 += 0x28;
				}//loc_80724
			}//loc_80724

			a1++;

			if (v0 != 0)
			{
				if (v1-- != 0)
				{
					goto loc_80648;
				}

				t0 = a1[0];
				goto loc_80640;
			}
		}//loc_80870
	}
	//loc_8073C
	v0 = DQA;
	s2 = 0xC000000;

	t0 = a1[0];
	if (v0 != 0)
	{
	loc_8074C:
		a1++;
		v1 = 1;

	loc_80754:
		t1 = a1[0];
		v0--;
		if ((unsigned long)s0 < (unsigned long)db.polybuf_limit)
		{
			int* t99;
			int* t88;
			int* t77;
			int* t66;
			int s77;

			t88 = &a0[((t1 >> 13) & 0x7F8) >> 2];
			t77 = &a0[((t1 >> 5) & 0x7F8) >> 2];
			t66 = &a0[((t1 << 3) & 0x7F8) >> 2];

			s4 = t66[0];
			s5 = t77[0];
			s6 = t88[0];
			SXY0 = s4;
			SXY1 = s5;
			SXY2 = s6;

			t99 = &a0[((t1 >> 21) & 0x7F8) >> 2];

			docop2(0x1400006);

			t6 = t66[1];
			t7 = t77[1];
			t8 = t88[1];
			s77 = t99[0];
			t9 = t99[1];

			SZ0 = t6;
			SZ1 = t7;
			SZ2 = t8;
			SZ3 = t9;

			at = MAC0;

			docop2(0x168002E);

			t5 = (t0 & 0xFFF);
			t0 >>= 16;

			if (at > 0)
			{
				struct PSXTEXTSTRUCT* t55 = &psxtextinfo[t5];

				t2 = t9 >> 7;
				t1 = OTZ >> 1;
				t2 &= fp;
				at = t1;

				if (at < 256)
				{
					t3 = (t9 >> 10) & 0xF800;
					t9 = (t9 >> 13) & 0xF8;
					t9 |= t3;
					t9 |= t2;
					t4 = t55->u2v2pad;
					at = t4;
					UnpackRGB(&t2, &t6, &fp, &t3, &at, &t7, &t8);

					t2 = t55->u0v0clut;
					t3 = t55->u1v1tpage;
					t5 = t55->u3v3pad;
					InitGT4(s0, t6, s4, t2, t7, s5, t3, t8, s6, t4, t9, s77, t5);

					unsigned long* t11 = &db.pickup_ot[t1];
					t2 = t11[0] | s2;
					t11[0] = (unsigned long)s0;
					((unsigned long*)s0)[0] = t2;
					s0 += 0x34;
				}//loc_80858
			}//loc_80858

			a1++;

			if (v0 != 0)
			{
				if (v1-- != 0)
				{
					goto loc_80754;
				}

				t0 = a1[0];
				goto loc_8074C;
			}
		}//loc_80870
	}//loc_80870
	RFC = 0;
	db.polyptr = s0;
}	

void phd_PutPolygons_seethrough(short* mesh, unsigned char shade)
{
	int v0;
	int s6;
	int* a1;
	int v1;
	int* a2;
	int sp[256];
	int* s7;
	int t0;
	int t1;
	int t2;
	int t3;
	int t4;
	int t5;
	int s4;
	int at;
	int* a3;
	int t6;
	int t7;
	int t8;
	int* a0;
	char* s0;
	char* s1;
	int fp;
	int gp;
	int s5;
	int t9;
	int s3;

	S_MemSet((char*)&sp[0], 0, sizeof(sp));

	if (shade == 0)
	{
		return;
	}

	if (shade == 128)
	{
		phd_PutPolygons_normal(mesh, 1);
	}

	return;///@fixme this crashes on stack corruption

	initialise_light_matrix();

	v0 = ((int*)mesh)[2];
	mesh += 6;
	s6 = v0;
	a1 = (int*)&mesh[v0 >> 17];
	v1 = v0 & 0x8000;
	v0 &= 0xFF;

	if (v0 > 0x7D)
	{
		a2 = (int*)&tsv_buffer[0];
	}
	else
	{
		a2 = &sp[0];
	}

	//loc_7FB64
	s7 = a2;
	t0 = TRZ - 12288;
	t1 = 0;
	s4 = t0;
	at = v0 << 3;

	if (t0 > 0)
	{
		t1 = t0 >> 1;
	}
	//loc_7FB84
	IR0 = t1;
	
	if (v1 != 0)
	{
		v1 = v0;
		a3 = (int*)mesh;

		//loc_7FB94
		do
		{
			t0 = ((short*)a3)[3];
			a3 += 2;
			IRGB = t0;
			v1--;
			a2 += 2;

			docop2(0x680029);

			t0 = ORGB;
			((short*)a2)[-1] = t0;

		} while (v1 != 0);

		a2 = s7;
	}
	else
	{
		v1 = v0;

		//loc_7FBC4
		a3 = (int*)&mesh[at >> 1];//checkme
		
		//loc_7FBC8
		do
		{
			VX0 = a3[0] & 0xFFFF;
			VY0 = (a3[0] >> 16) & 0xFFFF;
			VZ0 = a3[1];
			a3 += 2;

			docop2(0xE80413);
			v1--;
			a2 += 2;
			t0 = ORGB;
			((short*)a2)[-1] = t0;
		} while (v1 != 0);

		a2 = s7;
	}
	//loc_7FBF0
	t0 = ((int*)mesh)[0];
	t1 = ((int*)mesh)[1];
	t2 = ((int*)mesh)[2];
	t3 = ((int*)mesh)[3];
	t4 = ((int*)mesh)[4];
	t5 = ((int*)mesh)[5];

	RFC = (unsigned int)mesh;

	//loc_7FC0C
	do
	{
		VX0 = t0 & 0xFFFF;
		VY0 = t0 >> 16;
		VZ0 = t1;

		VX1 = t2 & 0xFFFF;
		VY1 = t2 >> 16;
		VZ1 = t3;

		VX2 = t4 & 0xFFFF;
		VY2 = t4 >> 16;
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

		t6 = SZ1;
		t7 = SZ2;
		t8 = SZ3;

		a2[0] = SXY0;
		((short*)a2)[2] = t6;
		a2[2] = SXY1;
		((short*)a2)[6] = t7;
		a2[4] = SXY2;
		((short*)a2)[10] = t8;
		a2 += 6;
	} while (v0 > 0);

	a0 = s7;
	a2 = (int*)psxtextinfo;
	a3 = (int*)db.ot;
	s0 = db.polyptr;
	s1 = db.polybuf_limit;

	v0 = a1[0];
	fp = 0xF80000;
	at = v0 >> 16;
	DQA = at;
	v0 &= 0xFFFF;
	gp = 0x9000000;
	a1++;

	if (v0 != 0)
	{
		t0 = a1[0];

	loc_7FCAC:
		a1++;
		v1 = 3;

	loc_7FCB4:
		t1 = a1[0];
		v0--;
		if ((unsigned long)s0 < (unsigned long)s1)
		{

			t8 = (t1 >> 13) & 0x7F8;
			t8 += (int)a0;

			t7 = (t1 >> 5) & 0x7F8;
			t7 += (int)a0;

			t6 = (t1 << 3) & 0x7F8;
			t6 += (int)a0;

			s4 = ((int*)t6)[0];
			s5 = ((int*)t7)[0];
			s6 = ((int*)t8)[0];

			SXY0 = s4;
			SXY1 = s5;
			SXY2 = s6;

			t5 = t0 & 0xFF;
			t0 >>= 8;
			docop2(0x1400006);

			t6 = ((int*)t6)[1];//bad value, short seems fine but upper most 16 bits are wrong
			t7 = ((int*)t7)[1];//bad value, short seems fine but upper most 16 bits are wrong
			t8 = ((int*)t8)[1];//bad value, short seems fine but upper most 16 bits are wrong
			SZ1 = t6;
			SZ2 = t7;
			SZ3 = t8;

			t1 >>= 16;
			t1 &= 0xF00;
			at = MAC0;
			docop2(0x158002D);
			t5 |= t1;

			if (at >= 0)
			{
				t5 <<= 4;
				t5 += (int)a2;
				t1 = OTZ;

				if (t1 < 0xA02 && t1 >= 0x21)
				{
					t1 <<= 2;
					t4 = ((int*)t5)[2];
					at = t4 << 8;

					UnpackRGB(&t2, &t6, &fp, &t3, &at, &t7, &t8);

					at = IRGB;
					t2 = ((int*)t5)[0];
					t3 = ((int*)t5)[1];
					t2 -= at;
					t1 += (int)a3;
					at = 0xFF9FFFFF;
					t3 &= at;
					at = 0x200000;
					t3 |= at;
					at = shade & 0xFF;
					InitGT3_V2((int*)s0, s4, &s3, t6, at, t7, t8, s5, t3, t2, s6, t4);

					t2 = ((int*)t1)[0];
					((int*)t1)[0] = (int)s0;
					t2 |= gp;
					((int*)s0)[0] = (int)t2;
					s0 += 0x28;

					s0 = do_the_flat_colursub_poly_tri(s0, shade & 0xFF, t6, t7, t8, s4, s5, s6, t1);

				}//loc_7FDB8
			}//loc_7FDB8

			a1++;
			if (v0 != 0)
			{
				if (v1-- != 0)
				{
					goto loc_7FCB4;
				}

				t0 = a1[0];
				goto loc_7FCAC;

			}//loc_7FDD0
		}//loc_7FDD0
		else
		{
			goto DrawExit;
		}

		DQA = v0;
		gp = 0xC000000;
		t0 = a1[0];
	}
	if (v0 == 0)
	{
		goto DrawExit;
	}

loc_7FDE0:
	a1++;
	v1 = 1;

loc_7FDE8:
	t1 = a1[0];

	v0--;
	if ((unsigned long)s0 < (unsigned long)s1)
	{
		t9 = t1 >> 21;
		t8 = (t1 >> 13) & 0x7F8;
		t8 += (int)a0;
		t7 = (t1 >> 5) & 0x7F8;
		t7 += (int)a0;
		t6 = (t1 << 3) & 0x7F8;
		t6 += (int)a0;

		s4 = ((int*)t6)[0];
		s5 = ((int*)t7)[0];
		s6 = ((int*)t8)[0];

		SXY0 = s4;
		SXY1 = s5;
		SXY2 = s6;

		t9 &= 0x7F8;
		t9 += (int)a0;
		docop2(0x1400006);

		t6 = ((int*)t6)[1];
		t7 = ((int*)t7)[1];
		t8 = ((int*)t8)[1];
		int s77 = ((int*)t9)[0];
		t9 = ((int*)t9)[1];
		SZ0 = t6;
		SZ1 = t7;
		SZ2 = t8;
		SZ3 = t9;
		at = MAC0;

		docop2(0x168002E);
		t5 = t0 & 0xFFF;
		t0 >>= 16;
		t5 <<= 4;

		if (at >= 0)
		{
			t5 += (int)a2;
			t2 = t9 >> 7;
			t1 = OTZ;
			t2 &= fp;

			if (t1 < 0xA02 && t1 >= 0x21)
			{
				t1 <<= 2;
				t3 = t9 >> 10;
				t3 &= 0xF800;
				t9 >>= 13;
				t9 &= 0xF8;
				t9 |= t3;
				t9 |= t2;
				t4 = ((int*)t5)[2];
				at = t4;
				UnpackRGB(&t2, &t6, &fp, &t3, &at, &t7, &t8);

				at = DQB;

				t2 = ((int*)t5)[0];
				t3 = ((int*)t5)[1];
				t5 = ((int*)t5)[3];
				t2 -= at;
				t1 += (int)a3;
				at = 0x3E000000;
				t6 |= at;
				at = 0xFF9FFFFF;
				t3 &= at;
				at = 0x200000;
				t3 |= at;
				at = shade & 0xFF;
				InitGT4_V2(s0, &s4, &s3, t6, at, t7, t8, t9, t2, s5, t3, s6, t4, s77, t5);
				at = ((int*)t1)[0];
				((int*)t1)[0] = (int)s0;
				at |= gp;
				((int*)s0)[0] = (int)at;
				s0 += 0x34;
				s0 = do_the_flat_colursub_poly_quad(s0, shade & 0xFF, t6, t7, t8, t9, s4, s5, s6, s77, t1);;
			}

		}
		//loc_7FF20
		a1++;
		if (v0 == 0)
		{
			goto DrawExit;
		}

		if (v1-- != 0)
		{
			goto loc_7FDE8;
		}

		t0 = a1[0];
		goto loc_7FDE0;
	}
	else
	{
		goto DrawExit;
	}

	return;

DrawExit:
	RFC = 0;
	db.polyptr = s0;
}
