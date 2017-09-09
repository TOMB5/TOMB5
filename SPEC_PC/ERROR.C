#include "ERROR.H"
#include "SPECIFIC.H"


char *__cdecl sub_401C94(signed int a1)
{
	char *result; // eax@16

	if (a1 > -2005532081)
	{
		if (a1 > -2005531929)
		{
			if (a1 > -2005530624)
			{
				if (a1 > -2005530590)
				{
					if (a1 <= -2005401500)
					{
						if (a1 == -2005401500)
							return "The specified wave format is not supported. ";
						if (a1 > -2005401590)
						{
							if (a1 == -2005401570)
								return "The buffer control (volume, pan, and so on) requested by the caller is not available. ";
							if (a1 == -2005401550)
								return "This function is not valid for the current state of this object. ";
							if (a1 == -2005401530)
								return "The caller does not have the priority level required for the function to succeed. ";
						}
						else
						{
							if (a1 == -2005401590)
								return "The request failed because resources, such as a priority level, were already in use by another caller. ";
							if (a1 == -2005530589)
								return "Too many primitives";
							if (a1 == -2005530588)
								return "Invalid matrix";
							if (a1 == -2005530586)
								return "Conflicting texture palette";
						}
						return "Undefined Error";
					}
					if (a1 <= -2005401440)
					{
						if (a1 == -2005401440)
							return "Another application has a higher priority level, preventing this call from succeeding ";
						if (a1 == -2005401480)
							return "No sound driver is available for use. ";
						if (a1 == -2005401470)
							return "The object is already initialized. ";
						if (a1 == -2005401450)
							return "The buffer memory has been lost and must be restored. ";
						return "Undefined Error";
					}
					if (a1 == -2005401430)
					{
						result = "The IDirectSound::Initialize method has not been called or has not been called successfully before other methods were called. ";
					}
					else
					{
						if (a1)
							return "Undefined Error";
						result = "The request completed successfully.";
					}
				}
				else if (a1 == -2005530590)
				{
					result = "Unsupported texture filter";
				}
				else
				{
					switch (a1)
					{
					case -2005530622:
						result = "Colorkey attached";
						break;
					case -2005530594:
						result = "Conflicting texture filter";
						break;
					case -2005530591:
						result = "Conflicting render state";
						break;
					case -2005530601:
						result = "Stencil buffer not present";
						break;
					case -2005530595:
						result = "Too many operations";
						break;
					case -2005530596:
						result = "Unsupported alpha argument";
						break;
					case -2005530597:
						result = "Unsupported alpha operation";
						break;
					case -2005530598:
						result = "Unsupported color argument";
						break;
					case -2005530599:
						result = "Unsupported color opertation";
						break;
					case -2005530593:
						result = "Unsupported factor value";
						break;
					case -2005530611:
						result = "Vertex buffer create failed";
						break;
					case -2005530610:
						result = "Vertex buffer locked";
						break;
					case -2005530612:
						result = "Vertex buffer optimised";
						break;
					case -2005530600:
						result = "Wrong texture format";
						break;
					case -2005530602:
						result = "ZBuffer not present";
						break;
					default:
						return "Undefined Error";
					}
				}
			}
			else if (a1 == -2005530624)
			{
				result = "Invalid vertex format";
			}
			else
			{
				switch (a1)
				{
				case -2005531902:
					result = "Already in begin scene";
					break;
				case -2005531928:
					result = "Invalid palette";
					break;
				case -2005531922:
					result = "Light set failed";
					break;
				case -2005531921:
					result = "Light has viewport";
					break;
				case -2005531920:
					result = "Light not in this viewport";
					break;
				case -2005531897:
					result = "No current viewport";
					break;
				case -2005531901:
					result = "Not in begin scene";
					break;
				case -2005531900:
					result = "No viewports";
					break;
				case -2005531910:
					result = "Begin scene failed";
					break;
				case -2005531909:
					result = "End scene failed";
					break;
				case -2005531912:
					result = "Scene in scene";
					break;
				case -2005531911:
					result = "Scene not in scene";
					break;
				case -2005531925:
					result = "Surface not in video memory";
					break;
				case -2005531899:
					result = "Viewport data not set";
					break;
				case -2005531898:
					result = "Viewport has no device";
					break;
				case -2005531927:
					result = "ZBuffer needs system memory";
					break;
				case -2005531926:
					result = "ZBuffer needs video memory";
					break;
				default:
					return "Undefined Error";
				}
			}
		}
		else if (a1 == -2005531929)
		{
			result = "Material get data failed";
		}
		else
		{
			switch (a1)
			{
			case -2005532032:
				result = "An attempt to page lock a surface failed. Page lock will not work on a display-memory surface or an emulated primary surface. ";
				break;
			case -2005532012:
				result = "An attempt to page unlock a surface failed. Page unlock will not work on a display-memory surface or an emulated primary surface. ";
				break;
			case -2005532052:
				result = "A device context (DC) has already been returned for this surface. Only one DC can be retrieved for each surface. ";
				break;
			case -2005531973:
				result = "Surfaces created by one DirectDraw device cannot be used directly by another DirectDraw device. ";
				break;
			case -2005531981:
				result = "The data has expired and is therefore no longer valid. ";
				break;
			case -2005532080:
				result = "The requested operation could not be performed because the surface was of the wrong type. ";
				break;
			case -2005531982:
				result = "There is more data available than the specified buffer size can hold. ";
				break;
			case -2005532070:
				result = "An attempt was made to create or set a device window without first setting the focus window. ";
				break;
			case -2005532042:
				result = "An attempt was made to allocate non-local video memory from a device that does not support non-local video memory. ";
				break;
			case -2005532072:
				result = "The device does not support optimized surfaces. ";
				break;
			case -2005532071:
				result = "The surface is an optimized surface, but it has not yet been allocated any memory. ";
				break;
			case -2005531992:
				result = "An attempt is made to page unlock a surface with no outstanding page locks. ";
				break;
			case -2005531977:
				result = "The video port is not active. ";
				break;
			case -2005531972:
				result = "Bad major version";
				break;
			case -2005531971:
				result = "Bad minor version";
				break;
			case -2005531965:
				result = "Device aggregated";
				break;
			case -2005531955:
				result = "Execute clipped failed";
				break;
			case -2005531962:
				result = "Execute create failed";
				break;
			case -2005531961:
				result = "Execute destroy failed";
				break;
			case -2005531956:
				result = "Execute failed";
				break;
			case -2005531960:
				result = "Execute lock failed";
				break;
			case -2005531958:
				result = "Execute locked";
				break;
			case -2005531957:
				result = "Execute not locked";
				break;
			case -2005531959:
				result = "Execute unlock failed";
				break;
			case -2005531966:
				result = "Init failed";
				break;
			case -2005531967:
				result = "Invalid device";
				break;
			case -2005531937:
				result = "Invalid current viewport";
				break;
			case -2005531936:
				result = "Invalid primitive type";
				break;
			case -2005531933:
				result = "Invalid ramp texture";
				break;
			case -2005531935:
				result = "Invalid vertex type";
				break;
			case -2005531932:
				result = "Material create failed";
				break;
			case -2005531931:
				result = "Material destroy failed";
				break;
			case -2005531930:
				result = "Material set data failed";
				break;
			case -2005531942:
				result = "Matrix create failed";
				break;
			case -2005531941:
				result = "Matrix destroy failed";
				break;
			case -2005531939:
				result = "Matrix get data failed";
				break;
			case -2005531940:
				result = "Matrix set data failed";
				break;
			case -2005531938:
				result = "Set viewport data failed";
				break;
			case -2005531934:
				result = "Bad texture size";
				break;
			case -2005531951:
				result = "Texture create failed";
				break;
			case -2005531950:
				result = "Texture destroy failed";
				break;
			case -2005531943:
				result = "Texture get surface failed";
				break;
			case -2005531947:
				result = "Texture load failed";
				break;
			case -2005531949:
			case -2005531945:
				result = "Texture lock failed";
				break;
			case -2005531952:
				result = "Texture no support";
				break;
			case -2005531944:
				result = "Texture not locked";
				break;
			case -2005531946:
				result = "Texture swap failed";
				break;
			case -2005531948:
				result = "Texture unlock failed";
				break;
			default:
				return "Undefined Error";
			}
		}
	}
	else
	{
		if (a1 == -2005532081)
			return "The operation cannot be carried out because no mipmap capable texture mapping hardware is present or available. ";
		if (a1 > -2005532288)
		{
			switch (a1)
			{
			case -2005532098:
				result = "A DirectDrawClipper object is attached to a source surface that has passed into a call to the IDirectDrawSurface4::BltFast method.";
				break;
			case -2005532087:
				result = "Windows can not create any more device contexts (DCs), or a DC was requested for a palette-indexed surface when the surface had no palette and the display mode was not palette-indexed (in this case DirectDraw cannot select a proper palette into the DC).";
				break;
			case -2005532089:
				result = "Primary and 3-D surfaces, or surfaces that are implicitly created, cannot be duplicated. ";
				break;
			case -2005532237:
				result = "Access to this surface is refused because an attempt was made to lock the primary surface without DCI support. ";
				break;
			case -2005532105:
				result = "An attempt was made to set a clip list for a DirectDrawClipper object that is already monitoring a window handle. ";
				break;
			case -2005532272:
				result = "No source color key is specified for this operation. ";
				break;
			case -2005532110:
				result = "A DirectDraw object representing this driver has already been created for this process. ";
				break;
			case -2005532091:
				result = "An attempt was made to set the cooperative level when it was already set to exclusive. ";
				break;
			case -2005532101:
				result = "The DirectDraw cooperative level window handle has already been set. It cannot be reset while the process has surfaces or palettes created. ";
				break;
			case -2005532102:
				result = "DirectDraw is prevented from restoring state because the DirectDraw cooperative level window handle has been subclassed. ";
				break;
			case -2005532084:
				result = "The surface cannot be restored because it is an implicitly created surface. ";
				break;
			case -2005532111:
				result = "The globally unique identifier (GUID) passed to the DirectDrawCreate function is not a valid DirectDraw driver identifier. ";
				break;
			case -2005532093:
				result = "The position of the overlay on the destination is no longer legal. ";
				break;
			case -2005532151:
				result = "The specified stream contains invalid data. ";
				break;
			case -2005532097:
				result = "No blitter hardware is present. ";
				break;
			case -2005532104:
				result = "No DirectDrawClipper object is attached to the surface object. ";
				break;
			case -2005532086:
				result = "No DC has ever been created for this surface. ";
				break;
			case -2005532096:
				result = "No DirectDraw raster operation (ROP) hardware is available. ";
				break;
			case -2005532109:
				result = "Hardware-only DirectDraw object creation is not possible; the driver does not support any hardware. ";
				break;
			case -2005532107:
				result = "Software emulation is not available. ";
				break;
			case -2005532103:
				result = "Clipper notification requires a window handle, or no window handle has been previously set as the cooperative level window handle. ";
				break;
			case -2005532094:
				result = "The IDirectDrawSurface4::GetOverlayPosition method is called on an overlay that the IDirectDrawSurface4::UpdateOverlay method has not been called on to establish a destination. ";
				break;
			case -2005532100:
				result = "No palette object is attached to this surface. ";
				break;
			case -2005532099:
				result = "There is no hardware support for 16- or 256-color palettes. ";
				break;
			case -2005532092:
				result = "An overlay component is called for a non-overlay surface. ";
				break;
			case -2005532090:
				result = "An attempt has been made to flip a surface that cannot be flipped. ";
				break;
			case -2005532088:
				result = "An attempt is made to unlock a surface that was not locked. ";
				break;
			case -2005532083:
				result = "The surface being used is not a palette-based surface. ";
				break;
			case -2005532095:
				result = "The IDirectDrawSurface4::GetOverlayPosition method is called on a hidden overlay. ";
				break;
			case -2005532285:
				result = "Access to this palette is refused because the palette is locked by another thread. ";
				break;
			case -2005532108:
				result = "This process has already created a primary surface. ";
				break;
			case -2005532106:
				result = "The region passed to the IDirectDrawClipper::GetClipList method is too small. ";
				break;
			case -2005532262:
				result = "An attempt was made to attach a surface to another surface to which it is already attached. ";
				break;
			case -2005532252:
				result = "An attempt was made to make a surface a dependency of another surface to which it is already dependent. ";
				break;
			case -2005532242:
				result = "Access to the surface is refused because the surface is locked by another thread. ";
				break;
			case -2005532232:
				result = "Access to the surface is refused because the surface is obscured. ";
				break;
			case -2005532222:
				result = "Access to the surface is refused because the surface memory is gone. Call the IDirectDrawSurface4::Restore method on this surface to restore the memory associated with it. ";
				break;
			case -2005532212:
				result = "The requested surface is not attached. ";
				break;
			case -2005532202:
				result = "The height requested by DirectDraw is too large. ";
				break;
			case -2005532192:
				result = "The size requested by DirectDraw is too large. However, the individual height and width are valid sizes. ";
				break;
			case -2005532182:
				result = "The width requested by DirectDraw is too large. ";
				break;
			case -2005532162:
				result = "The FourCC format requested is not supported by DirectDraw. ";
				break;
			case -2005532152:
				result = "The bitmask in the pixel format requested is not supported by DirectDraw. ";
				break;
			case -2005532082:
				result = "The display is currently in an unsupported mode. ";
				break;
			case -2005532135:
				result = "A vertical blank is in progress. ";
				break;
			case -2005532132:
				result = "The previous blit operation that is transferring information to or from this surface is incomplete. ";
				break;
			case -2005532085:
				result = "This surface cannot be restored because it was created in a different mode. ";
				break;
			case -2005532112:
				result = "The provided rectangle was not horizontally aligned on a required boundary. ";
				break;
			default:
				return "Undefined Error";
			}
		}
		else
		{
			if (a1 == -2005532288)
				return "An attempt was made to have more than one color key active on an overlay. ";
			if (a1 > -2005532462)
			{
				switch (a1)
				{
				case -2005532457:
					result = "The surface does not currently have a color key. ";
					break;
				case -2005532452:
					result = "The operation cannot be carried out because there is no hardware support for the destination color key. ";
					break;
				case -2005532460:
					result = "A create function is called without the IDirectDraw4::SetCooperativeLevel method being called. ";
					break;
				case -2005532450:
					result = "DirectDraw support is not possible with the current display driver. ";
					break;
				case -2005532447:
					result = "The operation requires the application to have exclusive mode, but the application does not have exclusive mode. ";
					break;
				case -2005532442:
					result = "Flipping visible surfaces is not supported. ";
					break;
				case -2005532432:
					result = "No GDI is present. ";
					break;
				case -2005532422:
					result = "The operation cannot be carried out because no mirroring hardware is present or available. ";
					break;
				case -2005532412:
					result = "The operation cannot be carried out because no overlay hardware is present or available. ";
					break;
				case -2005532392:
					result = "The operation cannot be carried out because no appropriate raster operation hardware is present or available. ";
					break;
				case -2005532382:
					result = "The operation cannot be carried out because no rotation hardware is present or available. ";
					break;
				case -2005532362:
					result = "The operation cannot be carried out because there is no hardware support for stretching. ";
					break;
				case -2005532356:
					result = "The DirectDrawSurface object is not using a 4-bit color palette and the requested operation requires a 4-bit color palette. ";
					break;
				case -2005532355:
					result = "The DirectDrawSurface object is not using a 4-bit color index palette and the requested operation requires a 4-bit color index palette. ";
					break;
				case -2005532352:
					result = "The DirectDrawSurface object is not using an 8-bit color palette and the requested operation requires an 8-bit color palette. ";
					break;
				case -2005532342:
					result = "The operation cannot be carried out because no texture-mapping hardware is present or available. ";
					break;
				case -2005532417:
					result = "The requested item was not found. ";
					break;
				case -2005532337:
					result = "The operation cannot be carried out because there is no hardware support for vertical blank synchronized operations. ";
					break;
				case -2005532332:
					result = "The operation to create a z-buffer in display memory or to perform a blit using a z-buffer cannot be carried out because there is no hardware support for z-buffers. ";
					break;
				case -2005532322:
					result = "The overlay surfaces cannot be z-layered based on the z-order because the hardware does not support z-ordering of overlays. ";
					break;
				case -2005532312:
					result = "The hardware needed for the requested operation has already been allocated. ";
					break;
				case -2005532292:
					result = "DirectDraw does not have enough display memory to perform the operation. ";
					break;
				case -2005532402:
					result = "Operation could not be carried out because the source and destination rectangles are on the same surface and overlap each other. ";
					break;
				case -2005532290:
					result = "The hardware does not support clipped overlays. ";
					break;
				default:
					return "Undefined Error";
				}
			}
			else
			{
				if (a1 == -2005532462)
					return "The operation cannot be carried out because no color-conversion hardware is present or available. ";
				if (a1 > (signed int)0x8876005A)
				{
					switch (a1)
					{
					case -2005532577:
						result = "The primary surface creation request does not match with the existing primary surface. ";
						break;
					case -2005532572:
						result = "One or more of the capability bits passed to the callback function are incorrect. ";
						break;
					case -2005532562:
						result = "DirectDraw does not support the provided clip list. ";
						break;
					case -2005532552:
						result = "DirectDraw does not support the requested mode. ";
						break;
					case -2005532542:
						result = "DirectDraw received a pointer that was an invalid DirectDraw object. ";
						break;
					case -2005532527:
						result = "The pixel format was invalid as specified. ";
						break;
					case -2005532522:
						result = "The provided rectangle was invalid. ";
						break;
					case -2005532512:
						result = "One or more surfaces are locked, causing the failure of the requested operation. ";
						break;
					case -2005532502:
						result = "No 3-D hardware or emulation is present. ";
						break;
					case -2005532492:
						result = "No alpha acceleration hardware is present or available, causing the failure of the requested operation. ";
						break;
					case -2005532467:
						result = "No clip list is available. ";
						break;
					default:
						return "Undefined Error";
					}
				}
				else
				{
					if (a1 == 0x8876005A)
						return "The height of the provided rectangle is not a multiple of the required alignment. ";
					if (a1 <= (signed int)0x80070057)
					{
						if (a1 == 0x80070057)
							return "One or more of the parameters passed to the method are incorrect. ";
						if (a1 > (signed int)0x80040110)
						{
							if (a1 == 0x800401F0)
								return "An attempt was made to call an interface method of a DirectDraw object created by CoCreateInstance before the object was initialized. ";
							if (a1 == 0x8007000E)
								return "DirectDraw does not have enough memory to perform the operation. ";
						}
						else
						{
							if (a1 == 0x80040110)
								return "The object does not support aggregation. ";
							if (a1 == 0x80004001)
								return "The operation is not supported. ";
							if (a1 == 0x80004002)
								return "The requested COM interface is not available. ";
							if (a1 == 0x80004005)
								return "There is an undefined error condition. ";
						}
						return "Undefined Error";
					}
					switch (a1)
					{
					case 0x88760005:
						result = "The object has already been initialized.";
						break;
					case 0x8876000A:
						result = "A surface cannot be attached to another requested surface.";
						break;
					case 0x88760014:
						result = "A surface cannot be detached from another requested surface.";
						break;
					case 0x88760028:
						result = "No support is currently available. ";
						break;
					case 0x88760037:
						result = "An exception was encountered while performing the requested operation. ";
						break;
					default:
						return "Undefined Error";
					}
				}
			}
		}
	}
	return result;
}

char *__cdecl sub_401168(signed int a1)
{
	char *result; // eax@10

	if (a1 > -2147220983)
	{
		if (a1 <= -2147024809)
		{
			if (a1 == -2147024809)
				return "An invalid parameter was passed to the returning function,or the object was not in a state that admitted the function to be called.";
			if (a1 > -2147024884)
			{
				if (a1 == -2147024882)
					return "The DInput subsystem couldn't allocate sufficient memory to complete the caller's request.";
				if (a1 == -2147024875)
					return "This object has not been initialized";
				if (a1 == -2147024866)
					return "Access to the device has been lost.  It must be re-acquired.";
			}
			else
			{
				if (a1 == -2147024884)
					return "The operation cannot be performed unless the device is acquired.";
				if (a1 == -2147220982)
					return " SendDeviceData failed because more information was requested to be sent than can be sent to the device.  Some devices have restrictions on how much data can be sent to them";
				if (a1 == -2147024894)
					return "The requested object does not exist.";
				if (a1 == -2147024891)
					return "Another app has a higher priority level, preventing this call from succeeding.";
			}
			return "Undefined Error";
		}
		if (a1 > -2147023743)
		{
			if (a1 == -2147023649)
			{
				result = "This object is already initialized";
			}
			else
			{
				if (a1)
					return "Undefined Error";
				result = "The request completed successfully.";
			}
		}
		else
		{
			if (a1 != -2147023743)
			{
				if (a1 == -2147024777)
					return "The object could not be created due to an incompatible driver version or mismatched or incomplete driver components.";
				if (a1 == -2147024726)
					return "The operation cannot be performed while the device is acquired.";
				if (a1 != -2147023746)
					return "Undefined Error";
			}
			result = "The application was written for an unsupported prerelease version of DirectInput.";
		}
	}
	else
	{
		if (a1 == -2147220983)
			return " The operation could not be completed because the device is not plugged in.";
		if (a1 <= -2147220990)
		{
			if (a1 == -2147220990)
				return "Not all the requested information fit into the buffer.";
			if (a1 > -2147221232)
			{
				if (a1 == -2147221164)
					return "The device or device instance or effect is not registered with DirectInput.";
				if (a1 == -2147220992)
					return "Unable to IDirectInputJoyConfig_Acquire because the user does not have sufficient privileges to change the joystick configuration.";
				if (a1 == -2147220991)
					return "The device is full.";
			}
			else
			{
				if (a1 == -2147221232)
					return "This object does not support aggregation";
				if (a1 == -2147467263)
					return "The function called is not supported at this time";
				if (a1 == -2147467262)
					return "The specified interface is not supported by the object";
				if (a1 == -2147467259)
					return "An undetermined error occured inside the DInput subsystem";
			}
			return "Undefined Error";
		}
		switch (a1)
		{
		case -2147220989:
			result = "The effect is not downloaded.";
			break;
		case -2147220988:
			result = " The device cannot be reinitialized because there are still effects attached to it.";
			break;
		case -2147220987:
			result = " The operation cannot be performed unless the device is acquired in DISCL_EXCLUSIVE mode.";
			break;
		case -2147220986:
			result = " The effect could not be downloaded because essential information is missing.";
			break;
		case -2147220985:
			result = " Attempted to read buffered device data from a device that is not buffered.";
			break;
		case -2147220984:
			result = " An attempt was made to modify parameters of an effect while it is playing";
			break;
		default:
			return "Undefined Error";
		}
	}
	return result;
}



signed int __cdecl sub_40211C(int a1)
{
	signed int result; // eax@2
	char* v2; // eax@3

	if (a1 < 0)
	{
		v2 = sub_401168(a1);
		sub_4DEB10(1, "ERROR : %s", v2);
		result = a1;
	}
	else
	{
		result = 0;
	}
	return result;
}

signed int __cdecl sub_40179E(int a1)
{
	signed int result; // eax@2
	char* v2; // eax@3

	if (a1 < 0)
	{
		v2 = sub_401C94(a1);
		sub_4DEB10(1, "ERROR : %s", v2);
		result = 1;
	}
	else
	{
		result = 0;
	}
	return result;
}
