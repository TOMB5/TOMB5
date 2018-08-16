#include "SETUP.H"
#include "SPECIFIC.H"
#include "INCLUDE.H"
#include "GLOBAL.H"
#include "../SPEC_PC/SPECTYPES.H"

Settings appsettings;
HKEY reg_key;
DWORD reg_disp;
BOOL settings_present;
LPSTR reg_class;
int16_t default_keys[18] = { 200, 208, 203, 205, 52, 53, 54, 184, 157, 57, 51, 82, 207, 1, 211, 209, 25, 28 };
int16_t opt_Keys[18] = { 200, 208, 203, 205, 52, 53, 54, 184, 157, 57, 51, 82, 207, 1, 211, 209, 25, 28 };
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

void CLNoFMV(char* arg)
{
	Log(LT_Enter, "CLNoFMV");
	appsettings.NoFMV = arg == nullptr;
}

void CLSetup(char* arg)
{
	Log(LT_Enter, "CLSetup");
	appsettings.OpenSetup = arg == nullptr;
}

bool InitSetupDialog()
{
	Unimpl();
	return false;
}

BOOL CreateRegKeyRW(LPCSTR lpSubKey)
{
	return RegCreateKeyExA(HKEY_CURRENT_USER, lpSubKey, 0, reg_class, 0, KEY_ALL_ACCESS, nullptr, &reg_key, &reg_disp) == ERROR_SUCCESS;
}

BOOL CreateKey(char* sub)
{
	if (sub == nullptr)
		return CreateRegKeyRW(reg_path);

	char subkey[256];
	sprintf(subkey, "%s\\%s", reg_path, sub);
	return CreateRegKeyRW(subkey);
}

void RegWrite(LPCSTR name, DWORD data)
{
	RegSetValueExA(reg_key, name, 0, 4, (BYTE*)&data, sizeof(DWORD));
}

void RegWriteMulti(LPCSTR name, ...)
{
	va_list data;
	va_start(data, name);
	RegSetValueExA(reg_key, name, 0, 4, (BYTE*)data, 4);
}

bool RegReadBool(LPCSTR name, void* out, BYTE def)
{
	DWORD cb = 4;
	DWORD type;
	DWORD buf;
	if (RegQueryValueExA(reg_key, name, 0, &type, (BYTE*)&buf, &cb) == ERROR_SUCCESS && type == 4 && cb == 4)
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

bool RegReadInt(LPCSTR name, void* out, int def)
{
	DWORD cb = 4;
	DWORD type;
	if (RegQueryValueExA(reg_key, name, 0, &type, (BYTE*)out, &cb) == ERROR_SUCCESS && type == 4 && cb == 4)
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

void CheckKeyConflicts()
{
	for(int i = 0; i < 18; i++)
	{
		for(int j = 0; j < 18; j++)
		{
			if ()
		}
	}
}

bool LoadSettings()
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
			App.orig_flags |= WA_UNKNOWN1;
		else
			App.orig_flags |= WA_FULLSCREEN;
	}

	CreateKey("Game");

	for(int i = 0; i < 18; i++)
	{
		int tmp;
		char buf[6];
		sprintf(buf, "Key%d", i);
		RegReadInt(buf, &tmp, default_keys[i]);
		opt_Keys[i] = tmp;
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