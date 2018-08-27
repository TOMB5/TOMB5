#include "STANDARD.H"
#include "GLOBAL.H"
#include "WINMAIN.H"
//#include "console.h"
#include <math.h>
#include "TEMPLATE.H"
#include "INPUT.H"
#include "DI.H"
//#include "display.h"
//#include "frontend.h"
#include "INIT.H"

sint32 input;
sint32 dbinput;
sint32 inputBusy;

short mouse_x;
short mouse_y;
int mouse_vkeys;
unsigned char keymap[256];
int32_t conflict[18];
int16_t layout[2][18] = 
{
	{ DIK_UP, DIK_DOWN, DIK_LEFT, DIK_RIGHT, DIK_PERIOD, DIK_SLASH, DIK_RSHIFT, DIK_RMENU, DIK_RCONTROL, DIK_SPACE, DIK_COMMA, DIK_NUMPAD0, DIK_END, DIK_ESCAPE, DIK_DELETE, DIK_NEXT, DIK_P, DIK_RETURN },
	{ DIK_UP, DIK_DOWN, DIK_LEFT, DIK_RIGHT, DIK_PERIOD, DIK_SLASH, DIK_RSHIFT, DIK_RMENU, DIK_RCONTROL, DIK_SPACE, DIK_COMMA, DIK_NUMPAD0, DIK_END, DIK_ESCAPE, DIK_DELETE, DIK_NEXT, DIK_P, DIK_RETURN }
};
int joy_x;
int joy_y;
int joy_fire;

int S_UpdateInput()
int Key(int number)
{
	short key = layout[1][number];

	if (number >= 256)
		return joy_fire & (1 << number);

	if (keymap[key])
		return 1;

	switch(key)
	{
		case DIK_RCONTROL:
			return keymap[DIK_LCONTROL];
		case DIK_LCONTROL:
			return keymap[DIK_RCONTROL];
		case DIK_RSHIFT:
			return keymap[DIK_LSHIFT];
		case DIK_LSHIFT:
			return keymap[DIK_RSHIFT];
		case DIK_RMENU:
			return keymap[DIK_LMENU];
		case DIK_LMENU:
			return keymap[DIK_RMENU];
	}

	if (conflict[number])
		return 0;

	key = layout[0][number];

	if (keymap[key])
		return 1;

	switch (key)
	{
	case DIK_RCONTROL:
		return keymap[DIK_LCONTROL];
	case DIK_LCONTROL:
		return keymap[DIK_RCONTROL];
	case DIK_RSHIFT:
		return keymap[DIK_LSHIFT];
	case DIK_LSHIFT:
		return keymap[DIK_RSHIFT];
	case DIK_RMENU:
		return keymap[DIK_LMENU];
	case DIK_LMENU:
		return keymap[DIK_RMENU];
	}

	return 0;
}

}