#include "GPU.H"
#include "ERROR.H"

DWORD dword_D99D7C;
DWORD dword_D99DA4;
BYTE unk_D99D80[12];
DWORD BumpBitCount;
DWORD BumpDU;
DWORD BumpDV;
HWND dword_86B9A4;
#pragma comment (lib, "ddraw.lib")
#pragma comment (lib, "dxguid.lib")

#pragma comment (lib, "d3dx9.lib")
char *__cdecl sub_401A7D(void *a1, int a2, size_t a3)
{
	unsigned int v3; // esi@2
	char *result; // eax@2

	if (a2)
	{
		v3 = a3;
		result = (char *)realloc(a1, a3 * (a2 + 1));
	}
	else
	{
		v3 = a3;
		result = (char *)malloc(a3);
	}
	memset(&result[v3 * a2], 0, v3);
	return result;
}

unsigned int __cdecl sub_49F9C0(unsigned int a1, _BYTE *a2, _BYTE *a3)
{
	unsigned int result; // eax@1
	char i; // cl@1
	char v5; // cl@3

	result = a1;
	for (i = 0; !(result & 1); ++i)
		result >>= 1;
	*a2 = i;
	v5 = 0;
	if (result & 1)
	{
		do
		{
			result >>= 1;
			++v5;
		} while (result & 1);
		result = (unsigned int)a3;
		*a3 = v5;
	}
	else
	{
		*a3 = 0;
	}
	return result;
}


unsigned int __cdecl sub_4016B3(int a1, int a2, int a3)
{
	return sub_49F9C0(a1, (_BYTE *)a2, (_BYTE *)a3);
}

int DXMove(int xLeft, int yTop)
{
	int result; // eax@1

	Log(2, "DXMove : x %d y %d", xLeft, yTop);
	result = ptr_ctx;
	if (ptr_ctx)
	{
		if (!(ptr_ctx->flags & 1))
			result = SetRect(
				&ptr_ctx->windowPos,
				xLeft,
				yTop,
				xLeft + ptr_ctx->width,
				yTop + ptr_ctx->height);
	}
	return result;
}

int __cdecl DXDDCreate(GUID *lpGUID, LPDIRECTDRAW4* a2)
{
	HRESULT v3; // eax@1
	int v4; // eax@2
	int v5; // eax@3
	int result; // eax@5
	LPDIRECTDRAW lpDD; // [sp+10h] [bp-4h]@1

	Log(2, "DXDDCreate");
	v3 = DirectDrawCreate(lpGUID, &lpDD, 0);
	if (sub_40179E(v3))
	{
		Log(1, "DXDDCreate Failed");
		result = 0;
	}
	else
	{
		v4 = lpDD->lpVtbl->QueryInterface(lpDD, &IID_IDirectDraw4, a2);

		sub_40179E(v4);
		if (lpDD)
		{
			v5 = lpDD->lpVtbl->Release(lpDD);
			Log(4, "Released %s @ %x - RefCnt = %d", "DirectDraw", lpDD, v5);
			lpDD = 0;
		}
		else
		{
			Log(1, "%s Attempt To Release NULL Ptr", "DirectDraw");
		}
		Log(5, "DXDDCreate Successful");
		result = 1;
	}
	return result;
}



int DXChangeVideoMode()
{
	int v0; // esi@1

	Log(2, "DXChangeVideoMode");
	ptr_ctx->flags |= 0x40u;
	ptr_ctx->d3d->lpVtbl->EvictManagedTextures(ptr_ctx->d3d);
	v0 = DXCreate(
		0,
		0,
		0,
		ptr_ctx->flags,
		ptr_ctx,
		ptr_ctx->dxWndHwnd,
		ptr_ctx->dxWndStyle);
	ptr_ctx->flags ^= 0x40u;
	Log(2, "Exited DXChangeVideoMode %d", v0);
	return v0;
}



signed long __stdcall sub_401CBC(LPDDSURFACEDESC2 a1, int a2__)
{
	int v2; // esi@1
	struct dispmode *v3; // eax@1
	struct dispmode* v4; // ebx@1
	int v5; // edx@1
	struct gfxadapt* a2 = (struct gfxadapt*)a2__;
	v2 = a2->numDispModes;
	v3 = (struct dispmode*)sub_401A7D(*(void **)&a2->displayModes, a2->numDispModes, 150);
	a2->displayModes = v3;
	v4 = &v3[v2];
	v4->width = a1->dwWidth;
	v4->height = a1->dwHeight;
	v4->depth = a1->ddpfPixelFormat.dwRGBBitCount;
	v5 = (a1->ddpfPixelFormat.dwFlags >> 5) & 1;
	v4->isIndexed8 = v5;
	v4->mipMapCount = a1->dwMipMapCount;
	qmemcpy(&v4->surfaceDesc, (const void *)a1, 124);
	if (v5)
	{
		Log(3, "%d x %d - %d Bit - Palette", v4->width, v4->height, v4->depth);
	}
	else
	{
		sub_4016B3(a1->ddpfPixelFormat.dwRBitMask, &v4->offsetR, &v4->bitsR);
		sub_4016B3(a1->ddpfPixelFormat.dwGBitMask, &v4->offsetG, &v4->bitsG);
		sub_4016B3(a1->ddpfPixelFormat.dwBBitMask, &v4->offsetB, &v4->bitsB);
		Log(
			3,
			"%d x %d - %d Bit - %d%d%d",
			v4->width,
			v4->height,
			v4->depth,
			v4->bitsR,
			v4->bitsG,
			v4->bitsB);
	}
	++a2->numDispModes;
	return 1;
}

signed int __cdecl DXD3DCreate(LPDIRECTDRAW4 a1, IDirect3D3** a2)
{
	int v2; // eax@1
	signed int result; // eax@2

	Log(2, "DXD3DCreate");
	v2 = a1->lpVtbl->QueryInterface(a1, &IID_IDirect3D3, a2);
	if (sub_40179E(v2))
	{
		Log(1, "DXD3DCreate Failed");
		result = 0;
	}
	else
	{
		Log(5, "DXD3DCreate Successful");
		result = 1;
	}
	return result;
}


BOOL __cdecl DXSetCooperativeLevel(LPDIRECTDRAW4 a1, HWND a2, int a3)
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
		if (a3 & (1 << i))
		{
			strcat(v120, flags[i]);
			strcat(v120, " ");
		}
	}

	Log(2, v120);
	int v7 = a1->lpVtbl->SetCooperativeLevel(a1, a2, a3);
	return sub_40179E(v7) == 0;
}

signed int __cdecl DXCreateSurface(LPDIRECTDRAW4 a1, LPDDSURFACEDESC2 a2, LPDIRECTDRAWSURFACE4* a3)
{
	int v3; // eax@1
	signed int result; // eax@2

	Log(2, "DXCreateSurface");
	v3 = a1->lpVtbl->CreateSurface(a1, a2, a3, 0);
	if (sub_40179E(v3))
	{
		Log(1, "DXCreateSurface Failed");
		result = 0;
	}
	else
	{
		result = 1;
	}
	return result;
}

signed int __cdecl DXCreateD3DDevice(LPDIRECT3D3 a1, const IID a2, LPDIRECTDRAWSURFACE4 a6, LPDIRECT3DDEVICE3* a7)
{
	int v7; // eax@1
	signed int result; // eax@2

	Log(2, "DXCreateD3DDevice");
	v7 = a1->lpVtbl->CreateDevice(a1, &a2, a6, a7, 0);
	if (sub_40179E(v7))
	{
		Log(1, "DXCreateD3DDevice Failed");
		result = 0;
	}
	else
	{
		Log(2, "DXCreateD3DDevice Successful");
		result = 1;
	}
	return result;
}

BOOL __cdecl DXSetVideoMode(LPDIRECTDRAW4 a1, int a2, int a3, int a4)
{
	int v4; // eax@1
#if DEBUG
	a2 = 1680;
	a3 = 1050;
	a4 = 32;
#endif
	Log(2, "DXSetVideoMode");
	Log(5, "SetDisplayMode - %dx%dx%d", a2, a3, a4);
	v4 = a1->lpVtbl->SetDisplayMode(a1, a2, a3, a4, 0, 0);
	return sub_40179E(v4) == 0;
}

signed int __stdcall sub_401019(LPDDPIXELFORMAT a1, LPVOID a2__)
{
	int v2; // eax@1
	int v3; // esi@3
	struct acceltexformatinfo *v4; // eax@3
	struct acceltexformatinfo *v5; // ebp@3
	int v6; // eax@3
	int v7; // eax@7
	_BYTE *v8; // esi@8
	int v9; // ST18_4@9
	int v10; // ST14_4@9
	int v11; // ST10_4@9
	int v12; // ST0C_4@9
	int v13; // ST08_4@9
	signed int result; // eax@11
	int v15; // [sp-10h] [bp-14h]@8
	struct acceladapt* a2 = (struct accelaadapt*)a2__;
	v2 = a1->dwFlags;
	if (v2 & 1 && v2 & 0x40)
	{
		v3 = a2->numTexFormats;
		v4 = (struct acceltexformatinfo*)sub_401A7D(*(void **)&a2->texFormats, a2->numTexFormats, 0x34u);
		a2->texFormats = v4;
		v5 = &v4[v3];
		qmemcpy(&v4[v3], a1, 0x20u);
		v6 = a1->dwFlags;
		if (v6 & 0x20)
		{
			v5->field1 = 1;
			v5->depth = 8;
			Log(3, "8 Bit");
		}
		else if (v6 & 8)
		{
			v5->field1 = 1;
			v5->depth = 4;
			Log(3, "4 Bit");
		}
		else
		{
			v5->field1 = 0;
			v5->depth = a1->dwRGBBitCount;
			v7 = a1->dwFlags;
			if (v7 & 0x40)
			{
				if (v7 & 1)
				{
					sub_4016B3(a1->dwRBitMask, &v5->offsetR, &v5->bitsR);
					sub_4016B3(a1->dwGBitMask, &v5->offsetG, &v5->bitsG);
					sub_4016B3(a1->dwBBitMask, &v5->offsetB, &v5->bitsB);
					sub_4016B3(a1->dwRGBAlphaBitMask, &v5->offsetA, &v5->bitsA);
					v9 = v5->bitsA;
					v10 = v5->bitsB;
					v11 = v5->bitsG;
					v12 = v5->bitsR;
					v13 = v5->depth;
					v5->field2 = 1;
					Log(3, "%d Bit %d%d%d%d RGBA", v13, v12, v11, v10, v9);
				}
				else
				{
					sub_4016B3(a1->dwRBitMask, &v5->offsetR, &v5->bitsR);
					sub_4016B3(a1->dwGBitMask, &v5->offsetG, &v5->bitsG);
					sub_4016B3(a1->dwBBitMask, &v5->offsetB, &v5->bitsB);
					Log(3, "%d Bit %d%d%d RGB", v5->depth, v5->bitsR, v5->bitsG, v5->bitsB);
				}
			}
		}
		++a2->numTexFormats;
		result = 1;
	}
	else
	{
		result = 1;
	}
	return result;
}

signed int __stdcall sub_402FDB(LPDDPIXELFORMAT a1, struct acceladapt* a2)
{
	int v2; // esi@1
	struct zBufFormat*v3; // eax@1
	struct zBufFormat* v4; // eax@1
	int v5; // ST08_4@1

	v2 = a2->numZbufFormats;
	v3 = (struct zBufFormat*)sub_401A7D(*(void **)&a2->zBufFormats, a2->numZbufFormats, 36);
	a2->zBufFormats = v3;
	v4 = &v3[v2];
	qmemcpy((void *)v4, (const void *)a1, 32);
	v5 = a1->dwRGBBitCount;
	v4->depth = v5;
	Log(3, "%d Bit", v5);
	++a2->numZbufFormats;
	return 1;
}

signed int __cdecl sub_40206D(int a1)
{
	signed int result; // eax@2

	switch (a1)
	{
	case 1:
		result = 0x4000;
		break;
	case 2:
		result = 0x2000;
		break;
	case 4:
		result = 4096;
		break;
	case 8:
		result = 2048;
		break;
	case 16:
		result = 1024;
		break;
	case 24:
		result = 512;
		break;
	case 32:
		result = 256;
		break;
	default:
		result = 0;
		break;
	}
	return result;
}


signed long __stdcall sub_402ECD(GUID* a1, CHAR *devDesc, CHAR *devName, LPD3DDEVICEDESC a4, LPD3DDEVICEDESC a5, void* a6__)
{
	int v6; // esi@1
	struct acceladapt *v7; // eax@1
	struct acceladapt * v8; // ebp@1
	GUID* v9; // ecx@3
	char *v10; // ebx@4
	unsigned int v11; // ecx@7
	char v12; // dl@7
	char *v13; // edi@7
	char *v14; // esi@7
	char v15; // cl@7
	unsigned int v16; // ecx@8
	char v17; // al@8
	int v18; // ebx@10
	int v19; // eax@10
	struct gfxadapt* v20; // edi@11
	struct dispmode *v21; // eax@12
	int v22; // ecx@12
	struct dispmode *v23; // eax@12
	int v24; // ecx@16
	int v25; // eax@20
	LPDIRECTDRAWSURFACE4 v26; // eax@22
	int v27; // eax@25
	int v28; // eax@26
	int v29; // eax@30
	int v30; // eax@32
	LPDIRECTDRAWSURFACE4 v32; // [sp+10h] [bp-88h]@17
	LPDIRECT3DDEVICE3 v33; // [sp+14h] [bp-84h]@18
	int v34; // [sp+18h] [bp-80h]@10
	DDSURFACEDESC2 v35; // [sp+1Ch] [bp-7Ch]@17
	struct gfxadapt* a6 = (struct gfxadapt*)a6__;
	v6 = a6->numAccelAdapters;
	v7 = (struct acceladapt*)sub_401A7D(*(void **)&a6->accelAdapters, a6->numAccelAdapters, 410);
	a6->accelAdapters = v7;
	v8 = &v7[v6];
	if (a1)
	{
		v9 = &v8->guid;
		v8->field1 = &v8->guid;
		v8->guid = *a1;
	}
	else
	{
		v8->field1 = 0;
	}
	v10 = v8->description;
	lstrcpyA(v8->description, devDesc);
	lstrcpyA(v8->name, devName);
	Log(5, "Found - %s", devDesc);
	if (a4->dwFlags)
	{
		v8->field2 = 1;
		qmemcpy(&v8->deviceDesc, a4, 0xFCu);
	}
	else
	{
		v8->field2 = 0;
		qmemcpy(&v8->deviceDesc, a5, 0xFCu);
		if (ptr_ctx->byte_D9AC23)
		{
			char* aCoreDesignMmxH = "Core Design MMX Hardware Card Emulation";
			v11 = strlen(aCoreDesignMmxH) + 1;
			v12 = v11;
			v11 >>= 2;
			qmemcpy(v10, aCoreDesignMmxH, 4 * v11);
			v14 = &aCoreDesignMmxH[4 * v11];
			v13 = &v10[4 * v11];
			v15 = v12;
		}
		else
		{
			char* aCoreDesignHard = "Core Design Hardware Card Emulation";
			v16 = strlen(aCoreDesignHard) + 1;
			v17 = v16;
			v16 >>= 2;
			qmemcpy(v10, aCoreDesignHard, 4 * v16);
			v14 = &aCoreDesignHard[4 * v16];
			v13 = &v10[4 * v16];
			v15 = v17;
		}
		qmemcpy(v13, v14, v15 & 3);
	}
	Log(5, "Finding Compatible Display Modes");
	v18 = 0;
	v8->numDispModes = 0;
	v19 = a6->numDispModes;
	v34 = 0;
	if (v19 > 0)
	{
		do
		{
			v20 = a6;
			if (sub_40206D(a6->displayModes[v18].depth) & v8->deviceDesc.dwDeviceRenderBitDepth)
			{
				v21 = (struct dispmode*)sub_401A7D(*(void **)&v8->displayModes, v8->numDispModes, 150);
				v22 = v8->numDispModes;
				v8->displayModes = v21;
				v23 = &v21[v22];
				qmemcpy(v23, &a6->displayModes[v18], 0x96u);
				if (v23->isIndexed8)
					Log(3, "%d x %d - %d Bit - Palette", v23->width, v23->height, v23->depth);
				else
					Log(
						3,
						"%d x %d - %d Bit - %d%d%d",
						v23->width,
						v23->height,
						v23->depth,
						v23->bitsR,
						v23->bitsG,
						v23->bitsB);
				v20 = a6;
				++v8->numDispModes;
			}
			v24 = v20->numDispModes;
			v18++;
			++v34;
		} while (v34 < v24);
	}
	Log(5, "Enumerate Texture Formats");
	memset(&v35, 0, 0x7Cu);
	v35.dwSize = 124;
	v35.dwFlags = 1;
	v35.ddsCaps.dwCaps = 8704;
	DXSetCooperativeLevel(iface_DirectDraw, dword_86B9A4, 21);
	DXCreateSurface(iface_DirectDraw, &v35, &v32);
	if (v32)
	{
		DXCreateD3DDevice(
			iface_D3D3,
			v8->guid,
			v32,
			&v33);
		if (v33)
			goto LABEL_35;
		Log(1, "Create D3DDevice Failed");
		if (v32)
		{
			v25 = v32->lpVtbl->Release(v32);
			Log(4, "Released %s @ %x - RefCnt = %d", "DirectDrawSurface", v32, v25);
			v32 = 0;
		}
		else
		{
			Log(1, "%s Attempt To Release NULL Ptr", "DirectDrawSurface");
		}
		DXSetVideoMode(
			iface_DirectDraw,
			v8->displayModes->width,
			v8->displayModes->height,
			v8->displayModes->depth);
		DXCreateSurface(iface_DirectDraw, &v35, &v32);
		v26 = v32;
		if (v32)
		{
			DXCreateD3DDevice(
				iface_D3D3,
				v8->guid,
				v32,
				&v33);
			v26 = v32;
		}
		if (v33)
		{
		LABEL_35:
			v8->numTexFormats = 0;
			Log(2, "DXEnumTextureFormats");
			v27 = v33->lpVtbl->EnumTextureFormats(v33, &sub_401019, v8);
			sub_40179E(v27);
			if (v33)
			{
				v28 = v33->lpVtbl->Release(v33);
				Log(4, "Released %s @ %x - RefCnt = %d", "D3DDevice", v33, v28);
				v33 = 0;
			}
			else
			{
				Log(1, "%s Attempt To Release NULL Ptr", "D3DDevice");
			}
			v26 = v32;
		}
		if (v26)
		{
			v29 = v26->lpVtbl->Release(v26);
			Log(4, "Released %s @ %x - RefCnt = %d", "DirectDrawSurface", v32, v29);
			v32 = 0;
		}
		else
		{
			Log(1, "%s Attempt To Release NULL Ptr", "DirectDrawSurface");
		}
	}
	DXSetCooperativeLevel(iface_DirectDraw, dword_86B9A4, 8);
	Log(5, "Enumerating ZBuffer Formats");
	Log(2, "DXEnumZBufferFormats");
	v30 = iface_D3D3->lpVtbl->EnumZBufferFormats(
		iface_D3D3,
		&v8->guid,
		sub_402FDB,
		v8);
	sub_40179E(v30);
	++a6->numAccelAdapters;
	return 1;
}

signed int __stdcall DXEnumDirectDraw(GUID *lpGUID, LPSTR DriverDescription, LPSTR DriverName, LPVOID Context__)
{
	int v4; // esi@1
	struct gfxadapt* v5; // eax@1
	struct gfxadapt* v6; // esi@1
	char* v7; // eax@3
	int v8; // eax@5
	int v9; // eax@5
	int v10; // eax@5
	int v11; // eax@6
	int v12; // eax@7
	int v13; // eax@10
	struct dxcontext_s* Context = (struct dxcontext_s*)Context__;
	Log(2, "DXEnumDirectDraw");
	v4 = Context->numGraphicsAdapters;
	v5 = (struct gfxadapt*)sub_401A7D(*(void **)&Context->graphicsAdapters, Context->numGraphicsAdapters, 1590);
	Context->graphicsAdapters = v5;
	v6 = &v5[v4];
	if (lpGUID)
	{
		v6->field3 = &v6->guid;
		v6->guid = *lpGUID;
	}
	else
	{
		v6->field3 = 0;
	}
	lstrcpyA(v6->driverDesc, DriverDescription);
	lstrcpyA(v6->driverName, DriverName);
	Log(5, "Obtaining Information For %s", DriverDescription);
	if (DXDDCreate(lpGUID, &iface_DirectDraw))
	{
		v8 = iface_DirectDraw->lpVtbl->GetDeviceIdentifier(
			iface_DirectDraw,
			v6->driverDllName,
			0);
		sub_40179E(v8);
		Log(
			5,
			"Found - %s\r\nDriver %s Version %d.%d.%d.%d",
			v6->deviceName,
			v6->driverDllName,
			v6->versionMajor,
			v6->versionMinor,
			v6->versionBuild,
			v6->versionRevision);
		memset(&v6->capabilities, 0, 380);
		v6->capabilities.dwSize = 380;
		Log(5, "Getting Device Capabilities");
		v9 = iface_DirectDraw->lpVtbl->GetCaps(
			iface_DirectDraw,
			&v6->capabilities,
			0);
		sub_40179E(v9);
		Log(5, "Enumerating Display Modes");
		DXSetCooperativeLevel(iface_DirectDraw, 0, 77);
		Log(2, "DXEnumDisplayModes");
		v10 = iface_DirectDraw->lpVtbl->EnumDisplayModes(
			iface_DirectDraw,
			0,
			0,
			v6,
			&sub_401CBC);
		sub_40179E(v10);
		if (DXD3DCreate(iface_DirectDraw, &iface_D3D3))
		{
			Log(2, "DXEnumDirect3D");
			v11 = iface_D3D3->lpVtbl->EnumDevices(iface_D3D3, &sub_402ECD, v6);
			sub_40179E(v11);
			if (iface_D3D3)
			{
				v12 = iface_D3D3->lpVtbl->Release(iface_D3D3);
				Log(4, "Released %s @ %x - RefCnt = %d", "Direct3D", iface_D3D3, v12);
				iface_D3D3 = 0;
			}
			else
			{
				Log(1, "%s Attempt To Release NULL Ptr", "Direct3D");
			}
		}
		DXSetCooperativeLevel(iface_DirectDraw, 0, 8);
		if (iface_DirectDraw)
		{
			v13 = iface_DirectDraw->lpVtbl->Release(iface_DirectDraw);
			Log(4, "Released %s @ %x - RefCnt = %d", "DirectDraw", iface_DirectDraw, v13);
			iface_DirectDraw = 0;
			++Context->numGraphicsAdapters;
			return 1;
		}
		Log(1, "%s Attempt To Release NULL Ptr", "DirectDraw");
	}
	++Context->numGraphicsAdapters;
	return 1;
}

signed int __stdcall DXEnumDirectSound(GUID* a1, CHAR *devDesc, CHAR *devName, int a4__)
{
	int v4; // edi@1
	struct soundcard *v5; // eax@1
	struct soundcard* v6; // edi@1
	int v7; // eax@3
	struct dxcontext_s* a4 = (struct dxcontext_s*)a4__;
	Log(2, "DXEnumDirectSound");
	v4 = a4->numSoundCards;
	v5 = (struct soundcard*)sub_401A7D(*(void **)&a4->soundCards, a4->numSoundCards, 0x82u);
	a4->soundCards = v5;
	v6 = &v5[v4];
	if (a1)
	{
		v6->field1 = &v6->guid;
		v6->guid = *a1;
	}
	else
	{
		v6->field1 = 0;
	}
	lstrcpyA(v6->description, devDesc);
	lstrcpyA(v6->name, devName);
	Log(5, "Found - %s %s", v6->description, v6->name);
	++a4->numSoundCards;
	return 1;
}

signed int __cdecl DXInitialise(void *lpContext, HWND hwnd)
{
	HRESULT v2; // eax@1
	HRESULT v3; // eax@1

	Log(2, "DXInitialise");
	dword_86B9A4 = hwnd;
	Log(5, "Enumerating DirectDraw Devices");
	v2 = DirectDrawEnumerateA(DXEnumDirectDraw, lpContext);
	sub_40179E(v2);
	v3 = DirectSoundEnumerateA(DXEnumDirectSound, lpContext);
	sub_40179E(v3);
	//ptr_ctx = (struct dxcontext_s*)lpContext;
	return 1;
}


signed int __stdcall sub_402AB3(LPDDPIXELFORMAT a1, void *a2)
{
	signed int result; // eax@2

	if (a1->dwFlags == DDPF_BUMPDUDV)
	{
		result = 0;
		qmemcpy(a2, a1, 0x20u);
		dword_D99D7C = 1;
	}
	else
	{
		result = 1;
	}
	return result;
}

int sub_401424()
{
	struct acceladapt* result; // eax@1

	dword_D99DA4 = 0;
	result = &ptr_ctx->graphicsAdapters[ptr_ctx->curGfxAdapt].accelAdapters[ptr_ctx->curAccelAdapt];
	if ((D3DTEXOPCAPS_BUMPENVMAP | D3DTEXOPCAPS_BUMPENVMAPLUMINANCE) & result->deviceDesc.dwTextureOpCaps)
	{
		if (result->deviceDesc.wMaxTextureBlendStages >= 3u)
		{
			dword_D99D7C = 0;
			ptr_ctx->d3d_dev->lpVtbl->EnumTextureFormats(
				ptr_ctx->d3d_dev,
				sub_402AB3,
				&unk_D99D80[0]);
			result = dword_D99D7C;
			if (dword_D99D7C)
			{
				Log(5, "Bump bit count 0x%X", *(_DWORD *)BumpBitCount);
				Log(5, "Bump DU %X", *(_DWORD *)BumpDU);
				Log(5, "Bump DV %X", *(_DWORD *)BumpDV);
				result = *(_DWORD *)BumpBitCount;
				if (*(_DWORD *)BumpBitCount == 16)
					dword_D99DA4 = 1;
			}
		}
	}
	return result;
}



HWND CloseDirectX()
{
	HWND result; // eax@1
	LPDIRECTDRAW4 v1; // ecx@2
	LPDIRECT3DVIEWPORT3 v2; // eax@2
	int v3; // eax@3
	LPDIRECT3DDEVICE3 v4; // eax@5
	int v5; // eax@6
	LPDIRECTDRAWSURFACE4 v6; // eax@8
	int v7; // eax@9
	LPDIRECTDRAWSURFACE4 v8; // eax@11
	int v9; // eax@12
	LPDIRECTDRAWSURFACE4 v10; // eax@14
	int v11; // eax@15
	int v12; // eax@19
	LPDIRECT3D3 v13; // eax@21
	int v14; // eax@22

	Log(2, "CloseDirectX");
	result = (HWND)ptr_ctx;
	if (ptr_ctx)
	{
		v1 = ptr_ctx->ddraw;
		v2 = ptr_ctx->viewport;
		if (v2)
		{
			v3 = v2->lpVtbl->Release(v2);
			Log(4, "Released %s @ %x - RefCnt = %d", "Viewport", ptr_ctx->viewport, v3);
			ptr_ctx->viewport = 0;
		}
		else
		{
			Log(1, "%s Attempt To Release NULL Ptr", "Viewport");
		}
		v4 = ptr_ctx->d3d_dev;
		if (v4)
		{
			v5 = v4->lpVtbl->Release(ptr_ctx->d3d_dev);
			Log(4, "Released %s @ %x - RefCnt = %d", "Direct3DDevice", ptr_ctx->d3d_dev, v5);
			ptr_ctx->d3d_dev = 0;
		}
		else
		{
			Log(1, "%s Attempt To Release NULL Ptr", "Direct3DDevice");
		}
		v6 = ptr_ctx->buf_z;
		if (v6)
		{
			v7 = v6->lpVtbl->Release(ptr_ctx->buf_z);
			Log(4, "Released %s @ %x - RefCnt = %d", "Z Buffer", ptr_ctx->buf_z, v7);
			ptr_ctx->buf_z = 0;
		}
		else
		{
			Log(1, "%s Attempt To Release NULL Ptr", "Z Buffer");
		}
		v8 = ptr_ctx->buf_back;
		if (v8)
		{
			v9 = v8->lpVtbl->Release(ptr_ctx->buf_back);
			Log(4, "Released %s @ %x - RefCnt = %d", "Back Buffer", ptr_ctx->buf_back, v9);
			ptr_ctx->buf_back = 0;
		}
		else
		{
			Log(1, "%s Attempt To Release NULL Ptr", "Back Buffer");
		}
		v10 = ptr_ctx->buf_primary;
		if (v10)
		{
			v11 = v10->lpVtbl->Release(ptr_ctx->buf_primary);
			Log(4, "Released %s @ %x - RefCnt = %d", "Primary Buffer", ptr_ctx->buf_primary, v11);
			ptr_ctx->buf_primary = 0;
		}
		else
		{
			Log(1, "%s Attempt To Release NULL Ptr", "Primary Buffer");
		}
		result = (HWND)ptr_ctx;
		if (!(ptr_ctx->flags & 0x40))
		{
			if (ptr_ctx->ddraw)
			{
				v12 = ptr_ctx->ddraw->lpVtbl->Release(ptr_ctx->ddraw);
				Log(4, "Released %s @ %x - RefCnt = %d", "DirectDraw", ptr_ctx->ddraw, v12);
				ptr_ctx->ddraw = 0;
			}
			else
			{
				Log(1, "%s Attempt To Release NULL Ptr", "DirectDraw");
			}
			v13 = ptr_ctx->d3d;
			if (v13)
			{
				v14 = v13->lpVtbl->Release(ptr_ctx->d3d);
				result = Log(4, "Released %s @ %x - RefCnt = %d", "Direct3D", ptr_ctx->d3d, v14);
				ptr_ctx->d3d = 0;
			}
			else
			{
				result = Log(1, "%s Attempt To Release NULL Ptr", "Direct3D");
			}
		}
	}
	return result;
}

int sub_40193D()
{
	S_Warn("[sub_40193D] - Unimplemented!\\n");
	return 0;
}

signed int __cdecl DXCreateViewport(LPDIRECT3D3 a1, LPDIRECT3DDEVICE3 a2, DWORD a3, DWORD a4, LPDIRECT3DVIEWPORT3 *a5)
{
	HRESULT v5; // eax@1
	signed int result; // eax@2
	int v7; // eax@3
	LPDIRECT3DVIEWPORT3 v8; // eax@5
	HRESULT v9; // eax@5
	HRESULT v10; // eax@7
	D3DVIEWPORT2 v11; // [sp+14h] [bp-2Ch]@5

	Log(2, "DXCreateViewport");
	v5 = a1->lpVtbl->CreateViewport(a1, a5, 0);
	if (sub_40179E(v5))
	{
		result = 0;
	}
	else
	{
		v7 = a2->lpVtbl->AddViewport(a2, *a5);
		if (sub_40179E(v7))
		{
			result = 0;
		}
		else
		{
			memset(&v11, 0, sizeof(v11));
			v11.dvClipWidth = (D3DVALUE)a3;
			v11.dvClipHeight = (D3DVALUE)a4;
			v11.dwX = 0;
			v11.dwY = 0;
			v11.dvClipX = 0;
			v11.dvClipY = 0;
			v11.dvMinZ = 0;
			v8 = *a5;
			v11.dwHeight = a4;
			v11.dwSize = 44;
			v11.dwWidth = a3;
			v11.dvMaxZ = 1;
			v9 = v8->lpVtbl->SetViewport2(v8, &v11);
			if (sub_40179E(v9))
			{
				result = 0;
			}
			else
			{
				v10 = a2->lpVtbl->SetCurrentViewport(a2, *a5);
				sub_40179E(v10);
				result = 1;
			}
		}
	}
	return result;
}

signed int __cdecl DXCreate(int a1, int a2, int a3, int flags, struct dxcontext_s *a5, HWND a6, DWORD dwStyle)
{

	signed int v7; // edi@1
	signed int result; // eax@5
	int v9; // eax@8
	struct dispmode* v10; // ecx@13
	int v11; // eax@26
	int v12; // eax@30
	int v13; // eax@32
	int v14; // eax@32
	int v15; // eax@33
	int v16; // eax@35
	int v17; // eax@37
	struct gfxadapt* v18; // edi@38
	int v19; // eax@42
	HDC hDC; // [sp+28h] [bp-12Ch]@14
	IDirectDrawClipper* hDC_;
	struct tagRECT Rect; // [sp+2Ch] [bp-128h]@28
	int v22; // [sp+3Ch] [bp-118h]@8
	HWND hWnd; // [sp+40h] [bp-114h]@14
	DDSURFACEDESC2 a2a; // [sp+44h] [bp-110h]@15
	DEVMODEA var94; // [sp+C0h] [bp-94h]@14
	__int16 v26; // [sp+E4h] [bp-70h]@14
	int v27; // [sp+E8h] [bp-6Ch]@14
	int v28; // [sp+128h] [bp-2Ch]@14

	v7 = 0;
	Log(2, "DXCreate");
	//ptr_ctx = a5;
	a5->flags = flags;
	dxctx.dxWndHwnd = a6;
	dxctx.dxWndStyle = dwStyle;
	if (flags & 0x40)
		v7 = 1;
	CloseDirectX();
	if (!v7)
	{
		if (!DXDDCreate(
			ptr_ctx->graphicsAdapters[ptr_ctx->curGfxAdapt].field3,
			&ptr_ctx->ddraw))
		{
			CloseDirectX();
			return 0;
		}
		if (!DXD3DCreate(ptr_ctx->ddraw, &ptr_ctx->d3d))
		{
			CloseDirectX();
			return 0;
		}
	}
	v22 = flags & 1;
	v9 = v22 != 0 ? 19 : 8;
	if (flags & 0x20)
		v9 |= 0x800u;
	ptr_ctx->dword_D9ABE5 = v9;
	if (!DXSetCooperativeLevel(ptr_ctx->ddraw, a6, v9))
	{
		CloseDirectX();
		return 0;
	}
	if (flags & 1)
	{
		v10 = ptr_ctx->graphicsAdapters[ptr_ctx->curGfxAdapt]
			.accelAdapters[ptr_ctx->curAccelAdapt]
			.displayModes;
		DXSetVideoMode(
			ptr_ctx->ddraw,
			v10[ptr_ctx->curDispMode].width,
			v10[ptr_ctx->curDispMode].height,
			v10[ptr_ctx->curDispMode].depth);
	}
	else
	{
		hWnd = GetDesktopWindow();
		v26 = 148;
		hDC = GetDC(hWnd);
		v28 = ptr_ctx->graphicsAdapters[ptr_ctx->curGfxAdapt]
			.accelAdapters[ptr_ctx->curAccelAdapt]
			.displayModes[ptr_ctx->curDispMode]
			.depth;
		ReleaseDC(hWnd, hDC);
		v27 = 0x40000;
		ChangeDisplaySettingsA(&var94, 0);
	}
	memset(&a2a, 0, sizeof(a2a));
	a2a.dwSize = 124;
	if (v22)
	{
		a2a.dwBackBufferCount = 1;
		a2a.dwFlags = 33;
		a2a.ddsCaps.dwCaps = 25112;
		if (!(flags & 0x80))
		{
			a2a.dwBackBufferCount = 0;
			a2a.dwFlags = 1;
			a2a.ddsCaps.dwCaps = 25088;
		}
		Log(3, "Create Primary Surface");
		if (!DXCreateSurface(ptr_ctx->ddraw, &a2a, &ptr_ctx->buf_primary))
		{
			CloseDirectX();
			return 0;
		}
		if (flags & 0x80)
		{
			Log(3, "Get Attached Back Buffer");
			a2a.ddsCaps.dwCaps = 4;
			ptr_ctx->buf_primary->lpVtbl->GetAttachedSurface(
				ptr_ctx->buf_primary,
				&a2a.ddsCaps,
				&ptr_ctx->buf_back);
		}
		else
		{
			ptr_ctx->buf_back = ptr_ctx->buf_primary;
		}
		ptr_ctx->width = ptr_ctx->graphicsAdapters[ptr_ctx->curGfxAdapt]
			.accelAdapters[ptr_ctx->curAccelAdapt]
			.displayModes[ptr_ctx->curDispMode]
			.width;
		ptr_ctx->height = ptr_ctx->graphicsAdapters[ptr_ctx->curGfxAdapt]
			.accelAdapters[ptr_ctx->curAccelAdapt]
			.displayModes[ptr_ctx->curDispMode]
			.height;
		ptr_ctx->stru_D9ABBD.top = 0;
		ptr_ctx->stru_D9ABBD.left = 0;
		ptr_ctx->stru_D9ABBD.right = ptr_ctx->graphicsAdapters[ptr_ctx->curGfxAdapt]
			.accelAdapters[ptr_ctx->curAccelAdapt]
			.displayModes[ptr_ctx->curDispMode]
			.width;
		ptr_ctx->stru_D9ABBD.bottom = ptr_ctx->graphicsAdapters[ptr_ctx->curGfxAdapt]
			.accelAdapters[ptr_ctx->curAccelAdapt]
			.displayModes[ptr_ctx->curDispMode]
			.height;
	}
	else
	{
		Log(5, "DXCreate: Windowed Mode");
		Rect.top = 0;
		Rect.left = 0;
		Rect.right = ptr_ctx->graphicsAdapters[ptr_ctx->curGfxAdapt]
			.accelAdapters[ptr_ctx->curAccelAdapt]
			.displayModes[ptr_ctx->curDispMode]
			.width;
		Rect.bottom = ptr_ctx->graphicsAdapters[ptr_ctx->curGfxAdapt]
			.accelAdapters[ptr_ctx->curAccelAdapt]
			.displayModes[ptr_ctx->curDispMode]
			.height;
		AdjustWindowRect(&Rect, dwStyle, 0);
		SetWindowPos(a6, 0, 0, 0, Rect.right - Rect.left, Rect.bottom - Rect.top, 6u);
		GetClientRect(a6, &ptr_ctx->stru_D9ABBD);
		GetClientRect(a6, &ptr_ctx->windowPos);
		ClientToScreen(a6, (LPPOINT)&ptr_ctx->windowPos.left);
		ClientToScreen(a6, (LPPOINT)&ptr_ctx->windowPos.right);
		ptr_ctx->width = ptr_ctx->stru_D9ABBD.right;
		ptr_ctx->height = ptr_ctx->stru_D9ABBD.bottom;
		Log(5, "w %d h %d", ptr_ctx->width, ptr_ctx->height);
		a2a.dwFlags = 1;
		a2a.ddsCaps.dwCaps = 512;
		if (!DXCreateSurface(ptr_ctx->ddraw, &a2a, &ptr_ctx->buf_primary))
		{
			CloseDirectX();
			return 0;
		}
		v12 = ptr_ctx->ddraw->lpVtbl->CreateClipper(
			ptr_ctx->ddraw,
			0,
			&hDC_,
			0);
		if (sub_40179E(v12))
		{
			CloseDirectX();
			return 0;
		}
		v13 = hDC_->lpVtbl->SetHWnd(hDC_, 0, a6);
		sub_40179E(v13);
		v14 = ptr_ctx->buf_primary->lpVtbl->SetClipper(
			ptr_ctx->buf_primary,
			hDC_);
		sub_40179E(v14);
		if (hDC_)
		{
			v15 = hDC_->lpVtbl->Release(hDC_);
			Log(4, "Released %s @ %x - RefCnt = %d", "Clipper", hDC_, v15);
			hDC_ = 0;
		}
		else
		{
			Log(1, "%s Attempt To Release NULL Ptr", "Clipper");
		}
		a2a.dwFlags = 7;
		a2a.dwWidth = ptr_ctx->width;
		a2a.dwHeight = ptr_ctx->height;
		a2a.ddsCaps.dwCaps = 8256;
		v16 = ptr_ctx->ddraw->lpVtbl->CreateSurface(
			ptr_ctx->ddraw,
			&a2a,
			&ptr_ctx->buf_back,
			0);
		if (sub_40179E(v16))
		{
			CloseDirectX();
			return 0;
		}
	}
	if (flags & 0x10 && flags & 0x80)
	{
		Log(3, "ZBUFFER NOT WORKING, NOT CREATED TODO");
		/*Log(3, "Creating ZBuffer");
		memset(&a2a, 0, sizeof(a2a));
		a2a.dwSize = 124;
		a2a.dwFlags = DDSD_PIXELFORMAT | DDSD_WIDTH | DDSD_HEIGHT | DDSD_CAPS;
		a2a.ddsCaps.dwCaps = DDCAPS_OVERLAYSTRETCH | DDCAPS_READSCANLINE;
		a2a.dwWidth = ptr_ctx->width;
		a2a.dwHeight = ptr_ctx->height;
		qmemcpy(
		&a2a.ddpfPixelFormat,
		&ptr_ctx->graphicsAdapters[ptr_ctx->curGfxAdapt]
		.accelAdapters[ptr_ctx->curAccelAdapt]
		.zBufFormats->pixFormat,
		sizeof(a2a.ddpfPixelFormat));
		v11 = ptr_ctx->ddraw->lpVtbl->CreateSurface(
		ptr_ctx->ddraw,
		&a2a,
		&ptr_ctx->buf_z,
		0);
		if (sub_40179E(v11))
		{
		CloseDirectX();
		return 0;
		}
		v17 = ptr_ctx->buf_back->lpVtbl->AddAttachedSurface(
		ptr_ctx->buf_back,
		ptr_ctx->buf_z);
		sub_40179E(v17);
		Log(3, "ZBuffer Created %x", ptr_ctx->buf_z);*/
	}
	v18 = ptr_ctx->graphicsAdapters;
	if (DXCreateD3DDevice(
		ptr_ctx->d3d,
		ptr_ctx->graphicsAdapters[ptr_ctx->curGfxAdapt]
		.accelAdapters[ptr_ctx->curAccelAdapt]
		.guid,
		ptr_ctx->buf_back,
		&ptr_ctx->d3d_dev))
	{
		ptr_ctx->d3d_dev_bis = ptr_ctx->d3d_dev;
		if (DXCreateViewport(
			ptr_ctx->d3d,
			ptr_ctx->d3d_dev,
			ptr_ctx->width,
			ptr_ctx->height,
			&ptr_ctx->viewport))
		{
			v19 = ptr_ctx->d3d_dev->lpVtbl->SetRenderTarget(
				ptr_ctx->d3d_dev,
				ptr_ctx->buf_back,
				0);
			sub_40179E(v19);
			if (!(ptr_ctx->flags & 0x80))
				sub_40193D();
			result = 1;
		}
		else
		{
			CloseDirectX();
			result = 0;
		}
	}
	else
	{
		CloseDirectX();
		result = 0;
	}
	return result;
	S_Warn("[DXCreate] - Unimplemented!\n");
	return 0;
}

int __cdecl sub_4B8780(LPDIRECTDRAWSURFACE4 a3, HGDIOBJ h, int xSrc, int ySrc, int wSrc, int hSrc)
{
	int v6; // ebx@0
	int v7; // ebp@0
	LPDIRECTDRAWSURFACE4 v8; // esi@2
	HDC v9; // ebp@3
	int v11; // edi@5
	int v12; // ebx@5
	HDC hdcDest; // [sp+18h] [bp-9Ch]@0
	HDC v14; // [sp+20h] [bp-94h]@8
	char pv[80]; // [sp+28h] [bp-8Ch]@5
	DDSURFACEDESC2 surfd;

	if (h && (v8 = a3) != NULL)
	{
		a3->lpVtbl->Restore(a3);
		v9 = CreateCompatibleDC(0);
		if (!v9)
			OutputDebugStringA("createcompatible dc failed");
		SelectObject(v9, h);
		GetObjectA(h, 24, &pv);
		surfd.dwSize = 124;
		surfd.dwFlags = 6;
		a3->lpVtbl->GetSurfaceDesc(a3, &surfd);
		v11 = 0;
		v12 = 0;
		if (!(dxctx.flags & 0x80))
		{
			v8 = dxctx.buf_primary;
			if (dxctx.flags & 2)
			{
				v11 = dxctx.windowPos.left;
				v12 = dxctx.windowPos.top;
			}
		}
		int v15 = v8->lpVtbl->GetDC(v8, &v14);
		if (!v15)
		{
			hdcDest = v14;
			StretchBlt(hdcDest, v11, v12, surfd.dwWidth, surfd.dwHeight, v9, xSrc, ySrc, wSrc, hSrc, 0xCC0020);
			v8->lpVtbl->ReleaseDC(v8, hdcDest);
		}
		DeleteDC(v9);
		return v15;
	}
	else
	{
		return 0x80004005;
	}
}

signed int __cdecl LoadBitmapEx(struct IDirectDrawSurface4 *surface, const CHAR *name)
{
	HANDLE v2; // eax@1
	void *v3; // esi@1
	signed int v4; // eax@2
	signed int v5; // edi@2
	signed int result; // eax@4

	v2 = LoadImageA(0, name, 0, 0, 0, 0x2010u);
	v3 = v2;
	if (v2)
	{
		sub_4B8780(surface, v2, 0, 0, 0, 0);
		v5 = v4;
		DeleteObject(v3);
		if (v5)
			Log(1, "LoadBitmap FAILED");
		result = v5;
	}
	else
	{
		Log(1, "LoadBitmap FAILED");
		result = 0x80004005;
	}
	return result;
}

int __cdecl DDCopyBitmap(LPDIRECTDRAWSURFACE4 surface, char *filename)
{
	HMODULE v2; // eax@1
	HANDLE handle; // esi@1
	int result; // eax@3
	int v5; // eax@4
	int v6; // edi@4

	v2 = GetModuleHandleA(0);
	handle = LoadImageA(v2, filename, 0, 0, 0, 0x2000u);
	if (handle || (handle = LoadImageA(0, filename, 0, 0, 0, 0x2010u)) != 0)
	{
		v5 = sub_4B8780(surface, handle, 0, 0, 0, 0);
		if (v5)
			OutputDebugStringA("ddcopybitmap failed\n");
		DeleteObject(handle);
		result = v5;
	}
	else
	{
		OutputDebugStringA("handle is null\n");
		result = 0x80004005;
	}
	return result;
}