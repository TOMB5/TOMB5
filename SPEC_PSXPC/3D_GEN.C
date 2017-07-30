#include "3D_GEN.H"

#include "CAMERA.H"
#include "LOAD_LEV.H"

#include <assert.h>

long phd_left;
long phd_right;
long phd_top;
long phd_bottom;
long phd_persp;
long w2v_matrix[12];
long* phd_mxptr;
long matrix_stack[24];
struct PHD_3DPOS viewer;
//struct VECTOR3D CamPos;
//struct VECTOR3D CamTgt;

void phd_InitWindow(int view_angle)//5D74C, 5DBC8
{
	int v0 = (((((((view_angle << 1) + view_angle) << 3) - view_angle << 2) - view_angle) >> 3) & 0x1FFE);
	int a0 = (v0 + 1) << 1;

	short* a00 = (short*)(char*)(&rcossin_tbl[0]) + a0;
	short* v00 = (short*)(char*)(&rcossin_tbl[0]) + (v0 * 2);

	if (v00[0] == 0)
	{
		assert(0);
	}
	else
	{
		a0 = 256;
		phd_right = 511;
		phd_persp = (a00[0] << 8) / v00[0];
		phd_left = 0;
		phd_top = 0;
		phd_bottom = 239;
		phd_mxptr = &matrix_stack[0];
		//SetGeomOffset();
		int a1 = 120;
		a0 = phd_persp;
		//SetGeomScreen();
	}
}

long mGetAngle(long x/*$a1*/, long z/*$a0*/, long tx/*$a3*/, long tz/*$a2*/)//77678(<), 796BC(<)
{

	int t0 = tz - z;
	int t1 = tx - x;
	int at = t0 | t1;
	int v0 = 0;
	if (at != 0)
	{
		int a0 = 0x90000;
		if (t0 < 0)
		{
			v0 |= 0x10;
			t0 = -t0;
		}

		//0x796E0
		a0 |= 0x5FD4;
		if (t1 < 0)
		{
			v0 += 8;
			t1 = -t1;
		}

		//796F0
		int a1 = 0x90000;
		if (t0 < t1)
		{
			v0 += 4;
			at = t0;
			t0 = t1;
			t1 = at;
		}
		
		//7970C
		at = t1 >> 0x10;

		while (t1 >> 0x10 != 0)
		{
			t0 <<= 1;
			t1 <<= 1;
		}

		//79724
		t1 <<= 0xB;
		t1 /= t0;
		a1 |= 0x5FB4;
		a1 += v0;
		t0 = t1;
		t1 = atanOctantTab[v0 / 4];

		t0 = atanTab[t0];

		t0 += t1;

		v0 = t0;
		if (t0 < 0)
		{
			v0 = 0 - t0;
			v0 = 0 - v0;
			return v0;
		}//79760

		return t0;

	}//79760

	return 0;
}
