#include "LIBGTE.H"
#include "EMULATOR_GLOBALS.H"

#define VX0  (gteRegs.CP2D.p[ 0 ].sw.l)
#define VY0  (gteRegs.CP2D.p[ 0 ].sw.h)
#define VZ0  (gteRegs.CP2D.p[ 1 ].sw.l)
#define VX1  (gteRegs.CP2D.p[ 2 ].w.l)
#define VY1  (gteRegs.CP2D.p[ 2 ].w.h)
#define VZ1  (gteRegs.CP2D.p[ 3 ].w.l)
#define VX2  (gteRegs.CP2D.p[ 4 ].w.l)
#define VY2  (gteRegs.CP2D.p[ 4 ].w.h)
#define VZ2  (gteRegs.CP2D.p[ 5 ].w.l)
#define R    (gteRegs.CP2D.p[ 6 ].b.l)
#define G    (gteRegs.CP2D.p[ 6 ].b.h)
#define B    (gteRegs.CP2D.p[ 6 ].b.h2)
#define CODE (gteRegs.CP2D.p[ 6 ].b.h3)
#define OTZ  (gteRegs.CP2D.p[ 7 ].w.l)
#define IR0  (gteRegs.CP2D.p[ 8 ].sw.l)
#define IR1  (gteRegs.CP2D.p[ 9 ].sw.l)
#define IR2  (gteRegs.CP2D.p[ 10 ].sw.l)
#define IR3  (gteRegs.CP2D.p[ 11 ].sw.l)
#define SXY0 (gteRegs.CP2D.p[ 12 ].d)
#define SX0  (gteRegs.CP2D.p[ 12 ].sw.l)
#define SY0  (gteRegs.CP2D.p[ 12 ].sw.h)
#define SXY1 (gteRegs.CP2D.p[ 13 ].d)
#define SX1  (gteRegs.CP2D.p[ 13 ].sw.l)
#define SY1  (gteRegs.CP2D.p[ 13 ].sw.h)
#define SXY2 (gteRegs.CP2D.p[ 14 ].d)
#define SX2  (gteRegs.CP2D.p[ 14 ].sw.l)
#define SY2  (gteRegs.CP2D.p[ 14 ].sw.h)
#define SXYP (gteRegs.CP2D.p[ 15 ].d)
#define SXP  (gteRegs.CP2D.p[ 15 ].sw.l)
#define SYP  (gteRegs.CP2D.p[ 15 ].sw.h)
#define SZ0  (gteRegs.CP2D.p[ 16 ].w.l)
#define SZ1  (gteRegs.CP2D.p[ 17 ].w.l)
#define SZ2  (gteRegs.CP2D.p[ 18 ].w.l)
#define SZ3  (gteRegs.CP2D.p[ 19 ].w.l)
#define RGB0 (gteRegs.CP2D.p[ 20 ].d)
#define R0   (gteRegs.CP2D.p[ 20 ].b.l)
#define G0   (gteRegs.CP2D.p[ 20 ].b.h)
#define B0   (gteRegs.CP2D.p[ 20 ].b.h2)
#define CD0  (gteRegs.CP2D.p[ 20 ].b.h3)
#define RGB1 (gteRegs.CP2D.p[ 21 ].d)
#define R1   (gteRegs.CP2D.p[ 21 ].b.l)
#define G1   (gteRegs.CP2D.p[ 21 ].b.h)
#define B1   (gteRegs.CP2D.p[ 21 ].b.h2)
#define CD1  (gteRegs.CP2D.p[ 21 ].b.h3)
#define RGB2 (gteRegs.CP2D.p[ 22 ].d)
#define R2   (gteRegs.CP2D.p[ 22 ].b.l)
#define G2   (gteRegs.CP2D.p[ 22 ].b.h)
#define B2   (gteRegs.CP2D.p[ 22 ].b.h2)
#define CD2  (gteRegs.CP2D.p[ 22 ].b.h3)
#define RES1 (gteRegs.CP2D.p[ 23 ].d)
#define MAC0 (gteRegs.CP2D.p[ 24 ].sd)
#define MAC1 (gteRegs.CP2D.p[ 25 ].sd)
#define MAC2 (gteRegs.CP2D.p[ 26 ].sd)
#define MAC3 (gteRegs.CP2D.p[ 27 ].sd)
#define IRGB (gteRegs.CP2D.p[ 28 ].d)
#define ORGB (gteRegs.CP2D.p[ 29 ].d)
#define LZCS (gteRegs.CP2D.p[ 30 ].d)
#define LZCR (gteRegs.CP2D.p[ 31 ].d)

#define R11 (gteRegs.CP2C.p[ 0 ].sw.l)
#define R12 (gteRegs.CP2C.p[ 0 ].sw.h)
#define R13 (gteRegs.CP2C.p[ 1 ].sw.l)
#define R21 (gteRegs.CP2C.p[ 1 ].sw.h)
#define R22 (gteRegs.CP2C.p[ 2 ].sw.l)
#define R23 (gteRegs.CP2C.p[ 2 ].sw.h)
#define R31 (gteRegs.CP2C.p[ 3 ].sw.l)
#define R32 (gteRegs.CP2C.p[ 3 ].sw.h)
#define R33 (gteRegs.CP2C.p[ 4 ].sw.l)
#define TRX (gteRegs.CP2C.p[ 5 ].sd)
#define TRY (gteRegs.CP2C.p[ 6 ].sd)
#define TRZ (gteRegs.CP2C.p[ 7 ].sd)
#define L11 (gteRegs.CP2C.p[ 8 ].sw.l)
#define L12 (gteRegs.CP2C.p[ 8 ].sw.h)
#define L13 (gteRegs.CP2C.p[ 9 ].sw.l)
#define L21 (gteRegs.CP2C.p[ 9 ].sw.h)
#define L22 (gteRegs.CP2C.p[ 10 ].sw.l)
#define L23 (gteRegs.CP2C.p[ 10 ].sw.h)
#define L31 (gteRegs.CP2C.p[ 11 ].sw.l)
#define L32 (gteRegs.CP2C.p[ 11 ].sw.h)
#define L33 (gteRegs.CP2C.p[ 12 ].sw.l)
#define RBK (gteRegs.CP2C.p[ 13 ].sd)
#define GBK (gteRegs.CP2C.p[ 14 ].sd)
#define BBK (gteRegs.CP2C.p[ 15 ].sd)
#define LR1 (gteRegs.CP2C.p[ 16 ].sw.l)
#define LR2 (gteRegs.CP2C.p[ 16 ].sw.h)
#define LR3 (gteRegs.CP2C.p[ 17 ].sw.l)
#define LG1 (gteRegs.CP2C.p[ 17 ].sw.h)
#define LG2 (gteRegs.CP2C.p[ 18 ].sw.l)
#define LG3 (gteRegs.CP2C.p[ 18 ].sw.h)
#define LB1 (gteRegs.CP2C.p[ 19 ].sw.l)
#define LB2 (gteRegs.CP2C.p[ 19 ].sw.h)
#define LB3 (gteRegs.CP2C.p[ 20 ].sw.l)
#define RFC (gteRegs.CP2C.p[ 21 ].sd)
#define GFC (gteRegs.CP2C.p[ 22 ].sd)
#define BFC (gteRegs.CP2C.p[ 23 ].sd)
#define OFX (gteRegs.CP2C.p[ 24 ].sd)
#define OFY (gteRegs.CP2C.p[ 25 ].sd)
#define H   (gteRegs.CP2C.p[ 26 ].sw.l)
#define DQA (gteRegs.CP2C.p[ 27 ].sw.l)
#define DQB (gteRegs.CP2C.p[ 28 ].sd)
#define ZSF3 (gteRegs.CP2C.p[ 29 ].sw.l)
#define ZSF4 (gteRegs.CP2C.p[ 30 ].sw.l)
#define FLAG (gteRegs.CP2C.p[ 31 ].d)

typedef union {
	struct {
		unsigned int	Index, Random, EntryLo0, BPC,
			Context, BDA, PIDMask, DCIC,
			BadVAddr, BDAM, EntryHi, BPCM,
			Status, Cause, EPC, PRid,
			Config, LLAddr, WatchLO, WatchHI,
			XContext, Reserved1, Reserved2, Reserved3,
			Reserved4, Reserved5, ECC, CacheErr,
			TagLo, TagHi, ErrorEPC, Reserved6;
	} n;
	unsigned int r[32];
} psxCP0Regs;

typedef union
{
	struct { unsigned char l, h, h2, h3; } b;
	struct { unsigned short l, h; } w;
	struct { char l, h, h2, h3; } sb;
	struct { short l, h; } sw;

	unsigned int d;
	int sd;
} PAIR;

typedef struct {
	unsigned char r, g, b, c;
} CBGR;

typedef struct {
	short x, y, z, pad;
} SVector3D;

typedef struct {
	short x, y;
} SVector2D;

typedef struct {
	short z, pad;
} SVector2Dz;

typedef union
{
	struct 
	{
		SVector3D    v0, v1, v2;
		CBGR         rgb;
		int          otz;
		int          ir0, ir1, ir2, ir3;
		SVector2D    sxy0, sxy1, sxy2, sxyp;
		SVector2Dz   sz0, sz1, sz2, sz3;
		CBGR         rgb0, rgb1, rgb2;
		int          reserved;
		int          mac0, mac1, mac2, mac3;
		unsigned int irgb, orgb;
		int          lzcs, lzcr;
	} n;
	
	unsigned int r[32];
	PAIR p[32];

} psxCP2Data;

typedef struct {
	short m11, m12, m13, m21, m22, m23, m31, m32, m33, pad;
} SMatrix3D;

typedef union
{
	struct {
		SMatrix3D rMatrix;
		int      trX, trY, trZ;
		SMatrix3D lMatrix;
		int      rbk, gbk, bbk;
		SMatrix3D cMatrix;
		int      rfc, gfc, bfc;
		int      ofx, ofy;
		int      h;
		int      dqa, dqb;
		int      zsf3, zsf4;
		int      flag;
	} n;
	unsigned int r[32];
	PAIR p[32];
} psxCP2Ctrl;

typedef struct
{
	psxCP0Regs CP0;  /* Coprocessor0 Registers */
	psxCP2Data CP2D; /* Cop2 data registers */
	psxCP2Ctrl CP2C; /* Cop2 control registers */
} GTERegisters;

GTERegisters gteRegs;

void InitGeom()
{
	UNIMPLEMENTED();
}

void SetGeomOffset(int ofx, int ofy)
{
	OFX = ofx << 16;
	OFY = ofy << 16;
}

void SetGeomScreen(int h)
{
	H = h;
}
