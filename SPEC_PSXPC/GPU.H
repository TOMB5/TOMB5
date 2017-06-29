#ifndef GPU_H
#define GPU_H

struct RECT
{
	short x;
	short y;
	short w;
	short h;
};

struct DR_ENV
{
	unsigned long tag;
	unsigned long code[15];
};

struct DRAWENV
{
	struct RECT clip;
	short ofs[2];
	struct RECT tw;
	unsigned short tpage;
	unsigned char dtd;
	unsigned char dfe;
	unsigned char isbg;
	unsigned char r0;
	unsigned char g0;
	unsigned char b0;
	struct DR_ENV dr_env;
};

struct DISPENV
{
	struct RECT disp;
	struct RECT screen;
	unsigned char isinter;
	unsigned char isrgb24;
	unsigned char pad0;
	unsigned char pad1;
};

struct DB_STRUCT
{
	int current_buffer;
	unsigned long* ot;
	char* polyptr;
	char* curpolybuf;
	char* polybuf_limit;
	int nOTSize;
	int nPBSize;
	unsigned long* order_table[2];
	unsigned long* poly_buffer[2];
	unsigned long* pickup_ot;
	unsigned long* pickup_order_table[2];
	struct DRAWENV draw[2];
	struct DISPENV disp[2];
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

struct MMTEXTURE
{
	struct TEXTURE t[3];
};

extern unsigned long GnFrameCounter;
extern unsigned long GnLastFrameCount;
extern struct PSXTEXTSTRUCT* psxtextinfo;
extern struct PSXSPRITESTRUCT* psxspriteinfo;
extern int rgbscaleme;
extern int gfx_debugging_mode;
extern struct DB_STRUCT db;
extern struct MMTEXTURE* RoomTextInfo;
extern unsigned long GadwOrderingTables_V2[512];
extern unsigned long GadwOrderingTables[5128];
extern unsigned long GadwPolygonBuffers[52260];

void GPU_UseOrderingTables(unsigned long* pBuffers, int nOTSize);

#endif