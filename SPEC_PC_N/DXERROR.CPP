#include "STANDARD.H"
#include "GLOBAL.H"
#include "INCLUDE.H"

char* ERR_Describe_DX(HRESULT error)
{
	switch (error)
	{
		// Generic no error
	case 0:
		return "No error.\0";

		// DirectDraw errors
	case DDERR_ALREADYINITIALIZED:
		return "This object is already initialized.\0";
	case DDERR_BLTFASTCANTCLIP:
		return "Return if a clipper object is attached to the source surface passed into a BltFast call.\0";
	case DDERR_CANNOTATTACHSURFACE:
		return "This surface can not be attached to the requested surface.\0";
	case DDERR_CANNOTDETACHSURFACE:
		return "This surface can not be detached from the requested surface.\0";
	case DDERR_CANTCREATEDC:
		return "Windows can not create any more DCs.\0";
	case DDERR_CANTDUPLICATE:
		return "Can't duplicate primary & 3D surfaces, or surfaces that are implicitly created.\0";
	case DDERR_CLIPPERISUSINGHWND:
		return "An attempt was made to set a cliplist for a clipper object that is already monitoring an hwnd.\0";
	case DDERR_COLORKEYNOTSET:
		return "No src color key specified for this operation.\0";
	case DDERR_CURRENTLYNOTAVAIL:
		return "Support is currently not available.\0";
	case DDERR_DIRECTDRAWALREADYCREATED:
		return "A DirectDraw object representing this driver has already been created for this process.\0";
	case DDERR_EXCEPTION:
		return "An exception was encountered while performing the requested operation.\0";
	case DDERR_EXCLUSIVEMODEALREADYSET:
		return "An attempt was made to set the cooperative level when it was already set to exclusive.\0";
	case DDERR_GENERIC:
		return "Generic failure.\0";
	case DDERR_HEIGHTALIGN:
		return "Height of rectangle provided is not a multiple of reqd alignment.\0";
	case DDERR_HWNDALREADYSET:
		return "The CooperativeLevel HWND has already been set. It can not be reset while the process has surfaces or palettes created.\0";
	case DDERR_HWNDSUBCLASSED:
		return "HWND used by DirectDraw CooperativeLevel has been subclassed, this prevents DirectDraw from restoring state.\0";
	case DDERR_IMPLICITLYCREATED:
		return "This surface can not be restored because it is an implicitly created surface.\0";
	case DDERR_INCOMPATIBLEPRIMARY:
		return "Unable to match primary surface creation request with existing primary surface.\0";
	case DDERR_INVALIDCAPS:
		return "One or more of the caps bits passed to the callback are incorrect.\0";
	case DDERR_INVALIDCLIPLIST:
		return "DirectDraw does not support the provided cliplist.\0";
	case DDERR_INVALIDDIRECTDRAWGUID:
		return "The GUID passed to DirectDrawCreate is not a valid DirectDraw driver identifier.\0";
	case DDERR_INVALIDMODE:
		return "DirectDraw does not support the requested mode.\0";
	case DDERR_INVALIDOBJECT:
		return "DirectDraw received a pointer that was an invalid DIRECTDRAW object.\0";
	case DDERR_INVALIDPARAMS:
		return "One or more of the parameters passed to the function are incorrect.\0";
	case DDERR_INVALIDPIXELFORMAT:
		return "The pixel format was invalid as specified.\0";
	case DDERR_INVALIDPOSITION:
		return "Returned when the position of the overlay on the destination is no longer legal for that destination.\0";
	case DDERR_INVALIDRECT:
		return "Rectangle provided was invalid.\0";
	case DDERR_INVALIDSURFACETYPE:
		return "The requested action could not be performed because the surface was of the wrong type.";
	case DDERR_LOCKEDSURFACES:
		return "Operation could not be carried out because one or more surfaces are locked.\0";
	case DDERR_NO3D:
		return "There is no 3D present.\0";
	case DDERR_NOALPHAHW:
		return "Operation could not be carried out because there is no alpha accleration hardware present or available.\0";
	case DDERR_NOBLTHW:
		return "No blitter hardware present.\0";
	case DDERR_NOCLIPLIST:
		return "No cliplist available.\0";
	case DDERR_NOCLIPPERATTACHED:
		return "No clipper object attached to surface object.\0";
	case DDERR_NOCOLORCONVHW:
		return "Operation could not be carried out because there is no color conversion hardware present or available.\0";
	case DDERR_NOCOLORKEY:
		return "Surface doesn't currently have a color key\0";
	case DDERR_NOCOLORKEYHW:
		return "Operation could not be carried out because there is no hardware support of the destination color key.\0";
	case DDERR_NOCOOPERATIVELEVELSET:
		return "Create function called without DirectDraw object method SetCooperativeLevel being called.\0";
	case DDERR_NODC:
		return "No DC was ever created for this surface.\0";
	case DDERR_NODDROPSHW:
		return "No DirectDraw ROP hardware.\0";
	case DDERR_NODIRECTDRAWHW:
		return "A hardware-only DirectDraw object creation was attempted but the driver did not support any hardware.\0";
	case DDERR_NOEMULATION:
		return "Software emulation not available.\0";
	case DDERR_NOEXCLUSIVEMODE:
		return "Operation requires the application to have exclusive mode but the application does not have exclusive mode.\0";
	case DDERR_NOFLIPHW:
		return "Flipping visible surfaces is not supported.\0";
	case DDERR_NOGDI:
		return "There is no GDI present.\0";
	case DDERR_NOHWND:
		return "Clipper notification requires an HWND or no HWND has previously been set as the CooperativeLevel HWND.\0";
	case DDERR_NOMIRRORHW:
		return "Operation could not be carried out because there is no hardware present or available.\0";
	case DDERR_NOOVERLAYDEST:
		return "Returned when GetOverlayPosition is called on an overlay that UpdateOverlay has never been called on to establish a destination.\0";
	case DDERR_NOOVERLAYHW:
		return "Operation could not be carried out because there is no overlay hardware present or available.\0";
	case DDERR_NOPALETTEATTACHED:
		return "No palette object attached to this surface.\0";
	case DDERR_NOPALETTEHW:
		return "No hardware support for 16 or 256 color palettes.\0";
	case DDERR_NORASTEROPHW:
		return "Operation could not be carried out because there is no appropriate raster op hardware present or available.\0";
	case DDERR_NOROTATIONHW:
		return "Operation could not be carried out because there is no rotation hardware present or available.\0";
	case DDERR_NOSTRETCHHW:
		return "Operation could not be carried out because there is no hardware support for stretching.\0";
	case DDERR_NOT4BITCOLOR:
		return "DirectDrawSurface is not in 4 bit color palette and the requested operation requires 4 bit color palette.\0";
	case DDERR_NOT4BITCOLORINDEX:
		return "DirectDrawSurface is not in 4 bit color index palette and the requested operation requires 4 bit color index palette.\0";
	case DDERR_NOT8BITCOLOR:
		return "DirectDrawSurface is not in 8 bit color mode and the requested operation requires 8 bit color.\0";
	case DDERR_NOTAOVERLAYSURFACE:
		return "Returned when an overlay member is called for a non-overlay surface.\0";
	case DDERR_NOTEXTUREHW:
		return "Operation could not be carried out because there is no texture mapping hardware present or available.\0";
	case DDERR_NOTFLIPPABLE:
		return "An attempt has been made to flip a surface that is not flippable.\0";
	case DDERR_NOTFOUND:
		return "Requested item was not found.\0";
	case DDERR_NOTLOCKED:
		return "Surface was not locked.  An attempt to unlock a surface that was not locked at all, or by this process, has been attempted.\0";
	case DDERR_NOTPALETTIZED:
		return "The surface being used is not a palette-based surface.\0";
	case DDERR_NOVSYNCHW:
		return "Operation could not be carried out because there is no hardware support for vertical blank synchronized operations.\0";
	case DDERR_NOZBUFFERHW:
		return "Operation could not be carried out because there is no hardware support for zbuffer blitting.\0";
	case DDERR_NOZOVERLAYHW:
		return "Overlay surfaces could not be z layered based on their BltOrder because the hardware does not support z layering of overlays.\0";
	case DDERR_OUTOFCAPS:
		return "The hardware needed for the requested operation has already been allocated.\0";
	case DDERR_OUTOFMEMORY:
		return "DirectDraw does not have enough memory to perform the operation.\0";
	case DDERR_OUTOFVIDEOMEMORY:
		return "DirectDraw does not have enough memory to perform the operation.\0";
	case DDERR_OVERLAYCANTCLIP:
		return "The hardware does not support clipped overlays.\0";
	case DDERR_OVERLAYCOLORKEYONLYONEACTIVE:
		return "Can only have ony color key active at one time for overlays.\0";
	case DDERR_OVERLAYNOTVISIBLE:
		return "Returned when GetOverlayPosition is called on a hidden overlay.\0";
	case DDERR_PALETTEBUSY:
		return "Access to this palette is being refused because the palette is already locked by another thread.\0";
	case DDERR_PRIMARYSURFACEALREADYEXISTS:
		return "This process already has created a primary surface.\0";
	case DDERR_REGIONTOOSMALL:
		return "Region passed to Clipper::GetClipList is too small.\0";
	case DDERR_SURFACEALREADYATTACHED:
		return "This surface is already attached to the surface it is being attached to.\0";
	case DDERR_SURFACEALREADYDEPENDENT:
		return "This surface is already a dependency of the surface it is being made a dependency of.\0";
	case DDERR_SURFACEBUSY:
		return "Access to this surface is being refused because the surface is already locked by another thread.\0";
	case DDERR_SURFACEISOBSCURED:
		return "Access to surface refused because the surface is obscured.\0";
	case DDERR_SURFACELOST:
		return "Access to this surface is being refused because the surface memory is gone. The DirectDrawSurface object representing this surface should have Restore called on it.\0";
	case DDERR_SURFACENOTATTACHED:
		return "The requested surface is not attached.\0";
	case DDERR_TOOBIGHEIGHT:
		return "Height requested by DirectDraw is too large.\0";
	case DDERR_TOOBIGSIZE:
		return "Size requested by DirectDraw is too large, but the individual height and width are OK.\0";
	case DDERR_TOOBIGWIDTH:
		return "Width requested by DirectDraw is too large.\0";
	case DDERR_UNSUPPORTED:
		return "Action not supported.\0";
	case DDERR_UNSUPPORTEDFORMAT:
		return "FOURCC format requested is unsupported by DirectDraw.\0";
	case DDERR_UNSUPPORTEDMASK:
		return "Bitmask in the pixel format requested is unsupported by DirectDraw.\0";
	case DDERR_VERTICALBLANKINPROGRESS:
		return "Vertical blank is in progress.\0";
	case DDERR_WASSTILLDRAWING:
		return "Informs DirectDraw that the previous Blt which is transfering information to or from this Surface is incomplete.\0";
	case DDERR_WRONGMODE:
		return "This surface can not be restored because it was created in a different mode.\0";
	case DDERR_XALIGN:
		return "Rectangle provided was not horizontally aligned on required boundary.\0";

		// Direct3D errors
	case D3DERR_BADMAJORVERSION:
		return "D3DERR_BADMAJORVERSION\0";
	case D3DERR_BADMINORVERSION:
		return "D3DERR_BADMINORVERSION\0";
	case D3DERR_EXECUTE_LOCKED:
		return "D3DERR_EXECUTE_LOCKED\0";
	case D3DERR_EXECUTE_NOT_LOCKED:
		return "D3DERR_EXECUTE_NOT_LOCKED\0";
	case D3DERR_EXECUTE_CREATE_FAILED:
		return "D3DERR_EXECUTE_CREATE_FAILED\0";
	case D3DERR_EXECUTE_DESTROY_FAILED:
		return "D3DERR_EXECUTE_DESTROY_FAILED\0";
	case D3DERR_EXECUTE_LOCK_FAILED:
		return "D3DERR_EXECUTE_LOCK_FAILED\0";
	case D3DERR_EXECUTE_UNLOCK_FAILED:
		return "D3DERR_EXECUTE_UNLOCK_FAILED\0";
	case D3DERR_EXECUTE_FAILED:
		return "D3DERR_EXECUTE_FAILED\0";
	case D3DERR_EXECUTE_CLIPPED_FAILED:
		return "D3DERR_EXECUTE_CLIPPED_FAILED\0";
	case D3DERR_TEXTURE_NO_SUPPORT:
		return "D3DERR_TEXTURE_NO_SUPPORT\0";
	case D3DERR_TEXTURE_NOT_LOCKED:
		return "D3DERR_TEXTURE_NOT_LOCKED\0";
	case D3DERR_TEXTURE_LOCKED:
		return "D3DERR_TEXTURELOCKED\0";
	case D3DERR_TEXTURE_CREATE_FAILED:
		return "D3DERR_TEXTURE_CREATE_FAILED\0";
	case D3DERR_TEXTURE_DESTROY_FAILED:
		return "D3DERR_TEXTURE_DESTROY_FAILED\0";
	case D3DERR_TEXTURE_LOCK_FAILED:
		return "D3DERR_TEXTURE_LOCK_FAILED\0";
	case D3DERR_TEXTURE_UNLOCK_FAILED:
		return "D3DERR_TEXTURE_UNLOCK_FAILED\0";
	case D3DERR_TEXTURE_LOAD_FAILED:
		return "D3DERR_TEXTURE_LOAD_FAILED\0";
	case D3DERR_MATRIX_CREATE_FAILED:
		return "D3DERR_MATRIX_CREATE_FAILED\0";
	case D3DERR_MATRIX_DESTROY_FAILED:
		return "D3DERR_MATRIX_DESTROY_FAILED\0";
	case D3DERR_MATRIX_SETDATA_FAILED:
		return "D3DERR_MATRIX_SETDATA_FAILED\0";
	case D3DERR_SETVIEWPORTDATA_FAILED:
		return "D3DERR_SETVIEWPORTDATA_FAILED\0";
	case D3DERR_MATERIAL_CREATE_FAILED:
		return "D3DERR_MATERIAL_CREATE_FAILED\0";
	case D3DERR_MATERIAL_DESTROY_FAILED:
		return "D3DERR_MATERIAL_DESTROY_FAILED\0";
	case D3DERR_MATERIAL_SETDATA_FAILED:
		return "D3DERR_MATERIAL_SETDATA_FAILED\0";
	case D3DERR_LIGHT_SET_FAILED:
		return "D3DERR_LIGHT_SET_FAILED\0";

		// DirectSound errors
	case DSERR_ALLOCATED:
		return "The call failed because resources (such as a priority level) were already being used by another caller.\0";
	case DSERR_CONTROLUNAVAIL:
		return "The control (vol,pan,etc.) requested by the caller is not available.\0";
	case DSERR_INVALIDCALL:
		return "This call is not valid for the current state of this object.\0";
	case DSERR_PRIOLEVELNEEDED:
		return "The caller does not have the priority level required for the function to succeed.\0";
	case DSERR_BADFORMAT:
		return "The specified WAVE format is not supported.\0";
	case DSERR_NODRIVER:
		return "No sound driver is available for use.\0";
	case DSERR_ALREADYINITIALIZED:
		return "This object is already initialized.\0";
	case DSERR_NOAGGREGATION:
		return "This object does not support aggregation.\0";
	case DSERR_BUFFERLOST:
		return "The buffer memory has been lost, and must be Restored.\0";
	case DSERR_OTHERAPPHASPRIO:
		return "Another app has a higher priority level, preventing this call from succeeding.\0";
	case DSERR_UNINITIALIZED:
		return "The Initialize() member on the Direct Sound Object has not been called or called successfully before calls to other members.\0";
		// todo add others
	case DIERR_INSUFFICIENTPRIVS:
		return "Unable to IDirectInputJoyConfig_Acquire because the user does not have sufficient privileges to change the joystick configuration.\0";
	case DIERR_DEVICEFULL:
		return "The device is full.\0";
	case DIERR_MOREDATA:
		return "Not all the requested information fit into the buffer.\0";
	case DIERR_NOTDOWNLOADED:
		return "The effect is not downloaded.\0";
	case DIERR_HASEFFECTS:
		return "The device cannot be reinitialized because there are still effects attached to it.\0";
	case DIERR_NOTEXCLUSIVEACQUIRED:
		return "The operation cannot be performed unless the device is acquired in DISCL_EXCLUSIVE mode.\0";
	case DIERR_INCOMPLETEEFFECT:
		return "The effect could not be downloaded because essential information is missing.  For example, no axes have been associated with the effect, or no type-specific information has been created.\0";
	case DIERR_NOTBUFFERED:
		return "Attempted to read buffered device data from a device that is not buffered.\0";
	case DIERR_EFFECTPLAYING:
		return "An attempt was made to modify parameters of an effect while it is playing.  Not all hardware devices support altering the parameters of an effect while it is playing.\0";

	default:
		Log(LT_Error, "HRESULT=%08x", error);
		return "Unrecognized error value.\0";
	}
}

/*** WELL temporary error shit ***/
local char* LaszInitErrs[] =
{
	"OK",

	"PreferredAdapterNotFound",
	"CantCreateWindow",
	"CantCreateDirectDraw",
	"CantInitRenderer",
	"CantCreateDirectInput",
	"CantCreateKeyboardDevice",
	"CantSetKBCooperativeLevel",
	"CantSetKBDataFormat",
	"CantAcquireKeyboard",
	"CantSetDSCooperativeLevel",

	"DD_SetExclusiveMode",
	"DD_ClearExclusiveMode",
	"SetDisplayMode",
	"CreateScreenBuffers",
	"GetBackBuffer",
	"CreatePalette",
	"SetPalette",
	"CreatePrimarySurface",
	"CreateBackBuffer",
	"CreateClipper",
	"SetClipperHWnd",
	"SetClipper",
	"CreateZBuffer",
	"AttachZBuffer",
	"CreateRenderBuffer",
	"CreatePictureBuffer",
	"D3D_Create",
	"CreateDevice",
	"CreateViewport",
	"AddViewport",
	"SetViewport2",
	"SetCurrentViewport",

	"ClearRenderBuffer",
	"UpdateRenderInfo",
	"GetThirdBuffer",

	"GoFullScreen",
	"GoWindowed",

	"WrongBitDepth",
	"GetPixelFormat",
	"GetDisplayMode"
};

char* ERR_Describe_Init(int nError)
{
	return LaszInitErrs[nError];
}
