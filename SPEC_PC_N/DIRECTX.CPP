#include <ddraw.h>
#include "DIRECTX.H"

static LPDIRECTDRAW4		lpDD2;
static LPDIRECT3D3			lpD3D2;
static LPDIRECTDRAWSURFACE4 lpDDSurface;
static LPDIRECT3DDEVICE3	lpD3DDevice;
static HWND					WindowHandle;
static bool bSoftRend = false;

/*
Function :	DXBitMask2ShiftCnt
Useage   :	Convert Bitmask to Shifts and Bit cnt

*/

void DXBitMask2ShiftCnt(unsigned long mask, unsigned char* shift, unsigned char* cnt)
{
	unsigned long m;
	unsigned char n;
	for (n = 0, m = mask; !(m & 1); n++, m >>= 1);
	*shift = n;
	for (n = 0; m & 1; n++, m >>= 1);
	*cnt = n;
}

bool DXSetCooperativeLevel(LPDIRECTDRAW4 lpDD2, HWND WindowHandle, int Flags)
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
	RetVal = lpDD2->SetCooperativeLevel(WindowHandle, Flags);
	if (RetVal != DD_OK) return false;
	return true;
}

BOOL DXDDCreate(GUID FAR* lpGuid, LPDIRECTDRAW* lpDD)
{
	LPDIRECTDRAW lpDDTemp;

	Log(LT_Enter, "DXDDCreate");

	if (DX_TRY(DirectDrawCreate(lpGuid, &lpDDTemp, NULL)))
	{
		Log(LT_Error, "DXDDCreate Failed");
		return FALSE;
	}

	DX_TRY(lpDDTemp->QueryInterface(IID_IDirectDraw4, (LPVOID*)&lpDD2));

	DXRelease(lpDDTemp, "DirectDraw");

	Log(LT_Info, "DXDDCreate Successful");

	return TRUE;
}

HRESULT CALLBACK DXEnumDisplayModes(LPDDSURFACEDESC2 lpddsd, LPVOID lpContext)
{
	DIRECTDRAWINFO* DDInfo;
	DDInfo = (DIRECTDRAWINFO*)lpContext;

	// Allocate DisplayMode Structure 
	if (DDInfo->nDisplayMode == 0)
		DDInfo->DisplayMode = (DISPLAYMODE*)malloc(sizeof(DISPLAYMODE));
	else
		DDInfo->DisplayMode = (DISPLAYMODE*)realloc(DDInfo->DisplayMode, sizeof(DISPLAYMODE)*(DDInfo->nDisplayMode + 1));

	// Clear Structure 
	memset(&DDInfo->DisplayMode[DDInfo->nDisplayMode], 0, sizeof(DISPLAYMODE));

	// Store Details Of Display Mode
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
		// Get RGBA Bit Counts and Shifts

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

	// Increase Number Of Display Modes
	DDInfo->nDisplayMode++;

	return DDENUMRET_OK;
}

/*
Function	:	DXCreateDirect3D
Useage		:	Create A Direct3D2 Interface
*/

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

/*
Function	:	BPPToDDBD
Useage		:	Convert bpp to DDBD
*/

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

/*
Function	: DXCreateSurface
Useage		: Create DirectDraw Surface
*/

bool DXCreateSurface(LPDIRECTDRAW4 lpDD2, DDSURFACEDESC2* ddsd, LPDIRECTDRAWSURFACE4* lpSurface)
{
	Log(LT_Enter, "DXCreateSurface");
	int RetVal;
	LPDIRECTDRAWSURFACE4 lps;
	RetVal = lpDD2->CreateSurface(ddsd, &lps, NULL);
	if (DX_TRY(RetVal))
	{
		Log(LT_Error, "DXCreateSurface Failed");
		return false;
	}
	return true;
}

/*
Function	:	DXCreateDirect3DDevice
Useage		:	Create A Direct3D Device
*/

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

/*
Function	:	DXSetVideoMode
Useage		:	Set Video Mode
*/

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

	// Is it Palettised

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

HRESULT CALLBACK DXEnumDirect3D(LPGUID lpGuid, LPSTR lpDeviceDesc, LPSTR lpDeviceName, LPD3DDEVICEDESC lpHWDesc, LPD3DDEVICEDESC lpHELDesc, LPVOID lpContext)
{
	int n;

	DIRECTDRAWINFO* DDInfo;
	DDInfo = (DIRECTDRAWINFO*)lpContext;

	if (lpHWDesc->dwFlags == 0)
	{
		// Discard 8 Bit Drivers
		if (lpHELDesc->dcmColorModel&D3DCOLOR_MONO) return D3DENUMRET_OK;
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

	// Store Details Of Driver Information
	if (lpGuid == NULL)
		DDInfo->D3DInfo[DDInfo->nD3DInfo].lpGuid = NULL;
	else
	{
		DDInfo->D3DInfo[DDInfo->nD3DInfo].lpGuid = &DDInfo->D3DInfo[DDInfo->nD3DInfo].Guid;
		memcpy(&DDInfo->D3DInfo[DDInfo->nD3DInfo].Guid, lpGuid, sizeof(GUID));
	}

	lstrcpy(DDInfo->D3DInfo[DDInfo->nD3DInfo].About, lpDeviceDesc);
	lstrcpy(DDInfo->D3DInfo[DDInfo->nD3DInfo].Name, lpDeviceName);

	// Store Device Descriptions
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
			// ToDo: Make a setup specifier
			//		 Only Want 16 Bit Video Modes

			if (DDInfo->DisplayMode[n].bpp == 16)
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
	}

	Log(LT_Info, "Enumerate Texture Formats");

	// Setup A D3DDEVICE For Texture Format Enumeration
	// First Try Using the Primary Surface

	DDSURFACEDESC2 ddsd;
	DXInit(ddsd);
	ddsd.dwFlags = DDSD_CAPS;
	ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | DDSCAPS_3DDEVICE;

	lpDDSurface = NULL;

	DXSetCooperativeLevel(lpDD2, WindowHandle, DDSCL_FULLSCREEN | DDSCL_EXCLUSIVE | DDSCL_NOWINDOWCHANGES);
	DXCreateSurface(lpDD2, &ddsd, &lpDDSurface);
	
	if (lpDDSurface)
	{
		lpD3DDevice = NULL;
		DXCreateDirect3DDevice(lpD3D2, DDInfo->D3DInfo[DDInfo->nD3DInfo].Guid, lpDDSurface, &lpD3DDevice);

		if (lpD3DDevice == NULL)
		{
			DXRelease(lpDDSurface, "DirectDrawSurface");

			DXSetVideoMode(
				lpDD2,
				DDInfo->D3DInfo[DDInfo->nD3DInfo].DisplayMode->w,
				DDInfo->D3DInfo[DDInfo->nD3DInfo].DisplayMode->h,
				DDInfo->D3DInfo[DDInfo->nD3DInfo].DisplayMode->bpp);

			DXCreateSurface(lpDD2, &ddsd, &lpDDSurface);

			if (lpDDSurface)
			{
				DXCreateDirect3DDevice(lpD3D2, DDInfo->D3DInfo[DDInfo->nD3DInfo].Guid, lpDDSurface, &lpD3DDevice);
			}
		}

		if (lpD3DDevice)
		{
			// Enumerate Texture Formats For This D3DDevice
			DDInfo->D3DInfo[DDInfo->nD3DInfo].nTexture = 0;

			lpD3DDevice->EnumTextureFormats(DXEnumTextureFormats, (LPVOID)&DDInfo->D3DInfo[DDInfo->nD3DInfo]);

			DXRelease(lpD3DDevice, "D3DDevice");
			DXRelease(lpDDSurface, "DirectDrawSurface");
		}
	}

	DXSetCooperativeLevel(lpDD2, WindowHandle, DDSCL_NORMAL);

	Log(LT_Info, "Enumerating ZBuffer Formats");
	Log(LT_Enter, "DXEnumZBufferFormats");

	DX_TRY(lpD3D2->EnumZBufferFormats(
		DDInfo->D3DInfo[DDInfo->nD3DInfo].Guid,
		DXEnumZBufferFormats,
		&DDInfo->D3DInfo[DDInfo->nD3DInfo]));

	// Increase Number Of Devices

	DDInfo->nD3DInfo++;

	return D3DENUMRET_OK;
}

BOOL CALLBACK DXEnumDirectDraw(GUID FAR* lpGuid, LPSTR lpDeviceDesc, LPSTR lpDeviceName, LPVOID lpContext)
{
	Log(LT_Enter, "DXEnumDirectDraw");

	DEVICEINFO*		 dd;

	dd = (DEVICEINFO*)lpContext;

	// Allocate Device Structure
	if (dd->nDDInfo == 0)
		dd->DDInfo = (DIRECTDRAWINFO*)malloc(sizeof(DIRECTDRAWINFO));
	else
		dd->DDInfo = (DIRECTDRAWINFO*)realloc(dd->DDInfo, sizeof(DIRECTDRAWINFO)*(dd->nDDInfo + 1));

	// Clear Structure
	memset(&dd->DDInfo[dd->nDDInfo], 0, sizeof(DIRECTDRAWINFO));

	// Store DirectDraw Info	
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

	if (DXDDCreate(lpGuid, (LPDIRECTDRAW*)&lpDD2))
	{
		DX_TRY(lpDD2->GetDeviceIdentifier(&dd->DDInfo[dd->nDDInfo].DDDevIdent, NULL));
		Log(LT_Info, "Found - %s\nDriver %s Version %d.%d.%d.%d",
			dd->DDInfo[dd->nDDInfo].DDDevIdent.szDescription,
			dd->DDInfo[dd->nDDInfo].DDDevIdent.szDriver,
			HIWORD(dd->DDInfo[dd->nDDInfo].DDDevIdent.liDriverVersion.HighPart),
			LOWORD(dd->DDInfo[dd->nDDInfo].DDDevIdent.liDriverVersion.HighPart),
			HIWORD(dd->DDInfo[dd->nDDInfo].DDDevIdent.liDriverVersion.LowPart),
			LOWORD(dd->DDInfo[dd->nDDInfo].DDDevIdent.liDriverVersion.LowPart));

		DXInit(dd->DDInfo[dd->nDDInfo].DDCaps);

		Log(LT_Info, "Getting Device Capabilities");

		DX_TRY(lpDD2->GetCaps(&dd->DDInfo[dd->nDDInfo].DDCaps, NULL));

		Log(LT_Info, "Enumerating Display Modes");

		DXSetCooperativeLevel(lpDD2, NULL, DDSCL_NOWINDOWCHANGES | DDSCL_ALLOWMODEX | DDSCL_FULLSCREEN | DDSCL_NORMAL);

		DX_TRY(lpDD2->EnumDisplayModes(0, NULL, (LPVOID)&dd->DDInfo[dd->nDDInfo], DXEnumDisplayModes));

		if (DXCreateDirect3D(lpDD2, &lpD3D2))
		{
			Log(LT_Enter, "DXEnumDirect3D");
			DX_TRY(lpD3D2->EnumDevices(DXEnumDirect3D, (LPVOID)&dd->DDInfo[dd->nDDInfo]));
			DXRelease(lpD3D2, "Direct3D");
		}

		DXSetCooperativeLevel(lpDD2, NULL, DDSCL_NORMAL);

		DXRelease(lpDD2, "DirectDraw");
	}

	// Increase Number Of Devices
	dd->nDDInfo++;

	return DDENUMRET_OK;
}

void DXInitialise(DEVICEINFO* dd, HWND hWnd)
{
	WindowHandle = hWnd;
	Log(LT_Enter, "DXInitialise");
	Log(LT_Info, "Enumerating DirectDraw Devices");
	DX_TRY(DirectDrawEnumerate(DXEnumDirectDraw, dd));
	DX_TRY(DirectSoundEnumerate(DXEnumDirectSound, dd));
}