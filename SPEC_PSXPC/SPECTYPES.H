#ifndef SPECTYPES_H
#define SPECTYPES_H

#define INPUT_H "PSXPCINPUT.H"
#define CMATH_H "math.h"

#include "TYPES.H"

#include <sys/types.h>

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
};

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

struct TEXTURE
{
	unsigned char u0;
	unsigned char v0;
	unsigned short clut;
	unsigned char u1;
	unsigned char v1;
	unsigned short tpage;
	unsigned char u2;
	unsigned char v2;
	unsigned char id[2];
	unsigned char u3;
	unsigned char v3;
	unsigned short wclut;
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

struct PSXTEXTI
{
	unsigned char u0;
	unsigned char v0;
	unsigned short clut;
	unsigned char u1;
	unsigned char v1;
	unsigned short tpage;
	unsigned char u2;
	unsigned char v2;
	unsigned char codeGT4;
	unsigned char codeGT3;
	unsigned char u3;
	unsigned char v3;
	unsigned short pad3;
};

struct VECTOR3D
{
	long x;
	long y;
	long z;
};

struct PSXTEXTSTRUCT
{
	unsigned long u0v0clut;
	unsigned long u1v1tpage;
	unsigned long u2v2pad;
	unsigned long u3v3pad;
};

struct PSXSPRITESTRUCT
{
	short x1;
	short y1;
	short x2;
	short y2;
	unsigned short clut;
	unsigned short tpage;
	unsigned char u1;
	unsigned char v1;
	unsigned char u2;
	unsigned char v2;
};

struct MMTEXTURE
{
	struct TEXTURE t[3];
};

struct TSV
{
	unsigned long xy;
	unsigned long rgz;
};

#if 0
struct ControllerPacket
{
	unsigned char transStatus;
	unsigned char dataFormat;
	struct fake76 data;
};
#endif

struct pad_configs
{
	unsigned long pad_L2;
	unsigned long pad_R2;
	unsigned long pad_L1;
	unsigned long pad_R1;
	unsigned long pad_triangle;
	unsigned long pad_square; 
	unsigned long pad_circle;
	unsigned long pad_cross;
};

struct GouraudBarColourSet
{
	unsigned char abLeftRed[5];
	unsigned char abLeftGreen[5];
	unsigned char abLeftBlue[5];
	unsigned char abRightRed[5];
	unsigned char abRightGreen[5];
	unsigned char abRightBlue[5];
};

struct STASHEDOBJ
{
	short clip;
	short numnodestodraw;
	struct ITEM_INFO* item;
	short* frmptr0;
};

struct STASHEDDAT
{
	short* mesh;
	char matrix[32];
};

struct WATERTAB
{
	char shimmer;
	char choppy;
	unsigned char random;
	unsigned char abs;
};

struct VIBRATION
{
	short Rate;
	short Len;
	short Lev;
	short Acc;
	short Dec;
	short Sus;
	short Flag;
	short Vib;
};

struct REQUESTER
{
	unsigned short TitleTxt;
	unsigned short TitleCol : 5;
	unsigned short nOptions : 3;
	unsigned short CursorPos : 3;
	unsigned short OptionCol : 5;
	unsigned long JustifyL : 5;
	unsigned long JustifyR : 5;
	unsigned long Arrows : 5;
	unsigned long Ignore : 5;
	unsigned short OptionTxt[5];
};

struct SCALE
{
	short xgrid;
	char scalefactor;
	char nummarks;
};

struct COCKSUCK
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char pad;
	short finalcnt;
	short profile_xcnt;
};

struct PACKEDNAME
{
	char Name[12];
	unsigned char Days;
	unsigned char Hours;
	unsigned char Min;
	unsigned char Sec;
	unsigned short Slot;
	unsigned char Level;
	unsigned char Pad;
};

struct ILIGHT
{
	short x;
	short y;
	short z;
	short pad1;
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char pad;
};

struct ITEM_LIGHT
{
	struct ILIGHT Light[4];
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
	unsigned long active : 1; // offset=132.0
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
	unsigned long meshswap_meshbits; // size=0, offset=136
	short draw_room; // size=0, offset=140
	short TOSSPAD; // size=0, offset=142
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
	enum mood_type mood; // size=4, offset=16
	struct ITEM_INFO* enemy; // size=144, offset=20
	struct ITEM_INFO ai_target; // size=144, offset=24
	short pad; // size=0, offset=168
	short item_num; // size=0, offset=170
	struct PHD_VECTOR target; // size=12, offset=172
	struct lot_info LOT; // size=44, offset=184
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
};

struct RECTPSX {
	short x; // size=0, offset=0
	short y; // size=0, offset=2
	short w; // size=0, offset=4
	short h; // size=0, offset=6
};
struct DR_ENV {
	unsigned long tag; // size=0, offset=0
	unsigned long code[15]; // size=60, offset=4
};
struct DRAWENV {
	struct RECTPSX clip; // size=8, offset=0
	short ofs[2]; // size=4, offset=8
	struct RECTPSX tw; // size=8, offset=12
	unsigned short tpage; // size=0, offset=20
	unsigned char dtd; // size=0, offset=22
	unsigned char dfe; // size=0, offset=23
	unsigned char isbg; // size=0, offset=24
	unsigned char r0; // size=0, offset=25
	unsigned char g0; // size=0, offset=26
	unsigned char b0; // size=0, offset=27
	struct DR_ENV dr_env; // size=64, offset=28
};
struct DISPENV {
	struct RECTPSX disp; // size=8, offset=0
	struct RECTPSX screen; // size=8, offset=8
	unsigned char isinter; // size=0, offset=16
	unsigned char isrgb24; // size=0, offset=17
	unsigned char pad0; // size=0, offset=18
	unsigned char pad1; // size=0, offset=19
};

struct DB_STRUCT
{
	int current_buffer; // size=0, offset=0
	unsigned long *ot; // size=0, offset=4
	char *polyptr; // size=0, offset=8
	char *curpolybuf; // size=0, offset=12
	char *polybuf_limit; // size=0, offset=16
	int nOTSize; // size=0, offset=20
	int nPBSize; // size=0, offset=24
	unsigned long *order_table[2]; // size=8, offset=28
	unsigned long *poly_buffer[2]; // size=8, offset=36
	unsigned long *pickup_ot; // size=0, offset=44
	unsigned long *pickup_order_table[2]; // size=8, offset=48
	struct DRAWENV draw[2]; // size=184, offset=56
	struct DISPENV disp[2]; // size=40, offset=240
};

typedef unsigned short PadData;

typedef struct
{
	unsigned short buttons;
	char xOffset;
	char yOffset;
} MouseData;

typedef struct
{
	unsigned short digitalButtons;
	char centralTwist;
	char buttonI;
	char buttonII;
	char topLeft;
} NegconData;

typedef struct
{
	unsigned char transStatus;
	unsigned char dataFormat;

	union
	{
		PadData    pad;
		NegconData negcon;
	}
	data;
} TapCtrllerData;

typedef struct
{
	TapCtrllerData ctrllers[4];
} MultiTapData;


typedef struct
{
	unsigned char transStatus;
	unsigned char dataFormat;

	union
	{
		PadData      pad;
		MouseData    mouse;
		NegconData   negcon;
		MultiTapData tap;
	}
	data;
} ControllerPacket;

#endif