#ifndef MISSILE_H
#define MISSILE_H

#include "SPECTYPES.H"

extern struct ITEM_LIGHT fxil;

extern void ControlBodyPart(short fx_number);
extern int ExplodeFX(struct FX_INFO *fx, int NoXZVel, long bits);

#endif