#ifndef SPECTYPES_H
#define SPECTYPES_H

#include "TYPES.H"



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

#ifdef PSXPC_VERSION
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
struct VECTOR3D {
	long x; // size=0, offset=0
	long y; // size=0, offset=4
	long z; // size=0, offset=8
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

typedef void *SpuIRQCallbackProc;
typedef void *SpuTransferCallbackProc;
typedef void *SpuStCallbackProc;

#endif