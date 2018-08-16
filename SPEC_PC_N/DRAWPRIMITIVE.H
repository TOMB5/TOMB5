#ifndef DRAWPRIMITIVE_H
#define DRAWPRIMITIVE_H

#include "INCLUDE.H"

extern HRESULT(*DrawPrimitive)(D3DPRIMITIVETYPE dptPrimitiveType, D3DVERTEXTYPE dvtVertexType,
	LPVOID lpvVertices, DWORD dwVertexCount, DWORD dwFlags);
extern HRESULT(*BeginScene)();
extern HRESULT(*EndScene)();
extern HRESULT(*SetRenderState)(D3DRENDERSTATETYPE dwRenderStateType, DWORD dwRenderState);

void InitialiseFunctionTable();

void GPU_BeginScene();

int32_t DrawPhaseGame();
void phd_PutPolygons(short* mesh);
void DrawStaticObjects(short current_room);
void DrawEffect(short fx);

void SkyDrawPhase();

extern int num_fog_bulbs;

extern uint32_t GnFrameCounter;

#endif