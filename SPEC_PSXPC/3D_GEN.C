#include "3D_GEN.H"

#include "CAMERA.H"
#include "GPU.H"
#include "LOAD_LEV.H"
#include "SPECIFIC.H"
#include "TYPES.H"

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

void phd_InitWindow(int view_angle)//5D74C, 5DBC8 (F)
{
	phd_right = SCREEN_WIDTH - 1;
	phd_persp = COS((((((view_angle << 1) + view_angle) << 3) - view_angle) << 2) - view_angle) << 8 / SIN((((((view_angle << 1) + view_angle) << 3) - view_angle) << 2) - view_angle);
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