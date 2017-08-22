#ifndef WINMAIN_H
#define WINMAIN_H

#include <windows.h>

extern HWND SendMsg(char a1, char *a2, ...);
extern int WinProcMsg();
extern char* WinProcessCommandLine(char *a1);
extern char WinRunCheck(const CHAR *lpName, const CHAR *lpClassName, HANDLE *mutex);
extern HWND WinClose();
extern int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nShowCmd);

#endif