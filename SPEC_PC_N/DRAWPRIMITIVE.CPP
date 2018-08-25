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
#include "HWINSERT.H"
#include "SPOTCAM.H"
#include "TOMB4FX.H"
#include "EFFECT2.H"
#include "DIRECTX.H"

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

int dword_E4B100;
int num_fog_bulbs;

uint32_t GnFrameCounter;

static int bound_list[128];
static int bound_start = 0;
static int bound_end = 0;

D3DMATRIX d3d_camera;

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
	App.sceneDone = false;

	if (App.bNoFocus)
		WaitUntilFalse(&App.bNoFocus);

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

void InitialiseSortList()
{
	Unimpl();
}

void GPU_BeginScene()
{
	D3DRECT rect;
	rect.x1 = App.r1.left;
	rect.y1 = App.r1.top;
	rect.y2 = App.r1.top + App.r1.bottom;
	rect.x2 = App.r1.left + App.r1.right;

	DX_TRY(App.lpViewPort->Clear2(1, &rect, 1, 0, 1.0f, 0)); // todo understand dwFlags
	BeginScene();
	InitBuckets();
	InitialiseSortList();
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

void DrawLara(ITEM_INFO* item, int a2)
{
	Unimpl();
}

void SetupSkelebobMeshswaps()
{
	Unimpl();
}

void RestoreLaraMeshswaps()
{
	Unimpl();
}

float lara_left_mat[12];
float lara_right_mat[12];

void aUpdate()
{
	Unimpl();
}

void InitDynamicLighting()
{
	Unimpl();
}

void Draw_Mirror_Lara()
{
	Unimpl();
}

void SetGunFlash(short gun_type)
{
	Unimpl();
}

void DoUwEffect()
{
	Unimpl();
}

void S_DrawFires()
{
	Unimpl();
}

void S_DrawSmokeSparks()
{
	Unimpl();
}

void S_DrawSplashes()
{
	Unimpl();
}

void DrawBubbles()
{
	Unimpl();
}

void DrawDebris()
{
	Unimpl();
}

void DrawBlood()
{
	Unimpl();
}

void DrawDrips()
{
	Unimpl();
}

void DrawShockwaves()
{
	Unimpl();
}

void DrawLightning()
{
	Unimpl();
}

void DrawTwogunLasers()
{
	Unimpl();
}

void DrawGunshells()
{
	Unimpl();
}

void DrawCutSeqActors()
{
	Unimpl();
}

void DrawRopeList()
{
	Unimpl();
}

void S_DrawSparks()
{
	Unimpl();
}

void DrawRats()
{
	Unimpl();
}

void DrawBats()
{
	Unimpl();
}

void DrawSpiders()
{
	Unimpl();
}

void aSetViewMatrix()
{
	//DX_TRY(App.lpD3DDevice->SetTransform(D3DTRANSFORMSTATE_VIEW, 0));
	Unimpl();
}

void InsertRoom(room_info* r)
{
	Unimpl();
}

void SaveD3DCameraMatrix()
{
	D3DIdentityMatrix(&d3d_camera);
	d3d_camera._11 = phd_dxptr[0];
	d3d_camera._12 = phd_dxptr[4];
	d3d_camera._13 = phd_dxptr[8];
	d3d_camera._21 = phd_dxptr[1];
	d3d_camera._22 = phd_dxptr[5];
	d3d_camera._23 = phd_dxptr[9];
	d3d_camera._31 = phd_dxptr[2];
	d3d_camera._32 = phd_dxptr[6];
	d3d_camera._33 = phd_dxptr[10];
	d3d_camera._41 = phd_dxptr[3];
	d3d_camera._42 = phd_dxptr[7];
	d3d_camera._43 = phd_dxptr[11];
}

void ResetFogBulbList()
{
	Unimpl();
}

void RoomTestThing()
{
	Unimpl();
}

void BuildFogBulbList()
{
	Unimpl();
}

void BuildFXFogBulbList()
{
	Unimpl();
}


void DrawRooms(short current_room)
{
	DoMonitorScreen();

	CurrentRoom = current_room;

	room_info* r = &room[current_room];

	r->test_left = phd_left = 0;
	r->test_top = phd_top = 0;
	r->test_right = phd_right = phd_winxmax;
	r->test_bottom = phd_bottom = phd_winymax;
	
	//dword_E6CAE8 = 0;
	outside = r->flags & RF_SKYBOX_VISIBLE;
	camera_underwater = r->flags & RF_FILL_WATER;
	r->bound_active = 2;
	bound_list[0] = current_room;
	bound_start = 0;
	bound_end = 1;
	number_draw_rooms = 0;

	if (outside)
	{
		outside_top = 0;
		outside_left = 0;
		outside_right = phd_winxmax;
		outside_bottom = phd_winymax;
	}
	else
	{
		outside_left = phd_winxmax;
		outside_top = phd_winymax;
		outside_bottom = 0;
		outside_right = 0;
	}

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
			dword_E4B100 = 4;	

			if (lara_item->mesh_bits != 0 && !SCNoDrawLara)
			{
				if (lara.skelebob)
					SetupSkelebobMeshswaps();

				DrawLara(lara_item, 0);

				if (lara.skelebob)
					RestoreLaraMeshswaps();

				phd_PushMatrix();

				if (lara.right_arm.flash_gun)
				{
					memcpy(phd_dxptr, lara_right_mat, 12 * sizeof(float));
					SetGunFlash(lara.gun_type);
				}

				if (lara.left_arm.flash_gun)
				{
					memcpy(phd_dxptr, lara_left_mat, 12 * sizeof(float));
					SetGunFlash(lara.gun_type);
				}

				phd_PopMatrix();

				DrawGunflashes();
			}

			if (gfLevelFlags & GF_LVOP_MIRROR_USED && lara_item->room_number == gfMirrorRoom)
			{
				Draw_Mirror_Lara();
			}
		}
	}

	InitDynamicLighting();

	dword_E4B100 = 0;

	for (int i = 0; i < 32; i++)
	{
		if (dynamics[i].on)
		{
			if (dynamics[i].x < 0)
				dynamics[i].x = 0;

			if (dynamics[i].z < 0)
				dynamics[i].z = 0;
		}
	}

	phd_PushMatrix();
	phd_TranslateAbs(0, 0, 0);
	SaveD3DCameraMatrix();
	phd_PopMatrix();
	ResetFogBulbList();
	RoomTestThing();
	BuildFogBulbList();
	BuildFXFogBulbList();

	for (int i = 0; i < number_draw_rooms; i++)
	{
		auto cr = &room[draw_rooms[i]];

		phd_PushMatrix();
		phd_TranslateAbs(cr->x, cr->y, cr->z);

		CurrentRoom = draw_rooms[i];

		phd_left = cr->left;
		phd_right = cr->right;
		phd_top = cr->top;
		phd_bottom = cr->bottom;

		aSetViewMatrix();
		InsertRoom(cr);

		phd_PopMatrix();
	}

	DrawGunshells();
	//
	if (GLOBAL_playing_cutseq)
		DrawCutSeqActors();

	DrawRopeList();
	S_DrawSparks();
	DrawRats();
	DrawBats();
	DrawSpiders();

	long bak_x = lara_item->pos.x_pos;
	long bak_y = lara_item->pos.y_pos;
	long bak_z = lara_item->pos.z_pos;
	short bak_room = lara_item->room_number;

	lara_item->pos.x_pos = camera.pos.x;
	lara_item->pos.y_pos = camera.pos.y;
	lara_item->pos.z_pos = camera.pos.z;
	lara_item->room_number = camera.pos.room_number;

	DoWeather();
	DoUwEffect();
	S_DrawFires();
	S_DrawSmokeSparks();
	S_DrawSplashes();
	DrawBubbles();
	DrawDebris();
	DrawBlood();
	DrawDrips();
	DrawShockwaves();
	DrawLightning();
	DrawTwogunLasers();

	lara_item->pos.x_pos = bak_x;
	lara_item->pos.y_pos = bak_y;
	lara_item->pos.z_pos = bak_z;
	lara_item->room_number = bak_room;

	if (gfLevelFlags & GF_LVOP_LENSFLARE_USED)
		SetUpLensFlare(gfLensFlare.x, gfLensFlare.y - 4096, gfLensFlare.z, nullptr);

	if (LaserSightActive)
		DrawLaserSightSprite();

	for(int i = 0; i < number_draw_rooms; i++)
	{
		PrintObjects(draw_rooms[i]);
	}

	aUpdate();
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

	phd_PopMatrix();

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