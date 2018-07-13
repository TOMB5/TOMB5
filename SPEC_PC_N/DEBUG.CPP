#include "DEBUG.H"
#include "GLOBAL.H"

UINT dbm_logout, dbm_clearlog, dbm_deftype, dbm_command;

void DB_InitLog(char opt)
{
	dbm_logout = RegisterWindowMessageA("UM_DBLOGOUT");
	dbm_clearlog = RegisterWindowMessageA("UM_DBCLEARLOG");
	dbm_deftype = RegisterWindowMessageA("UM_DBDEFTYPE");
	dbm_command = RegisterWindowMessageA("UM_DBCOMMAND");
	
	HKEY phkResult;
	DWORD dwDisposition, cbData, Type;
	BYTE Data[1024];
	STARTUPINFO StartupInfo;
	PROCESS_INFORMATION ProcessInformation;

	if (opt & 1
		&& !RegCreateKeyExA(HKEY_LOCAL_MACHINE, "Software\Core\DBlog", REG_OPTION_NON_VOLATILE, nullptr, 0, KEY_ALL_ACCESS, nullptr, &phkResult, &dwDisposition)
		&& dwDisposition == 2)
	{
		memset(&Data, 0, 0x400u);

		Type = 1;
		cbData = 1024;

		RegQueryValueExA(phkResult, "CmdLine", nullptr, &Type, Data, &cbData);
		memset(&StartupInfo, 0, sizeof(StartupInfo));

		StartupInfo.cb = 68;

		if (!CreateProcessA(nullptr, (LPSTR)Data, nullptr, nullptr, 0, 0, nullptr, nullptr, &StartupInfo, &ProcessInformation))
			GetLastError();

		WaitForInputIdle(ProcessInformation.hProcess, 0xFFFFFFFF);
		RegCloseKey(phkResult);
	}
}