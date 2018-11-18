#include "DEBUG.H"
#include "GLOBAL.H"
#include "INPUT.H"
#include "CONTROL.H"
#include "DISPLAY.H"
#include "DRAWPRIMITIVE.H"
#include "GAMEFLOW.H"
#include "DELTAPAK.H"
#include "PICTURE.H"
#include "DIRECTX.H"

UINT dbm_logout, dbm_clearlog, dbm_deftype, dbm_command;
DWORD dbginput;
FILE* fplog;

void DB_InitLog(char opt)
{
	dbm_logout = RegisterWindowMessageA("UM_DBLOGOUT");
	dbm_clearlog = RegisterWindowMessageA("UM_DBCLEARLOG");
	dbm_deftype = RegisterWindowMessageA("UM_DBDEFTYPE");
	dbm_command = RegisterWindowMessageA("UM_DBCOMMAND");

	fplog = fopen("trlog.txt", "w");
	
	/*HKEY phkResult;
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
	}*/
}

static int dboff = 0;

void SendMsg(HWND hWnd, LPARAM lParam)// (F)
{
	do
	{
		if (PostMessageA(hWnd, dbm_logout, 0, lParam))
			break;
	} while (FindWindowA("DBLogWindowClass", "DBLog Server"));
}

void DB_DefType(char* name, LPARAM lParam, WPARAM wParam)// (F)
{
	HWND dblog = FindWindowA("DBLogWindowClass", "DBLog Server");

	if (dblog)
	{
		HANDLE db = OpenFileMappingA(FILE_MAP_READ | FILE_MAP_WRITE, true, "DBLOGMAPMEM");
		void* map = MapViewOfFile(db, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, 0x100000u);

		if (map)
		{
			strcpy((char*)map, name);
			SendMessageA(dblog, dbm_deftype, wParam, lParam);
		}
	}
}

void Log_backend(char type, char* fmt, ...)// (F)
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
			char* bptr = addr + 1;

			for (int i = 0, run = 1; i < len + 1; i++, run++)
			{
				if (buf[i] != '\n' && buf[i] != '\0')
				{
					*bptr++ = buf[i];
				}
				else
				{
					if (run > 1)
					{
						*bptr = 0;
						SendMsg(dblog, dboff);
						bptr++;
						dboff += run + 1;
						*bptr++ = type;
					}

					run = 0;
				}
			}

			if (dboff > 0xFFC00)
			{
				dboff = 0;
				SendMessageA(dblog, dbm_clearlog, 0, 0);
			}

			CloseHandle(db);
		}
	}
}

void GetInputStr(char* buf)// (F)
{
	const char* names[] = {
		"FORWARD",
		"BACK",
		"LEFT",
		"RIGHT",
		"JUMP",
		"DRAW",
		"ACTION",
		"WALK",
		"OPTION",
		"LOOK",
		"LSTEP",
		"RSTEP",
		"ROLL",
		"PAUSE",
		"A",
		"B",
		"CHEAT",
		"D",
		"E",
		"FLARE",
		"SELECT",
		"DESELECT",
		"SAVE",
		"LOAD",
		"STEPSHIFT",
		"LOOKLEFT",
		"LOOKRIGHT",
		"LOOKFORWARD",
		"LOOKBACK",
		"DUCK",
		"SPRINT",
		"UNK31",
	};

	buf[0] = 0;

	if (dbginput == IN_NONE)
	{
		strcpy(buf, "---");
	}
	else
	{
		for(int i = 0; i < 32; i++)
		{
			if (dbginput & (1 << i))
			{
				strcat(buf, names[i]);
				strcat(buf, ", ");
			}
		}

		buf[strlen(buf) - 2] = 0;
	}
}

int cur_tpage = 0;

void DrawDebugPre()
{
	D3DTLVERTEX v1, v2;
	v1.sx = 0;
	v1.sy = 0;
	v1.sz = f_znear;
	v1.color = RGBA(255, 0, 0, 255);
	v1.specular = RGBA(0, 255, 255, 255);
	v1.rhw = f_persp / f_znear * f_oneopersp;

	v2.sx = 500;
	v2.sy = 500;
	v2.sz = f_znear;
	v2.color = RGBA(0, 255, 0, 255);
	v2.specular = RGBA(255, 255, 0, 255);
	v2.rhw = f_persp / f_znear * f_oneopersp;

	AddLine(&v1, &v2, 6);
}

void DrawDebugPost()
{
	DDBLTFX fx;
	DXInit(fx);
	//fx.dwFillColor = GENRGB(0, 0, (5 * GnFrameCounter) % 256);
	fx.dwFillColor = (64 + abs((int)((2 * GnFrameCounter) % 192 - 96))) << (8 * (((GnFrameCounter / 6) % 27) / 9));
	App.lpBackBuffer->Blt(nullptr, nullptr, nullptr, DDBLT_COLORFILL | DDBLT_WAIT, &fx);

	RECT dest{ 256, 256, 512, 512 };
	RECT src{ 0, 0, DXTextureList[cur_tpage].width, DXTextureList[cur_tpage].height };
	Log(LT_Info, "Debug draw %08x", DXTextureList[cur_tpage].surface);
	DX_TRY(App.lpBackBuffer->Blt(&dest, DXTextureList[cur_tpage].surface, &src, DDBLT_WAIT, nullptr));
}

void ShowDebugInfo()// (F)
{
	char buf[2048];
	sprintf(buf,
		"FPS : %3.2f\n"
		"Game frame : %d\n"
		"Mouse : %4d ; %4d\n"
		"Game mode : %d\n"
		"Malloc : %5dK (%3d%%) used - %5dK free - %5dK total\n"
		"Current : level #%02d / cutseq #%02d (playing=%5s)\n"
		"DrawPrimitive calls : %9d\n"
		"BF list : %6d\n"
		"Texture page : %2d (%3d x %3d)\n"
		"Input : ", App.fps, GnFrameCounter, mouse_x, mouse_y, gfGameMode, malloc_used / 1024, (int)(malloc_used * 100.0 / malloc_size), malloc_free / 1024, malloc_size / 1024,
		gfCurrentLevel, cutseq_num, GLOBAL_playing_cutseq ? "TRUE" : "FALSE", App.DrawPrimitiveCnt, surfacenumbf, 
		cur_tpage, DXTextureList[cur_tpage].width, DXTextureList[cur_tpage].height);
	GetInputStr(buf + strlen(buf));
	PrintString(10, 10, 0, buf, 0);

	if (keymap[DIK_U])
	{
		cur_tpage--;
		if (cur_tpage < 0)
			cur_tpage = 0;
	}
	if (keymap[DIK_I])
	{
		cur_tpage++;
		if (cur_tpage > 63)
			cur_tpage = 63;
	}
}