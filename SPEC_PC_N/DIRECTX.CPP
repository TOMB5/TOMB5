#include <ddraw.h>
#include "DIRECTX.H"
#include "GLOBAL.H"
#include <dinput.h>
#pragma comment (lib, "ddraw.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "dinput.lib")
#pragma comment (lib, "d3dx9.lib")

static LPDIRECTDRAW4		enum_lpDD;
static LPDIRECT3D3			enum_lpD3D;
static LPDIRECTDRAWSURFACE4 enum_lpDDSurface;
static LPDIRECT3DDEVICE3	enum_lpD3DDevice;
static HWND					WindowHandle;
static bool bSoftRend = false;

void DXBitMask2ShiftCnt(unsigned long mask, unsigned char* shift, unsigned char* cnt)
{
	unsigned long m;
	unsigned char n;
	for (n = 0, m = mask; !(m & 1); n++, m >>= 1);
	*shift = n;
	for (n = 0; m & 1; n++, m >>= 1);
	*cnt = n;
}

#ifdef __cplusplus
extern "C" {
#endif
	bool DXSetCooperativeLevel(LPDIRECTDRAW4 lpDD, HWND WindowHandle, int Flags)
	{
		static const char* flags[] =
		{
			"fullscreen",		  //    1
			"allowreboot",		  //    2
			"nowindowchanges",	  //    4
			"normal",			  //    8
			"exclusive",		  //   16
			"",					  //   32
			"allowmodex",		  //   64
			"setfocuswindow",	  //  128
			"setdevicewindow",	  //  256
			"createdevicewindow", //  512
			"multithreaded",	  // 1024
			"fpusetup",			  // 2048
		};

		char v120[1024];
		strcpy(v120, "DXSetCooperativeLevel - ");

		for (int i = 0; i < 12; i++)
		{
			if (Flags & (1 << i))
			{
				strcat(v120, flags[i]);
				strcat(v120, " ");
			}
		}
		
		Log(LT_Info, v120);

		int RetVal;
		RetVal = lpDD->SetCooperativeLevel(WindowHandle, Flags);
		if (RetVal != DD_OK) return false;
		return true;
	}
#ifdef __cplusplus
}
#endif
BOOL DXDDCreate(GUID FAR* lpGuid, LPDIRECTDRAW* lpDD)
{
	LPDIRECTDRAW lpDDTemp;

	Log(LT_Enter, "DXDDCreate");

	if (DX_TRY(DirectDrawCreate(lpGuid, &lpDDTemp, NULL)))
	{
		Log(LT_Error, "DXDDCreate Failed");
		return FALSE;
	}

	DX_TRY(lpDDTemp->QueryInterface(IID_IDirectDraw4, (LPVOID*)lpDD));

	DXRelease(lpDDTemp, "DirectDraw");

	Log(LT_Info, "DXDDCreate Successful");

	return TRUE;
}

HRESULT CALLBACK DXEnumDisplayModes(LPDDSURFACEDESC2 lpddsd, LPVOID lpContext)
{
	DIRECTDRAWINFO* DDInfo;
	DDInfo = (DIRECTDRAWINFO*)lpContext;

	if (DDInfo->nDisplayMode == 0)
		DDInfo->DisplayMode = (DISPLAYMODE*)malloc(sizeof(DISPLAYMODE));
	else
		DDInfo->DisplayMode = (DISPLAYMODE*)realloc(DDInfo->DisplayMode, sizeof(DISPLAYMODE)*(DDInfo->nDisplayMode + 1));

	memset(&DDInfo->DisplayMode[DDInfo->nDisplayMode], 0, sizeof(DISPLAYMODE));

	DDInfo->DisplayMode[DDInfo->nDisplayMode].w = lpddsd->dwWidth;
	DDInfo->DisplayMode[DDInfo->nDisplayMode].h = lpddsd->dwHeight;
	DDInfo->DisplayMode[DDInfo->nDisplayMode].bpp = lpddsd->ddpfPixelFormat.dwRGBBitCount;
	DDInfo->DisplayMode[DDInfo->nDisplayMode].bPalette = lpddsd->ddpfPixelFormat.dwFlags&DDPF_PALETTEINDEXED8 ? true : false;
	DDInfo->DisplayMode[DDInfo->nDisplayMode].mipMapCount = lpddsd->dwMipMapCount;
	memcpy(&DDInfo->DisplayMode[DDInfo->nDisplayMode].ddsd, lpddsd, sizeof(DDSURFACEDESC));

	if (DDInfo->DisplayMode[DDInfo->nDisplayMode].bPalette)
	{
		Log(
			LT_Info,
			"%d x %d - %d Bit - Palette",
			DDInfo->DisplayMode[DDInfo->nDisplayMode].w,
			DDInfo->DisplayMode[DDInfo->nDisplayMode].h,
			DDInfo->DisplayMode[DDInfo->nDisplayMode].bpp);
	}
	else
	{
		DXBitMask2ShiftCnt(lpddsd->ddpfPixelFormat.dwRBitMask,
		                   &DDInfo->DisplayMode[DDInfo->nDisplayMode].rshift,
		                   &DDInfo->DisplayMode[DDInfo->nDisplayMode].rbpp);

		DXBitMask2ShiftCnt(lpddsd->ddpfPixelFormat.dwGBitMask,
		                   &DDInfo->DisplayMode[DDInfo->nDisplayMode].gshift,
		                   &DDInfo->DisplayMode[DDInfo->nDisplayMode].gbpp);

		DXBitMask2ShiftCnt(lpddsd->ddpfPixelFormat.dwBBitMask,
		                   &DDInfo->DisplayMode[DDInfo->nDisplayMode].bshift,
		                   &DDInfo->DisplayMode[DDInfo->nDisplayMode].bbpp);

		Log(
			LT_Info,
			"%d x %d - %d Bit - %d%d%d",
			DDInfo->DisplayMode[DDInfo->nDisplayMode].w,
			DDInfo->DisplayMode[DDInfo->nDisplayMode].h,
			DDInfo->DisplayMode[DDInfo->nDisplayMode].bpp,
			DDInfo->DisplayMode[DDInfo->nDisplayMode].rbpp,
			DDInfo->DisplayMode[DDInfo->nDisplayMode].gbpp,
			DDInfo->DisplayMode[DDInfo->nDisplayMode].bbpp);
	}

	DDInfo->nDisplayMode++;

	return DDENUMRET_OK;
}

bool DXCreateDirect3D(LPDIRECTDRAW4 lpDD2, LPDIRECT3D3* lpD3D2)
{
	int RetVal;
	RetVal = lpDD2->QueryInterface(IID_IDirect3D3, (LPVOID*)lpD3D2);
	if (DX_TRY(RetVal))
	{
		Log(LT_Error, "DXD3DCreate Failed");
		return false;
	}
	else
	{
		Log(LT_Info, "DXD3DCreate Successful");
		return true;
	}
}

DWORD BPPToDDBD(int bpp)
{
	switch (bpp)
	{
	case 1:
		return DDBD_1;
	case 2:
		return DDBD_2;
	case 4:
		return DDBD_4;
	case 8:
		return DDBD_8;
	case 16:
		return DDBD_16;
	case 24:
		return DDBD_24;
	case 32:
		return DDBD_32;
	}
	return (DWORD)0;
}

bool DXCreateSurface(LPDIRECTDRAW4 lpDD2, DDSURFACEDESC2* ddsd, LPDIRECTDRAWSURFACE4* lpSurface)
{
	Log(LT_Enter, "DXCreateSurface");
	int RetVal;
	RetVal = lpDD2->CreateSurface(ddsd, lpSurface, NULL);
	if (DX_TRY(RetVal))
	{
		Log(LT_Error, "DXCreateSurface Failed");
		return false;
	}
	return true;
}

bool DXCreateDirect3DDevice(LPDIRECT3D3 lpD3D2, GUID Guid, LPDIRECTDRAWSURFACE4 lpSurface, LPDIRECT3DDEVICE3* lpD3DDevice2)
{
	int RetVal;
	RetVal = lpD3D2->CreateDevice(Guid, lpSurface, lpD3DDevice2, NULL);
	if (DX_TRY(RetVal))
	{
		Log(LT_Error, "DXCreateD3DDevice Failed");
		return false;
	}
	else
	{
		Log(LT_Info, "DXCreateD3DDevice Successful");
		return true;
	}
}

bool DXCreateViewport(LPDIRECT3D3 lpD3D, LPDIRECT3DDEVICE3 lpD3DDevice, int w, int h, LPDIRECT3DVIEWPORT3* lpViewport)
{
	D3DVIEWPORT2 viewdata;

	Log(LT_Enter, "DXCreateViewport");

	if (DX_TRY(lpD3D->CreateViewport(lpViewport, NULL))) return false;

	if (DX_TRY(lpD3DDevice->AddViewport(*lpViewport))) return false;

	DXInit(viewdata);
	viewdata.dvClipWidth = w;
	viewdata.dvClipHeight = h;
	viewdata.dwX = 0;
	viewdata.dwY = 0;
	viewdata.dvClipX = 0.0;
	viewdata.dvClipY = 0.0;
	viewdata.dvMinZ = 0.0;
	viewdata.dwHeight = h;
	viewdata.dwWidth = w;
	viewdata.dvMaxZ = 1.0;

	if (DX_TRY((*lpViewport)->SetViewport2(&viewdata))) return false;

	DX_TRY(lpD3DDevice->SetCurrentViewport(*lpViewport));

	return true;
}

bool DXSetVideoMode(LPDIRECTDRAW4 lpDD2, int w, int h, int bpp)
{
#if TRUE
	// otherwise it fucks up my desktop icons --zdimension
	w = 1680;
	h = 1050;
	bpp = 32;
#endif
	int RetVal;
	Log(LT_Enter, "DXSetVideoMode");
	Log(LT_Info, "SetDisplayMode - %dx%dx%d", w, h, bpp);
	RetVal = lpDD2->SetDisplayMode(w, h, bpp, 0, NULL);
	if (RetVal != DD_OK) return false;
	return true;
}

HRESULT CALLBACK DXEnumTextureFormats(LPDDPIXELFORMAT lpddpf, LPVOID lpContext)
{
	DIRECT3DINFO* D3DInfo;
	D3DInfo = (DIRECT3DINFO*)lpContext;

	if (D3DInfo->nTexture == 0)
		D3DInfo->Texture = (D3DTEXTUREINFO*)malloc(sizeof(D3DTEXTUREINFO));
	else
		D3DInfo->Texture = (D3DTEXTUREINFO*)realloc(D3DInfo->Texture, sizeof(D3DTEXTUREINFO)*(D3DInfo->nTexture + 1));


	memset(&D3DInfo->Texture[D3DInfo->nTexture], 0, sizeof(D3DTEXTUREINFO));
	memcpy(&D3DInfo->Texture[D3DInfo->nTexture].ddpf, lpddpf, sizeof(DDPIXELFORMAT));

	if (lpddpf->dwFlags & DDPF_PALETTEINDEXED8)
	{
		D3DInfo->Texture[D3DInfo->nTexture].bPalette = true;
		D3DInfo->Texture[D3DInfo->nTexture].bpp = 8;
		Log(LT_Info, "8 Bit");
	}
	else if (lpddpf->dwFlags & DDPF_PALETTEINDEXED4)
	{
		D3DInfo->Texture[D3DInfo->nTexture].bPalette = true;
		D3DInfo->Texture[D3DInfo->nTexture].bpp = 4;
		Log(LT_Info, "4 Bit");
	}
	else
	{
		D3DInfo->Texture[D3DInfo->nTexture].bPalette = false;
		D3DInfo->Texture[D3DInfo->nTexture].bpp = lpddpf->dwRGBBitCount;

		if (lpddpf->dwFlags & DDPF_RGB)
		{
			DXBitMask2ShiftCnt(lpddpf->dwRBitMask,
				&D3DInfo->Texture[D3DInfo->nTexture].rshift,
				&D3DInfo->Texture[D3DInfo->nTexture].rbpp);

			DXBitMask2ShiftCnt(lpddpf->dwGBitMask,
				&D3DInfo->Texture[D3DInfo->nTexture].gshift,
				&D3DInfo->Texture[D3DInfo->nTexture].gbpp);

			DXBitMask2ShiftCnt(lpddpf->dwBBitMask,
				&D3DInfo->Texture[D3DInfo->nTexture].bshift,
				&D3DInfo->Texture[D3DInfo->nTexture].bbpp);

			if (lpddpf->dwFlags & DDPF_ALPHAPIXELS)
			{
				DXBitMask2ShiftCnt(lpddpf->dwRGBAlphaBitMask,
					&D3DInfo->Texture[D3DInfo->nTexture].ashift,
					&D3DInfo->Texture[D3DInfo->nTexture].abpp);
				D3DInfo->Texture[D3DInfo->nTexture].bAlpha = true;

				Log(LT_Info, "%d Bit %d%d%d%d RGBA", 
					D3DInfo->Texture[D3DInfo->nTexture].bpp,
					D3DInfo->Texture[D3DInfo->nTexture].rbpp,
					D3DInfo->Texture[D3DInfo->nTexture].gbpp,
					D3DInfo->Texture[D3DInfo->nTexture].bbpp,
					D3DInfo->Texture[D3DInfo->nTexture].abpp);
			}
			else
			{
				Log(LT_Info, "%d Bit %d%d%d RGB", 
					D3DInfo->Texture[D3DInfo->nTexture].bpp,
					D3DInfo->Texture[D3DInfo->nTexture].rbpp,
					D3DInfo->Texture[D3DInfo->nTexture].gbpp, 
					D3DInfo->Texture[D3DInfo->nTexture].bbpp);
			}
		}

	}

	D3DInfo->nTexture++;

	return D3DENUMRET_OK;
}

HRESULT CALLBACK DXEnumZBufferFormats(LPDDPIXELFORMAT lpddpf, LPVOID lpContext)
{
	DIRECT3DINFO* D3DInfo;
	D3DInfo = (DIRECT3DINFO*)lpContext;

	if (D3DInfo->nZbuffer== 0)
		D3DInfo->Zbuffer = (zBufFormat*)malloc(sizeof(zBufFormat));
	else
		D3DInfo->Zbuffer = (zBufFormat*)realloc(D3DInfo->Zbuffer, sizeof(zBufFormat)*(D3DInfo->nZbuffer + 1));


	memset(&D3DInfo->Zbuffer[D3DInfo->nZbuffer], 0, sizeof(zBufFormat));
	memcpy(&D3DInfo->Zbuffer[D3DInfo->nZbuffer].ddpf, lpddpf, sizeof(DDPIXELFORMAT));

	D3DInfo->Zbuffer[D3DInfo->nZbuffer].bpp = lpddpf->dwRGBBitCount;

	Log(LT_Info, "%d Bit", D3DInfo->Zbuffer[D3DInfo->nZbuffer].bpp);

	D3DInfo->nZbuffer++;

	return D3DENUMRET_OK;
}

HRESULT CALLBACK DXEnumDirect3D(LPGUID lpGuid, LPSTR lpDeviceDesc, LPSTR lpDeviceName, LPD3DDEVICEDESC lpHWDesc, LPD3DDEVICEDESC lpHELDesc, LPVOID lpContext)
{
	int n;

	DIRECTDRAWINFO* DDInfo;
	DDInfo = (DIRECTDRAWINFO*)lpContext;

	if (lpHWDesc->dwFlags == 0)
	{
		if (lpHELDesc->dcmColorModel & D3DCOLOR_MONO) return D3DENUMRET_OK;
	}


#ifdef DISABLESOFTWARE
	if (lpHWDesc->dwFlags == 0)
		return D3DENUMRET_OK;
#endif

	if (lpHWDesc->dwFlags == 0 && bSoftRend == true)
		return D3DENUMRET_OK;


	if (lpHWDesc->dwFlags == 0)
	{
		bSoftRend = true;
		strcpy(lpDeviceDesc, "Core Design Hardware Card Emulation");
		strcpy(lpDeviceName, "RGB Emulation");
	}


	if (DDInfo->nD3DInfo == 0)
		DDInfo->D3DInfo = (DIRECT3DINFO*)malloc(sizeof(DIRECT3DINFO));
	else
		DDInfo->D3DInfo = (DIRECT3DINFO*)realloc(DDInfo->D3DInfo, sizeof(DIRECT3DINFO)*(DDInfo->nD3DInfo + 1));

	memset(&DDInfo->D3DInfo[DDInfo->nD3DInfo], 0, sizeof(DIRECT3DINFO));

	if (lpGuid == NULL)
		DDInfo->D3DInfo[DDInfo->nD3DInfo].lpGuid = NULL;
	else
	{
		DDInfo->D3DInfo[DDInfo->nD3DInfo].lpGuid = &DDInfo->D3DInfo[DDInfo->nD3DInfo].Guid;
		memcpy(&DDInfo->D3DInfo[DDInfo->nD3DInfo].Guid, lpGuid, sizeof(GUID));
	}

	lstrcpy(DDInfo->D3DInfo[DDInfo->nD3DInfo].About, lpDeviceDesc);
	lstrcpy(DDInfo->D3DInfo[DDInfo->nD3DInfo].Name, lpDeviceName);

	if (lpHWDesc->dwFlags != 0)
	{
		DDInfo->D3DInfo[DDInfo->nD3DInfo].bHardware = true;
		memcpy(&DDInfo->D3DInfo[DDInfo->nD3DInfo].DeviceDesc, lpHWDesc, sizeof(D3DDEVICEDESC));
	}
	else
	{
		DDInfo->D3DInfo[DDInfo->nD3DInfo].bHardware = false;
		memcpy(&DDInfo->D3DInfo[DDInfo->nD3DInfo].DeviceDesc, lpHELDesc, sizeof(D3DDEVICEDESC));
	}

	Log(LT_Info, "Finding Compatible Display Modes");

	for (n = 0; n<DDInfo->nDisplayMode; n++)
	{
		if (BPPToDDBD(DDInfo->DisplayMode[n].bpp)&DDInfo->D3DInfo[DDInfo->nD3DInfo].DeviceDesc.dwDeviceRenderBitDepth)
		{
			if (DDInfo->D3DInfo[DDInfo->nD3DInfo].nDisplayMode == 0)
				DDInfo->D3DInfo[DDInfo->nD3DInfo].DisplayMode = (DISPLAYMODE*)malloc(sizeof(DISPLAYMODE));
			else
				DDInfo->D3DInfo[DDInfo->nD3DInfo].DisplayMode = (DISPLAYMODE*)realloc(DDInfo->D3DInfo[DDInfo->nD3DInfo].DisplayMode, sizeof(DISPLAYMODE)*(DDInfo->D3DInfo[DDInfo->nD3DInfo].nDisplayMode + 1));

			memcpy(&DDInfo->D3DInfo[DDInfo->nD3DInfo].DisplayMode[DDInfo->D3DInfo[DDInfo->nD3DInfo].nDisplayMode], &DDInfo->DisplayMode[n], sizeof(DISPLAYMODE));

			if (DDInfo->D3DInfo[DDInfo->nD3DInfo].DisplayMode[DDInfo->D3DInfo[DDInfo->nD3DInfo].nDisplayMode].bPalette)
			{
				Log(LT_Info, "%d x %d - %d Bit - Palette", 
					DDInfo->D3DInfo[DDInfo->nD3DInfo].DisplayMode[DDInfo->D3DInfo[DDInfo->nD3DInfo].nDisplayMode].w, 
					DDInfo->D3DInfo[DDInfo->nD3DInfo].DisplayMode[DDInfo->D3DInfo[DDInfo->nD3DInfo].nDisplayMode].h, 
					DDInfo->D3DInfo[DDInfo->nD3DInfo].DisplayMode[DDInfo->D3DInfo[DDInfo->nD3DInfo].nDisplayMode].bpp);
			}
			else
			{
				Log(
					LT_Info, "%d x %d - %d Bit - %d%d%d",
					DDInfo->D3DInfo[DDInfo->nD3DInfo].DisplayMode[DDInfo->D3DInfo[DDInfo->nD3DInfo].nDisplayMode].w,
					DDInfo->D3DInfo[DDInfo->nD3DInfo].DisplayMode[DDInfo->D3DInfo[DDInfo->nD3DInfo].nDisplayMode].h,
					DDInfo->D3DInfo[DDInfo->nD3DInfo].DisplayMode[DDInfo->D3DInfo[DDInfo->nD3DInfo].nDisplayMode].bpp,
					DDInfo->D3DInfo[DDInfo->nD3DInfo].DisplayMode[DDInfo->D3DInfo[DDInfo->nD3DInfo].nDisplayMode].rbpp,
					DDInfo->D3DInfo[DDInfo->nD3DInfo].DisplayMode[DDInfo->D3DInfo[DDInfo->nD3DInfo].nDisplayMode].gbpp,
					DDInfo->D3DInfo[DDInfo->nD3DInfo].DisplayMode[DDInfo->D3DInfo[DDInfo->nD3DInfo].nDisplayMode].bbpp);
			}

			DDInfo->D3DInfo[DDInfo->nD3DInfo].nDisplayMode++;
		}
	}

	Log(LT_Info, "Enumerate Texture Formats");

	DDSURFACEDESC2 ddsd;
	DXInit(ddsd);
	ddsd.dwFlags = DDSD_CAPS;
	ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | DDSCAPS_3DDEVICE;

	DXSetCooperativeLevel(enum_lpDD, WindowHandle, DDSCL_FULLSCREEN | DDSCL_EXCLUSIVE | DDSCL_NOWINDOWCHANGES);
	DXCreateSurface(enum_lpDD, &ddsd, &enum_lpDDSurface);
	
	if (enum_lpDDSurface)
	{
		DXCreateDirect3DDevice(enum_lpD3D, DDInfo->D3DInfo[DDInfo->nD3DInfo].Guid, enum_lpDDSurface, &enum_lpD3DDevice);

		if (enum_lpD3DDevice == NULL)
		{
			Log(LT_Error, "Create D3DDevice Failed");

			DXRelease(enum_lpDDSurface, "DirectDrawSurface");

			DXSetVideoMode(
				enum_lpDD,
				DDInfo->D3DInfo[DDInfo->nD3DInfo].DisplayMode->w,
				DDInfo->D3DInfo[DDInfo->nD3DInfo].DisplayMode->h,
				DDInfo->D3DInfo[DDInfo->nD3DInfo].DisplayMode->bpp);

			DXCreateSurface(enum_lpDD, &ddsd, &enum_lpDDSurface);

			if (enum_lpDDSurface)
			{
				DXCreateDirect3DDevice(enum_lpD3D, DDInfo->D3DInfo[DDInfo->nD3DInfo].Guid, enum_lpDDSurface, &enum_lpD3DDevice);
			}
		}

		if (enum_lpD3DDevice)
		{
			DDInfo->D3DInfo[DDInfo->nD3DInfo].nTexture = 0;
			Log(LT_Enter, "DXEnumTextureFormats");

			enum_lpD3DDevice->EnumTextureFormats(DXEnumTextureFormats, (LPVOID)&DDInfo->D3DInfo[DDInfo->nD3DInfo]);

			DXRelease(enum_lpD3DDevice, "D3DDevice");
			DXRelease(enum_lpDDSurface, "DirectDrawSurface");
		}
	}

	DXSetCooperativeLevel(enum_lpDD, WindowHandle, DDSCL_NORMAL);

	Log(LT_Info, "Enumerating ZBuffer Formats");
	Log(LT_Enter, "DXEnumZBufferFormats");

	DX_TRY(enum_lpD3D->EnumZBufferFormats(
		DDInfo->D3DInfo[DDInfo->nD3DInfo].Guid,
		DXEnumZBufferFormats,
		&DDInfo->D3DInfo[DDInfo->nD3DInfo]));

	DDInfo->nD3DInfo++;

	return D3DENUMRET_OK;
}

BOOL CALLBACK DXEnumDirectDraw(GUID FAR* lpGuid, LPSTR lpDeviceDesc, LPSTR lpDeviceName, LPVOID lpContext)
{
	Log(LT_Enter, "DXEnumDirectDraw");

	DEVICEINFO*		 dd;

	dd = (DEVICEINFO*)lpContext;

	if (dd->nDDInfo == 0)
		dd->DDInfo = (DIRECTDRAWINFO*)malloc(sizeof(DIRECTDRAWINFO));
	else
		dd->DDInfo = (DIRECTDRAWINFO*)realloc(dd->DDInfo, sizeof(DIRECTDRAWINFO)*(dd->nDDInfo + 1));

	memset(&dd->DDInfo[dd->nDDInfo], 0, sizeof(DIRECTDRAWINFO));
	
	if (lpGuid == NULL)
		dd->DDInfo[dd->nDDInfo].lpGuid = NULL;
	else
	{
		dd->DDInfo[dd->nDDInfo].lpGuid = &dd->DDInfo[dd->nDDInfo].Guid;
		memcpy(&dd->DDInfo[dd->nDDInfo].Guid, lpGuid, sizeof(GUID));
	}

	lstrcpy(dd->DDInfo[dd->nDDInfo].About, lpDeviceDesc);
	lstrcpy(dd->DDInfo[dd->nDDInfo].Name, lpDeviceName);

	Log(LT_Info, "Obtaining Information For %s", lpDeviceDesc);

	if (DXDDCreate(lpGuid, (LPDIRECTDRAW*)&enum_lpDD))
	{
		DX_TRY(enum_lpDD->GetDeviceIdentifier(&dd->DDInfo[dd->nDDInfo].DDDevIdent, NULL));
		Log(LT_Info, "Found - %s\nDriver %s Version %d.%d.%d.%d",
			dd->DDInfo[dd->nDDInfo].DDDevIdent.szDescription,
			dd->DDInfo[dd->nDDInfo].DDDevIdent.szDriver,
			HIWORD(dd->DDInfo[dd->nDDInfo].DDDevIdent.liDriverVersion.HighPart),
			LOWORD(dd->DDInfo[dd->nDDInfo].DDDevIdent.liDriverVersion.HighPart),
			HIWORD(dd->DDInfo[dd->nDDInfo].DDDevIdent.liDriverVersion.LowPart),
			LOWORD(dd->DDInfo[dd->nDDInfo].DDDevIdent.liDriverVersion.LowPart));

		DXInit(dd->DDInfo[dd->nDDInfo].DDCaps);

		Log(LT_Info, "Getting Device Capabilities");

		DX_TRY(enum_lpDD->GetCaps(&dd->DDInfo[dd->nDDInfo].DDCaps, NULL));

		Log(LT_Info, "Enumerating Display Modes");

		DXSetCooperativeLevel(enum_lpDD, NULL, DDSCL_NOWINDOWCHANGES | DDSCL_ALLOWMODEX | DDSCL_FULLSCREEN | DDSCL_NORMAL);

		DX_TRY(enum_lpDD->EnumDisplayModes(0, NULL, (LPVOID)&dd->DDInfo[dd->nDDInfo], DXEnumDisplayModes));

		if (DXCreateDirect3D(enum_lpDD, &enum_lpD3D))
		{
			Log(LT_Enter, "DXEnumDirect3D");
			DX_TRY(enum_lpD3D->EnumDevices(DXEnumDirect3D, (LPVOID)&dd->DDInfo[dd->nDDInfo]));
			DXRelease(enum_lpD3D, "Direct3D");
		}

		DXSetCooperativeLevel(enum_lpDD, NULL, DDSCL_NORMAL);

		DXRelease(enum_lpDD, "DirectDraw");
	}

	dd->nDDInfo++;

	return DDENUMRET_OK;
}

BOOL CALLBACK DXEnumDirectSound(GUID FAR* lpGuid, LPCSTR lpDeviceDesc, LPCSTR lpDeviceName, LPVOID lpContext)
{
	Log(LT_Enter, "DXEnumDirectSound");

	DEVICEINFO*		 dd;

	dd = (DEVICEINFO*)lpContext;

	if (dd->nDSInfo == 0)
		dd->DSInfo = (DIRECTSOUNDINFO*)malloc(sizeof(DIRECTSOUNDINFO));
	else
		dd->DSInfo = (DIRECTSOUNDINFO*)realloc(dd->DSInfo, sizeof(DIRECTSOUNDINFO)*(dd->nDSInfo + 1));

	memset(&dd->DSInfo[dd->nDSInfo], 0, sizeof(DIRECTSOUNDINFO));

	if (lpGuid == NULL)
		dd->DSInfo[dd->nDSInfo].lpGuid = NULL;
	else
	{
		dd->DSInfo[dd->nDSInfo].lpGuid = &dd->DSInfo[dd->nDSInfo].Guid;
		memcpy(&dd->DSInfo[dd->nDSInfo].Guid, lpGuid, sizeof(GUID));
	}

	lstrcpy(dd->DSInfo[dd->nDSInfo].About, lpDeviceDesc);
	lstrcpy(dd->DSInfo[dd->nDSInfo].Name, lpDeviceName);

	Log(LT_Info, "Found - %s %s", dd->DSInfo[dd->nDSInfo].About, dd->DSInfo[dd->nDSInfo].Name);

	dd->nDSInfo++;

	return DDENUMRET_OK;
}

void DXInitialise(DEVICEINFO* dd, HWND hWnd)
{
	Log(LT_Enter, "DXInitialise");
	WindowHandle = hWnd;
	Log(LT_Info, "Enumerating DirectDraw Devices");
	DX_TRY(DirectDrawEnumerate(DXEnumDirectDraw, dd));
	DX_TRY(DirectSoundEnumerate(DXEnumDirectSound, dd));
}

void CloseDirectX()
{
	Log(LT_Enter, "CloseDirectX");

	DXRelease(App.lpViewPort, "Viewport");
	DXRelease(App.lpD3DDevice, "Direct3DDevice");
	DXRelease(App.lpZBuffer, "Z Buffer");
	DXRelease(App.lpBackBuffer, "Back Buffer");
	DXRelease(App.lpFrontBuffer, "Primary Buffer");

	if (!(App.Flags & WA_SOFTWARE))
	{
		DXRelease(App.lpDD, "DirectDraw");
		DXRelease(App.lpD3D, "Direct3D");
	}
}

bool DXCreate(int width, int height, int depth, int flags, WINAPP* app, HWND window, DWORD dwStyle)
{
	Log(LT_Enter, "DXCreate");

	app->Flags = flags;
	app->GhWnd = window;
	app->DXWndStyle = dwStyle;

	CloseDirectX();

	if (!(flags & WA_SOFTWARE))
	{
		if (!DXDDCreate(CUR_DD.lpGuid, (LPDIRECTDRAW*)&App.lpDD))
		{
			CloseDirectX();
			return 0;
		}
		if (!DXCreateDirect3D(App.lpDD, &App.lpD3D))
		{
			CloseDirectX();
			return 0;
		}
	}

	int dwFlags;

	if (flags & WA_FULLSCREEN)
		dwFlags = DDSCL_FULLSCREEN | DDSCL_ALLOWREBOOT | DDSCL_EXCLUSIVE;
	else
		dwFlags = DDSCL_NORMAL;

	if (flags & WA_FPUSETUP)
		dwFlags |= DDSCL_FPUSETUP;

	app->DXCoopLevel = dwFlags;

	if (!DXSetCooperativeLevel(App.lpDD, window, dwFlags))
	{
		CloseDirectX();
		return 0;
	}

	if (flags & WA_FULLSCREEN)
	{
		DXSetVideoMode(
			App.lpDD,
			CUR_DM.w,
			CUR_DM.h,
			CUR_DM.bpp);
	}
	else
	{
		HWND desktop = GetDesktopWindow();
		DEVMODE mode;
		Zero(mode);
		mode.dmSize = 148;
		HDC hDC = GetDC(desktop);
		mode.dmBitsPerPel = CUR_DM.bpp;
		ReleaseDC(desktop, hDC);
		mode.dmFields = DM_BITSPERPEL;
		ChangeDisplaySettings(&mode, 0);
	}

	DDSURFACEDESC2 surf;
	DXInit(surf);

	if (flags & WA_FULLSCREEN)
	{
		surf.dwBackBufferCount = 0;
		surf.dwFlags = DDSD_CAPS;
		surf.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | DDSCAPS_3DDEVICE | DDSCAPS_VIDEOMEMORY;

		if (flags & WA_BACK_BUFFER)
		{
			surf.dwBackBufferCount = 1;
			surf.dwFlags |= DDSD_BACKBUFFERCOUNT;
			surf.ddsCaps.dwCaps |= DDSCAPS_COMPLEX | DDSCAPS_FLIP;
		}

		Log(LT_DXShit, "Create Primary Surface");

		if (!DXCreateSurface(App.lpDD, &surf, &App.lpFrontBuffer))
		{
			CloseDirectX();
			return 0;
		}

		if (flags & WA_BACK_BUFFER)
		{
			Log(LT_DXShit, "Get Attached Back Buffer");

			surf.ddsCaps.dwCaps = DDSCAPS_BACKBUFFER;

			App.lpFrontBuffer->GetAttachedSurface(&surf.ddsCaps, &App.lpBackBuffer);
		}
		else
		{
			App.lpBackBuffer = App.lpFrontBuffer;
		}

		App.width = CUR_DM.w;
		App.height = CUR_DM.h;
		App.r1.top = 0;
		App.r1.left = 0;
		App.r1.right = CUR_DM.w;
		App.r1.bottom = CUR_DM.h;
	}
	else
	{
		Log(LT_Info, "DXCreate: Windowed Mode");

		tagRECT rect;
		rect.top = 0;
		rect.left = 0;
		rect.right = CUR_DM.w;
		rect.bottom = CUR_DM.h;

		AdjustWindowRect(&rect, dwStyle, false);
		SetWindowPos(window, HWND_TOP, 0, 0, rect.right - rect.left, rect.bottom - rect.top, SWP_NOMOVE | SWP_NOZORDER);

		GetClientRect(window, &App.r1);
		GetClientRect(window, &App.GnWindowRect);

		ClientToScreen(window, (LPPOINT)&App.GnWindowRect.left);
		ClientToScreen(window, (LPPOINT)&App.GnWindowRect.right);

		App.width = App.r1.right;
		App.height = App.r1.bottom;

		Log(LT_Info, "w %d h %d", App.width, App.height);

		surf.dwFlags = DDSD_CAPS;
		surf.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;

		if (!DXCreateSurface(App.lpDD, &surf, &App.lpFrontBuffer))
		{
			CloseDirectX();
			return 0;
		}

		LPDIRECTDRAWCLIPPER clipper;
		if (DX_TRY(App.lpDD->CreateClipper(0, &clipper, nullptr)))
		{
			CloseDirectX();
			return 0;
		}

		DX_TRY(clipper->SetHWnd(0, window));
		DX_TRY(App.lpFrontBuffer->SetClipper(clipper));

		DXRelease(clipper, "Clipper");

		surf.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
		surf.dwWidth = App.width;
		surf.dwHeight = App.height;
		surf.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_3DDEVICE;

		if (DX_TRY(App.lpDD->CreateSurface(&surf, &App.lpBackBuffer, nullptr)))
		{
			CloseDirectX();
			return 0;
		}
	}

	if (flags & 0x10 && flags & 0x80)
	{
		Log(LT_DXShit, "Creating ZBuffer");

		Zero(surf);

		surf.dwSize = 124;
		surf.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT;
		surf.ddsCaps.dwCaps = DDSCAPS_VIDEOMEMORY | DDSCAPS_ZBUFFER;
		surf.dwWidth = App.width;
		surf.dwHeight = App.height;

		memcpy(&surf.ddpfPixelFormat, &CUR_D3D.Zbuffer->ddpf, sizeof(DDPIXELFORMAT));

		if (DX_TRY(App.lpDD->CreateSurface(&surf, &App.lpZBuffer, nullptr)))
		{
			CloseDirectX();
			return 0;
		}

		DX_TRY(App.lpBackBuffer->AddAttachedSurface(App.lpZBuffer));

		Log(LT_DXShit, "ZBuffer Created %x", App.lpZBuffer);
	}

	if (DXCreateDirect3DDevice(App.lpD3D, CUR_D3D.Guid, App.lpBackBuffer, &App.lpD3DDevice))
	{
		App.lpD3DDevice_BIS = App.lpD3DDevice;

		if (DXCreateViewport(App.lpD3D, App.lpD3DDevice, App.width, App.height, &App.lpViewPort))
		{
			DX_TRY(App.lpD3DDevice->SetRenderTarget(App.lpBackBuffer, 0));

			if (!(App.Flags & 0x80))
			{
				// todo
			}

			return true;
		}
	}

	CloseDirectX();
	return false;
}

HRESULT LoadPicture(LPDIRECTDRAWSURFACE4 surf, HGDIOBJ h, int xSrc, int ySrc, int wSrc, int hSrc)
{
	if (!h)
		return 0x80004005;

	if (!surf)
		return 0x80004005;

	surf->Restore();

	HDC dc = CreateCompatibleDC(nullptr);
	if (!dc)
		OutputDebugStringA("createcompatible dc failed");

	SelectObject(dc, h);

	BITMAP bmp;
	GetObjectA(h, sizeof(BITMAP), &bmp);

	DDSURFACEDESC2 desc; // todo maybe surf desc (not 2)
	DXInit(desc);
	desc.dwFlags = DDSD_WIDTH | DDSD_HEIGHT;

	surf->GetSurfaceDesc(&desc);

	int x = 0;
	int y = 0;

	if (App.Flags & WA_BACK_BUFFER)
	{
		surf = App.lpFrontBuffer;

		if (App.Flags & WA_UNKNOWN1)
		{
			x = App.GnWindowRect.left;
			y = App.GnWindowRect.top;
		}
	}

	HDC dest;
	HRESULT res = surf->GetDC(&dest);

	if (res == NO_ERROR)
	{
		StretchBlt(dest, x, y, desc.dwWidth, desc.dwHeight, dc, xSrc, ySrc, wSrc, hSrc, SRCCOPY);
		surf->ReleaseDC(dest);
	}

	DeleteDC(dc);

	return res;
}

HRESULT DDCopyBitmap(LPDIRECTDRAWSURFACE4 surface, char* filename)
{
	HMODULE mod = GetModuleHandleA(nullptr);
	HANDLE image = LoadImageA(mod, filename, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);

	if (!image)
		image = LoadImageA(mod, filename, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);

	if (!image)
	{
		Log(LT_Error, "handle is null");

		return 0x80004005;
	}

	HRESULT res = LoadPicture(surface, image, 0, 0, 0, 0);

	if (res)
		Log(LT_Error, "ddcopybitmap failed");

	DeleteObject(image);

	return res;
}

BOOL PASCAL DXEnumDirectInput(LPCDIDEVICEINSTANCE lpddi, LPVOID pvRef)
{
	return FAILED(App.lpDI->CreateDeviceEx(lpddi->guidInstance, IID_IDirectInputDevice2A, (LPVOID*)&App.lpDIJoystick, nullptr));
}

BOOL PASCAL DXEnumDirectInputObjects(LPCDIDEVICEOBJECTINSTANCEA lpddoi, LPVOID pvRef)
{
	DIPROPRANGE prop;
	DXInit(prop.diph);

	prop.diph.dwHeaderSize = 16;
	prop.diph.dwHow = 1;
	prop.diph.dwObj = lpddoi->dwOfs;

	prop.lMin = -1000;
	prop.lMax = 1000;

	return SUCCEEDED(App.lpDIJoystick->SetProperty(DIPROP_RANGE, &prop.diph));
}

void DXCreateDirectInput(HWND hWnd, HINSTANCE hInstance)
{
	LPDIRECTINPUTA di;
	DX_TRY(DirectInputCreateA(hInstance, 0x700, &di, nullptr));
	di->QueryInterface(IID_IDirectInput2A, (LPVOID*)&App.lpDI);
	DXRelease(di, "DirectInput");

	LPDIRECTINPUTDEVICEA keyb;
	DX_TRY(App.lpDI->CreateDevice(GUID_SysKeyboard, &keyb, nullptr));
	keyb->QueryInterface(IID_IDirectInputDevice2A, (LPVOID*)&App.lpDIKeyboard);
	DXRelease(keyb, "Keyboard");

	DX_TRY(App.lpDIKeyboard->SetCooperativeLevel(hWnd, DDSCL_ALLOWREBOOT | DDSCL_NORMAL));
	DX_TRY(App.lpDIKeyboard->SetDataFormat(&c_dfDIKeyboard));
	DX_TRY(App.lpDIKeyboard->Acquire());

	DX_TRY(App.lpDI->EnumDevices(DIDEVTYPE_JOYSTICK, DXEnumDirectInput, nullptr, DIEDFL_ATTACHEDONLY));

	if (App.lpDIJoystick)
	{
		DX_TRY(App.lpDIJoystick->SetDataFormat(&c_dfDIJoystick));
		DX_TRY(App.lpDIJoystick->SetCooperativeLevel(hWnd, DDSCL_FULLSCREEN | DDSCL_NOWINDOWCHANGES));

		DIDEVCAPS caps;
		App.lpDIJoystick->GetCapabilities(&caps);
		App.lpDIJoystick->EnumObjects(DXEnumDirectInputObjects, hWnd, DIDFT_AXIS);
		DX_TRY(App.lpDIJoystick->Acquire());
	}
}

void DXMove(int x, int y)
{
	Log(LT_Enter, "DXMove : x %d y %d", x, y);

	if (!(App.Flags & WA_FULLSCREEN))
	{
		SetRect(&App.GnWindowRect, x, y, x + App.width, y + App.height);
	}
}

void AcquireInput(bool acquire)
{
	if (App.lpDIJoystick)
	{
		if (acquire)
		{
			App.lpDIJoystick->Acquire();
		}
		else
		{
			App.lpDIJoystick->Unacquire();
		}
	}
}

void SaveDDBuffer(LPDIRECTDRAWSURFACE4 surf, const char* prefix)
{
	static int nFile = 0;
	static char header[18] = { 0,0,2,0,0,0,0,0,0,0,0,0,0x40,0x01,0x00,0x01,16,0 };
	char filename[16];

	DDSURFACEDESC2 ddsd;
	DXInit(ddsd);

	if (DX_TRY(surf->GetSurfaceDesc(&ddsd)))
		return;

	DX_TRY(surf->Lock(nullptr, &ddsd, DDLOCK_WAIT, nullptr));

	short* p = (short*)ddsd.lpSurface;

	sprintf(filename, "%s%04d.tga", prefix, nFile++);
	FILE* handle = fopen(filename, "wb");

	if (handle)
	{
		short* p1 = (short*)&header[12];

		*p1++ = short(ddsd.dwWidth);
		*p1 = short(ddsd.dwHeight);

		fwrite(header, 18, 1, handle);

		short* pd = (short*)malloc_ptr;

		p += ddsd.lPitch / 2 * ddsd.dwHeight;

		for (int i = 0; i < ddsd.dwHeight; i++)
		{
			for (int j = 0; j < ddsd.dwWidth; j++)
			{
				int k = p[j];

				if (ddsd.ddpfPixelFormat.dwRBitMask == 0xF800)
				{
					int r = (k >> 11) & 0x1F;
					int g = (k >> 6) & 0x1F;
					int b = k & 0x1F;

					*pd++ = (r << 10) + (g << 5) + b;
				}
				else
				{
					*pd++ = k;
				}
			}

			p -= ddsd.lPitch / 2;
		}

		fwrite(malloc_ptr, 2 * ddsd.dwWidth * ddsd.dwHeight, 1, handle);
		fclose(handle);

		filename[7]++;

		if (filename[7] > '9')
		{
			filename[7] = '0';
			filename[6]++;
		}
	}

	DX_TRY(surf->Unlock(nullptr));
}

void DXShowFrame()
{
	if (false)
		SaveDDBuffer(App.lpBackBuffer, "Tomb");

	if (App.lpFrontBuffer->IsLost())
	{
		Log(LT_DXShit, "Restored Primary Buffer");
		DX_TRY(App.lpFrontBuffer->Restore());
	}

	if (App.lpBackBuffer->IsLost())
	{
		Log(LT_DXShit, "Restored Back Buffer");
		DX_TRY(App.lpBackBuffer->Restore());
	}

	if (App.Flags & WA_UNKNOWN1)
	{
		DX_TRY(App.lpFrontBuffer->Blt(&App.GnWindowRect, App.lpBackBuffer, &App.r1, DDBLT_WAIT, nullptr));
	}
	else if (App.Flags & WA_BACK_BUFFER)
	{
		DX_TRY(App.lpFrontBuffer->Flip(nullptr, true));
	}
}