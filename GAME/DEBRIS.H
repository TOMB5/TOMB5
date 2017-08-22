#ifndef DEBRIS_H
#define DEBRIS_H

#include "SPECTYPES.H"

extern struct DEBRIS_STRUCT debris[128];
extern short DebrisFlags;
extern long next_debris;
extern struct SHATTER_ITEM ShatterItem;

extern void ShatterObject(struct SHATTER_ITEM *ShatterItem, struct MESH_INFO *StaticMesh, short Num, short RoomNumber, int NoXZVel);
extern void TriggerDebris(struct GAME_VECTOR *pos, void *TextInfo, short *Offsets, long *Vels, int rgb);
extern long GetFreeDebris();

#endif