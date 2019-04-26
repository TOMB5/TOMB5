#ifndef GPU_H
#define GPU_H

#include "STYPES.H"

//#include <sys/types.h>
#include <LIBGPU.H>

extern unsigned long GnFrameCounter;
extern unsigned long GnLastFrameCount;
extern struct PSXTEXTSTRUCT* psxtextinfo;
extern struct PSXSPRITESTRUCT* psxspriteinfo;
extern int rgbscaleme;
extern int gfx_debugging_mode;
extern struct DB_STRUCT db;
extern struct MMTEXTURE* RoomTextInfo;
#if __linux__ || __APPLE__
extern unsigned long* GadwOrderingTables_V2;
extern unsigned long* GadwOrderingTables;
extern unsigned long* GadwPolygonBuffers;
#else
extern unsigned long GadwOrderingTables_V2[];
extern unsigned long GadwOrderingTables[];
extern unsigned long GadwPolygonBuffers[];
#endif

extern void GPU_UseOrderingTables(unsigned long* pBuffers, int nOTSize);
extern void GPU_UsePolygonBuffers(unsigned long* pBuffers, int nPBSize);
extern void GPU_EndScene();
extern int GPU_FlipNoIdle();
extern void do_gfx_debug_mode(unsigned long* otstart);
extern void GPU_FlipStory(unsigned long* gfx);

#define SCREEN_WIDTH 512

#if NTSC_VERSION
#define SCREEN_HEIGHT 240
#else
#define SCREEN_HEIGHT 256
#endif

#endif