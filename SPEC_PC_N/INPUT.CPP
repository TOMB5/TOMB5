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
int16_t layout[2][18] = 
{
	{ DIK_UP, DIK_DOWN, DIK_LEFT, DIK_RIGHT, DIK_PERIOD, DIK_SLASH, DIK_RSHIFT, DIK_RMENU, DIK_RCONTROL, DIK_SPACE, DIK_COMMA, DIK_NUMPAD0, DIK_END, DIK_ESCAPE, DIK_DELETE, DIK_NEXT, DIK_P, DIK_RETURN },
	{ DIK_UP, DIK_DOWN, DIK_LEFT, DIK_RIGHT, DIK_PERIOD, DIK_SLASH, DIK_RSHIFT, DIK_RMENU, DIK_RCONTROL, DIK_SPACE, DIK_COMMA, DIK_NUMPAD0, DIK_END, DIK_ESCAPE, DIK_DELETE, DIK_NEXT, DIK_P, DIK_RETURN }
};

int S_UpdateInput()
{
	Unimpl();
	return 0;
}