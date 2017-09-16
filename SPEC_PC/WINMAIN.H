#ifndef WINMAIN_H
#define WINMAIN_H
#undef __cplusplus
#include <windows.h>
#include <dsound.h>
#include "SPECTYPES.H"
#include <dinput.h>
#include <d3d.h>



extern const char* ClassName;
extern const char* WindowName;
extern LPARAM dword_E4ACB8;
extern HANDLE dword_E4ACA4;
extern UINT dword_E4ACAC;

extern void __fastcall sub_4DA111(_DWORD *a1);

void* dword_D9AB34;
BYTE byte_86BBB4;
extern HWND hWnd;
extern DWORD dword_876C40;
DWORD dword_D9AB18;
DWORD dword_D9ADE8;
WORD word_C713D0;
WORD word_D6866C;
WORD word_C717E4;
WORD word_C713D8;

DWORD dword_D9BB8C;
DWORD dword_D9BB88;
DWORD GnFrameCounter;
int(*ptr_EndScene)(void);
int(*ptr_BeginScene)();
int(*dword_876C14)(float*, float*, float*);
int(*dword_876C08)(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD);
int(*dword_876C10)(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD);
int(*dword_876C04)(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD);
int(*dword_876BFC)(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD);
struct acceltexformatinfo*(*dword_876C00)(_DWORD, _DWORD, _DWORD);
extern HKEY hKey;
extern BYTE opt_NoFMV;
extern BYTE opt_Setup;
extern HWND SendMsg(HWND hWnd, LPARAM lParam);
extern int WinProcMsg();
extern char* WinProcessCommandLine(char *a1);
extern char WinRunCheck(const CHAR *lpName, const CHAR *lpClassName, HANDLE *mutex);
extern HWND WinClose();
extern int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd);
extern HANDLE sub_4DEA40(LPCSTR lpName);
extern LPVOID sub_4DEA20(HANDLE hFileMappingObject);
extern int HWInitialise();
extern int __cdecl sub_4017E9(int a1, int a2, signed int width, signed int a4, int a5, int a6, int a7);
extern signed __int64 sub_402DD3();

#endif