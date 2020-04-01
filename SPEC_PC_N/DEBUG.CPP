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
#include "CAMERA.H"
#include "FILE.H"

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

void GetInputStr(DWORD in, char* buf)// (F)
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

	if (in == IN_NONE)
	{
		strcpy(buf, "---");
	}
	else
	{
		for(int i = 0; i < 32; i++)
		{
			if (in & (1 << i))
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
	/*D3DTLVERTEX v1, v2;
	v1.sx = 0;
	v1.sy = 0;
	v1.sz = f_znear;
	v1.color = RGBA(0, 0, 255, 255);
	v1.specular = RGBA(0, 255, 255, 255);
	v1.rhw = f_persp / f_znear * f_oneopersp;

	v2.sx = 500;
	v2.sy = 500;
	v2.sz = f_znear;
	v2.color = RGBA(0, 255, 0, 255);
	v2.specular = RGBA(255, 255, 0, 255);
	v2.rhw = f_persp / f_znear * f_oneopersp;

	AddLine(&v1, &v2, 6);*/
}

void DrawDebugPost()
{
	return;
	DDBLTFX fx;
	DXInit(fx);
	//fx.dwFillColor = GENRGB(0, 0, (5 * GnFrameCounter) % 256);
	fx.dwFillColor = (64 + abs((int)((2 * GnFrameCounter) % 192 - 96))) << (8 * (((GnFrameCounter / 6) % 27) / 9));
	//App.lpBackBuffer->Blt(nullptr, nullptr, nullptr, DDBLT_COLORFILL | DDBLT_WAIT, &fx);

	RECT dest{ 256, 256, 512, 512 };
	RECT src{ 0, 0, DXTextureList[cur_tpage].width, DXTextureList[cur_tpage].height };
	Log(LT_Info, "Debug draw %08x - %2d (%3d x %3d)", DXTextureList[cur_tpage].surface, cur_tpage, DXTextureList[cur_tpage].width, DXTextureList[cur_tpage].height);
	//DX_TRY(App.lpBackBuffer->Blt(&dest, DXTextureList[cur_tpage].surface, &src, DDBLT_WAIT, nullptr));
	DX_TRY(App.lpBackBuffer->Blt(nullptr, DXTextureList[cur_tpage].surface, nullptr, DDBLT_WAIT, nullptr));
	//

	D3DMATERIAL7 mtrl;
	ZeroMemory(&mtrl, sizeof(mtrl));
	mtrl.ambient.r = 1.0f;
	mtrl.ambient.g = 1.0f;
	mtrl.ambient.b = 0.0f;
	App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_AMBIENT, 0xffffffff);

	// Start by setting up an identity matrix.
	D3DMATRIX mat;
	mat._11 = mat._22 = mat._33 = mat._44 = 1.0f;
	mat._12 = mat._13 = mat._14 = mat._41 = 0.0f;
	mat._21 = mat._23 = mat._24 = mat._42 = 0.0f;
	mat._31 = mat._32 = mat._34 = mat._43 = 0.0f;

	// The world matrix controls the position and orientation 
	// of the polygons in world space. We'll use it later to 
	// spin the triangle.
	D3DMATRIX matWorld = mat;
	//App.lpD3DDevice->SetTransform(D3DTRANSFORMSTATE_WORLD, &matWorld);

	// The view matrix defines the position and orientation of 
	// the camera. Here, we are just moving it back along the z-
	// axis by 10 units.
	D3DMATRIX matView = mat;
	matView._43 = 30.0f;
	//App.lpD3DDevice->SetTransform(D3DTRANSFORMSTATE_VIEW, &matView);

	// The projection matrix defines how the 3-D scene is "projected" 
	// onto the 2-D render target surface. For more information,
	// see "What Is the Projection Transformation?"
	float fTimeKey = cur_tpage / 500.0f;
	// Set up a very simple projection that scales x and y 
	// by 2, and translates z by -1.0.
	D3DMATRIX matProj = mat;
	matProj._11 = 2.0f;
	matProj._22 = 2.0f;
	matProj._34 = 1.0f;
	matProj._43 = -1.0f;
	matProj._44 = 0.0f;
	//App.lpD3DDevice->SetTransform(D3DTRANSFORMSTATE_PROJECTION, &matProj);

	D3DMATRIX matSpin;
	matSpin._11 = matSpin._22 = matSpin._33 = matSpin._44 = 1.0f;
	matSpin._12 = matSpin._13 = matSpin._14 = matSpin._41 = 0.0f;
	matSpin._21 = matSpin._23 = matSpin._24 = matSpin._42 = 0.0f;
	matSpin._31 = matSpin._32 = matSpin._34 = matSpin._43 = 0.0f;

	matSpin._11 = (FLOAT)cos(fTimeKey);
	matSpin._33 = (FLOAT)cos(fTimeKey);
	matSpin._13 = -(FLOAT)sin(fTimeKey);
	matSpin._31 = (FLOAT)sin(fTimeKey);

	//App.lpD3DDevice->SetTransform(D3DTRANSFORMSTATE_WORLD, &matSpin);

	//S_InitD3DMatrix();
	//SetD3DViewMatrix();
	//DX_TRY(App.lpD3DDevice->SetTransform(D3DTRANSFORMSTATE_VIEW, &w2v_matrix_d3d));
	//
	//D3DMATRIX test(0.982, 0.012, 0.189, 0, 0, 0.998, -0.066, 0, -0.189, 0.065, 0.98, 0, 6445.135, 1617.68, 715.305, 1);
	//DX_TRY(App.lpD3DDevice->SetTransform(D3DTRANSFORMSTATE_VIEW, &test));

	{
		D3DVECTOR p1{ 1900.0f, 000.0f, 0.2f };
		D3DVECTOR p2{ 2200.0f, -600.0f, 0.2f };
		D3DVECTOR p3{ 100.0f, -600.0f, 0.2f };
		D3DVECTOR vNormal{ 0.0f, 0.0f, 1.0f };
		// Initialize the 3 vertices for the front of the triangle
		D3DVERTEX g_pvTriangleVertices[6];
		g_pvTriangleVertices[0] = D3DVERTEX(p1, vNormal, 0, 0);
		g_pvTriangleVertices[1] = D3DVERTEX(p2, vNormal, 1, 0);
		g_pvTriangleVertices[2] = D3DVERTEX(p3, vNormal, 1, 1);

		// Initialize the 3 vertices for the back of the triangle
		g_pvTriangleVertices[3] = D3DVERTEX(p1, -vNormal, 0, 0);
		g_pvTriangleVertices[4] = D3DVERTEX(p3, -vNormal, 0, 1);
		g_pvTriangleVertices[5] = D3DVERTEX(p2, -vNormal, 1, 1);
		/*App.lpD3DDevice->SetTexture(0, DXTextureList[1].tex);
		App.lpD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, D3DFVF_VERTEX,
			g_pvTriangleVertices, 6, NULL);*/
	}

	{
		D3DVECTOR p1{ 0, 0, 0.2f };
		D3DVECTOR p2{ 300, 0, 0.2f };
		D3DVECTOR p3{ 300, -300, 0.2f };
		D3DVECTOR p4{ 0, -300, 0.2f };
		D3DVECTOR vNormal{ 0.0f, 0.0f, 1.0f };
		// Initialize the 3 vertices for the front of the triangle
		D3DVERTEX g_pvTriangleVertices[12];
		g_pvTriangleVertices[0] = D3DVERTEX(p1, vNormal, 0, 0);
		g_pvTriangleVertices[1] = D3DVERTEX(p2, vNormal, 1, 0);
		g_pvTriangleVertices[2] = D3DVERTEX(p3, vNormal, 1, 1);

		g_pvTriangleVertices[3] = D3DVERTEX(p1, vNormal, 0, 0);
		g_pvTriangleVertices[4] = D3DVERTEX(p3, vNormal, 1, 1);
		g_pvTriangleVertices[5] = D3DVERTEX(p4, vNormal, 0, 1);


		g_pvTriangleVertices[6] = D3DVERTEX(p1, -vNormal, 0, 0);
		g_pvTriangleVertices[7] = D3DVERTEX(p2, -vNormal, 1, 0);
		g_pvTriangleVertices[8] = D3DVERTEX(p3, -vNormal, 1, 1);

		g_pvTriangleVertices[9] = D3DVERTEX(p1, -vNormal, 0, 0);
		g_pvTriangleVertices[10] = D3DVERTEX(p3, -vNormal, 1, 1);
		g_pvTriangleVertices[11] = D3DVERTEX(p4, -vNormal, 0, 1);

		/*App.lpD3DDevice->SetTexture(0, DXTextureList[1].tex);
		App.lpD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, D3DFVF_VERTEX,
			g_pvTriangleVertices, 12, NULL);*/
	}

}

void ShowDebugInfo()// (F)
{
	if (!info3dptrbf)
		return;

	//PrintString(0, 25, 0, "Unregistered HyperCam 2", 0);
	
	char buf[2048];
	sprintf(buf,
		"FPS : %3.2f, game frame : %d\n"
		"Mouse : %4d ; %4d\n"
		"Game mode : %d\n"
		"Malloc : %5dK (%3d%%) used - %5dK free - %5dK total\n"
		"Current : level #%02d / cutseq #%02d (playing=%5s)\n"
		"DrawPrimitive calls : %4d / %4d\n"
	/*	"ViewMatrix\t WorldMatrix\t Projection\t W2V\n"
		"(%.3f,%.3f,%.3f,%.3f)\t(%.3f,%.3f,%.3f,%.3f)\t(%.3f,%.3f,%.3f,%.3f)\t(%.3f,%.3f,%.3f,%.3f)\n"
		"(%.3f,%.3f,%.3f,%.3f)\t(%.3f,%.3f,%.3f,%.3f)\t(%.3f,%.3f,%.3f,%.3f)\t(%.3f,%.3f,%.3f,%.3f)\n"
		"(%.3f,%.3f,%.3f,%.3f)\t(%.3f,%.3f,%.3f,%.3f)\t(%.3f,%.3f,%.3f,%.3f)\t(%.3f,%.3f,%.3f,%.3f)\n"
		"(%.3f,%.3f,%.3f,%.3f)\t(%.3f,%.3f,%.3f,%.3f)\t(%.3f,%.3f,%.3f,%.3f)\t(%.3f,%.3f,%.3f,%.3f)\n"*/
		"BF list : %6d\n"
		"Playing XA : %3d (%s)\n"
		"Camera : %d (%5d ; %5d ; %5d) room %3d\n"
		"Input : ", App.fps, GnFrameCounter, mouse_x, mouse_y, gfGameMode, malloc_used / 1024, (int)(malloc_used * 100.0 / malloc_size), malloc_free / 1024, malloc_size / 1024,
		gfCurrentLevel, cutseq_num, GLOBAL_playing_cutseq ? "TRUE" : "FALSE", App.DrawPrimitiveCnt, App.DrawPrimitiveCntBuk,
		/*App.ViewMatrix._11, App.ViewMatrix._12, App.ViewMatrix._13, App.ViewMatrix._14, App.WorldMatrix._11, App.WorldMatrix._12, App.WorldMatrix._13, App.WorldMatrix._14, transform_projection._11, transform_projection._12, transform_projection._13, transform_projection._14, w2v_matrix_d3d._11, w2v_matrix_d3d._12, w2v_matrix_d3d._13, w2v_matrix_d3d._14,
		App.ViewMatrix._21, App.ViewMatrix._22, App.ViewMatrix._23, App.ViewMatrix._24, App.WorldMatrix._21, App.WorldMatrix._22, App.WorldMatrix._23, App.WorldMatrix._24, transform_projection._21, transform_projection._22, transform_projection._23, transform_projection._24, w2v_matrix_d3d._21, w2v_matrix_d3d._22, w2v_matrix_d3d._23, w2v_matrix_d3d._24,
		App.ViewMatrix._31, App.ViewMatrix._32, App.ViewMatrix._33, App.ViewMatrix._34, App.WorldMatrix._31, App.WorldMatrix._32, App.WorldMatrix._33, App.WorldMatrix._34, transform_projection._31, transform_projection._32, transform_projection._33, transform_projection._34, w2v_matrix_d3d._31, w2v_matrix_d3d._32, w2v_matrix_d3d._33, w2v_matrix_d3d._34,
		App.ViewMatrix._41, App.ViewMatrix._42, App.ViewMatrix._43, App.ViewMatrix._44, App.WorldMatrix._41, App.WorldMatrix._42, App.WorldMatrix._43, App.WorldMatrix._44, transform_projection._41, transform_projection._42, transform_projection._43, transform_projection._44, w2v_matrix_d3d._41, w2v_matrix_d3d._42, w2v_matrix_d3d._43, w2v_matrix_d3d._44,*/
		surfacenumbf, 
		XATrack, XATrack == -1 ? "---" : xa_filenames[XATrack],
		camera.type, camera.pos.x, camera.pos.y, camera.pos.z, camera.pos.room_number);
	GetInputStr(dbginput, buf + strlen(buf));
	strcat(buf, " / ");
	GetInputStr(dbinput, buf + strlen(buf));
	PrintString(10, 24, 6, buf, 0);

	float s = 100;
	float ox = 500;
	float oy = 300;
	D3DTLVERTEX v[4] =
	{
		{{ox + 0, oy + 0, 0.1}, 0.1, 0xFFFFFFFF, 0xFF000000, 1, 1},
		{{ox + s, oy + 0, 0.1}, 0.1, 0xFFFFFFFF, 0xFF000000, 1, 1},
		{{ox + s, oy + s, 0.1}, 0.1, 0xFFFFFFFF, 0xFF000000, 1, 1},
		{{ox + 0, oy + s, 0.1}, 0.1, 0xFFFFFFFF, 0xFF000000, 1, 1},
	};
	//AddQuadClippedZBuffer(v, 0, 1, 2, 3, &object_textures[cur_tpage], 0);

	
	if (dbinput & IN_LEFT)
	{
		cur_tpage--;
		if (cur_tpage < 0)
			cur_tpage = 0;
	}
	if (dbinput & IN_RIGHT)
	{
		cur_tpage++;
		if (cur_tpage > 63)
			cur_tpage = 63;
	}

	if (keymap[DIK_LSHIFT])
	{
		camera.pos.x += 256;
	}
}