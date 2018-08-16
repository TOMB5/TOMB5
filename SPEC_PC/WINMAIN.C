#undef __cplusplus
#define FORCE_NO_SOUND


#include "WINMAIN.H"
#include "SPECIFIC.H"
#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <crtdbg.h>
#include "GAMEFLOW.H"
#include <process.h>
#include <mm3dnow.h>
#include <ddraw.h>
#include <dsound.h>
#include "GAME.H"
#include <d3d.h>
#include "SOUND.H"
#include "resource.h"

#include "ERROR.H"
#include "MMREG.H"
#include "MSAcm.h"
#include "FILE.H"
#include "CONTROL.H"
#include "CD.H"
#include "PCSOUND.H"
#include "CAMERA.H"
#include "DIRECTX.H"
#include "PCINPUT.H"





int dword_876C48 = 0;
HWND hWnd;
const char* Name = "Tomb Raider Chronicles";
const char* ClassName = "DBLogWindowClass";
const char* WindowName = "DBLog Server";
UINT Msg;
WNDCLASSA WndClass;
HINSTANCE hinst;
HANDLE hThread;
const char* Caption = "Tomb Raider";
LPARAM dword_E4ACB8;
HANDLE dword_E4ACA4;
UINT dword_E4ACA8;
UINT dword_E4ACAC;
UINT dword_E4ACB0;
uint8 byte_57A098;

const char* String = "UM_DBLOGOUT";
const char* SubKey = "Software\\Core\\DBlog";
const char* ValueName = "CmdLine";
char GameDrive;
BYTE byte_D9ADEC;
DWORD dword_D9AD9C;
DWORD dword_D9AB24;
DWORD dword_D9AB20;
DWORD dword_D9AB28;







unsigned thread_id;
void* dword_E916E0;
DWORD dword_876C40;


HKEY hKey;
LPSTR Class;
DWORD dwDisposition;

DWORD window_width;
WORD window_width_minus_1;
DWORD window_height;
WORD window_pos_x;
WORD window_height_minus_1;
WORD window_pos_y;
DWORD middle_width;
DWORD middle_height;
DWORD dword_55D21C;
float middle_width_flt;
DWORD dword_55D1F4;
float middle_height_flt;
float flt_55D250;
DWORD phd_right;
DWORD phd_bottom;
float flt_55D664;
DWORD phd_top;
DWORD phd_left;
float flt_51D160;
float flt_55DA34;
float flt_51D14C;
float flt_55DA40;
float flt_55D228;
float flt_55D24C;
float flt_55D238;
float flt_51D158;
float flt_55DA38;
float flt_55D668;
float flt_55D25C;
float flt_51D150;
float flt_51D154;
float flt_55D220;
float flt_55D268;
float flt_51D15C;

BYTE opt_NoFMV;
BYTE opt_Setup;




WORD opt_Keys[18] =
{
	0x00C8, 0x00D0, 0x00CB, 0x00CD, 0x0034, 0x0035, 0x0036, 0x00B8, 0x009D, 0x0039, 
	0x0033, 0x0052, 0x00CF, 0x0001, 0x00D3, 0x00D1, 0x0019, 0x001C
};

WORD opt_Keys2[18] =
{
	0x00C8, 0x00D0, 0x00CB, 0x00CD, 0x0034, 0x0035, 0x0036, 0x00B8, 0x009D, 0x0039,
	0x0033, 0x0052, 0x00CF, 0x0001, 0x00D3, 0x00D1, 0x0019, 0x001C
};

DWORD dword_878C4C[18] = { 0 };

DWORD opt_JDck = 5;
DWORD opt_JDsh = 3;
DWORD opt_JWlk = 4;
DWORD opt_JJmp = 0;
DWORD opt_JAct = 1;
DWORD opt_JDrw = 2;
DWORD opt_JFlr = 9;
DWORD opt_JLok = 6;
DWORD opt_JRol = 7;
DWORD opt_JInv = 8;




HGDIOBJ gdiobject;

BYTE byte_511894[] =
{
	0x82, 0xE9, 0x8A, 0xE8, 0x88, 0xEA, 0x94, 0xF6, 0x85, 0xE0, 0xA0, 0xE1, 0xA2, 0xF3
};

BYTE unk_5118A2[5] = { 0 };
DWORD dword_57A08C;
BYTE opt_LowQualityTextures;
BYTE opt_LowQualityBumpMap;
DWORD opt_VolumetricFog;
BYTE opt_BilinearFiltering;


int* phd_mxptr; // 12 ints
int other_matrix_shit[12];
D3DMATRIX transform_world;
D3DMATRIX transform_projection;
D3DMATRIX transform_view;


DWORD dword_57A088;
DWORD dword_57A090;










float flt_50A438 = 12288.0;
float flt_50A43C = 20480.0;
float flt_50A444 = 2048.0;

WORD word_507AC0[844] = 
{
	0x0004, 0x000D, 0xFFF5, 0x0B00, 0xC4CE, 0x3EC4, 0xE8EA, 0x3E68, 0x0007, 0x0005, 0xFFF6, 0x0501, 0xA4B1, 0x3EA4, 0xD0EE, 0x3DD0, 0x000E, 0x000C, 0xFFF6, 0x0B01, 0x9C91, 0x3E9C, 0x98B3, 0x3E18, 0x000A, 0x000E, 0xFFF6, 0x0D01, 0xD6DC, 0x3F56, 0xD068, 0x3D50, 0x000F, 0x000C, 0xFFF7, 0x0C02, 0xA0B2, 0x3E20, 0xD0EE, 0x3DD0, 0x000E, 0x000C, 0xFFF6, 0x0B01, 0x9EA1, 0x3F1E, 0xE4C9, 0x3E64, 0x0005, 0x0005, 0xFFF5, 0x0400, 0xCCCD, 0x3F4C, 0x9C91, 0x3E1C, 0x0006, 0x0010, 0xFFF4, 0x0D00, 0x8872, 0x3E08, 0xA0B2, 0x3E20, 0x0006, 0x0010, 0xFFF5, 0x0E00, 0xB8BF, 0x3F38, 0xED0B, 0x3E6C, 0x0005, 0x0005, 0xFFF5, 0x0400, 0xB0F2, 0x3DB0, 0xA0B2, 0x3E20, 0x000B, 0x000B, 0xFFF7, 0x0B02, 0xB2AF, 0x3F32, 0xED0B, 0x3E6C, 0x0005, 0x0005, 0xFFFE, 0x0C08, 0xD4CC, 0x3ED4, 0xF0E9, 0x3E70, 0x0008, 0x0003, 0xFFFC, 0x0906, 0xE4EB, 0x3EE4, 0xF0E9, 0x3E70, 0x0005, 0x0004, 0xFFFE, 0x0B08, 0xD4DC, 0x3F54, 0x98B3, 0x3E18, 0x0009, 0x000F, 0xFFF4, 0x0C00, 0xB0AF, 0x3EB0, 0xC4CE, 0x3E44, 0x000A, 0x000A, 0xFFF8, 0x0B03, 0xC8CD, 0x3F48, 0xDCCA, 0x3E5C, 0x0006, 0x000A, 0xFFF8, 0x0B03, 0xB8AE, 0x3E38, 0xD0EE, 0x3E50, 0x0009, 0x000A, 0xFFF8, 0x0B03, 0xB0AF, 0x3EB0, 0x98B3, 0x3E18, 0x0008, 0x000B, 0xFFF8, 0x0C03, 0xF8E8, 0x3E78, 0xA0B2, 0x3E20, 0x000B, 0x000B, 0xFFF8, 0x0C03, 0x8E93, 0x3F0E, 0xC0AD, 0x3E40, 0x0009, 0x000C, 0xFFF7, 0x0C02, 0xE8EA, 0x3F68, 0xC8AC, 0x3E48, 0x0009, 0x000B, 0xFFF7, 0x0B02, 0xF0E9, 0x3EF0, 0xBCCF, 0x3E3C, 0x0009, 0x000C, 0xFFF7, 0x0C02, 0xB0F2, 0x3DB0, 0xCCCD, 0x3E4C, 0x0009, 0x000B, 0xFFF7, 0x0B02, 0xDCEC, 0x3EDC, 0xC4CE, 0x3E44, 0x0009, 0x000B, 0xFFF8, 0x0C03, 0x9891, 0x3F18, 0xE4C9, 0x3E64, 0x0005, 0x0009, 0xFFF9, 0x0B04, 0x8883, 0x3F08, 0xE4C9, 0x3E64, 0x0005, 0x000A, 0xFFF9, 0x0C04, 0xB2AF, 0x3F32, 0xA0B2, 0x3E20, 0x000C, 0x000A, 0xFFF8, 0x0B03, 0xD2CC, 0x3F52, 0xD4CC, 0x3E54, 0x000B, 0x0007, 0xFFF9, 0x0904, 0xF0E9, 0x3F70, 0xA0B2, 0x3E20, 0x000C, 0x000A, 0xFFF8, 0x0B03, 0xC0F0, 0x3D40, 0x9C91, 0x3E1C, 0x000A, 0x000D, 0xFFF5, 0x0B00, 0x8494, 0x3E84, 0xD068, 0x3D50, 0x0010, 0x000E, 0xFFF6, 0x0D01, 0x8284, 0x3F02, 0xD068, 0x3D50, 0x000E, 0x000D, 0xFFF5, 0x0B00, 0xD6DC, 0x3F56, 0xC8AC, 0x3DC8, 0x000D, 0x000D, 0xFFF5, 0x0B00, 0x8484, 0x3F04, 0x8C93, 0x3E0C, 0x000B, 0x000D, 0xFFF5, 0x0B00, 0x0000, 0x0000, 0xD0EE, 0x3DD0, 0x000D, 0x000D, 0xFFF5, 0x0B00, 0xE0EB, 0x3D60, 0xD0EE, 0x3DD0, 0x000D, 0x000D, 0xFFF5, 0x0B00, 0x8494, 0x3E84, 0xD8A9, 0x3DD8, 0x000C, 0x000D, 0xFFF5, 0x0B00, 0xB6AE, 0x3F36, 0xD8A9, 0x3DD8, 0x000C, 0x000D, 0xFFF5, 0x0B00, 0xC8CD, 0x3F48, 0xD068, 0x3D50, 0x000E, 0x000D, 0xFFF5, 0x0B00, 0xDEDB, 0x3F5E, 0xD8ED, 0x3E58, 0x0005, 0x000D, 0xFFF5, 0x0B00, 0xE0EB, 0x3E60, 0xD0EE, 0x3E50, 0x0005, 0x0010, 0xFFF5, 0x0E00, 0xE6EB, 0x3F66, 0xF16F, 0x3D70, 0x000D, 0x000D, 0xFFF5, 0x0B00, 0x9093, 0x3F10, 0x8C93, 0x3E0C, 0x000B, 0x000D, 0xFFF5, 0x0B00, 0xC0AD, 0x3E40, 0xD068, 0x3D50, 0x0012, 0x000D, 0xFFF5, 0x0B00, 0x9093, 0x3F10, 0xD068, 0x3D50, 0x000E, 0x000D, 0xFFF5, 0x0B00, 0xD8ED, 0x3E58, 0xD0EE, 0x3DD0, 0x000C, 0x000D, 0xFFF5, 0x0B00, 0xC8CD, 0x3F48, 0xD0EE, 0x3DD0, 0x000C, 0x000D, 0xFFF5, 0x0B00, 0xF0E9, 0x3F70, 0x0000, 0x0000, 0x000E, 0x000F, 0xFFF5, 0x0D00, 0x9EA1, 0x3F1E, 0xD068, 0x3D50, 0x000E, 0x000D, 0xFFF5, 0x0B00, 0x9CA2, 0x3F1C, 0x8C93, 0x3E0C, 0x000B, 0x000D, 0xFFF5, 0x0B00, 0xACB0, 0x3F2C, 0xD068, 0x3D50, 0x000E, 0x000D, 0xFFF5, 0x0B00, 0xC4CE, 0x3EC4, 0xD068, 0x3D50, 0x000F, 0x000D, 0xFFF5, 0x0B00, 0xA4B1, 0x3EA4, 0xD068, 0x3D50, 0x000F, 0x000D, 0xFFF5, 0x0B00, 0xC0F0, 0x3DC0, 0xD068, 0x3D50, 0x0017, 0x000D, 0xFFF5, 0x0B00, 0xBABF, 0x3F3A, 0xD068, 0x3D50, 0x000D, 0x000E, 0xFFF5, 0x0C00, 0xE4EB, 0x3EE4, 0xD068, 0x3D50, 0x000F, 0x000D, 0xFFF5, 0x0B00, 0xE4EB, 0x3F64, 0xE0EB, 0x3DE0, 0x000C, 0x000D, 0xFFF5, 0x0B00, 0xF8E8, 0x3E78, 0xF0E9, 0x3E70, 0x0006, 0x0004, 0xFFFC, 0x0906, 0xF8F9, 0x3F78, 0xED0B, 0x3E6C, 0x0006, 0x0004, 0xFFFC, 0x0906, 0xB0AF, 0x3EB0, 0xED0B, 0x3E6C, 0x0008, 0x0004, 0xFFFC, 0x0906, 0x8E93, 0x3F0E, 0xF0E9, 0x3E70, 0x0007, 0x0003, 0xFFFD, 0x0907, 0xF0E9, 0x3EF0, 0xED0B, 0x3E6C, 0x0008, 0x0004, 0xFFFC, 0x0906, 0xF2FA, 0x3F72, 0xED0B, 0x3E6C, 0x0005, 0x0005, 0xFFF5, 0x0400, 0xC4CE, 0x3EC4, 0xC4CE, 0x3E44, 0x000B, 0x0009, 0xFFF9, 0x0B04, 0xC0CF, 0x3EC0, 0x8C93, 0x3E0C, 0x000B, 0x000E, 0xFFF4, 0x0B00, 0x9093, 0x3E90, 0xD0EE, 0x3E50, 0x0009, 0x0009, 0xFFF9, 0x0B04, 0x0000, 0x0000, 0x9C91, 0x3E1C, 0x000B, 0x000C, 0xFFF6, 0x0B01, 0xA4A0, 0x3F24, 0xD0EE, 0x3E50, 0x0009, 0x0009, 0xFFF9, 0x0B04, 0xA8B1, 0x3F28, 0x98B3, 0x3E18, 0x000A, 0x000E, 0xFFF4, 0x0B00, 0xF0E9, 0x3EF0, 0x8C93, 0x3E0C, 0x000C, 0x000C, 0xFFF9, 0x0E04, 0xD8CB, 0x3ED8, 0x8C93, 0x3E0C, 0x000B, 0x000E, 0xFFF4, 0x0B00, 0xC2BD, 0x3F42, 0xD8A9, 0x3DD8, 0x0006, 0x000C, 0xFFF6, 0x0B01, 0xA0B2, 0x3E20, 0xCCCD, 0x3E4C, 0x0006, 0x0010, 0xFFF6, 0x0E01, 0xE0EB, 0x3DE0, 0xD0EE, 0x3DD0, 0x000C, 0x000E, 0xFFF4, 0x0B00, 0xA4B1, 0x3EA4, 0xD0EE, 0x3E50, 0x0006, 0x000D, 0xFFF5, 0x0B00, 0xC0CF, 0x3EC0, 0xD0EE, 0x3DD0, 0x0012, 0x0009, 0xFFF9, 0x0B04, 0x9891, 0x3F18, 0xC0AD, 0x3E40, 0x000C, 0x0009, 0xFFF9, 0x0B04, 0xF8E8, 0x3E78, 0xCCCD, 0x3E4C, 0x000A, 0x0009, 0xFFF9, 0x0B04, 0xF4F9, 0x3F74, 0xF16F, 0x3D70, 0x000B, 0x000D, 0xFFF9, 0x0E04, 0xD0EE, 0x3E50, 0x9C91, 0x3E1C, 0x000A, 0x000D, 0xFFF9, 0x0E04, 0xA0F5, 0x3D20, 0xD0EE, 0x3E50, 0x000A, 0x0009, 0xFFF9, 0x0B04, 0xBEBE, 0x3F3E, 0xD0EE, 0x3E50, 0x0009, 0x0009, 0xFFF9, 0x0B04, 0x0000, 0x0000, 0xCCCD, 0x3E4C, 0x0009, 0x000B, 0xFFF7, 0x0B02, 0xB2AF, 0x3F32, 0xC8AC, 0x3E48, 0x000B, 0x0009, 0xFFF9, 0x0B04, 0x8284, 0x3F02, 0xC0AD, 0x3E40, 0x000C, 0x0009, 0xFFF9, 0x0B04, 0x8484, 0x3F04, 0xD0EE, 0x3DD0, 0x0012, 0x0009, 0xFFF9, 0x0B04, 0xF2FA, 0x3F72, 0xC8AC, 0x3E48, 0x000B, 0x0009, 0xFFF9, 0x0B04, 0xA0B2, 0x3E20, 0x98B3, 0x3E18, 0x000B, 0x000D, 0xFFF9, 0x0E04, 0xE8EA, 0x3F68, 0xA490, 0x3E24, 0x0008, 0x0009, 0xFFF9, 0x0B04, 0xDEDB, 0x3F5E, 0xA490, 0x3E24, 0x0009, 0x000D, 0xFFF9, 0x0E04, 0x8284, 0x3F02, 0xE4C9, 0x3E64, 0x0006, 0x0009, 0xFFF9, 0x0B04, 0xC2BD, 0x3F42, 0x9C91, 0x3E1C, 0x000A, 0x000D, 0xFFF6, 0x0C01, 0x8073, 0x3E00, 0xE0EB, 0x3E60, 0x0005, 0x000C, 0xFFF6, 0x0B01, 0x0000, 0x0000, 0xD068, 0x3D50, 0x0018, 0x000D, 0xFFF6, 0x0B06, 0xC0BE, 0x3F40, 0x0000, 0x0000, 0x0018, 0x000D, 0xFFF6, 0x0B06, 0xA8B1, 0x3F28, 0x0000, 0x0000, 0x0018, 0x000D, 0xFFF6, 0x0B06, 0xD8DC, 0x3F58, 0x0000, 0x0000, 0x0018, 0x000D, 0xFFF6, 0x0B06, 0x9692, 0x3F16, 0xD0EE, 0x3DD0, 0x0012, 0x0009, 0xFFF8, 0x0B06, 0xA8B1, 0x3F28, 0xD0EE, 0x3DD0, 0x000D, 0x000C, 0xFFF7, 0x0B06, 0xE4EB, 0x3EE4, 0xD0EE, 0x3DD0, 0x0012, 0x0009, 0xFFF8, 0x0B06, 0xF0E9, 0x3F70, 0xE0EB, 0x3DE0, 0x000D, 0x000C, 0xFFF7, 0x0B06, 0x0000, 0x0000, 0x0000, 0x0000, 0x0029, 0x000D, 0xFFF6, 0x0B06, 0xA8B1, 0x3EA8, 0x0000, 0x0000, 0x0029, 0x000D, 0xFFF6, 0x0B06, 0xA8B1, 0x3E28, 0x0000, 0x0000, 0x0029, 0x000D, 0xFFF6, 0x0B06, 0xFD09, 0x3EFC, 0x0000, 0x0000, 0x0029, 0x000D, 0xFFF6, 0x0B06
};

BYTE byte_50A0FD[80] =
{
	0x80, 0x80, 0x00, 0x80, 0x80, 0x80, 0x00, 0x80, 0x80, 0x80, 0x00, 0x80, 0x80, 0x80, 0x00, 0x80, 0x80, 0x80, 0x00, 0x80, 0x80, 0x80, 0x00, 0x80, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0xA0, 0x00, 0x00, 0x00, 0x50, 0x00, 0x80, 0x80, 0x80, 0x00, 0x10, 0x10, 0x10, 0x00, 0xC0, 0x80, 0x40, 0x00, 0x40, 0x10, 0x00, 0x00, 0x10, 0x10, 0x10, 0x00, 0x80, 0x80, 0x80, 0x00, 0xE0, 0xC0, 0x00, 0x00, 0x40, 0x20, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x01
};
WORD word_E4DEC8[1908];
DWORD dword_E4DEA8;
DWORD dword_E4DC40;
DWORD dword_E4DEA4;



//DEFINE_GUID(IID_IDirect3D3, 0xBB223240, 0xE72B, 0x11D0, 0xA9, 0xB4, 0x00, 0xAA, 0x00, 0xC0, 0x99, 0x3E);

HWND SendMsg(HWND hWnd, LPARAM lParam)
{
	HWND result; // eax@1

	do
	{
		result = (HWND)PostMessageA(hWnd, dword_E4ACA8, 0, lParam);
		if (result)
			break;
		result = FindWindowA(ClassName, WindowName);
	} while (result);
	return result;
}

int WinProcMsg()
{
	int result; // eax@4
	struct tagMSG Msg; // [sp+10h] [bp-1Ch]@2

	Log(2, "WinProcMsg");
	do
	{
		GetMessageA(&Msg, 0, 0, 0);
		if (!TranslateAcceleratorA(hWnd, ptr_ctx->hAccTable, &Msg))
		{
			TranslateMessage(&Msg);
			DispatchMessageA(&Msg);
		}
		result = dword_876C48;
	} while (!dword_876C48 && Msg.message != 18);
	return result;
}

char *WinProcessCommandLine(char *a1)
{
	S_Warn("[WinProcessCommandLine] - Unimplemented!\n");
#if 0
	int(__cdecl **v1)(int); // esi@1
	unsigned int v2; // esi@3
	int(__cdecl **v3)(int); // esi@7
	char *result; // eax@8
	const char *v5; // edx@8
	unsigned int v6; // eax@10
	unsigned int v7; // kr14_4@10
	const char *v8; // edx@14
	unsigned int v9; // eax@14
	unsigned int v10; // kr1C_4@14
	size_t v11; // eax@17
	unsigned int v12; // kr24_4@17
	char v13[4]; // [sp+Ch] [bp-14h]@8
	int v14; // [sp+10h] [bp-10h]@8
	int v15; // [sp+14h] [bp-Ch]@8
	int v16; // [sp+18h] [bp-8h]@8
	int v17; // [sp+1Ch] [bp-4h]@8

	Log(2, "WinProcessCommandLine");
	v1 = &off_51184D;
	do
	{
		(*v1)((int)a_init);
		v1 = (int(__cdecl **)(int))((char *)v1 + 45);
	} while ((signed int)v1 < (signed int)&unk_5118A7);
	v2 = 0;
	if (strlen(a1) != 0)
	{
		do
		{
			if (toupper(a1[v2]))
				a1[v2] = toupper(a1[v2]);
			++v2;
		} while (v2 < strlen(a1));
	}
	v3 = &off_51184D;
	do
	{
		*(_DWORD *)v13 = 0;
		v14 = 0;
		v15 = 0;
		v16 = 0;
		v17 = 0;
		result = strstr(a1, (const char *)v3 - 21);
		v5 = result;
		if (result)
		{
			if (*((_BYTE *)v3 - 1))
			{
				v6 = 0;
				v7 = strlen(v5) + 1;
				if (v7 != 1)
				{
					while (*v5 != 61)
					{
						++v6;
						++v5;
						if (v6 >= v7 - 1)
						{
							result = (char *)(*v3)(v13);
							goto LABEL_23;
						}
					}
					v8 = v5 + 1;
					v9 = 0;
					v10 = strlen(v8) + 1;
					if (v10 != 1)
					{
						do
						{
							if (*v8 != 32)
								break;
							++v9;
							++v8;
						} while (v9 < v10 - 1);
					}
					v11 = 0;
					v12 = strlen(v8) + 1;
					if (v12 != 1)
					{
						do
						{
							if (v8[v11] == 32)
								break;
							++v11;
						} while (v11 < v12 - 1);
					}
					strncpy(v13, v8, v11);
				}
				result = (char *)(*v3)(v13);
			}
			else
			{
				result = (char *)(*v3)(0);
			}
		}
	LABEL_23:
		v3 = (int(__cdecl **)(int))((char *)v3 + 45);
	} while ((signed int)v3 < (signed int)&unk_5118A7);
	return result;
#endif
	return 0;
}

char WinRunCheck(const CHAR *lpName, const CHAR *lpClassName, HANDLE *mutex)
{
	HWND v3; // eax@2
	char result; // al@4

	Log(2, "WinRunCheck");
	*mutex = CreateMutexA(0, 1, lpName);
	if (GetLastError() == 183)
	{
		v3 = FindWindowA(lpClassName, lpName);
		if (v3)
			SendMessageA(v3, WM_ACTIVATE, 0, 0);
		result = 1;
	}
	else
	{
		result = 0;
	}
	return result;
}

HWND WinClose()
{
	S_Warn("[WinClose] - Unimplemented!\n");
	return NULL;
}

void InitConsole()
{
	AllocConsole();

	HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
	int hCrt = _open_osfhandle((long)handle_out, _O_TEXT);
	FILE* hf_out = _fdopen(hCrt, "w");
	setvbuf(hf_out, NULL, _IONBF, 1);
	*stdout = *hf_out;
	setbuf(stdout, NULL);

	HANDLE handle_in = GetStdHandle(STD_INPUT_HANDLE);
	hCrt = _open_osfhandle((long)handle_in, _O_TEXT);
	FILE* hf_in = _fdopen(hCrt, "r");
	setvbuf(hf_in, NULL, _IONBF, 128);
	*stdin = *hf_in;

	freopen("CONOUT$", "w", stdout);
	freopen("CONIN$", "r", stdin);
}

HANDLE sub_4DEA40(LPCSTR lpName)
{
	return OpenFileMappingA(6u, 1, lpName);
}

LPVOID sub_4DEA20(HANDLE hFileMappingObject)
{
	return MapViewOfFile(hFileMappingObject, 6u, 0, 0, 0x100000u);
}

int sub_4DEA50(char* a1, LPARAM lParam, int a3)
{
	HWND v3; // ebx@1
	char *v4; // edx@2
	int result; // eax@3

	v3 = FindWindowA(ClassName, WindowName);
	if (v3 && (dword_E4ACA4 = sub_4DEA40("DBLOGMAPMEM"), (v4 = (char *)sub_4DEA20(dword_E4ACA4)) != 0))
	{
		strcpy(v4, a1);
		result = SendMessageA(v3, dword_E4ACB0, (unsigned __int8)a3, lParam);
	}
	else
	{
		result = (int)a1;
	}
	return result;
}

signed int sub_4D22D0()
{
	/*signed int result; // eax@1
	int v6; // [sp+Ch] [bp-20h]@1
	CPPEH_RECORD ms_exc; // [sp+14h] [bp-18h]@1

	v6 = 1;
	_EAX = 1;
	__asm { cpuid }
	ms_exc.registration.TryLevel = -1;
	result = 1;
	if ((unsigned int)&unk_800000 & _EDX)
	{
		_m_femms();
		ms_exc.registration.TryLevel = -1;
	}
	else
	{
		result = 0;
	}
	return result;*/
	return 0; // TODO IF IT DOESNT WORK PUT 1 HERE
}

char sub_4DEC40(char a1)
{
	LSTATUS v1; // eax@1
	HKEY phkResult; // [sp+4h] [bp-464h]@2
	DWORD Type; // [sp+8h] [bp-460h]@4
	DWORD cbData; // [sp+Ch] [bp-45Ch]@4
	DWORD dwDisposition; // [sp+10h] [bp-458h]@2
	struct _PROCESS_INFORMATION ProcessInformation; // [sp+14h] [bp-454h]@4
	struct _STARTUPINFOA StartupInfo; // [sp+24h] [bp-444h]@4
	BYTE Data[0x400]; // [sp+68h] [bp-400h]@4

	dword_E4ACA8 = RegisterWindowMessageA(String);
	dword_E4ACAC = RegisterWindowMessageA("UM_DBCLEARLOG");
	dword_E4ACB0 = RegisterWindowMessageA("UM_DBDEFTYPE");
	Msg = RegisterWindowMessageA("UM_DBCOMMAND");
	LOBYTE(v1) = a1;
	if (a1 & 1)
	{
		v1 = RegCreateKeyExA(HKEY_LOCAL_MACHINE, SubKey, 0, 0, 0, 0xF003Fu, 0, &phkResult, &dwDisposition);
		if (!v1 && dwDisposition == 2)
		{
			memset(&Data, 0, 0x400u);
			Type = 1;
			cbData = 1024;
			RegQueryValueExA(phkResult, ValueName, 0, &Type, Data, &cbData);
			memset(&StartupInfo, 0, sizeof(StartupInfo));
			StartupInfo.cb = 68;
			if (!CreateProcessA(0, (LPSTR)Data, 0, 0, 0, 0, 0, 0, &StartupInfo, &ProcessInformation))
				GetLastError();
			WaitForInputIdle(ProcessInformation.hProcess, 0xFFFFFFFF);
			LOBYTE(v1) = RegCloseKey(phkResult);
		}
	}
	return v1;
}

char FindCDDrive()
{
	unsigned int v0; // ebx@1
	HANDLE v1; // eax@4
	char result; // al@6
	CHAR String1[8]; // [sp+Ch] [bp-18h]@1
	CHAR FileName[14]; // [sp+14h] [bp-10h]@1

	strcpy(FileName, "c:\\script.dat");
	v0 = GetLogicalDrives();
	GameDrive = 'A';
	lstrcpyA(String1, "A:\\");
	if (v0)
	{
		while (1)
		{
			if (v0 & 1)
			{
				String1[0] = GameDrive;
				if (GetDriveTypeA(String1) == 3 || GetDriveTypeA(String1) == 5)
				{
					FileName[0] = GameDrive;
					v1 = CreateFileA(FileName, 0x80000000, 0, 0, 3u, 0x80u, 0);
					if (v1 != (HANDLE)-1)
						break;
				}
			}
			v0 >>= 1;
			++GameDrive;
			if (!v0)
				goto LABEL_6;
		}
		CloseHandle(v1);
		result = 1;
	}
	else
	{
	LABEL_6:
		result = 0;
	}
	return result;
}


signed int DXToggleFullScreen()
{
	struct DISPLAYMODE* v0; // eax@2
	signed int result; // eax@2
	struct DISPLAYMODE* v2; // eax@3

	Log(2, "DXToggleFullScreen");
	if (ptr_ctx->flags & 2)
	{
		Log(5, "Switching To Full Screen");
		ptr_ctx->flags ^= 2u;
		ptr_ctx->flags |= 0x41u;
		ptr_ctx->flags |= 0x40u;
		ptr_ctx->d3d->lpVtbl->EvictManagedTextures(ptr_ctx->d3d);
		v0 = &ptr_ctx->graphicsAdapters[ptr_ctx->curGfxAdapt]
			.D3DInfo[ptr_ctx->curAccelAdapt]
			.DisplayMode[ptr_ctx->curDispMode];
		DXCreate(
			v0->w,
			v0->h,
			v0->bpp,
			ptr_ctx->flags,
			ptr_ctx,
			ptr_ctx->GhWnd,
			ptr_ctx->dxWndStyle);
		ptr_ctx->flags ^= 0x40u;
		result = 1;
	}
	else
	{
		Log(5, "Switching To A Window");
		ptr_ctx->flags ^= 1u;
		ptr_ctx->flags |= 0x42u;
		ptr_ctx->d3d->lpVtbl->EvictManagedTextures(ptr_ctx->d3d);
		v2 = &ptr_ctx->graphicsAdapters[ptr_ctx->curGfxAdapt]
			.D3DInfo[ptr_ctx->curAccelAdapt]
		.DisplayMode[ptr_ctx->curDispMode];
		DXCreate(
			v2->w,
			v2->h,
			v2->bpp,
			ptr_ctx->flags,
			ptr_ctx,
			ptr_ctx->GhWnd,
			ptr_ctx->dxWndStyle);
		ptr_ctx->flags ^= 0x40u;
		result = 1;
	}
	return result;
}

int HWInitialise()
{
	Log(2, "HWInitialise");
	ptr_ctx->d3d_dev->lpVtbl->SetTextureStageState(ptr_ctx->d3d_dev, 0, D3DTSS_COLOROP, D3DTOP_DISABLE);
	ptr_ctx->d3d_dev->lpVtbl->SetTextureStageState(ptr_ctx->d3d_dev, 1, D3DTSS_COLOROP, D3DTOP_DISABLE);
	ptr_ctx->d3d_dev->lpVtbl->SetTextureStageState(ptr_ctx->d3d_dev, 2, D3DTSS_COLOROP, D3DTOP_DISABLE);
	ptr_ctx->d3d_dev->lpVtbl->SetTextureStageState(ptr_ctx->d3d_dev, 3, D3DTSS_COLOROP, D3DTOP_DISABLE);
	ptr_ctx->d3d_dev->lpVtbl->SetTextureStageState(ptr_ctx->d3d_dev, 4, D3DTSS_COLOROP, D3DTOP_DISABLE);
	ptr_ctx->d3d_dev->lpVtbl->SetTextureStageState(ptr_ctx->d3d_dev, 5, D3DTSS_COLOROP, D3DTOP_DISABLE);
	ptr_ctx->d3d_dev->lpVtbl->SetTextureStageState(ptr_ctx->d3d_dev, 6, D3DTSS_COLOROP, D3DTOP_DISABLE);
	ptr_ctx->d3d_dev->lpVtbl->SetTextureStageState(ptr_ctx->d3d_dev, 7, D3DTSS_COLOROP, D3DTOP_DISABLE);
	ptr_ctx->d3d_dev->lpVtbl->SetTextureStageState(ptr_ctx->d3d_dev, 0, D3DTSS_TEXCOORDINDEX, 0);

	if (ptr_ctx->opt_Filter)
	{
		ptr_ctx->d3d_dev->lpVtbl->SetTextureStageState(ptr_ctx->d3d_dev, 0, D3DTSS_MINFILTER, D3DTFN_LINEAR);
		ptr_ctx->d3d_dev->lpVtbl->SetTextureStageState(ptr_ctx->d3d_dev, 0, D3DTSS_MIPFILTER, D3DTFP_NONE);
		ptr_ctx->d3d_dev->lpVtbl->SetTextureStageState(ptr_ctx->d3d_dev, 0, D3DTSS_MAGFILTER, D3DTFG_LINEAR);
	}
	else
	{
		ptr_ctx->d3d_dev->lpVtbl->SetTextureStageState(ptr_ctx->d3d_dev, 0, D3DTSS_MAGFILTER, D3DTFG_POINT);
		ptr_ctx->d3d_dev->lpVtbl->SetTextureStageState(ptr_ctx->d3d_dev, 0, D3DTSS_MINFILTER, D3DTFN_POINT);
		ptr_ctx->d3d_dev->lpVtbl->SetTextureStageState(ptr_ctx->d3d_dev, 0, D3DTSS_MIPFILTER, D3DTFP_NONE);
	}

	ptr_ctx->d3d_dev->lpVtbl->SetTextureStageState(ptr_ctx->d3d_dev, 0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	ptr_ctx->d3d_dev->lpVtbl->SetTextureStageState(ptr_ctx->d3d_dev, 0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
	ptr_ctx->d3d_dev->lpVtbl->SetTextureStageState(ptr_ctx->d3d_dev, 0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	ptr_ctx->d3d_dev->lpVtbl->SetTextureStageState(ptr_ctx->d3d_dev, 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	ptr_ctx->d3d_dev->lpVtbl->SetTextureStageState(ptr_ctx->d3d_dev, 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	ptr_ctx->d3d_dev->lpVtbl->SetTextureStageState(ptr_ctx->d3d_dev, 0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
	ptr_ctx->d3d_dev->lpVtbl->SetTextureStageState(ptr_ctx->d3d_dev, 0, D3DTSS_TEXCOORDINDEX, 0);


	ptr_ctx->d3d_dev->lpVtbl->SetRenderState(ptr_ctx->d3d_dev, D3DRENDERSTATE_ALPHABLENDENABLE, FALSE);
	ptr_ctx->d3d_dev->lpVtbl->SetRenderState(ptr_ctx->d3d_dev, D3DRENDERSTATE_SPECULARENABLE, TRUE);
	ptr_ctx->d3d_dev->lpVtbl->SetRenderState(ptr_ctx->d3d_dev, D3DRENDERSTATE_CULLMODE, D3DCULL_NONE);
	sub_40179E(ptr_ctx->d3d_dev->lpVtbl->SetRenderState(ptr_ctx->d3d_dev, D3DRENDERSTATE_ZENABLE, TRUE));
	sub_40179E(ptr_ctx->d3d_dev->lpVtbl->SetRenderState(ptr_ctx->d3d_dev, D3DRENDERSTATE_ZWRITEENABLE, TRUE));
	sub_40179E(ptr_ctx->d3d_dev->lpVtbl->SetRenderState(ptr_ctx->d3d_dev, D3DRENDERSTATE_TEXTUREPERSPECTIVE, TRUE));
	ptr_ctx->d3d_dev->lpVtbl->SetRenderState(ptr_ctx->d3d_dev, D3DRENDERSTATE_TEXTUREMAPBLEND, D3DTBLEND_MODULATEALPHA);
	ptr_ctx->d3d_dev->lpVtbl->SetRenderState(ptr_ctx->d3d_dev, D3DRENDERSTATE_FILLMODE, D3DFILL_SOLID);
	ptr_ctx->d3d_dev->lpVtbl->SetRenderState(ptr_ctx->d3d_dev, D3DRENDERSTATE_DITHERENABLE, TRUE);
	ptr_ctx->d3d_dev->lpVtbl->SetRenderState(ptr_ctx->d3d_dev, D3DRENDERSTATE_ALPHAREF, 0);
	ptr_ctx->d3d_dev->lpVtbl->SetRenderState(ptr_ctx->d3d_dev, D3DRENDERSTATE_ALPHAFUNC, D3DCMP_NOTEQUAL);
	ptr_ctx->d3d_dev->lpVtbl->SetRenderState(ptr_ctx->d3d_dev, D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA);
	ptr_ctx->d3d_dev->lpVtbl->SetRenderState(ptr_ctx->d3d_dev, D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA);
	ptr_ctx->d3d_dev->lpVtbl->SetRenderState(ptr_ctx->d3d_dev, D3DRENDERSTATE_ALPHATESTENABLE, FALSE);


	sub_40179E(ptr_ctx->d3d_dev->lpVtbl->SetLightState(ptr_ctx->d3d_dev, D3DLIGHTSTATE_AMBIENT, 0));
	sub_40179E(ptr_ctx->d3d_dev->lpVtbl->SetLightState(ptr_ctx->d3d_dev, D3DLIGHTSTATE_COLORVERTEX, 0));
	sub_40179E(ptr_ctx->d3d_dev->lpVtbl->SetLightState(ptr_ctx->d3d_dev, D3DLIGHTSTATE_COLORMODEL, D3DCOLOR_RGB));
	sub_40179E(ptr_ctx->d3d_dev->lpVtbl->SetLightState(ptr_ctx->d3d_dev, D3DLIGHTSTATE_FOGMODE, D3DFOG_LINEAR));
	sub_40179E(ptr_ctx->d3d_dev->lpVtbl->SetLightState(ptr_ctx->d3d_dev, D3DLIGHTSTATE_FOGSTART, LODWORD(flt_50A438)));
	sub_40179E(ptr_ctx->d3d_dev->lpVtbl->SetLightState(ptr_ctx->d3d_dev, D3DLIGHTSTATE_FOGEND, LODWORD(flt_50A43C)));


	ptr_ctx->d3d_dev->lpVtbl->SetRenderState(ptr_ctx->d3d_dev, D3DRENDERSTATE_FOGCOLOR, RGBA_MAKE(0, 0, 0, 255));
	return ptr_ctx->d3d_dev->lpVtbl->SetRenderState(ptr_ctx->d3d_dev, D3DRENDERSTATE_FOGENABLE, TRUE);
}

void __cdecl sub_401E47(LPD3DMATRIX a1)
{
	a1->_11 = 1.0;
	a1->_12 = 0.0;
	a1->_13 = 0.0;
	a1->_14 = 0.0;
	a1->_21 = 0.0;
	a1->_22 = 1.0;
	a1->_23 = 0.0;
	a1->_24 = 0.0;
	a1->_31 = 0.0;
	a1->_32 = 0.0;
	a1->_33 = 1.0;
	a1->_34 = 0.0;
	a1->_41 = 0.0;
	a1->_42 = 0.0;
	a1->_43 = 0.0;
	a1->_44 = 1.0;
}

void sub_401D84()
{
	sub_401E47(&transform_world);
	sub_401E47(&transform_projection);
	transform_projection._22 = -1.0;
	sub_40179E(ptr_ctx->d3d_dev->lpVtbl->SetTransform(ptr_ctx->d3d_dev, D3DTRANSFORMSTATE_WORLD, &transform_world));
	sub_40179E(ptr_ctx->d3d_dev->lpVtbl->SetTransform(ptr_ctx->d3d_dev, D3DTRANSFORMSTATE_PROJECTION, &transform_projection));
}

void sub_402BAD()
{
	int* v0 = phd_mxptr;
	sub_401E47(&transform_view);
	transform_view._11 = (double)v0[0] / 16384.0;
	transform_view._12 = (double)v0[4] / 16384.0;
	transform_view._13 = (double)v0[8] / 16384.0;
	transform_view._21 = (double)v0[1] / 16384.0;
	transform_view._22 = (double)v0[5] / 16384.0;
	transform_view._23 = (double)v0[9] / 16384.0;
	transform_view._31 = (double)v0[2] / 16384.0;
	transform_view._32 = (double)v0[6] / 16384.0;
	transform_view._33 = (double)v0[10] / 16384.0;
	transform_view._41 = (double)v0[3] / 16384.0;
	transform_view._42 = (double)v0[7] / 16384.0;
	transform_view._43 = (double)v0[11] / 16384.0;
}

HMODULE GetKernel32()
{
	return GetModuleHandleA("kernel32.dll");
}

FARPROC sub_4DB931(HMODULE a1)
{
	return GetProcAddress(a1, "Sleep");
}

FARPROC GetSleepFunc()
{
	HMODULE v0; // eax@1

	v0 = GetKernel32();
	return sub_4DB931(v0);
}

void Sleep1ms()
{
	FARPROC v0; // eax@1

	v0 = GetSleepFunc();
	((void(__stdcall *)(_DWORD))v0)(1);
}

void __fastcall sub_4DA111(_DWORD *a1)
{
	do
	{
		Sleep1ms();
	} while (*a1);
}

void __fastcall sub_4D8F51(_DWORD *a1)
{
	do
	{
		Sleep1ms();
	} while (!*a1);
}

void sub_4D3211()
{
	sub_4DA111(&ptr_ctx->isInScene);
}

void sub_4D31D1()
{
	sub_4D8F51(&ptr_ctx->isInScene);
}

void __cdecl sub_402563(signed int a1, signed int a2)
{
	double v3; // st7@1
	double v4; // st7@1

	dword_55D21C = a1;
	dword_55D1F4 = a2;
	flt_55D228 = (double)a2;
	flt_55D24C = (double)a1;
	flt_55D238 = flt_55D268 / flt_55D24C;
	flt_51D158 = (double)a1 / 16384.0;
	flt_55DA38 = (double)a2 / 16384.0;
	flt_55D668 = flt_51D15C / flt_51D158;
	flt_55D25C = flt_50A444 / flt_51D158;
	v3 = flt_55DA38 * flt_51D158 * 0.99000001 / (flt_51D158 - flt_55DA38);
	flt_51D150 = 1 / 200.0 - v3 / flt_51D158;
	v4 = -v3;
	flt_51D154 = v4;
	flt_55D220 = v4 / flt_50A444;
}

int __cdecl InitWindow(int x, int y, signed int width, signed int height, int a5, int a6, int fov_deg)
{
	int result; // eax@1

	window_width = width;
	window_width_minus_1 = width - 1;
	window_height = height;
	window_pos_x = x;
	window_height_minus_1 = height - 1;
	window_pos_y = y;
	middle_width = width / 2;
	middle_height = height / 2;
	dword_55D21C = a5 << 14;
	middle_width_flt = (double)(width / 2);
	dword_55D1F4 = a6 << 14;
	middle_height_flt = (double)(height / 2);
	AlterFOV(ANGLE(fov_deg));
	sub_402563(dword_55D21C, dword_55D1F4);
	flt_55D250 = (double)window_pos_x;
	phd_right = window_width_minus_1;
	result = window_width_minus_1 + 1;
	phd_bottom = window_height_minus_1;
	flt_55D664 = (double)window_pos_y;
	phd_top = y;
	phd_left = x;
	flt_51D160 = (double)result;
	phd_mxptr = other_matrix_shit;
	flt_55DA34 = (double)(window_height_minus_1 + 1);
	flt_51D14C = flt_51D160 - flt_55D250;
	flt_55DA40 = flt_55DA34 - flt_55D664;
	return result;
}


int __cdecl sub_40198D(int a1, int *a2, int *a3)
{
	int v3; // ebp@1
	int v4; // ebx@1
	int v5; // esi@1
	int v6; // eax@2
	int v7; // edi@5
	int v8; // ecx@8
	int result; // eax@34

	v3 = 0;
	v4 = 0;
	v5 = 0;
	if (BYTE2(a1) - 128 <= 0)
	{
		v6 = 2 * BYTE2(a1);
	}
	else
	{
		v5 = (BYTE2(a1) - 128) >> 1;
		v6 = 255;
	}
	if (BYTE1(a1) - 128 <= 0)
	{
		v7 = 2 * BYTE1(a1);
	}
	else
	{
		v4 = (BYTE1(a1) - 128) >> 1;
		v7 = 255;
	}
	if ((unsigned __int8)a1 - 128 <= 0)
	{
		v8 = 2 * (unsigned __int8)a1;
	}
	else
	{
		v3 = ((unsigned __int8)a1 - 128) >> 1;
		v8 = 255;
	}
	if (v6 <= 255)
	{
		if (v6 < 0)
			v6 = 0;
	}
	else
	{
		v6 = 255;
	}
	if (v7 <= 255)
	{
		if (v7 < 0)
			v7 = 0;
	}
	else
	{
		v7 = 255;
	}
	if (v8 <= 255)
	{
		if (v8 < 0)
			v8 = 0;
	}
	else
	{
		v8 = 255;
	}
	if (v5 <= 255)
	{
		if (v5 < 0)
			v5 = 0;
	}
	else
	{
		v5 = 255;
	}
	if (v4 <= 255)
	{
		if (v4 < 0)
			v4 = 0;
	}
	else
	{
		v4 = 255;
	}
	if (v3 <= 255)
	{
		if (v3 < 0)
			v3 = 0;
	}
	else
	{
		v3 = 255;
	}
	result = v8 | ((v7 | (v6 << 8)) << 8);
	*a2 = result;
	*a3 = v3 | ((v4 | (v5 << 8)) << 8);
	return result;
}

signed __int64 InitFont_old()
{
	BYTE *v0; // edi@1
	BYTE v1; // ST3C_1@2
	BYTE v2; // ST38_1@2
	BYTE v3; // al@2
	unsigned __int8 v4; // ST40_1@2
	BYTE v5; // dl@2
	signed int v6; // ebx@2
	int v7; // ebp@2
	signed int v8; // ecx@2
	char *v9; // esi@2
	signed int v10; // eax@2
	int v11; // eax@3
	int v12; // edx@3
	int v13; // ecx@3
	signed int v14; // eax@9
	char v15; // dh@9
	signed int v16; // eax@9
	__int16 v17; // dx@9
	int v18; // eax@9
	BOOL v19; // zf@9
	signed int v20; // esi@11
	signed int v21; // eax@12
	__int16 v22; // dx@13
	__int16 v23; // cx@13
	double v24; // st7@15
	signed __int64 v25; // rax@16
	signed __int64 result; // rax@17
	signed int v27; // [sp+10h] [bp-50h]@2
	signed int v28; // [sp+14h] [bp-4Ch]@2
	signed int v29; // [sp+18h] [bp-48h]@2
	signed int v30; // [sp+1Ch] [bp-44h]@2
	int v31; // [sp+20h] [bp-40h]@2
	int v32; // [sp+24h] [bp-3Ch]@2
	char *v33; // [sp+28h] [bp-38h]@1
	signed int v34; // [sp+28h] [bp-38h]@2
	int v35; // [sp+44h] [bp-1Ch]@9
	int v36; // [sp+48h] [bp-18h]@9
	int v37; // [sp+4Ch] [bp-14h]@2
	int v38; // [sp+50h] [bp-10h]@2
	int v39; // [sp+54h] [bp-Ch]@2
	float v40; // [sp+58h] [bp-8h]@2
	int v41; // [sp+5Ch] [bp-4h]@2

	v33 = (char *)&word_E4DEC8[844] + 1;
	v0 = byte_50A0FD;
	do
	{
		v1 = *v0;
		v2 = v0[1];
		v3 = v0[5];
		v4 = *(v0 - 1);
		v5 = v0[3];
		v38 = (unsigned __int8)v0[4];
		v37 = (unsigned __int8)v3;
		v41 = -v4;
		LODWORD(v40) = -(unsigned __int8)v1;
		v6 = 0;
		v7 = (unsigned __int8)v5;
		v8 = 16 * (unsigned __int8)v1;
		v39 = -(unsigned __int8)v2;
		v9 = v33;
		v10 = 16 * (unsigned __int8)v2;
		v29 = 0;
		v27 = 0;
		v30 = 0;
		v28 = 16 * v4;
		v32 = 16 * (unsigned __int8)v1;
		v31 = 16 * (unsigned __int8)v2;
		v34 = 16;
		do
		{
			v11 = (v6 >> 4) + (v10 >> 4);
			v12 = (v27 >> 4) + (v8 >> 4);
			v13 = (v29 >> 4) + (v28 >> 4);
			if ((unsigned __int16)v11 > 0xFFu)
				LOWORD(v11) = 255;
			if ((unsigned __int16)v12 > 0xFFu)
				LOWORD(v12) = 255;
			if ((unsigned __int16)v13 > 0xFFu)
				LOWORD(v13) = 255;
			sub_40198D((unsigned __int16)v13 | (((unsigned __int16)v12 | ((unsigned __int16)v11 << 8)) << 8), &v35, &v36);
			v14 = v35;
			v15 = BYTE1(v35);
			v9[1] = v35;
			*v9 = v15;
			*(v9 - 1) = v14 >> 16;
			v16 = v36;
			v17 = v36;
			v9[2] = -1;
			v9[5] = v17;
			v9[4] = HIBYTE(v17);
			v9[3] = v16 >> 16;
			v6 = v37 + v30;
			v18 = v38;
			v9[6] = -1;
			v27 += v18;
			v10 = v39 + v31;
			v8 = LODWORD(v40) + v32;
			v28 += v41;
			v9 += 8;
			v29 += v7;
			v19 = v34 == 1;
			v30 = v6;
			v31 += v39;
			v32 += LODWORD(v40);
			--v34;
		} while (!v19);
		v0 += 8;
		v33 = v9;
	} while (v0 < &byte_50A0FD[80] + 1);
	v20 = 0;
	if (*(_DWORD *)&byte_50A0FD[79])
	{
		v21 = 0;
		do
		{
			v22 = word_507AC0[v21];
			word_E4DEC8[v21 + 1] = word_507AC0[v21 + 1];
			v23 = word_507AC0[v21 + 2];
			word_E4DEC8[v21] = v22;
			word_E4DEC8[v21 + 2] = v23;
			v21 += 8;
		} while (v21 < 848);
		*(_DWORD *)&byte_50A0FD[79] = 0;
	}
	v41 = window_height_minus_1;
	v40 = (double)window_width_minus_1;
	v24 = (double)window_height_minus_1;
	do
	{
		v41 = word_E4DEC8[v20 + 1];
		v25 = (signed __int64)((double)v41 * v24 / 240.0);
		v41 = word_E4DEC8[v20];
		word_507AC0[v20 + 1] = v25;
		word_507AC0[v20] = (signed __int64)((double)v41 * v40 / 512.0);
		v41 = word_E4DEC8[v20 + 2];
		word_507AC0[v20 + 2] = (signed __int64)((double)v41 * v24 / 240.0);
		v20 += 8;
	} while (v20 < 848);
	result = (signed __int64)(v24 * 0.058333334);
	dword_E4DEA8 = result;
	dword_E4DC40 = result;
	dword_E4DEA4 = 6;
	return result;
}

void __cdecl sub_4018AC(signed int param)
{
	signed int v1; // esi@1
	int v2; // edi@10
	int v3; // ebx@11
	int v4; // eax@11
	int v5; // ecx@11
	struct DISPLAYMODE* v7; // ecx@13
	int v8; // ecx@16
	struct DISPLAYMODE* v9; // ecx@17
	struct DISPLAYMODE* v10; // ebx@27
	struct DISPLAYMODE* v11; // ebx@29
	HCURSOR v12; // eax@41
	int v13; // [sp+Ch] [bp+4h]@10

	v1 = param;
	if (param == 8)
	{
		if (!ptr_ctx->byte_D9AC2B
			&& ptr_ctx->graphicsAdapters[ptr_ctx->curGfxAdapt].DDCaps.dwCaps2 & DDSCAPS2_STEREOSURFACELEFT
			&& !dword_874968)
		{
			Log(6, "KA_ALTENTER");
			Log(5, "HangGameThread");
			while (ptr_ctx->isInScene)
				;
			ptr_ctx->dword_D9ABFD = 1;
			while (!ptr_ctx->isInScene)
				;
			SuspendThread(hThread);
			Log(5, "Game Thread Suspended");
			//j_nullsub_22();
			DXToggleFullScreen();
			HWInitialise();
			//j_nullsub_24();
			sub_401D84();
			sub_402BAD();
			ResumeThread(hThread);
			ptr_ctx->dword_D9ABFD = 0;
			Log(5, "Game Thread Resumed");
			if (ptr_ctx->flags & 1)
			{
				SetCursor(0);
				ShowCursor(0);
			}
			else
			{
				v12 = LoadCursorA(hinst, (LPCSTR)IDC_ARROW);
				SetCursor(v12);
				ShowCursor(1);
			}
		}
	}
	else if (param > 40000 && param <= 40002 && !dword_874968 && !ptr_ctx->byte_D9AC2B)
	{
		Log(5, "Change Video Mode");
		Log(5, "HangGameThread");
		if (ptr_ctx->isInScene)
			sub_4D3211();
		ptr_ctx->dword_D9ABFD = 1;
		if (!ptr_ctx->isInScene)
			sub_4D31D1();
		SuspendThread(hThread);
		Log(5, "Game Thread Suspended");
		v2 = ptr_ctx->curDispMode;
		v13 = ptr_ctx->curDispMode;
		if (v1 == IDR_VKADD)
		{
			v3 = ptr_ctx;
			v4 = ptr_ctx->curDispMode + 1;
			ptr_ctx->curDispMode = v4;
			v5 = ptr_ctx->graphicsAdapters[ptr_ctx->curGfxAdapt]
				.D3DInfo[ptr_ctx->curAccelAdapt]
				.nDisplayMode;
			if (v4 >= v5)
			{
				v4 = v5 - 1;
				ptr_ctx->curDispMode = v5 - 1;
			}
			v7 = ptr_ctx->graphicsAdapters[ptr_ctx->curGfxAdapt].D3DInfo[ptr_ctx->curAccelAdapt].DisplayMode;
			if (v7[v4].bpp != v7[v2].bpp)
			{
				while (1)
				{
					ptr_ctx->curDispMode = ++v4;
					v8 = *(_DWORD *)(ptr_ctx + 8);
					if (v4 >= ptr_ctx->graphicsAdapters[ptr_ctx->curGfxAdapt]
						.D3DInfo[ptr_ctx->curAccelAdapt]
						.nDisplayMode)
						break;
					v9 = ptr_ctx->graphicsAdapters[ptr_ctx->curGfxAdapt].D3DInfo[ptr_ctx->curAccelAdapt].DisplayMode;
					if (v9[4].bpp == v9[v2].bpp)
						goto LABEL_18;
					v3 = ptr_ctx;
				}
				ptr_ctx->curDispMode = v13;
				goto LABEL_23;
			}
		LABEL_18:
			v2 = v13;
		}
		else
		{
			v4 = ptr_ctx->curDispMode - 1;
			ptr_ctx->curDispMode = v4;
			if (v4 < 0)
			{
				v4 = 0;
				ptr_ctx->curDispMode = 0;
			}
			v10 = ptr_ctx->graphicsAdapters[ptr_ctx->curGfxAdapt]
				.D3DInfo[ptr_ctx->curAccelAdapt]
				.DisplayMode;
			if (v10[v4].bpp != v10[v2].bpp)
			{
				while (1)
				{
					ptr_ctx->curDispMode = --v4;
					if (v4 < 0)
						break;
					v11 = ptr_ctx->graphicsAdapters[ptr_ctx->curGfxAdapt]
						.D3DInfo[ptr_ctx->curAccelAdapt]
						.DisplayMode;
					if (v11[v4].bpp == v11[v2].bpp)
						goto LABEL_19;
				}
				ptr_ctx->curDispMode = v2;
				goto LABEL_23;
			}
		}
	LABEL_19:
		if (v2 != v4)
		{
			//j_nullsub_22();
			if (!DXChangeVideoMode())
			{
				ptr_ctx->curDispMode = v2;
				DXChangeVideoMode();
			}
			HWInitialise();
			//j_nullsub_24();
			InitWindow(0, 0, ptr_ctx->width, ptr_ctx->height, 20, 20480, 80);
			InitFont();
			sub_401D84();
			sub_402BAD();
		}
	LABEL_23:
		ResumeThread(hThread);
		ptr_ctx->dword_D9ABFD = 0;
		Log(5, "Game Thread Resumed");
		dword_D9AD9C = 120;
		return;
	}
}

void sub_4D3191()
{
	sub_4DA111(&ptr_ctx->isInScene);
}

void sub_4CF191()
{
	sub_4D8F51(&ptr_ctx->isInScene);
}

int __cdecl sub_40286A(int a1)
{
	LPDIRECTINPUTDEVICE2A result; // eax@1

	result = ptr_ctx->dinput_other;
	if (result)
	{
		if (a1)
			result = result->lpVtbl->Acquire(ptr_ctx->dinput_other);
		else
			result = result->lpVtbl->Unacquire(result);
	}
	return result;
}

LRESULT __stdcall sub_401E8D(HWND hWnd, unsigned int Msg, int wParam, void *lParam)
{
	if (Msg > 0x10)
	{
		if (Msg == WM_COMMAND)
		{
			Log(6, "WM_COMMAND");
			sub_4018AC((unsigned __int16)wParam);
		}
		else
		{
			if (Msg == WM_MOUSEFIRST)
			{
				dword_D9AB24 = (signed __int16)lParam;
				dword_D9AB20 = SHIWORD(lParam);
				dword_D9AB28 = wParam;
				return DefWindowProcA(hWnd, 0x200u, wParam, (LPARAM)lParam);
			}
			if (Msg == WM_APP)
			{
				sub_4027DE(lParam, wParam);
				return 0;
			}
		}
		return DefWindowProcA(hWnd, Msg, wParam, (LPARAM)lParam);
	}
	if (Msg == WM_CLOSE)
	{
		Log(6, "WM_CLOSE");
		byte_D9ADEC = 1;
		PostQuitMessage(0);
		return DefWindowProcA(hWnd, 0x10u, wParam, (LPARAM)lParam);
	}
	if (Msg == WM_CREATE)
	{
		dword_D9AD9C = 0;
		Log(6, "WM_CREATE");
		return DefWindowProcA(hWnd, 1u, wParam, (LPARAM)lParam);
	}
	if (Msg == WM_MOVE)
	{
		Log(6, "WM_MOVE");
		DXMove((signed __int16)lParam, SHIWORD(lParam));
		return DefWindowProcA(hWnd, 3u, wParam, (LPARAM)lParam);
	}
	if (Msg != WM_ACTIVATE)
		return DefWindowProcA(hWnd, Msg, wParam, (LPARAM)lParam);
	Log(6, "WM_ACTIVATE");
	if (byte_D9ADEC)
		return DefWindowProcA(hWnd, Msg, wParam, (LPARAM)lParam);
	if (ptr_ctx->byte_D9AC2B)
		return 0;
	if ((_WORD)wParam)
	{
		if ((signed int)(unsigned __int16)wParam > 0 && (signed int)(unsigned __int16)wParam <= 2)
		{
			Log(6, "WM_ACTIVE");
			if (ptr_ctx->byte_D9AC19)
			{
				sub_40286A(1);
				ResumeThread(hThread);
				ptr_ctx->dword_D9ABFD = 0;
				Log(5, "Game Thread Resumed");
				return 0;
			}
		}
	}
	else
	{
		Log(6, "WM_INACTIVE");
		if (ptr_ctx->byte_D9AC19)
		{
			sub_40286A(0);
			Log(5, "HangGameThread");
			if (ptr_ctx->isInScene)
				sub_4D3191();
			ptr_ctx->dword_D9ABFD = 1;
			if (!ptr_ctx->isInScene)
				sub_4CF191();
			SuspendThread(hThread);
			Log(5, "Game Thread Suspended");
		}
	}
	return 0;
}











LSTATUS __cdecl sub_4029B9(LPCSTR lpValueName, BYTE Data)
{
	return RegSetValueExA(hKey, lpValueName, 0, 4u, &Data, 4u);
}

char __cdecl ReadRegDword(LPCSTR lpValueName, DWORD* Type, BYTE Data)
{
	_DWORD *v3; // edi@1
	char result; // al@4
	int v5; // esi@5
	DWORD cbData; // [sp+Ch] [bp-4h]@1
	DWORD dwType = 0;
	v3 = Type;
	cbData = 4;
	if (RegQueryValueExA(hKey, lpValueName, 0, &dwType, (LPBYTE)Type, &cbData) || (int)Type != 4 || cbData != 4)
	{
		v5 = Data;
		sub_4029B9(lpValueName, Data);
		*v3 = v5;
		result = 0;
	}
	else
	{
		result = 1;
	}
	return result;
}

BOOL __cdecl sub_4020A9(LPCSTR lpSubKey)
{
	return RegCreateKeyExA(HKEY_CURRENT_USER, lpSubKey, 0, Class, 0, 0xF003Fu, 0, &hKey, &dwDisposition) == 0;
}

int __cdecl sub_402964(char* a1)
{
	int result; // eax@2
	CHAR SubKey[256]; // [sp+0h] [bp-100h]@2

	if (a1)
	{
		sprintf(&SubKey, "%s\\%s", "Software\\Core Design\\Tomb Raider Chronicles", a1);
		result = sub_4020A9(&SubKey);
	}
	else
	{
		result = sub_4020A9("Software\\Core Design\\Tomb Raider Chronicles");
	}
	return result;
}

LSTATUS __cdecl sub_402B94(LPCSTR lpValueName, BYTE Data)
{
	*(_DWORD *)&Data = (unsigned __int8)Data;
	return RegSetValueExA(hKey, lpValueName, 0, 4u, &Data, 4u);
}

char __cdecl ReadRegByte(LPCSTR lpValueName, BYTE* buf, BYTE defaultVal)
{
	const CHAR *v3; // esi@1
	char result; // al@4
	BYTE v5; // bl@5
	DWORD cbData; // [sp+4h] [bp-8h]@1
	BYTE Data[4]; // [sp+8h] [bp-4h]@1

	v3 = lpValueName;
	cbData = 4;
	if (RegQueryValueExA(hKey, lpValueName, 0, (LPDWORD)&lpValueName, Data, &cbData)
		|| lpValueName != (LPCSTR)4
		|| cbData != 4)
	{
		v5 = defaultVal;
		sub_402B94(v3, defaultVal);
		*(_BYTE *)buf = v5;
		result = 0;
	}
	else
	{
		*(_BYTE *)buf = *(_DWORD *)Data != 0;
		result = 1;
	}
	return result;
}

int __cdecl LoadTextureFormats(HWND hDlg, HWND hWnd)
{
	HWND v2; // eax@1
	HWND v3; // eax@1
	struct DIRECT3DINFO* result; // eax@1
	struct D3DTEXTUREINFO* v5; // eax@3
	int depth; // esi@3
	int bitsB; // ebx@3
	int bitsR; // edi@3
	HWND v9; // eax@9
	_BYTE v10[5]; // [sp+13h] [bp-39h]@1
	int v11; // [sp+18h] [bp-34h]@2
	int bitsG; // [sp+1Ch] [bp-30h]@3
	int bitsA; // [sp+20h] [bp-2Ch]@3
	CHAR v14[40]; // [sp+24h] [bp-28h]@3

	SendMessageA(hWnd, CB_RESETCONTENT, 0, 0);
	v2 = GetDlgItem(hDlg, IDC_TEXRES);
	EnableWindow(v2, 1);
	v3 = GetDlgItem(hDlg, IDC_SOFTWARE);
	v10[4] = 0;
	*(_DWORD *)v10 = SendMessageA(v3, BM_GETCHECK, 0, 0) != 0;
	result = &dxctx.graphicsAdapters[opt_GraphicsAdapter].D3DInfo[opt_AccelAdapter];
	if (result->nTexture > 0)
	{
		v11 = 0;
		do
		{
			v5 = &result->Texture[v11];
			depth = v5->bpp;
			bitsB = v5->bbpp;
			bitsR = v5->rbpp;
			bitsG = v5->gbpp;
			bitsA = v5->abpp;
			wsprintfA(v14, "%d %s RGBA %d%d%d%d", v5->bpp, &gfStringWad[gfStringOffset[STR_BIT]], bitsR, bitsG, bitsB, bitsA);
			SendMessageA(hWnd, CB_ADDSTRING, 0, (LPARAM)v14);
			if (v10[0])
			{
				if (depth == 32 && bitsR == 8 && bitsB == 8 && bitsG == 8 && bitsA == 8)
				{
					SendMessageA(hWnd, CB_SETCURSEL, *(WPARAM *)&v10[1], 0);
					dword_57A088 = *(_DWORD *)&v10[1];
					v9 = GetDlgItem(hDlg, IDC_TEXRES);
					EnableWindow(v9, 0);
				}
			}
			else if (depth != 16 || bitsR != 5 || bitsB != 5 || bitsG != 5 || bitsA != 1)
			{
				SendMessageA(hWnd, CB_SETCURSEL, 0, 0);
				dword_57A088 = 0;
			}
			else
			{
				SendMessageA(hWnd, CB_SETCURSEL, *(WPARAM *)&v10[1], 0);
				dword_57A088 = *(_DWORD *)&v10[1];
			}
			++*(_DWORD *)&v10[1];
			v11++;
			result = &dxctx.graphicsAdapters[opt_GraphicsAdapter].D3DInfo[opt_AccelAdapter];
		} while (*(_DWORD *)&v10[1] < result->nTexture);
	}
	return result;
}

char __cdecl LoadResolutions(HWND hDlg, HWND hWnd, char a3)
{
	HWND v3; // edi@2
	HWND v5; // eax@2
	HWND v7; // eax@3
	HWND v8; // eax@4
	HWND v9; // eax@4
	int v10; // ecx@5
	struct DIRECT3DINFO* v11; // eax@5
	struct DISPLAYMODE* v12; // eax@7
	int res_w; // edx@7
	int res_h; // ebx@7
	signed int res_bit; // eax@7
	int v16; // edx@18
	int v17; // edx@20
	struct DIRECT3DINFO* v18; // eax@20
	LPARAM v19; // ebx@20
	HWND v20; // eax@24
	HWND v22; // eax@24
	HWND v23; // eax@25
	WPARAM v24; // ST10_4@26
	HWND v25; // eax@26
	HWND v26; // eax@27
	HWND v27; // eax@28
	WPARAM v28; // ST10_4@29
	HWND v29; // eax@29
	HWND v30; // eax@30
	HWND v31; // eax@31
	WPARAM v32; // ST10_4@32
	HWND v33; // eax@32
	HWND v34; // eax@33
	HWND v35; // eax@34
	WPARAM v36; // ST10_4@35
	HWND v37; // eax@35
	HWND v38; // eax@36
	HWND v39; // eax@36
	HWND v40; // eax@37
	HWND v41; // eax@37
	HWND v42; // eax@39
	HWND v43; // eax@39
	char result; // al@40
	HWND v45; // eax@41
	HWND v46; // [sp-10h] [bp-60h]@12
	WPARAM v47; // [sp-8h] [bp-58h]@2
	WPARAM v48; // [sp-8h] [bp-58h]@12
	LPARAM lParam; // [sp+10h] [bp-40h]@5
	int v50; // [sp+18h] [bp-38h]@6
	int v51; // [sp+1Ch] [bp-34h]@7
	signed int v52; // [sp+20h] [bp-30h]@7
	int wParam; // [sp+24h] [bp-2Ch]@1
	CHAR var28[44]; // [sp+28h] [bp-28h]@8
	BOOL hDlga; // [sp+54h] [bp+4h]@4

	wParam = 0;
	if (opt_AccelAdapter)
	{
		v3 = hDlg;
		v5 = GetDlgItem(hDlg, IDC_HARDACCEL);
		SendMessageA(v5, BM_SETCHECK, 1u, 0);
		v47 = 0;
	}
	else
	{
		v3 = hDlg;
		v7 = GetDlgItem(hDlg, IDC_HARDACCEL);
		SendMessageA(v7, BM_SETCHECK, 0, 0);
		v47 = 1;
	}
	v8 = GetDlgItem(v3, IDC_SOFTWARE);
	SendMessageA(v8, BM_SETCHECK, v47, 0);
	v9 = GetDlgItem(v3, IDC_SOFTWARE);
	hDlga = SendMessageA(v9, BM_GETCHECK, 0, 0) != 0;
	if (a3)
	{
		SendMessageA(hWnd, CB_RESETCONTENT, 0, 0);
		v10 = opt_GraphicsAdapter;
		lParam = 0;
		v11 = &dxctx.graphicsAdapters[opt_GraphicsAdapter].D3DInfo[opt_AccelAdapter];
		if (v11->nDisplayMode > 0)
		{
			v50 = 0;
			do
			{
				v12 = &v11->DisplayMode[v50];
				res_w = v12->w;
				res_h = v12->h;
				res_bit = v12->bpp;
				v51 = res_w;
				v52 = res_bit;
				if (res_bit <= 8)
				{
					v16 = opt_AccelAdapter;
					goto LABEL_20;
				}
				wsprintfA(var28, "%dx%d %d %s", res_w, res_h, res_bit, &gfStringWad[gfStringOffset[STR_BIT]]);
				SendMessageA(hWnd, CB_ADDSTRING, 0, (LPARAM)var28);
				SendMessageA(hWnd, CB_SETITEMDATA, wParam, lParam);
				if (hDlga)
				{
					if (v51 != 320 || res_h != 240 || v52 != 16)
						goto LABEL_18;
					v48 = wParam;
					v46 = hWnd;
				}
				else
				{
					if (v51 != 640 || res_h != 480 || v52 != 16)
						goto LABEL_18;
					v48 = wParam;
					v46 = hWnd;
				}
				SendMessageA(v46, CB_SETCURSEL, v48, 0);
				dword_57A090 = wParam;
			LABEL_18:
				v16 = opt_AccelAdapter;
				v10 = opt_GraphicsAdapter;
				++wParam;
			LABEL_20:
				v50++;
				++lParam;
				v18 = dxctx.graphicsAdapters[v10].D3DInfo;
				v19 = v18[v16].nDisplayMode;
				v11 = &v18[v16];
			} while (lParam < v19);
		}
	}
	else
	{
		v10 = opt_GraphicsAdapter;
	}
	if (dxctx.graphicsAdapters[v10].DDCaps.dwCaps2 & DDCAPS2_CANRENDERWINDOWED)
	{
		v23 = GetDlgItem(v3, IDC_WINDOWED);
		EnableWindow(v23, 1);
	}
	else
	{
		v20 = GetDlgItem(v3, IDC_WINDOWED);
		EnableWindow(v20, 0);
		v22 = GetDlgItem(v3, IDC_WINDOWED);
		SendMessageA(v22, BM_SETCHECK, 0, 0);
	}
	v24 = (unsigned __int8)opt_BilinearFiltering;
	v25 = GetDlgItem(v3, IDC_BILINEAR);
	SendMessageA(v25, BM_SETCHECK, v24, 0);
	if (hDlga)
	{
		v26 = GetDlgItem(v3, IDC_VOLUMEFOG);
		EnableWindow(v26, 0);
		opt_VolumetricFog = 0;
	}
	else
	{
		v27 = GetDlgItem(v3, IDC_VOLUMEFOG);
		EnableWindow(v27, 1);
	}
	v28 = (unsigned __int8)opt_VolumetricFog;
	v29 = GetDlgItem(v3, IDC_VOLUMEFOG);
	SendMessageA(v29, BM_SETCHECK, v28, 0);
	if (hDlga)
	{
		v30 = GetDlgItem(v3, IDC_BUMPMAP);
		EnableWindow(v30, 0);
		opt_LowQualityBumpMap = 0;
	}
	else
	{
		v31 = GetDlgItem(v3, IDC_BUMPMAP);
		EnableWindow(v31, 1);
	}
	v32 = (unsigned __int8)opt_LowQualityBumpMap;
	v33 = GetDlgItem(v3, IDC_BUMPMAP);
	SendMessageA(v33, BM_SETCHECK, v32, 0);
	if (hDlga)
	{
		v34 = GetDlgItem(v3, IDC_LOWTEXT);
		EnableWindow(v34, 0);
		opt_LowQualityTextures = 0;
	}
	else
	{
		v35 = GetDlgItem(v3, IDC_LOWTEXT);
		EnableWindow(v35, 1);
	}
	v36 = (unsigned __int8)opt_LowQualityTextures;
	v37 = GetDlgItem(v3, IDC_LOWTEXT);
	SendMessageA(v37, BM_SETCHECK, v36, 0);
	if (opt_LowQualityTextures)
	{
		v38 = GetDlgItem(v3, IDC_LOWBUMP);
		SendMessageA(v38, BM_SETCHECK, 1u, 0);
		v39 = GetDlgItem(v3, IDC_LOWBUMP);
		EnableWindow(v39, 0);
	}
	else
	{
		v40 = GetDlgItem(v3, IDC_LOWBUMP);
		EnableWindow(v40, 1);
		v41 = GetDlgItem(v3, IDC_LOWBUMP);
		SendMessageA(v41, BM_SETCHECK, 0, 0);
	}
	if (!opt_LowQualityBumpMap)
	{
		v42 = GetDlgItem(v3, IDC_LOWBUMP);
		SendMessageA(v42, BM_SETCHECK, 0, 0);
		v43 = GetDlgItem(v3, IDC_LOWBUMP);
		EnableWindow(v43, 0);
	}
	result = a3;
	if (a3)
	{
		v45 = GetDlgItem(v3, IDC_TEXRES);
		result = LoadTextureFormats(v3, v45);
	}
	return result;

	S_Warn("[sub_4017B7] - Unimplemented!\n");
	return 0;
}

int __cdecl LoadAccelAdapters(HWND hDlg, HWND hWnd)
{
	int v2; // esi@1
	struct DIRECTDRAWINFO* v3; // eax@1
	int v4; // edi@2
	HWND v5; // eax@4

	SendMessageA(hWnd, CB_RESETCONTENT, 0, 0);
	v2 = 0;
	v3 = &dxctx.graphicsAdapters[opt_GraphicsAdapter];
	if (v3->nD3DInfo > 0)
	{
		v4 = 0;
		do
		{
			SendMessageA(hWnd, CB_ADDSTRING, 0, v3->D3DInfo[v4].About);
			++v2;
			v4++;
			v3 = &dxctx.graphicsAdapters[opt_GraphicsAdapter];
		} while (v2 < v3->nD3DInfo);
	}
	SendMessageA(hWnd, CB_SETCURSEL, 1u, 0);
	opt_AccelAdapter = 1;
	v5 = GetDlgItem(hDlg, IDC_RESOLUTION);
	return LoadResolutions(hDlg, v5, 1);
}

int __cdecl LoadGraphicsAdapters(HWND hDlg, HWND hWnd)
{
	int v2; // eax@1
	int v3; // edi@1
	int v4; // esi@2
	HWND v5; // eax@4
	CHAR v7[256]; // [sp+10h] [bp-100h]@3

	SendMessageA(hWnd, CB_RESETCONTENT, 0, 0);
	v2 = dxctx.numGraphicsAdapters;
	v3 = 0;
	if (dxctx.numGraphicsAdapters > 0)
	{
		v4 = 0;
		do
		{
			wsprintfA(
				v7,
				"%s - %s (%d.%d.%02d.%04d)",
				dxctx.graphicsAdapters[v4].deviceName,
				dxctx.graphicsAdapters[v4].driverDllName,
				dxctx.graphicsAdapters[v4].versionMajor,
				dxctx.graphicsAdapters[v4].versionMinor,
				dxctx.graphicsAdapters[v4].versionBuild,
				dxctx.graphicsAdapters[v4].versionRevision);
			SendMessageA(hWnd, CB_ADDSTRING, 0, (LPARAM)v7);
			v2 = dxctx.numGraphicsAdapters;
			++v3;
			v4++;
		} while (v3 < dxctx.numGraphicsAdapters);
	}
	SendMessageA(hWnd, CB_SETCURSEL, v2 - 1, 0);
	opt_GraphicsAdapter = dxctx.numGraphicsAdapters - 1;
	v5 = GetDlgItem(hDlg, IDC_OUTSETTINGS);
	return LoadAccelAdapters(hDlg, v5);
}

void sub_402D10()
{
	for(int i = 0; i < 18; i++)
	{
		dword_878C4C[i] = 0;

		for(int j = 0; j < 18; j++)
		{
			if (opt_Keys[i] == opt_Keys2[j])
			{
				dword_878C4C[i] = 1;
				break;
			}
		}
	}
}

char LoadSettings()
{
	int v0; // eax@8
	int v1; // eax@9
	int v2; // edx@13
	int v3; // ecx@13
	char result; // al@13
	DWORD Type; // [sp+3h] [bp-5h]@3
	DWORD Type2;

	if ((unsigned __int8)sub_402964("System"))
	{
		ReadRegByte("Setup", (int)&opt_Setup, 0);
		if (opt_Setup)
		{
			ptr_ctx->textRes = 256;
			ptr_ctx->bumpRes = 256;
			ptr_ctx->dword_D9AC27 = 32;
			ReadRegDword("DD", &ptr_ctx->curGfxAdapt, 0);
			ReadRegDword("D3D", &ptr_ctx->curAccelAdapt, 0);
			ReadRegDword("VMode", &ptr_ctx->curDispMode, 0);
			ReadRegDword("TFormat", &ptr_ctx->curTexFormat, 0);
			ReadRegDword("DS", &ptr_ctx->curSoundCard, 0);
			ReadRegByte("BumpMap", &ptr_ctx->tEnableBumpMap, 1);
			ReadRegByte("Filter", &ptr_ctx->opt_Filter, 1);
			ReadRegByte("DisableSound", &ptr_ctx->opt_DisableSound, 0);
#ifdef FORCE_NO_SOUND
			ptr_ctx->opt_DisableSound = 1;
#endif
			ReadRegByte("Volumetric", &ptr_ctx->opt_Volumetric, 1);
			ReadRegByte("NoFMV", &opt_NoFMV, 0);
			ReadRegByte("TextLow", (int)&Type, 0);
			if ((_BYTE)Type)
				ptr_ctx->textRes = 128;
			ReadRegByte("BumpLow", (int)&Type, 0);
			if ((_BYTE)Type)
				ptr_ctx->bumpRes = 128;
			ReadRegByte("HardWare", (int)&Type, 1);
			if ((_BYTE)Type)
			{
				v0 = ptr_ctx->dword_D9AC27;
				LOBYTE(v0) = ptr_ctx->dword_D9AC27 | 0x90;
				ptr_ctx->dword_D9AC27 = v0;
			}
			/*ReadRegByte("Window", (int)&Type, 0);
			v1 = dword_D9AC27;
			if ((_BYTE)Type)
				LOBYTE(v1) = dword_D9AC27 | 2;
			else
				LOBYTE(v1) = dword_D9AC27 | 1;
			dword_D9AC27 = v1;*/
		}
		sub_402964("Game");
		ReadRegDword("Key0", &opt_Keys2[0], opt_Keys[0]);
		ReadRegDword("Key1", &opt_Keys2[1], opt_Keys[1]);
		ReadRegDword("Key2", &opt_Keys2[2], opt_Keys[2]);
		ReadRegDword("Key3", &opt_Keys2[3], opt_Keys[3]);
		ReadRegDword("Key4", &opt_Keys2[4], opt_Keys[4]);
		ReadRegDword("Key5", &opt_Keys2[5], opt_Keys[5]);
		ReadRegDword("Key6", &opt_Keys2[6], opt_Keys[6]);
		ReadRegDword("Key7", &opt_Keys2[7], opt_Keys[7]);
		ReadRegDword("Key8", &opt_Keys2[8], opt_Keys[8]);
		ReadRegDword("Key9", &opt_Keys2[9], opt_Keys[9]);
		ReadRegDword("Key10", &opt_Keys2[10], opt_Keys[10]);
		ReadRegDword("Key11", &opt_Keys2[11], opt_Keys[11]);
		ReadRegDword("Key12", &opt_Keys2[12], opt_Keys[12]);
		ReadRegDword("Key13", &opt_Keys2[13], opt_Keys[13]);
		ReadRegDword("Key14", &opt_Keys2[14], opt_Keys[14]);
		ReadRegDword("Key15", &opt_Keys2[15], opt_Keys[15]);
		ReadRegDword("Key16", &opt_Keys2[16], opt_Keys[16]);
		ReadRegDword("Key17", &opt_Keys2[17], opt_Keys[17]);
		ReadRegDword("JDck", &opt_JDck, 5);
		ReadRegDword("JDsh", &opt_JDsh, 3);
		ReadRegDword("JWlk", &opt_JWlk, 4);
		ReadRegDword("JJmp", &opt_JJmp, 0);
		ReadRegDword("JAct", &opt_JAct, 1);
		ReadRegDword("JDrw", &opt_JDrw, 2);
		ReadRegDword("JFlr", &opt_JFlr, 9);
		ReadRegDword("JLok", &opt_JLok, 6);
		ReadRegDword("JRol", &opt_JRol, 7);
		ReadRegDword("JInv", &opt_JInv, 8);
		ReadRegDword("MusicVolume", &opt_MusicVolume, 80);
		ReadRegDword("SFXVolume", &opt_SFXVolume, 90);
		ReadRegDword("ControlMethod", &opt_ControlMethod, 0);
		ReadRegDword("SoundQuality", &opt_SoundQuality, 1);
		ReadRegDword("AutoTarget", &ptr_ctx->opt_AutoTarget, 1);
		ReadRegDword("WindowX", &dxctx.windowPos.left, 0);
		ReadRegDword("WindowY", &dxctx.windowPos.top, 0);
		sub_402D10();
		result = opt_Setup;
	}
	else
	{
		result = 0;
	}
	return result;
	S_Warn("[sub_402F77] - Unimplemented!\n");
	return 0;
}

char *__cdecl sub_401C9E(const char *a1, char *a2)
{
	const char *v2; // ebp@1
	char *v3; // esi@1
	unsigned int v4; // kr04_4@1
	char v5; // bl@3
	int v6; // ecx@4
	_BYTE *v7; // eax@4
	char *result; // eax@9
	int v9; // [sp+10h] [bp+4h]@2

	v2 = a1;
	v3 = a2;
	v4 = strlen(a1) + 1;
	if ((signed int)(v4 - 1) <= 0)
	{
		result = a2;
		*a2 = 0;
	}
	else
	{
		v9 = v4 - 1;
		do
		{
			v5 = *v2++;
			if (v5 >= 128)
			{
				v6 = 0;
				v7 = byte_511894;
				while (v5 != *v7)
				{
					v7 += 2;
					++v6;
					if ((signed int)v7 >= (signed int)&unk_5118A2)
					{
						Log(1, "Reqd : %x", v5);
						goto LABEL_8;
					}
				}
				v5 = byte_511894[2 * v6 + 1];
			}
		LABEL_8:
			*v3++ = v5;
			--v9;
		} while (v9);
		result = a2;
		*v3 = 0;
	}
	return result;
}

LRESULT __cdecl sub_4018F2(HWND hDlg, HWND hWnd)
{
	int v2; // eax@1
	int v3; // esi@1
	int v4; // ebp@2
	HWND v5; // eax@5
	HWND v6; // eax@5

	SendMessageA(hWnd, CB_RESETCONTENT, 0, 0);
	v2 = dxctx.numSoundCards;
	v3 = 0;
	if (dxctx.numSoundCards > 0)
	{
		v4 = 0;
		do
		{
			SendMessageA(hWnd, CB_ADDSTRING, 0, ptr_ctx->soundCards[v4].description);
			v2 = dxctx.numSoundCards;
			++v3;
			v4 += 130;
		} while (v3 <  dxctx.numSoundCards);
	}
	dword_57A08C = 0;
	if (!v2)
	{
		SendMessageA(hWnd, CB_ADDSTRING, 0, (LPARAM)&gfStringWad[gfStringOffset[STR_NO_SOUND_CARD_INSTALLED]]);
		v5 = GetDlgItem(hDlg, IDC_NOSOUND);
		EnableWindow(v5, 0);
		v6 = GetDlgItem(hDlg, IDC_NOSOUND);
		SendMessageA(v6, BM_SETCHECK, 1u, 0);
		EnableWindow(hWnd, 0);
	}
	return SendMessageA(hWnd, CB_SETCURSEL, 0, 0);
}

char __cdecl sub_402DF1(HWND hDlg)
{
	HWND v1; // eax@1
	BYTE v2; // al@1
	HWND v3; // eax@1
	BYTE v4; // al@1
	HWND v5; // eax@1
	LRESULT v6; // ST10_4@1
	HWND v7; // eax@1
	BYTE v8; // al@1
	HWND v9; // eax@1
	BYTE v10; // al@1
	HWND v11; // eax@1
	BYTE v12; // al@1
	HWND v13; // eax@1
	LRESULT v14; // eax@1
	HWND v15; // eax@1
	LRESULT v16; // eax@1
	HWND v17; // eax@1
	LRESULT v18; // eax@1
	HWND v19; // eax@1
	LRESULT v20; // eax@1
	HWND v21; // eax@1
	LRESULT v22; // eax@1
	HWND v23; // eax@1
	LRESULT v24; // eax@1
	HWND v25; // eax@1
	LRESULT v26; // eax@1
	HWND v27; // eax@1
	LRESULT v28; // eax@1
	HWND v29; // eax@1
	LRESULT v30; // eax@1

	sub_402964("System");
	v1 = GetDlgItem(hDlg, IDC_GFXADAPTER);
	v2 = SendMessageA(v1, CB_GETCURSEL, 0, 0);
	sub_4029B9("DD", v2);
	v3 = GetDlgItem(hDlg, IDC_OUTSETTINGS);
	v4 = SendMessageA(v3, CB_GETCURSEL, 0, 0);
	sub_4029B9("D3D", v4);
	v5 = GetDlgItem(hDlg, IDC_RESOLUTION);
	v6 = SendMessageA(v5, CB_GETCURSEL, 0, 0);
	v7 = GetDlgItem(hDlg, IDC_RESOLUTION);
	v8 = SendMessageA(v7, CB_GETITEMDATA, v6, 0);
	sub_4029B9("VMode", v8);
	v9 = GetDlgItem(hDlg, IDC_SNDADAPTER);
	v10 = SendMessageA(v9, CB_GETCURSEL, 0, 0);
	sub_4029B9("DS", v10);
	v11 = GetDlgItem(hDlg, IDC_TEXRES);
	v12 = SendMessageA(v11, CB_GETCURSEL, 0, 0);
	sub_4029B9("TFormat", v12);
	v13 = GetDlgItem(hDlg, IDC_BILINEAR);
	v14 = SendMessageA(v13, BM_GETCHECK, 0, 0);
	sub_402B94("Filter", v14 != 0);
	v15 = GetDlgItem(hDlg, IDC_BUMPMAP);
	v16 = SendMessageA(v15, BM_GETCHECK, 0, 0);
	sub_402B94("BumpMap", v16 != 0);
	v17 = GetDlgItem(hDlg, IDC_HARDACCEL);
	v18 = SendMessageA(v17, BM_GETCHECK, 0, 0);
	sub_402B94("HardWare", v18 != 0);
	v19 = GetDlgItem(hDlg, IDC_NOSOUND);
	v20 = SendMessageA(v19, BM_GETCHECK, 0, 0);
	sub_402B94("DisableSound", v20 != 0);
	v21 = GetDlgItem(hDlg, IDC_LOWTEXT);
	v22 = SendMessageA(v21, BM_GETCHECK, 0, 0);
	sub_402B94("TextLow", v22 != 0);
	v23 = GetDlgItem(hDlg, IDC_LOWBUMP);
	v24 = SendMessageA(v23, BM_GETCHECK, 0, 0);
	sub_402B94("BumpLow", v24 != 0);
	v25 = GetDlgItem(hDlg, IDC_WINDOWED);
	v26 = SendMessageA(v25, BM_GETCHECK, 0, 0);
	sub_402B94("Window", v26 != 0);
	v27 = GetDlgItem(hDlg, IDC_VOLUMEFOG);
	v28 = SendMessageA(v27, BM_GETCHECK, 0, 0);
	sub_402B94("Volumetric", v28 != 0);
	v29 = GetDlgItem(hDlg, IDC_NOFMV);
	v30 = SendMessageA(v29, BM_GETCHECK, 0, 0);
	sub_402B94("NoFMV", v30 != 0);
	sub_402B94("Setup", 1);
	return 1;
}

signed int __stdcall DialogFunc(HWND hDlg, int msg, unsigned int wParam, int lParam)
{
	signed int result; // eax@11
	HWND v5; // eax@16
	HWND v6; // eax@16
	HWND v7; // esi@22
	HWND(__stdcall *v8)(HWND, int); // edi@22
	HWND v9; // eax@22
	HWND v10; // eax@25
	HWND v11; // ebx@28
	HWND v12; // esi@28
	HWND v13; // eax@32
	HWND v14; // eax@34
	HWND v15; // eax@36
	HWND v16; // eax@38
	HWND v17; // eax@40
	HGDIOBJ v18; // ST10_4@43
	HWND v19; // eax@43
	HGDIOBJ v20; // ST10_4@43
	HWND v21; // eax@43
	HGDIOBJ v22; // ST10_4@43
	HWND v23; // eax@43
	HGDIOBJ v24; // ST10_4@43
	HWND v25; // eax@43
	HGDIOBJ v26; // ST10_4@43
	HWND v27; // eax@43
	char *v28; // ST10_4@44
	HWND v29; // eax@44
	char *v30; // ST10_4@44
	HWND v31; // eax@44
	char *v32; // ST10_4@44
	HWND v33; // eax@44
	char *v34; // ST10_4@44
	HWND v35; // eax@44
	char *v36; // ST10_4@44
	HWND v37; // eax@44
	char *v38; // ST10_4@44
	HWND v39; // eax@44
	char *v40; // ST10_4@44
	HWND v41; // eax@44
	char *v42; // ST10_4@44
	HWND v43; // eax@44
	char *v44; // ST10_4@44
	HWND v45; // eax@44
	char *v46; // ST10_4@44
	HWND v47; // eax@44
	char *v48; // ST10_4@44
	HWND v49; // eax@44
	char *v50; // ST10_4@44
	HWND v51; // eax@44
	char *v52; // ST10_4@44
	HWND v53; // eax@44
	char *v54; // ST10_4@44
	HWND v55; // eax@44
	char *v56; // ST10_4@44
	HWND v57; // eax@44
	char *v58; // ST10_4@44
	HWND v59; // eax@44
	char *v60; // ST10_4@44
	HWND v61; // eax@44
	char *v62; // ST10_4@44
	HWND v63; // eax@44
	HWND v64; // eax@44
	HWND v65; // eax@44
	WPARAM v66; // [sp-8h] [bp-114h]@20
	char v67[16]; // [sp-4h] [bp-110h]@22
	char v68[256]; // [sp+Ch] [bp-100h]@44

	if (msg == 272)
	{
		Log(6, "WM_INITDIALOG");
		if (Gameflow->Language == LNG_JAPAN)
		{
			v18 = GetStockObject(13);
			gdiobject = v18;
			v19 = GetDlgItem(hDlg, IDC_GFXADAPTER);
			SendMessageA(v19, WM_SETFONT, 0, (LPARAM)v18);
			v20 = gdiobject;
			v21 = GetDlgItem(hDlg, IDC_OUTSETTINGS);
			SendMessageA(v21, WM_SETFONT, 0, (LPARAM)v20);
			v22 = gdiobject;
			v23 = GetDlgItem(hDlg, IDC_RESOLUTION);
			SendMessageA(v23, WM_SETFONT, 0, (LPARAM)v22);
			v24 = gdiobject;
			v25 = GetDlgItem(hDlg, IDC_TEXRES);
			SendMessageA(v25, WM_SETFONT, 0, (LPARAM)v24);
			v26 = gdiobject;
			v27 = GetDlgItem(hDlg, IDC_SNDADAPTER);
			SendMessageA(v27, WM_SETFONT, 0, (LPARAM)v26);
		}
		v28 = sub_401C9E(&gfStringWad[gfStringOffset[STR_GRAPHICS_ADAPTER]], v68);
		v29 = GetDlgItem(hDlg, 1001);
		SendMessageA(v29, WM_SETTEXT, 0, (LPARAM)v28);
		v30 = sub_401C9E(&gfStringWad[gfStringOffset[STR_OUTPUT_SETTINGS]], v68);
		v31 = GetDlgItem(hDlg, 1002);
		SendMessageA(v31, WM_SETTEXT, 0, (LPARAM)v30);
		v32 = sub_401C9E(&gfStringWad[gfStringOffset[STR_OK_BIS]], v68);
		v33 = GetDlgItem(hDlg, IDOK);
		SendMessageA(v33, WM_SETTEXT, 0, (LPARAM)v32);
		v34 = sub_401C9E(&gfStringWad[gfStringOffset[STR_CANCEL_BIS_BIS]], v68);
		v35 = GetDlgItem(hDlg, IDCANCEL);
		SendMessageA(v35, WM_SETTEXT, 0, (LPARAM)v34);
		v36 = sub_401C9E(&gfStringWad[gfStringOffset[STR_OUTPUT_RESOLUTION]], v68);
		v37 = GetDlgItem(hDlg, 1009);
		SendMessageA(v37, WM_SETTEXT, 0, (LPARAM)v36);
		v38 = sub_401C9E(&gfStringWad[gfStringOffset[STR_BILINEAR_FILTERING]], v68);
		v39 = GetDlgItem(hDlg, IDC_BILINEAR);
		SendMessageA(v39, WM_SETTEXT, 0, (LPARAM)v38);
		v40 = sub_401C9E(&gfStringWad[gfStringOffset[STR_BUMP_MAPPING]], v68);
		v41 = GetDlgItem(hDlg, IDC_BUMPMAP);
		SendMessageA(v41, WM_SETTEXT, 0, (LPARAM)v40);
		v42 = sub_401C9E(&gfStringWad[gfStringOffset[STR_HARDWARE_ACCELERATION]], v68);
		v43 = GetDlgItem(hDlg, IDC_HARDACCEL);
		SendMessageA(v43, WM_SETTEXT, 0, (LPARAM)v42);
		v44 = sub_401C9E(&gfStringWad[gfStringOffset[STR_SOFTWARE_MODE]], v68);
		v45 = GetDlgItem(hDlg, IDC_SOFTWARE);
		SendMessageA(v45, WM_SETTEXT, 0, (LPARAM)v44);
		v46 = sub_401C9E(&gfStringWad[gfStringOffset[STR_SOUND_DEVICE]], v68);
		v47 = GetDlgItem(hDlg, 1017);
		SendMessageA(v47, WM_SETTEXT, 0, (LPARAM)v46);
		v48 = sub_401C9E(&gfStringWad[gfStringOffset[STR_DISABLE]], v68);
		v49 = GetDlgItem(hDlg, IDC_NOSOUND);
		SendMessageA(v49, WM_SETTEXT, 0, (LPARAM)v48);
		v50 = sub_401C9E(&gfStringWad[gfStringOffset[STR_LOW_RESOLUTION_TEXTURES]], v68);
		v51 = GetDlgItem(hDlg, IDC_LOWTEXT);
		SendMessageA(v51, WM_SETTEXT, 0, (LPARAM)v50);
		v52 = sub_401C9E(&gfStringWad[gfStringOffset[STR_LOW_RESOLUTION_BUMP_MAPS]], v68);
		v53 = GetDlgItem(hDlg, IDC_LOWBUMP);
		SendMessageA(v53, WM_SETTEXT, 0, (LPARAM)v52);
		v54 = sub_401C9E(&gfStringWad[gfStringOffset[STR_TEXTURE_BIT_DEPTH]], v68);
		v55 = GetDlgItem(hDlg, 1013);
		SendMessageA(v55, WM_SETTEXT, 0, (LPARAM)v54);
		v56 = sub_401C9E(&gfStringWad[gfStringOffset[STR_WINDOWED]], v68);
		v57 = GetDlgItem(hDlg, IDC_WINDOWED);
		SendMessageA(v57, WM_SETTEXT, 0, (LPARAM)v56);
		v58 = sub_401C9E(&gfStringWad[gfStringOffset[STR_RENDER_OPTIONS]], v68);
		v59 = GetDlgItem(hDlg, 1023);
		SendMessageA(v59, WM_SETTEXT, 0, (LPARAM)v58);
		v60 = sub_401C9E(&gfStringWad[gfStringOffset[STR_VOLUMETRIC_FX]], v68);
		v61 = GetDlgItem(hDlg, IDC_VOLUMEFOG);
		SendMessageA(v61, WM_SETTEXT, 0, (LPARAM)v60);
		v62 = sub_401C9E(&gfStringWad[gfStringOffset[STR_NO_FMV]], v68);
		v63 = GetDlgItem(hDlg, IDC_NOFMV);
		SendMessageA(v63, WM_SETTEXT, 0, (LPARAM)v62);
		v64 = GetDlgItem(hDlg, IDC_GFXADAPTER);
		LoadGraphicsAdapters(hDlg, v64);
		v65 = GetDlgItem(hDlg, IDC_SNDADAPTER);
		sub_4018F2(hDlg, v65);
		return 1;
	}
	if (msg != WM_COMMAND)
		return 0;
	if ((signed int)(unsigned __int16)wParam > IDC_SOFTWARE)
	{
		switch ((unsigned __int16)wParam)
		{
		case IDC_NOSOUND:
			if (wParam >> 16)
				return 0;
			v11 = GetDlgItem(hDlg, (unsigned __int16)wParam);
			v12 = GetDlgItem(hDlg, IDC_SNDADAPTER);
			if (SendMessageA(v11, BM_GETCHECK, 0, 0))
			{
				EnableWindow(v12, 0);
				result = 0;
			}
			else
			{
				EnableWindow(v12, 1);
				result = 0;
			}
			return result;
		case IDC_LOWTEXT:
			if (wParam >> 16)
				return 0;
			v7 = hDlg;
			v8 = GetDlgItem;
			v13 = GetDlgItem(hDlg, IDC_LOWTEXT);
			opt_LowQualityTextures = SendMessageA(v13, BM_GETCHECK, 0, 0) != 0;
			break;
		case IDC_BUMPMAP:
			if (wParam >> 16)
				return 0;
			v7 = hDlg;
			v8 = GetDlgItem;
			v14 = GetDlgItem(hDlg, IDC_BUMPMAP);
			opt_LowQualityBumpMap = SendMessageA(v14, BM_GETCHECK, 0, 0) != 0;
			break;
		case IDC_VOLUMEFOG:
			if (wParam >> 16)
				return 0;
			v7 = hDlg;
			v8 = GetDlgItem;
			v15 = GetDlgItem(hDlg, IDC_VOLUMEFOG);
			LOBYTE(opt_VolumetricFog) = SendMessageA(v15, BM_GETCHECK, 0, 0) != 0;
			break;
		case IDC_BILINEAR:
			if (wParam >> 16)
				return 0;
			v7 = hDlg;
			v8 = GetDlgItem;
			v16 = GetDlgItem(hDlg, IDC_BILINEAR);
			opt_BilinearFiltering = SendMessageA(v16, BM_GETCHECK, 0, 0) != 0;
			break;
		default:
			return 0;
		}
		v67[0] = 0;
		goto LABEL_40;
	}
	if ((unsigned __int16)wParam == IDC_SOFTWARE)
	{
		if (wParam >> 16)
			return 0;
		opt_AccelAdapter = 0;
		v66 = 0;
		goto LABEL_25;
	}
	if ((signed int)(unsigned __int16)wParam > IDC_GFXADAPTER)
	{
		if ((unsigned __int16)wParam == IDC_OUTSETTINGS)
		{
			if (wParam >> 16 != 1)
				return 0;
			v7 = hDlg;
			v8 = GetDlgItem;
			v9 = GetDlgItem(hDlg, IDC_OUTSETTINGS);
			opt_AccelAdapter = SendMessageA(v9, CB_GETCURSEL, 0, 0);
			v67[0] = 1;
		LABEL_40:
			v17 = v8(v7, IDC_RESOLUTION);
			LoadResolutions(v7, v17, v67[0]);
			return 0;
		}
		if ((unsigned __int16)wParam != IDC_HARDACCEL || wParam >> 16)
			return 0;
		opt_AccelAdapter = 1;
		v66 = 1;
	LABEL_25:
		v7 = hDlg;
		v8 = GetDlgItem;
		v10 = GetDlgItem(hDlg, IDC_OUTSETTINGS);
		SendMessageA(v10, CB_SETCURSEL, v66, 0);
		v67[0] = 1;
		goto LABEL_40;
	}
	if ((unsigned __int16)wParam == IDC_GFXADAPTER)
	{
		if (wParam >> 16 == 1)
		{
			v5 = GetDlgItem(hDlg, IDC_GFXADAPTER);
			opt_GraphicsAdapter = SendMessageA(v5, CB_GETCURSEL, 0, 0);
			v6 = GetDlgItem(hDlg, IDC_OUTSETTINGS);
			LoadAccelAdapters(hDlg, v6);
			return 0;
		}
		return 0;
	}
	if ((unsigned __int16)wParam != 1)
	{
		if ((unsigned __int16)wParam == 2)
		{
			if (gdiobject)
				DeleteObject(gdiobject);
			EndDialog(hDlg, 0);
			return 1;
		}
		return 0;
	}
	if (gdiobject)
		DeleteObject(gdiobject);
	sub_402DF1(hDlg);
	EndDialog(hDlg, 1);
	return 1;
}

BOOL  InitSetupDialog()
{
	INT_PTR v0; // esi@1
	BOOL result; // al@2

	ShowCursor(1);
	v0 = DialogBoxParamA(hinst, (LPCSTR)IDD_SETUP, 0, DialogFunc, 0);
	ShowCursor(0);
	if (v0 == -1)
	{
		MessageBoxA(0, "Unable To Initialise Dialog", Class, 0);
		result = 0;
	}
	else
	{
		result = v0 != 0;
	}
	return result;
}

int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	InitConsole();

	memset(&dxctx, 0, sizeof(dxctx));

	//S_Warn("[WinMain] - Unimplemented!\n");

	HWND v4; // eax@1
	HWND v5; // eax@3
	int v6; // eax@5
	HWND v8; // eax@8
	HWND v9; // esi@15
	HDC v10; // edi@15
	struct DISPLAYMODE* v11; // ecx@15
	HWND desktopHwnd; // eax@25
	HWND v13; // esi@25
	HDC desktopDC; // eax@25
	HWND v15; // eax@25
	struct tagRECT Rect; // [sp+Ch] [bp-A4h]@8
	char v17[36]; // [sp+1Ch] [bp-94h]@25
	__int16 v18; // [sp+40h] [bp-70h]@25
	int v19; // [sp+44h] [bp-6Ch]@25
	int v20; // [sp+84h] [bp-2Ch]@25

	ptr_ctx = &dxctx;

	byte_57A098 = 0;
	ptr_ctx->byte_D9AC23 = sub_4D22D0() != 0;
	ptr_ctx->byte_D9AC19 = 0;
	ptr_ctx->opt_AutoTarget = 0;
	sub_4DEC40(1);
	v4 = FindWindowA(ClassName, WindowName);
	if (v4)
		PostMessageA(v4, Msg, 2u, 0);
	v5 = FindWindowA(ClassName, WindowName);
	if (v5)
		PostMessageA(v5, dword_E4ACAC, 0, 0);
	sub_4DEA50("Error", 255, 1);
	sub_4DEA50("Function", 0x8000, 0);
	sub_4DEA50("DirectX Information", 0x802040, 1);
	sub_4DEA50("Object Release", 128, 0);
	sub_4DEA50("General Information", 0x800000, 1);
	sub_4DEA50("Windows Message", 0x800080, 0);
	sub_4DEA50("Level Info", 0x8000FF, 0);
	sub_4DEA50("Sound", 32896, 0);
	Log(5, "Launching - %s", Name);
	Log(2, "WinMain");
	_CrtSetReportMode(0, 2);
	v6 = _CrtSetDbgFlag(-1);
	LOBYTE(v6) = v6 | 0x24;
	_CrtSetDbgFlag(v6);
	if (!(unsigned __int8)WinRunCheck(Name, "MainGameWindow", &ptr_ctx->hObject))
	{
		FindCDDrive();
		LoadGameflow();
		WinProcessCommandLine(lpCmdLine);
		hinst = hInstance;
		WndClass.hIcon = 0;
		WndClass.lpszMenuName = 0;
		WndClass.lpszClassName = "MainGameWindow";
		WndClass.hbrBackground = (HBRUSH)GetStockObject(4);
		WndClass.hInstance = hInstance;
		WndClass.style = 3;
		WndClass.lpfnWndProc = (WNDPROC)sub_401E8D;
		WndClass.cbClsExtra = 0;
		WndClass.cbWndExtra = 0;
		WndClass.hCursor = LoadCursorA(hinst, (LPCSTR)IDC_ARROW);
		if (!RegisterClassA(&WndClass))
		{
			Log(1, "Unable To Register Window Class");
			return 0;
		}
		Rect.left = 0;
		Rect.top = 0;
		Rect.right = 640;
		Rect.bottom = 480;
		AdjustWindowRect(&Rect, WS_CAPTION, 0);
		v8 = CreateWindowExA(
			WS_EX_APPWINDOW,
			"MainGameWindow",
			Name,
			WS_CAPTION,
			2147483648,
			2147483648,
			Rect.right - Rect.left,
			Rect.bottom - Rect.top,
			0,
			0,
			hInstance,
			0);
		hWnd = v8;
		if (!v8)
		{
			Log(1, "Unable To Create Window");
			return 0;
		}
		DXInitialise(&dxctx, v8);
		if (byte_57A098 || !(unsigned __int8)LoadSettings())
		{
			if (!(unsigned __int8)InitSetupDialog())
			{
				free(gfScriptFile);
				free(gfStringOffset);
				WinClose();
				return 0;
			}
			LoadSettings();
		}
		SetWindowPos(hWnd, 0, dxctx.windowPos.left, dxctx.windowPos.top, 0, 0, 5u);
		v9 = GetDesktopWindow();
		v10 = GetDC(v9);
		ptr_ctx->OriginalBPP = GetDeviceCaps(v10, 12);
		ReleaseDC(v9, v10);
		ptr_ctx->dword_D9ABFD = 0;
		ptr_ctx->isInScene = 0;
		ptr_ctx->byte_D9AC2B = 0;
		v11 = ptr_ctx->graphicsAdapters[ptr_ctx->curGfxAdapt].D3DInfo[ptr_ctx->curAccelAdapt].DisplayMode;
		if (!DXCreate(
			v11[ptr_ctx->curDispMode].w,
			v11[ptr_ctx->curDispMode].h,
			v11[ptr_ctx->curDispMode].bpp,
			ptr_ctx->dword_D9AC27,
			&dxctx,
			hWnd,
			WS_CAPTION))
		{
			MessageBoxA(0, &gfStringWad[gfStringOffset[STR_FAILED_TO_SETUP_DIRECTX]], Caption, 0);
			return 0;
		}
		sub_401424();
		UpdateWindow(hWnd);
		ShowWindow(hWnd, nCmdShow);
		if (ptr_ctx->flags & 1)
		{
			SetCursor(0);
			ShowCursor(0);
		}
		sub_402CD4(hWnd, hinst);
		ptr_ctx->hAccTable = LoadAcceleratorsA(hInstance, (LPCSTR)0x65);
		if (!ptr_ctx->opt_DisableSound)
		{
			DXDSCreate();
			ACMInit();
		}
		dword_E916E0 = NULL;
		dword_876C40 = 1;
		dword_876C48 = 0;
		hThread = (HANDLE)_beginthreadex(0, 0, GameMain, 0, 0, &thread_id);
		WinProcMsg();
		dword_876C48 = 1;
		while (dword_876C40)
			;
		if (dword_E916E0)
			free(dword_E916E0);
		WinClose();
		desktopHwnd = GetDesktopWindow();
		v13 = desktopHwnd;
		desktopDC = GetDC(desktopHwnd);
		v18 = 148;
		v20 = ptr_ctx->OriginalBPP;
		ReleaseDC(v13, desktopDC);
		v19 = 0x40000;
		ChangeDisplaySettingsA((DEVMODEA *)&v17[0], 0);
		v15 = FindWindowA(ClassName, WindowName);
		if (v15)
			PostMessageA(v15, Msg, 4u, 0);
	}
	return 0;
}
