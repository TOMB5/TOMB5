#ifndef WINMAIN_H
#define WINMAIN_H
#undef __cplusplus
#include <windows.h>
typedef unsigned int uint;
typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned long ulong;

typedef          char   int8;
typedef   signed char   sint8;
typedef unsigned char   uint8;
typedef          short  int16;
typedef   signed short  sint16;
typedef unsigned short  uint16;
typedef          int    int32;
typedef   signed int    sint32;
typedef unsigned int    uint32;
#define _BYTE  uint8
#define _WORD  uint16
#define _DWORD uint32
#define _QWORD uint64
#define LOBYTE(x)   (*((_BYTE*)&(x)))   // low byte
#define LOWORD(x)   (*((_WORD*)&(x)))   // low word
#define LODWORD(x)  (*((_DWORD*)&(x)))  // low dword
#define HIBYTE(x)   (*((_BYTE*)&(x)+1))
#define HIWORD(x)   (*((_WORD*)&(x)+1))
#define HIDWORD(x)  (*((_DWORD*)&(x)+1))
#define BYTEn(x, n)   (*((_BYTE*)&(x)+n))
#define WORDn(x, n)   (*((_WORD*)&(x)+n))
#define SLOBYTE(x)   (*((int8*)&(x)))
#define SLOWORD(x)   (*((int16*)&(x)))
#define SLODWORD(x)  (*((int32*)&(x)))
#define SHIBYTE(x)   (*((int8*)&(x)+1))
#define SHIWORD(x)   (*((int16*)&(x)+1))
#define SHIDWORD(x)  (*((int32*)&(x)+1))
#define SBYTEn(x, n)   (*((int8*)&(x)+n))
#define SWORDn(x, n)   (*((int16*)&(x)+n))
#define NULL 0

inline void *qmemcpy(void *dst, const void *src, size_t cnt)
{
	char *out = (char *)dst;
	const char *in = (const char *)src;
	while (cnt > 0)
	{
		*out++ = *in++;
		--cnt;
	}
	return dst;
}

int dword_876C48 = 0;
HWND hWnd;
HACCEL hAccTable;
const char* Name = "Tomb Raider Chronicles";
const char* ClassName = "DBLogWindowClass";
const char* WindowName = "DBLog Server";
UINT Msg;
HANDLE hObject;
WNDCLASSA WndClass;
HINSTANCE hinst;
HANDLE hThread;
const char* Caption = "Tomb Raider";
LPARAM dword_E4ACB8;
HANDLE dword_E4ACA4;
UINT dword_E4ACA8;
UINT dword_E4ACAC;
UINT dword_E4ACB0;
uint8 byte_57A098;
uint8 byte_D9AC23;
uint8 byte_D9AC19;
DWORD dword_D9AC30;
const char* String = "UM_DBLOGOUT";
const char* SubKey = "Software\\Core\\DBlog";
const char* ValueName = "CmdLine";
char GameDrive;
BYTE byte_D9ADEC;
DWORD dword_D9AD9C;
DWORD dword_D9AB24;
DWORD dword_D9AB20;
DWORD dword_D9AB28;
DWORD dword_86BD94;
BYTE byte_D9AC2B;
DWORD dword_D9ABFD;
uint32 dword_D9ABF9;
DWORD dword_86B9A4;
DWORD dword_86B9A8;
char aTheIdirectsoun[127] = "The IDirectSound::Initialize method has not been called or has not been called successfully before other methods were called. "; // weak
char aTheRequestComp[36] = "The request completed successfully."; // weak
char aUndefinedError[16] = "Undefined Error"; // weak
char aAnotherApplica[87] = "Another application has a higher priority level, preventing this call from succeeding "; // weak
char aNoSoundDriverI[39] = "No sound driver is available for use. "; // weak
char aTheObjectIsAlr[36] = "The object is already initialized. "; // weak
char aTheBufferMemor[55] = "The buffer memory has been lost and must be restored. "; // weak
char aTheSpecifiedWa[45] = "The specified wave format is not supported. "; // weak
char aTheBufferContr[87] = "The buffer control (volume, pan, and so on) requested by the caller is not available. "; // weak
char aThisFunctionIs[66] = "This function is not valid for the current state of this object. "; // weak
char aTheCallerDoesN[83] = "The caller does not have the priority level required for the function to succeed. "; // weak
char aTheRequestFail[104] = "The request failed because resources, such as a priority level, were already in use by another caller. "; // weak
char aTooManyPrimiti[20] = "Too many primitives"; // weak
char aInvalidMatrix[15] = "Invalid matrix"; // weak
char aConflictingT_0[28] = "Conflicting texture palette"; // weak
char aUnsupportedTex[27] = "Unsupported texture filter"; // weak
char aZbufferNotPres[20] = "ZBuffer not present"; // weak
char aWrongTextureFo[21] = "Wrong texture format"; // weak
char aVertexBufferOp[24] = "Vertex buffer optimised"; // weak
char aVertexBufferLo[21] = "Vertex buffer locked"; // weak
char aVertexBufferCr[28] = "Vertex buffer create failed"; // weak
char aUnsupportedFac[25] = "Unsupported factor value"; // weak
char aUnsupportedC_0[29] = "Unsupported color opertation"; // weak
char aUnsupportedCol[27] = "Unsupported color argument"; // weak
char aUnsupportedA_0[28] = "Unsupported alpha operation"; // weak
char aUnsupportedAlp[27] = "Unsupported alpha argument"; // weak
char aTooManyOperati[20] = "Too many operations"; // weak
char aStencilBufferN[27] = "Stencil buffer not present"; // weak
char aConflictingRen[25] = "Conflicting render state"; // weak
char aConflictingTex[27] = "Conflicting texture filter"; // weak
char aColorkeyAttach[18] = "Colorkey attached"; // weak
char aInvalidVertexF[22] = "Invalid vertex format"; // weak
char aZbufferNeedsVi[27] = "ZBuffer needs video memory"; // weak
char aZbufferNeedsSy[28] = "ZBuffer needs system memory"; // weak
char aViewportHasNoD[23] = "Viewport has no device"; // weak
char aViewportDataNo[22] = "Viewport data not set"; // weak
char aSurfaceNotInVi[28] = "Surface not in video memory"; // weak
char aSceneNotInScen[19] = "Scene not in scene"; // weak
char aSceneInScene[15] = "Scene in scene"; // weak
char aEndSceneFailed[17] = "End scene failed"; // weak
char aBeginSceneFail[19] = "Begin scene failed"; // weak
char aNoViewports[13] = "No viewports"; // weak
char aNotInBeginScen[19] = "Not in begin scene"; // weak
char aNoCurrentViewp[20] = "No current viewport"; // weak
char aLightNotInThis[27] = "Light not in this viewport"; // weak
char aLightHasViewpo[19] = "Light has viewport"; // weak
char aLightSetFailed[17] = "Light set failed"; // weak
char aInvalidPalette[16] = "Invalid palette"; // weak
char aAlreadyInBegin[23] = "Already in begin scene"; // weak
char aMaterialGetDat[25] = "Material get data failed"; // weak
char aTextureUnlockF[22] = "Texture unlock failed"; // weak
char aTextureSwapFai[20] = "Texture swap failed"; // weak
char aTextureNotLock[19] = "Texture not locked"; // weak
char aTextureNoSuppo[19] = "Texture no support"; // weak
char aTextureLockFai[20] = "Texture lock failed"; // weak
char aTextureLoadFai[20] = "Texture load failed"; // weak
char aTextureGetSurf[27] = "Texture get surface failed"; // weak
char aTextureDestroy[23] = "Texture destroy failed"; // weak
char aTextureCreateF[22] = "Texture create failed"; // weak
char aBadTextureSize[17] = "Bad texture size"; // weak
char aSetViewportDat[25] = "Set viewport data failed"; // weak
char aMatrixSetDataF[23] = "Matrix set data failed"; // weak
char aMatrixGetDataF[23] = "Matrix get data failed"; // weak
char aMatrixDestroyF[22] = "Matrix destroy failed"; // weak
char aMatrixCreateFa[21] = "Matrix create failed"; // weak
char aMaterialSetDat[25] = "Material set data failed"; // weak
char aMaterialDestro[24] = "Material destroy failed"; // weak
char aMaterialCreate[23] = "Material create failed"; // weak
char aInvalidVertexT[20] = "Invalid vertex type"; // weak
char aInvalidRampTex[21] = "Invalid ramp texture"; // weak
char aInvalidPrimiti[23] = "Invalid primitive type"; // weak
char aInvalidCurrent[25] = "Invalid current viewport"; // weak
char aInvalidDevice[15] = "Invalid device"; // weak
char aInitFailed[12] = "Init failed"; // weak
char aExecuteUnlockF[22] = "Execute unlock failed"; // weak
char aExecuteNotLock[19] = "Execute not locked"; // weak
char aExecuteLocked[15] = "Execute locked"; // weak
char aExecuteLockFai[20] = "Execute lock failed"; // weak
char aExecuteFailed[15] = "Execute failed"; // weak
char aExecuteDestroy[23] = "Execute destroy failed"; // weak
char aExecuteCreateF[22] = "Execute create failed"; // weak
char aExecuteClipped[23] = "Execute clipped failed"; // weak
char aDeviceAggregat[18] = "Device aggregated"; // weak
char aBadMinorVersio[18] = "Bad minor version"; // weak
char aBadMajorVersio[18] = "Bad major version"; // weak
char aTheVideoPortIs[31] = "The video port is not active. "; // weak
char aAnAttemptIsM_0[77] = "An attempt is made to page unlock a surface with no outstanding page locks. "; // weak
char aTheSurfaceIsAn[84] = "The surface is an optimized surface, but it has not yet been allocated any memory. "; // weak
char aTheDeviceDoesN[49] = "The device does not support optimized surfaces. "; // weak
char aAnAttemptWas_6[116] = "An attempt was made to allocate non-local video memory from a device that does not support non-local video memory. "; // weak
char aAnAttemptWas_5[94] = "An attempt was made to create or set a device window without first setting the focus window. "; // weak
char aThereIsMoreDat[71] = "There is more data available than the specified buffer size can hold. "; // weak
char aTheRequestedOp[91] = "The requested operation could not be performed because the surface was of the wrong type. "; // weak
char aTheDataHasExpi[56] = "The data has expired and is therefore no longer valid. "; // weak
char aSurfacesCreate[97] = "Surfaces created by one DirectDraw device cannot be used directly by another DirectDraw device. "; // weak
char aADeviceContext[114] = "A device context (DC) has already been returned for this surface. Only one DC can be retrieved for each surface. "; // weak
char aAnAttemptToP_0[131] = "An attempt to page unlock a surface failed. Page unlock will not work on a display-memory surface or an emulated primary surface. "; // weak
char aAnAttemptToPag[127] = "An attempt to page lock a surface failed. Page lock will not work on a display-memory surface or an emulated primary surface. "; // weak
char aTheOperation_8[113] = "The operation cannot be carried out because no mipmap capable texture mapping hardware is present or available. "; // weak
char aTheProvidedR_0[77] = "The provided rectangle was not horizontally aligned on a required boundary. "; // weak
char aThisSurfaceCan[77] = "This surface cannot be restored because it was created in a different mode. "; // weak
char aThePreviousBli[101] = "The previous blit operation that is transferring information to or from this surface is incomplete. "; // weak
char aAVerticalBlank[34] = "A vertical blank is in progress. "; // weak
char aTheDisplayIsCu[50] = "The display is currently in an unsupported mode. "; // weak
char aTheBitmaskInTh[75] = "The bitmask in the pixel format requested is not supported by DirectDraw. "; // weak
char aTheFourccForma[61] = "The FourCC format requested is not supported by DirectDraw. "; // weak
char aTheWidthReques[49] = "The width requested by DirectDraw is too large. "; // weak
char aTheSizeRequest[106] = "The size requested by DirectDraw is too large. However, the individual height and width are valid sizes. "; // weak
char aTheHeightReque[50] = "The height requested by DirectDraw is too large. "; // weak
char aTheRequestedSu[40] = "The requested surface is not attached. "; // weak
char aAccessToTheS_1[173] = "Access to the surface is refused because the surface memory is gone. Call the IDirectDrawSurface4::Restore method on this surface to restore the memory associated with it. "; // weak
char aAccessToTheS_0[67] = "Access to the surface is refused because the surface is obscured. "; // weak
char aAccessToTheSur[83] = "Access to the surface is refused because the surface is locked by another thread. "; // weak
char aAnAttemptWas_4[105] = "An attempt was made to make a surface a dependency of another surface to which it is already dependent. "; // weak
char aAnAttemptWas_3[93] = "An attempt was made to attach a surface to another surface to which it is already attached. "; // weak
char aTheRegionPasse[79] = "The region passed to the IDirectDrawClipper::GetClipList method is too small. "; // weak
char aThisProcessHas[53] = "This process has already created a primary surface. "; // weak
char aAccessToThisPa[84] = "Access to this palette is refused because the palette is locked by another thread. "; // weak
char aTheIdirectdr_0[83] = "The IDirectDrawSurface4::GetOverlayPosition method is called on a hidden overlay. "; // weak
char aTheSurfaceBein[56] = "The surface being used is not a palette-based surface. "; // weak
char aAnAttemptIsMad[61] = "An attempt is made to unlock a surface that was not locked. "; // weak
char aAnAttemptHasBe[68] = "An attempt has been made to flip a surface that cannot be flipped. "; // weak
char aAnOverlayCompo[59] = "An overlay component is called for a non-overlay surface. "; // weak
char aThereIsNoHardw[61] = "There is no hardware support for 16- or 256-color palettes. "; // weak
char aNoPaletteObjec[48] = "No palette object is attached to this surface. "; // weak
char aTheIdirectdraw[178] = "The IDirectDrawSurface4::GetOverlayPosition method is called on an overlay that the IDirectDrawSurface4::UpdateOverlay method has not been called on to establish a destination. "; // weak
char aClipperNotific[132] = "Clipper notification requires a window handle, or no window handle has been previously set as the cooperative level window handle. "; // weak
char aSoftwareEmulat[38] = "Software emulation is not available. "; // weak
char aHardwareOnlyDi[101] = "Hardware-only DirectDraw object creation is not possible; the driver does not support any hardware. "; // weak
char aNoDirectdrawRa[61] = "No DirectDraw raster operation (ROP) hardware is available. "; // weak
char aNoDcHasEverBee[47] = "No DC has ever been created for this surface. "; // weak
char aNoDirectdrawcl[64] = "No DirectDrawClipper object is attached to the surface object. "; // weak
char aNoBlitterHardw[33] = "No blitter hardware is present. "; // weak
char aTheSpecifiedSt[45] = "The specified stream contains invalid data. "; // weak
char aThePositionOfT[68] = "The position of the overlay on the destination is no longer legal. "; // weak
char aTheGloballyUni[124] = "The globally unique identifier (GUID) passed to the DirectDrawCreate function is not a valid DirectDraw driver identifier. "; // weak
char aTheSurfaceCann[77] = "The surface cannot be restored because it is an implicitly created surface. "; // weak
char aDirectdrawIsPr[122] = "DirectDraw is prevented from restoring state because the DirectDraw cooperative level window handle has been subclassed. "; // weak
char aTheDirectdrawC[141] = "The DirectDraw cooperative level window handle has already been set. It cannot be reset while the process has surfaces or palettes created. "; // weak
char aAnAttemptWas_2[88] = "An attempt was made to set the cooperative level when it was already set to exclusive. "; // weak
char aADirectdrawObj[89] = "A DirectDraw object representing this driver has already been created for this process. "; // weak
char aNoSourceColorK[54] = "No source color key is specified for this operation. "; // weak
char aAnAttemptWas_1[115] = "An attempt was made to set a clip list for a DirectDrawClipper object that is already monitoring a window handle. "; // weak
char aAccessToThisSu[112] = "Access to this surface is refused because an attempt was made to lock the primary surface without DCI support. "; // weak
char aPrimaryAnd3DSu[90] = "Primary and 3-D surfaces, or surfaces that are implicitly created, cannot be duplicated. "; // weak
char aWindowsCanNotC[254] = "Windows can not create any more device contexts (DCs), or a DC was requested for a palette-indexed surface when the surface had no palette and the display mode was not palette-indexed (in this case DirectDraw cannot select a proper palette into the DC)."; // weak
char aADirectdrawcli[131] = "A DirectDrawClipper object is attached to a source surface that has passed into a call to the IDirectDrawSurface4::BltFast method."; // weak
char aAnAttemptWas_0[75] = "An attempt was made to have more than one color key active on an overlay. "; // weak
char aTheHardwareDoe[49] = "The hardware does not support clipped overlays. "; // weak
char aOperationCould[130] = "Operation could not be carried out because the source and destination rectangles are on the same surface and overlap each other. "; // weak
char aDirectdrawDo_2[74] = "DirectDraw does not have enough display memory to perform the operation. "; // weak
char aTheHardwareNee[77] = "The hardware needed for the requested operation has already been allocated. "; // weak
char aTheOverlaySurf[125] = "The overlay surfaces cannot be z-layered based on the z-order because the hardware does not support z-ordering of overlays. "; // weak
char aTheOperationTo[166] = "The operation to create a z-buffer in display memory or to perform a blit using a z-buffer cannot be carried out because there is no hardware support for z-buffers. "; // weak
char aTheOperation_7[118] = "The operation cannot be carried out because there is no hardware support for vertical blank synchronized operations. "; // weak
char aTheRequestedIt[35] = "The requested item was not found. "; // weak
char aTheOperation_6[98] = "The operation cannot be carried out because no texture-mapping hardware is present or available. "; // weak
char aTheDirectdra_1[127] = "The DirectDrawSurface object is not using an 8-bit color palette and the requested operation requires an 8-bit color palette. "; // weak
char aTheDirectdra_0[137] = "The DirectDrawSurface object is not using a 4-bit color index palette and the requested operation requires a 4-bit color index palette. "; // weak
char aTheDirectdraws[125] = "The DirectDrawSurface object is not using a 4-bit color palette and the requested operation requires a 4-bit color palette. "; // weak
char aTheOperation_5[90] = "The operation cannot be carried out because there is no hardware support for stretching. "; // weak
char aTheOperation_4[91] = "The operation cannot be carried out because no rotation hardware is present or available. "; // weak
char aTheOperation_3[111] = "The operation cannot be carried out because no appropriate raster operation hardware is present or available. "; // weak
char aTheOperation_2[90] = "The operation cannot be carried out because no overlay hardware is present or available. "; // weak
char aTheOperation_1[92] = "The operation cannot be carried out because no mirroring hardware is present or available. "; // weak
char aNoGdiIsPresent[20] = "No GDI is present. "; // weak
char aFlippingVisibl[45] = "Flipping visible surfaces is not supported. "; // weak
char aTheOperationRe[114] = "The operation requires the application to have exclusive mode, but the application does not have exclusive mode. "; // weak
char aDirectdrawSupp[69] = "DirectDraw support is not possible with the current display driver. "; // weak
char aACreateFunctio[96] = "A create function is called without the IDirectDraw4::SetCooperativeLevel method being called. "; // weak
char aTheOperation_0[105] = "The operation cannot be carried out because there is no hardware support for the destination color key. "; // weak
char aTheSurfaceDoes[50] = "The surface does not currently have a color key. "; // weak
char aTheOperationCa[99] = "The operation cannot be carried out because no color-conversion hardware is present or available. "; // weak
char aNoClipListIsAv[28] = "No clip list is available. "; // weak
char aNoAlphaAcceler[105] = "No alpha acceleration hardware is present or available, causing the failure of the requested operation. "; // weak
char aNo3DHardwareOr[42] = "No 3-D hardware or emulation is present. "; // weak
char aOneOrMoreSurfa[82] = "One or more surfaces are locked, causing the failure of the requested operation. "; // weak
char aTheProvidedRec[37] = "The provided rectangle was invalid. "; // weak
char aThePixelFormat[44] = "The pixel format was invalid as specified. "; // weak
char aDirectdrawRece[70] = "DirectDraw received a pointer that was an invalid DirectDraw object. "; // weak
char aDirectdrawDo_1[49] = "DirectDraw does not support the requested mode. "; // weak
char aDirectdrawDo_0[53] = "DirectDraw does not support the provided clip list. "; // weak
char aOneOrMoreOfT_0[83] = "One or more of the capability bits passed to the callback function are incorrect. "; // weak
char aThePrimarySurf[88] = "The primary surface creation request does not match with the existing primary surface. "; // weak
char aTheHeightOfThe[83] = "The height of the provided rectangle is not a multiple of the required alignment. "; // weak
char aAnExceptionWas[72] = "An exception was encountered while performing the requested operation. "; // weak
char aNoSupportIsCur[36] = "No support is currently available. "; // weak
char aASurfaceCann_0[61] = "A surface cannot be detached from another requested surface."; // weak
char aASurfaceCannot[59] = "A surface cannot be attached to another requested surface."; // weak
char aTheObjectHasAl[41] = "The object has already been initialized."; // weak
char aOneOrMoreOfThe[67] = "One or more of the parameters passed to the method are incorrect. "; // weak
char aAnAttemptWasMa[135] = "An attempt was made to call an interface method of a DirectDraw object created by CoCreateInstance before the object was initialized. "; // weak
char aDirectdrawDoes[66] = "DirectDraw does not have enough memory to perform the operation. "; // weak
char aTheObjectDoesN[42] = "The object does not support aggregation. "; // weak
char aTheOperationIs[33] = "The operation is not supported. "; // weak
char aTheRequestedCo[47] = "The requested COM interface is not available. "; // weak
char aThereIsAnUndef[40] = "There is an undefined error condition. "; // weak
char aThisObjectIsAl[35] = "This object is already initialized"; // weak
char aTheApplication[82] = "The application was written for an unsupported prerelease version of DirectInput."; // weak
char aTheObjectCould[117] = "The object could not be created due to an incompatible driver version or mismatched or incomplete driver components."; // weak
char aTheOperatio_11[64] = "The operation cannot be performed while the device is acquired."; // weak
char aAnInvalidParam[132] = "An invalid parameter was passed to the returning function,or the object was not in a state that admitted the function to be called."; // weak
char aTheDinputSubsy[91] = "The DInput subsystem couldn't allocate sufficient memory to complete the caller's request."; // weak
char aThisObjectHasN[37] = "This object has not been initialized"; // weak
char aAccessToTheDev[61] = "Access to the device has been lost.  It must be re-acquired."; // weak
char aTheOperatio_10[65] = "The operation cannot be performed unless the device is acquired."; // weak
char aSenddevicedata[174] = " SendDeviceData failed because more information was requested to be sent than can be sent to the device.  Some devices have restrictions on how much data can be sent to them"; // weak
char aTheRequestedOb[37] = "The requested object does not exist."; // weak
char aAnotherAppHasA[79] = "Another app has a higher priority level, preventing this call from succeeding."; // weak
char aTheOperationCo[76] = " The operation could not be completed because the device is not plugged in."; // weak
char aAnAttemptWas_7[75] = " An attempt was made to modify parameters of an effect while it is playing"; // weak
char aAttemptedToRea[76] = " Attempted to read buffered device data from a device that is not buffered."; // weak
char aTheEffectCould[78] = " The effect could not be downloaded because essential information is missing."; // weak
char aTheOperation_9[90] = " The operation cannot be performed unless the device is acquired in DISCL_EXCLUSIVE mode."; // weak
char aTheDeviceCanno[84] = " The device cannot be reinitialized because there are still effects attached to it."; // weak
char aTheEffectIsNot[30] = "The effect is not downloaded."; // weak
char aNotAllTheReque[55] = "Not all the requested information fit into the buffer."; // weak
char aTheDeviceOrDev[76] = "The device or device instance or effect is not registered with DirectInput."; // weak
char aUnableToIdirec[131] = "Unable to IDirectInputJoyConfig_Acquire because the user does not have sufficient privileges to change the joystick configuration."; // weak
char aTheDeviceIsFul[20] = "The device is full."; // weak
char aThisObjectDoes[41] = "This object does not support aggregation"; // weak
char aTheFunctionCal[50] = "The function called is not supported at this time"; // weak
char aTheSpecifiedIn[55] = "The specified interface is not supported by the object"; // weak
char aAnUndetermined[58] = "An undetermined error occured inside the DInput subsystem"; // weak

extern HWND SendMsg(HWND hWnd, LPARAM lParam);
extern int WinProcMsg();
extern char* WinProcessCommandLine(char *a1);
extern char WinRunCheck(const CHAR *lpName, const CHAR *lpClassName, HANDLE *mutex);
extern HWND WinClose();
extern int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd);
extern HANDLE sub_4DEA40(LPCSTR lpName);
extern LPVOID sub_4DEA20(HANDLE hFileMappingObject);

#endif