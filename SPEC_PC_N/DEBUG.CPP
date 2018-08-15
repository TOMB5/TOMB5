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

static int dboff = 0;

void SendMsg(HWND hWnd, LPARAM lParam)
{
	do
	{
		if (PostMessageA(hWnd, dbm_logout, 0, lParam))
			break;
	} while (FindWindowA("DBLogWindowClass", "DBLog Server"));
}

void Log_backend(char type, char* fmt, ...)
{
	char buf[1024];

	va_list argptr;
	va_start(argptr, fmt);
	vsprintf(buf, fmt, argptr);
	va_end(argptr);

	int len = strlen(buf);

	HWND dblog = FindWindowA("DBLogWindowClass", "DBLog Server");

	if (dblog)
	{
		HANDLE db = OpenFileMappingA(FILE_MAP_READ | FILE_MAP_WRITE, true, "DBLOGMAPMEM");
		void* map = MapViewOfFile(db, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, 0x100000u);

		if (map)
		{
			char* addr = (char*)map + dboff;
			*addr = type;
			strcpy(addr + 1, buf);

			SendMsg(dblog, dboff);

			dboff += strlen(buf) + 1;

			if (dboff > 0xFFC00)
			{
				dboff = 0;
				SendMessageA(dblog, dbm_clearlog, 0, 0);
			}

			CloseHandle(db);
		}
	}
}