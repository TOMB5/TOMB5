#ifndef GPU_H
#define GPU_H

#include "SPECTYPES.H"

#include <sys/types.h>
#include <LIBAPI.H>
#include <LIBGTE.H>
#include <LIBGPU.H>

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

extern void GPU_UseOrderingTables(unsigned long* pBuffers, int nOTSize);
extern void GPU_UsePolygonBuffers(unsigned long* pBuffers, int nPBSize);
extern void GPU_BeginScene();
extern void GPU_EndScene();
extern int GPU_FlipNoIdle();
extern void GPU_FlipStory(unsigned long* gfx);
extern void GPU_SyncBothScreens();
extern void GPU_ClearVRAM();
extern void GPU_FlipToBuffer(int buffer_index);
extern void GPU_GetScreenPosition(short* x, short* y);
extern void GPU_SetScreenPosition(short x, short y);
extern void clear_a_rect(RECT* r);
extern long OptimiseOTagR(unsigned long* ot, int nOTSize);
extern void draw_rotate_sprite(long a0, long a1, long a2);

#endif