#ifndef BUBBLES_H
#define BUBBLES_H

extern void SetInventoryLighting(int rgb0, int rgb1, int rgb2, int rgb3);
extern void DrawMonoScreen(int a0);
extern void DrawFlash();
extern void insert_psx_clip_window(long x, long y, long w, long h, long arg_10);
extern void CalcClipWindow_ONGTE(short room_number, long unknown);
extern void DrawPsxTile(long a0, long a1, long a2, long a3);
extern void TriggerDynamic(long x, long y, long z, int falloff, int r, int g, int b);
extern void DEL_ApplyMatrixSV(int v0, int v1, short* m);

#endif