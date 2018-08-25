#ifndef _DIRECTX_H
#define _DIRECTX_H
#define DISABLESOFTWARE
#include "INCLUDE.H"
#include "SPECTYPES.H"

#define DXRelease(ptr, desc) {if(ptr){Log(LT_Release, "Released %s @ %x - RefCnt = %d", desc, ptr, ptr->Release());ptr=NULL;}else{Log(LT_Error, "%s Attempt To Release NULL Ptr", desc);}}

#define DXInit(dstruct)			{memset(&dstruct,0,sizeof(dstruct));dstruct.dwSize = sizeof(dstruct);}
#define DXDisplayMode(a,b)		(a)->DDInfo[(b)->nDD].D3DInfo[(b)->nD3D].DisplayMode[(b)->nVMode]  
#define DXD3DGuid(a,b)			(a)->DDInfo[(b)->nDD].D3DInfo[(b)->nD3D].Guid
#define DXD3D(a,b)				(a)->DDInfo[(b)->nDD].D3DInfo[(b)->nD3D]
#define DXD3DTexture(a,b)		(a)->DDInfo[(b)->nDD].D3DInfo[(b)->nD3D].Texture[(b)->nTexture]
#define DXDD(a,b)				(a)->DDInfo[(b)->nDD]

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


#define GENRGB(r, g, b) DXRGB(&App.DeviceInfo, &App.DXConfig, r, g, b)

#ifdef __cplusplus
extern "C" {
#endif
	bool	DXSetCooperativeLevel(LPDIRECTDRAW4 lpDD2, HWND WindowHandle, int Flags);
#ifdef __cplusplus
}
#endif

#define CUR_DD App.DeviceInfo.DDInfo[App.DXConfig.nDD]
#define CUR_D3D CUR_DD.D3DInfo[App.DXConfig.nD3D]
#define CUR_DM CUR_D3D.DisplayMode[App.DXConfig.nVMode]
#define CUR_TEX CUR_D3D.Texture[App.DXConfig.nTexture]

void DXInitialise(DEVICEINFO* DeviceInfo, HWND WindowHandle);
bool DXCreateDirect3D(LPDIRECTDRAW4 lpDD2, LPDIRECT3D3* lpD3D2);
BOOL DXDDCreate(GUID FAR* lpGuid, LPDIRECTDRAW* lpDD);
bool DXSetVideoMode(LPDIRECTDRAW4 lpDD2, int w, int h, int bpp);
bool DXCreateSurface(LPDIRECTDRAW4 lpDD2, DDSURFACEDESC2* ddsd, LPDIRECTDRAWSURFACE4* lpSurface);
bool DXCreateDirect3DDevice(LPDIRECT3D3 lpD3D2, GUID Guid, LPDIRECTDRAWSURFACE4 lpSurface, LPDIRECT3DDEVICE3* lpD3DDevice2);
bool DXCreateViewport(LPDIRECT3D3 lpD3D, LPDIRECT3DDEVICE3 lpD3DDevice, int w, int h, LPDIRECT3DVIEWPORT3* lpViewport);
bool DXCreate(int width, int height, int depth, int flags, WINAPP* app, HWND window, DWORD dwStyle);
void CloseDirectX();
HRESULT DDCopyBitmap(LPDIRECTDRAWSURFACE4 surface, char* filename);
void DXCreateDirectInput(HWND hWnd, HINSTANCE hInstance);
void DXMove(int x, int y);
void AcquireInput(bool acquire);
void DXShowFrame();

#endif