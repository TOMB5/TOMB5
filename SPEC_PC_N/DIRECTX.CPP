#include <ddraw.h>
#include "DIRECTX.H"
#include "GLOBAL.H"
#include <dinput.h>
#include "SOUND.H"
#include "SETUP.H"
#include <mmreg.h>
#include <msacm.h>
#include "INPUT.H"
#pragma comment (lib, "ddraw.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "dinput.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "Msacm32.lib")

static LPDIRECTDRAW4		enum_lpDD;
static LPDIRECT3D3			enum_lpD3D;
static LPDIRECTDRAWSURFACE4 enum_lpDDSurface;
static LPDIRECT3DDEVICE3	enum_lpD3DDevice;
static HWND					WindowHandle;
static bool bSoftRend = false;
static LPDIRECTSOUNDBUFFER DSSoundBuffer;
static LPDIRECTSOUNDBUFFER ACMSoundBuffer;
static LPDIRECTSOUNDNOTIFY DSNotify;

int NumSamplesTable[3] =
{
	11025, 22050, 44100
};
int NumSamples;
bool ACMInited;
HACMDRIVERID acm_driver_id;
HACMDRIVER acm_driver;
ACMSTREAMHEADER acm_header_1;
ACMSTREAMHEADER acm_header_2;
ACMSTREAMHEADER acm_header_3;
ACMSTREAMHEADER acm_header_4;

void* wave_file_buf;
BYTE* source_buffer;

HACMSTREAM acm_stream;
int acm_lock_length;
DWORD acm_max_length;
LPBYTE acm_audio_ptr;
DWORD acm_audio_bytes;

int joystick_read_x;
int joystick_read_y;
int joystick_read_fire;
bool joystick_read;

const char* xa_filenames[] =
{
	"xa1_TL_10B.wav", "xa1_Z10.wav", "xa1_TL_05.wav", "xa1_TL_08.wav", "xa1_TL_11.wav", 
	"xa1_ANDYPEW.wav", "xa1_SECRET.wav", "xa1_TL_02.wav", "xa2_HMMM05.wav", "xa2_TL_01.wav", 
	"xa2_ATTACK04.wav", "xa2_UWATER2B.wav", "xa2_SPOOKY2A.wav", "xa2_TL_10A.wav", "xa2_HMMM02.wav", 
	"xa2_TOMS01.wav", "xa3_Attack03.wav", "xa3_Attack02.wav", "xa3_Hmmm01.wav", "xa3_Stealth1.wav", 
	"xa3_Stealth2.wav", "xa3_Attack01.wav", "xa3_TL_06.wav", "xa3_TL_03.wav", "xa4_hmmm06.wav", 
	"xa4_mil01.wav", "xa4_Z_03.wav", "xa4_hit01.wav", "xa4_spooky05.wav", "xa4_drama01.wav", 
	"xa4_stealth4.wav", "xa4_mil05.wav", "xa5_HMMM04.wav", "xa5_MIL06.wav", "xa5_SPOOKY02.wav", 
	"xa5_TL_12.wav", "xa5_MIL02A.wav", "xa5_HMMM03.wav", "xa5_MIL02.wav", "xa5_TL_04.wav", 
	"xa6_Mil04.wav", "xa6_Solo01.wav", "xa6_Z12.wav", "xa6_Stealth3.wav", "xa6_AuthSolo.wav", 
	"xa6_Spooky03.wav", "xa6_Z13.wav", "xa6_Z_04anim.wav", "xa7_z_06a.wav", "xa7_andyoooh.wav", 
	"xa7_andyooer.wav", "xa7_tl_07.wav", "xa7_z_02.wav", "xa7_evibes01.wav", "xa7_z_06.wav", 
	"xa7_authtr.wav", "xa8_mil03.wav", "xa8_fightsc.wav", "xa8_richcut3.wav", "xa8_z_13.wav", 
	"xa8_z_08.wav", "xa8_uwater2a.wav", "xa8_jobyalrm.wav", "xa8_mil02b.wav", "xa9_swampy.wav", 
	"xa9_evibes02.wav", "xa9_gods01.wav", "xa9_z_03.wav", "xa9_richcut4.wav", "xa9_title4.wav", 
	"xa9_spooky01.wav", "xa9_chopin01.wav", "xa10_echoir01.wav", "xa10_title3.wav",
	"xa10_perc01.wav", "xa10_vc01.wav", "xa10_title2.wav", "xa10_z_09.wav", "xa10_spooky04.wav", 
	"xa10_z_10.wav", "xa11_vc01atv.wav", "xa11_andy3.wav", "xa11_title1.wav", "xa11_flyby1.wav", 
	"xa11_monk_2.wav", "xa11_andy4.wav", "xa11_flyby3.wav", "xa11_flyby2.wav", "xa12_moses01.wav", 
	"xa12_andy4b.wav", "xa12_z_10.wav", "xa12_flyby4.wav", "xa12_richcut1.wav", "xa12_andy5.wav",
	"xa12_z_05.wav", "xa12_z_01.wav", "xa13_Joby3.wav", "xa13_Andy7.wav", "xa13_Andrea3B.wav", 
	"xa13_cossack.wav", "xa13_Z_07.wav", "xa13_Andy6.wav", "xa13_Andrea3.wav", "xa13_Joby7.wav", 
	"xa14_uwater1.wav", "xa14_joby1.wav", "xa14_andy10.wav", "xa14_richcut2.wav", 
	"xa14_andrea1.wav", "xa14_andy8.wav", "xa14_joby6.wav", "xa14_ecredits.wav", 
	"xa15_boss_01.wav", "xa15_joby2.wav", "xa15_joby4.wav", "xa15_joby5.wav", "xa15_joby9.wav", 
	"xa15_a_andy.wav", "xa15_a_rome.wav", "xa15_andy2.wav", "xa16_Joby8.wav", "xa16_A_Sub_Amb.wav", 
	"xa16_Joby10.wav", "xa16_A_Harbour_out.wav", "xa16_A_Andy_Out_Norm.wav", 
	"xa16_A_Andy_Out_Spooky.wav", "xa16_A_Rome_Day.wav", "xa16_A_Underwater.wav",
	"xa17_A_Rome_Night.wav", "xa17_A_VC_Saga.wav", "xa17_A_Industry.wav", "xa17_Andrea2.wav", 
	"xa17_Andy1.wav", "xa17_Andrea4.wav", "xa17_Andy9.wav", "xa17_Andy11.wav"
};

void DXBitMask2ShiftCnt(unsigned long mask, unsigned char* shift, unsigned char* cnt)// (F)
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
	bool DXSetCooperativeLevel(LPDIRECTDRAW4 lpDD, HWND WindowHandle, int Flags)// (F)
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

		return lpDD->SetCooperativeLevel(WindowHandle, Flags) == DD_OK;
	}
#ifdef __cplusplus
}
#endif
BOOL DXDDCreate(GUID FAR* lpGuid, LPDIRECTDRAW* lpDD)// (F)
{
	LPDIRECTDRAW lpDDTemp;

	Log(LT_Enter, "DXDDCreate");

	if (DX_TRY(DirectDrawCreate(lpGuid, &lpDDTemp, nullptr)))
	{
		Log(LT_Error, "DXDDCreate Failed");
		return FALSE;
	}

	DX_TRY(lpDDTemp->QueryInterface(IID_IDirectDraw4, (LPVOID*)lpDD));

	DXRelease(lpDDTemp, "DirectDraw");

	Log(LT_Info, "DXDDCreate Successful");

	return TRUE;
}

HRESULT CALLBACK DXEnumDisplayModes(LPDDSURFACEDESC2 lpddsd, LPVOID lpContext)// (F)
{
	DIRECTDRAWINFO* DDInfo;
	DDInfo = (DIRECTDRAWINFO*)lpContext;

	if (DDInfo->nDisplayMode == 0)
		DDInfo->DisplayMode = (DISPLAYMODE*)malloc(sizeof(DISPLAYMODE));
	else
		DDInfo->DisplayMode = (DISPLAYMODE*)realloc(DDInfo->DisplayMode, sizeof(DISPLAYMODE)*(DDInfo->nDisplayMode + 1));

	Zero(DDInfo->DisplayMode[DDInfo->nDisplayMode]);

	DDInfo->DisplayMode[DDInfo->nDisplayMode].w = lpddsd->dwWidth;
	DDInfo->DisplayMode[DDInfo->nDisplayMode].h = lpddsd->dwHeight;
	DDInfo->DisplayMode[DDInfo->nDisplayMode].bpp = lpddsd->ddpfPixelFormat.dwRGBBitCount;
	DDInfo->DisplayMode[DDInfo->nDisplayMode].bPalette = lpddsd->ddpfPixelFormat.dwFlags&DDPF_PALETTEINDEXED8 ? true : false;
	DDInfo->DisplayMode[DDInfo->nDisplayMode].mipMapCount = lpddsd->dwMipMapCount;
	DDInfo->DisplayMode[DDInfo->nDisplayMode].ddsd = *lpddsd;

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

bool DXCreateDirect3D(LPDIRECTDRAW4 lpDD2, LPDIRECT3D3* lpD3D2)// (F)
{
	if (DX_TRY(lpDD2->QueryInterface(IID_IDirect3D3, (LPVOID*)lpD3D2)))
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

DWORD BPPToDDBD(int bpp)// (F)
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
	default:
		return 0;
	}
}

bool DXCreateSurface(LPDIRECTDRAW4 lpDD2, DDSURFACEDESC2* ddsd, LPDIRECTDRAWSURFACE4* lpSurface)// (F)
{
	Log(LT_Enter, "DXCreateSurface");
	if (DX_TRY(lpDD2->CreateSurface(ddsd, lpSurface, nullptr)))
	{
		Log(LT_Error, "DXCreateSurface Failed");
		return false;
	}
	return true;
}

bool DXCreateDirect3DDevice(LPDIRECT3D3 lpD3D2, GUID Guid, LPDIRECTDRAWSURFACE4 lpSurface, LPDIRECT3DDEVICE3* lpD3DDevice2)// (F)
{
	if (DX_TRY(lpD3D2->CreateDevice(Guid, lpSurface, lpD3DDevice2, nullptr)))
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

bool DXCreateViewport(LPDIRECT3D3 lpD3D, LPDIRECT3DDEVICE3 lpD3DDevice, int w, int h, LPDIRECT3DVIEWPORT3* lpViewport)// (F)
{
	D3DVIEWPORT2 viewdata;

	Log(LT_Enter, "DXCreateViewport");

	if (DX_TRY(lpD3D->CreateViewport(lpViewport, nullptr))) return false;

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

bool DXSetVideoMode(LPDIRECTDRAW4 lpDD2, int w, int h, int bpp)// (F)
{
	Log(LT_Enter, "DXSetVideoMode");
	Log(LT_Info, "SetDisplayMode - %dx%dx%d", w, h, bpp);

	return lpDD2->SetDisplayMode(w, h, bpp, 0, NULL) == DD_OK;
}

HRESULT CALLBACK DXEnumTextureFormats(LPDDPIXELFORMAT lpddpf, LPVOID lpContext)// (F)
{
	DIRECT3DINFO* D3DInfo = (DIRECT3DINFO*)lpContext;

	if (D3DInfo->nTexture == 0)
		D3DInfo->Texture = (D3DTEXTUREINFO*)malloc(sizeof(D3DTEXTUREINFO));
	else
		D3DInfo->Texture = (D3DTEXTUREINFO*)realloc(D3DInfo->Texture, sizeof(D3DTEXTUREINFO)*(D3DInfo->nTexture + 1));

	Zero(D3DInfo->Texture[D3DInfo->nTexture]);
	D3DInfo->Texture[D3DInfo->nTexture].ddpf = *lpddpf;

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

HRESULT CALLBACK DXEnumZBufferFormats(LPDDPIXELFORMAT lpddpf, LPVOID lpContext)// (F)
{
	DIRECT3DINFO* D3DInfo = (DIRECT3DINFO*)lpContext;

	if (D3DInfo->nZbuffer== 0)
		D3DInfo->Zbuffer = (zBufFormat*)malloc(sizeof(zBufFormat));
	else
		D3DInfo->Zbuffer = (zBufFormat*)realloc(D3DInfo->Zbuffer, sizeof(zBufFormat)*(D3DInfo->nZbuffer + 1));

	Zero(D3DInfo->Zbuffer[D3DInfo->nZbuffer]);
	D3DInfo->Zbuffer[D3DInfo->nZbuffer].ddpf = *lpddpf;

	D3DInfo->Zbuffer[D3DInfo->nZbuffer].bpp = lpddpf->dwRGBBitCount;

	Log(LT_Info, "%d Bit", D3DInfo->Zbuffer[D3DInfo->nZbuffer].bpp);

	D3DInfo->nZbuffer++;

	return D3DENUMRET_OK;
}

HRESULT CALLBACK DXEnumDirect3D(LPGUID lpGuid, LPSTR lpDeviceDesc, LPSTR lpDeviceName, LPD3DDEVICEDESC lpHWDesc, LPD3DDEVICEDESC lpHELDesc, LPVOID lpContext)// (F)
{
	DIRECTDRAWINFO* DDInfo = (DIRECTDRAWINFO*)lpContext;

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

	Zero(DDInfo->D3DInfo[DDInfo->nD3DInfo]);

	if (lpGuid == nullptr)
	{
		DDInfo->D3DInfo[DDInfo->nD3DInfo].lpGuid = nullptr;
	}
	else
	{
		DDInfo->D3DInfo[DDInfo->nD3DInfo].lpGuid = &DDInfo->D3DInfo[DDInfo->nD3DInfo].Guid;
		DDInfo->D3DInfo[DDInfo->nD3DInfo].Guid = *lpGuid;
	}

	lstrcpy(DDInfo->D3DInfo[DDInfo->nD3DInfo].About, lpDeviceDesc);
	lstrcpy(DDInfo->D3DInfo[DDInfo->nD3DInfo].Name, lpDeviceName);

	if (lpHWDesc->dwFlags != 0)
	{
		DDInfo->D3DInfo[DDInfo->nD3DInfo].bHardware = true;
		DDInfo->D3DInfo[DDInfo->nD3DInfo].DeviceDesc = *lpHWDesc;
	}
	else
	{
		DDInfo->D3DInfo[DDInfo->nD3DInfo].bHardware = false;
		DDInfo->D3DInfo[DDInfo->nD3DInfo].DeviceDesc = *lpHELDesc;
	}

	Log(LT_Info, "Finding Compatible Display Modes");

	for (int n = 0; n<DDInfo->nDisplayMode; n++)
	{
		if (BPPToDDBD(DDInfo->DisplayMode[n].bpp)&DDInfo->D3DInfo[DDInfo->nD3DInfo].DeviceDesc.dwDeviceRenderBitDepth)
		{
			if (DDInfo->D3DInfo[DDInfo->nD3DInfo].nDisplayMode == 0)
				DDInfo->D3DInfo[DDInfo->nD3DInfo].DisplayMode = (DISPLAYMODE*)malloc(sizeof(DISPLAYMODE));
			else
				DDInfo->D3DInfo[DDInfo->nD3DInfo].DisplayMode = (DISPLAYMODE*)realloc(DDInfo->D3DInfo[DDInfo->nD3DInfo].DisplayMode, sizeof(DISPLAYMODE)*(DDInfo->D3DInfo[DDInfo->nD3DInfo].nDisplayMode + 1));

			DDInfo->D3DInfo[DDInfo->nD3DInfo].DisplayMode[DDInfo->D3DInfo[DDInfo->nD3DInfo].nDisplayMode] = DDInfo->DisplayMode[n];

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

		if (enum_lpD3DDevice == nullptr)
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

BOOL CALLBACK DXEnumDirectDraw(GUID FAR* lpGuid, LPSTR lpDeviceDesc, LPSTR lpDeviceName, LPVOID lpContext)// (F)
{
	Log(LT_Enter, "DXEnumDirectDraw");

	DEVICEINFO*		 dd = (DEVICEINFO*)lpContext;

	if (dd->nDDInfo == 0)
		dd->DDInfo = (DIRECTDRAWINFO*)malloc(sizeof(DIRECTDRAWINFO));
	else
		dd->DDInfo = (DIRECTDRAWINFO*)realloc(dd->DDInfo, sizeof(DIRECTDRAWINFO)*(dd->nDDInfo + 1));

	Zero(dd->DDInfo[dd->nDDInfo]);
	
	if (lpGuid == nullptr)
	{
		dd->DDInfo[dd->nDDInfo].lpGuid = nullptr;
	}
	else
	{
		dd->DDInfo[dd->nDDInfo].lpGuid = &dd->DDInfo[dd->nDDInfo].Guid;
		dd->DDInfo[dd->nDDInfo].Guid = *lpGuid;
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

		DX_TRY(enum_lpDD->GetCaps(&dd->DDInfo[dd->nDDInfo].DDCaps, nullptr));

		Log(LT_Info, "Enumerating Display Modes");

		DXSetCooperativeLevel(enum_lpDD, nullptr, DDSCL_NOWINDOWCHANGES | DDSCL_ALLOWMODEX | DDSCL_FULLSCREEN | DDSCL_NORMAL);

		Log(LT_Enter, "DXEnumDisplayModes");

		DX_TRY(enum_lpDD->EnumDisplayModes(0, nullptr, (LPVOID)&dd->DDInfo[dd->nDDInfo], DXEnumDisplayModes));

		if (DXCreateDirect3D(enum_lpDD, &enum_lpD3D))
		{
			Log(LT_Enter, "DXEnumDirect3D");
			DX_TRY(enum_lpD3D->EnumDevices(DXEnumDirect3D, (LPVOID)&dd->DDInfo[dd->nDDInfo]));
			DXRelease(enum_lpD3D, "Direct3D");
		}

		DXSetCooperativeLevel(enum_lpDD, nullptr, DDSCL_NORMAL);

		DXRelease(enum_lpDD, "DirectDraw");
	}

	dd->nDDInfo++;

	return DDENUMRET_OK;
}

BOOL CALLBACK DXEnumDirectSound(GUID FAR* lpGuid, LPCSTR lpDeviceDesc, LPCSTR lpDeviceName, LPVOID lpContext)// (F)
{
	Log(LT_Enter, "DXEnumDirectSound");

	DEVICEINFO*		 dd = (DEVICEINFO*)lpContext;

	if (dd->nDSInfo == 0)
		dd->DSInfo = (DIRECTSOUNDINFO*)malloc(sizeof(DIRECTSOUNDINFO));
	else
		dd->DSInfo = (DIRECTSOUNDINFO*)realloc(dd->DSInfo, sizeof(DIRECTSOUNDINFO)*(dd->nDSInfo + 1));

	Zero(dd->DSInfo[dd->nDSInfo]);

	if (lpGuid == nullptr)
	{
		dd->DSInfo[dd->nDSInfo].lpGuid = nullptr;
	}
	else
	{
		dd->DSInfo[dd->nDSInfo].lpGuid = &dd->DSInfo[dd->nDSInfo].Guid;
		dd->DSInfo[dd->nDSInfo].Guid = *lpGuid;
	}

	lstrcpy(dd->DSInfo[dd->nDSInfo].About, lpDeviceDesc);
	lstrcpy(dd->DSInfo[dd->nDSInfo].Name, lpDeviceName);

	Log(LT_Info, "Found - %s %s", dd->DSInfo[dd->nDSInfo].About, dd->DSInfo[dd->nDSInfo].Name);

	dd->nDSInfo++;

	return DDENUMRET_OK;
}

void DXInitialise(DEVICEINFO* dd, HWND hWnd)// (F)
{
	Log(LT_Enter, "DXInitialise");
	WindowHandle = hWnd;
	Log(LT_Info, "Enumerating DirectDraw Devices");
	DX_TRY(DirectDrawEnumerate(DXEnumDirectDraw, dd));
	DX_TRY(DirectSoundEnumerate(DXEnumDirectSound, dd));
}

void CloseDirectX()// (F)
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

bool DXCreate(int width, int height, int depth, int flags, WINAPP* app, HWND window, DWORD dwStyle)// back buffer todo
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
			return false;
		}
		if (!DXCreateDirect3D(App.lpDD, &App.lpD3D))
		{
			CloseDirectX();
			return false;
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
		return false;
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
			return false;
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
		App.GnClientRect.top = 0;
		App.GnClientRect.left = 0;
		App.GnClientRect.right = CUR_DM.w;
		App.GnClientRect.bottom = CUR_DM.h;
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

		GetClientRect(window, &App.GnClientRect);
		GetClientRect(window, &App.GnWindowRect);

		ClientToScreen(window, (LPPOINT)&App.GnWindowRect.left);
		ClientToScreen(window, (LPPOINT)&App.GnWindowRect.right);

		App.width = App.GnClientRect.right;
		App.height = App.GnClientRect.bottom;

		Log(LT_Info, "w %d h %d", App.width, App.height);

		surf.dwFlags = DDSD_CAPS;
		surf.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;

		if (!DXCreateSurface(App.lpDD, &surf, &App.lpFrontBuffer))
		{
			CloseDirectX();
			return false;
		}

		LPDIRECTDRAWCLIPPER clipper;
		if (DX_TRY(App.lpDD->CreateClipper(0, &clipper, nullptr)))
		{
			CloseDirectX();
			return false;
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
			return false;
		}
	}

	if (flags & WA_UNKNOWN2 && flags & WA_BACK_BUFFER)
	{
		Log(LT_DXShit, "Creating ZBuffer");

		Zero(surf);

		surf.dwSize = 124;
		surf.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT;
		surf.ddsCaps.dwCaps = DDSCAPS_VIDEOMEMORY | DDSCAPS_ZBUFFER;
		surf.dwWidth = App.width;
		surf.dwHeight = App.height;

		surf.ddpfPixelFormat = CUR_D3D.Zbuffer->ddpf;

		if (DX_TRY(App.lpDD->CreateSurface(&surf, &App.lpZBuffer, nullptr)))
		{
			CloseDirectX();
			return false;
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

			if (!(App.Flags & WA_BACK_BUFFER))
			{
				// todo
			}

			return true;
		}
	}

	CloseDirectX();
	return false;
}

HRESULT LoadPicture(LPDIRECTDRAWSURFACE4 surf, HGDIOBJ h, int xSrc, int ySrc, int wSrc, int hSrc)// (F)
{
	if (!h || !surf)
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

		if (App.Flags & WA_WINDOWED)
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

HRESULT DDCopyBitmap(LPDIRECTDRAWSURFACE4 surface, char* filename)// todo embed in executable
{
	//HMODULE mod = GetModuleHandleA(nullptr); todo
	HMODULE mod = nullptr;
	HANDLE image = LoadImageA(mod, filename, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);

	if (!image)
		image = LoadImageA(mod, filename, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);

	if (!image)
	{
		Log(LT_Error, "handle is null");

		return GetLastError();
	}

	HRESULT res = LoadPicture(surface, image, 0, 0, 640, 480);

	if (res)
		Log(LT_Error, "ddcopybitmap failed");

	DeleteObject(image);

	return res;
}

BOOL PASCAL DXEnumDirectInput(LPCDIDEVICEINSTANCE lpddi, LPVOID pvRef)// (F)
{
	return FAILED(App.lpDI->CreateDeviceEx(lpddi->guidInstance, IID_IDirectInputDevice2A, (LPVOID*)&App.lpDIJoystick, nullptr));
}

BOOL PASCAL DXEnumDirectInputObjects(LPCDIDEVICEOBJECTINSTANCEA lpddoi, LPVOID pvRef)// (F)
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

void DXCreateDirectInput(HWND hWnd, HINSTANCE hInstance)// (F)
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

void DXMove(int x, int y)// (F)
{
	Log(LT_Enter, "DXMove : x %d y %d", x, y);

	if (!(App.Flags & WA_FULLSCREEN))
	{
		SetRect(&App.GnWindowRect, x, y, x + App.width, y + App.height);
	}
}

void AcquireInput(bool acquire)// (F)
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

void SaveDDBuffer(LPDIRECTDRAWSURFACE4 surf, const char* prefix)// (F)
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

void DXShowFrame()// (F)
{
	if (keymap[DIK_APOSTROPHE])
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

	if (App.Flags & WA_WINDOWED)
	{
		DX_TRY(App.lpFrontBuffer->Blt(&App.GnWindowRect, App.lpBackBuffer, &App.GnClientRect, DDBLT_WAIT, nullptr));
	}
	else if (App.Flags & WA_BACK_BUFFER)
	{
		DX_TRY(App.lpFrontBuffer->Flip(nullptr, true));
	}
}

bool DXChangeVideoMode()// (F)
{
	Log(LT_Enter, "DXChangeVideoMode");

	App.Flags |= WA_SOFTWARE;
	App.lpD3D->EvictManagedTextures();

	bool ret = DXCreate(0, 0, 0, App.Flags, &App, App.GhWnd, App.DXWndStyle);
	Log(LT_Enter, "Exited DXChangeVideoMode %d", ret);
	return ret;
}

void DXToggleFullScreen()// (F)
{
	Log(LT_Enter, "DXToggleFullScreen");

	if (App.Flags & WA_WINDOWED)
	{
		Log(LT_Info, "Switching To Full Screen");

		App.Flags ^= WA_WINDOWED;
		App.Flags |= WA_FULLSCREEN;
		App.Flags |= WA_SOFTWARE;
	}
	else
	{
		Log(LT_Info, "Switching To A Window");

		App.Flags ^= WA_FULLSCREEN;
		App.Flags |= WA_WINDOWED;
		App.Flags |= WA_SOFTWARE;
	}

	App.lpD3D->EvictManagedTextures();

	DXCreate(CUR_DM.w, CUR_DM.h, CUR_DM.bpp, App.Flags, &App, App.GhWnd, App.DXWndStyle);
}

void DXDSCreate()// (F)
{
	Log(LT_Enter, "DXDSCreate");
	DX_TRY(DirectSoundCreate(CUR_DS.lpGuid, &App.lpDS, nullptr));
	DX_TRY(App.lpDS->SetCooperativeLevel(App.WindowHandle, DSSCL_EXCLUSIVE));
	DXSetOutputFormat();
	sound_active = true;
}

bool SetSoundOutputFormat(int num_samples, char a2)// (F)
{
	if (!a2 && NumSamples == num_samples)
		return true;

	WAVEFORMATEX wf;
	wf.wFormatTag = WAVE_FORMAT_PCM;
	wf.nChannels = 2;
	wf.nSamplesPerSec = num_samples;
	wf.nAvgBytesPerSec = num_samples * 4;
	wf.nBlockAlign = 4;
	wf.wBitsPerSample = 16;
	wf.cbSize = 0;
	S_SoundStopAllSamples();

	if (DSSoundBuffer == nullptr)
		return true;

	if (DX_TRY(DSSoundBuffer->SetFormat(&wf)))
	{
		Log(LT_Error, "Can't set sound output format to %d", wf.nSamplesPerSec);
		return false;
	}

	return true;
}

bool DXSetOutputFormat()// (F)
{
	Log(LT_Enter, "DXSetOutputFormat");

	DSBUFFERDESC desc;
	DXInit(desc);
	desc.dwFlags = DSBCAPS_PRIMARYBUFFER;
	if (DX_TRY(App.lpDS->CreateSoundBuffer(&desc, &DSSoundBuffer, nullptr)))
	{
		Log(LT_Error, "Can't Get Primary Sound Buffer");
		return false;
	}

	SetSoundOutputFormat(NumSamplesTable[opt_SoundQuality], 0);
	DSSoundBuffer->Play(0, 0, DSBPLAY_LOOPING);
	return true;
}

BOOL CALLBACK ACMEnumCallback(HACMDRIVERID hadid, DWORD_PTR dwInstance, DWORD fdwSupport)// (F)
{
	ACMDRIVERDETAILSA padd;
	Zero(padd);
	padd.cbStruct = sizeof(padd);

	acmDriverDetailsA(hadid, &padd, 0);

	if (strcmp(padd.szShortName, "MS-ADPCM"))
		return true;

	acm_driver_id = hadid;

	return false;
}

void SetupNotifications()
{
	Unimpl();
}

void InitACM()// (F)
{
	DWORD ver = acmGetVersion();

	ACMInited = false;
	Log(LT_Sound, "ACM Version %u.%.02u", ver >> 24, (BYTE)(ver >> 16));
	acmDriverEnum(ACMEnumCallback, 0, 0);

	if (!acm_driver_id)
	{
		Log(LT_Error, "*** Unable To Locate MS-ADPCM Driver ***");
		return;
	}

	if (acmDriverOpen(&acm_driver, acm_driver_id, 0))
	{
		Log(LT_Error, "*** Failed To Open Driver MS-ADPCM Driver ***");
		return;
	}

	source_buffer = (BYTE*)malloc(22528);
	wave_file_buf = malloc(22528 * 10);

	auto wfSrc = (ADPCMWAVEFORMAT*)malloc(sizeof(WAVEFORMATEX) + 32);	
	wfSrc->wfx.wFormatTag = WAVE_FORMAT_ADPCM;
	wfSrc->wfx.nChannels = 2;
	wfSrc->wfx.nSamplesPerSec = 44100;
	wfSrc->wfx.nAvgBytesPerSec = 44359;
	wfSrc->wfx.nBlockAlign = 2048;
	wfSrc->wfx.wBitsPerSample = sizeof(DWORD);
	wfSrc->wfx.cbSize = 32;
	wfSrc->wSamplesPerBlock = 2036;
	wfSrc->wNumCoef = 7;
	wfSrc->aCoef[0] = { 256, 0 };
	wfSrc->aCoef[1] = { 512, -256 };
	wfSrc->aCoef[2] = { 0, 0 };
	wfSrc->aCoef[3] = { 192, 64 };
	wfSrc->aCoef[4] = { 240, 0 };
	wfSrc->aCoef[5] = { 460, -208 };
	wfSrc->aCoef[6] = { 392, -232 };
	static WAVEFORMATEX* p = (WAVEFORMATEX*)malloc(1024); // TODO: BAD BAD BAD BAD BAD
	static WAVEFORMATEX& wfDst = *p;
	Zero(wfDst);
	wfDst.wFormatTag = WAVE_FORMAT_PCM;

	DWORD max_format;
	acmMetrics(nullptr, ACM_METRIC_MAX_SIZE_FORMAT, &max_format);

	acmFormatSuggest(acm_driver, &wfSrc->wfx, &wfDst, max_format, ACM_FORMATSUGGESTF_WFORMATTAG);

	acm_lock_length = 358336;
	acm_max_length = 89584;

	DSBUFFERDESC desc;
	DXInit(desc);
	desc.dwFlags = DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_CTRLPOSITIONNOTIFY | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLPAN | DSBCAPS_CTRLFREQUENCY | DSBCAPS_LOCSOFTWARE;
	desc.dwBufferBytes = 358336;
	desc.lpwfxFormat = &wfDst;
	App.lpDS->CreateSoundBuffer(&desc, &ACMSoundBuffer, nullptr);
	ACMSoundBuffer->QueryInterface(IID_IDirectSoundNotify, (LPVOID*)&DSNotify);
	SetupNotifications();
	acmStreamOpen(&acm_stream, acm_driver, &wfSrc->wfx, &wfDst, nullptr, 0, 0, 0);
	DWORD stream_size;
	acmStreamSize(acm_stream, 22528, &stream_size, 0);
	DX_TRY(ACMSoundBuffer->Lock(0, acm_lock_length, (LPVOID*)&acm_audio_ptr, &acm_audio_bytes, nullptr, nullptr, 0));

	memset(acm_audio_ptr, 0, acm_lock_length);

	DSInit(acm_header_1);
	DSInit(acm_header_2);
	DSInit(acm_header_3);
	DSInit(acm_header_4);

	acm_header_1.pbSrc = acm_header_2.pbSrc = acm_header_3.pbSrc = acm_header_4.pbSrc = source_buffer;
	acm_header_1.cbDstLength = acm_header_2.cbDstLength = acm_header_3.cbDstLength = acm_header_4.cbDstLength = stream_size;
	acm_header_1.cbSrcLength = acm_header_2.cbSrcLength = acm_header_3.cbSrcLength = acm_header_4.cbSrcLength = 22528;

	acm_header_1.pbDst = &acm_audio_ptr[0 * acm_max_length];
	acm_header_2.pbDst = &acm_audio_ptr[1 * acm_max_length];
	acm_header_3.pbDst = &acm_audio_ptr[2 * acm_max_length];
	acm_header_4.pbDst = &acm_audio_ptr[3 * acm_max_length];

	acmStreamPrepareHeader(acm_stream, &acm_header_1, 0);
	acmStreamPrepareHeader(acm_stream, &acm_header_2, 0);
	acmStreamPrepareHeader(acm_stream, &acm_header_3, 0);
	acmStreamPrepareHeader(acm_stream, &acm_header_4, 0);
					
	DX_TRY(ACMSoundBuffer->Unlock(acm_audio_ptr, acm_lock_length, nullptr, 0));

	ACMInited = true;
}

void ACMClose()
{
	if (ACMInited)
	{
		S_CDStop();

		// todo
		// todo

		acmStreamUnprepareHeader(acm_stream, &acm_header_1, 0);
		acmStreamUnprepareHeader(acm_stream, &acm_header_2, 0);
		acmStreamUnprepareHeader(acm_stream, &acm_header_3, 0);
		acmStreamUnprepareHeader(acm_stream, &acm_header_4, 0);

		acmStreamClose(acm_stream, 0);
		acmDriverClose(acm_driver, 0);

		DXRelease(DSNotify, "Notification");
		DXRelease(ACMSoundBuffer, "Stream Buffer");
	}
}

void DXFreeInfo(DEVICEINFO* info)// (F)
{
	Log(LT_Enter, "DXFreeInfo");

	for(int i = 0; i < info->nDDInfo; i++)
	{
		auto dd = info->DDInfo[i];

		for(int j = 0; j < dd.nD3DInfo; j++)
		{
			free(dd.D3DInfo[i].DisplayMode);
			free(dd.D3DInfo[i].Texture);
			free(dd.D3DInfo[i].Zbuffer);
		}

		free(dd.D3DInfo);
		free(dd.DisplayMode);
	}

	free(info->DDInfo);
	free(info->DSInfo);
}

void DI_ReadKeyboard(BYTE* keymap)// (F)
{
	HRESULT err = App.lpDIKeyboard->GetDeviceState(256, keymap);

	if (FAILED(err))
	{
		if (err == DIERR_INPUTLOST)
			App.lpDIKeyboard->Acquire();

		App.lpDIKeyboard->GetDeviceState(256, keymap);
	}
}

int DI_ReadJoystick(int* joy_x, int* joy_y)// (F)
{
	if (joystick_read)
	{
		*joy_x = joystick_read_x;
		*joy_y = joystick_read_y;
		return joystick_read_fire;
	}
	else
	{
		*joy_x = 0;
		*joy_y = 0;
		return 0;
	}
}

bool DI_UpdateJoystick()// (F)
{
	joystick_read = false;

	joystick_read_x = 0;
	joystick_read_y = 0;
	joystick_read_fire = 0;

	if (App.lpDIJoystick == nullptr)
		return false;

	DIJOYSTATE stat;

	HRESULT err;

	do
	{
		App.lpDIJoystick->Poll();

		if ((err = App.lpDIJoystick->GetDeviceState(80, &stat)) != DIERR_INPUTLOST)
			break;

		err = App.lpDIJoystick->Acquire();
	} while (err == DIERR_INPUTLOST);

	if (FAILED(err))
		return false;

	
	joystick_read_x = stat.lX;
	joystick_read_y = stat.lY;

	joystick_read = true;

	joystick_read_fire = 0;

	for(int i = 0; i < 32; i++)
	{
		if (KEYDOWN(stat.rgbButtons[i]))
			joystick_read_fire |= 1 << i;
	}

	return true;
}