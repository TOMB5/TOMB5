#ifndef TYPES_H
#define TYPES_H

// required for NULL macro because if we define it ourselves it shits brixes
#include <stdlib.h>
#include <stddef.h>


/*#ifndef ABS
#define ABS(x) (((x)<0)?(-(x)):(x))
#endif*/

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#ifndef MIN
#define MIN(x, y) (((x)<(y))?(x):(y))
#endif

#ifndef MAX
#define MAX(x, y) (((x)>(y))?(x):(y))
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef SIGN
#define SIGN(x) ((0 < (x)) - ((x) < 0))
#endif

// (65536 / 360) ~ 182.0444...
// Game used 182, so maybe our code will be more precise %)
#define ANGLE(x) (short)((x) * 65536.0 / 360.0)

#define SIN(x) (rcossin_tbl[((int)(x) >> 3) & 0x1FFE])
#define COS(x) (rcossin_tbl[(((int)(x) >> 3) & 0x1FFE) + 1])

#define TRIGMULT2(a, b) (((a) * (b)) >> W2V_SHIFT)
#define TRIGMULT2F(a, b) (((a) * (b)) / 16384.0f)
#define TRIGMULT3(a, b, c) TRIGMULT2(TRIGMULT2(a, b), c)

#if PC_VERSION
#define phd_atan_asm phd_atan
#endif
#if 0 // for later...
inline int phd_atan(long x, long y)
{
	char octant = 0;
	int res;
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
	return (int)(atan2(x, y) * 32768.0 / 3.14159265359);
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
#define SECTOR(x) (short)((x) * WALL_L)
#define CLICK 256

#define UNIT_SHADOW 256
#define UNIT_SHADOW_SHIFT 8



#define LARA_HITPOINTS 1000

#define ROUND_MUL_LOW(x, m) ((x) & ~(m - 1))

#define SECTOR_TO_WORLD(S) ((S) > (0) ? SECTOR((S) + 0.5) : (0))

#define XZ_GET_SECTOR(room, x, z) (r->floor[(int)((z) / 1024 + r->x_size * ((x) / 1024))])

#define PSXENGINE (PSXPC_VERSION || PSX_VERSION)

#define TEXTURE_PAGE (256 * 256)

#define W2V_SHIFT 		14				// Shift scale of View.Frame to World.Frame
#define	W2V_SCALE 		(1<<W2V_SHIFT)	// Scale of View Frame to World Frame

enum msoff {
	M00, M01, M02, M03,
	M10, M11, M12, M13,
	M20, M21, M22, M23
};

#ifndef CLAMP
#define CLAMP(x, a, b) ((x)<(a)?(a):((x)>(b)?(b):(x)))
#endif

#define CLAMPADD(x, a, b) ((x)<(a)?((x)+(a)):((x)>(b)?((x)-(b)):0))

#define RED(rgb) (((rgb) >> 16) & 0xFF)
#define GREEN(rgb) (((rgb) >> 8) & 0xFF)
#define BLUE(rgb) ((rgb) & 0xFF)
#define ALPHA(rgb) (((rgb) >> 24) & 0xFF)

#define RGBONLY(r, g, b) ((b & 0xFF) | (((g & 0xFF) | ((r & 0xFF) << 8)) << 8))
#define RGBA(r, g, b, a) (RGBONLY(r, g, b) | ((a) << 24))

#define NO_ROOM 0xFF

enum PRINT_OPTIONS
{
	PRINT_BLINK = 1 << 13,			// 0x2000
	PRINT_UNK14 = 1 << 14,			// 0x4000
	PRINT_CENTER = 1 << 15,			// 0x8000
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
	RF_SKYBOX_VISIBLE = (1 << 3),		    // 0x0008   speeds up rendering if no rendered room has this
	RF_WIND_BLOWS_PONYTAIL = (1 << 5),	    // 0x0020   also some particles
	RF_UNKNOWN_6 = (1 << 6),			    // 0x0040   used in official levels, no apparent effects
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

struct VECTOR
{
	long vx;
	long vy;
	long vz;
#if PSXENGINE
	long pad;
#endif
};

struct SVECTOR
{
	short vx;
	short vy;
	short vz;
	short pad;
};

struct CVECTOR
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char cd;
};

struct PHD_VECTOR
{
	long x;
	long y;
	long z;
};
#if PC_VERSION
#pragma pack(push, 1)
#endif
struct PHD_3DPOS
{
	long x_pos; // off 0 [64]
	long y_pos; // off 4 [68]
	long z_pos; // off 8 [72]
	short x_rot; // off 12 [76]
	short y_rot; // off 14 [78]
	short z_rot; // off 16 [80]
};

struct FLOOR_INFO
{
	unsigned short index; // size=0, offset=0
	unsigned short fx : 4; // offset=2.0
	unsigned short box : 11; // offset=2.4
	unsigned short stopper : 1; // offset=3.7
	unsigned char pit_room; // size=0, offset=4
	char floor; // size=0, offset=5
	unsigned char sky_room; // size=0, offset=6
	char ceiling; // size=0, offset=7
};

struct LIGHTINFO
{
	long x; // size=0, offset=0
	long y; // size=0, offset=4
	long z; // size=0, offset=8
	unsigned char Type; // size=0, offset=12
	unsigned char r; // size=0, offset=13
	unsigned char g; // size=0, offset=14
	unsigned char b; // size=0, offset=15
	short nx; // size=0, offset=16
	short ny; // size=0, offset=18
	short nz; // size=0, offset=20
	short Intensity; // size=0, offset=22
	unsigned char Inner; // size=0, offset=24
	unsigned char Outer; // size=0, offset=25
	short FalloffScale; // size=0, offset=26
	short Length; // size=0, offset=28
	short Cutoff; // size=0, offset=30
};

struct MESH_INFO
{
	long x; // size=0, offset=0
	long y; // size=0, offset=4
	long z; // size=0, offset=8
	short y_rot; // size=0, offset=12
	short shade; // size=0, offset=14
	short Flags; // size=0, offset=16
	short static_number; // size=0, offset=18
};

struct FX_INFO
{
	struct PHD_3DPOS pos; // size=20, offset=0
	short room_number; // size=0, offset=20
	short object_number; // size=0, offset=22
	short next_fx; // size=0, offset=24
	short next_active; // size=0, offset=26
	short speed; // size=0, offset=28
	short fallspeed; // size=0, offset=30
	short frame_number; // size=0, offset=32
	short counter; // size=0, offset=34
	short shade; // size=0, offset=36
	short flag1; // size=0, offset=38
	short flag2; // size=0, offset=40
};

struct lara_arm
{
	short* frame_base; // size=0, offset=0
	short frame_number; // size=0, offset=4
	short anim_number; // size=0, offset=6
	short lock; // size=0, offset=8
	short y_rot; // size=0, offset=10
	short x_rot; // size=0, offset=12
	short z_rot; // size=0, offset=14
	short flash_gun; // size=0, offset=16
};

struct box_node
{
	short exit_box; // size=0, offset=0
	unsigned short search_number; // size=0, offset=2
	short next_expansion; // size=0, offset=4
	short box_number; // size=0, offset=6
};

struct lot_info
{
	struct box_node* node; // size=8, offset=0
	short head; // size=0, offset=4
	short tail; // size=0, offset=6
	unsigned short search_number; // size=0, offset=8
	unsigned short block_mask; // size=0, offset=10
	short step; // size=0, offset=12
	short drop; // size=0, offset=14
	short zone_count; // size=0, offset=16
	short target_box; // size=0, offset=18
	short required_box; // size=0, offset=20
	short fly; // size=0, offset=22
	unsigned short can_jump : 1; // offset=24.0
	unsigned short can_monkey : 1; // offset=24.1
	unsigned short is_amphibious : 1; // offset=24.2
	unsigned short is_jumping : 1; // offset=24.3
	unsigned short is_monkeying : 1; // offset=24.4
	struct PHD_VECTOR target; // size=12, offset=28
	enum zone_type zone; // size=4, offset=40
};

struct ROPE_STRUCT
{
	struct PHD_VECTOR Segment[24]; // size=288, offset=0
	struct PHD_VECTOR Velocity[24]; // size=288, offset=288
	struct PHD_VECTOR NormalisedSegment[24]; // size=288, offset=576
	struct PHD_VECTOR MeshSegment[24]; // size=288, offset=864
	struct PHD_VECTOR Position; // size=12, offset=1152
	long SegmentLength; // size=0, offset=1164
	short Active; // size=0, offset=1168
	short Coiled; // size=0, offset=1170
};
struct lara_info {
	short item_number; // size=0, offset=0
	short gun_status; // size=0, offset=2
	short gun_type; // size=0, offset=4
	short request_gun_type; // size=0, offset=6
	short last_gun_type; // size=0, offset=8
	short calc_fallspeed; // size=0, offset=10
	short water_status; // size=0, offset=12
	short climb_status; // size=0, offset=14
	short pose_count; // size=0, offset=16
	short hit_frame; // size=0, offset=18
	short hit_direction; // size=0, offset=20
	short air; // size=0, offset=22
	short dive_count; // size=0, offset=24
	short death_count; // size=0, offset=26
	short current_active; // size=0, offset=28
	short current_xvel; // size=0, offset=30
	short current_yvel; // size=0, offset=32
	short current_zvel; // size=0, offset=34
	short spaz_effect_count; // size=0, offset=36
	short flare_age; // size=0, offset=38
	short BurnCount; // size=0, offset=40
	short weapon_item; // size=0, offset=42
	short back_gun; // size=0, offset=44
	short flare_frame; // size=0, offset=46
	short poisoned; // size=0, offset=48
	short dpoisoned; // size=0, offset=50
	unsigned char Anxiety; // size=0, offset=52
	unsigned char wet[15]; // size=15, offset=53
	unsigned short flare_control_left : 1; // offset=68.0
	unsigned short Unused1 : 1; // offset=68.1
	unsigned short look : 1; // offset=68.2
	unsigned short burn : 1; // offset=68.3
	unsigned short keep_ducked : 1; // offset=68.4
	unsigned short IsMoving : 1; // offset=68.5
	unsigned short CanMonkeySwing : 1; // offset=68.6
	unsigned short BurnBlue : 2; // offset=68.7
	unsigned short Gassed : 1; // offset=69.1
	unsigned short BurnSmoke : 1; // offset=69.2
	unsigned short IsDucked : 1; // offset=69.3
	unsigned short has_fired : 1; // offset=69.4
	unsigned short Busy : 1; // offset=69.5
	unsigned short LitTorch : 1; // offset=69.6
	unsigned short IsClimbing : 1; // offset=69.7
	unsigned short Fired : 1; // offset=70.0
	long water_surface_dist; // size=0, offset=72
	struct PHD_VECTOR last_pos; // size=12, offset=76
	struct FX_INFO* spaz_effect; // size=44, offset=88
	int mesh_effects; // size=0, offset=92
	short* mesh_ptrs[15]; // size=60, offset=96
	struct ITEM_INFO* target; // size=144, offset=156
	short target_angles[2]; // size=4, offset=160
	short turn_rate; // size=0, offset=164
	short move_angle; // size=0, offset=166
	short head_y_rot; // size=0, offset=168
	short head_x_rot; // size=0, offset=170
	short head_z_rot; // size=0, offset=172
	short torso_y_rot; // size=0, offset=174
	short torso_x_rot; // size=0, offset=176
	short torso_z_rot; // size=0, offset=178
	struct lara_arm left_arm; // size=20, offset=180
	struct lara_arm right_arm; // size=20, offset=200
	unsigned short holster; // size=0, offset=220
	struct creature_info* creature; // size=228, offset=224
	long CornerX; // size=0, offset=228
	long CornerZ; // size=0, offset=232
	char RopeSegment; // size=0, offset=236
	char RopeDirection; // size=0, offset=237
	short RopeArcFront; // size=0, offset=238
	short RopeArcBack; // size=0, offset=240
	short RopeLastX; // size=0, offset=242
	short RopeMaxXForward; // size=0, offset=244
	short RopeMaxXBackward; // size=0, offset=246
	long RopeDFrame; // size=0, offset=248
	long RopeFrame; // size=0, offset=252
	unsigned short RopeFrameRate; // size=0, offset=256
	unsigned short RopeY; // size=0, offset=258
	long RopePtr; // size=0, offset=260
	void* GeneralPtr; // size=0, offset=264
	int RopeOffset; // size=0, offset=268
	unsigned long RopeDownVel; // size=0, offset=272
	char RopeFlag; // size=0, offset=276
	char MoveCount; // size=0, offset=277
	int RopeCount; // size=0, offset=280
	char skelebob; // size=0, offset=284
	char pistols_type_carried; // size=0, offset=285
	char uzis_type_carried; // size=0, offset=286
	char shotgun_type_carried; // size=0, offset=287
	char crossbow_type_carried; // size=0, offset=288
	char hk_type_carried; // size=0, offset=289
	char sixshooter_type_carried; // size=0, offset=290
	char lasersight; // size=0, offset=291
	char silencer; // size=0, offset=292
	char binoculars; // size=0, offset=293
	char crowbar; // size=0, offset=294
	char examine1; // size=0, offset=295
	char examine2; // size=0, offset=296
	char examine3; // size=0, offset=297
	char wetcloth; // size=0, offset=298
	char bottle; // size=0, offset=299
	char puzzleitems[12]; // size=12, offset=300
	unsigned short puzzleitemscombo; // size=0, offset=312
	unsigned short keyitems; // size=0, offset=314
	unsigned short keyitemscombo; // size=0, offset=316
	unsigned short pickupitems; // size=0, offset=318
	unsigned short pickupitemscombo; // size=0, offset=320
	short num_small_medipack; // size=0, offset=322
	short num_large_medipack; // size=0, offset=324
	short num_flares; // size=0, offset=326
	short num_pistols_ammo; // size=0, offset=328
	short num_uzi_ammo; // size=0, offset=330
	short num_revolver_ammo; // size=0, offset=332
	short num_shotgun_ammo1; // size=0, offset=334
	short num_shotgun_ammo2; // size=0, offset=336
	short num_hk_ammo1; // size=0, offset=338
	short num_crossbow_ammo1; // size=0, offset=340
	short num_crossbow_ammo2; // size=0, offset=342
	char location; // size=0, offset=344
	char highest_location; // size=0, offset=345
	char locationPad; // size=0, offset=346
	unsigned char TightRopeOnCount; // size=0, offset=347
	unsigned char TightRopeOff; // size=0, offset=348
	unsigned char TightRopeFall; // size=0, offset=349
	unsigned char ChaffTimer; // size=0, offset=350
};

struct STATS {
	unsigned long Timer; // size=0, offset=0
	unsigned long Distance; // size=0, offset=4
	unsigned long AmmoUsed; // size=0, offset=8
	unsigned long AmmoHits; // size=0, offset=12
	unsigned short Kills; // size=0, offset=16
	unsigned char Secrets; // size=0, offset=18
	unsigned char HealthUsed; // size=0, offset=19
};

struct savegame_info
{
	short Checksum; // size=0, offset=0
	unsigned short VolumeCD; // size=0, offset=2
	unsigned short VolumeFX; // size=0, offset=4
	short ScreenX; // size=0, offset=6
	short ScreenY; // size=0, offset=8
	unsigned char ControlOption; // size=0, offset=10
	unsigned char VibrateOn; // size=0, offset=11
	char pad[3];
	unsigned char AutoTarget; // size=0, offset=12
	struct lara_info Lara; // size=352, offset=16
	struct STATS Level; // size=20, offset=368
	struct STATS Game; // size=20, offset=388
	short WeaponObject; // size=0, offset=408
	short WeaponAnim; // size=0, offset=410
	short WeaponFrame; // size=0, offset=412
	short WeaponCurrent; // size=0, offset=414
	short WeaponGoal; // size=0, offset=416
	unsigned long CutSceneTriggered1; // size=0, offset=420
	unsigned long CutSceneTriggered2; // size=0, offset=424
	char GameComplete; // size=0, offset=428
	unsigned char CurrentLevel; // size=0, offset=429
	unsigned char CampaignSecrets[4]; // size=4, offset=430
	unsigned char TLCount; // size=0, offset=434
};

struct MATRIX3D
{
	short m00; // size=0, offset=0
	short m01; // size=0, offset=2
	short m02; // size=0, offset=4
	short m10; // size=0, offset=6
	short m11; // size=0, offset=8
	short m12; // size=0, offset=10
	short m20; // size=0, offset=12
	short m21; // size=0, offset=14
	short m22; // size=0, offset=16
	short pad; // size=0, offset=18
	long tx; // size=0, offset=20
	long ty; // size=0, offset=24
	long tz; // size=0, offset=28
};

struct GAMEFLOW
{
	unsigned int CheatEnabled : 1; // offset=0.0
	unsigned int LoadSaveEnabled : 1; // offset=0.1
	unsigned int TitleEnabled : 1; // offset=0.2
	unsigned int PlayAnyLevel : 1; // offset=0.3
	unsigned int Language : 3; // offset=0.4
	unsigned int DemoDisc : 1; // offset=0.7
	unsigned int Unused : 24; // offset=1.0
	unsigned int InputTimeout; // size=0, offset=4
	unsigned char SecurityTag; // size=0, offset=8
	unsigned char nLevels; // size=0, offset=9
	unsigned char nFileNames; // size=0, offset=10
	unsigned char Pad; // size=0, offset=11
	unsigned short FileNameLen; // size=0, offset=12
	unsigned short ScriptLen; // size=0, offset=14
};

struct STRINGHEADER
{
	unsigned short nStrings; // size=0, offset=0
	unsigned short nPSXStrings; // size=0, offset=2
	unsigned short nPCStrings; // size=0, offset=4
	unsigned short StringWadLen; // size=0, offset=6
	unsigned short PSXStringWadLen; // size=0, offset=8
	unsigned short PCStringWadLen; // size=0, offset=10
};

struct GAME_VECTOR
{
	long x; // size=0, offset=0
	long y; // size=0, offset=4
	long z; // size=0, offset=8
	short room_number; // size=0, offset=12
	short box_number; // size=0, offset=14
};

struct OBJECT_VECTOR
{
	long x; // size=0, offset=0
	long y; // size=0, offset=4
	long z; // size=0, offset=8
	short data; // size=0, offset=12
	short flags; // size=0, offset=14
};

struct SPHERE
{
	long x; // size=0, offset=0
	long y; // size=0, offset=4
	long z; // size=0, offset=8
	long r; // size=0, offset=12
};

struct PENDULUM
{
	struct PHD_VECTOR Position; // size=12, offset=0
	struct PHD_VECTOR Velocity; // size=12, offset=12
	int node; // size=0, offset=24
	struct ROPE_STRUCT* Rope; // size=1172, offset=28
};

struct RAT_STRUCT
{
	struct PHD_3DPOS pos; // size=20, offset=0
	short room_number; // size=0, offset=20
	short speed; // size=0, offset=22
	short fallspeed; // size=0, offset=24
	unsigned char On; // size=0, offset=26
	unsigned char flags; // size=0, offset=27
};

struct BAT_STRUCT
{
	struct PHD_3DPOS pos; // size=20, offset=0
	short room_number; // size=0, offset=20
	short speed; // size=0, offset=22
	short Counter; // size=0, offset=24
	short LaraTarget; // size=0, offset=26
	char XTarget; // size=0, offset=28
	char ZTarget; // size=0, offset=29
	unsigned char On; // size=0, offset=30
	unsigned char flags; // size=0, offset=31
};

struct SPIDER_STRUCT
{
	struct PHD_3DPOS pos; // size=20, offset=0
	short room_number; // size=0, offset=20
	short speed; // size=0, offset=22
	short fallspeed; // size=0, offset=24
	unsigned char On; // size=0, offset=26
	unsigned char flags; // size=0, offset=27
};

struct TWOGUN_INFO
{
	struct PHD_3DPOS pos; // size=20, offset=0
	short life; // size=0, offset=20
	short coil; // size=0, offset=22
	short spin; // size=0, offset=24
	short spinadd; // size=0, offset=26
	short length; // size=0, offset=28
	short dlength; // size=0, offset=30
	short size; // size=0, offset=32
	char r; // size=0, offset=34
	char g; // size=0, offset=35
	char b; // size=0, offset=36
	char fadein; // size=0, offset=37
};

struct CHARDEF
{
	unsigned char u; // size=0, offset=0
	unsigned char v; // size=0, offset=1
	unsigned char w; // size=0, offset=2
	unsigned char h; // size=0, offset=3
	char YOffset; // size=0, offset=4
	unsigned char TopShade; // size=0, offset=5
	unsigned char BottomShade; // size=0, offset=6
};

struct COLL_INFO
{
	long mid_floor; // size=0, offset=0
	long mid_ceiling; // size=0, offset=4
	long mid_type; // size=0, offset=8
	long front_floor; // size=0, offset=12
	long front_ceiling; // size=0, offset=16
	long front_type; // size=0, offset=20
	long left_floor; // size=0, offset=24
	long left_ceiling; // size=0, offset=28
	long left_type; // size=0, offset=32
	long right_floor; // size=0, offset=36
	long right_ceiling; // size=0, offset=40
	long right_type; // size=0, offset=44
	long left_floor2; // size=0, offset=48
	long left_ceiling2; // size=0, offset=52
	long left_type2; // size=0, offset=56
	long right_floor2; // size=0, offset=60
	long right_ceiling2; // size=0, offset=64
	long right_type2; // size=0, offset=68
	long radius; // size=0, offset=72
	long bad_pos; // size=0, offset=76
	long bad_neg; // size=0, offset=80
	long bad_ceiling; // size=0, offset=84
	struct PHD_VECTOR shift; // size=12, offset=88
	struct PHD_VECTOR old; // size=12, offset=100
	short old_anim_state; // size=0, offset=112
	short old_anim_number; // size=0, offset=114
	short old_frame_number; // size=0, offset=116
	short facing; // size=0, offset=118
	short quadrant; // size=0, offset=120
	short coll_type; // size=0, offset=122 USE ENUM CT_*
	short* trigger; // size=0, offset=124
	char tilt_x; // size=0, offset=128
	char tilt_z; // size=0, offset=129
	char hit_by_baddie; // size=0, offset=130
	char hit_static; // size=0, offset=131
	unsigned short slopes_are_walls : 2; // offset=132.0
	unsigned short slopes_are_pits : 1; // offset=132.2
	unsigned short lava_is_pit : 1; // offset=132.3
	unsigned short enable_baddie_push : 1; // offset=132.4
	unsigned short enable_spaz : 1; // offset=132.5
	unsigned short hit_ceiling : 1; // offset=132.6
};

struct ANIM_STRUCT
{
	short* frame_ptr; // size=0, offset=0
	short interpolation; // size=0, offset=4
	short current_anim_state; // size=0, offset=6
	long velocity; // size=0, offset=8
	long acceleration; // size=0, offset=12
	long Xvelocity; // size=0, offset=16
	long Xacceleration; // size=0, offset=20
	short frame_base; // size=0, offset=24
	short frame_end; // size=0, offset=26
	short jump_anim_num; // size=0, offset=28
	short jump_frame_num; // size=0, offset=30
	short number_changes; // size=0, offset=32
	short change_index; // size=0, offset=34
	short number_commands; // size=0, offset=36
	short command_index; // size=0, offset=38
};

struct SPARKS
{
	long x; // size=0, offset=0
	long y; // size=0, offset=4
	long z; // size=0, offset=8
	short Xvel; // size=0, offset=12
	short Yvel; // size=0, offset=14
	short Zvel; // size=0, offset=16
	short Gravity; // size=0, offset=18
	short RotAng; // size=0, offset=20
	short Flags; // size=0, offset=22
	unsigned char sSize; // size=0, offset=24
	unsigned char dSize; // size=0, offset=25
	unsigned char Size; // size=0, offset=26
	unsigned char Friction; // size=0, offset=27
	unsigned char Scalar; // size=0, offset=28
	unsigned char Def; // size=0, offset=29
	char RotAdd; // size=0, offset=30
	char MaxYvel; // size=0, offset=31
	unsigned char On; // size=0, offset=32
	unsigned char sR; // size=0, offset=33
	unsigned char sG; // size=0, offset=34
	unsigned char sB; // size=0, offset=35
	unsigned char dR; // size=0, offset=36
	unsigned char dG; // size=0, offset=37
	unsigned char dB; // size=0, offset=38
	unsigned char R; // size=0, offset=39
	unsigned char G; // size=0, offset=40
	unsigned char B; // size=0, offset=41
	unsigned char ColFadeSpeed; // size=0, offset=42
	unsigned char FadeToBlack; // size=0, offset=43
	unsigned char sLife; // size=0, offset=44
	unsigned char Life; // size=0, offset=45
	unsigned char TransType; // size=0, offset=46
	unsigned char extras; // size=0, offset=47
	char Dynamic; // size=0, offset=48
	unsigned char FxObj; // size=0, offset=49
	unsigned char RoomNumber; // size=0, offset=50
	unsigned char NodeNumber; // size=0, offset=51
};

struct ACTORME
{
	int offset; // size=0, offset=0
	short objslot; // size=0, offset=4
	short nodes; // size=0, offset=6
};

struct RTDECODE
{
	unsigned long length; // size=0, offset=0
	unsigned long off; // size=0, offset=4
	unsigned short counter; // size=0, offset=8
	unsigned short data; // size=0, offset=10
	unsigned char decodetype; // size=0, offset=12
	unsigned char packmethod; // size=0, offset=13
	unsigned short padfuck; // size=0, offset=14
};

struct PACKNODE
{
	short xrot_run; // size=0, offset=0
	short yrot_run; // size=0, offset=2
	short zrot_run; // size=0, offset=4
	short xkey; // size=0, offset=6
	short ykey; // size=0, offset=8
	short zkey; // size=0, offset=10
	struct RTDECODE decode_x; // size=16, offset=12
	struct RTDECODE decode_y; // size=16, offset=28
	struct RTDECODE decode_z; // size=16, offset=44
	unsigned long xlength; // size=0, offset=60
	unsigned long ylength; // size=0, offset=64
	unsigned long zlength; // size=0, offset=68
	char* xpacked; // size=0, offset=72
	char* ypacked; // size=0, offset=76
	char* zpacked; // size=0, offset=80
};

struct NODELOADHEADER
{
	short xkey; // size=0, offset=0
	short ykey; // size=0, offset=2
	short zkey; // size=0, offset=4
	short packmethod; // size=0, offset=6
	short xlength; // size=0, offset=8
	short ylength; // size=0, offset=10
	short zlength; // size=0, offset=12
};

struct RESIDENT_THING
{
	char* packed_data; // size=0, offset=0
};

struct NEW_CUTSCENE
{
	short numactors; // size=0, offset=0
	short numframes; // size=0, offset=2
	int orgx; // size=0, offset=4
	int orgy; // size=0, offset=8
	int orgz; // size=0, offset=12
	int audio_track; // size=0, offset=16
	int camera_offset; // size=0, offset=20
	struct ACTORME actor_data[10]; // size=80, offset=24
};

struct CUTSEQ_ROUTINES
{
	void(*init_func)(); // size=0, offset=0
	void(*control_func)(); // size=0, offset=4
	void(*end_func)(); // size=0, offset=8
};

struct DOORPOS_DATA
{
	struct FLOOR_INFO* floor; // size=8, offset=0
	struct FLOOR_INFO data; // size=8, offset=4
	short block; // size=0, offset=12
};

struct DOOR_DATA
{
	struct DOORPOS_DATA d1; // size=16, offset=0
	struct DOORPOS_DATA d1flip; // size=16, offset=16
	struct DOORPOS_DATA d2; // size=16, offset=32
	struct DOORPOS_DATA d2flip; // size=16, offset=48
	short Opened; // size=0, offset=64
	short* dptr1; // size=0, offset=68
	short* dptr2; // size=0, offset=72
	short* dptr3; // size=0, offset=76
	short* dptr4; // size=0, offset=80
	char dn1; // size=0, offset=84
	char dn2; // size=0, offset=85
	char dn3; // size=0, offset=86
	char dn4; // size=0, offset=87
	struct ITEM_INFO* item; // size=144, offset=88
};

struct CHANGE_STRUCT
{
	short goal_anim_state; // size=0, offset=0
	short number_ranges; // size=0, offset=2
	short range_index; // size=0, offset=4
};
struct RANGE_STRUCT
{
	short start_frame; // size=0, offset=0
	short end_frame; // size=0, offset=2
	short link_anim_num; // size=0, offset=4
	short link_frame_num; // size=0, offset=6
};

struct door_vbuf
{
	long xv; // size=0, offset=0
	long yv; // size=0, offset=4
	long zv; // size=0, offset=8
};

struct BITE_INFO
{
	long x; // size=0, offset=0
	long y; // size=0, offset=4
	long z; // size=0, offset=8
	long mesh_num; // size=0, offset=12
};

struct box_info
{
	unsigned char left; // size=0, offset=0
	unsigned char right; // size=0, offset=1
	unsigned char top; // size=0, offset=2
	unsigned char bottom; // size=0, offset=3
	short height; // size=0, offset=4
	short overlap_index; // size=0, offset=6
};

struct AI_info
{
	short zone_number; // size=0, offset=0
	short enemy_zone; // size=0, offset=2
	long distance; // size=0, offset=4
	long ahead; // size=0, offset=8
	long bite; // size=0, offset=12
	short angle; // size=0, offset=16
	short x_angle; // size=0, offset=18
	short enemy_facing; // size=0, offset=20
};

struct AIOBJECT
{
	short object_number; // size=0, offset=0
	short room_number; // size=0, offset=2
	long x; // size=0, offset=4
	long y; // size=0, offset=8
	long z; // size=0, offset=12
	short trigger_flags; // size=0, offset=16
	short flags; // size=0, offset=18
	short y_rot; // size=0, offset=20
	short box_number; // size=0, offset=22
};

struct CAMERA_INFO
{
	struct GAME_VECTOR pos; // size=16, offset=0
	struct GAME_VECTOR target; // size=16, offset=16
	enum camera_type type; // size=4, offset=32
	enum camera_type old_type; // size=4, offset=36
	long shift; // size=0, offset=40
	long flags; // size=0, offset=44
	long fixed_camera; // size=0, offset=48
	long number_frames; // size=0, offset=52
	long bounce; // size=0, offset=56
	long underwater; // size=0, offset=60
	long target_distance; // size=0, offset=64
	short target_angle; // size=0, offset=68
	short target_elevation; // size=0, offset=70
	short actual_elevation; // size=0, offset=72
	short actual_angle; // size=0, offset=74
	short lara_node; // size=0, offset=76
	short box; // size=0, offset=78
	short number; // size=0, offset=80
	short last; // size=0, offset=82
	short timer; // size=0, offset=84
	short speed; // size=0, offset=86
	short targetspeed; // size=0, offset=88
	struct ITEM_INFO* item; // size=144, offset=92
	struct ITEM_INFO* last_item; // size=144, offset=96
	struct OBJECT_VECTOR* fixed; // size=16, offset=100
	int mike_at_lara; // size=0, offset=104
	struct PHD_VECTOR mike_pos; // size=12, offset=108
};

struct SHATTER_ITEM
{
	struct SPHERE Sphere; // size=16, offset=0
	struct ITEM_LIGHT* il; // size=48, offset=16
	short* meshp; // size=0, offset=20
	long Bit; // size=0, offset=24
	short YRot; // size=0, offset=28
	short Flags; // size=0, offset=30
};

struct OLD_CAMERA
{
	short current_anim_state; // size=0, offset=0
	short goal_anim_state; // size=0, offset=2
	long target_distance; // size=0, offset=4
	short target_angle; // size=0, offset=8
	short target_elevation; // size=0, offset=10
	short actual_elevation; // size=0, offset=12
	struct PHD_3DPOS pos; // size=20, offset=16
	struct PHD_3DPOS pos2; // size=20, offset=36
	struct PHD_VECTOR t; // size=12, offset=56
};

struct DEBRIS_STRUCT
{
	void* TextInfo; // size=0, offset=0
	long x; // size=0, offset=4
	long y; // size=0, offset=8
	long z; // size=0, offset=12
	short XYZOffsets1[3]; // size=6, offset=16
	short Dir; // size=0, offset=22
	short XYZOffsets2[3]; // size=6, offset=24
	short Speed; // size=0, offset=30
	short XYZOffsets3[3]; // size=6, offset=32
	short Yvel; // size=0, offset=38
	short Gravity; // size=0, offset=40
	short RoomNumber; // size=0, offset=42
	unsigned char On; // size=0, offset=44
	unsigned char XRot; // size=0, offset=45
	unsigned char YRot; // size=0, offset=46
	unsigned char r; // size=0, offset=47
	unsigned char g; // size=0, offset=48
	unsigned char b; // size=0, offset=49
	unsigned char Pad[2]; // size=2, offset=50
};

struct SPOTCAM
{
	long x; // size=0, offset=0
	long y; // size=0, offset=4
	long z; // size=0, offset=8
	long tx; // size=0, offset=12
	long ty; // size=0, offset=16
	long tz; // size=0, offset=20
	unsigned char sequence; // size=0, offset=24
	unsigned char camera; // size=0, offset=25
	short fov; // size=0, offset=26
	short roll; // size=0, offset=28
	short timer; // size=0, offset=30
	short speed; // size=0, offset=32
	short flags; // size=0, offset=34
	short room_number; // size=0, offset=36
	short pad; // size=0, offset=38
};

struct QUAKE_CAM
{
	struct GAME_VECTOR spos; // size=16, offset=0
	struct GAME_VECTOR epos; // size=16, offset=16
};

struct DYNAMIC
{
	long x; // size=0, offset=0
	long y; // size=0, offset=4
	long z; // size=0, offset=8
	unsigned char on; // size=0, offset=12
	unsigned char r; // size=0, offset=13
	unsigned char g; // size=0, offset=14
	unsigned char b; // size=0, offset=15
	unsigned short falloff; // size=0, offset=16
	unsigned char used; // size=0, offset=18
	unsigned char pad1[1]; // size=1, offset=19
	long FalloffScale; // size=0, offset=20
};

struct SP_DYNAMIC
{
	unsigned char On; // size=0, offset=0
	unsigned char Falloff; // size=0, offset=1
	unsigned char R; // size=0, offset=2
	unsigned char G; // size=0, offset=3
	unsigned char B; // size=0, offset=4
	unsigned char Flags; // size=0, offset=5
	unsigned char Pad[2]; // size=2, offset=6
};

struct SPLASH_STRUCT
{
	long x; // size=0, offset=0
	long y; // size=0, offset=4
	long z; // size=0, offset=8
	short InnerRad; // size=0, offset=12
	short InnerSize; // size=0, offset=14
	short InnerRadVel; // size=0, offset=16
	short InnerYVel; // size=0, offset=18
	short InnerY; // size=0, offset=20
	short MiddleRad; // size=0, offset=22
	short MiddleSize; // size=0, offset=24
	short MiddleRadVel; // size=0, offset=26
	short MiddleYVel; // size=0, offset=28
	short MiddleY; // size=0, offset=30
	short OuterRad; // size=0, offset=32
	short OuterSize; // size=0, offset=34
	short OuterRadVel; // size=0, offset=36
	char flags; // size=0, offset=38
	unsigned char life; // size=0, offset=39
};

struct RIPPLE_STRUCT
{
	long x; // size=0, offset=0
	long y; // size=0, offset=4
	long z; // size=0, offset=8
	char flags; // size=0, offset=12
	unsigned char life; // size=0, offset=13
	unsigned char size; // size=0, offset=14
	unsigned char init; // size=0, offset=15
};

struct SPLASH_SETUP
{
	long x; // size=0, offset=0
	long y; // size=0, offset=4
	long z; // size=0, offset=8
	short InnerRad; // size=0, offset=12
	short InnerSize; // size=0, offset=14
	short InnerRadVel; // size=0, offset=16
	short InnerYVel; // size=0, offset=18
	short pad1; // size=0, offset=20
	short MiddleRad; // size=0, offset=22
	short MiddleSize; // size=0, offset=24
	short MiddleRadVel; // size=0, offset=26
	short MiddleYVel; // size=0, offset=28
	short pad2; // size=0, offset=30
	short OuterRad; // size=0, offset=32
	short OuterSize; // size=0, offset=34
	short OuterRadVel; // size=0, offset=36
	short pad3; // size=0, offset=38
};

struct FIRE_LIST
{
	long x; // size=0, offset=0
	long y; // size=0, offset=4
	long z; // size=0, offset=8
	char on; // size=0, offset=12
	char size; // size=0, offset=13
	short room_number; // size=0, offset=14
};

struct FIRE_SPARKS
{
	short x; // size=0, offset=0
	short y; // size=0, offset=2
	short z; // size=0, offset=4
	short Xvel; // size=0, offset=6
	short Yvel; // size=0, offset=8
	short Zvel; // size=0, offset=10
	short Gravity; // size=0, offset=12
	short RotAng; // size=0, offset=14
	short Flags; // size=0, offset=16
	unsigned char sSize; // size=0, offset=18
	unsigned char dSize; // size=0, offset=19
	unsigned char Size; // size=0, offset=20
	unsigned char Friction; // size=0, offset=21
	unsigned char Scalar; // size=0, offset=22
	unsigned char Def; // size=0, offset=23
	char RotAdd; // size=0, offset=24
	char MaxYvel; // size=0, offset=25
	unsigned char On; // size=0, offset=26
	unsigned char sR; // size=0, offset=27
	unsigned char sG; // size=0, offset=28
	unsigned char sB; // size=0, offset=29
	unsigned char dR; // size=0, offset=30
	unsigned char dG; // size=0, offset=31
	unsigned char dB; // size=0, offset=32
	unsigned char R; // size=0, offset=33
	unsigned char G; // size=0, offset=34
	unsigned char B; // size=0, offset=35
	unsigned char ColFadeSpeed; // size=0, offset=36
	unsigned char FadeToBlack; // size=0, offset=37
	unsigned char sLife; // size=0, offset=38
	unsigned char Life; // size=0, offset=39
};

struct SMOKE_SPARKS
{
	long x; // size=0, offset=0
	long y; // size=0, offset=4
	long z; // size=0, offset=8
	short Xvel; // size=0, offset=12
	short Yvel; // size=0, offset=14
	short Zvel; // size=0, offset=16
	short Gravity; // size=0, offset=18
	short RotAng; // size=0, offset=20
	short Flags; // size=0, offset=22
	unsigned char sSize; // size=0, offset=24
	unsigned char dSize; // size=0, offset=25
	unsigned char Size; // size=0, offset=26
	unsigned char Friction; // size=0, offset=27
	unsigned char Scalar; // size=0, offset=28
	unsigned char Def; // size=0, offset=29
	char RotAdd; // size=0, offset=30
	char MaxYvel; // size=0, offset=31
	unsigned char On; // size=0, offset=32
	unsigned char sShade; // size=0, offset=33
	unsigned char dShade; // size=0, offset=34
	unsigned char Shade; // size=0, offset=35
	unsigned char ColFadeSpeed; // size=0, offset=36
	unsigned char FadeToBlack; // size=0, offset=37
	char sLife; // size=0, offset=38
	char Life; // size=0, offset=39
	unsigned char TransType; // size=0, offset=40
	unsigned char FxObj; // size=0, offset=41
	unsigned char NodeNumber; // size=0, offset=42
	unsigned char mirror; // size=0, offset=43
};

struct BLOOD_STRUCT
{
	long x; // size=0, offset=0
	long y; // size=0, offset=4
	long z; // size=0, offset=8
	short Xvel; // size=0, offset=12
	short Yvel; // size=0, offset=14
	short Zvel; // size=0, offset=16
	short Gravity; // size=0, offset=18
	short RotAng; // size=0, offset=20
	unsigned char sSize; // size=0, offset=22
	unsigned char dSize; // size=0, offset=23
	unsigned char Size; // size=0, offset=24
	unsigned char Friction; // size=0, offset=25
	char RotAdd; // size=0, offset=26
	unsigned char On; // size=0, offset=27
	unsigned char sShade; // size=0, offset=28
	unsigned char dShade; // size=0, offset=29
	unsigned char Shade; // size=0, offset=30
	unsigned char ColFadeSpeed; // size=0, offset=31
	unsigned char FadeToBlack; // size=0, offset=32
	char sLife; // size=0, offset=33
	char Life; // size=0, offset=34
	char Pad; // size=0, offset=35
};

struct GUNSHELL_STRUCT
{
	struct PHD_3DPOS pos; // size=20, offset=0
	short fallspeed; // size=0, offset=20
	short room_number; // size=0, offset=22
	short speed; // size=0, offset=24
	short counter; // size=0, offset=26
	short DirXrot; // size=0, offset=28
	short object_number; // size=0, offset=30
};

struct BUBBLE_STRUCT
{
	struct PHD_VECTOR pos; // size=12, offset=0
	short room_number; // size=0, offset=12
	short speed; // size=0, offset=14
	short size; // size=0, offset=16
	short dsize; // size=0, offset=18
	unsigned char shade; // size=0, offset=20
	unsigned char vel; // size=0, offset=21
	unsigned char y_rot; // size=0, offset=22
	char Flags; // size=0, offset=23
	short Xvel; // size=0, offset=24
	short Yvel; // size=0, offset=26
	short Zvel; // size=0, offset=28
	short Pad; // size=0, offset=30
};

struct GUNFLASH_STRUCT
{
	struct MATRIX3D matrix; // size=32, offset=0
	short on; // size=0, offset=32
};

struct NODEOFFSET_INFO
{
	short x; // size=0, offset=0
	short y; // size=0, offset=2
	short z; // size=0, offset=4
	char mesh_num; // size=0, offset=6
	unsigned char GotIt; // size=0, offset=7
};

struct SHOCKWAVE_STRUCT
{
	long x; // size=0, offset=0
	long y; // size=0, offset=4
	long z; // size=0, offset=8
	short InnerRad; // size=0, offset=12
	short OuterRad; // size=0, offset=14
	short XRot; // size=0, offset=16
	short Flags; // size=0, offset=18
	unsigned char r; // size=0, offset=20
	unsigned char g; // size=0, offset=21
	unsigned char b; // size=0, offset=22
	unsigned char life; // size=0, offset=23
	short Speed; // size=0, offset=24
	short Temp; // size=0, offset=26
};

struct HAIR_STRUCT
{
	struct PHD_3DPOS pos; // size=20, offset=0
	struct PHD_VECTOR vel; // size=12, offset=20
};

struct DISPLAYPU
{
	short life; // size=0, offset=0
	short object_number; // size=0, offset=2
};

struct INVOBJ
{
	short object_number; // size=0, offset=0
	short yoff; // size=0, offset=2
	short scale1; // size=0, offset=4
	short yrot; // size=0, offset=6
	short xrot; // size=0, offset=8
	short zrot; // size=0, offset=10
	short flags; // size=0, offset=12
	short objname; // size=0, offset=14
	unsigned long meshbits; // size=0, offset=16
};

struct OBJLIST
{
	short invitem; // size=0, offset=0
	unsigned short yrot; // size=0, offset=2
	unsigned short bright; // size=0, offset=4
};

struct RINGME
{
	struct OBJLIST current_object_list[100]; // size=600, offset=0
	int ringactive; // size=0, offset=600
	int objlistmovement; // size=0, offset=604
	int curobjinlist; // size=0, offset=608
	int numobjectsinlist; // size=0, offset=612
};

struct AMMOLIST
{
	short invitem; // size=0, offset=0
	short amount; // size=0, offset=2
	unsigned short yrot; // size=0, offset=4
};
struct MENUTHANG
{
	int type; // size=0, offset=0
	char* text; // size=0, offset=4
};

struct COMBINELIST
{
	void(*combine_routine)(int flag); // size=0, offset=0
	short item1; // size=0, offset=4
	short item2; // size=0, offset=6
	short combined_item; // size=0, offset=8
};

struct WEAPON_INFO
{
	short lock_angles[4]; // size=8, offset=0
	short left_angles[4]; // size=8, offset=8
	short right_angles[4]; // size=8, offset=16
	short aim_speed; // size=0, offset=24
	short shot_accuracy; // size=0, offset=26
	short gun_height; // size=0, offset=28
	short target_dist; // size=0, offset=30
	char damage; // size=0, offset=32
	char recoil_frame; // size=0, offset=33
	char flash_time; // size=0, offset=34
	char draw_frame; // size=0, offset=35
	short sample_num; // size=0, offset=36
};

struct PISTOL_DEF
{
	short ObjectNum; // size=0, offset=0
	char Draw1Anim2; // size=0, offset=2
	char Draw1Anim; // size=0, offset=3
	char Draw2Anim; // size=0, offset=4
	char RecoilAnim; // size=0, offset=5
};

struct SUBSUIT_INFO
{
	short XRot; // size=0, offset=0
	short dXRot; // size=0, offset=2
	short XRotVel; // size=0, offset=4
	short Vel[2]; // size=4, offset=6
	short YVel; // size=0, offset=10
};

struct SAMPLE_INFO
{
	short number; // size=0, offset=0
	unsigned char volume; // size=0, offset=2
	char radius; // size=0, offset=3
	char randomness; // size=0, offset=4
	char pitch; // size=0, offset=5
	short flags; // size=0, offset=6
};

struct SoundSlot
{
	int OrigVolume; // size=0, offset=0
	int nVolume; // size=0, offset=4
	int nPan; // size=0, offset=8
	int nPitch; // size=0, offset=12
	int nSampleInfo; // size=0, offset=16
	unsigned long distance; // size=0, offset=20
	struct PHD_VECTOR pos; // size=12, offset=24
};

struct FOOTPRINT
{
	long x; // size=0, offset=0
	long y; // size=0, offset=4
	long z; // size=0, offset=8
	short YRot; // size=0, offset=12
	short Active; // size=0, offset=14
};

//Reconstructed, size hint = 8;
struct MESH_STRUCT//maybe NODEOFFSET_INFO
{
	short unk00;//0
	short unk01;//2
	long unk02;//4
	unsigned char unk03;//8
};

#if PC_VERSION
#pragma pop
#endif
#endif
