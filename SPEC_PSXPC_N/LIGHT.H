#ifndef LIGHT_H
#define LIGHT_H

#include "STYPES.H"

extern void S_CalculateStaticMeshLight(long floor, long touch_bits, long mesh_bits, int anim_state);
extern void CalculateObjectLighting(struct ITEM_INFO* item, short* frmptr, struct STASHEDOBJ* sobject, short numnodestodraw, int anim_state);

#endif