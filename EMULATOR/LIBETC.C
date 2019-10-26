#include "LIBETC.H"

#include "EMULATOR.H"
#include "EMULATOR_GLOBALS.H"
#include "EMULATOR_PRIVATE.H"

#include <stdio.h>
#if defined(_WINDOWS)
#include <d3d9.h>
#endif

void(*vsync_callback)(void) = NULL;

int ResetCallback(void)
{
	vsync_callback = NULL;
	UNIMPLEMENTED();
	return 0;
}

int VSync(int mode)
{
	if (mode == 0)
	{
		if (vsync_callback != NULL)
		{
			vsync_callback();
		}

		Emulator_EndScene();
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
		return 7;
	}

	return 0;
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
