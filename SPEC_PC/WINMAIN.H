#ifndef WINMAIN_H
#define WINMAIN_H

#include <windef.h>

extern HWND SendMsg(char a1, char *a2, ...);
extern int WinProcMsg();
extern char* WinProcessCommandLine(char *a1);
extern char WinRunCheck(const CHAR *lpName, const CHAR *lpClassName, HANDLE *mutex);
extern HWND WinClose();
extern int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow);

#endif