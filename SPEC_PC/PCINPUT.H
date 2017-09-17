#ifndef PCINPUT_H
#define PCINPUT_H
#include <windows.h>
#define DIRECTINPUT_VERSION 0x0700
#include <dinput.h>
#pragma comment (lib, "dinput.lib")
extern long input;
extern long inputBusy;

extern int sub_402CD4(HWND hWnd, HINSTANCE hInstance);

#endif