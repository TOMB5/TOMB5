#include "3D_GEN.H"

#include "CAMERA.H"
#include "GPU.H"
#include "LOAD_LEV.H"
#include "SPECIFIC.H"

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
		assert(0);
	}

	//loc_5D7B0
	phd_right = SCREEN_WIDTH - 1;
	phd_persp = (rcossin_tbl[((((((((view_angle * 2) + view_angle) * 8) - view_angle) * 4) - view_angle) / 8) & 0x1FFE) + 1] << 8) / rcossin_tbl[(((((((view_angle * 2) + view_angle) * 8) - view_angle) * 4) - view_angle) / 8) & 0x1FFE];
	phd_left = 0;
	phd_top = 0;
	phd_bottom = SCREEN_HEIGHT - 1;
	phd_mxptr = &matrix_stack[0];

	if (SDL_Init(SDL_INIT_VIDEO) == 0)
	{
		g_window = SDL_CreateWindow("TOMB5", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
	}
	else
	{
		S_ExitSystem("Error: Failed to initialise SDL\n");
	}

	SDL_GLContext context = SDL_GL_CreateContext(g_window);
}

long mGetAngle(long x, long z, long tx, long tz)//77678(<), 796BC(<) (F)
{
	long dx = tx - x;
	long dz = tz - z;
	short table_index = 0;
	long result_angle = 0;
	long temp = 0;

	if ((dx | dz) != 0)
	{
		if (dx < 0)
		{
			table_index |= 0x10;//FIXME: += (4);
			dx = -dx;
		}

		//0x796E0
		if (dz < 0)
		{
			table_index += 2;
			dz = -dz;
		}

		//796F0
		if (dx < dz)
		{
			table_index += 1;
			temp = dx;
			dx = dz;
			dz = temp;
		}
		
		//7970C
		while ((dz / 65536) != 0)
		{
			dx /= 2;
			dz /= 2;
		}

		//79724
		result_angle = atanTab[(dz * 2048) / dx];
		result_angle += atanOctantTab[table_index];

		if (result_angle < 0)
		{
			result_angle = -result_angle;
		}//79760

	}//79760

	return -result_angle & 0xFFFF;
}