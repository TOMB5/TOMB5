#ifndef TEXTURE_H
#define TEXTURE_H

#include "INCLUDE.H"

#define MAX_D3D_TEXTURES 32
#define MAX_D3D_PALETTES 16
#define TX_FLAG_SLOTUSED 1


struct DXTEXTURE
{
	IDirectDrawSurface3* pSystemSurface;
	IDirectDrawSurface3* pDeviceSurface;
	IDirectDrawPalette*	 pPalette;
	IDirect3DTexture2*	 pTexture;
	D3DTEXTUREHANDLE	 hTexture;
	int					 nWidth;
	int					 nHeight;
	DWORD				 dwFlags;
	unsigned short*		 pSoftwareSurface;
};

extern  DXTEXTURE DXTextureList[MAX_D3D_TEXTURES];
extern  IDirectDrawPalette* DXPaletteList[MAX_D3D_PALETTES];

#endif