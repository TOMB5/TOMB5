#include "ANIMITEM.H"

#include <LIBGTE.H>
#include "GTEREG.H"

void mmPushMatrix(int* fp)//81C0C(<)
{
	mLoadMatrix((int*)fp[20], fp);
}

void mLoadMatrix(int* a0, int* fp)//81C18(<)
{
	R11 = (a0[0] & 0xFFFF);
	R12 = (a0[0] >> 16) & 0xFFFF;
	R13 = (a0[1] & 0xFFFF);
	R21 = (a0[1] >> 16) & 0xFFFF;
	R22 = (a0[2] & 0xFFFF);
	R23 = (a0[2] >> 16) & 0xFFFF;
	R31 = (a0[3] & 0xFFFF);
	R32 = (a0[3] >> 16) & 0xFFFF;
	R33 = (a0[4] & 0xFFFF);
	TRX = a0[5];
	TRY = a0[6];
	TRZ = a0[7];

	fp[50] = (int)a0;
}

void stash_the_info(int meshp/*a0*/, int* fp)//81750
{
	int* at;

	at = (int*)fp[17];

	((int*)at)[0] = meshp;

	at[1] = R11 | (R12 << 16);
	at[2] = R13 | (R21 << 16);
	at[3] = R22 | (R23 << 16);
	at[4] = R31 | (R32 << 16);

	at[5] = R33;
	at[6] = TRX;
	at[7] = TRY;
	at[8] = TRZ;

	at += 9;

	fp[19]++;
	fp[17] = (int)at;
}

int GetBounds(int t0, int a2, int a3, int t1, int t2, int v0, int a0, int a1, int t3, int t4, int t5)//8139C
{
	if (t0 < a2)
	{
		a2 = t0;
	}

	//loc_813AC
	if (t0 >= a3)
	{
		a3 = t0;
	}

	//loc_813B8
	if (t1 < a2)
	{
		a2 = t1;
	}

	//loc_813C4
	if (t1 >= a3)
	{
		a3 = t1;
	}

	if (t2 < a2)
	{
		a3 = t2;
	}

	//loc_813DC
	t0 <<= 16;
	if (t2 >= a3)
	{
		a3 = t2;
	}

	//loc_813E8
	t1 <<= 16;
	t2 <<= 16;

	if (t0 < a0)
	{
		a0 = t0;
	}

	if (t0 >= a1)
	{
		a1 = t0;
	}

	if (t1 < a0)
	{
		a0 = t1;
	}

	if (t1 >= a1)
	{
		a1 = t1;
	}

	if (t2 < a0)
	{
		a0 = t2;
	}

	if (t2 >= a1)
	{
		a1 = t2;
	}

	if (t3 < 0x5000)
	{
		v0 = 1;
	}

	if (t4 < 0x5000)
	{
		v0 = 1;
	}

	if (t5 < 0x5000)
	{
		v0 = 1;
	}

	return v0;
}

int mClipBoundingBox2(short* bounds, int* sp /*fp*/)//811FC
{
	int t0 = TRZ - 20480;
	int t3;
	int t1;
	int t4;
	int t2;
	int t7;
	int v0 = 0;
	int at;
	int t9;
	int t8;
	int a0;
	int a1;
	int a2;
	int t5;
	int a3;

	if (t0 < 0)
	{
		t0 = bounds[0];
		t3 = bounds[1];
		t1 = bounds[2];
		t4 = bounds[3];
		t2 = bounds[4];
		t7 = bounds[5];

		t1 <<= 16;
		t4 <<= 16;

		at = t0 | t1;
		VX0 = at & 0xFFFF;
		VY0 = at >> 16;
		VZ0 = t2;

		at = t3 | t1;
		VX1 = at & 0xFFFF;
		VY1 = at >> 16;
		VZ1 = t2;

		at = t0 | t4;
		VX2 = at & 0xFFFF;
		VY2 = at >> 16;
		VZ2 = t2;

		docop2(0x280030);

		t9 = t3 | t4;
		t8 = t2;

		a0 = 0x7FFFFFFF;
		a1 = 0x81000000;
		a2 = a0;
		t0 = SXY0;
		t1 = SXY1;
		t2 = SXY2;
		t3 = SZ1;
		t4 = SZ2;
		t5 = SZ3;

		VZ0 = t7;
		VZ1 = t7;
		VZ2 = t7;

		a3 = a1;

		docop2(0x280030);

		t3 -= 33;
		t4 -= 33;
		t5 -= 33;

		v0 = 0;
		v0 = GetBounds(t0, a2, a3, t1, t2, v0, a0, a1, t3, t4, t5);

		t0 = SXY0;
		t1 = SXY1;
		t2 = SXY2;
		t3 = SZ1;
		t4 = SZ2;
		t5 = SZ3;

		VX0 = (t9 & 0xFFFF);
		VY0 = (t9 >> 16) & 0xFFFF;
		VZ0 = t8;

		VX1 = (t9 & 0xFFFF);
		VY1 = (t9 >> 16) & 0xFFFF;

		t2 -= 0x21;
		docop2(0x280030);
		t4 -= 0x21;
		t5 -= 0x21;

		v0 = GetBounds(t0, a2, a3, t1, t2, v0, a0, a1, t3, t4, t5);
	
		t0 = SXY0;
		t1 = SXY1;
		t3 = SZ1;
		t4 = SZ2;

		t3 -= 0x21;
		t4 -= 0x21;
		t2 = t1;
		t5 = t4;

		v0 = GetBounds(t0, at, a3, t1, t2, v0, a0, a1, t3, t4, t5);
		t0 = ((short*)sp)[73];
		t1 = ((short*)sp)[75];
		t2 = ((short*)sp)[72];
		t3 = ((short*)sp)[74];

		a0 >>= 16;
		a1 >>= 16;
		a2 >>= 16;
		a3 >>= 16;

		if (v0 == 0 || t0 < a0 || t1 < a2 || a1 < t2 || a3 < t3)
		{
			return 0;
		}

		if (v0 < 9 || a0 < t2 || a2 < t3 || t0 < a1 || t1 < a3)
		{
			return -1;
		}

		return 1;
	}

	return v0;
}
