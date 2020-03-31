#ifndef DELTAPAK_S_H
#define DELTAPAK_S_H

extern void DrawCutSeqActors();
extern void updateAnimFrame(struct PACKNODE* node, int flags, short* frame);
extern void DecodeAnim(struct PACKNODE* node, int a1, int frame, short a3);

#endif