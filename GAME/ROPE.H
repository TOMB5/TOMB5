#ifndef ROPE_H
#define ROPE_H

#include "TYPES.H"

extern void SaveRope();
extern void LoadRope();
extern void Straighten(struct ROPE_STRUCT* a1, struct PHD_VECTOR* a2, struct PHD_VECTOR* a3, long a4);
extern void StraightenRope(struct ITEM_INFO* item);

#endif