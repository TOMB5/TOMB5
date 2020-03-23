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
	D3DTLBUMPVERTEX v1;
	D3DTLBUMPVERTEX v2;
};

struct dinfo_tri // size 132
{
	dinfo_head head;
	D3DTLBUMPVERTEX v1;//12
	D3DTLBUMPVERTEX v2;//52
	D3DTLBUMPVERTEX v3;//92
};

struct dinfo_quad // size 252
{
	dinfo_head head;
	D3DTLBUMPVERTEX v1;//12
	D3DTLBUMPVERTEX v2;//52
	D3DTLBUMPVERTEX v3;//92
	D3DTLBUMPVERTEX v1bis;//132
	D3DTLBUMPVERTEX v3bis;//172
	D3DTLBUMPVERTEX v4;//212
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
		const D3DVALUE z = v[v4].sz;

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
		const D3DVALUE z = v[v3].sz;

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
	//Log(LT_Enter, "AddQuadClippedZBuffer %4d;%4d;%4d;%4d tex=%d", v1, v2, v3, v4, tex->tile_and_flag);
	if(0)Log(LT_Enter, "AddQuadClippedZBuffer %d=(%3.1f,%3.1f,%3.1f) %d=(%3.1f,%3.1f,%3.1f) %d=(%.1f,%3.1f,%3.1f) %d=(%3.1f,%3.1f,%3.1f) tex=%d", 
		v1, v[v1].sx, v[v1].sy, v[v1].sz,
		v2, v[v2].sx, v[v2].sy, v[v2].sz,
		v3, v[v3].sx, v[v3].sy, v[v3].sz,
		v4, v[v4].sx, v[v4].sy, v[v4].sz,
		tex->tile_and_flag);

	const WORD vp1 = d9ab34[v1];
	const WORD vp2 = d9ab34[v2];
	const WORD vp3 = d9ab34[v3];
	const WORD vp4 = d9ab34[v4];

	OBJECT_TEXTURE newtex;
	OBJECT_TEXTURE* next;

	int v1b = v1;
	int v3b = v3;

	if (!(vp1 & vp2 & vp3 & vp4))
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
				D3DTLBUMPVERTEX* vptr;
				int* cnt_ptr;

				FindBucket(next->tile_and_flag, &vptr, &cnt_ptr);

				const auto buk = (TEXTUREBUCKET*)(cnt_ptr - 1);
				Log(LT_Info, "QuadZ writing 6 verts to bucket %d", buk - Bucket);

				*cnt_ptr += 6;

				D3DTLVERTEX* vp1b = &v[v1b];

				vptr->sx = vp1b->sx;
				vptr->sy = vp1b->sy;
				vptr->sz = f_a - f_boo * vp1b->rhw;
				vptr->rhw = vp1b->rhw;
				vptr->color = vp1b->color;
				vptr->specular = vp1b->specular;
				vptr->tu = next->vertices[0].x;
				vptr->tv = next->vertices[0].y;

				Log(LT_Info, "X=%f Y=%f Z=%f", vptr->sx, vptr->sy, vptr->sz);

				vptr[3] = vptr[0];

				vptr++;

				vptr->sx = vt2->sx;
				vptr->sy = vt2->sy;
				vptr->sz = f_a - f_boo * vt2->rhw;
				vptr->rhw = vt2->rhw;
				vptr->color = vt2->color;
				vptr->specular = vt2->specular;
				vptr->tu = next->vertices[1].x;
				vptr->tv = next->vertices[1].y;

				Log(LT_Info, "X=%f Y=%f Z=%f", vptr->sx, vptr->sy, vptr->sz);

				vptr++;

				D3DTLVERTEX* vt3 = &v[v3b];

				vptr->sx = vt3->sx;
				vptr->sy = vt3->sy;
				vptr->sz = f_a - f_boo * vt3->rhw;
				vptr->rhw = vt3->rhw;
				vptr->color = vt3->color;
				vptr->specular = vt3->specular;
				vptr->tu = next->vertices[2].x;
				vptr->tv = next->vertices[2].y;

				Log(LT_Info, "X=%f Y=%f Z=%f", vptr->sx, vptr->sy, vptr->sz);

				vptr[2] = vptr[0];

				vptr++;

				D3DTLVERTEX* vt4 = &v[v4];

				vptr->sx = vt4->sx;
				vptr->sy = vt4->sy;
				vptr->sz = f_a - f_boo * vt4->rhw;
				vptr->rhw = vt4->rhw;
				vptr->color = vt4->color;
				vptr->specular = vt4->specular;
				vptr->tu = next->vertices[3].x;
				vptr->tv = next->vertices[3].y;

				Log(LT_Info, "X=%f Y=%f Z=%f", vptr->sx, vptr->sy, vptr->sz);

				d9ab1c += 2;
			}
		}
	}
}

int ZClipper(int num_vert, D3DTLBUMPVERTEX* v1, D3DTLBUMPVERTEX* v2)
{
	Unimpl();
	return 0;
}

int XYUVGClipper(int num_vert, D3DTLBUMPVERTEX* v)
{
	Unimpl();
	return 0;
}

void AddClippedPoly(D3DTLBUMPVERTEX* vt1, int num, D3DTLBUMPVERTEX* vt2)
{
	Log(LT_Enter, "AddClippedPoly n=%d", num);
	
	auto v1 = vt1;
	auto v2 = vt2;

	for(int i = 0; i < 3; i++, v1++, v2++)
	{
		v1->sx = v2->sx;
		v1->sy = v2->sy;
		v1->sz = f_a - f_boo * v2->rhw;

		v1->rhw = v2->rhw;
		v1->color = v2->color;
		v1->specular = v2->specular;

		v1->tu = v2->tv / v2->rhw;
		v1->tv = v2->sx / v2->rhw;
	}

	d9ab10++;

	num -= 3;

	for(int i = 0; i < num; i++, d9ab10++, v2++)
	{
		*v1++ = *vt1;
		*v1 = v1[-2];
		v1++;

		v1->sx = v2->sx;
		v1->sy = v2->sy;
		v1->sz = f_a - f_boo * v2->rhw;

		v1->rhw = v2->rhw;
		v1->color = v2->color;
		v1->specular = v2->specular;

		v1->tu = v2->tv / v2->rhw;
		v1->tv = v2->sx / v2->rhw;
	}
}

D3DTLBUMPVERTEX stru_BA3FB0[24];
D3DTLBUMPVERTEX stru_923C88[20];

void AddTriClippedZBuffer(D3DTLVERTEX *v, int v1, int v2, int v3, OBJECT_TEXTURE* tex, int dside)
{
	const WORD vp1 = d9ab34[v1];
	const WORD vp2 = d9ab34[v2];
	const WORD vp3 = d9ab34[v3];

	OBJECT_TEXTURE newtex;
	OBJECT_TEXTURE* next;

	D3DTLBUMPVERTEX* vptr;

	if (vp1 & vp2 & vp3)
		return;

	int v27 = 0;
	int v31 = 1;

	Log(LT_Enter, "AddTriClippedZBuffer %4d[%d];%4d[%d];%4d[%d] tex=%d", v1, vp1, v2, vp2, v3, vp3, tex->tile_and_flag);

	if ((vp1 | vp2 | vp3) & 0x8000)
	{
		if (visible_zclip(&v[v1], &v[v2], &v[v3]))
		{
			next = tex;
			vptr = stru_923C88;
			v27 = 1;
		}
		else
		{
			if (!dside)
				return;

			SWAP(v2, v3);

			if (!visible_zclip(&v[v1], &v[v2], &v[v3]))
				return;

			newtex.attribute = tex->attribute;
			newtex.new_flags = tex->new_flags;
			newtex.tile_and_flag = tex->tile_and_flag;

			newtex.vertices[0] = tex->vertices[0];
			newtex.vertices[1] = tex->vertices[2];
			newtex.vertices[2] = tex->vertices[1];

			next = &newtex;

			vptr = stru_923C88;
		}
	}
	else
	{
		if (PtrVisible(&v[v1], &v[v2], &v[v3]))
		{
			if (!dside)
				return;

			SWAP(v2, v3);

			newtex.attribute = tex->attribute;
			newtex.new_flags = tex->new_flags;
			newtex.tile_and_flag = tex->tile_and_flag;

			newtex.vertices[0] = tex->vertices[0];
			newtex.vertices[1] = tex->vertices[2];
			newtex.vertices[2] = tex->vertices[1];

			next = &newtex;
		}
		else
		{
			next = tex;
		}

		if (d9ab34[v1] | d9ab34[v2] | d9ab34[v3])
		{
			vptr = stru_BA3FB0;
		}
		else
		{
				
			int* cnt_ptr;

			FindBucket(next->tile_and_flag, &vptr, &cnt_ptr);

			const auto buk = (TEXTUREBUCKET*)(cnt_ptr - 1);
			Log(LT_Info, "TriZ writing 3 verts to bucket %d", buk - Bucket);

			v31 = 0;

			*cnt_ptr += 3;
		}
	}

	auto first = vptr;

	D3DTLVERTEX * vt1 = &v[v1];

	vptr->sx = vt1->sx;
	vptr->sy = vt1->sy;
	vptr->sz = f_a - f_boo * vt1->rhw;
	vptr->rhw = vt1->rhw;
	vptr->color = vt1->color;
	vptr->specular = vt1->specular;
	vptr->tu = next->vertices[0].x;
	vptr->tv = next->vertices[0].y;

	Log(LT_Info, "X=%f Y=%f Z=%f", vptr->sx, vptr->sy, vptr->sz);

	vptr++;

	D3DTLVERTEX* vt2 = &v[v2];

	vptr->sx = vt2->sx;
	vptr->sy = vt2->sy;
	vptr->sz = f_a - f_boo * vt2->rhw;
	vptr->rhw = vt2->rhw;
	vptr->color = vt2->color;
	vptr->specular = vt2->specular;
	vptr->tu = next->vertices[1].x;
	vptr->tv = next->vertices[1].y;

	Log(LT_Info, "X=%f Y=%f Z=%f", vptr->sx, vptr->sy, vptr->sz);

	vptr++;

	D3DTLVERTEX* vt3 = &v[v3];

	vptr->sx = vt3->sx;
	vptr->sy = vt3->sy;
	vptr->sz = f_a - f_boo * vt3->rhw;
	vptr->rhw = vt3->rhw;
	vptr->color = vt3->color;
	vptr->specular = vt3->specular;
	vptr->tu = next->vertices[2].x;
	vptr->tv = next->vertices[2].y;

	Log(LT_Info, "X=%f Y=%f Z=%f", vptr->sx, vptr->sy, vptr->sz);

	if (v31)
	{
		int v23 = 3;

		if (v27)
		{	
			v23 = ZClipper(3, stru_923C88, stru_BA3FB0);

			if (!v23)
				return;
		}
		else
		{
			for (int i = 0; i < 3; i++, first++)
			{
				first->tu *= first->rhw;
				first->tv *= first->rhw;
			}
		}

		const int v26 = XYUVGClipper(v23, stru_BA3FB0);
		if (v26)
		{
			int* cnt_ptr;

			FindBucket(next->tile_and_flag, &vptr, &cnt_ptr);

			*cnt_ptr += 3 * v26 - 6;
			AddClippedPoly(vptr, v26, stru_BA3FB0);
		}
	}
	else
	{
		for(int i = 0; i < 3; i++, first++)
		{
			first->sz = f_a - f_boo * first->rhw;
		}

		d9ab1c++;
	}
}

void AddQuadClippedSorted(D3DTLVERTEX *v, int v1, int v2, int v3, int v4, OBJECT_TEXTURE* tex, int dside)
{
	const WORD vp1 = d9ab34[v1];
	const WORD vp2 = d9ab34[v2];
	const WORD vp3 = d9ab34[v3];
	const WORD vp4 = d9ab34[v4];

	OBJECT_TEXTURE newtex;
	OBJECT_TEXTURE* next;

	int v1b = v1;
	int v3b = v3;

	if (vp1 & vp2 & vp3 & vp4)
		return;

	
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

			info3dptrbf = (short*)(info + 1);

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

void AddTriClippedSorted(D3DTLVERTEX *v, int v1, int v2, int v3, OBJECT_TEXTURE* tex, int dside)
{
	D3DTLBUMPVERTEX* vptr; // ecx
	signed int v28; // eax
	float* v29; // ecx
	signed int v30; // edx
	double v31; // st7
	int v32; // eax
	__int16* v33; // ecx
	int v34; // edx

	const WORD vp1 = d9ab34[v1];
	const WORD vp2 = d9ab34[v2];
	const WORD vp3 = d9ab34[v3];

	OBJECT_TEXTURE newtex;
	OBJECT_TEXTURE* next;

	if (vp1 & vp2 & vp3)
		return;

	Log(LT_Enter, "AddTriClippedSorted %4d[%d];%4d[%d];%4d[%d] tex=%d", v1, vp1, v2, vp2, v3, vp3, tex->tile_and_flag);

	char v36 = 0;
	int v38 = v1;
	char v1b = true;
	
	if ((vp1 | vp2 | vp3) & 0x8000u)
	{
		if (visible_zclip(&v[v1], &v[v2], &v[v3]))
		{
			next = tex;
			vptr = stru_923C88;
			
			v36 = 1;
		}
		else
		{
			if (!dside)
				return;
			
			SWAP(v2, v3);
			
			if (!visible_zclip(&v[v1], &v[v2], &v[v3]))
				return;
			
			v36 = 1;

			newtex.attribute = tex->attribute;
			newtex.new_flags = tex->new_flags;
			newtex.tile_and_flag = tex->tile_and_flag;
			
			newtex.vertices[0] = tex->vertices[0];
			newtex.vertices[1] = tex->vertices[2];
			newtex.vertices[2] = tex->vertices[1];
			
			vptr = stru_923C88;
		}
	}
	else
	{
		if (PtrVisible(&v[v1], &v[v2], &v[v3]))
		{
			if (!dside)
				return;
			
			SWAP(v2, v3);
			
			newtex.attribute = tex->attribute;
			newtex.new_flags = tex->new_flags;
			newtex.tile_and_flag = tex->tile_and_flag;
			
			newtex.vertices[0] = tex->vertices[0];
			newtex.vertices[1] = tex->vertices[2];
			newtex.vertices[2] = tex->vertices[1];
		}
		else
		{
			next = tex;
		}

		
		if (d9ab34[v38] | d9ab34[v2] | d9ab34[v3])
		{
			vptr = stru_BA3FB0;
		}
		else
		{
			auto info = (dinfo_tri*)info3dptrbf;

			info->head.texattr = next->attribute;
			info->head.tile_and_flag = next->tile_and_flag;
			info->head.num_verts = 3;
			info->head.e4b100 = e4b100;

			vptr = &info->v1;

			info3dptrbf = (short*)(info + 1);

			*sort3dptrbf++ = (int)info;

			v1b = false;
		}
	}

	D3DTLVERTEX* vt1 = &v[v1];

	vptr[0].sx = vt1->sx;
	vptr[0].sy = vt1->sy;
	vptr[0].sz = f_a - f_boo * vt1->rhw;
	vptr[0].rhw = vt1->rhw;
	vptr[0].color = vt1->color;
	vptr[0].specular = vt1->specular;
	vptr[0].tu = next->vertices[0].x;
	vptr[0].tv = next->vertices[0].y;
	vptr[0].tu2 = vt1->tu;
	vptr[0].tv2 = vt1->tv;

	float v3a = 0.0;

	if (e4b100)
	{
		v3a = v3a + vt1->sz;
	}
	else if (vt1->sz > v3a)
	{
		v3a = vt1->sz;
	}

	D3DTLVERTEX* vt2 = &v[v2];

	vptr[1].sx = vt2->sx;
	vptr[1].sy = vt2->sy;
	vptr[1].sz = f_a - f_boo * vt2->rhw;
	vptr[1].rhw = vt2->rhw;
	vptr[1].color = vt2->color;
	vptr[1].specular = vt2->specular;
	vptr[1].tu = next->vertices[1].x;
	vptr[1].tv = next->vertices[1].y;
	vptr[1].tu2 = vt2->tu;
	vptr[1].tv2 = vt2->tv;

	if (e4b100)
	{
		v3a = v3a + vt2->sz;
	}
	else if (vt2->sz > v3a)
	{
		v3a = vt2->sz;
	}
	
	D3DTLVERTEX* vt3 = &v[v3];

	vptr[2].sx = vt3->sx;
	vptr[2].sy = vt3->sy;
	vptr[2].sz = f_a - f_boo * vt3->rhw;
	vptr[2].rhw = vt3->rhw;
	vptr[2].color = vt3->color;
	vptr[2].specular = vt3->specular;
	vptr[2].tu = next->vertices[2].x;
	vptr[2].tv = next->vertices[2].y;
	vptr[2].tu2 = vt3->tu;
	vptr[2].tv2 = vt3->tv;
	
	if (e4b100)
	{
		v3a = v3a + vt3->sz;
	}
	else if (vt3->sz > v3a)
	{
		v3a = vt3->sz;
	}
	
	if (v1b)
	{
		UNIMPLEMENTED();
		return;
		v28 = 3;
		if (v36)
		{
			v28 = ZClipper(3, stru_923C88, stru_BA3FB0);
			if (!v28)
				return;
		}
		else
		{
			v29 = &stru_BA3FB0[0].rhw;
			v30 = 3;
			do
			{
				v31 = v29[3] * *v29;
				v29 += 10;
				--v30;
				*(v29 - 7) = v31;
				*(v29 - 6) = *(v29 - 6) * *(v29 - 10);
			} while (v30);
		}
		v32 = XYUVGClipper(v28, stru_BA3FB0);
		if (v32)
		{
			v33 = info3dptrbf;
			info3dptrbf[2] = next->attribute;
			v34 = 3 * v32 - 6;
			v33[4] = v34;
			if (e4b100)
				*(float*)v33 = v3a * 0.33333299;
			else
				*(float*)v33 = v3a;
			v33[3] = next->tile_and_flag;
			v33[5] = e4b100;
			info3dptrbf += 20 * v34 + 6;
			*sort3dptrbf = (int)v33;
			++sort3dptrbf;
			surfacenumbf++;
			AddClippedPoly((D3DTLBUMPVERTEX*)(v33 + 6), v32, stru_BA3FB0);
		}
	}
	else
	{
		vptr[0].sz = f_a - f_boo * vptr[0].rhw;
		vptr[1].sz = f_a - f_boo * vptr[1].rhw;
		vptr[2].sz = f_a - f_boo * vptr[2].rhw;
		
		if (e4b100)
			*(float*)&tex->attribute = v3a / 3.0;
		else
			*(float*)&tex->attribute = v3a;
		
		surfacenumbf++;
		++d9ab1c;
	}
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
	const float compare = buffer[(left + right) / 2][0];

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
		auto ptr = (dinfo_head**)buffer;
		
		for (int i = 0; i < number; i++)
		{
			(*ptr++)->z -= i / 10.0;
		}

		do_quickysorty(0, number - 1, buffer);
	}
}

HRESULT HWBeginScene()// (F)
{
	Log(LT_Enter, "HWBeginScene");
	
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
	Log(LT_Enter, "HWEndScene");
	
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

	DX_TRY(App.lpViewPort->Clear2(1, &rect, D3DCLEAR_TARGET, RGBA_MAKE(255, 0, 0, 0), 1.0f, 0));
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
		const int xv = vbufdoor[i].xv =
			phd_mxptr[M00] * portal->Vertices[i].x +
			phd_mxptr[M01] * portal->Vertices[i].y +
			phd_mxptr[M02] * portal->Vertices[i].z +
			phd_mxptr[M03];

		const int yv = vbufdoor[i].yv =
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
		const int current = bound_list[bound_start++ % 128];
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
room_info* inserting_room;
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

DWORD dword_56ED10;
DWORD dword_57753C;
float dword_56ED0C;
DWORD dword_577540;

void Update()
{
	++dword_57753C;
	dword_56ED0C = f_znear;

	dword_577540 = 0;

	if (cam_dir_flt.y >= 0.0)
		dword_56ED10 = (95 - (int)((1.0 - cam_dir_flt.y) * -144.0)) << 24;
	else
		dword_56ED10 = 0xEF000000;
}

bool CheckBoundsClip(bounding_box_f* bbox)
{
	float minX = 10000, maxX = -10000;
	float minY = 10000, maxY = -10000;
	float minZ = 10000, maxZ = -10000;

	const auto ptr = (float*)bbox;

	for (int i = 0; i < 8; i++)
	{
		const auto idx = word_511A68[i];

		const float f1 = ptr[idx[0]];
		const float f2 = ptr[idx[1]];
		const float f3 = ptr[idx[2]];

		const float ox = App.ViewMatrix._41 + App.ViewMatrix._31 * f3 + App.ViewMatrix._21 * f2 + App.ViewMatrix._11 * f1;
		const float oy = App.ViewMatrix._42 + App.ViewMatrix._32 * f3 + App.ViewMatrix._22 * f2 + App.ViewMatrix._12 * f1;
		float oz = App.ViewMatrix._43 + App.ViewMatrix._33 * f3 + App.ViewMatrix._23 * f2 + App.ViewMatrix._13 * f1;

		dword_921618[i] = { ox, oy, oz };

		const float z = MAX(f_znear, oz);
		const float persp = f_persp / z;
		const float x = persp * ox + f_centerx;
		const float y = persp * oy + f_centery;

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
DYNTHING stru_7ED6B0[64];
DWORD dword_7DFFDC;
int dword_7EE0C4;

int BuildRoomletLights(ROOMLET* r)
{
	auto dyn = dynamics;
	auto vptr = stru_7ED6B0;
	int nvert = 0;

	const float rx = inserting_room->RoomX;
	const float ry = inserting_room->RoomY;
	const float rz = inserting_room->RoomZ;

	const float minX = r->BoundingBox.minX;
	const float minZ = r->BoundingBox.minZ;
	const float maxX = r->BoundingBox.maxX;
	const float maxZ = r->BoundingBox.maxZ;

	for(int i = 0; i < 32; i++, dyn++)
	{
		if (dyn->on)
		{
			const float dx = dyn->x - rx;
			const float dy = dyn->y - ry;
			const float dz = dyn->z - rz;
			const float falloff = dyn->falloff / 2 + dyn->falloff / 8;

			if (dx - falloff <= maxX && 
				dx + falloff >= minX && 
				dz - falloff <= maxZ && 
				dz + falloff >= minZ)
			{
				vptr->sx = dx;
				vptr->sy = dy;
				vptr->sz = dz;

				vptr->r = dyn->r / 255.0;
				vptr->g = dyn->g / 255.0;
				vptr->b = dyn->b / 255.0;

				vptr->falloff = falloff;
				vptr->falloff_inv = 1 / falloff;
				vptr->falloff_sqr = falloff * falloff;
				vptr->unk = 0;

				vptr++;
				nvert++;
			}
		}
	}

	dword_7DFFDC = 0;
	if (dword_7EE0C4)
		Log(LT_Info, "BuildRoomletLights - UNIMPL FOR");
	for(int i = 0; i < dword_7EE0C4; i++)
	{
		
	}

	return nvert;
}

float flt_511A5C = SECTOR(20);
float flt_511A64 = SECTOR(12);

void RoomletTransformLight(tr5_room_vertex* vert, int num_vert, int num_lights, int num_vert_2, int a5)
{
	Log(LT_Enter, "RoomletTransformLight vert=%d lights=%d vert_2=%d a5=%5d", num_vert, num_lights, num_vert_2, a5);
	
	int water = camera.underwater;
	if (!(App.Flags & WA_BACK_BUFFER))
		water = 0;

	auto vptr = vert_buf;
	auto d9ptr = d9ab34;

	for(int i = 0; i < num_vert; i++, vptr++)
	{
		float vx = vert->Vertex.x;
		float vy = vert->Vertex.y;
		float vz = vert->Vertex.z;
		float nx = vert->Normal.x;
		float ny = vert->Normal.y;
		float nz = vert->Normal.z;

		if (i < num_vert_2)
		{
			vy += WaterTable[0][(inserting_room->MeshEffect << 6)
				+ ((BYTE)(wibble >> 2)
					+ WaterTable[0][(inserting_room->MeshEffect << 6)
						+ ((BYTE)((int)(vx + inserting_room->x) / 64)
							+ (BYTE)((int)(vy + inserting_room->y) / 64)
							+ (BYTE)((int)(vz + inserting_room->z) / 128) & 0x3F)].random & 0x3F)].choppy;
		}

		float ox = App.ViewMatrix._41 + App.ViewMatrix._31 * vz + App.ViewMatrix._21 * vy + App.ViewMatrix._11 * vx;
		float oy = App.ViewMatrix._42 + App.ViewMatrix._32 * vz + App.ViewMatrix._22 * vy + App.ViewMatrix._12 * vx;
		float oz = App.ViewMatrix._43 + App.ViewMatrix._33 * vz + App.ViewMatrix._23 * vy + App.ViewMatrix._13 * vx;

		vptr->tu = ox;
		vptr->tv = oy;

		int v7 = 0;

		if (oz < f_znear)
		{
			v7 = 0xFF80;
		}
		else
		{
			float persp = f_persp / oz;

			ox *= persp;
			oy *= persp;

			ox += f_centerx;
			oy += f_centery;

			if (water)
			{
				float fix = oz / 512.0;

				ox += flt_878658[((wibble + (long)(fix * oy)) >> 3) & 0x1F];
				oy += flt_878658[((wibble + (long)(fix * ox)) >> 3) & 0x1F];
			}

			vptr->rhw = persp * f_oneopersp;

			if (ox >= room_left_flt)
			{
				if (ox > room_right_flt)
					v7 = 2;
			}
			else
			{
				v7 = 1;
			}

			if (oy >= room_top_flt)
			{
				if (oy > room_bottom_flt)
					v7 += 8;
			}
			else
			{
				v7 += 4;
			}
		}

		BYTE cr = 0, cg = 0, cb = 0;
		BYTE sr = 0, sg = 0, sb = 0;

		vptr->sx = ox;
		vptr->sy = oy;
		vptr->sz = oz;

		vptr++;
		*d9ptr++ = v7;

		float r = 0.0, g = 0.0, b = 0.0;

		auto dyn = stru_7ED6B0;
		for(int i = 0; i < num_lights; i++, dyn++)
		{
			float dx = vx - dyn->sx;
			float dy = vy - dyn->sy;
			float dz = vz - dyn->sz;

			float sqr = dx * dx + dy * dy + dz * dz;

			if(sqr < dyn->falloff_sqr)
			{
				float norm = sqrt(sqr);

				float px = (App.ViewMatrix._31 * nz + App.ViewMatrix._21 * ny + App.ViewMatrix._11 * nx) * (1.0 / norm * dx);
				float py = (App.ViewMatrix._32 * nz + App.ViewMatrix._22 * ny + App.ViewMatrix._12 * nx) * (1.0 / norm * dy);
				float pz = (App.ViewMatrix._33 * nz + App.ViewMatrix._23 * ny + App.ViewMatrix._13 * nx) * (1.0 / norm * dz);

				float fix = (1.0 - (px + py + pz)) * ((dyn->falloff - norm) * dyn->falloff_inv);

				r += fix * dyn->r;
				g += fix * dyn->g;
				b += fix * dyn->b;
			}
		}

		BYTE vr = (vert->Colour >> 16) & 0xFF;
		BYTE vg = (vert->Colour >>  8) & 0xFF;
		BYTE vb = (vert->Colour >>  0) & 0xFF;

		int mr = vr + r * 255;
		int mg = vr + g * 255;
		int mb = vr + b * 255;

		if (dword_7EE0C8)
		{
			int fix = 2 * WaterTable[0][(inserting_room->MeshEffect << 6)
				+ ((BYTE)(wibble >> 2)
					+ WaterTable[0][(inserting_room->MeshEffect << 6)
					+ ((BYTE)(vx / 64)
						+ (BYTE)(vy / 64)
						+ (BYTE)(vz / 128) & 0x3F)].random & 0x3F)].choppy;

			mr -= fix;
			mg -= fix;
			mb -= fix;
		}
		else if (a5 != 0 && i > num_vert_2 && i < a5 + num_vert_2)
		{
			int fix = (inserting_room->MeshEffect << 6)
				+ ((BYTE)(wibble >> 2)
					+ WaterTable[0][(inserting_room->MeshEffect << 6)
					+ ((BYTE)(vx / 64)
						+ (BYTE)(vy / 64)
						+ (BYTE)(vz / 128) & 0x3F)].random & 0x3F);

			int fix2 = WaterTable[0][fix].shimmer + WaterTable[0][fix].abs;

			mr += fix;
			mg += fix;
			mb += fix;
		}

		if (oz > (double)flt_511A5C)
		{
			int fix = (oz - flt_511A5C) * flt_511A64 * 255.0;

			mr -= fix;
			mg -= fix;
			mb -= fix;
		}

		if (mr <= 128)
		{
			cr = 2 * mr;
		}
		else
		{
			sr = (mr - 128) >> 1;
			cr = 255;
		}

		if (mg <= 128)
		{
			cg = 2 * mg;
		}
		else
		{
			sg = (mg - 128) >> 1;
			cg = 255;
		}

		if (mb <= 128)
		{
			cb = 2 * mb;
		}
		else
		{
			sb = (mb - 128) >> 1;
			cb = 255;
		}

		if (dword_7DFFDC)
		{
			Unimpl();
		}

		cr = CLAMP(cr, 0, 255);
		cg = CLAMP(cg, 0, 255);
		cb = CLAMP(cb, 0, 255);

		sr = CLAMP(sr, 0, 255);
		sg = CLAMP(sg, 0, 255);
		sb = CLAMP(sb, 0, 255);

		vptr->color = ARGB(cr, cg, cb, 255);
		vptr->specular = ARGB(sr, sg, sb, 255);
	}
}

void InsertRoomlet(ROOMLET* r)
{
	if (r->NumLayerVertices == 0)
		return;

	RoomletTransformLight(
		(tr5_room_vertex*)r->VerticesOffset, 
		r->NumLayerVertices, 
		BuildRoomletLights(r) & 0x7FFFFFFF, 
		r->NumLayerVertices, 
		r->UnknownL1);

	char* poly = (char*)r->PolyOffset;

	for(int i = 0; i < r->NumLayerRectangles; i++, poly += sizeof(tr_face4))
	{
		auto face = (tr_face4*)poly;
		const auto tex = &object_textures[face->Texture];

		if (tex->attribute == OT_ALL_OPAQUE)
		{
			AddQuad1(vert_buf, face->Vertices[0], face->Vertices[1], face->Vertices[2], face->Vertices[3], tex, face->DoubleSided);
		}
		else
		{
			AddQuad2(vert_buf, face->Vertices[0], face->Vertices[1], face->Vertices[2], face->Vertices[3], tex, face->DoubleSided);
		}
	}

	for (int i = 0; i < r->NumLayerTriangles; i++, poly += sizeof(tr_face3))
	{
		auto face = (tr_face3*)poly;
		const auto tex = &object_textures[face->Texture];

		if (!tex->attribute == OT_ALL_OPAQUE)
		{
			AddTri1(vert_buf, face->Vertices[0], face->Vertices[1], face->Vertices[2], tex, face->DoubleSided);
		}
		else
		{
			AddTri2(vert_buf, face->Vertices[0], face->Vertices[1], face->Vertices[2], tex, face->DoubleSided);
		}
	}
}

void InsertRoom(room_info* r)
{
	Log(LT_Info, "InsertRoom %d", r - room);

	room_top_flt = room_top_flt_2 = r->top;
	room_left_flt = room_left_flt_2 = r->left;
	room_bottom_flt = room_bottom_flt_2 = r->bottom;
	room_right_flt = room_right_flt_2 = r->right;

	cam_pos_flt = { (float)camera.pos.x, (float)camera.pos.y, (float)camera.pos.z };
	cam_tar_flt = { (float)camera.target.x, (float)camera.target.y, (float)camera.target.z };

	const float dx = cam_tar_flt.x - cam_pos_flt.x;
	const float dy = cam_tar_flt.y - cam_pos_flt.y;
	const float dz = cam_tar_flt.z - cam_pos_flt.z;

	const float norm = sqrt(dx * dx + dy * dy + dz * dz);

	cam_dir_flt = { dx / norm, dy / norm, dz / norm };

	if (r->Unknown1)
	{
		inserting_room = r;
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
		const auto cr = &room[draw_rooms[i]];

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

	const long bak_x = lara_item->pos.x_pos;
	const long bak_y = lara_item->pos.y_pos;
	const long bak_z = lara_item->pos.z_pos;
	const short bak_room = lara_item->room_number;

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
	Log(LT_Enter, "DrawLoadingScreen");
	
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

void DrawFlash()// to test
{
	BYTE r = FlashFader * FlashFadeR >> 5;
	BYTE g = FlashFader * FlashFadeG >> 5;
	BYTE b = FlashFader * FlashFadeB >> 5;

	DrawPsxTile(0, phd_winwidth | (phd_winheight << 16), RGBA(r, g, b, 0x62));
	DrawPsxTile(0, phd_winwidth | (phd_winheight << 16), RGBA(r, g, b, 0xFF));
}

void ReleaseScreen()
{
	in_loading_screen = false;
	DXRelease(surf_screen, "Picture Surface");
}

void HWR_DrawRoutine(short* info, short num_verts, short texture, short type)// (F)
{
	Log(LT_Info, "HWR_DrawRoutine: num=%4d, tex=%4d, type=%4d", num_verts, texture, type);

	switch (type)
	{
	case OT_ALL_OPAQUE:
		if (App.lpZBuffer)
		{
			App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ZWRITEENABLE, TRUE);
		}

		App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ALPHATESTENABLE, FALSE);
		App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, FALSE);
		App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA);
		App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA);

		DX_TRY(App.lpD3DDevice->SetTexture(0, DXTextureList[texture].tex));

		App.lpD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, FVF, info, num_verts, D3DDP_DONOTUPDATEEXTENTS | D3DDP_DONOTCLIP);

		App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ALPHATESTENABLE, TRUE);
		App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, TRUE);

		break;
	case OT_ALPHA_TESTING:
		App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ALPHATESTENABLE, TRUE);
		App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, TRUE);
		App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA);
		App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA);

		DX_TRY(App.lpD3DDevice->SetTexture(0, DXTextureList[texture].tex));

		App.lpD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, FVF, info, num_verts, D3DDP_DONOTUPDATEEXTENTS | D3DDP_DONOTCLIP);

		break;
	case OT_ALPHA_BLENDING:
		if (App.lpZBuffer)
		{
			App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ZWRITEENABLE, FALSE);
		}

		App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ALPHATESTENABLE, FALSE);
		App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, FALSE);
		App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_ONE);
		App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_ONE);

		DX_TRY(App.lpD3DDevice->SetTexture(0, DXTextureList[texture].tex));

		App.lpD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, FVF, info, num_verts, D3DDP_DONOTUPDATEEXTENTS | D3DDP_DONOTCLIP);

		App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_SPECULARENABLE, TRUE);
		App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA);
		App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA);

		break;
	case OT_ALPHA_BLENDING_INV:
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

		App.lpD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, FVF, info, num_verts, D3DDP_DONOTUPDATEEXTENTS | D3DDP_DONOTCLIP);

		App.lpD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);

		App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_SPECULARENABLE, TRUE);

		break;
	case OT_ALPHA_TESTING_DEPTHLESS:
		DX_TRY(App.lpD3DDevice->SetTexture(0, DXTextureList[texture].tex));

		if (App.lpZBuffer)
		{
			App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ZENABLE, FALSE);
			App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ZWRITEENABLE, FALSE);
		}

		App.lpD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, FVF, info, num_verts, D3DDP_DONOTUPDATEEXTENTS | D3DDP_DONOTCLIP);

		if (App.lpZBuffer)
		{
			App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ZENABLE, TRUE);
			App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ZWRITEENABLE, TRUE);
		}

		break;
	case OT_UNUSED:
		break;
	case OT_WIREFRAME:
		if (App.lpZBuffer)
		{
			App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ZWRITEENABLE, FALSE);
		}

		App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ALPHATESTENABLE, FALSE);
		App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, FALSE);
		App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_ONE);
		App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_ONE);

		DX_TRY(App.lpD3DDevice->SetTexture(0, nullptr));

		App.lpD3DDevice->DrawPrimitive(D3DPT_LINELIST, FVF, info, num_verts, D3DDP_DONOTUPDATEEXTENTS | D3DDP_DONOTCLIP);

		break;
	case OT_FORCED_ALPHA:
		if (App.lpZBuffer)
		{
			App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ZWRITEENABLE, TRUE);
		}

		App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ALPHATESTENABLE, TRUE);
		App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA);
		App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA);

		App.lpD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);

		DX_TRY(App.lpD3DDevice->SetTexture(0, DXTextureList[texture].tex));

		App.lpD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, FVF, info, num_verts, D3DDP_DONOTUPDATEEXTENTS | D3DDP_DONOTCLIP);

		App.lpD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);

		break;
	default:
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

		if (surfacenumbf <= 0)
		{
			// todo: original was invalid
		}
		else
		{
			auto ptr = (short**)&sort3d_bufferbf[0][0];
			for (i = 0; i < surfacenumbf; i++, ptr++)
			{
				info = (dinfo_head*)(*ptr);

				if (info->texattr == OT_ALPHA_TESTING || 
					info->texattr == OT_ALPHA_TESTING_DEPTHLESS || 
					info->texattr == OT_ALL_OPAQUE)
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

				if (info->texattr == OT_ALPHA_TESTING ||
					info->texattr == OT_ALPHA_TESTING_DEPTHLESS ||
					info->texattr == OT_ALL_OPAQUE)
				{
					if (info->tile_and_flag != tile_and_flag || info->texattr != type)
					{
						switch(type)
						{
						case OT_ALL_OPAQUE:
							if (App.lpZBuffer)
								App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ZWRITEENABLE, TRUE);

							App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ALPHATESTENABLE, FALSE);
							App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, FALSE);
							App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA);
							App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA);

							DX_TRY(App.lpD3DDevice->SetTexture(0, DXTextureList[tile_and_flag].tex));
							App.lpD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, FVF, Bucket[0].Vertex, v3, D3DDP_DONOTUPDATEEXTENTS | D3DDP_DONOTCLIP);

							App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ALPHATESTENABLE, TRUE);
							App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, TRUE);

							break;
						case OT_ALPHA_TESTING:
							App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ALPHATESTENABLE, TRUE);
							App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, TRUE);
							App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA);
							App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA);

							DX_TRY(App.lpD3DDevice->SetTexture(0, DXTextureList[tile_and_flag].tex));

							App.lpD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, FVF, Bucket[0].Vertex, v3, D3DDP_DONOTUPDATEEXTENTS | D3DDP_DONOTCLIP);

							break;
						case OT_ALPHA_BLENDING:
							if (App.lpZBuffer)
								App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ZWRITEENABLE, FALSE);

							App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ALPHATESTENABLE, FALSE);
							App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_SPECULARENABLE, FALSE);
							App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_ONE);
							App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_ONE);

							DX_TRY(App.lpD3DDevice->SetTexture(0, DXTextureList[tile_and_flag].tex));

							App.lpD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, FVF, Bucket[0].Vertex, v3, D3DDP_DONOTUPDATEEXTENTS | D3DDP_DONOTCLIP);

							App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_SPECULARENABLE, TRUE);
							App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA);
							App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA);

							break;
						case OT_ALPHA_BLENDING_INV:
							if (App.lpZBuffer)
								App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ZWRITEENABLE, FALSE);

							App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ALPHATESTENABLE, TRUE);
							App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_SPECULARENABLE, FALSE);
							App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA);
							App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA);
							App.lpD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);

							DX_TRY(App.lpD3DDevice->SetTexture(0, DXTextureList[tile_and_flag].tex));

							App.lpD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, FVF, Bucket[0].Vertex, v3, D3DDP_DONOTUPDATEEXTENTS | D3DDP_DONOTCLIP);

							App.lpD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
							App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_SPECULARENABLE, TRUE);

							break;
						case OT_ALPHA_TESTING_DEPTHLESS:
							DX_TRY(App.lpD3DDevice->SetTexture(0, DXTextureList[tile_and_flag].tex));

							if (App.lpZBuffer)
							{
								App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ZENABLE, FALSE);
								App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ZWRITEENABLE, FALSE);
							}

							App.lpD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, FVF, Bucket[0].Vertex, v3, D3DDP_DONOTUPDATEEXTENTS | D3DDP_DONOTCLIP);

							if (App.lpZBuffer)
							{
								App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ZENABLE, TRUE);
								App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ZWRITEENABLE, TRUE);
							}

							break;
						case OT_UNUSED:
							break;
						case OT_WIREFRAME:
							if (App.lpZBuffer)
								App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ZWRITEENABLE, FALSE);

							App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ALPHATESTENABLE, FALSE);
							App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_ONE);
							App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_ONE);

							DX_TRY(App.lpD3DDevice->SetTexture(0, nullptr));

							App.lpD3DDevice->DrawPrimitive(D3DPT_LINELIST, FVF, Bucket[0].Vertex, v3, D3DDP_DONOTUPDATEEXTENTS | D3DDP_DONOTCLIP);

							break;
						case OT_FORCED_ALPHA:
							if (App.lpZBuffer)
								App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ZWRITEENABLE, TRUE);

							App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ALPHATESTENABLE, TRUE);
							App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA);
							App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA);
							App.lpD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);

							DX_TRY(App.lpD3DDevice->SetTexture(0, DXTextureList[tile_and_flag].tex));

							App.lpD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, FVF, Bucket[0].Vertex, v3, D3DDP_DONOTUPDATEEXTENTS | D3DDP_DONOTCLIP);

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
						auto vptr = (D3DTLBUMPVERTEX*)(info + 1);
						for(int j = 0; j < info->num_verts; j++, v3++)
						{
							*vert++ = *vptr++;
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
			auto ptr = (dinfo_head**)sort3d_bufferbf + i;
			for (; i >= 0; i--, ptr--)
			{
				info = *ptr;

				if (info->texattr == OT_ALPHA_BLENDING || 
					info->texattr == OT_ALPHA_BLENDING_INV || 
					info->texattr == OT_WIREFRAME || 
					info->texattr == OT_FORCED_ALPHA)
					break;
			}
		}

		v3 = 0;
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

				if (info->texattr == OT_ALPHA_BLENDING ||
					info->texattr == OT_ALPHA_BLENDING_INV ||
					info->texattr == OT_WIREFRAME ||
					info->texattr == OT_FORCED_ALPHA)
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

						auto vptr = (D3DTLBUMPVERTEX*)(info + 1);
						for (int j = 0; j < info->num_verts; j++, v3++)
						{
							*vert++ = *vptr++;
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
		auto ptr = (dinfo_head**)sort3d_bufferbf;
		for(int i = 0; i < surfacenumbf; i++, ptr++)
		{
			const auto info = *ptr;

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