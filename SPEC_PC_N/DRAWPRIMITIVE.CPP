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
#include "OBJLIGHT.H"
#include "TEXTURE.H"
#include "DEBUG.H"

HRESULT(*DrawPrimitive)(D3DPRIMITIVETYPE dptPrimitiveType, D3DVERTEXTYPE dvtVertexType,
	LPVOID lpvVertices, DWORD dwVertexCount, DWORD dwFlags);
HRESULT(*BeginScene)();
HRESULT(*EndScene)();
HRESULT(*SetRenderState)(D3DRENDERSTATETYPE dwRenderStateType, DWORD dwRenderState);
bool(*PtrVisible)(D3DTLVERTEX *v1, D3DTLVERTEX *v2, D3DTLVERTEX *v3);
void(*AddQuad1)(D3DTLVERTEX *v, int v1, int v2, int v3, int v4, OBJECT_TEXTURE* tex, int a7);
void(*AddQuad2)(D3DTLVERTEX *v, int v1, int v2, int v3, int v4, OBJECT_TEXTURE* tex, int a7);
void(*AddTri1)(D3DTLVERTEX *v, int v1, int v2, int v3, OBJECT_TEXTURE* tex, int a7);
void(*AddTri2)(D3DTLVERTEX *v, int v1, int v2, int v3, OBJECT_TEXTURE* tex, int a7);
void(*AddLine)(D3DTLVERTEX *v1, D3DTLVERTEX *v2, short color);

DXTEXTURE DXTextureList[MAX_D3D_TEXTURES];

uint32_t global_ambient;

float fog_start = SECTOR(12);
float fog_end = SECTOR(20);

int num_fog_bulbs;

int num_snow_flakes;
int num_rain_drops;
int num_snow_splashes;
int num_rain_splashes;

uint32_t GnFrameCounter;

static int bound_list[128];
static int bound_start = 0;
static int bound_end = 0;

#define MAX_POLYGONS 4000

float sort3d_bufferbf[MAX_POLYGONS][10];
short info3d_bufferbf[MAX_POLYGONS * 30];

int* sort3dptrbf;
short* info3dptrbf;

int surfacenumbf;

D3DMATRIX d3d_camera;

SNOWFLAKE raindrops[2048];
SNOWFLAKE snowflakes[2048];


void SubdivideEdge(D3DTLVERTEX *pv1, D3DTLVERTEX *pv2, D3DTLVERTEX *pv3, short *a4, float u1, float v1, float u2, float v2, float *u, float *v)
{
	Unimpl();
}
void SubdivideQuad(D3DTLVERTEX *pv1, D3DTLVERTEX *pv2, D3DTLVERTEX *pv3, D3DTLVERTEX *pv4, OBJECT_TEXTURE* tex, int a6, int a7, short *face)
{
	Unimpl();
}
void SubdivideTri (D3DTLVERTEX *pv1, D3DTLVERTEX *pv2, D3DTLVERTEX *pv3, OBJECT_TEXTURE* tex, int a5, int a6, short *face)
{
	Unimpl();
}

void AddQuadSubdivide(D3DTLVERTEX *v, int v1, int v2, int v3, int v4, OBJECT_TEXTURE* tex, int a7)
{
	Unimpl();
}
void AddTriSubdivide(D3DTLVERTEX *v, int v1, int v2, int v3, OBJECT_TEXTURE* tex, int a7)
{
	Unimpl();
}

void AddQuadClippedZBuffer(D3DTLVERTEX *v, int v1, int v2, int v3, int v4, OBJECT_TEXTURE* tex, int a7)
{
	Unimpl();
}
void AddTriClippedZBuffer(D3DTLVERTEX *v, int v1, int v2, int v3, OBJECT_TEXTURE* tex, int a7)
{
	Unimpl();
}

void AddQuadClippedSorted(D3DTLVERTEX *v, int v1, int v2, int v3, int v4, OBJECT_TEXTURE* tex, int a7)
{
	Unimpl();
}
void AddTriClippedSorted(D3DTLVERTEX *v, int v1, int v2, int v3, OBJECT_TEXTURE* tex, int a7)
{
	Unimpl();
}
enum dinfo_type
{
	DI_LINE = 2,
	DI_TRI = 3,
	DI_QUAD = 4,
};
struct dinfo_line
{
	float z;
	short color;
	short unk1;
	short type;
	short unk3;
	D3DTLVERTEX v1;
	int unk4;
	int unk5;
	D3DTLVERTEX v2;
};
struct dinfo_tri
{
	float z;
	short texattr;
	short unk1;
	short type;
	short unk3;
};
void AddLineClippedSorted(D3DTLVERTEX *v1, D3DTLVERTEX *v2, short color)// (F)
{
	auto ptr = (dinfo_line*)info3dptrbf;
	ptr->unk1 = 0;
	ptr->color = color;
	ptr->type = 2;
	info3dptrbf = (short*)(ptr + 1);

	*sort3dptrbf++ = (int)ptr;

	ptr->z = v1->sz;
	surfacenumbf++;

	ptr->v1.sx = v1->sx;
	ptr->v1.sy = v1->sy;
	ptr->v1.sz = f_a - f_boo * v1->rhw;
	ptr->v1.rhw = v1->rhw;
	ptr->v1.color = v1->color;
	ptr->v1.specular = v1->specular;

	ptr->v2.sx = v2->sx;
	ptr->v2.sy = v2->sy;
	ptr->v2.sz = f_a - f_boo * v2->rhw;
	ptr->v2.rhw = v2->rhw;
	ptr->v2.color = v2->color;
	ptr->v2.specular = v2->specular;
}

void do_quickysorty(int left, int right, float buffer[][10])// (F)
{
	int i = left;
	int j = right;
	float compare = buffer[(left + right) / 2][0];

	do
	{
		if (buffer[i][0] > compare)
			while (buffer[i][1] > compare && i < right)
				i++;

		if (compare > buffer[j][0])
			while (compare > buffer[j][1] && j > left)
				j--;

		if (i <= j)
		{
			SWAPARR(buffer, i, j);

			i++;
			j--;
		}
	} while (i <= j);

	if (left < j)
		do_quickysorty(left, j, buffer);

	if (i < right)
		do_quickysorty(i, right, buffer);
}

void SortPolyList(int number, float buffer[][10])// (F)
{
	if (number != 0)
	{
		for (int i = 0; i < number; i++)
		{
			buffer[i][0] -= i / 10.0;
		}

		do_quickysorty(0, number - 1, buffer);
	}
}

HRESULT HWBeginScene()// (F)
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

HRESULT HWEndScene()// (F)
{
	App.isInScene = false;

	return App.lpD3DDevice->EndScene();
}

bool Visible(D3DTLVERTEX *v1, D3DTLVERTEX *v2, D3DTLVERTEX *v3)// (F)
{
	return (v1->sy - v2->sy) * (v3->sx - v2->sx) - (v3->sy - v2->sy) * (v1->sx - v2->sx) < 0.0;
}

void InitialiseFunctionTable()// (F)
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

void InitialiseSortList()// (F)
{
	info3dptrbf = info3d_bufferbf;
	sort3dptrbf = (int*)sort3d_bufferbf;
	surfacenumbf = 0;
}

void GPU_BeginScene()// (F)
{
	D3DRECT rect;
	rect.x1 = App.GnClientRect.left;
	rect.y1 = App.GnClientRect.top;
	rect.y2 = App.GnClientRect.top + App.GnClientRect.bottom;
	rect.x2 = App.GnClientRect.left + App.GnClientRect.right;

	DX_TRY(App.lpViewPort->Clear2(1, &rect, D3DCLEAR_TARGET, RGBA_MAKE(0, 0, 0, 0), 1.0f, 0));
	BeginScene();
	InitBuckets();
	InitialiseSortList();
}

void SetGlobalAmbient(uint32_t color)// (F)
{
	global_ambient = color;
}

void DrawEffect(short fx_num)
{
	FX_INFO* fx = &effects[fx_num];
	object_info* obj = &objects[fx->object_number];

	if (obj->draw_routine != nullptr && obj->loaded)
	{
		phd_PushMatrix();
		phd_TranslateAbs(fx->pos.x_pos, fx->pos.y_pos, fx->pos.z_pos);

		if (phd_mxptr[M23] > phd_znear && phd_mxptr[M23] < phd_zfar)
		{
			phd_RotYXZ(fx->pos.y_rot, fx->pos.x_rot, fx->pos.z_rot);

			if (gfCurrentLevel == LVL5_COLOSSEUM && fx->object_number == BODY_PART)
			{
				SetGlobalAmbient(RGB_MAKE(40, 32, 32));
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

void DoWeather()// (F)
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

void InitialiseFogBulbs()// (F)
{
	
}

void CreateFXBulbs()// (F)
{
	
}

void SkyDrawPhase()
{
	Unimpl();
}

void DrawLara__1(ITEM_INFO* item, int a2)
{
	Unimpl();
}

void DrawLara__4(ITEM_INFO* item, int a2)
{
	Unimpl();
}

void DrawLara__5(ITEM_INFO* item, int a2)
{
	Unimpl();
}

void DrawLara__6(ITEM_INFO* item, int a2)
{
	Unimpl();
}

void DrawLara(ITEM_INFO* item, int a2)// (F)
{
	if (lara.skelebob)
	{
		DrawLara__6(item, a2);
	}
	else
	{
		switch(LaraDrawType)
		{
		case LARA_NORMAL:
		case LARA_YOUNG:
		case LARA_BUNHEAD:
			DrawLara__1(item, a2);
			return;

		case LARA_CATSUIT:
			DrawLara__4(item, a2);

		case LARA_DIVESUIT:
			DrawLara__5(item, a2);
			return;
		}
	}
}

void FadeLightList(PCLIGHT* lights, int num)// (F)
{
	for(int i = 0; i < num; i++)
	{
		PCLIGHT* ptr = &lights[i];

		if (ptr->UnknownByte == 0 || ptr->UnknownInt == 0)
			continue;

		if (ptr->LightType == LT_SHADOW)
		{
			ptr->ShadowIntensity += ptr->dy2;
		}
		else
		{
			ptr->r = ptr->r3 + ptr->r;
			ptr->g = ptr->g3 + ptr->g;
			ptr->b = ptr->b3 + ptr->b;
		}

		ptr->UnknownInt--;

		if (ptr->LightType == LT_SHADOW)
		{
			if (ptr->ShadowIntensity <= 0)
			{
				ptr->UnknownByte = 0;
			}
		}
		else
		{
			if (ptr->r <= 0.0 && ptr->g <= 0.0 && ptr->b <= 0.0)
			{
				ptr->UnknownByte = 0;
			}
		}
	}
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

void Update()
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

void InsertRoom(room_info* r)
{
	Unimpl();
}

void SaveD3DCameraMatrix()// (F)
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

void RoomTestThing()// (F)
{
	
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
			e4b100 = 4;	

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

	e4b100 = 0;

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

		SetViewMatrix();
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

	Update();
}

void phd_PutPolygons(short* mesh)
{
	Unimpl();
}

int32_t DrawPhaseGame()// (F)
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
	DrawDebugPre();
	S_OutputPolyList();
	camera.number_frames = S_DumpScreen();
	S_AnimateTextures(camera.number_frames);
	return camera.number_frames;
}

void DrawBinoculars()
{
	Unimpl();
}

void DrawLoadingScreen()
{
	Unimpl();
}

void DrawFlash()
{
	Unimpl();
}

void ReleaseScreen()
{
	Unimpl();
}

void HWR_DrawRoutine(short* info, short num_verts, short texture, short type)// (F)
{
	switch (type)
	{
	case 0:
		if (App.lpZBuffer)
		{
			App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ZWRITEENABLE, TRUE);
		}

		App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ALPHATESTENABLE, FALSE);
		App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, FALSE);
		App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA);
		App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA);

		DX_TRY(App.lpD3DDevice->SetTexture(0, DXTextureList[texture].tex));

		App.lpD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 708, info, num_verts, D3DDP_DONOTUPDATEEXTENTS | D3DDP_DONOTCLIP);

		App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ALPHATESTENABLE, TRUE);
		App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, TRUE);

		break;
	case 1:
		App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ALPHATESTENABLE, TRUE);
		App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, TRUE);
		App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA);
		App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA);

		DX_TRY(App.lpD3DDevice->SetTexture(0, DXTextureList[texture].tex));

		App.lpD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 708, info, num_verts, D3DDP_DONOTUPDATEEXTENTS | D3DDP_DONOTCLIP);

		break;
	case 2:
		if (App.lpZBuffer)
		{
			App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ZWRITEENABLE, FALSE);
		}

		App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ALPHATESTENABLE, FALSE);
		App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, FALSE);
		App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_ONE);
		App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_ONE);

		DX_TRY(App.lpD3DDevice->SetTexture(0, DXTextureList[texture].tex));

		App.lpD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 708, info, num_verts, D3DDP_DONOTUPDATEEXTENTS | D3DDP_DONOTCLIP);

		App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_SPECULARENABLE, TRUE);
		App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA);
		App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA);

		break;
	case 3:
		if (App.lpZBuffer)
		{
			App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ZWRITEENABLE, FALSE);
		}

		App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_SPECULARENABLE, TRUE);
		App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ALPHATESTENABLE, TRUE);
		App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA);
		App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA);

		App.lpD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);

		DX_TRY(App.lpD3DDevice->SetTexture(0, DXTextureList[texture].tex));

		App.lpD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 708, info, num_verts, D3DDP_DONOTUPDATEEXTENTS | D3DDP_DONOTCLIP);

		App.lpD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);

		App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_SPECULARENABLE, TRUE);

		break;
	case 4:
		DX_TRY(App.lpD3DDevice->SetTexture(0, DXTextureList[texture].tex));

		if (App.lpZBuffer)
		{
			App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ZENABLE, FALSE);
			App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ZWRITEENABLE, FALSE);
		}

		App.lpD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 708, info, num_verts, D3DDP_DONOTUPDATEEXTENTS | D3DDP_DONOTCLIP);

		if (App.lpZBuffer)
		{
			App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ZENABLE, TRUE);
			App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ZWRITEENABLE, TRUE);
		}

		break;
	case 5:
		break;
	case 6:
		if (App.lpZBuffer)
		{
			App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ZWRITEENABLE, FALSE);
		}

		App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ALPHATESTENABLE, FALSE);
		App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, FALSE);
		App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_ONE);
		App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_ONE);

		DX_TRY(App.lpD3DDevice->SetTexture(0, nullptr));

		App.lpD3DDevice->DrawPrimitive(D3DPT_LINELIST, 708, info, num_verts, D3DDP_DONOTUPDATEEXTENTS | D3DDP_DONOTCLIP);

		break;
	case 7:
		if (App.lpZBuffer)
		{
			App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ZWRITEENABLE, TRUE);
		}

		App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ALPHATESTENABLE, TRUE);
		App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA);
		App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA);

		App.lpD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);

		DX_TRY(App.lpD3DDevice->SetTexture(0, DXTextureList[texture].tex));

		App.lpD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 708, info, num_verts, D3DDP_DONOTUPDATEEXTENTS | D3DDP_DONOTCLIP);

		App.lpD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);

		break;
	}

	App.DrawPrimitiveCnt++;
}

void DrawSortList()
{
	if (surfacenumbf == 0)
		return;

	App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ALPHATESTENABLE, TRUE);
	App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA);
	App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA);
	App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, TRUE);

	if (App.lpZBuffer)
	{
		S_Warn("No DrawSortList for ZBuffer");
		if (surfacenumbf < 0)
		{
			// TODO
		}
		else
		{
			for(int i = 0; i < surfacenumbf; i++)
			{
				
			}
		}
	}
	//else // LINE 421
	{
		int* ptr = (int*)&sort3d_bufferbf[0][0];
		for(int i = 0; i < surfacenumbf; i++, ptr++)
		{
			short* info = (short*)(*ptr);
			if (info[5] == 4)
				App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_TEXTUREPERSPECTIVE, FALSE);

			HWR_DrawRoutine(&info[6], info[4], info[3], info[2]);

			if (info[5] == 4)
				App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_TEXTUREPERSPECTIVE, TRUE);
		}
	}

	App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ZWRITEENABLE, TRUE);
	App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ALPHATESTENABLE, FALSE);
	App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, FALSE);

	InitBuckets();
}