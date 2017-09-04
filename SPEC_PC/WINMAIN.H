#ifndef WINMAIN_H
#define WINMAIN_H
#undef __cplusplus
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
#define SLOBYTE(x)   (*((int8*)&(x)))
#define SLOWORD(x)   (*((int16*)&(x)))
#define SLODWORD(x)  (*((int32*)&(x)))
#define SHIBYTE(x)   (*((int8*)&(x)+1))
#define SHIWORD(x)   (*((int16*)&(x)+1))
#define SHIDWORD(x)  (*((int32*)&(x)+1))
#define SBYTEn(x, n)   (*((int8*)&(x)+n))
#define SWORDn(x, n)   (*((int16*)&(x)+n))
#define NULL 0

inline void *qmemcpy(void *dst, const void *src, size_t cnt)
{
	char *out = (char *)dst;
	const char *in = (const char *)src;
	while (cnt > 0)
	{
		*out++ = *in++;
		--cnt;
	}
	return dst;
}

extern const char* ClassName;
extern const char* WindowName;
extern LPARAM dword_E4ACB8;
extern HANDLE dword_E4ACA4;
extern UINT dword_E4ACAC;

extern HKEY hKey;
extern DWORD opt_DD;
extern DWORD opt_D3D;
extern DWORD opt_VMode;
extern DWORD opt_TFormat;
extern DWORD opt_DS;
extern BYTE opt_BumpMap;
extern BYTE opt_Filter;
extern BYTE opt_DisableSound;
extern BYTE opt_Volumetric;
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

#endif