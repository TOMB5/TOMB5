#ifndef SPECTYPES_H
#define SPECTYPES_H

#include "TYPES.H"
#include <stddef.h>

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
#define BYTE1(x)   BYTEn(x,  1)         // byte 1 (counting from 0)
#define BYTE2(x)   BYTEn(x,  2)
#define BYTE3(x)   BYTEn(x,  3)
#define BYTE4(x)   BYTEn(x,  4)
#define BYTE5(x)   BYTEn(x,  5)
#define BYTE6(x)   BYTEn(x,  6)
#define BYTE7(x)   BYTEn(x,  7)
#define BYTE8(x)   BYTEn(x,  8)
#define BYTE9(x)   BYTEn(x,  9)
#define BYTE10(x)  BYTEn(x, 10)
#define BYTE11(x)  BYTEn(x, 11)
#define BYTE12(x)  BYTEn(x, 12)
#define BYTE13(x)  BYTEn(x, 13)
#define BYTE14(x)  BYTEn(x, 14)
#define BYTE15(x)  BYTEn(x, 15)
#define WORD1(x)   WORDn(x,  1)
#define WORD2(x)   WORDn(x,  2)         // third word of the object, unsigned
#define WORD3(x)   WORDn(x,  3)
#define WORD4(x)   WORDn(x,  4)
#define WORD5(x)   WORDn(x,  5)
#define WORD6(x)   WORDn(x,  6)
#define WORD7(x)   WORDn(x,  7)
#define SBYTE1(x)   SBYTEn(x,  1)
#define SBYTE2(x)   SBYTEn(x,  2)
#define SBYTE3(x)   SBYTEn(x,  3)
#define SBYTE4(x)   SBYTEn(x,  4)
#define SBYTE5(x)   SBYTEn(x,  5)
#define SBYTE6(x)   SBYTEn(x,  6)
#define SBYTE7(x)   SBYTEn(x,  7)
#define SBYTE8(x)   SBYTEn(x,  8)
#define SBYTE9(x)   SBYTEn(x,  9)
#define SBYTE10(x)  SBYTEn(x, 10)
#define SBYTE11(x)  SBYTEn(x, 11)
#define SBYTE12(x)  SBYTEn(x, 12)
#define SBYTE13(x)  SBYTEn(x, 13)
#define SBYTE14(x)  SBYTEn(x, 14)
#define SBYTE15(x)  SBYTEn(x, 15)
#define SWORD1(x)   SWORDn(x,  1)
#define SWORD2(x)   SWORDn(x,  2)
#define SWORD3(x)   SWORDn(x,  3)
#define SWORD4(x)   SWORDn(x,  4)
#define SWORD5(x)   SWORDn(x,  5)
#define SWORD6(x)   SWORDn(x,  6)
#define SWORD7(x)   SWORDn(x,  7)

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
#pragma pack(push, 1)
struct object_info {
	short nmeshes; // size=0, offset=0
	short mesh_index; // size=0, offset=2
	long bone_index; // size=0, offset=4
	short* frame_base; // size=0, offset=8
	void(*initialise); // size=0, offset=12
	void(*control)(); // size=0, offset=16
	void(*floor)(); // size=0, offset=20
	void(*ceiling)(); // size=0, offset=24
	void(*draw_routine)(); // size=0, offset=28
	void(*collision)(); // size=0, offset=32
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
	void(*draw_routine_extra)(); // size=0, offset=52
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
	char pad[128];
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
	char pad[5478];
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
#pragma pop

#endif