#include "3D_GEN.H"

#include "CAMERA.H"

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