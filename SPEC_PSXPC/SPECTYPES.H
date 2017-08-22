#ifndef SPECTYPES_H
#define SPECTYPES_H

#include "TYPES.H"

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

struct ControllerPacket
{
	unsigned char transStatus;
	unsigned char dataFormat;
	//union .76fake data;//?
};

#endif