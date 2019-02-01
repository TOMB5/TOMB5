#include "LIBPAD.H"

#include <SDL.h>
#include <stdio.h>
#include <assert.h>

SDL_GameController* padHandle[MAX_CONTROLLERS];

unsigned char* padData[MAX_CONTROLLERS];

void PadInitDirect(unsigned char* pad1, unsigned char* pad2)
{
	padData[0] = pad1;
	padData[1] = pad2;

	padData[0][0] = 0xFF;
	padData[0][1] = 0xFF;

	if (SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER) < 0)
	{
		printf("Failed to initialise subsystem GAMECONTROLLER\n");
	}

	if (SDL_NumJoysticks() < 1)
	{
		printf("Failed to locate a connected gamepad!\n");
		return;
	}

	for (int i = 0; i < SDL_NumJoysticks(); i++)
	{
		if (SDL_IsGameController(i) && i < MAX_CONTROLLERS)
		{
			padHandle[i] = SDL_GameControllerOpen(i);///@TODO close joysticks
		}
	}
}

void PadInitMtap(unsigned char* unk00, unsigned char* unk01)
{
}

void PadInitGun(unsigned char* unk00, int unk01)
{
}

int PadChkVsync()
{
	
	return 0;
}

void PadStartCom()
{
}

void PadStopCom()
{
}

unsigned int PadEnableCom(unsigned int unk00)
{
	return 0;
}

void PadEnableGun(unsigned char unk00)
{
}

void PadRemoveGun()
{
}

int PadGetState(int port)
{
	if (!(SDL_GameControllerGetAttached(padHandle[port])))
	{
		return PadStateDiscon;
	}
	else
	{
		return PadStateStable;
	}

	return 0;
}

int PadInfoMode(int unk00, int, int unk01)
{
	return 7;//?
}

int PadInfoAct(int unk00, int, int unk01)
{
	return 0;
}

int PadInfoComb(int unk00, int, int unk01)
{
	return 0;
}

int PadSetActAlign(int unk00, unsigned char* unk01)
{
	return 0;
}

int PadSetMainMode(int socket, int offs, int lock)
{
	return 0;
}

void PadSetAct(int unk00, unsigned char* unk01, int unk02)
{
}

unsigned short UpdateInput(SDL_GameController* pad)
{
	unsigned short ret = -1;

	if (SDL_GameControllerGetButton(pad, SDL_CONTROLLER_BUTTON_X))//Square
	{
		ret &= ~0x8000;
	}

	if (SDL_GameControllerGetButton(pad, SDL_CONTROLLER_BUTTON_B))//Circle
	{
		ret &= ~0x2000;
	}

	if (SDL_GameControllerGetButton(pad, SDL_CONTROLLER_BUTTON_Y))//Triangle
	{
		ret &= ~0x1000;
	}

	if (SDL_GameControllerGetButton(pad, SDL_CONTROLLER_BUTTON_A))//Cross
	{
		ret &= ~0x4000;
		printf("LIBPAD_APRESSED!\n");
	}

	return ret;
}