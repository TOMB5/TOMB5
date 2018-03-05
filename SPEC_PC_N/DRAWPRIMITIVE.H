#ifndef DRAWPRIMITIVE_H
#define DRAWPRIMITIVE_H

#include "INCLUDE.H"

extern HRESULT(*DrawPrimitive)(D3DPRIMITIVETYPE dptPrimitiveType, D3DVERTEXTYPE dvtVertexType,
	LPVOID lpvVertices, DWORD dwVertexCount, DWORD dwFlags);
extern HRESULT(*BeginScene)();
extern HRESULT(*EndScene)();
extern HRESULT(*SetRenderState)(D3DRENDERSTATETYPE dwRenderStateType, DWORD dwRenderState);

#endif