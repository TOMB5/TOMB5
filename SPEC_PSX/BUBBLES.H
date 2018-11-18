#ifndef BUBBLES_H
#define BUBBLES_H

extern void DrawMonoScreen(int a0);
extern void DrawFlash();
extern void insert_psx_clip_window(long x, long y, long w, long a3, long h);
extern void CalcClipWindow_ONGTE(short room_number, long unknown);
extern void DrawPsxTile(long a0, long a1, long a2, long a3);
extern void S_DrawSparks();

#endif