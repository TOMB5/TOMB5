#include "DRAWPRIMITIVE.H"
#include "GLOBAL.H"

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