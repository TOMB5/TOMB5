#ifndef WINMAIN_H
#define WINMAIN_H

#include <windows.h>
typedef unsigned int uint;
typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned long ulong;

typedef          char   int8;
typedef   signed char   sint8;
typedef unsigned char   uint8;
typedef          short  int16;
typedef   signed short  sint16;
typedef unsigned short  uint16;
typedef          int    int32;
typedef   signed int    sint32;
typedef unsigned int    uint32;
#define _BYTE  uint8
#define _WORD  uint16
#define _DWORD uint32
#define _QWORD uint64
#define LOBYTE(x)   (*((_BYTE*)&(x)))   // low byte
#define LOWORD(x)   (*((_WORD*)&(x)))   // low word
#define LODWORD(x)  (*((_DWORD*)&(x)))  // low dword
#define HIBYTE(x)   (*((_BYTE*)&(x)+1))
#define HIWORD(x)   (*((_WORD*)&(x)+1))
#define HIDWORD(x)  (*((_DWORD*)&(x)+1))
#define BYTEn(x, n)   (*((_BYTE*)&(x)+n))
#define WORDn(x, n)   (*((_WORD*)&(x)+n))

int dword_876C48 = 0;
HWND hWnd;
HACCEL hAccTable;
const char* Name = "Tomb Raider Chronicles";
const char* ClassName = "DBLogWindowClass";
const char* WindowName = "DBLog Server";
UINT Msg;
HANDLE hObject;
WNDCLASSA WndClass;
HINSTANCE hinst;
HANDLE hThread;
const char* Caption = "Tomb Raider";
LPARAM dword_E4ACB8;
HANDLE dword_E4ACA4;
UINT dword_E4ACAC;
UINT dword_E4ACB0;
uint8 byte_57A098;
uint8 byte_D9AC23;
uint8 byte_D9AC19;

extern HWND SendMsg(HWND hWnd, LPARAM lParam);
extern int WinProcMsg();
extern char* WinProcessCommandLine(char *a1);
extern char WinRunCheck(const CHAR *lpName, const CHAR *lpClassName, HANDLE *mutex);
extern HWND WinClose();
extern int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd);
extern HANDLE sub_4DEA40(LPCSTR lpName);
extern LPVOID sub_4DEA20(HANDLE hFileMappingObject);

#endif