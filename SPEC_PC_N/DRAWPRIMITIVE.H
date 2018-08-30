#ifndef DRAWPRIMITIVE_H
#define DRAWPRIMITIVE_H

#include "INCLUDE.H"



extern HRESULT(*DrawPrimitive)(D3DPRIMITIVETYPE dptPrimitiveType, D3DVERTEXTYPE dvtVertexType,
	LPVOID lpvVertices, DWORD dwVertexCount, DWORD dwFlags);
extern HRESULT(*BeginScene)();
extern HRESULT(*EndScene)();
extern HRESULT(*SetRenderState)(D3DRENDERSTATETYPE dwRenderStateType, DWORD dwRenderState);

extern bool(*PtrVisible)(D3DTLVERTEX *v1, D3DTLVERTEX *v2, D3DTLVERTEX *v3);
extern void(*AddQuad1)(D3DTLVERTEX *v, int v1, int v2, int v3, int v4, OBJECT_TEXTURE* tex, int a7);
extern void(*AddQuad2)(D3DTLVERTEX *v, int v1, int v2, int v3, int v4, OBJECT_TEXTURE* tex, int a7);
extern void(*AddTri1)(D3DTLVERTEX *v, int v1, int v2, int v3, OBJECT_TEXTURE* tex, int a7);
extern void(*AddTri2)(D3DTLVERTEX *v, int v1, int v2, int v3, OBJECT_TEXTURE* tex, int a7);
extern void(*AddLine)(D3DTLVERTEX *v1, D3DTLVERTEX *v2, short color);

void InitialiseFunctionTable();

void GPU_BeginScene();

int32_t DrawPhaseGame();
void phd_PutPolygons(short* mesh);
void DrawStaticObjects(short current_room);
void DrawEffect(short fx);

void SkyDrawPhase();

void InitialiseSortList();

void SubdivideEdge(D3DTLVERTEX *pv1, D3DTLVERTEX *pv2, D3DTLVERTEX *pv3, short *a4, float u1, float v1, float u2, float v2, float *u, float *v);
void SubdivideQuad(D3DTLVERTEX *pv1, D3DTLVERTEX *pv2, D3DTLVERTEX *pv3, D3DTLVERTEX *pv4, OBJECT_TEXTURE* tex, int a6, int a7, short *face);
void SubdivideTri(D3DTLVERTEX *pv1, D3DTLVERTEX *pv2, D3DTLVERTEX *pv3, OBJECT_TEXTURE* tex, int a5, int a6, short *face);
void AddQuadSubdivide(D3DTLVERTEX *v, int v1, int v2, int v3, int v4, OBJECT_TEXTURE* tex, int a7);
void AddTriSubdivide(D3DTLVERTEX *v, int v1, int v2, int v3, OBJECT_TEXTURE* tex, int a7);
void AddQuadClippedZBuffer(D3DTLVERTEX *v, int v1, int v2, int v3, int v4, OBJECT_TEXTURE* tex, int a7);
void AddTriClippedZBuffer(D3DTLVERTEX *v, int v1, int v2, int v3, OBJECT_TEXTURE* tex, int a7);
void AddQuadClippedSorted(D3DTLVERTEX *v, int v1, int v2, int v3, int v4, OBJECT_TEXTURE* tex, int a7);
void AddTriClippedSorted(D3DTLVERTEX *v, int v1, int v2, int v3, OBJECT_TEXTURE* tex, int a7);
void AddLineClippedSorted(D3DTLVERTEX *v1, D3DTLVERTEX *v2, short color);
HRESULT HWBeginScene();
HRESULT HWEndScene();
bool Visible(D3DTLVERTEX *v1, D3DTLVERTEX *v2, D3DTLVERTEX *v3);
void SetGlobalAmbient(uint32_t color);
void PrintObjects(short current_room);
void DoRain();
void DoSnow();
void SortPolyList(int number, float buffer[][10]);
void DrawBinoculars();
void DrawLoadingScreen();
void ReleaseScreen();
void DrawFlash();
void DrawSortList();
extern uint32_t global_ambient;

extern SNOWFLAKE raindrops[];
extern SNOWFLAKE snowflakes[];


extern float sort3d_bufferbf[][10];
extern short info3d_bufferbf[];
extern int* sort3dptrbf;
extern short* info3dptrbf;
extern int surfacenumbf;

extern int num_fog_bulbs;

extern int num_snow_flakes;
extern int num_rain_drops;
extern int num_snow_splashes;
extern int num_rain_splashes;

extern float fog_start;
extern float fog_end;

extern uint32_t GnFrameCounter;

#endif