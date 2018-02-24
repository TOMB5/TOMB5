#ifndef _DIRECTX_H
#define _DIRECTX_H

#include "INCLUDE.H"

struct DXCONFIG
{
	int nDD;
	int nD3D;
	int nVMode;
	int nTexture;
	int bZBuffer;
	int nSoundCard;
};

struct DISPLAYMODE					// Display Mode Info
{
	int				w;				// Width
	int				h;				// Height
	unsigned long	bpp;			// Bits Per Pixel
	unsigned int	mipMapCount;
	bool			bPalette;		// Is It Palettised
	DDSURFACEDESC	ddsd;			// Surface Description
	unsigned char	rbpp;			// Red Bits Per Pixel
	unsigned char	gbpp;			// Green Bits Per Pixel
	unsigned char	bbpp;			// Blue Bits Per Pixel
	unsigned char	rshift;			// Shifts For Red 
	unsigned char	gshift;			// Shifts For Green
	unsigned char	bshift;			// Shifts For Blue
};

struct D3DTEXTUREINFO
{
	DDPIXELFORMAT	ddpf;			// Texture Pixel Format
	unsigned long	bpp;			// Bits Per Pixel (if Palettised)
	bool			bPalette;		// Is it Palettised
	bool			bAlpha;			// Does It Support Alpha
	unsigned char	rbpp;			// Red Bits Per Pixel 
	unsigned char	gbpp;			// Green Bits Per Pixel
	unsigned char	bbpp;			// Blue Bits Per Pixel
	unsigned char	abpp;			// Alpha Bits Per Pixel
	unsigned char	rshift;			// Shifts For Red
	unsigned char	gshift;			// Shifts For Green
	unsigned char	bshift;			// Shifts For Blue
	unsigned char	ashift;			// Shifts For Alpha
};

struct zBufFormat
{
	DDPIXELFORMAT ddpf; // pos 0 s 32
	unsigned long bpp; // pos 32 s 4
};

struct DIRECT3DINFO
{
	char			Name[30];		// Name String
	char			About[80];		// Description String
	LPGUID			lpGuid;			// GUID
	GUID			Guid;
	D3DDEVICEDESC	DeviceDesc;		// Device Description
	bool			bHardware;		// Is It Hardware
	int				nDisplayMode;	// Number Of Display Modes
	DISPLAYMODE*	DisplayMode;	// Ptr To Compatible Display Modes
	int				nTexture;		// Number Of Texture Formats
	D3DTEXTUREINFO*	Texture;		// Texture Info
	DWORD numZbufFormats; // pos 402 s 4
	struct zBufFormat* zBufFormats; // pos 406 s 4
};

struct DIRECTDRAWINFO
{
	char			Name[30];		// Name String   
	char			About[80];		// Description String
	LPGUID			lpGuid;			// GUID
	GUID			Guid;
	DDCAPS			DDCaps;			// Device Capabilites
	DDDEVICEIDENTIFIER DDDevIdent;
	int				nDisplayMode;	// Number Of Display Modes	
	DISPLAYMODE*	DisplayMode;	// Ptr To Display Mode Structure
	int				nD3DInfo;		// Number Of D3D Drivers
	DIRECT3DINFO*	D3DInfo;		// Ptr To D3D Info Structure
};

struct DIRECTSOUNDINFO
{
	char			Name[30];		// Name String   
	char			About[80];		// Description String
	LPGUID			lpGuid;			// GUID
	GUID			Guid;
};

struct DEVICEINFO					// DirectX Device Information
{
	int				nDDInfo;		// Entries
	int				nDSInfo;
	DIRECTDRAWINFO*	DDInfo;			// Ptr To Info Structure
	DIRECTSOUNDINFO* DSInfo;
};

#define DXRelease(ptr, desc) {if(ptr){Log(LT_Release, "Released %s @ %x - RefCnt = %d", desc, ptr, ptr->Release());ptr=NULL;}else{Log(LT_Error, "%s Attempt To Release NULL Ptr", desc);}}

#define DXInit(dstruct)			{memset(&dstruct,0,sizeof(dstruct));dstruct.dwSize = sizeof(dstruct);}
#define DXDisplayMode(a,b)		a->DDInfo[b->nDD].D3DInfo[b->nD3D].DisplayMode[b->nVMode]  
#define DXD3DGuid(a,b)			a->DDInfo[b->nDD].D3DInfo[b->nD3D].Guid
#define DXD3D(a,b)				a->DDInfo[b->nDD].D3DInfo[b->nD3D]
#define DXD3DTexture(a,b)		a->DDInfo[b->nDD].D3DInfo[b->nD3D].Texture[b->nTexture]
#define DXDD(a,b)				a->DDInfo[b->nDD]

#define DXRGB(i,j,r,g,b)		r>>(8-DXDisplayMode(i,j).rbpp)<<(DXDisplayMode(i,j).rshift)|\
								g>>(8-DXDisplayMode(i,j).gbpp)<<(DXDisplayMode(i,j).gshift)|\
								b>>(8-DXDisplayMode(i,j).bbpp)<<(DXDisplayMode(i,j).bshift)		

#define DXRGBA(i,j,r,g,b,a)		r>>(8-DXDisplayMode(i,j).rbpp)<<(DXDisplayMode(i,j).rshift)|\
								g>>(8-DXDisplayMode(i,j).gbpp)<<(DXDisplayMode(i,j).gshift)|\
								b>>(8-DXDisplayMode(i,j).bbpp)<<(DXDisplayMode(i,j).bshift)|\
								a>>(8-DXDisplayMode(i,j).abpp)<<(DXDisplayMode(i,j).ashift)		

#define DXTEXTURERGB(i,j,r,g,b)	r>>(8-DXD3DTexture(i,j).rbpp)<<(DXD3DTexture(i,j).rshift)|\
								g>>(8-DXD3DTexture(i,j).gbpp)<<(DXD3DTexture(i,j).gshift)|\
								b>>(8-DXD3DTexture(i,j).bbpp)<<(DXD3DTexture(i,j).bshift)	

#define DXTEXTURERGBA(i,j,r,g,b,a)	r>>(8-DXD3DTexture(i,j).rbpp)<<(DXD3DTexture(i,j).rshift)|\
									g>>(8-DXD3DTexture(i,j).gbpp)<<(DXD3DTexture(i,j).gshift)|\
									b>>(8-DXD3DTexture(i,j).bbpp)<<(DXD3DTexture(i,j).bshift)|\
									a>>(8-DXD3DTexture(i,j).abpp)<<(DXD3DTexture(i,j).ashift)	

bool	DXSetCooperativeLevel(LPDIRECTDRAW2 lpDD2, HWND WindowHandle, int Flags);

void DXInitialise(DEVICEINFO* DeviceInfo, HWND WindowHandle);

#endif