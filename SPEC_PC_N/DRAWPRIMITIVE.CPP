#include "DRAWPRIMITIVE.H"
#include "GLOBAL.H"
#include "DELSTUFF.H"
#include "LARA.H"
#include "DOOR.H"
#include "HEALTH.H"
#include "CAMERA.H"
#include "DELTAPAK.H"
#include "GAME.H"
#include "EFFECTS.H"
#include "GAMEFLOW.H"
#include "DRAW.H"
#include "ITEMS.H"
#include "CONTROL.H"

HRESULT(*DrawPrimitive)(D3DPRIMITIVETYPE dptPrimitiveType, D3DVERTEXTYPE dvtVertexType,
	LPVOID lpvVertices, DWORD dwVertexCount, DWORD dwFlags);
HRESULT(*BeginScene)();
HRESULT(*EndScene)();
HRESULT(*SetRenderState)(D3DRENDERSTATETYPE dwRenderStateType, DWORD dwRenderState);
bool(*PtrVisible)(D3DTLVERTEX *v1, D3DTLVERTEX *v2, D3DTLVERTEX *v3);
void(*AddQuad1)(D3DTLVERTEX *v, int v1, int v2, int v3, int v4, int a6, int a7);
void(*AddQuad2)(D3DTLVERTEX *v, int v1, int v2, int v3, int v4, int a6, int a7);
void(*AddTri1)(D3DTLVERTEX *v, int v1, int v2, int v3, int a6, int a7);
void(*AddTri2)(D3DTLVERTEX *v, int v1, int v2, int v3, int a6, int a7);
void(*AddLine)(D3DTLVERTEX *v1, D3DTLVERTEX *v2, short color);

struct TEXTURESTRUCT
{
	uint16 drawtype;
	uint16 tpage;
	uint16 pad;
	float u1, v1;
	float u2, v2;
	float u3, v3;
	float u4, v4;
};

void SubdivideEdge(D3DTLVERTEX *pv1, D3DTLVERTEX *pv2, D3DTLVERTEX *pv3, short *a4, float u1, float v1, float u2, float v2, float *u, float *v)
{
	Unimpl();
}
void SubdivideQuad(D3DTLVERTEX *pv1, D3DTLVERTEX *pv2, D3DTLVERTEX *pv3, D3DTLVERTEX *pv4, TEXTURESTRUCT* tex, int a6, int a7, short *face)
{
	Unimpl();
}
void SubdivideTri (D3DTLVERTEX *pv1, D3DTLVERTEX *pv2, D3DTLVERTEX *pv3, TEXTURESTRUCT* tex, int a5, int a6, short *face)
{
	Unimpl();
}

void AddQuadSubdivide(D3DTLVERTEX *v, int v1, int v2, int v3, int v4, int a6, int a7)
{
	Unimpl();
}
void AddTriSubdivide(D3DTLVERTEX *v, int v1, int v2, int v3, int a6, int a7)
{
	Unimpl();
}

void AddQuadClippedZBuffer(D3DTLVERTEX *v, int v1, int v2, int v3, int v4, int a6, int a7)
{
	Unimpl();
}
void AddTriClippedZBuffer(D3DTLVERTEX *v, int v1, int v2, int v3, int a6, int a7)
{
	Unimpl();
}

void AddQuadClippedSorted(D3DTLVERTEX *v, int v1, int v2, int v3, int v4, int a6, int a7)
{
	Unimpl();
}
void AddTriClippedSorted(D3DTLVERTEX *v, int v1, int v2, int v3, int a6, int a7)
{
	Unimpl();
}
void AddLineClippedSorted(D3DTLVERTEX *v1, D3DTLVERTEX *v2, short color)
{
	Unimpl();
}

HRESULT HWBeginScene()
{
	if (App.isInScene)
	{
		Log(LT_Error, "Already In Scene");
	}

	App.isInScene = true;
	App.dword_D9AC01 = 0;

	// todo

	return App.lpD3DDevice->BeginScene();
}

HRESULT HWEndScene()
{
	App.isInScene = false;

	return App.lpD3DDevice->EndScene();
}

bool Visible(D3DTLVERTEX *v1, D3DTLVERTEX *v2, D3DTLVERTEX *v3)
{
	return (v1->sy - v2->sy) * (v3->sx - v2->sx) - (v3->sy - v2->sy) * (v1->sx - v2->sx) < 0.0;
}

void InitialiseFunctionTable()
{
	BeginScene = HWBeginScene;
	EndScene = HWEndScene;

	PtrVisible = Visible;

	if (App.lpZBuffer)
	{
		AddQuad1 = AddQuadClippedZBuffer;
		AddTri1 = AddTriClippedZBuffer;
		AddQuad2 = AddQuadClippedSorted;
		AddTri2 = AddTriClippedSorted;
	}
	else
	{
		AddQuad1 = AddQuadSubdivide;
		AddTri1 = AddTriSubdivide;
		AddQuad2 = AddQuadSubdivide;
		AddTri2 = AddTriSubdivide;
	}

	AddLine = AddLineClippedSorted;
}

void GPU_BeginScene()
{
	Unimpl();
}

void SetGlobalAmbient(uint32_t color)
{
	Unimpl();
}

void DrawEffect(short fx_num)
{
	FX_INFO* fx = &effects[fx_num];
	object_info* obj = &objects[fx->object_number];

	if (obj->draw_routine != nullptr && obj->loaded)
	{
		phd_PushMatrix();
		phd_TranslateAbs(fx->pos.x_pos, fx->pos.y_pos, fx->pos.z_pos);

		if (phd_mxptr[11] > phd_znear && phd_mxptr[11] < phd_zfar)
		{
			phd_RotYXZ(fx->pos.y_rot, fx->pos.x_rot, fx->pos.z_rot);

			if (gfCurrentLevel == LVL5_COLOSSEUM && fx->object_number == BODY_PART)
			{
				SetGlobalAmbient(0xFF282020);
			}

			//S_CalculateLight(fx->pos.x_pos, fx->pos.y_pos, fx->pos.z_pos, fx->room_number, &stru_E71352);
			// null sub, dont care

			if (obj->nmeshes != 0)
			{
				phd_PutPolygons(meshes[obj->mesh_index]);
			}
			else
			{
				phd_PutPolygons(meshes[fx->frame_number]);
			}
		}

		phd_PopMatrix();
	}
}

void PrintObjects(short current_room)
{
	Unimpl();
}

void DoRain()
{
	Unimpl();
}

void DoSnow()
{
	Unimpl();
}

void DoWeather()
{
	if (WeatherType == WEATHER_RAIN)
		DoRain();
	else if (WeatherType == WEATHER_SNOW)
		DoSnow();
}

void DrawLaserSightSprite()
{
	Unimpl();
}

void DrawStaticObjects(short current_room)
{
	Unimpl();
}

void DoMonitorScreen()
{
	Unimpl();
}

void GetRoomBounds()
{
	Unimpl();
}

void InitialiseFogBulbs()
{
	
}

void CreateFXBulbs()
{
	
}

void SkyDrawPhase()
{
	Unimpl();
}

void DrawRooms(short current_room)
{
	DoMonitorScreen();

	room_info* r = &room[current_room];

	r->test_left = phd_left = 0;
	r->test_top = phd_top = 0;
	r->test_right = phd_right = phd_winxmax;
	r->test_bottom = phd_bottom = phd_winymax;

	// todo

	r->bound_active = 2;

	// todo

	GetRoomBounds();
	InitialiseFogBulbs();
	CreateFXBulbs();
	ProcessClosedDoors();

	if (gfCurrentLevel != LVL5_TITLE)
		SkyDrawPhase();

	if (objects[LARA].loaded)
	{
		if (!(lara_item->flags & IFLAG_INVISIBLE))
		{
			
		}
	}
}

void phd_PutPolygons(short* mesh)
{
	Unimpl();
}

int32_t DrawPhaseGame()
{
	CalcLaraMatrices(0);
	phd_PushUnitMatrix();
	CalcLaraMatrices(1);

	phd_mxptr -= 12;
	phd_dxptr -= 48;

	if (GLOBAL_playing_cutseq)
		frigup_lara();

	SetLaraUnderwaterNodes();
	DrawRooms(camera.pos.room_number);
	DrawGameInfo(TRUE);
	S_OutputPolyList();
	camera.number_frames = S_DumpScreen();
	S_AnimateTextures(camera.number_frames);
	return camera.number_frames;
}