#ifndef TEXTURE_H
#define TEXTURE_H

#include "INCLUDE.H"

#define MAX_D3D_TEXTURES 64

#pragma pack(push, 1)
struct DXTEXTURE
{
	LPDIRECT3DTEXTURE2 tex;
	LPDIRECTDRAWSURFACE4 surface;
	LPDIRECT3DTEXTURE2 tex2;
	DWORD a3;
	DWORD a4;
	DWORD a5;
	DWORD width;
	DWORD height;
	DWORD a8;
	BYTE a9;
	BYTE a10;
	BYTE a11;
	DWORD other_id;
};
#pragma pop

extern  DXTEXTURE DXTextureList[MAX_D3D_TEXTURES];

#endif