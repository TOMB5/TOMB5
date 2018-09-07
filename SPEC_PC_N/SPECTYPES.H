#ifndef SPECTYPES_H
#define SPECTYPES_H

#define INPUT_H "INPUT.H"
#define CMATH_H "math.h"

#include "STANDARD.H"
#include "TYPES.H"
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#define STRINGIFY2(x) #x
#define STRINGIFY(x) STRINGIFY2(x)
#define Unimpl() S_Warn("[" __FUNCTION__ "] - Unimplemented!\n")

#define SWAP(a, b) {auto _ = a; a = b; b = _;}

#define SWAPARR(arr, i, j, len) {void* tmp = malloc(sizeof(arr[i]));memcpy(tmp, arr[i], sizeof(arr[i]));memcpy(arr[j], arr[i], sizeof(arr[i]));memcpy(arr[i], tmp, sizeof(tmp));}

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

#define DIVFP(A, B) (((A) / ((B) >> 8)) << 8)
#define MULFP(A, B) ((((A) % (B)) << 16) | (((A) * (B)) >> 6))

#define SLOWORD(l)           ((sint16)(((DWORD_PTR)(l)) & 0xffff))
#define SHIWORD(l)           ((sint16)((((DWORD_PTR)(l)) >> 16) & 0xffff))

#pragma pack(push, 1)
struct object_info {
	short nmeshes; // size=0, offset=0
	short mesh_index; // size=0, offset=2
	long bone_index; // size=0, offset=4
	short* frame_base; // size=0, offset=8
	void(*initialise)(short item_number); // size=0, offset=12
	void(*control)(short item_number); // size=0, offset=16
	void(*floor)(struct ITEM_INFO* item, int x, int y, int z, int* height); // size=0, offset=20
	void(*ceiling)(struct ITEM_INFO* item, int x, int y, int z, int* height); // size=0, offset=24
	void(*draw_routine)(struct ITEM_INFO* item); // size=0, offset=28
	void(*collision)(short item_num, struct ITEM_INFO* laraitem, struct COLL_INFO* coll); // size=0, offset=32
	short object_mip; // size=0, offset=36
	short anim_index; // size=0, offset=38
	short hit_points; // size=0, offset=40
	short pivot_length; // size=0, offset=42
	short radius; // size=0, offset=44
	short shadow_size; // size=0, offset=46
	unsigned short bite_offset; // size=0, offset=48
	unsigned short loaded : 1; // offset=50.0
	unsigned short intelligent : 1; // offset=50.1
	unsigned short non_lot : 1; // offset=50.2
	unsigned short save_position : 1; // offset=50.3
	unsigned short save_hitpoints : 1; // offset=50.4
	unsigned short save_flags : 1; // offset=50.5
	unsigned short save_anim : 1; // offset=50.6
	unsigned short semi_transparent : 1; // offset=50.7
	unsigned short water_creature : 1; // offset=51.0
	unsigned short using_drawanimating_item : 1; // offset=51.1
	unsigned short HitEffect : 2; // offset=51.2
	unsigned short undead : 1; // offset=51.4
	unsigned short save_mesh : 1; // offset=51.5
	void(*draw_routine_extra)(struct ITEM_INFO* item); // size=0, offset=52
	unsigned long explodable_meshbits; // size=0, offset=56
	unsigned long padfuck; // size=0, offset=60
};

struct static_info
{
	short mesh_number;
	short flags;
	short x_minp;
	short x_maxp;
	short y_minp;
	short y_maxp;
	short z_minp;
	short z_maxp;
	short x_minc;
	short x_maxc;
	short y_minc;
	short y_maxc;
	short z_minc;
	short z_maxc;
};

struct ROOM_LIGHT   // 88 bytes
{
	float x, y, z;       // Position of light, in world coordinates
	float r, g, b;       // Colour of the light

	uint32_t ShadowIntensity;    // only if LightType == LIGHT_SHADOW

	float In;            // Cosine of the IN value for light / size of IN value
	float Out;           // Cosine of the OUT value for light / size of OUT value
	float RadIn;         // (IN radians) * 2
	float RadOut;        // (OUT radians) * 2
	float Range;         // Range of light

	float dx, dy, dz;    // Direction - used only by sun and spot lights
	int32_t x2, y2, z2;    // Same as position, only in integer.
	int32_t dx2, dy2, dz2; // Same as direction, only in integer.

	uint8_t LightType;

	uint8_t Filler[3];     // Dummy values = 3 x 0xCD
};

struct room_info {
	short* data; // size=0, offset=0
	short* door; // size=0, offset=4
	struct FLOOR_INFO* floor; // size=8, offset=8
	struct LIGHTINFO* light; // size=32, offset=12
	struct MESH_INFO* mesh; // size=20, offset=16
	long x; // size=0, offset=20
	long y; // size=0, offset=24
	long z; // size=0, offset=28
	long minfloor; // size=0, offset=32
	long maxceiling; // size=0, offset=36
	short x_size; // size=0, offset=40
	short y_size; // size=0, offset=42
	struct CVECTOR ambient; // size=4, offset=44
	short num_lights; // size=0, offset=48
	short num_meshes; // size=0, offset=50
	unsigned char ReverbType; // size=0, offset=52
	unsigned char FlipNumber; // size=0, offset=53
	char MeshEffect; // size=0, offset=54
	char bound_active; // size=0, offset=55
	short left; // size=0, offset=56
	short right; // size=0, offset=58
	short top; // size=0, offset=60
	short bottom; // size=0, offset=62
	short test_left; // size=0, offset=64
	short test_right; // size=0, offset=66
	short test_top; // size=0, offset=68
	short test_bottom; // size=0, offset=70
	short item_number; // size=0, offset=72
	short fx_number; // size=0, offset=74
	short flipped_room; // size=0, offset=76
	unsigned short flags; // size=0, offset=78

	uint32_t Unknown1;
	uint32_t Unknown2;     // Always 0
	uint32_t Unknown3;     // Always 0

	uint32_t Separator;    // 0xCDCDCDCD

	uint16_t Unknown4;
	uint16_t Unknown5;

	float RoomX;
	float RoomY;
	float RoomZ;

	uint32_t Separator1[4]; // Always 0xCDCDCDCD
	uint32_t Separator2;    // 0 for normal rooms and 0xCDCDCDCD for null rooms
	uint32_t Separator3;    // Always 0xCDCDCDCD

	uint32_t NumRoomTriangles;
	uint32_t NumRoomRectangles;

	struct ROOM_LIGHT* RoomLights; 

	uint32_t LightDataSize;
	uint32_t NumLights2;    // Always same as NumLights

	uint32_t Unknown6;

	int32_t RoomYTop;
	int32_t RoomYBottom;

	uint32_t NumLayers;

	struct ROOMLET* LayerOffset;
	struct tr5_room_vertex* VerticesOffset;
	void* PolyOffset;
	void* PolyOffset2;   // Same as PolyOffset

	uint32_t NumVertices;

	uint32_t Separator5[4];  // Always 0xCDCDCDCD
};

struct PCLIGHT
{
	float x, y, z;       // Position of light, in world coordinates
	float r, g, b;       // Colour of the light

	uint32_t ShadowIntensity;    // only if LightType == LIGHT_SHADOW

	float In;            // Cosine of the IN value for light / size of IN value
	float Out;           // Cosine of the OUT value for light / size of OUT value
	float RadIn;         // (IN radians) * 2
	float RadOut;        // (OUT radians) * 2
	float Range;         // Range of light

	float dx, dy, dz;    // Direction - used only by sun and spot lights
	int32_t x2, y2, z2;    // Same as position, only in integer.
	int32_t dx2, dy2, dz2; // Same as direction, only in integer.

	float r2, g2, b2;
	float r3, g3, b3;

	int32_t UnknownInt;
	uint8_t LightType;
	uint8_t UnknownByte;
	
	int32_t dx3, dy3, dz3;
	int32_t magnsq;
};

struct ITEM_LIGHT
{
	int red;
	int green;
	int blue;
	struct CVECTOR room_ambient;
	int d_red;
	int d_green;
	int d_blue;
	int room_num;
};

struct ITEM_INFO {
	long floor; // size=0, offset=0
	unsigned long touch_bits; // size=0, offset=4
	unsigned long mesh_bits; // size=0, offset=8
	short object_number; // size=0, offset=12
	short current_anim_state; // size=0, offset=14
	short goal_anim_state; // size=0, offset=16
	short required_anim_state; // size=0, offset=18
	short anim_number; // size=0, offset=20
	short frame_number; // size=0, offset=22
	short room_number; // size=0, offset=24
	short next_item; // size=0, offset=26
	short next_active; // size=0, offset=28
	short speed; // size=0, offset=30
	short fallspeed; // size=0, offset=32
	short hit_points; // size=0, offset=34
	unsigned short box_number; // size=0, offset=36
	short timer; // size=0, offset=38
	short flags; // size=0, offset=40
	short shade; // size=0, offset=42
	short trigger_flags; // size=0, offset=44
	short carried_item; // size=0, offset=46
	short after_death; // size=0, offset=48
	unsigned short fired_weapon; // size=0, offset=50
	short item_flags[4]; // size=8, offset=52
	void* data; // size=0, offset=60
	struct PHD_3DPOS pos; // size=20, offset=64
	struct ITEM_LIGHT il; // size=48, offset=84
	struct PCLIGHT lights_1[21];
	struct PCLIGHT lights_2[21];
	DWORD num_lights_1;
	DWORD num_lights_2;
	DWORD light_room_num;
	DWORD unk_thing;
	struct PHD_VECTOR ambient_light_pos;
	struct PCLIGHT* ptr_lights_1;
	struct PCLIGHT* ptr_lights_2;
	unsigned long active : 1; // offset=132.0 OFF=5610
	unsigned long status : 2; // offset=132.1
	unsigned long gravity_status : 1; // offset=132.3
	unsigned long hit_status : 1; // offset=132.4
	unsigned long collidable : 1; // offset=132.5
	unsigned long looked_at : 1; // offset=132.6
	unsigned long dynamic_light : 1; // offset=132.7
	unsigned long poisoned : 1; // offset=133.0
	unsigned long ai_bits : 5; // offset=133.1
	unsigned long really_active : 1; // offset=133.6
	unsigned long InDrawRoom : 1; // offset=133.7
	unsigned long meshswap_meshbits; // size=0, offset=136 OFF=132
	short draw_room; // size=0, offset=140 OFF=136
	short TOSSPAD; // size=0, offset=142 OFF=138
};
struct creature_info {
	short joint_rotation[4]; // size=8, offset=0
	short maximum_turn; // size=0, offset=8
	short flags; // size=0, offset=10
	unsigned short alerted : 1; // offset=12.0
	unsigned short head_left : 1; // offset=12.1
	unsigned short head_right : 1; // offset=12.2
	unsigned short reached_goal : 1; // offset=12.3
	unsigned short hurt_by_lara : 1; // offset=12.4
	unsigned short patrol2 : 1; // offset=12.5
	unsigned short jump_ahead : 1; // offset=12.6
	unsigned short monkey_ahead : 1; // offset=12.7
	enum mood_type mood; // size=4, offset=14
	struct ITEM_INFO* enemy; // size=144, offset=18
	struct ITEM_INFO ai_target; // size=144, offset=22
	short item_num; // size=0, offset=5644
	struct PHD_VECTOR target; // size=12, offset=5646
	struct lot_info LOT; // size=44, offset=5658
};

struct tr4_mesh_face3    // 10 bytes
{
	uint16_t Vertices[3];
	uint16_t Texture;
	uint16_t Effects;    // TR4-5 ONLY: alpha blending and environment mapping strength
};

struct tr4_mesh_face4    // 12 bytes
{
	uint16_t Vertices[4];
	uint16_t Texture;
	uint16_t Effects;
};

struct ROOMLET   // 56 bytes
{
	uint32_t NumLayerVertices;   // Number of vertices in this layer (4 bytes)
	uint16_t UnknownL1;
	uint16_t NumLayerRectangles; // Number of rectangles in this layer (2 bytes)
	uint16_t NumLayerTriangles;  // Number of triangles in this layer (2 bytes)
	uint16_t UnknownL2;

	uint16_t Filler;             // Always 0
	uint16_t Filler2;            // Always 0

								 // The following 6 floats define the bounding box for the layer

	float    LayerBoundingBoxX1;
	float    LayerBoundingBoxY1;
	float    LayerBoundingBoxZ1;
	float    LayerBoundingBoxX2;
	float    LayerBoundingBoxY2;
	float    LayerBoundingBoxZ2;

	uint32_t Filler3;     // Always 0 (4 bytes)
	void* VerticesOffset;
	void* PolyOffset;
	void* PolyOffset2;
};

struct tr5_vertex   // 12 bytes
{
	float x;
	float y;
	float z;
};

struct tr5_room_vertex  // 28 bytes
{
	struct tr5_vertex Vertex;     // Vertex is now floating-point
	struct tr5_vertex Normal;
	uint32_t Colour;     // 32-bit colour
};

struct SPRITE_STRUCT // 24 bytes
{
	uint16_t tile;
	uint8_t x;
	uint8_t y;
	uint16_t width;
	uint16_t height;
	float left;
	float top;
	float right;
	float bottom;
};

struct tr_object_texture_vert // 4 bytes
{
	uint8_t Xcoordinate; // 1 if Xpixel is the low value, 255 if Xpixel is the high value in the object texture
	uint8_t Xpixel;
	uint8_t Ycoordinate; // 1 if Ypixel is the low value, 255 if Ypixel is the high value in the object texture
	uint8_t Ypixel;
};

struct tr4_object_texture // 38 bytes
{
	uint16_t               Attribute;
	uint16_t               TileAndFlag;
	uint16_t               NewFlags;

	struct tr_object_texture_vert Vertices[4]; // The four corners of the texture

	uint32_t               OriginalU;
	uint32_t               OriginalV;
	uint32_t               Width;     // Actually width-1
	uint32_t               Height;    // Actually height-1

	uint16_t Padding;
};

struct OBJECT_TEXTURE_VERT
{
	float x;
	float y;
};

struct OBJECT_TEXTURE
{
	uint16_t attribute;
	uint16_t tile_and_flag;
	uint16_t new_flags;
	struct OBJECT_TEXTURE_VERT vertices[4];
};

enum OBJECT_TEXTURE_ATTRIBUTE
{
	OT_ALL_OPAQUE = 0,
	OT_ALPHA_TESTING = 1,
	OT_ALPHA_BLENDING = 2,
	OT_ALPHA_BLENDING_INV = 3,
	OT_ALPHA_TESTING_DEPTHLESS = 4,
	OT_UNUSED = 5,
	OT_WIREFRAME = 6,
	OT_FORCED_ALPHA = 7
};

struct DRIP_STRUCT
{
	long x; // size=0, offset=0
	long y; // size=0, offset=4
	long z; // size=0, offset=8
	unsigned char On; // size=0, offset=12
	unsigned char R; // size=0, offset=13
	unsigned char G; // size=0, offset=14
	unsigned char B; // size=0, offset=15
	short Yvel; // size=0, offset=16
	unsigned char Gravity; // size=0, offset=18
	unsigned char Life; // size=0, offset=19
	short RoomNumber; // size=0, offset=20
	unsigned char Outside; // size=0, offset=22
	unsigned char Pad; // size=0, offset=23
	char padding[8];
	unsigned short padding1;
	char padding2[2];
	unsigned short padding3;
	char padding4[2];
};

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
	DDSURFACEDESC2	ddsd;			// Surface Description
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
	struct DISPLAYMODE*	DisplayMode;	// Ptr To Compatible Display Modes
	int				nTexture;		// Number Of Texture Formats
	struct D3DTEXTUREINFO*	Texture;		// Texture Info
	int nZbuffer; // pos 402 s 4
	struct zBufFormat* Zbuffer; // pos 406 s 4
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
	struct DISPLAYMODE*	DisplayMode;	// Ptr To Display Mode Structure
	int				nD3DInfo;		// Number Of D3D Drivers
	struct DIRECT3DINFO*	D3DInfo;		// Ptr To D3D Info Structure
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
	struct DIRECTDRAWINFO*	DDInfo;			// Ptr To Info Structure
	struct DIRECTSOUNDINFO* DSInfo;
};


struct WINAPP
{
	HINSTANCE				hInstance;
	HWND					WindowHandle;
	WNDCLASS				WindowClass;

	struct DEVICEINFO				DeviceInfo;			// Device Information
	struct DXCONFIG				DXConfig;

	BYTE pad;

	LPDIRECTDRAW4			lpDD;				// DirectDraw2 Interface
	LPDIRECT3D3				lpD3D;				// Direct3D2 Interface
	LPDIRECT3DDEVICE3		lpD3DDevice;		// Direct 3D2 Device
	LPDIRECT3DDEVICE3		lpD3DDevice_BIS;	// Direct 3D2 Device

	LPDIRECTDRAWSURFACE4	lpFrontBuffer;		// Primary Surface
	LPDIRECTDRAWSURFACE4	lpBackBuffer;		// Back Buffer
	LPDIRECTDRAWSURFACE4	lpZBuffer;			// Z Buffer

	LPDIRECT3DVIEWPORT3		lpViewPort;

	LPDIRECTSOUND			lpDS;

	unsigned int width;
	unsigned int height;

	RECT					GnClientRect;
	RECT					GnWindowRect;

	unsigned int			Flags;
	unsigned int			DXWndStyle;
	unsigned int			DXCoopLevel;

	LPDIRECTINPUT7A			lpDI;
	LPDIRECTINPUTDEVICE2A	lpDIKeyboard;
	LPDIRECTINPUTDEVICE2A	lpDIJoystick;

	HWND					GhWnd; // pos 100 s 4
	DWORD isInScene; // pos 104 s 4
	DWORD					bNoFocus;				// Application Window Has Fous

	DWORD sceneDone;
	HANDLE hObject; // D9AC05

	float fps;
	DWORD dword_D9AC0D;
	DWORD dword_D9AC11;

	HACCEL hAccTable;
	uint8 GameInitialized;
	BYTE					tBumpMap;
	DWORD textRes;
	DWORD bumpRes;
	uint8 MMXSupport;
	BYTE					tBilinearFilter;
	BYTE					tVolumetricShadows;
	BYTE					tDisableSound;
	DWORD orig_flags;
	BYTE PlayingFMV;
	DWORD OriginalBPP;

	BYTE					tAutoTarget;
	DWORD dword_D9AC34;
	DWORD dword_D9AC38;

	LPDIRECTDRAWPALETTE		Palette;				// Palette For SW Renderer
	char pad111[272];
	D3DMATRIX ViewMatrix;
	char pad112[8];
	DWORD DrawPrimitiveCnt;
	char pad11201[4];
	uint16_t* AnimTextureRanges;
	char pad1121[4];
	D3DMATRIX WorldMatrix;
	char pad113[8];
	DWORD fps_counter = 0;
	float fps_static = 0.0f;
	char pad114[584];


	bool					bRender;			// Ok To Render

	int						nRenderMode;		// Hardware/Internal Renderer
	int						nUVAdd;

	bool					tJoystickEnabled;
	int						Joystick;

	float					fps_weird;
};


typedef struct
{
	signed char	  shimmer;
	signed char   choppy;
	unsigned char random;
	unsigned char abs;
} WATERTAB;

struct CutsceneHeader
{
	uint32_t offset;
	uint32_t size;
};

struct Cutseq
{
	struct CutsceneHeader cutscenes[45];
	uint8_t padding[1688];
};

struct SNOWFLAKE
{
	long x;
	long y;
	long z;
	int8_t xv;
	uint8_t yv; // also life
	int8_t zv;
	uint8_t life;
	uint16_t underwater;
	short room_number;
};



#pragma pop

enum WINAPP_FLAGS
{
	WA_FULLSCREEN = (1 << 0),
	WA_WINDOWED = (1 << 1),
	WA_UNKNOWN2 = (1 << 4),
	WA_FPUSETUP = (1 << 5),
	WA_SOFTWARE = (1 << 6),
	WA_BACK_BUFFER = (1 << 7),
};

#endif