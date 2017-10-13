#ifndef GPU_H
#define GPU_H

#include "SPECTYPES.H"

#include <SDL.h>

extern unsigned long GnFrameCounter;
extern unsigned long GnLastFrameCount;
extern PSXTEXTSTRUCT* psxtextinfo;
extern PSXSPRITESTRUCT* psxspriteinfo;
extern int rgbscaleme;
extern int gfx_debugging_mode;
extern DB_db;
extern MMTEXTURE* RoomTextInfo;
extern unsigned long GadwOrderingTables_V2[512];
extern unsigned long GadwOrderingTables[5128];
extern unsigned long GadwPolygonBuffers[52260];

extern void GPU_UseOrderingTables(unsigned long* pBuffers, int nOTSize);
extern void GPU_UsePolygonBuffers(unsigned long* pBuffers , int nPBSize);
extern void GPU_BeginScene();
extern void GPU_EndScene();
extern int GPU_FlipNoIdle();
extern void GPU_SyncBothScreens();
extern void GPU_GetScreenPosition(short* x, short* y);
extern void GPU_ClearVRAM();
extern void GPU_FlipToBuffer(int buffer_index);
extern void GPU_SetScreenPosition(short x, short y);
extern SDL_Window* g_window;

#endif