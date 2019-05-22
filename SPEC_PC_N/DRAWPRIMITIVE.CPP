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
#include "DISPLAY.H"
#include "FILE.H"
#include "TWOGUN.H"

struct dinfo_head
{
	float z;
	short texattr;
	short tile_and_flag;
	short num_verts;
	short e4b100;
};
struct dinfo_line // size 92
{
	dinfo_head head;
	D3DTLVERTEX v1;
	char pad1[8];
	D3DTLVERTEX v2;
	char pad2[8];
};

struct dinfo_tri // size 132
{
	dinfo_head head;
	D3DTLVERTEX v1;//12
	char pad1[8];
	D3DTLVERTEX v2;//52
	char pad2[8];
	D3DTLVERTEX v3;//92
	char pad3[8];
};

struct dinfo_quad // size 252
{
	dinfo_head head;
	D3DTLVERTEX v1;//12
	char pad1[8];
	D3DTLVERTEX v2;//52
	char pad2[8];
	D3DTLVERTEX v3;//92
	char pad3[8];
	D3DTLVERTEX v1bis;//132
	char pad4[8];
	D3DTLVERTEX v3bis;//172
	char pad5[8];
	D3DTLVERTEX v4;//212
	char pad6[8];
};

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

bool visible_zclip(D3DTLVERTEX *v1, D3DTLVERTEX *v2, D3DTLVERTEX *v3)
{
	return (v3->tu * v1->sz - v3->sz * v1->tu) * v2->tv
		+ (v3->sz * v1->tv - v3->tv * v1->sz) * v2->tu
		+ (v3->tv * v1->tu - v3->tu * v1->tv) * v2->sz < 0.0;
}

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

void AddQuadSubdivide(D3DTLVERTEX *v, int v1, int v2, int v3, int v4, OBJECT_TEXTURE* tex, int dside)
{
	if (e4b100)
	{
		AddQuadClippedSorted(v, v1, v2, v3, v4, tex, dside);
	}
	else
	{
		D3DVALUE z = v[v4].sz;

		if (z >= 3500.0)
		{
			AddQuadClippedSorted(v, v1, v2, v3, v4, tex, dside);
		}
		else
		{
			int num = 1;

			if (z < 2000.0)
				num = 2;

			short face[4];

			face[0] = d9ab34[v1];
			face[1] = d9ab34[v2];
			face[2] = d9ab34[v3];
			face[3] = d9ab34[v4];

			SubdivideQuad(&v[v1], &v[v2], &v[v3], &v[v4], tex, dside, num, face);
		}
	}
}
void AddTriSubdivide(D3DTLVERTEX *v, int v1, int v2, int v3, OBJECT_TEXTURE* tex, int dside)
{
	if (e4b100)
	{
		AddTriClippedSorted(v, v1, v2, v3, tex, dside);
	}
	else
	{
		D3DVALUE z = v[v3].sz;

		if (z >= 3500.0)
		{
			AddTriClippedSorted(v, v1, v2, v3, tex, dside);
		}
		else
		{
			int num = 1;

			if (z < 2000.0)
				num = 2;

			short face[3];

			face[0] = d9ab34[v1];
			face[1] = d9ab34[v2];
			face[2] = d9ab34[v3];

			SubdivideTri(&v[v1], &v[v2], &v[v3], tex, dside, num, face);
		}
	}
}

void AddQuadClippedZBuffer(D3DTLVERTEX *v, int v1, int v2, int v3, int v4, OBJECT_TEXTURE* tex, int dside)
{
	WORD vp1 = d9ab34[v1];
	WORD vp2 = d9ab34[v2];
	WORD vp3 = d9ab34[v3];
	WORD vp4 = d9ab34[v4];

	OBJECT_TEXTURE newtex;
	OBJECT_TEXTURE* next;

	int v1b = v1;
	int v3b = v3;

	if (vp1 & vp2 & vp3 & vp4)
	{
		if ((vp1 | vp2 | vp3 | vp4) & 0x8000u)
		{
			AddTriClippedZBuffer(v, v1b, v2, v3, tex, dside);

			newtex.attribute = tex->attribute;
			newtex.new_flags = tex->new_flags;
			newtex.tile_and_flag = tex->tile_and_flag;

			newtex.vertices[0] = tex->vertices[0];
			newtex.vertices[1] = tex->vertices[2];
			newtex.vertices[2] = tex->vertices[3];

			AddTriClippedZBuffer(v, v1b, v3, v4, &newtex, dside);

			return;
		}

		if (dside || !PtrVisible(&v[v1b], &v[v2], &v[v3b]))
		{
			D3DTLVERTEX* vt2 = &v[v2];

			if (PtrVisible(&v[v1], &v[v2], &v[v3]))
			{
				if (!dside)
					return;

				SWAP(v1b, v3b);

				newtex.attribute = tex->attribute;
				newtex.new_flags = tex->new_flags;
				newtex.tile_and_flag = tex->tile_and_flag;

				newtex.vertices[0] = tex->vertices[2];
				newtex.vertices[1] = tex->vertices[1];
				newtex.vertices[2] = tex->vertices[0];
				newtex.vertices[3] = tex->vertices[3];

				next = &newtex;
			}
			else
			{
				next = tex;
			}

			if (d9ab34[v1b] | d9ab34[v2] | d9ab34[v3b] | d9ab34[v4])
			{
				AddTriClippedZBuffer(v, v1b, v2, v3b, next, dside);

				newtex.attribute = tex->attribute;
				newtex.new_flags = tex->new_flags;
				newtex.tile_and_flag = tex->tile_and_flag;

				newtex.vertices[0] = tex->vertices[0];
				newtex.vertices[1] = tex->vertices[2];
				newtex.vertices[2] = tex->vertices[3];

				AddTriClippedZBuffer(v, v1b, v3b, v4, &newtex, dside);
			}
			else
			{
				TLVERTEX* vptr;
				DWORD* cnt_ptr;

				FindBucket(next->tile_and_flag, &vptr, &cnt_ptr);

				D3DTLVERTEX* vp1b = &v[v1b];

				vptr->v.sx = vp1b->sx;
				vptr->v.sy = vp1b->sy;
				vptr->v.sz = f_a - f_boo * vp1b->rhw;
				vptr->v.rhw = vp1b->rhw;
				vptr->v.color = vp1b->color;
				vptr->v.specular = vp1b->specular;
				vptr->v.tu = next->vertices[0].x;
				vptr->v.tv = next->vertices[0].y;

				vptr[3] = vptr[0];

				vptr++;

				vptr->v.sx = vt2->sx;
				vptr->v.sy = vt2->sy;
				vptr->v.sz = f_a - f_boo * vt2->rhw;
				vptr->v.rhw = vt2->rhw;
				vptr->v.color = vt2->color;
				vptr->v.specular = vt2->specular;
				vptr->v.tu = next->vertices[1].x;
				vptr->v.tv = next->vertices[1].y;

				vptr++;

				D3DTLVERTEX* vt3 = &v[v3b];

				vptr->v.sx = vt3->sx;
				vptr->v.sy = vt3->sy;
				vptr->v.sz = f_a - f_boo * vt3->rhw;
				vptr->v.rhw = vt3->rhw;
				vptr->v.color = vt3->color;
				vptr->v.specular = vt3->specular;
				vptr->v.tu = next->vertices[2].x;
				vptr->v.tv = next->vertices[2].y;

				vptr[2] = vptr[0];

				vptr++;

				D3DTLVERTEX* vt4 = &v[v4];

				vptr->v.sx = vt4->sx;
				vptr->v.sy = vt4->sy;
				vptr->v.sz = f_a - f_boo * vt4->rhw;
				vptr->v.rhw = vt4->rhw;
				vptr->v.color = vt4->color;
				vptr->v.specular = vt4->specular;
				vptr->v.tu = next->vertices[3].x;
				vptr->v.tv = next->vertices[3].y;

				d9ab1c += 2;
			}
		}
	}
}
void AddTriClippedZBuffer(D3DTLVERTEX *v, int v1, int v2, int v3, OBJECT_TEXTURE* tex, int dside)
{
	d9ab34;
	Unimpl();
}

void AddQuadClippedSorted(D3DTLVERTEX *v, int v1, int v2, int v3, int v4, OBJECT_TEXTURE* tex, int dside)
{
	WORD vp1 = d9ab34[v1];
	WORD vp2 = d9ab34[v2];
	WORD vp3 = d9ab34[v3];
	WORD vp4 = d9ab34[v4];

	OBJECT_TEXTURE newtex;
	OBJECT_TEXTURE* next;

	int v1b = v1;
	int v3b = v3;

	if (vp1 & vp2 & vp3 & vp4)
	{
		if ((vp1 | vp2 | vp3 | vp4) & 0x8000u)
		{
			AddTriClippedSorted(v, v1b, v2, v3, tex, dside);
			
			newtex.attribute = tex->attribute;
			newtex.new_flags = tex->new_flags;
			newtex.tile_and_flag = tex->tile_and_flag;

			newtex.vertices[0] = tex->vertices[0];
			newtex.vertices[1] = tex->vertices[2];
			newtex.vertices[2] = tex->vertices[3];

			AddTriClippedSorted(v, v1b, v3, v4, &newtex, dside);

			return;
		}

		D3DTLVERTEX* vt2 = &v[v2];

		if (PtrVisible(&v[v1], &v[v2], &v[v3]))
		{
			if (!dside)
				return;

			SWAP(v1b, v3b);

			newtex.attribute = tex->attribute;
			newtex.new_flags = tex->new_flags;
			newtex.tile_and_flag = tex->tile_and_flag;

			newtex.vertices[0] = tex->vertices[2];
			newtex.vertices[1] = tex->vertices[1];
			newtex.vertices[2] = tex->vertices[0];
			newtex.vertices[3] = tex->vertices[3];

			next = &newtex;
		}
		else
		{
			next = tex;
		}

		if (dside || !PtrVisible(&v[v1b], &v[v2], &v[v3b]))
		{
			if (d9ab34[v1b] | d9ab34[v2] | d9ab34[v3b] | d9ab34[v4])
			{
				AddTriClippedSorted(v, v1b, v2, v3b, next, dside);

				newtex.attribute = tex->attribute;
				newtex.new_flags = tex->new_flags;
				newtex.tile_and_flag = tex->tile_and_flag;

				newtex.vertices[0] = tex->vertices[0];
				newtex.vertices[1] = tex->vertices[2];
				newtex.vertices[2] = tex->vertices[3];

				AddTriClippedSorted(v, v1b, v3b, v4, &newtex, dside);
			}
			else
			{
				auto info = (dinfo_quad*)info3dptrbf;

				info->head.texattr = next->attribute;
				info->head.tile_and_flag = next->tile_and_flag;
				info->head.num_verts = 6;
				info->head.e4b100 = e4b100;

				info3dptrbf += sizeof(*info);

				*sort3dptrbf++ = (int)info;

				surfacenumbf++;

				D3DTLVERTEX* vp1b = &v[v1b];

				info->v1.sx = vp1b->sx;
				info->v1.sy = vp1b->sy;
				info->v1.sz = f_a - f_boo * vp1b->rhw;
				info->v1.rhw = vp1b->rhw;
				info->v1.color = vp1b->color;
				info->v1.specular = vp1b->specular;
				info->v1.tu = next->vertices[0].x;
				info->v1.tv = next->vertices[0].y;

				D3DVALUE z = vp1b->sz;

				if (!e4b100)
				{
					if (z <= 0.0)
						z = 0.0;
					else
						z = vp1b->sz;
				}

				info->v1bis = info->v1;

				info->v2.sx = vt2->sx;
				info->v2.sy = vt2->sy;
				info->v2.sz = f_a - f_boo * vt2->rhw;
				info->v2.rhw = vt2->rhw;
				info->v2.color = vt2->color;
				info->v2.specular = vt2->specular;
				info->v2.tu = next->vertices[1].x;
				info->v2.tv = next->vertices[1].y;

				if (e4b100)
				{
					z = z + vt2->sz;
				}
				else if (z < vt2->sz)
				{
					z = vt2->sz;
				}

				D3DTLVERTEX* vt3 = &v[v3b];

				info->v3.sx = vt3->sx;
				info->v3.sy = vt3->sy;
				info->v3.sz = f_a - f_boo * vt3->rhw;
				info->v3.rhw = vt3->rhw;
				info->v3.color = vt3->color;
				info->v3.specular = vt3->specular;
				info->v3.tu = next->vertices[2].x;
				info->v3.tv = next->vertices[2].y;

				if (e4b100)
				{
					z = z + vt3->sz;
				}
				else if (z < vt3->sz)
				{
					z = vt3->sz;
				}

				info->v3bis = info->v3;

				D3DTLVERTEX* vt4 = &v[v4];

				info->v4.sx = vt4->sx;
				info->v4.sy = vt4->sy;
				info->v4.sz = f_a - f_boo * vt4->rhw;
				info->v4.rhw = vt4->rhw;
				info->v4.color = vt4->color;
				info->v4.specular = vt4->specular;
				info->v4.tu = next->vertices[3].x;
				info->v4.tv = next->vertices[3].y;

				if (e4b100)
				{
					z = z + vt4->sz;
				}
				else if (z < vt4->sz)
				{
					z = vt4->sz;
				}
				if (e4b100)
					z = z * 0.25;

				info->head.z = z;

				d9ab1c += 2;
			}
		}
	}
}

void AddTriClippedSorted(D3DTLVERTEX *v, int v1, int v2, int v3, OBJECT_TEXTURE* tex, int dside)
{
	d9ab34;
	Unimpl();
}


void AddLineClippedSorted(D3DTLVERTEX *v1, D3DTLVERTEX *v2, short color)// (F)
{
	auto ptr = (dinfo_line*)info3dptrbf;
	ptr->head.tile_and_flag = 0;
	ptr->head.texattr = color;
	ptr->head.num_verts = 2;
	info3dptrbf = (short*)(ptr + 1);

	*sort3dptrbf++ = (int)ptr;

	ptr->head.z = v1->sz;
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

void SetRoomBounds(tr_room_portal* portal, int room_number, struct room_info* parent)
{
	struct room_info* r = &room[room_number];

	if (r->left <= parent->test_left &&
		r->right >= parent->test_right &&
		r->top <= parent->test_top &&
		r->bottom >= parent->test_bottom)
		return;

	int left = parent->test_right;
	int right = parent->test_left;
	int top = parent->test_bottom;
	int bottom = parent->test_top;

	struct door_vbuf* dest = vbufdoor;
	int t5 = 0;
	int t6 = 0;

	for (int i = 0; i < 4; i++, dest++)
	{
		int xv = vbufdoor[i].xv =
			phd_mxptr[M00] * portal->Vertices[i].x +
			phd_mxptr[M01] * portal->Vertices[i].y +
			phd_mxptr[M02] * portal->Vertices[i].z +
			phd_mxptr[M03];

		int yv = vbufdoor[i].yv =
			phd_mxptr[M10] * portal->Vertices[i].x +
			phd_mxptr[M11] * portal->Vertices[i].y +
			phd_mxptr[M12] * portal->Vertices[i].z +
			phd_mxptr[M13];

		int zv = vbufdoor[i].zv =
			phd_mxptr[M20] * portal->Vertices[i].x +
			phd_mxptr[M21] * portal->Vertices[i].y +
			phd_mxptr[M22] * portal->Vertices[i].z +
			phd_mxptr[M23];

		if (zv > 0)
		{
			if (zv > 20480)
				t6++;

			zv /= phd_persp;

			int xs, ys;

			if (zv)
			{
				xs = xv / zv + 256;
				ys = yv / zv + 120;
			}
			else
			{
				xs = xv >= 0 ? phd_right : phd_left;
				ys = yv >= 0 ? phd_bottom : phd_top;
			}

			if (xs - 1 < left)
				left = xs - 1;

			if (xs + 1 > right)
				right = xs + 1;

			if (ys - 1 < top)
				top = ys - 1;

			if (ys + 1 > bottom)
				bottom = ys + 1;
		}
		else
		{
			t5++;
		}
	}

	if (t5 == 4 || t6 == 4)
		return;

	if (t5 > 0)
	{
		dest = vbufdoor;

		struct door_vbuf* last = dest + 3;

		for (int i = 0; i < 4; i++, last = dest, dest++)
		{
			if (dest->zv < 0 ^ last->zv < 0)
			{
				if (dest->xv < 0 && last->xv < 0)
				{
					left = 0;
				}
				else if (dest->xv > 0 && last->xv > 0)
				{
					right = 511;
				}
				else
				{
					left = 0;
					right = 511;
				}

				if (dest->yv < 0 && last->yv < 0)
				{
					top = 0;
				}
				else if (dest->yv > 0 && last->yv > 0)
				{
					bottom = 239;
				}
				else
				{
					top = 0;
					bottom = 239;
				}
			}
		}
	}

	if (left < parent->test_left)
		left = parent->test_left;

	if (right > parent->test_right)
		right = parent->test_right;

	if (top < parent->test_top)
		top = parent->test_top;

	if (bottom > parent->test_bottom)
		bottom = parent->test_bottom;

	if (left >= right || top >= bottom)
		return;

	if (r->bound_active & 2)
	{
		if (left < r->test_left)
			r->test_left = left;

		if (top < r->test_top)
			r->test_top = top;

		if (right > r->test_right)
			r->test_right = right;

		if (bottom > r->test_bottom)
			r->test_bottom = bottom;
	}
	else
	{
		bound_list[bound_end++ % 128] = room_number;

		r->bound_active |= 2;

		r->test_left = left;
		r->test_right = right;
		r->test_top = top;
		r->test_bottom = bottom;
	}
}

void GetRoomBounds()
{
	bound_start = 0;
	bound_end = 1;

	while (bound_start != bound_end)
	{
		int current = bound_list[bound_start++ % 128];
		room_info* r = &room[current];
		r->bound_active -= 2;

		if (r->test_left < r->left)
			r->left = r->test_left;
		if (r->test_top < r->top)
			r->top = r->test_top;
		if (r->test_right > r->right)
			r->right = r->test_right;
		if (r->test_bottom > r->bottom)
			r->bottom = r->test_bottom;

		if (!(r->bound_active & 1))
		{
			draw_rooms[number_draw_rooms++] = current;
			r->bound_active |= 1;

			if (r->flags & RF_SKYBOX_VISIBLE)
				outside = RF_SKYBOX_VISIBLE;
		}

		if (r->flags & RF_SKYBOX_VISIBLE)
		{
			if (r->left < outside_left)
				outside_left = r->left;
			if (r->right > outside_right)
				outside_right = r->right;
			if (r->top < outside_top)
				outside_top = r->top;
			if (r->bottom > outside_bottom)
				outside_bottom = r->bottom;
		}

		mPushMatrix();
		mTranslateAbsXYZ(r->x, r->y, r->z);

		short* door;
		if ((door = r->door))
		{
			tr_room_portal* portal = (tr_room_portal*)(door + 1);
			for (short i = *door++; i > 0; i--, portal++)
			{
				if (portal->Normal.x * (r->x + portal->Vertices[0].x - w2v_matrix[M03]) +
					portal->Normal.y * (r->y + portal->Vertices[0].y - w2v_matrix[M13]) +
					portal->Normal.z * (r->z + portal->Vertices[0].z - w2v_matrix[M23])
					>= 0)
				{
					continue;
				}

				SetRoomBounds(portal, portal->AdjoiningRoom, r);
			}
		}
		mPopMatrix();
	}
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

void DrawTwogunLaser(TWOGUN_INFO* tg)
{
	Unimpl();
}

void DrawTwogunLasers()// (F)
{
	for(int i = 0; i < 4; i++)
	{
		if (twogun[i].life != 0)
			DrawTwogunLaser(&twogun[i]);
	}
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

DWORD dword_57A508;
float room_top_flt, room_left_flt, room_bottom_flt, room_right_flt;
float room_top_flt_2, room_left_flt_2, room_bottom_flt_2, room_right_flt_2;
tr5_vertex cam_pos_flt, cam_tar_flt, cam_dir_flt;
room_info* dword_7DFC0C;
DWORD dword_7EE0C8;
WORD word_511A68[8][3] = 
{
	{ 0, 1, 2 }, 
	{ 3, 1, 2 }, 
	{ 0, 1, 5 }, 
	{ 3, 1, 5 }, 
	{ 0, 4, 2 }, 
	{ 3, 4, 2 },
	{ 0, 4, 5 }, 
	{ 3, 4, 5 }
};
tr5_vertex dword_921618[8];

bool CheckBoundsClip(bounding_box_f* bbox)
{
	float minX = 10000, maxX = -10000;
	float minY = 10000, maxY = -10000;
	float minZ = 10000, maxZ = -10000;

	auto ptr = (float*)bbox;

	for (int i = 0; i < 8; i++)
	{
		auto idx = word_511A68[i];

		float f1 = ptr[idx[0]];
		float f2 = ptr[idx[1]];
		float f3 = ptr[idx[2]];

		float ox = App.ViewMatrix._41 + App.ViewMatrix._31 * f3 + App.ViewMatrix._21 * f2 + App.ViewMatrix._11 * f1;
		float oy = App.ViewMatrix._42 + App.ViewMatrix._32 * f3 + App.ViewMatrix._22 * f2 + App.ViewMatrix._12 * f1;
		float oz = App.ViewMatrix._43 + App.ViewMatrix._33 * f3 + App.ViewMatrix._23 * f2 + App.ViewMatrix._13 * f1;

		dword_921618[i] = { ox, oy, oz };

		float z = MAX(f_znear, oz);
		float persp = f_persp / z;
		float x = persp * ox + f_centerx;
		float y = persp * oy + f_centery;

		if (x < minX)
			minX = x;
		if (x > maxX)
			maxX = x;

		if (y < minY)
			minY = y;
		if (y > maxY)
			maxY = y;

		if (z < minZ)
			minZ = z;
		if (z > maxZ)
			maxZ = z;

		if (minX < clip_xmin)
			minX = clip_xmin;
		if (maxX > clip_xmax)
			maxX = clip_xmax;
		if (minY < clip_ymin)
			minY = clip_ymin;
		if (maxY > clip_ymax)
			maxY = clip_ymax;
	}

	return minX <= room_right_flt_2
		&& maxX >= room_left_flt_2
		&& minY <= room_bottom_flt_2
		&& maxY >= room_top_flt_2;
}

D3DTLVERTEX vert_buf[1024];

int BuildRoomletLights(ROOMLET* r)
{
	Unimpl();
	return 0;
}

void RoomletTransformLight(float* vert, int num_vert, int a3, int num_vert_2, int a5)
{
	Unimpl();
}

void InsertRoomlet(ROOMLET* r)
{
	if (r->NumLayerVertices == 0)
		return;

	RoomletTransformLight(
		(float*)r->VerticesOffset, 
		r->NumLayerVertices, 
		BuildRoomletLights(r) & 0x7FFFFFFF, 
		r->NumLayerVertices, 
		r->UnknownL1);

	char* poly = (char*)r->PolyOffset;

	for(int i = 0; i < r->NumLayerRectangles; i++, poly += sizeof(tr_face4))
	{
		auto face = (tr_face4*)poly;
		auto tex = &object_textures[face->Texture];

		if (tex->attribute)
		{
			AddQuad2(vert_buf, face->Vertices[0], face->Vertices[1], face->Vertices[2], face->Vertices[3], tex, face->DoubleSided);
		}
		else
		{
			AddQuad1(vert_buf, face->Vertices[0], face->Vertices[1], face->Vertices[2], face->Vertices[3], tex, face->DoubleSided);
		}
	}

	for (int i = 0; i < r->NumLayerTriangles; i++, poly += sizeof(tr_face3))
	{
		auto face = (tr_face3*)poly;
		auto tex = &object_textures[face->Texture];

		if (tex->attribute)
		{
			AddTri2(vert_buf, face->Vertices[0], face->Vertices[1], face->Vertices[2], tex, face->DoubleSided);
		}
		else
		{
			AddTri1(vert_buf, face->Vertices[0], face->Vertices[1], face->Vertices[2], tex, face->DoubleSided);
		}
	}
}

void InsertRoom(room_info* r)
{
	room_top_flt = room_top_flt_2 = r->top;
	room_left_flt = room_left_flt_2 = r->left;
	room_bottom_flt = room_bottom_flt_2 = r->bottom;
	room_right_flt = room_right_flt_2 = r->right;

	cam_pos_flt = { (float)camera.pos.x, (float)camera.pos.y, (float)camera.pos.z };
	cam_tar_flt = { (float)camera.target.x, (float)camera.target.y, (float)camera.target.z };

	float dx = cam_tar_flt.x - cam_pos_flt.x;
	float dy = cam_tar_flt.y - cam_pos_flt.y;
	float dz = cam_tar_flt.z - cam_pos_flt.z;

	float norm = sqrt(dx * dx + dy * dy + dz * dz);

	cam_dir_flt = { dx / norm, dy / norm, dz / norm };

	if (r->Unknown1)
	{
		dword_7DFC0C = r;
		dword_7EE0C8 = r->flags & RF_FILL_WATER;

		for(int i = 0; i < r->NumLayers; i++)
		{
			if (CheckBoundsClip(&r->LayerOffset[i].BoundingBox))
				InsertRoomlet(&r->LayerOffset[i]);
		}

		dword_57A508 = 0xFFFFFF;
	}
}

void SaveD3DCameraMatrix()// (F)
{
	D3DIdentityMatrix(&d3d_camera);
	d3d_camera._11 = phd_dxptr[M00];
	d3d_camera._12 = phd_dxptr[M10];
	d3d_camera._13 = phd_dxptr[M20];
	d3d_camera._21 = phd_dxptr[M01];
	d3d_camera._22 = phd_dxptr[M11];
	d3d_camera._23 = phd_dxptr[M21];
	d3d_camera._31 = phd_dxptr[M02];
	d3d_camera._32 = phd_dxptr[M12];
	d3d_camera._33 = phd_dxptr[M22];
	d3d_camera._41 = phd_dxptr[M03];
	d3d_camera._42 = phd_dxptr[M13];
	d3d_camera._43 = phd_dxptr[M23];
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
	Log(LT_Info, "DrawRooms N=%d", number_draw_rooms);
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

	e4b100 = 3;

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
	if (App.Flags & WA_BACK_BUFFER)
	{
		App.lpBackBuffer->Blt(nullptr, surf_screen, nullptr, DDBLT_WAIT, nullptr);
	}
	else
	{
		/*DDSURFACEDESC2 desc;
		DXInit(desc);
		surf_screen->Lock(nullptr, &desc, DDLOCK_NOSYSLOCK | DDLOCK_WAIT, nullptr);

		short* src = (short*)pix_buf;
		short* dest = (short*)desc.lpSurface;

		for (int i = 0; i < pix_num; i++, src++, dest++)
		{
			*dest = (*src & 0x1F) | 2 * (*src & 0xFFE0);
		}

		surf_screen->Unlock(nullptr);*/
		S_Warn("NO BACK BUFFER BS!");
		Unimpl();
	}
}

void DrawFlash()
{
	Unimpl();
}

void ReleaseScreen()
{
	in_loading_screen = false;
	DXRelease(surf_screen, "Picture Surface");
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

	int v3 = 0;

	if (App.lpZBuffer)
	{
		dinfo_head* info = nullptr;
		int i = 0;

		//S_Warn("No DrawSortList for ZBuffer");
		if (surfacenumbf <= 0)
		{
			
		}
		else
		{
			auto ptr = (short**)&sort3d_bufferbf[0][0];
			for (i = 0; i < surfacenumbf; i++, ptr++)
			{
				info = (dinfo_head*)(*ptr);

				if (info->texattr == 1 || info->texattr == 4 || info->texattr == 0)
					break;
			}
		}

		auto vert = Bucket[0].Vertex;
		auto tile_and_flag = info->tile_and_flag;
		auto type = info->texattr;

		if (i < surfacenumbf)
		{
			auto ptr = (dinfo_head**)sort3d_bufferbf + i;

			for (; i < surfacenumbf; i++)
			{
				info = (dinfo_head*)(*ptr);

				if (info->texattr == 1 || info->texattr == 4 || info->texattr == 0)
				{
					if (info->tile_and_flag != tile_and_flag || info->texattr != type)
					{
						switch(type)
						{
						case 0:
							if (App.lpZBuffer)
								App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ZWRITEENABLE, TRUE);

							App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ALPHATESTENABLE, FALSE);
							App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, FALSE);
							App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA);
							App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA);

							DX_TRY(App.lpD3DDevice->SetTexture(0, DXTextureList[tile_and_flag].tex));
							D3DFVF_VERTEX
							App.lpD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 708, Bucket[0].Vertex, v3, D3DDP_DONOTUPDATEEXTENTS | D3DDP_DONOTCLIP);

							App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ALPHATESTENABLE, TRUE);
							App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, TRUE);

							break;
						case 1:
							App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ALPHATESTENABLE, TRUE);
							App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, TRUE);
							App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA);
							App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA);

							DX_TRY(App.lpD3DDevice->SetTexture(0, DXTextureList[tile_and_flag].tex));

							App.lpD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 708, Bucket[0].Vertex, v3, D3DDP_DONOTUPDATEEXTENTS | D3DDP_DONOTCLIP);

							break;
						case 2:
							if (App.lpZBuffer)
								App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ZWRITEENABLE, FALSE);

							App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ALPHATESTENABLE, FALSE);
							App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_SPECULARENABLE, FALSE);
							App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_ONE);
							App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_ONE);

							DX_TRY(App.lpD3DDevice->SetTexture(0, DXTextureList[tile_and_flag].tex));

							App.lpD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 708, Bucket[0].Vertex, v3, D3DDP_DONOTUPDATEEXTENTS | D3DDP_DONOTCLIP);

							App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_SPECULARENABLE, TRUE);
							App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA);
							App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA);

							break;
						case 3:
							if (App.lpZBuffer)
								App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ZWRITEENABLE, FALSE);

							App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ALPHATESTENABLE, TRUE);
							App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_SPECULARENABLE, FALSE);
							App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA);
							App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA);
							App.lpD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);

							DX_TRY(App.lpD3DDevice->SetTexture(0, DXTextureList[tile_and_flag].tex));

							App.lpD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 708, Bucket[0].Vertex, v3, D3DDP_DONOTUPDATEEXTENTS | D3DDP_DONOTCLIP);

							App.lpD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
							App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_SPECULARENABLE, TRUE);

							break;
						case 4:
							DX_TRY(App.lpD3DDevice->SetTexture(0, DXTextureList[tile_and_flag].tex));

							if (App.lpZBuffer)
							{
								App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ZENABLE, FALSE);
								App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ZWRITEENABLE, FALSE);
							}

							App.lpD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 708, Bucket[0].Vertex, v3, D3DDP_DONOTUPDATEEXTENTS | D3DDP_DONOTCLIP);

							if (App.lpZBuffer)
							{
								App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ZENABLE, TRUE);
								App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ZWRITEENABLE, TRUE);
							}

							break;
						case 6:
							if (App.lpZBuffer)
								App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ZWRITEENABLE, FALSE);

							App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ALPHATESTENABLE, FALSE);
							App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_ONE);
							App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_ONE);

							DX_TRY(App.lpD3DDevice->SetTexture(0, nullptr));

							App.lpD3DDevice->DrawPrimitive(D3DPT_LINELIST, 708, Bucket[0].Vertex, v3, D3DDP_DONOTUPDATEEXTENTS | D3DDP_DONOTCLIP);

							break;
						case 7:
							if (App.lpZBuffer)
								App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ZWRITEENABLE, TRUE);

							App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ALPHATESTENABLE, TRUE);
							App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA);
							App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA);
							App.lpD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);

							DX_TRY(App.lpD3DDevice->SetTexture(0, DXTextureList[tile_and_flag].tex));

							App.lpD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 708, Bucket[0].Vertex, v3, D3DDP_DONOTUPDATEEXTENTS | D3DDP_DONOTCLIP);

							App.lpD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);

							break;
						default:
							break;
						}

						v3 = 0;

						App.DrawPrimitiveCnt++;

						tile_and_flag = info->tile_and_flag;
						type = info->texattr;
						vert = Bucket[0].Vertex;
						--ptr;
					}
					else
					{
						auto vptr = (char*)(info + 1);
						for(int j = 0; j < info->num_verts; j++)
						{
							*vert++ = *(D3DTLVERTEX*)vptr;
							vptr += 40;
							vert = (D3DTLVERTEX*)((char*)vert + 40);
						}
					}
				}

				ptr++;
			}

			if (v3)
				HWR_DrawRoutine((short*)Bucket[0].Vertex, v3, tile_and_flag, type);
		}

		i = surfacenumbf - 1;

		if (i >= 0)
		{
			auto ptr = (short**)&sort3d_bufferbf[0][0];
			for (; i >= 0; i--, ptr--)
			{
				info = (dinfo_head*)(*ptr);

				if (info->texattr == 2 || info->texattr == 3 || info->texattr == 6 || info->texattr == 7)
					break;
			}
		}

		vert = Bucket[0].Vertex;
		tile_and_flag = info->tile_and_flag;
		type = info->texattr;
		int sortptra = 0;

		if (i >= 0)
		{
			auto ptr = (dinfo_head**)sort3d_bufferbf + i;

			for(; i >= 0; i--, ptr--)
			{
				info = (dinfo_head*)(*ptr);

				if (info->texattr == 2 || info->texattr == 3 || info->texattr == 6 || info->texattr == 7)
				{
					if (info->tile_and_flag != tile_and_flag || info->texattr != type)
					{
						HWR_DrawRoutine((short*)Bucket[0].Vertex, v3, tile_and_flag, type);

						v3 = 0;
						tile_and_flag = info->tile_and_flag;
						type = info->texattr;
						vert = Bucket[0].Vertex;
						ptr++;
						i++;
					}
					else
					{
						sortptra += info->num_verts;

						if (sortptra >= 2076)
						{
							HWR_DrawRoutine((short*)Bucket[0].Vertex, v3, tile_and_flag, type);

							v3 = 0;
							vert = Bucket[0].Vertex;
							sortptra = 0;
						}

						auto vptr = (char*)(info + 1);
						for (int j = 0; j < info->num_verts; j++, v3++)
						{
							*vert = *(D3DTLVERTEX*)vptr;
							vptr += 40;
							vert = (D3DTLVERTEX*)((char*)vert + 40);
						}
					}
				}
			}

			if (v3)
				HWR_DrawRoutine((short*)Bucket[0].Vertex, v3, tile_and_flag, type);
		}
	}
	else // LINE 421
	{
		auto ptr = (short**)&sort3d_bufferbf[0][0];
		for(int i = 0; i < surfacenumbf; i++, ptr++)
		{
			auto info = (dinfo_head*)(*ptr);

			if (info->e4b100 == 4)
				App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_TEXTUREPERSPECTIVE, FALSE);

			HWR_DrawRoutine((short*)(info + 1), info->num_verts, info->tile_and_flag, info->texattr);

			if (info->e4b100 == 4)
				App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_TEXTUREPERSPECTIVE, TRUE);
		}
	}

	App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ZWRITEENABLE, TRUE);
	App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ALPHATESTENABLE, FALSE);
	App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, FALSE);

	InitBuckets();
}