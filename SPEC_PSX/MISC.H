#ifndef MISC_H
#define MISC_H

#include <SYS\TYPES.H>
#include <LIBGTE.H>
#include <LIBGPU.H>

extern void S_LongMemCpy(unsigned long* pDest, unsigned long* pSrc, unsigned long size);
extern void DrawF4(unsigned short x, unsigned short y, unsigned short w, unsigned short h, unsigned short unk, unsigned short unk2);
extern void DrawTPage(unsigned char a0, unsigned char a1);
extern void DrawLineH(long a0, long a1, long a2, long a3);
extern void DrawLineV(long a0, long a1, long a2, long a3);
extern void LOAD_VSyncHandler();
extern void LOAD_DrawEnable(unsigned char isEnabled);
extern void GPU_BeginScene();
extern void draw_rotate_sprite(long a0, long a1, long a2);
extern void GPU_ClearVRAM();
extern void clear_a_rect(RECT* r);
extern void GPU_GetScreenPosition(short* x, short* y);
extern void GPU_SetScreenPosition(short x, short y);
extern void GPU_SyncBothScreens();
extern void GPU_FlipToBuffer(int buffer_index);
extern void S_AnimateTextures(long nFrames);

#endif