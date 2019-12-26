#include "LIBETC.H"

#include "EMULATOR.H"
#include "EMULATOR_GLOBALS.H"
#include "EMULATOR_PRIVATE.H"

#include <stdio.h>
#if defined(_WINDOWS)
#include <d3d9.h>
#endif

#include <assert.h>

void(*vsync_callback)(void) = NULL;

int ResetCallback(void)
{
	vsync_callback = NULL;
	UNIMPLEMENTED();
	return 0;
}

int VSync(int mode)
{
	///static int startTime = SDL_GetTicks();

	if (mode == 0)
	{
		if (vsync_callback != NULL)
		{
			vsync_callback();
		}

		Emulator_EndScene();
		///return (SDL_GetTicks() - startTime / 1000);
	}
	else if (mode > 0)
	{
		while (mode--)
		{
			//vblank
		}
		Emulator_EndScene();
	}
	else if (mode < 0)
	{
		//Unimplemented
		///return (SDL_GetTicks() / 1000);
	}

	return 0;//Assert?
}

int VSyncCallback(void(*f)(void))
{
	vsync_callback = f;
	return 0;
}

long GetVideoMode(void)
{
	return MODE_NTSC;
}
