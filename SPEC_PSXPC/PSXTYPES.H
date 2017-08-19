#ifndef PSXTYPES_H
#define PSXTYPES_H


// 4 enums
enum mood_type
{
	BORED_MOOD = 0,
	ATTACK_MOOD = 1,
	ESCAPE_MOOD = 2,
	STALK_MOOD = 3,
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
enum target_type
{
	NO_TARGET = 0,
	PRIME_TARGET = 1,
	SECONDARY_TARGET = 2,
};

// 33 unions

struct MouseData {
	unsigned short buttons; // size=0, offset=0
	char xOffset; // size=0, offset=2
	char yOffset; // size=0, offset=3
};
struct NegconData {
	unsigned short digitalButtons; // size=0, offset=0
	char centralTwist; // size=0, offset=2
	char buttonI; // size=0, offset=3
	char buttonII; // size=0, offset=4
	char topLeft; // size=0, offset=5
};
struct GunConData {
	unsigned short digitalButtons; // size=0, offset=0
	unsigned char GunconX; // size=0, offset=2
	unsigned char GunConScreenDiv; // size=0, offset=3
	unsigned char GunconY; // size=0, offset=4
	unsigned char pad; // size=0, offset=5
};
struct AnalogjoyData {
	unsigned short digitalButtons; // size=0, offset=0
	unsigned char right_x; // size=0, offset=2
	unsigned char right_y; // size=0, offset=3
	unsigned char left_x; // size=0, offset=4
	unsigned char left_y; // size=0, offset=5
};
struct AnalogController {
	unsigned short digitalButtons; // size=0, offset=0
	unsigned char right_x; // size=0, offset=2
	unsigned char right_y; // size=0, offset=3
	unsigned char left_x; // size=0, offset=4
	unsigned char left_y; // size=0, offset=5
};

struct fake85
{
	unsigned short pad; // size=0, offset=0
	struct NegconData negcon; // size=6, offset=0
	struct AnalogController Analog; // size=6, offset=0
};

struct TapCtrllerData {
	unsigned char transStatus; // size=0, offset=0
	unsigned char dataFormat; // size=0, offset=1
	struct fake85 data; // size=6, offset=2
};
struct MultiTapData {
	struct TapCtrllerData ctrllers[4]; // size=32, offset=0
};


struct fake88
{
	unsigned short pad; // size=0, offset=0
struct MouseData mouse; // size=4, offset=0
struct NegconData negcon; // size=6, offset=0
struct AnalogjoyData joystick; // size=6, offset=0
struct MultiTapData tap; // size=32, offset=0
struct GunConData guncon; // size=6, offset=0
struct AnalogController analog; // size=6, offset=0
};
struct fake21{
	unsigned short pad; // size=0, offset=0
struct NegconData negcon; // size=6, offset=0
struct AnalogController Analog; // size=6, offset=0
};
struct fake5
{
	unsigned short pad; // size=0, offset=0
struct NegconData negcon; // size=6, offset=0
struct AnalogController Analog; // size=6, offset=0
};
struct fake8{
	unsigned short pad; // size=0, offset=0
struct MouseData mouse; // size=4, offset=0
struct NegconData negcon; // size=6, offset=0
struct AnalogjoyData joystick; // size=6, offset=0
struct MultiTapData tap; // size=32, offset=0
struct GunConData guncon; // size=6, offset=0
struct AnalogController analog; // size=6, offset=0
};
struct fake87{
	unsigned short pad; // size=0, offset=0
struct NegconData negcon; // size=6, offset=0
struct AnalogController Analog; // size=6, offset=0
};
struct fake90
{
	unsigned short pad; // size=0, offset=0
struct MouseData mouse; // size=4, offset=0
struct NegconData negcon; // size=6, offset=0
struct AnalogjoyData joystick; // size=6, offset=0
struct MultiTapData tap; // size=32, offset=0
struct GunConData guncon; // size=6, offset=0
struct AnalogController analog; // size=6, offset=0
};
struct fake97{
	unsigned short pad; // size=0, offset=0
struct NegconData negcon; // size=6, offset=0
struct AnalogController Analog; // size=6, offset=0
};
struct fake100{
	unsigned short pad; // size=0, offset=0
struct MouseData mouse; // size=4, offset=0
struct NegconData negcon; // size=6, offset=0
struct AnalogjoyData joystick; // size=6, offset=0
struct MultiTapData tap; // size=32, offset=0
struct GunConData guncon; // size=6, offset=0
struct AnalogController analog; // size=6, offset=0
};
struct fake59{
	unsigned short pad; // size=0, offset=0
struct NegconData negcon; // size=6, offset=0
struct AnalogController Analog; // size=6, offset=0
};
struct fake62{
	unsigned short pad; // size=0, offset=0
struct MouseData mouse; // size=4, offset=0
struct NegconData negcon; // size=6, offset=0
struct AnalogjoyData joystick; // size=6, offset=0
struct MultiTapData tap; // size=32, offset=0
struct GunConData guncon; // size=6, offset=0
struct AnalogController analog; // size=6, offset=0
};
struct fake95{
	unsigned short pad; // size=0, offset=0
struct NegconData negcon; // size=6, offset=0
struct AnalogController Analog; // size=6, offset=0
};
struct fake98{
	unsigned short pad; // size=0, offset=0
struct MouseData mouse; // size=4, offset=0
struct NegconData negcon; // size=6, offset=0
struct AnalogjoyData joystick; // size=6, offset=0
struct MultiTapData tap; // size=32, offset=0
struct GunConData guncon; // size=6, offset=0
struct AnalogController analog; // size=6, offset=0
};

struct fake79{
	unsigned short pad; // size=0, offset=0
struct MouseData mouse; // size=4, offset=0
struct NegconData negcon; // size=6, offset=0
struct AnalogjoyData joystick; // size=6, offset=0
struct MultiTapData tap; // size=32, offset=0
struct GunConData guncon; // size=6, offset=0
struct AnalogController analog; // size=6, offset=0
};
struct fake73{
	unsigned short pad; // size=0, offset=0
struct NegconData negcon; // size=6, offset=0
struct AnalogController Analog; // size=6, offset=0
};
struct fake86{
	unsigned short pad; // size=0, offset=0
struct NegconData negcon; // size=6, offset=0
struct AnalogController Analog; // size=6, offset=0
};
struct fake89{
	unsigned short pad; // size=0, offset=0
struct MouseData mouse; // size=4, offset=0
struct NegconData negcon; // size=6, offset=0
struct AnalogjoyData joystick; // size=6, offset=0
struct MultiTapData tap; // size=32, offset=0
struct GunConData guncon; // size=6, offset=0
struct AnalogController analog; // size=6, offset=0
};
struct fake76{
	unsigned short pad; // size=0, offset=0
struct MouseData mouse; // size=4, offset=0
struct NegconData negcon; // size=6, offset=0
struct AnalogjoyData joystick; // size=6, offset=0
struct MultiTapData tap; // size=32, offset=0
struct GunConData guncon; // size=6, offset=0
struct AnalogController analog; // size=6, offset=0
};
struct fake103{
	unsigned short pad; // size=0, offset=0
struct NegconData negcon; // size=6, offset=0
struct AnalogController Analog; // size=6, offset=0
};
struct fake106{
	unsigned short pad; // size=0, offset=0
struct MouseData mouse; // size=4, offset=0
struct NegconData negcon; // size=6, offset=0
struct AnalogjoyData joystick; // size=6, offset=0
struct MultiTapData tap; // size=32, offset=0
struct GunConData guncon; // size=6, offset=0
struct AnalogController analog; // size=6, offset=0
};

struct fake92{
	unsigned short pad; // size=0, offset=0
struct MouseData mouse; // size=4, offset=0
struct NegconData negcon; // size=6, offset=0
struct AnalogjoyData joystick; // size=6, offset=0
struct MultiTapData tap; // size=32, offset=0
struct GunConData guncon; // size=6, offset=0
struct AnalogController analog; // size=6, offset=0
};
struct fake24
{
	unsigned short pad; // size=0, offset=0
struct NegconData negcon; // size=6, offset=0
struct AnalogController Analog; // size=6, offset=0
};
struct fake27{
	unsigned short pad; // size=0, offset=0
struct MouseData mouse; // size=4, offset=0
struct NegconData negcon; // size=6, offset=0
struct AnalogjoyData joystick; // size=6, offset=0
struct MultiTapData tap; // size=32, offset=0
struct GunConData guncon; // size=6, offset=0
struct AnalogController analog; // size=6, offset=0
};
struct fake113{
	unsigned short pad; // size=0, offset=0
struct NegconData negcon; // size=6, offset=0
struct AnalogController Analog; // size=6, offset=0
};
struct fake116{
	unsigned short pad; // size=0, offset=0
struct MouseData mouse; // size=4, offset=0
struct NegconData negcon; // size=6, offset=0
struct AnalogjoyData joystick; // size=6, offset=0
struct MultiTapData tap; // size=32, offset=0
struct GunConData guncon; // size=6, offset=0
struct AnalogController analog; // size=6, offset=0
};
struct fake81{
	unsigned short pad; // size=0, offset=0
struct NegconData negcon; // size=6, offset=0
struct AnalogController Analog; // size=6, offset=0
};
struct fake84{
	unsigned short pad; // size=0, offset=0
struct MouseData mouse; // size=4, offset=0
struct NegconData negcon; // size=6, offset=0
struct AnalogjoyData joystick; // size=6, offset=0
struct MultiTapData tap; // size=32, offset=0
struct GunConData guncon; // size=6, offset=0
struct AnalogController analog; // size=6, offset=0
};
struct fake74{
	unsigned short pad; // size=0, offset=0
struct NegconData negcon; // size=6, offset=0
struct AnalogController Analog; // size=6, offset=0
};
struct fake77
{
	unsigned short pad; // size=0, offset=0
	struct MouseData mouse; // size=4, offset=0
	struct NegconData negcon; // size=6, offset=0
	struct AnalogjoyData joystick; // size=6, offset=0
	struct MultiTapData tap; // size=32, offset=0
	struct GunConData guncon; // size=6, offset=0
	struct AnalogController analog; // size=6, offset=0
};

#ifndef PSX
// 136 structs
struct TCB {
	long status; // size=0, offset=0
	long mode; // size=0, offset=4
	unsigned long reg[40]; // size=160, offset=8
	long system[6]; // size=24, offset=168
};

struct EXEC {
	unsigned long pc0; // size=0, offset=0
	unsigned long gp0; // size=0, offset=4
	unsigned long t_addr; // size=0, offset=8
	unsigned long t_size; // size=0, offset=12
	unsigned long d_addr; // size=0, offset=16
	unsigned long d_size; // size=0, offset=20
	unsigned long b_addr; // size=0, offset=24
	unsigned long b_size; // size=0, offset=28
	unsigned long s_addr; // size=0, offset=32
	unsigned long s_size; // size=0, offset=36
	unsigned long sp; // size=0, offset=40
	unsigned long fp; // size=0, offset=44
	unsigned long gp; // size=0, offset=48
	unsigned long ret; // size=0, offset=52
	unsigned long base; // size=0, offset=56
};
struct DIRENTRY {
	char name[20]; // size=20, offset=0
	long attr; // size=0, offset=20
	long size; // size=0, offset=24
	struct DIRENTRY *next; // size=40, offset=28
	long head; // size=0, offset=32
	char system[4]; // size=4, offset=36
};

#endif

struct VECTOR {
	long vx; // size=0, offset=0
	long vy; // size=0, offset=4
	long vz; // size=0, offset=8
	long pad; // size=0, offset=12
};
struct SVECTOR {
	short vx; // size=0, offset=0
	short vy; // size=0, offset=2
	short vz; // size=0, offset=4
	short pad; // size=0, offset=6
};
struct CVECTOR {
	unsigned char r; // size=0, offset=0
	unsigned char g; // size=0, offset=1
	unsigned char b; // size=0, offset=2
	unsigned char cd; // size=0, offset=3
};
struct DVECTOR {
	short vx; // size=0, offset=0
	short vy; // size=0, offset=2
};
struct RVECTOR {
	struct SVECTOR v; // size=8, offset=0
	unsigned char uv[2]; // size=2, offset=8
	unsigned short pad; // size=0, offset=10
	struct CVECTOR c; // size=4, offset=12
	struct DVECTOR sxy; // size=4, offset=16
	unsigned long sz; // size=0, offset=20
};
struct CRVECTOR3 {
	struct RVECTOR r01; // size=24, offset=0
	struct RVECTOR r12; // size=24, offset=24
	struct RVECTOR r20; // size=24, offset=48
	struct RVECTOR *r0; // size=24, offset=72
	struct RVECTOR *r1; // size=24, offset=76
	struct RVECTOR *r2; // size=24, offset=80
	unsigned long *rtn; // size=0, offset=84
};
struct CRVECTOR4 {
	struct RVECTOR r01; // size=24, offset=0
	struct RVECTOR r02; // size=24, offset=24
	struct RVECTOR r31; // size=24, offset=48
	struct RVECTOR r32; // size=24, offset=72
	struct RVECTOR rc; // size=24, offset=96
	struct RVECTOR *r0; // size=24, offset=120
	struct RVECTOR *r1; // size=24, offset=124
	struct RVECTOR *r2; // size=24, offset=128
	struct RVECTOR *r3; // size=24, offset=132
	unsigned long *rtn; // size=0, offset=136
};
struct RECTTRC {
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
	struct RECTTRC clip; // size=8, offset=0
	short ofs[2]; // size=4, offset=8
	struct RECTTRC tw; // size=8, offset=12
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
	struct RECTTRC disp; // size=8, offset=0
	struct RECTTRC screen; // size=8, offset=8
	unsigned char isinter; // size=0, offset=16
	unsigned char isrgb24; // size=0, offset=17
	unsigned char pad0; // size=0, offset=18
	unsigned char pad1; // size=0, offset=19
};
struct PHD_VECTOR {
	long x; // size=0, offset=0
	long y; // size=0, offset=4
	long z; // size=0, offset=8
};
struct PHD_3DPOS {
	long x_pos; // size=0, offset=0
	long y_pos; // size=0, offset=4
	long z_pos; // size=0, offset=8
	short x_rot; // size=0, offset=12
	short y_rot; // size=0, offset=14
	short z_rot; // size=0, offset=16
};
struct TEXTURE {
	unsigned char u0; // size=0, offset=0
	unsigned char v0; // size=0, offset=1
	unsigned short clut; // size=0, offset=2
	unsigned char u1; // size=0, offset=4
	unsigned char v1; // size=0, offset=5
	unsigned short tpage; // size=0, offset=6
	unsigned char u2; // size=0, offset=8
	unsigned char v2; // size=0, offset=9
	unsigned char id[2]; // size=2, offset=10
	unsigned char u3; // size=0, offset=12
	unsigned char v3; // size=0, offset=13
	unsigned short wclut; // size=0, offset=14
};
struct CdlLOC {
	unsigned char minute; // size=0, offset=0
	unsigned char second; // size=0, offset=1
	unsigned char sector; // size=0, offset=2
	unsigned char track; // size=0, offset=3
};
struct ILIGHT {
	short x; // size=0, offset=0
	short y; // size=0, offset=2
	short z; // size=0, offset=4
	short pad1; // size=0, offset=6
	unsigned char r; // size=0, offset=8
	unsigned char g; // size=0, offset=9
	unsigned char b; // size=0, offset=10
	unsigned char pad; // size=0, offset=11
};
struct ITEM_LIGHT {
	struct ILIGHT Light[4]; // size=48, offset=0
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
	void *data; // size=0, offset=60
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

struct SpuVolume {
	short left; // size=0, offset=0
	short right; // size=0, offset=2
};
struct SpuVoiceAttr {
	unsigned long voice; // size=0, offset=0
	unsigned long mask; // size=0, offset=4
	struct SpuVolume volume; // size=4, offset=8
	struct SpuVolume volmode; // size=4, offset=12
	struct SpuVolume volumex; // size=4, offset=16
	unsigned short pitch; // size=0, offset=20
	unsigned short note; // size=0, offset=22
	unsigned short sample_note; // size=0, offset=24
	short envx; // size=0, offset=26
	unsigned long addr; // size=0, offset=28
	unsigned long loop_addr; // size=0, offset=32
	long a_mode; // size=0, offset=36
	long s_mode; // size=0, offset=40
	long r_mode; // size=0, offset=44
	unsigned short ar; // size=0, offset=48
	unsigned short dr; // size=0, offset=50
	unsigned short sr; // size=0, offset=52
	unsigned short rr; // size=0, offset=54
	unsigned short sl; // size=0, offset=56
	unsigned short adsr1; // size=0, offset=58
	unsigned short adsr2; // size=0, offset=60
};
struct SpuExtAttr {
	struct SpuVolume volume; // size=4, offset=0
	long reverb; // size=0, offset=4
	long mix; // size=0, offset=8
};
struct SpuStVoiceAttr {
	char status; // size=0, offset=0
	char pad1; // size=0, offset=1
	char pad2; // size=0, offset=2
	char pad3; // size=0, offset=3
	long last_size; // size=0, offset=4
	unsigned long buf_addr; // size=0, offset=8
	unsigned long data_addr; // size=0, offset=12
};
struct FLOOR_INFO {
	unsigned short index; // size=0, offset=0
	unsigned short fx : 4; // offset=2.0
	unsigned short box : 11; // offset=2.4
	unsigned short stopper : 1; // offset=3.7
	unsigned char pit_room; // size=0, offset=4
	char floor; // size=0, offset=5
	unsigned char sky_room; // size=0, offset=6
	char ceiling; // size=0, offset=7
};
struct LIGHTINFO {
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
struct MESH_INFO {
	long x; // size=0, offset=0
	long y; // size=0, offset=4
	long z; // size=0, offset=8
	short y_rot; // size=0, offset=12
	short shade; // size=0, offset=14
	short Flags; // size=0, offset=16
	short static_number; // size=0, offset=18
};
struct FX_INFO {
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
struct lara_arm {
	short *frame_base; // size=0, offset=0
	short frame_number; // size=0, offset=4
	short anim_number; // size=0, offset=6
	short lock; // size=0, offset=8
	short y_rot; // size=0, offset=10
	short x_rot; // size=0, offset=12
	short z_rot; // size=0, offset=14
	short flash_gun; // size=0, offset=16
};
struct box_node {
	short exit_box; // size=0, offset=0
	unsigned short search_number; // size=0, offset=2
	short next_expansion; // size=0, offset=4
	short box_number; // size=0, offset=6
};
struct lot_info {
	struct box_node *node; // size=8, offset=0
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
	struct ITEM_INFO *enemy; // size=144, offset=20
	struct ITEM_INFO ai_target; // size=144, offset=24
	short pad; // size=0, offset=168
	short item_num; // size=0, offset=170
	struct PHD_VECTOR target; // size=12, offset=172
	struct lot_info LOT; // size=44, offset=184
};
struct ROPE_STRUCT {
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
	struct FX_INFO *spaz_effect; // size=44, offset=88
	int mesh_effects; // size=0, offset=92
	short *mesh_ptrs[15]; // size=60, offset=96
	struct ITEM_INFO *target; // size=144, offset=156
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
	struct creature_info *creature; // size=228, offset=224
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
	void *GeneralPtr; // size=0, offset=264
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
struct MATRIX3D {
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
struct GAMEFLOW {
	unsigned long CheatEnabled : 1; // offset=0.0
	unsigned long LoadSaveEnabled : 1; // offset=0.1
	unsigned long TitleEnabled : 1; // offset=0.2
	unsigned long PlayAnyLevel : 1; // offset=0.3
	unsigned long Language : 3; // offset=0.4
	unsigned long DemoDisc : 1; // offset=0.7
	unsigned long Unused : 24; // offset=1.0
	unsigned long InputTimeout; // size=0, offset=4
	unsigned char SecurityTag; // size=0, offset=8
	unsigned char nLevels; // size=0, offset=9
	unsigned char nFileNames; // size=0, offset=10
	unsigned char Pad; // size=0, offset=11
	unsigned short FileNameLen; // size=0, offset=12
	unsigned short ScriptLen; // size=0, offset=14
};
struct STRINGHEADER {
	unsigned short nStrings; // size=0, offset=0
	unsigned short nPSXStrings; // size=0, offset=2
	unsigned short nPCStrings; // size=0, offset=4
	unsigned short StringWadLen; // size=0, offset=6
	unsigned short PSXStringWadLen; // size=0, offset=8
	unsigned short PCStringWadLen; // size=0, offset=10
};
struct GAME_VECTOR {
	long x; // size=0, offset=0
	long y; // size=0, offset=4
	long z; // size=0, offset=8
	short room_number; // size=0, offset=12
	short box_number; // size=0, offset=14
};
struct OBJECT_VECTOR {
	long x; // size=0, offset=0
	long y; // size=0, offset=4
	long z; // size=0, offset=8
	short data; // size=0, offset=12
	short flags; // size=0, offset=14
};
struct SPHERE {
	long x; // size=0, offset=0
	long y; // size=0, offset=4
	long z; // size=0, offset=8
	long r; // size=0, offset=12
};
struct RTDECODE {
	unsigned long length; // size=0, offset=0
	unsigned long off; // size=0, offset=4
	unsigned short counter; // size=0, offset=8
	unsigned short data; // size=0, offset=10
	unsigned char decodetype; // size=0, offset=12
	unsigned char packmethod; // size=0, offset=13
	unsigned short padfuck; // size=0, offset=14
};
struct ACTORME {
	int offset; // size=0, offset=0
	short objslot; // size=0, offset=4
	short nodes; // size=0, offset=6
};
struct room_info {
	short *data; // size=0, offset=0
	short *door; // size=0, offset=4
	struct FLOOR_INFO *floor; // size=8, offset=8
	struct LIGHTINFO *light; // size=32, offset=12
	struct MESH_INFO *mesh; // size=20, offset=16
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
struct PENDULUM {
	struct PHD_VECTOR Position; // size=12, offset=0
	struct PHD_VECTOR Velocity; // size=12, offset=12
	int node; // size=0, offset=24
	struct ROPE_STRUCT *Rope; // size=1172, offset=28
};
struct object_info {
	short nmeshes; // size=0, offset=0
	short mesh_index; // size=0, offset=2
	long bone_index; // size=0, offset=4
	short *frame_base; // size=0, offset=8
	void(*initialise)(); // size=0, offset=12
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
struct RAT_STRUCT {
	struct PHD_3DPOS pos; // size=20, offset=0
	short room_number; // size=0, offset=20
	short speed; // size=0, offset=22
	short fallspeed; // size=0, offset=24
	unsigned char On; // size=0, offset=26
	unsigned char flags; // size=0, offset=27
};
struct BAT_STRUCT {
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
struct SPIDER_STRUCT {
	struct PHD_3DPOS pos; // size=20, offset=0
	short room_number; // size=0, offset=20
	short speed; // size=0, offset=22
	short fallspeed; // size=0, offset=24
	unsigned char On; // size=0, offset=26
	unsigned char flags; // size=0, offset=27
};
struct TWOGUN_INFO {
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
struct CHARDEF {
	unsigned char u; // size=0, offset=0
	unsigned char v; // size=0, offset=1
	unsigned char w; // size=0, offset=2
	unsigned char h; // size=0, offset=3
	char YOffset; // size=0, offset=4
	unsigned char TopShade; // size=0, offset=5
	unsigned char BottomShade; // size=0, offset=6
};
struct COLL_INFO {
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
	short coll_type; // size=0, offset=122
	short *trigger; // size=0, offset=124
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
struct ANIM_STRUCT {
	short *frame_ptr; // size=0, offset=0
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
struct SPARKS {
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
struct PACKNODE {
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
	char *xpacked; // size=0, offset=72
	char *ypacked; // size=0, offset=76
	char *zpacked; // size=0, offset=80
};
struct NODELOADHEADER {
	short xkey; // size=0, offset=0
	short ykey; // size=0, offset=2
	short zkey; // size=0, offset=4
	short packmethod; // size=0, offset=6
	short xlength; // size=0, offset=8
	short ylength; // size=0, offset=10
	short zlength; // size=0, offset=12
};
struct RESIDENT_THING {
	char *packed_data; // size=0, offset=0
};
struct NEW_CUTSCENE {
	short numactors; // size=0, offset=0
	short numframes; // size=0, offset=2
	int orgx; // size=0, offset=4
	int orgy; // size=0, offset=8
	int orgz; // size=0, offset=12
	int audio_track; // size=0, offset=16
	int camera_offset; // size=0, offset=20
	struct ACTORME actor_data[10]; // size=80, offset=24
};
struct CUTSEQ_ROUTINES {
	void(*init_func)(); // size=0, offset=0
	void(*control_func)(); // size=0, offset=4
	void(*end_func)(); // size=0, offset=8
};
struct DOORPOS_DATA {
	struct FLOOR_INFO *floor; // size=8, offset=0
	struct FLOOR_INFO data; // size=8, offset=4
	short block; // size=0, offset=12
};
struct DOOR_DATA {
	struct DOORPOS_DATA d1; // size=16, offset=0
	struct DOORPOS_DATA d1flip; // size=16, offset=16
	struct DOORPOS_DATA d2; // size=16, offset=32
	struct DOORPOS_DATA d2flip; // size=16, offset=48
	short Opened; // size=0, offset=64
	short *dptr1; // size=0, offset=68
	short *dptr2; // size=0, offset=72
	short *dptr3; // size=0, offset=76
	short *dptr4; // size=0, offset=80
	char dn1; // size=0, offset=84
	char dn2; // size=0, offset=85
	char dn3; // size=0, offset=86
	char dn4; // size=0, offset=87
	struct ITEM_INFO *item; // size=144, offset=88
};
struct CHANGE_STRUCT {
	short goal_anim_state; // size=0, offset=0
	short number_ranges; // size=0, offset=2
	short range_index; // size=0, offset=4
};
struct RANGE_STRUCT {
	short start_frame; // size=0, offset=0
	short end_frame; // size=0, offset=2
	short link_anim_num; // size=0, offset=4
	short link_frame_num; // size=0, offset=6
};
struct door_vbuf {
	long xv; // size=0, offset=0
	long yv; // size=0, offset=4
	long zv; // size=0, offset=8
};
struct BITE_INFO {
	long x; // size=0, offset=0
	long y; // size=0, offset=4
	long z; // size=0, offset=8
	long mesh_num; // size=0, offset=12
};
struct box_info {
	unsigned char left; // size=0, offset=0
	unsigned char right; // size=0, offset=1
	unsigned char top; // size=0, offset=2
	unsigned char bottom; // size=0, offset=3
	short height; // size=0, offset=4
	short overlap_index; // size=0, offset=6
};
struct AI_info {
	short zone_number; // size=0, offset=0
	short enemy_zone; // size=0, offset=2
	long distance; // size=0, offset=4
	long ahead; // size=0, offset=8
	long bite; // size=0, offset=12
	short angle; // size=0, offset=16
	short x_angle; // size=0, offset=18
	short enemy_facing; // size=0, offset=20
};
struct AIOBJECT {
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
struct CAMERA_INFO {
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
	struct ITEM_INFO *item; // size=144, offset=92
	struct ITEM_INFO *last_item; // size=144, offset=96
	struct OBJECT_VECTOR *fixed; // size=16, offset=100
	int mike_at_lara; // size=0, offset=104
	struct PHD_VECTOR mike_pos; // size=12, offset=108
};
struct SHATTER_ITEM {
	struct SPHERE Sphere; // size=16, offset=0
	struct ITEM_LIGHT *il; // size=48, offset=16
	short *meshp; // size=0, offset=20
	long Bit; // size=0, offset=24
	short YRot; // size=0, offset=28
	short Flags; // size=0, offset=30
};
struct OLD_CAMERA {
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
struct static_info {
	short mesh_number; // size=0, offset=0
	short flags; // size=0, offset=2
	short x_minp; // size=0, offset=4
	short x_maxp; // size=0, offset=6
	short y_minp; // size=0, offset=8
	short y_maxp; // size=0, offset=10
	short z_minp; // size=0, offset=12
	short z_maxp; // size=0, offset=14
	short x_minc; // size=0, offset=16
	short x_maxc; // size=0, offset=18
	short y_minc; // size=0, offset=20
	short y_maxc; // size=0, offset=22
	short z_minc; // size=0, offset=24
	short z_maxc; // size=0, offset=26
};
struct PSXTEXTI {
	unsigned char u0; // size=0, offset=0
	unsigned char v0; // size=0, offset=1
	unsigned short clut; // size=0, offset=2
	unsigned char u1; // size=0, offset=4
	unsigned char v1; // size=0, offset=5
	unsigned short tpage; // size=0, offset=6
	unsigned char u2; // size=0, offset=8
	unsigned char v2; // size=0, offset=9
	unsigned char codeGT4; // size=0, offset=10
	unsigned char codeGT3; // size=0, offset=11
	unsigned char u3; // size=0, offset=12
	unsigned char v3; // size=0, offset=13
	unsigned short pad3; // size=0, offset=14
};
struct DEBRIS_STRUCT {
	void *TextInfo; // size=0, offset=0
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
struct SPOTCAM {
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
struct QUAKE_CAM {
	struct GAME_VECTOR spos; // size=16, offset=0
	struct GAME_VECTOR epos; // size=16, offset=16
};
struct DYNAMIC {
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
struct SP_DYNAMIC {
	unsigned char On; // size=0, offset=0
	unsigned char Falloff; // size=0, offset=1
	unsigned char R; // size=0, offset=2
	unsigned char G; // size=0, offset=3
	unsigned char B; // size=0, offset=4
	unsigned char Flags; // size=0, offset=5
	unsigned char Pad[2]; // size=2, offset=6
};
struct SPLASH_STRUCT {
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
struct RIPPLE_STRUCT {
	long x; // size=0, offset=0
	long y; // size=0, offset=4
	long z; // size=0, offset=8
	char flags; // size=0, offset=12
	unsigned char life; // size=0, offset=13
	unsigned char size; // size=0, offset=14
	unsigned char init; // size=0, offset=15
};
struct SPLASH_SETUP {
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
struct FIRE_LIST {
	long x; // size=0, offset=0
	long y; // size=0, offset=4
	long z; // size=0, offset=8
	char on; // size=0, offset=12
	char size; // size=0, offset=13
	short room_number; // size=0, offset=14
};
struct FIRE_SPARKS {
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
struct SMOKE_SPARKS {
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
struct BLOOD_STRUCT {
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
struct GUNSHELL_STRUCT {
	struct PHD_3DPOS pos; // size=20, offset=0
	short fallspeed; // size=0, offset=20
	short room_number; // size=0, offset=22
	short speed; // size=0, offset=24
	short counter; // size=0, offset=26
	short DirXrot; // size=0, offset=28
	short object_number; // size=0, offset=30
};
struct BUBBLE_STRUCT {
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
struct GUNFLASH_STRUCT {
	struct MATRIX3D matrix; // size=32, offset=0
	short on; // size=0, offset=32
};
struct DRIP_STRUCT {
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
struct NODEOFFSET_INFO {
	short x; // size=0, offset=0
	short y; // size=0, offset=2
	short z; // size=0, offset=4
	char mesh_num; // size=0, offset=6
	unsigned char GotIt; // size=0, offset=7
};
struct SHOCKWAVE_STRUCT {
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
struct HAIR_STRUCT {
	struct PHD_3DPOS pos; // size=20, offset=0
	struct PHD_VECTOR vel; // size=12, offset=20
};
struct DISPLAYPU {
	short life; // size=0, offset=0
	short object_number; // size=0, offset=2
};
struct INVOBJ {
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
struct OBJLIST {
	short invitem; // size=0, offset=0
	unsigned short yrot; // size=0, offset=2
	unsigned short bright; // size=0, offset=4
};
struct RINGME {
	struct OBJLIST current_object_list[100]; // size=600, offset=0
	int ringactive; // size=0, offset=600
	int objlistmovement; // size=0, offset=604
	int curobjinlist; // size=0, offset=608
	int numobjectsinlist; // size=0, offset=612
};
struct AMMOLIST {
	short invitem; // size=0, offset=0
	short amount; // size=0, offset=2
	unsigned short yrot; // size=0, offset=4
};
struct MENUTHANG {
	int type; // size=0, offset=0
	char *text; // size=0, offset=4
};
struct COMBINELIST {
	void(*combine_routine)(); // size=0, offset=0
	short item1; // size=0, offset=4
	short item2; // size=0, offset=6
	short combined_item; // size=0, offset=8
};
struct WEAPON_INFO {
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
struct PISTOL_DEF {
	short ObjectNum; // size=0, offset=0
	char Draw1Anim2; // size=0, offset=2
	char Draw1Anim; // size=0, offset=3
	char Draw2Anim; // size=0, offset=4
	char RecoilAnim; // size=0, offset=5
};
struct SUBSUIT_INFO {
	short XRot; // size=0, offset=0
	short dXRot; // size=0, offset=2
	short XRotVel; // size=0, offset=4
	short Vel[2]; // size=4, offset=6
	short YVel; // size=0, offset=10
};
struct savegame_info {
	short Checksum; // size=0, offset=0
	unsigned short VolumeCD; // size=0, offset=2
	unsigned short VolumeFX; // size=0, offset=4
	short ScreenX; // size=0, offset=6
	short ScreenY; // size=0, offset=8
	unsigned char ControlOption; // size=0, offset=10
	unsigned char VibrateOn; // size=0, offset=11
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
struct SAMPLE_INFO {
	short number; // size=0, offset=0
	unsigned char volume; // size=0, offset=2
	char radius; // size=0, offset=3
	char randomness; // size=0, offset=4
	char pitch; // size=0, offset=5
	short flags; // size=0, offset=6
};
struct SoundSlot {
	int OrigVolume; // size=0, offset=0
	int nVolume; // size=0, offset=4
	int nPan; // size=0, offset=8
	int nPitch; // size=0, offset=12
	int nSampleInfo; // size=0, offset=16
	unsigned long distance; // size=0, offset=20
	struct PHD_VECTOR pos; // size=12, offset=24
};
struct FOOTPRINT {
	long x; // size=0, offset=0
	long y; // size=0, offset=4
	long z; // size=0, offset=8
	short YRot; // size=0, offset=12
	short Active; // size=0, offset=14
};
struct VECTOR3D {
	long x; // size=0, offset=0
	long y; // size=0, offset=4
	long z; // size=0, offset=8
};
struct CdlFILE {
	struct CdlLOC pos; // size=4, offset=0
	unsigned long size; // size=0, offset=4
	char name[16]; // size=16, offset=8
};
struct SpuCommonAttr {
	unsigned long mask; // size=0, offset=0
	struct SpuVolume mvol; // size=4, offset=4
	struct SpuVolume mvolmode; // size=4, offset=8
	struct SpuVolume mvolx; // size=4, offset=12
	struct SpuExtAttr cd; // size=12, offset=16
	struct SpuExtAttr ext; // size=12, offset=28
};
struct LINE_F2 {
	unsigned long tag; // size=0, offset=0
	unsigned char r0; // size=0, offset=4
	unsigned char g0; // size=0, offset=5
	unsigned char b0; // size=0, offset=6
	unsigned char code; // size=0, offset=7
	short x0; // size=0, offset=8
	short y0; // size=0, offset=10
	short x1; // size=0, offset=12
	short y1; // size=0, offset=14
};
struct DB_STRUCT {
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
struct PSXTEXTSTRUCT {
	unsigned long u0v0clut; // size=0, offset=0
	unsigned long u1v1tpage; // size=0, offset=4
	unsigned long u2v2pad; // size=0, offset=8
	unsigned long u3v3pad; // size=0, offset=12
};
struct PSXSPRITESTRUCT {
	short x1; // size=0, offset=0
	short y1; // size=0, offset=2
	short x2; // size=0, offset=4
	short y2; // size=0, offset=6
	unsigned short clut; // size=0, offset=8
	unsigned short tpage; // size=0, offset=10
	unsigned char u1; // size=0, offset=12
	unsigned char v1; // size=0, offset=13
	unsigned char u2; // size=0, offset=14
	unsigned char v2; // size=0, offset=15
};
struct MMTEXTURE {
	struct TEXTURE t[3]; // size=48, offset=0
};
struct TSV {
	unsigned long xy; // size=0, offset=0
	unsigned long rgz; // size=0, offset=4
};
struct ControllerPacket {
	unsigned char transStatus; // size=0, offset=0
	unsigned char dataFormat; // size=0, offset=1
	struct fake76 data; // size=32, offset=2
};
struct pad_configs {
	unsigned long pad_L2; // size=0, offset=0
	unsigned long pad_R2; // size=0, offset=4
	unsigned long pad_L1; // size=0, offset=8
	unsigned long pad_R1; // size=0, offset=12
	unsigned long pad_triangle; // size=0, offset=16
	unsigned long pad_square; // size=0, offset=20
	unsigned long pad_circle; // size=0, offset=24
	unsigned long pad_cross; // size=0, offset=28
};
struct GouraudBarColourSet {
	unsigned char abLeftRed[5]; // size=5, offset=0
	unsigned char abLeftGreen[5]; // size=5, offset=5
	unsigned char abLeftBlue[5]; // size=5, offset=10
	unsigned char abRightRed[5]; // size=5, offset=15
	unsigned char abRightGreen[5]; // size=5, offset=20
	unsigned char abRightBlue[5]; // size=5, offset=25
};
struct STASHEDOBJ {
	short clip; // size=0, offset=0
	short numnodestodraw; // size=0, offset=2
	struct ITEM_INFO *item; // size=144, offset=4
	short *frmptr0; // size=0, offset=8
};
struct STASHEDDAT {
	short *mesh; // size=0, offset=0
	char matrix[32]; // size=32, offset=4
};
struct WATERTAB {
	char shimmer; // size=0, offset=0
	char choppy; // size=0, offset=1
	unsigned char random; // size=0, offset=2
	unsigned char abs; // size=0, offset=3
};
struct LINE_G2 {
	unsigned long tag; // size=0, offset=0
	unsigned char r0; // size=0, offset=4
	unsigned char g0; // size=0, offset=5
	unsigned char b0; // size=0, offset=6
	unsigned char code; // size=0, offset=7
	short x0; // size=0, offset=8
	short y0; // size=0, offset=10
	unsigned char r1; // size=0, offset=12
	unsigned char g1; // size=0, offset=13
	unsigned char b1; // size=0, offset=14
	unsigned char p1; // size=0, offset=15
	short x1; // size=0, offset=16
	short y1; // size=0, offset=18
};
struct VIBRATION {
	short Rate; // size=0, offset=0
	short Len; // size=0, offset=2
	short Lev; // size=0, offset=4
	short Acc; // size=0, offset=6
	short Dec; // size=0, offset=8
	short Sus; // size=0, offset=10
	short Flag; // size=0, offset=12
	short Vib; // size=0, offset=14
};
struct REQUESTER {
	unsigned short TitleTxt; // size=0, offset=0
	unsigned short TitleCol : 5; // offset=2.0
	unsigned short nOptions : 3; // offset=2.5
	unsigned short CursorPos : 3; // offset=3.0
	unsigned short OptionCol : 5; // offset=3.3
	unsigned long JustifyL : 5; // offset=4.0
	unsigned long JustifyR : 5; // offset=4.5
	unsigned long Arrows : 5; // offset=5.2
	unsigned long Ignore : 5; // offset=5.7
	unsigned short OptionTxt[5]; // size=10, offset=8
};
struct SCALE {
	short xgrid; // size=0, offset=0
	char scalefactor; // size=0, offset=2
	char nummarks; // size=0, offset=3
};
struct COCKSUCK {
	unsigned char r; // size=0, offset=0
	unsigned char g; // size=0, offset=1
	unsigned char b; // size=0, offset=2
	unsigned char pad; // size=0, offset=3
	short finalcnt; // size=0, offset=4
	short profile_xcnt; // size=0, offset=6
};
struct PACKEDNAME {
	char Name[12]; // size=12, offset=0
	unsigned char Days; // size=0, offset=12
	unsigned char Hours; // size=0, offset=13
	unsigned char Min; // size=0, offset=14
	unsigned char Sec; // size=0, offset=15
	unsigned short Slot; // size=0, offset=16
	unsigned char Level; // size=0, offset=18
	unsigned char Pad; // size=0, offset=19
};
struct POLY_FT4 {
	unsigned long tag; // size=0, offset=0
	unsigned char r0; // size=0, offset=4
	unsigned char g0; // size=0, offset=5
	unsigned char b0; // size=0, offset=6
	unsigned char code; // size=0, offset=7
	short x0; // size=0, offset=8
	short y0; // size=0, offset=10
	unsigned char u0; // size=0, offset=12
	unsigned char v0; // size=0, offset=13
	unsigned short clut; // size=0, offset=14
	short x1; // size=0, offset=16
	short y1; // size=0, offset=18
	unsigned char u1; // size=0, offset=20
	unsigned char v1; // size=0, offset=21
	unsigned short tpage; // size=0, offset=22
	short x2; // size=0, offset=24
	short y2; // size=0, offset=26
	unsigned char u2; // size=0, offset=28
	unsigned char v2; // size=0, offset=29
	unsigned short pad1; // size=0, offset=30
	short x3; // size=0, offset=32
	short y3; // size=0, offset=34
	unsigned char u3; // size=0, offset=36
	unsigned char v3; // size=0, offset=37
	unsigned short pad2; // size=0, offset=38
};

#endif