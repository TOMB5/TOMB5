#include "standard.h"
#include "global.h"


#include "init.h"
#include "winmain.h"
//#include "debug.h"
#include "hwrender.h"

extern "C" void S_ExitSystem(char *message) {
	DXSetCooperativeLevel(App.lpDD, App.WindowHandle, DDSCL_NORMAL);
	MessageBox(App.WindowHandle, message, NULL, MB_OK);
	//ShutdownGame();
	strcpy(exit_message, message);
	//EndLog();
	exit(1);
}