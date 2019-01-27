#include "LIBETC.H"

#include <stdio.h>

#include "EMULATOR.H"


void(*vsync_callback)(void) = NULL;

int ResetCallback(void)
{
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

		while (lastTime - SDL_GetTicks() < (1000 / 60))
		{
			SDL_Delay(1);
		}

		Emulator_EndScene();
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
	return 0;
}
