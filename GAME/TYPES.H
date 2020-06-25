#if PC_VERSION
#pragma clang diagnostic push
#pragma ide diagnostic ignored "UnusedGlobalDeclarationInspection"
#endif
#ifndef GTYPES_H
#define GTYPES_H

#ifndef MATRIX_WRAPPER
#define MATRIX_WRAPPER
#if PC_VERSION
#include <d3dtypes.h>
typedef D3DMATRIX MatrixThing;
#else
typedef struct MATRIX3D MatrixThing;
#endif
#endif

// required for NULL macro because if we define it ourselves it shits brixes
#if PSXPC_TEST
#include <stdint.h>
#endif

#if SAT_VERSION
#include <SEGA_XPT.H>
#endif

#if !SAT_VERSION
#include <stddef.h>
#include <stdlib.h>


#ifndef ABS
#define ABS(x) (((x)<0)?(-(x)):(x))
#endif

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#ifndef MIN
#define MIN(x, y) (((x)<(y))?(x):(y))
#endif

#ifndef MAX
#define MAX(x, y) (((x)>(y))?(x):(y))
#endif

#endif

#if !SAT_VERSION
#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif
#endif

#ifndef SIGN
#define SIGN(x) ((0 < (x)) - ((x) < 0))
#endif

// (65536 / 360) ~ 182.0444...
// Game used 182, so maybe our code will be more precise %)
#define ANGLE(x) (short)((x) * 65536.0 / 360.0)

#if PC_VERSION
#define SIN(x) (4 * rcossin_tbl[((int)(x) >> 3) & 0x1FFE])
#define COS(x) (4 * rcossin_tbl[(((int)(x) >> 3) & 0x1FFE) + 1])
#else
#define SIN(x) (rcossin_tbl[((int)(x) >> 3) & 0x1FFE])
#define COS(x) (rcossin_tbl[(((int)(x) >> 3) & 0x1FFE) + 1])
#endif

#define TRIGMULT2(a, b) (((a) * (b)) >> W2V_SHIFT)
#define TRIGMULT2F(a, b) (((a) * (b)) / 16384.0f)
#define TRIGMULT3(a, b, c) TRIGMULT2(TRIGMULT2(a, b), c)

#if PC_VERSION
#define phd_atan_asm phd_atan
#endif
#if 0 // for later...
inline int phd_atan(long x, long y)
{
 /* 0x00 */ char octant = 0;
 /* 0x00 */ int res;
	if (x < 0)
	{
		octant = 4;
		x = -x;
	}
	if (y < 0)
	{
		octant += 2;
		y = -y;
	}
	if (y > x)
	{
		const long tmp = x;
		x = y;
		y = tmp;
		octant += 1;
	}
	if (x == 0)
	{
		x = 1;
	}
	res = atanOctantTab[octant] + atanTab[(y * 2048) / x];
	return abs(res);
}
#elif 1
#if PC_VERSION
#include <math.h>

inline int phd_atan(long x, long y)
{
	return (int)(atan2(y, x) * 32768.0 / 3.14159265359);
}
#endif
#endif


#define RGB555(r, g, b) ((r << 7) & 0x7C00 | (g << 2) & 0x3E0 | (b >> 3) & 0x1F)
#define RED5(rgb) (((rgb >> 10) & 0x1F) << 3)
#define GREEN5(rgb) (((rgb >> 5) & 0x1F) << 3)
#define BLUE5(rgb) ((rgb & 0x1F) << 3)
#define WHITE555 RGB555(255, 255, 255)
#define GRAY555  RGB555(128, 128, 128)
#define BLACK555 RGB555(  0,   0,   0)

#define WALL_L  	 1024
#define WALL_SHIFT 10
#define STEP_L     (WALL_L/4)

//#define SECTOR 1024
#define SECTOR(x) ((x) * WALL_L)
#define CLICK 256

#define UNIT_SHADOW 256
#define UNIT_SHADOW_SHIFT 8

#define BAD_HEIGHT (-32512)

#define LARA_HITPOINTS 1000

#define ROUND_MUL_LOW(x, m) ((x) & ~(m - 1))

#define SECTOR_TO_WORLD(S) ((S) > (0) ? SECTOR((S) + 0.5) : (0))

#define XZ_GET_SECTOR(room, x, z) (r->floor[(int)((z) / 1024 + r->x_size * ((x) / 1024))])

#define PSXENGINE (PSXPC_VERSION || PSX_VERSION || SAT_VERSION || PS2_VERSION)

#define TEXTURE_PAGE (256 * 256)

#if PC_VERSION
#define W2V_SHIFT 		14				// Shift scale of View.Frame to World.Frame
#else
#define W2V_SHIFT 12
#endif
#define	W2V_SCALE 		(1<<W2V_SHIFT)	// Scale of View Frame to World Frame

#if !SAT_VERSION
enum msoff {
	M00, M01, M02, M03,
	M10, M11, M12, M13,
	M20, M21, M22, M23
};
#endif

#ifndef CLAMP
#define CLAMP(x, a, b) ((x)<(a)?(a):((x)>(b)?(b):(x)))
#endif

#define CLAMPADDSHIFT(x, a, b) ((unsigned short)((x)+(a) & 0xFFFF)<(b)?0:((x)<-(a))?((x)+(a)):((x+-a)))
#define CLAMPADD2(x, a, b) ((unsigned short)((x)+(a))<(b)?0:((x)<(-(a)))?((x)+(a)):((x)+(-(a))))
#define CLAMPADD3(x, a, b, c) ((unsigned short)((x)+(a))<(b)?c:((x)<(-(c)))?((x)):(-c))
#define CLAMPADD(x, a, b) ((x)<(a)?((x)+(a)):((x)>(b)?((x)-(b)):0))///@FIXME this is actually incorrect, update all to use CLAMPADD2.

#define RED(rgb) (((rgb) >> 16) & 0xFF)
#define GREEN(rgb) (((rgb) >> 8) & 0xFF)
#define BLUE(rgb) ((rgb) & 0xFF)
#define ALPHA(rgb) (((rgb) >> 24) & 0xFF)

#define RGBONLY(r, g, b) ((b & 0xFF) | (((g & 0xFF) | ((r & 0xFF) << 8)) << 8))
#define RGBA(r, g, b, a) (RGBONLY(r, g, b) | ((a) << 24))
#define ARGB(r, g, b, a) (RGBA(b, g, r, a))

#define NO_ROOM 0xFF

enum font_flags
{
	FF_NONE = (0 << 0), // 0x0000
	FF_UNK0 = (1 << 0),	// 0x0001
	FF_UNK1 = (1 << 1),	// 0x0002
	FF_UNK2 = (1 << 2),	// 0x0004
	FF_UNK3 = (1 << 3),	// 0x0008
	FF_UNK4 = (1 << 4),	// 0x0010
	FF_UNK5 = (1 << 5),	// 0x0020
	FF_UNK6 = (1 << 6),	// 0x0040
	FF_UNK7 = (1 << 7),	// 0x0080
	FF_UNK8 = (1 << 8),	// 0x0100
	FF_UNK9 = (1 << 9),	// 0x0200
	FF_UNK10 = (1 << 10),	// 0x0400
	FF_UNK11 = (1 << 11),	// 0x0800
	FF_SMALL = (1 << 12),	// 0x1000
	FF_BLINK = (1 << 13),	// 0x2000
	FF_R_JUSTIFY = (1 << 14),	// 0x4000
	FF_CENTER = (1 << 15),	// 0x8000
};

enum zone_type
{
	SKELLY_ZONE = 0,
	BASIC_ZONE = 1,
	CROC_ZONE = 2,
	HUMAN_ZONE = 3,
	FLYER_ZONE = 4,
};

enum camera_type
{
	CHASE_CAMERA = 0,
	FIXED_CAMERA = 1,
	LOOK_CAMERA = 2,
	COMBAT_CAMERA = 3,
	CINEMATIC_CAMERA = 4,
	HEAVY_CAMERA = 5,
};

enum mood_type
{
	BORED_MOOD = 0,
	ATTACK_MOOD = 1,
	ESCAPE_MOOD = 2,
	STALK_MOOD = 3,
};

enum target_type
{
	NO_TARGET = 0,
	PRIME_TARGET = 1,
	SECONDARY_TARGET = 2,
};

enum room_flags
{
	RF_FILL_WATER = (1 << 0),			    // 0x0001
	RF_ALWAYS_SFX = (1 << 1),				// 0x0002
	RF_PITCH_SHIFT = (1 << 2),				// 0x0004
	RF_SKYBOX_VISIBLE = (1 << 3),		    // 0x0008   speeds up rendering if no rendered room has this
	RF_DYNAMIC_LIT = (1 << 4),				// 0x0010
	RF_WIND_BLOWS_PONYTAIL = (1 << 5),	    // 0x0020   also some particles
	RF_INSIDE = (1 << 6),	    		    // 0x0040   used in official levels, no apparent effects
	RF_HIDE_GLOBAL_LENS_FLARE = (1 << 7),   // 0x0080   TRLE "NL"
	RF_CAUSTICS_EFFECT = (1 << 8),		    // 0x0100   TRLE "M"
	RF_WATER_REFLECTIVITY = (1 << 9),	    // 0x0200   TRLE "R"
	RF_UNKNOWN_10 = (1 << 10),			    // 0x0400   NGLE uses it for snow
	RF_TRLE_D = (1 << 11),					// 0x0800   NGLE uses it for rain
	RF_TRLE_P = (1 << 12)					// 0x1000   NGLE uses it for cold rooms
};

enum item_status
{
	ITEM_INACTIVE = 0,
	ITEM_ACTIVE = 1,
	ITEM_DEACTIVATED = 2,
	ITEM_INVISIBLE = 3
};

enum material_index
{
	MAT_MUD,
	MAT_SNOW,
	MAT_SAND,
	MAT_GRAVEL,
	MAT_ICE,
	MAT_WATER,		 // Unused
	MAT_STONE,		 // Unused
	MAT_WOOD,
	MAT_METAL,
	MAT_MARBLE,
	MAT_GRASS,		 // Same SFX as sand
	MAT_CONCRETE,	 // Same SFX as stone
	MAT_OLD_WOOD,	 // Same SFX as wood
	MAT_OLD_METAL,	 // Same SFX as metal

	NUM_MATERIALS
};

enum weather_type
{
	WEATHER_NORMAL = 0,
	WEATHER_RAIN = 1,
	WEATHER_SNOW = 2
};

enum command_types
{
	COMMAND_NULL = 0,
	COMMAND_MOVE_ORIGIN,
	COMMAND_JUMP_VELOCITY,
	COMMAND_ATTACK_READY,
	COMMAND_DEACTIVATE,
	COMMAND_SOUND_FX,
	COMMAND_EFFECT
};

#if !(PSXPC_TEST || SAT_VERSION)
struct VECTOR
{
 /* 0x00 */ long vx;
 /* 0x04 */ long vy;
 /* 0x08 */ long vz;
#if PSXENGINE
 /* 0x0C */ long pad;
#endif
};
#endif

struct PHD_VECTOR
{
 /* 0x00 */ long x;
 /* 0x04 */ long y;
 /* 0x08 */ long z;
};

struct WATERTAB
{
 /* 0x00 */ char shimmer;
 /* 0x01 */ char choppy;
 /* 0x02 */ unsigned char random;
 /* 0x03 */ unsigned char abs;
};

#if PC_VERSION || PSXPC_VERSION || PSXPC_TEST
#pragma pack(push, 1)
#endif
struct PHD_3DPOS
{
 /* 0x00 */ long x_pos; // off 0 [64]
 /* 0x04 */ long y_pos; // off 4 [68]
 /* 0x08 */ long z_pos; // off 8 [72]
 /* 0x0C */ short x_rot; // off 12 [76]
 /* 0x0E */ short y_rot; // off 14 [78]
 /* 0x10 */ short z_rot; // off 16 [80]
#if PSXPC_TEST
 /* 0x12 */ short padding;
#endif
};

struct FLOOR_INFO
{
 /* 0x00 */ unsigned short index; // size=0, offset=0
 /* 0x02 */ unsigned short fx : 4; // offset=2.0
		    unsigned short box : 11; // offset=2.4
		    unsigned short stopper : 1; // offset=3.7
 /* 0x04 */ unsigned char pit_room; // size=0, offset=4
 /* 0x05 */ char floor; // size=0, offset=5
 /* 0x06 */ unsigned char sky_room; // size=0, offset=6
 /* 0x07 */ char ceiling; // size=0, offset=7
};

struct LIGHTINFO
{
 /* 0x00 */ long x; // size=0, offset=0
 /* 0x04 */ long y; // size=0, offset=4
 /* 0x08 */ long z; // size=0, offset=8
 /* 0x0C */ unsigned char Type; // size=0, offset=12
 /* 0x0D */ unsigned char r; // size=0, offset=13
 /* 0x0E */ unsigned char g; // size=0, offset=14
 /* 0x0F */ unsigned char b; // size=0, offset=15
 /* 0x10 */ short nx; // size=0, offset=16
 /* 0x12 */ short ny; // size=0, offset=18
 /* 0x14 */ short nz; // size=0, offset=20
 /* 0x16 */ short Intensity; // size=0, offset=22
 /* 0x18 */ unsigned char Inner; // size=0, offset=24
 /* 0x19 */ unsigned char Outer; // size=0, offset=25
 /* 0x1A */ short FalloffScale; // size=0, offset=26
 /* 0x1C */ short Length; // size=0, offset=28
 /* 0x1E */ short Cutoff; // size=0, offset=30
};

struct MESH_INFO
{
 /* 0x00 */ long x; // size=0, offset=0
 /* 0x04 */ long y; // size=0, offset=4
 /* 0x08 */ long z; // size=0, offset=8
 /* 0x0C */ short y_rot; // size=0, offset=12
 /* 0x0E */ short shade; // size=0, offset=14
 /* 0x10 */ short Flags; // size=0, offset=16
 /* 0x12 */ short static_number; // size=0, offset=18
};

struct FX_INFO
{
 /* 0x00 */ struct PHD_3DPOS pos; // size=20, offset=0
 /* 0x14 */ short room_number; // size=0, offset=20
 /* 0x16 */ short object_number; // size=0, offset=22
 /* 0x18 */ short next_fx; // size=0, offset=24
 /* 0x1A */ short next_active; // size=0, offset=26
 /* 0x1C */ short speed; // size=0, offset=28
 /* 0x1E */ short fallspeed; // size=0, offset=30
 /* 0x20 */ short frame_number; // size=0, offset=32
 /* 0x22 */ short counter; // size=0, offset=34
 /* 0x24 */ short shade; // size=0, offset=36
 /* 0x26 */ short flag1; // size=0, offset=38
 /* 0x28 */ short flag2; // size=0, offset=40
};

struct lara_arm
{
 /* 0x00 */ short* frame_base; // size=0, offset=0
 /* 0x04 */ short frame_number; // size=0, offset=4
 /* 0x06 */ short anim_number; // size=0, offset=6
 /* 0x08 */ short lock; // size=0, offset=8
 /* 0x0A */ short y_rot; // size=0, offset=10
 /* 0x0C */ short x_rot; // size=0, offset=12
 /* 0x0E */ short z_rot; // size=0, offset=14
 /* 0x10 */ short flash_gun; // size=0, offset=16
};

struct box_node
{
 /* 0x00 */ short exit_box; // size=0, offset=0
 /* 0x02 */ unsigned short search_number; // size=0, offset=2
 /* 0x04 */ short next_expansion; // size=0, offset=4
 /* 0x06 */ short box_number; // size=0, offset=6
};

struct lot_info
{
 /* 0x00 */ struct box_node* node; // size=8, offset=0
 /* 0x04 */ short head; // size=0, offset=4
 /* 0x06 */ short tail; // size=0, offset=6
 /* 0x08 */ unsigned short search_number; // size=0, offset=8
 /* 0x0A */ unsigned short block_mask; // size=0, offset=10
 /* 0x0C */ short step; // size=0, offset=12
 /* 0x0E */ short drop; // size=0, offset=14
 /* 0x10 */ short zone_count; // size=0, offset=16
 /* 0x12 */ short target_box; // size=0, offset=18
 /* 0x14 */ short required_box; // size=0, offset=20
 /* 0x16 */ short fly; // size=0, offset=22
 /* 0x18 */ unsigned short can_jump : 1; // offset=24.0
		    unsigned short can_monkey : 1; // offset=24.1
		    unsigned short is_amphibious : 1; // offset=24.2
		    unsigned short is_jumping : 1; // offset=24.3
		    unsigned short is_monkeying : 1; // offset=24.4
 /* 0x1C */ struct PHD_VECTOR target; // size=12, offset=28
 /* 0x28 */ enum zone_type zone; // size=4, offset=40
};

struct ROPE_STRUCT
{
 /* 0x000 */ struct PHD_VECTOR Segment[24]; // size=288, offset=0
 /* 0x120 */ struct PHD_VECTOR Velocity[24]; // size=288, offset=288
 /* 0x240 */ struct PHD_VECTOR NormalisedSegment[24]; // size=288, offset=576
 /* 0x360 */ struct PHD_VECTOR MeshSegment[24]; // size=288, offset=864
 /* 0x480 */ struct PHD_VECTOR Position; // size=12, offset=1152
 /* 0x48C */ long SegmentLength; // size=0, offset=1164
 /* 0x490 */ short Active; // size=0, offset=1168
 /* 0x492 */ short Coiled; // size=0, offset=1170
};

struct lara_info
{
 /* 0x000 */ short item_number; // size=0, offset=0
 /* 0x002 */ short gun_status; // size=0, offset=2
 /* 0x004 */ short gun_type; // size=0, offset=4
 /* 0x006 */ short request_gun_type; // size=0, offset=6
 /* 0x008 */ short last_gun_type; // size=0, offset=8
 /* 0x00A */ short calc_fallspeed; // size=0, offset=10
 /* 0x00C */ short water_status; // size=0, offset=12
 /* 0x00E */ short climb_status; // size=0, offset=14
 /* 0x010 */ short pose_count; // size=0, offset=16
 /* 0x012 */ short hit_frame; // size=0, offset=18
 /* 0x014 */ short hit_direction; // size=0, offset=20
 /* 0x016 */ short air; // size=0, offset=22
 /* 0x018 */ short dive_count; // size=0, offset=24
 /* 0x01A */ short death_count; // size=0, offset=26
 /* 0x01C */ short current_active; // size=0, offset=28
 /* 0x01E */ short current_xvel; // size=0, offset=30
 /* 0x020 */ short current_yvel; // size=0, offset=32
 /* 0x022 */ short current_zvel; // size=0, offset=34
 /* 0x024 */ short spaz_effect_count; // size=0, offset=36
 /* 0x026 */ short flare_age; // size=0, offset=38
 /* 0x028 */ short BurnCount; // size=0, offset=40
 /* 0x02A */ short weapon_item; // size=0, offset=42
 /* 0x02C */ short back_gun; // size=0, offset=44
 /* 0x02E */ short flare_frame; // size=0, offset=46
 /* 0x030 */ short poisoned; // size=0, offset=48
 /* 0x032 */ short dpoisoned; // size=0, offset=50
 /* 0x034 */ unsigned char Anxiety; // size=0, offset=52
 /* 0x035 */ unsigned char wet[15]; // size=15, offset=53
 /* 0x044 */ unsigned short flare_control_left : 1; // offset=68.0 - 0x0001
			 unsigned short Unused1 : 1; // offset=68.1 - 0x0002
			 unsigned short look : 1; // offset=68.2 - 0x0004
			 unsigned short burn : 1; // offset=68.3 - 0x0008
			 unsigned short keep_ducked : 1; // offset=68.4 - 0x0010
			 unsigned short IsMoving : 1; // offset=68.5 - 0x0020
			 unsigned short CanMonkeySwing : 1; // offset=68.6 - 0x0040
			 unsigned short BurnBlue : 2; // offset=68.7 - 0x0080 | 0x0100
			 unsigned short Gassed : 1; // offset=69.1 - 0x0200
			 unsigned short BurnSmoke : 1; // offset=69.2 - 0x0400
			 unsigned short IsDucked : 1; // offset=69.3 - 0x0800
			 unsigned short has_fired : 1; // offset=69.4 - 0x1000
			 unsigned short Busy : 1; // offset=69.5 - 0x2000
			 unsigned short LitTorch : 1; // offset=69.6 - 0x4000
			 unsigned short IsClimbing : 1; // offset=69.7 - 0x8000
			 unsigned short Fired : 1; // offset=70.0 - 0x0001
 /* 0x048 */ long water_surface_dist; // size=0, offset=72
 /* 0x04C */ struct PHD_VECTOR last_pos; // size=12, offset=76
 /* 0x058 */ struct FX_INFO* spaz_effect; // size=44, offset=88
 /* 0x05C */ int mesh_effects; // size=0, offset=92
 /* 0x060 */ short* mesh_ptrs[15]; // size=60, offset=96
 /* 0x09C */ struct ITEM_INFO* target; // size=144, offset=156
 /* 0x0A0 */ short target_angles[2]; // size=4, offset=160
 /* 0x0A4 */ short turn_rate; // size=0, offset=164
 /* 0x0A6 */ short move_angle; // size=0, offset=166
 /* 0x0A8 */ short head_y_rot; // size=0, offset=168
 /* 0x0AA */ short head_x_rot; // size=0, offset=170
 /* 0x0AC */ short head_z_rot; // size=0, offset=172
 /* 0x0AE */ short torso_y_rot; // size=0, offset=174
 /* 0x0B0 */ short torso_x_rot; // size=0, offset=176
 /* 0x0B2 */ short torso_z_rot; // size=0, offset=178
 /* 0x0B4 */ struct lara_arm left_arm; // size=20, offset=180
 /* 0x0C8 */ struct lara_arm right_arm; // size=20, offset=200
 /* 0x0DC */ unsigned short holster; // size=0, offset=220
 /* 0x0E0 */ struct creature_info* creature; // size=228, offset=224
 /* 0x0E4 */ long CornerX; // size=0, offset=228
 /* 0x0E8 */ long CornerZ; // size=0, offset=232
 /* 0x0EC */ char RopeSegment; // size=0, offset=236
 /* 0x0ED */ char RopeDirection; // size=0, offset=237
 /* 0x0EE */ short RopeArcFront; // size=0, offset=238
 /* 0x0F0 */ short RopeArcBack; // size=0, offset=240
 /* 0x0F2 */ short RopeLastX; // size=0, offset=242
 /* 0x0F4 */ short RopeMaxXForward; // size=0, offset=244
 /* 0x0F6 */ short RopeMaxXBackward; // size=0, offset=246
 /* 0x0F8 */ long RopeDFrame; // size=0, offset=248
 /* 0x0FC */ long RopeFrame; // size=0, offset=252
 /* 0x100 */ unsigned short RopeFrameRate; // size=0, offset=256
 /* 0x102 */ unsigned short RopeY; // size=0, offset=258
 /* 0x104 */ long RopePtr; // size=0, offset=260
 /* 0x108 */ void* GeneralPtr; // size=0, offset=264
 /* 0x10C */ int RopeOffset; // size=0, offset=268
 /* 0x110 */ unsigned long RopeDownVel; // size=0, offset=272
 /* 0x114 */ char RopeFlag; // size=0, offset=276
 /* 0x115 */ char MoveCount; // size=0, offset=277
 /* 0x118 */ int RopeCount; // size=0, offset=280
 /* 0x11C */ char skelebob; // size=0, offset=284
 /* 0x11D */ char pistols_type_carried; // size=0, offset=285
 /* 0x11E */ char uzis_type_carried; // size=0, offset=286
 /* 0x11F */ char shotgun_type_carried; // size=0, offset=287
 /* 0x120 */ char crossbow_type_carried; // size=0, offset=288
 /* 0x121 */ char hk_type_carried; // size=0, offset=289
 /* 0x122 */ char sixshooter_type_carried; // size=0, offset=290
 /* 0x123 */ char lasersight; // size=0, offset=291
 /* 0x124 */ char silencer; // size=0, offset=292
 /* 0x125 */ char binoculars; // size=0, offset=293
 /* 0x126 */ char crowbar; // size=0, offset=294
 /* 0x127 */ char examine1; // size=0, offset=295
 /* 0x128 */ char examine2; // size=0, offset=296
 /* 0x129 */ char examine3; // size=0, offset=297
 /* 0x12A */ char wetcloth; // size=0, offset=298
 /* 0x12B */ char bottle; // size=0, offset=299
 /* 0x12C */ char puzzleitems[12]; // size=12, offset=300
 /* 0x138 */ unsigned short puzzleitemscombo; // size=0, offset=312
 /* 0x13A */ unsigned short keyitems; // size=0, offset=314
 /* 0x13C */ unsigned short keyitemscombo; // size=0, offset=316
 /* 0x13E */ unsigned short pickupitems; // size=0, offset=318
 /* 0x140 */ unsigned short pickupitemscombo; // size=0, offset=320
 /* 0x142 */ short num_small_medipack; // size=0, offset=322
 /* 0x144 */ short num_large_medipack; // size=0, offset=324
 /* 0x146 */ short num_flares; // size=0, offset=326
 /* 0x148 */ short num_pistols_ammo; // size=0, offset=328
 /* 0x14A */ short num_uzi_ammo; // size=0, offset=330
 /* 0x14C */ short num_revolver_ammo; // size=0, offset=332
 /* 0x14E */ short num_shotgun_ammo1; // size=0, offset=334
 /* 0x150 */ short num_shotgun_ammo2; // size=0, offset=336
 /* 0x152 */ short num_hk_ammo1; // size=0, offset=338
 /* 0x154 */ short num_crossbow_ammo1; // size=0, offset=340
 /* 0x156 */ short num_crossbow_ammo2; // size=0, offset=342
 /* 0x158 */ char location; // size=0, offset=344
 /* 0x159 */ char highest_location; // size=0, offset=345
 /* 0x15A */ char locationPad; // size=0, offset=346
 /* 0x15B */ unsigned char TightRopeOnCount; // size=0, offset=347
 /* 0x15C */ unsigned char TightRopeOff; // size=0, offset=348
 /* 0x15D */ unsigned char TightRopeFall; // size=0, offset=349
 /* 0x15E */ unsigned char ChaffTimer; // size=0, offset=350
};

struct STATS {
 /* 0x00 */ unsigned long Timer; // size=0, offset=0
 /* 0x04 */ unsigned long Distance; // size=0, offset=4
 /* 0x08 */ unsigned long AmmoUsed; // size=0, offset=8
 /* 0x0C */ unsigned long AmmoHits; // size=0, offset=12
 /* 0x10 */ unsigned short Kills; // size=0, offset=16
 /* 0x12 */ unsigned char Secrets; // size=0, offset=18
 /* 0x13 */ unsigned char HealthUsed; // size=0, offset=19
};

struct savegame_info
{
 /* 0x000 */ short Checksum; // size=0, offset=0
 /* 0x002 */ unsigned short VolumeCD; // size=0, offset=2
 /* 0x004 */ unsigned short VolumeFX; // size=0, offset=4
 /* 0x006 */ short ScreenX; // size=0, offset=6
 /* 0x008 */ short ScreenY; // size=0, offset=8
 /* 0x00A */ unsigned char ControlOption; // size=0, offset=10
 /* 0x00B */ unsigned char VibrateOn; // size=0, offset=11
#if PC_VERSION
 			char pad[3];
#endif
 /* 0x00C */ unsigned char AutoTarget; // size=0, offset=12
 /* 0x010 */ lara_info Lara; // size=352, offset=16
 /* 0x170 */ STATS Level; // size=20, offset=368
 /* 0x184 */ STATS Game; // size=20, offset=388
 /* 0x198 */ short WeaponObject; // size=0, offset=408
 /* 0x19A */ short WeaponAnim; // size=0, offset=410
 /* 0x19C */ short WeaponFrame; // size=0, offset=412
 /* 0x19E */ short WeaponCurrent; // size=0, offset=414
 /* 0x1A0 */ short WeaponGoal; // size=0, offset=416
 /* 0x1A4 */ unsigned long CutSceneTriggered1; // size=0, offset=420
 /* 0x1A8 */ unsigned long CutSceneTriggered2; // size=0, offset=424
 /* 0x1AC */ char GameComplete; // size=0, offset=428
 /* 0x1AD */ unsigned char CurrentLevel; // size=0, offset=429
 /* 0x1AE */ unsigned char CampaignSecrets[4]; // size=4, offset=430
 /* 0x1B2 */ unsigned char TLCount; // size=0, offset=434
};

struct MATRIX3D
{
 /* 0x00 */ short m00; // size=0, offset=0
 /* 0x02 */ short m01; // size=0, offset=2
 /* 0x04 */ short m02; // size=0, offset=4
 /* 0x06 */ short m10; // size=0, offset=6
 /* 0x08 */ short m11; // size=0, offset=8
 /* 0x0A */ short m12; // size=0, offset=10
 /* 0x0C */ short m20; // size=0, offset=12
 /* 0x0E */ short m21; // size=0, offset=14
 /* 0x10 */ short m22; // size=0, offset=16
 /* 0x12 */ short pad; // size=0, offset=18
 /* 0x14 */ long tx; // size=0, offset=20
 /* 0x18 */ long ty; // size=0, offset=24
 /* 0x1C */ long tz; // size=0, offset=28
};

struct GAMEFLOW
{
 /* 0x00 */ unsigned int CheatEnabled : 1; // offset=0.0
			unsigned int LoadSaveEnabled : 1; // offset=0.1
			unsigned int TitleEnabled : 1; // offset=0.2
			unsigned int PlayAnyLevel : 1; // offset=0.3
			unsigned int Language : 3; // offset=0.4
			unsigned int DemoDisc : 1; // offset=0.7
			unsigned int Unused : 24; // offset=1.0
 /* 0x04 */ unsigned int InputTimeout; // size=0, offset=4
 /* 0x08 */ unsigned char SecurityTag; // size=0, offset=8
 /* 0x09 */ unsigned char nLevels; // size=0, offset=9
 /* 0x0A */ unsigned char nFileNames; // size=0, offset=10
 /* 0x0B */ unsigned char Pad; // size=0, offset=11
 /* 0x0C */ unsigned short FileNameLen; // size=0, offset=12
 /* 0x0E */ unsigned short ScriptLen; // size=0, offset=14
};

struct STRINGHEADER
{
 /* 0x00 */ unsigned short nStrings; // size=0, offset=0
 /* 0x02 */ unsigned short nPSXStrings; // size=0, offset=2
 /* 0x04 */ unsigned short nPCStrings; // size=0, offset=4
 /* 0x06 */ unsigned short StringWadLen; // size=0, offset=6
 /* 0x08 */ unsigned short PSXStringWadLen; // size=0, offset=8
 /* 0x0A */ unsigned short PCStringWadLen; // size=0, offset=10
};

struct GAME_VECTOR
{
 /* 0x00 */ long x; // size=0, offset=0
 /* 0x04 */ long y; // size=0, offset=4
 /* 0x08 */ long z; // size=0, offset=8
 /* 0x0C */ short room_number; // size=0, offset=12
 /* 0x0E */ short box_number; // size=0, offset=14
};

struct OBJECT_VECTOR
{
 /* 0x00 */ long x; // size=0, offset=0
 /* 0x04 */ long y; // size=0, offset=4
 /* 0x08 */ long z; // size=0, offset=8
 /* 0x0C */ short data; // size=0, offset=12
 /* 0x0E */ short flags; // size=0, offset=14
};

struct SPHERE
{
 /* 0x00 */ long x; // size=0, offset=0
 /* 0x04 */ long y; // size=0, offset=4
 /* 0x08 */ long z; // size=0, offset=8
 /* 0x0C */ long r; // size=0, offset=12
};

struct PENDULUM
{
 /* 0x00 */ PHD_VECTOR Position; // size=12, offset=0
 /* 0x0C */ PHD_VECTOR Velocity; // size=12, offset=12
 /* 0x18 */ int node; // size=0, offset=24
 /* 0x1C */ ROPE_STRUCT* Rope; // size=1172, offset=28
};

struct RAT_STRUCT
{
 /* 0x00 */ PHD_3DPOS pos; // size=20, offset=0
 /* 0x14 */ short room_number; // size=0, offset=20
 /* 0x16 */ short speed; // size=0, offset=22
 /* 0x18 */ short fallspeed; // size=0, offset=24
 /* 0x1A */ unsigned char On; // size=0, offset=26
 /* 0x1B */ unsigned char flags; // size=0, offset=27
};

struct BAT_STRUCT
{
 /* 0x00 */ PHD_3DPOS pos; // size=20, offset=0
 /* 0x14 */ short room_number; // size=0, offset=20
 /* 0x16 */ short speed; // size=0, offset=22
 /* 0x18 */ short Counter; // size=0, offset=24
 /* 0x1A */ short LaraTarget; // size=0, offset=26
 /* 0x1C */ char XTarget; // size=0, offset=28
 /* 0x1D */ char ZTarget; // size=0, offset=29
 /* 0x1E */ unsigned char On; // size=0, offset=30
 /* 0x1F */ unsigned char flags; // size=0, offset=31
};

struct SPIDER_STRUCT
{
 /* 0x00 */ PHD_3DPOS pos; // size=20, offset=0
 /* 0x14 */ short room_number; // size=0, offset=20
 /* 0x16 */ short speed; // size=0, offset=22
 /* 0x18 */ short fallspeed; // size=0, offset=24
 /* 0x1A */ unsigned char On; // size=0, offset=26
 /* 0x1B */ unsigned char flags; // size=0, offset=27
};

struct TWOGUN_INFO
{
 /* 0x00 */ PHD_3DPOS pos; // size=20, offset=0
 /* 0x14 */ short life; // size=0, offset=20
 /* 0x16 */ short coil; // size=0, offset=22
 /* 0x18 */ short spin; // size=0, offset=24
 /* 0x1A */ short spinadd; // size=0, offset=26
 /* 0x1C */ short length; // size=0, offset=28
 /* 0x1E */ short dlength; // size=0, offset=30
 /* 0x20 */ short size; // size=0, offset=32
 /* 0x22 */ char r; // size=0, offset=34
 /* 0x23 */ char g; // size=0, offset=35
 /* 0x24 */ char b; // size=0, offset=36
 /* 0x25 */ char fadein; // size=0, offset=37
};

struct CHARDEF
{
#if PC_VERSION
			float u;
			float v;
			short w;
			short h;
			short YOffset;
#else
 /* 0x00 */ unsigned char u; // size=0, offset=0
 /* 0x01 */ unsigned char v; // size=0, offset=1
 /* 0x02 */ unsigned char w; // size=0, offset=2
 /* 0x03 */ unsigned char h; // size=0, offset=3
 /* 0x04 */ char YOffset; // size=0, offset=4
#endif
 /* 0x05 */ unsigned char TopShade; // size=0, offset=5
 /* 0x06 */ unsigned char BottomShade; // size=0, offset=6
};

struct COLL_INFO
{
 /* 0x00 */ long mid_floor; // size=0, offset=0
 /* 0x04 */ long mid_ceiling; // size=0, offset=4
 /* 0x08 */ long mid_type; // size=0, offset=8
 /* 0x0C */ long front_floor; // size=0, offset=12
 /* 0x10 */ long front_ceiling; // size=0, offset=16
 /* 0x14 */ long front_type; // size=0, offset=20
 /* 0x18 */ long left_floor; // size=0, offset=24
 /* 0x1C */ long left_ceiling; // size=0, offset=28
 /* 0x20 */ long left_type; // size=0, offset=32
 /* 0x24 */ long right_floor; // size=0, offset=36
 /* 0x28 */ long right_ceiling; // size=0, offset=40
 /* 0x2C */ long right_type; // size=0, offset=44
 /* 0x30 */ long left_floor2; // size=0, offset=48
 /* 0x34 */ long left_ceiling2; // size=0, offset=52
 /* 0x38 */ long left_type2; // size=0, offset=56
 /* 0x3C */ long right_floor2; // size=0, offset=60
 /* 0x40 */ long right_ceiling2; // size=0, offset=64
 /* 0x44 */ long right_type2; // size=0, offset=68
 /* 0x48 */ long radius; // size=0, offset=72
 /* 0x4C */ long bad_pos; // size=0, offset=76
 /* 0x50 */ long bad_neg; // size=0, offset=80
 /* 0x54 */ long bad_ceiling; // size=0, offset=84
 /* 0x58 */ PHD_VECTOR shift; // size=12, offset=88
 /* 0x64 */ PHD_VECTOR old; // size=12, offset=100
 /* 0x70 */ short old_anim_state; // size=0, offset=112
 /* 0x72 */ short old_anim_number; // size=0, offset=114
 /* 0x74 */ short old_frame_number; // size=0, offset=116
 /* 0x76 */ short facing; // size=0, offset=118
 /* 0x78 */ short quadrant; // size=0, offset=120
 /* 0x7A */ short coll_type; // size=0, offset=122 USE ENUM CT_*
 /* 0x7C */ short* trigger; // size=0, offset=124
 /* 0x80 */ char tilt_x; // size=0, offset=128
 /* 0x81 */ char tilt_z; // size=0, offset=129
 /* 0x82 */ char hit_by_baddie; // size=0, offset=130
 /* 0x83 */ char hit_static; // size=0, offset=131
 /* 0x84 */ unsigned short slopes_are_walls : 2; // offset=132.0
			unsigned short slopes_are_pits : 1; // offset=132.2
			unsigned short lava_is_pit : 1; // offset=132.3
			unsigned short enable_baddie_push : 1; // offset=132.4
			unsigned short enable_spaz : 1; // offset=132.5
			unsigned short hit_ceiling : 1; // offset=132.6
};

struct ANIM_STRUCT
{
 /* 0x00 */ short* frame_ptr; // size=0, offset=0
 /* 0x04 */ short interpolation; // size=0, offset=4
 /* 0x06 */ short current_anim_state; // size=0, offset=6
 /* 0x08 */ long velocity; // size=0, offset=8
 /* 0x0C */ long acceleration; // size=0, offset=12
 /* 0x10 */ long Xvelocity; // size=0, offset=16
 /* 0x14 */ long Xacceleration; // size=0, offset=20
 /* 0x18 */ short frame_base; // size=0, offset=24
 /* 0x1A */ short frame_end; // size=0, offset=26
 /* 0x1C */ short jump_anim_num; // size=0, offset=28
 /* 0x1E */ short jump_frame_num; // size=0, offset=30
 /* 0x20 */ short number_changes; // size=0, offset=32
 /* 0x22 */ short change_index; // size=0, offset=34
 /* 0x24 */ short number_commands; // size=0, offset=36
 /* 0x26 */ short command_index; // size=0, offset=38
};

struct SPARKS
{
 /* 0x00 */ long x; // size=0, offset=0
 /* 0x04 */ long y; // size=0, offset=4
 /* 0x08 */ long z; // size=0, offset=8
 /* 0x0C */ short Xvel; // size=0, offset=12
 /* 0x0E */ short Yvel; // size=0, offset=14
 /* 0x10 */ short Zvel; // size=0, offset=16
 /* 0x12 */ short Gravity; // size=0, offset=18
 /* 0x14 */ short RotAng; // size=0, offset=20
 /* 0x16 */ short Flags; // size=0, offset=22
 /* 0x18 */ unsigned char sSize; // size=0, offset=24
 /* 0x19 */ unsigned char dSize; // size=0, offset=25
 /* 0x1A */ unsigned char Size; // size=0, offset=26
 /* 0x1B */ unsigned char Friction; // size=0, offset=27
 /* 0x1C */ unsigned char Scalar; // size=0, offset=28
 /* 0x1D */ unsigned char Def; // size=0, offset=29
 /* 0x1E */ char RotAdd; // size=0, offset=30
 /* 0x1F */ char MaxYvel; // size=0, offset=31
 /* 0x20 */ unsigned char On; // size=0, offset=32
 /* 0x21 */ unsigned char sR; // size=0, offset=33
 /* 0x22 */ unsigned char sG; // size=0, offset=34
 /* 0x23 */ unsigned char sB; // size=0, offset=35
 /* 0x24 */ unsigned char dR; // size=0, offset=36
 /* 0x25 */ unsigned char dG; // size=0, offset=37
 /* 0x26 */ unsigned char dB; // size=0, offset=38
 /* 0x27 */ unsigned char R; // size=0, offset=39
 /* 0x28 */ unsigned char G; // size=0, offset=40
 /* 0x29 */ unsigned char B; // size=0, offset=41
 /* 0x2A */ unsigned char ColFadeSpeed; // size=0, offset=42
 /* 0x2B */ unsigned char FadeToBlack; // size=0, offset=43
 /* 0x2C */ unsigned char sLife; // size=0, offset=44
 /* 0x2D */ unsigned char Life; // size=0, offset=45
 /* 0x2E */ unsigned char TransType; // size=0, offset=46
 /* 0x2F */ unsigned char extras; // size=0, offset=47
 /* 0x30 */ char Dynamic; // size=0, offset=48
 /* 0x31 */ unsigned char FxObj; // size=0, offset=49
 /* 0x32 */ unsigned char RoomNumber; // size=0, offset=50
 /* 0x33 */ unsigned char NodeNumber; // size=0, offset=51
};

struct ACTORME
{
 /* 0x00 */ int offset; // size=0, offset=0
 /* 0x04 */ short objslot; // size=0, offset=4
 /* 0x06 */ short nodes; // size=0, offset=6
};

struct RTDECODE
{
 /* 0x00 */ unsigned long length; // size=0, offset=0
 /* 0x04 */ unsigned long off; // size=0, offset=4
 /* 0x08 */ unsigned short counter; // size=0, offset=8
 /* 0x0A */ unsigned short data; // size=0, offset=10
 /* 0x0C */ unsigned char decodetype; // size=0, offset=12
 /* 0x0D */ unsigned char packmethod; // size=0, offset=13
 /* 0x0E */ unsigned short padfuck; // size=0, offset=14
};

struct PACKNODE
{
 /* 0x00 */ short xrot_run; // size=0, offset=0
 /* 0x02 */ short yrot_run; // size=0, offset=2
 /* 0x04 */ short zrot_run; // size=0, offset=4
 /* 0x06 */ short xkey; // size=0, offset=6
 /* 0x08 */ short ykey; // size=0, offset=8
 /* 0x0A */ short zkey; // size=0, offset=10
 /* 0x0C */ RTDECODE decode_x; // size=16, offset=12
 /* 0x1C */ RTDECODE decode_y; // size=16, offset=28
 /* 0x2C */ RTDECODE decode_z; // size=16, offset=44
 /* 0x3C */ unsigned long xlength; // size=0, offset=60
 /* 0x40 */ unsigned long ylength; // size=0, offset=64
 /* 0x44 */ unsigned long zlength; // size=0, offset=68
 /* 0x48 */ char* xpacked; // size=0, offset=72
 /* 0x4C */ char* ypacked; // size=0, offset=76
 /* 0x50 */ char* zpacked; // size=0, offset=80
};

struct NODELOADHEADER
{
 /* 0x00 */ short xkey; // size=0, offset=0
 /* 0x02 */ short ykey; // size=0, offset=2
 /* 0x04 */ short zkey; // size=0, offset=4
 /* 0x06 */ short packmethod; // size=0, offset=6
 /* 0x08 */ short xlength; // size=0, offset=8
 /* 0x0A */ short ylength; // size=0, offset=10
 /* 0x0C */ short zlength; // size=0, offset=12
};

struct RESIDENT_THING
{
 /* 0x00 */ char* packed_data; // size=0, offset=0
};

struct NEW_CUTSCENE
{
 /* 0x00 */ short numactors; // size=0, offset=0
 /* 0x02 */ short numframes; // size=0, offset=2
 /* 0x04 */ int orgx; // size=0, offset=4
 /* 0x08 */ int orgy; // size=0, offset=8
 /* 0x0C */ int orgz; // size=0, offset=12
 /* 0x10 */ int audio_track; // size=0, offset=16
 /* 0x14 */ int camera_offset; // size=0, offset=20
 /* 0x18 */ ACTORME actor_data[10]; // size=80, offset=24
};

struct CUTSEQ_ROUTINES
{
 /* 0x00 */ void(*init_func)(); // size=0, offset=0
 /* 0x04 */ void(*control_func)(); // size=0, offset=4
 /* 0x08 */ void(*end_func)(); // size=0, offset=8
};

struct DOORPOS_DATA
{
 /* 0x00 */ FLOOR_INFO* floor; // size=8, offset=0
 /* 0x04 */ FLOOR_INFO data; // size=8, offset=4
 /* 0x0C */ short block; // size=0, offset=12
};

struct DOOR_DATA
{
 /* 0x00 */ DOORPOS_DATA d1; // size=16, offset=0
 /* 0x10 */ DOORPOS_DATA d1flip; // size=16, offset=16
 /* 0x20 */ DOORPOS_DATA d2; // size=16, offset=32
 /* 0x30 */ DOORPOS_DATA d2flip; // size=16, offset=48
 /* 0x40 */ short Opened; // size=0, offset=64
 /* 0x44 */ short* dptr1; // size=0, offset=68
 /* 0x48 */ short* dptr2; // size=0, offset=72
 /* 0x4C */ short* dptr3; // size=0, offset=76
 /* 0x50 */ short* dptr4; // size=0, offset=80
 /* 0x54 */ char dn1; // size=0, offset=84
 /* 0x55 */ char dn2; // size=0, offset=85
 /* 0x56 */ char dn3; // size=0, offset=86
 /* 0x57 */ char dn4; // size=0, offset=87
 /* 0x58 */ ITEM_INFO* item; // size=144, offset=88
};

struct CHANGE_STRUCT
{
 /* 0x00 */ short goal_anim_state; // size=0, offset=0
 /* 0x02 */ short number_ranges; // size=0, offset=2
 /* 0x04 */ short range_index; // size=0, offset=4
};
struct RANGE_STRUCT
{
 /* 0x00 */ short start_frame; // size=0, offset=0
 /* 0x02 */ short end_frame; // size=0, offset=2
 /* 0x04 */ short link_anim_num; // size=0, offset=4
 /* 0x06 */ short link_frame_num; // size=0, offset=6
};

struct door_vbuf
{
 /* 0x00 */ long xv; // size=0, offset=0
 /* 0x04 */ long yv; // size=0, offset=4
 /* 0x08 */ long zv; // size=0, offset=8
};

struct BITE_INFO
{
 /* 0x00 */ long x; // size=0, offset=0
 /* 0x04 */ long y; // size=0, offset=4
 /* 0x08 */ long z; // size=0, offset=8
 /* 0x0C */ long mesh_num; // size=0, offset=12
};

struct box_info
{
 /* 0x00 */ unsigned char left; // size=0, offset=0
 /* 0x01 */ unsigned char right; // size=0, offset=1
 /* 0x02 */ unsigned char top; // size=0, offset=2
 /* 0x03 */ unsigned char bottom; // size=0, offset=3
 /* 0x04 */ short height; // size=0, offset=4
 /* 0x06 */ short overlap_index; // size=0, offset=6
};

struct AI_info
{
 /* 0x00 */ short zone_number; // size=0, offset=0
 /* 0x02 */ short enemy_zone; // size=0, offset=2
 /* 0x04 */ long distance; // size=0, offset=4
 /* 0x08 */ long ahead; // size=0, offset=8
 /* 0x0C */ long bite; // size=0, offset=12
 /* 0x10 */ short angle; // size=0, offset=16
 /* 0x12 */ short x_angle; // size=0, offset=18
 /* 0x14 */ short enemy_facing; // size=0, offset=20
};

struct AIOBJECT
{
 /* 0x00 */ short object_number; // size=0, offset=0
 /* 0x02 */ short room_number; // size=0, offset=2
 /* 0x04 */ long x; // size=0, offset=4
 /* 0x08 */ long y; // size=0, offset=8
 /* 0x0C */ long z; // size=0, offset=12
 /* 0x10 */ short trigger_flags; // size=0, offset=16
 /* 0x12 */ short flags; // size=0, offset=18
 /* 0x14 */ short y_rot; // size=0, offset=20
 /* 0x16 */ short box_number; // size=0, offset=22
};

struct CAMERA_INFO
{
 /* 0x00 */ GAME_VECTOR pos; // size=16, offset=0
 /* 0x10 */ GAME_VECTOR target; // size=16, offset=16
 /* 0x20 */ enum camera_type type; // size=4, offset=32
 /* 0x24 */ enum camera_type old_type; // size=4, offset=36
 /* 0x28 */ long shift; // size=0, offset=40
 /* 0x2C */ long flags; // size=0, offset=44
 /* 0x30 */ long fixed_camera; // size=0, offset=48
 /* 0x34 */ long number_frames; // size=0, offset=52
 /* 0x38 */ long bounce; // size=0, offset=56
 /* 0x3C */ long underwater; // size=0, offset=60
 /* 0x40 */ long target_distance; // size=0, offset=64
 /* 0x44 */ short target_angle; // size=0, offset=68
 /* 0x46 */ short target_elevation; // size=0, offset=70
 /* 0x48 */ short actual_elevation; // size=0, offset=72
 /* 0x4A */ short actual_angle; // size=0, offset=74
 /* 0x4C */ short lara_node; // size=0, offset=76
 /* 0x4E */ short box; // size=0, offset=78
 /* 0x50 */ short number; // size=0, offset=80
 /* 0x52 */ short last; // size=0, offset=82
 /* 0x54 */ short timer; // size=0, offset=84
 /* 0x56 */ short speed; // size=0, offset=86
 /* 0x58 */ short targetspeed; // size=0, offset=88
 /* 0x5C */ ITEM_INFO* item; // size=144, offset=92
 /* 0x60 */ ITEM_INFO* last_item; // size=144, offset=96
 /* 0x64 */ OBJECT_VECTOR* fixed; // size=16, offset=100
 /* 0x68 */ int mike_at_lara; // size=0, offset=104
 /* 0x6C */ PHD_VECTOR mike_pos; // size=12, offset=108
};

struct SHATTER_ITEM
{
 /* 0x00 */ SPHERE Sphere; // size=16, offset=0
 //  FIX ME:
 //  Excuse me? For some reason, I need to specify struct here or it'll break.
 //  The compiler doesnt seem to care about the other wrong typedefs?
 /* 0x10 */ struct ITEM_LIGHT* il; // size=48, offset=16
 /* 0x14 */ short* meshp; // size=0, offset=20
 /* 0x18 */ long Bit; // size=0, offset=24
 /* 0x1C */ short YRot; // size=0, offset=28
 /* 0x1E */ short Flags; // size=0, offset=30
};

struct OLD_CAMERA
{
 /* 0x00 */ short current_anim_state; // size=0, offset=0
 /* 0x02 */ short goal_anim_state; // size=0, offset=2
 /* 0x04 */ long target_distance; // size=0, offset=4
 /* 0x08 */ short target_angle; // size=0, offset=8
 /* 0x0A */ short target_elevation; // size=0, offset=10
 /* 0x0C */ short actual_elevation; // size=0, offset=12
 /* 0x10 */ PHD_3DPOS pos; // size=20, offset=16
 /* 0x24 */ PHD_3DPOS pos2; // size=20, offset=36
 /* 0x38 */ PHD_VECTOR t; // size=12, offset=56
};

struct DEBRIS_STRUCT
{
 /* 0x00 */ void* TextInfo; // size=0, offset=0
 /* 0x04 */ long x; // size=0, offset=4
 /* 0x08 */ long y; // size=0, offset=8
 /* 0x0C */ long z; // size=0, offset=12
 /* 0x10 */ short XYZOffsets1[3]; // size=6, offset=16
 /* 0x16 */ short Dir; // size=0, offset=22
 /* 0x18 */ short XYZOffsets2[3]; // size=6, offset=24
 /* 0x1E */ short Speed; // size=0, offset=30
 /* 0x20 */ short XYZOffsets3[3]; // size=6, offset=32
 /* 0x26 */ short Yvel; // size=0, offset=38
 /* 0x28 */ short Gravity; // size=0, offset=40
 /* 0x2A */ short RoomNumber; // size=0, offset=42
 /* 0x2C */ unsigned char On; // size=0, offset=44
 /* 0x2D */ unsigned char XRot; // size=0, offset=45
 /* 0x2E */ unsigned char YRot; // size=0, offset=46
 /* 0x2F */ unsigned char r; // size=0, offset=47
 /* 0x30 */ unsigned char g; // size=0, offset=48
 /* 0x31 */ unsigned char b; // size=0, offset=49
 /* 0x32 */ unsigned char Pad[2]; // size=2, offset=50
};

struct SPOTCAM
{
 /* 0x00 */ long x; // size=0, offset=0
 /* 0x04 */ long y; // size=0, offset=4
 /* 0x08 */ long z; // size=0, offset=8
 /* 0x0C */ long tx; // size=0, offset=12
 /* 0x10 */ long ty; // size=0, offset=16
 /* 0x14 */ long tz; // size=0, offset=20
 /* 0x18 */ unsigned char sequence; // size=0, offset=24
 /* 0x19 */ unsigned char camera; // size=0, offset=25
 /* 0x1A */ short fov; // size=0, offset=26
 /* 0x1C */ short roll; // size=0, offset=28
 /* 0x1E */ short timer; // size=0, offset=30
 /* 0x20 */ short speed; // size=0, offset=32
 /* 0x22 */ short flags; // size=0, offset=34
 /* 0x24 */ short room_number; // size=0, offset=36
 /* 0x26 */ short pad; // size=0, offset=38
};

struct QUAKE_CAM
{
 /* 0x00 */ GAME_VECTOR spos; // size=16, offset=0
 /* 0x10 */ GAME_VECTOR epos; // size=16, offset=16
};

struct DYNAMIC
{
 /* 0x00 */ long x; // size=0, offset=0
 /* 0x04 */ long y; // size=0, offset=4
 /* 0x08 */ long z; // size=0, offset=8
 /* 0x0C */ unsigned char on; // size=0, offset=12
 /* 0x0D */ unsigned char r; // size=0, offset=13
 /* 0x0E */ unsigned char g; // size=0, offset=14
 /* 0x0F */ unsigned char b; // size=0, offset=15
 /* 0x10 */ unsigned short falloff; // size=0, offset=16
 /* 0x12 */ unsigned char used; // size=0, offset=18
 /* 0x13 */ unsigned char pad1[1]; // size=1, offset=19
 /* 0x14 */ long FalloffScale; // size=0, offset=20
};

struct SP_DYNAMIC
{
 /* 0x00 */ unsigned char On; // size=0, offset=0
 /* 0x01 */ unsigned char Falloff; // size=0, offset=1
 /* 0x02 */ unsigned char R; // size=0, offset=2
 /* 0x03 */ unsigned char G; // size=0, offset=3
 /* 0x04 */ unsigned char B; // size=0, offset=4
 /* 0x05 */ unsigned char Flags; // size=0, offset=5
 /* 0x06 */ unsigned char Pad[2]; // size=2, offset=6
};

struct SPLASH_STRUCT
{
 /* 0x00 */ long x; // size=0, offset=0
 /* 0x04 */ long y; // size=0, offset=4
 /* 0x08 */ long z; // size=0, offset=8
 /* 0x0C */ short InnerRad; // size=0, offset=12
 /* 0x0E */ short InnerSize; // size=0, offset=14
 /* 0x10 */ short InnerRadVel; // size=0, offset=16
 /* 0x12 */ short InnerYVel; // size=0, offset=18
 /* 0x14 */ short InnerY; // size=0, offset=20
 /* 0x16 */ short MiddleRad; // size=0, offset=22
 /* 0x18 */ short MiddleSize; // size=0, offset=24
 /* 0x1A */ short MiddleRadVel; // size=0, offset=26
 /* 0x1C */ short MiddleYVel; // size=0, offset=28
 /* 0x1E */ short MiddleY; // size=0, offset=30
 /* 0x20 */ short OuterRad; // size=0, offset=32
 /* 0x22 */ short OuterSize; // size=0, offset=34
 /* 0x24 */ short OuterRadVel; // size=0, offset=36
 /* 0x26 */ char flags; // size=0, offset=38
 /* 0x27 */ unsigned char life; // size=0, offset=39
};

struct RIPPLE_STRUCT
{
 /* 0x00 */ long x; // size=0, offset=0
 /* 0x04 */ long y; // size=0, offset=4
 /* 0x08 */ long z; // size=0, offset=8
 /* 0x0C */ char flags; // size=0, offset=12
 /* 0x0D */ unsigned char life; // size=0, offset=13
 /* 0x0E */ unsigned char size; // size=0, offset=14
 /* 0x0F */ unsigned char init; // size=0, offset=15
};

struct SPLASH_SETUP
{
 /* 0x00 */ long x; // size=0, offset=0
 /* 0x04 */ long y; // size=0, offset=4
 /* 0x08 */ long z; // size=0, offset=8
 /* 0x0C */ short InnerRad; // size=0, offset=12
 /* 0x0E */ short InnerSize; // size=0, offset=14
 /* 0x10 */ short InnerRadVel; // size=0, offset=16
 /* 0x12 */ short InnerYVel; // size=0, offset=18
 /* 0x14 */ short pad1; // size=0, offset=20
 /* 0x16 */ short MiddleRad; // size=0, offset=22
 /* 0x18 */ short MiddleSize; // size=0, offset=24
 /* 0x1A */ short MiddleRadVel; // size=0, offset=26
 /* 0x1C */ short MiddleYVel; // size=0, offset=28
 /* 0x1E */ short pad2; // size=0, offset=30
 /* 0x20 */ short OuterRad; // size=0, offset=32
 /* 0x22 */ short OuterSize; // size=0, offset=34
 /* 0x24 */ short OuterRadVel; // size=0, offset=36
 /* 0x26 */ short pad3; // size=0, offset=38
};

struct FIRE_LIST
{
 /* 0x00 */ long x; // size=0, offset=0
 /* 0x04 */ long y; // size=0, offset=4
 /* 0x08 */ long z; // size=0, offset=8
 /* 0x0C */ char on; // size=0, offset=12
 /* 0x0D */ char size; // size=0, offset=13
 /* 0x0E */ short room_number; // size=0, offset=14
};

struct FIRE_SPARKS
{
 /* 0x00 */ short x; // size=0, offset=0
 /* 0x02 */ short y; // size=0, offset=2
 /* 0x04 */ short z; // size=0, offset=4
 /* 0x06 */ short Xvel; // size=0, offset=6
 /* 0x08 */ short Yvel; // size=0, offset=8
 /* 0x0A */ short Zvel; // size=0, offset=10
 /* 0x0C */ short Gravity; // size=0, offset=12
 /* 0x0E */ short RotAng; // size=0, offset=14
 /* 0x10 */ short Flags; // size=0, offset=16
 /* 0x12 */ unsigned char sSize; // size=0, offset=18
 /* 0x13 */ unsigned char dSize; // size=0, offset=19
 /* 0x14 */ unsigned char Size; // size=0, offset=20
 /* 0x15 */ unsigned char Friction; // size=0, offset=21
 /* 0x16 */ unsigned char Scalar; // size=0, offset=22
 /* 0x17 */ unsigned char Def; // size=0, offset=23
 /* 0x18 */ char RotAdd; // size=0, offset=24
 /* 0x19 */ char MaxYvel; // size=0, offset=25
 /* 0x1A */ unsigned char On; // size=0, offset=26
 /* 0x1B */ unsigned char sR; // size=0, offset=27
 /* 0x1C */ unsigned char sG; // size=0, offset=28
 /* 0x1D */ unsigned char sB; // size=0, offset=29
 /* 0x1E */ unsigned char dR; // size=0, offset=30
 /* 0x1F */ unsigned char dG; // size=0, offset=31
 /* 0x20 */ unsigned char dB; // size=0, offset=32
 /* 0x21 */ unsigned char R; // size=0, offset=33
 /* 0x22 */ unsigned char G; // size=0, offset=34
 /* 0x23 */ unsigned char B; // size=0, offset=35
 /* 0x24 */ unsigned char ColFadeSpeed; // size=0, offset=36
 /* 0x25 */ unsigned char FadeToBlack; // size=0, offset=37
 /* 0x26 */ unsigned char sLife; // size=0, offset=38
 /* 0x27 */ unsigned char Life; // size=0, offset=39
};

struct SMOKE_SPARKS
{
 /* 0x00 */ long x; // size=0, offset=0
 /* 0x04 */ long y; // size=0, offset=4
 /* 0x08 */ long z; // size=0, offset=8
 /* 0x0C */ short Xvel; // size=0, offset=12
 /* 0x0E */ short Yvel; // size=0, offset=14
 /* 0x10 */ short Zvel; // size=0, offset=16
 /* 0x12 */ short Gravity; // size=0, offset=18
 /* 0x14 */ short RotAng; // size=0, offset=20
 /* 0x16 */ short Flags; // size=0, offset=22
 /* 0x18 */ unsigned char sSize; // size=0, offset=24
 /* 0x19 */ unsigned char dSize; // size=0, offset=25
 /* 0x1A */ unsigned char Size; // size=0, offset=26
 /* 0x1B */ unsigned char Friction; // size=0, offset=27
 /* 0x1C */ unsigned char Scalar; // size=0, offset=28
 /* 0x1D */ unsigned char Def; // size=0, offset=29
 /* 0x1E */ char RotAdd; // size=0, offset=30
 /* 0x1F */ char MaxYvel; // size=0, offset=31
 /* 0x20 */ unsigned char On; // size=0, offset=32
 /* 0x21 */ unsigned char sShade; // size=0, offset=33
 /* 0x22 */ unsigned char dShade; // size=0, offset=34
 /* 0x23 */ unsigned char Shade; // size=0, offset=35
 /* 0x24 */ unsigned char ColFadeSpeed; // size=0, offset=36
 /* 0x25 */ unsigned char FadeToBlack; // size=0, offset=37
 /* 0x26 */ char sLife; // size=0, offset=38
 /* 0x27 */ char Life; // size=0, offset=39
 /* 0x28 */ unsigned char TransType; // size=0, offset=40
 /* 0x29 */ unsigned char FxObj; // size=0, offset=41
 /* 0x2A */ unsigned char NodeNumber; // size=0, offset=42
 /* 0x2B */ unsigned char mirror; // size=0, offset=43
};

struct BLOOD_STRUCT
{
 /* 0x00 */ long x; // size=0, offset=0
 /* 0x04 */ long y; // size=0, offset=4
 /* 0x08 */ long z; // size=0, offset=8
 /* 0x0C */ short Xvel; // size=0, offset=12
 /* 0x0E */ short Yvel; // size=0, offset=14
 /* 0x10 */ short Zvel; // size=0, offset=16
 /* 0x12 */ short Gravity; // size=0, offset=18
 /* 0x14 */ short RotAng; // size=0, offset=20
 /* 0x16 */ unsigned char sSize; // size=0, offset=22
 /* 0x17 */ unsigned char dSize; // size=0, offset=23
 /* 0x18 */ unsigned char Size; // size=0, offset=24
 /* 0x19 */ unsigned char Friction; // size=0, offset=25
 /* 0x1A */ char RotAdd; // size=0, offset=26
 /* 0x1B */ unsigned char On; // size=0, offset=27
 /* 0x1C */ unsigned char sShade; // size=0, offset=28
 /* 0x1D */ unsigned char dShade; // size=0, offset=29
 /* 0x1E */ unsigned char Shade; // size=0, offset=30
 /* 0x1F */ unsigned char ColFadeSpeed; // size=0, offset=31
 /* 0x20 */ unsigned char FadeToBlack; // size=0, offset=32
 /* 0x21 */ char sLife; // size=0, offset=33
 /* 0x22 */ char Life; // size=0, offset=34
 /* 0x23 */ char Pad; // size=0, offset=35
};

struct GUNSHELL_STRUCT
{
 /* 0x00 */ PHD_3DPOS pos; // size=20, offset=0
 /* 0x14 */ short fallspeed; // size=0, offset=20
 /* 0x16 */ short room_number; // size=0, offset=22
 /* 0x18 */ short speed; // size=0, offset=24
 /* 0x1A */ short counter; // size=0, offset=26
 /* 0x1C */ short DirXrot; // size=0, offset=28
 /* 0x1E */ short object_number; // size=0, offset=30
};

struct BUBBLE_STRUCT
{
 /* 0x00 */ PHD_VECTOR pos; // size=12, offset=0
 /* 0x0C */ short room_number; // size=0, offset=12
 /* 0x0E */ short speed; // size=0, offset=14
 /* 0x10 */ short size; // size=0, offset=16
 /* 0x12 */ short dsize; // size=0, offset=18
 /* 0x14 */ unsigned char shade; // size=0, offset=20
 /* 0x15 */ unsigned char vel; // size=0, offset=21
 /* 0x16 */ unsigned char y_rot; // size=0, offset=22
 /* 0x17 */ char Flags; // size=0, offset=23
 /* 0x18 */ short Xvel; // size=0, offset=24
 /* 0x1A */ short Yvel; // size=0, offset=26
 /* 0x1C */ short Zvel; // size=0, offset=28
 /* 0x1E */ short Pad; // size=0, offset=30
};

struct GUNFLASH_STRUCT
{
 /* 0x00 */ MATRIX3D matrix; // size=32, offset=0
 /* 0x20 */ short on; // size=0, offset=32
};

struct NODEOFFSET_INFO
{
 /* 0x00 */ short x; // size=0, offset=0
 /* 0x02 */ short y; // size=0, offset=2
 /* 0x04 */ short z; // size=0, offset=4
 /* 0x06 */ char mesh_num; // size=0, offset=6
 /* 0x07 */ unsigned char GotIt; // size=0, offset=7
};

struct SHOCKWAVE_STRUCT
{
 /* 0x00 */ long x; // size=0, offset=0
 /* 0x04 */ long y; // size=0, offset=4
 /* 0x08 */ long z; // size=0, offset=8
 /* 0x0C */ short InnerRad; // size=0, offset=12
 /* 0x0E */ short OuterRad; // size=0, offset=14
 /* 0x10 */ short XRot; // size=0, offset=16
 /* 0x12 */ short Flags; // size=0, offset=18
 /* 0x14 */ unsigned char r; // size=0, offset=20
 /* 0x15 */ unsigned char g; // size=0, offset=21
 /* 0x16 */ unsigned char b; // size=0, offset=22
 /* 0x17 */ unsigned char life; // size=0, offset=23
 /* 0x18 */ short Speed; // size=0, offset=24
 /* 0x1A */ short Temp; // size=0, offset=26
};

struct HAIR_STRUCT
{
 /* 0x00 */ PHD_3DPOS pos; // size=20, offset=0
 /* 0x14 */ PHD_VECTOR vel; // size=12, offset=20
};

struct DISPLAYPU
{
 /* 0x00 */ short life; // size=0, offset=0
 /* 0x02 */ short object_number; // size=0, offset=2
};

struct INVOBJ
{
 /* 0x00 */ short object_number; // size=0, offset=0
 /* 0x02 */ short yoff; // size=0, offset=2
 /* 0x04 */ short scale1; // size=0, offset=4
 /* 0x06 */ short yrot; // size=0, offset=6
 /* 0x08 */ short xrot; // size=0, offset=8
 /* 0x0A */ short zrot; // size=0, offset=10
 /* 0x0C */ short flags; // size=0, offset=12
 /* 0x0E */ short objname; // size=0, offset=14
 /* 0x10 */ unsigned long meshbits; // size=0, offset=16
};

struct OBJLIST
{
 /* 0x00 */ short invitem; // size=0, offset=0
 /* 0x02 */ unsigned short yrot; // size=0, offset=2
 /* 0x04 */ unsigned short bright; // size=0, offset=4
};

struct RINGME
{
 /* 0x000 */ OBJLIST current_object_list[100]; // size=600, offset=0
 /* 0x258 */ int ringactive; // size=0, offset=600
 /* 0x25C */ int objlistmovement; // size=0, offset=604
 /* 0x260 */ int curobjinlist; // size=0, offset=608
 /* 0x264 */ int numobjectsinlist; // size=0, offset=612
};

struct AMMOLIST
{
 /* 0x00 */ short invitem; // size=0, offset=0
 /* 0x02 */ short amount; // size=0, offset=2
 /* 0x04 */ unsigned short yrot; // size=0, offset=4
};
struct MENUTHANG
{
 /* 0x00 */ int type; // size=0, offset=0
 /* 0x04 */ char* text; // size=0, offset=4
};

struct COMBINELIST
{
 /* 0x00 */ void(*combine_routine)(int flag); // size=0, offset=0
 /* 0x04 */ short item1; // size=0, offset=4
 /* 0x06 */ short item2; // size=0, offset=6
 /* 0x08 */ short combined_item; // size=0, offset=8
};

struct WEAPON_INFO
{
 /* 0x00 */ short lock_angles[4]; // size=8, offset=0
 /* 0x08 */ short left_angles[4]; // size=8, offset=8
 /* 0x10 */ short right_angles[4]; // size=8, offset=16
 /* 0x18 */ short aim_speed; // size=0, offset=24
 /* 0x1A */ short shot_accuracy; // size=0, offset=26
 /* 0x1C */ short gun_height; // size=0, offset=28
 /* 0x1E */ short target_dist; // size=0, offset=30
 /* 0x20 */ char damage; // size=0, offset=32
 /* 0x21 */ char recoil_frame; // size=0, offset=33
 /* 0x22 */ char flash_time; // size=0, offset=34
 /* 0x23 */ char draw_frame; // size=0, offset=35
 /* 0x24 */ short sample_num; // size=0, offset=36
};

struct PISTOL_DEF
{
 /* 0x00 */ short ObjectNum; // size=0, offset=0
 /* 0x02 */ char Draw1Anim2; // size=0, offset=2
 /* 0x03 */ char Draw1Anim; // size=0, offset=3
 /* 0x04 */ char Draw2Anim; // size=0, offset=4
 /* 0x05 */ char RecoilAnim; // size=0, offset=5
};

struct SUBSUIT_INFO
{
 /* 0x00 */ short XRot; // size=0, offset=0
 /* 0x02 */ short dXRot; // size=0, offset=2
 /* 0x04 */ short XRotVel; // size=0, offset=4
 /* 0x06 */ short Vel[2]; // size=4, offset=6
 /* 0x0A */ short YVel; // size=0, offset=10
};

struct SAMPLE_INFO
{
 /* 0x00 */ short number; // size=0, offset=0
 /* 0x02 */ unsigned char volume; // size=0, offset=2
 /* 0x03 */ char radius; // size=0, offset=3
 /* 0x04 */ char randomness; // size=0, offset=4
 /* 0x05 */ char pitch; // size=0, offset=5
 /* 0x06 */ short flags; // size=0, offset=6
};

struct SoundSlot
{
 /* 0x00 */ int OrigVolume; // size=0, offset=0
 /* 0x04 */ int nVolume; // size=0, offset=4
 /* 0x08 */ int nPan; // size=0, offset=8
 /* 0x0C */ int nPitch; // size=0, offset=12
 /* 0x10 */ int nSampleInfo; // size=0, offset=16
 /* 0x14 */ unsigned long distance; // size=0, offset=20
 /* 0x18 */ PHD_VECTOR pos; // size=12, offset=24
};

struct FOOTPRINT
{
 /* 0x00 */ long x; // size=0, offset=0
 /* 0x04 */ long y; // size=0, offset=4
 /* 0x08 */ long z; // size=0, offset=8
 /* 0x0C */ short YRot; // size=0, offset=12
 /* 0x0E */ short Active; // size=0, offset=14
};

// ---------------------------------------------------------------
// OpenTomb structs // Miscellaneous test structs
// TODO: Remove these ideally. Strictly adhere to the PSX engine.
// ---------------------------------------------------------------

//Reconstructed, size hint = 8;
//maybe NODEOFFSET_INFO
struct MESH_STRUCT
{
 /* 0x00 */ short unk00;//0
 /* 0x02 */ short unk01;//2
 /* 0x04 */ long unk02;//4
 /* 0x08 */ unsigned char unk03;//8
};

struct mesh_header
{
 /* 0x00 */ short x;
 /* 0x02 */ short y;
 /* 0x04 */ short z;
 /* 0x06 */ short radius;
 /* 0x08 */ char vertices;
 /* 0x09 */ char flags;
 /* 0x0A */ short face_offset;
};

struct tr_vertex   // 6 bytes
{
 /* 0x00 */ short x;
 /* 0x02 */ short y;
 /* 0x04 */ short z;
};

struct tr_room_portal  // 32 bytes
{
 /* 0x00 */ unsigned short  AdjoiningRoom; // Which room this portal leads to
 /* 0x04 */ tr_vertex Normal;
 /* 0x08 */ tr_vertex Vertices[4];
};

#if PC_VERSION || PSXPC_VERSION || PSXPC_TEST
#pragma pack(pop)
#endif
#endif

#if PC_VERSION
#pragma clang diagnostic pop
#endif