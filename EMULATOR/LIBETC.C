#include "LIBETC.H"

#include "EMULATOR_PRIVATE.H"
#include "EMULATOR.H"

#if defined(_WINDOWS)
#include <d3d9.h>
#endif

#if defined(SDL2)
#include <SDL_timer.h>
#include <SDL.h>
#include <assert.h>

SDL_GameController* padHandleDebug[MAX_CONTROLLERS];

#endif

unsigned char* padDataDebug[MAX_CONTROLLERS];
const unsigned char* keyboardStateDebug;

char scratchData[4096];///@TODO check size

void(*vsync_callback)(void) = NULL;

static int g_initialisedPadSubsystem = FALSE;

int StopCallback(void)
{
	UNIMPLEMENTED();
	return 0;
}

void PadInit(int mode)
{
#if defined(SDL2)
	if (g_initialisedPadSubsystem == FALSE)
	{
		if (SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER) < 0)
		{
			eprinterr("Failed to initialise subsystem GAMECONTROLLER\n");
		}

		if (SDL_NumJoysticks() < 1)
		{
			eprinterr("Failed to locate a connected gamepad!\n");
		}
		else
		{
			for (int i = 0; i < SDL_NumJoysticks(); i++)
			{
				if (SDL_IsGameController(i) && i < MAX_CONTROLLERS)
				{
					padHandleDebug[i] = SDL_GameControllerOpen(i);///@TODO close joysticks
				}
			}
		}

		keyboardStateDebug = SDL_GetKeyboardState(NULL);
		g_initialisedPadSubsystem = TRUE;
	}
#endif
}

int ResetCallback(void)
{
	vsync_callback = NULL;
	return 0;
}

extern unsigned int g_swapTime;

static unsigned int currentTime = 0;
static unsigned int lastTime = 0;
static int numFrames = 0;

int VSync(int mode)
{
	Emulator_DoPollEvent();
	Emulator_UpdateInput();

	lastTime = currentTime;
	currentTime = SDL_GetTicks();

#if defined(SDL2)
	if (mode < 0)
		return SDL_GetTicks() - g_swapTime;

	if (mode == 0)
	{
		if (vsync_callback != NULL)
			vsync_callback();

		unsigned int elapsedTime = (currentTime - lastTime) * 2.354f;
		return elapsedTime;
	}
	else if (mode > 0)
	{
	}

	return SDL_GetTicks();
#elif 1
	if (mode < 0)
		return GetTickCount() - g_swapTime;

	if (mode == 0)
	{
		if (vsync_callback != NULL)
			vsync_callback();
	}
	else if (mode > 0)
	{
	}

	return GetTickCount();
#else
	return 0;
#endif
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

long SetVideoMode(long mode)
{
	UNIMPLEMENTED();
	return MODE_NTSC;
}

u_long PadRead(int id)
{
	unsigned short debugkbInputs = 0;

	if (g_initialisedPadSubsystem == FALSE)
	{
		return 0;
	}

	Emulator_UpdateInputDebug();

	extern unsigned short kbInputs;

	if (!(kbInputs & 0x10))
	{
		debugkbInputs |= PADLup;
	}

	if (!(kbInputs & 0x40))
	{
		debugkbInputs |= PADLdown;
	}

	if (!(kbInputs & 0x80))
	{
		debugkbInputs |= PADLleft;
	}

	if (!(kbInputs & 0x20))
	{
		debugkbInputs |= PADLright;
	}

	return debugkbInputs;
}
