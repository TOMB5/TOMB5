#ifndef MISSILE_H
#define MISSILE_H

#include "SPECTYPES.H"

extern ITEM_LIGHT fxil;

extern void ControlBodyPart(short fx_number);
extern int ExplodeFX(FX_INFO* fx, int NoXZVel, long bits);

#endif