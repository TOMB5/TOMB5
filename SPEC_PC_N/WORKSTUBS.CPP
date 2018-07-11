#include "STANDARD.H"
#include "GLOBAL.H"


#include "INIT.H"
#include "WINMAIN.H"
//#include "DEBUG.H"
#include "HWRENDER.H"

extern "C" void S_ExitSystem(char *message) {
	DXSetCooperativeLevel(App.lpDD, App.WindowHandle, DDSCL_NORMAL);
	MessageBox(App.WindowHandle, message, NULL, MB_OK);
	//ShutdownGame();
	strcpy(exit_message, message);
	//EndLog();
	exit(1);
}