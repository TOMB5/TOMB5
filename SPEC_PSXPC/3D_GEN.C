#include "3D_GEN.H"

#include "CAMERA.H"
#include "GPU.H"
#include "LOAD_LEV.H"
#include "SPECIFIC.H"

#ifdef PSXPC_VERSION
	#include <SDL.h>
#else
	#include <LIBGTE.H>
#endif

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
struct VECTOR3D CamPos;
struct VECTOR3D CamTgt;

void phd_InitWindow(int view_angle)//5D74C, 5DBC8
{
	if (rcossin_tbl[(((((((view_angle * 2) + view_angle) * 8) - view_angle) * 4) - view_angle) / 8) & 0x1FFE] == 0)
	{
#ifdef PSX_VERSION
		_asm("break 7")
#endif
	}

	//loc_5D7B0
	phd_right = SCREEN_WIDTH - 1;
	phd_persp = (rcossin_tbl[((((((((view_angle * 2) + view_angle) * 8) - view_angle) * 4) - view_angle) / 8) & 0x1FFE) + 1] << 8) / rcossin_tbl[(((((((view_angle * 2) + view_angle) * 8) - view_angle) * 4) - view_angle) / 8) & 0x1FFE];
	phd_left = 0;
	phd_top = 0;
	phd_bottom = SCREEN_HEIGHT - 1;
	phd_mxptr = &matrix_stack[0];

#ifdef PSX_VERSION
	SetGeomOffset(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	SetGeomScreen(phd_persp);
#endif

#ifdef PSXPC_VERSION
	if (SDL_Init(SDL_INIT_VIDEO) == 0)
	{
		g_window = SDL_CreateWindow("TOMB5", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
	}
	else
	{
		S_ExitSystem("Error: Failed to initialise SDL\n");
	}

	SDL_GLContext context = SDL_GL_CreateContext(g_window);
#endif
}

long mGetAngle(long x/*$a1*/, long z/*$a0*/, long tx/*$a3*/, long tz/*$a2*/)//77678(<), 796BC(<)
{

	int t0 = tz - z;
	int t1 = tx - x;
	int at = t0 | t1;
	int v0 = 0;
	int a0 = 0;
	int a1 = 0;

	if (at != 0)
	{
		a0 = 0x90000;
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
		a1 = 0x90000;
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