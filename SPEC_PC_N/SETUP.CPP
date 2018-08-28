#include "SETUP.H"
#include "SPECIFIC.H"
#include "INCLUDE.H"
#include "GLOBAL.H"
#include "resource.h"
#include "GAMEFLOW.H"
#include "INPUT.H"

Settings appsettings;
HKEY reg_key;
DWORD reg_disp;
BOOL settings_present;
LPSTR reg_class;

int16_t opt_JDck = 5;
int16_t opt_JDsh = 3;
int16_t opt_JWlk = 4;
int16_t opt_JJmp = 0;
int16_t opt_JAct = 1;
int16_t opt_JDrw = 2;
int16_t opt_JFlr = 9;
int16_t opt_JLok = 6;
int16_t opt_JRol = 7;
int16_t opt_JInv = 8;
uint8_t opt_MusicVolume = 40;
uint8_t opt_SFXVolume = 80;
uint8_t opt_ControlMethod;
uint8_t opt_SoundQuality = 1;


const char* reg_path = "Software\\Core Design\\Tomb Raider Chronicles";

void CLNoFMV(char* arg)// (F)
{
	Log(LT_Enter, "CLNoFMV");
	appsettings.NoFMV = arg == nullptr;
}

void CLSetup(char* arg)// (F)
{
	Log(LT_Enter, "CLSetup");
	appsettings.OpenSetup = arg == nullptr;
}

BYTE oemToIso[10] = { 0x82, 0xE9, 0x8A, 0xE8, 0x88, 0xEA, 0x94, 0xF6, 0x85, 0xE0 };

char* LoadToISO(const char* instr, char* outbuf)// (F)
{
	char* bufptr = outbuf;

	char curchar;
	while ((curchar = *instr++) != 0)
	{
		if (curchar >= 128)
		{
			int i;
			for (i = 0; i < 10; i += 2)
			{
				if (curchar == oemToIso[i])
				{
					curchar = oemToIso[i + 1];
					break;
				}
			}

			if (i == 10)
			{
				Log(LT_Error, "Reqd : %x", curchar);
			}
		}

		*bufptr++ = curchar;
	}

	*bufptr = 0;

	return outbuf;
}

void LoadGraphicsAdapters(HWND hDlg, HWND hWnd)
{
	Unimpl();
}

void LoadSoundAdapters(HWND hDlg, HWND hWnd)
{
	Unimpl();
}

INT_PTR CALLBACK DialogFunc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)// (F)
{
	switch(uMsg)
	{
	case WM_INITDIALOG:
		Log(LT_WindowMessage, "WM_INITDIALOG");

		if (Gameflow->Language == LNG_JAPAN)
		{
			auto obj = GetStockObject(SYSTEM_FONT);
			SendMessageA(GetDlgItem(hDlg, IDC_GFXADAPTER), WM_SETFONT, 0, (LPARAM)obj);
			SendMessageA(GetDlgItem(hDlg, IDC_OUTSETTINGS), WM_SETFONT, 0, (LPARAM)obj);
			SendMessageA(GetDlgItem(hDlg, IDC_RESOLUTION), WM_SETFONT, 0, (LPARAM)obj);
			SendMessageA(GetDlgItem(hDlg, IDC_TEXRES), WM_SETFONT, 0, (LPARAM)obj);
			SendMessageA(GetDlgItem(hDlg, IDC_SNDADAPTER), WM_SETFONT, 0, (LPARAM)obj);
		}

		char buf[256];

		SendMessageA(GetDlgItem(hDlg, IDC_GFXADAPTERTXT), WM_SETTEXT, 0, (LPARAM)LoadToISO(&gfStringWad[gfStringOffset[STR_GRAPHICS_ADAPTER]], buf));
		SendMessageA(GetDlgItem(hDlg, IDC_OUTSETTINGSTXT), WM_SETTEXT, 0, (LPARAM)LoadToISO(&gfStringWad[gfStringOffset[STR_OUTPUT_SETTINGS]], buf));
		SendMessageA(GetDlgItem(hDlg, IDOK), WM_SETTEXT, 0, (LPARAM)LoadToISO(&gfStringWad[gfStringOffset[STR_OK_BIS]], buf));
		SendMessageA(GetDlgItem(hDlg, IDCANCEL), WM_SETTEXT, 0, (LPARAM)LoadToISO(&gfStringWad[gfStringOffset[STR_CANCEL_BIS_BIS]], buf));
		SendMessageA(GetDlgItem(hDlg, IDC_RESOLUTIONTXT), WM_SETTEXT, 0, (LPARAM)LoadToISO(&gfStringWad[gfStringOffset[STR_OUTPUT_RESOLUTION]], buf));
		SendMessageA(GetDlgItem(hDlg, IDC_BILINEAR), WM_SETTEXT, 0, (LPARAM)LoadToISO(&gfStringWad[gfStringOffset[STR_BILINEAR_FILTERING]], buf));
		SendMessageA(GetDlgItem(hDlg, IDC_BUMPMAP), WM_SETTEXT, 0, (LPARAM)LoadToISO(&gfStringWad[gfStringOffset[STR_BUMP_MAPPING]], buf));
		SendMessageA(GetDlgItem(hDlg, IDC_HARDACCEL), WM_SETTEXT, 0, (LPARAM)LoadToISO(&gfStringWad[gfStringOffset[STR_HARDWARE_ACCELERATION]], buf));
		SendMessageA(GetDlgItem(hDlg, IDC_SOFTWARE), WM_SETTEXT, 0, (LPARAM)LoadToISO(&gfStringWad[gfStringOffset[STR_SOFTWARE_MODE]], buf));
		SendMessageA(GetDlgItem(hDlg, IDC_SNDADAPTERTXT), WM_SETTEXT, 0, (LPARAM)LoadToISO(&gfStringWad[gfStringOffset[STR_SOUND_DEVICE]], buf));
		SendMessageA(GetDlgItem(hDlg, IDC_NOSOUND), WM_SETTEXT, 0, (LPARAM)LoadToISO(&gfStringWad[gfStringOffset[STR_DISABLE]], buf));
		SendMessageA(GetDlgItem(hDlg, IDC_LOWTEXT), WM_SETTEXT, 0, (LPARAM)LoadToISO(&gfStringWad[gfStringOffset[STR_LOW_RESOLUTION_TEXTURES]], buf));
		SendMessageA(GetDlgItem(hDlg, IDC_LOWBUMP), WM_SETTEXT, 0, (LPARAM)LoadToISO(&gfStringWad[gfStringOffset[STR_LOW_RESOLUTION_BUMP_MAPS]], buf));
		SendMessageA(GetDlgItem(hDlg, IDC_TEXRESTXT), WM_SETTEXT, 0, (LPARAM)LoadToISO(&gfStringWad[gfStringOffset[STR_TEXTURE_BIT_DEPTH]], buf));
		SendMessageA(GetDlgItem(hDlg, IDC_WINDOWED), WM_SETTEXT, 0, (LPARAM)LoadToISO(&gfStringWad[gfStringOffset[STR_WINDOWED]], buf));
		SendMessageA(GetDlgItem(hDlg, IDC_RENDEROPTIONS), WM_SETTEXT, 0, (LPARAM)LoadToISO(&gfStringWad[gfStringOffset[STR_RENDER_OPTIONS]], buf));
		SendMessageA(GetDlgItem(hDlg, IDC_VOLUMEFOG), WM_SETTEXT, 0, (LPARAM)LoadToISO(&gfStringWad[gfStringOffset[STR_VOLUMETRIC_FX]], buf));
		SendMessageA(GetDlgItem(hDlg, IDC_NOFMV), WM_SETTEXT, 0, (LPARAM)LoadToISO(&gfStringWad[gfStringOffset[STR_NO_FMV]], buf));

		LoadGraphicsAdapters(hDlg, GetDlgItem(hDlg, IDC_GFXADAPTER));
		LoadSoundAdapters(hDlg, GetDlgItem(hDlg, IDC_SNDADAPTER));

		return 1;

	case WM_COMMAND:
		return 0;// TODO TODO TODO
		if (lParam)
			DeleteObject((HGDIOBJ)lParam);

		EndDialog(hDlg, 1);

		return 1;
	}

	return 0;
}

bool InitSetupDialog()// (F)
{
	ShowCursor(true);
	INT_PTR res = DialogBoxParamA(App.hInstance, (LPCSTR)IDD_SETUP, nullptr, DialogFunc, 0);
	ShowCursor(false);

	if (res == -1)
	{
		MessageBoxA(nullptr, "Unable To Initialise Dialog", reg_class, 0);
		return false;
	}

	return res != 0;
}

BOOL CreateRegKeyRW(LPCSTR lpSubKey)// (F)
{
	return RegCreateKeyExA(HKEY_CURRENT_USER, lpSubKey, 0, reg_class, 0, KEY_ALL_ACCESS, nullptr, &reg_key, &reg_disp) == ERROR_SUCCESS;
}

BOOL CreateKey(char* sub)// (F)
{
	if (sub == nullptr)
		return CreateRegKeyRW(reg_path);

	char subkey[256];
	sprintf(subkey, "%s\\%s", reg_path, sub);
	return CreateRegKeyRW(subkey);
}

void RegWrite(LPCSTR name, DWORD data)// (F)
{
	RegSetValueExA(reg_key, name, 0, 4, (BYTE*)&data, sizeof(DWORD));
}

void RegWriteMulti(LPCSTR name, ...)// (F)
{
	va_list data;
	va_start(data, name);
	RegSetValueExA(reg_key, name, 0, 4, (BYTE*)data, 4);
}

bool RegReadBool(LPCSTR name, void* out, BYTE def)// (F)
{
	DWORD cb = 4;
	DWORD type;
	DWORD buf;
	if (RegQueryValueExA(reg_key, name, nullptr, &type, (BYTE*)&buf, &cb) == ERROR_SUCCESS && type == 4 && cb == 4)
	{
		*(BYTE*)out = buf != 0;
		return true;
	}
	else
	{
		RegWrite(name, def);
		*(BYTE*)out = def;
		return false;
	}
}

bool RegReadInt(LPCSTR name, void* out, int def)// (F)
{
	DWORD cb = 4;
	DWORD type;
	if (RegQueryValueExA(reg_key, name, nullptr, &type, (BYTE*)out, &cb) == ERROR_SUCCESS && type == 4 && cb == 4)
	{
		return true;
	}
	else
	{
		RegWriteMulti(name, def);
		*(int*)out = def;
		return false;
	}
}

void SaveSettings()
{
	Unimpl();
}

void CheckKeyConflicts()// (F)
{
	for(int i = 0; i < 18; i++)
	{
		conflict[i] = false;

		for(int j = 0; j < 18; j++)
		{
			if (layout[1][i] == layout[0][i])
			{
				conflict[i] = true;
				break;
			}
		}
	}
}

bool LoadSettings()// (F)
{
	if (!CreateKey("System"))
		return false;

	RegReadBool("Setup", &settings_present, 0);

	if (settings_present)
	{
		App.textRes = 256;
		App.bumpRes = 256;
		App.orig_flags = WA_FPUSETUP;

		RegReadInt("DD", &App.DXConfig.nDD, 0);
		RegReadInt("D3D", &App.DXConfig.nD3D, 0);
		RegReadInt("VMode", &App.DXConfig.nVMode, 0);
		RegReadInt("TFormat", &App.DXConfig.nTexture, 0);
		RegReadInt("DS", &App.DXConfig.nSoundCard, 0);

		RegReadBool("BumpMap", &App.tBumpMap, 1);
		RegReadBool("Filter", &App.tBilinearFilter, 1);
		RegReadBool("DisableSound", &App.tDisableSound, 0);
		RegReadBool("Volumetric" ,&App.tVolumetricShadows, 1);
		RegReadBool("NoFMV", &appsettings.NoFMV, 0);

		bool tmp = false;

		RegReadBool("TextLow", &tmp, 0);
		if (tmp)
			App.textRes = 128;

		RegReadBool("BumpLow", &tmp, 0);
		if (tmp)
			App.bumpRes = 128;

		RegReadBool("HardWare", &tmp, 1);
		if (tmp)
			App.orig_flags |= WA_BACK_BUFFER | WA_UNKNOWN2;

		RegReadBool("Window", &tmp, 0);
		if (tmp)
			App.orig_flags |= WA_WINDOWED;
		else
			App.orig_flags |= WA_FULLSCREEN;
	}

	CreateKey("Game");

	for(int i = 0; i < 18; i++)
	{
		int tmp;
		char buf[6];
		sprintf(buf, "Key%d", i);
		RegReadInt(buf, &tmp, layout[0][i]);
		layout[1][i] = tmp;
	}

	RegReadInt("JDck", &opt_JDck, 5);
	RegReadInt("JDsh", &opt_JDsh, 3);
	RegReadInt("JWlk", &opt_JWlk, 4);
	RegReadInt("JJmp", &opt_JJmp, 0);
	RegReadInt("JAct", &opt_JAct, 1);
	RegReadInt("JDrw", &opt_JDrw, 2);
	RegReadInt("JFlr", &opt_JFlr, 9);
	RegReadInt("JLok", &opt_JLok, 6);
	RegReadInt("JRol", &opt_JRol, 7);
	RegReadInt("JInv", &opt_JInv, 8);

	RegReadInt("MusicVolume", &opt_MusicVolume, 80);
	RegReadInt("SFXVolume", &opt_SFXVolume, 90);
	RegReadInt("ControlMethod", &opt_ControlMethod, 0);
	RegReadInt("SoundQuality", &opt_SoundQuality, 1);
	RegReadInt("AutoTarget", &App.tAutoTarget, 1);
	RegReadInt("WindowX", &App.GnWindowRect.left, 0);
	RegReadInt("WindowY", &App.GnWindowRect.top, 0);

	CheckKeyConflicts();

	return settings_present;
}