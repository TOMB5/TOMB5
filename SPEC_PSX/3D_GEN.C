#include "3D_GEN.H"

#include "CAMERA.H"
#include "GPU.H"
#include "SPECIFIC.H"

#include <LIBGTE.H>

long phd_left;
long phd_right;
long phd_top;
long phd_bottom;
long phd_persp;
long w2v_matrix[12];
long* phd_mxptr;
long matrix_stack[24];
struct PHD_3DPOS viewer;
struct VECTOR3D CamPos;
struct VECTOR3D CamTgt;

void phd_InitWindow(int view_angle)//5D74C, 5DBC8 (F)
{
	if (rcossin_tbl[(((((((view_angle * 2) + view_angle) * 8) - view_angle) * 4) - view_angle) / 8) & 0x1FFE] == 0)
	{
#if PAELLA
		S_Warn("[phd_InitWindow] - Unimplemented mips\n");
#else
		__asm__ volatile ("break 7");
#endif
	}

	//loc_5D7B0
	phd_right = SCREEN_WIDTH - 1;
	phd_persp = (rcossin_tbl[((((((((view_angle * 2) + view_angle) * 8) - view_angle) * 4) - view_angle) / 8) & 0x1FFE) + 1] << 8) / rcossin_tbl[(((((((view_angle * 2) + view_angle) * 8) - view_angle) * 4) - view_angle) / 8) & 0x1FFE];
	phd_left = 0;
	phd_top = 0;
	phd_bottom = SCREEN_HEIGHT - 1;
	phd_mxptr = &matrix_stack[0];

	SetGeomOffset(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	SetGeomScreen(phd_persp);
}