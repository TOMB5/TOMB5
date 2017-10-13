#ifndef DEBRIS_H
#define DEBRIS_H

#include "SPECTYPES.H"

extern DEBRIS_debris[128];
extern short DebrisFlags;
extern long next_debris;
extern SHATTER_ITEM ShatterItem;

extern void ShatterObject(SHATTER_ITEM* ShatterItem, MESH_INFO* StaticMesh, short Num, short RoomNumber, int NoXZVel);
extern void TriggerDebris(GAME_VECTOR* pos, void* TextInfo, short* Offsets, long* Vels, int rgb);
extern long GetFreeDebris();

#endif